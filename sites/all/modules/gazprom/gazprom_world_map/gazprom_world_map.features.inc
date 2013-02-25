<?php
/**
 * @file
 * gazprom_world_map.features.inc
 */

/**
 * Implements hook_ctools_plugin_api().
 */
function gazprom_world_map_ctools_plugin_api() {
  list($module, $api) = func_get_args();
  if ($module == "openlayers" && $api == "openlayers_layers") {
    return array("version" => "1");
  }
  list($module, $api) = func_get_args();
  if ($module == "openlayers" && $api == "openlayers_maps") {
    return array("version" => "1");
  }
  list($module, $api) = func_get_args();
  if ($module == "openlayers" && $api == "openlayers_styles") {
    return array("version" => "1");
  }
}

/**
 * Implements hook_views_api().
 */
function gazprom_world_map_views_api() {
  list($module, $api) = func_get_args();
  if ($module == "views" && $api == "views_default") {
    return array("version" => "3.0");
  }
}

/**
 * Implements hook_image_default_styles().
 */
function gazprom_world_map_image_default_styles() {
  $styles = array();

  // Exported image style: map-popup-85
  $styles['map-popup-85'] = array(
    'name' => 'map-popup-85',
    'effects' => array(
      25 => array(
        'label' => 'Scale',
        'help' => 'Scaling will maintain the aspect-ratio of the original image. If only a single dimension is specified, the other dimension will be calculated.',
        'effect callback' => 'image_scale_effect',
        'dimensions callback' => 'image_scale_dimensions',
        'form callback' => 'image_scale_form',
        'summary theme' => 'image_scale_summary',
        'module' => 'image',
        'name' => 'image_scale',
        'data' => array(
          'width' => '85',
          'height' => '',
          'upscale' => 0,
        ),
        'weight' => '1',
      ),
    ),
  );

  // Exported image style: map-popup-85x85
  $styles['map-popup-85x85'] = array(
    'name' => 'map-popup-85x85',
    'effects' => array(
      19 => array(
        'label' => 'Change file format',
        'help' => 'Choose to save the image as a different filetype.',
        'effect callback' => 'coloractions_convert_image',
        'form callback' => 'coloractions_convert_form',
        'summary theme' => 'coloractions_convert_summary',
        'module' => 'imagecache_coloractions',
        'name' => 'coloractions_convert',
        'data' => array(
          'format' => 'image/gif',
          'quality' => '75',
        ),
        'weight' => '-10',
      ),
      18 => array(
        'label' => 'Scale and crop',
        'help' => 'Scale and crop will maintain the aspect-ratio of the original image, then crop the larger dimension. This is most useful for creating perfectly square thumbnails without stretching the image.',
        'effect callback' => 'image_scale_and_crop_effect',
        'dimensions callback' => 'image_resize_dimensions',
        'form callback' => 'image_resize_form',
        'summary theme' => 'image_resize_summary',
        'module' => 'image',
        'name' => 'image_scale_and_crop',
        'data' => array(
          'width' => '85',
          'height' => '85',
        ),
        'weight' => '-9',
      ),
    ),
  );

  return $styles;
}
