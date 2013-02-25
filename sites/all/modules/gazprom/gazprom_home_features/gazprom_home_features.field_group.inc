<?php
/**
 * @file
 * gazprom_home_features.field_group.inc
 */

/**
 * Implements hook_field_group_info().
 */
function gazprom_home_features_field_group_info() {
  $export = array();

  $field_group = new stdClass();
  $field_group->disabled = FALSE; /* Edit this to true to make a default field_group disabled initially */
  $field_group->api_version = 1;
  $field_group->identifier = 'group_content_links_1|node|home_page_feature|form';
  $field_group->group_name = 'group_content_links_1';
  $field_group->entity_type = 'node';
  $field_group->bundle = 'home_page_feature';
  $field_group->mode = 'form';
  $field_group->parent_name = '';
  $field_group->data = array(
    'label' => 'Left Side Content Link',
    'weight' => '3',
    'children' => array(
      0 => 'body',
      1 => 'field_content_reference',
      2 => 'field_link_text',
    ),
    'format_type' => 'fieldset',
    'format_settings' => array(
      'label' => 'Left Side Content Link',
      'instance_settings' => array(
        'required_fields' => 1,
        'classes' => '',
        'description' => '',
      ),
      'formatter' => 'collapsible',
    ),
  );
  $export['group_content_links_1|node|home_page_feature|form'] = $field_group;

  $field_group = new stdClass();
  $field_group->disabled = FALSE; /* Edit this to true to make a default field_group disabled initially */
  $field_group->api_version = 1;
  $field_group->identifier = 'group_content_links_2|node|home_page_feature|form';
  $field_group->group_name = 'group_content_links_2';
  $field_group->entity_type = 'node';
  $field_group->bundle = 'home_page_feature';
  $field_group->mode = 'form';
  $field_group->parent_name = '';
  $field_group->data = array(
    'label' => 'Right Side Content Link',
    'weight' => '4',
    'children' => array(
      0 => 'field_body_2',
      1 => 'field_content_reference_2',
      2 => 'field_link_text_2',
    ),
    'format_type' => 'fieldset',
    'format_settings' => array(
      'label' => 'Right Side Content Link',
      'instance_settings' => array(
        'required_fields' => 0,
        'classes' => '',
        'description' => '',
      ),
      'formatter' => 'collapsed',
    ),
  );
  $export['group_content_links_2|node|home_page_feature|form'] = $field_group;

  $field_group = new stdClass();
  $field_group->disabled = FALSE; /* Edit this to true to make a default field_group disabled initially */
  $field_group->api_version = 1;
  $field_group->identifier = 'group_content_links|node|home_page_feature|form';
  $field_group->group_name = 'group_content_links';
  $field_group->entity_type = 'node';
  $field_group->bundle = 'home_page_feature';
  $field_group->mode = 'form';
  $field_group->parent_name = '';
  $field_group->data = array(
    'label' => 'Content Links',
    'weight' => '2',
    'children' => array(
      0 => 'group_content_links_1',
      1 => 'group_content_links_2',
    ),
    'format_type' => 'tabs',
    'format_settings' => array(
      'formatter' => '',
      'instance_settings' => array(
        'classes' => '',
      ),
    ),
  );
  $export['group_content_links|node|home_page_feature|form'] = $field_group;

  return $export;
}
