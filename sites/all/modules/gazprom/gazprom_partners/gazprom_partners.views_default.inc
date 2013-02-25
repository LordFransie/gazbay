<?php
/**
 * @file
 * gazprom_partners.views_default.inc
 */

/**
 * Implements hook_views_default_views().
 */
function gazprom_partners_views_default_views() {
  $export = array();

  $view = new view;
  $view->name = 'partners';
  $view->description = '';
  $view->tag = 'default';
  $view->base_table = 'node';
  $view->human_name = 'Partners';
  $view->core = 7;
  $view->api_version = '3.0';
  $view->disabled = FALSE; /* Edit this to true to make a default view disabled initially */

  /* Display: Master */
  $handler = $view->new_display('default', 'Master', 'default');
  $handler->display->display_options['title'] = 'Partners';
  $handler->display->display_options['use_ajax'] = TRUE;
  $handler->display->display_options['access']['type'] = 'perm';
  $handler->display->display_options['cache']['type'] = 'none';
  $handler->display->display_options['query']['type'] = 'views_query';
  $handler->display->display_options['query']['options']['distinct'] = TRUE;
  $handler->display->display_options['query']['options']['query_comment'] = FALSE;
  $handler->display->display_options['exposed_form']['type'] = 'basic';
  $handler->display->display_options['pager']['type'] = 'mini';
  $handler->display->display_options['pager']['options']['items_per_page'] = '9';
  $handler->display->display_options['pager']['options']['offset'] = '0';
  $handler->display->display_options['pager']['options']['id'] = '0';
  $handler->display->display_options['pager']['options']['expose']['items_per_page_options_all'] = 0;
  $handler->display->display_options['style_plugin'] = 'fixed_row_grid';
  $handler->display->display_options['style_options']['rows'] = '3';
  $handler->display->display_options['style_options']['fill_each_column'] = 1;
  $handler->display->display_options['row_plugin'] = 'fields';
  $handler->display->display_options['row_options']['hide_empty'] = 0;
  $handler->display->display_options['row_options']['default_field_elements'] = 1;
  /* Footer: Global: Text area */
  $handler->display->display_options['footer']['area']['id'] = 'area';
  $handler->display->display_options['footer']['area']['table'] = 'views';
  $handler->display->display_options['footer']['area']['field'] = 'area';
  $handler->display->display_options['footer']['area']['label'] = 'Total Count Footer';
  $handler->display->display_options['footer']['area']['empty'] = FALSE;
  $handler->display->display_options['footer']['area']['content'] = '<?php
  $view = views_get_current_view();
  print \'<span class="view-total-count">\' . $view->total_rows . \'</span>\'; 
?>';
  $handler->display->display_options['footer']['area']['format'] = 'php_code';
  $handler->display->display_options['footer']['area']['tokenize'] = 0;
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
  /* Field: Content: Link to website */
  $handler->display->display_options['fields']['field_url_text_1']['id'] = 'field_url_text_1';
  $handler->display->display_options['fields']['field_url_text_1']['table'] = 'field_data_field_url_text';
  $handler->display->display_options['fields']['field_url_text_1']['field'] = 'field_url_text';
  $handler->display->display_options['fields']['field_url_text_1']['label'] = '';
  $handler->display->display_options['fields']['field_url_text_1']['exclude'] = TRUE;
  $handler->display->display_options['fields']['field_url_text_1']['alter']['alter_text'] = 0;
  $handler->display->display_options['fields']['field_url_text_1']['alter']['make_link'] = 0;
  $handler->display->display_options['fields']['field_url_text_1']['alter']['absolute'] = 0;
  $handler->display->display_options['fields']['field_url_text_1']['alter']['external'] = 0;
  $handler->display->display_options['fields']['field_url_text_1']['alter']['replace_spaces'] = 0;
  $handler->display->display_options['fields']['field_url_text_1']['alter']['trim_whitespace'] = 0;
  $handler->display->display_options['fields']['field_url_text_1']['alter']['nl2br'] = 0;
  $handler->display->display_options['fields']['field_url_text_1']['alter']['word_boundary'] = 1;
  $handler->display->display_options['fields']['field_url_text_1']['alter']['ellipsis'] = 1;
  $handler->display->display_options['fields']['field_url_text_1']['alter']['strip_tags'] = 0;
  $handler->display->display_options['fields']['field_url_text_1']['alter']['trim'] = 0;
  $handler->display->display_options['fields']['field_url_text_1']['alter']['html'] = 0;
  $handler->display->display_options['fields']['field_url_text_1']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['field_url_text_1']['element_default_classes'] = 1;
  $handler->display->display_options['fields']['field_url_text_1']['hide_empty'] = 0;
  $handler->display->display_options['fields']['field_url_text_1']['empty_zero'] = 0;
  $handler->display->display_options['fields']['field_url_text_1']['hide_alter_empty'] = 1;
  $handler->display->display_options['fields']['field_url_text_1']['type'] = 'text_plain';
  $handler->display->display_options['fields']['field_url_text_1']['field_api_classes'] = 0;
  /* Field: Content: Country */
  $handler->display->display_options['fields']['field_country']['id'] = 'field_country';
  $handler->display->display_options['fields']['field_country']['table'] = 'field_data_field_country';
  $handler->display->display_options['fields']['field_country']['field'] = 'field_country';
  $handler->display->display_options['fields']['field_country']['label'] = '';
  $handler->display->display_options['fields']['field_country']['exclude'] = TRUE;
  $handler->display->display_options['fields']['field_country']['alter']['alter_text'] = 0;
  $handler->display->display_options['fields']['field_country']['alter']['make_link'] = 0;
  $handler->display->display_options['fields']['field_country']['alter']['absolute'] = 0;
  $handler->display->display_options['fields']['field_country']['alter']['external'] = 0;
  $handler->display->display_options['fields']['field_country']['alter']['replace_spaces'] = 0;
  $handler->display->display_options['fields']['field_country']['alter']['trim_whitespace'] = 0;
  $handler->display->display_options['fields']['field_country']['alter']['nl2br'] = 0;
  $handler->display->display_options['fields']['field_country']['alter']['word_boundary'] = 1;
  $handler->display->display_options['fields']['field_country']['alter']['ellipsis'] = 1;
  $handler->display->display_options['fields']['field_country']['alter']['strip_tags'] = 0;
  $handler->display->display_options['fields']['field_country']['alter']['trim'] = 0;
  $handler->display->display_options['fields']['field_country']['alter']['html'] = 0;
  $handler->display->display_options['fields']['field_country']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['field_country']['element_default_classes'] = 1;
  $handler->display->display_options['fields']['field_country']['hide_empty'] = 0;
  $handler->display->display_options['fields']['field_country']['empty_zero'] = 0;
  $handler->display->display_options['fields']['field_country']['hide_alter_empty'] = 1;
  $handler->display->display_options['fields']['field_country']['type'] = 'i18n_taxonomy_term_reference_plain';
  $handler->display->display_options['fields']['field_country']['field_api_classes'] = 0;
  /* Field: Content: Partner Logo */
  $handler->display->display_options['fields']['field_logo']['id'] = 'field_logo';
  $handler->display->display_options['fields']['field_logo']['table'] = 'field_data_field_logo';
  $handler->display->display_options['fields']['field_logo']['field'] = 'field_logo';
  $handler->display->display_options['fields']['field_logo']['label'] = '';
  $handler->display->display_options['fields']['field_logo']['alter']['alter_text'] = 0;
  $handler->display->display_options['fields']['field_logo']['alter']['make_link'] = 1;
  $handler->display->display_options['fields']['field_logo']['alter']['path'] = '[field_url_text_1]';
  $handler->display->display_options['fields']['field_logo']['alter']['absolute'] = 0;
  $handler->display->display_options['fields']['field_logo']['alter']['external'] = 1;
  $handler->display->display_options['fields']['field_logo']['alter']['replace_spaces'] = 0;
  $handler->display->display_options['fields']['field_logo']['alter']['trim_whitespace'] = 0;
  $handler->display->display_options['fields']['field_logo']['alter']['alt'] = 'Visit website';
  $handler->display->display_options['fields']['field_logo']['alter']['target'] = '_new';
  $handler->display->display_options['fields']['field_logo']['alter']['nl2br'] = 0;
  $handler->display->display_options['fields']['field_logo']['alter']['word_boundary'] = 1;
  $handler->display->display_options['fields']['field_logo']['alter']['ellipsis'] = 1;
  $handler->display->display_options['fields']['field_logo']['alter']['strip_tags'] = 0;
  $handler->display->display_options['fields']['field_logo']['alter']['trim'] = 0;
  $handler->display->display_options['fields']['field_logo']['alter']['html'] = 0;
  $handler->display->display_options['fields']['field_logo']['element_class'] = 'image-partner-logo';
  $handler->display->display_options['fields']['field_logo']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['field_logo']['element_default_classes'] = 1;
  $handler->display->display_options['fields']['field_logo']['hide_empty'] = 0;
  $handler->display->display_options['fields']['field_logo']['empty_zero'] = 0;
  $handler->display->display_options['fields']['field_logo']['hide_alter_empty'] = 1;
  $handler->display->display_options['fields']['field_logo']['click_sort_column'] = 'fid';
  $handler->display->display_options['fields']['field_logo']['type'] = 'image_swapper_default';
  $handler->display->display_options['fields']['field_logo']['settings'] = array(
    'base_style' => 'partner_logo_bw',
    'hover_style' => 'partner_logo_color',
    'effect' => 'fade',
  );
  $handler->display->display_options['fields']['field_logo']['field_api_classes'] = 1;
  /* Field: Content: Title */
  $handler->display->display_options['fields']['title']['id'] = 'title';
  $handler->display->display_options['fields']['title']['table'] = 'node';
  $handler->display->display_options['fields']['title']['field'] = 'title';
  $handler->display->display_options['fields']['title']['label'] = '';
  $handler->display->display_options['fields']['title']['exclude'] = TRUE;
  $handler->display->display_options['fields']['title']['alter']['alter_text'] = 1;
  $handler->display->display_options['fields']['title']['alter']['text'] = '[field_country]: [title]';
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
  /* Field: Title as link to site */
  $handler->display->display_options['fields']['field_url_text']['id'] = 'field_url_text';
  $handler->display->display_options['fields']['field_url_text']['table'] = 'field_data_field_url_text';
  $handler->display->display_options['fields']['field_url_text']['field'] = 'field_url_text';
  $handler->display->display_options['fields']['field_url_text']['ui_name'] = 'Title as link to site';
  $handler->display->display_options['fields']['field_url_text']['label'] = '';
  $handler->display->display_options['fields']['field_url_text']['alter']['alter_text'] = 1;
  $handler->display->display_options['fields']['field_url_text']['alter']['text'] = '<a href="[field_url_text]" target="_new" title="Visit website">[title]</a>';
  $handler->display->display_options['fields']['field_url_text']['alter']['make_link'] = 0;
  $handler->display->display_options['fields']['field_url_text']['alter']['absolute'] = 0;
  $handler->display->display_options['fields']['field_url_text']['alter']['external'] = 0;
  $handler->display->display_options['fields']['field_url_text']['alter']['replace_spaces'] = 0;
  $handler->display->display_options['fields']['field_url_text']['alter']['trim_whitespace'] = 0;
  $handler->display->display_options['fields']['field_url_text']['alter']['nl2br'] = 0;
  $handler->display->display_options['fields']['field_url_text']['alter']['word_boundary'] = 1;
  $handler->display->display_options['fields']['field_url_text']['alter']['ellipsis'] = 1;
  $handler->display->display_options['fields']['field_url_text']['alter']['strip_tags'] = 0;
  $handler->display->display_options['fields']['field_url_text']['alter']['trim'] = 0;
  $handler->display->display_options['fields']['field_url_text']['alter']['html'] = 0;
  $handler->display->display_options['fields']['field_url_text']['element_class'] = 'subheading';
  $handler->display->display_options['fields']['field_url_text']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['field_url_text']['element_default_classes'] = 1;
  $handler->display->display_options['fields']['field_url_text']['empty'] = '[title]';
  $handler->display->display_options['fields']['field_url_text']['hide_empty'] = 0;
  $handler->display->display_options['fields']['field_url_text']['empty_zero'] = 0;
  $handler->display->display_options['fields']['field_url_text']['hide_alter_empty'] = 0;
  $handler->display->display_options['fields']['field_url_text']['type'] = 'text_plain';
  $handler->display->display_options['fields']['field_url_text']['field_api_classes'] = 0;
  /* Field: Content: Body */
  $handler->display->display_options['fields']['body']['id'] = 'body';
  $handler->display->display_options['fields']['body']['table'] = 'field_data_body';
  $handler->display->display_options['fields']['body']['field'] = 'body';
  $handler->display->display_options['fields']['body']['label'] = '';
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
  $handler->display->display_options['fields']['body']['type'] = 'text_summary_or_trimmed';
  $handler->display->display_options['fields']['body']['settings'] = array(
    'trim_length' => '600',
  );
  $handler->display->display_options['fields']['body']['field_api_classes'] = 0;
  /* Sort criterion: Taxonomy term: Name */
  $handler->display->display_options['sorts']['name']['id'] = 'name';
  $handler->display->display_options['sorts']['name']['table'] = 'taxonomy_term_data';
  $handler->display->display_options['sorts']['name']['field'] = 'name';
  $handler->display->display_options['sorts']['name']['relationship'] = 'term_node_tid';
  $handler->display->display_options['sorts']['name']['expose']['label'] = 'Country Term Name';
  /* Filter criterion: Content: Published or admin */
  $handler->display->display_options['filters']['status_extra']['id'] = 'status_extra';
  $handler->display->display_options['filters']['status_extra']['table'] = 'node';
  $handler->display->display_options['filters']['status_extra']['field'] = 'status_extra';
  /* Filter criterion: Content: Type */
  $handler->display->display_options['filters']['type']['id'] = 'type';
  $handler->display->display_options['filters']['type']['table'] = 'node';
  $handler->display->display_options['filters']['type']['field'] = 'type';
  $handler->display->display_options['filters']['type']['value'] = array(
    'partner' => 'partner',
  );
  /* Filter criterion: Content translation: Language */
  $handler->display->display_options['filters']['language']['id'] = 'language';
  $handler->display->display_options['filters']['language']['table'] = 'node';
  $handler->display->display_options['filters']['language']['field'] = 'language';
  $handler->display->display_options['filters']['language']['value'] = array(
    '***CURRENT_LANGUAGE***' => '***CURRENT_LANGUAGE***',
    'und' => 'und',
  );

  /* Display: Block: All by Country */
  $handler = $view->new_display('block', 'Block: All by Country', 'block');
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
  $translatables['partners'] = array(
    t('Master'),
    t('Partners'),
    t('more'),
    t('Apply'),
    t('Reset'),
    t('Sort by'),
    t('Asc'),
    t('Desc'),
    t('Items per page'),
    t('- All -'),
    t('Offset'),
    t('Total Count Footer'),
    t('<?php
  $view = views_get_current_view();
  print \'<span class="view-total-count">\' . $view->total_rows . \'</span>\'; 
?>'),
    t('Country'),
    t('[field_url_text_1]'),
    t('Visit website'),
    t('_new'),
    t('[field_country]: [title]'),
    t('<a href="[field_url_text]" target="_new" title="Visit website">[title]</a>'),
    t('[title]'),
    t('Country Term Name'),
    t('Block: All by Country'),
  );
  $export['partners'] = $view;

  return $export;
}
