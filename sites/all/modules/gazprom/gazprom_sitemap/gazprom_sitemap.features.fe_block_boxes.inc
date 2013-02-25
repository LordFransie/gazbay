<?php
/**
 * @file
 * gazprom_sitemap.features.fe_block_boxes.inc
 */

/**
 * Implements hook_default_fe_block_boxes().
 */
function gazprom_sitemap_default_fe_block_boxes() {
  $export = array();

  $fe_block_boxes = new stdClass();
  $fe_block_boxes->info = 'Site Map Anchor';
  $fe_block_boxes->format = 'page_code';
  $fe_block_boxes->machine_name = 'site_map_link';
  $fe_block_boxes->body = '<div id="site-map-link">
  <a title="<?php print t(\'Site map\'); ?>"><?php print t(\'Site map\'); ?></a>
</div>';

  $export['site_map_link'] = $fe_block_boxes;

  return $export;
}
