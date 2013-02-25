/**
 * gazprom Javascript core
 * 
 * Author: jon@system-werks.com
 * Feb 2012 through Nov 2012
 * You do not have permission to use this code.
 *
 **/

(function($, Drupal) {
Drupal.behaviors.gazprom = {
    attach: function (context, settings) {

      var $context = $(context);
      if (Drupal.settings.gazprom.simpleMode == 'true') return;
      $('body.simple').removeClass('simple');
      $('html.no-js').removeClass('no-js');

      // various criteria could put us into singlePageMode, including ?singlePageMode=true in the URL
      if (Drupal.gazprom.singlePageMode === null) {
        Drupal.gazprom.utility.adjustMode();
        Drupal.gazprom.singlePageMode = Drupal.gazprom.utility.singlePageModeTest();
      }
      
      var $room;
      if ($context.is('.content-room-wrapper')) {
        $room = $context;
      } else {
        $room = $context.find('.content-room-wrapper:first');
      }
      if ($room.length == 0 || $context.is('.overlay-wrapper, .content-overlay-wrapper')) {
        // overlay content (@TODO should we really be calling init.room on overlays too?)

        $context.find('div.inline-content-cycler').inlineContentCycler();
        Drupal.gazprom.init.anchorHandlers($context);

      } else {
        // initialize the room provided in this context
        // (if this is the first call to this function, then this will be the first page/room loaded by the URL)
        Drupal.gazprom.init.room($room);
      }
      

      // initialize and build the rest of the site
      if (!$('body').hasClass('gazprom-initialized')) {
        $('body').addClass('gazprom-initialized');
        Drupal.gazprom.init.site();
        
        // A 20 second timeout to make sure initialization hasn't failed
        setTimeout(function(){
          if (!Drupal.gazprom.initialized) {
            var msg = 'Something has gone wrong and the main Javascript program has not executed. Please refresh your browser.';
            alert(msg);
          }
        }, 20000);
      }
      return;
    }
  };
  
})(jQuery, Drupal);

(function($, Drupal){
  
  Drupal.gazprom = {
    initialized: false,
    scrollIsActive: false, // this gets changed when scrolling is happening via scrollToRoom/scrollToFloor
    minRoomHeight: 920,
    minRoomWidth: 980,
    shortRoom: 780,
    scrollSpeed: 1250, // 1500
    scrollCatchUpSpeed: 150,
    scrollEasing: 'easeInOutSine',
    singlePageMode: null,
    winWidth: $(window).width(),
    winHeight: $(window).height(),
    useInnerShiv: false,
    mode: 'medium',
    settings: {
      'light': {
        preloadFloors: false,
        preloadRooms: false,
        keepFloors: false,
        keepRooms: false,
        parallax: false
      },
      'medium': {
        preloadFloors: false,
        preloadRooms: false,
        keepFloors: true,
        keepRooms: true,
        parallax: true
      },
      'heavy': {
        preloadFloors: true,
        preloadRooms: false,
        keepFloors: true,
        keepRooms: true,
        parallax: true
      },
      'extra-heavy': {
        preloadFloors: true,
        preloadRooms: true,
        keepFloors: true,
        keepRooms: true,
        parallax: true
      }
    },
    initialHref: '',
    lastDOMhref: '',
    activeRoom: $([]),
    activeFloor: $([]),
    openPathAttempts: {path: '', count: 0},
    openPath: function(href, data) {
      /**
       * Primary handler for path (URL / href) changes
       * Typically called by the onStateChange function passed
       * into the hijax plugin
       **/
      
      //console.log('openPath:', href, data);
      var data = (data ? data : {});
      var id = this.utility.urlToId(href);
      var $room = $('#' + id);
      if ($room.length == 1) {
        // content is alread loaded, so scroll to it
         this.openInDOM($room, data);
         this.openPathAttempts = {path: '', count: 0};
      } else {
        // content needs to be loaded and then handled accordingly
        if (this.openPathAttempts.path != href) {
          this.openPathAttempts = {path: href, count: 0};
        }
        if (this.openPathAttempts.count++ > 2) {
          //console.log('Error. Could not load ' + href + ' after 3 attempts');
          Drupal.gazprom.utility.clearBusy();
          this.openPathAttempts = {path: '', count: 0};
          return;
        }
        this.loadContent(href, {
          selector: '.content-floor-wrapper:first, #navigation-main, h1.head-title',
          callback: function($content, href, options) {
            Drupal.gazprom.insertContent($content, href, data);
          }
        })
      }
      
      return;
      
    }, 
    openInDOM: function($room, options) {
      var $overlayOpened = $('.overlay-open');
      if ($overlayOpened.length > 0 ) {
        $overlayOpened.removeClass('overlay-open'); // somewhat of a hack: this signals the overlay's onClose function to NOT go back in History
        $overlayOpened.overlay().close();
      }

      // record this current URL as last used for this room .. @TODO, huh?
      $room.data('urlAtLastScroll', window.location.pathname + window.location.search);

      // jump to it
      this.activateRoom($room, options);
      
      // Incase something went wrong earlier:
      Drupal.gazprom.utility.clearBusy();

    },
    openInOverlay: function($content, options) {
      var $trigger = $('#gazprom-overlay-trigger');
      //if (this.closeOtherOverlay($trigger, href) == true) return;
      this.closeOtherOverlay($trigger);
      
      var State = $.hijax_getState();
      var previousHref;
      if (typeof State.data.previousHref != 'undefined' && State.data.previousHref != Drupal.gazprom.currentURL(State)) {
        previousHref = State.data.previousHref;
      } else if (this.lastDOMhref && this.lastDOMhref != Drupal.gazprom.currentURL(State)) {
        previousHref = this.lastDOMhref;
      } else {
        previousHref = Drupal.settings.basePath + Drupal.settings.pathPrefix;
      }
      
      this.deactivateRoom();
      
      var api = $trigger.data('overlay');
      if (api) {
        if (api.isOpened()) {
          // overlay already open, just refresh content
          api.content = $content;
          _updateContent(api);
        } else {
          // overlay already initialized, but was closed
          api.data = $.extend({}, api.data, {hrefOnClose: previousHref}); // update data with previousHref (for close)
          api.content = $content; // Is this okay to do? Memory issues?
          api.load();          
        }
      } else {
        // overlay never opened yet
        $trigger.overlay({
          mask: {color: '#000', opacity: 0.8, loadSpeed: 'fast', zIndex: 9000, closeOnClick: false, closeOnEsc: false},
          target: '#gazprom-overlay',
          closeOnClick: false,
          closeOnEsc: true,
          close: '#gazprom-overlay .overlay-close',
          oneInstance: false,
          load: true,
          top: 0,
          onBeforeLoad: function(event) {
            if (!this.data) {
              this.data = {hrefOnClose: previousHref};
            }
            if (!this.content) {
              this.content = $content;
            }
            //_loadContent(this, this.data.href);
            // we go through all this crap because this onBeforeLoad function ends up scoped inside the
            // first instance of overlay creation .. which still has the original href!
            var $overlay = this.getOverlay();

            $overlay.css('z-index', '9001');
//            $overlay.expose({color: '#000', opacity: 0.8, loadSpeed: 'fast', zIndex: 9000, closeOnClick: false, closeOnEsc: false});
          },
          onLoad: function(event) {
            this.getTrigger().addClass('overlay-open');
            _updateContent(this);
          },
          onClose: function(event) {
            var $trigger = this.getTrigger();
            var $overlay = this.getOverlay();
            var $wrap = $overlay.find('.overlay-wrapper');

            var jspAPI = $wrap.find('.main-section').data('jsp');
            if (jspAPI) {
              jspAPI.destroy();
            }
            
            $('#gazprom-overlay .overlay-wrapper').empty(); // must do this so the id is gone from document.

            if ($trigger.hasClass('overlay-open')) {
              $trigger.removeClass('overlay-open');
              Drupal.gazprom.gotoHref(this.data.hrefOnClose);
//              $.mask.close();
            }
          }
          
        });
        
      }
      
      function _updateContent(api) {
        var $trigger = api.getTrigger();
        var $overlay = api.getOverlay();
        var $wrap = $overlay.find('.overlay-wrapper');
        
        var $content = api.content;
        
        $wrap.empty().append($content); //.fadeOut(0);
        
        // Remove some attributes designed for regular DOM viewing of content
        $content.removeClass('content-room-wrapper').addClass('content-overlay-wrapper');
        $content.find('.full-height').removeClass('full-height');
        $content.find('.step-width').removeClass('step-width');

        // attach close handler.
        $content.append('<a class="overlay-close close"></a>');
        $wrap.find('.overlay-close').unbind('click').bind('click.contentOverlay',function() {
          if (api) api.close();
        });

        // Customize overlay depending on content types.
        $overlay.removeClass('video text search'); // clear old content's settings.
        if ($content.find('.open-in-video-overlay').length > 0) {
          $overlay.addClass('video');
        } else if ($content.find('.search-results').length > 0) {
          $overlay.addClass('search text');
          $content.append('<a class="overlay-tool overlay-print print"></a>');
        } else if ($content.find('.open-in-photo-overlay ').length > 0) {
          $overlay.addClass('photo');
        } else {
          $overlay.addClass('text')
          $content.append('<a class="overlay-tool overlay-print print"></a>');
        }
        
        // attach jScrollPane to the content
        if (!$('html').is('.touch') && $overlay.is('.text')) {
          $wrap.find('.main-section').jScrollPane({
            animateScroll: true,
            hideFocus: true,
            autoReinitialise: true
          });
        }
        
        Drupal.gazprom.init.printTools($wrap);
        Drupal.gazprom.init.shareTools($wrap);
        Drupal.attachBehaviors($content, {stage2: 'immediate'});

        Drupal.gazprom.utility.clearBusy();
        //$wrap.fadeIn(200);

        // update window title
        var headTitle = Drupal.gazprom.utility.getRoomTitle($content);
        if (headTitle) document.title = headTitle;

      }
    },
    openInPhotoOverlay: function($content, options) {
      var $trigger = $('#photo-overlay-trigger');
      //if (this.closeOtherOverlay($trigger, href) == true) return;
      this.closeOtherOverlay($trigger);
      
      var State = $.hijax_getState();
      var previousHref;
      if (typeof State.data.previousHref != 'undefined' && State.data.previousHref != Drupal.gazprom.currentURL(State)) {
        previousHref = State.data.previousHref;
      } else if (this.lastDOMhref) {
        previousHref = this.lastDOMhref;
      } else {
        previousHref = Drupal.settings.basePath + Drupal.settings.pathPrefix;
      }
      
      this.deactivateRoom();
      
      var api = $trigger.data('overlay');
      if (api) {
        if (api.isOpened()) {
          // overlay already open, just refresh content
          api.content = $content;
          _updateContent(api);
        } else {
          // overlay already initialized, but was closed
          api.data = $.extend({}, api.data, {hrefOnClose: previousHref}); // update data with previousHref (for close)
          api.content = $content; // Is this okay to do? Memory issues?
          api.load();          
        }
      } else {
        // overlay never opened yet
        $trigger.overlay({
          target: '#photo-overlay',
          close: '#photo-overlay .overlay-close',
          oneInstance: false,
          load: true,
          top: 0,
          onBeforeLoad: function(event) {
            $('#header, nav.second-navigation, #footer-page').addClass('full-width');

            if (!this.data) {
              this.data = {hrefOnClose: previousHref};
            }
            if (!this.content) {
              this.content = $content;
            }
            //_loadContent(this, this.data.href);
            // we go through all this crap because this onBeforeLoad function ends up scoped inside the
            // first instance of overlay creation .. which still has the original href!
            return;
          },
          onLoad: function(event) {
            this.getTrigger().addClass('overlay-open');
            _updateContent(this);
          },
          onClose: function(event) {
            var
              $trigger = this.getTrigger(),
              $overlay = this.getOverlay(),
              $wrap = $overlay.find('.overlay-wrapper');

            Drupal.gazprom.viewPhoto.close();
            
            $('#header, nav.second-navigation, #footer-page').removeClass('full-width');

            var jspAPI = $wrap.find('.main-section').data('jsp');
            if (jspAPI) {
              jspAPI.destroy();
            }
            
            $('#photo-overlay .overlay-wrapper').empty(); // must do this so the id is gone from document.

            if ($trigger.hasClass('overlay-open')) {
              $trigger.removeClass('overlay-open');
              Drupal.gazprom.gotoHref(this.data.hrefOnClose);
            }
          }
          
        });
        
      }
      
      function _updateContent(api) {
        var $trigger = api.getTrigger();
        var $overlay = api.getOverlay();
        var $wrap = $overlay.find('.overlay-wrapper');
        
        var $content = api.content;
        
        $wrap.empty().append($content); //.fadeOut(0);
        
        // Remove some attributes designed for regular DOM viewing of content
        $content.removeClass('content-room-wrapper').addClass('content-overlay-wrapper');
        $content.find('.full-height').removeClass('full-height');
        $content.find('.step-width').removeClass('step-width');

        // attach close handler.
        $content.append('<a class="overlay-close close"></a>');
        $wrap.find('.overlay-close').unbind('click').bind('click.contentOverlay',function() {
          if (api) api.close();
        });

        // Customize overlay depending on content types.
        $overlay.removeClass('video text search'); // clear old content's settings.
        if ($content.find('.open-in-video-overlay').length > 0) {
          $overlay.addClass('video');
        } else if ($content.find('.search-results').length > 0) {
          $overlay.addClass('search text');
          $content.append('<a class="overlay-tool overlay-print print"></a>');
        } else if ($content.find('.open-in-photo-overlay ').length > 0) {
          $overlay.addClass('photo');
        } else {
          $overlay.addClass('text')
          $content.append('<a class="overlay-tool overlay-print print"></a>');
        }
        
//        // attach jScrollPane to the content
//        if (!$('html').is('.touch') && $overlay.is('.text')) {
//          $wrap.find('.main-section').jScrollPane({
//            animateScroll: true,
//            hideFocus: true,
//            autoReinitialise: true
//          });
//        }
        
        Drupal.gazprom.init.printTools($wrap);
        Drupal.gazprom.init.shareTools($wrap);
        Drupal.attachBehaviors($content, {stage2: 'immediate'});

        // modify content & attach photoViewer controls
        Drupal.gazprom.viewPhoto.view($wrap, $trigger.data('overlay'));

        Drupal.gazprom.utility.clearBusy();
        //$wrap.fadeIn(200);

        // update window title
        var headTitle = Drupal.gazprom.utility.getRoomTitle($content);
        if (headTitle) document.title = headTitle;

      }
    },
    closeOtherOverlay: function($goodTrigger) {
      var $overlayOpened = $('.overlay-open').not($goodTrigger);
      if ($overlayOpened.length > 0 ) {
        $overlayOpened.each(function(){
          var api = $(this).overlay();
          if (typeof api != 'undefined') {
            api.getTrigger().removeClass('overlay-open'); // This needs to be done so the overlay doesn't try to get to it's hrefOnClose
            api.close();
          }
        });
        return true;
      } else {
        return false;
      }
    },
    gotoRoom: function($room, options) {
      // slide to a room.
      // example of option: {skipScroll: true}
      if ($($room).length == 0) return; // something went wrong
//      var destinationData = Drupal.gazprom.utility.findDirectoryEntry($room.attr('id'));
//      if (destinationData) {
//        Drupal.gazprom.gotoHref(destinationData.href, options); // newWindowTitle?
//      }
      var href = $room.data('href');
      if (href) {
        Drupal.gazprom.gotoHref(href, options);
      }
    },
    gotoHref: function(href, data, force) {
      /* we have an href/url, and maybe some options data, handle it as
       * .. if it was a click
       **/
      if (Drupal.gazprom.hijax.initialized == true) {
        //$.hijax_addState(href, data, force);
        $.hijax_addState(href, {}, force);
        // href and data end up being passed to Drupal.gazprom.hijax.onStatechange()
      } else if (data) {
        Drupal.gazprom.openPath(href, data);
      }
    },
    activateRoom: function($room, options) {
      /**
       * Handle everything related to activating a room. The room could
       * be activated by various methods. Various things might have to happen
       * to make the room fully active.
       **/
      if ($room.is('.active-room')) return;

      // Make sure we track this HREF so that overlays can goto it when they close
      Drupal.gazprom.lastDOMhref = Drupal.gazprom.currentURL();

      var path;
      if ($room.find('.open-in-overlay').length > 0 
        || $room.find('.open-in-video-overlay').length > 0
        || $room.find('.open-in-photo-overlay').length > 0) {
        path = $room.find('article').attr('about');
        if (path) {
          $room.remove();
          Drupal.gazprom.openPath(path);
          return;
        }
      }
      
      var settings = $.extend({
        skipScroll: false
      }, options);
      
      var $floor = $room.closest('.content-floor-wrapper');

      // if there is another room already activated, deactivate it
      _deactivateOld();
      
      // update the nav-main anchor to point to this room's href
      var $mainNavAnchor = $room.data('nav-main-anchor');
      if ($mainNavAnchor && $room.data('href')) {
        $mainNavAnchor.attr('href', $room.data('href'));
      }

      // make sure all anchors referencing this room are set to active.
      // This includes the $mainNavAnchor that we just updated above.
      var href = ($room.data('href') ? $room.data('href') : Drupal.gazprom.currentURL());
      var $anchors = $('a[href$="' + href + '"]'); // @TODO bad to find all relevetant anchors? above code didn't find home page link
      $anchors.each(function() {
        Drupal.gazprom.utility.activeAnchor($(this), options);
      });
      Drupal.gazprom.utility.activeAnchor($room.data('nav-second-anchor'), options)
      Drupal.gazprom.utility.activeAnchor($room.data('nav-main-anchor'), options)
            
      _activateRoom()
      
      function _activateRoom() {
        /**
         * Activate the room
         **/
        
        // update window title
        var headTitle = Drupal.gazprom.utility.getRoomTitle($room);
        document.title = headTitle;
        
        if (!settings.skipScroll) {
          var scrollOptions = {callback: _activateRoom_finish};
          if (typeof settings.duration != 'undefined') {
            $.extend(scrollOptions, {duration: settings.duration});
          }
          Drupal.gazprom.utility.scrollToRoom($room, scrollOptions);
        } else {
          _activateRoom_finish();
        }
      }
      
      function _activateRoom_finish() {
        _deactivateOld(); // note: this needs to be done twice if user is clicking rapidly on many navigation links
        $room.addClass('active-room activated').removeClass('previously-active');
        Drupal.gazprom.activeRoom = $room;
        if (Drupal.gazprom.activeFloor.length == 0) {
          Drupal.gazprom.activeFloor = $room.closest('.content-floor-wrapper');
          Drupal.gazprom.activeFloor.addClass('active-floor');
        }
        $room.trigger('room-activation');

        if (!$floor.hasClass('active-floor')) {
          // deactivate old floor
          //var $oldFloor = $('.content-floor-wrapper.active-floor');
          var $oldFloor = Drupal.gazprom.activeFloor;
          $floor.addClass('active-floor activated');
          Drupal.gazprom.activeFloor = $floor;
          if ($oldFloor.length > 0) {
            $oldFloor.removeClass('active-floor activated');
            // @TODO trigger floor-deactivated event? unlock $oldFloor's second-navigation?
            if (!Drupal.gazprom.settings[Drupal.gazprom.mode].keepFloors && $('.content-floor-wrapper').length > 1) {
              // strip old floor out of DOM
              $oldFloor.replaceWith('<div class="content-floor-wrapper placeholder">');
              Drupal.gazprom.scroll.sync();
            } else if ($oldFloor.is('.error-floor')) {
              $oldFloor.remove();
            }
          }
          $floor.trigger('floor-activation');
          
        } else {
          if (!Drupal.gazprom.settings[Drupal.gazprom.mode].keepRooms) {
            // strip old room out of DOM
            $floor.find('.content-room-wrapper.previously-active').replaceWith('<div class="content-room-wrapper placeholder">');
            Drupal.gazprom.scroll.sync($floor, {horzOnly: true});
          }
        }
        
        // Incase something went wrong earlier, make sure the correct second-level navigation is stuck.
        // .. Also unsticks an old second-level navigation when we activate home page. This is mainly here
        // .. because of bugs, possibly browser bugs, related to waypoints.
        var $currentStuck = $('nav.second-navigation.stuck');
        if (!$currentStuck.closest('.content-floor-wrapper').is('.active-floor')) {
          Drupal.gazprom.utility.toggleNavSticky($currentStuck, 'unsticky');
        }
        Drupal.gazprom.utility.toggleNavSticky($floor.find('nav.second-navigation'), 'sticky');
        
        // @TODO EXPERIMENTAL:
        // change the floor's referencing anchor to now point to this room
//        var destination = Drupal.gazprom.utility.findDirectoryEntry($room.attr('id'));
//        var $referencingMainNavAnchor = $floor.data('referencingAnchor'); // @TODO is this weak?
//        if ($referencingMainNavAnchor != undefined && destination != undefined) {
//          $referencingMainNavAnchor.attr('href', destination.href);
//          // @TODO anchor title attribute?
//        }


        if (typeof settings.callback == 'function') settings.callback.call();
        
        Drupal.gazprom.utility.clearBusy();
      }

      function _deactivateOld() {
        // if there is another room already activated, deactivate it
        //var $oldRoom = $('.content-room-wrapper.active-room');
        var $oldRoom = Drupal.gazprom.activeRoom;
        if ($oldRoom.length > 0) {
          Drupal.gazprom.deactivateRoom($oldRoom);
        }
      }
      
    }, 
    deactivateRoom: function($room) {
      if (typeof $room == 'undefined') {
        //$room = $('.content-room-wrapper.active-room');
        $room = Drupal.gazprom.activeRoom;
      }
      if ($room.is('.active-room')) {
        $room.trigger('room-deactivation');
        $room.closest('.content-floor-wrapper').find('.content-room-wrapper.previously-active').removeClass('previously-active');
        $room.removeClass('active-room activated').addClass('previously-active');
        Drupal.gazprom.activeRoom = $([]);
      }
    }, 
    windowResizeInit: function() {
      Drupal.gazprom.winWidth = $(window).width();
      Drupal.gazprom.winHeight = $(window).height();
      $(window).resize( $.debounce(100, Drupal.gazprom.windowResizeEvent));
      $(window).resize( $.debounce(150, Drupal.gazprom.windowResizeScroll));
    },
    windowResizeEvent: function() {
      /**
       * Called via $.debounce when window is resized.
       * Triggers custom event to tell items to resize themselves
       **/
      //console.log('window resize');
      
      // if stage is inside the absolute positioned bottom content pane, make sure
      // it is big enough. There is CSS to allow it to climb to the top of the page as well (escape various containers)
      // @TODO rethink this? is stage even needed inside a "basic page" node type anymore now that we have page_code node type?
      $('.constant-bottom .stage').css({
        height: $(window).height() - $('#footer-page').height(),
        bottom: null
      }); // @TODO should this be bound to the event somewhere else?
      
      Drupal.gazprom.winWidth = $(window).width();
      Drupal.gazprom.winHeight = $(window).height();

      $(window).trigger('resizeComplete'); // let other handlers update their elements (i.e. stepWidth(), sizeRoom(), scrollingList, fluidCenterAlign)
    },
    windowResizeScroll: function() {
      /**
       * Called via $.debounce when window is resized
       * Causes current room to scroll back into view
       **/
      //console.log('window scroll reset');
      //Drupal.gazprom.utility.scrollToRoom($('.content-room-wrapper.active-room'), {duration:25})
      Drupal.gazprom.utility.scrollToRoom(Drupal.gazprom.activeRoom, {duration:25})
    },
    shareThis: function(service) {
      var State = $.hijax_getState();
      var url = State.cleanUrl;
      var title = window.document.title; // @TODO shouldn't title be sent into the State?
      
      // split off query parameters
      url = url.split('?',1)[0];
      var shareUrl, features;
      if (service == 'facebook') {
        shareUrl = 'http://facebook.com/sharer.php?u=' + encodeURIComponent(url) + '&t=' + encodeURIComponent(title);
        features = 'width=660,height=512';
      } else if (service == 'twitter') {
        shareUrl = 'http://twitter.com/share?url=' + encodeURIComponent(url);
        features = 'width=750,height=250';
      } else if (service == 'google') {
        shareUrl = 'https://plusone.google.com/_/+1/confirm?url=' + encodeURIComponent(url) + '&title=' + encodeURIComponent(title);
        features = 'width=550,height=420';
      } else if (service == 'livejournal') {
        (function(){
          var u='http://www.livejournal.com/',w=window.open('','','toolbar=0,resizable=1,scrollbars=1,status=1,width=730,height=500');
          if(window.LJ_bookmarklet){
            return LJ_bookmarklet(w,u)
          };
          var e=document.createElement('script');
          e.setAttribute('type','text/javascript');
          e.onload=function(){
            LJ_bookmarklet(w,u)
          };
          e.setAttribute('src',u+'js/bookmarklet.js');
          document.getElementsByTagName('head').item(0).appendChild(e)
        })();
        // code retrieved from http://www.livejournal.com/bookmarklet.bml .. does it have issues?
        return;
      }
      
      features = features + ',menubar=yes,toolbar=yes,location=yes,scrollbars=yes';
      window.open(shareUrl, 'share', features);
    },
    loadContent: function(href, options) {
      /* AJAX load content */

      var settings = $.extend({
        selector: null,
        setBusy: true,
        callback: null
      }, options);

      if (settings.setBusy) {
        Drupal.gazprom.utility.setBusy(); // will be cleared by activateRoom
      }
      $.get(href, function(data) {
        var $newContent;
        if ($('html').is('.ie8, .ie7, .ie6') && Drupal.gazprom.useInnerShiv) {
          $newContent = $(innerShiv($(data).outerHTML()));
        } else {
          $newContent = $(data);
        }
        if (settings.selector) {
          $newContent = $newContent.find(settings.selector);
        }

        if (typeof settings.callback == 'function') {
          settings.callback.call(this, $newContent, href, options);
          return null;
        } else {
          return $newContent;
        }
      });

    },
    insertContent: function($content, href, options) {
      /* Typically called after loadContent() and used
       * to insert the content in the correct place.
       */
     
      var $contentNavMain = $content.filter('#navigation-main');
      $content = $content.not('#navigation-main');
      var $contentNavSecond = $content.find('.second-navigation');
      
      var type = 'unknown';
      if ($content.find('.open-in-overlay, .open-in-video-overlay').length > 0) {
        _insertOverlay();
      } else if ($content.find('.open-in-photo-overlay ').length > 0) {
        _insertPhotoOverlay();
      } else if ($content.find('.open-within-room').length > 0) {
        _insertWithinRoom();
      } else {
        _insertDOM(options);
      }

      /**
       * Insert $content into DOM as a floor or room
       **/
      function _insertDOM(options) {
        var 
          //$activeFloor = $('.content-floor-wrapper.active-floor'),
          $activeFloor = Drupal.gazprom.activeFloor,
          //$activeRoom = $activeFloor.find('.active-room'),
          $activeRoom = Drupal.gazprom.activeRoom,
          roomError = false,
          newFloorPos,
          newRoomPos;
        var settings = $.extend({}, {
          interiorReplacement: false,
          insertOnly: false,
          stage2initMode: 'immediate'
        }, options)
        

        // If this DOM (building) is new, pad it with placeholders for each floor.
        _padDOMwithFloors();

        // Determine position of new content relative to current content.
        var $newNavItem = $contentNavMain.find('ul.menu li a.active-trail');
        newFloorPos = $contentNavMain.find('ul.menu li a').index($newNavItem);
        if (newFloorPos < 0) {
          if ($content.is('.front-page')) {
            // Home page would not be found as active link in $contentNavMain as active, so 
            // .. it would return -1. It's actually belongs in floor position 0 (first).
            newFloorPos = 0;
          } else {
            // Something went wrong. This content has no identifiable position and is not the front page,
            // .. so just append it to the end and wish it well.
            var $errorFloor = $('.content-floor-wrapper.floor-error');
            if (true || $errorFloor.length == 0) {
              // (as of right now, we are creating a new floor for each error situation. Ran into problems
              //  .. with scrolling and putting them all on the same floor.)
              $('.content-floor-wrapper:last').after('<div class="content-floor-wrapper placeholder floor-error"></div>');
            }
            newFloorPos = $('.content-floor-wrapper').length - 1;
            roomError = true;
          }
        } else {
          newFloorPos++;
          // 0 would be return for 1st Main Nav position, so increase by 1 to accomodate the home page
        }
        

        var $destinationFloor = $('.content-floor-wrapper:eq(' + newFloorPos + ')'),
          $destinationNavItem;
        if (newFloorPos == 0) {
          $destinationNavItem = $('#go-home');
        } else {
          $destinationNavItem = $('#navigation-main ul.menu li a:eq(' + (newFloorPos - 1) + ')');
        }

        if ($destinationFloor.find('.content-room-wrapper').length == 0) {
          // This $content goes into a brand new floor (empty).
          $destinationFloor.replaceWith($content);
          // Now we only need the room contained within the $content.
          $content = $content.find('.content-room-wrapper');
          $content.sizeRoom();
          Drupal.gazprom.scroll.sync();
          _finish();
        } else {
          // This floor for this $content already has rooms. It could also be the floor we are already on.
          $content = $content.find('.content-room-wrapper');

          // But make sure there are placeholders for all rooms we expect on this floor.
          _padFloorWithRooms($destinationFloor);

          // The second nav that came with the $content will tell us what room position the
          // .. content should fill up.
          $newNavItem = $contentNavSecond.find('ul.menu li a.active-trail');
          newRoomPos = $contentNavSecond.find('ul.menu li a').index($newNavItem);
          if (newRoomPos == -1) {
            // Technically something went wrong here. This is a room being pushing into a floor
            // .. that already has a room, but should only have one (no second nav). But we want to handle this
            // .. as gracefully as possible -> Append it to the floor.
            newRoomPos = $destinationFloor.find('.content-room-wrapper').length;
            $destinationFloor.append('<div class="content-room-wrapper placeholder room-error"></div>');
            roomError = true;
          }

          var $replaceRoom = $destinationFloor.find('.content-room-wrapper:eq(' + newRoomPos + ')');
          var insertIntoExisting = settings.interiorReplacement
            && ($replaceRoom.find('.content.constant-bottom').length > 0)
            && ($content.find('.content.constant-bottom').length > 0);
          if (!$replaceRoom.is('.placeholder') && $replaceRoom.is('.active-room') && insertIntoExisting && !($('html').is('.ie7, .ie8'))) {
            var $interiorArea = $replaceRoom.find('.bottom-content');
            $content.find('.bottom-content').animate({opacity:0}, 0).addClass('fadeIn');
            $interiorArea.animate({
              opacity: 0
            }, {
              duration: 100,
              complete: function() {
                $interiorArea.replaceWith($content.find('.bottom-content'));
                _finishRoom();
              }
            });
            //$replaceRoom.find('.content.constant-bottom').replaceWith($content.find('.content.constant-bottom'));
          } else if (!$replaceRoom.is('.placeholder') && insertIntoExisting) {
            $replaceRoom.find('.content.constant-bottom').replaceWith($content.find('.content.constant-bottom'));
            _finishRoom();
          } else {
            $replaceRoom.replaceWith($content);
            _finishRoom();
          }

        }
        
        function _finishRoom() {
          if (insertIntoExisting) {
            $replaceRoom.attr('id', $content.attr('id')).removeClass('initialized active-room');
            $replaceRoom.find('h1.head-title').replaceWith($content.find('h1.head-title'));
            $content = $replaceRoom;
          } else {
            $content.sizeRoom(); // necessary here so the horz part of .scroll.sync() will work.
            Drupal.gazprom.scroll.sync($destinationFloor, {horzOnly: true});
          }
          $content.data('nav-second-anchor', $destinationFloor.find('.second-navigation ul.menu li a:eq(' + newRoomPos + ')'))
          
          _finish();
        }
        
        function _finish() {
          // Tag error pages correctly (pages/rooms that are not correctly positioned in DOM)
          if (roomError) {
            $content.addClass('room-error');
            $content.closest('.content-floor-wrapper').addClass('floor-error');
          }

          // link up the inserted room to the appropriate anchor in the main navigation.
          $content.data('nav-main-anchor', $destinationNavItem);
          $content.data('href', href);


          Drupal.attachBehaviors($content, {stage2: settings.stage2initMode});
          if (!settings.insertOnly) {
            $.doTimeout(10, function() {
              // Make sure everything in DOM catches up.
              Drupal.gazprom.openPath(href, options);
            });
          }
        }

        function _padDOMwithFloors() {
          // This function only executes fully once. The assumption is there is always
          // .. one floor loaded with the intial request. Then this function is called
          // .. and we put placeholder floors in for the missing floors. The correct
          // .. number of placeholder floors has to be put before and after the currently
          // .. loaded floor.
          var numNeeded = $('#navigation-main ul.menu li a').length + 1;
          var numPresent = $('.content-floor-wrapper:not(.error-floor)').length;
          if (numPresent >= numNeeded) return;
          
          //var $currentFloor = $('.content-floor-wrapper.active-floor');
          var $currentFloor = Drupal.gazprom.activeFloor;
          if ($currentFloor.length == 0) $currentFloor = $('.content-floor-wrapper.active-floor');
          if ($currentFloor.length == 0) $currentFloor = $('.content-floor-wrapper:first');
          var $currentMainNavItem = $('#navigation-main ul.menu li a.active-trail');
          var currentFloorPos = $('#navigation-main ul.menu li a').index($currentMainNavItem) + 1;

          var numBefore = currentFloorPos;
          var numAfter = numNeeded - currentFloorPos - 1;
          if ($currentFloor.is('.error-floor')) {
            numBefore = numNeeded;
            numAfter = 0;
          }

          for (i = 0; i < numBefore; i++) {
            $currentFloor.before('<div class="content-floor-wrapper placeholder">');
          }
          for (i = 0; i < numAfter; i++) {
            $currentFloor.after('<div class="content-floor-wrapper placeholder">');
          }
        }
        function _padFloorWithRooms($floor) {
          // This function only executes fully once for each floor that gets a new
          // .. room added to it. Placeholder rooms are inserted for ths new room
          // .. and the rooms that will be loaded another day. The assumption is
          // .. one room has already been put into this floor. Either by a full floor
          // .. insertion in parent function, or by initial request to server.
          var numNeeded = $floor.find('nav.second-navigation ul.menu li a').length;
          var numPresent = $floor.find('.content-room-wrapper').length;
          if (numPresent >= numNeeded) return;

          var $currentRoom = $floor.find('.content-room-wrapper:first');
          var $currentSecondNavItem = $floor.find('nav.second-navigation ul.menu li a.active-trail');
          var currentRoomPos = $floor.find('nav.second-navigation ul.menu li a').index($currentSecondNavItem);

          var numBefore = currentRoomPos;
          var numAfter = numNeeded - currentRoomPos - 1;

          for (i = 0; i < numBefore; i++) {
            $currentRoom.before('<div class="content-room-wrapper placeholder">');
          }
          for (i = 0; i < numAfter; i++) {
            $currentRoom.after('<div class="content-room-wrapper placeholder">');
          }
        }
      }
      
      /**
       * Send $content into an overlay
       **/
      function _insertOverlay() {
        $content = $content.find('.content-wrapper:first');
        Drupal.gazprom.openInOverlay($content);
      }

      /**
       * Send $content into a photo overlay.
       **/
      // @TODO combine with regular overlay
      function _insertPhotoOverlay() {
        $content = $content.find('.content-main:first');
        Drupal.gazprom.openInPhotoOverlay($content);
      }

      /**
       * Replace a room with the $content
       **/
      function _insertWithinRoom() {
        // Locate the room this content goes into by using the navigation links provided.
        var
          $newNavMainItem = $contentNavMain.find('ul.menu li a.active-trail'),
          mainNavPosition = $contentNavMain.find('ul.menu li a').index($newNavMainItem),
          $newNavSecondItem = $contentNavSecond.find('ul.menu li a.active-trail'),
          secondNavPosition = $contentNavSecond.find('ul.menu li a').index($newNavSecondItem);
          
        if (mainNavPosition < 0 || secondNavPosition < 0) {
          // Without active-trail nav items in the incoming content, we cannot figure out
          // .. which room this content goes into. So let _insertDOM() handle it as an error room.
          _insertDOM();
        } else {
          _insertDOM({interiorReplacement: true});
        }
      }

    }
    
  };
})(jQuery, Drupal);

(function($, Drupal) {
  Drupal.gazprom.photoGallery = function($room) {

    // @TODO this really needs to be broken out into its own area. Maybe custom module JS code?
    if (($room.find('.stage .view-photo-grid').length == 0) && ($room.find('.stage .view-photo-list').length == 0)) return;
    
    var $stage = $room.find('.stage:first');
    var $gallery = $stage.find('.photo-gallery-content');
    var $controls = $stage.find('.photo-gallery-controls');
    var $filterDialog = $stage.find('.gallery-filter-dialog');
    var $searchDialog = $stage.find('.gallery-search-dialog');
    var stageWidth = $stage.width();
    var stageHeight = $stage.height();

    // remove sideways room navigators
    $room.addClass('no-room-navigation');
    //$room.find('.room-navigator').remove();
    
    // bind up gallery controls
    _bindGalleryControls();

    // bind up grid scroll handlers
    $stage.find('.grid-scroll-buttons .grid-button').bind('click', _scrollGrid);

    // bind up sort/filter controls
    $stage.find('.gallery-control-filter').unbind('click.photoGallery').bind('click.photoGallery', function(e) {
      e.preventDefault();
      _toggleFilterDialog();
    });
    
    // bind up search control
    $stage.find('.gallery-control-search').unbind('click.photoGallery').bind('click.photoGallery', function(e) {
      e.preventDefault();
      _toggleSearchDialog();
    })
    // bind up TEMPORARY handlers for search and slideshow @TODO
    $stage.find('.gallery-control-show, .XXXgallery-control-search').unbind('click.photoGallery').bind('click.photoGallery', function(e) {
      e.preventDefault();
      alert('This function is not yet available');
    })
    
    // make sure controls don't show up during build/load
   $stage.find('.photo-gallery-controls, .grid-button').hide();
    
    // hack the right edge of the overlay so that it fits within #scroller even though it is position:fixed
    $stage.find('.photo-gallery-controls, .gallery-search-dialog').css({width: 'auto', right: $.getScrollbarWidth()});
    
    var $grid, $list;
    var $table, totalPages, gridWidth, gridHeight, totalCells;
    _initializeGallery();
    
    
    function _initializeGallery() {
      $grid = $gallery.find('.view-photo-grid:first');
      $list = $gallery.find('.view-photo-list:first');
      

      $room.unbind('room-activation.photoGallery').unbind('room-deactivation.photoGallery')
      if ($grid.length == 1) {
        _initializeGrid();
      } else if ($list.length == 1) {
        _initializeList();
      }
    }
    function _initializeList() {
      // make sure grid controls are not visable
      $stage.find('.grid-button, .photo-gallery-focus-ring').fadeOut(500);

      // bind up activation/deactivation routines
      $room.unbind('room-activation.photoGallery').bind('room-activation.photoGallery', function() {
        $stage.find('.photo-gallery-controls').show().fadeOut(0).fadeIn(500);
      }).unbind('room-deactivation.photoGallery').bind('room-deactivation.photoGallery', function() {
        _filterClose(0);
        _searchClose(0);
        $stage.find('.photo-gallery-controls').fadeOut(500, function(){
          $(this).hide();
        });
      })
      if ($room.is('.active-room')) $room.trigger('room-activation.photoGallery');

      // bind viewPhoto handler to table anchors
      $list.find('.view-content tbody tr a').not('.photo-galleryprocessed')
        .bind('click', _viewPhoto)
        .addClass('gazprom-click-processed photo-gallery-processed');

      // most reliable way of doing row highlighting in a table is to use Javascript
      $list.find('.view-content tbody tr').hover(function(){
        $(this).addClass('hovered');
      }, function(){
        $(this).removeClass('hovered');
      })
      
      // hook up click event on entire row
      $list.find('.view-content tbody tr').unbind('click.photoGallery').bind('click.photoGallery', function(e){
        e.preventDefault();
        $(this).find('.view-collection-topmost a').trigger('click');
      });
      
      // manually set the height to fill in the area between the controls and the second navigation
      // (it has top margin to keep it from going under second navigation)
      // yes, this sucks.. but seemed like the best idea at the time
      $(window).unbind('resizeComplete.photoGallery').bind('resizeComplete.photoGallery', function() {
        var listHeight = $(window).height() - $('#header').height() - $('.second-navigation').height() - $stage.find('.photo-gallery-controls').height();
        listHeight = listHeight - ($('#footer-page').height() * 2); // not really sure why, but it works.
        $list.css({height: listHeight});
      }).trigger('resizeComplete.photoGallery');
      
      // don't let mousewheels escape
      $list.unbind('mousewheel.photoGallery').bind('mousewheel.photoGallery', function(e){
        e.preventDefault();
        // @TODO this needs to work! .. but contain itself to the $list only
      });
      
      
      // move Views filter & sort forms into our div container to display them
      _relocateSortFilters();

      _listInstalled();
    }
    function _initializeGrid() {
      var $firstUL = $grid.find('ul:first');
      if ($firstUL.length == 0) return; // no photos
      
      // move Views filter & sort forms into our div container to display them
      _relocateSortFilters();
      
      
      $grid.bind('mousewheel', function(e) {
        e.preventDefault();
        // @TODO is this a good idea? maybe mousewheel should scroll grid?
      });

      // bind up activation/deactivation routines
      $room.unbind('room-activation.photoGallery').bind('room-activation.photoGallery', _gridActivation)
        .unbind('room-deactivation.photoGallery').bind('room-deactivation.photoGallery', _gridDeactivation);
      if ($room.is('.active-room')) $room.trigger('room-activation.photoGallery');

      if (true || Drupal.gazprom.singlePageMode || $room.is('.active-room')) {
        _buildGrid();
      } else {
        $room.unbind('room-activation.build-photo-grid').bind('room-activation.build-photo-grid', function () {
          _buildGrid();
          $room.unbind('room-activation.build-photo-grid');
        });
      }
      
      // Hide tooltip when hover over some items on $stage
      $stage.find('.photo-gallery-controls, .gallery-filter-dialog, .grid-scroll-buttons, .gallery-search-dialog').hover(
        function (){
          $grid.find('.photo-grid-tip.active').each(function() {
            $(this).data('tooltip').hide();
          });
        },
        function(){
        });
      }

    function _buildGrid() {
      // determine how many pages of View content we have and what the grid dimensions will need to be
      var $pager = $grid.find('ul.pager');
      var $loadedContent = $grid.find('.view-content .item-list').children();
      $loadedContent.remove();
      var currentText = $pager.find('.pager-current').text();
      var totalPages, gridWidth, gridHeight, totalCells, pagerData,
        itemsPerCell = 9, // the number of items in the view results MUST be a multiple of this number
        itemsPerView = $loadedContent.find('li').length;
      if (currentText == '') {
        totalPages = 1;
        gridWidth = Math.ceil(Math.sqrt(Math.ceil(itemsPerView / itemsPerCell)));
        gridHeight = gridWidth;
        totalCells = gridWidth * gridHeight;
      } else {
        pagerData = currentText.split(/ .* /); // text is like 2 of 14 ***OR*** 2 из 14
        totalPages = parseInt(pagerData[1]);
        gridWidth = Math.ceil(Math.sqrt(totalPages * Math.ceil(itemsPerView / itemsPerCell)));
        gridHeight = gridWidth;
        totalCells = gridWidth * gridHeight;
      }

      // create our table grid
      $grid.find('.view-content .item-list').prepend('<table class="photo-grid"></table>');
      $table = $grid.find('.view-content .item-list table');
      for (row = 1; row <= gridHeight; row++) {
        $table.append('<tr class="row-'+row+'"></tr>');
        $row = $table.find('tr.row-' + row);
        for (column = 1; column <= gridWidth; column++) {
          $row.append('<td class="col-'+column+' temporary"></td>')
          $row.find('td:last').append('<ul><li></li><li></li><li></li><li></li><li></li><li></li><li></li><li></li><li></li><div class="clearfix"></div></ul>');
        }
      }

      var page, pagesLoaded = 0;
      for(page = 0; page < totalPages; page++) {
        if (page == 0) {
          // Page 0 has already been fetched, so just flow in the LI elements (photos)
          _flowInItems($loadedContent.find('li'), 0);
        } else {
          if (true) {
            _lazyLoadViewsPage(page);
          } else {
            (function() {
              var thisPage = page;
              _getViewPage(thisPage, function($newContent) {
                $newContent = $newContent; // set in the _getViewPage function
                var $items = $newContent.find('li');
                _flowInItems($items, thisPage);
              });
            })();          
          }
        }
      }

       function _lazyLoadViewsPage(page) {
         // For a given Views page, tag the table cell(s)
         // .. and setup an AJAX lazyload handler to fetch the content

        var itemsBefore = page * itemsPerView; // Number of photos that have appeared BEFORE this Views page's photos
        var itemsToTag = itemsPerView, row, column, $cell;
        while (itemsToTag > 0) {
          itemsToTag = itemsToTag - itemsPerCell;
          row = Math.floor((itemsBefore + itemsToTag) / (gridWidth * itemsPerCell)) + 1;
          column = Math.floor(((itemsBefore + itemsToTag) % (gridWidth * itemsPerCell)) / itemsPerCell) + 1;
          $cell = $table.find('tr.row-'+row+' td.col-'+column);
//          $cell.find('li').css('background-color', 'yellow');
          if (itemsToTag == 0) {
            $cell.addClass('ajax-lazyload-pending views-page-primary views-page-' + page).removeClass('temporary').data('viewsPage', page);
            $cell.one('ajax-load', function() {
              var $cell = $(this);
//              $cell.find('li').css('background-color', 'blue');
              $cell.removeClass('ajax-lazyload-pending');
              var thisPage = $cell.data('viewsPage');
              _getViewPage(thisPage, function($newContent) {
                $newContent = $newContent; // set in the _getViewPage function
                var $items = $newContent.find('li');
                _flowInItems($items, thisPage);
              });
            });
          } else {
            $cell.addClass('ajax-lazyload-pending views-page-secondary views-page-' + page).removeClass('temporary').data('viewsPage', page);
            $cell.one('ajax-load', function() {
              var $cell = $(this);
              $cell.removeClass('ajax-lazyload-pending');
//              $cell.find('li').css('background-color', 'green');
              var page = $cell.data('viewsPage');
              var $primaryCell = $cell.closest('table').find('td.ajax-lazyload-pending.views-page-primary.views-page-' + page);
              $primaryCell.trigger('ajax-load'); // Might've already been triggered
            });
          }
        }

       }
       
       function _flowInItems($items, asPage) {
          var numProcessed = 0;
          var itemsBefore = asPage * itemsPerView;
          var row = Math.floor(itemsBefore / (gridWidth * itemsPerCell)) + 1,
            column = Math.floor((itemsBefore % (gridWidth * itemsPerCell)) / itemsPerCell) + 1;
          var $cell;
          while(numProcessed < $items.length && row <= gridHeight && column <= gridWidth) {
            $cell = $table.find('tr.row-'+row+' td.col-'+column);
            $cell.removeClass('temporary').find('ul').empty().append($items.slice(numProcessed, numProcessed + 9));
            // attach click handlers to pictures
            _photoEventHandlers($cell);
            numProcessed = numProcessed + $cell.find('ul li').length;
            column++;
            if (column > gridWidth) {
              column = 1;
              row++;
            }
          }
          _loadLazyImages();
//          pagesLoaded++
//          if (pagesLoaded >= totalPages) {
//            // all done
//            _gridInstalled();
//          }
       }

      $grid.find('.view-content .item-list').append('<div class="clearfix"></div>');

      $grid.addClass('scrolling-grid');
      
      _gridInstalled();

      //_updateGridButtons();
   

    }
      
    function _gridInstalled() {
      
      // empty unused grid cells of their temporary LI elements
      $table.find('td.temporary').empty();
      
      // all done so scroll to something interesting
      var gridHeight = $table.find('tr').length, gridWidth = $table.find('tr:first td').length, $target;
//      $target = $table.find('tr.row-' + Math.floor(gridHeight / 2) + ' td.col-' + Math.floor(gridWidth / 2)).find('li:eq(5)');
//      if ($target.length == 0) $target = $table.find('tr:first').find('td:first').find('li:last');
      $target = $table.find('tr:first td:first li:first');
      if ($target.length == 0) {
        // probably an empty grid
        $stage.find('div.photo-gallery-focus-ring').fadeOut(100, function(){
          $(this).remove();
          _updateGridButtons();
        });
      } else {
        $target.addClass('hover-focus');
        $grid.scrollTo($target,500, {
          offset:{
            top:-360,left:-410
          },
          onAfter: function() {
            _checkLazyLoad();
//            _loadLazyImages();
            _updateHoverFocus();
            _updateGridButtons();
          }
        });
      }


    }
    function _gridActivation() {
      
      // add focus ring to grid
      if ($stage.find('.photo-gallery-focus-ring').length == 0) {
        $stage.append('<div class="photo-gallery-focus-ring"></div>');
      }
      _updateHoverFocus(0);
      
      // bind up the hover-focus ring .. subsequent clicks to a photo will be captured by the focus ring
      var $ring = $stage.find('div.photo-gallery-focus-ring');
      $ring.unbind('click.photoGallery').bind('click.photoGallery', function(e) {
        var $currentFocus = $(this).data('currentFocus');
        if ($currentFocus.length > 0) $currentFocus.find('a').trigger('click');
      }).bind('mousewheel', function(e) {
        e.preventDefault();
      });
      $ring.unbind('mouseover.photoGallery').bind('mouseover.photoGallery', function(e) {
        var $currentFocus = $(this).data('currentFocus');
        if ($currentFocus.length > 0) $currentFocus.find('a').trigger('mouseover');
      })

      
      
      $stage.find('.photo-gallery-controls, .grid-button').show().fadeOut(0).fadeIn(500);
      
    }
    function _gridDeactivation() {
      _filterClose(0);
      _searchClose(0);
      $stage.find('.photo-gallery-controls, .grid-button').fadeOut(500, function(){
        $(this).hide();
      });
      $stage.find('.photo-gallery-focus-ring').fadeOut(500, function(){
        $(this).remove(); // let activation create it again
      });
    }
    function _listInstalled() {
      
      if (!$('html').is('.touch')) {
        $list.jScrollPane({
          animateScroll: true,
          hideFocus: true
        });
      }

    }
    function _photoEventHandlers($context) {

      // attach lazyload function which gets triggered
      // automatically from events in _scrollGrid
      $context.find('img.lazyLoad').lazyload({
        container: $grid,
        event: 'loadMe',
        effect: 'fadeIn',
        effectspeed: 250,
        threshold: 200
      }).addClass('load-pending');
//      $context.find('li').css('background-color', 'aqua');

      // Click handler
      $context.find('li a').not('.photo-galleryprocessed')
        .bind('click', _viewPhoto)
        .addClass('gazprom-click-processed photo-gallery-processed');

      // attach tooltips to photos
      //var moveRingTimeout;
      $context.find('li a').tooltip({
        tipClass: 'photo-grid-tip',
        relative: true,
        offset: [-70,-8],
        predelay: 50,
        delay:10,
        onBeforeShow: function() {
          $grid.find('.photo-grid-tip.active').each(function() {
            $(this).data('tooltip').hide();
          });
        },
        onShow: function() {
          var api = this;
          var $trigger = api.getTrigger();
          var $tip = api.getTip();
          var conf = api.getConf();
          
          $tip.addClass('active').data('tooltip', this);
          
//          clearTimeout(moveRingTimeout);
//          moveRingTimeout = setTimeout(_moveRing, 500);
          $.doTimeout('movering', 250, _moveRing);
          $stage.unbind('mousemove.tooltip').bind('mousemove.tooltip', 
            $.throttle( 10, function(e) {
              _update(e);
            })
          ).trigger('mousemove.tooltip');
          $tip.hide();
            
          function _update(e) {
            if (!$tip || !api.isShown()) {return;}
            pos = _getPosition($trigger, $tip, conf, [e.pageY, e.pageX]);
            $tip.css({position: 'absolute', top: pos.top, left: pos.left, display: 'inherit'})
            return;
          }
          function _getPosition($trigger, $tip, conf, mousepos) {
            var left = mousepos[1] - $trigger.offset().left + conf.offset[1];
            var top = mousepos[0] - $trigger.offset().top + conf.offset[0];
            return {top: top, left: left};
          }
          function _moveRing() {
            $grid.find('.view-content li.hover-focus').removeClass('hover-focus');
            $trigger.closest('li').addClass('hover-focus');
            _updateHoverFocus();
          }
        },
        onHide: function() {
//          clearTimeout(moveRingTimeout);
          $.doTimeout('movering');
          var api = this;
          api.getTip().removeClass('active');
          //api.getTrigger().unbind('mousemove.tooltip');
          $stage.unbind('mousemove.tooltip');
        }
//        tip: '#photo-gallery-tooltip-display'
      });
      

    } 
    function _updatePhotoFocus($target) {
      return; // no longer using this.. no letting focus ring follow mouse with hoverIntent functions
      // put the focus fing into the correct LI
      if ($target.find('div.photo-gallery-focus-ring').length > 0) return;
      var $focusRing = $stage.find('div.photo-gallery-focus-ring');
      $focusRing.data('currentFocus', $target);
      $focusRing.fadeOut(50, function() {
        $target.append($focusRing);
        $focusRing.show().fadeIn(100);
      });
    }
    function _embedPhotoFocus() {
      var $focusRing = $stage.children('div.photo-gallery-focus-ring');
      if ($focusRing.length == 0) return; // already embedded in an LI
      var $target = $focusRing.data('currentFocus');
      if (!$target) return;
      $target.append($focusRing.css({top: '',left:''}));
    }
    function _extractPhotoFocus() {
      var $focusRing = $stage.find('li div.photo-gallery-focus-ring');
      if ($focusRing.length == 0) return; // not currently embeded within an LI
      $stage.append($focusRing);
      _updateHoverFocus(0);
    }
    function _updateHoverFocus(durationSetting) {
      var $focusRing = $stage.children('div.photo-gallery-focus-ring');
      var duration = (typeof durationSetting != 'undefined') ? durationSetting : 250;
      if ($focusRing.length == 0) return; // must be embedded in an LI
      var $currentFocus = $grid.find('li.hover-focus');
      if ($currentFocus.length == 0)  return; // leave it where it is
      
      // must store the LI that actually has focus as it will lose focus
      // when we move the focus ring over it
      $focusRing.data('currentFocus', $currentFocus);
      
      // find out where focus ring needs to be and move it there
      var posX = $currentFocus.position().left;
      var posY = $currentFocus.position().top;
      posX = posX - parseInt($focusRing.css('padding-left'));
      posY = posY - parseInt($focusRing.css('padding-top')) + 2;
      if (posX != $focusRing.position().left || posY != $focusRing.position().top) {
        if (!$focusRing.is(':visible')) $focusRing.show(); //$focusRing.fadeIn(500);
        // move it
        $focusRing.animate({
          left: posX,
          top: posY
        }, {
          duration: duration,
          complete: function() {
            $(this).css('display', 'block'); // no idea why this is needed here.. but it is
          }
        });
      }
    }
    function _loadLazyImages() {
      $.doTimeout(50, function() {
        $grid.find('table li img.load-pending:in-grid-viewport').trigger('loadMe').removeClass('load-pending');
      });
    }
    function _checkLazyLoad() {
      $grid.find('table td.ajax-lazyload-pending:in-grid-viewport').trigger('ajax-load');
    }
    function _scrollGrid(e) {
      e.preventDefault();
      var $target = $(this);
      var settings = {
        onAfter: null,
        margin: true,
        duration: 1000
      };
      _filterClose();
      _searchClose();

      $grid.find('.photo-grid-tip.active').each(function() {
        $(this).data('tooltip').hide();
      });

      if ($target.hasClass('deactivated')) return;
      var delta = {};
      if ($target.is('.scroll-right')) {
        delta = {top: 0, left: (stageWidth - 240)};
      } else 
      if ($target.is('.scroll-left')) {
        delta = {top: 0, left: -1 * (stageWidth - 240)};
      } else
      if ($target.is('.scroll-up')) {
        delta = {top: -1 * (stageHeight - 240), left: 0};
      }else
      if ($target.is('.scroll-down')) {
        delta = {top: (stageHeight - 240), left: 0};
      }
    
      // construct scrollTo relative scroll configuration
      var scrollChange = {top: '+=0px', left: '+=0px'};
      if (delta.top < 0) {
        scrollChange.top = '-=' + Math.abs(delta.top) + 'px';
      }
      if (delta.top > 0) {
        scrollChange.top = '+=' + delta.top + 'px';
      }
      if (delta.left < 0) {
        scrollChange.left = '-=' + Math.abs(delta.left) + 'px';
      }
      if (delta.left > 0) {
        scrollChange.left = '+=' + delta.left + 'px';
      }
      
      var $focusRing = $stage.find('.photo-gallery-focus-ring');

      // before we scroll the grid, must put focus ring into LI it hovers over so it will move with grid.
      _embedPhotoFocus();
      
      // execute the movements
      $grid.stop(true,false).scrollTo(scrollChange, {
        margin: settings.margin,
        duration: settings.duration,
        onAfter: function() {
          _extractPhotoFocus(); // take out of LI and make sure it is positioned correctly above it
          _loadLazyImages();
          _checkLazyLoad();
          _updateGridButtons();
          if (typeof settings.onAfter == 'function') {
            settings.onAfter.call();
          }
        }
      });
      
//      $focusRing.animate({
//        top: -1 * delta.top,
//        left: -1 * delta.left
//      }, settings.duration);
      
    }
    function _updateGridButtons() {
      return; // @TODO not yet ready for prime time
      $stage.find('.grid-button').removeClass('deactivated');
      if ($grid.scrollLeft() == 0) {
        $stage.find('.grid-scroll-buttons .grid-button.scroll-left').addClass('deactivated');
      }
      if ($grid.scrollTop() == 0) {
        $stage.find('.grid-scroll-buttons .grid-button.scroll-up').addClass('deactivated');
      }
      if ($grid.find('li img:right-of-grid-viewport').length == 0) {
//      if ($grid.scrollLeft() +$grid.width() >= $.scrollTo.max($grid, 'x')) {
        $stage.find('.grid-scroll-buttons .grid-button.scroll-right').addClass('deactivated');
      }
      if ($grid.find('li img:below-grid-viewport').length == 0) {
//      if ($grid.scrollTop() + $grid.height() >= $.scrollTo.max($grid, 'y')) {
        $stage.find('.grid-scroll-buttons .grid-button.scroll-down').addClass('deactivated');
      }
    }
    function _viewPhoto(e) {
      e.preventDefault();
      var $anchor = $(e.currentTarget);
      if ($grid.length > 0) {
        _updatePhotoFocus($anchor.closest('li'));
      }

      Drupal.gazprom.gotoHref($anchor.attr('href')); //, {viewPhoto: true});
      
      return false;
    }
    function _getViewPage(pageNum, callback) {
 
      var href = Drupal.gazprom.utility.getViewsAjaxPath() + '?' ;
      var viewIDdata = _getViewID();
      href = href + 'view_name=' + viewIDdata.view_name + '&view_display_id=' + viewIDdata.view_display_id + '&' + 'page=' + (pageNum);
      
      // we need the view filter & sort arguments from the pager's link (pager gets updated by filter's ajax routine)
      var $pagerNext = $gallery.find('.item-list ul.pager li.pager-next')
      if ($pagerNext.length > 0) {
        var pagerNextHref = $pagerNext.find('a').attr('href');
        var hrefParts = pagerNextHref.split('?');
        if (hrefParts.length > 0) {
          var queryString = hrefParts[1];
          href = href + '&' + queryString.replace('&page=', '&ignoreThis=');
          // @TODO this needs work
        }
      }
      
      $.get(href, function(result){
        _processViewAJAXresult(result, callback);
      }); 
    }
    function _getViewID() {
      // returns a string with the current gallery's view_name and view_display_id
      // formatted for ajax get purposes
      
      return Drupal.gazprom.utility.getViewIDs($gallery.find('.view'));
      
      // is this a hack? find the view_name and view_display_id values from the classes
//      var classArray = $gallery.find('.view').attr('class').split(' ');
//      var view_name, display_id;
//      $.each(classArray, function(index, value) {
//        if (value.substring(0,8) == 'view-id-') {
//          view_name = value.replace('view-id-', '');
//        }
//        if (value.substring(0,16) == 'view-display-id-') {
//          display_id = value.replace('view-display-id-', '');
//        }
//      });
//      if (!view_name && ! display_id) return {}; // something went wrong
//      
//      return {view_name: view_name, view_display_id: display_id};
      //return 'view_name=' + view_name + '&view_display_id=' + display_id;
    }
    function _processViewAJAXresult(result, callback) {
      //var $newContent = $(result[1].data).find(vars.viewInnerSelector).children(); //.find('.view-content ul.item-list, .view-content table tbody').children();
      var $newContent = $(result[1].data).find('.view-content .item-list ul');
      // make sure new content is attached to handlers
      //Drupal.gazprom.init.anchorHandlers($newContent);
      // ^^^ actually, this isn't needed in here. The callback is going to attach its
      // own click handlers

      // temp hack:
//      $newContent.find('img').each(function(){
//        $(this).attr('src','');
//      });

      if (typeof callback == 'function') {
        callback($newContent);
      }
    }
    function _toggleFilterDialog() {
      if ($filterDialog.hasClass('opened')) {
        _filterClose();
      } else {
        _filterOpen();
      }
    }
    function _filterOpen() {
      //_gridControls('hide');
      var cssHeight = $filterDialog.css('height');
      $filterDialog.stop(true,true).height(0).show().animate({
        height: cssHeight
      }, {
        duration: 500
      });
      $filterDialog.removeClass('closed').addClass('opened');
    }
    function _filterClose(duration) {
      if (typeof duration == 'undefined') duration = 500;
      $filterDialog.stop(true,true).animate({
        height:0
      }, {
        duration: duration,
        complete: function() {
          $filterDialog.hide().css('height','');
          //_gridControls('show');
        }
      });
      $filterDialog.removeClass('opened').addClass('closed');
    }
    function _toggleSearchDialog() {
      if ($searchDialog.hasClass('opened')) {
        _searchClose();
        $searchDialog.find('input').trigger('submitQuery');
      } else {
        _searchOpen();
      }
    }
    function _searchOpen() {
      var cssHeight = $searchDialog.css('height');
      $searchDialog.stop(true,true).height(0).show().animate({
        height: cssHeight
      }, {
        duration: 200,
        complete: function() {
          $searchDialog.find('input').focus();
        }
      });
      $searchDialog.removeClass('closed').addClass('opened');
    }
    function _searchClose(duration) {
      if (typeof duration == 'undefined') duration = 200;
      $searchDialog.stop(true,true).animate({
        height:0
      }, {
        duration: duration,
        complete: function() {
          $searchDialog.hide().css('height','');
        }
      });
      $searchDialog.removeClass('opened').addClass('closed');
    }
    function _gridControls(command) {
      if ($grid.length > 0) {
        switch(command) {
          case 'show':
            $stage.find('.grid-button').fadeIn(500);
            break;
          case 'hide':
            $stage.find('.grid-button').fadeOut(500);
            _filterClose(100);
            _searchClose(100);
            break;
        }
      }
    }
    function _relocateSortFilters() {
      var $filters = $gallery.find('.view-filters');
      $filterDialog.empty().append($filters.clone(false));
      $filters.remove();
      $filters = $filterDialog.find('.view-filters');
      
      $searchFilter = $filterDialog.find('.views-widget-filter-keys');
      $searchDialog.empty().append($searchFilter.clone());
      var $searchInput = $searchDialog.find('.views-widget-filter-keys input');
      $searchInput.data('lastValue', $searchFilter.find('input').val());
      if ($searchInput.data('lastValue')) {
        $searchDialog.addClass('value-set');
        $stage.find('.gallery-control-search').addClass('active');
      } else {
        $searchDialog.removeClass('value-set');
        $stage.find('.gallery-control-search').removeClass('active');
      }
      $searchDialog.find('.views-widget-filter-keys input').bind('keydown', function(e) {
        if (e.keyCode == 13) {
          e.preventDefault();
          $(this).trigger('submitQuery');
          return false;
        } else {
          return true;
        }
      }).bind('submitQuery', function(e) {
        var $searchInput = $(this),
          lastValue = $searchInput.data('lastValue'),
          newValue = $searchInput.val(); 
        
        if (newValue != lastValue) {
          $searchFilter.find('input').val($searchInput.val());
          $searchInput.data('lastValue', newValue);
          $searchFilter.closest('form').submit();
          $searchDialog.addClass('value-set');
          $stage.find('.gallery-control-search').addClass('active');
        }
        if (newValue == '') {
          $searchDialog.removeClass('value-set');
          $stage.find('.gallery-control-search').removeClass('active');
        }
        _searchClose();
      })
        
      // customize form elements @TODO get this to somewhere else!!
      // to apply only to checkbox use:
      $filters.find('input[type="checkbox"]').ezMark({
       checkboxCls: 'gazprom-checkbox',
       checkedCls: 'active'
      });

      // for only radio buttons:
      $filters.find('input[type="radio"]').ezMark({
       radioCls: 'gazprom-radio' ,
       selectedCls: 'active'
      });

      $filterDialog.find('form').addClass('hijacked').ajaxForm({
        beforeSerialize: function($form, options) { 
          _filterClose();
          _searchClose();
          var viewIDdata = _getViewID();
          options.data = viewIDdata;
          options.url = Drupal.gazprom.utility.getViewsAjaxPath();
          // return false; // to cancel submit                  
        },
        beforeSubmit: function(arr, $form, options) {
          arr = arr;
          $form = $form;
          options = options;
            // The array of form data takes the following form: 
            // [ { name: 'username', value: 'jresig' }, { name: 'password', value: 'secret' } ] 

            // return false; // to cancel submit     
            Drupal.gazprom.utility.setBusy();
        },
        success: function showResponse(result, statusText, xhr, $form)  { 
          result = result;
          var $newContent = $(result[1].data); //.find('.view-content .item-list ul');
          
          $gallery.empty().append($newContent);
          _initializeGallery();
          Drupal.gazprom.utility.clearBusy();
          return;
        }
      });
    }
    function _bindGalleryControls() {
      $stage.find('.gallery-control-list-view a, .gallery-control-grid-view a')
      .unbind('click.photoGallery').bind('click.photoGallery', function(e) {
        e.preventDefault()
        var $target = $(e.currentTarget);
        //if ($target.parent().is('.active')) return;
        $stage.find('.active-grouping.active').removeClass('active');
        $target.parent().addClass('active');
        _loadNewGallery($target.attr('href'));
        return false;
      }).addClass('gazprom-click-processed');
    }
    function _loadNewGallery(href) {
      // a different gallery was chosen, so load it up and replace current
      
      // first, fade out current
      //$gallery.add($stage.find('.grid-button')).fadeOut(500);
      
      $room.trigger('room-deactivation.photoGallery');
      
      _filterClose();
      _searchClose();
      // get new content
      Drupal.gazprom.utility.setBusy();
      $.get(href, function(data) {
        if ($('html').is('.ie8, .ie7, .ie6') && Drupal.gazprom.useInnerShiv) {
         $newContent = $(innerShiv($(data).find('.stage .photo-gallery-content').first().outerHTML()));
        }else {
          $newContent = $(data).find('.stage .photo-gallery-content').first();
        }
        $newContent = $newContent.children(); // remove .photo-gallery-content div
        
        $stage.find('.photo-gallery-content').empty().append($newContent.unwrap());
        _initializeGallery();
        Drupal.gazprom.utility.clearBusy();

        // @TODO This needs to start using the loadContent() and insertContent() functions
      });

    }
          
  }
})(jQuery, Drupal);

(function($, Drupal) {
  var viewPhoto =
  Drupal.gazprom.viewPhoto = {
    view: function($wrap, api) {
      /* essentially the init of the photo display program
       * Uses photo node content already contained within the $wrap and the overlay (api)
       **/

      this.$wrap = $wrap;
      this.overlay_api = api;
      $wrap.css('overflow', 'hidden');
      $wrap.find('.view-collection-contents').hide(); // @TODO temporary
      $wrap.find('.field-name-field-ref-collection').hide();

      
      var $image = $wrap.find('.field-name-field-image img');
      $image.hide();
      this.$image = $image;
    
      // build out various
      $wrap.append('<div class="photo-controls"></div>');
      var $controls = $wrap.find('.photo-controls');
      this.$controls = $controls;
      
      $controls.append($wrap.find('.field-name-field-photo-description'));
      var $description = $controls.find('.field-name-field-photo-description');
      $description.show();

      $controls.append($wrap.find('.field-name-field-ref-collection, .field-name-title-field'));
      var $title = $controls.find('.field-name-field-ref-collection, .field-name-title-field');
      $title.addClass('field-name-field-ref-collection')
      $title.show();
      // Note: Searching here for both .field-name-field-ref-collection or .field-nam-title-field. As of Mar 29 2012, Entity Translation
      // .. is enabled on Media: Collection (Photo Set) node types and the title has been replaced with title_field (which is translatable) via
      // .. the Title module. See the node--media-photo.tpl.php for the code required to properly retrieve the translated title_field from
      // .. the referenced Media: Collection node. The References module seems to have issues with field translation via Entity Translation module.

      $slideshow_pause = $('<div class="slideshow-pause" title="' + Drupal.t('Pause slideshow') + '"></div>');
      $slideshow_play = $('<div class="slideshow-play" title="' + Drupal.t('Start slideshow') + '"></div>');
      $title.after('<div class="slideshow-controls"></div><div class="clearfix"></div>');
      $controls.find('.slideshow-controls').append($slideshow_pause, $slideshow_play);

      $controls.append('<div class="related-photos"></div>');
      $controls.fadeOut(0);
      var $relatedPhotos = $controls.find('.related-photos');
      $relatedPhotos.append($wrap.find('.view-collection-contents .view-content').children());
      $relatedPhotos.after('<div class="clearfix"></div>');
      this.$imageList = $relatedPhotos.find('.item-list ul');
      
      // locate the current photo in the list, set it active, and move to front of list ??
      var imageSrc = $image.attr('src');
      var $currentImage = this.$imageList.find('li a[href="'+imageSrc+'",imagesrc="'+imageSrc+'"]').closest('li');
      if ($currentImage.length == 0)
        $currentImage = this.$imageList.find('li a[imagesrc="'+imageSrc+'"]').closest('li'); // the imagesrc attribute is added in the View
      if ($currentImage.length > 0) {
        //$currentImage.prependTo(this.$imageList);
        this.makeThumbActive($currentImage);
      }

      $control_next = $('<div class="photo-control photo-next" title="' + Drupal.t('Next photo') + '">');
      $control_prev = $('<div class="photo-control photo-prev" title="' + Drupal.t('Previous photo') + '"></div>');
      $control_close = $('<div class="photo-control close" title="' + Drupal.t('Close') + '"></a>');
      //$control_share = $('<div class="photo-control share">Share</div><div class="photo-control share-icons"></div>');
      $control_share = $('<div class="photo-control share">Share</div>');
      $control_share_tooltip = $('<div class="page-tool-tip share-links"><a class="share-facebook share-link" title="Facebook">Facebook</a><a class="share-twitter share-link" title="Twitter">Twitter</a><a class="share-google share-link" title="Google+">Google+</a></div>');
      $control_revealBottom = $('<div class="photo-control reveal" title="' + Drupal.t('Enlarge photo') + '"></div>');

      $wrap.append($control_next, $control_prev, $control_close,$control_share,$control_share_tooltip);
      $wrap.find('.photo-control').fadeOut(0);
      $wrap.append('<div class="photo-cover"></div>');

      $controls.append($control_revealBottom);

      // bind controllers to their functions
      $control_next.unbind('click').bind('click', this.nextPhoto);
      $control_prev.unbind('click').bind('click', this.prevPhoto);
      //this.$imageList.find('li').unbind('click').bind('click', this.specificPhoto)
      this.$imageList.find('li a:not(.viewPhoto-processed)').unbind('click').bind('click.viewPhoto', this.specificPhoto).removeClass('hijaxed').addClass('viewPhoto-processed');
      $control_close.unbind('click').bind('click', this.closeController);
      $control_share.unbind('click').bind('click', this.share);
      $slideshow_pause.unbind('click').bind('click', this.pause);
      $slideshow_play.unbind('click').bind('click', this.play);
      //$control_revealBottom.unbind('click').bind('click', {element: $controls, controllers: this.controllers}, this.controllers.toggleReveal);
      $control_revealBottom.unbind('click').bind('click', this.toggleReveal);


      // share functions
      Drupal.gazprom.init.shareTools($wrap);
      
      // make sure the image is full loaded, adjust it, and fade things in
      this.adjustPhoto($image, _finishView);

      function _finishView() {
        if (viewPhoto.inFullScreen) {
          viewPhoto.slideDown(true);
          viewPhoto.fullScreen();
        }
        if (!$image.hasClass('viewed')) {
          $image.fadeOut(0).fadeIn(500, function() {
            viewPhoto.$controls.fadeIn(500);
            viewPhoto.$wrap.find('.photo-control').fadeIn(500);
            $image.addClass('viewed'); // so we don't fadein after window resizes
            viewPhoto.makeThumbActive($currentImage);
          });
        }
      }

    },
    close: function () {
      $(window).unbind('resize.viewPhoto');
      clearTimeout(viewPhoto.slideshowTimeout);
      if (viewPhoto.inFullScreen) {
        $('#header, nav.second-navigation').fadeIn(500);
      }
      $('#header, nav.second-navigation, #footer-page').removeClass('full-width');
      
    },
    nextPhoto: function(e) {
      e.preventDefault();
      //e.data.viewPhoto.changePhoto('forward');
      viewPhoto.changePhoto('forward')
    },
    prevPhoto: function(e) {
      e.preventDefault();
      viewPhoto.changePhoto('back');
    },
    specificPhoto: function(e) {
      e.preventDefault();
      var $newPhoto = $(e.currentTarget);
      if ($newPhoto.is('a')) $newPhoto = $newPhoto.closest('li');
      viewPhoto.loadNewPhoto($newPhoto);
    },
    closeController: function(e) {
      e.preventDefault();
      viewPhoto.overlay_api.close();
    },
    pause: function(e) {
      e.preventDefault();
      clearTimeout(viewPhoto.slideshowTimeout);
      viewPhoto.slideUp();
      viewPhoto.$controls.find('.slideshow-play').removeClass('active');
      viewPhoto.lessScreen();
    },
    play: function(e) {
      e.preventDefault();
      viewPhoto.slideshowTimeout = setTimeout(_interval, 2000);
      viewPhoto.slideDown(false);
      viewPhoto.$controls.find('.slideshow-play').addClass('active');
      viewPhoto.fullScreen();
      
      function _interval() {
        viewPhoto.changePhoto('forward');
        viewPhoto.slideshowTimeout = setTimeout(_interval, 10000);
      }

    },
    slideDown: function(withDelay) {
      //if (!(viewPhoto.$controls.data('originalHeight'))) viewPhoto.$controls.data('originalHeight', viewPhoto.$controls.height());
      viewPhoto.$controls.data('originalHeight', viewPhoto.$controls.height());
      viewPhoto.$controls.removeClass('expanded').addClass('collapsed');
      var delayAmount = (withDelay == true) ? 1000 : 0;
      var $albumTitle = viewPhoto.$controls.find('.field-name-field-ref-collection');
//      var newHeight = $albumTitle.position().top + $albumTitle.outerHeight();
//      viewPhoto.$controls.delay(delayAmount).animate({
//        height: newHeight //'35px'
//      }, 500);
      viewPhoto.$controls.find('.related-photos').delay(delayAmount).slideUp(500);
    },
    slideUp: function() {
      viewPhoto.$controls.removeClass('collapsed').addClass('expanded');
      var originalHeight = viewPhoto.$controls.data('originalHeight');
      if (typeof originalHeight != 'undefined') {
//        viewPhoto.$controls.stop().animate({
//          height: originalHeight
//        }, 500);
      viewPhoto.$controls.find('.related-photos').slideDown(500);
      }
    },
    toggleReveal: function(e) {
      if (viewPhoto.$controls.is('.collapsed')) {
        viewPhoto.slideUp();
        viewPhoto.lessScreen();
      } else {
        viewPhoto.slideDown();
        viewPhoto.fullScreen();
      }
    },
    fullScreen: function() {
      var $close = viewPhoto.$wrap.find('.photo-control.close');
      var $share = viewPhoto.$wrap.find('.photo-control.share');
      $close.data('originalCSS', {top: $close.css('top'), opacity: $close.css('opacity')});
      $share.data('originalCSS', {top: $share.css('top'), opacity: $share.css('opacity')});
      viewPhoto.$wrap.find('.photo-control:not(.reveal)').css({opacity: 0})
      $close.animate({
        opacity: .3,
        top: 10
      }, 500);
      $share.animate({
        opacity: 0,
        top: 10
      }, 500, function() {
        $share.css('display', 'none');
      });
      $('#header, nav.second-navigation').fadeOut(500);
      viewPhoto.inFullScreen = true;
    },
    lessScreen: function() {
      var $close = viewPhoto.$wrap.find('.photo-control.close');
      var $share = viewPhoto.$wrap.find('.photo-control.share');
      viewPhoto.$wrap.find('.photo-control:not(.reveal)').css('opacity','');
      $close.animate({
        opacity: $close.data('originalCSS')['opacity'],
        top: $close.data('originalCSS')['top']
      }, 500);
      $share.css('display', 'block').css('opacity', 0).animate({
        opacity: $share.data('originalCSS')['opacity'],
        top: $share.data('originalCSS')['top']
      }, 500);
      
      $('#header, nav.second-navigation').fadeIn(500);
      viewPhoto.inFullScreen = false;
    },
    changePhoto: function(direction) {
      var $currentPhoto = this.$imageList.find('.active');
      if ($currentPhoto.length == 0) $currentPhoto = this.$imageList.find('li').first();
      var $newPhoto;
      if (direction == 'back') {
        $newPhoto = $currentPhoto.prev();
        if ($newPhoto.length == 0) $newPhoto = this.$imageList.find('li').last();
      }else {
        $newPhoto = $currentPhoto.next();
        if ($newPhoto.length == 0) $newPhoto = this.$imageList.find('li').first();
      }
      this.loadNewPhoto($newPhoto);
    },
    makeThumbActive: function($photo) {
      this.$imageList.find('.active').removeClass('active');
      $photo.addClass('active');
      //return;
      // if needed, slide it into view
      var $container = $photo.closest('div.photo-controls');
      var $wrapper = $photo.closest('div.related-photos');
      var offset = $photo.position().left;
      var adjustToCenter = ($container.width() / 2) - offset - ($photo.width() / 2),
        newMarginLeft;
      if (offset + $photo.width() > $container.width() - ($container.width() * .10)) {
        newMarginLeft = 
        $wrapper.stop(true, true).animate({
          marginLeft: parseInt($wrapper.css('marginLeft').replace('auto', '0px')) + adjustToCenter
        }, {duration: 500});
      }
      if (offset < $container.width() * .10 && ($wrapper.find('li:first').position().left < 1)) {
        if (Math.abs($wrapper.find('li:first').offset().left) < adjustToCenter) adjustToCenter = Math.abs($wrapper.find('li:first').position().left);
        $wrapper.stop(true, true).animate({
          marginLeft: parseInt($wrapper.css('marginLeft').replace('auto', '0px')) + adjustToCenter
        }, {duration: 500});
      }
      
    },
    loadNewPhoto: function($newPhoto) {
//      this.makeThumbActive($newPhoto);
      
      var newImageSrc = $newPhoto.find('a').attr('imagesrc'); // this special attribute is put in by the View
      if (!newImageSrc) newImageSrc = $newPhoto.find('a').attr('href'); // try a traditional link
      var viewPhoto = this;
      viewPhoto.$image.css({position: 'absolute', zIndex: '1', width: viewPhoto.$image.width(), height: viewPhoto.$image.height(), top: 0, left: 0});
      var newImage = new Image();
      $(newImage)
        .unbind('load')
        .bind('load', function() {
          var $newImage = $(this);
          $newImage.attr('width', this.width).attr('height', this.height);
          $newImage.css({zIndex: '0', position: 'absolute', top: 0, left: 0});
          viewPhoto.$image.after($newImage);
          viewPhoto.adjustPhoto($newImage, function() {
            if (!$newImage.hasClass('viewed')) {
              viewPhoto.$image.fadeOut(750, function(){
                viewPhoto.$image.remove();
                viewPhoto.$image = $newImage;
                $newImage.addClass('viewed'); // So we only do this once (resize will trigger this callback again)

                viewPhoto.makeThumbActive($newPhoto);
              });
              $newImage.fadeOut(0).fadeIn(750);
              // Remove this fadeOut/fadeIn if client ever decides to go back will images that fill entire viewport (fitInContainer: false)
              
              // Swap new photo description in
              viewPhoto.$controls.find('.field-name-field-photo-description').empty().append($newPhoto.find('.views-field-field-photo-description').children().clone());
            }
          });
        })
        .attr('src', newImageSrc);
    },
    adjustPhoto: function(element, callback) {
      
      var $wrap = this.$wrap;
      var $image = element ? element : this.$image;
      
      $image.fluidCenterAlignImage({
        containerSelector: $wrap.selector,
        fitInContainer: true,
        useAbsoluteSizes: true,
        callback: callback
      });
      return;
      
    },
    inFullScreen: false,
    $wrap: {},
    $image: {},
    $imageList: {},
    $controls: {},
    overlay_api: {},
    slideshowTimeout: 0
  }
})(jQuery, Drupal); // Drupal.gazprom.viewPhoto


(function($, Drupal){
  /*
   * Settings and functions associated with Hijax (history.js and AJAX loading)
   * 
   */
  Drupal.gazprom.hijax = {
    initialized: false,
    previousStateID: 0,
    doAJAX: false,
    containerSelector: '.default-ajax-receiver:first',
    contentContainer: $([]),
    animateBefore: {},
    callback: {},
    pageHit: function (path) {
      if ((typeof(_gaq) == 'object') && path) {
          _gaq.push(['_trackPageview', path]);
      }
    },
    readyCheck: function() {
      /* check to see if document is ready for first statechange */
      //return $('body').is('.gazprom-built');
      return Drupal.gazprom.hijax.initialized;
    },
    onStatechange: function(href, options, State) {
      /* This is the primary handler for all hijaxed links within the site */
      if (Drupal.gazprom.build.inBuildMode == true) return; // not ready yet
      
      var newHref = Drupal.gazprom.currentURL(State);

      /* track the page hit */
      if (typeof(options.pageHit) == 'function') {
          options.pageHit.call(this, href);
      }

      var data = State.data;
      Drupal.gazprom.openPath(newHref, (data ? data : null));
      
      return;
    // @TODO gotta sort out this href vs newHref situaton. href is deprecated, but still being passed by hijax.js
    }
  }
  Drupal.gazprom.currentURL = function(State) {
    /*
     * Returns a santized URL using History's state
     * (strips http and such)
     */
    if (typeof State == 'undefined') State = $.hijax_getState();
    
//    var pathExtract = /^[a-z]+:\/\/\/?[^\/]+(\/[^?]*)/i; // <--- this one removes query string :(
//    var href = (pathExtract.exec(State.cleanUrl))[1];
    
    var pathExtract = /(http:\/\/[^/]*)(\/.*)/i; // <-- remove protocol and host, but leave everything else intact
    var href = (pathExtract.exec(State.cleanUrl))[2];
    
    // If this is early in the initialization process, HTML4 browsers might still give up a hashed URL like /en#en/content/company
    // .. we are most likely called by the room initialization function and it really does need /en as the path. See the
    // .. _finish() function inside activeRoom().
    var hashClear = /(^.*)(#.*)/i;
    var regExResult = hashClear.exec(href);
    if (regExResult !== null) {
      href = regExResult[1];
    }
    // @TODO This is kindof a hack. Is there a better way to clean this up incase the hash part of the URL is important.
    
    return href;
  }
  
})(jQuery, Drupal);


(function($, Drupal){
  
  Drupal.gazprom.init = {
    site: function() {
      /*
       * This is the main initialization routine. It loads all first and second level
       * navigation anchors, build a directory and does some additional data initialization.
       * @TODO add in various UI initializers
       */

       // preload CSS images
       //$.preloadCssImages();

      if (Modernizr.history === false && window.location.pathname != Drupal.settings.gazprom.front_page && !Drupal.gazprom.singlePageMode) {
         window.location.href = 'http://' + window.location.hostname + Drupal.settings.gazprom.front_page + '#' + window.location.pathname;
         // @TODO check the status on this
         return;
       }
        
        // window resize handler
        Drupal.gazprom.windowResizeInit();
        
        // main search form
        Drupal.gazprom.search.init();
        
        // site map
        Drupal.gazprom.sitemap.init();
        
        // lang drodown;
        Drupal.gazprom.init.langDropdown();
        
        // non-room links that need to be hijaxed
        $('#footer-page a.hijax').once('gazprom-click', function() {
          $(this).hijax();
        });
        
        if (Drupal.gazprom.singlePageMode === true) {
          // activate the first room loaded
          var $firstRoom = $('.content-room-wrapper:first');
          Drupal.gazprom.activateRoom($firstRoom);

          $('html').addClass('singlePageMode');
          
          // done with init.site() for singlePageMode
          //return; 
         
        }
        
        // track scrolling status
        Drupal.gazprom.scroll.init();

        Drupal.gazprom.directory = new Array();
        
        // setup a temporary click disabler on all anchors until all loading/building is done
        $('a').bind('click.duringInitialization', function(e){
          e.preventDefault();
          Drupal.settings.gazprom.scrollToFirst_id = Drupal.gazprom.utility.urlToId($(e.currentTarget).attr('href'));
          return false;
          // this gets unbind'ed in Drupal.gazprom.build.complete()
        });
        // record the id of the content already loaded.. we're going to want to scroll back to it when
        // .. everything is finished loading
        var $originalContent = $('.content-room-wrapper:first');
        if ($originalContent.length > 0) {
          Drupal.settings.gazprom.scrollToFirst_id = $originalContent.attr('id');
          var cleanUrl = $.hijax_getState().cleanUrl;
          var pathExtract = /^[a-z]+:\/\/\/?[^\/]+(\/[^?]*)/i;
          cleanUrl = (pathExtract.exec(cleanUrl))[1];
          if (cleanUrl.indexOf('#') != -1) {
            var parts = cleanUrl.split('#');
            if (parts[1]) {
              cleanUrl = parts[1];
            }
          }
          Drupal.settings.gazprom.scrollToFirst_id = Drupal.gazprom.utility.urlToId(cleanUrl);

          // @TODO Everything above can most likely be discarded
          
        }
        
          // call stage1 init/build routine. This function populates the rest of the rooms
          // .. on the floor that our initially loaded content is on. This is done for 
          // .. deep linking situations. In the case of loading the home page first, then
          // .. this function will do nothing except call stage2
          Drupal.gazprom.build.start(_finishInit);


        function _finishInit() {
          
          // attach waypoints ot floors (if not already done in init.room()
          $.waypoints.settings.scrollThrottle = 50; // the default of 100 was a little too slow
          $('.content-floor-wrapper:not(.waypoints-attached)').each(function() {
            Drupal.gazprom.scroll.floorWaypoints($(this));
          }).addClass('waypoints-attached');
          
          // initialize hijax settings
          if (!Drupal.gazprom.singlePageMode) {
            $.hijax_init(Drupal.gazprom.hijax);

//            if (false) {
//              if (window.location.hash != '') {
//                var href = window.location.hash;
//                href = href.replace(/^#/, '');
//                href = href.replace(/^!/, '');
//                href = href.replace(/^\//, '');
//                href = '/' + href;
//                $.hijax_replaceState('/', {}, true);
//                setTimeout(function() {
//                  // have to use timeout so old browsers (Firefox 3!) get their state properly updated for this call
//                  Drupal.gazprom.gotoHref(href, {}, true);
//                }, 500);
//              } else {
//                var $firstRoom = $('#' + Drupal.settings.gazprom.scrollToFirst_id);
//                Drupal.gazprom.activateRoom($firstRoom, {skipScroll:false, XXXduration:100});
//                // note: don't try to make duration 0 or very fast.. for some reason, waypoint functions still kick in 
//                // and end up changing the destination.. figure this out!
//              }
//            }

            // use openPath to go to the current href (URL.. whatever) so that the right room
            // .. gets activated. Also covers HTML4 <-> HTML5 URL issues
            $.doTimeout(500, function() {
              // have to use timeout so old browsers (Firefox 3!) get their state properly updated for this call
              var href = Drupal.gazprom.currentURL($.hijax_getState());
              Drupal.gazprom.openPath(href);
            });
          }
          
          // Hijax the main navigation items (including home page link)
          $('#navigation-main a, a#go-home').hijax();

          // light up all the indicators
          $('nav .indicator').each(function() {
            Drupal.gazprom.utility.updateIndicator($(this));
          });

          // For any rooms that have their stage2 initialization deferred, trigger it now.
          // (This is used when preloading rooms.)
          $('.content-room-wrapper').trigger('initStage2');
          
          // Make sure current room is activated (again?) after initStage2.
          //$('.content-room-wrapper.active-room').trigger('room-activation');
          Drupal.gazprom.activeRoom.trigger('room-activation');
          
          Drupal.gazprom.initialized = true;
        }
    },
    room: function($room, options) {
      // called on the intial room (loaded without AJAX) and every room subsequently inserted & loaded
      // via AJAX. If you are new here: A room is equivelant to a page. A floor is a container with multiple rooms.
      
      var settings = $.extend({
        stage2: 'deferred' // deferred until initStage2 event is triggered
      }, options);
      
      if ($($room).length == 0) return;
      var $floor = $room.closest('.content-floor-wrapper'), $secondNavigation;
      if ($floor.length == 0) return; // something went wrong

      if ($room.is('.initialized')) return;
      $room.addClass('initialized');
      
      if (!$room.data('href')) {
        // The room hasn't been run through this routine yet and it wasn't added via the .insertContent() function so
        // .. it is most likely the first room requested.
        
        $room.data('href', Drupal.gazprom.currentURL());
        $room.data('nav-main-anchor', $('#navigation-main ul.menu li a.active-trail'));
        $room.data('nav-second-anchor', $('nav.second-navigation ul.menu li a.active-trail'))
      }
      
      

      // see if the room has been wrapped in various containers necessary for scrolling
      if ($room.closest('.floor-slider').length == 0) {
        
        $secondNavigation = $room.siblings('nav.second-navigation');
        
        $room.wrap('<div class="floor-slider width-full"><div class="rooms-of-floor"></div></div>');
        $room.closest('.rooms-of-floor').append('<div class="clearfix js-added-line-2194"></div>')
        $room.closest('.floor-slider').css({
          overflow: 'hidden'
        });
        // (only first INSTALLED room of each floor will need this wrapping applied. the other rooms will be inserted into the wrapping)
        
        // good opportunity to also attach waypoint handlers to the floor
        Drupal.gazprom.scroll.floorWaypoints($floor);
        $floor.addClass('waypoints-attached');

      } else {
        $secondNavigation = $room.closest('.floor-slider').siblings('nav.second-navigation');
        
      }
      
      // tag first-rooms for different styling and other purposes
      if ($secondNavigation.length > 0) {
        var $idOfFirstLink = Drupal.gazprom.utility.urlToId($secondNavigation.find('ul.menu a:first').attr('href'));
        if ($idOfFirstLink == $room.attr('id')) {
          $room.addClass('first-room');
        } else {
          $room.addClass('not-first-room');
        }
      } else if (!$room.is('.room-error')) {
        // if no second navigation, then assume this room is one and only of the floor
        $room.addClass('first-room only-room');
        
        // for pages that are not on the navigation menus (i.e. country pages), we might want to visit them in singlePageMode
        if (Drupal.gazprom.singlePageMode) {
          $room.removeClass('first-room only-room');
          $room.addClass('not-first-room');
        }
      }
      
      // set the room to a fixed width & height (the window's)
      $room.sizeRoom();
      
      // bind up special background image resizer
      $room.find('div.to-background img.fancy-background-image:not(.fluid-center-align)').fluidCenterAlignImage({
        containerSelector: '.expand-top',
        safeOffset: {top: 157, left: 0, right: 0, bottom: 0}
      });
      $floor.find('.relative-wrapper img.fancy-background-image:not(.fluid-center-align)').fluidCenterAlignImage({
        containerSelector: '.relative-wrapper',
        safeOffset: {top: 157, left: 0, right: 0, bottom: 0}
      });
      $room.find('div.stage img.stage-background:not(.fluid-center-align)').fluidCenterAlignImage({
        containerSelector: '.stage',
        safeOffset: {top: 157, left: 0, right: 0, bottom: 0}
      });
      /* top: 157 = the height of first and second navigation */

      // configure step-width containers
      $room.find('.step-width').stepWidth();
      
      // former home of paginateContent calls
      
      // setup print button(s)
      Drupal.gazprom.init.printTools($room);

      // setup share buttons
      Drupal.gazprom.init.shareTools($room);
      
      // attach room navigators to rooms (sideways scrollers)
      Drupal.gazprom.init.roomNavigators($room);
      
      // if present, hookup scrolling-list items (i.e. home page features)
      $room.find('.scrolling-list').scrollingList({
        fluidImageSafeOffset: {top: 88, left:0, right: 0, bottom: 0}
      });
      
      // add and configure parallax scrolling layers
      if (Drupal.gazprom.settings[Drupal.gazprom.mode].parallax) {
      $room.find('.scrolling-list.parallax').once('parallax', function() {
        // create extra scrolling parallax layer with only the text from the .scrolling-list-items
        // and then make it spread apart (see marginBottom CSS below) so that it can be scrolled at a
        // different speed (faster) than the background images which will be left inside the original .scrolling-list-items 
        var $lowerLevel = $room.find('.scrolling-list-items');
        $lowerLevel.after($lowerLevel.clone());
        var $upperLevel = $lowerLevel.next('.scrolling-list-items');
        $upperLevel.addClass('duplicates');

        $upperLevel.addClass('upper-level').css({position: 'absolute', top: 0, left: 0, right: 0, zIndex: 0});

        $lowerLevel.find('ul li > div.list-row').children().not('div.views-field-field-background-image').remove(); // remove text, leave background
        $upperLevel.find('ul li > div.list-row').children().filter('div.views-field-field-background-image').remove(); // remove background, leave text
        $upperLevel.css('overflow', 'visible');

        var speedMultiple = 4;
        
        $(window).bind('resizeComplete.scrollingList', function() {
          var rowHeight = $upperLevel.parent().height();
          $upperLevel.css({
            height: rowHeight
          });
          var $items = $upperLevel.find('.item-list li');
          $items.css('height', rowHeight);
          $items.css({
            height: rowHeight,
            marginBottom: (rowHeight * speedMultiple) - rowHeight
          });
          $upperLevel.find('li').css('marginBottom', (rowHeight * speedMultiple ) - rowHeight); // space each row (table) apart from each other by an appropirate amount
        }).trigger('resizeComplete.scrollingList');

        var $container = $(this);
        $container.find('.scrolling-list-items.duplicates')
          .after('<div class="parallax-layer arrows layer-1-1 large">')
          .after('<div class="parallax-layer arrows layer-1-2 medium">')
          .after('<div class="parallax-layer arrows layer-1-3 small">')
          .after('<div class="parallax-layer arrows layer-1-4 xsmall">')
          .after('<div class="parallax-layer logos layer-2-1 large">')
          .after('<div class="parallax-layer logos layer-2-2 medium">')
          .after('<div class="parallax-layer logos layer-2-3 small">')
          .after('<div class="parallax-layer layer-depth">');
          
        $container.find('.scrolling-list-items:not(.duplicates)').parallax(
          [{
              layer: $upperLevel,
              selector: $upperLevel.selector,
              label: 'text',
              speed: speedMultiple
            },
            {
              layer: $container.find('.parallax-layer.layer-1-1'),
              selector: '.parallax-layer.layer-1-1',
              speed: speedMultiple / 1.25,
              adjustHeight: true,
              label: 'arrows-large',
              zIndex: -8
            },
            {
              layer: $container.find('.parallax-layer.layer-1-2'),
              selector: '.parallax-layer.layer-1-2',
              speed: speedMultiple / 1.75,
              adjustHeight: true,
              label: 'arrows-medium',
              zIndex: -8
            },
            {
              layer: $container.find('.parallax-layer.layer-1-3'),
              selector: '.parallax-layer.layer-1-3',
              speed: speedMultiple / 2,
              adjustHeight: true,
              label: 'arrows-small',
              zIndex: -8
            },
            {
              layer: $container.find('.parallax-layer.layer-1-4'),
              selector: '.parallax-layer.layer-1-4',
              speed: speedMultiple / 3,
              adjustHeight: true,
              label: 'arrows-xsmall',
              zIndex: -8
            },
            {
              layer: $container.find('.parallax-layer.layer-2-1'),
              selector: '.parallax-layer.layer-2-1',
              speed: speedMultiple / 1.5,
              adjustHeight: true,
              label: 'logos-large',
              zIndex: -7
            },
            {
              layer: $container.find('.parallax-layer.layer-2-2'),
              selector: '.parallax-layer.layer-2-2',
              speed: speedMultiple / 2.5,
              adjustHeight: true,
              label: 'logos-med',
              zIndex: -7
            },
            {
              layer: $container.find('.parallax-layer.layer-2-3'),
              selector: '.parallax-layer.layer-2-3',
              speed: speedMultiple / 3.5,
              adjustHeight: true,
              label: 'logos-small',
              zIndex: -7
            },
            {
              layer: $container.find('.parallax-layer.layer-depth'),
              selector: '.parallax-layer.layer-depth',
              speed: speedMultiple / 40,
              adjustHeight: false,
              label: 'depth',
              zIndex: -6
            }
          ]);
      });
        
      }
      
      // configure inline-content-cyclers (see the Behind The Site page)
      $room.find('div.inline-content-cycler').inlineContentCycler();
      
      // configure webforms
      this.webform($room);
      
      // connect up anchors to click handlers
      this.anchorHandlers($room);
      
      // text-shadow pollyfill
      // https://github.com/heygrady/textshadow
      if (!Modernizr.textshadow) {
        $('#front-features .views-field-summary').textshadow();
        $('.expand-top h1').textshadow();
        $('.expand-top h2').addClass('testing').textshadow();
        // @TODO these look like crap
      }
      
      // finish room initialization
      if (Drupal.gazprom.build.inBuildMode && !Drupal.gazprom.singlePageMode && settings.stage2 == 'deferred') {
        $room.bind('initStage2', function() {
          Drupal.gazprom.init.roomStage2($room);
          $room.unbind('initStage2');
        });
      } else {
        Drupal.gazprom.init.roomStage2($room);
      }
      
      return;
      
    },
    roomStage2: function($room) {
      // finish initializing the room. This steps are more like building the room
      // as content is likely to be added via AJAX calls
  
      // if present, initialize/build a photo gallery
      Drupal.gazprom.photoGallery($room);

      // if present, hookup microsite
      Drupal.gazprom.init.microsite($room);
      
      // if present, hookup interactive map
      // PLEASE NOTE: The map is now pulled in via an iframe with the path /gazprom/world-map/iframe
      // Please see the gazprom_world_map.module
      
      // if present, hookup Views UI
      $room.find('.management-tabs .view').viewsSelector();
      
      // if present, hookup Timline UI
      Drupal.gazprom.init.timeline($room);
      
      // setup content pagination (must come after step-width & viewsSelector initializations)
      // first-room pages
      $room.find('.paginate-content-inside .field-name-body .field-item').addClass('paginate-content');
      $room.filter('.first-room').find('.paginate-content').not('.paginate-content-processed').filter(function() {return $(this).find('.paginate-content').length === 0;})
      .addClass('paginate-content-processed')
      .paginateContent({
        prevButtonText: '',
        nextButtonText: Drupal.t('Read'),
        middleText: '',
        adjustContainer: false,
        containerHeight: 'auto'
      });
      // regular pages
      $room.find('.paginate-content').not('.paginate-content-processed').filter(function() {return $(this).find('.paginate-content').length === 0;})
      .addClass('paginate-content-processed')
      .paginateContent({
        prevButtonText: '',
        nextButtonText: Drupal.t('Read'),
        middleText: '',
        adjustContainer: false,
        containerHeight: 'auto'
      });
      // country pages
      $room.find('.paginate-country-information-to-overlay')
        .find('.field-name-field-location-information .field-item, .field-name-field-country-info .field-item').addClass('paginate-content-to-overlay');
      $room.find('.paginate-content-to-overlay').not('.paginate-content-processed')
      .addClass('paginate-content-processed')
      .paginateContent({
        prevButtonText: '',
        nextButtonText: Drupal.t('Read'),
        middleText: '',
        adjustContainer: false,
//        containerHeight: 200,
        containerHeight: 'auto',
        containerWidth: 'auto',
        externalHandoff: true,
        externalFn: function() {
          // this element is added in the taxonomy-term template file
          var pathOfCountry = $(this).closest('.content').find('.path-to-content').text(); // @TODO is .content strong enough for this?
          Drupal.gazprom.gotoHref(pathOfCountry + '?overlay=true', {openInOverlay: true});
        }
      });
      // content inside management tabs
      // These are tricky since they are likely not visible and quicktabs also seems to be effing with widths?
      // pageinateContent has some tricks up it's sleeves to deal with this.
      $room.find('.management-tabs li .views-field-body .field-content').not('.paginate-content-processed').each(function() {
        var $container = $(this);
        $container.addClass('paginate-content-to-overlay')
        .paginateContent({
          prevButtonText: '',
          nextButtonText: Drupal.t('Read'),
          middleText: '',
          adjustContainer: true,
          containerHeight: 'auto',
          containerWidth: function() {
            // Messy, but this seems to be the best way to deal with the $container's width. We need to know the 
            // .. width because the $container (and it's parents) are possibly display:none and $.getHiddenDimensions()
            // .. seem to want to work for quicktabs (give either 0 or a width that is smaller than it should be)
            return $container.closest('.step-width').innerWidth() - parseInt($container.closest('ul').css('margin-left')) - 60;
          },
          externalHandoff: true,
          externalFn: function() {
            var pathOfContent = $(this).closest('li.views-row').find('.content-link a').attr('href'); // this is inserted by the CEO Message View
            if (pathOfContent) Drupal.gazprom.gotoHref(pathOfContent + '?overlay=true', {openInOverlay: true});
          }
        });
        //$message.prependTo($originalContainer);
      })
      .addClass('paginate-content-processed');
      
      // configure variable scrollers (i.e. news items) -- MUST come after step-width initialization
      $room.find('.variable-scroller.grid-scroller').not('.variable-scroller-processed').variableScroller({
        viewInnerSelector: '.view-content table.views-view-grid tbody',
        rowSelector: '.view-content table.views-view-grid tr',
        itemSelector: '.view-content table.views-view-grid tbody td',
        scrollButtons: false,
        usePager: true
      }).addClass('variable-scroller-processed');
      $room.find('.variable-scroller.timeline-scroller').not('.variable-scroller-processed').variableScroller({
        viewInnerSelector: '.view-content ul.item-list',
        itemSelector: '.view-content ul.item-list li',
        usePager: false,
        scrollButtons: true
      }).addClass('variable-scroller-processed');
      $room.find('.variable-scroller').not('.variable-scroller-processed').variableScroller({
        viewInnerSelector: '.view-content ul.item-list',
        itemSelector: '.view-content ul.item-list li',
        usePager: false,
        scrollButtons: true
      }).addClass('variable-scroller-processed');

      // upgade background images 
      $room.find('img.fancy-background-image').upgradeBackgroundImages(); // local to this room
      //$room.closest('.content-floor-wrapper').find('.relative-wrapper img.fancy-background-image').upgradeBackgroundImages(); // relocated for the entire floor
      
      // Check if there area any elements in room that need fadeIn animation.
      // (Likley from the insertContent() function).
      if ($room.find('.fadeIn').length > 0) {
        $room.find('.fadeIn').animate({opacity: 1}, {
          duration: 100,
          complete: function() {
            $(this).removeClass('fadeIn');
          }
        });
      }
      
    },
    anchorHandlers: function($context) {
      /*
       * Connect the content's anchors to various handlers.
       * Typically called by init.room() but can also be called by various
       * AJAX loaders (i.e. variable scrollers)
       */
 
      // @TODO testing
      // configure tooltip popups
      $context.find('XXXa[title]:not(.tooltip-processed)').tooltip({
        effect: 'slide',
        position: 'center left',
        predelay: 100
      }).dynamic({}).addClass('tooltip-processed');

      // attached photos (i.e. Country pages)
      $context.find('.view.contains-photos a').unbind('click').bind('click.viewPhoto', function(e) {
        e.preventDefault();
        Drupal.gazprom.gotoHref($(this).attr('href'), {viewPhoto: true});
      }).addClass('no-hijax').addClass('photo-click');

      // external links
      $context.find('a[href^="http://"], a[href^="https://"]')
        .not('[href^="http://' + window.location.host + '"], [href^="https://' + window.location.host + '"]')
        .attr("target", "_blank").addClass('external-link gazprom-click-no');
      // exclude links with target window reference
      $context.find('a[target]').addClass('no-hijax');
      
      // mailto links
      $context.find('a[href^="mailto:"]').addClass('mailto-link gazprom-click-no');
      
      // file links
      $context.find('.field-type-file a').addClass('no-hijax').attr('target', '_blank');
      
      // deal with home page globe link
      $context.find('XXX.world-link a').once('gazprom-click', function() {
        var $link = $(this);
        var $overlay = $link.siblings('.world-overlay');
        var $container = $link.parent();
        var $hoverItems = $($link, $overlay, $container);
        $container.hoverIntent({
          over: function() {
            $overlay.fadeIn(200);
          },
          out: function() {
            $overlay.fadeOut(200);
          },
          timeout: 1000
        }); // @TODO switch to Tooltip?

        $context.find('.world-overlay a').unbind('click').bind('click', function(e) {
          e.preventDefault();
          Drupal.gazprom.click_handlers.worldMapClick($(this))
          // @TODO is this poorly done?
        }).addClass('gazprom-click-processed');
      });
      $context.find('div.world-link:not(.hover-processed)').hoverIntent({
          over: function() {
            $(this).find('.world-overlay').fadeIn(200);
          },
          out: function() {
            $(this).find('.world-overlay').fadeOut(200);
          },
          timeout: 1000
        }).addClass('hover-processed'); // @TODO switch to Tooltip?
        

      // the handlers below are all for multiPageMode and aren't needed in singlePageMode
      if (Drupal.gazprom.singlePageMode) return;
      
      $context.find('XXXXX.breadcrumb a').once('gazprom-click', function() {
        $(this).hijax();
      });

      $context.find('XXXXnav.third-navigation a').once('gazprom-click', function() {
        $(this).bind('click.gazprom', Drupal.gazprom.click_handlers.room);
      });
      
      
      // handle links that need to stay be within the room (i.e. Countries page)
      $context.find('XXXX.open-within-room a').once('gazprom-click', function(e) {
        //$(this).bind('click.gazprom', Drupal.gazprom.click_handlers.room(e));
        $(this).bind('click.gazprom', function(e) {
          e.preventDefault();
          var $anchor = $(this);
          var href = $anchor.attr('href');
          var $room = $anchor.closest('.content-room-wrapper')
          Drupal.gazprom.gotoHref(href, {openWithinRoom: true, roomID: $room.attr('id')}); // newWindowTitle?

        });
      })
      
      // exclude quicktabs links
      $context.find('ul.quicktabs-tabs a').addClass('no-hijax');
      
      // bind up all remaining anchors to our custom hijax routines
      $context.find('a').not('a.no-hijax, a.gazprom-click-no, a.gazprom-click-processed').hijax();
      
      // If not already done, bind up second-level navigation for this floor
      $context.closest('.content-floor-wrapper').find('nav.second-navigation ul.menu a').not('hijaxed').hijax();
      
      return;
    },
    printTools: function($context) {
      
      var contentSelector = 'h1.head-title, .print-content h2, .print-content h3, .print-content .field-name-field-image .field-item, .print-content .field-name-body .field-item';
      $context.find('.print-control, .page-tool.print').printContent({
        containerSelector: '.content-room-wrapper', // @TODO could be .content-wrapper also
        contentSelector: contentSelector
      });
      $context.find('.overlay-tool.print').printContent({
        containerSelector: '.content-wrapper',
        contentSelector: [
          'h1.head-title',
          '.content-main h2, .content-main h3',
          '.content-main .field-name-field-image .field-item',
          '.content-main .field-name-body .field-item',
          '.content-main .field-name-field-country-info .field-item',
          '.content-main .field-name-field-location-information .field-item',
          '.content-main .field-name-field-date-event'
        ],
        excludeSelector: [
          '.inline-content-cycler'
        ]
      });
    },
    shareTools: function($context) {
      
      // hookup tooltip for page content share tool (at bottom of basic page)
      $context.find('.page-tools a.share, .photo-control.share').removeAttr('title')
        .tooltip({
          tipClass: 'page-tool-tip',
          position: 'center left',
          relative: true,
          effect: 'fade',
          predelay: 100,
          delay: 500,
          offset: [0,3],
          onShow: function() {
            this.getTrigger().addClass('hover');
          },
          onBeforeHide: function() {
            this.getTrigger().removeClass('hover');
          }
        });
        
      // attach handlers to share-links (a.share-link)
      $context.find('.share-links a.share-link').unbind('click.shareTools').bind('click.shareTools', function(e) {
        e.preventDefault();
        var $a = $(this), service;
        if ($a.hasClass('share-facebook')) {
          service = 'facebook';
        } else if ($a.hasClass('share-twitter')) {
          service = 'twitter';
        } else if ($a.hasClass('share-google')) {
          service = 'google';
        }else if ($a.hasClass('share-livejournal')) {
          service = 'livejournal';
        }
        if (service) {
          Drupal.gazprom.shareThis(service);
        }
        return;
      }).addClass('no-hijax');
      
        
    },
    roomNavigators: function($room) {
      var $floor = $room.closest('.content-floor-wrapper'),
        $secondNavigation = $floor.find('nav.second-navigation');
      if ($floor.length == 0 || $secondNavigation.length == 0) return;
      
      var $roomsNavItem = $room.data('nav-second-anchor');
      var roomNavPos = $secondNavigation.find('ul.menu li a').index($roomsNavItem),
        totalNavCount = $secondNavigation.find('ul.menu li a').length,
        $prevLink, $nextLink;
        
      if (roomNavPos > 0) {
        $prevLink = $secondNavigation.find('ul.menu li a').eq(roomNavPos - 1);
        _prevNavigator($room, $prevLink);
      }
      if (roomNavPos < totalNavCount - 1) {
        $nextLink = $secondNavigation.find('ul.menu li a').eq(roomNavPos + 1);
        _nextNavigator($room, $nextLink);
      }
      
      function _nextNavigator($room, $anchor) {
        $room.append('<div class="room-navigator-next room-navigator"></div>')
        $room.find('.room-navigator-next').bind('click.gazprom', function(e) {
          $anchor.trigger('click');
        });
      }
      function _prevNavigator($room, $anchor) {
        $room.append('<div class="room-navigator-previous room-navigator"></div>')
        $room.find('.room-navigator-previous').bind('click.gazprom', function(e) {
          $anchor.trigger('click');
        });
      }
      
    },
    microsite: function($room) {
      var $microsite = $room.find('.stage #gazprom-microsite');
      if ($microsite.length == 0 ) return;

      // see also the microsite.js code in the microsite module. That handles actual SWF insertion
      if (!Drupal.microsite) {
        //console.log('Drupal.microsite JS object not present');
        return;
      }
      
      // remove sideways room navigators
      $room.addClass('no-room-navigation');
      var $stage = $room.find('.stage');
      
      $microsite.once('gazprom-microsite', function() {
        var $room = $microsite.closest('.content-room-wrapper');
        if ($room.length == 0) return; // something went wrong
        // initialize the Flash object, which starts loading code
        function _initFlashPlayer() {
          if (Drupal.microsite.installed != true) {
            setTimeout(function(){
              _initFlashPlayer();
            }, 500);
          } else {
            Drupal.microsite.initFlashPlayer();
          }
        }
        //_initFlashPlayer();
        
        $room.unbind('room-activation.microsite').bind('room-activation.microsite', function() {
          if (Drupal.microsite.installed == true) {
            // was installed at startup (see Drupal.microsite.behaviors:attach)
            //Drupal.microsite.initFlashPlayer();
          } else {
            Drupal.microsite.install({base: Drupal.settings.microsite.pathToAssets, language: Drupal.settings.microsite.language}, {
              onFailure: function(e) {
                $stage.find('.no-flash-content').show();
                $stage.find('.no-flash-content').find('.variable-scroller-processed').trigger('update');
              },
              onSuccess: function(e) {
                Drupal.microsite.initFlashPlayer(e, $room.find('.stage'));
              }
            });
          }
        }).unbind('room-deactivation.microsite').bind('room-deactivation.microsite', function() {
          if (Drupal.microsite.installed == true) {
            //Drupal.microsite.stopFlashPlayer();
          }
          Drupal.microsite.remove();
        });
        
      });
      
      
    },
    webform: function($room) {
      var $webform = $room.find('form.webform-client-form');
      if ($webform.length == 0) return;

      if (!$.fn.ajaxForm) return; // singlePageMode? error?
      
      $webform.addClass('hijacked-webform').ajaxForm({
        beforeSerialize: function($form, options) { 
          $form = $form;
//          return false;
// return false to cancel submit                  
        },
        beforeSubmit: function(arr, $form, options) {
//          arr = arr;
            // The array of form data takes the following form: 
            // [ { name: 'username', value: 'jresig' }, { name: 'password', value: 'secret' } ] 

            //return false;
            // return false to cancel submit              
            Drupal.gazprom.utility.setBusy();
        },
        success: function showResponse(result, statusText, xhr, $form)  { 
          result = result;
          var $newContent = $(result).find('.ajax-form-wrapper').children();
          if ($newContent.length == 0) {
            $newContent = $(result).find('.webform-confirmation, .webform-client-form');
          }
          
          if ($newContent.length > 0) {
            $room.find('.ajax-form-wrapper').fadeOut(500, function($newContent) {
              _insertNewContent();
            });
          }
          return;
          
          function _insertNewContent() {
            $room.find('.ajax-form-wrapper').empty().append($newContent).fadeIn(500);
            $webform = $room.find('form.webform-client-form');
            Drupal.attachBehaviors($room);
            //Drupal.gazprom.init.room($room);
            $room.trigger('room-activation.webform');
            Drupal.gazprom.utility.clearBusy();
          }
        }
      });
      
      // 
      
      // must prevent tabbing to form input until room is active
      $room.unbind('room-activation.webform').bind('room-activation.webform', function() {
        $webform.find('input, textarea').removeAttr('disabled');
        $webform.find('input, textarea').first().focus();
      }).unbind('room-deactivation.webform').bind('room-deactivation.webform', function() {
        $webform.find('input, textarea').attr('disabled', 'disabled');
      });
      
      if ($room.is('.active-room')) {
        $room.trigger('room-activation.webform');
      } else {
        $room.trigger('room-deactivation.webform');
      }
    },
    langDropdown: function($context) {
      if (typeof $context == 'undefined') {
        $context = $('#header');
      }
      
      var $selectElement = $context.find('#lang-dropdown-form select');
      if ($selectElement.length == 0) return;
      
      $selectElement.selectbox({
        onOpen: function(selectbox) {
          var $selectbox = $('#' + selectbox.id).siblings('.sbHolder');
          $selectbox.removeClass('closed').addClass('opened');
        },
        onClose: function(selectbox) {
          var $selectbox = $('#' + selectbox.id).siblings('.sbHolder');
          $selectbox.removeClass('opened').addClass('closed');
        }
      });
      
      // hide currently selected option
      var $selectbox = $selectElement.siblings('.sbHolder');
      var textOfSelected = $selectbox.find('a.sbSelector').text();
      $selectbox.find('ul li a:contains("' + textOfSelected + '")').hide();
      
      if (!Drupal.gazprom.singlePageMode) {
        // hijack the select so we can control the result
        $selectElement.unbind('change').bind('change.langDropDown', function(e) {
            e.stopImmediatePropagation()
            e.preventDefault();
            
            //var $langSwitcherList = $('.active-room').find('ul.language-switcher-locale-url');
            var $langSwitcherList = Drupal.gazprom.activeRoom.find('ul.language-switcher-locale-url');
            var lang = this.options[this.selectedIndex].value, href;
            if ($langSwitcherList.length == 0) {
              href = $(this).parents('form').find('input[name="' + lang + '"]').val();
            } else {
              href = $langSwitcherList.find('li.' + lang + ' a').attr('href');
              if (!href) {
                href = $(this).parents('form').find('input[name="' + lang + '"]').val();
              }
            }
            document.location.href = href;

            return false;
        });
      }
      
      
    },
    timeline: function($context) {
      var $timeline = $context.find('.timeline-container');
      var $events = $context.find('.timeline-events');
      if ($timeline.length == 0 || $events.length == 0) return;
      
      var $timeline_years = $timeline.find('ul li');

      // bind handlers for the timeline
      $timeline_years.unbind('click').bind('click.timeline', function() {
        var $this = $(this);
        var year = $this.text();
        $timeline_years.filter('.active').removeClass('active');
        $this.addClass('active');
        _loadYear(year);
      });
      $timeline_years.first().trigger('click.timeline');

      function _loadYear(year) {

        if ($events.children().length > 0) $events.children().fadeOut(200);
        
        var view_name, display_id;
        if (false) {
          var viewIDsObj = Drupal.gazprom.utility.getViewIDs($events.find('.view:first'));
          if (!viewIDsObj) return; // something went wrong;
          view_name = viewIDsObj.view_name;
          display_id = viewIDsObj.view_display_id;
        } else {
          view_name = 'history';
          display_id = 'events';
        }
        
        var href = Drupal.gazprom.utility.getViewsAjaxPath();
              //+ '?view_name=' + view_name + '&view_display_id=' + display_id + '&field_date_event=' + year;

        $.getJSON(href, {view_name: view_name, view_display_id: display_id, view_args: year}, function(result) {

          var data = result[1];
          
          if ($('html').is('.ie8, .ie7, .ie6') && Drupal.gazprom.useInnerShiv) {
            $events.empty().append(innerShiv(data.data)); // @TODO is innerShiv still needed with our version of jQuery?
          } else {
            $events.empty().append(data.data);
          }
          $events.find('.view').viewsSelector({hideMenuIfOnlyOne: true});
          return;
        });
      }
    }

  }
})(jQuery, Drupal);

(function($, Drupal){
/**
 * Function related to scrolling
 */
  Drupal.gazprom.scroll = {
    scrollingInEffect: false,
    waypointsOff: false,
    scrollerSelector: '#scroller',
    $scroller: null,
    sensitivity: 250, // primarily for testing of scroll settle (see snapTo)
    snapTo: true,
    wheelSwipe: false,
    wheelSwipeThreshold: 5,
    lockWheelToFloor: true,
    snapToDuration: 500, //Drupal.gazprom.scrollSpeed,  // 500,
    init: function() {
      
      if (!this.$scroller) this.$scroller = $(this.scrollerSelector);
      
      var that = this;
      
      // Setup debounce functions that will toggle the inEffect switch automatically
      // (works for automated scrolling for for user controlled scrolling)
      // (needs to be called when build is done)
      
      this.$scroller.bind('scroll.scroll-begin', $.debounce(this.sensitivity, true, this._scrollActive));
      this.$scroller.bind('scroll.scroll-end', $.debounce(this.sensitivity, false, this._scrollSettled));
      
      // setup mousewheel handler to determine if mousemovement is more like a a swipe or a scroll
      this.swipeTriggeredDb = $.debounce( 50, this.swipeTriggered);
      this.$scroller.bind('mousewheel', this.mousewheel);

      this.scrollingInEffect = false;
      
    },
    mousewheel: function (e, delta, deltaX, deltaY) {
        var that = Drupal.gazprom.scroll;
        if (Drupal.gazprom.scrollIsActive) {
          // a system generated scroll is happening, so cancel normal response to mouse wheel
          e.preventDefault();
          return false;
        }
        if (Math.abs(delta) > that.wheelSwipeThreshold && that.wheelSwipe ) {
          // appears to be a large motion, so treat it like a swipe
          e.preventDefault();
          that.swipeTriggeredDb(deltaX, deltaY, that);
          return false;
        }
        if (that.lockWheelToFloor &&
          ((deltaY < 0 && Drupal.gazprom.activeFloor.outerHeight() + Drupal.gazprom.activeFloor.offset().top < Drupal.gazprom.winHeight)
            || (deltaY > 0 && Drupal.gazprom.activeFloor.offset().top > 0))) {
          // scrolled to limits of a floor with mousewheel .. so stop them! (per client request)
          e.preventDefault();
          if (deltaY > 0) {
            that.sync(Drupal.gazprom.activeFloor, {vDuration: 100, toBottom: false});
            $.doTimeout('reset_sticky', 500, function(){
              Drupal.gazprom.utility.toggleNavSticky(Drupal.gazprom.activeFloor.find('nav.second-navigation'), 'sticky');
            });
          } else {
            that.sync(Drupal.gazprom.activeFloor, {vDuration: 100, toBottom: true});
          }
          Drupal.gazprom.scrollIsActive = true;
          $.doTimeout(1000, function() {
            Drupal.gazprom.scrollIsActive = false;
          });
          return false;
        }
        // let normal scroll handle the event
        return true;

    },
    floorWaypoints: function($floor) {
      if (Drupal.gazprom.singlePageMode) return;
      if (!this.$scroller) this.$scroller = $('#scroller');
      
      var that = this;

      // attach a waypoint at the bottom of the floor
      $floor.append('<div class="bottom-waypoint">');
      var $floorBottom = $floor.find('.bottom-waypoint');
 
      // attach our waypoint handlers to the $floor provided. Each floor gets multiple waypoint handlers

      // top of floor is touching bottom of main nav
      // .. so consider sticking/unsticking second-nav
      $floor.waypoint(function(e, direction) {
        e.stopImmediatePropagation(); 
        if (Drupal.gazprom.build.inBuildMode || that.waypointsOff == true || $(this).hasClass('waypoint-off')) {
          //console.log('top triggered, but off:' + $floor.find('.content-room-wrapper:first').attr('id'));
          return false
        } 
        //console.log('top triggered: ' + $floor.find('.content-room-wrapper:first').attr('id'));
        Drupal.gazprom.scroll.atWaypoint($floor, 'top', direction);
        return false;
      }, {
        context: this.scrollerSelector,
        continuous: false,
        onlyOnScroll: true,
        offset: $('#header').outerHeight()
      });
      
      // bottom of floor is at 25% from the top of window
      // .. so consider sticking/unsticking second-nav
      $floorBottom.waypoint(function(e, direction) {
        e.stopPropagation(); // @TODO can't remember why this is needed
        if (Drupal.gazprom.build.inBuildMode || that.waypointsOff == true || $(this).hasClass('waypoint-off')) {
          //console.log('bottom triggered, but off:' + $floor.find('.content-room-wrapper:first').attr('id'));
          return;
        }
        //console.log('bottom triggered: ' + $floor.find('.content-room-wrapper:first').attr('id'));
        Drupal.gazprom.scroll.atWaypoint($floor, 'bottom', direction);
      }, {
        context: this.scrollerSelector,
        //offset: '25%',
        offset: $('#header').outerHeight() * 4,
        onlyOnScroll: true,
        continuous: false
      });
      
      if (this.snapTo) {
        $floor.prepend('<div class="snapTo-waypoint">'); // special waypoint DIV at top of floor
        var $floorSnapTo = $floor.find('.snapTo-waypoint');
        $floorSnapTo.waypoint(function(e, direction) {
          e.stopPropagation();
          var that = Drupal.gazprom.scroll;
          if (Drupal.gazprom.build.inBuildMode || Drupal.gazprom.scrollIsActive || that.waypointsOff == true || $(this).hasClass('waypoint-off')) {
            //console.log('snapTo triggered, but off:' + $floor.find('.content-room-wrapper:first').attr('id'));
            return false
          } 
          if (Drupal.gazprom.scrollIsActive || that.waypointsOff) return; // don't snap if this is a site generated scroll
          if ($(this).hasClass('waypoint-off')) return;
          //console.log('snapTo triggered:', $(this).parent(), direction);
          
          function _snapIfDone() {
            if (that.scrollingInEffect) {
              // scroll hasn't settled yet, we got called too early
              $.doTimeout('checkIfDone', that.sensitivity + 10,  _snapIfDone);
            } else {
              _snapTo();
            }
          }
          _snapIfDone();
          
          function _snapTo() {
            //console.log('snapTo triggered: ' + $floor.find('.content-room-wrapper:first').attr('id') + ', direction: ' + direction);
            if (direction == 'down' && $floor.is('.active-floor')) {
              that.snapToFloor('next'); // this waypoint function was triggered with the incoming floor (scrolling down into floor)
            } else if ($floor.is('.active-floor')) {
              that.snapToFloor('prev'); // this waypoint function was triggered with the top of the outgoing floor (scrolling up away from floor)
            }
          }
        }, {
          context: this.scrollerSelector,
          offset: '50%', // top of floor has hit the 50% marker (50% down from top of window)
          onlyOnScroll: true,
          continuous: false
        });
                
      }
      
    },
    atWaypoint: function ($floor, whichEnd, direction) {
      /**
       * atWaypoint gets triggered as floors scroll in or out of view
       **/
      
      // if the scrolling is because of scrollToFloor then we want to ignore all 
      // activation waypoints, except the floor we are scrolling to (scroll-destination) and the
      // floor we are scrolling away from (active-floor)
      if (Drupal.gazprom.scrollIsActive && !$floor.hasClass('scroll-destination') && !$floor.is('.active-floor')) {
        return;
      }
      // don't bother during build process (false triggers)
      if (Drupal.gazprom.build.inBuildMode == true) return;
      
      var $secondNav = $floor.find('nav.second-navigation');
      var $room;
      if ($secondNav.length > 0) {
        var $activeAnchor = $secondNav.find('ul.menu li > a.active');
        $room = $('#' + Drupal.gazprom.utility.urlToId($activeAnchor.attr('href')));
      } else {
        // probably the home page
        $room = $floor.find('.content-room-wrapper:first');
      }
      
//      if ($floor.hasClass('scroll-destination')) console.log('scroll-destination on floor of: ' + $room.attr('id'));
//      if ($floor.hasClass('active-floor')) console.log('active-floor on floor of: ' + $room.attr('id'));
      var destinationData = Drupal.gazprom.utility.findDirectoryEntry($room.attr('id'));

      var action;
      if (whichEnd == 'top' && direction == 'down' && (!Drupal.gazprom.scrollIsActive || $floor.hasClass('scroll-destination'))) {
        //console.log('activate: #' + $room.attr('id') + ', whichEnd: ' + whichEnd + ', direction: ' + direction);
        action = 'activate';
      } else if (whichEnd == 'bottom' && direction == 'up') {
        //console.log('activate: #' + $room.attr('id') + ', whichEnd: ' + whichEnd + ', direction: ' + direction);
        action = 'activate';
        //action = 'stickit';
      } else if (whichEnd == 'top' && direction == 'up') {
        //console.log('deactivate: #' + $room.attr('id') + ', whichEnd: ' + whichEnd + ', direction: ' + direction);
        action = 'deactivate';
      } else if (whichEnd == 'bottom' && direction == 'down') {
        //console.log('deactivate: #' + $room.attr('id') + ', whichEnd: ' + whichEnd + ', direction: ' + direction);
        action = 'deactivate';
      } else {
        //console.log('unknown waypoint situation');
      }
      
      if (action == 'stickit') {
        Drupal.gazprom.utility.toggleNavSticky($secondNav, 'sticky'); // incase floor is still active, but nav was unstuck
      }
      if (action == 'unstickit'){
        Drupal.gazprom.utility.toggleNavSticky($secondNav, 'unsticky');
      }
      if (action == 'activate') {
        Drupal.gazprom.gotoRoom($room, {skipScroll: true});
        Drupal.gazprom.utility.toggleNavSticky($secondNav, 'sticky'); // incase floor is still active, but nav was unstuck
      }
      if (action == 'deactivate') {
        Drupal.gazprom.utility.toggleNavSticky($secondNav, 'unsticky');
        Drupal.gazprom.deactivateRoom($room);
      }
    },
    swipeTriggered: function(deltaX, deltaY, that) {
      if (typeof that == 'undefined') that = this;
      //console.log('swipe: ', deltaX, deltaY);
      if (deltaY > 0) {
        // scrolling up
        that.snapToFloor('prev');
      } else if (deltaY < 0) {
        // scrolling down
        that.snapToFloor('next');
       } else if (deltaX > 0) {
        // scrolling right
        //that.snapToRoom($('.content-floor-wrapper.active-floor'), 'next');
        that.snapToRoom(Drupal.gazprom.activeFloor, 'next');
      } else if (deltaX < 0) {
        // scrolling left
        //that.snapToRoom($('.content-floor-wrapper.active-floor'), 'prev');
        that.snapToRoom(Drupal.gazprom.activeFloor, 'prev');
      }
      return false;
      
    },
    snapToHref: function (href) {
      if (!href) return;
      
      Drupal.gazprom.gotoHref(href, {catchUpDuration: this.snapToDuration, duration: this.snapToDuration});
    },
    snapToFloor: function (direction) {
      //var $currentFloor = $('.content-floor-wrapper.active-floor'), $newFloor;
      var $currentFloor = Drupal.gazprom.activeFloor, $newFloor;
      if (direction == 'prev') {
        $newFloor = $currentFloor.prev('.content-floor-wrapper:not(.placeholder)');
      } else {
        $newFloor = $currentFloor.next('.content-floor-wrapper:not(.placeholder)');
      }
      if ($newFloor.length > 0) {
        var $room = $newFloor.find('.content-room-wrapper.active-room');
        if ($room.length == 0) $room = $newFloor.find('.content-room-wrapper.previously-active');
        if ($room.length == 0) $room = $newFloor.find('.content-room-wrapper:first');

        if (!$room.is('.active-room')) {
          Drupal.gazprom.gotoRoom($room, {catchUpDuration: this.snapToDuration, duration: this.snapToDuration});
        } else {
          Drupal.gazprom.utility.scrollToRoom($room, {catchUpDuration: this.snapToDuration, duration: this.snapToDuration});
        }
      } else {
        // Floor hasn't been put in DOM yet, so we need to find the URL and goto it (which will load & insert it)
        var $newNavItem;
        if (direction == 'prev') {
          if ($('#navigation-main ul.menu li a:first').is('.active')) {
            $newNavItem = $('#go-home');
          } else {
            $newNavItem = $('#navigation-main ul.menu li a.active').closest('li').prev('li').find('a');
          }
        } else {
          if ($('.content-floor-wrapper:first').is('.active-floor') && ($('#navigation-main ul.menu li a.active').length == 0)) {
            $newNavItem = $('#navigation-main ul.menu li a:first');
          } else {
            $newNavItem = $('#navigation-main ul.menu li a.active').closest('li').next('li').find('a');
          }
        }
        this.snapToHref($newNavItem.attr('href'));
      }
      
    },
    snapToRoom: function($floor, direction) {
      if ($floor.length == 0) return;
      var $room = $floor.find('.content-room-wrapper.active-room'), $newRoom;
      if ($room.length == 0) $room = $floor.find('.content-room-wrapper:first');
      if (direction == 'prev') {
        $newRoom = $room.prev('.content-room-wrapper:not(.placeholder)');
      } else {
        $newRoom = $room.next('.content-room-wrapper:not(.placeholder)');
      }
      
      if ($newRoom.length > 0) {
        Drupal.gazprom.gotoRoom($newRoom, {catchUpDuration: this.snapToDuration, duration: this.snapToDuration});
      } else {
        // Room hasn't been put in DOM yet, so we need to find the URL and goto it (which will load & insert it)
        var $newNavItem;
        if (direction == 'prev') {
          $newNavItem = $floor.find('.second-navigation ul.menu li a.active').closest('li').prev('li').find('a');
        } else {
          $newNavItem = $floor.find('.second-navigation ul.menu li a.active').closest('li').next('li').find('a');
        }
        this.snapToHref($newNavItem.attr('href'));
      }
    },
    sync: function($floor, options) {
      var settings = $.extend({
        horzOnly: false,
        toBottom: false,
        vDuration: 0,
        hDuration: 0
      }, options);
      if (typeof $floor == 'undefined') {
        $floor = Drupal.gazprom.activeFloor;
      }
      var that = this;
      var $activeRoom = $floor.find('.content-room-wrapper.active-room');
      if ($activeRoom.length == 0) $activeRoom = $floor.find('.content-room-wrapper.previously-active');
      
      var
        $vert = $('#scroller'),
        $horz = $floor.find('.floor-slider'),
        offset = 0;
      
      if (settings.toBottom) {
        offset = -1 * (Drupal.gazprom.winHeight - $floor.outerHeight());
      }
      
      if ($floor.length > 0 && !settings.horzOnly) {
        //console.log('.scroll.sync:', '#' + $activeRoom.attr('id'), horzOnly);
        //this.switchWaypoints('off');
        this.waypointsRefresh();
        $vert.stop(true, false).scrollTo($floor, settings.vDuration, {
          onAfter: function() {
            that.switchWaypoints('on');
            // @TODO This is a nightmare. For some reason, when inserting content above current
            // .. content (scrolled into view), this sync always seems to cause a scroll down
            // .. even though the scroll goes up after the content is inserted. Using this timeout
            // .. to deal with the effects. 750 seems like a good number.
          },
          offset: {top: offset, left: 0}
          //offset: 0
        });
      }
      if ($activeRoom.length > 0) {
        $horz.stop(true, false).scrollTo($activeRoom, settings.hDuration);
      }
    },
    waypointList: null,
    switchWaypoints: function(mode) {
      return;
      var that = this;
      if (mode == 'off') {
        this.waypointList = $.waypoints();
        this.waypointsOff = true;
        //console.log('waypoints: off (' + this.waypointList.length + ')');
        this.waypointList.addClass('waypoint-off'); 
      } else {
        this.waypointsOff = false;
        if (this.waypointList !== null) {
          this.waypointList.not('.snapTo-waypoint').removeClass('waypoint-off');
          //console.log('waypoints: on (' + this.waypointList.not('.snapTo-waypoint').length + ')');
          $.doTimeout(2000, function() {
            that.waypointList.filter('.snapTo-waypoint').removeClass('waypoint-off');
            //console.log('snapTO waypoints: on (' + that.waypointList.filter('.snapTo-waypoint').length + ')');
          });
        }
      }
    },
    waypointsRefresh: function() {
      $.waypoints('refresh');
    },
    _scrollActive: function() {
      Drupal.gazprom.scroll.scrollingInEffect = true;
      //console.log('scrolling started');
    },
    _scrollSettled: function() {
      Drupal.gazprom.scroll.scrollingInEffect = false;
      //console.log('settled');
    }
  }
})(jQuery, Drupal); 

(function($, Drupal){
  /*
   * BUILD functions are used to assemble the various pages of content
   * into the room & floor metaphors. This includes actually
   * loading the content via AJAX calls.
   */
  
   Drupal.gazprom.build = {
//  var build = {
    ajaxCounter: 0,
    showLoadScreen: false,
    inBuildMode: true, // gets turned off by exitBuildMode
    onComplete: function() {},
    stepsTotal: 0,
    stepsCompleted: 0,
    start: function(callback) {
      this.enterBuildMode();

      if (typeof callback == 'function') this.onComplete = callback;
      
      if (!Drupal.gazprom.settings[Drupal.gazprom.mode].preloadFloors) {
        this.exitBuildMode();
        return;
      }
      
//      // first things first, we need to make sure the initially loaded content is hooked up as a room and 
//      // .. added to the directory. This content may or may not be the home page.
//      // the room has already been initialized by the call to Drupal.behaviors.gazprom.attach();
//      var $activeFirstNav = $('#navigation-main ul.menu li a.active-trail'), initialRoomData;
//      if ($activeFirstNav.length > 0) {
//        var initialFloorNum = $('#navigation-main ul.menu li a').index($activeFirstNav);
//        initialFloorNum++; // add one for the home page floor, which is not represented in #navigation-main
//        var $activeSecondNav = $('nav.second-navigation ul.menu li a.active-trail');
//        if ($activeSecondNav.length > 0) {
//          var initialRoomNum = $('nav.second-navigation ul.menu li a').index($activeSecondNav);
//          initialRoomData = this.newRoom($activeSecondNav, {floor: initialFloorNum, room: initialRoomNum});
//          Drupal.gazprom.directory.push(initialRoomData);
//        } else {
//          initialRoomData = this.newRoom($activeFirstNav, {floor: initialFloorNum, room: 0});
//          Drupal.gazprom.directory.push(initialRoomData);
//        }
//      }else {
//        // intial content does not have active-trail in first nav, so must be home page
//        // @TODO problems here for overlay content that doesn't have properly configured menu trail? (solved with Menu Position module)
//        
//        // hook up the home page as a room
//        var $homeAnchor = $('a[href="' + (Drupal.settings.gazprom.front_page ? Drupal.settings.gazprom.front_page : '/') + '"]:first');
//        initialRoomData = this.newRoom($homeAnchor, {floor: 0, room: 0});
//        Drupal.gazprom.directory.push(initialRoomData);
//      }
//
//      this.updateProgressBar();
//      
//      // trigger stage2 of init.room for this first room
//      $('.content-room-wrapper:first').trigger('initStage2');
      
      Drupal.gazprom.build.stage1();

      
    },
    stage1: function() {
      /*
       * Load up all the sibling pages/rooms to the initial page/room that was
       * loaded by the URL request
       */
      
      this.stage2();
      return;
      // Not yet ready for prime time (since the lift navigation has been rewritten)

      // determine which floor the current content is from by using the active-trail of the first-level navigation
      var $activeFirstNav = $('#navigation-main ul.menu li a.active-trail');
      var currentFloor = $('#navigation-main ul.menu li a').index($activeFirstNav);
      currentFloor++;
      // note: -1 (not found) becomes 0 .. So the assumption is that the first floor, which is the home page and won't
      // .. appear in the first-level nav, will be the loaded content. Is this weak?

      // load up all sibling pages/rooms to the currently loaded content
      if (currentFloor > 0) {
        // bind up a progress handler that will be called for each completed
        // .. room. When all the rooms are completed, stage2 will be called
        this.stage1Progress();
        
        var build = this;
        build.stepsTotal += $('.second-navigation ul.menu li a').length;
        
        $('.second-navigation ul.menu li a').each(function(roomIndex, elem) {
          var $menuAnchor = $(elem);
          build.ajaxCounter++;
          build.addRoom($menuAnchor.attr('href'));
        });
      }else {
        this.stage2();
      }

    },
    stage1Progress: function() {
      /*
       * Called each time a page/room is loaded from stage1
       */
      this.ajaxCounter = 0; // reset counter, which then gets increased in the elevatorDestination function
      var build = this;
      $(document).unbind('roomInstalled').bind('roomInstalled', function() {
        build.ajaxCounter--;
        build.stepsCompleted++;
        if (build.ajaxCounter <= 0) {
          $(document).unbind('roomInstalled');
            $.doTimeout(50, function() {
              build.stage2();
            });
        }
      });

    },
    stage2: function() {
      /*
       * Install all floors, referenced by the first-level navigation.
       * This also loads/installs the first room of each floor
       */

      // first, bind-up a progress handler that will be called for each completed
      // .. floor. When all the floors are completed, stage 3 will be called
      this.stage2Progress();
      var build = this;

      // if it's not already in the directory, we must load/add the home page in this stage
      var homeRoom = Drupal.gazprom.utility.findDirectoryEntry('home');      
      if (homeRoom == null) {
        var $homeAnchor = $('a[href="' + Drupal.settings.gazprom.front_page + '"]:first');
        homeRoom = this.newRoom($homeAnchor, {floor: 0, room: 0});
        Drupal.gazprom.directory.push(homeRoom);
      }

      build.stepsTotal += $('#navigation-main ul.menu li a').length;

      // loop through the anchors in first-level navigation and install/load the
      // .. matching floor with the first room/page
      $('#navigation-main ul.menu li a').each(function(floorIndex, elem) {
        var $menuAnchor = $(elem);
        build.ajaxCounter++;
        build.addRoom($menuAnchor.attr('href'));
      });


    },
    stage2Progress: function() {

      this.ajaxCounter = 0; // reset counter, which then gets increased in the elevatorDestination function
      var build = this;
      
      $(document).unbind('roomInstalled').bind('roomInstalled', function() {
        build.ajaxCounter--;
        build.stepsCompleted++;
        if (build.ajaxCounter <= 0) {
          // all floors finished installing (and first rooms are loaded)
          // .. so now fetch all the other rooms of each floor
          // .. (the sibling rooms of the initially loaded content happen to already
          // .. .. be loaded)
          $(document).unbind('roomInstalled');
          $.doTimeout(50, function() {
            build.stage3();
          });
          //build.complete();

        }
      });


    },
    stage3: function() {
      /*
       * Install all the remaining rooms of each floor installed during stage 2
       */
      
      var build = this;
      
      if (!Drupal.gazprom.settings[Drupal.gazprom.mode].preloadRooms) {
        build.complete();
        return;
      }
      
      
      // first, bind-up a progress handler
      this.stage3Progress();
      
      // now load the additional rooms of each floor
      $('.second-navigation ul.menu').each(function(floorIndex, elem) {
        build.stepsTotal += $(this).find('li > a').length - 1;
        $(this).find('li > a').each(function(roomIndex, elem) {
          var $menuAnchor = $(elem);
          build.ajaxCounter++;
          build.addRoom($menuAnchor.attr('href'));
        });
      });
      if ($('.second-navigation ul.menu').length == 0) build.complete();

    },
    stage3Progress: function() {
      
      this.ajaxCounter = 0;
      var build = this;
      
      $(document).unbind('roomInstalled').bind('roomInstalled', function() {
        build.ajaxCounter--;
        build.stepsCompleted++;
        if (build.ajaxCounter <= 0) {
          $.doTimeout(50, function() {
            build.complete();
          });
        }
      });

    },
    complete: function() {
      /*
       * All rooms (and floors) have been installed/loaded
       */
      

      // make a reference between a main navigation anchor and the floor
      var $listOfFloors = $('.content-floor-wrapper');
      $('#navigation-main ul.menu li a').each(function(i, elem){
        var $floor = $($listOfFloors.get(i+1));
        var $anchor = $(elem);
        $floor.data('referencingAnchor', $anchor);
      });
      // @TODO is this still needed? find a better way?
      
      // attach room navigators to rooms (sideways scrollers)
//      Drupal.gazprom.init.roomNavigators();
      
      if (false) {
        // use this for debugging scrolling functions by 1 pixel
        $(window).keydown(function(e) {
          var key = e.keyCode;
          if (key == 40 || key == 38) {
            e.preventDefault();
            if (key == 40) {
              $.scrollTo({top:'+=1px', left: 0},0);
            } else {
              $.scrollTo({top:'-=1px', left: 0},0);
            }
            return false;
          }
        return true;
        });
      }

      Drupal.gazprom.build.exitBuildMode();

    },
    addRoom: function(href) {
      
      Drupal.gazprom.loadContent(href, {
        selector: '.content-floor-wrapper:first, #navigation-main',
        setBusy: false,
        callback: function($content, href) {
          Drupal.gazprom.insertContent($content, href, {
            insertOnly: true,
            stage2initMode: 'deferred'
          });
          $(document).trigger('roomInstalled');
        }
      });
    },
    newRoom: function($menuAnchor, location, $divTemplate) {
      /**
       * This inserts containers for a new room/page and then fetches the content via
       * AJAX. Does special handling for floors a.k.a. first rooms
       */
      
      var build = this;
      
      // create object to store data about this room/page
      var destination = {
        name: $menuAnchor.text(),
        href: $menuAnchor.attr('href'),
        id: Drupal.gazprom.utility.urlToId($menuAnchor.attr('href')),
        location: location
      };

      // rangle the id some
      if (destination.id == '') {
        destination.id = 'home';
      }

      // is this the first room of a floor or is this an interior room?
      // This gets determined by figuring out if the $anchor passed to this function is part of the 
      // .. main navigation or part of a secondary navigation. So a prerequesite is that $anchors must
      // .. be used from the main navigation for first rooms of a floor (this makes sense because the
      // .. second navigation for the floor isn't loaded yet anyway)
      var $nav = $menuAnchor.closest('nav');
      var isFloor = ($nav.attr('id') == 'navigation-main' || $menuAnchor.attr('href') == Drupal.settings.gazprom.front_page)  ? true : false;

      //var $newRoomWrapper =  $divTemplate.clone().empty();
      
      // see if the destination already has content (i.e. home page or content for deep-linking)
      // .. and if not, create a place for it and fetch the content for it
      var $room = $('#'+destination.id);
      if ($room.length == 0) {
        // the room, referenced by the $menuAnchor, is not yet in the DOM .. so lets add it
        
        // is this the first room of a floor or is this an interior room?
        if (isFloor) {
          // add first room of a floor

          // create a temporary container for the new floor (including first room) content
          var $newFloorWrapper = $('<div class="temp-wrapper content-floor-wrapper"></div>');
          $newFloorWrapper.append('<div class="content-room-wrapper content-wrapper"></div>');
          // set the room wrapper's ID to match the href of the $menuAnchor
          $newFloorWrapper.find('.content-room-wrapper').attr('id', destination.id); // this DIV will actually get replaced by the AJAX content, but
          // .. we need to keep it in place, with the right ID, until the AJAX content arrives, so we know where the other rooms/floors need to be
          // .. placed in relation to it (before or after)


          // determine where in the current DOM this new floor (plus first room) needs to be inserted
          var floorBefore = -1;
          // loop through existing floors and find out if one of the existing floor is before this new floor
          $('.content-floor-wrapper').each(function(){
            var roomID = $(this).find('.content-room-wrapper:first').attr('id');
            var roomData = Drupal.gazprom.utility.findDirectoryEntry(roomID);
            if (roomData != null) {
              if (roomData.location.floor < location.floor) {
                floorBefore = roomData.location.floor;
              }
            }
          });
          // @TODO ** placement of loaded rooms is not working correctly if the original room was a interior rooom of a floor
          // .. it works okay if the original room is the first room of a floor
          if (floorBefore >= 0) {
            // found the floor before the one we're working with already in the DOM
            // .. so add our new destination right after it
            var $floorDIVbefore = $($('.content-floor-wrapper').get(floorBefore)); //.closest('.content-floor-wrapper');
            $floorDIVbefore.after($newFloorWrapper);
          }else {
            // never found the floor before this one, so assume that this floor is before of whatever
            // .. floors are already in place
            var $floorDIVafter = $('.content-floor-wrapper:first');
            $floorDIVafter.before($newFloorWrapper);
          }
          // AJAX fetch the first room of the floor (page)
          build.ajaxCounter++;
          $.get(destination.href, function(data) {
            if ($('html').is('.ie8, .ie7, .ie6') && Drupal.gazprom.useInnerShiv) {
             $newContent = $(innerShiv($(data).find('.content-floor-wrapper:first').outerHTML()));
            }else {
              $newContent = $(data).find('.content-floor-wrapper:first');
            }
            
            $newFloorWrapper.empty().append($newContent);
            //Drupal.gazprom.init.room($newFloorWrapper.find('.content-room-wrapper:first')); // @TODO is this best place for this?
            Drupal.attachBehaviors($newFloorWrapper.find('.content-room-wrapper:first')); // @TODO is this best place for this?
            $newFloorWrapper.children().unwrap();
            $(document).trigger('roomInstalled');
          });

        } else {
          // add other rooms of a floor (at least one was already loaded)
          
          // create a temporary container for the new room content
          var $newRoomWrapper = $('<div class="content-room-wrapper content-wrapper temp-wrapper"></div>');
          // set the room wrapper's ID to match the href of the $menuAnchor
          $newRoomWrapper.attr('id', destination.id); // this DIV will actually get replaced by the AJAX content, but
          // .. we need to keep it in place, with the right ID, until the AJAX content arrives, so we know where the other rooms/floors need to be
          // .. placed in relation to it (before or after)

          var roomBefore = -1;
          $menuAnchor.closest('.content-floor-wrapper').find('.content-room-wrapper').each(function(){
            roomID = $(this).attr('id');
            roomData = Drupal.gazprom.utility.findDirectoryEntry(roomID);
            if (roomData) {
              if (roomData.location.room < location.room) {
                roomBefore = roomData.location.room;
              }
            } else {
              //roomBefore = -1;
            }
          });
          if (roomBefore >= 0) {
            // found the room before the one we're working with already in the div
            // .. so add our new room right after it
            var $roomDIVbefore = $($menuAnchor.closest('.content-floor-wrapper').find('.content-room-wrapper').get(roomBefore));
            $roomDIVbefore.after($newRoomWrapper);
          } else {
            // never found the room before this one, so assume that this room is before whatever
            // .. rooms are already in place
            var $roomDIVafter = $menuAnchor.closest('.content-floor-wrapper').find('.content-room-wrapper:first');
            $roomDIVafter.before($newRoomWrapper);
          }
          // AJAX fetch the room (page)
          build.ajaxCounter++;
          $.get(destination.href, function(data) {
            if ($('html').is('.ie8, .ie7, .ie6') && Drupal.gazprom.useInnerShiv) {
              $newContent = $(innerShiv($('<div>').append($(data).find('.content-room-wrapper:first')).outerHTML()));
            } else {
              $newContent = $(data).find('.content-room-wrapper:first');
            }
            
            $newRoomWrapper.empty().append($newContent);

            //Drupal.gazprom.init.room($newRoomWrapper.find('.content-room-wrapper:first')); // @TODO is this best place for this?
            Drupal.attachBehaviors($newRoomWrapper.find('.content-room-wrapper:first')); // @TODO is this best place for this?
            
            $newRoomWrapper.children().unwrap();
            $(document).trigger('roomInstalled');
          });

        }

      } else {
        // room already in place, but needs destination data attached
        //$room.data('destination', destination);
      }

      // hijack the anchor so it scrolls to the destination
      $menuAnchor.hijax();
      // @TODO is this hiding too much in here? Maybe a better place to hijax the navigation anchors?

      return destination;
      
    },
    enterBuildMode: function() {
      this.inBuildMode = true;
      $('html').addClass('build-mode');
      $('html,body').css({
        overflow: 'hidden'
      });
      
      if (this.showLoadScreen == true && !Drupal.gazprom.singlePageMode && Drupal.gazprom.settings[Drupal.gazprom.mode].preloadFloors) {
        if ($('#load-screen').length == 0 ) $('body').prepend('<div id="load-screen"></div>');
        $('#load-screen').addClass('build-mode');
      }
    },
    exitBuildMode: function() {
      $('html,body').removeClass('build-mode pre-built simple').addClass('gazprom-built');
      
      $('body').addClass('mode-' + Drupal.gazprom.mode); // mode-light, mode-medium, mode-heavy, mode-extra-heavy
      $('#scroller').focus();

      // release the temporary click handler
      $('a').unbind('click.duringInitialization');

      // must adjust header & footer so that it doesn't cover the #scroller's scrollbar
      // (second-navigation gets the same treatment when it goes through the stick process
      $('#header, #footer-page').css({
        width: 'auto',
        right: $.getScrollbarWidth() + 'px'
      });
      
      // always return scroll back to the .content-floor-wrapper we started with
      // and do one more window resize event
      setTimeout(function(){
        $(window).trigger('resize');
        _finish();
      }, 200);

      function _finish() {
        if ($('#load-screen').length > 0 ) {
          $('#load-screen').delay(200).animate({
            opacity: 0
          }, 500, function() {
            $('#load-screen').remove();
            Drupal.gazprom.build.inBuildMode = false;
            Drupal.gazprom.build.onComplete.call();
          });
        } else {
          Drupal.gazprom.build.inBuildMode = false;
          Drupal.gazprom.build.onComplete.call();
        }

      }
      
    },
    updateProgressBar: function() {
      var build = this;
      if ($('#load-progress').length == 0) {
        $('#load-screen').append('<div id="load-progress"><div id="load-progress-bar"></div></div>');
      }
      var totalWidth = $('#load-progress').width();
      var $bar = $('#load-progress-bar');
      $.doTimeout (250, function() {
        if (build.stepsCompleted <= build.stepsTotal && build.inBuildMode) {
          var completion = 1 / (build.stepsTotal / build.stepsCompleted );
          $bar.css('width', totalWidth * completion);
          return true;
        } else {
          return false; // done
        }
      });
      
      // unfortunately, it appears that IE8/7 doesn't pain the screen often enough to display this progress update
    }
  }
  
})(jQuery, Drupal);


(function($, Drupal){
  Drupal.gazprom.click_handlers = {
    room: function(e) {
      // @TODO NO LONGER USED??

      /* handle a click within a room */
      // @TODO currently only handles third-navigation, which replaces room's content
      // .. make it handle "read more" links? or should there be another handler for those?
      // .. what about external links? what about everything else?

      var $this = $(e.currentTarget);
      var href = $this.attr('href');
      if (href == '') return true;
      e.preventDefault();
      var $room = $this.closest('.content-room-wrapper');
      $room.empty();
      $room.append('<div class="temp-wrapper"></div>');
      var $loadWrapper = $room.find('.temp-wrapper');
      $loadWrapper.load(href + ' .content-room-wrapper', function() {
        $loadWrapper.find('.content-room-wrapper').children().unwrap();
        $loadWrapper.children().unwrap();
        Drupal.gazprom.init.room($room);
      });
      
      return false;
    },
    clickInIframe: function(href, e) {
      //console.log(href + ' was clicked');
      
      Drupal.gazprom.gotoHref(href);
      return;
      
//      // look for a matching anchor in this frame
//      var $localAnchor = $('.open-within-room a[href="' + href + '"]:first');
//      if ($localAnchor.length > 0) {
//        var $room = $localAnchor.closest('.content-room-wrapper');
//        if ($room.length > 0) {
//         // Drupal.gazprom.utility.scrollToRoom($room, 
//          Drupal.gazprom.activateRoom($room, {callback: function(){
//            $localAnchor.trigger('click');
//          }});
//        } else {
//          $localAnchor.trigger('click');
//        }
//      }
    },
    worldMapClick: function($anchor) {
      // @TODO NO LONGER USED??
      var href = $anchor.attr('href');
      var $thisRoom = $anchor.closest('.content-room-wrapper');
      var $remoteAnchor = $('.content-room-wrapper').not($thisRoom).find('a[href="' + href + '"]').first();
      if ($remoteAnchor.length > 0) {
        var $room = $remoteAnchor.closest('.content-room-wrapper');
        if ($room.length > 0) {
          Drupal.gazprom.activateRoom($room, {callback: function() {
            $remoteAnchor.trigger('click');
          }});
        // @TODO rethink this
        } else {
          $remoteAnchor.trigger('click');
        }
      }
    }
    
  }
})(jQuery, Drupal);

(function($, Drupal){
  Drupal.gazprom.utility = {
    findDirectoryEntry: function(id) {
      /*
       * Find and return a directory entry (destination) based on the room ID
       */
      var dirPosition = Drupal.gazprom.utility.ArrayIndexOf(Drupal.gazprom.directory, function(obj){
        return obj.id == id;
      });
      if (dirPosition == -1) return null;
      return Drupal.gazprom.directory[dirPosition];
      
    },
    ArrayIndexOf: function(a, fnc) {
      /*
       * find array index for an object property matching
       * gleamed from: http://blog.webonweboff.com/2010/05/javascript-search-array-of-objects.html
       */
      if (!fnc || typeof (fnc) != 'function') {
        return -1;
      }
      if (!a || !a.length || a.length < 1) return -1;
      for (var i = 0; i < a.length; i++) {
        if (fnc(a[i])) return i;
      }
      return -1;
    },
    urlToId: function(url) {
      /*
       * return a DOM id version of the provided URL string
       */

      if (typeof url == 'undefined') return 'error'; // Something went wrong. 
      var id = url.toLowerCase().replace(/[^a-z0-9]/g, '-');
      id = id.replace(/^-/, ''); // remove possible first -
      id = id.replace(/^-/, ''); // remove possible second - !! (some HTML4 seems to be like #./news-media) @todo find out why?
      id = id.replace(/-$/, ''); // remove possible trailing -

      var langPrefix = Drupal.settings.pathPrefix;
      langPrefix = langPrefix.replace(/\/$/, '');

      if (id == '' || id == '-' || id == langPrefix) id = 'home'; // a href of "/" becomes home
      
      return id;
    },
    isInView: function(elem) {
      var docViewTop = $(window).scrollTop();
      var docViewBottom = docViewTop + $(window).height();

      var elemTop = $(elem).offset().top;
      var elemBottom = elemTop + $(elem).height();

      return ((elemBottom >= docViewTop + ($(window).height() / 2)) 
          && (elemTop <= docViewTop + ($(window).height() / 2)));
    },
    getRoomTitle: function($room) {
      return $room.find('h1.head-title').text();
    }, // end getRoomTitle
    scrollToRoom: function($room, options) {
      // scrolls to specified room

      var settings = $.extend({
        duration: Drupal.gazprom.scrollSpeed,
        catchUpDuration: Drupal.gazprom.scrollCatchUpSpeed,
        easing: Drupal.gazprom.scrollEasing,
        callback: null
      }, options);

      if (!$room) {
        //$room = $('.content-room-wrapper.active-room');
        $room = Drupal.gazprom.activeRoom;
      }
      

      var $floor = $room.closest('.content-floor-wrapper');
      var $floorSlider = $floor.find('.floor-slider:first');
      var $secondNavigation = $floor.find('.second-navigation:first');
      if ($room.length == 0 || $floor.length == 0 || $floorSlider.length == 0) {
        //console.log('ERROR: Drupal.gazprom.scrollToRoom given invalid room');
        return; // something went wrong
      }

      if (!$floor.hasClass('active-floor')) {
        // floor needs to be scrolled-to first
        Drupal.gazprom.scrollIsActive = true; // flag other functions that we are scrolling
        this.scrollToFloor($floor, $.extend({},settings,{
          callback: function() {
            _scrollToRoom();
          }
        }));
      } else if ($floor.offset().top != $(window).scrollTop()) {
        // user has scrolled the window, so reset floor to top
        this.scrollToFloor($floor, $.extend({},settings,{
          callback: function() {
            _scrollToRoom();
          },
          duration: settings.catchUpDuration
        }));
      } else {
        // everything looks good, scroll to the room (horizontally)
        // also causes update to second navigation active indicator
        _scrollToRoom();
      }
      
     
      function _scrollToRoom() {
        _moveSecondNavIndicator();
        if ($room.offset().left != 0) {
          Drupal.gazprom.scrollIsActive = true; // flag other functions that we are scrolling
          $floorSlider.stop(true,false).scrollTo($room, {
            duration: settings.duration,
            easing: settings.easing,
            axis: 'xy',
            onAfter: _scrollComplete
          });
        } else {
          _scrollComplete();
        }
      }
      
     
      function _scrollComplete() {
        Drupal.gazprom.scrollIsActive = false;
        if (typeof settings.callback == 'function') settings.callback.call();
      }
      
      function _moveSecondNavIndicator() {
        // adjust indicator
        var $indicator = $floor.find('nav.second-navigation').find('.indicator');
        Drupal.gazprom.utility.updateIndicator($indicator, settings);
      }

      
    },
    scrollToFloor: function($floor, options) {
      // scrolls to specified floor

      var settings = $.extend({
        duration: Drupal.gazprom.scrollSpeed,
        easing: Drupal.gazprom.scrollEasing,
        offset: 0,
        callback: null
      }, options);

      if (typeof($floor) == 'undefined') {
        //$floor = $('.content-floor-wrapper.active-floor');
        $floor = Drupal.gazprom.activeFloor;
      }
      
      if ($floor.offset().top != $(window).scrollTop()) {
        Drupal.gazprom.scrollIsActive = true; // flag other functions that we are scrolling
        $('.content-floor-wrapper.scroll-destination').removeClass('scroll-destination');
        $floor.addClass('scroll-destination');
        var $scroller = $('#scroller');
        $scroller.stop(true).scrollTo($floor, {
          duration: settings.duration,
          axis: 'y',
          offset: settings.offset,
          easing: settings.easing,
          onAfter: _scrollComplete
        });
        // @TODO figure out why $(window).stop(true) doesn't actually work!!
      } else {
        _scrollComplete();
      }

      function _scrollComplete() {
        Drupal.gazprom.scrollIsActive = false;
        $('.content-floor-wrapper.scroll-destination').removeClass('scroll-destination');
        if (typeof settings.callback == 'function') settings.callback.call();
      }

    },
    updateIndicator: function($indicator, options) {
      if ($($indicator).length == 0) return;
      var settings = $.extend({
        duration: Drupal.gazprom.scrollSpeed,
        easing: Drupal.gazprom.scrollEasing
      }, options);
      $indicator.stop(true);
      var original_left = parseInt($indicator.offset().left);
      var original_width = parseInt($indicator.width());
      var new_left, new_width;
      var $activeAnchor = $indicator.parent().find('ul.menu a.active');
      if ($activeAnchor.length > 0) {
        new_left = $activeAnchor.offset().left - $indicator.parent().offset().left;
        new_width = $activeAnchor.width();
      } else {
        new_left = 0;
        new_width = 0;
      }
      if (new_width == original_width && new_left == original_left) return;

      if (new_width == 0) {
        $indicator.fadeOut(settings.duration, function() {
          $(this).css({width: 0});
        });
        return;
      }
      if (original_width == 0) {
        $indicator.stop(true)
          .fadeOut(0)
          .css({
            width: new_width,
            left: new_left
          });
        $indicator.fadeIn(settings.duration);

      } else {
        $indicator.stop(true).animate({
         width: new_width,
         left: new_left,
         opacity: 1
        }, {
         easing: settings.easing,
         duration: settings.duration
        });
      }

    },
    activeAnchor: function($anchor, options) {
      /*
       * Makes the provided anchor the visually active link
       */
      if ($($anchor).length == 0) return;
      if ($anchor.hasClass('active')) return; // Already set.{
      if ($anchor.attr('href') == Drupal.settings.gazprom.front_page) {
        // special case for link to home
        $('#navigation-main a, #navigation-main li').removeClass('active active-trail');

        // adjust navigation-main indicator
        this.updateIndicator($('#navigation-main .indicator'), options);
        // @TODO this should be in activateRoom, right? This could be getting called multiple times

      } else {
        var $container = $anchor.closest('ul');
        if ($container.length == 0) {
          $container = $anchor.closest('nav');
        }
        if ($container.length == 0 && $anchor.parent().hasClass('breadcrumb')) {
          $container = $anchor.closest('.content-floor-wrapper').find('.second-navigation:first');
        }
        $container.find('a, li').removeClass('active active-trail');
        $anchor.addClass('active active-trail');
        $anchor.parent('li').addClass('active active-trail');

        // adjust indicator in top level nav (scrollToRoom will do it for second-level nav)
        var $indicator = $anchor.closest('nav#navigation-main').find('.indicator');
        this.updateIndicator($indicator, options);
        // @TODO for second-level navigation, this has been moved into scrollToRoom
        // @TODO this should be in activateRoom, right? This could be getting called multiple times

      }
    },
    toggleNavSticky: function($nav, mode) {
      /*
       * Makes navigation menu (second navigation) sticky
       * or unsticky. Called from atWaypoint or in activateRoom during scroll
       */
      if (typeof $nav == 'undefined') return;
      if ($nav.length == 0) return;
      if (Drupal.gazprom.singlePageMode) return;

      var useAnimations = true && !(Drupal.gazprom.mode == 'light');
      
      if (!$nav.hasClass('stuck') && mode == 'sticky') {
        $('.second-navigation.stuck').each(function(){
          // make sure there are no left over second-navigation bars that are still stuck when they shouldn't be
          _unstickIt($(this));
        });
        _stickIt($nav);
      } else if (mode == 'unsticky'){
        _unstickIt($nav);
      }

      function _stickIt($element) {
        //console.log('_stickIt triggered: ' + $element.closest('.content-floor-wrapper').find('.content-room-wrapper:first').attr('id'));
        //console.profile('_stickIt');
        var $header = $('#header');
        var headerHeight = $header.outerHeight(); // this is soon to be the fixed top of our nav
        var delta;
        if (useAnimations) {
          delta = ($header.offset().top + headerHeight) - $element.offset().top;  // where is the nav now compared to where we are going to put it
          if ((delta < headerHeight / 2) && (delta > -1 * (headerHeight / 2))) delta = 0; // ignore small differences
        } else {
          delta = 0;
        }
        // make it fixed at it's current location
        $element.addClass('stuck').css({
          position: 'fixed',
          top: headerHeight - delta,
          right: $.getScrollbarWidth(), // for #scroller's scrollbar
          zIndex: 49
        });
        $element.before('<div class="stucks-old-position" style="height:0"></div>'); // consider using this for animating the _unstickIt procedure
        // if it's far enough way, animate it into the correct position
        if (delta != 0) {
          //console.log('animating into position, delta = ' + delta);
          $element.animate({
            top: headerHeight
          },{
            duration: 250,
            complete: function() {
              $element.addClass('stuck'); 
            }
          });
        }
      }
      
      function _unstickIt($element) {
        //console.log('_unstickIt triggered: ' + $element.closest('.content-floor-wrapper').find('.content-room-wrapper:first').attr('id'));
        var $oldPosition = $element.siblings('.stucks-old-position');
        var delta;
        if ($oldPosition.length > 0) {
          delta = $element.offset().top - $oldPosition.offset().top; // where is the element as compared to where it's going
        } else {
          delta = 0;
        }
        if ((delta < $element.height()) && (delta > -1 * $element.height())) delta = 0; // ignore small differences
        if (!useAnimations) delta = 0; // performance issues, so disabled for now
        if (delta > 0) {
          // currently NOT doing an animation for downward .. problems with fixed vs absolute and the scrolling continuing during animation..
          //console.log('animating back to position, delta = ' + delta);
          var properties = {
            // moving down, so animate it in that direction
            top: parseInt($element.css('top')) - delta
          }
          if (delta > 0) {
            // moving up, so just fade it out
            properties = {
              opacity: 0
            }
          }
          $element.removeClass('stuck').animate(properties, {
            duration: 250,
            complete: function() {
              $element.css({
                position: '',
                top: '',
                zIndex: '',
                right: '',
                opacity: ''
              });
              $element.removeClass('stuck');
            }
          });
        } else {
          $element.removeClass('stuck').css({
            position: '',
            top: '',
            zIndex: '',
            right: '',
            opacity: ''
          });
        }
        $element.siblings('.stucks-old-position').remove();

      }

    },
    singlePageModeTest: function() {
      var $singlePageMode = false;
      
      $singlePageMode = $singlePageMode || Drupal.settings.gazprom.singlePageMode == 'true';
      
      //$singlePageMode = $singlePageMode || $('html').is('.ie7') || $('html').is('.XXXie8');
      
      // if URL has ?singlePageMode=true , the gazprom_preprocess_html() function in template.php will set this cookie
      $singlePageMode = $singlePageMode || $.cookie('gazprom-single-page') == 'true';
      
      // temporary? test for ipad/iphone/android device
      //$singlePageMode = $singlePageMode || $('html').is('.touch');

      return $singlePageMode;
    },
    adjustMode: function() {
      var mode = Drupal.gazprom.mode;
      if ($('html').is('.ie7') || $('html').is('.ie8')) {
        mode = 'light';
      }
      
      if ($('html').is('.touch')) {
        mode = 'light';
      }
      
//      if ($.waypoints('viewportHeight') <= Drupal.gazprom.shortRoom) {
//        mode = 'light';
//      }

      // hack for Russian language to not use Parallax effect (results in tattoos on face)
      if (Drupal.settings.pathPrefix == 'ru/') {
        Drupal.gazprom.settings[mode].parallax = false;
      }
      
      if ($.cookie('gazprom-mode')) {
        mode = $.cookie('gazprom-mode');
      }
      
      Drupal.gazprom.mode = mode;
    },
    getViewIDs: function($view) {
      // is this a hack? find the view_name and view_display_id values from the classes
      var classArray = $view.attr('class').split(' ');
      var view_name, display_id;
      $.each(classArray, function(index, value) {
        if (value.substring(0,8) == 'view-id-') {
          view_name = value.replace('view-id-', '');
        }
        if (value.substring(0,16) == 'view-display-id-') {
          display_id = value.replace('view-display-id-', '');
        }
      });
      if (!view_name && ! display_id) return {}; // something went wrong
      
      return {view_name: view_name, view_display_id: display_id};
      
    },
    getViewsAjaxPath: function() {
      var path;
      if (Drupal.settings.views) {
        path = Drupal.settings.views.ajax_path ? Drupal.settings.views.ajax_path : null;
      }
      if (!path) {
        path = Drupal.settings.basePath + Drupal.settings.pathPrefix + 'views/ajax';
      }
      
      return path;
    },
    setBusy: function() {
        $('#busy').show();
    },
    clearBusy: function() {
      $('#busy').hide();
    }
  }
})(jQuery, Drupal);

(function($, Drupal){
  Drupal.gazprom.search = {
    effectDuration: 250,
    widthDelta: 100,
    init: function($context) {
      if (typeof $context == 'undefined') {
        $context = $('#header');
      }
      var $searchForm = $context.find('form.simple-search-form, form#search-block-form');
      var $input = $searchForm.find('input.form-text');
      
      if ($input.closest('#header').length > 0) {
        // main heder search, attach focus & blur event handlers
        this.initInputSlide($input, $searchForm);
      }
      
      
      $searchForm.find('input.form-text').attr('value','');
      $searchForm.ajaxForm({
        beforeSerialize: function($form, options) { 
          $form = $form;
//          return false;
// return false to cancel submit                  
        },
        beforeSubmit: function(arr, $form, options) {
          arr = arr;
          //arr.push({name: 'overlay', value: 'true'});
            // The array of form data takes the following form: 
            // [ { name: 'username', value: 'jresig' }, { name: 'password', value: 'secret' } ] 
          
//          if (arr[0]['name'] == 'keywords' && arr[0]['value'] == '' && $form.find('input.form-text').data('value')) {
//            arr[0]['value'] = $form.find('input.form-text').data('value');
//          }

            
            var $input = $form.find('input.form-text');
            $input.trigger('blur');
            if ($input.attr('value') == '') return false; // nothing entered

            // construct a href for our search-result View to process via our openPath() function
            var queryString;
            $.each(arr, function(i, elem){
              if (elem['name'] == 'keywords') {
                queryString = elem['value'];
              }
            });

            Drupal.gazprom.gotoHref(Drupal.settings.basePath + Drupal.settings.pathPrefix + 'search-results/' + queryString, {searchResults:true}); // @TODO put keywords in href?

            return false;
            // return false to cancel submit                  
        },
        success: function showResponse(result, statusText, xhr, $form)  { 
          result = result;
          //var $newContent = $(result).find('.content-overlay-wrapper'); //.children();
          if ($('html').is('.ie8, .ie7, .ie6') && Drupal.gazprom.useInnerShiv) {
            $newContent = $(innerShiv($(result).find('.content-wrapper').first().outerHTML()));
          }else {
            $newContent = $(result).find('.content-wrapper').first();
          }

          if (true && $newContent.length > 0) {
            var $resultsContainer = $('#search-results-staging');
            if ($resultsContainer.length == 0) {
              $('body').append('<div id="search-results-staging" style="display:none;"></div>');
              $resultsContainer = $('#search-results-staging');
            }
            $resultsContainer.empty().append($newContent);
            Drupal.gazprom.gotoHref('/search-results', {searchResults:true}); // @TODO put keywords in href?
            
            // hide the keywords
            var $input = $form.find('input.form-text');
//            $input.data('value', $input.attr('value')).attr('value','');
            //$input.blur();
            //Drupal.gazprom.init.room($('#search-results'));
//            $room.find('.ajax-form-wrapper').fadeOut(500, function($newContent) {
//              _insertNewContent();
//            });
          }
          return;
          
//          function _insertNewContent() {
//            $room.find('.ajax-form-wrapper').empty().append($newContent).fadeIn(500);
//            Drupal.gazprom.init.room($room);
//          }
        }
        
      });
    },
    initInputSlide: function ($input, $form) {
      
      $input.css('width', 10);
      $input.data('originalWidth', $input.width());
      $form.data('originalWidth', $form.width());
      var widthDelta = this.widthDelta;
      var effectDuration = this.effectDuration;
      $input.unbind('focus.searchForm').bind('focus.searchForm', function(e) {
        $input.css('color', '#fff');
        if ($(window).width() < 1080) {
          $input.closest('.block').siblings('.block').fadeOut(effectDuration / 2);
        }
        $input.stop(true).animate({width: $input.data('originalWidth') + widthDelta}, effectDuration);
        $form.stop(true).animate({width: $form.data('originalWidth') + widthDelta}, effectDuration);
      })
      .unbind('blur.searchForm').bind('blur.searchForm', function(e) {
        $input.css('color','transparent'); // hide the text
          $input.closest('.block').siblings('.block').fadeIn(effectDuration / 2);
        $input.stop(true).animate({width: $input.data('originalWidth')}, effectDuration);
        $form.stop(true).animate({width: $form.data('originalWidth')}, effectDuration);
      });
      
      $form.hoverIntent(function(){
        $input.trigger('focus');
      }, function(){
        //$(this).trigger('blur');
      });
      
    },
    displayInOverlay: function($content) {
      
    }
  }
})(jQuery, Drupal);

(function($, Drupal) {
  Drupal.gazprom.sitemap = {
    $sitemap: null,
    $sitemapLink: null,
    $closeBtn: null,
    effectDuration: 750,
    init: function($context) {
      if (typeof $context == 'undefined') {
        $context = $('#header');
      }
      var sitemap = this;
      
      // make sure there is a site map present
      this.$sitemap = $('body').find('.menu-block-wrapper.menu-name-main-menu:last').attr('id', 'sitemap');
      this.$sitemap.prependTo($('#header'));
      this.$sitemap.data('originalHeight', this.$sitemap.height());
      this.$sitemap.css('height', 0);
      
      // hijax the links
      this.$sitemap.find('a').unbind('click').bind('click.sitemap', function(e) {
        if (Drupal.gazprom.hijax.initialized) {
          e.preventDefault();
          sitemap.click($(this));
        } else {
          return true; // let normal handler do it's job (probably singlePageMode)
        }
      });
      
      if (this.$sitemap.find('a.close').length == 0) {
        this.$sitemap.append('<a class="close" title="' + Drupal.t('Close') + '"></a>');
      }
      this.$closeBtn = this.$sitemap.find('a.close')
      this.$closeBtn.unbind('click').bind('click.sitemap', function() {
        sitemap.toggle();
      }).hide();

      this.$sitemapLink = $context.find('#site-map-link a');
      this.$sitemapLink.unbind('click').bind('click.sitemap', function() {
        sitemap.toggle();
      })
    },
    toggle: function () {
      if (this.$sitemap.is('.open')) {
        this.close();
      } else {
        this.open();
      }
    },
    open: function(callback) {
      this.$sitemap.removeClass('closed').addClass('open');
      this.$sitemapLink.addClass('active');
      var $closeBtn = this.$closeBtn;
      this.$sitemap.stop(true).animate({
        height: this.$sitemap.data('originalHeight')
      },{
        duration: this.effectDuration,
        complete: function() {
          $closeBtn.fadeIn(500);
          if (typeof callback == 'function') callback.call();
        }
      });
    },
    close: function(callback) {
      this.$sitemap.removeClass('open').addClass('closed');
      this.$sitemapLink.removeClass('active');
      var $closeBtn = this.$closeBtn;
      $closeBtn.fadeOut(100);
      this.$sitemap.stop(true).animate({
        height: 0
      }, {
        duration: this.effectDuration,
        complete: function() {
          if (typeof callback == 'function') callback.call();
        }
      });
    },
    click: function($anchor) {
      
      // must match up with the correct top-level navigation anchor
      var $listItem = $anchor.closest('li');
      var $menu = $listItem.closest('ul.menu');
      if ($menu.parent().attr('id') != 'sitemap') {
        // one of the sub (second-nav) links, so jump up to the right LI of the parent UL menu
        $listItem = $listItem.parent().closest('li');
        $menu = $listItem.closest('ul.menu');
      }
      var pos = this.$sitemap.find('ul.menu:first > li').index($listItem);
      var $newAnchor = $($('nav#navigation-main ul.menu a').get(pos));
      
      this.close(function() {
        Drupal.gazprom.gotoHref($anchor.attr('href'));
      });
      
    }
  }
})(jQuery, Drupal);

(function($) {
  
  $.fn.scrollingList = function(options) {
    var options = $.extend({
      scrollDuration: 2000,
      autoScrollInterval: 10000,
      autoScroll: true,
      parentHeightSelector: '.expand-top',
      easing: 'easeInOutSine',
//      easing: 'swing',
//      easing: 'linear',
      css3easing: 'ease-in-out',
      fluidImageSafeOffset: {top: 0, left: 0, right: 0, bottom: 0}
    }, options);
    return this.once('scrollingList', function() {
      var $this = $(this);
      var $listWrapper = $this.find('.scrolling-list-items:first');
      var $list = $listWrapper.find('ul:first');
      var $items = $list.find('li');
      var $index = $this.find('.scrolling-list-index ul:first');
      
      
      $(window).bind('resizeComplete.scrollingList', function() {
        _sizeItemRows(); // also executes _scrollToItem()
      });
      
      // front-feature scrolling-list needs a lot of hacking for the background images to work properly
      // (sorry for doing this.. there were deadlines to be met, Views 3 was throwing me off and i couldn't properly customize field output for multiple value image field)
      // (at site launch, scrolling-list is not being used anywhere except front-features)
      // there is now a shuffle happening in PHP: views-view-fields--front-features--main.tpl.php
      $items.each(function(i, elem) {
        var $item = $(elem);
        var $images = $item.find('.views-field-field-background-image img');
        $images.removeAttr('width').removeAttr('height').addClass('fancy-background-image');
        $images.first().addClass('display-now');
        $images.not(':first').addClass('display-later'); // fluidCenterAlignImage() does not issue show() if this call is added
      });

      $index.find('li:first').addClass('active');
      $items.find('li:first').addClass('active');
      _sizeItemRows(); // also executes _scrollToItem()

      // attach resize routine to background images
      $list.find('img.fancy-background-image').fluidCenterAlignImage({
//        containerSelector: '.views-field-field-background-image',
        containerSelector: '.views-row',
        safeOffset: options.fluidImageSafeOffset
      });
      
      // configure tooltip popups
      $index.find('li:not(.tooltip-inside)')
        .addClass('tooltip-inside')
        .prepend('<div class="tooltip-trigger"></div>')
        .find('div.tooltip-trigger')
        .tooltip({
//          effect: 'slide', // slide effect caused problems in Firefox with the background image not sliding properly
//          offset: [11,3],
          effect: 'fade',
          offset: [1,3],
          position: 'center left',
          predelay: 100,
          relative: true,
          onBeforeShow: function(e, position) {
            if (this.getTrigger().closest('li').is('.active')) {
              this.hide(); // @TODO not working
            }
          }
        })
        .dynamic({});
        $index.find('li.tooltip-inside div').not('.tooltip-trigger').wrap('<div class="tooltip"></div>');


      $index.find('li').once('gazprom-click', function() {
        $(this).bind('click.gazprom', function(e) {
          e.preventDefault();
          $(this).find('a').trigger('click');
          return false;
        });
      });
        
      // attach click handler to the anchor
      // (the tooltip-trigger triggers the anchor on click)
      $index.find('li a').once('gazprom-click', function() {
        var $indexAnchor = $(this);
        $indexAnchor.bind('click.gazprom', function(e) {
          e.preventDefault();
          var $anchor = $(this);
          var $current = $index.find('li.active');
          var currentPos = $index.find('li').index($current);
          var $container = $anchor.closest('li');
          options.autoScroll = false;
          var pos = $index.find('li a').index($(this));
          var delta = Math.abs(pos - currentPos);
          var $item = $($items.get(pos));
          _scrollToItem($item, options.scrollDuration + (delta * options.scrollDuration * .5));
          return false;
        });
      });
      
        var currentPos = 0;
        var $room = $index.closest('.content-room-wrapper');
        var timeoutID = 'autoscroll-' + $room.attr('id');
        $room.bind('room-activation.verticalList', function() {
          $.doTimeout( timeoutID, options.autoScrollInterval, function() {
            if (options.autoScroll === true) {
              currentPos++;
              if (currentPos > $items.length - 1) currentPos = 0;
              var $item = $($items.get(currentPos));
              _scrollToItem($item, options.scrollDuration);
              return true; // do it again
            } else {
              return false;
            }
          });
        }).bind('room-deactivation.verticalList', function() {
          $.doTimeout( timeoutID ); // stop
        });
       
      function _scrollToItem($item, duration, skipImageRotation) {
        var pos = $items.index($item);
        if (typeof skipImageRotation == 'undefined') skipImageRotation = false;
        if (pos < 0) return;
        var $newActive = $($index.find('li').get(pos));
        $index.find('li.active').removeClass('active');
        $newActive.addClass('active');
        $items.removeClass('active');
        $item.addClass('active');
        
        // rotate images (if there are more than one)
        if ($item.find('img.display-later').length > 0 && !skipImageRotation) {
          var $current = $item.find('img').not('.display-later');
          var $next = $current.next('.display-later');
          if ($next.length == 0) {
            $next = $current.closest('li').find('.display-later').first();
          }
          if ($next.length > 0) {
            $current.hide().removeClass('display-now').addClass('display-later');
            $next.show().removeClass('display-later').addClass('display-now');
          }
        }
        
        $newActive.find('div.tooltip-trigger').tooltip().hide();

        var $slider = $listWrapper.find('.view-content'),
          newTop = $item.position().top * -1;
        if (Modernizr.csstransitions) {
          $slider.addClass('animate').css({
            '-webkit-transition': 'top ' + duration + 'ms ' + options.css3easing,
            '-moz-transition': 'top ' + duration + 'ms ' + options.css3easing,
            '-ms-transition': 'top ' + duration + 'ms ' + options.css3easing,
            '-o-transition': 'top ' + duration + 'ms ' + options.css3easing,
            'transition': 'top ' + duration + 'ms ' + options.css3easing
          });
          $listWrapper.trigger('scrollList-scroll-start');
          $slider.css({top: newTop});
          $.doTimeout(duration + 10, function() {
              $listWrapper.trigger('scrollList-scroll-stop');
          });
        } else if (!$('html').is('.ie8, .ie7')) {
          $listWrapper.trigger('scrollList-scroll-start');
          $slider.stop(true).animate({top: newTop}, {
            duration: duration,
            easing: options.easing,
            complete: function() {
              $listWrapper.trigger('scrollList-scroll-stop');
            }
          });
        } else {
          // scrollTo is still best solution for IE8
          $listWrapper.stop(true).scrollTo($item, {
            duration: duration,
            easing: options.easing,
            onAfter: function() {
            }
          });
        }
      }
      
      function _sizeItemRows() {
        var parentHeight = $this.closest(options.parentHeightSelector).height(),
          totalHeight = parentHeight * $items.length;
        $listWrapper.css({
          height: parentHeight,
          overflow: 'hidden'
        });
        $items.css('height', parentHeight);
        $items.closest('.view-content').css({height: totalHeight});
        
        // sync scroll to the active item
        _scrollToItem($items.filter('.active'), 0, true);
      }
    });
  }
  
  $.fn.parallax = function(configArray) {
    
    // only works with one element
    var $scroller = $($(this).get(0));
    
    // store the orginal tops of the layers (incase there are any offsets)
    var originalTops = [];
    $.each(configArray, function(index, config) {
      config.originalTop = parseInt(config.layer.css('top'));
      if (config.zIndex) config.layer.css('z-index', config.zIndex);
      if (config.adjustHeight) {
        config.layer.css({
          bottom: 'auto',
          height: Math.ceil($scroller.find('.view-content').height() * config.speed)
        });
      }
    });
    // bind scroller function
    if ($('html').is('.ie8, .ie7')) {
      $scroller.unbind('scroll.parallax').bind('scroll.parallax', $.throttle(1, true, _shiftLayers_scrollTo));
      // As of Mar 26 2012, we are no longer using .scrollTo to move the scrollingList, except for IE8/7. We are either
      // using CSS3 transitions on the top property, or animating the top property.
    } else {
      // bind step watcher. 
      var trackSteps = false;
      var $slider = $scroller.find('.view-content');
      $scroller.bind('scrollList-scroll-start', function() {
        trackSteps = true;
        setTimeout(_shiftLayers, 30);
      }).bind('scrollList-scroll-stop', function() {
        trackSteps = false;
      });
    }
    
    function _shiftLayers_scrollTo() {
      // how far have we moved
      var delta = $scroller.scrollTop();
      for(index = 0; index < configArray.length; index++) {
        // adjust this layer
        var config = configArray[index];
        config.layer.css('top', config.originalTop - (delta * config.speed));
//        config.layer.css('marginTop',  -1 * delta * config.speed);
      }
    }
    
    function _shiftLayers() {
        var delta = $slider.position().top * -1, index, config;
        //console.log(delta);
        for(index = 0; index < configArray.length; index++) {
          // adjust this layer
          config = configArray[index];
          config.layer.css('top', config.originalTop - Math.floor(delta * config.speed));
  //        config.layer.css('marginTop',  -1 * delta * config.speed);
        }
      if (trackSteps) setTimeout(_shiftLayers, 30);
    }
    
    // return jQuery chain
    return $(this);
    
  }
  
  $.fn.variableScroller = function(options) {
    var settings = $.extend({
      viewInnerSelector: '.view-content ul.item-list',
      rowSelector: this.viewInnerSelector, // not really a row.. see _itemsPerView()
      itemSelector: '.view-content ul.item-list li',
      usePager: false,
      scrollButtons: true,
      duration: 1000,
      staticContent: false
    }, options);
  
    return $(this).once('variable-scroller', function() {
      var $container = $(this);
      $container.wrap('<div class="variable-scroller-wrapper"></div>');

      if (settings.scrollButtons === true) {
        $container.before('<div class="prev"></div>');
        $container.after('<div class="next"></div>');
        $container.after('<div class="padding-right"></div>'); // css crap to cover incoming scrolling items
      }
      // pager gets created in _updatePager()
      
      var $wrapper = $container.closest('.variable-scroller-wrapper');
      var $prevButton = $wrapper.find('.prev');
      var $nextButton = $wrapper.find('.next');
      var $firstItem = $container.find(settings.itemSelector + ':first');
      var $lastItem = $container.find(settings.itemSelector + ':last');
      
      var vars = $.extend({
        container: $container,
        wrapper: $wrapper,
        viewInnerSelector: settings.viewInnerSelector,
        rowSelector: (settings.rowSelector || settings.viewInnerSelector),
        itemSelector: settings.itemSelector,
        prev: $prevButton,
        next: $nextButton,
        firstItem: $firstItem,
        lastItem: $lastItem,
        totalItemCount: 0,
        itemsPerRequest: 0,
        itemsPerView: 0,
        currentPageNum: 1,
        $pager: null
      }, settings);
      // @TODO shouldn't we just pass around settings?
      
      // initialize
      $container.css('overflow', 'hidden');
      $container.children(':first').css('width', '10000%');
      $container.find('ul.pager').css('display', 'none');

//      // always try and load one more page of content (so content is ready to be scrolled in)
//      _loadMoreContent(vars);

      // grab the (possible) total item count from the View's footer
      vars.totalItemCount = Number($container.find('.view-footer span.view-total-count').text());
      // how many items get loaded with each AJAX call (hint, at initialization, it's the current total)
      vars.itemsPerRequest = $container.find(vars.itemSelector).length;
      // how many items fit in the current scroller view
      vars.itemsPerView = _itemsPerView(vars);
      // build the pager (if needed);
      _updatePager(vars);
      // bind a handler for change to the container width
      if (vars.container.closest('.step-width').length == 1) {
        vars.container.closest('.step-width').bind('step-width-resize.variableScroller', function() {
          _updateDisplay(vars);
        });
      } else {
        $(window).bind('resizeComplete.variableScroller', function() {
          _updateDisplay(vars);
        });
      }
      vars.container.bind('update', function() {
        _updateDisplay(vars);
      });
      
//      // always try and load one more page of content (so content is ready to be scrolled in)
//      _loadMoreContent(vars);
      
      // first update of buttons
      _updateButtons(vars); // (also gets done, with an AJAX delay, by _loadMoreContent)
      
      // bind click events for the scrollers
      $prevButton
        .bind('click', function(e) {
          e.preventDefault();
          if ($(this).hasClass('enabled')) {
            _scrollBack(vars);
          }
        });
      $nextButton
        .bind('click', function(e) {
          e.preventDefault();
          if ($(this).hasClass('enabled')) {
            _scrollForward(vars);
          }
        })
        
    });
    
    function _scrollForward(vars) {
      var amount = vars.container.width();
      if (amount * 2 > vars.lastItem.position().left) {
        amount = vars.lastItem.position().left - amount + vars.lastItem.outerWidth();
      }
      vars.currentPageNum++;
      _updatePageNum(vars);
      vars.container.stop(true,false).scrollTo({top: 0, left: '+=' + amount + 'px'}, vars.duration, {onAfter: function() {
        _updateButtons(vars);
        _loadMoreContent(vars);
      }});
    }
    
    function _scrollBack(vars) {
      var amount = vars.container.width();
      if (amount > vars.container.scrollLeft()) {
        amount = vars.container.scrollLeft();
      }
      vars.currentPageNum--;
      _updatePageNum(vars);
      vars.container.stop(true,false).scrollTo({top: 0, left: '-=' + amount + 'px'}, vars.duration, {onAfter: function() {
          _updateButtons(vars);
      }});
    }
    function _scrollToPage(vars, pageNum) {
      if (!pageNum) return;
      var position = vars.container.width() * (pageNum - 1);
      var totalItemsNeeded = (pageNum - 1) * vars.itemsPerView + 1;
            vars.currentPageNum = pageNum;
            _updatePageNum(vars);
      if (vars.container.find(vars.itemSelector).length < totalItemsNeeded) {
        _loadMoreContent(vars, function(){
          _scrollToPage(vars, pageNum);
        });
      } else {
        vars.container.stop(true,false).scrollTo({top:0, left: position+'px'}, vars.duration, {onAfter: function() {
            var $pagerItems = vars.$pager.find('.variable-scroller-pager-item');
            _updateButtons(vars);
            _loadMoreContent(vars); // always good to load one more page
        }})
      }
    }
    
    function _updateDisplay(vars) {
      vars.itemsPerView = _itemsPerView(vars);
      _updatePager(vars);
      _updateButtons(vars);
    }
    
    function _updateButtons(vars) {
      if (!_isInView(vars.firstItem, vars.container)) {
        vars.prev.addClass('enabled').removeClass('disabled');
      } else {
        vars.prev.removeClass('enabled').addClass('disabled');
      }
      if (!_isInView(vars.lastItem, vars.container)) {
        vars.next.addClass('enabled').removeClass('disabled');
      } else {
        vars.next.removeClass('enabled').addClass('disabled');
      }
      
    }
    function _loadMoreContent(vars, callback) {
      var pagerNextHref = vars.container.find('ul.pager .pager-next a').attr('href');
      if (!pagerNextHref || vars.staticContent === true) return;
      
      var view_name, display_id;
      var viewIDsObj = Drupal.gazprom.utility.getViewIDs(vars.container.find('.view:first'));
      if (!viewIDsObj) return; // something went wrong;
      view_name = viewIDsObj.view_name;
      display_id = viewIDsObj.view_display_id;
//      // is this a hack? find the view_name and view_display_id values from the classes
//      var classArray = vars.container.find('.view:first').attr('class').split(' ');
//      var view_name, display_id;
//      $.each(classArray, function(index, value) {
//        if (value.substring(0,8) == 'view-id-') {
//          view_name = value.replace('view-id-', '');
//        }
//        if (value.substring(0,16) == 'view-display-id-') {
//          display_id = value.replace('view-display-id-', '');
//        }
//      });
//      if (!view_name && ! display_id) return; // something went wrong
      
      href = Drupal.gazprom.utility.getViewsAjaxPath()
            + '?view_name=' + view_name + '&view_display_id=' + display_id + '&' + pagerNextHref.split('?')[1];
      $.get(href, function(result) {
        var $newContent = $(result[1].data).find(vars.viewInnerSelector).children(); //.find('.view-content ul.item-list, .view-content table tbody').children();
        var $newPager = $(result[1].data).find('ul.pager').children();
        
        if (vars.rowSelector != vars.viewInnerSelector) {
          // looks to be a table grid
          $newContent = $(result[1].data).find(vars.rowSelector);
          vars.container.find(vars.rowSelector).each(function(pos, elem) {
            var $row = $(this);
            var $newCells = $($newContent.get(pos)).children();
            $row.find('td').attr('class','');
            $newCells.attr('class','');
            $row.append($newCells);
            //$(this).append($($newContent.get(pos)).children());
          Drupal.attachBehaviors($newCells)
          // make sure new content is attached to handlers
          Drupal.gazprom.init.anchorHandlers($newCells);
          });
        } else {
          // looks to be floating LI's
          vars.container.find(vars.viewInnerSelector).append($newContent);
          Drupal.attachBehaviors($newContent)
          // make sure new content is attached to handlers
          //Drupal.gazprom.init.anchorHandlers($newContent);
        }
        vars.container.find('ul.pager').empty().append($newPager); // this is the Views pager, not our page
        
        // must update the session vars to the new lastItem
        vars.lastItem = vars.container.find(vars.itemSelector + ':last');
        
        if (typeof callback == 'function') {
          callback();
        }
        // update buttons
        _updateButtons(vars);        
      });
    }
    
    function _updatePager(vars) {
      if ((vars.totalItemCount == 0) || (vars.usePager !== true)) return;
      var numOfPages;
      vars.itemsPerView != 0 ? numOfPages = Math.ceil(vars.totalItemCount / vars.itemsPerView) : numOfPages = 0;
      if (numOfPages < 2 ) {
        // pager not needed .. if this is after resize, clear out any DIVs that might have been added previously
        $(vars.$pager).remove();
        vars.$pager = null;
        // @todo also get rid of .pager-inside class?
        return;
      }
      if (vars.container.find('.view-footer').length == 0) {
        vars.container.append('<div class="view-footer variable-scroller-added"></div>');
      }
      //vars.container.find('.view-footer span.view-page-count').remove();
      //vars.container.find('.view-footer').append('<span class="view-page-count"> ' + vars.itemsPerView + ' per page = ' + numOfPages + ' pages</span>');
      var pagerHTML = '';
      for (i = 1; i <= numOfPages; i++) {
        pagerHTML = pagerHTML + '<span class="variable-scroller-pager-item">' + i + '</span>';
      }
      pagerHTML = '<div class="variable-scroller-pager">' + pagerHTML + '</div>';
      
      // determine where to put the pagerHTML div
      var $specificPaginationLocation = vars.wrapper.closest('.content-room-wrapper').find('.pagination-goes-here');
      var $pager, $pagerItems;
      if ($specificPaginationLocation.length > 0) {
        $specificPaginationLocation.find('.variable-scroller-pager').remove();
        $specificPaginationLocation.append(pagerHTML);
        $pager = $specificPaginationLocation.find('.variable-scroller-pager');
        $pagerItems = $specificPaginationLocation.find('.variable-scroller-pager-item');
        $specificPaginationLocation.closest('.page-tools').addClass('pager-inside');
      } else {
        vars.wrapper.find('.variable-scroller-pager').remove();
        vars.wrapper.append(pagerHTML);
        $pager = vars.wrapper.find('.variable-scroller-pager');
        $pagerItems = vars.wrapper.find('.variable-scroller-pager-item');
      }
      if ($pagerItems.filter('.active').length == 0) {
        // no active pager number, so assume first should be
        $pagerItems.first().addClass('active');
      }
      $pagerItems.unbind('click.variablePager').bind('click.variablePager', function() {
        _scrollToPage(vars, parseInt($(this).text()));
      });
      vars.$pager = $pager;
      vars.container.scrollTo({top:0, left:0}); //_scrollToPage(vars,1);
    }
    
    function _updatePageNum(vars) {
      if ((vars.totalItemCount == 0) || (vars.usePager !== true)) return;
      if (vars.currentPageNum < 1) vars.currentPageNum = 1;
      vars.$pager.find('.variable-scroller-pager-item').filter('.active').removeClass('active');
      $(vars.$pager.find('.variable-scroller-pager-item').get(vars.currentPageNum - 1)).addClass('active');
    }

    function _itemsPerView(vars) {
      /* this is a crazy way of counting up how many items are visible .. this can handle a ul li arrangement or a tr td arrangement */
      /* tr td arrangement has multiple columns in each row. Some of the columns will be off view */
      var currentScrollLeft = vars.container.scrollLeft();
      vars.container.scrollTo({top: 0, left: 0}, 0);
      var itemsPerView = 0;
      vars.container.find(vars.rowSelector).each(function() {
        var innerSelector = ($(this).get(0).tagName.toLowerCase() == 'tr' ? 'td' : 'li');
        $(this).find(innerSelector).each(function() {
          if (_isInView($(this), vars.container)) {
            itemsPerView++;
          } else {
            return false; // exit each loop
          }
          return true; // continue loop
        });
      });
      vars.container.scrollTo({top: 0, left: currentScrollLeft}, 0);
      return itemsPerView;
    }
    
    function _isInView($item, $container) {
      if ($item.length == 0) return false;
      var itemLeft = $item.position().left;
      var containerWidth = $container.width();
      return ((itemLeft >= 0) && (itemLeft < containerWidth));
    }
  }
  
  $.fn.viewsSelector = function(options) {
    /**
     * Handles the views on the management page
     **/
    var defaults = {
      hideMenuIfOnlyOne: false
    }
    return this.once('viewsSelector', function(){
      var settings = $.extend({}, defaults, options);
      var $view = $(this);
      $view.addClass('view-selector-menu');
      var $list = $view.find('.view-content > .item-list > ul');
      
      var $menuItems = $list.find('li.views-row').each(function() {
        $(this).find('.views-field').first().addClass('selector');
      });
      $menuItems = $list.find('.views-field.selector');
      $list.before('<div class="selector-menu"></div>');
      var $selectorMenu = $view.find('.selector-menu');
      $selectorMenu.append($menuItems);
      $list.find('li.views-row').hide();
      
      $menuItems.unbind('click.viewsSelector').bind('click.viewsSelector', _activateRow).each(function() {
        $(this).attr('title', $(this).find('span').text());
      });
      $menuItems.first().trigger('click.viewsSelector');
      if (settings.hideMenuIfOnlyOne && $menuItems.length == 1) {
        $menuItems.hide();
      }
      
      function _activateRow(e) {
        e.preventDefault();
        var $selector = $(this);
        $menuItems.filter('.active').removeClass('active');
        $selector.addClass('active');
        var index = $menuItems.index($selector);
        var $currentlySelected = $list.find('li.views-row.selected-active');
        if ($currentlySelected.length > 0) {
          $currentlySelected.fadeOut(250, function() {
            $(this).removeClass('selected-active');
            $list.find('li.views-row:nth-child(' + (index + 1) + ')').addClass('selected-active').fadeIn(250);
            $menuItems.filter('.active').removeClass('active');
            $selector.addClass('active');
          });
        } else {
          $list.find('li.views-row:nth-child(' + (index + 1) + ')').addClass('selected-active').fadeIn(250);
        }
      }
    })
  }
  
  $.fn.sizeRoom = function () {
    
    var footerHeight = $('#footer-page').height();
    
    return $(this).once('sizeRoom', function() {
      var $room = $(this);      
      $(window).bind('resizeComplete.sizeRoom', function() {
        _doResize($room);
      });
      _doResize($room);
    });
    
    // @TODO: Consider something where we only have one resizeComplete event rather than one for each room.
    
    function _doResize($room) {
      //console.log('Resizing: ' + $room.attr('id'));
      var winWidth =  Drupal.gazprom.winWidth; 
      var winHeight = Drupal.gazprom.winHeight; 


      var roomWidth = winWidth;
      if (!Drupal.gazprom.singlePageMode) {
        roomWidth = roomWidth - $.getScrollbarWidth(); // must accomodate #scroller's scrollbar
      } 
      var roomHeight = winHeight; // - footerHeight;
      if (roomHeight < Drupal.gazprom.shortRoom) {
        $('body').addClass('short-window')
        roomHeight = Drupal.gazprom.minRoomHeight;
      } else {
        $('body').removeClass('short-window');
      }
      if (roomHeight < Drupal.gazprom.minRoomHeight) roomHeight = Drupal.gazprom.minRoomHeight;
      if (roomWidth < Drupal.gazprom.minRoomWidth) roomWidth = Drupal.gazprom.minRoomWidth;
      
      if (!Drupal.gazprom.singlePageMode) {
        $room.css({
          width: roomWidth,
          height: roomHeight,
          minHeight: null,
          'float': 'left'
        })     
      } else {
        $room.css({
          width: roomWidth,
          minHeight: roomHeight,
          'float': 'left'
        })     
      }
    }

  }
  
  $.fn.stepWidth = function() {
    return $(this).once('stepWidth', function() {
      var $container = $(this);
      var $parent = $container.parent();
      var settings = {
//        defaultStep: 430
        defaultStep: 200
      }, stepSize = settings.defaultStep, stepMin = 1 * stepSize, minWidth =0, maxWidth = 1920, widthSubtract = 0;
      
      var classArray = $container.attr('class').split(' ');
      $.each(classArray, function(index, value) {
        if (value.substring(0,10) == 'step-size-') {
          stepSize = parseInt(value.replace('step-size-',''));
        }
        if (value.substring(0,9) == 'step-min-') {
          stepMin = parseInt(value.replace('step-min-', '')) * stepSize;
        }
        if (value.substring(0,10) == 'min-width-') {
          minWidth = parseInt(value.replace('min-width-', ''));
        }
        if (value.substring(0,10) == 'max-width-') {
          maxWidth = parseInt(value.replace('max-width-', ''));
        }
        if (value.substring(0,15) == 'width-subtract-') {
          widthSubtract = parseInt(value.replace('width-subtract-', ''));
        }
      });

      $(window).bind('resizeComplete.stepWidth', function() {
        var parentWidth = $parent.width();
        var newWidth = Math.floor(parentWidth / stepSize) * stepSize;
        if (widthSubtract > 0) newWidth = newWidth - widthSubtract;
        if (newWidth < stepMin) newWidth = stepMin;
        if (newWidth < minWidth) newWidth = minWidth;
        if (newWidth > maxWidth) newWidth = maxWidth;
        $container.css('width', newWidth);
        //console.log('setWidth, newWidth = ' + newWidth);
        $container.trigger('step-width-resize'); // this signals children that this step-width container has changed size
      }).trigger('resizeComplete.stepWidth');
      
    });
  }
  
  $.fn.inlineContentCycler = function(options) {
    
    var defaults = {
      duration: 1000,
      easing: 'swing'
    };
    
    return $(this).not('.inline-content-cycler-processed').each(function(i, elem) {_attach($(elem), options);});
    
    function _attach($element, options) {
      var settings = $.extend({}, defaults, options);
      
      var $listContainer = $element.is('ul') ? $element : $element.find('ul');
      if ($listContainer.length == 0) return;
      $listContainer.addClass('item-list');
      $element.addClass('inline-content-cycler-processed');

      var $listItems = $listContainer.find('li'), listClass = '';
      if ($listItems.length == 1) {
        listClass = 'single';
      } else if ($listItems.length == 2) {
        listClass = 'one-one';
      } else if ($listItems.length == 3) {
        listClass = 'one-two';
        $listItems.first().addClass('first');
        $listItems.last().addClass('last');
      } else if ($listItems.length > 3) {
        listClass = 'paged-list';
      }
      
      $listContainer.wrap('<div class="inline-content-cycler-wrapper">');
      var $wrapper = $listContainer.parent();
      $wrapper.addClass(listClass).append('<div class="clearfix">');
      $wrapper.data('settings', settings);

      $listItems //.find('img')
        .unbind('click').bind('click.inline-cycler', _listItemClick)
        .css({cursor: 'pointer'});
        
      $listItems.each(function() {
        var $li = $(this);
        var $item = $li.children('img:first');
        if ($item.attr('data-youtube')) {
          $li.append('<div class="video-overlay">');
        }
      });


      if ($listItems.length > 3) {
        $listContainer.wrap('<div class="inline-content-cycler-scroll">');
        $wrapper.append('<div class="inline-content-cycler-index"><ul class="index-list">');
        var $indexList = $wrapper.find('.inline-content-cycler-index > ul.index-list');
        $listItems.each(function() {
          var $li = $(this), $item = $li.children(':first'), imgSrc;
          if ($item.attr('data-thumbnail')) {
            imgSrc = $item.attr('data-thumbnail');
          } else if ($item.attr('src')) {
            imgSrc = $item.attr('src');
          } else {
            imgSrc = null;
          }

          if (imgSrc) {
            var $indexLI= $('<li>');
            $indexLI.append('<img>');
            $indexList.append($indexLI);
            $indexLI.find('img').attr('src', imgSrc).addClass('inline-content-cycler-thumbnail');
            $indexLI.bind('click.inline-cycler', _indexClick).css({cursor: 'pointer'});;
            $indexLI.data('references', $li);
            
            if ($item.attr('data-youtube')) {
              $indexLI.append('<div class="video-overlay">');
            }
          }
          

        });

        $wrapper.find('.inline-content-cycler-index').variableScroller({
          viewInnerSelector: null,
          itemSelector: 'ul.index-list li',
          staticContent: true
        });
        //$listItems.first().addClass('active');
      }
    }
    
    function _indexClick(e) {
      e.preventDefault();
      var $indexLI = $(this);
      var $li = $indexLI.data('references');
      if (!$li.is('.active')) {
        _activateItem($li); // scroll it into place
      } else {
        _deactivateOld($li.closest('.inline-content-cycler-wrapper'));
      }
      
      return false;
    }
    
    function _listItemClick(e) {
      e.preventDefault();
      var $listItem = $(this);
      var $wrapper = $listItem.closest('.inline-content-cycler-wrapper');
      var $item = $listItem.children('img:first');
      
      _deactivateOld($wrapper.closest('.node'));
      $listItem.addClass('active');

      if ($item.attr('data-youtube') && (!$item.is('.missing'))) {
        var $player = $('<iframe width="' + $item.width() + '" height="' + $item.height() + '" src="" frameborder="0" allowfullscreen></iframe>');
        $item.after($player);
        $player.attr('src', 'http://www.youtube.com/embed/' + $item.attr('data-youtube') + '?rel=0&autoplay=1&autohide=1');
        $listItem.children().not('iframe').addClass('missing').fadeOut(500);
      }

      return false;
    }
    
    function _activateItem($listItem) {
      var $wrapper = $listItem.closest('.inline-content-cycler-wrapper');
      var settings = $wrapper.data('settings');
      var $scroll = $wrapper.find('.inline-content-cycler-scroll');
      _deactivateOld($wrapper);
      $scroll.scrollTo($listItem, {
        duration: settings.duration,
        easing: settings.easing,
        onAfter: function() {
         $listItem.trigger('click');
        }
      });
    
    }
    
    function _deactivateOld($wrapper) {
      var $oldActives = $wrapper.find('.item-list li.active');
      $oldActives.each(function() {
        var $oldActive = $(this);
        if ($oldActive.children('.missing').length > 0) {
          $oldActive.children('iframe').remove(); // remove youtube iframe element
          $oldActive.children('.missing').removeClass('missing').fadeIn(500);
        }
        $(this).removeClass('active');
      });
    }
    
    function _playVideo($item) {
      
    }
  }
})(jQuery);

(function($) {
  $.easing.easeInOutSine = function (x, t, b, c, d) {
    return -c/2 * (Math.cos(Math.PI*t/d) - 1) + b;
  }
  $.easing.easeOutCirc = function (x, t, b, c, d) {
	return c * Math.sqrt(1 - (t=t/d-1)*t) + b;
  }
  $.easing.easeInOutCirc = function (x, t, b, c, d) {
      if ((t/=d/2) < 1) return -c/2 * (Math.sqrt(1 - t*t) - 1) + b;
      return c/2 * (Math.sqrt(1 - (t-=2)*t) + 1) + b;
  }
  $.easing.easeOutCubic =  function (x, t, b, c, d) {
    return c*((t=t/d-1)*t*t + 1) + b;
  }
  $.easing.easeInOutCubic = function (x, t, b, c, d) {
      if ((t/=d/2) < 1) return c/2*t*t*t + b;
      return c/2*((t-=2)*t*t + 2) + b;
  }
  $.easing.easeOutExpo = function (x, t, b, c, d) {
    return (t==d) ? b+c : c * (-Math.pow(2, -10 * t/d) + 1) + b;
  }
  $.easing.easeInOutSine = function (x, t, b, c, d) {
		return -c/2 * (Math.cos(Math.PI*t/d) - 1) + b;
  }
  // easing functions from http://gsgd.co.uk/sandbox/jquery/easing/jquery.easing.1.3.js
  // see: http://james.padolsey.com/demos/jquery/easing/
  // also: http://jqueryui.com/demos/effect/easing.html
        
    
})(jQuery);


(function($) {
  
  var imageList = [];
  
  $.fn.fluidCenterAlignImage = function(options) {
    /*
     * Scale and align images to fit container
     * Alignment will be vertical and horizontal.
     * Scaling and cropping will be decided based on
     * Image aspect and container aspect
     */
    
    var settings = $.extend({
      containerSelector: '.fancy-background-image-container',
      eventName: 'resizeFluidImages',
      safeOffset: {top: 0, left: 0, right: 0, bottom: 0},
      useAbsoluteSizes: true,
      fitInContainer: false
    }, options);
    
    function _triggerImageResizes() {
      $('img.fluid-center-align').removeClass('fluid-center-align-done').trigger(settings.eventName);
    }
    $(window).unbind('resizeComplete.fluidCenterAlignImage')
      .bind('resizeComplete.fluidCenterAlignImage', _triggerImageResizes );

    return $(this).each(function(){
      var $image = $(this);
      var $container = $image.closest(settings.containerSelector);
      if ($container.length == 0) return;
      
      $image.hide();     //console.log($image.attr('src'));
      
      var imageWidth = -1, imageHeight = -1;
      
      // Bind up custom resizeFluidImages event hanler (event name can be altered in settings)
      $image.unbind(settings.eventName).bind(settings.eventName, function(e) {
        if ($image.hasClass('fluid-center-align-done')) return;
        //$image.removeClass('fluid-center-align-done');
        if (e.newImage ? e.newImage : false || imageWidth == -1 || imageHeight == -1) {
          imageWidth = imageHeight = -1;
          _loadImage($image, function() {
            _fluidCenterAlignImage({$image: $image, width: imageWidth, height: imageHeight}, $container);
            if (!$image.is('.display-later')) $image.show();
            if (typeof settings.callback == 'function') settings.callback.call();
          });
        } else {
          _fluidCenterAlignImage({$image: $image, width: imageWidth, height: imageHeight}, $container);
          if (typeof settings.callback == 'function') settings.callback.call();
          if (!$image.is('.display-later')) $image.show();
        }
      }).addClass('fluid-center-align');

      // Trigger our custom event handler, which will make sure
      // .. image is loaded (or cached)
      $image.trigger(settings.eventName);
      
      function _loadImage($image, callback) {
        var img = new Image();
        $(img).bind({
          load: function() {
            //console.log('load triggered for ' + $(this).attr('src'));
            imageWidth = this.width;
            imageHeight = this.height;
            if (typeof callback == 'function') callback.call();
          },
          error: function() {
            //console.log('error triggered for ' + $(this).attr('src'));
          }
        });
        img.src = $image.attr('src');
        return;
        // For reasons I can't quite understand, it seems that it is possible
        // .. for this handler to not fire at all. If you put a breakpoint somewhere
        // .. in code after this, it seems that the load finishes but nothing happens
      }

    })


  function _fluidCenterAlignImage(imageData, $container) {

    var $image = imageData.$image;
    if (imageData.width <= 0 || imageData.height <= 0) {
      return; // something went wrong
      //imageData = _getNaturalDimensions($image);
    }
    var imageWidth = imageData.width;
    var imageHeight = imageData.height;

    $image.removeAttr('width').removeAttr('height'); // make sure attributes don't overrule our CSS

    // grab the container's width & height
    var viewerHeight = $container.outerHeight(),
      viewerWidth = $container.outerWidth(),
      horizontalOffset, verticalOffset;
    if ((imageWidth / imageHeight) > (viewerWidth / viewerHeight) || (settings.fitInContainer && (imageWidth / imageHeight < .85))) {
      if (!settings.useAbsoluteSizes) {
        $image.css({width: 'auto', height: '100%', marginTop: '0', marginLeft: '0'});
      } else {
        $image.css({width: 'auto', height: viewerHeight, marginTop: '0', marginLeft: '0'});
      }
      // see if the new width is now pushed past the viewport
      var newWidth = (viewerHeight / imageHeight) * imageWidth;
      // must calculate what the width has become (web browser might not tell us yet)
      if (newWidth > viewerWidth) {
        horizontalOffset = Math.floor((newWidth / 2) - (viewerWidth / 2) - ((settings.safeOffset.left + settings.safeOffset.right) / 2));
        $image.css({marginLeft: '-' + horizontalOffset + 'px', marginRight: 'auto'});
      } else if (newWidth < viewerWidth) {
        horizontalOffset = Math.floor((viewerWidth / 2) - ( newWidth/ 2) - ((settings.safeOffset.left + settings.safeOffset.right) / 2));
        $image.css({marginLeft: horizontalOffset + 'px', marginRight: 'auto'});
      }
      
    } else {
      if (!settings.useAbsoluteSizes) {
        $image.css({width: '100%', height: 'auto', marginTop: '0', marginLeft: '0'});
      } else {
        $image.css({width: viewerWidth, height: 'auto', marginTop: '0', marginLeft: '0'});
      }
      // see if the new height is now pushed past the viewport
      var newHeight = (viewerWidth / imageWidth) * imageHeight;
      // must calculate what the height has become (web browser might not tell us yet)
      if (newHeight > viewerHeight) {
        verticalOffset = Math.floor((newHeight / 2) - (viewerHeight / 2) - ((settings.safeOffset.top + settings.safeOffset.bottom) / 2));
        $image.css({marginTop: '-' + verticalOffset + 'px'});
      }
    }
    $image.addClass('fluid-center-align-done');
    //console.log('fluid-center-align: ' + $image.attr('src'));
  }

}
  
  $.fn.upgradeBackgroundImages = function() {
    var $window = $(window);

    return $(this).once('upgradeOnResize', function() {
      var $image = $(this);
      var $container = $image.closest('.content-room-wrapper');
      if ($container.length == 0) $container = $image.closest('.content-floor-wrapper');
      $window.bind('resizeComplete.upgradeImages', $.debounce(500, function() {
        _doUpgrade($image, $container);
      }) );
      _doUpgrade($image, $container);
    });

    function _doUpgrade($image, $container) {
      //var maxWidth = $(window).width();
      var maxWidth = $container.width();
      var desiredWidth;
      if (maxWidth <= 480) {
        desiredWidth = 480;
      } else if (maxWidth <= 720) {
        desiredWidth = 720;
      } else if (maxWidth <= 960) {
        desiredWidth = 960;
      } else if (maxWidth <= 980) {
        desiredWidth = 980;
      } else if (maxWidth <= 1200) {
        desiredWidth = 1200;
      } else if (maxWidth <= 1440) {
        desiredWidth = 1440;
      } else if (maxWidth <= 1680) {
        desiredWidth = 1680;
      } else if (maxWidth <= 1680) {
        desiredWidth = 1680;
      } else {
        desiredWidth = 9999
      }
      
      var newSrc = $image.attr('src');
      newSrc = newSrc.replace(/\/backgrounder(.*?)\//, '/backgrounder-' + desiredWidth + '/');
      if (newSrc == $image.attr('src')) return;
      
      _loadNewImage(newSrc, function() {
        //console.log('upgrade to: ' + newSrc)
        if ($image.hasClass('fluid-center-align')) {
          var event = $.Event('resizeFluidImages');
          event.newImage = true;
          $image.attr('src', newSrc).trigger(event);
      } else {
          $image.attr('src', newSrc);
        }
      }, function() {
        // error, didn't load
        // @TODO consider trying to next higher size?
        //console.log('error with: ' + newSrc)
        return;
      });


      function _loadNewImage(newSrc, callback, errorCallback) {
        var img = new Image();
        img.onload = function() {
          if (typeof callback == 'function') callback.call();
          delete(img);
        }
        img.onerror = function() {
          if (typeof errorCallback == 'function') errorCallback.call();
          delete(img);
        }
        img.src = newSrc;
        return;
      }
    }

  }
  
 
})(jQuery);

(function($) {
  /**
   * Content Paginator plug-in
   * Custom developed for Gazprom International site by
   * jon@system-werks.com 2012-01-16
   **/
  
  var defaults = {
    containerHeight: 250,
    containerWidth: 'auto',
    adjustContainer: true,
    prevButtonText: 'Prev',
    nextButtonText: 'Next',
    middleText: 'More',
    effect: 'fadeOut',
    effectDefaults: {
      duration: 150
    },
    externalHandoff: false,
    externalFn: null
  }
  
  var methods = {
    init: function(options) {
      var settings = $.extend({}, defaults, options);
      var $container = $(this);
      if ($container.length == 0) return;

      // cleaup DIVs that don't belong .. is this a hack? better way to reduce content down to mainly <p> elements?
      $container.find('div > p').unwrap(); // WYSIWYG editor sometimes seems to wrap Ps inside DIVs
      // create content containers and move content into pool
      var $elements = $container.children();
      $elements.wrapAll('<div class="content-paginator-content-current">');
      $container.prepend('<div class="content-paginator-previous-content" style="display:none">');
      $container.append('<div class="content-paginator-content-pool" style="display:none">')
      $container.append('<div class="content-paginator-controls" style="display:none"><a class="prev">' + settings.prevButtonText + 
        '</a><span>' + settings.middleText + '</span><a class="next">' + settings.nextButtonText + '</a></div>');
      
      if (!settings.externalHandoff) {
        $container.find('.content-paginator-controls a.prev').bind('click', function() {
          $container.paginateContent('prev', settings);
        }).addClass('no-hijax');
        $container.find('.content-paginator-controls a.next').bind('click', function() {
          $container.paginateContent('next', settings);
        }).addClass('no-hijax');
      } else {
        $container.find('.content-paginator-controls a.prev').hide();
        $container.find('.content-paginator-controls a.next').bind('click', settings.externalFn).addClass('no-hijax');
      }
      $container.css({marginBottom: $container.find('.content-paginator-controls').outerHeight()});
      
      methods.update($container, settings);
      $(window).bind('resizeComplete.aContentPaginator', function() {
        methods.update($container, settings);
      })
    },
    update: function($container, options) {
      var settings = $.extend({}, defaults, options);
      settings = util.adjustDimensions($container, settings);
      if (settings.adjustContainer) {
        //$container.css({height: 'auto', maxHeight: settings.containerHeight, overflow: 'visible'});
        $container.css({height: settings.containerHeight, width: settings.containerWidth, overflow: 'visible'});
      } else {
        $container.css({overflow: 'visible'});
      }
      
      // if this is a true update, take a shortcut and just reset pagination so that proper
      // .. pagination can be done with current $container size
      var $page = $container.find('.content-paginator-content-current');
      var $contentPool = $container.find('.content-paginator-content-pool')
      var $previousContent = $container.find('.content-paginator-previous-content');
      $page.children().prependTo($contentPool);
      $previousContent.children().prependTo($contentPool);
      
      $container.paginateContent('next', $.extend({}, settings, {effect: 'none'}));
      return;
    },
    next: function(options) {
      var settings = $.extend({}, defaults, options);
      var $container = settings.$container = $(this);
      var $page = settings.$page = $container.find('.content-paginator-content-current');
      var $contentPool = settings.$contentPool = $container.find('.content-paginator-content-pool')
      var $previousContent = settings.$previousContent = $container.find('.content-paginator-previous-content');
      if ($contentPool.children().length == 0) return;
      settings = util.adjustDimensions($container, settings);
      if (effects[settings.effect]) {
        effects[settings.effect]['before']($container, _shiftContent, settings.effectDefaults);
      } else {
        _shiftContent();
      }
      
      function _shiftContent() {
        if ($page.children().length > 0) {
          $page.children().appendTo($previousContent);
        }
        $contentPool.children().each(function(i,elem) {
          var $poolElement = $(elem);
          
          // Check if this element has a <!--break--> marker inside
          var forceBreak = false;
          if ($previousContent.children().length == 0) {
            var breakCheck = /(^.*)(<!--break-->)(.*$)/i;
            var breakCheckResult = breakCheck.exec($poolElement.html());
            if (breakCheckResult != null) {
              var $secondHalf = $poolElement.clone();
              $poolElement.html(breakCheckResult[1]);
              $secondHalf.html(breakCheckResult[2] + breakCheckResult[3]);
              forceBreak = true;
              if ($poolElement.is(':empty') && i == 0) {
                $poolElement.html(breakCheckResult[2] + breakCheckResult[3]);
                $secondHalf = $([]);
                forceBreak = false;
              } else if ($poolElement.is(':empty')) {
                $poolElement = $([]);
              } 
              $secondHalf.prependTo($contentPool);
            }
          }
          
          $page.append($poolElement);
          var height = $page.innerHeight();
          if (height == 0 && !$page.is(':visible')) {
            height = $page.getHiddenDimensions().innerHeight;
          }
          if (height > settings.containerHeight && i != 0) {
            $poolElement.prependTo($contentPool);
            return false;
          } else {
            if (forceBreak) {
              return false;
            } else {
              return true;
            }
          }
        });
        
        if (effects[settings.effect]) effects[settings.effect]['after']($container, null, settings.effectDefaults);
        util.updateButtons($container);
      }
      // @TODO consolidate to one _shiftContent() function instead of two
    
    },
    prev: function(options) {
      var settings = $.extend(defaults, options);
      var $container = settings.$container = $(this);
      var $page = settings.$page = $container.find('.content-paginator-content-current');
      var $contentPool = settings.$contentPool = $container.find('.content-paginator-content-pool')
      var $previousContent = settings.$previousContent = $container.find('.content-paginator-previous-content');
      if ($previousContent.children().length == 0) return;
      settings = util.adjustDimensions($container, settings);
      if (effects[settings.effect]) {
        effects[settings.effect]['before']($container, _shiftContent, settings.effectDefaults);
      } else {
        _shiftContent();
      }
    
      function _shiftContent() {
        if ($page.children().length > 0) {
          $page.children().prependTo($contentPool);
        }
        $($previousContent.children().get().reverse()).each(function(i, elem) {
          var $poolElement = $(elem);
         
          // Check if this element has a <!--break--> marker inside
          var forceBreak = false;
          if ($poolElement.html() != '<!--break-->') {
            var breakCheck = /(^.*)(<!--break-->)(.*$)/i;
            var breakCheckResult = breakCheck.exec($poolElement.html());
            if (breakCheckResult != null) {
              var $firstHalf = $poolElement.clone();
              $firstHalf.html(breakCheckResult[1]);
              $poolElement.html(breakCheckResult[2] + breakCheckResult[3]);
              forceBreak = true;
              if ($poolElement.is(':empty') && i == 0) {
                $poolElement.html(breakCheckResult[1]);
                $firstHalf = $([]);
                forceBreak = false;
              } else if ($poolElement.is(':empty')) {
                $poolElement = $([]);
              } 
              $firstHalf.appendTo($previousContent);
            }
          }
          
          $page.prepend($poolElement);
          if ($page.height() > settings.containerHeight && i != 0) {
            $poolElement.appendTo($previousContent);
            return false;
          } else {
            if (forceBreak) {
              return false;
            } else {
              return true;
            }
          }
        });

        if (effects[settings.effect]) effects[settings.effect]['after']($container, null, settings.effectDefaults);
        util.updateButtons($container);
      }
    }
  }
  
  var util = {
    updateButtons: function(c) {
      var $p = c.find('.content-paginator-controls a.prev');
      var $n = c.find('.content-paginator-controls a.next');
      if (c.find('.content-paginator-previous-content').children().length > 0) {
        $p.removeClass('disabled');
      } else {
        $p.addClass('disabled');
      }
      if (c.find('.content-paginator-content-pool').children().length > 0) {
        $n.removeClass('disabled');
      } else {
        $n.addClass('disabled');
      }
      if ($p.is('.disabled') && $n.is('.disabled')) {
        c.find('.content-paginator-controls').hide();
      } else {
        c.find('.content-paginator-controls').show();
      }
    },
    adjustDimensions: function($container, settings) {
      if (settings.containerHeight == 0 || settings.containerHeight == 'auto') {
        $container.css('height', '');
        if ($container.css('maxHeight') != 'none') {
          settings.containerHeight = parseInt($container.css('maxHeight'));
        } else {
          settings.containerHeight = $container.innerHeight();
        }
      }
      if (settings.containerWidth == 0 || settings.containerWidth == 'auto') {
        $container.css('width', '');
        settings.containerWidth = $container.innerWidth();
      }
      if (settings.containerWidth == 0 || settings.containerHeight == 0) {
        var hiddenDims = $container.getHiddenDimensions();
        settings.containerWidth = hiddenDims.innerWidth;
        settings.containerHeight = hiddenDims.innerHeight;
        // This doesn't seem to always work well. Particularly for quicktabs. See the function in the call to paginateContent
      }
      return settings;
    }
  }
  
  var effects = {
    fadeOut: {
      before: function($e, callback, options) {
        if ($('html').is('.ie8, .ie7')) {
          if (typeof callback == 'function') callback.call();
          return;
        }
        var settings = $.extend({}, defaults.effectDefaults, options);
        //$e.fadeOut(settings.duration, callback);
        $e.animate({opacity: 0}, {
          duration: settings.duration,
          complete: callback
        });
      },
      after: function($e, callback, options) {
        if ($('html').is('.ie8, .ie7')) {
          if (typeof callback == 'function') callback.call();
          return;
        }
        var settings = $.extend({}, defaults.effectDefaults, options);
        //$e.fadeIn(settings.duration, callback);
        $e.animate({opacity: 1}, {
          duration: settings.duration,
          complete: callback
        });
      }
    },
    slide: {
      before: function($e, callback, options) {
        var settings = $.extend({}, defaults.effectDefaults, options);
        
      },
      after: function($e, callback, options) {
        var settings = $.extend({}, defaults.effectDefaults, options);

      }
    }
  }
  
  // make a jQuery plugin
  $.fn.paginateContent = function(parameter) {
    
    if (methods[parameter]) {
      return methods[parameter].apply(this, Array.prototype.slice.call(arguments, 1));
    }
//    else if (typeof parameter === "function" || !parameter) {
//        return methods.init.apply(this, arguments);
//    }
    else if (typeof parameter === "object" || !parameter) {
        //return methods.init.apply(this, [null, parameter]);
        return methods.init.apply(this, [parameter]);
    }
  }
  
  
})(jQuery);

(function($, window) {
  /*
   * Print Content
   * Created for Gazprom International website
   * jon@system-werks.com Jan 2012
   */
  
  
  var defaults = {
    containerSelector: 'body',
    contentSelector: '.content', // can also be an array of selector strings
    excludeSelector: null
  }
  
  // @TODO make contentSelector work as an array
  
  var methods = {
    init: function(options) {
      var settings = $.extend({}, defaults, options);
      var $printBtn = $(this);
      
      $printBtn.unbind('click').bind('click', function () {
        var $container = $printBtn.closest(settings.containerSelector);
        var selector = '';
        if (typeof settings.contentSelector == 'object') {
          selector = settings.contentSelector.join(', ');
        } else {
          selector = settings.contentSelector;
        }
        var $content = $container.find(settings.contentSelector).clone();
        if (settings.excludeSelector) {
          $content.find(settings.excludeSelector).remove();
        }
        $content.attr('style', '');
        $content.find('*').attr('style', '');
        $content.find('a').remove();
        var frame,win,doc;
        if (!$('html').is('.ie7, .ie8, .ie9')) {
          // Use a frame
          if ($('#print_frame').length == 0) {
            $('body').append('<iframe name="print_frame" id="print_frame" width="0" height="0" frameborder=2 src=""></iframe>');
          }
          var $printFrame = $('#print_frame');
          $printFrame.contents().empty()
          frame = window.frames['print_frame'];
          doc = frame.document;
        } else {
          // need to use external window. IE8 (of course) doesn't like to print from a frame
          var disp_setting="toolbar=yes,location=no,directories=yes,menubar=yes,"; 
            disp_setting+="scrollbars=yes,width=650, height=600, left=100, top=25"; 
          win=window.open("","",disp_setting);
          doc = win.document;
        }
        
        doc.open();
        doc.write( '' );
        doc.write( '<!DOCTYPE html PUBLIC \"-//W3C//DTD XHTML 1.0 Transitional//EN\" \"http://www.w3.org/TR/xhtml1/DTD/xhtml1-transitional.dtd\">' );
        doc.write( '<html>' );
        doc.write( '<head>' );
        doc.write( '<title></title>'); // @TODO
        doc.write( '<link href="/' + Drupal.settings.gazprom.pathToTheme + '/styles/text.css" rel="stylesheet">'
          + '<link href="/' + Drupal.settings.gazprom.pathToTheme + '/styles/print.css" rel="stylesheet">' );
        doc.write( '</head>' );
//        doc.write( '<body>' );
        doc.write('<body onLoad="self.print();self.close();">');
      
        $.each($content, function() {
          doc.write( $(this).outerHTML() );
        });

        var reference = '<h6 class="url-reference">' + window.location.href + '</h6>';
        doc.write( reference );

        doc.write( '</body>' );
        doc.write( '</html>' );
        
        doc.close();
        
        //var $otherFrame = $(frame.document);
        //alert($otherFrame.find('h6').length);

        // print it after a slight delay so that DOMs get settled
        //setTimeout(_printIt,500);
        
        function _printIt(){
          frame.focus();
          frame.print();
          frame.parent.focus(); // does this work? not sure .. 
          //$printFrame.contents().empty();
          //$printFrame.remove(); // would love to do this, but causes reresh of main page .. probably because focus is still on it?
        }
      });
      
    }
    
  }
  
  // make a jQuery plugin
  $.fn.printContent = function(parameter) {
    if (methods[parameter]) {
      // api call
      return methods[parameter].apply(this, Array.prototype.slice.call(arguments, 1));
    }
//    else if (typeof parameter === "function" || !parameter) { <-- use this patt<ern if callback needed
//        return methods.init.apply(this, arguments); 
//    }
    else if (typeof parameter === "object" || !parameter) {
        //return methods.init.apply(this, [null, parameter]); <-- use this patt<ern if callback needed
        return methods.init.apply(this, [parameter]);
    }
    
    // jQuery plugin pattern taken from Waypoints plugin
  }
  
})(jQuery, window);

(function($) {
  /**
   * Simple plugin to return outerHTML of an element (only IE has this built in)
   * retrieved from http://brandonaaron.net/blog/2007/06/17/jquery-snippets-outerhtml
   */
  $.fn.outerHTML = function() {
    return $('<div>').append( this.eq(0).clone() ).html();
  };
  
  /**
   * Custon plugin that can return data about an element that is normally
   * impossible to do because the element is display:none or another reason.
   * Based off of...
   * http://wvega.com/246/get-height-of-a-hidden-element-using-jquery/
   */
  $.fn.sandbox = function(width, height, fn) {
    var element = $(this).clone(), result;
    // make the element take space in the page but invisible
    element.css({
      visibility: 'hidden',
      display: 'block',
      position: 'absolute',
      width: width,
      height: 'auto'
    });//.appendTo($('body'));
    $(this).after(element);
    // to override any display: none !important you may have been using
    element.attr('style', element.attr('style').replace('block', 'block !important'));
    result = fn.apply(element);
    element.remove();
    return result;
  };

})(jQuery);

/**
 * From http://www.foliotek.com/devblog/getting-the-width-of-a-hidden-element-with-jquery-using-width/
 **/
(function($) {
$.fn.getHiddenDimensions = function(includeMargin) {
    var $item = this,
        props = {position: 'absolute', visibility: 'hidden', display: 'block'},
        dim = {width:0, height:0, innerWidth: 0, innerHeight: 0,outerWidth: 0,outerHeight: 0},
        $hiddenParents = $item.parents().andSelf().not(':visible'),
        includeMargin = (includeMargin == null)? false : includeMargin;
 
    var oldProps = [];
    $hiddenParents.each(function() {
        var old = {};
 
        for ( var name in props ) {
            old[ name ] = this.style[ name ];
            this.style[ name ] = props[ name ];
        }
 
        oldProps.push(old);
    });
 
    dim.width = $item.width();
    dim.outerWidth = $item.outerWidth(includeMargin);
    dim.innerWidth = $item.innerWidth();
    dim.height = $item.height();
    dim.innerHeight = $item.innerHeight();
    dim.outerHeight = $item.outerHeight(includeMargin);
 
    $hiddenParents.each(function(i) {
        var old = oldProps[i];
        for ( var name in props ) {
            this.style[ name ] = old[ name ];
        }
    });
 
    return dim;
}
}(jQuery));

/*! Copyright (c) 2008 Brandon Aaron (brandon.aaron@gmail.com || http://brandonaaron.net)
 * Dual licensed under the MIT (http://www.opensource.org/licenses/mit-license.php) 
 * and GPL (http://www.opensource.org/licenses/gpl-license.php) licenses.
 */

/**
 * Gets the width of the OS scrollbar
 */
(function($) {
	var scrollbarWidth = 0;
	$.getScrollbarWidth = function() {
		if ( !scrollbarWidth && !Drupal.gazprom.singlePageMode) {
			if ( $.browser.msie ) {
				var $textarea1 = $('<textarea cols="10" rows="2"></textarea>')
						.css({position: 'absolute', top: -1000, left: -1000}).appendTo('body'),
					$textarea2 = $('<textarea cols="10" rows="2" style="overflow: hidden;"></textarea>')
						.css({position: 'absolute', top: -1000, left: -1000}).appendTo('body');
				scrollbarWidth = $textarea1.width() - $textarea2.width();
				$textarea1.add($textarea2).remove();
			} else {
				var $div = $('<div />')
					.css({width: 100, height: 100, overflow: 'auto', position: 'absolute', top: -1000, left: -1000})
					.prependTo('body').append('<div />').find('div')
						.css({width: '100%', height: 200});
				scrollbarWidth = 100 - $div.width();
				$div.parent().remove();
			}
		}
		return scrollbarWidth;
	};
})(jQuery);

(function() {
  // In case we forget to take out console statements. IE becomes very unhappy when we forget. Let's not make IE unhappy
  if(typeof(console) === 'undefined') {
    console = {}
    console.log = console.error = console.info = console.debug = console.warn = console.trace = console.dir = console.dirxml = console.group = console.groupEnd = console.time = console.timeEnd = console.assert = function() {};
  }
  if (typeof(console.profile) == 'undefined') {
    console.profile = console.profileEnd = function() {};
  }
})();

/**
 * Custom jQuery pseudo selector to allow for
 * selecting elements that are visible within the photo gallery grid.
 * Relies on helper/convenience functions found in jquery.lazyload.js
 * (https://github.com/tuupola/jquery_lazyload)
 * 
 */
(function($, window, undefined) {

var $grid = false, settings;
$.extend($.expr[':'], {  
    'in-grid-viewport': function(elem) {
        if (!$grid) {
          $grid = $('div.view-photo-grid:first');
        } else if ($grid.parent().length == 0) {
          // photo gallery grid has been replaced
          $grid = $('div.view-photo-grid:first');
        }
        if ($grid.width() == 0) {
          $grid = $('div.view-photo-grid:first');
        }
        return !$.rightoffold(elem, {threshold: 240, container: $grid}) && !$.leftofbegin(elem, {threshold: 240, container: $grid}) && 
              !$.belowthefold(elem, {threshold: 240, container: $grid}) && !$.abovethetop(elem, {threshold: 240, container: $grid});
    },
    'right-of-grid-viewport': function(elem) {
        if (!$grid) {
          $grid = $('div.view-photo-grid:first');
        } else if ($grid.parent().length == 0) {
          // photo gallery grid has been replaced
          $grid = $('div.view-photo-grid:first');
        }
        if ($grid.width() == 0) {
          $grid = $('div.view-photo-grid:first');
        }
        return $.rightoffold(elem, {threshold: -240, container: $grid});
    },
    'below-grid-viewport': function(elem) {
        if (!$grid) {
          $grid = $('div.view-photo-grid:first');
        } else if ($grid.parent().length == 0) {
          // photo gallery grid has been replaced
          $grid = $('div.view-photo-grid:first');
        }
        if ($grid.width() == 0) {
          $grid = $('div.view-photo-grid:first');
        }
        return $.belowthefold(elem, {threshold: -240, container: $grid});
    }
});  
  
})(jQuery, window, undefined);