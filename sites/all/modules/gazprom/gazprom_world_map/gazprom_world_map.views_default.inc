<?php
/**
 * @file
 * gazprom_world_map.views_default.inc
 */

/**
 * Implements hook_views_default_views().
 */
function gazprom_world_map_views_default_views() {
  $export = array();

  $view = new view;
  $view->name = 'world_map';
  $view->description = '';
  $view->tag = 'default';
  $view->base_table = 'taxonomy_term_data';
  $view->human_name = 'World Map';
  $view->core = 7;
  $view->api_version = '3.0';
  $view->disabled = FALSE; /* Edit this to true to make a default view disabled initially */

  /* Display: Master */
  $handler = $view->new_display('default', 'Master', 'default');
  $handler->display->display_options['access']['type'] = 'perm';
  $handler->display->display_options['cache']['type'] = 'none';
  $handler->display->display_options['query']['type'] = 'views_query';
  $handler->display->display_options['query']['options']['query_comment'] = FALSE;
  $handler->display->display_options['exposed_form']['type'] = 'basic';
  $handler->display->display_options['pager']['type'] = 'full';
  $handler->display->display_options['pager']['options']['items_per_page'] = '100';
  $handler->display->display_options['pager']['options']['offset'] = '0';
  $handler->display->display_options['pager']['options']['id'] = '0';
  $handler->display->display_options['pager']['options']['expose']['items_per_page_options_all'] = 0;
  $handler->display->display_options['style_plugin'] = 'openlayers_map';
  $handler->display->display_options['style_options']['map'] = 'world_map_1';
  /* Field: Taxonomy term: Flag */
  $handler->display->display_options['fields']['field_flag_image']['id'] = 'field_flag_image';
  $handler->display->display_options['fields']['field_flag_image']['table'] = 'field_data_field_flag_image';
  $handler->display->display_options['fields']['field_flag_image']['field'] = 'field_flag_image';
  $handler->display->display_options['fields']['field_flag_image']['label'] = '';
  $handler->display->display_options['fields']['field_flag_image']['exclude'] = TRUE;
  $handler->display->display_options['fields']['field_flag_image']['alter']['alter_text'] = 0;
  $handler->display->display_options['fields']['field_flag_image']['alter']['make_link'] = 0;
  $handler->display->display_options['fields']['field_flag_image']['alter']['absolute'] = 0;
  $handler->display->display_options['fields']['field_flag_image']['alter']['external'] = 0;
  $handler->display->display_options['fields']['field_flag_image']['alter']['replace_spaces'] = 0;
  $handler->display->display_options['fields']['field_flag_image']['alter']['trim_whitespace'] = 0;
  $handler->display->display_options['fields']['field_flag_image']['alter']['nl2br'] = 0;
  $handler->display->display_options['fields']['field_flag_image']['alter']['word_boundary'] = 1;
  $handler->display->display_options['fields']['field_flag_image']['alter']['ellipsis'] = 1;
  $handler->display->display_options['fields']['field_flag_image']['alter']['strip_tags'] = 0;
  $handler->display->display_options['fields']['field_flag_image']['alter']['trim'] = 0;
  $handler->display->display_options['fields']['field_flag_image']['alter']['html'] = 0;
  $handler->display->display_options['fields']['field_flag_image']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['field_flag_image']['element_default_classes'] = 1;
  $handler->display->display_options['fields']['field_flag_image']['hide_empty'] = 0;
  $handler->display->display_options['fields']['field_flag_image']['empty_zero'] = 0;
  $handler->display->display_options['fields']['field_flag_image']['hide_alter_empty'] = 1;
  $handler->display->display_options['fields']['field_flag_image']['click_sort_column'] = 'fid';
  $handler->display->display_options['fields']['field_flag_image']['settings'] = array(
    'image_style' => 'map-popup-85',
    'image_link' => 'content',
  );
  $handler->display->display_options['fields']['field_flag_image']['field_api_classes'] = 0;
  /* Field: Taxonomy term: Name */
  $handler->display->display_options['fields']['name']['id'] = 'name';
  $handler->display->display_options['fields']['name']['table'] = 'taxonomy_term_data';
  $handler->display->display_options['fields']['name']['field'] = 'name';
  $handler->display->display_options['fields']['name']['label'] = '';
  $handler->display->display_options['fields']['name']['alter']['alter_text'] = 0;
  $handler->display->display_options['fields']['name']['alter']['make_link'] = 0;
  $handler->display->display_options['fields']['name']['alter']['absolute'] = 0;
  $handler->display->display_options['fields']['name']['alter']['external'] = 0;
  $handler->display->display_options['fields']['name']['alter']['replace_spaces'] = 0;
  $handler->display->display_options['fields']['name']['alter']['trim_whitespace'] = 0;
  $handler->display->display_options['fields']['name']['alter']['nl2br'] = 0;
  $handler->display->display_options['fields']['name']['alter']['word_boundary'] = 0;
  $handler->display->display_options['fields']['name']['alter']['ellipsis'] = 0;
  $handler->display->display_options['fields']['name']['alter']['strip_tags'] = 0;
  $handler->display->display_options['fields']['name']['alter']['trim'] = 0;
  $handler->display->display_options['fields']['name']['alter']['html'] = 0;
  $handler->display->display_options['fields']['name']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['name']['element_default_classes'] = 1;
  $handler->display->display_options['fields']['name']['hide_empty'] = 0;
  $handler->display->display_options['fields']['name']['empty_zero'] = 0;
  $handler->display->display_options['fields']['name']['hide_alter_empty'] = 1;
  $handler->display->display_options['fields']['name']['link_to_taxonomy'] = 1;
  $handler->display->display_options['fields']['name']['convert_spaces'] = 0;
  /* Field: Field: Geo Location */
  $handler->display->display_options['fields']['field_geo_location']['id'] = 'field_geo_location';
  $handler->display->display_options['fields']['field_geo_location']['table'] = 'field_data_field_geo_location';
  $handler->display->display_options['fields']['field_geo_location']['field'] = 'field_geo_location';
  $handler->display->display_options['fields']['field_geo_location']['label'] = '';
  $handler->display->display_options['fields']['field_geo_location']['exclude'] = TRUE;
  $handler->display->display_options['fields']['field_geo_location']['alter']['alter_text'] = 0;
  $handler->display->display_options['fields']['field_geo_location']['alter']['make_link'] = 0;
  $handler->display->display_options['fields']['field_geo_location']['alter']['absolute'] = 0;
  $handler->display->display_options['fields']['field_geo_location']['alter']['external'] = 0;
  $handler->display->display_options['fields']['field_geo_location']['alter']['replace_spaces'] = 0;
  $handler->display->display_options['fields']['field_geo_location']['alter']['trim_whitespace'] = 0;
  $handler->display->display_options['fields']['field_geo_location']['alter']['nl2br'] = 0;
  $handler->display->display_options['fields']['field_geo_location']['alter']['word_boundary'] = 1;
  $handler->display->display_options['fields']['field_geo_location']['alter']['ellipsis'] = 1;
  $handler->display->display_options['fields']['field_geo_location']['alter']['strip_tags'] = 0;
  $handler->display->display_options['fields']['field_geo_location']['alter']['trim'] = 0;
  $handler->display->display_options['fields']['field_geo_location']['alter']['html'] = 0;
  $handler->display->display_options['fields']['field_geo_location']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['field_geo_location']['element_default_classes'] = 1;
  $handler->display->display_options['fields']['field_geo_location']['hide_empty'] = 0;
  $handler->display->display_options['fields']['field_geo_location']['empty_zero'] = 0;
  $handler->display->display_options['fields']['field_geo_location']['hide_alter_empty'] = 1;
  $handler->display->display_options['fields']['field_geo_location']['click_sort_column'] = 'wkt';
  $handler->display->display_options['fields']['field_geo_location']['settings'] = array(
    'data' => 'full',
  );
  $handler->display->display_options['fields']['field_geo_location']['field_api_classes'] = 0;
  /* Filter criterion: Taxonomy vocabulary: Machine name */
  $handler->display->display_options['filters']['machine_name']['id'] = 'machine_name';
  $handler->display->display_options['filters']['machine_name']['table'] = 'taxonomy_vocabulary';
  $handler->display->display_options['filters']['machine_name']['field'] = 'machine_name';
  $handler->display->display_options['filters']['machine_name']['value'] = array(
    'location' => 'location',
  );
  /* Filter criterion: Field: Geo Location (field_geo_location:wkt) */
  $handler->display->display_options['filters']['field_geo_location_wkt']['id'] = 'field_geo_location_wkt';
  $handler->display->display_options['filters']['field_geo_location_wkt']['table'] = 'field_data_field_geo_location';
  $handler->display->display_options['filters']['field_geo_location_wkt']['field'] = 'field_geo_location_wkt';
  $handler->display->display_options['filters']['field_geo_location_wkt']['operator'] = 'not empty';

  /* Display: OpenLayers Data Overlay */
  $handler = $view->new_display('openlayers', 'OpenLayers Data Overlay', 'openlayers_1');
  $handler->display->display_options['pager']['type'] = 'some';
  $handler->display->display_options['pager']['options']['items_per_page'] = '100';
  $handler->display->display_options['pager']['options']['offset'] = '0';
  $handler->display->display_options['defaults']['style_plugin'] = FALSE;
  $handler->display->display_options['style_plugin'] = 'openlayers_data';
  $handler->display->display_options['style_options']['data_source'] = array(
    'value' => 'wkt',
    'other_lat' => 'name',
    'other_lon' => 'name',
    'wkt' => 'field_geo_location',
    'other_top' => 'name',
    'other_right' => 'name',
    'other_bottom' => 'name',
    'other_left' => 'name',
    'name_field' => '',
    'description_field' => '#row',
    'view_mode' => 'full',
  );
  $handler->display->display_options['defaults']['style_options'] = FALSE;
  $handler->display->display_options['defaults']['row_plugin'] = FALSE;
  $handler->display->display_options['row_plugin'] = 'fields';
  $handler->display->display_options['defaults']['row_options'] = FALSE;

  /* Display: Page */
  $handler = $view->new_display('page', 'Page', 'page_1');
  $handler->display->display_options['path'] = 'gazprom/world-map/test';

  /* Display: Block */
  $handler = $view->new_display('block', 'Block', 'block_1');

  /* Display: Testing */
  $handler = $view->new_display('block', 'Testing', 'block_2');
  $handler->display->display_options['defaults']['style_plugin'] = FALSE;
  $handler->display->display_options['style_plugin'] = 'table';
  $handler->display->display_options['style_options']['columns'] = array(
    'name' => 'name',
    'field_location_blurb' => 'field_location_blurb',
  );
  $handler->display->display_options['style_options']['default'] = '-1';
  $handler->display->display_options['style_options']['info'] = array(
    'name' => array(
      'sortable' => 0,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'field_location_blurb' => array(
      'sortable' => 0,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
  );
  $handler->display->display_options['style_options']['override'] = 1;
  $handler->display->display_options['style_options']['sticky'] = 0;
  $handler->display->display_options['style_options']['empty_table'] = 0;
  $handler->display->display_options['defaults']['style_options'] = FALSE;
  $handler->display->display_options['defaults']['row_plugin'] = FALSE;
  $handler->display->display_options['defaults']['row_options'] = FALSE;
  $translatables['world_map'] = array(
    t('Master'),
    t('more'),
    t('Apply'),
    t('Reset'),
    t('Sort by'),
    t('Asc'),
    t('Desc'),
    t('Items per page'),
    t('- All -'),
    t('Offset'),
    t('OpenLayers Data Overlay'),
    t('Page'),
    t('Block'),
    t('Testing'),
  );
  $export['world_map'] = $view;

  $view = new view;
  $view->name = 'world_map_2';
  $view->description = '';
  $view->tag = 'default';
  $view->base_table = 'node';
  $view->human_name = 'World Map 2';
  $view->core = 7;
  $view->api_version = '3.0';
  $view->disabled = FALSE; /* Edit this to true to make a default view disabled initially */

  /* Display: Master */
  $handler = $view->new_display('default', 'Master', 'default');
  $handler->display->display_options['access']['type'] = 'perm';
  $handler->display->display_options['cache']['type'] = 'none';
  $handler->display->display_options['query']['type'] = 'views_query';
  $handler->display->display_options['query']['options']['query_comment'] = FALSE;
  $handler->display->display_options['exposed_form']['type'] = 'basic';
  $handler->display->display_options['pager']['type'] = 'full';
  $handler->display->display_options['pager']['options']['items_per_page'] = '100';
  $handler->display->display_options['pager']['options']['offset'] = '0';
  $handler->display->display_options['pager']['options']['id'] = '0';
  $handler->display->display_options['pager']['options']['expose']['items_per_page_options_all'] = 0;
  $handler->display->display_options['style_plugin'] = 'openlayers_map';
  $handler->display->display_options['style_options']['map'] = 'world_map_2';
  /* Field: Content: Title */
  $handler->display->display_options['fields']['title']['id'] = 'title';
  $handler->display->display_options['fields']['title']['table'] = 'node';
  $handler->display->display_options['fields']['title']['field'] = 'title';
  $handler->display->display_options['fields']['title']['label'] = '';
  $handler->display->display_options['fields']['title']['alter']['alter_text'] = 0;
  $handler->display->display_options['fields']['title']['alter']['make_link'] = 0;
  $handler->display->display_options['fields']['title']['alter']['absolute'] = 0;
  $handler->display->display_options['fields']['title']['alter']['word_boundary'] = 0;
  $handler->display->display_options['fields']['title']['alter']['ellipsis'] = 0;
  $handler->display->display_options['fields']['title']['alter']['strip_tags'] = 0;
  $handler->display->display_options['fields']['title']['alter']['trim'] = 0;
  $handler->display->display_options['fields']['title']['alter']['html'] = 0;
  $handler->display->display_options['fields']['title']['hide_empty'] = 0;
  $handler->display->display_options['fields']['title']['empty_zero'] = 0;
  $handler->display->display_options['fields']['title']['link_to_node'] = 1;
  /* Sort criterion: Content: Title */
  $handler->display->display_options['sorts']['title']['id'] = 'title';
  $handler->display->display_options['sorts']['title']['table'] = 'node';
  $handler->display->display_options['sorts']['title']['field'] = 'title';
  /* Sort criterion: Content: Post date */
  $handler->display->display_options['sorts']['created']['id'] = 'created';
  $handler->display->display_options['sorts']['created']['table'] = 'node';
  $handler->display->display_options['sorts']['created']['field'] = 'created';
  $handler->display->display_options['sorts']['created']['order'] = 'DESC';
  /* Filter criterion: Content: Type */
  $handler->display->display_options['filters']['type']['id'] = 'type';
  $handler->display->display_options['filters']['type']['table'] = 'node';
  $handler->display->display_options['filters']['type']['field'] = 'type';
  $handler->display->display_options['filters']['type']['value'] = array(
    'country_page' => 'country_page',
  );
  $handler->display->display_options['filters']['type']['group'] = 1;
  /* Filter criterion: Content: Published */
  $handler->display->display_options['filters']['status']['id'] = 'status';
  $handler->display->display_options['filters']['status']['table'] = 'node';
  $handler->display->display_options['filters']['status']['field'] = 'status';
  $handler->display->display_options['filters']['status']['value'] = 1;
  $handler->display->display_options['filters']['status']['group'] = 1;
  $handler->display->display_options['filters']['status']['expose']['operator'] = FALSE;
  /* Filter criterion: Field: Geo Location (field_geo_location:wkt) */
  $handler->display->display_options['filters']['field_geo_location_wkt']['id'] = 'field_geo_location_wkt';
  $handler->display->display_options['filters']['field_geo_location_wkt']['table'] = 'field_data_field_geo_location';
  $handler->display->display_options['filters']['field_geo_location_wkt']['field'] = 'field_geo_location_wkt';
  $handler->display->display_options['filters']['field_geo_location_wkt']['operator'] = 'not empty';
  $handler->display->display_options['filters']['field_geo_location_wkt']['group'] = 1;
  /* Filter criterion: Content translation: Language */
  $handler->display->display_options['filters']['language']['id'] = 'language';
  $handler->display->display_options['filters']['language']['table'] = 'node';
  $handler->display->display_options['filters']['language']['field'] = 'language';
  $handler->display->display_options['filters']['language']['value'] = array(
    '***CURRENT_LANGUAGE***' => '***CURRENT_LANGUAGE***',
    'und' => 'und',
  );
  $handler->display->display_options['filters']['language']['group'] = 1;

  /* Display: OpenLayers Data Overlay */
  $handler = $view->new_display('openlayers', 'OpenLayers Data Overlay', 'openlayers_1');
  $handler->display->display_options['pager']['type'] = 'some';
  $handler->display->display_options['pager']['options']['items_per_page'] = '100';
  $handler->display->display_options['pager']['options']['offset'] = '0';
  $handler->display->display_options['defaults']['style_plugin'] = FALSE;
  $handler->display->display_options['style_plugin'] = 'openlayers_data';
  $handler->display->display_options['style_options']['data_source'] = array(
    'value' => 'wkt',
    'other_lat' => 'field_flag_image',
    'other_lon' => 'field_flag_image',
    'wkt' => 'field_geo_location',
    'other_top' => 'field_flag_image',
    'other_right' => 'field_flag_image',
    'other_bottom' => 'field_flag_image',
    'other_left' => 'field_flag_image',
    'name_field' => '',
    'description_field' => '#row',
    'view_mode' => 'full',
  );
  $handler->display->display_options['defaults']['style_options'] = FALSE;
  $handler->display->display_options['defaults']['row_plugin'] = FALSE;
  $handler->display->display_options['row_plugin'] = 'fields';
  $handler->display->display_options['defaults']['row_options'] = FALSE;
  $handler->display->display_options['defaults']['relationships'] = FALSE;
  /* Relationship: Content: Taxonomy terms on node */
  $handler->display->display_options['relationships']['term_node_tid']['id'] = 'term_node_tid';
  $handler->display->display_options['relationships']['term_node_tid']['table'] = 'node';
  $handler->display->display_options['relationships']['term_node_tid']['field'] = 'term_node_tid';
  $handler->display->display_options['relationships']['term_node_tid']['label'] = 'Country';
  $handler->display->display_options['relationships']['term_node_tid']['required'] = 0;
  $handler->display->display_options['relationships']['term_node_tid']['vocabularies'] = array(
    'location' => 'location',
    'tags' => 0,
    'staff_type' => 0,
  );
  $handler->display->display_options['defaults']['fields'] = FALSE;
  /* Field: Content: Primary Image */
  $handler->display->display_options['fields']['field_image']['id'] = 'field_image';
  $handler->display->display_options['fields']['field_image']['table'] = 'field_data_field_image';
  $handler->display->display_options['fields']['field_image']['field'] = 'field_image';
  $handler->display->display_options['fields']['field_image']['label'] = '';
  $handler->display->display_options['fields']['field_image']['alter']['alter_text'] = 0;
  $handler->display->display_options['fields']['field_image']['alter']['make_link'] = 0;
  $handler->display->display_options['fields']['field_image']['alter']['absolute'] = 0;
  $handler->display->display_options['fields']['field_image']['alter']['external'] = 0;
  $handler->display->display_options['fields']['field_image']['alter']['replace_spaces'] = 0;
  $handler->display->display_options['fields']['field_image']['alter']['trim_whitespace'] = 0;
  $handler->display->display_options['fields']['field_image']['alter']['nl2br'] = 0;
  $handler->display->display_options['fields']['field_image']['alter']['word_boundary'] = 1;
  $handler->display->display_options['fields']['field_image']['alter']['ellipsis'] = 1;
  $handler->display->display_options['fields']['field_image']['alter']['more_link'] = 0;
  $handler->display->display_options['fields']['field_image']['alter']['strip_tags'] = 0;
  $handler->display->display_options['fields']['field_image']['alter']['trim'] = 0;
  $handler->display->display_options['fields']['field_image']['alter']['html'] = 0;
  $handler->display->display_options['fields']['field_image']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['field_image']['element_default_classes'] = 1;
  $handler->display->display_options['fields']['field_image']['hide_empty'] = 1;
  $handler->display->display_options['fields']['field_image']['empty_zero'] = 0;
  $handler->display->display_options['fields']['field_image']['hide_alter_empty'] = 0;
  $handler->display->display_options['fields']['field_image']['click_sort_column'] = 'fid';
  $handler->display->display_options['fields']['field_image']['settings'] = array(
    'image_style' => 'map-popup-85x85',
    'image_link' => 'content',
  );
  $handler->display->display_options['fields']['field_image']['field_api_classes'] = 0;
  /* Field: Content: Title */
  $handler->display->display_options['fields']['title']['id'] = 'title';
  $handler->display->display_options['fields']['title']['table'] = 'node';
  $handler->display->display_options['fields']['title']['field'] = 'title';
  $handler->display->display_options['fields']['title']['label'] = '';
  $handler->display->display_options['fields']['title']['alter']['alter_text'] = 0;
  $handler->display->display_options['fields']['title']['alter']['make_link'] = 0;
  $handler->display->display_options['fields']['title']['alter']['absolute'] = 0;
  $handler->display->display_options['fields']['title']['alter']['word_boundary'] = 0;
  $handler->display->display_options['fields']['title']['alter']['ellipsis'] = 0;
  $handler->display->display_options['fields']['title']['alter']['strip_tags'] = 0;
  $handler->display->display_options['fields']['title']['alter']['trim'] = 0;
  $handler->display->display_options['fields']['title']['alter']['html'] = 0;
  $handler->display->display_options['fields']['title']['hide_empty'] = 0;
  $handler->display->display_options['fields']['title']['empty_zero'] = 0;
  $handler->display->display_options['fields']['title']['link_to_node'] = 1;
  /* Field: Content: Blurb */
  $handler->display->display_options['fields']['field_country_blurb']['id'] = 'field_country_blurb';
  $handler->display->display_options['fields']['field_country_blurb']['table'] = 'field_data_field_country_blurb';
  $handler->display->display_options['fields']['field_country_blurb']['field'] = 'field_country_blurb';
  $handler->display->display_options['fields']['field_country_blurb']['label'] = '';
  $handler->display->display_options['fields']['field_country_blurb']['alter']['alter_text'] = 0;
  $handler->display->display_options['fields']['field_country_blurb']['alter']['make_link'] = 0;
  $handler->display->display_options['fields']['field_country_blurb']['alter']['absolute'] = 0;
  $handler->display->display_options['fields']['field_country_blurb']['alter']['external'] = 0;
  $handler->display->display_options['fields']['field_country_blurb']['alter']['replace_spaces'] = 0;
  $handler->display->display_options['fields']['field_country_blurb']['alter']['trim_whitespace'] = 1;
  $handler->display->display_options['fields']['field_country_blurb']['alter']['nl2br'] = 1;
  $handler->display->display_options['fields']['field_country_blurb']['alter']['max_length'] = '600';
  $handler->display->display_options['fields']['field_country_blurb']['alter']['word_boundary'] = 1;
  $handler->display->display_options['fields']['field_country_blurb']['alter']['ellipsis'] = 1;
  $handler->display->display_options['fields']['field_country_blurb']['alter']['more_link'] = 0;
  $handler->display->display_options['fields']['field_country_blurb']['alter']['strip_tags'] = 0;
  $handler->display->display_options['fields']['field_country_blurb']['alter']['trim'] = 1;
  $handler->display->display_options['fields']['field_country_blurb']['alter']['html'] = 0;
  $handler->display->display_options['fields']['field_country_blurb']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['field_country_blurb']['element_default_classes'] = 1;
  $handler->display->display_options['fields']['field_country_blurb']['empty'] = 'Prospective project.';
  $handler->display->display_options['fields']['field_country_blurb']['hide_empty'] = 0;
  $handler->display->display_options['fields']['field_country_blurb']['empty_zero'] = 0;
  $handler->display->display_options['fields']['field_country_blurb']['hide_alter_empty'] = 1;
  $handler->display->display_options['fields']['field_country_blurb']['field_api_classes'] = 0;
  /* Field: Field: Geo Location */
  $handler->display->display_options['fields']['field_geo_location']['id'] = 'field_geo_location';
  $handler->display->display_options['fields']['field_geo_location']['table'] = 'field_data_field_geo_location';
  $handler->display->display_options['fields']['field_geo_location']['field'] = 'field_geo_location';
  $handler->display->display_options['fields']['field_geo_location']['label'] = '';
  $handler->display->display_options['fields']['field_geo_location']['exclude'] = TRUE;
  $handler->display->display_options['fields']['field_geo_location']['alter']['alter_text'] = 0;
  $handler->display->display_options['fields']['field_geo_location']['alter']['make_link'] = 0;
  $handler->display->display_options['fields']['field_geo_location']['alter']['absolute'] = 0;
  $handler->display->display_options['fields']['field_geo_location']['alter']['external'] = 0;
  $handler->display->display_options['fields']['field_geo_location']['alter']['replace_spaces'] = 0;
  $handler->display->display_options['fields']['field_geo_location']['alter']['trim_whitespace'] = 0;
  $handler->display->display_options['fields']['field_geo_location']['alter']['nl2br'] = 0;
  $handler->display->display_options['fields']['field_geo_location']['alter']['word_boundary'] = 1;
  $handler->display->display_options['fields']['field_geo_location']['alter']['ellipsis'] = 1;
  $handler->display->display_options['fields']['field_geo_location']['alter']['strip_tags'] = 0;
  $handler->display->display_options['fields']['field_geo_location']['alter']['trim'] = 0;
  $handler->display->display_options['fields']['field_geo_location']['alter']['html'] = 0;
  $handler->display->display_options['fields']['field_geo_location']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['field_geo_location']['element_default_classes'] = 1;
  $handler->display->display_options['fields']['field_geo_location']['hide_empty'] = 0;
  $handler->display->display_options['fields']['field_geo_location']['empty_zero'] = 0;
  $handler->display->display_options['fields']['field_geo_location']['hide_alter_empty'] = 1;
  $handler->display->display_options['fields']['field_geo_location']['click_sort_column'] = 'wkt';
  $handler->display->display_options['fields']['field_geo_location']['settings'] = array(
    'data' => 'full',
  );
  $handler->display->display_options['fields']['field_geo_location']['field_api_classes'] = 0;

  /* Display: Block */
  $handler = $view->new_display('block', 'Block', 'block_1');
  $translatables['world_map_2'] = array(
    t('Master'),
    t('more'),
    t('Apply'),
    t('Reset'),
    t('Sort by'),
    t('Asc'),
    t('Desc'),
    t('Items per page'),
    t('- All -'),
    t('Offset'),
    t('OpenLayers Data Overlay'),
    t('Country'),
    t('Prospective project.'),
    t('Block'),
  );
  $export['world_map_2'] = $view;

  return $export;
}
