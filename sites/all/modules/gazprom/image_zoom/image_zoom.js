/* 
 * Creates photo zoom effect
 * Dec 29, 2011 - jon@system-werks.com
 *
 * Image Zoom module developed for Gazprom International site
 * @TODO contribute this module?
 */

(function ($, Drupal) {
    Drupal.behaviors.image_zoom = {
      attach: function(context, settings) {
        var $context = $(context)
        var that = this;
        if (!$.fn.overlay) return;
        $context.find('img[zoom-path]:not(.image-zoom-processed)').each(function() {
          var $img = $(this), oldMaskZ, $oldMask;
          $img.overlay({
            target: '#image-zoom-overlay',
            oneInstance: false,
//            effect: 'apple',
            closeOnClick: false,
            closeOnEsc: true,
            close: '#image-zoom-overlay .overlay-close', // not really used, we manually attach a handler below.
            onBeforeLoad: function() {
              var $trigger = this.getTrigger();
              var $overlay = this.getOverlay();
              
              $overlay.css('z-index', '9010');
              
              if(true && $.mask.isLoaded()) {
                  //this is a second overlay, get old settings for use in the onClose function
                  oldMaskZ = $.mask.getConf().zIndex;
                  $oldMask = $.mask.getMask();
                  $oldMask.css('zIndex', 9009);
              }else{
                  $oldMask = null;
                  this.getOverlay().expose({color: '#000', opacity: 0.8, loadSpeed: 'fast', zIndex: 9009, closeOnClick: false, closeOnEsc: false});
              }
              var api = $trigger.data('overlay');
              var finalSize = that.getSize($img);
              $('#image-zoom-overlay').css({
//                background: 'url(' + $trigger.attr('src') + ') no-repeat left top',
                width: finalSize.width,
                height: finalSize.height
              });
              $.mask.getMask().next('img').attr('src', $img.attr('src'));
              $overlay.empty().append('<div class="overlay-content-wrapper"><div class="overlay-close"></div><img /></div>');
              var $wrap = $overlay.find('.overlay-content-wrapper');
              $wrap.find('img').attr('src', $trigger.attr('zoom-path')).fadeOut(0);
              $wrap.find('.overlay-close').fadeOut(0);
              $('#image-zoom-overlay').find('.overlay-content-wrapper img').css({
                width: finalSize.width,
                height: finalSize.height
              });
              
              // attach close handler (created in the onbeforeLoad so it is not used automatically)
              $('#image-zoom-overlay').find('.overlay-close').unbind('click').bind('click.contentOverlay',function() {
                if (api) api.close();
              });


            },
            onLoad: function() {
              var $trigger = this.getTrigger();
              var $overlay = this.getOverlay();
              
              var $wrap = $overlay.find('.overlay-content-wrapper');
              $wrap.find('img').fadeIn(500);
              $wrap.find('.overlay-close').delay(500).fadeIn(500);
            },
            onClose: function() {

              if ($oldMask != null && $.mask.isLoaded(true)) {
                $oldMask.css('zIndex', oldMaskZ).show();
              } else {
                $.mask.close();
              }
            }
          });
            
        }).addClass('image-zoom-processed');
      },
      getSize: function($image) {
        var winWidth = $(window).width() - 176;
        var winHeight = $(window).height() - 176 ;
        
//        var containerWidth = $('#image-zoom-overlay').width();
//        var containerHeight = $('#image-zoom-overlay').height();
        
        var imageWidth = $image.attr('zoom-width');
        var imageHeight = $image.attr('zoom-height');
        
        var ratio = imageWidth / imageHeight;
        
        if (ratio > 1) {
          if (imageWidth > winWidth) {
            return {width: winWidth, height: winWidth / ratio};
          } else {
            return {width: imageWidth, height: imageHeight};
          }
        } else {
          if (imageHeight > winHeight) {
            return {height: winHeight, width: winHeight * ratio};
          } else {
            return {height: imageHeight, width: imageWidth};
          }
        }
      }
    }
    
    
})(jQuery, Drupal);

