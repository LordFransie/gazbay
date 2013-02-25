<?php
/**
 * @file
 * gazprom_country_pages.field_group.inc
 */

/**
 * Implements hook_field_group_info().
 */
function gazprom_country_pages_field_group_info() {
  $export = array();

  $field_group = new stdClass();
  $field_group->disabled = FALSE; /* Edit this to true to make a default field_group disabled initially */
  $field_group->api_version = 1;
  $field_group->identifier = 'group_geo_location|node|country_page|form';
  $field_group->group_name = 'group_geo_location';
  $field_group->entity_type = 'node';
  $field_group->bundle = 'country_page';
  $field_group->mode = 'form';
  $field_group->parent_name = '';
  $field_group->data = array(
    'label' => 'Geo Location Data',
    'weight' => '5',
    'children' => array(
      0 => 'field_geo_location',
    ),
    'format_type' => 'fieldset',
    'format_settings' => array(
      'label' => 'Geo Location Data',
      'instance_settings' => array(
        'required_fields' => 1,
        'classes' => '',
        'description' => '',
      ),
      'formatter' => 'collapsed',
    ),
  );
  $export['group_geo_location|node|country_page|form'] = $field_group;

  $field_group = new stdClass();
  $field_group->disabled = FALSE; /* Edit this to true to make a default field_group disabled initially */
  $field_group->api_version = 1;
  $field_group->identifier = 'group_images|node|country_page|form';
  $field_group->group_name = 'group_images';
  $field_group->entity_type = 'node';
  $field_group->bundle = 'country_page';
  $field_group->mode = 'form';
  $field_group->parent_name = '';
  $field_group->data = array(
    'label' => 'Images and Attached Media',
    'weight' => '4',
    'children' => array(
      0 => 'field_image',
      1 => 'field_collection_attached',
      2 => 'field_country_map',
      3 => 'field_video_attached',
    ),
    'format_type' => 'fieldset',
    'format_settings' => array(
      'label' => 'Images and Attached Media',
      'instance_settings' => array(
        'required_fields' => 1,
        'classes' => '',
        'description' => '',
      ),
      'formatter' => 'collapsed',
    ),
  );
  $export['group_images|node|country_page|form'] = $field_group;

  $field_group = new stdClass();
  $field_group->disabled = FALSE; /* Edit this to true to make a default field_group disabled initially */
  $field_group->api_version = 1;
  $field_group->identifier = 'group_text|node|country_page|form';
  $field_group->group_name = 'group_text';
  $field_group->entity_type = 'node';
  $field_group->bundle = 'country_page';
  $field_group->mode = 'form';
  $field_group->parent_name = '';
  $field_group->data = array(
    'label' => 'Text',
    'weight' => '3',
    'children' => array(
      0 => 'field_country_blurb',
      1 => 'field_country_info',
    ),
    'format_type' => 'fieldset',
    'format_settings' => array(
      'label' => 'Text',
      'instance_settings' => array(
        'required_fields' => 1,
        'classes' => '',
        'description' => '',
      ),
      'formatter' => 'collapsed',
    ),
  );
  $export['group_text|node|country_page|form'] = $field_group;

  return $export;
}
