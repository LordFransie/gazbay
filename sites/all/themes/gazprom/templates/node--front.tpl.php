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

global $language;
?>
<!-- BEGIN node__front.tpl.php -->
<article id="node-<?php print $node->nid; ?>" class="<?php print $classes; ?> full-height clearfix"<?php print $attributes; ?>>
  <div class="content full-height"<?php print $content_attributes; ?>>
    <h2 style="display:none;">Features</h2>
    <div id="front-features" class="expand-top">
      <div class="scrolling-list vertical parallax">
        <div class="scrolling-list-items">
          <?php print views_embed_view('front_features', 'main'); ?>
        </div>  
        <div class="scrolling-list-index vertical">
          <?php print views_embed_view('front_features', 'index'); ?>
        </div>
      </div><!-- /#front-features -->
    </div><!-- /.expand-top -->
    
    <div id="front-news" class="constant-bottom">
      <div class="bottom-content">
        <div class="step-width step-size-100 min-width-900 width-subtract-200 auto-margins">
          <div class="headers">
            <h2 class="first"><?php print t('Featured'); ?></h2>
            <h2 class="second"><?php print t('Highlights'); ?></h2>  
          </div>
          <div id="front-news-feature">
          <?php print views_embed_view('home_small_feature', 'block'); // Block: Featured Queue ?>
          </div>
          <div id="front-news-view">
            <div class="step-width step-size-200">
              <hr>
              <div class="variable-scroller border-top">
            <?php print views_embed_view('news_media_lists', 'block'); // Block: All By Date ?>
              </div>
              <div id="home-social-links">
                <div class="social-links">
                  <a class="facebook" title="Facebook" href="http://www.facebook.com/gazprominternational" target="_new"></a>
                  <a class="twitter" title="Twitter" href="http://twitter.com/gazprom_int" target="_new"></a>
                  <!-- <a class="google-plus" title="Google+" target="_new"></a> -->
                  <a class="wikipedia" title="Wikipedia" target="_new" href="http://<?php print $language->language . '.'; ?>wikipedia.org/wiki/Gazprom_EP_International_B.V."></a>
                  <a class="linkedin" title="LinkedIn" href="http://www.linkedin.com/company/818385?trk=tyah" target="_new"></a>
                  <a class="youtube" title="YouTube" href="http://www.youtube.com/gazprominternational" target="_new"></a>
                  <a class="livejournal" title="LiveJournal" href="http://zargaz.livejournal.com" target="_new"></a>
                  <a class="rss" title="<?php print t('Subscribe to @feed-title', array('@feed-title'=> 'RSS feed')); ?>" target="_new" href="http://<?php print $_SERVER['SERVER_NAME'] . $url_prefix; ?>/rss.xml"></a>
                </div>
                <div class="world-link">
                  <a class="world"></a>
                  <div class="world-overlay">
                    <?php print views_embed_view('mini_country_flags', 'block'); ?>
                    <div class="clearfix"></div>
                    <div class="linker"></div>
                  </div>
                </div>
              </div>
            </div>
          </div>  
          <div class="clearfix"></div>
        </div><!-- /.center-contents -->
      </div><!-- /.bottom-content -->
    <?php
      // We hide the comments, tags and links now so that we can render them later.
      hide($content['comments']);
      hide($content['links']);
      hide($content['field_tags']);
      hide($content['body']);
      print render($content);
    ?>
    </div><!-- /#front-news .constant-bottom -->
  </div><!-- /.content -->

  <?php if (!empty($content['field_tags']) || !empty($content['links'])): ?>
    <footer>
      <?php // print render($content['field_tags']); ?>
      <?php // print render($content['links']); ?>
    </footer>
  <?php endif; ?>


</article><!-- /.node --><!-- END node__front.tpl.php -->
