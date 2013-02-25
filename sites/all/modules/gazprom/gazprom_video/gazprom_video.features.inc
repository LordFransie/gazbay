<?php
/**
 * @file
 * gazprom_video.features.inc
 */

/**
 * Implements hook_views_api().
 */
function gazprom_video_views_api() {
  return array("version" => "3.0");
}

/**
 * Implements hook_image_default_styles().
 */
function gazprom_video_image_default_styles() {
  $styles = array();

  // Exported image style: video_thumbnail_240
  $styles['video_thumbnail_240'] = array(
    'name' => 'video_thumbnail_240',
    'effects' => array(
      23 => array(
        'label' => 'Subroutine',
        'help' => 'Runs another defined preset on the image.',
        'effect callback' => 'imagecache_subroutine_image',
        'form callback' => 'imagecache_subroutine_form',
        'module' => 'imagecache_customactions',
        'name' => 'imagecache_subroutine',
        'data' => array(
          'subroutine_presetname' => 'video_thumbnail_300',
        ),
        'weight' => '1',
      ),
      24 => array(
        'label' => 'Scale',
        'help' => 'Scaling will maintain the aspect-ratio of the original image. If only a single dimension is specified, the other dimension will be calculated.',
        'effect callback' => 'image_scale_effect',
        'dimensions callback' => 'image_scale_dimensions',
        'form callback' => 'image_scale_form',
        'summary theme' => 'image_scale_summary',
        'module' => 'image',
        'name' => 'image_scale',
        'data' => array(
          'width' => '240',
          'height' => '',
          'upscale' => 0,
        ),
        'weight' => '2',
      ),
    ),
  );

  // Exported image style: video_thumbnail_300
  $styles['video_thumbnail_300'] = array(
    'name' => 'video_thumbnail_300',
    'effects' => array(
      23 => array(
        'label' => 'Scale',
        'help' => 'Scaling will maintain the aspect-ratio of the original image. If only a single dimension is specified, the other dimension will be calculated.',
        'effect callback' => 'image_scale_effect',
        'dimensions callback' => 'image_scale_dimensions',
        'form callback' => 'image_scale_form',
        'summary theme' => 'image_scale_summary',
        'module' => 'image',
        'name' => 'image_scale',
        'data' => array(
          'width' => '300',
          'height' => '',
          'upscale' => 0,
        ),
        'weight' => '1',
      ),
      24 => array(
        'label' => 'Crop',
        'help' => 'Cropping will remove portions of an image to make it the specified dimensions.',
        'effect callback' => 'image_crop_effect',
        'dimensions callback' => 'image_resize_dimensions',
        'form callback' => 'image_crop_form',
        'summary theme' => 'image_crop_summary',
        'module' => 'image',
        'name' => 'image_crop',
        'data' => array(
          'width' => '300',
          'height' => '212',
          'anchor' => 'center-center',
        ),
        'weight' => '2',
      ),
      28 => array(
        'label' => 'Overlay (watermark)',
        'help' => 'Choose the file image you wish to use as an overlay, and position it in a layer on top of the canvas.',
        'effect callback' => 'canvasactions_file2canvas_image',
        'form callback' => 'canvasactions_file2canvas_form',
        'summary theme' => 'canvasactions_file2canvas_summary',
        'module' => 'imagecache_canvasactions',
        'name' => 'canvasactions_file2canvas',
        'data' => array(
          'xpos' => 'center',
          'ypos' => 'center',
          'alpha' => '100',
          'path' => 'sites/all/themes/gazprom/images/play-btn.png',
        ),
        'weight' => '3',
      ),
    ),
  );

  // Exported image style: video_thumbnail_large
  $styles['video_thumbnail_large'] = array(
    'name' => 'video_thumbnail_large',
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
          'width' => '240',
          'height' => '',
          'upscale' => 0,
        ),
        'weight' => '1',
      ),
      26 => array(
        'label' => 'Crop',
        'help' => 'Cropping will remove portions of an image to make it the specified dimensions.',
        'effect callback' => 'image_crop_effect',
        'dimensions callback' => 'image_resize_dimensions',
        'form callback' => 'image_crop_form',
        'summary theme' => 'image_crop_summary',
        'module' => 'image',
        'name' => 'image_crop',
        'data' => array(
          'width' => '240',
          'height' => '170',
          'anchor' => 'center-center',
        ),
        'weight' => '2',
      ),
      27 => array(
        'label' => 'Overlay (watermark)',
        'help' => 'Choose the file image you wish to use as an overlay, and position it in a layer on top of the canvas.',
        'effect callback' => 'canvasactions_file2canvas_image',
        'form callback' => 'canvasactions_file2canvas_form',
        'summary theme' => 'canvasactions_file2canvas_summary',
        'module' => 'imagecache_canvasactions',
        'name' => 'canvasactions_file2canvas',
        'data' => array(
          'xpos' => 'center',
          'ypos' => 'center',
          'alpha' => '100',
          'path' => 'sites/all/themes/gazprom/images/play-btn.png',
        ),
        'weight' => '3',
      ),
    ),
  );

  // Exported image style: video_thumbnail_small
  $styles['video_thumbnail_small'] = array(
    'name' => 'video_thumbnail_small',
    'effects' => array(
      29 => array(
        'label' => 'Subroutine',
        'help' => 'Runs another defined preset on the image.',
        'effect callback' => 'imagecache_subroutine_image',
        'form callback' => 'imagecache_subroutine_form',
        'module' => 'imagecache_customactions',
        'name' => 'imagecache_subroutine',
        'data' => array(
          'subroutine_presetname' => 'video_thumbnail_large',
        ),
        'weight' => '1',
      ),
      30 => array(
        'label' => 'Scale',
        'help' => 'Scaling will maintain the aspect-ratio of the original image. If only a single dimension is specified, the other dimension will be calculated.',
        'effect callback' => 'image_scale_effect',
        'dimensions callback' => 'image_scale_dimensions',
        'form callback' => 'image_scale_form',
        'summary theme' => 'image_scale_summary',
        'module' => 'image',
        'name' => 'image_scale',
        'data' => array(
          'width' => '180',
          'height' => '',
          'upscale' => 0,
        ),
        'weight' => '2',
      ),
      31 => array(
        'label' => 'Crop',
        'help' => 'Cropping will remove portions of an image to make it the specified dimensions.',
        'effect callback' => 'image_crop_effect',
        'dimensions callback' => 'image_resize_dimensions',
        'form callback' => 'image_crop_form',
        'summary theme' => 'image_crop_summary',
        'module' => 'image',
        'name' => 'image_crop',
        'data' => array(
          'width' => '180',
          'height' => '115',
          'anchor' => 'center-center',
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
function gazprom_video_node_info() {
  $items = array(
    'media_videos' => array(
      'name' => t('Media: Videos'),
      'base' => 'node_content',
      'description' => '',
      'has_title' => '1',
      'title_label' => t('Title'),
      'help' => '',
    ),
  );
  return $items;
}
