<?php

/**
 * Implements hook_menu_local_task()
 *
 * @param array $variables
 *
 * return string with html
 */
function gazprom_menu_local_task($variables) {
  $link = $variables['element']['#link'];
  // remove the view link when viewing the node
  if ($link['path'] == 'node/%/view') return false;
  $link['localized_options']['html'] = TRUE;
  return '<li>'.l($link['title'], $link['href'], $link['localized_options']).'</li>'."\n";
}

/**
 * Implements hook_menu_local_task()
 *
 * @param array $variables
 *
 * return string with html
 */
function gazprom_menu_local_tasks(&$variables) {
  $output = '';
  $has_access = user_access('access contextual links');
  if (!empty($variables['primary'])) {
    $variables['primary']['#prefix'] = '<h2 class="element-invisible">' . t('Primary tabs') . '</h2>';

    // Only display contextual links if the user has the correct permissions enabled.
    // Otherwise, the default primary tabs will be used.
    $variables['primary']['#prefix'] = ($has_access) ?
      '<div class="contextual-links-wrapper"><ul class="contextual-links">' : '<ul class="tabs primary">';

    $variables['primary']['#suffix'] = ($has_access) ?
      '</ul></div>' : '</ul>';
    $output .= drupal_render($variables['primary']);
  }
  if (!empty($variables['secondary'])) {
    $variables['secondary']['#prefix'] = '<h2 class="element-invisible">' . t('Secondary tabs') . '</h2>';
    $variables['secondary']['#prefix'] = '<ul class="tabs secondary clearfix">';
    $variables['secondary']['#suffix'] = '</ul>';
    $output .= drupal_render($variables['secondary']);
  }
  return $output;

  /*
   * This function depends on the CSS class of 'contextual-links-region' to be added to the right parent DIV
   * of this .contextual-links-wrapper div. (probably in page.tpl.php for the div with class="section" that displays
   * the node.
   */
}

/**
 * Implements template_preprocess_page()
 * 
 */
function gazprom_preprocess_page(&$vars) {
  
  // catch errors and react 
  if (arg(0) == 'customerror') {
    
  }
  
  // we need to correctly id the .content-wrapper div for this page
  $vars['room_id'] = preg_replace('/[^a-z0-9]/','-', strtolower(request_path()));
  if (drupal_is_front_page()) $vars['room_id'] = 'home';

  $templates = array();
  // add template candidates for page's URL alias
  // (original code from http://drupal.org/node/139766)
  if (module_exists('path')) {
      //$alias = strtolower(request_path());
      $alias = drupal_get_path_alias();
      // @TODO multilingual issues?
      $suggestions = array();
      $template_filename = 'page_';
      foreach (explode('/', $alias) as $path_part) {
        if (!empty($path_part)) {
          $template_filename = $template_filename . '_' . $path_part;
          $templates[] = $template_filename;
        }
      }
    // @TODO NOT WORKING!!! see page--locations-world-map.tpl.php (never gets called)
  }
  // specific template candidate for front page
  if (drupal_is_front_page()) {
      $templates[] = 'page__front';
  }
  $vars['theme_hook_suggestions'] = array_merge($vars['theme_hook_suggestions'],$templates); // most important go LAST (there is a array_reverse call in theme.inc)

  // specific template candidate for pages loaded into the overlay @TODO consider an ajax test? more of these types of pages?
  if (isset($_GET['overlay'])) {
    $templates = array();
    $templates[] = 'page__overlay';
    foreach($vars['theme_hook_suggestions'] as $template) {
      $templates[] = $template . '__overlay';
    }
    $vars['theme_hook_suggestions'] = array_merge($vars['theme_hook_suggestions'],$templates); // most important go LAST (there is a array_reverse call in theme.inc)
  }
  
  // test for AJAX request and suggest alternate templates
  if(isset($_GET['ajax']) || (isset($_SERVER['HTTP_X_REQUESTED_WITH']) && strtolower($_SERVER['HTTP_X_REQUESTED_WITH']) == 'xmlhttprequest')) {
    $templates = array();
    $templates[] = 'page__ajax';
    foreach($vars['theme_hook_suggestions'] as $template) {
      $templates[] = $template . '__ajax';
    }
    $vars['theme_hook_suggestions'] = array_merge($vars['theme_hook_suggestions'],$templates); // most important go LAST (there is a array_reverse call in theme.inc)
  }

  // we need window title to be embedded in page for hijax purposes
  // (code copies from theme.inc template_preprocess_html() )
  // Construct page title.
  if (drupal_get_title()) {
    $head_title = array(
      'title' => strip_tags(drupal_get_title()),
      'name' => check_plain(variable_get('site_name', 'Drupal')),
    );
  }
  else {
    $head_title = array('name' => check_plain(variable_get('site_name', 'Drupal')));
    if (variable_get('site_slogan', '')) {
      $head_title['slogan'] = filter_xss_admin(variable_get('site_slogan', ''));
    }
  }
  $vars['head_title_array'] = $head_title;
  $vars['head_title'] = implode(' | ', $head_title);
  if ($vars['is_front'] == true) {
    $vars['head_title'] = $head_title['name'];
    $vars['head_title_array'] = array('name' => $head_title['name']);
  }

  // until we fully embrace the Ajax Framework, we must force these elements
  // .. to load so we always have the right JS files loaded regardless of which page
  // .. is initially loaded (support for deep linking)
  drupal_add_library('system', 'drupal.ajax');
  drupal_add_library('system', 'jquery.form');
  
  // hack in necessary JS and/or CSS files from modules we are depending on
  // @TODO .. really need to explore Drupal's AJAX functions which supposedly will add the JS during AJAX calls
  if (true || ($vars['is_front'] == true)) {
   drupal_add_js(drupal_get_path('module', 'image_swapper') . '/image_swapper.js');
   drupal_add_js(drupal_get_path('module', 'image_zoom') . '/image_zoom.js');
    
    // also see the microsite.module's microsite_preprocess_page() function which is essentially doing the same thing as here
  }
  
  // add OpenLayers CSS and JS
  if (false && ($vars['is_front'] == true) && (module_exists('openlayers'))) {
      $block = module_invoke('views', 'block_view', 'interacti-block_1');
      //$vars['offstage_map'] = render($block);
      $vars['page']['offstage_map'] = $block;

  //  openlayers_include();
      // @TOOD really shouldn't invole the block here (since we're not really going to render it here), but we need the CSS and JS to be added to the home page
      // .. and coudn't get ajax framework methods to work to insert the CSS and JS into our page .. so doing this instead.. not so bad because we can probably cache
      // .. the block anyway
  }
  
  // HUGE hack for required JS - quicktabs (for management page)'
  $block = module_invoke('quicktabs', 'block_view', 'management_tabs');
  render($block);
  // @TODO we REALLY need to use Drupal's AJAX Framework!!

  
  // add useful settings to JS (in addition to what was done in preprocess_html()
  drupal_add_js(array(
    'gazprom' => array(
        'front_page' => $vars['front_page'],
        )), 'setting');

  }

/**
 * Implements template_preprocess_node().
 *
 */
function gazprom_preprocess_node(&$vars) {

  $url_prefix = $GLOBALS['base_path'];
  if (!empty($GLOBALS['language_url'])) {
    $url_prefix .= $GLOBALS['language_url']->prefix;
  }
  $vars['url_prefix'] = $url_prefix;
  // @TODO is this already stored somewhere for us? need it in node--front-tpl.php (for RSS feed URL)

  // add template candidates for page's URL alias
  // (code from http://drupal.org/node/139766)
  if (module_exists('path')) {
      $alias = drupal_get_path_alias();
      $suggestions = array();
      $template_filename = 'node_';
      foreach (explode('/', $alias) as $path_part) {
        if (!empty($path_part)) {
          $template_filename = $template_filename . '_' . $path_part;
          $templates[] = $template_filename;
        }
      }
  }
  // specific template candidate for front page
  if ($vars['is_front'] && empty($vars['node']->view)) {
      $templates[] = 'node__front';
  }
  $vars['theme_hook_suggestions'] = array_merge($vars['theme_hook_suggestions'],$templates); // most important go LAST (there is a array_reverse call in theme.inc)

  // ^^^^^^^ the above code has problems: When you do a node_view() call, the code above inherits vars from the parent node

   // specific template candidate for pages loaded into the overlay @TODO consider an ajax test? more of these types of pages?
  if (isset($_GET['overlay'])) {
    $templates = array();
    $templates[] = 'node__overlay';
    foreach($vars['theme_hook_suggestions'] as $template) {
      $templates[] = $template . '__overlay';
    }
    $vars['theme_hook_suggestions'] = array_merge($vars['theme_hook_suggestions'],$templates); // most important go LAST (there is a array_reverse call in theme.inc)
  }
 
  // if available, add special CSS classes to the varaibles for rendering
  $css_classes_field = field_get_items('node', $vars['node'], 'field_css_classes');
  $css_classes = $css_classes_field[0]['safe_value'];
  foreach(preg_split('/ /', $css_classes) as $class) {
    $vars['classes_array'][] = $class;
  }
  
  // typically a node type that is supposed to open in overlay has a special class
  // .. in the template. For Page and Code Page node types, we need to determine if
  // .. this node belongs in an overlay (for when accessed by a deep link)
  if (($vars['node']->type == 'page' || $vars['node']->type == 'page_code') 
          && !$vars['is_front']
          && substr(drupal_get_path_alias(), 0, 6) != 'error/') {
    $menu = menu_get_active_trail();
    if (!empty($menu[1])) {
      if ($menu[1]['menu_name'] != 'main-menu') {
        $vars['classes_array'][] = 'open-in-overlay';
      }
    } else {
      $vars['classes_array'][] = 'open-in-overlay';
    }
  }
  // @TODO is this good enough?

  
}


/**
 * Contextually adds 960 Grid System classes.
 *
 * The first parameter passed is the *default class*. All other parameters must
 * be set in pairs like so: "$variable, 3". The variable can be anything available
 * within a template file and the integer is the width set for the adjacent box
 * containing that variable.
 *
 *  class="<?php print ns('grid-16', $var_a, 6); ?>"
 *
 * If $var_a contains data, the next parameter (integer) will be subtracted from
 * the default class. See the README.txt file.
 */
function ns() {
  $args = func_get_args();
  $default = array_shift($args);
  // Get the type of class, i.e., 'grid', 'pull', 'push', etc.
  // Also get the default unit for the type to be procesed and returned.
  list($type, $return_unit) = explode('_', $default);

  // Process the conditions.
  $flip_states = array('var' => 'int', 'int' => 'var');
  $state = 'var';
  foreach ($args as $arg) {
    if ($state == 'var') {
      $var_state = !empty($arg);
    }
    elseif ($var_state) {
      $return_unit = $return_unit - $arg;
    }
    $state = $flip_states[$state];
  }

  $output = '';
  // Anything below a value of 1 is not needed.
  if ($return_unit > 0) {
    $output = $type . '_' . $return_unit;
  }
  return $output;
}

/**
 * Implements template_preprocess_html().
 */
function gazprom_preprocess_html(&$vars) {

  $query_parameters = drupal_get_query_parameters();
  if (isset($query_parameters['mode'])) {
    setcookie('gazprom-mode', $query_parameters['mode'], 0, '/');
  }
  // test for simple mode
  $simpleMode = false;
  if (isset($query_parameters['simple']) && (strtolower($query_parameters['simple']) != 'false')) {
    setcookie('gazprom-simple', 'true', 0, '/');
    $simpleMode = true;
  } else if (isset($query_parameters['simple']) && (strtolower($query_parameters['simple']) == 'false')) {
    setcookie('gazprom-simple', null, 0, '/');
    $simpleMode = false;
  } else if (isset($_COOKIE['gazprom-simple'])) {
    $simpleMode = true;
  }
  
  // test for single-page mode
  $singlePageMode = false;
  if ($simpleMode == 'true') {
    $singlePageMode = true;
  } else if (isset($query_parameters['singlePageMode']) && (strtolower($query_parameters['singlePageMode']) != 'false')) {
    setcookie('gazprom-single-page', 'true', 0, '/');
    $singlePageMode = true;
  } else if (isset($query_parameters['singlePageMode']) && (strtolower($query_parameters['singlePageMode']) == 'false')) {
    setcookie('gazprom-single-page', null, 0, '/');
    $singlePageMode = false;
  } else if (isset($_COOKIE['gazprom-single-page'])) {
    $singlePageMode = true;
  }
  if ($singlePageMode) {
    $vars['classes_array'][] = 'singlePageMode';
  }
  
  
  // add useful settings to JS
  drupal_add_js(array(
      'gazprom' => array(
          'pathToTheme' => path_to_theme()
          //'singlePageMode' => ($singlePageMode ? 'true' : 'false'),
          //'simpleMode' => ($simpleMode ? 'true' : 'false'),
          )), 'setting');

  // set the title for the front page
  // @TODO there has to be a better way to do this?
  if ($vars['is_front'] == true) {
    $vars['head_title'] = check_plain(variable_get('site_name', 'Drupal'));
    $vars['head_title_array'] = array('name' => $vars['head_title']);
    $vars['head_array'] = array('title' => $vars['head_title']);
  }

    // test for AJAX request and suggest alternate templates
  $variable_test = variable_get('boost_enabled_text/html');
  $module_test = module_exists('boost');
  if ((isset($_GET['ajax']) || (isset($_SERVER['HTTP_X_REQUESTED_WITH']) && strtolower($_SERVER['HTTP_X_REQUESTED_WITH']) == 'xmlhttprequest'))
          && !(variable_get('boost_enabled_text/html') == 1 && module_exists('boost'))) {
    $templates = array();
    $templates[] = 'html__ajax';
    foreach($vars['theme_hook_suggestions'] as $template) {
      $templates[] = $template . '__ajax';
    }
    $vars['theme_hook_suggestions'] = array_merge($vars['theme_hook_suggestions'],$templates); // most important go LAST (there is a array_reverse call in theme.inc)
  }


}

/*
 * Implementation of theme_field()
 * Returns HTML for the field_background_image field
 */
function gazprom_field__field_background_image($vars) {
  $output = '';

  $output .= '<div class="to-background backgrounder">';
  foreach ($vars['items'] as $delta => $item) {
    $item['#item']['attributes']['class'][] = 'fancy-background-image';
    unset($item['#item']['width']);
    unset($item['#item']['height']);
    $output .= drupal_render($item); // calls gazprom_image_formatter() below (in place of theme_image_formatter())
  }
  $output .= '</div><!-- /.backgrounder -->';

  return $output;
  
  // @TODO consider moving this to field--field-background-image.tpl.php ??
}

/*
 * Implementation of theme_field()
 * Returns HTML for the field_background_image field
 */
function gazprom_field__field_background_image_multiple($vars) {
  $output = '';

  $output .= '<div class="backgrounder alternates">';
  foreach ($vars['items'] as $delta => $item) {
    $item['#item']['attributes']['class'][] = 'fancy-background-image';
    unset($item['#item']['width']);
    unset($item['#item']['height']);
    $output .= drupal_render($item); // calls gazprom_image_formatter() below (in place of theme_image_formatter())
  }
  $output .= '</div><!-- /.backgrounder -->';

  return $output;
  
  // @TODO consider moving this to field--field-background-image.tpl.php ??
}

/**
 * Returns HTML for an image field formatter.
 *
 * @param $variables
 *   An associative array containing:
 *   - item: An array of image data.
 *   - image_style: An optional image style.
 *   - path: An array containing the link 'path' and link 'options'.
 *
 * @ingroup themeable
 */
/* themed in Gazprom so that we can add the 'class' attribute.
 * Otherwise, this is a direct copy from theme_image_formatter()
 * in image.field.inc.
 */
function gazprom_image_formatter($variables) {
  $item = $variables['item'];
  $image = array(
    'path' => $item['uri'],
    'alt' => $item['alt'],
  );

  if (isset($item['width']) && isset($item['height'])) {
    $image['width'] = $item['width'];
    $image['height'] = $item['height'];
  }

  // Do not output an empty 'title' attribute.
  if (drupal_strlen($item['title']) > 0) {
    $image['title'] = $item['title'];
  }

  // add attributes (class)
  // (custom Gazprom code)
  if (isset($item['attributes'])) {
    $image['attributes'] = $item['attributes'];
  }
  
  if ($variables['image_style']) {
    $image['style_name'] = $variables['image_style'];
    $output = theme('image_style', $image);
  }
  else {
    $output = theme('image', $image);
  }

  if (!empty($variables['path']['path'])) {
    $path = $variables['path']['path'];
    $options = $variables['path']['options'];
    // When displaying an image inside a link, the html option must be TRUE.
    $options['html'] = TRUE;
    $output = l($output, $path, $options);
  }

  return $output;
}

function gazprom_preprocess_taxonomy_term(&$vars) {
  $vars = $vars;

  // specific template candidate for pages loaded into the overlay @TODO consider an ajax test? more of these types of pages?
  if (isset($_GET['overlay'])) {
    $templates = array();
    foreach($vars['theme_hook_suggestions'] as $template) {
      $templates[] = $template . '__overlay';
    }
    $vars['theme_hook_suggestions'] = array_merge($vars['theme_hook_suggestions'],$templates); // most important go LAST (there is a array_reverse call in theme.inc)
  }


}

/**
 * Alters the provided node $content variable to use
 * the field_background_image from the first node of the section/floor.
 * Depends on menu_block module's menu_tree_prune_tree() function.
 * 
 * @param array $content 
 * 
 */
function gazprom_util_fill_background_image(&$content, $useActive = false) {
  if (module_exists('menu_block')) {
    $menu_tree = menu_tree_page_data('main-menu');
    menu_tree_prune_tree($menu_tree, 2); // menu_block function

    if (!$useActive) {
      // Get the section's first menu item
      $menu_item = array_shift($menu_tree);
    } else {
      // Find the active menu item
      $menu_item = array_shift($menu_tree);
      while($menu_item && !$menu_item['link']['in_active_trail']) {
        $menu_item = array_shift($menu_tree);
      }
    }
    if ($menu_item) {
      if (substr($menu_item['link']['link_path'], 0, 5) == 'node/') {
        // This is weak, but simple/dirty way of getting nid. Find something better!
        $nid = str_replace('node/', '', $menu_item['link']['link_path']);
        if ($nid > 0) {
          $node = node_load($nid);
          if (!empty($node->field_background_image)) {
            $field = field_view_field('node', $node, 'field_background_image');
            $content['field_background_image'] = field_view_field('node', $node, 'field_background_image');
          }
        }
      }
    }
  }
}

/**
 * Implementation of template_preprocess_views_exposed_form.
 * This is function to translate the exposed filters taxonomy terms.
 * Only handling Photo Grid and Photo List views right now. Very much
 * a hack-job. Base code came from:
 * http://drupal.org/node/1402458 but modified to fit. Possibly modified to fit
 * alteratios from Better Exposed filters.
 * 
 * @param type $vars 
 * @global type $language
 */
function gazprom_preprocess_views_exposed_form(&$vars) {
  $form = &$vars['form'];
  if (($form['#id'] == 'views-exposed-form-photo-grid-block-1' || $form['#id'] == 'views-exposed-form-photo-list-block')
          && function_exists('i18n_taxonomy_term_name')) {
    global $language;
    $langcode = $language->language;

    foreach ($form['#info'] as $id => $info) {
      foreach($form[$info['value']]["#options"] as $key=>$option) {
        $term_id = key($option->option);
        $orig_value = $option->option[$term_id];
        $term = taxonomy_term_load($term_id);
        $form[$info['value']]["#options"][$key]->option[$term_id] = i18n_taxonomy_term_name($term, $langcode);
        if (substr($orig_value, 0, 1) == '-') {
          $form[$info['value']]["#options"][$key]->option[$term_id] = '-' . $form[$info['value']]["#options"][$key]->option[$term_id];
        }
        $term_id = $term_id;
      }
      unset($form[$info['value']]['#printed']);
      $vars['widgets'][$id]->widget = drupal_render($form[$info['value']]);
    }
  }
}