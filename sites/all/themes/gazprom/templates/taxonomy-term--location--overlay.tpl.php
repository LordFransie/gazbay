<?php

/**
 * @file
 * Default theme implementation to display a term.
 *
 * Available variables:
 * - $name: the (sanitized) name of the term.
 * - $content: An array of items for the content of the term (fields and
 *   description). Use render($content) to print them all, or print a subset
 *   such as render($content['field_example']). Use
 *   hide($content['field_example']) to temporarily suppress the printing of a
 *   given element.
 * - $term_url: Direct url of the current term.
 * - $term_name: Name of the current term.
 * - $classes: String of classes that can be used to style contextually through
 *   CSS. It can be manipulated through the variable $classes_array from
 *   preprocess functions. The default values can be one or more of the following:
 *   - taxonomy-term: The current template type, i.e., "theming hook".
 *   - vocabulary-[vocabulary-name]: The vocabulary to which the term belongs to.
 *     For example, if the term is a "Tag" it would result in "vocabulary-tag".
 *
 * Other variables:
 * - $term: Full term object. Contains data that may not be safe.
 * - $view_mode: View mode, e.g. 'full', 'teaser'...
 * - $page: Flag for the full page state.
 * - $classes_array: Array of html class attribute values. It is flattened
 *   into a string within the variable $classes.
 * - $zebra: Outputs either "even" or "odd". Useful for zebra striping in
 *   teaser listings.
 * - $id: Position of the term. Increments each time it's output.
 * - $is_front: Flags true when presented in the front page.
 * - $logged_in: Flags true when the current user is a logged-in member.
 * - $is_admin: Flags true when the current user is an administrator.
 *
 * @see template_preprocess()
 * @see template_preprocess_taxonomy_term()
 * @see template_process()
 */
?>
<article id="taxonomy-term-<?php print $term->tid; ?>" class="<?php print $classes; ?> clearfix"<?php print $attributes; ?>>
    
<?php
  // hide everything .. 'cause i'm lazy
  foreach($content as $key => $element) {
    hide($content[$key]);
  }; ?>
  
  <div class="content "<?php print $content_attributes; ?>>
        <h3><?php print $term_name; ?></h3>
          <?php
          if (!empty($content['field_image']) || !empty($content['field_location_information'])):
            print render($content['field_image']);
          ?>
          <?php
            print render($content['field_location_information']);
          ?>
          <div class="clearfix"></div>
          <?php endif; ?>
      
        <div class="clearfix"></div>
    <div class="path-to-content hide" style="XXdisplay:none;"><?php $current_path = drupal_get_path_alias($_GET["q"]); print '/'.$current_path; ?></div>
  </div><!-- /.content -->

  <?php if (!empty($content['field_tags']) || !empty($content['links'])): ?>
    <footer>
      <?php //print render($content['field_tags']); ?>
      <?php //print render($content['links']); ?>
    </footer>
  <?php endif; ?>

</article><!-- /.taxonomy-term -->
