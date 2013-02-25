<?php
/**
 * @file views-view-fields.tpl.php
 * Default simple view template to all the fields as a row.
 *
 * - $view: The view in use.
 * - $fields: an array of $field objects. Each one contains:
 *   - $field->content: The output of the field.
 *   - $field->raw: The raw data for the field, if it exists. This is NOT output safe.
 *   - $field->class: The safe class id to use.
 *   - $field->handler: The Views field handler object controlling this field. Do not use
 *     var_export to dump this object, as it can't handle the recursion.
 *   - $field->inline: Whether or not the field should be inline.
 *   - $field->inline_html: either div or span based on the above flag.
 *   - $field->wrapper_prefix: A complete wrapper containing the inline_html to use.
 *   - $field->wrapper_suffix: The closing tag for the wrapper.
 *   - $field->separator: an optional separator that may appear before a field.
 *   - $field->label: The wrap label text to use.
 *   - $field->label_html: The full HTML of the label to use including
 *     configured element type.
 * - $row: The raw result object from the query, with all data it fetched.
 *
 * @ingroup views_templates
 */

/**
 * Custom template for News & Media lists. @TODO consider making a Views Style plugin?
 */
?>
<?php
  $view = $view;
  $fields = $fields;
  $row = $row;
  
  switch ($row->node_type) {
    case 'page_code':
    case 'page':
    case 'webform':
    case 'ceo_message':
    case 'management':
    case 'project':
      $display_type = 'simple-content';
      break;

    case 'media_collection':
    case 'media_article':
    case 'media_corporate_news':
    case 'media_video':
      $display_type = 'date-based-content';
      break;
    default:
      $display_type = 'simple-content';
      break;
}
  $date = &$fields['field_date_event'];
  $type = &$fields['type'];
  $primaryImage = &$fields['field_image'];
  $title = &$fields['title'];
  
  $type->content = str_replace('Media: ', 'in ', $type->content);
  //$type->content = str_replace('Article', 'Corporate News', $type->content);
  
  // adjust content for display
  if ($display_type == 'simple-content') {
    unset($fields['type']);
    unset($fields['field_date_event']);
    unset($fields['field_short_title']);
  }
  if ($display_type == 'date-based-content') {
    unset($fields['title_1']); // used for page title at top of DIV
    unset($fields['field_featured_summary']);
  }
?>
<?php foreach ($fields as $id => $field): ?>
  <?php if (!empty($field->separator)): ?>
    <?php print $field->separator; ?>
  <?php endif; ?>

  <?php if (!empty($field->wrapper_prefix)) print $field->wrapper_prefix; ?>
    <?php if (!empty($field->label_html)) print $field->label_html; ?>
    <?php if (!empty($field->content)) print $field->content; ?>
  <?php if (!empty($field->wrapper_suffix)) print $field->wrapper_suffix; ?>
<?php endforeach; ?>
