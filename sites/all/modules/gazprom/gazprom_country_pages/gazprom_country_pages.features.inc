<?php
/**
 * @file
 * gazprom_country_pages.features.inc
 */

/**
 * Implements hook_ctools_plugin_api().
 */
function gazprom_country_pages_ctools_plugin_api() {
  return array("version" => "1");
}

/**
 * Implements hook_node_info().
 */
function gazprom_country_pages_node_info() {
  $items = array(
    'country_page' => array(
      'name' => t('Country Page'),
      'base' => 'node_content',
      'description' => t('Page to hold country informational text, images, and links to projects or corporate news.'),
      'has_title' => '1',
      'title_label' => t('Country Name'),
      'help' => '',
    ),
  );
  return $items;
}
