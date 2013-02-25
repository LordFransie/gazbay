<?php
/**
 * @file
 * gazprom_foreign_rep_office.features.inc
 */

/**
 * Implements hook_views_api().
 */
function gazprom_foreign_rep_office_views_api() {
  return array("version" => "3.0");
}

/**
 * Implements hook_image_default_styles().
 */
function gazprom_foreign_rep_office_image_default_styles() {
  $styles = array();

  // Exported image style: flag_144
  $styles['flag_144'] = array(
    'name' => 'flag_144',
    'effects' => array(
      12 => array(
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
      11 => array(
        'label' => 'Scale',
        'help' => 'Scaling will maintain the aspect-ratio of the original image. If only a single dimension is specified, the other dimension will be calculated.',
        'effect callback' => 'image_scale_effect',
        'dimensions callback' => 'image_scale_dimensions',
        'form callback' => 'image_scale_form',
        'summary theme' => 'image_scale_summary',
        'module' => 'image',
        'name' => 'image_scale',
        'data' => array(
          'width' => '144',
          'height' => '',
          'upscale' => 0,
        ),
        'weight' => '-9',
      ),
    ),
  );

  return $styles;
}

/**
 * Implements hook_node_info().
 */
function gazprom_foreign_rep_office_node_info() {
  $items = array(
    'foreign_rep_office' => array(
      'name' => t('Foreign Rep Office'),
      'base' => 'node_content',
      'description' => t('One node for each Gazprom International office'),
      'has_title' => '1',
      'title_label' => t('Complete Name of Office'),
      'help' => '',
    ),
  );
  return $items;
}
