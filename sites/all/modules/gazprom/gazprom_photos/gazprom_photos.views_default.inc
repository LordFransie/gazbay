<?php
/**
 * @file
 * gazprom_photos.views_default.inc
 */

/**
 * Implements hook_views_default_views().
 */
function gazprom_photos_views_default_views() {
  $export = array();

  $view = new view;
  $view->name = 'attached_photo_set';
  $view->description = 'Used for embedding photos into a node or taxonomy term page.';
  $view->tag = 'default';
  $view->base_table = 'node';
  $view->human_name = 'Attached Photo Set';
  $view->core = 7;
  $view->api_version = '3.0';
  $view->disabled = FALSE; /* Edit this to true to make a default view disabled initially */

  /* Display: Master */
  $handler = $view->new_display('default', 'Master', 'default');
  $handler->display->display_options['title'] = 'Attached Photo Set';
  $handler->display->display_options['css_class'] = 'contains-photos';
  $handler->display->display_options['access']['type'] = 'perm';
  $handler->display->display_options['cache']['type'] = 'none';
  $handler->display->display_options['query']['type'] = 'views_query';
  $handler->display->display_options['query']['options']['query_comment'] = FALSE;
  $handler->display->display_options['exposed_form']['type'] = 'basic';
  $handler->display->display_options['pager']['type'] = 'some';
  $handler->display->display_options['pager']['options']['items_per_page'] = '4';
  $handler->display->display_options['pager']['options']['offset'] = '0';
  $handler->display->display_options['style_plugin'] = 'grid';
  $handler->display->display_options['style_options']['columns'] = '2';
  $handler->display->display_options['style_options']['fill_single_line'] = 1;
  $handler->display->display_options['row_plugin'] = 'fields';
  /* Relationship: Content: Attached Media Collection (field_collection_attached) - reverse */
  $handler->display->display_options['relationships']['reverse_field_collection_attached_node']['id'] = 'reverse_field_collection_attached_node';
  $handler->display->display_options['relationships']['reverse_field_collection_attached_node']['table'] = 'node';
  $handler->display->display_options['relationships']['reverse_field_collection_attached_node']['field'] = 'reverse_field_collection_attached_node';
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
  $handler->display->display_options['fields']['field_image']['alter']['strip_tags'] = 0;
  $handler->display->display_options['fields']['field_image']['alter']['trim'] = 0;
  $handler->display->display_options['fields']['field_image']['alter']['html'] = 0;
  $handler->display->display_options['fields']['field_image']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['field_image']['element_default_classes'] = 1;
  $handler->display->display_options['fields']['field_image']['hide_empty'] = 0;
  $handler->display->display_options['fields']['field_image']['empty_zero'] = 0;
  $handler->display->display_options['fields']['field_image']['hide_alter_empty'] = 1;
  $handler->display->display_options['fields']['field_image']['click_sort_column'] = 'fid';
  $handler->display->display_options['fields']['field_image']['settings'] = array(
    'image_style' => 'attached_photo_grid',
    'image_link' => 'content',
  );
  $handler->display->display_options['fields']['field_image']['field_api_classes'] = 0;
  /* Sort criterion: Global: Random seed */
  $handler->display->display_options['sorts']['random_seed']['id'] = 'random_seed';
  $handler->display->display_options['sorts']['random_seed']['table'] = 'views';
  $handler->display->display_options['sorts']['random_seed']['field'] = 'random_seed';
  /* Contextual filter: Content: Part of Collection (field_ref_collection) */
  $handler->display->display_options['arguments']['field_ref_collection_nid']['id'] = 'field_ref_collection_nid';
  $handler->display->display_options['arguments']['field_ref_collection_nid']['table'] = 'field_data_field_ref_collection';
  $handler->display->display_options['arguments']['field_ref_collection_nid']['field'] = 'field_ref_collection_nid';
  $handler->display->display_options['arguments']['field_ref_collection_nid']['default_action'] = 'not found';
  $handler->display->display_options['arguments']['field_ref_collection_nid']['default_argument_type'] = 'fixed';
  $handler->display->display_options['arguments']['field_ref_collection_nid']['default_argument_skip_url'] = 0;
  $handler->display->display_options['arguments']['field_ref_collection_nid']['summary']['number_of_records'] = '0';
  $handler->display->display_options['arguments']['field_ref_collection_nid']['summary']['format'] = 'default_summary';
  $handler->display->display_options['arguments']['field_ref_collection_nid']['summary_options']['items_per_page'] = '25';
  $handler->display->display_options['arguments']['field_ref_collection_nid']['break_phrase'] = 0;
  $handler->display->display_options['arguments']['field_ref_collection_nid']['not'] = 0;
  /* Filter criterion: Content: Published */
  $handler->display->display_options['filters']['status']['id'] = 'status';
  $handler->display->display_options['filters']['status']['table'] = 'node';
  $handler->display->display_options['filters']['status']['field'] = 'status';
  $handler->display->display_options['filters']['status']['value'] = 1;
  $handler->display->display_options['filters']['status']['group'] = 0;
  $handler->display->display_options['filters']['status']['expose']['operator'] = FALSE;
  /* Filter criterion: Content: Type */
  $handler->display->display_options['filters']['type']['id'] = 'type';
  $handler->display->display_options['filters']['type']['table'] = 'node';
  $handler->display->display_options['filters']['type']['field'] = 'type';
  $handler->display->display_options['filters']['type']['value'] = array(
    'media_photo' => 'media_photo',
  );

  /* Display: Block: 2x2 Grid - 300px */
  $handler = $view->new_display('block', 'Block: 2x2 Grid - 300px', 'block_attached_photos_2x2');

  /* Display: Admin: Choose Reference */
  $handler = $view->new_display('references', 'Admin: Choose Reference', 'references_1');
  $handler->display->display_options['defaults']['title'] = FALSE;
  $handler->display->display_options['display_description'] = 'The view used by the References module to provide a list of photo sets to attach';
  $handler->display->display_options['pager']['type'] = 'some';
  $handler->display->display_options['defaults']['style_plugin'] = FALSE;
  $handler->display->display_options['style_plugin'] = 'references_style';
  $handler->display->display_options['defaults']['style_options'] = FALSE;
  $handler->display->display_options['defaults']['row_plugin'] = FALSE;
  $handler->display->display_options['row_plugin'] = 'references_fields';
  $handler->display->display_options['defaults']['row_options'] = FALSE;
  $handler->display->display_options['defaults']['relationships'] = FALSE;
  $handler->display->display_options['defaults']['fields'] = FALSE;
  /* Field: Content: Title */
  $handler->display->display_options['fields']['title']['id'] = 'title';
  $handler->display->display_options['fields']['title']['table'] = 'node';
  $handler->display->display_options['fields']['title']['field'] = 'title';
  $handler->display->display_options['fields']['title']['label'] = '';
  $handler->display->display_options['fields']['title']['alter']['alter_text'] = 0;
  $handler->display->display_options['fields']['title']['alter']['make_link'] = 0;
  $handler->display->display_options['fields']['title']['alter']['absolute'] = 0;
  $handler->display->display_options['fields']['title']['alter']['external'] = 0;
  $handler->display->display_options['fields']['title']['alter']['replace_spaces'] = 0;
  $handler->display->display_options['fields']['title']['alter']['trim_whitespace'] = 0;
  $handler->display->display_options['fields']['title']['alter']['nl2br'] = 0;
  $handler->display->display_options['fields']['title']['alter']['word_boundary'] = 1;
  $handler->display->display_options['fields']['title']['alter']['ellipsis'] = 1;
  $handler->display->display_options['fields']['title']['alter']['strip_tags'] = 0;
  $handler->display->display_options['fields']['title']['alter']['trim'] = 0;
  $handler->display->display_options['fields']['title']['alter']['html'] = 0;
  $handler->display->display_options['fields']['title']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['title']['element_default_classes'] = 1;
  $handler->display->display_options['fields']['title']['hide_empty'] = 0;
  $handler->display->display_options['fields']['title']['empty_zero'] = 0;
  $handler->display->display_options['fields']['title']['hide_alter_empty'] = 1;
  $handler->display->display_options['fields']['title']['link_to_node'] = 0;
  /* Field: Content: Date Released */
  $handler->display->display_options['fields']['field_date_event']['id'] = 'field_date_event';
  $handler->display->display_options['fields']['field_date_event']['table'] = 'field_data_field_date_event';
  $handler->display->display_options['fields']['field_date_event']['field'] = 'field_date_event';
  $handler->display->display_options['fields']['field_date_event']['label'] = '';
  $handler->display->display_options['fields']['field_date_event']['alter']['alter_text'] = 0;
  $handler->display->display_options['fields']['field_date_event']['alter']['make_link'] = 0;
  $handler->display->display_options['fields']['field_date_event']['alter']['absolute'] = 0;
  $handler->display->display_options['fields']['field_date_event']['alter']['external'] = 0;
  $handler->display->display_options['fields']['field_date_event']['alter']['replace_spaces'] = 0;
  $handler->display->display_options['fields']['field_date_event']['alter']['trim_whitespace'] = 0;
  $handler->display->display_options['fields']['field_date_event']['alter']['nl2br'] = 0;
  $handler->display->display_options['fields']['field_date_event']['alter']['word_boundary'] = 1;
  $handler->display->display_options['fields']['field_date_event']['alter']['ellipsis'] = 1;
  $handler->display->display_options['fields']['field_date_event']['alter']['strip_tags'] = 0;
  $handler->display->display_options['fields']['field_date_event']['alter']['trim'] = 0;
  $handler->display->display_options['fields']['field_date_event']['alter']['html'] = 0;
  $handler->display->display_options['fields']['field_date_event']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['field_date_event']['element_default_classes'] = 1;
  $handler->display->display_options['fields']['field_date_event']['hide_empty'] = 0;
  $handler->display->display_options['fields']['field_date_event']['empty_zero'] = 0;
  $handler->display->display_options['fields']['field_date_event']['hide_alter_empty'] = 1;
  $handler->display->display_options['fields']['field_date_event']['settings'] = array(
    'format_type' => 'short_simple',
    'fromto' => 'both',
    'multiple_number' => '',
    'multiple_from' => '',
    'multiple_to' => '',
  );
  $handler->display->display_options['fields']['field_date_event']['field_api_classes'] = 0;
  $handler->display->display_options['defaults']['sorts'] = FALSE;
  /* Sort criterion: Content: Post date */
  $handler->display->display_options['sorts']['created']['id'] = 'created';
  $handler->display->display_options['sorts']['created']['table'] = 'node';
  $handler->display->display_options['sorts']['created']['field'] = 'created';
  $handler->display->display_options['sorts']['created']['order'] = 'DESC';
  /* Sort criterion: Broken/missing handler */
  $handler->display->display_options['sorts']['publish_on']['id'] = 'publish_on';
  $handler->display->display_options['sorts']['publish_on']['table'] = 'scheduler';
  $handler->display->display_options['sorts']['publish_on']['field'] = 'publish_on';
  $handler->display->display_options['defaults']['arguments'] = FALSE;
  /* Contextual filter: Content: Has taxonomy term ID */
  $handler->display->display_options['arguments']['tid']['id'] = 'tid';
  $handler->display->display_options['arguments']['tid']['table'] = 'taxonomy_index';
  $handler->display->display_options['arguments']['tid']['field'] = 'tid';
  $handler->display->display_options['arguments']['tid']['default_action'] = 'default';
  $handler->display->display_options['arguments']['tid']['default_argument_type'] = 'taxonomy_tid';
  $handler->display->display_options['arguments']['tid']['default_argument_options']['term_page'] = 1;
  $handler->display->display_options['arguments']['tid']['default_argument_options']['node'] = 1;
  $handler->display->display_options['arguments']['tid']['default_argument_options']['anyall'] = '+';
  $handler->display->display_options['arguments']['tid']['default_argument_options']['limit'] = 1;
  $handler->display->display_options['arguments']['tid']['default_argument_options']['vocabularies'] = array(
    'location' => 'location',
  );
  $handler->display->display_options['arguments']['tid']['default_argument_skip_url'] = 0;
  $handler->display->display_options['arguments']['tid']['summary']['number_of_records'] = '0';
  $handler->display->display_options['arguments']['tid']['summary']['format'] = 'default_summary';
  $handler->display->display_options['arguments']['tid']['summary_options']['items_per_page'] = '25';
  $handler->display->display_options['arguments']['tid']['break_phrase'] = 0;
  $handler->display->display_options['arguments']['tid']['add_table'] = 0;
  $handler->display->display_options['arguments']['tid']['require_value'] = 0;
  $handler->display->display_options['arguments']['tid']['reduce_duplicates'] = 0;
  $handler->display->display_options['arguments']['tid']['set_breadcrumb'] = 0;
  $handler->display->display_options['defaults']['filters'] = FALSE;
  /* Filter criterion: Content: Published */
  $handler->display->display_options['filters']['status']['id'] = 'status';
  $handler->display->display_options['filters']['status']['table'] = 'node';
  $handler->display->display_options['filters']['status']['field'] = 'status';
  $handler->display->display_options['filters']['status']['value'] = 1;
  $handler->display->display_options['filters']['status']['group'] = 0;
  $handler->display->display_options['filters']['status']['expose']['operator'] = FALSE;
  /* Filter criterion: Content: Type */
  $handler->display->display_options['filters']['type']['id'] = 'type';
  $handler->display->display_options['filters']['type']['table'] = 'node';
  $handler->display->display_options['filters']['type']['field'] = 'type';
  $handler->display->display_options['filters']['type']['value'] = array(
    'media_collection' => 'media_collection',
  );

  /* Display: Block: 2x2 Grid - 240px */
  $handler = $view->new_display('block', 'Block: 2x2 Grid - 240px', 'block_attached_photos_2x2_240');
  $handler->display->display_options['defaults']['fields'] = FALSE;
  /* Field: Primary Image (115x75) */
  $handler->display->display_options['fields']['field_image']['id'] = 'field_image';
  $handler->display->display_options['fields']['field_image']['table'] = 'field_data_field_image';
  $handler->display->display_options['fields']['field_image']['field'] = 'field_image';
  $handler->display->display_options['fields']['field_image']['ui_name'] = 'Primary Image (115x75)';
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
  $handler->display->display_options['fields']['field_image']['alter']['strip_tags'] = 0;
  $handler->display->display_options['fields']['field_image']['alter']['trim'] = 0;
  $handler->display->display_options['fields']['field_image']['alter']['html'] = 0;
  $handler->display->display_options['fields']['field_image']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['field_image']['element_default_classes'] = 1;
  $handler->display->display_options['fields']['field_image']['hide_empty'] = 0;
  $handler->display->display_options['fields']['field_image']['empty_zero'] = 0;
  $handler->display->display_options['fields']['field_image']['hide_alter_empty'] = 1;
  $handler->display->display_options['fields']['field_image']['click_sort_column'] = 'fid';
  $handler->display->display_options['fields']['field_image']['settings'] = array(
    'image_style' => 'attached_photo_grid_115',
    'image_link' => 'content',
  );
  $handler->display->display_options['fields']['field_image']['field_api_classes'] = 0;
  $translatables['attached_photo_set'] = array(
    t('Master'),
    t('Attached Photo Set'),
    t('more'),
    t('Apply'),
    t('Reset'),
    t('Sort by'),
    t('Asc'),
    t('Desc'),
    t('field_collection_attached'),
    t('All'),
    t('Block: 2x2 Grid - 300px'),
    t('Admin: Choose Reference'),
    t('The view used by the References module to provide a list of photo sets to attach'),
    t('Block: 2x2 Grid - 240px'),
  );
  $export['attached_photo_set'] = $view;

  $view = new view;
  $view->name = 'collection_contents';
  $view->description = 'Used for displaying the contents of a media collection';
  $view->tag = 'default';
  $view->base_table = 'node';
  $view->human_name = 'Collection Contents';
  $view->core = 7;
  $view->api_version = '3.0';
  $view->disabled = FALSE; /* Edit this to true to make a default view disabled initially */

  /* Display: Master */
  $handler = $view->new_display('default', 'Master', 'default');
  $handler->display->display_options['title'] = 'Attached Media';
  $handler->display->display_options['access']['type'] = 'perm';
  $handler->display->display_options['cache']['type'] = 'none';
  $handler->display->display_options['query']['type'] = 'views_query';
  $handler->display->display_options['query']['options']['query_comment'] = FALSE;
  $handler->display->display_options['exposed_form']['type'] = 'basic';
  $handler->display->display_options['pager']['type'] = 'none';
  $handler->display->display_options['style_plugin'] = 'grid';
  $handler->display->display_options['style_options']['fill_single_line'] = 1;
  $handler->display->display_options['row_plugin'] = 'fields';
  /* No results behavior: Global: Text area */
  $handler->display->display_options['empty']['area']['id'] = 'area';
  $handler->display->display_options['empty']['area']['table'] = 'views';
  $handler->display->display_options['empty']['area']['field'] = 'area';
  $handler->display->display_options['empty']['area']['empty'] = FALSE;
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
  $handler->display->display_options['fields']['field_image']['alter']['strip_tags'] = 0;
  $handler->display->display_options['fields']['field_image']['alter']['trim'] = 0;
  $handler->display->display_options['fields']['field_image']['alter']['html'] = 0;
  $handler->display->display_options['fields']['field_image']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['field_image']['element_default_classes'] = 1;
  $handler->display->display_options['fields']['field_image']['hide_empty'] = 0;
  $handler->display->display_options['fields']['field_image']['empty_zero'] = 0;
  $handler->display->display_options['fields']['field_image']['hide_alter_empty'] = 0;
  $handler->display->display_options['fields']['field_image']['click_sort_column'] = 'fid';
  $handler->display->display_options['fields']['field_image']['settings'] = array(
    'image_style' => 'thumbnail',
    'image_link' => 'content',
  );
  $handler->display->display_options['fields']['field_image']['field_api_classes'] = 0;
  /* Field: Content: Title */
  $handler->display->display_options['fields']['title']['id'] = 'title';
  $handler->display->display_options['fields']['title']['table'] = 'node';
  $handler->display->display_options['fields']['title']['field'] = 'title';
  $handler->display->display_options['fields']['title']['label'] = '';
  $handler->display->display_options['fields']['title']['alter']['alter_text'] = 0;
  $handler->display->display_options['fields']['title']['alter']['make_link'] = 1;
  $handler->display->display_options['fields']['title']['alter']['path'] = 'node/[nid]/edit';
  $handler->display->display_options['fields']['title']['alter']['absolute'] = 0;
  $handler->display->display_options['fields']['title']['alter']['external'] = 0;
  $handler->display->display_options['fields']['title']['alter']['replace_spaces'] = 0;
  $handler->display->display_options['fields']['title']['alter']['trim_whitespace'] = 0;
  $handler->display->display_options['fields']['title']['alter']['nl2br'] = 0;
  $handler->display->display_options['fields']['title']['alter']['word_boundary'] = 0;
  $handler->display->display_options['fields']['title']['alter']['ellipsis'] = 0;
  $handler->display->display_options['fields']['title']['alter']['strip_tags'] = 0;
  $handler->display->display_options['fields']['title']['alter']['trim'] = 0;
  $handler->display->display_options['fields']['title']['alter']['html'] = 0;
  $handler->display->display_options['fields']['title']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['title']['element_default_classes'] = 1;
  $handler->display->display_options['fields']['title']['hide_empty'] = 0;
  $handler->display->display_options['fields']['title']['empty_zero'] = 0;
  $handler->display->display_options['fields']['title']['hide_alter_empty'] = 0;
  $handler->display->display_options['fields']['title']['link_to_node'] = 0;
  /* Sort criterion: DraggableViews: Order */
  $handler->display->display_options['sorts']['value0']['id'] = 'value0';
  $handler->display->display_options['sorts']['value0']['table'] = 'draggableviews_structure_node0';
  $handler->display->display_options['sorts']['value0']['field'] = 'value0';
  /* Sort criterion: Content: Post date */
  $handler->display->display_options['sorts']['created']['id'] = 'created';
  $handler->display->display_options['sorts']['created']['table'] = 'node';
  $handler->display->display_options['sorts']['created']['field'] = 'created';
  /* Contextual filter: Content: Part of Collection (field_ref_collection) */
  $handler->display->display_options['arguments']['field_ref_collection_nid']['id'] = 'field_ref_collection_nid';
  $handler->display->display_options['arguments']['field_ref_collection_nid']['table'] = 'field_data_field_ref_collection';
  $handler->display->display_options['arguments']['field_ref_collection_nid']['field'] = 'field_ref_collection_nid';
  $handler->display->display_options['arguments']['field_ref_collection_nid']['default_action'] = 'empty';
  $handler->display->display_options['arguments']['field_ref_collection_nid']['default_argument_type'] = 'fixed';
  $handler->display->display_options['arguments']['field_ref_collection_nid']['default_argument_skip_url'] = 0;
  $handler->display->display_options['arguments']['field_ref_collection_nid']['summary']['number_of_records'] = '0';
  $handler->display->display_options['arguments']['field_ref_collection_nid']['summary']['format'] = 'default_summary';
  $handler->display->display_options['arguments']['field_ref_collection_nid']['summary_options']['items_per_page'] = '25';
  $handler->display->display_options['arguments']['field_ref_collection_nid']['break_phrase'] = 0;
  $handler->display->display_options['arguments']['field_ref_collection_nid']['not'] = 0;
  /* Filter criterion: Content: Type */
  $handler->display->display_options['filters']['type']['id'] = 'type';
  $handler->display->display_options['filters']['type']['table'] = 'node';
  $handler->display->display_options['filters']['type']['field'] = 'type';
  $handler->display->display_options['filters']['type']['value'] = array(
    'media_photo' => 'media_photo',
  );
  /* Filter criterion: Content: Published or admin */
  $handler->display->display_options['filters']['status_extra']['id'] = 'status_extra';
  $handler->display->display_options['filters']['status_extra']['table'] = 'node';
  $handler->display->display_options['filters']['status_extra']['field'] = 'status_extra';

  /* Display: EVA: for collection node */
  $handler = $view->new_display('entity_view', 'EVA: for collection node', 'entity_view_1');
  $handler->display->display_options['defaults']['title'] = FALSE;
  $handler->display->display_options['title'] = 'Attached Photos:';
  $handler->display->display_options['defaults']['pager'] = FALSE;
  $handler->display->display_options['pager']['type'] = 'none';
  $handler->display->display_options['pager']['options']['offset'] = '0';
  $handler->display->display_options['defaults']['style_plugin'] = FALSE;
  $handler->display->display_options['style_plugin'] = 'draggabletable';
  $handler->display->display_options['style_options']['columns'] = array(
    'field_image' => 'field_image',
    'title' => 'title',
    'field_photo_description' => 'title',
    'changed' => 'changed',
    'edit_node' => 'edit_node',
    'translate_node' => 'edit_node',
    'delete_node' => 'edit_node',
    'value0' => 'value0',
  );
  $handler->display->display_options['style_options']['default'] = -1;
  $handler->display->display_options['style_options']['info'] = array(
    'field_image' => array(
      'sortable' => 0,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'title' => array(
      'sortable' => 0,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => ': ',
      'empty_column' => 0,
    ),
    'field_photo_description' => array(
      'sortable' => 0,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'changed' => array(
      'sortable' => 1,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'edit_node' => array(
      'align' => '',
      'separator' => ' | ',
      'empty_column' => 0,
    ),
    'translate_node' => array(
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'delete_node' => array(
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'value0' => array(
      'sortable' => 0,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
  );
  $handler->display->display_options['style_options']['override'] = 0;
  $handler->display->display_options['style_options']['sticky'] = 0;
  $handler->display->display_options['style_options']['empty_table'] = 0;
  $handler->display->display_options['style_options']['tabledrag_order'] = array(
    'field' => 'value0',
    'handler' => 'native',
  );
  $handler->display->display_options['style_options']['tabledrag_order_visible'] = array(
    'visible' => 0,
  );
  $handler->display->display_options['style_options']['tabledrag_hierarchy'] = array(
    'field' => 'none',
    'handler' => 'native',
  );
  $handler->display->display_options['style_options']['tabledrag_hierarchy_visible'] = array(
    'visible' => 0,
  );
  $handler->display->display_options['style_options']['draggableviews_depth_limit'] = '0';
  $handler->display->display_options['style_options']['tabledrag_expand'] = array(
    'expand_links' => 0,
    'collapsed' => 0,
    'by_uid' => 0,
  );
  $handler->display->display_options['style_options']['draggableviews_extensions'] = array(
    'extension_top' => '3',
    'extension_bottom' => '3',
  );
  $handler->display->display_options['style_options']['tabledrag_lock'] = array(
    'lock' => 0,
  );
  $handler->display->display_options['style_options']['draggableviews_default_on_top'] = '1';
  $handler->display->display_options['style_options']['draggableviews_arguments'] = array(
    'use_args' => 0,
  );
  $handler->display->display_options['defaults']['style_options'] = FALSE;
  $handler->display->display_options['defaults']['row_plugin'] = FALSE;
  $handler->display->display_options['defaults']['row_options'] = FALSE;
  $handler->display->display_options['defaults']['empty'] = FALSE;
  /* No results behavior: Global: Text area */
  $handler->display->display_options['empty']['area']['id'] = 'area';
  $handler->display->display_options['empty']['area']['table'] = 'views';
  $handler->display->display_options['empty']['area']['field'] = 'area';
  $handler->display->display_options['empty']['area']['empty'] = FALSE;
  $handler->display->display_options['empty']['area']['content'] = '<br><br><br>
<p>No member photos. Use "Add Photo" link to add a photo</p>';
  $handler->display->display_options['empty']['area']['format'] = 'full_html_simple';
  $handler->display->display_options['empty']['area']['tokenize'] = 0;
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
  $handler->display->display_options['fields']['field_image']['alter']['strip_tags'] = 0;
  $handler->display->display_options['fields']['field_image']['alter']['trim'] = 0;
  $handler->display->display_options['fields']['field_image']['alter']['html'] = 0;
  $handler->display->display_options['fields']['field_image']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['field_image']['element_default_classes'] = 1;
  $handler->display->display_options['fields']['field_image']['hide_empty'] = 0;
  $handler->display->display_options['fields']['field_image']['empty_zero'] = 0;
  $handler->display->display_options['fields']['field_image']['hide_alter_empty'] = 0;
  $handler->display->display_options['fields']['field_image']['click_sort_column'] = 'fid';
  $handler->display->display_options['fields']['field_image']['settings'] = array(
    'image_style' => 'thumbnail',
    'image_link' => '',
  );
  $handler->display->display_options['fields']['field_image']['field_api_classes'] = 0;
  /* Field: Content: Title */
  $handler->display->display_options['fields']['title']['id'] = 'title';
  $handler->display->display_options['fields']['title']['table'] = 'node';
  $handler->display->display_options['fields']['title']['field'] = 'title';
  $handler->display->display_options['fields']['title']['label'] = 'Node Title';
  $handler->display->display_options['fields']['title']['alter']['alter_text'] = 0;
  $handler->display->display_options['fields']['title']['alter']['make_link'] = 0;
  $handler->display->display_options['fields']['title']['alter']['path'] = 'node/[nid]/edit';
  $handler->display->display_options['fields']['title']['alter']['absolute'] = 0;
  $handler->display->display_options['fields']['title']['alter']['external'] = 0;
  $handler->display->display_options['fields']['title']['alter']['replace_spaces'] = 0;
  $handler->display->display_options['fields']['title']['alter']['trim_whitespace'] = 0;
  $handler->display->display_options['fields']['title']['alter']['nl2br'] = 0;
  $handler->display->display_options['fields']['title']['alter']['word_boundary'] = 0;
  $handler->display->display_options['fields']['title']['alter']['ellipsis'] = 0;
  $handler->display->display_options['fields']['title']['alter']['strip_tags'] = 0;
  $handler->display->display_options['fields']['title']['alter']['trim'] = 0;
  $handler->display->display_options['fields']['title']['alter']['html'] = 0;
  $handler->display->display_options['fields']['title']['element_label_colon'] = 0;
  $handler->display->display_options['fields']['title']['element_default_classes'] = 1;
  $handler->display->display_options['fields']['title']['hide_empty'] = 0;
  $handler->display->display_options['fields']['title']['empty_zero'] = 0;
  $handler->display->display_options['fields']['title']['hide_alter_empty'] = 0;
  $handler->display->display_options['fields']['title']['link_to_node'] = 0;
  /* Field: Content: Photo Description */
  $handler->display->display_options['fields']['field_photo_description']['id'] = 'field_photo_description';
  $handler->display->display_options['fields']['field_photo_description']['table'] = 'field_data_field_photo_description';
  $handler->display->display_options['fields']['field_photo_description']['field'] = 'field_photo_description';
  $handler->display->display_options['fields']['field_photo_description']['alter']['alter_text'] = 0;
  $handler->display->display_options['fields']['field_photo_description']['alter']['make_link'] = 0;
  $handler->display->display_options['fields']['field_photo_description']['alter']['absolute'] = 0;
  $handler->display->display_options['fields']['field_photo_description']['alter']['external'] = 0;
  $handler->display->display_options['fields']['field_photo_description']['alter']['replace_spaces'] = 0;
  $handler->display->display_options['fields']['field_photo_description']['alter']['trim_whitespace'] = 0;
  $handler->display->display_options['fields']['field_photo_description']['alter']['nl2br'] = 0;
  $handler->display->display_options['fields']['field_photo_description']['alter']['max_length'] = '100';
  $handler->display->display_options['fields']['field_photo_description']['alter']['word_boundary'] = 1;
  $handler->display->display_options['fields']['field_photo_description']['alter']['ellipsis'] = 1;
  $handler->display->display_options['fields']['field_photo_description']['alter']['more_link'] = 0;
  $handler->display->display_options['fields']['field_photo_description']['alter']['strip_tags'] = 0;
  $handler->display->display_options['fields']['field_photo_description']['alter']['trim'] = 1;
  $handler->display->display_options['fields']['field_photo_description']['alter']['html'] = 0;
  $handler->display->display_options['fields']['field_photo_description']['element_label_colon'] = 1;
  $handler->display->display_options['fields']['field_photo_description']['element_default_classes'] = 1;
  $handler->display->display_options['fields']['field_photo_description']['hide_empty'] = 0;
  $handler->display->display_options['fields']['field_photo_description']['empty_zero'] = 0;
  $handler->display->display_options['fields']['field_photo_description']['hide_alter_empty'] = 1;
  $handler->display->display_options['fields']['field_photo_description']['settings'] = array(
    'trim_length' => '100',
  );
  $handler->display->display_options['fields']['field_photo_description']['field_api_classes'] = 0;
  /* Field: Content: Updated date */
  $handler->display->display_options['fields']['changed']['id'] = 'changed';
  $handler->display->display_options['fields']['changed']['table'] = 'node';
  $handler->display->display_options['fields']['changed']['field'] = 'changed';
  $handler->display->display_options['fields']['changed']['label'] = 'Last Update';
  $handler->display->display_options['fields']['changed']['alter']['alter_text'] = 0;
  $handler->display->display_options['fields']['changed']['alter']['make_link'] = 0;
  $handler->display->display_options['fields']['changed']['alter']['absolute'] = 0;
  $handler->display->display_options['fields']['changed']['alter']['external'] = 0;
  $handler->display->display_options['fields']['changed']['alter']['replace_spaces'] = 0;
  $handler->display->display_options['fields']['changed']['alter']['trim_whitespace'] = 0;
  $handler->display->display_options['fields']['changed']['alter']['nl2br'] = 0;
  $handler->display->display_options['fields']['changed']['alter']['word_boundary'] = 1;
  $handler->display->display_options['fields']['changed']['alter']['ellipsis'] = 1;
  $handler->display->display_options['fields']['changed']['alter']['strip_tags'] = 0;
  $handler->display->display_options['fields']['changed']['alter']['trim'] = 0;
  $handler->display->display_options['fields']['changed']['alter']['html'] = 0;
  $handler->display->display_options['fields']['changed']['element_label_colon'] = 1;
  $handler->display->display_options['fields']['changed']['element_default_classes'] = 1;
  $handler->display->display_options['fields']['changed']['hide_empty'] = 0;
  $handler->display->display_options['fields']['changed']['empty_zero'] = 0;
  $handler->display->display_options['fields']['changed']['hide_alter_empty'] = 1;
  $handler->display->display_options['fields']['changed']['date_format'] = 'short';
  /* Field: Content: Edit link */
  $handler->display->display_options['fields']['edit_node']['id'] = 'edit_node';
  $handler->display->display_options['fields']['edit_node']['table'] = 'views_entity_node';
  $handler->display->display_options['fields']['edit_node']['field'] = 'edit_node';
  $handler->display->display_options['fields']['edit_node']['label'] = 'Operations';
  $handler->display->display_options['fields']['edit_node']['alter']['alter_text'] = 0;
  $handler->display->display_options['fields']['edit_node']['alter']['make_link'] = 0;
  $handler->display->display_options['fields']['edit_node']['alter']['absolute'] = 0;
  $handler->display->display_options['fields']['edit_node']['alter']['replace_spaces'] = 0;
  $handler->display->display_options['fields']['edit_node']['alter']['trim_whitespace'] = 0;
  $handler->display->display_options['fields']['edit_node']['alter']['nl2br'] = 0;
  $handler->display->display_options['fields']['edit_node']['alter']['word_boundary'] = 1;
  $handler->display->display_options['fields']['edit_node']['alter']['ellipsis'] = 1;
  $handler->display->display_options['fields']['edit_node']['alter']['strip_tags'] = 0;
  $handler->display->display_options['fields']['edit_node']['alter']['trim'] = 0;
  $handler->display->display_options['fields']['edit_node']['alter']['html'] = 0;
  $handler->display->display_options['fields']['edit_node']['element_label_colon'] = 1;
  $handler->display->display_options['fields']['edit_node']['element_default_classes'] = 1;
  $handler->display->display_options['fields']['edit_node']['hide_empty'] = 0;
  $handler->display->display_options['fields']['edit_node']['empty_zero'] = 0;
  $handler->display->display_options['fields']['edit_node']['hide_alter_empty'] = 1;
  /* Field: Content: Delete link */
  $handler->display->display_options['fields']['delete_node']['id'] = 'delete_node';
  $handler->display->display_options['fields']['delete_node']['table'] = 'views_entity_node';
  $handler->display->display_options['fields']['delete_node']['field'] = 'delete_node';
  $handler->display->display_options['fields']['delete_node']['alter']['alter_text'] = 0;
  $handler->display->display_options['fields']['delete_node']['alter']['make_link'] = 0;
  $handler->display->display_options['fields']['delete_node']['alter']['absolute'] = 0;
  $handler->display->display_options['fields']['delete_node']['alter']['replace_spaces'] = 0;
  $handler->display->display_options['fields']['delete_node']['alter']['trim_whitespace'] = 0;
  $handler->display->display_options['fields']['delete_node']['alter']['nl2br'] = 0;
  $handler->display->display_options['fields']['delete_node']['alter']['word_boundary'] = 1;
  $handler->display->display_options['fields']['delete_node']['alter']['ellipsis'] = 1;
  $handler->display->display_options['fields']['delete_node']['alter']['strip_tags'] = 0;
  $handler->display->display_options['fields']['delete_node']['alter']['trim'] = 0;
  $handler->display->display_options['fields']['delete_node']['alter']['html'] = 0;
  $handler->display->display_options['fields']['delete_node']['element_label_colon'] = 1;
  $handler->display->display_options['fields']['delete_node']['element_default_classes'] = 1;
  $handler->display->display_options['fields']['delete_node']['hide_empty'] = 0;
  $handler->display->display_options['fields']['delete_node']['empty_zero'] = 0;
  $handler->display->display_options['fields']['delete_node']['hide_alter_empty'] = 1;
  /* Field: DraggableViews: Order */
  $handler->display->display_options['fields']['value0']['id'] = 'value0';
  $handler->display->display_options['fields']['value0']['table'] = 'draggableviews_structure_node0';
  $handler->display->display_options['fields']['value0']['field'] = 'value0';
  $handler->display->display_options['fields']['value0']['label'] = '';
  $handler->display->display_options['fields']['value0']['alter']['alter_text'] = 0;
  $handler->display->display_options['fields']['value0']['alter']['make_link'] = 0;
  $handler->display->display_options['fields']['value0']['alter']['absolute'] = 0;
  $handler->display->display_options['fields']['value0']['alter']['external'] = 0;
  $handler->display->display_options['fields']['value0']['alter']['replace_spaces'] = 0;
  $handler->display->display_options['fields']['value0']['alter']['trim_whitespace'] = 0;
  $handler->display->display_options['fields']['value0']['alter']['nl2br'] = 0;
  $handler->display->display_options['fields']['value0']['alter']['word_boundary'] = 1;
  $handler->display->display_options['fields']['value0']['alter']['ellipsis'] = 1;
  $handler->display->display_options['fields']['value0']['alter']['strip_tags'] = 0;
  $handler->display->display_options['fields']['value0']['alter']['trim'] = 0;
  $handler->display->display_options['fields']['value0']['alter']['html'] = 0;
  $handler->display->display_options['fields']['value0']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['value0']['element_default_classes'] = 1;
  $handler->display->display_options['fields']['value0']['hide_empty'] = 0;
  $handler->display->display_options['fields']['value0']['empty_zero'] = 0;
  $handler->display->display_options['fields']['value0']['hide_alter_empty'] = 0;
  $handler->display->display_options['entity_type'] = 'node';
  $handler->display->display_options['bundles'] = array(
    0 => 'media_collection',
  );
  $handler->display->display_options['show_title'] = 1;

  /* Display: EVA: attached to node */
  $handler = $view->new_display('entity_view', 'EVA: attached to node', 'entity_view_2');
  $handler->display->display_options['display_description'] = 'For displaying collection contents within a node that references the collection.';
  $handler->display->display_options['defaults']['arguments'] = FALSE;
  /* Contextual filter: Content: Part of Collection (field_ref_collection) */
  $handler->display->display_options['arguments']['field_ref_collection_nid']['id'] = 'field_ref_collection_nid';
  $handler->display->display_options['arguments']['field_ref_collection_nid']['table'] = 'field_data_field_ref_collection';
  $handler->display->display_options['arguments']['field_ref_collection_nid']['field'] = 'field_ref_collection_nid';
  $handler->display->display_options['arguments']['field_ref_collection_nid']['default_argument_type'] = 'fixed';
  $handler->display->display_options['arguments']['field_ref_collection_nid']['default_argument_skip_url'] = 0;
  $handler->display->display_options['arguments']['field_ref_collection_nid']['summary']['number_of_records'] = '0';
  $handler->display->display_options['arguments']['field_ref_collection_nid']['summary']['format'] = 'default_summary';
  $handler->display->display_options['arguments']['field_ref_collection_nid']['summary_options']['items_per_page'] = '25';
  $handler->display->display_options['arguments']['field_ref_collection_nid']['break_phrase'] = 0;
  $handler->display->display_options['arguments']['field_ref_collection_nid']['not'] = 0;
  $handler->display->display_options['entity_type'] = 'node';
  $handler->display->display_options['bundles'] = array(
    0 => 'media_article',
    1 => 'project',
  );
  $handler->display->display_options['argument_mode'] = 'token';
  $handler->display->display_options['default_argument'] = '[node:field-collection-attached:nid]';
  $handler->display->display_options['show_title'] = 1;

  /* Display: EVA: attached to member */
  $handler = $view->new_display('entity_view', 'EVA: attached to member', 'entity_view_3');
  $handler->display->display_options['defaults']['title'] = FALSE;
  $handler->display->display_options['title'] = 'Collection Members';
  $handler->display->display_options['display_description'] = 'For displaying additional members nodes when viewing a member';
  $handler->display->display_options['defaults']['pager'] = FALSE;
  $handler->display->display_options['pager']['type'] = 'none';
  $handler->display->display_options['pager']['options']['offset'] = '0';
  $handler->display->display_options['defaults']['style_plugin'] = FALSE;
  $handler->display->display_options['style_plugin'] = 'list';
  $handler->display->display_options['defaults']['style_options'] = FALSE;
  $handler->display->display_options['defaults']['row_plugin'] = FALSE;
  $handler->display->display_options['row_plugin'] = 'fields';
  $handler->display->display_options['defaults']['row_options'] = FALSE;
  $handler->display->display_options['defaults']['relationships'] = FALSE;
  /* Relationship: File Usage: File */
  $handler->display->display_options['relationships']['node_to_file']['id'] = 'node_to_file';
  $handler->display->display_options['relationships']['node_to_file']['table'] = 'file_usage';
  $handler->display->display_options['relationships']['node_to_file']['field'] = 'node_to_file';
  $handler->display->display_options['relationships']['node_to_file']['label'] = 'Image File';
  $handler->display->display_options['relationships']['node_to_file']['required'] = 0;
  $handler->display->display_options['defaults']['fields'] = FALSE;
  /* Field: File: Path */
  $handler->display->display_options['fields']['uri']['id'] = 'uri';
  $handler->display->display_options['fields']['uri']['table'] = 'file_managed';
  $handler->display->display_options['fields']['uri']['field'] = 'uri';
  $handler->display->display_options['fields']['uri']['relationship'] = 'node_to_file';
  $handler->display->display_options['fields']['uri']['label'] = '';
  $handler->display->display_options['fields']['uri']['exclude'] = TRUE;
  $handler->display->display_options['fields']['uri']['alter']['alter_text'] = 0;
  $handler->display->display_options['fields']['uri']['alter']['make_link'] = 0;
  $handler->display->display_options['fields']['uri']['alter']['absolute'] = 0;
  $handler->display->display_options['fields']['uri']['alter']['external'] = 0;
  $handler->display->display_options['fields']['uri']['alter']['replace_spaces'] = 0;
  $handler->display->display_options['fields']['uri']['alter']['trim_whitespace'] = 0;
  $handler->display->display_options['fields']['uri']['alter']['nl2br'] = 0;
  $handler->display->display_options['fields']['uri']['alter']['word_boundary'] = 1;
  $handler->display->display_options['fields']['uri']['alter']['ellipsis'] = 1;
  $handler->display->display_options['fields']['uri']['alter']['strip_tags'] = 0;
  $handler->display->display_options['fields']['uri']['alter']['trim'] = 0;
  $handler->display->display_options['fields']['uri']['alter']['html'] = 0;
  $handler->display->display_options['fields']['uri']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['uri']['element_default_classes'] = 1;
  $handler->display->display_options['fields']['uri']['hide_empty'] = 0;
  $handler->display->display_options['fields']['uri']['empty_zero'] = 0;
  $handler->display->display_options['fields']['uri']['hide_alter_empty'] = 1;
  $handler->display->display_options['fields']['uri']['link_to_file'] = 0;
  $handler->display->display_options['fields']['uri']['file_download_path'] = 1;
  /* Field: Content: Primary Image */
  $handler->display->display_options['fields']['field_image']['id'] = 'field_image';
  $handler->display->display_options['fields']['field_image']['table'] = 'field_data_field_image';
  $handler->display->display_options['fields']['field_image']['field'] = 'field_image';
  $handler->display->display_options['fields']['field_image']['label'] = '';
  $handler->display->display_options['fields']['field_image']['exclude'] = TRUE;
  $handler->display->display_options['fields']['field_image']['alter']['alter_text'] = 0;
  $handler->display->display_options['fields']['field_image']['alter']['make_link'] = 0;
  $handler->display->display_options['fields']['field_image']['alter']['absolute'] = 0;
  $handler->display->display_options['fields']['field_image']['alter']['external'] = 0;
  $handler->display->display_options['fields']['field_image']['alter']['replace_spaces'] = 0;
  $handler->display->display_options['fields']['field_image']['alter']['trim_whitespace'] = 0;
  $handler->display->display_options['fields']['field_image']['alter']['nl2br'] = 0;
  $handler->display->display_options['fields']['field_image']['alter']['word_boundary'] = 1;
  $handler->display->display_options['fields']['field_image']['alter']['ellipsis'] = 1;
  $handler->display->display_options['fields']['field_image']['alter']['strip_tags'] = 0;
  $handler->display->display_options['fields']['field_image']['alter']['trim'] = 0;
  $handler->display->display_options['fields']['field_image']['alter']['html'] = 0;
  $handler->display->display_options['fields']['field_image']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['field_image']['element_default_classes'] = 1;
  $handler->display->display_options['fields']['field_image']['hide_empty'] = 0;
  $handler->display->display_options['fields']['field_image']['empty_zero'] = 0;
  $handler->display->display_options['fields']['field_image']['hide_alter_empty'] = 0;
  $handler->display->display_options['fields']['field_image']['click_sort_column'] = 'fid';
  $handler->display->display_options['fields']['field_image']['settings'] = array(
    'image_style' => 'photo_set_thumbnail',
    'image_link' => '',
  );
  $handler->display->display_options['fields']['field_image']['field_api_classes'] = 0;
  /* Field: Content: Path (rewrite) */
  $handler->display->display_options['fields']['path']['id'] = 'path';
  $handler->display->display_options['fields']['path']['table'] = 'node';
  $handler->display->display_options['fields']['path']['field'] = 'path';
  $handler->display->display_options['fields']['path']['ui_name'] = 'Content: Path (rewrite)';
  $handler->display->display_options['fields']['path']['label'] = '';
  $handler->display->display_options['fields']['path']['alter']['alter_text'] = 1;
  $handler->display->display_options['fields']['path']['alter']['text'] = '<a href="[path]" imageSrc="[uri]">[field_image]</a>';
  $handler->display->display_options['fields']['path']['alter']['make_link'] = 0;
  $handler->display->display_options['fields']['path']['alter']['absolute'] = 0;
  $handler->display->display_options['fields']['path']['alter']['external'] = 0;
  $handler->display->display_options['fields']['path']['alter']['replace_spaces'] = 0;
  $handler->display->display_options['fields']['path']['alter']['trim_whitespace'] = 0;
  $handler->display->display_options['fields']['path']['alter']['nl2br'] = 0;
  $handler->display->display_options['fields']['path']['alter']['word_boundary'] = 1;
  $handler->display->display_options['fields']['path']['alter']['ellipsis'] = 1;
  $handler->display->display_options['fields']['path']['alter']['strip_tags'] = 0;
  $handler->display->display_options['fields']['path']['alter']['trim'] = 0;
  $handler->display->display_options['fields']['path']['alter']['html'] = 0;
  $handler->display->display_options['fields']['path']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['path']['element_default_classes'] = 1;
  $handler->display->display_options['fields']['path']['hide_empty'] = 0;
  $handler->display->display_options['fields']['path']['empty_zero'] = 0;
  $handler->display->display_options['fields']['path']['hide_alter_empty'] = 1;
  $handler->display->display_options['fields']['path']['absolute'] = 0;
  /* Field: Content: Photo Description */
  $handler->display->display_options['fields']['field_photo_description']['id'] = 'field_photo_description';
  $handler->display->display_options['fields']['field_photo_description']['table'] = 'field_data_field_photo_description';
  $handler->display->display_options['fields']['field_photo_description']['field'] = 'field_photo_description';
  $handler->display->display_options['fields']['field_photo_description']['label'] = '';
  $handler->display->display_options['fields']['field_photo_description']['alter']['alter_text'] = 0;
  $handler->display->display_options['fields']['field_photo_description']['alter']['make_link'] = 0;
  $handler->display->display_options['fields']['field_photo_description']['alter']['absolute'] = 0;
  $handler->display->display_options['fields']['field_photo_description']['alter']['external'] = 0;
  $handler->display->display_options['fields']['field_photo_description']['alter']['replace_spaces'] = 0;
  $handler->display->display_options['fields']['field_photo_description']['alter']['trim_whitespace'] = 0;
  $handler->display->display_options['fields']['field_photo_description']['alter']['nl2br'] = 0;
  $handler->display->display_options['fields']['field_photo_description']['alter']['word_boundary'] = 1;
  $handler->display->display_options['fields']['field_photo_description']['alter']['ellipsis'] = 1;
  $handler->display->display_options['fields']['field_photo_description']['alter']['more_link'] = 0;
  $handler->display->display_options['fields']['field_photo_description']['alter']['strip_tags'] = 0;
  $handler->display->display_options['fields']['field_photo_description']['alter']['trim'] = 0;
  $handler->display->display_options['fields']['field_photo_description']['alter']['html'] = 0;
  $handler->display->display_options['fields']['field_photo_description']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['field_photo_description']['element_default_classes'] = 1;
  $handler->display->display_options['fields']['field_photo_description']['hide_empty'] = 0;
  $handler->display->display_options['fields']['field_photo_description']['empty_zero'] = 0;
  $handler->display->display_options['fields']['field_photo_description']['hide_alter_empty'] = 1;
  $handler->display->display_options['fields']['field_photo_description']['field_api_classes'] = 0;
  $handler->display->display_options['defaults']['arguments'] = FALSE;
  /* Contextual filter: Content: Part of Collection (field_ref_collection) */
  $handler->display->display_options['arguments']['field_ref_collection_nid']['id'] = 'field_ref_collection_nid';
  $handler->display->display_options['arguments']['field_ref_collection_nid']['table'] = 'field_data_field_ref_collection';
  $handler->display->display_options['arguments']['field_ref_collection_nid']['field'] = 'field_ref_collection_nid';
  $handler->display->display_options['arguments']['field_ref_collection_nid']['default_argument_type'] = 'fixed';
  $handler->display->display_options['arguments']['field_ref_collection_nid']['default_argument_skip_url'] = 0;
  $handler->display->display_options['arguments']['field_ref_collection_nid']['summary']['number_of_records'] = '0';
  $handler->display->display_options['arguments']['field_ref_collection_nid']['summary']['format'] = 'default_summary';
  $handler->display->display_options['arguments']['field_ref_collection_nid']['summary_options']['items_per_page'] = '25';
  $handler->display->display_options['arguments']['field_ref_collection_nid']['break_phrase'] = 0;
  $handler->display->display_options['arguments']['field_ref_collection_nid']['not'] = 0;
  $handler->display->display_options['entity_type'] = 'node';
  $handler->display->display_options['bundles'] = array(
    0 => 'media_photo',
  );
  $handler->display->display_options['argument_mode'] = 'token';
  $handler->display->display_options['default_argument'] = '[node:field-ref-collection:nid]/[node:nid]';
  $handler->display->display_options['show_title'] = 1;
  $translatables['collection_contents'] = array(
    t('Master'),
    t('Attached Media'),
    t('more'),
    t('Apply'),
    t('Reset'),
    t('Sort by'),
    t('Asc'),
    t('Desc'),
    t('node/[nid]/edit'),
    t('All'),
    t('EVA: for collection node'),
    t('Attached Photos:'),
    t('<br><br><br>
<p>No member photos. Use "Add Photo" link to add a photo</p>'),
    t('Node Title'),
    t('Photo Description'),
    t('Last Update'),
    t('Operations'),
    t('Delete link'),
    t('EVA: attached to node'),
    t('For displaying collection contents within a node that references the collection.'),
    t('EVA: attached to member'),
    t('Collection Members'),
    t('For displaying additional members nodes when viewing a member'),
    t('Image File'),
    t('<a href="[path]" imageSrc="[uri]">[field_image]</a>'),
  );
  $export['collection_contents'] = $view;

  $view = new view;
  $view->name = 'collection_topmost';
  $view->description = 'Used for displaying the contents of a media collection';
  $view->tag = 'default';
  $view->base_table = 'node';
  $view->human_name = 'Collection Topmost';
  $view->core = 7;
  $view->api_version = '3.0';
  $view->disabled = FALSE; /* Edit this to true to make a default view disabled initially */

  /* Display: Master */
  $handler = $view->new_display('default', 'Master', 'default');
  $handler->display->display_options['title'] = 'Topmost Attached Media';
  $handler->display->display_options['access']['type'] = 'perm';
  $handler->display->display_options['cache']['type'] = 'none';
  $handler->display->display_options['query']['type'] = 'views_query';
  $handler->display->display_options['query']['options']['query_comment'] = FALSE;
  $handler->display->display_options['exposed_form']['type'] = 'basic';
  $handler->display->display_options['pager']['type'] = 'some';
  $handler->display->display_options['pager']['options']['items_per_page'] = '1';
  $handler->display->display_options['pager']['options']['offset'] = '0';
  $handler->display->display_options['style_plugin'] = 'default';
  $handler->display->display_options['row_plugin'] = 'fields';
  /* No results behavior: Global: Text area */
  $handler->display->display_options['empty']['area']['id'] = 'area';
  $handler->display->display_options['empty']['area']['table'] = 'views';
  $handler->display->display_options['empty']['area']['field'] = 'area';
  $handler->display->display_options['empty']['area']['empty'] = FALSE;
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
  $handler->display->display_options['fields']['field_image']['alter']['strip_tags'] = 0;
  $handler->display->display_options['fields']['field_image']['alter']['trim'] = 0;
  $handler->display->display_options['fields']['field_image']['alter']['html'] = 0;
  $handler->display->display_options['fields']['field_image']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['field_image']['element_default_classes'] = 1;
  $handler->display->display_options['fields']['field_image']['hide_empty'] = 0;
  $handler->display->display_options['fields']['field_image']['empty_zero'] = 0;
  $handler->display->display_options['fields']['field_image']['hide_alter_empty'] = 0;
  $handler->display->display_options['fields']['field_image']['click_sort_column'] = 'fid';
  $handler->display->display_options['fields']['field_image']['settings'] = array(
    'image_style' => 'medium',
    'image_link' => 'content',
  );
  $handler->display->display_options['fields']['field_image']['field_api_classes'] = 0;
  /* Sort criterion: DraggableViews: Order */
  $handler->display->display_options['sorts']['value0']['id'] = 'value0';
  $handler->display->display_options['sorts']['value0']['table'] = 'draggableviews_structure_node0';
  $handler->display->display_options['sorts']['value0']['field'] = 'value0';
  /* Sort criterion: Content: Post date */
  $handler->display->display_options['sorts']['created']['id'] = 'created';
  $handler->display->display_options['sorts']['created']['table'] = 'node';
  $handler->display->display_options['sorts']['created']['field'] = 'created';
  /* Contextual filter: Content: Part of Collection (field_ref_collection) */
  $handler->display->display_options['arguments']['field_ref_collection_nid']['id'] = 'field_ref_collection_nid';
  $handler->display->display_options['arguments']['field_ref_collection_nid']['table'] = 'field_data_field_ref_collection';
  $handler->display->display_options['arguments']['field_ref_collection_nid']['field'] = 'field_ref_collection_nid';
  $handler->display->display_options['arguments']['field_ref_collection_nid']['default_action'] = 'empty';
  $handler->display->display_options['arguments']['field_ref_collection_nid']['default_argument_type'] = 'fixed';
  $handler->display->display_options['arguments']['field_ref_collection_nid']['default_argument_skip_url'] = 0;
  $handler->display->display_options['arguments']['field_ref_collection_nid']['summary']['number_of_records'] = '0';
  $handler->display->display_options['arguments']['field_ref_collection_nid']['summary']['format'] = 'default_summary';
  $handler->display->display_options['arguments']['field_ref_collection_nid']['summary_options']['items_per_page'] = '25';
  $handler->display->display_options['arguments']['field_ref_collection_nid']['break_phrase'] = 0;
  $handler->display->display_options['arguments']['field_ref_collection_nid']['not'] = 0;
  /* Filter criterion: Content: Type */
  $handler->display->display_options['filters']['type']['id'] = 'type';
  $handler->display->display_options['filters']['type']['table'] = 'node';
  $handler->display->display_options['filters']['type']['field'] = 'type';
  $handler->display->display_options['filters']['type']['value'] = array(
    'media_photo' => 'media_photo',
  );
  /* Filter criterion: Content: Published or admin */
  $handler->display->display_options['filters']['status_extra']['id'] = 'status_extra';
  $handler->display->display_options['filters']['status_extra']['table'] = 'node';
  $handler->display->display_options['filters']['status_extra']['field'] = 'status_extra';

  /* Display: EVA: for collection node */
  $handler = $view->new_display('entity_view', 'EVA: for collection node', 'entity_view_1');
  $handler->display->display_options['entity_type'] = 'node';
  $handler->display->display_options['bundles'] = array(
    0 => 'media_collection',
  );
  $handler->display->display_options['show_title'] = 0;

  /* Display: EVA: attached to node */
  $handler = $view->new_display('entity_view', 'EVA: attached to node', 'entity_view_2');
  $handler->display->display_options['display_description'] = 'For displaying collection contents within a node that references the collection.';
  $handler->display->display_options['defaults']['arguments'] = FALSE;
  /* Contextual filter: Content: Part of Collection (field_ref_collection) */
  $handler->display->display_options['arguments']['field_ref_collection_nid']['id'] = 'field_ref_collection_nid';
  $handler->display->display_options['arguments']['field_ref_collection_nid']['table'] = 'field_data_field_ref_collection';
  $handler->display->display_options['arguments']['field_ref_collection_nid']['field'] = 'field_ref_collection_nid';
  $handler->display->display_options['arguments']['field_ref_collection_nid']['default_argument_type'] = 'fixed';
  $handler->display->display_options['arguments']['field_ref_collection_nid']['default_argument_skip_url'] = 0;
  $handler->display->display_options['arguments']['field_ref_collection_nid']['summary']['number_of_records'] = '0';
  $handler->display->display_options['arguments']['field_ref_collection_nid']['summary']['format'] = 'default_summary';
  $handler->display->display_options['arguments']['field_ref_collection_nid']['summary_options']['items_per_page'] = '25';
  $handler->display->display_options['arguments']['field_ref_collection_nid']['break_phrase'] = 0;
  $handler->display->display_options['arguments']['field_ref_collection_nid']['not'] = 0;
  $handler->display->display_options['entity_type'] = 'node';
  $handler->display->display_options['bundles'] = array(
    0 => 'media_article',
    1 => 'project',
  );
  $handler->display->display_options['argument_mode'] = 'token';
  $handler->display->display_options['default_argument'] = '[node:field-collection-attached:nid]';
  $handler->display->display_options['show_title'] = 0;

  /* Display: Block: for Album List View Field */
  $handler = $view->new_display('block', 'Block: for Album List View Field', 'block_1');
  $handler->display->display_options['defaults']['empty'] = FALSE;
  /* No results behavior: Global: Text area */
  $handler->display->display_options['empty']['area']['id'] = 'area';
  $handler->display->display_options['empty']['area']['table'] = 'views';
  $handler->display->display_options['empty']['area']['field'] = 'area';
  $handler->display->display_options['empty']['area']['empty'] = FALSE;
  $handler->display->display_options['empty']['area']['format'] = 'page_code';
  $handler->display->display_options['empty']['area']['tokenize'] = 0;
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
  $handler->display->display_options['fields']['field_image']['alter']['strip_tags'] = 0;
  $handler->display->display_options['fields']['field_image']['alter']['trim'] = 0;
  $handler->display->display_options['fields']['field_image']['alter']['html'] = 0;
  $handler->display->display_options['fields']['field_image']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['field_image']['element_default_classes'] = 1;
  $handler->display->display_options['fields']['field_image']['hide_empty'] = 0;
  $handler->display->display_options['fields']['field_image']['empty_zero'] = 0;
  $handler->display->display_options['fields']['field_image']['hide_alter_empty'] = 0;
  $handler->display->display_options['fields']['field_image']['click_sort_column'] = 'fid';
  $handler->display->display_options['fields']['field_image']['settings'] = array(
    'image_style' => 'album_list_50x50',
    'image_link' => 'content',
  );
  $handler->display->display_options['fields']['field_image']['field_api_classes'] = 0;

  /* Display: Block: for Photos Admin */
  $handler = $view->new_display('block', 'Block: for Photos Admin', 'block_2');
  $handler->display->display_options['defaults']['empty'] = FALSE;
  /* No results behavior: Global: Text area */
  $handler->display->display_options['empty']['area']['id'] = 'area';
  $handler->display->display_options['empty']['area']['table'] = 'views';
  $handler->display->display_options['empty']['area']['field'] = 'area';
  $handler->display->display_options['empty']['area']['empty'] = FALSE;
  $handler->display->display_options['empty']['area']['format'] = 'page_code';
  $handler->display->display_options['empty']['area']['tokenize'] = 0;
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
  $handler->display->display_options['fields']['field_image']['hide_empty'] = 0;
  $handler->display->display_options['fields']['field_image']['empty_zero'] = 0;
  $handler->display->display_options['fields']['field_image']['hide_alter_empty'] = 0;
  $handler->display->display_options['fields']['field_image']['click_sort_column'] = 'fid';
  $handler->display->display_options['fields']['field_image']['settings'] = array(
    'image_style' => 'thumbnail',
    'image_link' => 'content',
  );
  $handler->display->display_options['fields']['field_image']['field_api_classes'] = 0;
  $translatables['collection_topmost'] = array(
    t('Master'),
    t('Topmost Attached Media'),
    t('more'),
    t('Apply'),
    t('Reset'),
    t('Sort by'),
    t('Asc'),
    t('Desc'),
    t('All'),
    t('EVA: for collection node'),
    t('EVA: attached to node'),
    t('For displaying collection contents within a node that references the collection.'),
    t('Block: for Album List View Field'),
    t('Block: for Photos Admin'),
  );
  $export['collection_topmost'] = $view;

  $view = new view;
  $view->name = 'photo_grid';
  $view->description = '';
  $view->tag = 'photo';
  $view->base_table = 'node';
  $view->human_name = 'Photo Grid';
  $view->core = 7;
  $view->api_version = '3.0';
  $view->disabled = FALSE; /* Edit this to true to make a default view disabled initially */

  /* Display: Master */
  $handler = $view->new_display('default', 'Master', 'default');
  $handler->display->display_options['title'] = 'Photo Grid';
  $handler->display->display_options['use_ajax'] = TRUE;
  $handler->display->display_options['access']['type'] = 'perm';
  $handler->display->display_options['cache']['type'] = 'none';
  $handler->display->display_options['query']['type'] = 'views_query';
  $handler->display->display_options['query']['options']['distinct'] = TRUE;
  $handler->display->display_options['query']['options']['query_comment'] = FALSE;
  $handler->display->display_options['exposed_form']['type'] = 'better_exposed_filters';
  $handler->display->display_options['exposed_form']['options']['submit_button'] = 'Sort';
  $handler->display->display_options['exposed_form']['options']['exposed_sorts_label'] = 'Order By';
  $handler->display->display_options['exposed_form']['options']['autosubmit'] = 0;
  $handler->display->display_options['exposed_form']['options']['autosubmit_hide'] = 1;
  $handler->display->display_options['exposed_form']['options']['bef'] = array(
    'sort' => array(
      'bef_format' => 'bef',
      'collapsible' => 0,
      'collapsible_label' => 'Sort options',
      'combine' => 0,
      'reset' => 0,
      'reset_label' => '',
    ),
    'term_node_tid_depth' => array(
      'bef_format' => 'bef_ul',
      'more_options' => array(
        'bef_select_all_none' => 0,
        'bef_collapsible' => 0,
        'bef_filter_description' => '',
        'tokens' => array(
          'available' => array(
            0 => 'global_types',
          ),
        ),
      ),
    ),
    'tid' => array(
      'bef_format' => 'bef',
      'more_options' => array(
        'bef_select_all_none' => 0,
        'bef_collapsible' => 0,
        'bef_filter_description' => '',
        'tokens' => array(
          'available' => array(
            0 => 'global_types',
          ),
        ),
      ),
    ),
  );
  $handler->display->display_options['pager']['type'] = 'mini';
  $handler->display->display_options['pager']['options']['items_per_page'] = '9';
  $handler->display->display_options['pager']['options']['offset'] = '0';
  $handler->display->display_options['pager']['options']['id'] = '0';
  $handler->display->display_options['pager']['options']['expose']['items_per_page_options_all'] = 0;
  $handler->display->display_options['style_plugin'] = 'list';
  $handler->display->display_options['row_plugin'] = 'fields';
  /* Relationship: Content: Part of Collection (field_ref_collection) */
  $handler->display->display_options['relationships']['field_ref_collection_nid']['id'] = 'field_ref_collection_nid';
  $handler->display->display_options['relationships']['field_ref_collection_nid']['table'] = 'field_data_field_ref_collection';
  $handler->display->display_options['relationships']['field_ref_collection_nid']['field'] = 'field_ref_collection_nid';
  $handler->display->display_options['relationships']['field_ref_collection_nid']['label'] = 'Parent Collection';
  $handler->display->display_options['relationships']['field_ref_collection_nid']['required'] = 1;
  $handler->display->display_options['relationships']['field_ref_collection_nid']['delta'] = '-1';
  /* Relationship: File Usage: File */
  $handler->display->display_options['relationships']['node_to_file']['id'] = 'node_to_file';
  $handler->display->display_options['relationships']['node_to_file']['table'] = 'file_usage';
  $handler->display->display_options['relationships']['node_to_file']['field'] = 'node_to_file';
  $handler->display->display_options['relationships']['node_to_file']['required'] = 1;
  /* Field: File: Path */
  $handler->display->display_options['fields']['uri']['id'] = 'uri';
  $handler->display->display_options['fields']['uri']['table'] = 'file_managed';
  $handler->display->display_options['fields']['uri']['field'] = 'uri';
  $handler->display->display_options['fields']['uri']['relationship'] = 'node_to_file';
  $handler->display->display_options['fields']['uri']['label'] = '';
  $handler->display->display_options['fields']['uri']['exclude'] = TRUE;
  $handler->display->display_options['fields']['uri']['alter']['alter_text'] = 0;
  $handler->display->display_options['fields']['uri']['alter']['make_link'] = 0;
  $handler->display->display_options['fields']['uri']['alter']['absolute'] = 0;
  $handler->display->display_options['fields']['uri']['alter']['external'] = 0;
  $handler->display->display_options['fields']['uri']['alter']['replace_spaces'] = 0;
  $handler->display->display_options['fields']['uri']['alter']['trim_whitespace'] = 0;
  $handler->display->display_options['fields']['uri']['alter']['nl2br'] = 0;
  $handler->display->display_options['fields']['uri']['alter']['word_boundary'] = 1;
  $handler->display->display_options['fields']['uri']['alter']['ellipsis'] = 1;
  $handler->display->display_options['fields']['uri']['alter']['more_link'] = 0;
  $handler->display->display_options['fields']['uri']['alter']['strip_tags'] = 0;
  $handler->display->display_options['fields']['uri']['alter']['trim'] = 0;
  $handler->display->display_options['fields']['uri']['alter']['html'] = 0;
  $handler->display->display_options['fields']['uri']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['uri']['element_default_classes'] = 0;
  $handler->display->display_options['fields']['uri']['hide_empty'] = 0;
  $handler->display->display_options['fields']['uri']['empty_zero'] = 0;
  $handler->display->display_options['fields']['uri']['hide_alter_empty'] = 1;
  $handler->display->display_options['fields']['uri']['link_to_file'] = 0;
  $handler->display->display_options['fields']['uri']['file_download_path'] = 1;
  /* Field: Content: Primary Image */
  $handler->display->display_options['fields']['field_image']['id'] = 'field_image';
  $handler->display->display_options['fields']['field_image']['table'] = 'field_data_field_image';
  $handler->display->display_options['fields']['field_image']['field'] = 'field_image';
  $handler->display->display_options['fields']['field_image']['label'] = '';
  $handler->display->display_options['fields']['field_image']['exclude'] = TRUE;
  $handler->display->display_options['fields']['field_image']['alter']['alter_text'] = 1;
  $handler->display->display_options['fields']['field_image']['alter']['text'] = '<img src="/sites/all/themes/gazprom/images/blank.gif" data-original="[field_image]" width="240" height="240" class="lazyLoad" />';
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
  $handler->display->display_options['fields']['field_image']['element_default_classes'] = 0;
  $handler->display->display_options['fields']['field_image']['hide_empty'] = 0;
  $handler->display->display_options['fields']['field_image']['empty_zero'] = 0;
  $handler->display->display_options['fields']['field_image']['hide_alter_empty'] = 0;
  $handler->display->display_options['fields']['field_image']['click_sort_column'] = 'fid';
  $handler->display->display_options['fields']['field_image']['type'] = 'image_url';
  $handler->display->display_options['fields']['field_image']['settings'] = array(
    'image_style' => 'grid-square',
    'image_link' => '',
  );
  $handler->display->display_options['fields']['field_image']['field_api_classes'] = 0;
  /* Field: Content: Related to Location */
  $handler->display->display_options['fields']['field_location']['id'] = 'field_location';
  $handler->display->display_options['fields']['field_location']['table'] = 'field_data_field_location';
  $handler->display->display_options['fields']['field_location']['field'] = 'field_location';
  $handler->display->display_options['fields']['field_location']['relationship'] = 'field_ref_collection_nid';
  $handler->display->display_options['fields']['field_location']['label'] = '';
  $handler->display->display_options['fields']['field_location']['exclude'] = TRUE;
  $handler->display->display_options['fields']['field_location']['alter']['alter_text'] = 0;
  $handler->display->display_options['fields']['field_location']['alter']['make_link'] = 0;
  $handler->display->display_options['fields']['field_location']['alter']['absolute'] = 0;
  $handler->display->display_options['fields']['field_location']['alter']['external'] = 0;
  $handler->display->display_options['fields']['field_location']['alter']['replace_spaces'] = 0;
  $handler->display->display_options['fields']['field_location']['alter']['trim_whitespace'] = 0;
  $handler->display->display_options['fields']['field_location']['alter']['nl2br'] = 0;
  $handler->display->display_options['fields']['field_location']['alter']['word_boundary'] = 1;
  $handler->display->display_options['fields']['field_location']['alter']['ellipsis'] = 1;
  $handler->display->display_options['fields']['field_location']['alter']['more_link'] = 0;
  $handler->display->display_options['fields']['field_location']['alter']['strip_tags'] = 0;
  $handler->display->display_options['fields']['field_location']['alter']['trim'] = 0;
  $handler->display->display_options['fields']['field_location']['alter']['html'] = 0;
  $handler->display->display_options['fields']['field_location']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['field_location']['element_default_classes'] = 0;
  $handler->display->display_options['fields']['field_location']['hide_empty'] = 0;
  $handler->display->display_options['fields']['field_location']['empty_zero'] = 0;
  $handler->display->display_options['fields']['field_location']['hide_alter_empty'] = 0;
  $handler->display->display_options['fields']['field_location']['type'] = 'i18n_taxonomy_term_reference_plain';
  $handler->display->display_options['fields']['field_location']['group_rows'] = 1;
  $handler->display->display_options['fields']['field_location']['delta_offset'] = '0';
  $handler->display->display_options['fields']['field_location']['delta_reversed'] = 0;
  $handler->display->display_options['fields']['field_location']['delta_first_last'] = 0;
  $handler->display->display_options['fields']['field_location']['field_api_classes'] = 0;
  /* Field: Content: Photo Description */
  $handler->display->display_options['fields']['field_photo_description']['id'] = 'field_photo_description';
  $handler->display->display_options['fields']['field_photo_description']['table'] = 'field_data_field_photo_description';
  $handler->display->display_options['fields']['field_photo_description']['field'] = 'field_photo_description';
  $handler->display->display_options['fields']['field_photo_description']['label'] = '';
  $handler->display->display_options['fields']['field_photo_description']['exclude'] = TRUE;
  $handler->display->display_options['fields']['field_photo_description']['alter']['alter_text'] = 0;
  $handler->display->display_options['fields']['field_photo_description']['alter']['make_link'] = 0;
  $handler->display->display_options['fields']['field_photo_description']['alter']['absolute'] = 0;
  $handler->display->display_options['fields']['field_photo_description']['alter']['external'] = 0;
  $handler->display->display_options['fields']['field_photo_description']['alter']['replace_spaces'] = 0;
  $handler->display->display_options['fields']['field_photo_description']['alter']['trim_whitespace'] = 0;
  $handler->display->display_options['fields']['field_photo_description']['alter']['nl2br'] = 0;
  $handler->display->display_options['fields']['field_photo_description']['alter']['max_length'] = '100';
  $handler->display->display_options['fields']['field_photo_description']['alter']['word_boundary'] = 1;
  $handler->display->display_options['fields']['field_photo_description']['alter']['ellipsis'] = 1;
  $handler->display->display_options['fields']['field_photo_description']['alter']['more_link'] = 0;
  $handler->display->display_options['fields']['field_photo_description']['alter']['strip_tags'] = 0;
  $handler->display->display_options['fields']['field_photo_description']['alter']['trim'] = 1;
  $handler->display->display_options['fields']['field_photo_description']['alter']['html'] = 0;
  $handler->display->display_options['fields']['field_photo_description']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['field_photo_description']['element_default_classes'] = 0;
  $handler->display->display_options['fields']['field_photo_description']['hide_empty'] = 0;
  $handler->display->display_options['fields']['field_photo_description']['empty_zero'] = 0;
  $handler->display->display_options['fields']['field_photo_description']['hide_alter_empty'] = 1;
  $handler->display->display_options['fields']['field_photo_description']['type'] = 'text_plain';
  $handler->display->display_options['fields']['field_photo_description']['settings'] = array(
    'trim_length' => '100',
  );
  $handler->display->display_options['fields']['field_photo_description']['field_api_classes'] = 0;
  /* Field: Main Output (big rewrite) */
  $handler->display->display_options['fields']['path']['id'] = 'path';
  $handler->display->display_options['fields']['path']['table'] = 'node';
  $handler->display->display_options['fields']['path']['field'] = 'path';
  $handler->display->display_options['fields']['path']['ui_name'] = 'Main Output (big rewrite)';
  $handler->display->display_options['fields']['path']['label'] = '';
  $handler->display->display_options['fields']['path']['alter']['alter_text'] = 1;
  $handler->display->display_options['fields']['path']['alter']['text'] = '<a href="[path]" imageSrc="[uri]">[field_image]</a>
<div class="photo-grid-tip">
  <div class="location">[field_location]</div>
  <div class="description">[field_photo_description]</div>
</div>';
  $handler->display->display_options['fields']['path']['alter']['make_link'] = 0;
  $handler->display->display_options['fields']['path']['alter']['absolute'] = 0;
  $handler->display->display_options['fields']['path']['alter']['external'] = 0;
  $handler->display->display_options['fields']['path']['alter']['replace_spaces'] = 0;
  $handler->display->display_options['fields']['path']['alter']['trim_whitespace'] = 0;
  $handler->display->display_options['fields']['path']['alter']['nl2br'] = 0;
  $handler->display->display_options['fields']['path']['alter']['word_boundary'] = 1;
  $handler->display->display_options['fields']['path']['alter']['ellipsis'] = 1;
  $handler->display->display_options['fields']['path']['alter']['more_link'] = 0;
  $handler->display->display_options['fields']['path']['alter']['strip_tags'] = 0;
  $handler->display->display_options['fields']['path']['alter']['trim'] = 0;
  $handler->display->display_options['fields']['path']['alter']['html'] = 0;
  $handler->display->display_options['fields']['path']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['path']['element_default_classes'] = 1;
  $handler->display->display_options['fields']['path']['hide_empty'] = 0;
  $handler->display->display_options['fields']['path']['empty_zero'] = 0;
  $handler->display->display_options['fields']['path']['hide_alter_empty'] = 1;
  $handler->display->display_options['fields']['path']['absolute'] = 0;
  /* Sort criterion: Global: Random seed */
  $handler->display->display_options['sorts']['random_seed']['id'] = 'random_seed';
  $handler->display->display_options['sorts']['random_seed']['table'] = 'views';
  $handler->display->display_options['sorts']['random_seed']['field'] = 'random_seed';
  $handler->display->display_options['sorts']['random_seed']['exposed'] = TRUE;
  $handler->display->display_options['sorts']['random_seed']['expose']['label'] = 'None';
  $handler->display->display_options['sorts']['random_seed']['reset_seed_int'] = 'custom';
  $handler->display->display_options['sorts']['random_seed']['reset_seed_custom'] = '3600';
  /* Sort criterion: Date of Photo Set */
  $handler->display->display_options['sorts']['field_date_event_value']['id'] = 'field_date_event_value';
  $handler->display->display_options['sorts']['field_date_event_value']['table'] = 'field_data_field_date_event';
  $handler->display->display_options['sorts']['field_date_event_value']['field'] = 'field_date_event_value';
  $handler->display->display_options['sorts']['field_date_event_value']['relationship'] = 'field_ref_collection_nid';
  $handler->display->display_options['sorts']['field_date_event_value']['ui_name'] = 'Date of Photo Set';
  $handler->display->display_options['sorts']['field_date_event_value']['order'] = 'DESC';
  $handler->display->display_options['sorts']['field_date_event_value']['exposed'] = TRUE;
  $handler->display->display_options['sorts']['field_date_event_value']['expose']['label'] = 'Date';
  /* Contextual filter: Content: Nid */
  $handler->display->display_options['arguments']['nid']['id'] = 'nid';
  $handler->display->display_options['arguments']['nid']['table'] = 'node';
  $handler->display->display_options['arguments']['nid']['field'] = 'nid';
  $handler->display->display_options['arguments']['nid']['default_argument_type'] = 'fixed';
  $handler->display->display_options['arguments']['nid']['summary']['format'] = 'default_summary';
  /* Filter criterion: Content: Type */
  $handler->display->display_options['filters']['type']['id'] = 'type';
  $handler->display->display_options['filters']['type']['table'] = 'node';
  $handler->display->display_options['filters']['type']['field'] = 'type';
  $handler->display->display_options['filters']['type']['value'] = array(
    'media_photo' => 'media_photo',
  );
  $handler->display->display_options['filters']['type']['group'] = 1;
  /* Filter criterion: Content: Published */
  $handler->display->display_options['filters']['status']['id'] = 'status';
  $handler->display->display_options['filters']['status']['table'] = 'node';
  $handler->display->display_options['filters']['status']['field'] = 'status';
  $handler->display->display_options['filters']['status']['value'] = '1';
  $handler->display->display_options['filters']['status']['group'] = 1;
  /* Filter criterion: Content: Hide from Gallery (field_gallery_hidden) */
  $handler->display->display_options['filters']['field_gallery_hidden_value']['id'] = 'field_gallery_hidden_value';
  $handler->display->display_options['filters']['field_gallery_hidden_value']['table'] = 'field_data_field_gallery_hidden';
  $handler->display->display_options['filters']['field_gallery_hidden_value']['field'] = 'field_gallery_hidden_value';
  $handler->display->display_options['filters']['field_gallery_hidden_value']['relationship'] = 'field_ref_collection_nid';
  $handler->display->display_options['filters']['field_gallery_hidden_value']['operator'] = 'not in';
  $handler->display->display_options['filters']['field_gallery_hidden_value']['value'] = array(
    1 => '1',
  );
  $handler->display->display_options['filters']['field_gallery_hidden_value']['group'] = 1;
  /* Filter criterion: Search: Search Terms */
  $handler->display->display_options['filters']['keys']['id'] = 'keys';
  $handler->display->display_options['filters']['keys']['table'] = 'search_index';
  $handler->display->display_options['filters']['keys']['field'] = 'keys';
  $handler->display->display_options['filters']['keys']['group'] = 1;
  $handler->display->display_options['filters']['keys']['exposed'] = TRUE;
  $handler->display->display_options['filters']['keys']['expose']['operator_id'] = 'keys_op';
  $handler->display->display_options['filters']['keys']['expose']['label'] = 'Search';
  $handler->display->display_options['filters']['keys']['expose']['operator'] = 'keys_op';
  $handler->display->display_options['filters']['keys']['expose']['identifier'] = 'keys';
  $handler->display->display_options['filters']['keys']['expose']['multiple'] = FALSE;
  /* Filter criterion: Country Filter */
  $handler->display->display_options['filters']['term_node_tid_depth']['id'] = 'term_node_tid_depth';
  $handler->display->display_options['filters']['term_node_tid_depth']['table'] = 'node';
  $handler->display->display_options['filters']['term_node_tid_depth']['field'] = 'term_node_tid_depth';
  $handler->display->display_options['filters']['term_node_tid_depth']['relationship'] = 'field_ref_collection_nid';
  $handler->display->display_options['filters']['term_node_tid_depth']['ui_name'] = 'Country Filter';
  $handler->display->display_options['filters']['term_node_tid_depth']['value'] = array(
    6 => '6',
    13 => '13',
    14 => '14',
    17 => '17',
    22 => '22',
    40 => '40',
    20 => '20',
    44 => '44',
    43 => '43',
    21 => '21',
    7 => '7',
    19 => '19',
    15 => '15',
    16 => '16',
    18 => '18',
    5 => '5',
    11 => '11',
    47 => '47',
    10 => '10',
    48 => '48',
  );
  $handler->display->display_options['filters']['term_node_tid_depth']['group'] = 1;
  $handler->display->display_options['filters']['term_node_tid_depth']['exposed'] = TRUE;
  $handler->display->display_options['filters']['term_node_tid_depth']['expose']['operator_id'] = 'term_node_tid_depth_op';
  $handler->display->display_options['filters']['term_node_tid_depth']['expose']['label'] = 'Country';
  $handler->display->display_options['filters']['term_node_tid_depth']['expose']['operator'] = 'term_node_tid_depth_op';
  $handler->display->display_options['filters']['term_node_tid_depth']['expose']['identifier'] = 'country';
  $handler->display->display_options['filters']['term_node_tid_depth']['expose']['multiple'] = 1;
  $handler->display->display_options['filters']['term_node_tid_depth']['expose']['reduce'] = 1;
  $handler->display->display_options['filters']['term_node_tid_depth']['reduce_duplicates'] = 0;
  $handler->display->display_options['filters']['term_node_tid_depth']['type'] = 'select';
  $handler->display->display_options['filters']['term_node_tid_depth']['vocabulary'] = 'location';
  $handler->display->display_options['filters']['term_node_tid_depth']['hierarchy'] = 1;
  $handler->display->display_options['filters']['term_node_tid_depth']['error_message'] = 1;
  $handler->display->display_options['filters']['term_node_tid_depth']['depth'] = '10';
  /* Filter criterion: Category Filter */
  $handler->display->display_options['filters']['tid']['id'] = 'tid';
  $handler->display->display_options['filters']['tid']['table'] = 'taxonomy_index';
  $handler->display->display_options['filters']['tid']['field'] = 'tid';
  $handler->display->display_options['filters']['tid']['relationship'] = 'field_ref_collection_nid';
  $handler->display->display_options['filters']['tid']['ui_name'] = 'Category Filter';
  $handler->display->display_options['filters']['tid']['group'] = 1;
  $handler->display->display_options['filters']['tid']['exposed'] = TRUE;
  $handler->display->display_options['filters']['tid']['expose']['operator_id'] = 'tid_op';
  $handler->display->display_options['filters']['tid']['expose']['label'] = 'Category';
  $handler->display->display_options['filters']['tid']['expose']['operator'] = 'tid_op';
  $handler->display->display_options['filters']['tid']['expose']['identifier'] = 'category';
  $handler->display->display_options['filters']['tid']['expose']['multiple'] = 1;
  $handler->display->display_options['filters']['tid']['expose']['reduce'] = 0;
  $handler->display->display_options['filters']['tid']['reduce_duplicates'] = 1;
  $handler->display->display_options['filters']['tid']['type'] = 'select';
  $handler->display->display_options['filters']['tid']['vocabulary'] = 'tags';
  $handler->display->display_options['filters']['tid']['hierarchy'] = 1;
  $handler->display->display_options['filters']['tid']['error_message'] = 0;

  /* Display: Block */
  $handler = $view->new_display('block', 'Block', 'block_1');
  $handler->display->display_options['block_caching'] = '-1';
  $translatables['photo_grid'] = array(
    t('Master'),
    t('Photo Grid'),
    t('more'),
    t('Sort'),
    t('Reset'),
    t('Order By'),
    t('Asc'),
    t('Desc'),
    t('Items per page'),
    t('- All -'),
    t('Offset'),
    t('Parent Collection'),
    t('File'),
    t('<img src="/sites/all/themes/gazprom/images/blank.gif" data-original="[field_image]" width="240" height="240" class="lazyLoad" />'),
    t('<a href="[path]" imageSrc="[uri]">[field_image]</a>
<div class="photo-grid-tip">
  <div class="location">[field_location]</div>
  <div class="description">[field_photo_description]</div>
</div>'),
    t('None'),
    t('Date'),
    t('All'),
    t('Search'),
    t('Country'),
    t('Category'),
    t('Block'),
  );
  $export['photo_grid'] = $view;

  $view = new view;
  $view->name = 'photo_list';
  $view->description = '';
  $view->tag = 'photo';
  $view->base_table = 'node';
  $view->human_name = 'Photo Album List';
  $view->core = 7;
  $view->api_version = '3.0';
  $view->disabled = FALSE; /* Edit this to true to make a default view disabled initially */

  /* Display: Master */
  $handler = $view->new_display('default', 'Master', 'default');
  $handler->display->display_options['title'] = 'Photo Album List';
  $handler->display->display_options['use_ajax'] = TRUE;
  $handler->display->display_options['access']['type'] = 'perm';
  $handler->display->display_options['cache']['type'] = 'none';
  $handler->display->display_options['query']['type'] = 'views_query';
  $handler->display->display_options['query']['options']['distinct'] = TRUE;
  $handler->display->display_options['query']['options']['query_comment'] = FALSE;
  $handler->display->display_options['exposed_form']['type'] = 'better_exposed_filters';
  $handler->display->display_options['exposed_form']['options']['submit_button'] = 'Sort';
  $handler->display->display_options['exposed_form']['options']['autosubmit'] = 0;
  $handler->display->display_options['exposed_form']['options']['autosubmit_hide'] = 1;
  $handler->display->display_options['exposed_form']['options']['bef'] = array(
    'sort' => array(
      'bef_format' => 'bef',
      'combine' => 0,
      'reset' => 0,
      'reset_label' => '',
    ),
    'term_node_tid_depth' => array(
      'bef_format' => 'bef_ul',
      'more_options' => array(
        'bef_select_all_none' => 0,
        'bef_collapsible' => 0,
        'bef_filter_description' => '',
      ),
    ),
    'tid_1' => array(
      'bef_format' => 'bef_ul',
      'more_options' => array(
        'bef_select_all_none' => 0,
        'bef_collapsible' => 0,
        'bef_filter_description' => '',
      ),
    ),
  );
  $handler->display->display_options['pager']['type'] = 'none';
  $handler->display->display_options['pager']['options']['offset'] = '0';
  $handler->display->display_options['style_plugin'] = 'table';
  $handler->display->display_options['style_options']['columns'] = array(
    'nid' => 'nid',
    'view' => 'view',
    'title_field' => 'title_field',
    'field_location' => 'field_location',
    'field_category_tags' => 'field_category_tags',
    'field_date_event' => 'field_date_event',
  );
  $handler->display->display_options['style_options']['default'] = '-1';
  $handler->display->display_options['style_options']['info'] = array(
    'nid' => array(
      'sortable' => 0,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'view' => array(
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'title_field' => array(
      'sortable' => 0,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'field_location' => array(
      'sortable' => 0,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'field_category_tags' => array(
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'field_date_event' => array(
      'sortable' => 0,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
  );
  $handler->display->display_options['style_options']['override'] = 0;
  $handler->display->display_options['style_options']['sticky'] = 1;
  $handler->display->display_options['style_options']['empty_table'] = 1;
  /* Relationship: Country */
  $handler->display->display_options['relationships']['term_node_tid']['id'] = 'term_node_tid';
  $handler->display->display_options['relationships']['term_node_tid']['table'] = 'node';
  $handler->display->display_options['relationships']['term_node_tid']['field'] = 'term_node_tid';
  $handler->display->display_options['relationships']['term_node_tid']['ui_name'] = 'Country';
  $handler->display->display_options['relationships']['term_node_tid']['label'] = 'Country';
  $handler->display->display_options['relationships']['term_node_tid']['required'] = 0;
  $handler->display->display_options['relationships']['term_node_tid']['vocabularies'] = array(
    'location' => 'location',
    'tags' => 0,
    'staff_type' => 0,
  );
  /* Relationship: Content: Part of Collection (field_ref_collection) - reverse */
  $handler->display->display_options['relationships']['reverse_field_ref_collection_node']['id'] = 'reverse_field_ref_collection_node';
  $handler->display->display_options['relationships']['reverse_field_ref_collection_node']['table'] = 'node';
  $handler->display->display_options['relationships']['reverse_field_ref_collection_node']['field'] = 'reverse_field_ref_collection_node';
  $handler->display->display_options['relationships']['reverse_field_ref_collection_node']['label'] = 'member_photos';
  $handler->display->display_options['relationships']['reverse_field_ref_collection_node']['required'] = 0;
  /* Field: Content: Nid */
  $handler->display->display_options['fields']['nid']['id'] = 'nid';
  $handler->display->display_options['fields']['nid']['table'] = 'node';
  $handler->display->display_options['fields']['nid']['field'] = 'nid';
  $handler->display->display_options['fields']['nid']['exclude'] = TRUE;
  $handler->display->display_options['fields']['nid']['alter']['alter_text'] = 0;
  $handler->display->display_options['fields']['nid']['alter']['make_link'] = 0;
  $handler->display->display_options['fields']['nid']['alter']['absolute'] = 0;
  $handler->display->display_options['fields']['nid']['alter']['external'] = 0;
  $handler->display->display_options['fields']['nid']['alter']['replace_spaces'] = 0;
  $handler->display->display_options['fields']['nid']['alter']['trim_whitespace'] = 0;
  $handler->display->display_options['fields']['nid']['alter']['nl2br'] = 0;
  $handler->display->display_options['fields']['nid']['alter']['word_boundary'] = 1;
  $handler->display->display_options['fields']['nid']['alter']['ellipsis'] = 1;
  $handler->display->display_options['fields']['nid']['alter']['strip_tags'] = 0;
  $handler->display->display_options['fields']['nid']['alter']['trim'] = 0;
  $handler->display->display_options['fields']['nid']['alter']['html'] = 0;
  $handler->display->display_options['fields']['nid']['element_label_colon'] = 1;
  $handler->display->display_options['fields']['nid']['element_default_classes'] = 1;
  $handler->display->display_options['fields']['nid']['hide_empty'] = 0;
  $handler->display->display_options['fields']['nid']['empty_zero'] = 0;
  $handler->display->display_options['fields']['nid']['hide_alter_empty'] = 1;
  $handler->display->display_options['fields']['nid']['link_to_node'] = 0;
  /* Field: Topmost Image from Collection */
  $handler->display->display_options['fields']['view']['id'] = 'view';
  $handler->display->display_options['fields']['view']['table'] = 'views';
  $handler->display->display_options['fields']['view']['field'] = 'view';
  $handler->display->display_options['fields']['view']['ui_name'] = 'Topmost Image from Collection';
  $handler->display->display_options['fields']['view']['label'] = '';
  $handler->display->display_options['fields']['view']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['view']['element_default_classes'] = 1;
  $handler->display->display_options['fields']['view']['hide_empty'] = 0;
  $handler->display->display_options['fields']['view']['empty_zero'] = 0;
  $handler->display->display_options['fields']['view']['hide_alter_empty'] = 1;
  $handler->display->display_options['fields']['view']['view'] = 'collection_topmost';
  $handler->display->display_options['fields']['view']['display'] = 'block_1';
  $handler->display->display_options['fields']['view']['arguments'] = '[nid]';
  $handler->display->display_options['fields']['view']['query_aggregation'] = 0;
  /* Field: Content: Collection Name */
  $handler->display->display_options['fields']['title_field']['id'] = 'title_field';
  $handler->display->display_options['fields']['title_field']['table'] = 'field_data_title_field';
  $handler->display->display_options['fields']['title_field']['field'] = 'title_field';
  $handler->display->display_options['fields']['title_field']['label'] = 'Name';
  $handler->display->display_options['fields']['title_field']['alter']['alter_text'] = 0;
  $handler->display->display_options['fields']['title_field']['alter']['make_link'] = 0;
  $handler->display->display_options['fields']['title_field']['alter']['absolute'] = 0;
  $handler->display->display_options['fields']['title_field']['alter']['external'] = 0;
  $handler->display->display_options['fields']['title_field']['alter']['replace_spaces'] = 0;
  $handler->display->display_options['fields']['title_field']['alter']['trim_whitespace'] = 0;
  $handler->display->display_options['fields']['title_field']['alter']['nl2br'] = 0;
  $handler->display->display_options['fields']['title_field']['alter']['word_boundary'] = 1;
  $handler->display->display_options['fields']['title_field']['alter']['ellipsis'] = 1;
  $handler->display->display_options['fields']['title_field']['alter']['more_link'] = 0;
  $handler->display->display_options['fields']['title_field']['alter']['strip_tags'] = 0;
  $handler->display->display_options['fields']['title_field']['alter']['trim'] = 0;
  $handler->display->display_options['fields']['title_field']['alter']['html'] = 0;
  $handler->display->display_options['fields']['title_field']['element_label_colon'] = 0;
  $handler->display->display_options['fields']['title_field']['element_default_classes'] = 1;
  $handler->display->display_options['fields']['title_field']['hide_empty'] = 0;
  $handler->display->display_options['fields']['title_field']['empty_zero'] = 0;
  $handler->display->display_options['fields']['title_field']['hide_alter_empty'] = 1;
  $handler->display->display_options['fields']['title_field']['field_api_classes'] = 0;
  /* Field: Content: Related to Location */
  $handler->display->display_options['fields']['field_location']['id'] = 'field_location';
  $handler->display->display_options['fields']['field_location']['table'] = 'field_data_field_location';
  $handler->display->display_options['fields']['field_location']['field'] = 'field_location';
  $handler->display->display_options['fields']['field_location']['label'] = 'Country';
  $handler->display->display_options['fields']['field_location']['alter']['alter_text'] = 0;
  $handler->display->display_options['fields']['field_location']['alter']['make_link'] = 0;
  $handler->display->display_options['fields']['field_location']['alter']['absolute'] = 0;
  $handler->display->display_options['fields']['field_location']['alter']['external'] = 0;
  $handler->display->display_options['fields']['field_location']['alter']['replace_spaces'] = 0;
  $handler->display->display_options['fields']['field_location']['alter']['trim_whitespace'] = 0;
  $handler->display->display_options['fields']['field_location']['alter']['nl2br'] = 0;
  $handler->display->display_options['fields']['field_location']['alter']['word_boundary'] = 1;
  $handler->display->display_options['fields']['field_location']['alter']['ellipsis'] = 1;
  $handler->display->display_options['fields']['field_location']['alter']['strip_tags'] = 0;
  $handler->display->display_options['fields']['field_location']['alter']['trim'] = 0;
  $handler->display->display_options['fields']['field_location']['alter']['html'] = 0;
  $handler->display->display_options['fields']['field_location']['element_label_colon'] = 1;
  $handler->display->display_options['fields']['field_location']['element_default_classes'] = 1;
  $handler->display->display_options['fields']['field_location']['hide_empty'] = 0;
  $handler->display->display_options['fields']['field_location']['empty_zero'] = 0;
  $handler->display->display_options['fields']['field_location']['hide_alter_empty'] = 1;
  $handler->display->display_options['fields']['field_location']['type'] = 'i18n_taxonomy_term_reference_plain';
  $handler->display->display_options['fields']['field_location']['group_rows'] = 1;
  $handler->display->display_options['fields']['field_location']['delta_limit'] = '1';
  $handler->display->display_options['fields']['field_location']['delta_offset'] = '0';
  $handler->display->display_options['fields']['field_location']['delta_reversed'] = 1;
  $handler->display->display_options['fields']['field_location']['delta_first_last'] = 0;
  $handler->display->display_options['fields']['field_location']['field_api_classes'] = 0;
  /* Field: Content: Category Tags */
  $handler->display->display_options['fields']['field_category_tags']['id'] = 'field_category_tags';
  $handler->display->display_options['fields']['field_category_tags']['table'] = 'field_data_field_category_tags';
  $handler->display->display_options['fields']['field_category_tags']['field'] = 'field_category_tags';
  $handler->display->display_options['fields']['field_category_tags']['label'] = 'Categories';
  $handler->display->display_options['fields']['field_category_tags']['alter']['alter_text'] = 0;
  $handler->display->display_options['fields']['field_category_tags']['alter']['make_link'] = 0;
  $handler->display->display_options['fields']['field_category_tags']['alter']['absolute'] = 0;
  $handler->display->display_options['fields']['field_category_tags']['alter']['external'] = 0;
  $handler->display->display_options['fields']['field_category_tags']['alter']['replace_spaces'] = 0;
  $handler->display->display_options['fields']['field_category_tags']['alter']['trim_whitespace'] = 0;
  $handler->display->display_options['fields']['field_category_tags']['alter']['nl2br'] = 0;
  $handler->display->display_options['fields']['field_category_tags']['alter']['word_boundary'] = 1;
  $handler->display->display_options['fields']['field_category_tags']['alter']['ellipsis'] = 1;
  $handler->display->display_options['fields']['field_category_tags']['alter']['strip_tags'] = 0;
  $handler->display->display_options['fields']['field_category_tags']['alter']['trim'] = 0;
  $handler->display->display_options['fields']['field_category_tags']['alter']['html'] = 0;
  $handler->display->display_options['fields']['field_category_tags']['element_label_colon'] = 1;
  $handler->display->display_options['fields']['field_category_tags']['element_default_classes'] = 1;
  $handler->display->display_options['fields']['field_category_tags']['hide_empty'] = 0;
  $handler->display->display_options['fields']['field_category_tags']['empty_zero'] = 0;
  $handler->display->display_options['fields']['field_category_tags']['hide_alter_empty'] = 1;
  $handler->display->display_options['fields']['field_category_tags']['type'] = 'i18n_taxonomy_term_reference_plain';
  $handler->display->display_options['fields']['field_category_tags']['group_rows'] = 1;
  $handler->display->display_options['fields']['field_category_tags']['delta_offset'] = '0';
  $handler->display->display_options['fields']['field_category_tags']['delta_reversed'] = 0;
  $handler->display->display_options['fields']['field_category_tags']['delta_first_last'] = 0;
  $handler->display->display_options['fields']['field_category_tags']['field_api_classes'] = 0;
  /* Field: Set Date */
  $handler->display->display_options['fields']['field_date_event']['id'] = 'field_date_event';
  $handler->display->display_options['fields']['field_date_event']['table'] = 'field_data_field_date_event';
  $handler->display->display_options['fields']['field_date_event']['field'] = 'field_date_event';
  $handler->display->display_options['fields']['field_date_event']['ui_name'] = 'Set Date';
  $handler->display->display_options['fields']['field_date_event']['label'] = 'Date';
  $handler->display->display_options['fields']['field_date_event']['alter']['alter_text'] = 0;
  $handler->display->display_options['fields']['field_date_event']['alter']['make_link'] = 0;
  $handler->display->display_options['fields']['field_date_event']['alter']['absolute'] = 0;
  $handler->display->display_options['fields']['field_date_event']['alter']['external'] = 0;
  $handler->display->display_options['fields']['field_date_event']['alter']['replace_spaces'] = 0;
  $handler->display->display_options['fields']['field_date_event']['alter']['trim_whitespace'] = 0;
  $handler->display->display_options['fields']['field_date_event']['alter']['nl2br'] = 0;
  $handler->display->display_options['fields']['field_date_event']['alter']['word_boundary'] = 1;
  $handler->display->display_options['fields']['field_date_event']['alter']['ellipsis'] = 1;
  $handler->display->display_options['fields']['field_date_event']['alter']['strip_tags'] = 0;
  $handler->display->display_options['fields']['field_date_event']['alter']['trim'] = 0;
  $handler->display->display_options['fields']['field_date_event']['alter']['html'] = 0;
  $handler->display->display_options['fields']['field_date_event']['element_label_colon'] = 1;
  $handler->display->display_options['fields']['field_date_event']['element_default_classes'] = 1;
  $handler->display->display_options['fields']['field_date_event']['hide_empty'] = 0;
  $handler->display->display_options['fields']['field_date_event']['empty_zero'] = 0;
  $handler->display->display_options['fields']['field_date_event']['hide_alter_empty'] = 1;
  $handler->display->display_options['fields']['field_date_event']['settings'] = array(
    'format_type' => 'simple',
    'fromto' => 'both',
    'multiple_number' => '',
    'multiple_from' => '',
    'multiple_to' => '',
    'show_repeat_rule' => 'show',
  );
  $handler->display->display_options['fields']['field_date_event']['field_api_classes'] = 0;
  /* Sort criterion: Set Date */
  $handler->display->display_options['sorts']['field_date_event_value']['id'] = 'field_date_event_value';
  $handler->display->display_options['sorts']['field_date_event_value']['table'] = 'field_data_field_date_event';
  $handler->display->display_options['sorts']['field_date_event_value']['field'] = 'field_date_event_value';
  $handler->display->display_options['sorts']['field_date_event_value']['ui_name'] = 'Set Date';
  $handler->display->display_options['sorts']['field_date_event_value']['order'] = 'DESC';
  $handler->display->display_options['sorts']['field_date_event_value']['exposed'] = TRUE;
  $handler->display->display_options['sorts']['field_date_event_value']['expose']['label'] = 'Date Released (field_date_event)';
  /* Sort criterion: Content: Title */
  $handler->display->display_options['sorts']['title']['id'] = 'title';
  $handler->display->display_options['sorts']['title']['table'] = 'node';
  $handler->display->display_options['sorts']['title']['field'] = 'title';
  $handler->display->display_options['sorts']['title']['exposed'] = TRUE;
  $handler->display->display_options['sorts']['title']['expose']['label'] = 'Name';
  /* Sort criterion: Taxonomy term: Name */
  $handler->display->display_options['sorts']['name']['id'] = 'name';
  $handler->display->display_options['sorts']['name']['table'] = 'taxonomy_term_data';
  $handler->display->display_options['sorts']['name']['field'] = 'name';
  $handler->display->display_options['sorts']['name']['relationship'] = 'term_node_tid';
  $handler->display->display_options['sorts']['name']['exposed'] = TRUE;
  $handler->display->display_options['sorts']['name']['expose']['label'] = 'Country';
  /* Filter criterion: Content: Published */
  $handler->display->display_options['filters']['status']['id'] = 'status';
  $handler->display->display_options['filters']['status']['table'] = 'node';
  $handler->display->display_options['filters']['status']['field'] = 'status';
  $handler->display->display_options['filters']['status']['value'] = 1;
  $handler->display->display_options['filters']['status']['group'] = 1;
  $handler->display->display_options['filters']['status']['expose']['operator'] = FALSE;
  /* Filter criterion: Content: Type */
  $handler->display->display_options['filters']['type']['id'] = 'type';
  $handler->display->display_options['filters']['type']['table'] = 'node';
  $handler->display->display_options['filters']['type']['field'] = 'type';
  $handler->display->display_options['filters']['type']['value'] = array(
    'media_collection' => 'media_collection',
  );
  $handler->display->display_options['filters']['type']['group'] = 1;
  /* Filter criterion: Content: Hide from Gallery (field_gallery_hidden) */
  $handler->display->display_options['filters']['field_gallery_hidden_value']['id'] = 'field_gallery_hidden_value';
  $handler->display->display_options['filters']['field_gallery_hidden_value']['table'] = 'field_data_field_gallery_hidden';
  $handler->display->display_options['filters']['field_gallery_hidden_value']['field'] = 'field_gallery_hidden_value';
  $handler->display->display_options['filters']['field_gallery_hidden_value']['operator'] = 'not in';
  $handler->display->display_options['filters']['field_gallery_hidden_value']['value'] = array(
    1 => '1',
  );
  $handler->display->display_options['filters']['field_gallery_hidden_value']['group'] = 1;
  /* Filter criterion: Search: Search Terms */
  $handler->display->display_options['filters']['keys']['id'] = 'keys';
  $handler->display->display_options['filters']['keys']['table'] = 'search_index';
  $handler->display->display_options['filters']['keys']['field'] = 'keys';
  $handler->display->display_options['filters']['keys']['relationship'] = 'reverse_field_ref_collection_node';
  $handler->display->display_options['filters']['keys']['group'] = 1;
  $handler->display->display_options['filters']['keys']['exposed'] = TRUE;
  $handler->display->display_options['filters']['keys']['expose']['operator_id'] = 'keys_op';
  $handler->display->display_options['filters']['keys']['expose']['label'] = 'Search';
  $handler->display->display_options['filters']['keys']['expose']['operator'] = 'keys_op';
  $handler->display->display_options['filters']['keys']['expose']['identifier'] = 'keys';
  $handler->display->display_options['filters']['keys']['expose']['multiple'] = FALSE;
  /* Filter criterion: Country Filter */
  $handler->display->display_options['filters']['term_node_tid_depth']['id'] = 'term_node_tid_depth';
  $handler->display->display_options['filters']['term_node_tid_depth']['table'] = 'node';
  $handler->display->display_options['filters']['term_node_tid_depth']['field'] = 'term_node_tid_depth';
  $handler->display->display_options['filters']['term_node_tid_depth']['ui_name'] = 'Country Filter';
  $handler->display->display_options['filters']['term_node_tid_depth']['value'] = array(
    6 => '6',
    13 => '13',
    14 => '14',
    17 => '17',
    22 => '22',
    40 => '40',
    20 => '20',
    44 => '44',
    43 => '43',
    21 => '21',
    7 => '7',
    19 => '19',
    15 => '15',
    16 => '16',
    18 => '18',
    5 => '5',
    11 => '11',
    47 => '47',
    10 => '10',
    48 => '48',
  );
  $handler->display->display_options['filters']['term_node_tid_depth']['group'] = 1;
  $handler->display->display_options['filters']['term_node_tid_depth']['exposed'] = TRUE;
  $handler->display->display_options['filters']['term_node_tid_depth']['expose']['operator_id'] = 'term_node_tid_depth_op';
  $handler->display->display_options['filters']['term_node_tid_depth']['expose']['label'] = 'Country';
  $handler->display->display_options['filters']['term_node_tid_depth']['expose']['operator'] = 'term_node_tid_depth_op';
  $handler->display->display_options['filters']['term_node_tid_depth']['expose']['identifier'] = 'country';
  $handler->display->display_options['filters']['term_node_tid_depth']['expose']['multiple'] = 1;
  $handler->display->display_options['filters']['term_node_tid_depth']['expose']['reduce'] = 1;
  $handler->display->display_options['filters']['term_node_tid_depth']['reduce_duplicates'] = 1;
  $handler->display->display_options['filters']['term_node_tid_depth']['type'] = 'select';
  $handler->display->display_options['filters']['term_node_tid_depth']['vocabulary'] = 'location';
  $handler->display->display_options['filters']['term_node_tid_depth']['hierarchy'] = 1;
  $handler->display->display_options['filters']['term_node_tid_depth']['error_message'] = 1;
  $handler->display->display_options['filters']['term_node_tid_depth']['depth'] = '10';
  /* Filter criterion: Category Filter */
  $handler->display->display_options['filters']['tid_1']['id'] = 'tid_1';
  $handler->display->display_options['filters']['tid_1']['table'] = 'taxonomy_index';
  $handler->display->display_options['filters']['tid_1']['field'] = 'tid';
  $handler->display->display_options['filters']['tid_1']['ui_name'] = 'Category Filter';
  $handler->display->display_options['filters']['tid_1']['group'] = 1;
  $handler->display->display_options['filters']['tid_1']['exposed'] = TRUE;
  $handler->display->display_options['filters']['tid_1']['expose']['operator_id'] = 'tid_1_op';
  $handler->display->display_options['filters']['tid_1']['expose']['label'] = 'Category';
  $handler->display->display_options['filters']['tid_1']['expose']['operator'] = 'tid_1_op';
  $handler->display->display_options['filters']['tid_1']['expose']['identifier'] = 'category';
  $handler->display->display_options['filters']['tid_1']['expose']['multiple'] = 1;
  $handler->display->display_options['filters']['tid_1']['expose']['reduce'] = 0;
  $handler->display->display_options['filters']['tid_1']['reduce_duplicates'] = 1;
  $handler->display->display_options['filters']['tid_1']['type'] = 'select';
  $handler->display->display_options['filters']['tid_1']['vocabulary'] = 'tags';
  $handler->display->display_options['filters']['tid_1']['hierarchy'] = 1;
  $handler->display->display_options['filters']['tid_1']['error_message'] = 1;

  /* Display: Block */
  $handler = $view->new_display('block', 'Block', 'block');
  $handler->display->display_options['defaults']['sorts'] = FALSE;
  /* Sort criterion: Album Date */
  $handler->display->display_options['sorts']['field_date_event_value']['id'] = 'field_date_event_value';
  $handler->display->display_options['sorts']['field_date_event_value']['table'] = 'field_data_field_date_event';
  $handler->display->display_options['sorts']['field_date_event_value']['field'] = 'field_date_event_value';
  $handler->display->display_options['sorts']['field_date_event_value']['ui_name'] = 'Album Date';
  $handler->display->display_options['sorts']['field_date_event_value']['order'] = 'DESC';
  $handler->display->display_options['sorts']['field_date_event_value']['exposed'] = TRUE;
  $handler->display->display_options['sorts']['field_date_event_value']['expose']['label'] = 'Date';
  /* Sort criterion: Content: Title */
  $handler->display->display_options['sorts']['title']['id'] = 'title';
  $handler->display->display_options['sorts']['title']['table'] = 'node';
  $handler->display->display_options['sorts']['title']['field'] = 'title';
  $handler->display->display_options['sorts']['title']['exposed'] = TRUE;
  $handler->display->display_options['sorts']['title']['expose']['label'] = 'Name';
  /* Sort criterion: Taxonomy term: Name */
  $handler->display->display_options['sorts']['name']['id'] = 'name';
  $handler->display->display_options['sorts']['name']['table'] = 'taxonomy_term_data';
  $handler->display->display_options['sorts']['name']['field'] = 'name';
  $handler->display->display_options['sorts']['name']['relationship'] = 'term_node_tid';
  $handler->display->display_options['sorts']['name']['exposed'] = TRUE;
  $handler->display->display_options['sorts']['name']['expose']['label'] = 'Country';

  /* Display: Block: Mobile */
  $handler = $view->new_display('block', 'Block: Mobile', 'mobile');
  $handler->display->display_options['defaults']['use_ajax'] = FALSE;
  $handler->display->display_options['defaults']['exposed_form'] = FALSE;
  $handler->display->display_options['exposed_form']['type'] = 'basic';
  $handler->display->display_options['exposed_form']['options']['autosubmit'] = 0;
  $handler->display->display_options['exposed_form']['options']['autosubmit_hide'] = 1;
  $handler->display->display_options['defaults']['style_plugin'] = FALSE;
  $handler->display->display_options['style_plugin'] = 'table';
  $handler->display->display_options['style_options']['columns'] = array(
    'nid' => 'nid',
    'view' => 'view',
    'title_field' => 'title_field',
    'field_location' => 'field_location',
    'field_category_tags' => 'field_category_tags',
    'field_date_event' => 'field_date_event',
  );
  $handler->display->display_options['style_options']['default'] = 'title_field';
  $handler->display->display_options['style_options']['info'] = array(
    'nid' => array(
      'sortable' => 0,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 1,
    ),
    'view' => array(
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'title_field' => array(
      'sortable' => 1,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'field_location' => array(
      'sortable' => 1,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'field_category_tags' => array(
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'field_date_event' => array(
      'sortable' => 1,
      'default_sort_order' => 'desc',
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
  $handler->display->display_options['defaults']['relationships'] = FALSE;
  /* Relationship: Country */
  $handler->display->display_options['relationships']['term_node_tid']['id'] = 'term_node_tid';
  $handler->display->display_options['relationships']['term_node_tid']['table'] = 'node';
  $handler->display->display_options['relationships']['term_node_tid']['field'] = 'term_node_tid';
  $handler->display->display_options['relationships']['term_node_tid']['ui_name'] = 'Country';
  $handler->display->display_options['relationships']['term_node_tid']['label'] = 'Country';
  $handler->display->display_options['relationships']['term_node_tid']['required'] = 0;
  $handler->display->display_options['relationships']['term_node_tid']['vocabularies'] = array(
    'location' => 'location',
    'tags' => 0,
    'staff_type' => 0,
  );
  $handler->display->display_options['defaults']['fields'] = FALSE;
  /* Field: Content: Nid */
  $handler->display->display_options['fields']['nid']['id'] = 'nid';
  $handler->display->display_options['fields']['nid']['table'] = 'node';
  $handler->display->display_options['fields']['nid']['field'] = 'nid';
  $handler->display->display_options['fields']['nid']['exclude'] = TRUE;
  $handler->display->display_options['fields']['nid']['alter']['alter_text'] = 0;
  $handler->display->display_options['fields']['nid']['alter']['make_link'] = 0;
  $handler->display->display_options['fields']['nid']['alter']['absolute'] = 0;
  $handler->display->display_options['fields']['nid']['alter']['external'] = 0;
  $handler->display->display_options['fields']['nid']['alter']['replace_spaces'] = 0;
  $handler->display->display_options['fields']['nid']['alter']['trim_whitespace'] = 0;
  $handler->display->display_options['fields']['nid']['alter']['nl2br'] = 0;
  $handler->display->display_options['fields']['nid']['alter']['word_boundary'] = 1;
  $handler->display->display_options['fields']['nid']['alter']['ellipsis'] = 1;
  $handler->display->display_options['fields']['nid']['alter']['strip_tags'] = 0;
  $handler->display->display_options['fields']['nid']['alter']['trim'] = 0;
  $handler->display->display_options['fields']['nid']['alter']['html'] = 0;
  $handler->display->display_options['fields']['nid']['element_label_colon'] = 1;
  $handler->display->display_options['fields']['nid']['element_default_classes'] = 1;
  $handler->display->display_options['fields']['nid']['hide_empty'] = 0;
  $handler->display->display_options['fields']['nid']['empty_zero'] = 0;
  $handler->display->display_options['fields']['nid']['hide_alter_empty'] = 1;
  $handler->display->display_options['fields']['nid']['link_to_node'] = 0;
  /* Field: Topmost Image from Collection */
  $handler->display->display_options['fields']['view']['id'] = 'view';
  $handler->display->display_options['fields']['view']['table'] = 'views';
  $handler->display->display_options['fields']['view']['field'] = 'view';
  $handler->display->display_options['fields']['view']['ui_name'] = 'Topmost Image from Collection';
  $handler->display->display_options['fields']['view']['label'] = '';
  $handler->display->display_options['fields']['view']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['view']['element_default_classes'] = 1;
  $handler->display->display_options['fields']['view']['hide_empty'] = 0;
  $handler->display->display_options['fields']['view']['empty_zero'] = 0;
  $handler->display->display_options['fields']['view']['hide_alter_empty'] = 1;
  $handler->display->display_options['fields']['view']['view'] = 'collection_topmost';
  $handler->display->display_options['fields']['view']['display'] = 'block_1';
  $handler->display->display_options['fields']['view']['arguments'] = '[nid]';
  $handler->display->display_options['fields']['view']['query_aggregation'] = 0;
  /* Field: Content: Collection Name */
  $handler->display->display_options['fields']['title_field']['id'] = 'title_field';
  $handler->display->display_options['fields']['title_field']['table'] = 'field_data_title_field';
  $handler->display->display_options['fields']['title_field']['field'] = 'title_field';
  $handler->display->display_options['fields']['title_field']['label'] = 'Name';
  $handler->display->display_options['fields']['title_field']['alter']['alter_text'] = 0;
  $handler->display->display_options['fields']['title_field']['alter']['make_link'] = 0;
  $handler->display->display_options['fields']['title_field']['alter']['absolute'] = 0;
  $handler->display->display_options['fields']['title_field']['alter']['external'] = 0;
  $handler->display->display_options['fields']['title_field']['alter']['replace_spaces'] = 0;
  $handler->display->display_options['fields']['title_field']['alter']['trim_whitespace'] = 0;
  $handler->display->display_options['fields']['title_field']['alter']['nl2br'] = 0;
  $handler->display->display_options['fields']['title_field']['alter']['word_boundary'] = 1;
  $handler->display->display_options['fields']['title_field']['alter']['ellipsis'] = 1;
  $handler->display->display_options['fields']['title_field']['alter']['more_link'] = 0;
  $handler->display->display_options['fields']['title_field']['alter']['strip_tags'] = 0;
  $handler->display->display_options['fields']['title_field']['alter']['trim'] = 0;
  $handler->display->display_options['fields']['title_field']['alter']['html'] = 0;
  $handler->display->display_options['fields']['title_field']['element_label_colon'] = 0;
  $handler->display->display_options['fields']['title_field']['element_default_classes'] = 1;
  $handler->display->display_options['fields']['title_field']['hide_empty'] = 0;
  $handler->display->display_options['fields']['title_field']['empty_zero'] = 0;
  $handler->display->display_options['fields']['title_field']['hide_alter_empty'] = 1;
  $handler->display->display_options['fields']['title_field']['field_api_classes'] = 0;
  /* Field: Content: Related to Location */
  $handler->display->display_options['fields']['field_location']['id'] = 'field_location';
  $handler->display->display_options['fields']['field_location']['table'] = 'field_data_field_location';
  $handler->display->display_options['fields']['field_location']['field'] = 'field_location';
  $handler->display->display_options['fields']['field_location']['label'] = 'Country';
  $handler->display->display_options['fields']['field_location']['alter']['alter_text'] = 0;
  $handler->display->display_options['fields']['field_location']['alter']['make_link'] = 0;
  $handler->display->display_options['fields']['field_location']['alter']['absolute'] = 0;
  $handler->display->display_options['fields']['field_location']['alter']['external'] = 0;
  $handler->display->display_options['fields']['field_location']['alter']['replace_spaces'] = 0;
  $handler->display->display_options['fields']['field_location']['alter']['trim_whitespace'] = 0;
  $handler->display->display_options['fields']['field_location']['alter']['nl2br'] = 0;
  $handler->display->display_options['fields']['field_location']['alter']['word_boundary'] = 1;
  $handler->display->display_options['fields']['field_location']['alter']['ellipsis'] = 1;
  $handler->display->display_options['fields']['field_location']['alter']['strip_tags'] = 0;
  $handler->display->display_options['fields']['field_location']['alter']['trim'] = 0;
  $handler->display->display_options['fields']['field_location']['alter']['html'] = 0;
  $handler->display->display_options['fields']['field_location']['element_label_colon'] = 1;
  $handler->display->display_options['fields']['field_location']['element_default_classes'] = 1;
  $handler->display->display_options['fields']['field_location']['hide_empty'] = 0;
  $handler->display->display_options['fields']['field_location']['empty_zero'] = 0;
  $handler->display->display_options['fields']['field_location']['hide_alter_empty'] = 1;
  $handler->display->display_options['fields']['field_location']['type'] = 'i18n_taxonomy_term_reference_plain';
  $handler->display->display_options['fields']['field_location']['group_rows'] = 1;
  $handler->display->display_options['fields']['field_location']['delta_limit'] = '1';
  $handler->display->display_options['fields']['field_location']['delta_offset'] = '0';
  $handler->display->display_options['fields']['field_location']['delta_reversed'] = 1;
  $handler->display->display_options['fields']['field_location']['delta_first_last'] = 0;
  $handler->display->display_options['fields']['field_location']['field_api_classes'] = 0;
  /* Field: Content: Category Tags */
  $handler->display->display_options['fields']['field_category_tags']['id'] = 'field_category_tags';
  $handler->display->display_options['fields']['field_category_tags']['table'] = 'field_data_field_category_tags';
  $handler->display->display_options['fields']['field_category_tags']['field'] = 'field_category_tags';
  $handler->display->display_options['fields']['field_category_tags']['label'] = 'Categories';
  $handler->display->display_options['fields']['field_category_tags']['alter']['alter_text'] = 0;
  $handler->display->display_options['fields']['field_category_tags']['alter']['make_link'] = 0;
  $handler->display->display_options['fields']['field_category_tags']['alter']['absolute'] = 0;
  $handler->display->display_options['fields']['field_category_tags']['alter']['external'] = 0;
  $handler->display->display_options['fields']['field_category_tags']['alter']['replace_spaces'] = 0;
  $handler->display->display_options['fields']['field_category_tags']['alter']['trim_whitespace'] = 0;
  $handler->display->display_options['fields']['field_category_tags']['alter']['nl2br'] = 0;
  $handler->display->display_options['fields']['field_category_tags']['alter']['word_boundary'] = 1;
  $handler->display->display_options['fields']['field_category_tags']['alter']['ellipsis'] = 1;
  $handler->display->display_options['fields']['field_category_tags']['alter']['strip_tags'] = 0;
  $handler->display->display_options['fields']['field_category_tags']['alter']['trim'] = 0;
  $handler->display->display_options['fields']['field_category_tags']['alter']['html'] = 0;
  $handler->display->display_options['fields']['field_category_tags']['element_label_colon'] = 1;
  $handler->display->display_options['fields']['field_category_tags']['element_default_classes'] = 1;
  $handler->display->display_options['fields']['field_category_tags']['hide_empty'] = 0;
  $handler->display->display_options['fields']['field_category_tags']['empty_zero'] = 0;
  $handler->display->display_options['fields']['field_category_tags']['hide_alter_empty'] = 1;
  $handler->display->display_options['fields']['field_category_tags']['type'] = 'i18n_taxonomy_term_reference_plain';
  $handler->display->display_options['fields']['field_category_tags']['group_rows'] = 1;
  $handler->display->display_options['fields']['field_category_tags']['delta_offset'] = '0';
  $handler->display->display_options['fields']['field_category_tags']['delta_reversed'] = 0;
  $handler->display->display_options['fields']['field_category_tags']['delta_first_last'] = 0;
  $handler->display->display_options['fields']['field_category_tags']['field_api_classes'] = 0;
  /* Field: Set Date */
  $handler->display->display_options['fields']['field_date_event']['id'] = 'field_date_event';
  $handler->display->display_options['fields']['field_date_event']['table'] = 'field_data_field_date_event';
  $handler->display->display_options['fields']['field_date_event']['field'] = 'field_date_event';
  $handler->display->display_options['fields']['field_date_event']['ui_name'] = 'Set Date';
  $handler->display->display_options['fields']['field_date_event']['label'] = 'Date';
  $handler->display->display_options['fields']['field_date_event']['alter']['alter_text'] = 0;
  $handler->display->display_options['fields']['field_date_event']['alter']['make_link'] = 0;
  $handler->display->display_options['fields']['field_date_event']['alter']['absolute'] = 0;
  $handler->display->display_options['fields']['field_date_event']['alter']['external'] = 0;
  $handler->display->display_options['fields']['field_date_event']['alter']['replace_spaces'] = 0;
  $handler->display->display_options['fields']['field_date_event']['alter']['trim_whitespace'] = 0;
  $handler->display->display_options['fields']['field_date_event']['alter']['nl2br'] = 0;
  $handler->display->display_options['fields']['field_date_event']['alter']['word_boundary'] = 1;
  $handler->display->display_options['fields']['field_date_event']['alter']['ellipsis'] = 1;
  $handler->display->display_options['fields']['field_date_event']['alter']['more_link'] = 0;
  $handler->display->display_options['fields']['field_date_event']['alter']['strip_tags'] = 0;
  $handler->display->display_options['fields']['field_date_event']['alter']['trim'] = 0;
  $handler->display->display_options['fields']['field_date_event']['alter']['html'] = 0;
  $handler->display->display_options['fields']['field_date_event']['element_label_colon'] = 1;
  $handler->display->display_options['fields']['field_date_event']['element_default_classes'] = 1;
  $handler->display->display_options['fields']['field_date_event']['hide_empty'] = 0;
  $handler->display->display_options['fields']['field_date_event']['empty_zero'] = 0;
  $handler->display->display_options['fields']['field_date_event']['hide_alter_empty'] = 1;
  $handler->display->display_options['fields']['field_date_event']['settings'] = array(
    'format_type' => 'short_simple',
    'fromto' => 'both',
    'multiple_number' => '',
    'multiple_from' => '',
    'multiple_to' => '',
  );
  $handler->display->display_options['fields']['field_date_event']['field_api_classes'] = 0;
  $handler->display->display_options['defaults']['sorts'] = FALSE;
  /* Sort criterion: Set Date */
  $handler->display->display_options['sorts']['field_date_event_value']['id'] = 'field_date_event_value';
  $handler->display->display_options['sorts']['field_date_event_value']['table'] = 'field_data_field_date_event';
  $handler->display->display_options['sorts']['field_date_event_value']['field'] = 'field_date_event_value';
  $handler->display->display_options['sorts']['field_date_event_value']['ui_name'] = 'Set Date';
  $handler->display->display_options['sorts']['field_date_event_value']['order'] = 'DESC';
  $handler->display->display_options['sorts']['field_date_event_value']['expose']['label'] = 'Date';
  /* Sort criterion: Content: Title */
  $handler->display->display_options['sorts']['title']['id'] = 'title';
  $handler->display->display_options['sorts']['title']['table'] = 'node';
  $handler->display->display_options['sorts']['title']['field'] = 'title';
  $handler->display->display_options['sorts']['title']['expose']['label'] = 'Name';
  $handler->display->display_options['defaults']['filters'] = FALSE;
  /* Filter criterion: Content: Published */
  $handler->display->display_options['filters']['status']['id'] = 'status';
  $handler->display->display_options['filters']['status']['table'] = 'node';
  $handler->display->display_options['filters']['status']['field'] = 'status';
  $handler->display->display_options['filters']['status']['value'] = 1;
  $handler->display->display_options['filters']['status']['group'] = 0;
  $handler->display->display_options['filters']['status']['expose']['operator'] = FALSE;
  /* Filter criterion: Content: Type */
  $handler->display->display_options['filters']['type']['id'] = 'type';
  $handler->display->display_options['filters']['type']['table'] = 'node';
  $handler->display->display_options['filters']['type']['field'] = 'type';
  $handler->display->display_options['filters']['type']['value'] = array(
    'media_collection' => 'media_collection',
  );
  $handler->display->display_options['filters']['type']['group'] = 0;
  /* Filter criterion: Content: Hide from Gallery (field_gallery_hidden) */
  $handler->display->display_options['filters']['field_gallery_hidden_value']['id'] = 'field_gallery_hidden_value';
  $handler->display->display_options['filters']['field_gallery_hidden_value']['table'] = 'field_data_field_gallery_hidden';
  $handler->display->display_options['filters']['field_gallery_hidden_value']['field'] = 'field_gallery_hidden_value';
  $handler->display->display_options['filters']['field_gallery_hidden_value']['operator'] = 'not in';
  $handler->display->display_options['filters']['field_gallery_hidden_value']['value'] = array(
    1 => '1',
  );
  $translatables['photo_list'] = array(
    t('Master'),
    t('Photo Album List'),
    t('more'),
    t('Sort'),
    t('Reset'),
    t('Sort by'),
    t('Asc'),
    t('Desc'),
    t('Country'),
    t('member_photos'),
    t('Nid'),
    t('Name'),
    t('Categories'),
    t('Date'),
    t('Date Released (field_date_event)'),
    t('Search'),
    t('Category'),
    t('Block'),
    t('Block: Mobile'),
    t('Apply'),
  );
  $export['photo_list'] = $view;

  $view = new view;
  $view->name = 'photos_related_to_node';
  $view->description = '';
  $view->tag = 'default';
  $view->base_table = 'node';
  $view->human_name = 'Photos Related to Node';
  $view->core = 7;
  $view->api_version = '3.0';
  $view->disabled = FALSE; /* Edit this to true to make a default view disabled initially */

  /* Display: Master */
  $handler = $view->new_display('default', 'Master', 'default');
  $handler->display->display_options['title'] = 'Full Photo Gallery EVA';
  $handler->display->display_options['access']['type'] = 'none';
  $handler->display->display_options['cache']['type'] = 'none';
  $handler->display->display_options['query']['type'] = 'views_query';
  $handler->display->display_options['query']['options']['query_comment'] = FALSE;
  $handler->display->display_options['exposed_form']['type'] = 'basic';
  $handler->display->display_options['pager']['type'] = 'full';
  $handler->display->display_options['pager']['options']['items_per_page'] = '0';
  $handler->display->display_options['pager']['options']['offset'] = '0';
  $handler->display->display_options['pager']['options']['id'] = '0';
  $handler->display->display_options['pager']['options']['expose']['items_per_page_options_all'] = 0;
  $handler->display->display_options['style_plugin'] = 'grid';
  $handler->display->display_options['style_options']['columns'] = '3';
  $handler->display->display_options['style_options']['fill_single_line'] = 0;
  $handler->display->display_options['row_plugin'] = 'fields';
  /* Header: Global: Text area */
  $handler->display->display_options['header']['area']['id'] = 'area';
  $handler->display->display_options['header']['area']['table'] = 'views';
  $handler->display->display_options['header']['area']['field'] = 'area';
  $handler->display->display_options['header']['area']['empty'] = TRUE;
  $handler->display->display_options['header']['area']['content'] = 'DEBUG: <?php
print arg(1);
?>';
  $handler->display->display_options['header']['area']['format'] = 'php_code';
  $handler->display->display_options['header']['area']['tokenize'] = 0;
  /* No results behavior: Global: Text area */
  $handler->display->display_options['empty']['area']['id'] = 'area';
  $handler->display->display_options['empty']['area']['table'] = 'views';
  $handler->display->display_options['empty']['area']['field'] = 'area';
  $handler->display->display_options['empty']['area']['empty'] = FALSE;
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
  $handler->display->display_options['fields']['field_image']['alter']['strip_tags'] = 0;
  $handler->display->display_options['fields']['field_image']['alter']['trim'] = 0;
  $handler->display->display_options['fields']['field_image']['alter']['html'] = 0;
  $handler->display->display_options['fields']['field_image']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['field_image']['element_default_classes'] = 1;
  $handler->display->display_options['fields']['field_image']['hide_empty'] = 0;
  $handler->display->display_options['fields']['field_image']['empty_zero'] = 0;
  $handler->display->display_options['fields']['field_image']['hide_alter_empty'] = 0;
  $handler->display->display_options['fields']['field_image']['click_sort_column'] = 'fid';
  $handler->display->display_options['fields']['field_image']['settings'] = array(
    'image_style' => 'thumbnail',
    'image_link' => 'content',
  );
  $handler->display->display_options['fields']['field_image']['field_api_classes'] = 0;
  /* Sort criterion: Content: Sticky */
  $handler->display->display_options['sorts']['sticky']['id'] = 'sticky';
  $handler->display->display_options['sorts']['sticky']['table'] = 'node';
  $handler->display->display_options['sorts']['sticky']['field'] = 'sticky';
  $handler->display->display_options['sorts']['sticky']['order'] = 'DESC';
  /* Sort criterion: Content: Post date */
  $handler->display->display_options['sorts']['created']['id'] = 'created';
  $handler->display->display_options['sorts']['created']['table'] = 'node';
  $handler->display->display_options['sorts']['created']['field'] = 'created';
  $handler->display->display_options['sorts']['created']['order'] = 'DESC';
  $handler->display->display_options['sorts']['created']['expose']['label'] = 'Post date';
  /* Contextual filter: Content: Has taxonomy term ID */
  $handler->display->display_options['arguments']['tid']['id'] = 'tid';
  $handler->display->display_options['arguments']['tid']['table'] = 'taxonomy_index';
  $handler->display->display_options['arguments']['tid']['field'] = 'tid';
  $handler->display->display_options['arguments']['tid']['default_action'] = 'default';
  $handler->display->display_options['arguments']['tid']['default_argument_type'] = 'taxonomy_tid';
  $handler->display->display_options['arguments']['tid']['default_argument_options']['term_page'] = 0;
  $handler->display->display_options['arguments']['tid']['default_argument_options']['node'] = 1;
  $handler->display->display_options['arguments']['tid']['default_argument_options']['limit'] = 1;
  $handler->display->display_options['arguments']['tid']['default_argument_options']['vocabularies'] = array(
    'photo_collections' => 'photo_collections',
    'location' => 0,
    'staff_type' => 0,
    'tags' => 0,
  );
  $handler->display->display_options['arguments']['tid']['default_argument_skip_url'] = 0;
  $handler->display->display_options['arguments']['tid']['summary']['number_of_records'] = '0';
  $handler->display->display_options['arguments']['tid']['summary']['format'] = 'default_summary';
  $handler->display->display_options['arguments']['tid']['summary_options']['items_per_page'] = '25';
  $handler->display->display_options['arguments']['tid']['break_phrase'] = 0;
  $handler->display->display_options['arguments']['tid']['add_table'] = 0;
  $handler->display->display_options['arguments']['tid']['require_value'] = 0;
  $handler->display->display_options['arguments']['tid']['reduce_duplicates'] = 0;
  $handler->display->display_options['arguments']['tid']['set_breadcrumb'] = 0;
  /* Contextual filter: Content: Nid */
  $handler->display->display_options['arguments']['nid']['id'] = 'nid';
  $handler->display->display_options['arguments']['nid']['table'] = 'node';
  $handler->display->display_options['arguments']['nid']['field'] = 'nid';
  $handler->display->display_options['arguments']['nid']['default_action'] = 'default';
  $handler->display->display_options['arguments']['nid']['default_argument_type'] = 'node';
  $handler->display->display_options['arguments']['nid']['default_argument_skip_url'] = 0;
  $handler->display->display_options['arguments']['nid']['summary']['number_of_records'] = '0';
  $handler->display->display_options['arguments']['nid']['summary']['format'] = 'default_summary';
  $handler->display->display_options['arguments']['nid']['summary_options']['items_per_page'] = '25';
  $handler->display->display_options['arguments']['nid']['break_phrase'] = 0;
  $handler->display->display_options['arguments']['nid']['not'] = 1;
  /* Filter criterion: Content: Type */
  $handler->display->display_options['filters']['type']['id'] = 'type';
  $handler->display->display_options['filters']['type']['table'] = 'node';
  $handler->display->display_options['filters']['type']['field'] = 'type';
  $handler->display->display_options['filters']['type']['value'] = array(
    'media_photo' => 'media_photo',
  );
  /* Filter criterion: Content: Published or admin */
  $handler->display->display_options['filters']['status_extra']['id'] = 'status_extra';
  $handler->display->display_options['filters']['status_extra']['table'] = 'node';
  $handler->display->display_options['filters']['status_extra']['field'] = 'status_extra';

  /* Display: EVA: Attached Photos */
  $handler = $view->new_display('entity_view', 'EVA: Attached Photos', 'entity_view_2');
  $handler->display->display_options['defaults']['title'] = FALSE;
  $handler->display->display_options['title'] = 'Attached Photo Collection (EVA)';
  $handler->display->display_options['defaults']['empty'] = FALSE;
  $handler->display->display_options['entity_type'] = 'node';
  $handler->display->display_options['bundles'] = array(
    0 => 'media_article',
    1 => 'project',
  );
  $handler->display->display_options['show_title'] = 1;

  /* Display: EVA: Related Photos */
  $handler = $view->new_display('entity_view', 'EVA: Related Photos', 'entity_view_1');
  $handler->display->display_options['defaults']['title'] = FALSE;
  $handler->display->display_options['title'] = 'Related Photos (EVA)';
  $handler->display->display_options['defaults']['empty'] = FALSE;
  $handler->display->display_options['entity_type'] = 'node';
  $handler->display->display_options['bundles'] = array(
    0 => 'media_photo',
  );
  $handler->display->display_options['show_title'] = 1;

  /* Display: EVA: Attached Photos Topmost */
  $handler = $view->new_display('entity_view', 'EVA: Attached Photos Topmost', 'entity_view_3');
  $handler->display->display_options['defaults']['title'] = FALSE;
  $handler->display->display_options['title'] = 'Attached Topmost Photo (EVA)';
  $handler->display->display_options['defaults']['pager'] = FALSE;
  $handler->display->display_options['pager']['type'] = 'some';
  $handler->display->display_options['pager']['options']['items_per_page'] = '1';
  $handler->display->display_options['pager']['options']['offset'] = '0';
  $handler->display->display_options['defaults']['style_plugin'] = FALSE;
  $handler->display->display_options['style_plugin'] = 'default';
  $handler->display->display_options['defaults']['style_options'] = FALSE;
  $handler->display->display_options['defaults']['row_plugin'] = FALSE;
  $handler->display->display_options['row_plugin'] = 'fields';
  $handler->display->display_options['defaults']['row_options'] = FALSE;
  $handler->display->display_options['defaults']['empty'] = FALSE;
  /* No results behavior: Global: Text area */
  $handler->display->display_options['empty']['area']['id'] = 'area';
  $handler->display->display_options['empty']['area']['table'] = 'views';
  $handler->display->display_options['empty']['area']['field'] = 'area';
  $handler->display->display_options['empty']['area']['empty'] = FALSE;
  $handler->display->display_options['empty']['area']['content'] = 'none found';
  $handler->display->display_options['empty']['area']['format'] = 'plain_text';
  $handler->display->display_options['empty']['area']['tokenize'] = 0;
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
  $handler->display->display_options['fields']['field_image']['alter']['strip_tags'] = 0;
  $handler->display->display_options['fields']['field_image']['alter']['trim'] = 0;
  $handler->display->display_options['fields']['field_image']['alter']['html'] = 0;
  $handler->display->display_options['fields']['field_image']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['field_image']['element_default_classes'] = 1;
  $handler->display->display_options['fields']['field_image']['hide_empty'] = 0;
  $handler->display->display_options['fields']['field_image']['empty_zero'] = 0;
  $handler->display->display_options['fields']['field_image']['hide_alter_empty'] = 0;
  $handler->display->display_options['fields']['field_image']['click_sort_column'] = 'fid';
  $handler->display->display_options['fields']['field_image']['settings'] = array(
    'image_style' => 'medium',
    'image_link' => 'content',
  );
  $handler->display->display_options['fields']['field_image']['field_api_classes'] = 0;
  $handler->display->display_options['defaults']['arguments'] = FALSE;
  /* Contextual filter: Content: Has taxonomy term ID */
  $handler->display->display_options['arguments']['tid']['id'] = 'tid';
  $handler->display->display_options['arguments']['tid']['table'] = 'taxonomy_index';
  $handler->display->display_options['arguments']['tid']['field'] = 'tid';
  $handler->display->display_options['arguments']['tid']['default_action'] = 'default';
  $handler->display->display_options['arguments']['tid']['default_argument_type'] = 'php';
  $handler->display->display_options['arguments']['tid']['default_argument_options']['code'] = '$node = node_load(arg(1));
if($node){
foreach (field_get_items(\'node\', $node, \'field_photo_collections\') as $term ) {
  $terms[] = $term[\'tid\'];
}
return implode(\'+\', $terms);
} else { return; }';
  $handler->display->display_options['arguments']['tid']['default_argument_skip_url'] = 0;
  $handler->display->display_options['arguments']['tid']['summary']['number_of_records'] = '0';
  $handler->display->display_options['arguments']['tid']['summary']['format'] = 'default_summary';
  $handler->display->display_options['arguments']['tid']['summary_options']['items_per_page'] = '25';
  $handler->display->display_options['arguments']['tid']['break_phrase'] = 0;
  $handler->display->display_options['arguments']['tid']['add_table'] = 0;
  $handler->display->display_options['arguments']['tid']['require_value'] = 0;
  $handler->display->display_options['arguments']['tid']['reduce_duplicates'] = 0;
  $handler->display->display_options['arguments']['tid']['set_breadcrumb'] = 0;
  $handler->display->display_options['entity_type'] = 'node';
  $handler->display->display_options['bundles'] = array(
    0 => 'media_article',
    1 => 'project',
  );
  $handler->display->display_options['argument_mode'] = 'token';
  $handler->display->display_options['default_argument'] = '[node:field-photo-collections:tid]';
  $handler->display->display_options['show_title'] = 0;
  $translatables['photos_related_to_node'] = array(
    t('Master'),
    t('Full Photo Gallery EVA'),
    t('more'),
    t('Apply'),
    t('Reset'),
    t('Sort by'),
    t('Asc'),
    t('Desc'),
    t('Items per page'),
    t('- All -'),
    t('Offset'),
    t('DEBUG: <?php
print arg(1);
?>'),
    t('Post date'),
    t('All'),
    t('EVA: Attached Photos'),
    t('Attached Photo Collection (EVA)'),
    t('EVA: Related Photos'),
    t('Related Photos (EVA)'),
    t('EVA: Attached Photos Topmost'),
    t('Attached Topmost Photo (EVA)'),
    t('none found'),
  );
  $export['photos_related_to_node'] = $view;

  return $export;
}
