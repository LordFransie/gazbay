<?php
/**
 * @file
 * gazprom_administration.layouts.inc
 */

/**
 * Implements hook_default_panels_layout().
 */
function gazprom_administration_default_panels_layout() {
  $export = array();

  $layout = new stdClass();
  $layout->disabled = FALSE; /* Edit this to true to make a default layout disabled initially */
  $layout->api_version = 1;
  $layout->name = 'two_one';
  $layout->admin_title = 'Two + One';
  $layout->admin_description = 'Top-left (fixed), Top-right (fluid) and then one center (fluid) below it.';
  $layout->category = 'Admin Layouts';
  $layout->plugin = 'flexible';
  $layout->settings = array(
    'items' => array(
      'canvas' => array(
        'type' => 'row',
        'contains' => 'column',
        'children' => array(
          0 => 'main',
        ),
        'parent' => NULL,
        'class' => '',
        'column_class' => '',
        'row_class' => '',
        'region_class' => '',
        'no_scale' => FALSE,
        'fixed_width' => '',
        'column_separation' => '0.5em',
        'region_separation' => '0.5em',
        'row_separation' => '0.5em',
      ),
      'main' => array(
        'type' => 'column',
        'width' => 100,
        'width_type' => '%',
        'children' => array(
          0 => 6,
          1 => 'main-row',
        ),
        'parent' => 'canvas',
        'class' => '',
      ),
      'main-row' => array(
        'type' => 'row',
        'contains' => 'region',
        'children' => array(
          0 => 'center',
        ),
        'parent' => 'main',
      ),
      'center' => array(
        'type' => 'region',
        'title' => 'Center',
        'width' => 100,
        'width_type' => '%',
        'parent' => 'main-row',
      ),
      6 => array(
        'type' => 'row',
        'contains' => 'column',
        'children' => array(
          0 => 8,
          1 => 7,
        ),
        'parent' => 'main',
        'class' => '',
      ),
      7 => array(
        'type' => 'column',
        'width' => '100',
        'width_type' => '%',
        'parent' => '6',
        'children' => array(
          0 => 10,
        ),
        'class' => '',
      ),
      8 => array(
        'type' => 'column',
        'width' => '700',
        'width_type' => 'px',
        'parent' => '6',
        'children' => array(
          0 => 9,
        ),
        'class' => '',
      ),
      9 => array(
        'type' => 'row',
        'contains' => 'region',
        'children' => array(
          0 => 'top_left',
        ),
        'parent' => '8',
        'class' => '',
      ),
      10 => array(
        'type' => 'row',
        'contains' => 'region',
        'children' => array(
          0 => 'top_right',
        ),
        'parent' => '7',
        'class' => '',
      ),
      'top_left' => array(
        'type' => 'region',
        'title' => 'Top Left',
        'width' => 100,
        'width_type' => '%',
        'parent' => '9',
        'class' => '',
      ),
      'top_right' => array(
        'type' => 'region',
        'title' => 'Top Right',
        'width' => 100,
        'width_type' => '%',
        'parent' => '10',
        'class' => '',
      ),
    ),
  );
  $export['two_one'] = $layout;

  return $export;
}
