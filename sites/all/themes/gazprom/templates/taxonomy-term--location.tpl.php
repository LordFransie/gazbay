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
<?php
  $region_menu = module_invoke('menu_block', 'block_view', '4');
  unset($region_menu['subject']); unset($region_menu['subject_array']);

  $country_menu = module_invoke('menu_block', 'block_view', '5');
  $current_region = $country_menu['subject']; // not entirely sure why subject is being set, but i'm okay with it since we need it anyway
  if ($current_region == 'CIS') $current_region = t('Commonwealth of Independent States'); // @TODO total hack .. use term's description field!
  unset($country_menu['subject']); unset($country_menu['subject_array']);

?>
<article id="taxonomy-term-<?php print $term->tid; ?>" class="open-within-room <?php print $classes; ?> clearfix"<?php print $attributes; ?>>
    
  <div class="expand-top">
    <?php print render($content['field_background_image']); ?>
    <div class="top-content">
      <hr />
      <h2><?php print t('Countries'); ?></h2>
    </div>
  </div><!-- /.expand-top -->

  
  <div class="content constant-bottom"<?php print $content_attributes; ?>>
    <div class="bottom-content content-country content-location step-width auto-margins min-width-960 max-width-1080">
    <?php
      // hide everything .. 'cause i'm lazy
      foreach($content as $key => $element) {
        hide($content[$key]);
      }; ?>
        <h3 class="no-border"><?php print $current_region; ?></h3>
        <div class="region-menu open-within-room"><?php print render($region_menu); ?></div>
        <hr />
        <div class="country-menu open-within-room"><?php print render($country_menu); ?></div>
        <div class="left-side">
          <hr class="country-menu-special-border"/>
          <?php
          if (!empty($content['field_image']) || !empty($content['field_location_information'])):
            print render($content['field_image']);
          ?>
          <div class="paginate-country-information-to-overlay">
          <?php
            print render($content['field_location_information']);
            //print render($content['field_page_code']);
          ?>
          </div>
          <div class="clearfix"></div>
          <hr />
          <?php endif; ?>
           <?php
            $view = views_get_view('country_project_or_news');
            $view->set_display('block'); // project list
            $view->set_arguments(array($term->tid));
            $view->execute();
            $rowCount = count($view->result);
            if ($rowCount > 0 ) {
              $view_title = t('Projects in ') . $term_name . ':';
              $view_content =  $view->preview();
            } else {
              $view = views_get_view('country_project_or_news');
              $view->set_display('block_1'); // corporate news list
              $view->set_arguments(array($term->tid));
              $view->execute();
              $rowCount = count($view->result);
              $view_title = t('Corporate News for ') . $term_name . ':';
              $view_content = $view->preview();
            }
            
            if ($rowCount > 0):
           ?>
          <div class="related-content">
            <h3 class="no-border"><?php print $view_title; ?></h3>
            <?php print $view_content; ?>
          </div>
           <?php endif; ?>
        </div>
        <div class="right-side Xcolumn Xrid_4">
          <?php
            print render($content['field_country_map']);
            if (empty($content['field_country_map'])) print render($content['field_flag_image']);
            //print render($content['field_page_code']);
          ?>
          <?php
            $related_video = field_get_items('taxonomy_term', $term, 'field_video_attached');
            $related_photo_set = field_get_items('taxonomy_term', $term, 'field_collection_attached');
            if (!empty($related_video[0]['nid'])) {
              print views_embed_view('browse_videos', 'embed_video_country', $related_video[0]['nid']);
            } else if (!empty($related_photo_set[0]['nid'])) {
              print views_embed_view('attached_photo_set', 'block_attached_photos_2x2', $related_photo_set[0]['nid']);
            }
          ?>
        </div>
        
      
    <?php
      //print render($content);
      //print render($content['field_image']);
      //print render($content['body']);
      //print render($content['field_page_code']);
    ?>
        <div class="clearfix"></div>
<?php if (false): ?>        
        <div class="page-tools <?php if (empty($content['field_location_information'])) { print 'no-body'; } ?>">
          <div class="pagination-goes-here"></div>
         <?php if (!empty($content['field_location_information'])): ?>
          <div class="page-tool print" title="<?php print t('Print'); ?>></div>
          <div class="page-tool share"><span>Share</span></div>
         <?php endif; ?>
          <div class="clearfix"></div>
        </div>
<?php endif; ?>        
    </div>
    <div class="hide open-within-room"><?php print render(module_invoke('menu', 'block_view', 'menu-countries')); ?></div>
    <div class="path-to-content hide"><?php $current_path = drupal_get_path_alias($_GET["q"]); print '/'.$current_path; ?></div>
 </div><!-- /.content -->

  <?php if (!empty($content['field_tags']) || !empty($content['links'])): ?>
    <footer>
      <?php //print render($content['field_tags']); ?>
      <?php //print render($content['links']); ?>
    </footer>
  <?php endif; ?>

</article><!-- /.taxonomy-term -->
<?php if (false): ?>
<div id="taxonomy-term-<?php print $term->tid; ?>" class="<?php print $classes; ?>">

  <h3><?php print $current_region; ?></h3>
  <div class="region-menu"><?php print render($region_menu); ?></div>
  <div class="country-menu"><?php print render($country_menu); ?></div>

  <?php if (!$page): ?>
    <h2><a href="<?php print $term_url; ?>"><?php print $term_name; ?></a></h2>
  <?php endif; ?>

  <div class="content">
    <?php print render($content); ?>
  </div>

</div>
<?php endif; ?>
