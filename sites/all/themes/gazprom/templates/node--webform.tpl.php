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

// if there is no background image specified, fetch the one that should be there for the first page (room) of this section (floor).
if (empty($node->field_background_image)) {
  gazprom_util_fill_background_image($content);
}

?>
<article id="node-<?php print $node->nid; ?>" class="<?php print $classes; ?> XXXfull-height clearfix"<?php print $attributes; ?>>
    
  <?php if (false && ($user_picture || !$page || $display_submitted)): ?>
    <header>
      <?php print $user_picture; ?>

      <?php print render($title_prefix); ?>
      <?php if (!$page): ?>
        <h2<?php print $title_attributes; ?>><a href="<?php print $node_url; ?>"><?php print $title; ?></a></h2>
      <?php endif; ?>
      <?php print render($title_suffix); ?>

      <?php if ($display_submitted): ?>
        
      <p class="submitted">
        <?php print $submitted; ?>
        <time pubdate datetime="<?php print $submitted_pubdate; ?>">
        <?php print $submitted_date; ?>
        </time>
      </p>
        
      <?php endif; ?>
    </header>
  <?php endif; ?>

  <div class="expand-top">
    <?php print render($content['field_background_image']); ?>
    <div class="top-content">
      <hr />
      <h2<?php print $title_attributes; ?>><?php print $title; ?></h2>
      <div class="content"><?php print render($content['field_intro_text']); ?></div>
    </div>
  </div><!-- /.expand-top -->

  
  <div class="content constant-bottom"<?php print $content_attributes; ?>>
    <div class="bottom-content step-width auto-margins min-width-960 max-width-980">
    <?php
      // hide everything .. 'cause i'm lazy
      foreach($content as $key => $element) {
        hide($content[$key]);
      }; ?>
      
      <?php if (!empty($content['field_image'])): ?>
      <div class="content-image primary-image-right column">
        <?php print render($content['field_image']); ?>
      </div>
      <?php endif; ?>
      <?php if (!empty($content['field_subtitle'])): ?>
        <div class="content-subtitle <?php if (!empty($content['field_image'])) print 'leave-image-room-right '; ?>">
          <h3 class="no-border"><?php print render($content['field_subtitle']); ?></h3>
          <hr />
        </div>
      <?php endif; ?>
      
      <div class="content-body  <?php if (!empty($content['field_image'])) print 'leave-image-room-right '; ?>">
        <?php print render($content['body']); ?>

        <div class="webform column ajax-form-wrapper">
          <?php print render($content['webform']); ?>
        </div>
        <div class="clearfix"></div>
        <?php
        print render($content);
        print render($content['field_page_code']);
      ?>
      </div>
    </div>
  </div><!-- /.content -->

  <?php if (!empty($content['field_tags']) || !empty($content['links'])): ?>
    <footer>
      <?php //print render($content['field_tags']); ?>
      <?php //print render($content['links']); ?>
    </footer>
  <?php endif; ?>

  <?php //print render($content['comments']); ?>

</article><!-- /.node -->
