<?php

// $Id: 
/**
 * @file
 * Template file for the image_swapper formatter
 */

/**
 *
 * Available variables:
 *
 * $base - Array containing themed images for the base/default state
 * $hover - Array containing themed images for the hover state
 * $effect - String containing the effect name to use
 */

$base = $base;
$hover = $hover;
$effect = $effect;

foreach($base as $delta => $data) {
  
  // determine width & height that container div needs to be. safest to use larger sizes incase base & hover styles are different dimensions
  $width = ($data['dimensions']['width'] > $hover[$delta]['dimensions']['width']) ? $data['dimensions']['width'] : $hover[$delta]['dimensions']['width'];
  $height = ($data['dimensions']['height'] > $hover[$delta]['dimensions']['height']) ? $data['dimensions']['height'] : $hover[$delta]['dimensions']['height'];
?>
<div class="contains-image-swapper" style="width: <?php print $width; ?>px; height: <?php print $height; ?>px; ">
  <?php 
  print $data['image'];
  print $hover[$delta]['image'];
  ?>
</div>
<?php
}
?>