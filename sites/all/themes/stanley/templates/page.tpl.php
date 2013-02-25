<nav id="topbar" class="topbar" data-dropdown="dropdown" data-scrollspy="scrollspy">
  <div class="topbar-inner">
    <div class="container-fluid">
      <?php if ($primary_local_tasks): ?>
        <ul class="primary-tabs nav"><?php print render($primary_local_tasks) ?></ul>
      <?php endif; ?>
      <?php if ($primary_local_tasks && $action_links): ?>
        <div class="nav divider"></div>
      <?php endif; ?>
      <?php if ($action_links): ?>
        <ul class="action-links nav"><?php print render($action_links) ?></ul>
      <?php endif; ?>
      <?php if (!$overlay && isset($secondary_menu)) : ?>
        <?php print theme('links', array('links' => $secondary_menu, 'attributes' => array('class' => 'nav secondary-nav'))) ?>
      <?php endif; ?>
    </div>
  </div>
</nav>

<div class="container-fluid">
  <header>
    <nav id="breadcrumb"><?php print $breadcrumb ?></nav>

    <hgroup id="page-title"><div class="limiter clearfix">
      <?php print render($title_prefix); ?>
      <h1 class="page-title <?php print $page_icon_class ?>">
        <?php if (!empty($page_icon_class)): ?><span class="icon"></span><?php endif; ?>
        <?php if ($title) print $title ?>
      </h1>
      <?php if (isset($subtitle)): ?>
        <h2><?php print $subtitle; ?></h2>
      <?php endif; ?>
      <?php print render($title_suffix); ?>
    </div></hgroup>
  </header>

  <?php if ($show_messages && $messages): ?>
  <div id="console" class="clearfix">
    <?php print $messages; ?>
  </div>
  <?php endif; ?>

  <section id="page"><div id="main-content" class="limiter clearfix">
    <?php if ($page['help']): ?>
      <div id="help" class="well">
      <?php print render($page['help']) ?>
      </div>
    <?php endif; ?>
    <div id="content" class="page-content clearfix">
      <?php if (!empty($page['content'])) print render($page['content']) ?>
    </div>
  </div></section>

  <footer class="clearfix">
    <?php if ($feed_icons): ?>
      <div class="feed-icons clearfix">
        <label><?php print t('Feeds') ?></label>
        <?php print $feed_icons ?>
      </div>
    <?php endif; ?>
  </footer>
</div>
