<?php
/**
 * @file
 * Contains the list style plugin.
 */

/**
 * Style plugin to render each item of an ordered or unordered list.
 *
 * @ingroup views_style_plugins
 */
class views_grid_fixed_rows_plugin_style extends views_plugin_style {
  /**
   * Set default options
   */
  function option_definition() {
    $options = parent::option_definition();

    $options['rows'] = array('default' => '4');
    $options['alignment'] = array('default' => 'vertical');
    $options['fill_each_column'] = array('default' => TRUE);
    $options['summary'] = array('default' => '');

    return $options;
  }

  /**
   * Render the given style.
   */
  function options_form(&$form, &$form_state) {
    parent::options_form($form, $form_state);
    $form['rows'] = array(
      '#type' => 'textfield',
      '#title' => t('Number of rows'),
      '#default_value' => $this->options['rows'],
      '#required' => TRUE,
      '#element_validate' => array('views_element_validate_integer'),
      '#description' => t('How many rows should the grid contain. The number of columns will be dynamically calculated based on the number of items selected.'),
    );
    $form['alignment'] = array(
      '#type' => 'radios',
      '#title' => t('Alignment'),
      '#options' => array('horizontal' => t('Horizontal'), 'vertical' => t('Vertical')),
      '#default_value' => $this->options['alignment'],
      '#description' => t('Horizontal alignment will place items starting in the upper left and moving right. Vertical alignment will place items starting in the upper left and moving down.'),
    );

    $form['fill_each_column'] = array(
      '#type' => 'checkbox',
      '#title' => t('Fill up each column'),
      '#description' => t('Fill last column with a matching number of rows to make grid even.'),
      '#default_value' => !empty($this->options['fill_each_column']),
    );

    $form['summary'] = array(
      '#type' => 'textfield',
      '#title' => t('Table summary'),
      '#description' => t('This value will be displayed as table-summary attribute in the html. Set this for better accessiblity of your site.'),
      '#default_value' => $this->options['summary'],
    );
  }
}
