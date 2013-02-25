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
<article id="node-<?php print $node->nid; ?>" class="<?php print $classes; ?> clearfix"<?php print $attributes; ?>>
    
  
  <div class="expand-top">
    <?php print render($content['field_background_image']); ?>
    <div class="top-content">
      <hr />
      <h2<?php print $title_attributes; ?>><?php print $title; ?></h2>
      <div class="content"><?php print render($content['field_intro_text']); ?></div>
    </div>
  </div><!-- /.expand-top -->

  
  <div class="content print-content constant-bottom"<?php print $content_attributes; ?>>
    <div class="bottom-content step-width auto-margins min-width-920 max-width-1400">
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
      if (!empty($content['field_subtitle'])): ?>
        <h3 class="no-border"><?php print render($content['field_subtitle']); ?></h3>
        <hr class="above-content"/>
      <?php endif;
      
      //print render($content);
      print render($content['field_image']);
      print '<div class="paginate-content-inside">';
      print render($content['body']);
      print ('</div>');
      print render($content['field_page_code']);
      ?>
        <div class="clearfix"></div>
        <div class="page-tools <?php if (empty($content['body']) && empty($content['XXfield_page_code'])) { print 'no-body'; } ?>">
          <div class="pagination-goes-here"></div>
         <?php if (!empty($content['body']) || !empty($content['XXfield_page_code'])): ?>
          <a class="page-tool print" title="<?php print t('Print'); ?>"><?php print t('Print'); ?></a>
          <a class="page-tool share" title="<?php print t('Share'); ?>"><?php print t('Share'); ?></a>
          <div class="page-tool-tip share-links">
            <a class="share-facebook share-link" title="Facebook">Facebook</a>
            <a class="share-twitter share-link" title="Twitter">Twitter</a>
            <a class="share-google share-link" title="Google+">Google+</a>
          </div>
         <?php endif; ?>
          <div class="clearfix"></div>
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
