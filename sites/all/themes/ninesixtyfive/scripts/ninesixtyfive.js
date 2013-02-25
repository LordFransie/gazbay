/**
 * ninesixtyfive javascript core
 *
 * - Provides frequently used extensions to base javascript objects
 * - jQuery browser detection tweak
 * - Define functions used in events
 */
 

// Ninesixtyfive behavior
(function($) {
  Drupal.behaviors.ninesixtyfive = {
    attach: function(context) {

      $('html').removeClass('no-js');

    }
  };
})(jQuery);


// Console.log wrapper to avoid errors when firebug is not present
// usage: log('inside coolFunc',this,arguments);
// paulirish.com/2009/log-a-lightweight-wrapper-for-consolelog/
window.log = function() {
  log.history = log.history || [];   // store logs to an array for reference
  log.history.push(arguments);
  if (this.console) {
    console.log(Array.prototype.slice.call(arguments));
  }
};

// init object
var ninesixtyfive = ninesixtyfive || {};

/**
 * Image handling functions
 */
ninesixtyfive.image = { _cache : [] };

// preload images
ninesixtyfive.image.preload = function() {
  for (var i = arguments.length; i--;) {
    var cacheImage = document.createElement('img');
    cacheImage.src = arguments[i];
    ninesixtyfive.image._cache.push(cacheImage);
  }
}
