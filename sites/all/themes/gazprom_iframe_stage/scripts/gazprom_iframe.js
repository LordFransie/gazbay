/**
 * gazprom iframe Javascript
 * For interactive map
 * 
 * Author: jon@system-werks.com
 *
 **/

// gazprom behavior
(function($, Drupal) {
  Drupal.behaviors.gazprom = {
    attach: function (context, settings) {
      var $context = $(context);
      
      var $map_popup_links = $context.find('.olPopup-container a');
      $map_popup_links.unbind('click').bind('click.gazprom', function(e) {
        e.preventDefault();
        var $anchor = $(this);
        var href = $anchor.attr('href');
        top.Drupal.gazprom.click_handlers.clickInIframe(href,e);
        return false;
      });
    }
  };
})(jQuery, Drupal);
