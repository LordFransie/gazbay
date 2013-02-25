<?php

/**
 * @file
 * Default theme implementation to display a node.
 *
 * Available variables:
 * - $title: the (sanitized) title of the node.
 * - $content: An array of node items. Use render($content) to print them all,
 *   or print a subset such as render($content['field_example']). Use
 *   hide($content['field_example']) to temporarily suppress the printing of a
 *   given element.
 * - $user_picture: The node author's picture from user-picture.tpl.php.
 * - $date: Formatted creation date. Preprocess functions can reformat it by
 *   calling format_date() with the desired parameters on the $created variable.
 * - $name: Themed username of node author output from theme_username().
 * - $node_url: Direct url of the current node.
 * - $display_submitted: whether submission information should be displayed.
 * - $classes: String of classes that can be used to style contextually through
 *   CSS. It can be manipulated through the variable $classes_array from
 *   preprocess functions. The default values can be one or more of the
 *   following:
 *   - node: The current template type, i.e., "theming hook".
 *   - node-[type]: The current node type. For example, if the node is a
 *     "Blog entry" it would result in "node-blog". Note that the machine
 *     name will often be in a short form of the human readable label.
 *   - node-teaser: Nodes in teaser form.
 *   - node-preview: Nodes in preview mode.
 *   The following are controlled through the node publishing options.
 *   - node-promoted: Nodes promoted to the front page.
 *   - node-sticky: Nodes ordered above other non-sticky nodes in teaser
 *     listings.
 *   - node-unpublished: Unpublished nodes visible only to administrators.
 * - $title_prefix (array): An array containing additional output populated by
 *   modules, intended to be displayed in front of the main title tag that
 *   appears in the template.
 * - $title_suffix (array): An array containing additional output populated by
 *   modules, intended to be displayed after the main title tag that appears in
 *   the template.
 *
 * Other variables:
 * - $node: Full node object. Contains data that may not be safe.
 * - $type: Node type, i.e. story, page, blog, etc.
 * - $comment_count: Number of comments attached to the node.
 * - $uid: User ID of the node author.
 * - $created: Time the node was published formatted in Unix timestamp.
 * - $classes_array: Array of html class attribute values. It is flattened
 *   into a string within the variable $classes.
 * - $zebra: Outputs either "even" or "odd". Useful for zebra striping in
 *   teaser listings.
 * - $id: Position of the node. Increments each time it's output.
 *
 * Node status variables:
 * - $view_mode: View mode, e.g. 'full', 'teaser'...
 * - $teaser: Flag for the teaser state (shortcut for $view_mode == 'teaser').
 * - $page: Flag for the full page state.
 * - $promote: Flag for front page promotion state.
 * - $sticky: Flags for sticky post setting.
 * - $status: Flag for published status.
 * - $comment: State of comment settings for the node.
 * - $readmore: Flags true if the teaser content of the node cannot hold the
 *   main body content.
 * - $is_front: Flags true when presented in the front page.
 * - $logged_in: Flags true when the current user is a logged-in member.
 * - $is_admin: Flags true when the current user is an administrator.
 *
 * Field variables: for each field instance attached to the node a corresponding
 * variable is defined, e.g. $node->body becomes $body. When needing to access
 * a field's raw values, developers/themers are strongly encouraged to use these
 * variables. Otherwise they will have to explicitly specify the desired field
 * language, e.g. $node->body['en'], thus overriding any language negotiation
 * rule that was previously applied.
 *
 * @see template_preprocess()
 * @see template_preprocess_node()
 * @see template_process()
 */
?>
<?php
  $region_menu = module_invoke('menu_block', 'block_view', '4');
  unset($region_menu['subject']); unset($region_menu['subject_array']);

  $country_menu = module_invoke('menu_block', 'block_view', '5');
  $current_region = $country_menu['subject']; // not entirely sure why subject is being set, but i'm okay with it since we need it anyway
  if (($current_region == 'CIS') || ($current_region == 'СНГ')) $current_region = t('Commonwealth of Independent States'); // @TODO total hack .. use term's description field!
  unset($country_menu['subject']); unset($country_menu['subject_array']);

  if (empty($node->field_background_image)) {
    gazprom_util_fill_background_image($content, true);
  }

  $country_term_field = field_get_items('node', $node, 'field_country');
  $tid = $country_term_field[0]['tid'];
  $term = taxonomy_term_load($tid);
  $country_term_localized = field_view_field('node', $node, 'field_country', array(
      'label' => 'hidden',
      'type' => 'i18n_taxonomy_term_reference_plain'
  ));
  $view = views_get_view('country_project_or_news');
  $view->set_display('block'); // project list
  $view->set_arguments(array($tid));
  $view->execute();
  $rowCount = count($view->result);
  if ($rowCount > 0 ) {
    //$view_title = t('Projects in @term:', array('@term' => $country_term_localized[0]['#markup'])); // @TODO this is kind of a hack
    $view_title = t('Projects') . ': ';
    $view_content =  $view->preview();
  } else {
    $view = views_get_view('country_project_or_news');
    $view->set_display('block_1'); // corporate news list
    $view->set_arguments(array($tid));
    $view->execute();
    $rowCount = count($view->result);
    //$view_title = t('Corporate News for @term:', array('@term' => $country_term_localized[0]['#markup']));
    $view_title = t('Related Corporate News') . ': ';
    $view_content = $view->preview();
  }

?>
<article id="node-<?php print $node->nid; ?>" class="open-within-room <?php print $classes; ?> clearfix"<?php print $attributes; ?>>
    
  <div class="expand-top">
    <?php print render($content['field_background_image']); ?>
    <div class="top-content">
      <hr />
      <h2><?php print t('Countries'); ?></h2>
    </div>
  </div><!-- /.expand-top -->

  
  <div class="content print-content constant-bottom"<?php print $content_attributes; ?>>
    <div class="bottom-content content-country content-location step-width auto-margins min-width-960 max-width-1200">
    <?php
      // hide everything .. 'cause i'm lazy
      foreach($content as $key => $element) {
        hide($content[$key]);
      }; 
      print render($title_prefix);
      if ($title): ?>
        <h1 class="title node-title overlay-title <?php if (!empty($content['field_subtitle'])) { print 'no-border '; } ?>"><?php print $title; ?></h1>
      <?php endif;
      print render($title_suffix);
      
      ?>
      <h3 class="no-border"><?php print $current_region; ?></h3>
      <div class="region-menu open-within-room"><?php print render($region_menu); ?></div>
      <hr />
      <div class="country-menu open-within-room"><?php print render($country_menu); ?></div>

        <div class="left-side">
          <hr class="country-menu-special-border"/>
          <?php
          if (!empty($content['field_image']) || !empty($content['field_country_info'])):
            print render($content['field_image']);
          ?>
          <div class="paginate-country-information-to-overlay<?php if ($rowCount == 0) print ' no-related-content'; ?>">
          <?php print render($content['field_country_info']); ?>
          </div>
          <div class="clearfix"></div>
            <?php if ($rowCount >0): ?><hr class="country-page-divider"/><?php endif; ?>
          <?php endif; ?>
           <?php
          
            if ($rowCount > 0):
           ?>
          <div class="related-content">
            <h3 class="no-border"><?php print $view_title; ?></h3>
            <?php print $view_content; ?>
          </div>
           <?php endif; ?>
        </div><!-- /.left-side -->
        <div class="right-side">
          <?php
            print render($content['field_country_map']);
            if (empty($content['field_country_map'])) {
              $flag = field_view_field('taxonomy_term', $term, 'field_flag_image', array( 
                  'label' => 'hidden',
                  'type' => 'image',
                  'settings' => array( 'image_style' => 'primary_image_300', 'image_link' => 'nothing' )
                  ));
              print render($flag);
            }
          ?>
          <?php
            $related_video = field_get_items('node', $node, 'field_video_attached');
            $related_photo_set = field_get_items('node', $node, 'field_collection_attached');
            if (!empty($related_video[0]['nid'])) {
              print views_embed_view('browse_videos', 'embed_video_country', $related_video[0]['nid']);
            } else if (!empty($related_photo_set[0]['nid'])) {
              print views_embed_view('attached_photo_set', 'block_attached_photos_2x2', $related_photo_set[0]['nid']);
            }
          ?>
        </div><!-- /.right-side -->
      
      <div class="clearfix"></div>
      <div class="hide open-within-room"><?php //print render(module_invoke('menu_block', 'block_view', '7')); // (all) Menu Countries and Regions (localized) ?></div>
      <div class="path-to-content hide"><?php $content_path = drupal_get_path_alias($_GET["q"]); print $GLOBALS['base_path'] . $GLOBALS['language']->prefix .'/' . $content_path; ?></div>
    </div>
  </div><!-- /.content -->

  <?php if (!empty($content['field_tags']) || !empty($content['links'])): ?>
    <footer>
      <?php //print render($content['field_tags']); ?>
      <?php //print render($content['links']); // @TODO this contains a translation-link!!!! ?>
    </footer>
  <?php endif; ?>

  <?php //print render($content['comments']); ?>

</article><!-- /.node -->
