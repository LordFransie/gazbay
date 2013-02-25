<?php
/**
 * @file
 * gazprom_home_features.views_default.inc
 */

/**
 * Implements hook_views_default_views().
 */
function gazprom_home_features_views_default_views() {
  $export = array();

  $view = new view;
  $view->name = 'front_features';
  $view->description = 'Display a list of all nodes in queue \'Front Page Features\'';
  $view->tag = 'nodequeue';
  $view->base_table = 'node';
  $view->human_name = 'front_features';
  $view->core = 0;
  $view->api_version = '3.0';
  $view->disabled = FALSE; /* Edit this to true to make a default view disabled initially */

  /* Display: Defaults */
  $handler = $view->new_display('default', 'Defaults', 'default');
  $handler->display->display_options['title'] = 'Features';
  $handler->display->display_options['use_more'] = TRUE;
  $handler->display->display_options['access']['type'] = 'none';
  $handler->display->display_options['cache']['type'] = 'none';
  $handler->display->display_options['query']['type'] = 'views_query';
  $handler->display->display_options['query']['options']['query_comment'] = FALSE;
  $handler->display->display_options['exposed_form']['type'] = 'basic';
  $handler->display->display_options['pager']['type'] = 'none';
  $handler->display->display_options['style_plugin'] = 'table';
  /* Header: Global: Text area */
  $handler->display->display_options['header']['area']['id'] = 'area';
  $handler->display->display_options['header']['area']['table'] = 'views';
  $handler->display->display_options['header']['area']['field'] = 'area';
  $handler->display->display_options['header']['area']['empty'] = FALSE;
  /* Relationship: Content: Link to content (field_content_reference) */
  $handler->display->display_options['relationships']['field_content_reference_nid']['id'] = 'field_content_reference_nid';
  $handler->display->display_options['relationships']['field_content_reference_nid']['table'] = 'field_data_field_content_reference';
  $handler->display->display_options['relationships']['field_content_reference_nid']['field'] = 'field_content_reference_nid';
  $handler->display->display_options['relationships']['field_content_reference_nid']['required'] = 0;
  $handler->display->display_options['relationships']['field_content_reference_nid']['delta'] = '-1';
  /* Relationship: Content: Link to content (2) (field_content_reference_2) */
  $handler->display->display_options['relationships']['field_content_reference_2_nid']['id'] = 'field_content_reference_2_nid';
  $handler->display->display_options['relationships']['field_content_reference_2_nid']['table'] = 'field_data_field_content_reference_2';
  $handler->display->display_options['relationships']['field_content_reference_2_nid']['field'] = 'field_content_reference_2_nid';
  /* Field: Content: Title */
  $handler->display->display_options['fields']['title']['id'] = 'title';
  $handler->display->display_options['fields']['title']['table'] = 'node';
  $handler->display->display_options['fields']['title']['field'] = 'title';
  $handler->display->display_options['fields']['title']['label'] = '';
  $handler->display->display_options['fields']['title']['link_to_node'] = 1;
  /* Field: Content: Background Image */
  $handler->display->display_options['fields']['field_background_image']['id'] = 'field_background_image';
  $handler->display->display_options['fields']['field_background_image']['table'] = 'field_data_field_background_image';
  $handler->display->display_options['fields']['field_background_image']['field'] = 'field_background_image';
  /* Sort criterion: DraggableViews: Order */
  $handler->display->display_options['sorts']['value0']['id'] = 'value0';
  $handler->display->display_options['sorts']['value0']['table'] = 'draggableviews_structure_node0';
  $handler->display->display_options['sorts']['value0']['field'] = 'value0';
  /* Sort criterion: Content: Post date */
  $handler->display->display_options['sorts']['created']['id'] = 'created';
  $handler->display->display_options['sorts']['created']['table'] = 'node';
  $handler->display->display_options['sorts']['created']['field'] = 'created';
  /* Filter criterion: Content: Type */
  $handler->display->display_options['filters']['type']['id'] = 'type';
  $handler->display->display_options['filters']['type']['table'] = 'node';
  $handler->display->display_options['filters']['type']['field'] = 'type';
  $handler->display->display_options['filters']['type']['value'] = array(
    'home_page_feature' => 'home_page_feature',
  );
  $handler->display->display_options['filters']['type']['exposed'] = TRUE;
  $handler->display->display_options['filters']['type']['expose']['operator_id'] = 'type_op';
  $handler->display->display_options['filters']['type']['expose']['label'] = 'Type';
  $handler->display->display_options['filters']['type']['expose']['use_operator'] = FALSE;
  $handler->display->display_options['filters']['type']['expose']['operator'] = 'type_op';
  $handler->display->display_options['filters']['type']['expose']['identifier'] = 'type';
  $handler->display->display_options['filters']['type']['expose']['required'] = FALSE;
  $handler->display->display_options['filters']['type']['expose']['remember'] = FALSE;
  $handler->display->display_options['filters']['type']['expose']['multiple'] = FALSE;
  /* Filter criterion: Content: Published */
  $handler->display->display_options['filters']['status']['id'] = 'status';
  $handler->display->display_options['filters']['status']['table'] = 'node';
  $handler->display->display_options['filters']['status']['field'] = 'status';
  $handler->display->display_options['filters']['status']['value'] = '1';
  /* Filter criterion: Content translation: Language */
  $handler->display->display_options['filters']['language']['id'] = 'language';
  $handler->display->display_options['filters']['language']['table'] = 'node';
  $handler->display->display_options['filters']['language']['field'] = 'language';
  $handler->display->display_options['filters']['language']['value'] = array(
    '***CURRENT_LANGUAGE***' => '***CURRENT_LANGUAGE***',
  );

  /* Display: Block: Home Features */
  $handler = $view->new_display('block', 'Block: Home Features', 'main');
  $handler->display->display_options['defaults']['style_plugin'] = FALSE;
  $handler->display->display_options['style_plugin'] = 'list';
  $handler->display->display_options['defaults']['style_options'] = FALSE;
  $handler->display->display_options['defaults']['row_plugin'] = FALSE;
  $handler->display->display_options['row_plugin'] = 'fields';
  $handler->display->display_options['row_options']['hide_empty'] = 0;
  $handler->display->display_options['row_options']['default_field_elements'] = 0;
  $handler->display->display_options['defaults']['row_options'] = FALSE;
  $handler->display->display_options['defaults']['relationships'] = FALSE;
  /* Relationship: Content: Link to content (field_content_reference) */
  $handler->display->display_options['relationships']['field_content_reference_nid']['id'] = 'field_content_reference_nid';
  $handler->display->display_options['relationships']['field_content_reference_nid']['table'] = 'field_data_field_content_reference';
  $handler->display->display_options['relationships']['field_content_reference_nid']['field'] = 'field_content_reference_nid';
  $handler->display->display_options['relationships']['field_content_reference_nid']['required'] = 0;
  $handler->display->display_options['relationships']['field_content_reference_nid']['delta'] = '-1';
  /* Relationship: Content: Link to content (2) (field_content_reference_2) */
  $handler->display->display_options['relationships']['field_content_reference_2_nid']['id'] = 'field_content_reference_2_nid';
  $handler->display->display_options['relationships']['field_content_reference_2_nid']['table'] = 'field_data_field_content_reference_2';
  $handler->display->display_options['relationships']['field_content_reference_2_nid']['field'] = 'field_content_reference_2_nid';
  $handler->display->display_options['relationships']['field_content_reference_2_nid']['required'] = 0;
  $handler->display->display_options['relationships']['field_content_reference_2_nid']['delta'] = '-1';
  $handler->display->display_options['defaults']['fields'] = FALSE;
  /* Field: Content: Background Image */
  $handler->display->display_options['fields']['field_background_image']['id'] = 'field_background_image';
  $handler->display->display_options['fields']['field_background_image']['table'] = 'field_data_field_background_image';
  $handler->display->display_options['fields']['field_background_image']['field'] = 'field_background_image';
  $handler->display->display_options['fields']['field_background_image']['label'] = '';
  $handler->display->display_options['fields']['field_background_image']['alter']['alter_text'] = 0;
  $handler->display->display_options['fields']['field_background_image']['alter']['make_link'] = 0;
  $handler->display->display_options['fields']['field_background_image']['alter']['absolute'] = 0;
  $handler->display->display_options['fields']['field_background_image']['alter']['external'] = 0;
  $handler->display->display_options['fields']['field_background_image']['alter']['replace_spaces'] = 0;
  $handler->display->display_options['fields']['field_background_image']['alter']['trim_whitespace'] = 0;
  $handler->display->display_options['fields']['field_background_image']['alter']['nl2br'] = 0;
  $handler->display->display_options['fields']['field_background_image']['alter']['word_boundary'] = 1;
  $handler->display->display_options['fields']['field_background_image']['alter']['ellipsis'] = 1;
  $handler->display->display_options['fields']['field_background_image']['alter']['strip_tags'] = 0;
  $handler->display->display_options['fields']['field_background_image']['alter']['trim'] = 0;
  $handler->display->display_options['fields']['field_background_image']['alter']['html'] = 0;
  $handler->display->display_options['fields']['field_background_image']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['field_background_image']['element_default_classes'] = 0;
  $handler->display->display_options['fields']['field_background_image']['hide_empty'] = 0;
  $handler->display->display_options['fields']['field_background_image']['empty_zero'] = 0;
  $handler->display->display_options['fields']['field_background_image']['hide_alter_empty'] = 1;
  $handler->display->display_options['fields']['field_background_image']['click_sort_column'] = 'fid';
  $handler->display->display_options['fields']['field_background_image']['settings'] = array(
    'image_style' => 'backgrounder',
    'image_link' => '',
  );
  $handler->display->display_options['fields']['field_background_image']['group_column'] = 'fid';
  $handler->display->display_options['fields']['field_background_image']['field_api_classes'] = 0;
  /* Field: Content: Additional Background Images */
  $handler->display->display_options['fields']['field_background_image_multiple']['id'] = 'field_background_image_multiple';
  $handler->display->display_options['fields']['field_background_image_multiple']['table'] = 'field_data_field_background_image_multiple';
  $handler->display->display_options['fields']['field_background_image_multiple']['field'] = 'field_background_image_multiple';
  $handler->display->display_options['fields']['field_background_image_multiple']['label'] = '';
  $handler->display->display_options['fields']['field_background_image_multiple']['alter']['alter_text'] = 0;
  $handler->display->display_options['fields']['field_background_image_multiple']['alter']['make_link'] = 0;
  $handler->display->display_options['fields']['field_background_image_multiple']['alter']['absolute'] = 0;
  $handler->display->display_options['fields']['field_background_image_multiple']['alter']['external'] = 0;
  $handler->display->display_options['fields']['field_background_image_multiple']['alter']['replace_spaces'] = 0;
  $handler->display->display_options['fields']['field_background_image_multiple']['alter']['trim_whitespace'] = 0;
  $handler->display->display_options['fields']['field_background_image_multiple']['alter']['nl2br'] = 0;
  $handler->display->display_options['fields']['field_background_image_multiple']['alter']['word_boundary'] = 1;
  $handler->display->display_options['fields']['field_background_image_multiple']['alter']['ellipsis'] = 1;
  $handler->display->display_options['fields']['field_background_image_multiple']['alter']['strip_tags'] = 0;
  $handler->display->display_options['fields']['field_background_image_multiple']['alter']['trim'] = 0;
  $handler->display->display_options['fields']['field_background_image_multiple']['alter']['html'] = 0;
  $handler->display->display_options['fields']['field_background_image_multiple']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['field_background_image_multiple']['element_default_classes'] = 0;
  $handler->display->display_options['fields']['field_background_image_multiple']['hide_empty'] = 0;
  $handler->display->display_options['fields']['field_background_image_multiple']['empty_zero'] = 0;
  $handler->display->display_options['fields']['field_background_image_multiple']['hide_alter_empty'] = 1;
  $handler->display->display_options['fields']['field_background_image_multiple']['click_sort_column'] = 'fid';
  $handler->display->display_options['fields']['field_background_image_multiple']['settings'] = array(
    'image_style' => 'backgrounder',
    'image_link' => '',
  );
  $handler->display->display_options['fields']['field_background_image_multiple']['group_rows'] = 1;
  $handler->display->display_options['fields']['field_background_image_multiple']['delta_offset'] = '0';
  $handler->display->display_options['fields']['field_background_image_multiple']['delta_reversed'] = 0;
  $handler->display->display_options['fields']['field_background_image_multiple']['delta_first_last'] = 0;
  $handler->display->display_options['fields']['field_background_image_multiple']['separator'] = '';
  $handler->display->display_options['fields']['field_background_image_multiple']['field_api_classes'] = 0;
  /* Field: Title */
  $handler->display->display_options['fields']['title']['id'] = 'title';
  $handler->display->display_options['fields']['title']['table'] = 'node';
  $handler->display->display_options['fields']['title']['field'] = 'title';
  $handler->display->display_options['fields']['title']['ui_name'] = 'Title';
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
  $handler->display->display_options['fields']['title']['element_wrapper_type'] = 'h1';
  $handler->display->display_options['fields']['title']['element_default_classes'] = 1;
  $handler->display->display_options['fields']['title']['hide_empty'] = 0;
  $handler->display->display_options['fields']['title']['empty_zero'] = 0;
  $handler->display->display_options['fields']['title']['hide_alter_empty'] = 1;
  $handler->display->display_options['fields']['title']['link_to_node'] = 0;
  /* Field: summary (left) */
  $handler->display->display_options['fields']['body']['id'] = 'body';
  $handler->display->display_options['fields']['body']['table'] = 'field_data_body';
  $handler->display->display_options['fields']['body']['field'] = 'body';
  $handler->display->display_options['fields']['body']['ui_name'] = 'summary (left)';
  $handler->display->display_options['fields']['body']['label'] = '';
  $handler->display->display_options['fields']['body']['alter']['alter_text'] = 0;
  $handler->display->display_options['fields']['body']['alter']['make_link'] = 0;
  $handler->display->display_options['fields']['body']['alter']['absolute'] = 0;
  $handler->display->display_options['fields']['body']['alter']['external'] = 0;
  $handler->display->display_options['fields']['body']['alter']['replace_spaces'] = 0;
  $handler->display->display_options['fields']['body']['alter']['trim_whitespace'] = 0;
  $handler->display->display_options['fields']['body']['alter']['nl2br'] = 1;
  $handler->display->display_options['fields']['body']['alter']['word_boundary'] = 1;
  $handler->display->display_options['fields']['body']['alter']['ellipsis'] = 1;
  $handler->display->display_options['fields']['body']['alter']['more_link'] = 0;
  $handler->display->display_options['fields']['body']['alter']['strip_tags'] = 0;
  $handler->display->display_options['fields']['body']['alter']['trim'] = 0;
  $handler->display->display_options['fields']['body']['alter']['html'] = 0;
  $handler->display->display_options['fields']['body']['element_type'] = 'div';
  $handler->display->display_options['fields']['body']['element_class'] = 'views-field-summary';
  $handler->display->display_options['fields']['body']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['body']['element_default_classes'] = 1;
  $handler->display->display_options['fields']['body']['hide_empty'] = 0;
  $handler->display->display_options['fields']['body']['empty_zero'] = 0;
  $handler->display->display_options['fields']['body']['hide_alter_empty'] = 1;
  $handler->display->display_options['fields']['body']['type'] = 'text_plain';
  $handler->display->display_options['fields']['body']['field_api_classes'] = 0;
  /* Field: Link text (left) */
  $handler->display->display_options['fields']['field_link_text_1']['id'] = 'field_link_text_1';
  $handler->display->display_options['fields']['field_link_text_1']['table'] = 'field_data_field_link_text';
  $handler->display->display_options['fields']['field_link_text_1']['field'] = 'field_link_text';
  $handler->display->display_options['fields']['field_link_text_1']['ui_name'] = 'Link text (left)';
  $handler->display->display_options['fields']['field_link_text_1']['label'] = '';
  $handler->display->display_options['fields']['field_link_text_1']['exclude'] = TRUE;
  $handler->display->display_options['fields']['field_link_text_1']['alter']['alter_text'] = 0;
  $handler->display->display_options['fields']['field_link_text_1']['alter']['make_link'] = 0;
  $handler->display->display_options['fields']['field_link_text_1']['alter']['path'] = '[path]';
  $handler->display->display_options['fields']['field_link_text_1']['alter']['absolute'] = 0;
  $handler->display->display_options['fields']['field_link_text_1']['alter']['external'] = 0;
  $handler->display->display_options['fields']['field_link_text_1']['alter']['replace_spaces'] = 0;
  $handler->display->display_options['fields']['field_link_text_1']['alter']['trim_whitespace'] = 0;
  $handler->display->display_options['fields']['field_link_text_1']['alter']['rel'] = 'test';
  $handler->display->display_options['fields']['field_link_text_1']['alter']['nl2br'] = 0;
  $handler->display->display_options['fields']['field_link_text_1']['alter']['word_boundary'] = 1;
  $handler->display->display_options['fields']['field_link_text_1']['alter']['ellipsis'] = 1;
  $handler->display->display_options['fields']['field_link_text_1']['alter']['strip_tags'] = 0;
  $handler->display->display_options['fields']['field_link_text_1']['alter']['trim'] = 0;
  $handler->display->display_options['fields']['field_link_text_1']['alter']['html'] = 0;
  $handler->display->display_options['fields']['field_link_text_1']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['field_link_text_1']['element_default_classes'] = 1;
  $handler->display->display_options['fields']['field_link_text_1']['hide_empty'] = 0;
  $handler->display->display_options['fields']['field_link_text_1']['empty_zero'] = 0;
  $handler->display->display_options['fields']['field_link_text_1']['hide_alter_empty'] = 1;
  $handler->display->display_options['fields']['field_link_text_1']['field_api_classes'] = 0;
  /* Field: Content: Link */
  $handler->display->display_options['fields']['view_node_1']['id'] = 'view_node_1';
  $handler->display->display_options['fields']['view_node_1']['table'] = 'views_entity_node';
  $handler->display->display_options['fields']['view_node_1']['field'] = 'view_node';
  $handler->display->display_options['fields']['view_node_1']['relationship'] = 'field_content_reference_nid';
  $handler->display->display_options['fields']['view_node_1']['label'] = '';
  $handler->display->display_options['fields']['view_node_1']['alter']['alter_text'] = 1;
  $handler->display->display_options['fields']['view_node_1']['alter']['text'] = '[field_link_text_1]';
  $handler->display->display_options['fields']['view_node_1']['alter']['make_link'] = 0;
  $handler->display->display_options['fields']['view_node_1']['alter']['absolute'] = 0;
  $handler->display->display_options['fields']['view_node_1']['alter']['replace_spaces'] = 0;
  $handler->display->display_options['fields']['view_node_1']['alter']['trim_whitespace'] = 0;
  $handler->display->display_options['fields']['view_node_1']['alter']['nl2br'] = 0;
  $handler->display->display_options['fields']['view_node_1']['alter']['word_boundary'] = 1;
  $handler->display->display_options['fields']['view_node_1']['alter']['ellipsis'] = 1;
  $handler->display->display_options['fields']['view_node_1']['alter']['strip_tags'] = 0;
  $handler->display->display_options['fields']['view_node_1']['alter']['trim'] = 0;
  $handler->display->display_options['fields']['view_node_1']['alter']['html'] = 0;
  $handler->display->display_options['fields']['view_node_1']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['view_node_1']['element_wrapper_type'] = 'div';
  $handler->display->display_options['fields']['view_node_1']['element_wrapper_class'] = 'blue-link-wrapper';
  $handler->display->display_options['fields']['view_node_1']['element_default_classes'] = 0;
  $handler->display->display_options['fields']['view_node_1']['hide_empty'] = 1;
  $handler->display->display_options['fields']['view_node_1']['empty_zero'] = 0;
  $handler->display->display_options['fields']['view_node_1']['hide_alter_empty'] = 1;
  $handler->display->display_options['fields']['view_node_1']['text'] = 'Rewritten';
  /* Field: summary (right) */
  $handler->display->display_options['fields']['field_body_2']['id'] = 'field_body_2';
  $handler->display->display_options['fields']['field_body_2']['table'] = 'field_data_field_body_2';
  $handler->display->display_options['fields']['field_body_2']['field'] = 'field_body_2';
  $handler->display->display_options['fields']['field_body_2']['ui_name'] = 'summary (right)';
  $handler->display->display_options['fields']['field_body_2']['label'] = '';
  $handler->display->display_options['fields']['field_body_2']['alter']['alter_text'] = 0;
  $handler->display->display_options['fields']['field_body_2']['alter']['make_link'] = 0;
  $handler->display->display_options['fields']['field_body_2']['alter']['absolute'] = 0;
  $handler->display->display_options['fields']['field_body_2']['alter']['external'] = 0;
  $handler->display->display_options['fields']['field_body_2']['alter']['replace_spaces'] = 0;
  $handler->display->display_options['fields']['field_body_2']['alter']['trim_whitespace'] = 0;
  $handler->display->display_options['fields']['field_body_2']['alter']['nl2br'] = 1;
  $handler->display->display_options['fields']['field_body_2']['alter']['word_boundary'] = 1;
  $handler->display->display_options['fields']['field_body_2']['alter']['ellipsis'] = 1;
  $handler->display->display_options['fields']['field_body_2']['alter']['more_link'] = 0;
  $handler->display->display_options['fields']['field_body_2']['alter']['strip_tags'] = 0;
  $handler->display->display_options['fields']['field_body_2']['alter']['trim'] = 0;
  $handler->display->display_options['fields']['field_body_2']['alter']['html'] = 0;
  $handler->display->display_options['fields']['field_body_2']['element_type'] = 'div';
  $handler->display->display_options['fields']['field_body_2']['element_class'] = 'views-field-summary';
  $handler->display->display_options['fields']['field_body_2']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['field_body_2']['element_default_classes'] = 1;
  $handler->display->display_options['fields']['field_body_2']['hide_empty'] = 0;
  $handler->display->display_options['fields']['field_body_2']['empty_zero'] = 0;
  $handler->display->display_options['fields']['field_body_2']['hide_alter_empty'] = 1;
  $handler->display->display_options['fields']['field_body_2']['type'] = 'text_plain';
  $handler->display->display_options['fields']['field_body_2']['field_api_classes'] = 0;
  /* Field: link text (right) */
  $handler->display->display_options['fields']['field_link_text_2']['id'] = 'field_link_text_2';
  $handler->display->display_options['fields']['field_link_text_2']['table'] = 'field_data_field_link_text_2';
  $handler->display->display_options['fields']['field_link_text_2']['field'] = 'field_link_text_2';
  $handler->display->display_options['fields']['field_link_text_2']['ui_name'] = 'link text (right)';
  $handler->display->display_options['fields']['field_link_text_2']['label'] = '';
  $handler->display->display_options['fields']['field_link_text_2']['exclude'] = TRUE;
  $handler->display->display_options['fields']['field_link_text_2']['alter']['alter_text'] = 0;
  $handler->display->display_options['fields']['field_link_text_2']['alter']['make_link'] = 0;
  $handler->display->display_options['fields']['field_link_text_2']['alter']['absolute'] = 0;
  $handler->display->display_options['fields']['field_link_text_2']['alter']['external'] = 0;
  $handler->display->display_options['fields']['field_link_text_2']['alter']['replace_spaces'] = 0;
  $handler->display->display_options['fields']['field_link_text_2']['alter']['trim_whitespace'] = 0;
  $handler->display->display_options['fields']['field_link_text_2']['alter']['nl2br'] = 0;
  $handler->display->display_options['fields']['field_link_text_2']['alter']['word_boundary'] = 1;
  $handler->display->display_options['fields']['field_link_text_2']['alter']['ellipsis'] = 1;
  $handler->display->display_options['fields']['field_link_text_2']['alter']['strip_tags'] = 0;
  $handler->display->display_options['fields']['field_link_text_2']['alter']['trim'] = 0;
  $handler->display->display_options['fields']['field_link_text_2']['alter']['html'] = 0;
  $handler->display->display_options['fields']['field_link_text_2']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['field_link_text_2']['element_default_classes'] = 1;
  $handler->display->display_options['fields']['field_link_text_2']['hide_empty'] = 0;
  $handler->display->display_options['fields']['field_link_text_2']['empty_zero'] = 0;
  $handler->display->display_options['fields']['field_link_text_2']['hide_alter_empty'] = 1;
  $handler->display->display_options['fields']['field_link_text_2']['field_api_classes'] = 0;
  /* Field: Content: Link (link - right side) */
  $handler->display->display_options['fields']['view_node']['id'] = 'view_node';
  $handler->display->display_options['fields']['view_node']['table'] = 'views_entity_node';
  $handler->display->display_options['fields']['view_node']['field'] = 'view_node';
  $handler->display->display_options['fields']['view_node']['relationship'] = 'field_content_reference_2_nid';
  $handler->display->display_options['fields']['view_node']['ui_name'] = 'Content: Link (link - right side)';
  $handler->display->display_options['fields']['view_node']['label'] = '';
  $handler->display->display_options['fields']['view_node']['alter']['alter_text'] = 1;
  $handler->display->display_options['fields']['view_node']['alter']['text'] = '[field_link_text_2]';
  $handler->display->display_options['fields']['view_node']['alter']['make_link'] = 0;
  $handler->display->display_options['fields']['view_node']['alter']['absolute'] = 0;
  $handler->display->display_options['fields']['view_node']['alter']['replace_spaces'] = 0;
  $handler->display->display_options['fields']['view_node']['alter']['trim_whitespace'] = 0;
  $handler->display->display_options['fields']['view_node']['alter']['nl2br'] = 0;
  $handler->display->display_options['fields']['view_node']['alter']['word_boundary'] = 1;
  $handler->display->display_options['fields']['view_node']['alter']['ellipsis'] = 1;
  $handler->display->display_options['fields']['view_node']['alter']['strip_tags'] = 0;
  $handler->display->display_options['fields']['view_node']['alter']['trim'] = 0;
  $handler->display->display_options['fields']['view_node']['alter']['html'] = 0;
  $handler->display->display_options['fields']['view_node']['element_type'] = 'div';
  $handler->display->display_options['fields']['view_node']['element_class'] = 'blue-link-wrapper right-side';
  $handler->display->display_options['fields']['view_node']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['view_node']['element_default_classes'] = 1;
  $handler->display->display_options['fields']['view_node']['hide_empty'] = 1;
  $handler->display->display_options['fields']['view_node']['empty_zero'] = 0;
  $handler->display->display_options['fields']['view_node']['hide_alter_empty'] = 1;
  $handler->display->display_options['fields']['view_node']['text'] = 'Rewritten';
  $handler->display->display_options['block_description'] = 'Features';

  /* Display: Block: Features Index */
  $handler = $view->new_display('block', 'Block: Features Index', 'index');
  $handler->display->display_options['defaults']['style_plugin'] = FALSE;
  $handler->display->display_options['style_plugin'] = 'list';
  $handler->display->display_options['defaults']['style_options'] = FALSE;
  $handler->display->display_options['defaults']['row_plugin'] = FALSE;
  $handler->display->display_options['row_plugin'] = 'fields';
  $handler->display->display_options['row_options']['hide_empty'] = 0;
  $handler->display->display_options['row_options']['default_field_elements'] = 1;
  $handler->display->display_options['defaults']['row_options'] = FALSE;
  $handler->display->display_options['defaults']['fields'] = FALSE;
  /* Field: Content: Title */
  $handler->display->display_options['fields']['title']['id'] = 'title';
  $handler->display->display_options['fields']['title']['table'] = 'node';
  $handler->display->display_options['fields']['title']['field'] = 'title';
  $handler->display->display_options['fields']['title']['label'] = '';
  $handler->display->display_options['fields']['title']['link_to_node'] = 1;

  /* Display: Admin Page: Set Order */
  $handler = $view->new_display('page', 'Admin Page: Set Order', 'page_1');
  $handler->display->display_options['defaults']['title'] = FALSE;
  $handler->display->display_options['title'] = 'Set Home Features Sort Order';
  $handler->display->display_options['defaults']['access'] = FALSE;
  $handler->display->display_options['access']['type'] = 'role';
  $handler->display->display_options['access']['role'] = array(
    3 => '3',
    4 => '4',
  );
  $handler->display->display_options['defaults']['style_plugin'] = FALSE;
  $handler->display->display_options['style_plugin'] = 'draggabletable';
  $handler->display->display_options['style_options']['columns'] = array(
    'title' => 'title',
    'value0' => 'value0',
    'created' => 'created',
    'changed' => 'changed',
    'status' => 'status',
    'field_background_image' => 'field_background_image',
  );
  $handler->display->display_options['style_options']['default'] = -1;
  $handler->display->display_options['style_options']['info'] = array(
    'title' => array(
      'sortable' => 0,
      'default_sort_order' => 'asc',
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
    'created' => array(
      'sortable' => 0,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'changed' => array(
      'sortable' => 0,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'status' => array(
      'sortable' => 0,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'field_background_image' => array(
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
  $handler->display->display_options['defaults']['header'] = FALSE;
  /* Header: Global: Text area */
  $handler->display->display_options['header']['area']['id'] = 'area';
  $handler->display->display_options['header']['area']['table'] = 'views';
  $handler->display->display_options['header']['area']['field'] = 'area';
  $handler->display->display_options['header']['area']['label'] = 'Admin Links';
  $handler->display->display_options['header']['area']['empty'] = TRUE;
  $handler->display->display_options['header']['area']['content'] = '<ul class="action-links links clearfix">
  <li><a href="/node/add/home-page-feature">Add New Home Page Feature</a></li>
</ul>
<div class="clearfix"></div>
';
  $handler->display->display_options['header']['area']['format'] = 'page_code';
  $handler->display->display_options['header']['area']['tokenize'] = 0;
  $handler->display->display_options['defaults']['fields'] = FALSE;
  /* Field: Content: Background Image */
  $handler->display->display_options['fields']['field_background_image']['id'] = 'field_background_image';
  $handler->display->display_options['fields']['field_background_image']['table'] = 'field_data_field_background_image';
  $handler->display->display_options['fields']['field_background_image']['field'] = 'field_background_image';
  $handler->display->display_options['fields']['field_background_image']['label'] = '';
  $handler->display->display_options['fields']['field_background_image']['alter']['alter_text'] = 0;
  $handler->display->display_options['fields']['field_background_image']['alter']['make_link'] = 0;
  $handler->display->display_options['fields']['field_background_image']['alter']['absolute'] = 0;
  $handler->display->display_options['fields']['field_background_image']['alter']['external'] = 0;
  $handler->display->display_options['fields']['field_background_image']['alter']['replace_spaces'] = 0;
  $handler->display->display_options['fields']['field_background_image']['alter']['trim_whitespace'] = 0;
  $handler->display->display_options['fields']['field_background_image']['alter']['nl2br'] = 0;
  $handler->display->display_options['fields']['field_background_image']['alter']['word_boundary'] = 1;
  $handler->display->display_options['fields']['field_background_image']['alter']['ellipsis'] = 1;
  $handler->display->display_options['fields']['field_background_image']['alter']['strip_tags'] = 0;
  $handler->display->display_options['fields']['field_background_image']['alter']['trim'] = 0;
  $handler->display->display_options['fields']['field_background_image']['alter']['html'] = 0;
  $handler->display->display_options['fields']['field_background_image']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['field_background_image']['element_default_classes'] = 1;
  $handler->display->display_options['fields']['field_background_image']['hide_empty'] = 0;
  $handler->display->display_options['fields']['field_background_image']['empty_zero'] = 0;
  $handler->display->display_options['fields']['field_background_image']['hide_alter_empty'] = 1;
  $handler->display->display_options['fields']['field_background_image']['click_sort_column'] = 'fid';
  $handler->display->display_options['fields']['field_background_image']['settings'] = array(
    'image_style' => 'thumbnail',
    'image_link' => '',
  );
  $handler->display->display_options['fields']['field_background_image']['group_column'] = 'fid';
  $handler->display->display_options['fields']['field_background_image']['field_api_classes'] = 0;
  /* Field: Content: Title */
  $handler->display->display_options['fields']['title']['id'] = 'title';
  $handler->display->display_options['fields']['title']['table'] = 'node';
  $handler->display->display_options['fields']['title']['field'] = 'title';
  $handler->display->display_options['fields']['title']['label'] = '';
  $handler->display->display_options['fields']['title']['link_to_node'] = 1;
  /* Field: Content translation: Language */
  $handler->display->display_options['fields']['language']['id'] = 'language';
  $handler->display->display_options['fields']['language']['table'] = 'node';
  $handler->display->display_options['fields']['language']['field'] = 'language';
  $handler->display->display_options['fields']['language']['alter']['alter_text'] = 0;
  $handler->display->display_options['fields']['language']['alter']['make_link'] = 0;
  $handler->display->display_options['fields']['language']['alter']['absolute'] = 0;
  $handler->display->display_options['fields']['language']['alter']['external'] = 0;
  $handler->display->display_options['fields']['language']['alter']['replace_spaces'] = 0;
  $handler->display->display_options['fields']['language']['alter']['trim_whitespace'] = 0;
  $handler->display->display_options['fields']['language']['alter']['nl2br'] = 0;
  $handler->display->display_options['fields']['language']['alter']['word_boundary'] = 1;
  $handler->display->display_options['fields']['language']['alter']['ellipsis'] = 1;
  $handler->display->display_options['fields']['language']['alter']['strip_tags'] = 0;
  $handler->display->display_options['fields']['language']['alter']['trim'] = 0;
  $handler->display->display_options['fields']['language']['alter']['html'] = 0;
  $handler->display->display_options['fields']['language']['element_label_colon'] = 1;
  $handler->display->display_options['fields']['language']['element_default_classes'] = 1;
  $handler->display->display_options['fields']['language']['hide_empty'] = 0;
  $handler->display->display_options['fields']['language']['empty_zero'] = 0;
  $handler->display->display_options['fields']['language']['hide_alter_empty'] = 1;
  $handler->display->display_options['fields']['language']['link_to_node'] = 0;
  $handler->display->display_options['fields']['language']['native_language'] = 0;
  /* Field: Content: Post date */
  $handler->display->display_options['fields']['created']['id'] = 'created';
  $handler->display->display_options['fields']['created']['table'] = 'node';
  $handler->display->display_options['fields']['created']['field'] = 'created';
  $handler->display->display_options['fields']['created']['alter']['alter_text'] = 0;
  $handler->display->display_options['fields']['created']['alter']['make_link'] = 0;
  $handler->display->display_options['fields']['created']['alter']['absolute'] = 0;
  $handler->display->display_options['fields']['created']['alter']['external'] = 0;
  $handler->display->display_options['fields']['created']['alter']['replace_spaces'] = 0;
  $handler->display->display_options['fields']['created']['alter']['trim_whitespace'] = 0;
  $handler->display->display_options['fields']['created']['alter']['nl2br'] = 0;
  $handler->display->display_options['fields']['created']['alter']['word_boundary'] = 1;
  $handler->display->display_options['fields']['created']['alter']['ellipsis'] = 1;
  $handler->display->display_options['fields']['created']['alter']['strip_tags'] = 0;
  $handler->display->display_options['fields']['created']['alter']['trim'] = 0;
  $handler->display->display_options['fields']['created']['alter']['html'] = 0;
  $handler->display->display_options['fields']['created']['element_label_colon'] = 1;
  $handler->display->display_options['fields']['created']['element_default_classes'] = 1;
  $handler->display->display_options['fields']['created']['hide_empty'] = 0;
  $handler->display->display_options['fields']['created']['empty_zero'] = 0;
  $handler->display->display_options['fields']['created']['hide_alter_empty'] = 1;
  $handler->display->display_options['fields']['created']['date_format'] = 'short';
  /* Field: Content: Updated date */
  $handler->display->display_options['fields']['changed']['id'] = 'changed';
  $handler->display->display_options['fields']['changed']['table'] = 'node';
  $handler->display->display_options['fields']['changed']['field'] = 'changed';
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
  /* Field: Content: Published */
  $handler->display->display_options['fields']['status']['id'] = 'status';
  $handler->display->display_options['fields']['status']['table'] = 'node';
  $handler->display->display_options['fields']['status']['field'] = 'status';
  $handler->display->display_options['fields']['status']['alter']['alter_text'] = 0;
  $handler->display->display_options['fields']['status']['alter']['make_link'] = 0;
  $handler->display->display_options['fields']['status']['alter']['absolute'] = 0;
  $handler->display->display_options['fields']['status']['alter']['external'] = 0;
  $handler->display->display_options['fields']['status']['alter']['replace_spaces'] = 0;
  $handler->display->display_options['fields']['status']['alter']['trim_whitespace'] = 0;
  $handler->display->display_options['fields']['status']['alter']['nl2br'] = 0;
  $handler->display->display_options['fields']['status']['alter']['word_boundary'] = 1;
  $handler->display->display_options['fields']['status']['alter']['ellipsis'] = 1;
  $handler->display->display_options['fields']['status']['alter']['strip_tags'] = 0;
  $handler->display->display_options['fields']['status']['alter']['trim'] = 0;
  $handler->display->display_options['fields']['status']['alter']['html'] = 0;
  $handler->display->display_options['fields']['status']['element_label_colon'] = 1;
  $handler->display->display_options['fields']['status']['element_default_classes'] = 1;
  $handler->display->display_options['fields']['status']['hide_empty'] = 0;
  $handler->display->display_options['fields']['status']['empty_zero'] = 0;
  $handler->display->display_options['fields']['status']['hide_alter_empty'] = 1;
  $handler->display->display_options['fields']['status']['not'] = 0;
  /* Field: DraggableViews: Order */
  $handler->display->display_options['fields']['value0']['id'] = 'value0';
  $handler->display->display_options['fields']['value0']['table'] = 'draggableviews_structure_node0';
  $handler->display->display_options['fields']['value0']['field'] = 'value0';
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
  $handler->display->display_options['fields']['value0']['element_label_colon'] = 1;
  $handler->display->display_options['fields']['value0']['element_default_classes'] = 1;
  $handler->display->display_options['fields']['value0']['hide_empty'] = 0;
  $handler->display->display_options['fields']['value0']['empty_zero'] = 0;
  $handler->display->display_options['fields']['value0']['hide_alter_empty'] = 1;
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
  $handler->display->display_options['defaults']['filters'] = FALSE;
  /* Filter criterion: Content: Type */
  $handler->display->display_options['filters']['type']['id'] = 'type';
  $handler->display->display_options['filters']['type']['table'] = 'node';
  $handler->display->display_options['filters']['type']['field'] = 'type';
  $handler->display->display_options['filters']['type']['value'] = array(
    'home_page_feature' => 'home_page_feature',
  );
  $handler->display->display_options['filters']['type']['group'] = 1;
  $handler->display->display_options['filters']['type']['exposed'] = TRUE;
  $handler->display->display_options['filters']['type']['expose']['operator_id'] = 'type_op';
  $handler->display->display_options['filters']['type']['expose']['label'] = 'Type';
  $handler->display->display_options['filters']['type']['expose']['use_operator'] = FALSE;
  $handler->display->display_options['filters']['type']['expose']['operator'] = 'type_op';
  $handler->display->display_options['filters']['type']['expose']['identifier'] = 'type';
  $handler->display->display_options['filters']['type']['expose']['required'] = FALSE;
  $handler->display->display_options['filters']['type']['expose']['remember'] = FALSE;
  $handler->display->display_options['filters']['type']['expose']['multiple'] = FALSE;
  /* Filter criterion: Content: Published */
  $handler->display->display_options['filters']['status']['id'] = 'status';
  $handler->display->display_options['filters']['status']['table'] = 'node';
  $handler->display->display_options['filters']['status']['field'] = 'status';
  $handler->display->display_options['filters']['status']['value'] = '1';
  $handler->display->display_options['filters']['status']['group'] = 1;
  $handler->display->display_options['path'] = 'admin/order-home-features';
  $handler->display->display_options['menu']['type'] = 'normal';
  $handler->display->display_options['menu']['title'] = 'Manage Home Page Features';
  $handler->display->display_options['menu']['weight'] = '0';
  $handler->display->display_options['menu']['name'] = 'menu-content-admin';

  /* Display: Admin: References */
  $handler = $view->new_display('references', 'Admin: References', 'references_1');
  $handler->display->display_options['defaults']['title'] = FALSE;
  $handler->display->display_options['pager']['type'] = 'some';
  $handler->display->display_options['defaults']['style_plugin'] = FALSE;
  $handler->display->display_options['style_plugin'] = 'references_style';
  $handler->display->display_options['defaults']['style_options'] = FALSE;
  $handler->display->display_options['defaults']['row_plugin'] = FALSE;
  $handler->display->display_options['row_plugin'] = 'references_fields';
  $handler->display->display_options['defaults']['row_options'] = FALSE;
  $handler->display->display_options['defaults']['relationships'] = FALSE;
  $handler->display->display_options['defaults']['fields'] = FALSE;
  /* Field: Content: Type */
  $handler->display->display_options['fields']['type']['id'] = 'type';
  $handler->display->display_options['fields']['type']['table'] = 'node';
  $handler->display->display_options['fields']['type']['field'] = 'type';
  $handler->display->display_options['fields']['type']['label'] = '';
  $handler->display->display_options['fields']['type']['alter']['alter_text'] = 0;
  $handler->display->display_options['fields']['type']['alter']['make_link'] = 0;
  $handler->display->display_options['fields']['type']['alter']['absolute'] = 0;
  $handler->display->display_options['fields']['type']['alter']['external'] = 0;
  $handler->display->display_options['fields']['type']['alter']['replace_spaces'] = 0;
  $handler->display->display_options['fields']['type']['alter']['trim_whitespace'] = 0;
  $handler->display->display_options['fields']['type']['alter']['nl2br'] = 0;
  $handler->display->display_options['fields']['type']['alter']['word_boundary'] = 1;
  $handler->display->display_options['fields']['type']['alter']['ellipsis'] = 1;
  $handler->display->display_options['fields']['type']['alter']['strip_tags'] = 0;
  $handler->display->display_options['fields']['type']['alter']['trim'] = 0;
  $handler->display->display_options['fields']['type']['alter']['html'] = 0;
  $handler->display->display_options['fields']['type']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['type']['element_default_classes'] = 1;
  $handler->display->display_options['fields']['type']['hide_empty'] = 0;
  $handler->display->display_options['fields']['type']['empty_zero'] = 0;
  $handler->display->display_options['fields']['type']['hide_alter_empty'] = 1;
  $handler->display->display_options['fields']['type']['link_to_node'] = 0;
  $handler->display->display_options['fields']['type']['machine_name'] = 0;
  /* Field: Content translation: Language */
  $handler->display->display_options['fields']['language']['id'] = 'language';
  $handler->display->display_options['fields']['language']['table'] = 'node';
  $handler->display->display_options['fields']['language']['field'] = 'language';
  $handler->display->display_options['fields']['language']['label'] = '';
  $handler->display->display_options['fields']['language']['alter']['alter_text'] = 0;
  $handler->display->display_options['fields']['language']['alter']['make_link'] = 0;
  $handler->display->display_options['fields']['language']['alter']['absolute'] = 0;
  $handler->display->display_options['fields']['language']['alter']['external'] = 0;
  $handler->display->display_options['fields']['language']['alter']['replace_spaces'] = 0;
  $handler->display->display_options['fields']['language']['alter']['trim_whitespace'] = 0;
  $handler->display->display_options['fields']['language']['alter']['nl2br'] = 0;
  $handler->display->display_options['fields']['language']['alter']['word_boundary'] = 1;
  $handler->display->display_options['fields']['language']['alter']['ellipsis'] = 1;
  $handler->display->display_options['fields']['language']['alter']['strip_tags'] = 0;
  $handler->display->display_options['fields']['language']['alter']['trim'] = 0;
  $handler->display->display_options['fields']['language']['alter']['html'] = 0;
  $handler->display->display_options['fields']['language']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['language']['element_default_classes'] = 1;
  $handler->display->display_options['fields']['language']['hide_empty'] = 0;
  $handler->display->display_options['fields']['language']['empty_zero'] = 0;
  $handler->display->display_options['fields']['language']['hide_alter_empty'] = 1;
  $handler->display->display_options['fields']['language']['link_to_node'] = 0;
  $handler->display->display_options['fields']['language']['native_language'] = 0;
  /* Field: Content: Title */
  $handler->display->display_options['fields']['title']['id'] = 'title';
  $handler->display->display_options['fields']['title']['table'] = 'node';
  $handler->display->display_options['fields']['title']['field'] = 'title';
  $handler->display->display_options['fields']['title']['label'] = '';
  $handler->display->display_options['fields']['title']['link_to_node'] = 1;
  $handler->display->display_options['defaults']['sorts'] = FALSE;
  /* Sort criterion: Content: Type */
  $handler->display->display_options['sorts']['type']['id'] = 'type';
  $handler->display->display_options['sorts']['type']['table'] = 'node';
  $handler->display->display_options['sorts']['type']['field'] = 'type';
  /* Sort criterion: Content: Title */
  $handler->display->display_options['sorts']['title']['id'] = 'title';
  $handler->display->display_options['sorts']['title']['table'] = 'node';
  $handler->display->display_options['sorts']['title']['field'] = 'title';
  $handler->display->display_options['sorts']['title']['exposed'] = TRUE;
  $handler->display->display_options['sorts']['title']['expose']['label'] = 'Title';
  /* Sort criterion: Content: Post date */
  $handler->display->display_options['sorts']['created']['id'] = 'created';
  $handler->display->display_options['sorts']['created']['table'] = 'node';
  $handler->display->display_options['sorts']['created']['field'] = 'created';
  $handler->display->display_options['sorts']['created']['exposed'] = TRUE;
  $handler->display->display_options['sorts']['created']['expose']['label'] = 'Post date';
  $handler->display->display_options['defaults']['arguments'] = FALSE;
  /* Contextual filter: Content translation: Language */
  $handler->display->display_options['arguments']['language']['id'] = 'language';
  $handler->display->display_options['arguments']['language']['table'] = 'node';
  $handler->display->display_options['arguments']['language']['field'] = 'language';
  $handler->display->display_options['arguments']['language']['default_argument_type'] = 'fixed';
  $handler->display->display_options['arguments']['language']['default_argument_skip_url'] = 0;
  $handler->display->display_options['arguments']['language']['summary']['number_of_records'] = '0';
  $handler->display->display_options['arguments']['language']['summary']['format'] = 'default_summary';
  $handler->display->display_options['arguments']['language']['summary_options']['items_per_page'] = '25';
  $handler->display->display_options['defaults']['filters'] = FALSE;
  /* Filter criterion: Content: Type */
  $handler->display->display_options['filters']['type']['id'] = 'type';
  $handler->display->display_options['filters']['type']['table'] = 'node';
  $handler->display->display_options['filters']['type']['field'] = 'type';
  $handler->display->display_options['filters']['type']['value'] = array(
    'page' => 'page',
    'ceo_message' => 'ceo_message',
    'page_code' => 'page_code',
    'media_videos' => 'media_videos',
    'webform' => 'webform',
  );
  $handler->display->display_options['filters']['type']['group'] = 1;
  $handler->display->display_options['filters']['type']['expose']['operator_id'] = 'type_op';
  $handler->display->display_options['filters']['type']['expose']['label'] = 'Type';
  $handler->display->display_options['filters']['type']['expose']['operator'] = 'type_op';
  $handler->display->display_options['filters']['type']['expose']['identifier'] = 'type';
  $handler->display->display_options['filters']['type']['expose']['reduce'] = 0;
  /* Filter criterion: Content: Published */
  $handler->display->display_options['filters']['status']['id'] = 'status';
  $handler->display->display_options['filters']['status']['table'] = 'node';
  $handler->display->display_options['filters']['status']['field'] = 'status';
  $handler->display->display_options['filters']['status']['value'] = '1';
  $handler->display->display_options['filters']['status']['group'] = 1;
  $translatables['front_features'] = array(
    t('Defaults'),
    t('Features'),
    t('more'),
    t('Apply'),
    t('Reset'),
    t('Sort by'),
    t('Asc'),
    t('Desc'),
    t('field_content_reference'),
    t('field_content_reference_2'),
    t('Background Image'),
    t('Type'),
    t('Block: Home Features'),
    t('[path]'),
    t('[field_link_text_1]'),
    t('Rewritten'),
    t('[field_link_text_2]'),
    t('Block: Features Index'),
    t('Admin Page: Set Order'),
    t('Set Home Features Sort Order'),
    t('Admin Links'),
    t('<ul class="action-links links clearfix">
  <li><a href="/node/add/home-page-feature">Add New Home Page Feature</a></li>
</ul>
<div class="clearfix"></div>
'),
    t('Language'),
    t('Post date'),
    t('Updated date'),
    t('Published'),
    t('Order'),
    t('Operations'),
    t('Admin: References'),
    t('Title'),
    t('All'),
  );
  $export['front_features'] = $view;

  $view = new view;
  $view->name = 'home_small_feature';
  $view->description = '';
  $view->tag = 'default';
  $view->base_table = 'node';
  $view->human_name = 'Home Small Feature';
  $view->core = 7;
  $view->api_version = '3.0';
  $view->disabled = FALSE; /* Edit this to true to make a default view disabled initially */

  /* Display: Master */
  $handler = $view->new_display('default', 'Master', 'default');
  $handler->display->display_options['title'] = 'front_news';
  $handler->display->display_options['css_class'] = 'view-style-horizontal-thumbs';
  $handler->display->display_options['use_ajax'] = TRUE;
  $handler->display->display_options['access']['type'] = 'perm';
  $handler->display->display_options['cache']['type'] = 'none';
  $handler->display->display_options['query']['type'] = 'views_query';
  $handler->display->display_options['query']['options']['query_comment'] = FALSE;
  $handler->display->display_options['exposed_form']['type'] = 'basic';
  $handler->display->display_options['pager']['type'] = 'mini';
  $handler->display->display_options['pager']['options']['items_per_page'] = '12';
  $handler->display->display_options['pager']['options']['offset'] = '0';
  $handler->display->display_options['pager']['options']['id'] = '0';
  $handler->display->display_options['pager']['options']['expose']['items_per_page_options_all'] = 0;
  $handler->display->display_options['style_plugin'] = 'list';
  $handler->display->display_options['style_options']['class'] = 'item-list';
  $handler->display->display_options['row_plugin'] = 'fields';
  $handler->display->display_options['row_options']['hide_empty'] = 0;
  $handler->display->display_options['row_options']['default_field_elements'] = 1;
  /* Relationship: Nodequeue: Queue */
  $handler->display->display_options['relationships']['nodequeue_rel']['id'] = 'nodequeue_rel';
  $handler->display->display_options['relationships']['nodequeue_rel']['table'] = 'node';
  $handler->display->display_options['relationships']['nodequeue_rel']['field'] = 'nodequeue_rel';
  /* Field: [path] */
  $handler->display->display_options['fields']['path']['id'] = 'path';
  $handler->display->display_options['fields']['path']['table'] = 'node';
  $handler->display->display_options['fields']['path']['field'] = 'path';
  $handler->display->display_options['fields']['path']['ui_name'] = '[path]';
  $handler->display->display_options['fields']['path']['label'] = '';
  $handler->display->display_options['fields']['path']['exclude'] = TRUE;
  $handler->display->display_options['fields']['path']['alter']['alter_text'] = 0;
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
  $handler->display->display_options['fields']['path']['absolute'] = 1;
  /* Field: Page Title */
  $handler->display->display_options['fields']['title_1']['id'] = 'title_1';
  $handler->display->display_options['fields']['title_1']['table'] = 'node';
  $handler->display->display_options['fields']['title_1']['field'] = 'title';
  $handler->display->display_options['fields']['title_1']['ui_name'] = 'Page Title';
  $handler->display->display_options['fields']['title_1']['label'] = '';
  $handler->display->display_options['fields']['title_1']['alter']['alter_text'] = 0;
  $handler->display->display_options['fields']['title_1']['alter']['make_link'] = 0;
  $handler->display->display_options['fields']['title_1']['alter']['absolute'] = 0;
  $handler->display->display_options['fields']['title_1']['alter']['external'] = 0;
  $handler->display->display_options['fields']['title_1']['alter']['replace_spaces'] = 0;
  $handler->display->display_options['fields']['title_1']['alter']['trim_whitespace'] = 0;
  $handler->display->display_options['fields']['title_1']['alter']['nl2br'] = 0;
  $handler->display->display_options['fields']['title_1']['alter']['max_length'] = '25';
  $handler->display->display_options['fields']['title_1']['alter']['word_boundary'] = 0;
  $handler->display->display_options['fields']['title_1']['alter']['ellipsis'] = 0;
  $handler->display->display_options['fields']['title_1']['alter']['strip_tags'] = 0;
  $handler->display->display_options['fields']['title_1']['alter']['trim'] = 1;
  $handler->display->display_options['fields']['title_1']['alter']['html'] = 0;
  $handler->display->display_options['fields']['title_1']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['title_1']['element_default_classes'] = 1;
  $handler->display->display_options['fields']['title_1']['hide_empty'] = 0;
  $handler->display->display_options['fields']['title_1']['empty_zero'] = 0;
  $handler->display->display_options['fields']['title_1']['hide_alter_empty'] = 1;
  $handler->display->display_options['fields']['title_1']['link_to_node'] = 1;
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
  $handler->display->display_options['fields']['field_date_event']['empty'] = 'no-date';
  $handler->display->display_options['fields']['field_date_event']['hide_empty'] = 0;
  $handler->display->display_options['fields']['field_date_event']['empty_zero'] = 0;
  $handler->display->display_options['fields']['field_date_event']['hide_alter_empty'] = 0;
  $handler->display->display_options['fields']['field_date_event']['settings'] = array(
    'format_type' => 'short_simple',
    'fromto' => 'both',
    'multiple_number' => '',
    'multiple_from' => '',
    'multiple_to' => '',
  );
  $handler->display->display_options['fields']['field_date_event']['field_api_classes'] = 0;
  /* Field: Content: Type */
  $handler->display->display_options['fields']['type']['id'] = 'type';
  $handler->display->display_options['fields']['type']['table'] = 'node';
  $handler->display->display_options['fields']['type']['field'] = 'type';
  $handler->display->display_options['fields']['type']['label'] = '';
  $handler->display->display_options['fields']['type']['alter']['alter_text'] = 0;
  $handler->display->display_options['fields']['type']['alter']['text'] = 'in [type]';
  $handler->display->display_options['fields']['type']['alter']['make_link'] = 0;
  $handler->display->display_options['fields']['type']['alter']['absolute'] = 0;
  $handler->display->display_options['fields']['type']['alter']['external'] = 0;
  $handler->display->display_options['fields']['type']['alter']['replace_spaces'] = 0;
  $handler->display->display_options['fields']['type']['alter']['trim_whitespace'] = 0;
  $handler->display->display_options['fields']['type']['alter']['nl2br'] = 0;
  $handler->display->display_options['fields']['type']['alter']['word_boundary'] = 1;
  $handler->display->display_options['fields']['type']['alter']['ellipsis'] = 1;
  $handler->display->display_options['fields']['type']['alter']['strip_tags'] = 0;
  $handler->display->display_options['fields']['type']['alter']['trim'] = 0;
  $handler->display->display_options['fields']['type']['alter']['html'] = 0;
  $handler->display->display_options['fields']['type']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['type']['element_default_classes'] = 1;
  $handler->display->display_options['fields']['type']['hide_empty'] = 0;
  $handler->display->display_options['fields']['type']['empty_zero'] = 0;
  $handler->display->display_options['fields']['type']['hide_alter_empty'] = 1;
  $handler->display->display_options['fields']['type']['link_to_node'] = 0;
  $handler->display->display_options['fields']['type']['machine_name'] = 0;
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
    'image_style' => 'media_thumbnail_standard',
    'image_link' => 'content',
  );
  $handler->display->display_options['fields']['field_image']['field_api_classes'] = 0;
  /* Field: Content: Title */
  $handler->display->display_options['fields']['title']['id'] = 'title';
  $handler->display->display_options['fields']['title']['table'] = 'node';
  $handler->display->display_options['fields']['title']['field'] = 'title';
  $handler->display->display_options['fields']['title']['label'] = '';
  $handler->display->display_options['fields']['title']['exclude'] = TRUE;
  $handler->display->display_options['fields']['title']['alter']['alter_text'] = 0;
  $handler->display->display_options['fields']['title']['alter']['make_link'] = 0;
  $handler->display->display_options['fields']['title']['alter']['absolute'] = 0;
  $handler->display->display_options['fields']['title']['alter']['external'] = 0;
  $handler->display->display_options['fields']['title']['alter']['replace_spaces'] = 0;
  $handler->display->display_options['fields']['title']['alter']['trim_whitespace'] = 0;
  $handler->display->display_options['fields']['title']['alter']['nl2br'] = 0;
  $handler->display->display_options['fields']['title']['alter']['max_length'] = '40';
  $handler->display->display_options['fields']['title']['alter']['word_boundary'] = 1;
  $handler->display->display_options['fields']['title']['alter']['ellipsis'] = 1;
  $handler->display->display_options['fields']['title']['alter']['strip_tags'] = 1;
  $handler->display->display_options['fields']['title']['alter']['trim'] = 1;
  $handler->display->display_options['fields']['title']['alter']['html'] = 0;
  $handler->display->display_options['fields']['title']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['title']['element_default_classes'] = 1;
  $handler->display->display_options['fields']['title']['hide_empty'] = 0;
  $handler->display->display_options['fields']['title']['empty_zero'] = 0;
  $handler->display->display_options['fields']['title']['hide_alter_empty'] = 1;
  $handler->display->display_options['fields']['title']['link_to_node'] = 0;
  /* Field: Content: Short Title */
  $handler->display->display_options['fields']['field_short_title']['id'] = 'field_short_title';
  $handler->display->display_options['fields']['field_short_title']['table'] = 'field_data_field_short_title';
  $handler->display->display_options['fields']['field_short_title']['field'] = 'field_short_title';
  $handler->display->display_options['fields']['field_short_title']['label'] = '';
  $handler->display->display_options['fields']['field_short_title']['alter']['alter_text'] = 0;
  $handler->display->display_options['fields']['field_short_title']['alter']['make_link'] = 0;
  $handler->display->display_options['fields']['field_short_title']['alter']['absolute'] = 0;
  $handler->display->display_options['fields']['field_short_title']['alter']['external'] = 0;
  $handler->display->display_options['fields']['field_short_title']['alter']['replace_spaces'] = 0;
  $handler->display->display_options['fields']['field_short_title']['alter']['trim_whitespace'] = 0;
  $handler->display->display_options['fields']['field_short_title']['alter']['nl2br'] = 0;
  $handler->display->display_options['fields']['field_short_title']['alter']['max_length'] = '50';
  $handler->display->display_options['fields']['field_short_title']['alter']['word_boundary'] = 1;
  $handler->display->display_options['fields']['field_short_title']['alter']['ellipsis'] = 1;
  $handler->display->display_options['fields']['field_short_title']['alter']['strip_tags'] = 0;
  $handler->display->display_options['fields']['field_short_title']['alter']['trim'] = 1;
  $handler->display->display_options['fields']['field_short_title']['alter']['html'] = 0;
  $handler->display->display_options['fields']['field_short_title']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['field_short_title']['element_default_classes'] = 1;
  $handler->display->display_options['fields']['field_short_title']['empty'] = '[title]';
  $handler->display->display_options['fields']['field_short_title']['hide_empty'] = 0;
  $handler->display->display_options['fields']['field_short_title']['empty_zero'] = 0;
  $handler->display->display_options['fields']['field_short_title']['hide_alter_empty'] = 0;
  $handler->display->display_options['fields']['field_short_title']['field_api_classes'] = 0;
  /* Field: Content: Body */
  $handler->display->display_options['fields']['body']['id'] = 'body';
  $handler->display->display_options['fields']['body']['table'] = 'field_data_body';
  $handler->display->display_options['fields']['body']['field'] = 'body';
  $handler->display->display_options['fields']['body']['label'] = '';
  $handler->display->display_options['fields']['body']['exclude'] = TRUE;
  $handler->display->display_options['fields']['body']['alter']['alter_text'] = 0;
  $handler->display->display_options['fields']['body']['alter']['make_link'] = 0;
  $handler->display->display_options['fields']['body']['alter']['absolute'] = 0;
  $handler->display->display_options['fields']['body']['alter']['external'] = 0;
  $handler->display->display_options['fields']['body']['alter']['replace_spaces'] = 0;
  $handler->display->display_options['fields']['body']['alter']['trim_whitespace'] = 0;
  $handler->display->display_options['fields']['body']['alter']['nl2br'] = 0;
  $handler->display->display_options['fields']['body']['alter']['word_boundary'] = 1;
  $handler->display->display_options['fields']['body']['alter']['ellipsis'] = 1;
  $handler->display->display_options['fields']['body']['alter']['strip_tags'] = 0;
  $handler->display->display_options['fields']['body']['alter']['trim'] = 0;
  $handler->display->display_options['fields']['body']['alter']['html'] = 0;
  $handler->display->display_options['fields']['body']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['body']['element_default_classes'] = 1;
  $handler->display->display_options['fields']['body']['hide_empty'] = 0;
  $handler->display->display_options['fields']['body']['empty_zero'] = 0;
  $handler->display->display_options['fields']['body']['hide_alter_empty'] = 1;
  $handler->display->display_options['fields']['body']['type'] = 'text_trimmed';
  $handler->display->display_options['fields']['body']['settings'] = array(
    'trim_length' => '50',
  );
  $handler->display->display_options['fields']['body']['field_api_classes'] = 0;
  /* Field: Content: Summary for Featuring */
  $handler->display->display_options['fields']['field_featured_summary']['id'] = 'field_featured_summary';
  $handler->display->display_options['fields']['field_featured_summary']['table'] = 'field_data_field_featured_summary';
  $handler->display->display_options['fields']['field_featured_summary']['field'] = 'field_featured_summary';
  $handler->display->display_options['fields']['field_featured_summary']['label'] = '';
  $handler->display->display_options['fields']['field_featured_summary']['alter']['alter_text'] = 0;
  $handler->display->display_options['fields']['field_featured_summary']['alter']['make_link'] = 0;
  $handler->display->display_options['fields']['field_featured_summary']['alter']['absolute'] = 0;
  $handler->display->display_options['fields']['field_featured_summary']['alter']['external'] = 0;
  $handler->display->display_options['fields']['field_featured_summary']['alter']['replace_spaces'] = 0;
  $handler->display->display_options['fields']['field_featured_summary']['alter']['trim_whitespace'] = 0;
  $handler->display->display_options['fields']['field_featured_summary']['alter']['nl2br'] = 0;
  $handler->display->display_options['fields']['field_featured_summary']['alter']['max_length'] = '50';
  $handler->display->display_options['fields']['field_featured_summary']['alter']['word_boundary'] = 1;
  $handler->display->display_options['fields']['field_featured_summary']['alter']['ellipsis'] = 1;
  $handler->display->display_options['fields']['field_featured_summary']['alter']['strip_tags'] = 0;
  $handler->display->display_options['fields']['field_featured_summary']['alter']['trim'] = 1;
  $handler->display->display_options['fields']['field_featured_summary']['alter']['html'] = 0;
  $handler->display->display_options['fields']['field_featured_summary']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['field_featured_summary']['element_default_classes'] = 1;
  $handler->display->display_options['fields']['field_featured_summary']['empty'] = '[body]';
  $handler->display->display_options['fields']['field_featured_summary']['hide_empty'] = 0;
  $handler->display->display_options['fields']['field_featured_summary']['empty_zero'] = 0;
  $handler->display->display_options['fields']['field_featured_summary']['hide_alter_empty'] = 0;
  $handler->display->display_options['fields']['field_featured_summary']['field_api_classes'] = 0;
  /* Field: Read Link */
  $handler->display->display_options['fields']['view_node']['id'] = 'view_node';
  $handler->display->display_options['fields']['view_node']['table'] = 'views_entity_node';
  $handler->display->display_options['fields']['view_node']['field'] = 'view_node';
  $handler->display->display_options['fields']['view_node']['ui_name'] = 'Read Link';
  $handler->display->display_options['fields']['view_node']['label'] = '';
  $handler->display->display_options['fields']['view_node']['exclude'] = TRUE;
  $handler->display->display_options['fields']['view_node']['alter']['alter_text'] = 0;
  $handler->display->display_options['fields']['view_node']['alter']['text'] = '<a href="[view_node]" title="[title_1]">Read</a>';
  $handler->display->display_options['fields']['view_node']['alter']['make_link'] = 0;
  $handler->display->display_options['fields']['view_node']['alter']['absolute'] = 0;
  $handler->display->display_options['fields']['view_node']['alter']['replace_spaces'] = 0;
  $handler->display->display_options['fields']['view_node']['alter']['trim_whitespace'] = 0;
  $handler->display->display_options['fields']['view_node']['alter']['nl2br'] = 0;
  $handler->display->display_options['fields']['view_node']['alter']['word_boundary'] = 1;
  $handler->display->display_options['fields']['view_node']['alter']['ellipsis'] = 1;
  $handler->display->display_options['fields']['view_node']['alter']['strip_tags'] = 0;
  $handler->display->display_options['fields']['view_node']['alter']['trim'] = 0;
  $handler->display->display_options['fields']['view_node']['alter']['html'] = 0;
  $handler->display->display_options['fields']['view_node']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['view_node']['element_wrapper_type'] = 'div';
  $handler->display->display_options['fields']['view_node']['element_wrapper_class'] = 'blue-link';
  $handler->display->display_options['fields']['view_node']['element_default_classes'] = 0;
  $handler->display->display_options['fields']['view_node']['hide_empty'] = 0;
  $handler->display->display_options['fields']['view_node']['empty_zero'] = 0;
  $handler->display->display_options['fields']['view_node']['hide_alter_empty'] = 1;
  $handler->display->display_options['fields']['view_node']['text'] = 'Read';
  /* Field: Link To Content */
  $handler->display->display_options['fields']['php']['id'] = 'php';
  $handler->display->display_options['fields']['php']['table'] = 'views';
  $handler->display->display_options['fields']['php']['field'] = 'php';
  $handler->display->display_options['fields']['php']['ui_name'] = 'Link To Content';
  $handler->display->display_options['fields']['php']['label'] = '';
  $handler->display->display_options['fields']['php']['alter']['alter_text'] = 0;
  $handler->display->display_options['fields']['php']['alter']['make_link'] = 1;
  $handler->display->display_options['fields']['php']['alter']['path'] = '[path]';
  $handler->display->display_options['fields']['php']['alter']['absolute'] = 0;
  $handler->display->display_options['fields']['php']['alter']['external'] = 0;
  $handler->display->display_options['fields']['php']['alter']['replace_spaces'] = 0;
  $handler->display->display_options['fields']['php']['alter']['trim_whitespace'] = 0;
  $handler->display->display_options['fields']['php']['alter']['nl2br'] = 0;
  $handler->display->display_options['fields']['php']['alter']['word_boundary'] = 1;
  $handler->display->display_options['fields']['php']['alter']['ellipsis'] = 1;
  $handler->display->display_options['fields']['php']['alter']['strip_tags'] = 0;
  $handler->display->display_options['fields']['php']['alter']['trim'] = 0;
  $handler->display->display_options['fields']['php']['alter']['html'] = 0;
  $handler->display->display_options['fields']['php']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['php']['element_wrapper_type'] = 'div';
  $handler->display->display_options['fields']['php']['element_wrapper_class'] = 'blue-link';
  $handler->display->display_options['fields']['php']['element_default_classes'] = 1;
  $handler->display->display_options['fields']['php']['hide_empty'] = 0;
  $handler->display->display_options['fields']['php']['empty_zero'] = 0;
  $handler->display->display_options['fields']['php']['hide_alter_empty'] = 1;
  $handler->display->display_options['fields']['php']['use_php_setup'] = 0;
  $handler->display->display_options['fields']['php']['php_value'] = 'if ($row->type == \'media_videos\') {
  return t(\'Watch Video\');
} else if ($row->type == \'page\' || $row->type==\'page_code\') {
  return t(\'Explore\');
} else {
 return t(\'Read\');
}';
  $handler->display->display_options['fields']['php']['use_php_click_sortable'] = '0';
  $handler->display->display_options['fields']['php']['php_click_sortable'] = '';
  /* Sort criterion: Content: Date Released (field_date_event) */
  $handler->display->display_options['sorts']['field_date_event_value']['id'] = 'field_date_event_value';
  $handler->display->display_options['sorts']['field_date_event_value']['table'] = 'field_data_field_date_event';
  $handler->display->display_options['sorts']['field_date_event_value']['field'] = 'field_date_event_value';
  $handler->display->display_options['sorts']['field_date_event_value']['order'] = 'DESC';
  /* Sort criterion: Nodequeue: Position */
  $handler->display->display_options['sorts']['position']['id'] = 'position';
  $handler->display->display_options['sorts']['position']['table'] = 'nodequeue_nodes';
  $handler->display->display_options['sorts']['position']['field'] = 'position';
  $handler->display->display_options['sorts']['position']['relationship'] = 'nodequeue_rel';
  /* Filter criterion: Content: Published or admin */
  $handler->display->display_options['filters']['status_extra']['id'] = 'status_extra';
  $handler->display->display_options['filters']['status_extra']['table'] = 'node';
  $handler->display->display_options['filters']['status_extra']['field'] = 'status_extra';
  /* Filter criterion: Content translation: Language */
  $handler->display->display_options['filters']['language']['id'] = 'language';
  $handler->display->display_options['filters']['language']['table'] = 'node';
  $handler->display->display_options['filters']['language']['field'] = 'language';
  $handler->display->display_options['filters']['language']['value'] = array(
    '***CURRENT_LANGUAGE***' => '***CURRENT_LANGUAGE***',
    'und' => 'und',
  );

  /* Display: Block: Featured Queue */
  $handler = $view->new_display('block', 'Block: Featured Queue', 'block');
  $handler->display->display_options['defaults']['pager'] = FALSE;
  $handler->display->display_options['pager']['type'] = 'some';
  $handler->display->display_options['pager']['options']['items_per_page'] = '1';
  $handler->display->display_options['pager']['options']['offset'] = '0';
  $handler->display->display_options['defaults']['relationships'] = FALSE;
  /* Relationship: Nodequeue: Queue */
  $handler->display->display_options['relationships']['nodequeue_rel']['id'] = 'nodequeue_rel';
  $handler->display->display_options['relationships']['nodequeue_rel']['table'] = 'node';
  $handler->display->display_options['relationships']['nodequeue_rel']['field'] = 'nodequeue_rel';
  $handler->display->display_options['relationships']['nodequeue_rel']['label'] = 'Featured Queue';
  $handler->display->display_options['relationships']['nodequeue_rel']['required'] = 1;
  $handler->display->display_options['relationships']['nodequeue_rel']['limit'] = 1;
  $handler->display->display_options['relationships']['nodequeue_rel']['names'] = array(
    'news_media_featured' => 'news_media_featured',
    'front_page_features' => 0,
    'news_media_highlights' => 0,
  );
  $handler->display->display_options['defaults']['sorts'] = FALSE;
  /* Sort criterion: Nodequeue: Position */
  $handler->display->display_options['sorts']['position']['id'] = 'position';
  $handler->display->display_options['sorts']['position']['table'] = 'nodequeue_nodes';
  $handler->display->display_options['sorts']['position']['field'] = 'position';
  $handler->display->display_options['sorts']['position']['relationship'] = 'nodequeue_rel';
  /* Sort criterion: Content: Post date */
  $handler->display->display_options['sorts']['created']['id'] = 'created';
  $handler->display->display_options['sorts']['created']['table'] = 'node';
  $handler->display->display_options['sorts']['created']['field'] = 'created';
  $handler->display->display_options['sorts']['created']['order'] = 'DESC';
  $translatables['home_small_feature'] = array(
    t('Master'),
    t('front_news'),
    t('more'),
    t('Apply'),
    t('Reset'),
    t('Sort by'),
    t('Asc'),
    t('Desc'),
    t('Items per page'),
    t('- All -'),
    t('Offset'),
    t('queue'),
    t('no-date'),
    t('in [type]'),
    t('[title]'),
    t('[body]'),
    t('<a href="[view_node]" title="[title_1]">Read</a>'),
    t('Read'),
    t('[path]'),
    t('Block: Featured Queue'),
    t('Featured Queue'),
  );
  $export['home_small_feature'] = $view;

  return $export;
}
