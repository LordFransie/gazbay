<?php
/**
 * @file
 * Contains theme override functions and process & preprocess functions for ninesixtyfive
 */

// Render SASS files
if (theme_get_setting('ninesixtyfive_sass')) {
  require_once dirname(__FILE__) . '/includes/sass.inc';
  ninesixtyfive_sass_render();
}


// Auto-rebuild the theme registry during theme development.
//if (theme_get_setting('ninesixtyfive_clear_registry')) {
//  // Rebuild .info data.
//  system_rebuild_theme_data();
//  // Rebuild theme registry.
//  drupal_theme_rebuild();
//}


/**
 * Implementation of hook_theme().
 */
function ninesixtyfive_theme($existing, $type, $theme, $path) {
  
  return array( 
    'dynamic_css' => array(
      'template' => 'styles/dynamic-css',
      'arguments' => array('form' => NULL),
    ),
  );
  
}


/**
 * Pass variables to dynamic-css.tpl.php
 */
function ninesixtyfive_preprocess_dynamic_css(&$vars) {
  $vars['page_max'] = theme_get_setting('ninesixtyfive_layout_max');
  $vars['page_min'] = theme_get_setting('ninesixtyfive_layout_min');
  $vars['footer'] = theme_get_setting('ninesixtyfive_layout_footer');
}


/**
 * Implements template_html_head_alter();
 *
 * Changes the default meta content-type tag to the shorter HTML5 version
 */
function ninesixtyfive_html_head_alter(&$head_elements) {
  $head_elements['system_meta_content_type']['#attributes'] = array(
    'charset' => 'utf-8'
  );
}


/**
 * Implements template_preprocess().
 */
function ninesixtyfive_preprocess(&$vars, $hook) {
  $vars['ninesixtyfive_path'] = base_path() . path_to_theme();
}


/**
 * Implements template_preprocess_html().
 */
function ninesixtyfive_preprocess_html(&$vars) {
  
  $vars['doctype'] = _ninesixtyfive_doctype();
  $vars['rdf'] = _ninesixtyfive_rdf($vars);
  $vars['html_attributes'] = 'lang="' . $vars['language']->language . '" dir="' . $vars['language']->dir . '" ' . $vars['rdf']->version . $vars['rdf']->namespaces;
  $vars['html5shiv'] = '<!--[if lt IE 9]><script src="'. base_path() . path_to_theme() .'/scripts/oldIEs/html5shiv.js"></script><![endif]-->';
  $vars['respond'] = '<!--[if lt IE 9]><script src="'. base_path() . path_to_theme() .'/scripts/oldIEs/respond.js"></script><![endif]-->';


  if (ninesixtyfive_ga_enabled()) {
    $ga_anonimize = theme_get_setting('ninesixtyfive_ga_anonimize') ? "_gaq.push (['_gat._anonymizeIp']);" : '';
    $ga_trackingcode = theme_get_setting('ninesixtyfive_ga_trackingcode');
    $vars['analytics'] = "<script type=\"text/javascript\">
      var _gaq = _gaq || [];
      _gaq.push(['_setAccount', '" . $ga_trackingcode . "']);
      _gaq.push(['_trackPageview']);" .
      $ga_anonimize . "
      (function() {
        var ga = document.createElement('script'); ga.type = 'text/javascript'; ga.async = true;
        ga.src = ('https:' == document.location.protocol ? 'https://ssl' : 'http://www') + '.google-analytics.com/ga.js';
        var s = document.getElementsByTagName('script')[0]; s.parentNode.insertBefore(ga, s);
      })();
    </script>";
  } else {
    $vars['analytics'] = '';
  }

  // Since menu is rendered in preprocess_page we need to detect it here to add body classes
  $has_main_menu = theme_get_setting('toggle_main_menu');
  $has_secondary_menu = theme_get_setting('toggle_secondary_menu');

  /* Add extra classes to body for more flexible theming */

  if (theme_get_setting('ninesixtyfive_layout_footer') > 0) {
    $vars['classes_array'][] = 'sticky-footer';
  }

  if ($has_main_menu or $has_secondary_menu) {
    $vars['classes_array'][] = 'with-navigation';
  }

  if ($has_secondary_menu) {
    $vars['classes_array'][] = 'with-subnav';
  }

  if (!empty($vars['page']['featured'])) {
    $vars['classes_array'][] = 'featured';
  }

  if ($vars['is_admin']) {
    $vars['classes_array'][] = 'admin';
  }
  
  if (theme_get_setting('ninesixtyfive_show_grid')) {
    $vars['classes_array'][] = 'show-grid';
  }
  
  $vars['classes_array'][] = 'dir-' . $vars['language']->dir;
  
  if (!$vars['is_front']) {
    // Add unique classes for each page and website section
    $path = drupal_get_path_alias($_GET['q']);
    $temp = explode('/', $path, 2);
    $section = array_shift($temp);
    $page_name = array_shift($temp);

    if (isset($page_name)) {
      $vars['classes_array'][] = drupal_html_id('page-' . $page_name);
    }

    $vars['classes_array'][] = drupal_html_id('section-' . $section);

    if (arg(0) == 'node') {
      if (arg(1) == 'add') {
        if ($section == 'node') {
          array_pop($vars['classes_array']); // Remove 'section-node'
        }
        $vars['classes_array'][] = 'section-node-add'; // Add 'section-node-add'
      } elseif (is_numeric(arg(1)) && (arg(2) == 'edit' || arg(2) == 'delete')) {
        if ($section == 'node') {
          array_pop($vars['classes_array']); // Remove 'section-node'
        }
        $vars['classes_array'][] = 'section-node-' . arg(2); // Add 'section-node-edit' or 'section-node-delete'
      }
    }
  }
}


/**
 * Implements template_preprocess_page().
 */
function ninesixtyfive_preprocess_page(&$vars) {
  
  if (isset($vars['node_title'])) {
    $vars['title'] = $vars['node_title'];
  }
  
  // Site navigation links.
  $vars['main_menu_links'] = '';
  if (isset($vars['main_menu'])) {
    $vars['main_menu_links'] = theme('links__system_main_menu', array(
      'links' => $vars['main_menu'],
      'attributes' => array(
        'id' => 'main-menu-links',
        'class' => array('inline', 'main-menu'),
      ),
      'heading' => array(
        'text' => t('Main menu'),
        'level' => 'h2',
        'class' => array('element-invisible'),
      ),
    ));
  }
  $vars['secondary_menu_links'] = '';
  if (isset($vars['secondary_menu'])) {
    $vars['secondary_menu_links'] = theme('links__system_secondary_menu', array(
      'links' => $vars['secondary_menu'],
      'attributes' => array(
        'id'    => 'secondary-menu-links',
        'class' => array('inline', 'secondary-menu'),
      ),
      'heading' => array(
        'text' => t('Secondary menu'),
        'level' => 'h2',
        'class' => array('element-invisible'),
      ),
    ));
  }
  
  // Adding classes wether #navigation is here or not
  if (!empty($vars['main_menu']) or !empty($vars['sub_menu'])) {
    $vars['classes_array'][] = 'with-navigation';
  }

  if (!empty($vars['secondary_menu'])) {
    $vars['classes_array'][] = 'with-subnav';
  }

  // Since the title and the shortcut link are both block level elements,
  // positioning them next to each other is much simpler with a wrapper div.
  if (!empty($vars['title_suffix']['add_or_remove_shortcut']) && $vars['title']) {
    // Add a wrapper div using the title_prefix and title_suffix render elements.
    $vars['title_prefix']['shortcut_wrapper'] = array(
      '#markup' => '<div class="shortcut-wrapper clearfix">',
      '#weight' => 100,
    );
    $vars['title_suffix']['shortcut_wrapper'] = array(
      '#markup' => '</div>',
      '#weight' => -99,
    );
    // Make sure the shortcut link is the first item in title_suffix.
    $vars['title_suffix']['add_or_remove_shortcut']['#weight'] = -100;
  }
  
  if(!theme_get_setting('ninesixtyfive_feed_icons')) {
    $vars['feed_icons'] = '';
  }
}


/**
 * Implements template_preprocess_node().
 *
 * Adds extra classes to node container for advanced theming
 */
function ninesixtyfive_preprocess_node(&$vars) {
  // Striping class
  $vars['classes_array'][] = 'node-' . $vars['zebra'];

  // Node is published
  $vars['classes_array'][] = ($vars['status']) ? 'published' : 'unpublished';

  // Node has comments?
  $vars['classes_array'][] = ($vars['comment']) ? 'with-comments' : 'no-comments';

  if ($vars['sticky']) {
    $vars['classes_array'][] = 'sticky'; // Node is sticky
  }

  if ($vars['promote']) {
    $vars['classes_array'][] = 'promote'; // Node is promoted to front page
  }

  if ($vars['teaser']) {
    $vars['classes_array'][] = 'node-teaser'; // Node is displayed as teaser.
  }

  if ($vars['uid'] && $vars['uid'] === $GLOBALS['user']->uid) {
    $classes[] = 'node-mine'; // Node is authored by current user.
  }
  
  $vars['submitted'] = t('Submitted by !username on ', array('!username' => $vars['name']));
  $vars['submitted_date'] = t('!datetime', array('!datetime' => $vars['date']));
  $vars['submitted_pubdate'] = format_date($vars['created'], 'custom', 'Y-m-d\TH:i:s');
  
  if ($vars['view_mode'] == 'full' && node_is_page($vars['node'])) {
    $vars['classes_array'][] = 'node-full';
  }
}


/**
 * Implements template_preprocess_block().
 */
function ninesixtyfive_preprocess_block(&$vars, $hook) {
  // Add a striping class.
  $vars['classes_array'][] = 'block-' . $vars['zebra'];

  // In the header region visually hide block titles.
  if ($vars['block']->region == 'header') {
    $vars['title_attributes_array']['class'][] = 'element-invisible';
  }
}


/**
 * Implements template_proprocess_search_block_form().
 *
 * Changes the search form to use the HTML5 "search" input attribute
 */
function ninesixtyfive_preprocess_search_block_form(&$vars) {
  $vars['search_form'] = str_replace('type="text"', 'type="search"', $vars['search_form']);
}


/**
 * Implements theme_menu_tree().
 */
function ninesixtyfive_menu_tree($vars) {
  return '<ul class="menu clearfix">' . $vars['tree'] . '</ul>';
}


/**
 * Implements theme_field__field_type().
 */
function ninesixtyfive_field__taxonomy_term_reference($vars) {
  $output = '';

  // Render the label, if it's not hidden.
  if (!$vars['label_hidden']) {
    $output .= '<h3 class="field-label">' . $vars['label'] . ': </h3>';
  }

  // Render the items.
  $output .= ( $vars['element']['#label_display'] == 'inline') ? '<ul class="links inline">' : '<ul class="links">';
  foreach ($vars['items'] as $delta => $item) {
    $output .= '<li class="taxonomy-term-reference-' . $delta . '"' . $vars['item_attributes'][$delta] . '>' . drupal_render($item) . '</li>';
  }
  $output .= '</ul>';

  // Render the top-level DIV.
  $output = '<div class="' . $vars['classes'] . (!in_array('clearfix', $vars['classes_array']) ? ' clearfix' : '') . '">' . $output . '</div>';

  return $output;
}


/**
 *  Return a themed breadcrumb trail
 */
function ninesixtyfive_breadcrumb($vars) {
  
  $breadcrumb = isset($vars['breadcrumb']) ? $vars['breadcrumb'] : array();
  
  if (theme_get_setting('ninesixtyfive_breadcrumb_hideonlyfront')) {
    $condition = count($breadcrumb) > 1;
  } else {
    $condition = !empty($breadcrumb);
  }
  
  if(theme_get_setting('ninesixtyfive_breadcrumb_showtitle')) {
    $title = drupal_get_title();
    if(!empty($title)) {
      $condition = true;
      $breadcrumb[] = $title;
    }
  }
  
  $separator = theme_get_setting('ninesixtyfive_breadcrumb_separator');

  if (!$separator) {
    $separator = '»';
  }
  
  if ($condition) {
    return implode(" {$separator} ", $breadcrumb);
  }
}


/**
 * Determine whether to output Google Analytics tracking code
 *
 * @return bool
 */
function ninesixtyfive_ga_enabled() {
  if (!theme_get_setting('ninesixtyfive_ga_enable')) {
    return FALSE;
  }

  global $user;
  $roles_orig = theme_get_setting('ninesixtyfive_ga_trackroles');

  // theme_get_setting() doesn't allow specifying default values so provide one here
  if (!is_array($roles_orig)) {
    $roles_orig = array();
  }

  // remove roles with permission
  $roles = array_filter($roles_orig);

  // get intersection of user's roles and roles without permission
  $intersect = array_intersect(array_keys($user->roles), array_keys($roles));

  return empty($intersect);
}


/**
 * Generate doctype for templates
 */
function _ninesixtyfive_doctype() {
  return (module_exists('rdf')) ? '<!DOCTYPE html PUBLIC "-//W3C//DTD HTML+RDFa 1.1//EN"' . "\n" . '"http://www.w3.org/MarkUp/DTD/xhtml-rdfa-1.dtd">' : '<!DOCTYPE html>' . "\n";
}


/**
 * Generate RDF object for templates
 *
 * Uses RDFa attributes if the RDF module is enabled
 * Lifted from Adaptivetheme for D7, full credit to Jeff Burnz
 * ref: http://drupal.org/node/887600
 *
 * @param array $vars
 */
function _ninesixtyfive_rdf($vars) {
  $rdf = new stdClass();

  if (module_exists('rdf')) {
    $rdf->version = 'version="HTML+RDFa 1.1"';
    $rdf->namespaces = $vars['rdf_namespaces'];
    $rdf->profile = ' profile="' . $vars['grddl_profile'] . '"';
  } else {
    $rdf->version = '';
    $rdf->namespaces = '';
    $rdf->profile = '';
  }

  return $rdf;
}


/**
 * Generate the HTML output for a menu link and submenu.
 *
 * @param $vars
 *   An associative array containing:
 *   - element: Structured array data for a menu link.
 *
 * @return
 *   A themed HTML string.
 *
 * @ingroup themeable
 */
function ninesixtyfive_menu_link(array $vars) {
  $element = $vars['element'];
  $sub_menu = '';

  if ($element['#below']) {
    $sub_menu = drupal_render($element['#below']);
  }

  $output = l($element['#title'], $element['#href'], $element['#localized_options']);
  // Adding a class depending on the TITLE of the link (not constant)
  $element['#attributes']['class'][] = drupal_html_id($element['#title']);
  // Adding a class depending on the ID of the link (constant)
  $element['#attributes']['class'][] = 'mid-' . $element['#original_link']['mlid'];
  return '<li' . drupal_attributes($element['#attributes']) . '>' . $output . $sub_menu . "</li>\n";
}


/**
 * Override or insert variables into theme_menu_local_task().
 */
function ninesixtyfive_preprocess_menu_local_task(&$vars) {
  $link = & $vars['element']['#link'];

  // If the link does not contain HTML already, check_plain() it now.
  // After we set 'html'=TRUE the link will not be sanitized by l().
  if (empty($link['localized_options']['html'])) {
    $link['title'] = check_plain($link['title']);
  }

  $link['localized_options']['html'] = TRUE;
  $link['title'] = '<span class="tab">' . $link['title'] . '</span>';
}


/**
 *  Duplicate of theme_menu_local_tasks() but adds clearfix to tabs.
 */
function ninesixtyfive_menu_local_tasks(&$vars) {
  $output = '';

  if (!empty($vars['primary'])) {
    $vars['primary']['#prefix'] = '<h2 class="element-invisible">' . t('Primary tabs') . '</h2>';
    $vars['primary']['#prefix'] .= '<ul class="tabs primary clearfix">';
    $vars['primary']['#suffix'] = '</ul>';
    $output .= drupal_render($vars['primary']);
  }

  if (!empty($vars['secondary'])) {
    $vars['secondary']['#prefix'] = '<h2 class="element-invisible">' . t('Secondary tabs') . '</h2>';
    $vars['secondary']['#prefix'] .= '<ul class="tabs secondary clearfix">';
    $vars['secondary']['#suffix'] = '</ul>';
    $output .= drupal_render($vars['secondary']);
  }

  return $output;
}


/**
 *  Helper function for sass integration. 
 */
function ninesixtyfive_sass_render() {
  $element = array(
     '#items' => drupal_add_css(), 
  );
  ninesixtyfive_pre_render($element);
}
