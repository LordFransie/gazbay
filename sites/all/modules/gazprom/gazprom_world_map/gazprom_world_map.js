/* 
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */

(function($) {

  var widthBefore = 0;
  var heightBefore = 0;
  Drupal.behaviors.gazprom_world_map = {
    attach: function (context, settings) {  
      
      // need a window resizer to resize map
      // it also applies initial sizing of map to match window (iframe)
      var $win = $(window);
      $(window).bind('resize.world-map', $.throttle(150, _resizeMap));
      $(window).trigger('resize.world-map');

      function _resizeMap() {
        var $mapContainer = $('.openlayers-container');
        var $map = $mapContainer.find('.openlayers-map');
        var map = $map.data('openlayers');
        if ( typeof map != 'undefined') {
          if ($win.width() != widthBefore || $win.height() != heightBefore) {
            $mapContainer.add($map).css({
              width: $win.width(),
              height: $win.height()
            });
            map.openlayers.updateSize();
            widthBefore = $win.width();
            heightBefore = $win.height();
          }
        } else {
          $.doTimeout('resizeEvent', 500, function() {
            _resizeMap();
          });
        }
      }
    }
  };
})(jQuery);



