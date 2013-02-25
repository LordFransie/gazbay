<?php
/**
 * @file
 * gazprom_pages.field_group.inc
 */

/**
 * Implements hook_field_group_info().
 */
function gazprom_pages_field_group_info() {
  $export = array();

  $field_group = new stdClass;
  $field_group->disabled = FALSE; /* Edit this to true to make a default field_group disabled initially */
  $field_group->api_version = 1;
  $field_group->identifier = 'group_page_code|node|page|form';
  $field_group->group_name = 'group_page_code';
  $field_group->entity_type = 'node';
  $field_group->bundle = 'page';
  $field_group->mode = 'form';
  $field_group->parent_name = '';
  $field_group->data = array(
    'label' => 'Page Code',
    'weight' => '8',
    'children' => array(
      0 => 'field_page_code',
      1 => 'field_css_classes',
    ),
    'format_type' => 'tab',
    'format_settings' => array(
      'label' => 'Page Code',
      'instance_settings' => array(
        'required_fields' => 0,
        'classes' => '',
        'description' => '',
      ),
      'formatter' => 'closed',
    ),
  );
  $export['group_page_code|node|page|form'] = $field_group;

  return $export;
}
