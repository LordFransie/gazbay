/* 
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */

(function($) {

  Drupal.behaviors.microsite = {
    attach: function (context, settings) {  
      //alert('about to call initVideoPlayer() from microsite.js script');
return;

// @TODO should we be doing anything in here now? what about test page?
// @TODO this all needs cleanup

if ($('#gazprom-microsite').length > 0) {
//        Drupal.microsite.install({base: Drupal.settings.microsite.pathToAssets}, function(){
//          Drupal.microsite.installed = true;
//        });
        Drupal.microsite.installed = true;
      }

      $('#microsite-test-init').click(function(e){
        e.preventDefault();
        Drupal.microsite.initFlashPlayer();
      });
      $('#microsite-test-stop').click(function(e){
        e.preventDefault();
        Drupal.microsite.stopFlashPlayer();
      });

    }
  };
})(jQuery);

(function($) {
  
if (!Drupal.microsite) Drupal.microsite = {};

var that = Drupal.microsite = {
    installed: false,
    install: function(params, options) {
      $.extend(this.params, params);
      
      var lang = (this.params.language ? this.params.language : 'en');
      switch (lang) {
        case 'ru':
          this.flashVars.languageNum = "1";
          break;
        case 'es':
          this.flashVars.languageNum = "2";
          break;
        case 'en':
        default:
          this.flashVars.languageNum = "0";
          break;
      }
      
      this.flashVars.xmlLocation = this.params.base + '/xml/data.xml';
      
      swfobject.embedSWF(Drupal.settings.microsite.pathToAssets + "/swf/Gazprom_Player.swf", "gazprom-microsite", "100%", "100%", "10.0.0", false,
        this.flashVars, this.params, this.attributes, _swfCallback);
        
      function _swfCallback (e) {
        if (typeof options.onSuccess == 'function' && e.success) {
          options.onSuccess.call(this, e);
        } else if (typeof options.onFailure == 'function' && !e.success) {
          options.onFailure.call(this, e);
        } else if (typeof options.callback == 'function') {
          options.callback.call(this, e);
        }
        
      }
    },
    remove: function() {
      var $microsite = $('#gazprom-microsite');
      var $wrapper = $microsite.parent();
      $microsite.remove();
      $wrapper.append('<div id="gazprom-microsite"></div>');
    },
    initFlashPlayer: function(e){
      if (e.success) {
        var $microsite = $('#gazprom-microsite');
        if (typeof $microsite.get(0).initPlayer != 'undefined') {
          try {
            $('#gazprom-microsite').get(0).initPlayer();
          }
          catch(e) {
            e = e;
          }
        } else {
          setTimeout(function() { 
            that.initFlashPlayer(e); 
          }, 500);
        }
      }
    },
    stopFlashPlayer: function(){
      var $microsite = $('#gazprom-microsite');
      if (typeof $microsite.get(0).initPlayer != 'undefined') {
        try {
          $('#gazprom-microsite').get(0).stopPlayer();
        }
        catch(e) {
          e = e;
        }
      }
    },
    flashVars: {
      languageNum: "0",
      xmlLocation: ''
    },
    params: {
      menu: "false",
      allowFullScreen: "true",
      wmode: 'transparent',
      base: null
    },
    attributes: {
      id: "gazprom-microsite"
    }
  }
  
})(jQuery);


