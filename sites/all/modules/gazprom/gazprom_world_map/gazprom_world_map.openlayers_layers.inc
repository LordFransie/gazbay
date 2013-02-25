<?php
/**
 * @file
 * gazprom_world_map.openlayers_layers.inc
 */

/**
 * Implements hook_openlayers_layers().
 */
function gazprom_world_map_openlayers_layers() {
  $export = array();

  $openlayers_layers = new stdClass;
  $openlayers_layers->disabled = FALSE; /* Edit this to true to make a default openlayers_layers disabled initially */
  $openlayers_layers->api_version = 1;
  $openlayers_layers->name = 'gazprom_interactive';
  $openlayers_layers->title = 'Gazprom Interactive Map Layer';
  $openlayers_layers->description = 'was: Google Maps Satellite Imagery. Customized for limited zoom controls.';
  $openlayers_layers->data = array(
    'baselayer' => TRUE,
    'type' => 'satellite',
    'projection' => array(
      0 => '900913',
    ),
    'layer_type' => 'openlayers_layer_type_google',
    'animationEnabled' => 1,
    'MIN_ZOOM_LEVEL' => 3,
    'MAX_ZOOM_LEVEL' => 6,
  );
  $export['gazprom_interactive'] = $openlayers_layers;

  return $export;
}
