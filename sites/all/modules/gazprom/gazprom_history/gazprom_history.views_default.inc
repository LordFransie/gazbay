<?php
/**
 * @file
 * gazprom_history.views_default.inc
 */

/**
 * Implements hook_views_default_views().
 */
function gazprom_history_views_default_views() {
  $export = array();

  $view = new view;
  $view->name = 'history';
  $view->description = '';
  $view->tag = 'default';
  $view->base_table = 'node';
  $view->human_name = 'History';
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
  $handler->display->display_options['style_plugin'] = 'list';
  $handler->display->display_options['row_plugin'] = 'fields';
  /* Field: Year */
  $handler->display->display_options['fields']['field_date_event']['id'] = 'field_date_event';
  $handler->display->display_options['fields']['field_date_event']['table'] = 'field_data_field_date_event';
  $handler->display->display_options['fields']['field_date_event']['field'] = 'field_date_event';
  $handler->display->display_options['fields']['field_date_event']['ui_name'] = 'Year';
  $handler->display->display_options['fields']['field_date_event']['label'] = '';
  $handler->display->display_options['fields']['field_date_event']['alter']['alter_text'] = 0;
  $handler->display->display_options['fields']['field_date_event']['alter']['text'] = '[field_date_event]';
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
  $handler->display->display_options['fields']['field_date_event']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['field_date_event']['element_default_classes'] = 1;
  $handler->display->display_options['fields']['field_date_event']['hide_empty'] = 0;
  $handler->display->display_options['fields']['field_date_event']['empty_zero'] = 0;
  $handler->display->display_options['fields']['field_date_event']['hide_alter_empty'] = 1;
  $handler->display->display_options['fields']['field_date_event']['settings'] = array(
    'format_type' => 'year',
    'fromto' => 'both',
    'multiple_number' => '',
    'multiple_from' => '',
    'multiple_to' => '',
  );
  $handler->display->display_options['fields']['field_date_event']['field_api_classes'] = 0;
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
  /* Field: Content: Description */
  $handler->display->display_options['fields']['field_history_description']['id'] = 'field_history_description';
  $handler->display->display_options['fields']['field_history_description']['table'] = 'field_data_field_history_description';
  $handler->display->display_options['fields']['field_history_description']['field'] = 'field_history_description';
  $handler->display->display_options['fields']['field_history_description']['label'] = '';
  $handler->display->display_options['fields']['field_history_description']['alter']['alter_text'] = 0;
  $handler->display->display_options['fields']['field_history_description']['alter']['make_link'] = 0;
  $handler->display->display_options['fields']['field_history_description']['alter']['absolute'] = 0;
  $handler->display->display_options['fields']['field_history_description']['alter']['external'] = 0;
  $handler->display->display_options['fields']['field_history_description']['alter']['replace_spaces'] = 0;
  $handler->display->display_options['fields']['field_history_description']['alter']['trim_whitespace'] = 0;
  $handler->display->display_options['fields']['field_history_description']['alter']['nl2br'] = 0;
  $handler->display->display_options['fields']['field_history_description']['alter']['word_boundary'] = 1;
  $handler->display->display_options['fields']['field_history_description']['alter']['ellipsis'] = 1;
  $handler->display->display_options['fields']['field_history_description']['alter']['strip_tags'] = 0;
  $handler->display->display_options['fields']['field_history_description']['alter']['trim'] = 0;
  $handler->display->display_options['fields']['field_history_description']['alter']['html'] = 0;
  $handler->display->display_options['fields']['field_history_description']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['field_history_description']['element_default_classes'] = 1;
  $handler->display->display_options['fields']['field_history_description']['hide_empty'] = 0;
  $handler->display->display_options['fields']['field_history_description']['empty_zero'] = 0;
  $handler->display->display_options['fields']['field_history_description']['hide_alter_empty'] = 1;
  $handler->display->display_options['fields']['field_history_description']['field_api_classes'] = 0;
  /* Sort criterion: Content: Date Released (field_date_event) */
  $handler->display->display_options['sorts']['field_date_event_value']['id'] = 'field_date_event_value';
  $handler->display->display_options['sorts']['field_date_event_value']['table'] = 'field_data_field_date_event';
  $handler->display->display_options['sorts']['field_date_event_value']['field'] = 'field_date_event_value';
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
    'history_event' => 'history_event',
  );

  /* Display: Year Timeline (block) */
  $handler = $view->new_display('block', 'Year Timeline (block)', 'year_timeline');
  $handler->display->display_options['defaults']['pager'] = FALSE;
  $handler->display->display_options['pager']['type'] = 'none';
  $handler->display->display_options['pager']['options']['offset'] = '0';
  $handler->display->display_options['defaults']['style_plugin'] = FALSE;
  $handler->display->display_options['style_plugin'] = 'list';
  $handler->display->display_options['style_options']['grouping'] = array(
    0 => array(
      'field' => 'field_date_event',
      'rendered' => 1,
      'rendered_strip' => 1,
    ),
  );
  $handler->display->display_options['defaults']['style_options'] = FALSE;
  $handler->display->display_options['defaults']['row_plugin'] = FALSE;
  $handler->display->display_options['row_plugin'] = 'fields';
  $handler->display->display_options['defaults']['row_options'] = FALSE;
  $handler->display->display_options['defaults']['fields'] = FALSE;
  /* Field: Year (not displayed via custom tpl files) */
  $handler->display->display_options['fields']['field_date_event']['id'] = 'field_date_event';
  $handler->display->display_options['fields']['field_date_event']['table'] = 'field_data_field_date_event';
  $handler->display->display_options['fields']['field_date_event']['field'] = 'field_date_event';
  $handler->display->display_options['fields']['field_date_event']['ui_name'] = 'Year (not displayed via custom tpl files)';
  $handler->display->display_options['fields']['field_date_event']['label'] = '';
  $handler->display->display_options['fields']['field_date_event']['alter']['alter_text'] = 0;
  $handler->display->display_options['fields']['field_date_event']['alter']['text'] = '[field_date_event]';
  $handler->display->display_options['fields']['field_date_event']['alter']['make_link'] = 0;
  $handler->display->display_options['fields']['field_date_event']['alter']['path'] = '?year=[field_date_event]';
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
  $handler->display->display_options['fields']['field_date_event']['element_class'] = 'hide';
  $handler->display->display_options['fields']['field_date_event']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['field_date_event']['element_default_classes'] = 1;
  $handler->display->display_options['fields']['field_date_event']['hide_empty'] = 0;
  $handler->display->display_options['fields']['field_date_event']['empty_zero'] = 0;
  $handler->display->display_options['fields']['field_date_event']['hide_alter_empty'] = 1;
  $handler->display->display_options['fields']['field_date_event']['settings'] = array(
    'format_type' => 'year',
    'fromto' => 'both',
    'multiple_number' => '',
    'multiple_from' => '',
    'multiple_to' => '',
  );
  $handler->display->display_options['fields']['field_date_event']['field_api_classes'] = 0;
  /* Field: Date (title, not displayed via custom tpl files) */
  $handler->display->display_options['fields']['title']['id'] = 'title';
  $handler->display->display_options['fields']['title']['table'] = 'node';
  $handler->display->display_options['fields']['title']['field'] = 'title';
  $handler->display->display_options['fields']['title']['ui_name'] = 'Date (title, not displayed via custom tpl files)';
  $handler->display->display_options['fields']['title']['label'] = '';
  $handler->display->display_options['fields']['title']['exclude'] = TRUE;
  $handler->display->display_options['fields']['title']['alter']['alter_text'] = 0;
  $handler->display->display_options['fields']['title']['alter']['make_link'] = 0;
  $handler->display->display_options['fields']['title']['alter']['absolute'] = 0;
  $handler->display->display_options['fields']['title']['alter']['external'] = 0;
  $handler->display->display_options['fields']['title']['alter']['replace_spaces'] = 0;
  $handler->display->display_options['fields']['title']['alter']['trim_whitespace'] = 0;
  $handler->display->display_options['fields']['title']['alter']['nl2br'] = 0;
  $handler->display->display_options['fields']['title']['alter']['word_boundary'] = 1;
  $handler->display->display_options['fields']['title']['alter']['ellipsis'] = 1;
  $handler->display->display_options['fields']['title']['alter']['more_link'] = 0;
  $handler->display->display_options['fields']['title']['alter']['strip_tags'] = 0;
  $handler->display->display_options['fields']['title']['alter']['trim'] = 0;
  $handler->display->display_options['fields']['title']['alter']['html'] = 0;
  $handler->display->display_options['fields']['title']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['title']['element_default_classes'] = 1;
  $handler->display->display_options['fields']['title']['hide_empty'] = 0;
  $handler->display->display_options['fields']['title']['empty_zero'] = 0;
  $handler->display->display_options['fields']['title']['hide_alter_empty'] = 1;
  $handler->display->display_options['fields']['title']['link_to_node'] = 1;
  /* Field: Content: Date Released */
  $handler->display->display_options['fields']['field_date_event_1']['id'] = 'field_date_event_1';
  $handler->display->display_options['fields']['field_date_event_1']['table'] = 'field_data_field_date_event';
  $handler->display->display_options['fields']['field_date_event_1']['field'] = 'field_date_event';
  $handler->display->display_options['fields']['field_date_event_1']['label'] = '';
  $handler->display->display_options['fields']['field_date_event_1']['alter']['alter_text'] = 0;
  $handler->display->display_options['fields']['field_date_event_1']['alter']['make_link'] = 0;
  $handler->display->display_options['fields']['field_date_event_1']['alter']['absolute'] = 0;
  $handler->display->display_options['fields']['field_date_event_1']['alter']['external'] = 0;
  $handler->display->display_options['fields']['field_date_event_1']['alter']['replace_spaces'] = 0;
  $handler->display->display_options['fields']['field_date_event_1']['alter']['trim_whitespace'] = 0;
  $handler->display->display_options['fields']['field_date_event_1']['alter']['nl2br'] = 0;
  $handler->display->display_options['fields']['field_date_event_1']['alter']['word_boundary'] = 1;
  $handler->display->display_options['fields']['field_date_event_1']['alter']['ellipsis'] = 1;
  $handler->display->display_options['fields']['field_date_event_1']['alter']['more_link'] = 0;
  $handler->display->display_options['fields']['field_date_event_1']['alter']['strip_tags'] = 0;
  $handler->display->display_options['fields']['field_date_event_1']['alter']['trim'] = 0;
  $handler->display->display_options['fields']['field_date_event_1']['alter']['html'] = 0;
  $handler->display->display_options['fields']['field_date_event_1']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['field_date_event_1']['element_default_classes'] = 1;
  $handler->display->display_options['fields']['field_date_event_1']['hide_empty'] = 0;
  $handler->display->display_options['fields']['field_date_event_1']['empty_zero'] = 0;
  $handler->display->display_options['fields']['field_date_event_1']['hide_alter_empty'] = 1;
  $handler->display->display_options['fields']['field_date_event_1']['settings'] = array(
    'format_type' => 'simple',
    'fromto' => 'both',
    'multiple_number' => '',
    'multiple_from' => '',
    'multiple_to' => '',
  );
  $handler->display->display_options['fields']['field_date_event_1']['field_api_classes'] = 0;
  /* Field: Content: Description */
  $handler->display->display_options['fields']['field_history_description']['id'] = 'field_history_description';
  $handler->display->display_options['fields']['field_history_description']['table'] = 'field_data_field_history_description';
  $handler->display->display_options['fields']['field_history_description']['field'] = 'field_history_description';
  $handler->display->display_options['fields']['field_history_description']['label'] = '';
  $handler->display->display_options['fields']['field_history_description']['alter']['alter_text'] = 0;
  $handler->display->display_options['fields']['field_history_description']['alter']['make_link'] = 0;
  $handler->display->display_options['fields']['field_history_description']['alter']['absolute'] = 0;
  $handler->display->display_options['fields']['field_history_description']['alter']['external'] = 0;
  $handler->display->display_options['fields']['field_history_description']['alter']['replace_spaces'] = 0;
  $handler->display->display_options['fields']['field_history_description']['alter']['trim_whitespace'] = 0;
  $handler->display->display_options['fields']['field_history_description']['alter']['nl2br'] = 0;
  $handler->display->display_options['fields']['field_history_description']['alter']['word_boundary'] = 1;
  $handler->display->display_options['fields']['field_history_description']['alter']['ellipsis'] = 1;
  $handler->display->display_options['fields']['field_history_description']['alter']['more_link'] = 0;
  $handler->display->display_options['fields']['field_history_description']['alter']['strip_tags'] = 0;
  $handler->display->display_options['fields']['field_history_description']['alter']['trim'] = 0;
  $handler->display->display_options['fields']['field_history_description']['alter']['html'] = 0;
  $handler->display->display_options['fields']['field_history_description']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['field_history_description']['element_default_classes'] = 1;
  $handler->display->display_options['fields']['field_history_description']['hide_empty'] = 0;
  $handler->display->display_options['fields']['field_history_description']['empty_zero'] = 0;
  $handler->display->display_options['fields']['field_history_description']['hide_alter_empty'] = 1;
  $handler->display->display_options['fields']['field_history_description']['field_api_classes'] = 0;

  /* Display: Events (block) */
  $handler = $view->new_display('block', 'Events (block)', 'events');
  $handler->display->display_options['defaults']['use_ajax'] = FALSE;
  $handler->display->display_options['use_ajax'] = TRUE;
  $handler->display->display_options['defaults']['pager'] = FALSE;
  $handler->display->display_options['pager']['type'] = 'none';
  $handler->display->display_options['pager']['options']['offset'] = '0';
  $handler->display->display_options['defaults']['fields'] = FALSE;
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
  $handler->display->display_options['fields']['field_date_event']['alter']['more_link'] = 0;
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
  $handler->display->display_options['fields']['title']['alter']['word_boundary'] = 0;
  $handler->display->display_options['fields']['title']['alter']['ellipsis'] = 0;
  $handler->display->display_options['fields']['title']['alter']['more_link'] = 0;
  $handler->display->display_options['fields']['title']['alter']['strip_tags'] = 0;
  $handler->display->display_options['fields']['title']['alter']['trim'] = 0;
  $handler->display->display_options['fields']['title']['alter']['html'] = 0;
  $handler->display->display_options['fields']['title']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['title']['element_default_classes'] = 1;
  $handler->display->display_options['fields']['title']['hide_empty'] = 0;
  $handler->display->display_options['fields']['title']['empty_zero'] = 0;
  $handler->display->display_options['fields']['title']['hide_alter_empty'] = 1;
  $handler->display->display_options['fields']['title']['link_to_node'] = 0;
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
  $handler->display->display_options['fields']['field_image']['hide_alter_empty'] = 1;
  $handler->display->display_options['fields']['field_image']['click_sort_column'] = 'fid';
  $handler->display->display_options['fields']['field_image']['settings'] = array(
    'image_style' => 'overlay_primary_240x170',
    'image_link' => '',
  );
  $handler->display->display_options['fields']['field_image']['field_api_classes'] = 0;
  /* Field: Content: Date Released */
  $handler->display->display_options['fields']['field_date_event_1']['id'] = 'field_date_event_1';
  $handler->display->display_options['fields']['field_date_event_1']['table'] = 'field_data_field_date_event';
  $handler->display->display_options['fields']['field_date_event_1']['field'] = 'field_date_event';
  $handler->display->display_options['fields']['field_date_event_1']['label'] = '';
  $handler->display->display_options['fields']['field_date_event_1']['alter']['alter_text'] = 0;
  $handler->display->display_options['fields']['field_date_event_1']['alter']['make_link'] = 0;
  $handler->display->display_options['fields']['field_date_event_1']['alter']['absolute'] = 0;
  $handler->display->display_options['fields']['field_date_event_1']['alter']['external'] = 0;
  $handler->display->display_options['fields']['field_date_event_1']['alter']['replace_spaces'] = 0;
  $handler->display->display_options['fields']['field_date_event_1']['alter']['trim_whitespace'] = 0;
  $handler->display->display_options['fields']['field_date_event_1']['alter']['nl2br'] = 0;
  $handler->display->display_options['fields']['field_date_event_1']['alter']['word_boundary'] = 1;
  $handler->display->display_options['fields']['field_date_event_1']['alter']['ellipsis'] = 1;
  $handler->display->display_options['fields']['field_date_event_1']['alter']['more_link'] = 0;
  $handler->display->display_options['fields']['field_date_event_1']['alter']['strip_tags'] = 0;
  $handler->display->display_options['fields']['field_date_event_1']['alter']['trim'] = 0;
  $handler->display->display_options['fields']['field_date_event_1']['alter']['html'] = 0;
  $handler->display->display_options['fields']['field_date_event_1']['element_class'] = 'label';
  $handler->display->display_options['fields']['field_date_event_1']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['field_date_event_1']['element_default_classes'] = 1;
  $handler->display->display_options['fields']['field_date_event_1']['hide_empty'] = 0;
  $handler->display->display_options['fields']['field_date_event_1']['empty_zero'] = 0;
  $handler->display->display_options['fields']['field_date_event_1']['hide_alter_empty'] = 1;
  $handler->display->display_options['fields']['field_date_event_1']['settings'] = array(
    'format_type' => 'simple',
    'fromto' => 'both',
    'multiple_number' => '',
    'multiple_from' => '',
    'multiple_to' => '',
  );
  $handler->display->display_options['fields']['field_date_event_1']['field_api_classes'] = 0;
  /* Field: Content: Description */
  $handler->display->display_options['fields']['field_history_description']['id'] = 'field_history_description';
  $handler->display->display_options['fields']['field_history_description']['table'] = 'field_data_field_history_description';
  $handler->display->display_options['fields']['field_history_description']['field'] = 'field_history_description';
  $handler->display->display_options['fields']['field_history_description']['label'] = '';
  $handler->display->display_options['fields']['field_history_description']['alter']['alter_text'] = 0;
  $handler->display->display_options['fields']['field_history_description']['alter']['make_link'] = 0;
  $handler->display->display_options['fields']['field_history_description']['alter']['absolute'] = 0;
  $handler->display->display_options['fields']['field_history_description']['alter']['external'] = 0;
  $handler->display->display_options['fields']['field_history_description']['alter']['replace_spaces'] = 0;
  $handler->display->display_options['fields']['field_history_description']['alter']['trim_whitespace'] = 0;
  $handler->display->display_options['fields']['field_history_description']['alter']['nl2br'] = 0;
  $handler->display->display_options['fields']['field_history_description']['alter']['word_boundary'] = 1;
  $handler->display->display_options['fields']['field_history_description']['alter']['ellipsis'] = 1;
  $handler->display->display_options['fields']['field_history_description']['alter']['strip_tags'] = 0;
  $handler->display->display_options['fields']['field_history_description']['alter']['trim'] = 0;
  $handler->display->display_options['fields']['field_history_description']['alter']['html'] = 0;
  $handler->display->display_options['fields']['field_history_description']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['field_history_description']['element_default_classes'] = 1;
  $handler->display->display_options['fields']['field_history_description']['hide_empty'] = 0;
  $handler->display->display_options['fields']['field_history_description']['empty_zero'] = 0;
  $handler->display->display_options['fields']['field_history_description']['hide_alter_empty'] = 1;
  $handler->display->display_options['fields']['field_history_description']['field_api_classes'] = 0;
  /* Field: &lt;div class=&quot;clearfix&quot;&gt;&lt;/div&gt; */
  $handler->display->display_options['fields']['nothing']['id'] = 'nothing';
  $handler->display->display_options['fields']['nothing']['table'] = 'views';
  $handler->display->display_options['fields']['nothing']['field'] = 'nothing';
  $handler->display->display_options['fields']['nothing']['ui_name'] = '<div class="clearfix"></div>';
  $handler->display->display_options['fields']['nothing']['label'] = '';
  $handler->display->display_options['fields']['nothing']['alter']['text'] = '<div class="clearfix"></div>';
  $handler->display->display_options['fields']['nothing']['alter']['make_link'] = 0;
  $handler->display->display_options['fields']['nothing']['alter']['absolute'] = 0;
  $handler->display->display_options['fields']['nothing']['alter']['external'] = 0;
  $handler->display->display_options['fields']['nothing']['alter']['replace_spaces'] = 0;
  $handler->display->display_options['fields']['nothing']['alter']['trim_whitespace'] = 0;
  $handler->display->display_options['fields']['nothing']['alter']['nl2br'] = 0;
  $handler->display->display_options['fields']['nothing']['alter']['word_boundary'] = 1;
  $handler->display->display_options['fields']['nothing']['alter']['ellipsis'] = 1;
  $handler->display->display_options['fields']['nothing']['alter']['more_link'] = 0;
  $handler->display->display_options['fields']['nothing']['alter']['strip_tags'] = 0;
  $handler->display->display_options['fields']['nothing']['alter']['trim'] = 0;
  $handler->display->display_options['fields']['nothing']['alter']['html'] = 0;
  $handler->display->display_options['fields']['nothing']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['nothing']['element_default_classes'] = 1;
  $handler->display->display_options['fields']['nothing']['hide_empty'] = 0;
  $handler->display->display_options['fields']['nothing']['empty_zero'] = 0;
  $handler->display->display_options['fields']['nothing']['hide_alter_empty'] = 0;
  $handler->display->display_options['defaults']['arguments'] = FALSE;
  /* Contextual filter: Content: Date Released (field_date_event) */
  $handler->display->display_options['arguments']['field_date_event_value']['id'] = 'field_date_event_value';
  $handler->display->display_options['arguments']['field_date_event_value']['table'] = 'field_data_field_date_event';
  $handler->display->display_options['arguments']['field_date_event_value']['field'] = 'field_date_event_value';
  $handler->display->display_options['arguments']['field_date_event_value']['default_action'] = 'empty';
  $handler->display->display_options['arguments']['field_date_event_value']['default_argument_type'] = 'fixed';
  $handler->display->display_options['arguments']['field_date_event_value']['default_argument_skip_url'] = 0;
  $handler->display->display_options['arguments']['field_date_event_value']['summary']['number_of_records'] = '0';
  $handler->display->display_options['arguments']['field_date_event_value']['summary']['format'] = 'default_summary';
  $handler->display->display_options['arguments']['field_date_event_value']['summary_options']['items_per_page'] = '25';
  $handler->display->display_options['arguments']['field_date_event_value']['year_range'] = '-99:+99';
  $handler->display->display_options['arguments']['field_date_event_value']['granularity'] = 'year';
  $translatables['history'] = array(
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
    t('[field_date_event]'),
    t('Year Timeline (block)'),
    t('?year=[field_date_event]'),
    t('Events (block)'),
    t('<div class="clearfix"></div>'),
    t('All'),
  );
  $export['history'] = $view;

  return $export;
}
