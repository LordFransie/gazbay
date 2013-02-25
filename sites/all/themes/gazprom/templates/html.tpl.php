<?php
/**
 * @file
 * Default theme implementation to display the basic html structure of a single
 * Drupal page.
 *
 * Variables:
 * - $css: An array of CSS files for the current page.
 * - $language: (object) The language the site is being displayed in.
 *   $language->language contains its textual representation.
 *   $language->dir contains the language direction. It will either be 'ltr' or 'rtl'.
 * - $rdf_namespaces: All the RDF namespace prefixes used in the HTML document.
 * - $grddl_profile: A GRDDL profile allowing agents to extract the RDF data.
 * - $head_title: A modified version of the page title, for use in the TITLE tag.
 * - $head: Markup for the HEAD section (including meta tags, keyword tags, and
 *   so on).
 * - $styles: Style tags necessary to import all CSS files for the page.
 * - $scripts: Script tags necessary to load the JavaScript files and settings
 *   for the page.
 * - $page_top: Initial markup from any modules that have altered the
 *   page. This variable should always be output first, before all other dynamic
 *   content.
 * - $page: The rendered page content.
 * - $page_bottom: Final closing markup from any modules that have altered the
 *   page. This variable should always be output last, after all other dynamic
 *   content.
 * - $classes String of classes that can be used to style contextually through
 *   CSS.
 *
 * @see template_preprocess()
 * @see template_preprocess_html()
 * @see template_process()
 */
?>
<!--[if IE]><![endif]-->
  <?php print $doctype; ?>
<!--[if IE 7 ]><html <?php print $html_attributes; ?> class="no-js ie7"><![endif]-->
<!--[if IE 8 ]><html <?php print $html_attributes; ?> class="no-js ie8"><![endif]-->
<!--[if IE 9 ]><html <?php print $html_attributes; ?> class="no-js ie9"><![endif]-->
<!--[if (gt IE 9)|!(IE)]><!--><html <?php print $html_attributes; ?> class="no-js"><!--<![endif]-->
<head<?php print $rdf->profile; ?>>

  <?php print $head; ?>

  <?php // Facebook Open Graph items hacked in for now ?>
  <meta property="og:image" content="<?php print 'http://' . $_SERVER['HTTP_HOST'] . '/' . path_to_theme() . '/images/company_logo.gif'; ?>" />
  
  <?php // Mobile viewport optimized: j.mp/bplateviewport  ?>
  <meta name="viewport" content="width=device-width, initial-scale=1.0, maximum-scale=1, user-scalable=no">

  <?php // Prevent blocking  ?>
  <!--[if IE 6]><![endif]-->

  <title><?php print $head_title; ?></title>
  
<?php print $styles . "\n"; ?>
<?php //print "\n" . implode("\n", $css_files) . "\n"; ?>
<?php // print $modernizr . "\n"; ?>
<?php print $scripts; ?>
<?php //print $html5shiv; // <-- replaced with inclusion of html5boilerplate modernizr-2.0.6.min.js above ?>
<?php //print $respond;  // <-- replaced with inclusion of html5boilerplate modernizr-2.0.6.min.js above ?>
  
</head>
<body class="simple pre-built <?php print $classes; ?>" <?php print $attributes;?>>
  <?php print $page_top; ?>
  <?php print $page; ?>
  <?php print $page_bottom; ?>

  <?php print $analytics; ?>
<!--[if lte IE 7 ]>
  <script src="//ajax.googleapis.com/ajax/libs/chrome-frame/1.0.3/CFInstall.min.js"></script>
  <script>window.attachEvent('onload',function(){CFInstall.check({mode:'overlay'})})</script>
<![endif]-->
</body>
</html>