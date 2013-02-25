<?php
/**
 * @file
 * The theme system, which controls the output of views jQuery Mobile.
 *
 */

/**
 * Display a view as a grid style, with fixed row count.
 */
function template_preprocess_views_grid_fixed_rows(&$vars) {
  $view     = $vars['view'];
  $result   = $view->result;
  $options  = $view->style_plugin->options;
  $handler  = $view->style_plugin;

  $num_rows  = $options['rows'];

  $rows = array();
  $row_indexes = array();

  $num_columns = floor(count($vars['rows']) / $num_rows);
  // The remainders are the 'odd' columns that are slightly longer.
  $remainders = count($vars['rows']) % $num_rows;
  $row = 0;
  $col = 0;
  foreach ($vars['rows'] as $count => $item) {
    $rows[$row][$col] = $item;
    $row_indexes[$row][$col] = $count;

    if ($options['alignment'] == 'horizontal') {
      $col++;
      if (!$remainders && $col == $num_columns) {
        $col = 0;
        $row++;
      }
      if ($remainders && $col == $num_columns + 1) {
        $col = 0;
        $row++;
        $remainders--;
      }
    } else {
      $row++;
      if ($row == $num_rows) {
        $row = 0;
        $col++;
      }
      if ($remainders && $col == $num_columns + 1) {
        $remainders--;
      }
    }
  }
  if (!empty($handler->options['fill_each_column'])) {
    for ($i = 0; $i < count($rows[0]); $i++) {
      // This should be string so that's okay :)
      if (!isset($rows[count($rows) - 1][$i])) {
        $rows[count($rows) - 1][$i] = '';
      }
    }
  }

  // Apply the row classes
  foreach ($rows as $row_number => $row) {
    $row_classes = array();
    $row_classes[] =  'row-' . ($row_number + 1);
    if ($row_number == 0) {
      $row_classes[] =  'row-first';
    }
    if (count($rows) == ($row_number + 1)) {
      $row_classes[] =  'row-last';
    }
    $vars['row_classes'][$row_number] = implode(' ', $row_classes);
    foreach ($rows[$row_number] as $column_number => $item) {
      $column_classes = array();
      $column_classes[] = 'col-'. ($column_number + 1);
      if ($column_number == 0) {
        $column_classes[] = 'col-first';
      }
      elseif (count($rows[$row_number]) == ($column_number + 1)) {
        $column_classes[] = 'col-last';
      }
      if (isset($row_indexes[$row_number][$column_number]) && $column_class = $view->style_plugin->get_row_class($row_indexes[$row_number][$column_number])) {
        $column_classes[] = $column_class;
      }
      $vars['column_classes'][$row_number][$column_number] = implode(' ', $column_classes);
    }
  }
  $vars['rows'] = $rows;
  $vars['class'] = 'views-view-grid views-view-grid-fixed-rows rows-' . $num_rows;
  if (!empty($handler->options['summary'])) {
    $vars['attributes_array'] = array('summary' => $handler->options['summary']);
  }
}


