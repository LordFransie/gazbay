<?php
/**
 * @file
 * Implementation of OpenLayers behavior for tooltips.
 */

/**
 * Ctools plugin definition.
 */
//$plugin = array(
//  'title' => t('Gazprom: Tooltip'),
//  'description' => t('A specially made version of tooltip popup for the Gazprom International site.'),
//  'type' => 'layer',
//  'behavior' => array(
//    'file' => 'gazprom_openlayers_behavior_tooltip.inc',
//    'class' => 'gazprom_openlayers_behavior_tooltip',
//    'parent' => 'openlayers_behavior',
//  ),
//);

/**
 * Attribution Behavior
 */
class gazprom_openlayers_behavior_tooltip extends openlayers_behavior {
  /**
   * Provide initial values for options.
   */
  function options_init() {
    return array(
      'attribution' => '',
      'layers' => array(),
    );
  }

  /**
   * Form defintion for per map customizations.
   */
  function options_form($defaults = array()) {
    // Only prompt for vector layers
    $vector_layers = array();
    foreach ($this->map['layers'] as $id => $name) {
      $layer = openlayers_layer_load($id);
      if (isset($layer->data['vector']) && $layer->data['vector'] == TRUE) {
        $vector_layers[$id] = $name;
      }
    }

    return array(
      'layers' => array(
        '#title' => t('Layers'),
        '#type' => 'checkboxes',
        '#options' => $vector_layers,
        '#description' => t('Select layer to apply tooltips to.'),
        '#default_value' => isset($defaults['layers']) ?
          $defaults['layers'] : array(),
      ),
    );
  }

  /**
   * Render.
   */
  function render(&$map) {
    drupal_add_js(drupal_get_path('module', 'gazprom_world_map') .
      '/openlayers_plugins/gazprom_openlayers_behavior_tooltip.js', array('weight' => 11));
    drupal_add_css(drupal_get_path('module', 'gazprom_world_map') .
      '/openlayers_plugins/gazprom_openlayers_behavior_tooltip.css');
    return $this->options;
  }
}
