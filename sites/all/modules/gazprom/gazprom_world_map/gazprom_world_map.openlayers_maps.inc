<?php
/**
 * @file
 * gazprom_world_map.openlayers_maps.inc
 */

/**
 * Implements hook_openlayers_maps().
 */
function gazprom_world_map_openlayers_maps() {
  $export = array();

  $openlayers_maps = new stdClass;
  $openlayers_maps->disabled = FALSE; /* Edit this to true to make a default openlayers_maps disabled initially */
  $openlayers_maps->api_version = 1;
  $openlayers_maps->name = 'geofield_widget_map_custom';
  $openlayers_maps->title = 'Geofield Widget Map (Custom)';
  $openlayers_maps->description = 'A Map Used for Geofield Input';
  $openlayers_maps->data = array(
    'width' => '580px',
    'height' => '580px',
    'image_path' => 'sites/all/modules/contrib_map_modules/openlayers/themes/default_dark/img/',
    'css_path' => 'sites/all/modules/contrib_map_modules/openlayers/themes/default_dark/style.css',
    'proxy_host' => '',
    'hide_empty_map' => 0,
    'center' => array(
      'initial' => array(
        'centerpoint' => '2,2',
        'zoom' => '3',
      ),
      'restrict' => array(
        'restrictextent' => 0,
        'restrictedExtent' => '',
      ),
    ),
    'behaviors' => array(
      'openlayers_behavior_geofield' => array(
        'feature_types' => array(
          'point' => 'point',
          'path' => 0,
          'polygon' => 0,
        ),
      ),
      'openlayers_behavior_keyboarddefaults' => array(),
      'openlayers_behavior_layerswitcher' => array(
        'ascending' => 1,
        'roundedCorner' => 1,
        'roundedCornerColor' => '#222222',
      ),
      'openlayers_behavior_navigation' => array(
        'zoomWheelEnabled' => 0,
        'zoomBoxEnabled' => 1,
        'documentDrag' => 0,
      ),
      'openlayers_behavior_panzoombar' => array(
        'zoomWorldIcon' => 0,
        'panIcons' => 1,
      ),
    ),
    'default_layer' => 'osm_mapnik',
    'layers' => array(
      'google_satellite' => 'google_satellite',
      'gazprom_interactive' => 'gazprom_interactive',
      'google_hybrid' => 'google_hybrid',
      'google_normal' => 'google_normal',
      'osm_mapnik' => 'osm_mapnik',
    ),
    'layer_weight' => array(
      'world_map_openlayers_1' => '0',
      'openlayers_geojson_picture_this' => '0',
      'geofield_formatter' => '0',
    ),
    'layer_styles' => array(
      'geofield_formatter' => '0',
      'openlayers_geojson_picture_this' => '0',
      'world_map_openlayers_1' => '0',
    ),
    'layer_styles_select' => array(
      'geofield_formatter' => '0',
      'openlayers_geojson_picture_this' => '0',
      'world_map_openlayers_1' => '0',
    ),
    'layer_activated' => array(
      'geofield_formatter' => 0,
      'openlayers_geojson_picture_this' => 0,
      'world_map_openlayers_1' => 0,
    ),
    'layer_switcher' => array(
      'geofield_formatter' => 0,
      'openlayers_geojson_picture_this' => 0,
      'world_map_openlayers_1' => 0,
    ),
    'projection' => '900913',
    'displayProjection' => '4326',
    'styles' => array(
      'default' => 'default_marker_red',
      'select' => 'default_marker_green',
      'temporary' => 'default_marker_gold',
    ),
  );
  $export['geofield_widget_map_custom'] = $openlayers_maps;

  $openlayers_maps = new stdClass;
  $openlayers_maps->disabled = FALSE; /* Edit this to true to make a default openlayers_maps disabled initially */
  $openlayers_maps->api_version = 1;
  $openlayers_maps->name = 'world_map_1';
  $openlayers_maps->title = 'World Map';
  $openlayers_maps->description = 'The interactive map for the Operations section';
  $openlayers_maps->data = array(
    'width' => 'auto',
    'height' => '920px',
    'image_path' => 'sites/all/modules/contrib_map_modules/openlayers/themes/default_dark/img/',
    'css_path' => 'sites/all/modules/contrib_map_modules/openlayers/themes/default_dark/style.css',
    'proxy_host' => '',
    'hide_empty_map' => 0,
    'center' => array(
      'initial' => array(
        'centerpoint' => '0, 0',
        'zoom' => '0',
      ),
      'restrict' => array(
        'restrictextent' => 0,
        'restrictedExtent' => '',
      ),
    ),
    'behaviors' => array(
      'gazprom_openlayers_behavior_tooltip' => array(
        'layers' => array(
          'world_map_openlayers_1' => 'world_map_openlayers_1',
        ),
      ),
      'openlayers_behavior_navigation' => array(
        'zoomWheelEnabled' => 0,
        'zoomBoxEnabled' => 1,
        'documentDrag' => 0,
      ),
      'openlayers_behavior_panzoombar' => array(
        'zoomWorldIcon' => 0,
        'panIcons' => 1,
      ),
    ),
    'default_layer' => 'gazprom_interactive',
    'layers' => array(
      'gazprom_interactive' => 'gazprom_interactive',
      'world_map_openlayers_1' => 'world_map_openlayers_1',
    ),
    'layer_weight' => array(
      'world_map_openlayers_1' => '0',
      'openlayers_geojson_picture_this' => '0',
      'geofield_formatter' => '0',
    ),
    'layer_styles' => array(
      'geofield_formatter' => '0',
      'openlayers_geojson_picture_this' => '0',
      'world_map_openlayers_1' => 'gazprom_marker_small_lit',
    ),
    'layer_styles_select' => array(
      'geofield_formatter' => '0',
      'openlayers_geojson_picture_this' => '0',
      'world_map_openlayers_1' => 'gazprom_marker_large_lit',
    ),
    'layer_activated' => array(
      'world_map_openlayers_1' => 'world_map_openlayers_1',
      'geofield_formatter' => 0,
      'openlayers_geojson_picture_this' => 0,
    ),
    'layer_switcher' => array(
      'geofield_formatter' => 0,
      'openlayers_geojson_picture_this' => 0,
      'world_map_openlayers_1' => 0,
    ),
    'projection' => '900913',
    'displayProjection' => '4326',
    'styles' => array(
      'default' => 'gazprom_marker_small_lit',
      'select' => 'gazprom_marker_large_lit',
      'temporary' => 'gazprom_marker_small_unlit',
    ),
  );
  $export['world_map_1'] = $openlayers_maps;

  $openlayers_maps = new stdClass;
  $openlayers_maps->disabled = FALSE; /* Edit this to true to make a default openlayers_maps disabled initially */
  $openlayers_maps->api_version = 1;
  $openlayers_maps->name = 'world_map_2';
  $openlayers_maps->title = 'World Map (Node)';
  $openlayers_maps->description = 'The interactive map for the Operations section. Works with nodes (country_page) instead of taxonomy.';
  $openlayers_maps->data = array(
    'width' => 'auto',
    'height' => '920px',
    'image_path' => 'sites/all/modules/contrib_map_modules/openlayers/themes/default_dark/img/',
    'css_path' => 'sites/all/modules/contrib_map_modules/openlayers/themes/default_dark/style.css',
    'proxy_host' => '',
    'hide_empty_map' => 0,
    'center' => array(
      'initial' => array(
        'centerpoint' => '0, 20',
        'zoom' => '0',
      ),
      'restrict' => array(
        'restrictextent' => 0,
        'restrictedExtent' => '',
      ),
    ),
    'behaviors' => array(
      'gazprom_openlayers_behavior_tooltip' => array(
        'layers' => array(
          'world_map_2_openlayers_1' => 'world_map_2_openlayers_1',
        ),
      ),
      'openlayers_behavior_navigation' => array(
        'zoomWheelEnabled' => 0,
        'zoomBoxEnabled' => 1,
        'documentDrag' => 0,
      ),
      'openlayers_behavior_panzoombar' => array(
        'zoomWorldIcon' => 0,
        'panIcons' => 1,
      ),
    ),
    'default_layer' => 'gazprom_interactive',
    'layers' => array(
      'gazprom_interactive' => 'gazprom_interactive',
      'world_map_2_openlayers_1' => 'world_map_2_openlayers_1',
    ),
    'layer_weight' => array(
      'world_map_2_openlayers_1' => '0',
      'world_map_openlayers_1' => '0',
      'openlayers_geojson_picture_this' => '0',
      'geofield_formatter' => '0',
    ),
    'layer_styles' => array(
      'geofield_formatter' => '0',
      'openlayers_geojson_picture_this' => '0',
      'world_map_openlayers_1' => 'gazprom_marker_small_lit',
      'world_map_2_openlayers_1' => 'gazprom_marker_small_lit',
    ),
    'layer_styles_select' => array(
      'geofield_formatter' => '0',
      'openlayers_geojson_picture_this' => '0',
      'world_map_openlayers_1' => 'gazprom_marker_large_lit',
      'world_map_2_openlayers_1' => 'gazprom_marker_large_lit',
    ),
    'layer_activated' => array(
      'world_map_2_openlayers_1' => 'world_map_2_openlayers_1',
      'geofield_formatter' => 0,
      'openlayers_geojson_picture_this' => 0,
      'world_map_openlayers_1' => 0,
    ),
    'layer_switcher' => array(
      'geofield_formatter' => 0,
      'openlayers_geojson_picture_this' => 0,
      'world_map_2_openlayers_1' => 0,
      'world_map_openlayers_1' => 0,
    ),
    'projection' => '900913',
    'displayProjection' => '4326',
    'styles' => array(
      'default' => 'gazprom_marker_small_lit',
      'select' => 'gazprom_marker_large_lit',
      'temporary' => 'gazprom_marker_small_unlit',
    ),
  );
  $export['world_map_2'] = $openlayers_maps;

  return $export;
}
