<?php

/**
 * @file
 * Default theme implementation to display a single Drupal page.
 *
 * Available variables:
 *
 * General utility variables:
 * - $base_path: The base URL path of the Drupal installation. At the very
 *   least, this will always default to /.
 * - $directory: The directory the template is located in, e.g. modules/system
 *   or themes/garland.
 * - $is_front: TRUE if the current page is the front page.
 * - $logged_in: TRUE if the user is registered and signed in.
 * - $is_admin: TRUE if the user has permission to access administration pages.
 *
 * Site identity:
 * - $front_page: The URL of the front page. Use this instead of $base_path,
 *   when linking to the front page. This includes the language domain or
 *   prefix.
 * - $logo: The path to the logo image, as defined in theme configuration.
 * - $site_name: The name of the site, empty when display has been disabled
 *   in theme settings.
 * - $site_slogan: The slogan of the site, empty when display has been disabled
 *   in theme settings.
 *
 * Navigation:
 * - $main_menu (array): An array containing the Main menu links for the
 *   site, if they have been configured.
 * - $secondary_menu (array): An array containing the Secondary menu links for
 *   the site, if they have been configured.
 * - $breadcrumb: The breadcrumb trail for the current page.
 *
 * Page content (in order of occurrence in the default page.tpl.php):
 * - $title_prefix (array): An array containing additional output populated by
 *   modules, intended to be displayed in front of the main title tag that
 *   appears in the template.
 * - $title: The page title, for use in the actual HTML content.
 * - $title_suffix (array): An array containing additional output populated by
 *   modules, intended to be displayed after the main title tag that appears in
 *   the template.
 * - $messages: HTML for status and error messages. Should be displayed
 *   prominently.
 * - $tabs (array): Tabs linking to any sub-pages beneath the current page
 *   (e.g., the view and edit tabs when displaying a node).
 * - $action_links (array): Actions local to the page, such as 'Add menu' on the
 *   menu administration interface.
 * - $feed_icons: A string of all feed icons for the current page.
 * - $node: The node object, if there is an automatically-loaded node
 *   associated with the page, and the node ID is the second argument
 *   in the page's path (e.g. node/12345 and node/12345/revisions, but not
 *   comment/reply/12345).
 *
 * Regions:
 * - $page['help']: Dynamic help text, mostly for admin pages.
 * - $page['highlighted']: Items for the highlighted content region.
 * - $page['content_top']: Items for the header region.
 * - $page['content']: The main content of the current page.
 * - $page['content_bottom']: Items for the header region.
 * - $page['sidebar_first']: Items for the first sidebar.
 * - $page['sidebar_second']: Items for the second sidebar.
 * - $page['header']: Items for the header region.
 * - $page['footer']: Items for the footer region.
 *
 * @see template_preprocess()
 * @see template_preprocess_page()
 * @see template_process()
 */
?>
<noscript>
<p style="font-size: 1em;margin-top:90px;padding:10px;background-color:red;color:white;text-align:center">This site requires Javascript to function normally. Please enable Javascript on your web browser.</p>
</noscript>
<?php if (false): ?>
<div id="load-screen" class="inline-images">
  <div id="load-table">
    <div id="load-table-cell">
      <div id="load-screen-logo">
        <img src="/<?php print path_to_theme(); ?>/images/gazprom_loading_3.gif" width="380" height="160" />
        <p><?php print t('Loading') . '...'; ?></p>
      </div>
      <!-- <div id="load-progress"><div id="load-progress-bar"></div></div> -->
      <div id="load-screen-tutorial">
        <div id="load-screen-table"><table><tr><td><?php print t('Site tip: On mouse or touchpad use scrolling function to navigate.'); ?></td></tr></table></div>
        <img src="/<?php print path_to_theme(); ?>/images/BJ016_gazprom_04vm.gif" width="273" height="150" />
      </div>
    </div>
  </div>
</div>
<?php endif; ?>
<header id="header" role="banner" class="grid_16 alpha omega">

      <?php if (true): ?>
      <div id="header-left" class="column alpha logo">
        <a href="<?php print $front_page; ?>" id="go-home"><img id="gazprom-logo" src="/<?php print path_to_theme() ?>/images/header-logo.png" width="134" height="67"/></a>
      </div>
      <?php elseif ($page['header-left']): ?>
      <div id="header-left" class="grid_3 alpha">
        <div class="simple box">
          <?php print render($page['header-left']); ?>
        </div>
      </div>
      <?php else: ?>
      <div id="branding" class="grid_3 alpha">
        <div class="simple box">
          <?php if ($logo): ?>
            <a href="<?php print $front_page; ?>" title="<?php print t('Home'); ?>" rel="home" id="logo">
              <img src="<?php print $logo; ?>" alt="<?php print t('Home'); ?>" />
            </a>
          <?php endif; ?>

          <?php if ($site_name): ?>
              <h1 id="site-name">
                <a href="<?php print $front_page; ?>" title="<?php print t('Home'); ?>" rel="home"><span><?php print $site_name; ?></span></a>
              </h1>
          <?php endif; ?>

          <?php if ($site_slogan && false): ?>
            <div id="site-slogan"><?php print $site_slogan; ?></div>
          <?php endif; ?>
        </div>
      </div>
      <?php endif; ?>

      <?php if (true): ?>
      <div id="header-middle" class="column">
        <?php if ($page['main_navigation']): ?>
          <nav id="navigation-main" class="">
            <div class="indicator"></div>
              <?php print render($page['main_navigation']); ?>
          </nav><!-- /#navigation-main -->
        <?php endif; ?>
      </div>
      <?php else: ?>
      <div id="header-middle" class="grid_8">
        <div class="simple box">
        <?php if ($page['main_navigation'] && false): ?>
          <nav id="navigation-main" class="">
              <?php print render($page['main_navigation']); ?>
          </nav><!-- /#navigation-main -->
        <?php else: ?>
          &nbsp;
        <?php endif; ?>
        </div>
      </div>
      <?php endif; ?>

      <?php if (true): ?>
      <div id="header-right" class="column omega">
        <!-- <img src="/<?php print path_to_theme(); ?>/images/options-bar-fpo-2.png" class="options-bar-fpo"/> -->
        <div class="frame">
          <?php if ($page['header-right']):
            print render($page['header-right']);
          else: ?>
            &nbsp;
          <?php endif; ?>
        </div>
      </div>
      <?php else: ?>
      <div id="header-right" class="grid_5 omega">
        <div class="simple box" style="Xbackground-color:lightsteelblue;">
          <?php if ($page['header-right']):
            print render($page['header-right']);
          else: ?>
            &nbsp;
          <?php endif; ?>
        </div>
      </div>
      <?php endif; ?>
      <div class="clearfix"></div>
    </header><!-- /#header -->

<div id="scroller">
  <div id="page" class="container_16 clearfix">

    <!-- <div class="clearfix"></div> -->

    <div class="content-floor-wrapper error-floor<?php if (empty($page['second_navigation'])); if ($is_front) print ' front-page'; ?> width-full">

      <?php if ($page['second_navigation']): ?>
      <nav class="second-navigation content-navigation">
        <div class="indicator"></div>
          <?php print render($page['second_navigation']); ?>
      </nav><!-- /#second-navigation -->
      <div class="clearfix"></div>
      <?php endif; ?>

      <div id="<?php print $room_id; ?>" class="content-room-wrapper content-wrapper">
        <h1 class="head-title" style="display:none;"><?php print $head_title; ?></h1>
        <section class="main-section full-height">
          <div class="frame contextual-links-region full-height">
          <?php if ($page['highlighted']): ?>
            <div id="highlighted">
              <?php print render($page['highlighted']); ?>
            </div><!-- /#highlighted -->
          <?php endif; ?>

          <?php if (false && !$is_front): ?>
            <div class="breadcrumb">
              <?php print $breadcrumb; ?>
            </div>
          <?php endif; ?>
          <?php if (false): ?>  
                        <?php print $messages; ?>
                        <?php print render($title_prefix); ?>
                        <?php if ($title): ?>
                          <h1 class="title" id="page-title"><?php print $title; ?></h1>
                        <?php endif; ?>
                        <?php print render($title_suffix); ?>
                        <?php if ($tabs): ?>
                          <div class="tabs"><?php print render($tabs); ?></div>
                        <?php endif; ?>
                        <?php print render($page['help']); ?>
                        <?php if ($action_links): ?>
                          <ul class="action-links"><?php print render($action_links); ?></ul>
                        <?php endif; ?>
          <?php endif; ?>

        <?php if ($page['third_navigation']): ?>
          <nav class="third-navigation content-navigation">
            <div class="frame">
              <?php print render($page['third_navigation']); ?>
            </div>
          </nav><!-- /#third-navigation -->
          <div class="clearfix"></div>
        <?php endif; ?>

          <div class="content-main room-content column full-height <?php print 'grid_16'; // print ns('grid_16', $page['content_sidebar_first'], 4, $page['content_sidebar_second'], 4) . ' ' . ns('push_4', !$page['content_sidebar_first'], 4); ?>">
            <?php print render($page['content_top']); ?>
            <?php print render($page['content']); ?>
            <?php print render($page['content_bottom']); ?>
            <?php // print $feed_icons; ?>
          </div>

          <?php if (FALSE && $page['content_sidebar_first']): ?>
                      <aside class="content-sidebar-first room-content column sidebar region grid_4 <?php print ns('pull_12', $page['content_sidebar_second'], 4); ?>" role="complementary">
                        <div class="box">
                        <?php print render($page['content_sidebar_first']); ?>
                        </div><!-- /.box -->
                      </aside><!-- /#content-sidebar-first -->
          <?php endif; ?>
          <?php if (FALSE && $page['content_sidebar_second']): ?>
                      <aside class="content-sidebar-second room-content column sidebar region grid_4" role="complementary">
                        <div class="box">
                        <?php print render($page['content_sidebar_second']); ?>
                        </div><!-- /.box -->
                      </aside><!-- /#content-sidebar-second -->
                      <?php endif; ?>

          <div class="clearfix"></div>
          </div><!-- /.frame -->

        </section><!-- /.main-section -->

        <?php if ($page['sidebar_first']): ?>
        <aside class="sidebar-first column sidebar region grid_4 <?php print ns('pull_12', $page['sidebar_second'], 3); ?>" role="complementary">
          <div class="box">
          <?php print render($page['sidebar_first']); ?>
          </div><!-- /.box -->
        </aside><!-- /#sidebar-first -->
        <?php endif; ?>

       <?php if ($page['overlay_sidebar_first']): ?>
      <aside class="overlay-sidebar overlay-sidebar-first sidebar region" role="complementary">
        <div class="box">
        <?php print render($page['overlay_sidebar_first']); ?>
        </div><!-- /.box -->
      </aside><!-- /#sidebar-first -->
      <?php endif; ?>

     <?php if ($page['sidebar_second']): ?>
        <aside class="sidebar-second column sidebar region grid_3" role="complementary">
          <div class="box">
        <?php print render($page['sidebar_second']); ?>
          </div><!-- /.box -->
        </aside><!-- /#sidebar-second -->
      <?php endif; ?>

     <?php if ($page['overlay_sidebar_second']): ?>
      <aside class="overlay-sidebar overlay-sidebar-second sidebar region" role="complementary">
       <?php print render($page['overlay_sidebar_second']); ?>
      </aside><!-- /#sidebar-second -->
     <?php endif; ?>

      <div class="clearfix"></div>
      </div><!-- /.content-room-wrapper -->
      <div class="clearfix"></div>

    </div><!-- /.content-floor-wrapper -->
    <!-- <div class="clearfix"></div> -->
  <?php if (true) { ?> 
  <?php if ($page['development_blocks']): ?>
    <aside id="dev-blocks" class="">
      <div class="box clearfix">
        <?php print render($page['development_blocks']); ?>
      </div>
    </aside><!-- /#dev-blocks -->
  <?php endif; ?>
  <!-- <div class="clearfix"></div> -->
  <?php } ?>

  </div><!-- /#page -->
</div><!-- /#scroller -->

<div id="footer-page" class="container_16">
  <div id="footer-page-left" class="grid_5">
   <?php if ($page['footer_left']): ?>
      <?php print render($page['footer_left']); ?>
   <?php endif; ?>
  </div><!-- /#footer-page-left -->
  <div id="footer-page-middle" class="grid_5">
   <?php if ($page['footer_middle']): ?>
      <?php print render($page['footer_middle']); ?>
   <?php endif; ?>
  </div><!-- /#footer-page-middle -->
  <div id="footer-page-right" class="grid_5">
   <?php if ($page['footer_right']): ?>
      <?php print render($page['footer_right']); ?>
   <?php endif; ?>
  </div><!-- /#footer-page-right -->
</div><!-- /#footer-page -->

<div class="gazprom-overlay" id="gazprom-overlay">
  <div class="overlay-wrapper"></div>
  <div class="content-background"></div>
</div>
<div class="overlay-trigger" id="gazprom-overlay-trigger"></div>

<div class="gazprom-overlay" id="photo-overlay">
  <div class="content-wrapper overlay-wrapper">
  </div>
</div>
<div class="overlay-trigger" id="photo-overlay-trigger"></div>

<div class="gazprom-overlay" id="image-zoom-overlay">
</div>

<div id="busy"></div>
