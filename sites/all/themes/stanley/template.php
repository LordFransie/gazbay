<?php

/**
 * Implementation of hook_theme().
*/
function stanley_theme() {
  $items = array();

  // Content theming.
  $items['help'] =
  $items['node'] =
  $items['comment'] =
  $items['comment_wrapper'] = array(
    'path' => drupal_get_path('theme', 'stanley') .'/templates',
    'template' => 'object',
  );
  $items['node']['template'] = 'node';

  // Help pages really need help. See preprocess_page().
  $items['help_page'] = array(
    'variables' => array('content' => array()),
    'path' => drupal_get_path('theme', 'stanley') .'/templates',
    'template' => 'object',
    'preprocess functions' => array(
      'template_preprocess',
      'stanley_preprocess_help_page',
    ),
    'process functions' => array('template_process'),
  );

  // Form layout: default (2 column).
  $items['block_add_block_form'] =
  $items['block_admin_configure'] =
  $items['comment_form'] =
  $items['contact_admin_edit'] =
  $items['contact_mail_page'] =
  $items['contact_mail_user'] =
  $items['filter_admin_format_form'] =
  $items['forum_form'] =
  $items['locale_languages_edit_form'] =
  $items['media_edit'] =
  $items['menu_edit_menu'] =
  $items['menu_edit_item'] =
  $items['node_type_form'] =
  $items['path_admin_form'] =
  $items['system_settings_form'] =
  $items['system_themes_form'] =
  $items['system_modules'] =
  $items['system_actions_configure'] =
  $items['taxonomy_form_term'] =
  $items['taxonomy_form_vocabulary'] =
  $items['user_profile_form'] =
  $items['user_admin_access_add_form'] = array(
    'render element' => 'form',
    'path' => drupal_get_path('theme', 'stanley') .'/templates',
    'template' => 'form-default',
    'preprocess functions' => array(
      'stanley_preprocess_form_buttons',
    ),
  );

  // These forms require additional massaging.
  $items['confirm_form'] = array(
    'render element' => 'form',
    'path' => drupal_get_path('theme', 'stanley') .'/templates',
    'template' => 'form-simple',
    'preprocess functions' => array(
      'stanley_preprocess_form_confirm',
      'stanley_preprocess_form_buttons',
    ),
  );
  $items['node_form'] = array(
    'render element' => 'form',
    'path' => drupal_get_path('theme', 'stanley') .'/templates',
    'template' => 'form-default',
    'preprocess functions' => array(
      'stanley_preprocess_form_buttons',
      'stanley_preprocess_form_node',
    ),
  );

  return $items;
}

/**
 * Implements hook_css_alter().
 */
function stanley_css_alter(&$css) {
  if (isset($css['modules/overlay/overlay-child.css'])) {
    $css['modules/overlay/overlay-child.css']['data'] = drupal_get_path('theme', 'stanley') . '/overlay-child.css';
  }

  if (isset($css['misc/ui/jquery.ui.theme.css'])) {
    $css['misc/ui/jquery.ui.theme.css']['data'] = drupal_get_path('theme', 'stanley') . '/jquery.ui.theme.css';
    $css['misc/ui/jquery.ui.theme.css']['weight']++;
  }

  //unset date_popup date picker css, core already has a theme
  unset($css['sites/all/modules/contrib/date/date_popup/themes/datepicker.1.7.css']);
}

/**
 * Implementation of hook_preprocess_html().
 */
function stanley_preprocess_html(&$vars) {
  // Add body class for theme.
  $vars['classes_array'][] = ' stanley';

  // HTML5 shiv -> http://code.google.com/p/html5shiv/
  $vars['shiv'] = '<!--[if lt IE 9]>' . "\n" . '<script src="//html5shim.googlecode.com/svn/trunk/html5.js"></script>' . "\n" . '<![endif]-->';

  // Don't assume RDFa is enabled and don't use XHTML if it is
  if (module_exists('rdf')) {
    $vars['doctype'] = '<!DOCTYPE html PUBLIC "-//W3C//DTD HTML+RDFa 1.1//EN">' . "\n";
    $vars['rdf_version'] = ' version="HTML+RDFa 1.1"';
    $vars['rdf_profile'] = ' profile="' . $vars['grddl_profile'] . '"';
  }
  else {
    $vars['doctype'] = '<!DOCTYPE html>' . "\n";
    $vars['rdf_version'] = '';
    $vars['rdf_profile'] = '';
  }
}

/**
 * Preprocessor for theme('page').
 */
function stanley_preprocess_page(&$vars) {
  // Show a warning if base theme is not present.
  if (!function_exists('tao_theme') && user_access('administer site configuration')) {
    drupal_set_message(t('The Stanley theme requires the !tao base theme in order to work properly.', array('!tao' => l('Tao', 'http://code.developmentseed.org/tao'))), 'warning');
  }

  // Set a page icon class.
  $vars['page_icon_class'] = ($item = menu_get_item()) ? implode(' ' , _stanley_icon_classes($item['href'])) : '';

  // If current page is local task, add title as subtitle
  if (!drupal_is_front_page()) {
    $item = menu_get_item();
    $title = drupal_get_title();
    if ($title !== $item['title']) {
      $vars['subtitle'] = check_plain($item['title']);
    }
  }

  // Help pages. They really do need help.
  if (strpos($_GET['q'], 'admin/help/') === 0 && isset($vars['page']['content']['system_main']['main']['#markup'])) {
    $vars['page']['content']['system_main']['main']['#markup'] = theme('help_page', array('content' => $vars['page']['content']['system_main']['main']['#markup']));
  }

  //add help marker to title
  if (!empty($vars['page']['help'])) {
    $vars['title_suffix'] = '<span class="main-help-marker" title="Show help">?</span>';
  }

  // Process local tasks. Only do this processing if the current theme is
  // indeed Stanley. Subthemes must reimplement this call.
  global $theme;
  if ($theme === 'stanley') {
    _stanley_local_tasks($vars);
  }

  // Overlay is enabled.
  $vars['overlay'] = (module_exists('overlay') && overlay_get_mode() === 'child');
}

/**
 * Implementation of preprocess_fieldset().
 */
function stanley_preprocess_fieldset(&$vars) {
  $element = $vars['element'];

  $description = !empty($element['#description']) ? "<div class=\"help-block\">{$element['#description']}</div>" : '';
  $children = !empty($element['#children']) ? $element['#children'] : '';
  $value = !empty($element['#value']) ? $element['#value'] : '';
  $vars['content'] = $description . $children . $value;
}

/**
 * Preprocessor for handling form button for most forms.
 */
function stanley_preprocess_form_buttons(&$vars) {
  if (!empty($vars['form']['actions'])) {
    $vars['actions'] = $vars['form']['actions'];
    unset($vars['form']['actions']);
  }
}

/**
 * Preprocessor for theme('confirm_form').
 */
function stanley_preprocess_form_confirm(&$vars) {
  // Move the title from the page title (usually too big and unwieldy)
  $title = filter_xss_admin(drupal_get_title());
  $vars['form']['description']['#markup'] = empty($vars['form']['description']['#markup']) ?
    "<strong>{$title}</strong>" :
    "<strong>{$title}</strong><p>{$vars['form']['description']['#markup']}</p>";
  drupal_set_title(t('Please confirm'));
}

/**
 * Preprocessor for theme('node_form').
 */
function stanley_preprocess_form_node(&$vars) {
  $vars['sidebar'] = isset($vars['sidebar']) ? $vars['sidebar'] : array();
  // Support nodeformcols if present.
  if (module_exists('nodeformcols')) {
    $map = array(
      'nodeformcols_region_right' => 'sidebar',
      'nodeformcols_region_footer' => 'footer',
      'nodeformcols_region_main' => NULL,
    );
    foreach ($map as $region => $target) {
      if (isset($vars['form'][$region])) {
        if (isset($vars['form'][$region]['#prefix'], $vars['form'][$region]['#suffix'])) {
          unset($vars['form'][$region]['#prefix']);
          unset($vars['form'][$region]['#suffix']);
        }
        if (isset($vars['form'][$region]['actions'], $vars['form'][$region]['actions'])) {
          $vars['actions'] = $vars['form'][$region]['actions'];
          unset($vars['form'][$region]['actions']);
        }
        if (isset($target)) {
          $vars[$target] = $vars['form'][$region];
          unset($vars['form'][$region]);
        }
      }
    }
  }
  // Default to showing taxonomy in sidebar if nodeformcols is not present.
  elseif (isset($vars['form']['taxonomy']) && empty($vars['sidebar'])) {
    $vars['sidebar']['taxonomy'] = $vars['form']['taxonomy'];
    unset($vars['form']['taxonomy']);
  }
}

/**
 * Preprocessor for theme('button').
 */
function stanley_preprocess_button(&$vars) {
  $vars['element']['#attributes']['class'][] = 'btn';

  if (isset($vars['element']['#value'])) {
    $classes = array(
      //specifics
      t('Save and add') => 'info',
      t('Add another item') => 'info',
      t('Add effect') => 'primary',
      t('Add and configure') => 'primary',
      t('Update style') => 'primary',
      t('Download feature') => 'primary',

      //generals
      t('Save') => 'primary',
      t('Apply') => 'primary',
      t('Create') => 'primary',
      t('Confirm') => 'primary',
      t('Submit') => 'primary',
      t('Export') => 'primary',
      t('Import') => 'primary',
      t('Restore') => 'primary',
      t('Rebuild') => 'primary',
      t('Add') => 'info',
      t('Update') => 'info',
      t('Delete') => 'danger',
      t('Remove') => 'danger',
    );
    foreach ($classes as $search => $class) {
      if (strpos($vars['element']['#value'], $search) !== FALSE) {
        $vars['element']['#attributes']['class'][] = $class;
        break;
      }
    }
  }
}

/**
 * Preprocessor for theme('image_button').
 */
function stanley_preprocess_image_button(&$vars) {
  $vars['element']['#attributes']['class'][] = 'btn';
}

/**
 * Preprocessor for theme('help').
 */
function stanley_preprocess_help(&$vars) {
  $vars['hook'] = 'help';
  $vars['attr']['id'] = 'help-text';
  $class = 'path-admin-help clear-block toggleable';
  $vars['attr']['class'] = isset($vars['attr']['class']) ? "{$vars['attr']['class']} $class" : $class;
  $help = menu_get_active_help();
  if (($test = strip_tags($help)) && !empty($help)) {
    // Thankfully this is static cached.
    $vars['attr']['class'] .= menu_secondary_local_tasks() ? ' with-tabs' : '';

    $vars['is_prose'] = TRUE;
    $vars['layout'] = TRUE;
    $vars['content'] = "<span class='icon'></span>" . $help;

    // Link to help section.
    $item = menu_get_item('admin/help');
    if ($item && $item['path'] === 'admin/help' && $item['access']) {
      $vars['links'] = l(t('More help topics'), 'admin/help');
    }
  }
}

/**
 * Preprocessor for theme('help_page').
 */
function stanley_preprocess_help_page(&$vars) {
  $vars['hook'] = 'help-page';

  $vars['title_attributes_array']['class'][] = 'help-page-title';
  $vars['title_attributes_array']['class'][] = 'clearfix';

  $vars['content_attributes_array']['class'][] = 'help-page-content';
  $vars['content_attributes_array']['class'][] = 'clearfix';
  $vars['content_attributes_array']['class'][] = 'prose';

  $vars['layout'] = TRUE;

  // Truly hackish way to navigate help pages.
  $module_info = system_rebuild_module_data();
  $modules = array();
  foreach (module_implements('help', TRUE) as $module) {
    if (module_invoke($module, 'help', "admin/help#$module", NULL)) {
      $modules[$module] = $module_info[$module]->info['name'];
    }
  }
  asort($modules);

  $links = array();
  foreach ($modules as $module => $name) {
    $links[] = array('title' => $name, 'href' => "admin/help/{$module}");
  }
  $vars['links'] = theme('links', array('links' => $links));
}

/**
 * Preprocessor for theme('node').
 */
function stanley_preprocess_node(&$vars) {
  $vars['layout'] = TRUE;
  $vars['submitted'] = _stanley_submitted($vars['node']);
}

/**
 * Preprocessor for theme('comment').
 */
function stanley_preprocess_comment(&$vars) {
  $vars['layout'] = TRUE;
  $vars['submitted'] = _stanley_submitted($vars['comment']);
}

/**
 * Preprocessor for theme('comment_wrapper').
 */
function stanley_preprocess_comment_wrapper(&$vars) {
  $vars['hook'] = 'box';
  $vars['layout'] = FALSE;
  $vars['title'] = t('Comments');

  $vars['attributes_array']['id'] = 'comments';

  $vars['title_attributes_array']['class'][] = 'box-title';
  $vars['title_attributes_array']['class'][] = 'clearfix';

  $vars['content_attributes_array']['class'][] = 'box-content';
  $vars['content_attributes_array']['class'][] = 'clearfix';
  $vars['content_attributes_array']['class'][] = 'prose';

  $vars['content'] = drupal_render_children($vars['content']);
}

/**
 * Preprocessor for theme('admin_block').
 */
function stanley_preprocess_admin_block(&$vars) {
  // Add icon and classes to admin block titles.
  if (isset($vars['block']['href'])) {
    $vars['block']['localized_options']['attributes']['class'] =  _stanley_icon_classes($vars['block']['href']);
  }
  $vars['block']['localized_options']['html'] = TRUE;
  if (isset($vars['block']['link_title'])) {
    $vars['block']['title'] = l("<span class='icon'></span>" . filter_xss_admin($vars['block']['link_title']), $vars['block']['href'], $vars['block']['localized_options']);
  }

  if (empty($vars['block']['content'])) {
    $vars['block']['content'] = "<div class='admin-block-description description'>{$vars['block']['description']}</div>";
  }
}

/**
 * Override of theme('breadcrumb').
 */
function stanley_breadcrumb($vars) {
  $output = '';

  // Optional: Add the site name to the front of the stack.
  if (!empty($vars['prepend'])) {
    $site_name = empty($vars['breadcrumb']) ? "<strong>". check_plain(variable_get('site_name', '')) ."</strong>" : l(variable_get('site_name', ''), '<front>', array('purl' => array('disabled' => TRUE)));
    array_unshift($vars['breadcrumb'], $site_name);
  }

  //add divider
  foreach ($vars['breadcrumb'] as $key => $link) {
    $vars['breadcrumb'][$key] = $link . '<span class="divider">/</span>';
  }

  // Add current page onto the end.
  if (!drupal_is_front_page()) {
    $item = menu_get_item();
    $end = end($vars['breadcrumb']);
    if ($end && strip_tags($end) !== $item['title']) {
      $vars['breadcrumb'][] = check_plain($item['title']);
    }
  }

  return theme('item_list', array('items' => $vars['breadcrumb'], 'attributes' => array('class' => array('breadcrumb'))));
}

/**
 * Override of theme('filter_guidelines').
 */
function stanley_filter_guidelines($variables) {
  return '';
}

/**
 * Override of theme('node_add_list').
 */
function stanley_node_add_list($vars) {
  $content = $vars['content'];

  $output = "<ul class='admin-list'>";
  if ($content) {
    foreach ($content as $item) {
      $item['title'] = "<span class='icon'></span>" . filter_xss_admin($item['title']);
      if (isset($item['localized_options']['attributes']['class'])) {
        $item['localized_options']['attributes']['class'] += _stanley_icon_classes($item['href']);
      }
      else {
        $item['localized_options']['attributes']['class'] = _stanley_icon_classes($item['href']);
      }
      $item['localized_options']['html'] = TRUE;
      $output .= "<li>";
      $output .= l($item['title'], $item['href'], $item['localized_options']);
      $output .= '<div class="description">'. filter_xss_admin($item['description']) .'</div>';
      $output .= "</li>";
    }
  }
  $output .= "</ul>";
  return $output;
}

/**
 * Override of theme_admin_block_content().
 */
function stanley_admin_block_content($vars) {
  $content = $vars['content'];

  $output = '';
  if (!empty($content)) {

    foreach ($content as $k => $item) {

      //-- Safety check for invalid clients of the function
      if (empty($content[$k]['localized_options']['attributes']['class'])) {
        $content[$k]['localized_options']['attributes']['class'] = array();
      }
      if (!is_array($content[$k]['localized_options']['attributes']['class'])) {
        $content[$k]['localized_options']['attributes']['class'] = array($content[$k]['localized_options']['attributes']['class']);
      }

      $content[$k]['title'] = "<span class='icon'></span>" . filter_xss_admin($item['title']);
      $content[$k]['localized_options']['html'] = TRUE;
      if (!empty($content[$k]['localized_options']['attributes']['class'])) {
        $content[$k]['localized_options']['attributes']['class'] += _stanley_icon_classes($item['href']);
      }
      else {
        $content[$k]['localized_options']['attributes']['class'] = _stanley_icon_classes($item['href']);
      }
    }
    $output = system_admin_compact_mode() ? '<ul class="admin-list admin-list-compact">' : '<ul class="admin-list">';
    foreach ($content as $item) {
      $output .= '<li class="leaf">';
      $output .= l($item['title'], $item['href'], $item['localized_options']);
      if (isset($item['description']) && !system_admin_compact_mode()) {
        $output .= "<div class='description'>{$item['description']}</div>";
      }
      $output .= '</li>';
    }
    $output .= '</ul>';
  }
  return $output;
}

/**
 * Override of theme('menu_local_task').
 */
function stanley_menu_local_task($variables) {
  $link = $variables['element']['#link'];
  $link_text = $link['title'];
  $classes = array();

  if (!empty($variables['element']['#active'])) {
    // Add text to indicate active tab for non-visual users.
    $active = '<span class="element-invisible">' . t('(active tab)') . '</span>';

    // If the link does not contain HTML already, check_plain() it now.
    // After we set 'html'=TRUE the link will not be sanitized by l().
    if (empty($link['localized_options']['html'])) {
      $link['title'] = check_plain($link['title']);
    }
    $link['localized_options']['html'] = TRUE;
    $link_text = t('!local-task-title!active', array('!local-task-title' => $link['title'], '!active' => $active));

    $classes[] = 'active';
  }

  // Render child tasks if available.
  $children = '';
  if (element_children($variables['element'])) {
    $link['localized_options']['attributes']['class'][] = 'dropdown-toggle';
    $classes[] = 'dropdown';

    $children = drupal_render_children($variables['element']);
    $children = '<ul class="secondary-tabs dropdown-menu">' . $children . "</ul>";
  }

  return '<li class="' . implode(' ', $classes) . '">' . l($link_text, $link['href'], $link['localized_options']) . $children . "</li>\n";
}

/**
 * Override of theme('status_message').
 */
function stanley_status_messages($variables) {
  $display = $variables['display'];
  $output = '';

  $status_heading = array(
    'status' => t('Status message'),
    'error' => t('Error message'),
    'warning' => t('Warning message'),
  );
  foreach (drupal_get_messages($display) as $type => $messages) {
    $output .= "<div class=\"messages $type\" data-alert=\"alert\">\n";
    $output .= '<a class="close" href="#">×</a>';

    if (!empty($status_heading[$type])) {
      $output .= '<h2 class="element-invisible">' . $status_heading[$type] . "</h2>\n";
    }
    if (count($messages) > 1) {
      $output .= " <ul>\n";
      foreach ($messages as $message) {
        $output .= '  <li>' . $message . "</li>\n";
      }
      $output .= " </ul>\n";
    }
    else {
      $output .= $messages[0];
    }
    $output .= "</div>\n";
  }
  return $output;
}

/**
 * Implements hook_form_alter().
 */
function stanley_form_alter(&$form, &$form_state, $form_id) {
  //make sure all forms are stacked
  $form['#attributes']['class'][] = 'form-stacked';

  //add classes to actions
  if (!empty($form['actions'])) {
    $form['actions']['#attributes']['class'][] = 'actions';

    if (!empty($form['actions']['cancel']) && $form['actions']['cancel']['#type'] == 'link') {
      $form['actions']['cancel']['#attributes']['class'][] = 'btn';
    }
  }

  //let's tackle some specific forms
  switch ($form_id) {
    case 'user_filter_form':
      $form['filters']['status']['filters']['#attributes']['class'][] = 'row';
      stanley_wrap_item_span($form['filters']['status']['filters']['role'], 'span4');
      stanley_wrap_item_span($form['filters']['status']['filters']['permission'], 'span4');
      stanley_wrap_item_span($form['filters']['status']['filters']['status'], 'span4');
      break;

    case 'dblog_filter_form':
      $form['filters']['status']['#type'] = 'container';
      $form['filters']['status']['#attributes']['class'][] = 'row';
      stanley_wrap_item_span($form['filters']['status']['type'], 'span4');
      stanley_wrap_item_span($form['filters']['status']['severity'], 'span4');
      break;

    case 'media_edit':
      unset($form['preview']['#suffix']);
      unset($form['actions']['#prefix']);
      break;

    case 'views_ui_edit_form':
      $form['changed']['#attributes']['class'][] = 'alert-message';
      $form['changed']['#attributes']['class'][] = 'block-message';
      break;
  }
}

/**
 * Override of theme('form_element').
 */
function stanley_form_element($variables) {
  $element = &$variables['element'];
  // This is also used in the installer, pre-database setup.
  $t = get_t();

  // This function is invoked as theme wrapper, but the rendered form element
  // may not necessarily have been processed by form_builder().
  $element += array(
    '#title_display' => 'before',
  );

  // Add element #id for #type 'item'.
  if (isset($element['#markup']) && !empty($element['#id'])) {
    $attributes['id'] = $element['#id'];
  }
  // Add element's #type and #name as class to aid with JS/CSS selectors.
  $attributes['class'] = array('form-item');
  if (!empty($element['#type'])) {
    $attributes['class'][] = 'form-type-' . strtr($element['#type'], '_', '-');
  }
  if (!empty($element['#name'])) {
    $attributes['class'][] = 'form-item-' . strtr($element['#name'], array(' ' => '-', '_' => '-', '[' => '-', ']' => ''));
  }
  // Add a class for disabled elements to facilitate cross-browser styling.
  if (!empty($element['#attributes']['disabled'])) {
    $attributes['class'][] = 'form-disabled';
  }
  // Add bootstrap classes
  $attributes['class'][] = 'clearfix';

  // Add append/prepend classes
  $excluded_fields = array_intersect(array('_add_new_field', '_add_new_group'), $element['#array_parents']);
  if ($element['#type'] == 'textfield' && empty($excluded_fields)) {
    if (!empty($element['#field_prefix'])) {
      $attributes['class'][] = 'input-prepend';
    }
    if (!empty($element['#field_suffix'])) {
      $attributes['class'][] = 'input-append';
    }
  }

  $output = '<div' . drupal_attributes($attributes) . '>' . "\n";

  // If #title is not set, we don't display any label or required marker.
  if (!isset($element['#title'])) {
    $element['#title_display'] = 'none';
  }
  $prefix = isset($element['#field_prefix']) ? '<span class="field-prefix add-on">' . $element['#field_prefix'] . '</span> ' : '';
  $suffix = isset($element['#field_suffix']) ? ' <span class="field-suffix add-on">' . $element['#field_suffix'] . '</span>' : '';

  switch ($element['#title_display']) {
    case 'before':
    case 'invisible':
      $output .= ' ' . theme('form_element_label', $variables);
      $output .= ' ' . $prefix . $element['#children'] . $suffix . "\n";
      break;

    case 'after':
      $output .= ' ' . $prefix . $element['#children'] . $suffix;
      $output .= ' ' . theme('form_element_label', $variables) . "\n";
      break;

    case 'none':
    case 'attribute':
      // Output no label and no required marker, only the children.
      $output .= ' ' . $prefix . $element['#children'] . $suffix . "\n";
      break;
  }

  if (!empty($element['#description'])) {
    $output .= '<div class="description help-block">' . $element['#description'] . "</div>\n";
  }

  $output .= "</div>\n";

  return $output;
}

/**
 * Override of theme('form_table').
 */
function stanley_table($variables) {
  $header = $variables['header'];
  $rows = $variables['rows'];
  $attributes = $variables['attributes'];
  $caption = $variables['caption'];
  $colgroups = $variables['colgroups'];
  $sticky = $variables['sticky'];
  $empty = $variables['empty'];

  // Add sticky headers, if applicable.
  if (count($header) && $sticky) {
    drupal_add_js('misc/tableheader.js');
    // Add 'sticky-enabled' class to the table to identify it for JS.
    // This is needed to target tables constructed by this function.
    $attributes['class'][] = 'sticky-enabled';
  }

  //Add bootstrap classes
  $attributes['class'][] = 'zebra-striped';


  $output = '<table' . drupal_attributes($attributes) . ">\n";

  if (isset($caption)) {
    $output .= '<caption>' . $caption . "</caption>\n";
  }

  // Format the table columns:
  if (count($colgroups)) {
    foreach ($colgroups as $number => $colgroup) {
      $attributes = array();

      // Check if we're dealing with a simple or complex column
      if (isset($colgroup['data'])) {
        foreach ($colgroup as $key => $value) {
          if ($key == 'data') {
            $cols = $value;
          }
          else {
            $attributes[$key] = $value;
          }
        }
      }
      else {
        $cols = $colgroup;
      }

      // Build colgroup
      if (is_array($cols) && count($cols)) {
        $output .= ' <colgroup' . drupal_attributes($attributes) . '>';
        $i = 0;
        foreach ($cols as $col) {
          $output .= ' <col' . drupal_attributes($col) . ' />';
        }
        $output .= " </colgroup>\n";
      }
      else {
        $output .= ' <colgroup' . drupal_attributes($attributes) . " />\n";
      }
    }
  }

  // Add the 'empty' row message if available.
  if (!count($rows) && $empty) {
    $header_count = 0;
    foreach ($header as $header_cell) {
      if (is_array($header_cell)) {
        $header_count += isset($header_cell['colspan']) ? $header_cell['colspan'] : 1;
      }
      else {
        $header_count++;
      }
    }
    $rows[] = array(array(
        'data' => $empty,
        'colspan' => $header_count,
        'class' => array('empty', 'message'),
      ));
  }

  // Format the table header:
  if (count($header)) {
    $ts = tablesort_init($header);
    // HTML requires that the thead tag has tr tags in it followed by tbody
    // tags. Using ternary operator to check and see if we have any rows.
    $output .= (count($rows) ? ' <thead><tr>' : ' <tr>');
    foreach ($header as $cell) {
      $cell = tablesort_header($cell, $header, $ts);
      $output .= _theme_table_cell($cell, TRUE);
    }
    // Using ternary operator to close the tags based on whether or not there are rows
    $output .= (count($rows) ? " </tr></thead>\n" : "</tr>\n");
  }
  else {
    $ts = array();
  }

  // Format the table rows:
  if (count($rows)) {
    $output .= "<tbody>\n";
    $flip = array(
      'even' => 'odd',
      'odd' => 'even',
    );
    $class = 'even';
    foreach ($rows as $number => $row) {
      $attributes = array();

      // Check if we're dealing with a simple or complex row
      if (isset($row['data'])) {
        foreach ($row as $key => $value) {
          if ($key == 'data') {
            $cells = $value;
          }
          else {
            $attributes[$key] = $value;
          }
        }
      }
      else {
        $cells = $row;
      }
      if (count($cells)) {
        // Add odd/even class
        if (empty($row['no_striping'])) {
          $class = $flip[$class];
          $attributes['class'][] = $class;
        }

        // Build row
        $output .= ' <tr' . drupal_attributes($attributes) . '>';
        $i = 0;
        foreach ($cells as $cell) {
          $cell = tablesort_cell($cell, $header, $ts, $i++);
          $output .= _theme_table_cell($cell);
        }
        $output .= " </tr>\n";
      }
    }
    $output .= "</tbody>\n";
  }

  $output .= "</table>\n";
  return $output;
}

/**
 * Wish I didn't have to do this, just to add some classes.
 */
function stanley_pager($variables) {
  $tags = $variables['tags'];
  $element = $variables['element'];
  $parameters = $variables['parameters'];
  $quantity = $variables['quantity'];
  global $pager_page_array, $pager_total;

  // Calculate various markers within this pager piece:
  // Middle is used to "center" pages around the current page.
  $pager_middle = ceil($quantity / 2);
  // current is the page we are currently paged to
  $pager_current = $pager_page_array[$element] + 1;
  // first is the first page listed by this pager piece (re quantity)
  $pager_first = $pager_current - $pager_middle + 1;
  // last is the last page listed by this pager piece (re quantity)
  $pager_last = $pager_current + $quantity - $pager_middle;
  // max is the maximum page number
  $pager_max = $pager_total[$element];
  // End of marker calculations.

  // Prepare for generation loop.
  $i = $pager_first;
  if ($pager_last > $pager_max) {
    // Adjust "center" if at end of query.
    $i = $i + ($pager_max - $pager_last);
    $pager_last = $pager_max;
  }
  if ($i <= 0) {
    // Adjust "center" if at start of query.
    $pager_last = $pager_last + (1 - $i);
    $i = 1;
  }
  // End of generation loop preparation.

  $li_first = theme('pager_first', array('text' => (isset($tags[0]) ? $tags[0] : t('« first')), 'element' => $element, 'parameters' => $parameters));
  $li_previous = theme('pager_previous', array('text' => (isset($tags[1]) ? $tags[1] : t('‹ previous')), 'element' => $element, 'interval' => 1, 'parameters' => $parameters));
  $li_next = theme('pager_next', array('text' => (isset($tags[3]) ? $tags[3] : t('next ›')), 'element' => $element, 'interval' => 1, 'parameters' => $parameters));
  $li_last = theme('pager_last', array('text' => (isset($tags[4]) ? $tags[4] : t('last »')), 'element' => $element, 'parameters' => $parameters));

  if ($pager_total[$element] > 1) {
    //first
    if ($li_first) {
      $items[] = array(
        'class' => array('pager-first', 'prev'),
        'data' => $li_first,
      );
    }
    else {
      $items[] = array(
        'class' => array('pager-first', 'prev', 'disabled'),
        'data' => '<a href="#">« first</a>',
      );
    }

    //previous
    if ($li_previous) {
      $items[] = array(
        'class' => array('pager-previous'),
        'data' => $li_previous,
      );
    }
    else {
      $items[] = array(
        'class' => array('pager-first', 'disabled'),
        'data' => '<a href="#">‹ previous</a>',
      );
    }

    // When there is more than one page, create the pager list.
    if ($i != $pager_max) {
      if ($i > 1) {
        $items[] = array(
          'class' => array('pager-ellipsis', 'disabled'),
          'data' => '<a href="#">…</a>',
        );
      }
      // Now generate the actual pager piece.
      for (; $i <= $pager_last && $i <= $pager_max; $i++) {
        if ($i < $pager_current) {
          $items[] = array(
            'class' => array('pager-item'),
            'data' => theme('pager_previous', array('text' => $i, 'element' => $element, 'interval' => ($pager_current - $i), 'parameters' => $parameters)),
          );
        }
        if ($i == $pager_current) {
          $items[] = array(
            'class' => array('pager-current', 'active'),
            'data' => '<a href="#">' . $i . '</a>',
          );
        }
        if ($i > $pager_current) {
          $items[] = array(
            'class' => array('pager-item'),
            'data' => theme('pager_next', array('text' => $i, 'element' => $element, 'interval' => ($i - $pager_current), 'parameters' => $parameters)),
          );
        }
      }
      if ($i < $pager_max) {
        $items[] = array(
          'class' => array('pager-ellipsis', 'disabled'),
          'data' => '<a href="#">…</a>',
        );
      }
    }

    // End generation.
    //next
    if ($li_next) {
      $items[] = array(
        'class' => array('pager-next'),
        'data' => $li_next,
      );
    }
    else {
      $items[] = array(
        'class' => array('pager-first', 'disabled'),
        'data' => '<a href="#">next ›</a>',
      );
    }

    //last
    if ($li_last) {
      $items[] = array(
        'class' => array('pager-last', 'next'),
        'data' => $li_last,
      );
    }
    else {
      $items[] = array(
        'class' => array('pager-first', 'next', 'disabled'),
        'data' => '<a href="#">last »</a>',
      );
    }

    return '<h2 class="element-invisible">' . t('Pages') . '</h2><div class="pagination">' . theme('item_list', array(
      'items' => $items,
      'attributes' => array('class' => array('pager')),
    ))
    . '</div>';
  }
}

/**
 * Undo what tao is doing
 */
function stanley_pager_link($variables) {
  $text = $variables['text'];
  $page_new = $variables['page_new'];
  $element = $variables['element'];
  $parameters = $variables['parameters'];
  $attributes = $variables['attributes'];

  $page = isset($_GET['page']) ? $_GET['page'] : '';
  if ($new_page = implode(',', pager_load_array($page_new[$element], $element, explode(',', $page)))) {
    $parameters['page'] = $new_page;
  }

  $query = array();
  if (count($parameters)) {
    $query = drupal_get_query_parameters($parameters, array());
  }
  if ($query_pager = pager_get_query_parameters()) {
    $query = array_merge($query, $query_pager);
  }

  // Set each pager link title
  if (!isset($attributes['title'])) {
    static $titles = NULL;
    if (!isset($titles)) {
      $titles = array(
        t('« first') => t('Go to first page'),
        t('‹ previous') => t('Go to previous page'),
        t('next ›') => t('Go to next page'),
        t('last »') => t('Go to last page'),
      );
    }
    if (isset($titles[$text])) {
      $attributes['title'] = $titles[$text];
    }
    elseif (is_numeric($text)) {
      $attributes['title'] = t('Go to page @number', array('@number' => $text));
    }
  }

  return l($text, $_GET['q'], array('attributes' => $attributes, 'query' => $query));
}

/**
 * Theme function for displaying form buttons
 */
function stanley_features_form_buttons(&$vars) {
  drupal_add_css(drupal_get_path('module', 'features') . '/features.css');

  $output = drupal_render_children($vars['element']);
  return !empty($output) ? "<div class=\"actions clear-block\">{$output}</div>" : '';
}

/**
 * Add a span4 wrapper to a form item
 */
function stanley_wrap_item_span(&$element, $class) {
  $element['#prefix'] = '<div class="' . $class . '">';
  $element['#suffix'] = '</div>';
}

/**
 * Helper function for cloning and drupal_render()'ing elements.
 */
function stanley_render_clone($elements) {
  static $instance;
  if (!isset($instance)) {
    $instance = 1;
  }
  foreach (element_children($elements) as $key) {
    if (isset($elements[$key]['#id'])) {
      $elements[$key]['#id'] = "{$elements[$key]['#id']}-{$instance}";
    }
  }
  $instance++;
  return drupal_render($elements);
}

/**
 * Helper function to submitted info theming functions.
 */
function _stanley_submitted($node) {
  $byline = t('Posted by !username', array('!username' => theme('username', array('name' => $node))));
  $date = format_date($node->created, 'small');
  return "<div class='byline'>{$byline}</div><div class='date'>$date</div>";
}

/**
 * Generate an icon class from a path.
 */
function _stanley_icon_classes($path) {
  $classes = array();
  $args = explode('/', $path);
  if ($args[0] === 'admin' || (count($args) > 1 && $args[0] === 'node' && $args[1] === 'add')) {
    // Add a class specifically for the current path that allows non-cascading
    // style targeting.
    $classes[] = 'path-'. str_replace('/', '-', implode('/', $args)) . '-';
    while (count($args)) {
      $classes[] = 'path-'. str_replace('/', '-', implode('/', $args));
      array_pop($args);
    }
    return $classes;
  }
  return array();
}

/**
 * we use this callback to add all subtasks of a primary localtask as children.
 * TODO: clean this up
 */
function _stanley_local_tasks(&$vars) {
  if (!empty($vars['primary_local_tasks'])) {
    foreach ($vars['primary_local_tasks'] as $key => $element) {
      //if subtasks are present use those
      if (!empty($element['#active'])) {
        if (!empty($vars['secondary_local_tasks'])) {
          $vars['primary_local_tasks'][$key] = $vars['primary_local_tasks'][$key] + $vars['secondary_local_tasks'];
        }
      }

      //add subtasks from the database
      //TODO: fix this to allow noraml hook_menu_local_tasks_alter behaviour
      else {
        $result = db_select('menu_router', NULL, array('fetch' => PDO::FETCH_ASSOC))
          ->fields('menu_router')
          ->condition('tab_parent', $element['#link']['path'])
          ->condition('context', MENU_CONTEXT_INLINE, '<>')
          ->condition('type', array(MENU_DEFAULT_LOCAL_TASK, MENU_LOCAL_TASK), 'IN')
          ->orderBy('weight')
          ->orderBy('title')
          ->execute();

        $router_item = menu_get_item($element['#link']['path']);
        $map = $router_item['original_map'];

        $i = 0;
        foreach ($result as $item) {
          _menu_translate($item, $map, TRUE);

          //only add items that we have access to
          if ($item['tab_parent'] && $item['access']) {
            //set path to that of parent for the first item
            if ($i === 0) {
              $item['href'] = $item['tab_parent'];
            }

            if (current_path() == $item['href']) {
              $vars['primary_local_tasks'][$key][] = array(
                '#theme' => 'menu_local_task',
                '#link' => $item,
                '#active' => TRUE,
              );
            }
            else {
              $vars['primary_local_tasks'][$key][] = array(
                '#theme' => 'menu_local_task',
                '#link' => $item,
              );
            }

            //only count items we have access to.
            $i++;
          }
        }
      }
    }
  }
}
