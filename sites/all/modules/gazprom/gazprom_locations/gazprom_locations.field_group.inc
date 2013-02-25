<?php
/**
 * @file
 * gazprom_locations.field_group.inc
 */

/**
 * Implements hook_field_group_info().
 */
function gazprom_locations_field_group_info() {
  $export = array();

  $field_group = new stdClass();
  $field_group->disabled = FALSE; /* Edit this to true to make a default field_group disabled initially */
  $field_group->api_version = 1;
  $field_group->identifier = 'group_attached_media|taxonomy_term|location|form';
  $field_group->group_name = 'group_attached_media';
  $field_group->entity_type = 'taxonomy_term';
  $field_group->bundle = 'location';
  $field_group->mode = 'form';
  $field_group->parent_name = '';
  $field_group->data = array(
    'label' => 'Attached Media Items',
    'weight' => '3',
    'children' => array(
      0 => 'field_collection_attached',
      1 => 'field_video_attached',
    ),
    'format_type' => 'fieldset',
    'format_settings' => array(
      'label' => 'Attached Media Items',
      'instance_settings' => array(
        'required_fields' => 1,
        'classes' => '',
        'description' => '',
      ),
      'formatter' => 'collapsed',
    ),
  );
  $export['group_attached_media|taxonomy_term|location|form'] = $field_group;

  $field_group = new stdClass();
  $field_group->disabled = FALSE; /* Edit this to true to make a default field_group disabled initially */
  $field_group->api_version = 1;
  $field_group->identifier = 'group_copy_text|taxonomy_term|location|form';
  $field_group->group_name = 'group_copy_text';
  $field_group->entity_type = 'taxonomy_term';
  $field_group->bundle = 'location';
  $field_group->mode = 'form';
  $field_group->parent_name = '';
  $field_group->data = array(
    'label' => 'Copy Text',
    'weight' => '1',
    'children' => array(
      0 => 'field_location_information',
      1 => 'field_location_blurb',
      2 => 'description',
    ),
    'format_type' => 'fieldset',
    'format_settings' => array(
      'formatter' => 'collapsible',
      'instance_settings' => array(
        'description' => '',
        'classes' => '',
        'required_fields' => 1,
      ),
    ),
  );
  $export['group_copy_text|taxonomy_term|location|form'] = $field_group;

  $field_group = new stdClass();
  $field_group->disabled = FALSE; /* Edit this to true to make a default field_group disabled initially */
  $field_group->api_version = 1;
  $field_group->identifier = 'group_geo_location_data|taxonomy_term|location|form';
  $field_group->group_name = 'group_geo_location_data';
  $field_group->entity_type = 'taxonomy_term';
  $field_group->bundle = 'location';
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
        'description' => 'Geo Location Data for the Interactive World Map',
      ),
      'formatter' => 'collapsed',
    ),
  );
  $export['group_geo_location_data|taxonomy_term|location|form'] = $field_group;

  $field_group = new stdClass();
  $field_group->disabled = FALSE; /* Edit this to true to make a default field_group disabled initially */
  $field_group->api_version = 1;
  $field_group->identifier = 'group_images|taxonomy_term|location|form';
  $field_group->group_name = 'group_images';
  $field_group->entity_type = 'taxonomy_term';
  $field_group->bundle = 'location';
  $field_group->mode = 'form';
  $field_group->parent_name = '';
  $field_group->data = array(
    'label' => 'Images and Flags',
    'weight' => '2',
    'children' => array(
      0 => 'field_flag_image',
      1 => 'field_country_map',
      2 => 'field_image',
    ),
    'format_type' => 'fieldset',
    'format_settings' => array(
      'label' => 'Images and Flags',
      'instance_settings' => array(
        'required_fields' => 1,
        'classes' => '',
        'description' => '',
      ),
      'formatter' => 'collapsed',
    ),
  );
  $export['group_images|taxonomy_term|location|form'] = $field_group;

  return $export;
}
