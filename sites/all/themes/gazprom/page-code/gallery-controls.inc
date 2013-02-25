<div class="photo-gallery-controls">
  <div class="gallery-controls-left">
    <div class="gallery-control-filter">
      <?php print t('Sort By'); ?>
    </div>
  </div>
  <div class="gallery-controls-right">
    <div class="gallery-control-show active-grouping hide">
      <a title="<?php print t('Slide Show'); ?>" class="no-hijax">Show</a>
    </div>
    <?php
      global $language;
      
      switch ($language->language) {
        case 'ru':
          $list_path = '/ru/news-media/photos/list';
          $grid_path = '/ru/news-media/fotoarhiv';
          break;
        
        case 'en':
        default:
          $list_path = '/en/news-media/photos/list';
          $grid_path = '/en/news-media/photos';
          break;
      }
      
      // @TODO Spanish (es)
      // @TODO This needs work! Bad idea to hard-code the paths in here, but needed
      // .. a quick solution for localization of paths. 
    ?>
    <div class="gallery-control-list-view active-grouping">
      <a href = "<?php print $list_path; ?>" title="<?php print t('List View'); ?>" class="no-hijax">List</a>
    </div>
    <div class="gallery-control-grid-view active-grouping active">
      <a href ="<?php print $grid_path; ?>" title="<?php print t('Grid View'); ?>" class="no-hijax">Grid</a>
    </div>
    <div class="gallery-control-search">
      <a title="<?php print t('Search'); ?>" class="no-hijax">Search</a>
    </div>
  </div>
</div>
<div class="gallery-filter-dialog"></div>
<div class="gallery-search-dialog"></div>
<div class="grid-scroll-buttons">
  <div class="grid-button scroll-up fixed-element"></div>
  <div class="grid-button scroll-left fixed-element"></div>
  <div class="grid-button scroll-right fixed-element"></div>
  <div class="grid-button scroll-down fixed-element"></div>
</div>
