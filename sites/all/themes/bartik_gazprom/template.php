<?php

/**
 * Implements hook_menu_local_task()
 *
 * @param array $variables
 *
 * return string with html
 */
function bartik_gazprom_menu_local_task($variables) {
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
function bartik_gazprom_menu_local_tasks(&$variables) {
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

