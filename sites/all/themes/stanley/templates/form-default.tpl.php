<div class="form form-layout-default">
  <div class="row">
    <div class="column-main span-two-thirds"><div class="column-wrapper clearfix">
      <?php print drupal_render_children($form); ?>
      <?php print stanley_render_clone($actions); ?>
    </div></div>
    <div class="column-side span-one-third"><div class="column-wrapper clearfix">
      <?php print drupal_render($actions); ?>
      <?php print drupal_render($sidebar); ?>
    </div></div>
  </div>
  <?php if (!empty($footer)): ?>
    <div class="column-footer"><div class="column-wrapper clearfix"><?php print drupal_render($footer); ?></div></div>
  <?php endif; ?>
</div>
