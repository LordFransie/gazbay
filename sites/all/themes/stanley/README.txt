# Stanley - A Drupal admin theme

## Description

Stanley is an admin theme inspired by Rubik (http://drupal.org/project/rubik) and is based on the Twitter Bootstrap UI kit (http://twitter.github.com/bootstrap/). It was specifically designed to be used with the Admin (http://drupal.org/project/admin) module. As Rubik, it also uses Tao (http://drupal.org/project/tao) as it's base theme.

The goal of this theme is to provide a unified backend experience. If this means we have to do a handful of overrides for a various range of modules, then that is what we will do. We managed to tackle a couple of the more famous modules and UI elements, but there is still enough work to be done.

The following is a selection of modules fine-tuned by Stanley:
  - Views (http://drupal.org/project/views)
  - Context (http://drupal.org/project/context)
  - Field UI
  - Some jQuery UI elements
  - Rules (http://drupal.org/project/rules)
  - Search API (http://drupal.org/project/search_api)
  - WYSIWYG (with CKEditor & the Chris theme) (http://drupal.org/project/wysiwyg)
  - Devel (http://drupal.org/project/devel)

Some minor adjustments have been made to make overlays have an acceptable behavior, but it hasn't been fully tested. I'm also pretty sure the core toolbar module won't play nice. Other untested core modules include dashboard and shortcut.

## Bootstrap

The current version (1.x) of Stanley was developed with Bootstrap v1.4.0.
Whenever Bootstrap v2 is deemed fit to come out and play a 2.x branch will be set up. Until then, let's get this 1.x version finalized.

## Installation

Install as you would any other theme (well, except for the bootstrap part):

1. Download Tao (http://drupal.org/project/tao) and put it in your desired theme folder
2. Download Stanley (http://drupal.org/project/stanley) and put it in the same folder, right next to Tao
3. Download the Bootstrap library v1 (http://twitter.github.com/bootstrap/), make sure the resulting folder is named "bootstrap"
4. Put the bootstrap folder inside the stanley theme folder, the bootstrap.min.css and the js folder should be in [path the themes]/stanley/bootstrap

5. (Optional) delete the docs, examples and lib folders from the bootstrap folder
6. In your Drupal site, go to appearance. Enable Stanley as your admin theme at the bottom of the page.

## Who

Developed and maintained by Stijn De Meyere, a Drupal freelancer (http://villaviscom.be)
