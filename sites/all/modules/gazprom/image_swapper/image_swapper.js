/* 
 * Creates rollover effect for thumbnails & logos
 * Dec 29, 2011 - jon@system-werks.com
 *
 * Image Swapper module developed for Gazprom International site
 * @TODO contribute this module?
 */

(function ($, Drupal) {
    Drupal.behaviors.image_swapper = {
      attach: function(context, settings) {
        var $context = $(context)
        $context.find('.contains-image-swapper:not(.image-swapper-processed)', context).each(function(){
          var $div = $(this);
          var $base_image = $div.find('img:first'), $hover_image = $div.find('img:last');
          $hover_image.css({display: 'none'});
          $div.css({position: 'relative'});
          var active_image_cache = new Image(); active_image_cache.src = $hover_image.attr('src'); // pre-fetch the hidden image
          var fadeDuration = 250;
          $base_image.css({opacity: 1, position: 'absolute', top: 0, left: 0, zIndex: '1'});
          $hover_image.css({opacity: 0, position: 'absolute', top: 0, left: 0, zIndex: '2', display: 'inherit'});
          var $hoverElement = $div.parent('a').length == 1 ? $div.parent() : $div;
          
          // If the $div is enclosed in a td element, assume we want to use that for the hoverItent trigger.
          // Yes, this is a total hack and we should really use a specific class to search for, but this will do
          // .. for now (and for the Gazprom project).
          if ($div.closest('td').length > 0) {
            $hoverElement = $div.closest('td');
          }
          
          $hoverElement.mouseenter(function(){
            $(this).addClass('hovering');
            $hover_image.stop(true, false).animate({opacity: 1}, fadeDuration);
          }).mouseleave(function(){
            $(this).removeClass('hovering');
            $hover_image.stop(true, false).animate({opacity: 0}, fadeDuration);
          });
        }).addClass('image-swapper-processed');
      }
    }
})(jQuery, Drupal);

