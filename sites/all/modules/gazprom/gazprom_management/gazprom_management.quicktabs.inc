<?php
/**
 * @file
 * gazprom_management.quicktabs.inc
 */

/**
 * Implements hook_quicktabs_default_quicktabs().
 */
function gazprom_management_quicktabs_default_quicktabs() {
  $export = array();

  $quicktabs = new stdClass();
  $quicktabs->disabled = FALSE; /* Edit this to true to make a default quicktabs disabled initially */
  $quicktabs->api_version = 1;
  $quicktabs->machine_name = 'management_tabs';
  $quicktabs->ajax = 0;
  $quicktabs->hide_empty_tabs = FALSE;
  $quicktabs->default_tab = 0;
  $quicktabs->title = 'Management Tabs';
  $quicktabs->tabs = array(
    0 => array(
      'vid' => 'management',
      'display' => 'block',
      'args' => '',
      'title' => 'Top Managers',
      'weight' => '-100',
      'type' => 'view',
    ),
    1 => array(
      'vid' => 'management',
      'display' => 'block_1',
      'args' => '',
      'title' => 'Supervisory Board',
      'weight' => '-99',
      'type' => 'view',
    ),
    2 => array(
      'vid' => 'ceo_messages',
      'display' => 'block',
      'args' => '',
      'title' => 'Our Message',
      'weight' => '-98',
      'type' => 'view',
    ),
  );
  $quicktabs->renderer = 'quicktabs';
  $quicktabs->style = 'default';
  $quicktabs->options = array();

  // Translatables
  // Included for use with string extractors like potx.
  t('Management Tabs');
  t('Our Message');
  t('Supervisory Board');
  t('Top Managers');

  $export['management_tabs'] = $quicktabs;

  return $export;
}
