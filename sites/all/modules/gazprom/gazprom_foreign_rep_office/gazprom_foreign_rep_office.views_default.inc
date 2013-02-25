<?php
/**
 * @file
 * gazprom_foreign_rep_office.views_default.inc
 */

/**
 * Implements hook_views_default_views().
 */
function gazprom_foreign_rep_office_views_default_views() {
  $export = array();

  $view = new view;
  $view->name = 'foreign_rep_offices';
  $view->description = '';
  $view->tag = 'default';
  $view->base_table = 'node';
  $view->human_name = 'Foreign Rep Offices';
  $view->core = 7;
  $view->api_version = '3.0';
  $view->disabled = FALSE; /* Edit this to true to make a default view disabled initially */

  /* Display: Master */
  $handler = $view->new_display('default', 'Master', 'default');
  $handler->display->display_options['title'] = 'Foreign Rep Offices';
  $handler->display->display_options['use_ajax'] = TRUE;
  $handler->display->display_options['access']['type'] = 'perm';
  $handler->display->display_options['cache']['type'] = 'none';
  $handler->display->display_options['query']['type'] = 'views_query';
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
  $handler->display->display_options['relationships']['term_node_tid']['required'] = 1;
  $handler->display->display_options['relationships']['term_node_tid']['vocabularies'] = array(
    'tags' => 0,
    'location' => 0,
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
  /* Field: Taxonomy term: Flag */
  $handler->display->display_options['fields']['field_flag_image_1']['id'] = 'field_flag_image_1';
  $handler->display->display_options['fields']['field_flag_image_1']['table'] = 'field_data_field_flag_image';
  $handler->display->display_options['fields']['field_flag_image_1']['field'] = 'field_flag_image';
  $handler->display->display_options['fields']['field_flag_image_1']['relationship'] = 'term_node_tid';
  $handler->display->display_options['fields']['field_flag_image_1']['label'] = '';
  $handler->display->display_options['fields']['field_flag_image_1']['alter']['alter_text'] = 0;
  $handler->display->display_options['fields']['field_flag_image_1']['alter']['make_link'] = 1;
  $handler->display->display_options['fields']['field_flag_image_1']['alter']['path'] = '[field_url_text_1]';
  $handler->display->display_options['fields']['field_flag_image_1']['alter']['absolute'] = 0;
  $handler->display->display_options['fields']['field_flag_image_1']['alter']['external'] = 1;
  $handler->display->display_options['fields']['field_flag_image_1']['alter']['replace_spaces'] = 0;
  $handler->display->display_options['fields']['field_flag_image_1']['alter']['trim_whitespace'] = 0;
  $handler->display->display_options['fields']['field_flag_image_1']['alter']['alt'] = 'Visit website';
  $handler->display->display_options['fields']['field_flag_image_1']['alter']['target'] = '_new';
  $handler->display->display_options['fields']['field_flag_image_1']['alter']['nl2br'] = 0;
  $handler->display->display_options['fields']['field_flag_image_1']['alter']['word_boundary'] = 1;
  $handler->display->display_options['fields']['field_flag_image_1']['alter']['ellipsis'] = 1;
  $handler->display->display_options['fields']['field_flag_image_1']['alter']['strip_tags'] = 0;
  $handler->display->display_options['fields']['field_flag_image_1']['alter']['trim'] = 0;
  $handler->display->display_options['fields']['field_flag_image_1']['alter']['html'] = 0;
  $handler->display->display_options['fields']['field_flag_image_1']['element_class'] = 'image-flag';
  $handler->display->display_options['fields']['field_flag_image_1']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['field_flag_image_1']['element_default_classes'] = 1;
  $handler->display->display_options['fields']['field_flag_image_1']['hide_empty'] = 0;
  $handler->display->display_options['fields']['field_flag_image_1']['empty_zero'] = 0;
  $handler->display->display_options['fields']['field_flag_image_1']['hide_alter_empty'] = 1;
  $handler->display->display_options['fields']['field_flag_image_1']['click_sort_column'] = 'fid';
  $handler->display->display_options['fields']['field_flag_image_1']['settings'] = array(
    'image_style' => 'flag_144',
    'image_link' => '',
  );
  $handler->display->display_options['fields']['field_flag_image_1']['field_api_classes'] = 0;
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
  $handler->display->display_options['fields']['field_country']['element_type'] = '0';
  $handler->display->display_options['fields']['field_country']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['field_country']['element_default_classes'] = 0;
  $handler->display->display_options['fields']['field_country']['hide_empty'] = 0;
  $handler->display->display_options['fields']['field_country']['empty_zero'] = 0;
  $handler->display->display_options['fields']['field_country']['hide_alter_empty'] = 1;
  $handler->display->display_options['fields']['field_country']['type'] = 'i18n_taxonomy_term_reference_plain';
  $handler->display->display_options['fields']['field_country']['field_api_classes'] = 0;
  /* Field: Country Name */
  $handler->display->display_options['fields']['name']['id'] = 'name';
  $handler->display->display_options['fields']['name']['table'] = 'taxonomy_term_data';
  $handler->display->display_options['fields']['name']['field'] = 'name';
  $handler->display->display_options['fields']['name']['relationship'] = 'term_node_tid';
  $handler->display->display_options['fields']['name']['ui_name'] = 'Country Name';
  $handler->display->display_options['fields']['name']['label'] = '';
  $handler->display->display_options['fields']['name']['exclude'] = TRUE;
  $handler->display->display_options['fields']['name']['alter']['alter_text'] = 0;
  $handler->display->display_options['fields']['name']['alter']['make_link'] = 0;
  $handler->display->display_options['fields']['name']['alter']['absolute'] = 0;
  $handler->display->display_options['fields']['name']['alter']['external'] = 0;
  $handler->display->display_options['fields']['name']['alter']['replace_spaces'] = 0;
  $handler->display->display_options['fields']['name']['alter']['trim_whitespace'] = 0;
  $handler->display->display_options['fields']['name']['alter']['nl2br'] = 0;
  $handler->display->display_options['fields']['name']['alter']['word_boundary'] = 1;
  $handler->display->display_options['fields']['name']['alter']['ellipsis'] = 1;
  $handler->display->display_options['fields']['name']['alter']['strip_tags'] = 0;
  $handler->display->display_options['fields']['name']['alter']['trim'] = 0;
  $handler->display->display_options['fields']['name']['alter']['html'] = 0;
  $handler->display->display_options['fields']['name']['element_type'] = '0';
  $handler->display->display_options['fields']['name']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['name']['element_default_classes'] = 0;
  $handler->display->display_options['fields']['name']['hide_empty'] = 0;
  $handler->display->display_options['fields']['name']['empty_zero'] = 0;
  $handler->display->display_options['fields']['name']['hide_alter_empty'] = 1;
  $handler->display->display_options['fields']['name']['link_to_taxonomy'] = 0;
  $handler->display->display_options['fields']['name']['convert_spaces'] = 0;
  /* Field: Country as Link */
  $handler->display->display_options['fields']['field_url_text']['id'] = 'field_url_text';
  $handler->display->display_options['fields']['field_url_text']['table'] = 'field_data_field_url_text';
  $handler->display->display_options['fields']['field_url_text']['field'] = 'field_url_text';
  $handler->display->display_options['fields']['field_url_text']['ui_name'] = 'Country as Link';
  $handler->display->display_options['fields']['field_url_text']['label'] = '';
  $handler->display->display_options['fields']['field_url_text']['alter']['alter_text'] = 1;
  $handler->display->display_options['fields']['field_url_text']['alter']['text'] = '<a href="[field_url_text]" target="_new" title="Visit website">[field_country] test</a>';
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
  $handler->display->display_options['fields']['field_url_text']['empty'] = '[field_country]';
  $handler->display->display_options['fields']['field_url_text']['hide_empty'] = 0;
  $handler->display->display_options['fields']['field_url_text']['empty_zero'] = 0;
  $handler->display->display_options['fields']['field_url_text']['hide_alter_empty'] = 0;
  $handler->display->display_options['fields']['field_url_text']['type'] = 'text_plain';
  $handler->display->display_options['fields']['field_url_text']['field_api_classes'] = 0;
  /* Field: Office Name */
  $handler->display->display_options['fields']['title']['id'] = 'title';
  $handler->display->display_options['fields']['title']['table'] = 'node';
  $handler->display->display_options['fields']['title']['field'] = 'title';
  $handler->display->display_options['fields']['title']['ui_name'] = 'Office Name';
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
  $handler->display->display_options['fields']['title']['element_class'] = 'label';
  $handler->display->display_options['fields']['title']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['title']['element_default_classes'] = 1;
  $handler->display->display_options['fields']['title']['hide_empty'] = 0;
  $handler->display->display_options['fields']['title']['empty_zero'] = 0;
  $handler->display->display_options['fields']['title']['hide_alter_empty'] = 1;
  $handler->display->display_options['fields']['title']['link_to_node'] = 0;
  /* Field: Address */
  $handler->display->display_options['fields']['field_address_text']['id'] = 'field_address_text';
  $handler->display->display_options['fields']['field_address_text']['table'] = 'field_data_field_address_text';
  $handler->display->display_options['fields']['field_address_text']['field'] = 'field_address_text';
  $handler->display->display_options['fields']['field_address_text']['ui_name'] = 'Address';
  $handler->display->display_options['fields']['field_address_text']['label'] = '';
  $handler->display->display_options['fields']['field_address_text']['alter']['alter_text'] = 0;
  $handler->display->display_options['fields']['field_address_text']['alter']['make_link'] = 0;
  $handler->display->display_options['fields']['field_address_text']['alter']['absolute'] = 0;
  $handler->display->display_options['fields']['field_address_text']['alter']['external'] = 0;
  $handler->display->display_options['fields']['field_address_text']['alter']['replace_spaces'] = 0;
  $handler->display->display_options['fields']['field_address_text']['alter']['trim_whitespace'] = 0;
  $handler->display->display_options['fields']['field_address_text']['alter']['nl2br'] = 0;
  $handler->display->display_options['fields']['field_address_text']['alter']['word_boundary'] = 1;
  $handler->display->display_options['fields']['field_address_text']['alter']['ellipsis'] = 1;
  $handler->display->display_options['fields']['field_address_text']['alter']['more_link'] = 0;
  $handler->display->display_options['fields']['field_address_text']['alter']['strip_tags'] = 0;
  $handler->display->display_options['fields']['field_address_text']['alter']['trim'] = 0;
  $handler->display->display_options['fields']['field_address_text']['alter']['html'] = 0;
  $handler->display->display_options['fields']['field_address_text']['element_class'] = 'outdent-span';
  $handler->display->display_options['fields']['field_address_text']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['field_address_text']['element_default_classes'] = 1;
  $handler->display->display_options['fields']['field_address_text']['hide_empty'] = 0;
  $handler->display->display_options['fields']['field_address_text']['empty_zero'] = 0;
  $handler->display->display_options['fields']['field_address_text']['hide_alter_empty'] = 1;
  $handler->display->display_options['fields']['field_address_text']['field_api_classes'] = 0;
  /* Field: Phone */
  $handler->display->display_options['fields']['field_phone_text']['id'] = 'field_phone_text';
  $handler->display->display_options['fields']['field_phone_text']['table'] = 'field_data_field_phone_text';
  $handler->display->display_options['fields']['field_phone_text']['field'] = 'field_phone_text';
  $handler->display->display_options['fields']['field_phone_text']['ui_name'] = 'Phone';
  $handler->display->display_options['fields']['field_phone_text']['label'] = '';
  $handler->display->display_options['fields']['field_phone_text']['alter']['alter_text'] = 0;
  $handler->display->display_options['fields']['field_phone_text']['alter']['make_link'] = 0;
  $handler->display->display_options['fields']['field_phone_text']['alter']['absolute'] = 0;
  $handler->display->display_options['fields']['field_phone_text']['alter']['external'] = 0;
  $handler->display->display_options['fields']['field_phone_text']['alter']['replace_spaces'] = 0;
  $handler->display->display_options['fields']['field_phone_text']['alter']['trim_whitespace'] = 0;
  $handler->display->display_options['fields']['field_phone_text']['alter']['nl2br'] = 0;
  $handler->display->display_options['fields']['field_phone_text']['alter']['word_boundary'] = 1;
  $handler->display->display_options['fields']['field_phone_text']['alter']['ellipsis'] = 1;
  $handler->display->display_options['fields']['field_phone_text']['alter']['more_link'] = 0;
  $handler->display->display_options['fields']['field_phone_text']['alter']['strip_tags'] = 0;
  $handler->display->display_options['fields']['field_phone_text']['alter']['trim'] = 0;
  $handler->display->display_options['fields']['field_phone_text']['alter']['html'] = 0;
  $handler->display->display_options['fields']['field_phone_text']['element_class'] = 'outdent-span';
  $handler->display->display_options['fields']['field_phone_text']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['field_phone_text']['element_default_classes'] = 1;
  $handler->display->display_options['fields']['field_phone_text']['hide_empty'] = 0;
  $handler->display->display_options['fields']['field_phone_text']['empty_zero'] = 0;
  $handler->display->display_options['fields']['field_phone_text']['hide_alter_empty'] = 1;
  $handler->display->display_options['fields']['field_phone_text']['field_api_classes'] = 0;
  /* Field: Fax */
  $handler->display->display_options['fields']['field_fax_text']['id'] = 'field_fax_text';
  $handler->display->display_options['fields']['field_fax_text']['table'] = 'field_data_field_fax_text';
  $handler->display->display_options['fields']['field_fax_text']['field'] = 'field_fax_text';
  $handler->display->display_options['fields']['field_fax_text']['ui_name'] = 'Fax';
  $handler->display->display_options['fields']['field_fax_text']['label'] = '';
  $handler->display->display_options['fields']['field_fax_text']['alter']['alter_text'] = 0;
  $handler->display->display_options['fields']['field_fax_text']['alter']['make_link'] = 0;
  $handler->display->display_options['fields']['field_fax_text']['alter']['absolute'] = 0;
  $handler->display->display_options['fields']['field_fax_text']['alter']['external'] = 0;
  $handler->display->display_options['fields']['field_fax_text']['alter']['replace_spaces'] = 0;
  $handler->display->display_options['fields']['field_fax_text']['alter']['trim_whitespace'] = 0;
  $handler->display->display_options['fields']['field_fax_text']['alter']['nl2br'] = 0;
  $handler->display->display_options['fields']['field_fax_text']['alter']['word_boundary'] = 1;
  $handler->display->display_options['fields']['field_fax_text']['alter']['ellipsis'] = 1;
  $handler->display->display_options['fields']['field_fax_text']['alter']['more_link'] = 0;
  $handler->display->display_options['fields']['field_fax_text']['alter']['strip_tags'] = 0;
  $handler->display->display_options['fields']['field_fax_text']['alter']['trim'] = 0;
  $handler->display->display_options['fields']['field_fax_text']['alter']['html'] = 0;
  $handler->display->display_options['fields']['field_fax_text']['element_class'] = 'outdent-span';
  $handler->display->display_options['fields']['field_fax_text']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['field_fax_text']['element_default_classes'] = 1;
  $handler->display->display_options['fields']['field_fax_text']['hide_empty'] = 0;
  $handler->display->display_options['fields']['field_fax_text']['empty_zero'] = 0;
  $handler->display->display_options['fields']['field_fax_text']['hide_alter_empty'] = 1;
  $handler->display->display_options['fields']['field_fax_text']['field_api_classes'] = 0;
  /* Field: Email */
  $handler->display->display_options['fields']['field_email_text']['id'] = 'field_email_text';
  $handler->display->display_options['fields']['field_email_text']['table'] = 'field_data_field_email_text';
  $handler->display->display_options['fields']['field_email_text']['field'] = 'field_email_text';
  $handler->display->display_options['fields']['field_email_text']['ui_name'] = 'Email';
  $handler->display->display_options['fields']['field_email_text']['label'] = '';
  $handler->display->display_options['fields']['field_email_text']['alter']['alter_text'] = 0;
  $handler->display->display_options['fields']['field_email_text']['alter']['make_link'] = 0;
  $handler->display->display_options['fields']['field_email_text']['alter']['absolute'] = 0;
  $handler->display->display_options['fields']['field_email_text']['alter']['external'] = 0;
  $handler->display->display_options['fields']['field_email_text']['alter']['replace_spaces'] = 0;
  $handler->display->display_options['fields']['field_email_text']['alter']['trim_whitespace'] = 0;
  $handler->display->display_options['fields']['field_email_text']['alter']['nl2br'] = 0;
  $handler->display->display_options['fields']['field_email_text']['alter']['word_boundary'] = 1;
  $handler->display->display_options['fields']['field_email_text']['alter']['ellipsis'] = 1;
  $handler->display->display_options['fields']['field_email_text']['alter']['more_link'] = 0;
  $handler->display->display_options['fields']['field_email_text']['alter']['strip_tags'] = 0;
  $handler->display->display_options['fields']['field_email_text']['alter']['trim'] = 0;
  $handler->display->display_options['fields']['field_email_text']['alter']['html'] = 0;
  $handler->display->display_options['fields']['field_email_text']['element_class'] = 'outdent-span';
  $handler->display->display_options['fields']['field_email_text']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['field_email_text']['element_default_classes'] = 1;
  $handler->display->display_options['fields']['field_email_text']['hide_empty'] = 1;
  $handler->display->display_options['fields']['field_email_text']['empty_zero'] = 0;
  $handler->display->display_options['fields']['field_email_text']['hide_alter_empty'] = 1;
  $handler->display->display_options['fields']['field_email_text']['field_api_classes'] = 0;
  /* Sort criterion: Taxonomy term: Name */
  $handler->display->display_options['sorts']['name']['id'] = 'name';
  $handler->display->display_options['sorts']['name']['table'] = 'taxonomy_term_data';
  $handler->display->display_options['sorts']['name']['field'] = 'name';
  $handler->display->display_options['sorts']['name']['relationship'] = 'term_node_tid';
  /* Filter criterion: Content: Published or admin */
  $handler->display->display_options['filters']['status_extra']['id'] = 'status_extra';
  $handler->display->display_options['filters']['status_extra']['table'] = 'node';
  $handler->display->display_options['filters']['status_extra']['field'] = 'status_extra';
  /* Filter criterion: Content: Type */
  $handler->display->display_options['filters']['type']['id'] = 'type';
  $handler->display->display_options['filters']['type']['table'] = 'node';
  $handler->display->display_options['filters']['type']['field'] = 'type';
  $handler->display->display_options['filters']['type']['value'] = array(
    'foreign_rep_office' => 'foreign_rep_office',
  );
  /* Filter criterion: Content translation: Language */
  $handler->display->display_options['filters']['language']['id'] = 'language';
  $handler->display->display_options['filters']['language']['table'] = 'node';
  $handler->display->display_options['filters']['language']['field'] = 'language';
  $handler->display->display_options['filters']['language']['value'] = array(
    '***CURRENT_LANGUAGE***' => '***CURRENT_LANGUAGE***',
    'und' => 'und',
  );

  /* Display: Block: All by Name */
  $handler = $view->new_display('block', 'Block: All by Name', 'block');
  $translatables['foreign_rep_offices'] = array(
    t('Master'),
    t('Foreign Rep Offices'),
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
    t('<a href="[field_url_text]" target="_new" title="Visit website">[field_country] test</a>'),
    t('[field_country]'),
    t('Block: All by Name'),
  );
  $export['foreign_rep_offices'] = $view;

  return $export;
}
