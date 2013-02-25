<?php
/**
 * @file
 * gazprom_flag_popup.views_default.inc
 */

/**
 * Implements hook_views_default_views().
 */
function gazprom_flag_popup_views_default_views() {
  $export = array();

  $view = new view;
  $view->name = 'mini_country_flags';
  $view->description = '';
  $view->tag = 'default';
  $view->base_table = 'node';
  $view->human_name = 'Mini Country Flags';
  $view->core = 7;
  $view->api_version = '3.0';
  $view->disabled = FALSE; /* Edit this to true to make a default view disabled initially */

  /* Display: Master */
  $handler = $view->new_display('default', 'Master', 'default');
  $handler->display->display_options['title'] = 'Mini Country Flags';
  $handler->display->display_options['access']['type'] = 'perm';
  $handler->display->display_options['cache']['type'] = 'none';
  $handler->display->display_options['query']['type'] = 'views_query';
  $handler->display->display_options['query']['options']['query_comment'] = FALSE;
  $handler->display->display_options['exposed_form']['type'] = 'basic';
  $handler->display->display_options['pager']['type'] = 'none';
  $handler->display->display_options['style_plugin'] = 'list';
  $handler->display->display_options['row_plugin'] = 'fields';
  /* Relationship: Content: Taxonomy terms on node */
  $handler->display->display_options['relationships']['term_node_tid']['id'] = 'term_node_tid';
  $handler->display->display_options['relationships']['term_node_tid']['table'] = 'node';
  $handler->display->display_options['relationships']['term_node_tid']['field'] = 'term_node_tid';
  $handler->display->display_options['relationships']['term_node_tid']['label'] = 'Country Term';
  $handler->display->display_options['relationships']['term_node_tid']['required'] = 0;
  $handler->display->display_options['relationships']['term_node_tid']['vocabularies'] = array(
    'tags' => 0,
    'location' => 0,
    'staff_type' => 0,
  );
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
  $handler->display->display_options['fields']['title']['alter']['strip_tags'] = 0;
  $handler->display->display_options['fields']['title']['alter']['trim'] = 0;
  $handler->display->display_options['fields']['title']['alter']['html'] = 0;
  $handler->display->display_options['fields']['title']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['title']['element_default_classes'] = 1;
  $handler->display->display_options['fields']['title']['hide_empty'] = 0;
  $handler->display->display_options['fields']['title']['empty_zero'] = 0;
  $handler->display->display_options['fields']['title']['hide_alter_empty'] = 1;
  $handler->display->display_options['fields']['title']['link_to_node'] = 0;
  /* Field: Content: Path */
  $handler->display->display_options['fields']['path']['id'] = 'path';
  $handler->display->display_options['fields']['path']['table'] = 'node';
  $handler->display->display_options['fields']['path']['field'] = 'path';
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
  $handler->display->display_options['fields']['path']['absolute'] = 0;
  /* Field: Taxonomy term: Flag */
  $handler->display->display_options['fields']['field_flag_image']['id'] = 'field_flag_image';
  $handler->display->display_options['fields']['field_flag_image']['table'] = 'field_data_field_flag_image';
  $handler->display->display_options['fields']['field_flag_image']['field'] = 'field_flag_image';
  $handler->display->display_options['fields']['field_flag_image']['relationship'] = 'term_node_tid';
  $handler->display->display_options['fields']['field_flag_image']['label'] = '';
  $handler->display->display_options['fields']['field_flag_image']['alter']['alter_text'] = 1;
  $handler->display->display_options['fields']['field_flag_image']['alter']['text'] = '<a href="[path]" title="[title]">[field_flag_image]</a>';
  $handler->display->display_options['fields']['field_flag_image']['alter']['make_link'] = 0;
  $handler->display->display_options['fields']['field_flag_image']['alter']['path'] = '[path]';
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
  $handler->display->display_options['fields']['field_flag_image']['element_type'] = '0';
  $handler->display->display_options['fields']['field_flag_image']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['field_flag_image']['element_default_classes'] = 0;
  $handler->display->display_options['fields']['field_flag_image']['hide_empty'] = 0;
  $handler->display->display_options['fields']['field_flag_image']['empty_zero'] = 0;
  $handler->display->display_options['fields']['field_flag_image']['hide_alter_empty'] = 1;
  $handler->display->display_options['fields']['field_flag_image']['click_sort_column'] = 'fid';
  $handler->display->display_options['fields']['field_flag_image']['settings'] = array(
    'image_style' => 'flag-mini',
    'image_link' => '',
  );
  $handler->display->display_options['fields']['field_flag_image']['field_api_classes'] = 0;
  /* Sort criterion: Content: Title */
  $handler->display->display_options['sorts']['title']['id'] = 'title';
  $handler->display->display_options['sorts']['title']['table'] = 'node';
  $handler->display->display_options['sorts']['title']['field'] = 'title';
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
    'country_page' => 'country_page',
  );
  /* Filter criterion: Content translation: Language */
  $handler->display->display_options['filters']['language']['id'] = 'language';
  $handler->display->display_options['filters']['language']['table'] = 'node';
  $handler->display->display_options['filters']['language']['field'] = 'language';
  $handler->display->display_options['filters']['language']['value'] = array(
    '***CURRENT_LANGUAGE***' => '***CURRENT_LANGUAGE***',
    'und' => 'und',
  );
  /* Filter criterion: Taxonomy term: Flag (field_flag_image:fid) */
  $handler->display->display_options['filters']['field_flag_image_fid']['id'] = 'field_flag_image_fid';
  $handler->display->display_options['filters']['field_flag_image_fid']['table'] = 'field_data_field_flag_image';
  $handler->display->display_options['filters']['field_flag_image_fid']['field'] = 'field_flag_image_fid';
  $handler->display->display_options['filters']['field_flag_image_fid']['relationship'] = 'term_node_tid';
  $handler->display->display_options['filters']['field_flag_image_fid']['operator'] = 'not empty';
  /* Filter criterion: Content: Promoted to front page */
  $handler->display->display_options['filters']['promote']['id'] = 'promote';
  $handler->display->display_options['filters']['promote']['table'] = 'node';
  $handler->display->display_options['filters']['promote']['field'] = 'promote';
  $handler->display->display_options['filters']['promote']['value'] = '1';

  /* Display: Block */
  $handler = $view->new_display('block', 'Block', 'block');
  $translatables['mini_country_flags'] = array(
    t('Master'),
    t('Mini Country Flags'),
    t('more'),
    t('Apply'),
    t('Reset'),
    t('Sort by'),
    t('Asc'),
    t('Desc'),
    t('Country Term'),
    t('<a href="[path]" title="[title]">[field_flag_image]</a>'),
    t('[path]'),
    t('Block'),
  );
  $export['mini_country_flags'] = $view;

  return $export;
}
