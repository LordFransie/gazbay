<div class="photo-gallery-content">
  <?php 
    print views_embed_view('photo_list', 'block');
  ?>
</div>
<?php
    include (dirname(__FILE__). '/gallery-controls.inc');
?>