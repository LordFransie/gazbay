<?php
/**
 * @file
 * gazprom_projects.features.inc
 */

/**
 * Implements hook_node_info().
 */
function gazprom_projects_node_info() {
  $items = array(
    'project' => array(
      'name' => t('Project'),
      'base' => 'node_content',
      'description' => t('Details about one project.'),
      'has_title' => '1',
      'title_label' => t('Project Name'),
      'help' => '',
    ),
  );
  return $items;
}
