<?php
/**
 * @file
 * gazprom_world_map.openlayers_styles.inc
 */

/**
 * Implements hook_openlayers_styles().
 */
function gazprom_world_map_openlayers_styles() {
  $export = array();

  $openlayers_styles = new stdClass;
  $openlayers_styles->disabled = FALSE; /* Edit this to true to make a default openlayers_styles disabled initially */
  $openlayers_styles->api_version = 1;
  $openlayers_styles->name = 'gazprom_marker_large_lit';
  $openlayers_styles->title = 'Gazprom Flame Large Lit';
  $openlayers_styles->description = 'Gazprom Flame Large Lit';
  $openlayers_styles->data = array(
    'externalGraphic' => '/sites/all/modules/gazprom/gazprom_world_map/openlayers_themes/gazprom_1/markers/FlameIcon_Large_Lit.png',
    'pointRadius' => 40,
    'fillColor' => '#EE9900',
    'strokeColor' => '#EE9900',
    'strokeWidth' => 1,
    'fillOpacity' => 1,
    'strokeOpacity' => 1,
    'strokeLinecap' => 'round',
    'strokeDashstyle' => 'solid',
    'cursor' => 'pointer',
    'graphicWidth' => 81,
    'graphicHeight' => 138,
    'graphicOpacity' => 1,
    'graphicXOffset' => -40,
    'graphicYOffset' => -115,
    'graphicName' => 'Gazprom Flame Unlit',
    'labelAlign' => 'cm',
  );
  $export['gazprom_marker_large_lit'] = $openlayers_styles;

  $openlayers_styles = new stdClass;
  $openlayers_styles->disabled = FALSE; /* Edit this to true to make a default openlayers_styles disabled initially */
  $openlayers_styles->api_version = 1;
  $openlayers_styles->name = 'gazprom_marker_small_lit';
  $openlayers_styles->title = 'Gazprom Flame Small Lit';
  $openlayers_styles->description = 'Gazprom Flame Small Lit';
  $openlayers_styles->data = array(
    'externalGraphic' => '/sites/all/modules/gazprom/gazprom_world_map/openlayers_themes/gazprom_1/markers/FlameIcon_Small_Lit.png',
    'pointRadius' => 30,
    'fillColor' => '#EE9900',
    'strokeColor' => '#EE9900',
    'strokeWidth' => 1,
    'fillOpacity' => 1,
    'strokeOpacity' => 1,
    'strokeLinecap' => 'round',
    'strokeDashstyle' => 'solid',
    'cursor' => 'pointer',
    'graphicWidth' => 60,
    'graphicHeight' => 81,
    'graphicOpacity' => 1,
    'graphicXOffset' => -30,
    'graphicYOffset' => -60,
    'graphicName' => 'Gazprom Flame Unlit',
    'labelAlign' => 'cm',
  );
  $export['gazprom_marker_small_lit'] = $openlayers_styles;

  $openlayers_styles = new stdClass;
  $openlayers_styles->disabled = FALSE; /* Edit this to true to make a default openlayers_styles disabled initially */
  $openlayers_styles->api_version = 1;
  $openlayers_styles->name = 'gazprom_marker_small_unlit';
  $openlayers_styles->title = 'Gazprom Flame Small Unlit';
  $openlayers_styles->description = 'Gazprom Flame Small Unlit';
  $openlayers_styles->data = array(
    'externalGraphic' => '/sites/all/modules/gazprom/gazprom_world_map/openlayers_themes/gazprom_1/markers/FlameIcon_Small_UnLit.png',
    'pointRadius' => 30,
    'fillColor' => '#EE9900',
    'strokeColor' => '#EE9900',
    'strokeWidth' => 1,
    'fillOpacity' => 1,
    'strokeOpacity' => 1,
    'strokeLinecap' => 'round',
    'strokeDashstyle' => 'solid',
    'cursor' => 'pointer',
    'graphicWidth' => 60,
    'graphicHeight' => 81,
    'graphicOpacity' => 1,
    'graphicXOffset' => -30,
    'graphicYOffset' => -60,
    'graphicName' => 'Gazprom Flame Unlit',
    'labelAlign' => 'cm',
  );
  $export['gazprom_marker_small_unlit'] = $openlayers_styles;

  return $export;
}
