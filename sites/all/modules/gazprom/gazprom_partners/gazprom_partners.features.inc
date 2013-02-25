<?php
/**
 * @file
 * gazprom_partners.features.inc
 */

/**
 * Implements hook_views_api().
 */
function gazprom_partners_views_api() {
  return array("version" => "3.0");
}

/**
 * Implements hook_image_default_styles().
 */
function gazprom_partners_image_default_styles() {
  $styles = array();

  // Exported image style: partner_logo_bw
  $styles['partner_logo_bw'] = array(
    'name' => 'partner_logo_bw',
    'effects' => array(
      14 => array(
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
      15 => array(
        'label' => 'Scale',
        'help' => 'Scaling will maintain the aspect-ratio of the original image. If only a single dimension is specified, the other dimension will be calculated.',
        'effect callback' => 'image_scale_effect',
        'dimensions callback' => 'image_scale_dimensions',
        'form callback' => 'image_scale_form',
        'summary theme' => 'image_scale_summary',
        'module' => 'image',
        'name' => 'image_scale',
        'data' => array(
          'width' => '165',
          'height' => '165',
          'upscale' => 0,
        ),
        'weight' => '-9',
      ),
      16 => array(
        'label' => 'Desaturate',
        'help' => 'Desaturate converts an image to grayscale.',
        'effect callback' => 'image_desaturate_effect',
        'dimensions passthrough' => TRUE,
        'module' => 'image',
        'name' => 'image_desaturate',
        'data' => array(),
        'weight' => '-8',
      ),
      17 => array(
        'label' => 'Define canvas',
        'help' => 'Define the size of the working canvas and background color, this controls the dimensions of the output image.',
        'effect callback' => 'canvasactions_definecanvas_image',
        'form callback' => 'canvasactions_definecanvas_form',
        'summary theme' => 'canvasactions_definecanvas_summary',
        'module' => 'imagecache_canvasactions',
        'name' => 'canvasactions_definecanvas',
        'data' => array(
          'RGB' => array(
            'HEX' => '',
          ),
          'under' => 1,
          'exact' => array(
            'width' => '165',
            'height' => '165',
            'xpos' => 'center',
            'ypos' => 'top',
          ),
          'relative' => array(
            'leftdiff' => '',
            'rightdiff' => '',
            'topdiff' => '',
            'bottomdiff' => '',
          ),
        ),
        'weight' => '-6',
      ),
    ),
  );

  // Exported image style: partner_logo_color
  $styles['partner_logo_color'] = array(
    'name' => 'partner_logo_color',
    'effects' => array(
      11 => array(
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
      12 => array(
        'label' => 'Scale',
        'help' => 'Scaling will maintain the aspect-ratio of the original image. If only a single dimension is specified, the other dimension will be calculated.',
        'effect callback' => 'image_scale_effect',
        'dimensions callback' => 'image_scale_dimensions',
        'form callback' => 'image_scale_form',
        'summary theme' => 'image_scale_summary',
        'module' => 'image',
        'name' => 'image_scale',
        'data' => array(
          'width' => '165',
          'height' => '165',
          'upscale' => 0,
        ),
        'weight' => '-9',
      ),
      13 => array(
        'label' => 'Define canvas',
        'help' => 'Define the size of the working canvas and background color, this controls the dimensions of the output image.',
        'effect callback' => 'canvasactions_definecanvas_image',
        'form callback' => 'canvasactions_definecanvas_form',
        'summary theme' => 'canvasactions_definecanvas_summary',
        'module' => 'imagecache_canvasactions',
        'name' => 'canvasactions_definecanvas',
        'data' => array(
          'RGB' => array(
            'HEX' => '',
          ),
          'under' => 1,
          'exact' => array(
            'width' => '165',
            'height' => '165',
            'xpos' => 'center',
            'ypos' => 'top',
          ),
          'relative' => array(
            'leftdiff' => '',
            'rightdiff' => '',
            'topdiff' => '',
            'bottomdiff' => '',
          ),
        ),
        'weight' => '3',
      ),
    ),
  );

  return $styles;
}

/**
 * Implements hook_node_info().
 */
function gazprom_partners_node_info() {
  $items = array(
    'partner' => array(
      'name' => t('Partner'),
      'base' => 'node_content',
      'description' => t('Content type to contain a Gazprom International partner.'),
      'has_title' => '1',
      'title_label' => t('Partner Name'),
      'help' => '',
    ),
  );
  return $items;
}
