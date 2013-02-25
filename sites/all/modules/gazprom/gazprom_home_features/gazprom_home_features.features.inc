<?php
/**
 * @file
 * gazprom_home_features.features.inc
 */

/**
 * Implements hook_ctools_plugin_api().
 */
function gazprom_home_features_ctools_plugin_api() {
  list($module, $api) = func_get_args();
  if ($module == "field_group" && $api == "field_group") {
    return array("version" => "1");
  }
}

/**
 * Implements hook_views_api().
 */
function gazprom_home_features_views_api() {
  return array("version" => "3.0");
}

/**
 * Implements hook_fe_nodequeue_export_fields().
 */
function gazprom_home_features_fe_nodequeue_export_fields() {
  $nodequeues = array();

  // Exported nodequeues: front_page_features
  $nodequeues['front_page_features'] = array(
    'qid' => '1',
    'name' => 'front_page_features',
    'title' => 'Front Page Features',
    'subqueue_title' => '',
    'size' => '0',
    'link' => 'add to front page features',
    'link_remove' => 'remove from front page features',
    'owner' => 'nodequeue',
    'show_in_ui' => '1',
    'show_in_tab' => '1',
    'show_in_links' => '1',
    'reference' => '0',
    'reverse' => '1',
    'i18n' => '1',
    'subqueues' => '1',
    'types' => array(
      0 => 'home_page_feature',
    ),
    'roles' => array(),
    'count' => 0,
  );

  // Exported nodequeues: news_media_featured
  $nodequeues['news_media_featured'] = array(
    'qid' => '3',
    'name' => 'news_media_featured',
    'title' => 'Home Page Small Featured Item',
    'subqueue_title' => '',
    'size' => '0',
    'link' => 'feature this',
    'link_remove' => 'feature this',
    'owner' => 'nodequeue',
    'show_in_ui' => '1',
    'show_in_tab' => '1',
    'show_in_links' => '1',
    'reference' => '0',
    'reverse' => '1',
    'i18n' => '0',
    'subqueues' => '1',
    'types' => array(
      0 => 'ceo_message',
      1 => 'management',
      2 => 'media_article',
      3 => 'media_collection',
      4 => 'media_corporate_news',
      5 => 'page',
      6 => 'page_code',
      7 => 'project',
      8 => 'webform',
    ),
    'roles' => array(),
    'count' => 0,
  );

  // Exported nodequeues: news_media_highlights
  $nodequeues['news_media_highlights'] = array(
    'qid' => '2',
    'name' => 'news_media_highlights',
    'title' => 'News/Media Highlights',
    'subqueue_title' => '',
    'size' => '0',
    'link' => 'add to highlights',
    'link_remove' => 'remove from highlights',
    'owner' => 'nodequeue',
    'show_in_ui' => '1',
    'show_in_tab' => '1',
    'show_in_links' => '1',
    'reference' => '0',
    'reverse' => '0',
    'i18n' => '1',
    'subqueues' => '1',
    'types' => array(),
    'roles' => array(),
    'count' => 0,
  );

  return $nodequeues;
}

/**
 * Implements hook_node_info().
 */
function gazprom_home_features_node_info() {
  $items = array(
    'home_page_feature' => array(
      'name' => t('Home Page Feature'),
      'base' => 'node_content',
      'description' => t('Featured content for the home page scroller.'),
      'has_title' => '1',
      'title_label' => t('Title'),
      'help' => '',
    ),
  );
  return $items;
}
