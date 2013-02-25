(function(){
  openSearchResults: function(){
      var $trigger = $('#gazprom-search-overlay-trigger');
      var $searchResults = $('#search-results-staging'); // code in Drupal.gazprom.search puts the core of the restuls HTML in here
      if ($searchResults.length == 0) return;
      if ($searchResults.children().length == 0) return;
      
      var State = $.hijax_getState();
      var previousHref;
      if (typeof State.data.previousHref != 'undefined') {
        previousHref = State.data.previousHref;
      } else {
        previousHref = Drupal.settings.basePath + Drupal.settings.pathPrefix;
      }
      
      function _loadContent(api, $resultsContainer) {
        // @TODO get this out of here? there is a lot crammed into this function
        var $trigger = api.getTrigger();
        var $overlay = api.getOverlay();
        var $wrap = $overlay.find('.overlay-wrapper');
        
        $wrap.empty().append($resultsContainer.children().clone());
        Drupal.attachBehaviors($wrap);
        //$.get(href + '?overlay=true', function(data) {
//          if ($('html').is('.ie8, .ie7, .ie6')) {
//            $newContent = $(innerShiv($(data).find('.content-wrapper').first().outerHTML()));
//          }else {
//            $newContent = $(data).find('.content-wrapper').first();
//          }
//          $wrap.empty().append($newContent);
          
          if (true) {
            Drupal.gazprom.init.printTools($wrap);
            Drupal.gazprom.init.shareTools($wrap);
            // hijax links .. need to do full init.room() on content?
            $wrap.find('.content-wrapper .content-main a, .content-wrapper .sidebar a').not('.outside-overlay, .no-hijax, .gazprom-click-no').once('gazprom-click', function() {
              $(this).hijax();
            });
          } else {
            // @TODO use this instead of code above?
            Drupal.attachBehaviors($wrap);
          }

          // attach jScrollPane to the content
          $wrap.find('.main-section').jScrollPane({
            animateScroll: true,
            hideFocus: true
          });
          
          // attach close handler (not sure why overlay can't identify our internal close button)
          $wrap.find('.overlay-close').unbind('click').bind('click.contentOverlay',function() {
            if (api) api.close();
          });

          // bind custom mousewheel handler so scrolling past bottom doesn't cause main window to scroll
          var $scrollingArea = $('#gazprom-search-overlay > .overlay-wrapper');
          $scrollingArea.bind('mousewheel', function(e, d) {
            e.preventDefault();
            return false;
            // jScrollPane is catching mousewheel events on the content area that has scrollbar
          });
          
        //});
        
      }

      var api = $trigger.data('overlay');
      if (api) {
        if (api.isOpened()) {
          // overlay already open, just refresh content
          api.data = $.extend({}, api.data, {href: href});
          _loadContent(api, $searchResults);
        } else {
          // overlay already initialized, but was closed
          api.data = $.extend({}, api.data, {href: href, hrefOnClose: previousHref}); // update data with previousHref (for close)
          api.load();          
        }
      } else {
        // overlay never opened yet
        // @TODO .. this is a lot of work to get jQuery Tools' overlay to only deal with one overlay instance
        $trigger.overlay({
          mask: {color: '#000', opacity: 0.8, loadSpeed: 'fast'},
  //            effect: 'apple',
          target: '#gazprom-search-overlay',
          close: '#gazprom-search-overlay .overlay-close',
          load: true,
          top: 0,
          onBeforeLoad: function(event) {
            if (!this.data) {
              this.data = {href: href, hrefOnClose: previousHref};
            }
            _loadContent(this, $searchResults);
            // we go through all this crap because this onBeforeLoad function ends up scoped inside the
            // first instance of overlay creation .. which still has the original href!
            return;
          },
          onLoad: function(event) {
            this.getTrigger().addClass('overlay-open');
          },
          onClose: function(event) {
            var $trigger = this.getTrigger();
            var $overlay = this.getOverlay();
            var $wrap = $overlay.find('.overlay-wrapper');

            var $scrollingArea = $('#gazprom-search-overlay > .overlay-wrapper');
            $scrollingArea.unbind('mousewheel');
            
            var jspAPI = $wrap.find('.main-section').data('jsp');
            if (jspAPI) {
              jspAPI.destroy();
            }
            
            $('#gazprom-search-overlay .overlay-wrapper').empty(); // must do this so the id is
            // .. gone from the document. Can't seem to use $wrap. Maybe it's a clone? data within the $anchor?


            if ($trigger.hasClass('overlay-open')) {
              this.getTrigger().removeClass('overlay-open');
              if (Drupal.gazprom.hijaxSettings.initialized == true) {
                $.hijax_addState(this.data.hrefOnClose);
              }
            }
          }
          
        });
        
      }
    }
 
     openSearchResults: function(href) {
      var $trigger = $('#gazprom-search-overlay-trigger');
      
      var State = $.hijax_getState();
      var previousHref;
      if (typeof State.data.previousHref != 'undefined') {
        previousHref = State.data.previousHref;
      } else {
        previousHref = Drupal.settings.basePath + Drupal.settings.pathPrefix;
      }
      
      function _loadContent(api, href) {
        // @TODO get this out of here? there is a lot crammed into this function
        var $trigger = api.getTrigger();
        var $overlay = api.getOverlay();
        var $wrap = $overlay.find('.overlay-wrapper');
        
        $.get(href + '?overlay=true', function(data) {
          if ($('html').is('.ie8, .ie7, .ie6')) {
            $newContent = $(innerShiv($(data).find('.content-wrapper').first().outerHTML()));
          }else {
            $newContent = $(data).find('.content-wrapper').first();
          }
          $wrap.empty().append($newContent);
          
          if (true) {
            Drupal.gazprom.init.printTools($wrap);
            Drupal.gazprom.init.shareTools($wrap);
            // hijax links .. need to do full init.room() on content?
            $wrap.find('.content-wrapper .content-main a, .content-wrapper .sidebar a').not('.outside-overlay, .no-hijax, .gazprom-click-no').once('gazprom-click', function() {
              $(this).hijax();
            });
          } else {
            // @TODO use this instead of code above?
            Drupal.attachBehaviors($wrap);
          }

          // attach jScrollPane to the content
          $wrap.find('.main-section').jScrollPane({
            animateScroll: true,
            hideFocus: true
          });
          
          // attach close handler (not sure why overlay can't identify our internal close button)
          $wrap.find('.overlay-close').unbind('click').bind('click.contentOverlay',function() {
            if (api) api.close();
          });

          // bind custom mousewheel handler so scrolling past bottom doesn't cause main window to scroll
          var $scrollingArea = $('#gazprom-search-overlay > .overlay-wrapper');
          $scrollingArea.bind('mousewheel', function(e, d) {
            e.preventDefault();
            return false;
            // jScrollPane is catching mousewheel events on the content area that has scrollbar
          });
          
        });
        
      }

      var api = $trigger.data('overlay');
      if (api) {
        if (api.isOpened()) {
          // overlay already open, just refresh content
          api.data = $.extend({}, api.data, {href: href});
          _loadContent(api, href);
        } else {
          // overlay already initialized, but was closed
          api.data = $.extend({}, api.data, {href: href, hrefOnClose: previousHref}); // update data with previousHref (for close)
          api.load();          
        }
      } else {
        // overlay never opened yet
        // @TODO .. this is a lot of work to get jQuery Tools' overlay to only deal with one overlay instance
        $trigger.overlay({
          mask: {color: '#000', opacity: 0.8, loadSpeed: 'fast'},
  //            effect: 'apple',
          target: '#gazprom-search-overlay',
          close: '#gazprom-search-overlay .overlay-close',
          load: true,
          top: 0,
          onBeforeLoad: function(event) {
            if (!this.data) {
              this.data = {href: href, hrefOnClose: previousHref};
            }
            _loadContent(this, this.data.href);
            // we go through all this crap because this onBeforeLoad function ends up scoped inside the
            // first instance of overlay creation .. which still has the original href!
            return;
          },
          onLoad: function(event) {
            this.getTrigger().addClass('overlay-open');
          },
          onClose: function(event) {
            var $trigger = this.getTrigger();
            var $overlay = this.getOverlay();
            var $wrap = $overlay.find('.overlay-wrapper');

            var $scrollingArea = $('#gazprom-search-overlay > .overlay-wrapper');
            $scrollingArea.unbind('mousewheel');
            
            var jspAPI = $wrap.find('.main-section').data('jsp');
            if (jspAPI) {
              jspAPI.destroy();
            }
            
            $('#gazprom-search-overlay .overlay-wrapper').empty(); // must do this so the id is
            // .. gone from the document. Can't seem to use $wrap. Maybe it's a clone? data within the $anchor?


            if ($trigger.hasClass('overlay-open')) {
              this.getTrigger().removeClass('overlay-open');
              if (Drupal.gazprom.hijaxSettings.initialized == true) {
                $.hijax_addState(this.data.hrefOnClose);
              }
            }
          }
          
        });
        
      }

    }


})();
