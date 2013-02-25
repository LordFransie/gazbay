<?php
/**
 * @file
 * gazprom_management.features.inc
 */

/**
 * Implements hook_ctools_plugin_api().
 */
function gazprom_management_ctools_plugin_api() {
  list($module, $api) = func_get_args();
  if ($module == "quicktabs" && $api == "quicktabs") {
    return array("version" => "1");
  }
}

/**
 * Implements hook_views_api().
 */
function gazprom_management_views_api() {
  return array("version" => "3.0");
}

/**
 * Implements hook_image_default_styles().
 */
function gazprom_management_image_default_styles() {
  $styles = array();

  // Exported image style: management_photo
  $styles['management_photo'] = array(
    'name' => 'management_photo',
    'effects' => array(
      13 => array(
        'label' => 'Scale',
        'help' => 'Scaling will maintain the aspect-ratio of the original image. If only a single dimension is specified, the other dimension will be calculated.',
        'effect callback' => 'image_scale_effect',
        'dimensions callback' => 'image_scale_dimensions',
        'form callback' => 'image_scale_form',
        'summary theme' => 'image_scale_summary',
        'module' => 'image',
        'name' => 'image_scale',
        'data' => array(
          'width' => '140',
          'height' => '',
          'upscale' => 0,
        ),
        'weight' => '1',
      ),
    ),
  );

  return $styles;
}

/**
 * Implements hook_node_info().
 */
function gazprom_management_node_info() {
  $items = array(
    'ceo_message' => array(
      'name' => t('Our Message'),
      'base' => 'node_content',
      'description' => t('Contents of Our Message nodes.'),
      'has_title' => '1',
      'title_label' => t('Title'),
      'help' => '',
    ),
    'management' => array(
      'name' => t('Management'),
      'base' => 'node_content',
      'description' => t('Use for bios of top managers and supervisory board members.'),
      'has_title' => '1',
      'title_label' => t('Full Name'),
      'help' => '',
    ),
  );
  return $items;
}
