<?php

/**
 * Implements template_preprocess_page()
 * 
 */
function gazprom_mobile_preprocess_page(&$vars) {
  
  $templates = array();
  
    // specific template candidate for front page
  if (drupal_is_front_page()) {
      $templates[] = 'page__front';
  }
  $vars['theme_hook_suggestions'] = array_merge($vars['theme_hook_suggestions'],$templates); // most important go LAST (there is a array_reverse call in theme.inc)

}