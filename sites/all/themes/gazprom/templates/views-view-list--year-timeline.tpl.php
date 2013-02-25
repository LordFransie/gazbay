<?php
/**
 * @file views-view-list--year-timeline.tpl.php
 * Customized version of views-view-list.tpl.php.
 * Designed to output only the grouped-by field of the History View, year_timeline block
 * Works in conjunction with views-view--year-timeline.tpl.php
 *
 * - $title : The title of this group of rows.  May be empty.
 * - $options['type'] will either be ul or ol.
 * @ingroup views_templates
 */
?>
<?php if (!empty($title)) : ?>
<li><span class="background"></span><span class="text"><?php print $title; ?></span></li>
<?php endif; ?>
