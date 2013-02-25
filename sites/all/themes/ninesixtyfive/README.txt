CONTENTS OF THIS FILE
---------------------
 * Introduction
 * Features
 * Installation
 * Useful Information
 * Known Issues
 * Authors
 * Sponsors


INTRODUCTION
-----------------------

965 is a base theme intended for advanced drupal theming, aiming at bringing the fun back to theming.
it is a collection of many open source goodies combined together.
it was started as a fork of Zentropy (http://drupal.org/project/zentropy) but have since evolved into new areas.
most of the ideas here came from many super talented developers, credits is left where credit is due.
the bugs are mine.

What it does ?
 * It includes SASS framework (thanks peroxide - https://github.com/codeincarnate/peroxide and SASSy - http://drupal.org/project/sassy)
 * It converts the core template files to HTML5 markup (thanks Boron - http://drupal.org/project/boron)
 * It includes a perfectly semantic grid system (based on 960gs http://960.gs/ via Compass - http://compass-style.org).
 * It is responsive out of the box - keeping a mobile first approuch.
 * It includes an HTMl5-friendly CSS Reset and other tweaks & best practices from HTML5Boilerplate v2.0 (http://html5boilerplate.com)
 * It includes important IE HTML5 fixes like respond.js  (https://github.com/scottjehl/Respond) and HTML5shiv (http://code.google.com/p/html5shiv)
 * It also features a bunch of other goodies thrown in: more regions, Google Analytics integration, support for Modernizr (http://www.modernizr.com/) and all sorts of awesomeness
 * It *doesn't* give you a pile of CSS rules you will have to override.


FEATURES
---------------

 * SASS (Syntactically Awesome Stylesheets) & Compass support - write CSS the way you always wanted - no further requirements, will work on almost any server
 * Responsive, mobile-first, content-first layout, out of the box.
 * Perfectly semantic grid - no more non-semantic grid classes thanks to compass and 960gs
 * Adaptive grid - you choose width, # of columns, gutter width, we (well, SASS) do the math.
 * Cross-browser styling compatibility improvements from HTML5 Boilerplate (http://html5boilerplate.com)
 * Boilerplate, ready made, sub-theme. just extract, rename, and start theming
 * Simple Google Analytics integration via theme settings
 * HTML5 doctype and meta content-type
 * Header and Footer sections marked up with header and footer elements
 * Navigation marked up with nav elements
 * Sidebars marked up with aside elements
 * Nodes marked up with article elements containing header and footer elements
 * Comments marked up as articles nested within their parent node article
 * Blocks marked up with section elements
 * Search form uses the new input type="search" attribute
 * WAI-ARIA accessibility roles added to primary elements
 * Updates all core modules to HTML5 markup
 * HTML5 shiv script included for full IE compatibility
 * respond.js included for a responsive IE
 * Many extra body and node classes for easy theming
 * Full HTML5 CSS Reset - from normalize.css
 * Optional blueprint grid system integration, no more vendor prefixes, simple IE fixes, and many more - all thanks to compass (http://compass-style.org/blog/2011/04/24/v011-release/)
 * Grid background "image", for easy element aligning, made with CSS3 and SASS to fit every grid you can imagine. 
 * oh, and RTL support, of course.


INSTALLATION
----------------------

 * Bad way - Extract the theme in your sites/all/themes/ directory, enable it and start hacking

 * Good way - 

      * Extract the theme in your sites/all/themes/ directory
      * Extract SUBTHEME.tar.gz into its own folder in your themes directory
      * Optional but recommended - Rename at least your folder and .info file
      * Enable your sub-theme and start hacking


USEFUL INFORMATION
----------------------------------

 * Out of the box 965 will give you a 960 pixel grid system, you may change grid properties in the _settings.scss file of your sub-theme

 * While you develop, you should keep the development mode turned on (see theme settings page), this will compile your SASS on every page load, and will give you FireSASS support (https://addons.mozilla.org/en-US/firefox/addon/firesass-for-firebug/). 

 * When not developing, turn development mode off, this will keep your CSS output light as a feather, in fact, the output of our semantic version of 960gs is much slimmer then the original css grid system.

 * Fluid child method - a way to have a nested grid system even with fluid, percentage-based, grids (see ninesixtyfive.scss)

 * 965 will always force latest IE rendering engine (even in intranet) & Chrome Frame

 * 965 will always set mobile viewport initial scale to 100%. with a responsive layout, this will give your mobile users the best experience, no need to zoom on every page load

 * 965 applies classes to the <html> tag to enable easier styling for Internet Exporer :

   - html.ie6 #selector { ... }
   - htm.ie7.ie6 #selector { ... }


KNOWN ISSUES
------------------------

* We hard-code the responsive layout break-points, we should have them configurable
* We don't have bi-directionality, directionality must be manually set in the SASS settings file
* Compiled CSS is not flushed with drupal cache clearing and must be flushed separately


AUTHORS
--------------

* Tsachi Shlidor (tsi) - http://drupal.org/user/322980 & http://rtl-themes.co.il
* Raz konforti (konforti) - http://drupal.org/user/99548
* Alex Weber (alexweber) - http://drupal.org/user/850856 & http://www.alexweber.com.br
* Leandro Nunes (lnunesbr) - http://drupal.org/user/324393 & http://www.nunesweb.com
* Miguel Trindade (migueltrindade) - http://drupal.org/user/690418/ & http://www.migueltrindade.com.br


SPONSORS
----------------

This project is made possible by :

* Webdrop (http://webdrop.net.br) 
* Linnovate (http://linnovate.net)
* Many others, credit is left where credit is due.
