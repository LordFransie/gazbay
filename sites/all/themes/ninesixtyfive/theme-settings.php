<?php

/**
 * @file
 * Theme settings for the ninesixtyfive
 */
function ninesixtyfive_form_system_theme_settings_alter(&$form, &$form_state) {
  
  $form['#submit'] = array('drupal_theme_rebuild', 'ninesixtyfive_clear_cache');
  
  /**
   * General Settings
   */
  $form['ninesixtyfive_general'] = array(
    '#type' => 'fieldset',
    '#title' => t('General'),
  );
  $form['ninesixtyfive_general']['ninesixtyfive_feed_icons'] = array(
    '#type' => 'checkbox',
    '#title' => t('Display Feed Icons'),
    '#default_value' => theme_get_setting('ninesixtyfive_feed_icons'),
  );
  /**
   * Development Settings
   */
  $form['ninesixtyfive_development'] = array(
    '#type' => 'fieldset',
    '#title' => t('Development'),
  );
  $form['ninesixtyfive_development']['ninesixtyfive_clear_registry'] = array(
    '#type' => 'checkbox',
    '#title' => t('Rebuild theme registry on every page request.'),
    '#description' => t('During theme development, it can be very useful to continuously <a href="!link">rebuild the theme registry</a>. WARNING: this is a huge performance penalty and must be turned off on production websites.', array('!link' => 'http://drupal.org/node/173880#theme-registry')),
    '#default_value' => theme_get_setting('ninesixtyfive_clear_registry'),
  );
  $form['ninesixtyfive_development']['ninesixtyfive_show_grid'] = array(
    '#type' => 'checkbox',
    '#title' => t('Show grid background layer.'),
    '#description' => t('Display a visible background grid, for easier elements positioning'),
    '#default_value' => theme_get_setting('ninesixtyfive_show_grid'),
  );
  /**
   * SASS Settings
   */
  $form['ninesixtyfive_sass'] = array(
    '#type' => 'fieldset',
    '#title' => t('SASS / SCSS'),
  );
  $form['ninesixtyfive_sass']['ninesixtyfive_sass'] = array(
    '#type' => 'checkbox',
    '#title' => t('Compile SASS / SCSS to CSS'),
    '#description' => t('SASS integration - uncheck if you are already using a different sass compiler.'),
    '#default_value' => theme_get_setting('ninesixtyfive_sass'),
  );
  $form['ninesixtyfive_sass']['ninesixtyfive_devel'] = array(
    '#type' => 'checkbox',
    '#title' => t('Development mode - Recompile all SASS / SCSS files on every change (+FireSass support).'),
    '#description' => t('SASS Development - Recompile SASS / SCSS files every time you change them and get <a href="!link">FireSass</a> support. WARNING: css output is way bigger, use only in development.', array('!link' => 'https://addons.mozilla.org/en-US/firefox/addon/firesass-for-firebug/')),
    '#default_value' => theme_get_setting('ninesixtyfive_devel'),
  );
  $form['ninesixtyfive_sass']['ninesixtyfive_flush'] = array(
    '#type' => 'submit',
    '#value' => 'Recompile SASS / SCSS files',
    '#submit' => array('ninesixtyfive_clear_cache'),
  );
  
  /**
   * Breadcrumb settings
   */
  $form['ninesixtyfive_breadcrumb'] = array(
    '#type' => 'fieldset',
    '#title' => t('Breadcrumb'),
  );

  $form['ninesixtyfive_breadcrumb']['ninesixtyfive_breadcrumb_hideonlyfront'] = array(
    '#type' => 'checkbox',
    '#title' => t('Hide the breadcrumb if the breadcrumb only contains the link to the front page.'),
    '#default_value' => theme_get_setting('ninesixtyfive_breadcrumb_hideonlyfront'),
  );
  
  $form['ninesixtyfive_breadcrumb']['ninesixtyfive_breadcrumb_showtitle'] = array(
    '#type' => 'checkbox',
    '#title' => t('Show page title on breadcrumb.'),
    '#default_value' => theme_get_setting('ninesixtyfive_breadcrumb_showtitle'),
  );

  $form['ninesixtyfive_breadcrumb']['ninesixtyfive_breadcrumb_separator'] = array(
    '#type' => 'textfield',
    '#title' => t('Breadcrumb separator'),
    '#default_value' => theme_get_setting('ninesixtyfive_breadcrumb_separator'),
  );

  /**
   * Google Analytics settings
   */
  $roles_all = user_roles();
  $roles_tracked = theme_get_setting('ninesixtyfive_ga_trackroles');

  $form['ninesixtyfive_ga'] = array(
    '#type' => 'fieldset',
    '#title' => t('Google Analytics'),
  );
  
  $form['ninesixtyfive_ga']['ninesixtyfive_ga_enable'] = array(
    '#type' => 'checkbox',
    '#title' => t('Enable Google Analytics'),
    '#default_value' => theme_get_setting('ninesixtyfive_ga_enable'),
  );
  
  $form['ninesixtyfive_ga']['ninesixtyfive_ga_trackingcode'] = array(
    '#type' => 'textfield',
    '#title' => t('Tracking code'),
    '#default_value' => theme_get_setting('ninesixtyfive_ga_trackingcode'),
  );
  
  $form['ninesixtyfive_ga']['ninesixtyfive_ga_trackroles'] = array(
    '#type' => 'checkboxes',
    '#title' => t('Exclude roles'),
    '#options' => $roles_all,
    '#description' => t('Exclude the following roles from being tracked'),
    '#default_value' => !empty($roles_tracked) ? array_values((array) $roles_tracked) : array(),
  );
  
  $form['ninesixtyfive_ga']['ninesixtyfive_ga_anonimize'] = array(
    '#type' => 'checkbox',
    '#title' => t('Anonimize IP'),
    '#description' => t('Tells Google Analytics to anonymize the information sent by the tracker objects by removing the last octet of the IP address prior to its storage. Note that this will slightly reduce the accuracy of geographic reporting.'),
    '#default_value' => theme_get_setting('ninesixtyfive_ga_anonimize')
  );
}

/**
 * Deletes old cached SCSS files.
 */
function ninesixtyfive_clear_cache() {
  variable_del('ninesixtyfive_cache');
  file_scan_directory('public://ninesixtyfive', '/.*/', array('callback' => 'drupal_delete_file_if_stale'));
}
