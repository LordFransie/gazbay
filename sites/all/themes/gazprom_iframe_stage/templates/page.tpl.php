<?php
/**
 * Tao's page.tpl.php file but with almost everything ripped out 
 */
?>
<?php if ($page['help'] || ($show_messages && $messages)): ?>
  <div id='console'><div class='limiter clearfix'>
    <?php print render($page['help']); ?>
    <?php if ($show_messages && $messages): print $messages; endif; ?>
  </div></div>
<?php endif; ?>

<div id='page'><div class='limiter clearfix'>


  <div id='main-content' class='clearfix'>

    <div id='content' class='iframe-stage clearfix'><?php print render($page['content']) ?></div>

  </div>


</div></div>

