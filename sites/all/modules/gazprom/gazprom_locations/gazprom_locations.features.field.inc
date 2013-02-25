<?php
/**
 * @file
 * gazprom_locations.features.field.inc
 */

/**
 * Implements hook_field_default_fields().
 */
function gazprom_locations_field_default_fields() {
  $fields = array();

  // Exported field: 'taxonomy_term-location-field_flag_image'
  $fields['taxonomy_term-location-field_flag_image'] = array(
    'field_config' => array(
      'active' => '1',
      'cardinality' => '1',
      'deleted' => '0',
      'entity_types' => array(),
      'field_name' => 'field_flag_image',
      'foreign keys' => array(
        'fid' => array(
          'columns' => array(
            'fid' => 'fid',
          ),
          'table' => 'file_managed',
        ),
      ),
      'indexes' => array(
        'fid' => array(
          0 => 'fid',
        ),
      ),
      'module' => 'image',
      'settings' => array(
        'default_image' => 0,
        'uri_scheme' => 'public',
      ),
      'translatable' => '0',
      'type' => 'image',
    ),
    'field_instance' => array(
      'bundle' => 'location',
      'deleted' => '0',
      'description' => '',
      'display' => array(
        'default' => array(
          'label' => 'hidden',
          'module' => 'image',
          'settings' => array(
            'image_link' => '',
            'image_style' => '',
          ),
          'type' => 'image',
          'weight' => '1',
        ),
        'full' => array(
          'label' => 'hidden',
          'module' => 'image',
          'settings' => array(
            'image_link' => '',
            'image_style' => '',
          ),
          'type' => 'image',
          'weight' => '3',
        ),
      ),
      'entity_type' => 'taxonomy_term',
      'field_name' => 'field_flag_image',
      'label' => 'Flag',
      'required' => 0,
      'settings' => array(
        'alt_field' => 0,
        'file_directory' => '',
        'file_extensions' => 'png gif jpg jpeg',
        'filefield_paths' => array(
          'active_updating' => 0,
          'file_name' => array(
            'options' => array(
              'pathauto' => 0,
              'transliterate' => 0,
            ),
            'value' => '[file:ffp-name-only-original].[file:ffp-extension-original]',
          ),
          'file_path' => array(
            'options' => array(
              'pathauto' => 0,
              'transliterate' => 0,
            ),
            'value' => '',
          ),
          'retroactive_update' => 0,
        ),
        'max_filesize' => '',
        'max_resolution' => '',
        'min_resolution' => '',
        'title_field' => 0,
        'user_register_form' => FALSE,
      ),
      'widget' => array(
        'active' => 1,
        'module' => 'image',
        'settings' => array(
          'insert' => 0,
          'insert_class' => '',
          'insert_default' => 'auto',
          'insert_styles' => array(
            'auto' => 'auto',
            'image' => 0,
            'image_album_list_50x50' => 0,
            'image_backgrounder' => 0,
            'image_cheap_dropshadow' => 0,
            'image_corners_combo' => 0,
            'image_default' => 0,
            'image_flag_160x105' => 0,
            'image_grid-square' => 0,
            'image_keyword_positioning' => 0,
            'image_large' => 0,
            'image_media_thumbnail_standard' => 0,
            'image_medium' => 0,
            'image_overlay_primary_240x170' => 0,
            'image_photo_set_thumbnail' => 0,
            'image_positioned_underlay' => 0,
            'image_primary_image_300' => 0,
            'image_relative_canvas' => 0,
            'image_rotate_alpha' => 0,
            'image_rotate_alpha_gif' => 0,
            'image_rotate_scale' => 0,
            'image_rotate_scale_alpha' => 0,
            'image_rounded' => 0,
            'image_rounded_bl' => 0,
            'image_rounded_flattened' => 0,
            'image_scale' => 0,
            'image_scale_canvas' => 0,
            'image_scale_rotate' => 0,
            'image_thumbnail' => 0,
            'image_watermark_100' => 0,
            'image_watermark_50' => 0,
            'link' => 0,
          ),
          'insert_width' => '',
          'preview_image_style' => 'thumbnail',
          'progress_indicator' => 'bar',
        ),
        'type' => 'image_image',
        'weight' => '2',
      ),
    ),
  );

  // Exported field: 'taxonomy_term-location-field_geo_location'
  $fields['taxonomy_term-location-field_geo_location'] = array(
    'field_config' => array(
      'active' => '1',
      'cardinality' => '1',
      'deleted' => '0',
      'entity_types' => array(),
      'field_name' => 'field_geo_location',
      'foreign keys' => array(),
      'indexes' => array(),
      'module' => 'geofield',
      'settings' => array(),
      'translatable' => '0',
      'type' => 'geofield',
    ),
    'field_instance' => array(
      'bundle' => 'location',
      'default_value' => NULL,
      'deleted' => '0',
      'description' => 'Using the point tool, select the location you would like this country to use on the interactive map.',
      'display' => array(
        'default' => array(
          'label' => 'above',
          'settings' => array(),
          'type' => 'hidden',
          'weight' => '2',
        ),
        'full' => array(
          'label' => 'above',
          'settings' => array(),
          'type' => 'hidden',
          'weight' => '0',
        ),
      ),
      'entity_type' => 'taxonomy_term',
      'field_name' => 'field_geo_location',
      'label' => 'Geo Location',
      'required' => 0,
      'settings' => array(
        'local_solr' => array(
          'enabled' => FALSE,
          'lat_field' => 'lat',
          'lng_field' => 'lng',
        ),
        'user_register_form' => FALSE,
      ),
      'widget' => array(
        'active' => 1,
        'module' => 'geofield',
        'settings' => array(
          'openlayers_map' => 'geofield_widget_map_custom',
        ),
        'type' => 'geofield_openlayers',
        'weight' => '5',
      ),
    ),
  );

  // Translatables
  // Included for use with string extractors like potx.
  t('Flag');
  t('Geo Location');
  t('Using the point tool, select the location you would like this country to use on the interactive map.');

  return $fields;
}
