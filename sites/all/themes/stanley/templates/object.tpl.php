<?php if (!empty($pre_object)) print render($pre_object) ?>

<div class="<?php print $classes ?> clearfix row" <?php print ($attributes) ?>>
  <?php if ($layout && (!empty($submitted) || !empty($links))): ?>
    <aside class="column-side span4"><div class="column-wrapper">
  <?php endif; ?>

  <?php if (!empty($submitted)): ?>
    <div class="<?php print $hook ?>-submitted clearfix"><?php print $submitted ?></div>
  <?php endif; ?>

  <?php if (!empty($links)): ?>
    <nav class="<?php print $hook ?>-links clearfix">
      <?php print render($links) ?>
    </nav>
  <?php endif; ?>

  <?php if ($layout && (!empty($submitted) || !empty($links))): ?>
    </div></aside>
  <?php endif; ?>

  <?php if ($layout): ?>
    <article class="column-main span12"><div class="column-wrapper">
  <?php endif; ?>

  <?php if (!empty($title_prefix)) print render($title_prefix); ?>

  <?php if (!empty($title)): ?>
    <h2 <?php if (!empty($title_attributes)) print $title_attributes ?>>
      <?php if (!empty($new)): ?><span class="new"><?php print $new ?></span><?php endif; ?>
      <?php print $title ?>
    </h2>
  <?php endif; ?>

  <?php if (!empty($title_suffix)) print render($title_suffix); ?>

  <?php if (!empty($content)): ?>
    <div class="<?php print $hook ?>-content clearfix <?php if (!empty($is_prose)) print "prose" ?>">
      <?php print render($content) ?>
    </div>
  <?php endif; ?>

  <?php if ($layout): ?>
    </div></article>
  <?php endif; ?>
</div>

<?php if (!empty($post_object)) print render($post_object) ?>
