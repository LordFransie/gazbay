<?php
/**
 * @file
 * gazprom_history.features.inc
 */

/**
 * Implements hook_views_api().
 */
function gazprom_history_views_api() {
  list($module, $api) = func_get_args();
  if ($module == "views" && $api == "views_default") {
    return array("version" => "3.0");
  }
}

/**
 * Implements hook_node_info().
 */
function gazprom_history_node_info() {
  $items = array(
    'history_event' => array(
      'name' => t('History Event'),
      'base' => 'node_content',
      'description' => t('A single item for the history timeline.'),
      'has_title' => '1',
      'title_label' => t('Title'),
      'help' => '',
    ),
  );
  return $items;
}
