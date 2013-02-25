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
?>
<div class="views-field views-field-field-background-image">
  <?php
   
    // Put the one image in field_background_image together with multiple images in field_background_image_multiple.
    // This is a bit of a hack. Consider a better solution for this. Consider replacing the two fields with one (that can be multiple).
    // They also need to be randomly sorted so that a different first image is always chosen.
    if (!empty($fields['field_background_image'])) {
      if (!empty($fields['field_background_image_multiple'])) {
        $multiple_images = $fields['field_background_image_multiple']->content;
        
        $background_images = explode('/><', $fields['field_background_image_multiple']->content);
        foreach($background_images as &$one_image) {
          if (!preg_match('/^</', $one_image)) $one_image = '<' . $one_image;
          if (!preg_match('/\/>$/', $one_image)) $one_image .= '/>';
        }
      }
      $background_images[] = $fields['field_background_image']->content;
      shuffle($background_images);
      print $fields['field_background_image']->wrapper_prefix . $fields['field_background_image']->label_html 
            . implode('', $background_images) . $fields['field_background_image']->wrapper_suffix;
    }
  
  ?>
</div>
<div class="front-feature-content">
  <div class="front-feature-spacer"></div>
  <div class="left-side-content">
    <hr />
    <?php if (!empty($fields['title'])) print $fields['title']->wrapper_prefix . $fields['title']->label_html . $fields['title']->content . $fields['title']->wrapper_suffix; ?>
    <?php if (!empty($fields['body'])) print $fields['body']->wrapper_prefix . $fields['body']->label_html . $fields['body']->content . $fields['body']->wrapper_suffix; ?>
    <?php if (!empty($fields['view_node_1'])) print $fields['view_node_1']->wrapper_prefix . $fields['view_node_1']->label_html . $fields['view_node_1']->content . $fields['view_node_1']->wrapper_suffix; ?>
  </div>
  <div class="right-side-content">
    <?php if (!empty($fields['field_body_2'])) print $fields['field_body_2']->wrapper_prefix . $fields['field_body_2']->label_html . $fields['field_body_2']->content . $fields['field_body_2']->wrapper_suffix; ?>
    <?php if (!empty($fields['view_node'])) print $fields['view_node']->wrapper_prefix . $fields['view_node']->label_html . $fields['view_node']->content . $fields['view_node']->wrapper_suffix; ?>
  </div>
</div>
