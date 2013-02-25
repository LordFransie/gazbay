<?php

/**
 * @file
 * Handles compiling of .sass / .scss files.
 */

/**
 * Flag for alter hooks that are executed before the SASS parser.
 */
define('NINESIXTYFIVE_PRECOMPILE', 'NINESIXTYFIVE_PRECOMPILE');

/**
 * Flag for alter hooks that are executed after the SASS parser.
 */
define('NINESIXTYFIVE_POSTCOMPILE', 'NINESIXTYFIVE_POSTCOMPILE');



/**
 * Implementation of hook_element_info_alter().
 */
function ninesixtyfive_element_info_alter(&$type) {
  array_unshift($type['styles']['#pre_render'], 'ninesixtyfive_pre_render');
  // Show development messages once an hour.
  if (theme_get_setting('ninesixtyfive_clear_registry') && user_access('administer site configuration') && flood_is_allowed('ninesixtyfive_registry_warning', 1)) {
    flood_register_event('ninesixtyfive_registry_warning');
    drupal_set_message(t('Your theme registry is being rebuilt on every page request. Don\'t forget to <a href="!link">disable this feature</a> before going public.', array('!link' => url('admin/appearance/settings/ninesixtyfive'))), 'warning');
  }
  if (theme_get_setting('ninesixtyfive_devel') && user_access('administer site configuration') && flood_is_allowed('ninesixtyfive_devel_warning', 1)) {
    flood_register_event('ninesixtyfive_devel_warning');
    drupal_set_message(t('Your SASS / SCSS files are being recompiled on every page request. Don\'t forget to <a href="!link">disable this feature</a> before going public.', array('!link' => url('admin/appearance/settings/ninesixtyfive'))), 'warning');
  }
}

/**
 * Builds the SASS cache. Should only be invoked by drupal_render().
 *
 * @param $elements
 *   A render array containing:
 *   '#items': The CSS items as returned by drupal_add_css() and altered by
 *   drupal_get_css().
 *   '#group_callback': A function to call to group #items to enable the use of
 *   fewer tags by aggregating files and/or using multiple @import statements
 *   within a single tag.
 *   '#aggregate_callback': A function to call to aggregate the items within the
 *   groups arranged by the #group_callback function.
 *
 * @return $elements
 *   The modified (pre-rendered) $elements parameter.
 */
function ninesixtyfive_pre_render($elements) {
  $map = $original = variable_get('ninesixtyfive_cache', array());
  $files = ninesixtyfive_pick_files($elements['#items']);
  $devel = theme_get_setting('ninesixtyfive_devel');
  // We can bail out here if there are no SCSS files anyways.
  if (function_exists('drupal_get_path')) {
    $inc = DRUPAL_ROOT . '/' . drupal_get_path('theme', 'ninesixtyfive') . "/phamlp/sass/SassParser.php";
    if (is_file($inc)) {
      require_once $inc;
    }
    else {
      return;
    }
  }
  if (empty($files)) {
    // Remove the files from the array of stylesheets.
    $elements['#items'] = array_diff_key($elements['#items'], $files);
    return $elements;
  }
  foreach ($files as $key => $file) {
    // Create a unique identifier for the file.
    if ($file['recompile'] !== TRUE) {
      $hash = hash('sha256', serialize($file));
      $path = isset($map[$hash]) ? $map[$hash] : NULL;
    }
    // We recompile this file if recompile equals TRUE, array (and thereby the
    // hash value) changed, if the file doesn't exist, or if we are in development
    // mode. NOTE: You can use the 'recompile' array for your CSS files to cache
    // them based on advanced criteria.
    if ($devel || $file['recompile'] === TRUE || !isset($path) || !file_exists($path)) {
      $data = ninesixtyfive_load_stylesheet($file['data']);
      if (!$output = ninesixtyfive_parse($data, $file, $file['syntax'])) {
        unset($elements['#items'][$key]);
        continue;
      }
      $directory = 'public://ninesixtyfive';
      $path = $directory . '/' . drupal_hash_base64($output) . '.css';
      // Create the CSS file.
      file_prepare_directory($directory, FILE_CREATE_DIRECTORY);
      if (!file_exists($path) && !file_unmanaged_save_data($output, $path, FILE_EXISTS_REPLACE)) {
        unset($elements['#items'][$key]);
        continue;
      }
    }
    // Update the item in the stylesheets array.
    $elements['#items'][$key] = $file;
    $elements['#items'][$key]['data'] = $path;
    //drupal_add_css($path, $elements['#items'][$key]);
    if ($file['recompile'] !== TRUE) {
      // Don't cache this item if it is set to recompile on every page load.
      $map[$hash] = $path;
    }
  }
  // If $map and $original don't match anymore that means we need to update the
  // CSS cache.
  if ($original !== $map) {
    variable_set('ninesixtyfive_cache', $map);
  }
  
  return $elements;
}

/**
 * Picks all SCSS and SASS files from an array of stylesheets.
 *
 * @param $items
 *   An array of stylesheets.
 *
 * @return
 *   The extracted files as an array.
 */
function ninesixtyfive_pick_files($items) {
  $files = array();
  foreach ($items as $key => $file) {
    if ($file['type'] == 'file') {
      $extension = drupal_substr($file['data'], -5);
      if (in_array($extension, array('.scss', '.sass'))) {
        $file['syntax'] = $extension == '.scss' ? 'scss' : 'sass';
        $file['recompile'] = isset($file['recompile']) ? $file['recompile'] : FALSE;
        // If the file is set to recompile on every page load then we don't want
        // it to be aggregated.
        $file['preprocess'] = !empty($file['recompile']) ? FALSE : $file['preprocess'];
        $files[$key] = $file;
      }
    }
  }
  return $files;
}

/**
 * Loads a stylesheet and writes the base path to all url declarations.
 *
 * @param $file
 *   A filepath or an array representing a stylesheet.
 *
 * @return
 *   A string that represents the processed contents of the stylesheet.
 */
function ninesixtyfive_load_stylesheet($file) {
  $file = is_array($file) ? $file['data'] : $file;
  $data = drupal_load_stylesheet($file);
  // Build the base URL of this CSS file. Start with the full URL.
  $base = file_create_url($file);
  // Move to the parent.
  $base = substr($base, 0, strrpos($base, '/'));
  // Simplify to a relative URL if the stylesheet URL starts with the base URL
  // of the website.
  if (substr($base, 0, strlen($GLOBALS['base_root'])) == $GLOBALS['base_root']) {
    $base = substr($base, strlen($GLOBALS['base_root']));
  }
  _drupal_build_css_path(NULL, $base . '/');
  // Anchor all paths in the CSS with its base URL, ignoring external and
  // absolute paths.
  $data = preg_replace_callback('/url\(\s*[\'"]?(?![a-z]+:|\/+)([^\'")]+)[\'"]?\s*\)/i', '_drupal_build_css_path', $data);
  $data = preg_replace("/url\(([^'\")]+)\)/i", "url('$1')", $data);
  return $data;
}

/**
 * Parse a SCSS string and transform it into CSS.
 *
 * @params $data
 *   A SCSS string.
 * @param $file
 *   The SASS or SCSS file that $data belongs to described by an array.
 * @param $syntax
 *   The syntax (SASS or SCSS) of the file contents. This information is needed
 *   by the parser.
 *
 * @return
 *   The transformed CSS as a string.
 */
function ninesixtyfive_parse($data, $file, $syntax) {
  try {
    $data = ninesixtyfive_get_libraries($syntax) . "\n\n" . $data;
    $info = array('file' => $file, 'syntax' => $syntax, 'iteration' => NINESIXTYFIVE_PRECOMPILE);
    drupal_alter('ninesixtyfive', $data, $info);
    // Remove all media queries
    $placeholders = _ninesixtyfive_match_media_queries($data);
    $data = str_replace($placeholders, array_keys($placeholders), $data);
    // Match variables for later replacement inside media queries.
    $variables = _ninesixtyfive_match_variables($data);
    // Quote all url(..) to ensure PhamlP doesn't strip them.
    $data = preg_replace("/url\(([^'\")]+)\)/i", "url('$1')", $data);
    // Are we in development mode ?
    $devel = theme_get_setting('ninesixtyfive_devel');
    $style = $devel ? 'nested' : 'compressed';
    // Watch all enabled themes for partials
    $themes = list_themes();
    $paths = array();
    $paths[] = drupal_get_path('theme', 'ninesixtyfive') . "/includes/";
    foreach ($themes as $theme) {
      if ($theme->status) {
        $paths[] = drupal_get_path('theme', $theme->name);
      }
    }
    // Execute the compiler.
    $parser = new SassParser(array(
      'style' => $style,
      'cache' => FALSE,
      'syntax' => $syntax,
      'load_paths' => $paths, // fix by http://code.google.com/p/phamlp/issues/detail?id=108
      'debug_info' => $devel,
      'extensions' => array('compass' => array()),
    ));
    // parsing the data content of the file.
    //$data = $parser->toCss($data, FALSE); 

    //parsing the file.
    $data = $parser->parse($file['data'])->render();
    
    // Replace the media queries and then any variables inside those media queries.
    $data = str_replace(array_keys($placeholders), $placeholders, $data);
    $data = str_replace(array_keys($variables), $variables, $data);
    $info = array('file' => $file, 'syntax' => $syntax, 'iteration' => NINESIXTYFIVE_POSTCOMPILE);
    drupal_alter('ninesixtyfive', $data, $info);
    return $data;
  }
  catch (Exception $e) {
    watchdog_exception('ninesixtyfive', $e);
    if (user_access('administer site configuration')) {
      drupal_set_message(t('An error occured while processing !stylesheet. Please consult your !watchdog for a detailed error description.', array('!stylesheet' => l(basename($file['data']), $file['data']), '!watchdog' => l('log messages', 'admin/reports/dblog'))), 'error');
    }
  }
}

/**
 * Fetches, caches and returns all SASS / SCSS libraries from all enabled
 * modules and the theme trail.
 *
 * @param $syntax
 *   The syntax (SASS or SCSS) of the file contents. This information is needed
 *   by the parser.
 *
 * @return
 *   A string representing the cummulated content of all library files for
 *   the given syntax.
 */
function ninesixtyfive_get_libraries($syntax) {
  $libraries = &drupal_static(__FUNCTION__);
  if (!isset($libraries)) {
    if (!theme_get_setting('ninesixtyfive_devel') && $cache = cache_get('ninesixtyfive_libraries:' . $GLOBALS['theme_key'] . '')) {
      $libraries = $cache->data;
    }
    else {
      $libraries = array('sass' => array(), 'scss' => array());
      // Load libraries from all enabled modules.
      foreach (system_get_info('module') as $module => $info) {
        if (!empty($info['ninesixtyfive'])) {
          foreach ($info['ninesixtyfive'] as $library) {
            $extension = drupal_substr($library, -5);
            if (in_array($extension, array('.scss', '.sass'))) {
              $current = $extension == '.scss' ? 'scss' : 'sass';
              $path = drupal_get_path('module', $module) . '/' . $library;
              $libraries[$current][$path] = $path;
            }
          }
        }
      }
      // Load libraries from the theme trail.
      foreach (array_merge($GLOBALS['base_theme_info'], array($GLOBALS['theme_info'])) as $info) {
        if (!empty($info->info['ninesixtyfive'])) {
          foreach ($info->info['ninesixtyfive'] as $library) {
            $extension = drupal_substr($library, -5);
            if (in_array($extension, array('.scss', '.sass'))) {
              $current = $extension == '.scss' ? 'scss' : 'sass';
              $path = drupal_get_path('theme', $info->name) . '/' . $library;
              $libraries[$current][$path] = $path;
            }
          }
        }
      }
      drupal_alter('ninesixtyfive_libraries_scss', $libraries['scss']);
      drupal_alter('ninesixtyfive_libraries_sass', $libraries['sass']);
      $libraries['scss'] = implode("\n\n", array_map('ninesixtyfive_load_stylesheet', $libraries['scss']));
      $libraries['sass'] = implode("\n\n", array_map('ninesixtyfive_load_stylesheet', $libraries['sass']));
      cache_set('ninesixtyfive_libraries:' . $GLOBALS['theme_key'], $libraries);
    }
  }
  if (isset($libraries[$syntax])) {
    return $libraries[$syntax];
  }
}

/**
 * Extract SCSS variables from a SCSS string.
 *
 * @param $data
 *   A SCSS string.
 *
 * @return
 *   An array of variable values, indexed by the variable name.
 */
function _ninesixtyfive_match_variables($data) {
  $variables = array();
  preg_match_all('/(^|\\n)\$([^\s]+): (.+);/', $data, $matches);
  foreach ($matches[2] as $key => $value) {
    $variables['$' . $value] = $matches[3][$key];
  }
  return $variables;
}

/**
 * Extracts all media queries from an SCSS string and replace them with named
 * placeholders.
 *
 * @param $data
 *   A SCSS string.
 *
 * @return
 *   An array of placeholders values, indexed by the placeholder token.
 */
function _ninesixtyfive_match_media_queries($data) {
  $placeholders = array();
  preg_match_all('/@media\s*(.+)\s*\{/', $data, $matches);
  foreach($matches[1] as $key => $value) {
    $placeholders['ninesixtyfive_media_query_' . $key] = $value;
  }
  return $placeholders;
}
