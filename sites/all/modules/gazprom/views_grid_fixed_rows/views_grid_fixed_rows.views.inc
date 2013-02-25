<?php
/**
 * @file
 * Defines the View Style Plugins for the Views jQM module.
 */

/**
 * Implements hook_views_plugins().
 */
function views_grid_fixed_rows_views_plugins() {
  $plugins = array(
    'style' => array(
      'fixed_row_grid' => array(
        'title' => t('Grid with Fixed Rows'),
        'help' => t('Creates a grid with a specified number of rows and dynamic columns.'),
        'handler' => 'views_grid_fixed_rows_plugin_style',
        'uses options' => TRUE,
        'uses row plugin' => TRUE,
        'uses grouping' => TRUE,
        'type' => 'normal',
        'path' => drupal_get_path('module', 'views_grid_fixed_rows'),
        'theme' => 'views_grid_fixed_rows',
        'theme path' => drupal_get_path('module', 'views_grid_fixed_rows') . '/theme',
        'theme file' => 'views_grid_fixed_rows.theme.inc',
      ),
    ),
  );
  
  return $plugins;
}
