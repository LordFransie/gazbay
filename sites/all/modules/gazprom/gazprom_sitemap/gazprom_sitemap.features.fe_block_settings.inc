<?php
/**
 * @file
 * gazprom_sitemap.features.fe_block_settings.inc
 */

/**
 * Implements hook_default_fe_block_settings().
 */
function gazprom_sitemap_default_fe_block_settings() {
  $export = array();

  // bartik_gazprom
  $theme = array();

  $theme['block-site_map_link'] = array(
    'module' => 'block',
    'theme' => 'bartik_gazprom',
    'status' => 0,
    'weight' => '0',
    'region' => '',
    'custom' => '0',
    'visibility' => '0',
    'pages' => '',
    'title' => '',
    'cache' => -1,
    'i18n_mode' => '0',
    'machine_name' => 'site_map_link',
  );

  $theme['menu_block-6'] = array(
    'module' => 'menu_block',
    'delta' => '6',
    'theme' => 'bartik_gazprom',
    'status' => 0,
    'weight' => '0',
    'region' => '',
    'custom' => '0',
    'visibility' => '0',
    'pages' => '',
    'title' => '',
    'cache' => -1,
    'i18n_mode' => '0',
  );

  $export['bartik_gazprom'] = $theme;

  // gazprom
  $theme = array();

  $theme['block-site_map_link'] = array(
    'module' => 'block',
    'theme' => 'gazprom',
    'status' => '1',
    'weight' => '-39',
    'region' => 'header-right',
    'custom' => '0',
    'visibility' => '0',
    'pages' => '',
    'title' => '<none>',
    'cache' => -1,
    'i18n_mode' => '0',
    'machine_name' => 'site_map_link',
  );

  $theme['menu_block-6'] = array(
    'module' => 'menu_block',
    'delta' => '6',
    'theme' => 'gazprom',
    'status' => '1',
    'weight' => '0',
    'region' => 'development_blocks',
    'custom' => '0',
    'visibility' => '0',
    'pages' => '',
    'title' => '<none>',
    'cache' => -1,
    'i18n_mode' => '0',
  );

  $export['gazprom'] = $theme;

  // gazprom_iframe_stage
  $theme = array();

  $theme['block-site_map_link'] = array(
    'module' => 'block',
    'theme' => 'gazprom_iframe_stage',
    'status' => 0,
    'weight' => '0',
    'region' => '',
    'custom' => '0',
    'visibility' => '0',
    'pages' => '',
    'title' => '<none>',
    'cache' => -1,
    'i18n_mode' => '0',
    'machine_name' => 'site_map_link',
  );

  $theme['menu_block-6'] = array(
    'module' => 'menu_block',
    'delta' => '6',
    'theme' => 'gazprom_iframe_stage',
    'status' => 0,
    'weight' => '0',
    'region' => '',
    'custom' => '0',
    'visibility' => '0',
    'pages' => '',
    'title' => '<none>',
    'cache' => -1,
    'i18n_mode' => '0',
  );

  $export['gazprom_iframe_stage'] = $theme;

  // gazprom_mobile
  $theme = array();

  $theme['block-site_map_link'] = array(
    'module' => 'block',
    'theme' => 'gazprom_mobile',
    'status' => 0,
    'weight' => '-9',
    'region' => '',
    'custom' => '0',
    'visibility' => '0',
    'pages' => '',
    'title' => '<none>',
    'cache' => -1,
    'i18n_mode' => '0',
    'machine_name' => 'site_map_link',
  );

  $theme['menu_block-6'] = array(
    'module' => 'menu_block',
    'delta' => '6',
    'theme' => 'gazprom_mobile',
    'status' => 0,
    'weight' => '-8',
    'region' => '',
    'custom' => '0',
    'visibility' => '0',
    'pages' => '',
    'title' => '<none>',
    'cache' => -1,
    'i18n_mode' => '0',
  );

  $export['gazprom_mobile'] = $theme;

  $theme_default = variable_get('theme_default', 'garland');
  $themes = list_themes();
  foreach ($export as $theme_key => $settings) {
    if ($theme_key != $theme_default && empty($themes[$theme_key]->status)) {
      unset($export[$theme_key]);
    }
  }
  return $export;
}
