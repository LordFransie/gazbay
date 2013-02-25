/**
 * gazprom Javascript core
 * 
 * Author: jon@system-werks.com
 *
 **/

// gazprom behavior
(function($) {
  
  
  Drupal.behaviors.gazprom = {
    attach: function (context, settings) {   
      $('body').once('hijacked', function() {
        // the Drupal .once() plug-in makes sure that this function is only called once
        $('html').removeClass('no-js');
        
        if (Drupal.settings.gazprom.simpleMode == 'true') return;
        Drupal.gazprom.init.enterBuildMode();
        
        
        // singlePageMode=true means we don't need to initialize all the site's functions
        if (Drupal.settings.gazprom.singlePageMode == 'true') {
          Drupal.gazprom.init.document();
          // @TODO we now have singlePageMode syno
          Drupal.gazprom.activateRoom($('.content-room-wrapper:first'));
        }

        // normal mode (singlePageMode=false) means we have to build out all the floors and rooms
        // .. of the site and initialize all scrolling functions
        if (Drupal.settings.gazprom.singlePageMode != 'true') {
          // force rooms to window height (even for single page mode)
          Drupal.gazprom.init.site();
        }

      });
      
    }
  };
})(jQuery);

(function($){
  Drupal.gazprom = {
    linkScrollInEffect: false,
    windowResizeTimeout: 0,
    windowResize: function() {
      clearTimeout(Drupal.gazprom.windowResizeTimeout);
      var $activeRoom = $('.content-room-wrapper.active-room');
      if ($activeRoom.length > 0) {
        Drupal.gazprom.scrollToRoom($activeRoom, {duration: 0});
      }
      Drupal.gazprom.windowResizeTimeout = setTimeout(function() {
        //console.log('window resize');
        // if stage is inside the absolute positioned bottom content pane, make sure
        // it is big enough. There is CSS to allow it to climb to the top of the page as well (escape various containers)
        // @TODO rethink this? is stage even needed inside a "basic page" node type anymore now that we have page_code node type?
        $('.constant-bottom .stage').css({
          height: $(window).height() - $('#footer-page').height(),
          bottom: null
        }); // @TODO should this be bound to the event somewhere else?
        $(window).trigger('resizeComplete'); // let other handlers update their elements (i.e. stepWidth()
      }, 250);
    }, // end windowResize
    setRoomToActive: function($room) {
      /*
       * Sets a room & floor to active status
       */

      var $floor = $room.closest('.content-floor-wrapper');

      // first disable old (all)
      $('.active-floor').removeClass('active-floor');
      $('.active-room').removeClass('active-room');

      $floor.addClass('active-floor');
      $room.addClass('active-room');

      return;
    }, // end setRoomToActive
    scrollToRoom: function($room, options) {
    
      var settings = $.extend({
        duration: 1500,
        catchUpDuration: 750,
        easing: 'swing'
        //easing: 'easeInOutCirc'
      }, options);


      var $previousActiveRoom = $('.active-room');
      if (!$room.is('.active-room')) { // window resize comes here for syncing the scroll bar .. but we don't want to trigger room events
        Drupal.gazprom.deactivateRoom($previousActiveRoom);
      }

      if (typeof($room) == 'undefined') {
        $room = $('.content-room-wrapper.active');
      }
      var $floor = $room.closest('.content-floor-wrapper');
      var $floorSlider = $floor.find('.floor-slider:first');
      var $secondNavigation = $floor.find('.second-navigation:first');
      if ($room.length == 0 || $floor.length == 0 || $floorSlider.length == 0) {
        //console.log('ERROR: Drupal.gazprom.scrollToRoom given invalid room');
        return true; // something went wrong
      }

      // for scroll effects
      $('.second-navigation.scroll-destination').removeClass('scroll-destination');
      $secondNavigation.addClass('scroll-destination');
      Drupal.gazprom.linkScrollInEffect = true;

      var id = $room.attr('id');
      var destination = Drupal.gazprom.utility.findDirectoryEntry(id);
      var offset = $floor.find('.second-navigation').outerHeight();
      if (offset == null) offset = 0;
      if (!$floor.hasClass('active-floor')) {
        // we are on another floor, so move to floor first
        $(window).stop(true,false).scrollTo($floor, {
          duration: settings.duration,
          axis: 'y',
          offset: offset,
          easing: settings.easing,
          onAfter: function() {
            _moveSecondNavIndicator();
            if ($room.offset().left != 0) {
              $floorSlider.stop(true,false).scrollTo($room, {
                easing: settings.easing,
                duration: settings.duration,
                axis: 'x',
                onAfter: function() {
                  _scrollComplete();
                }
              });
           } else {
              _scrollComplete();
           }
          }
        });

      } else {
        // click was on one of the other rooms of a floor
        if ($floor.offset().top != $(window).scrollTop() - offset) {
          // floor is not positioned correctly
          $(window).stop(true,false).scrollTo($floor, {
            duration: settings.catchUpDuration,
            axis: 'y',
            offset: offset,
            easing: settings.easing,
            onAfter: function() {
              _moveSecondNavIndicator();
              $floorSlider.stop(true,false).scrollTo($room, {
                duration: settings.duration,
                axis: 'x'
              });
              _scrollComplete();
            }
          });
        }
        else {
          _moveSecondNavIndicator();
          // floor looks good, so scroll to the room
          $floorSlider.stop(true,false).scrollTo($room, {
            duration: settings.duration,
            easing: settings.easing,
            axis: 'xy',
            onAfter: function() {
              _scrollComplete();
            }
          });
        }
      }

      // make sure room & floor are set to active status
      Drupal.gazprom.setRoomToActive($room);

      // @TODO EXPERIMENTAL:
      // change the floor's referencing anchor to now point to this room
      // (move into setRoomToActive()? )
      var $referencingMainNavAnchor = $floor.data('referencingAnchor'); // @TODO is this weak?
      //var destination = $room.data('destination');
      if ($referencingMainNavAnchor != undefined && destination != undefined) {
        $referencingMainNavAnchor.attr('href', destination.href);
        // @TODO anchor title?
      }

      function _scrollComplete() {
        Drupal.gazprom.linkScrollInEffect = false;
        $('.second-navigation.scroll-destination').removeClass('scroll-destination');
        Drupal.gazprom.activateRoom($room);
      }
      
      function _moveSecondNavIndicator() {
        // adjust indicator
        var $indicator = $floor.find('nav.second-navigation').find('.indicator');
        Drupal.gazprom.updateIndicator($indicator);
      }

    }, // end scrollToRoom
    activateRoom: function($room) {
      if (!$room.hasClass('activated')) {
        $room.trigger('room-activation');
        $room.addClass('activated');
      }
    }, // end activateRoom
    deactivateRoom: function($room) {
      if ($room.hasClass('activated')) {
        $room.trigger('room-deactivation');
        $room.removeClass('activated');
      }
    }, // end deactivateRoom
    openPath: function(href) {
      var id = Drupal.gazprom.utility.urlToId(href);
      var $room = $('#' + id);
      if (href == '/viewPhoto') {
        Drupal.gazprom.openPhotoInOverlay();
      } else
      if ($room.length == 0) {
        // room holding that href is not loaded, so load it via overlay
        Drupal.gazprom.openInOverlay(href);
      } else {
       Drupal.gazprom.openInDOM($room, href);
      }
      
    }, // end openPath
    openInDOM: function($room, href) {
      $overlayOpened = $('.overlay-open');
      if ($overlayOpened.length > 0 ) {
        $overlayOpened.removeClass('overlay-open'); // somewhat of a hack: this signals the overlay's onClose function to NOT go back in History
        $overlayOpened.overlay().close();
      }

      //var $anchors = $('nav a[href="' + href + '"]'); // could be more than one @TODO breadcrumbs too?
      var $anchors = $('a[href$="' + href + '"]'); // @TODO bad to find all relevetant anchors? above code didn't find home page link
      $anchors.each(function() {
        Drupal.gazprom.activeAnchor($(this));
      });
      // @TODO review whats going on here .. i think this who href$= was for breadcrumbs and such.. which we don't have anymore
//      $anchors = $('#navigation-main a[href$="' + href + '"]');
//      $anchors.each(function() {
//        Drupal.gazprom.activeAnchor($(this));
//      });

      if (!$room.hasClass('active-room')) {
        // scroll to it
        Drupal.gazprom.scrollToRoom($room);
        // get title out of DOM
        var headTitle = Drupal.gazprom.getRoomTitle($room);
        document.title = headTitle;
        //
        //@TODO removing this.. problematic? if (headTitle) options.newWindowTitle = headTitle; // send it back to hijax onstatechange routine
        //
        //
        // record this current URL as last used for this room .. @TODO, huh?
      } 
      if (($room.data('urlAtLastScroll')||false) && ($room.data('urlAtLastScroll') != window.location.pathname+window.location.search)) {
        // the URL has been changed, but we're alread scrolled onto the right room
        // so the assumption is that there is a change in the query parameters
        // reload the room content
        var fullURL = window.location.pathname + window.location.search; // @TODO test this on HTML4 browser

        var $contentContainer = $room.find('.bottom-content'); // @TODO is this good enough? any situation where we want to load the whole room?
        // @TODO also, find a better class name than .bottom-content
        $contentContainer.empty();
        $contentContainer.append('<div class="temp-wrapper"></div>');
        var $loadWrapper = $contentContainer.find('.temp-wrapper');
        $loadWrapper.load(fullURL + ' .bottom-content', function() {
          $loadWrapper.find('.bottom-content').children().unwrap();
          $loadWrapper.children().unwrap();
          Drupal.gazprom.init.room($room);
          // @TODO put this code somewhere else??
        });
      }
      $room.data('urlAtLastScroll', window.location.pathname + window.location.search);

      Drupal.gazprom.setRoomToActive($room); // just incase 

    }, // end openInDom
    openInOverlay: function(href) {
      var $anchor = $(window).data('lastClick'); // set in hijax.js @TODO too hackish??
      var $trigger = $('#gazprom-overlay-trigger');
      api = $trigger.data('overlay');
      if (api) {
        if (api.isOpened()) {
          //data = api.getConf().data;
          // overlay already open
          api.data = {href: href, historyCount: api.data.historyCount + 1};
          _loadContent(api, href);
        } else {
          // not the first overlay, but was closed
          api.data = {href: href, historyCount: 0};
          api.load();          
        }
      } else {
        // overlay never opened yet
        // @TODO .. this is a lot of work to get jQuery Tools' overlay to only deal with one overlay instance
        $trigger.overlay({
          mask: {color: '#000', opacity: 0.8, loadSpeed: 'fast'},
  //            effect: 'apple',
          target: '#gazprom-overlay',
          close: '#gazprom-overlay .overlay-close',
          load: true,
          top: 0,
          onBeforeLoad: function(event) {
            if (!this.data) {
              this.data = {href: href, historyCount: 0};
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

            if ($trigger.hasClass('overlay-open')) {
              this.getTrigger().removeClass('overlay-open');
              if (Drupal.gazprom.hijaxSettings.initialized == true) {
                if (this.data.historyCount ? this.data.historyCount > 0 : false) {
                  History.go(-1 * (api.data.historyCount + 1));
                } else {
                  History.back(); // @TODO error check? @TODO what about links in the overlay that goes to another page?
                }
              }
            }
            var $scrollingArea = $('#gazprom-overlay > .overlay-wrapper');
            $scrollingArea.unbind('mousewheel');
            
            var jspAPI = $wrap.find('.main-section').data('jsp');
            if (jspAPI) {
              jspAPI.destroy();
            }
            
            $('#gazprom-overlay .overlay-wrapper').empty(); // must do this so the id is
            // .. gone from the document. Can't seem to use $wrap. Maybe it's a clone? data within the $anchor?
          }
          
        });
        
        function _loadContent(api, href) {
          var $trigger = api.getTrigger();
//          var api = $trigger.data('overlay');
          var $overlay = api.getOverlay();
          var $wrap = $overlay.find('.overlay-wrapper');
          $wrap.empty().load(href + '?overlay=true' + ' .content-wrapper', function(data) {

             // @TODO too much code going in here.. move it somewhere safer

             // hijax links .. need to do full init.room() on content?
            $wrap.find('.content-wrapper .content-main a, .content-wrapper .sidebar a').once('gazprom-click', function() {
              $(this).unbind('click').bind('click.contentOverlay', function(e) {
                e.preventDefault();
                api.close();
                setTimeout(function(){
                  hijax.clickHandler(e);
                }, 1000);
                // @TODO @TODO @TODO @TODO @TODO
                // this is a complete nightmare and a mess. see all the data.historyCount crap above as well
                // the problem is .. links inside the overlay should (probably) be opened up inside the overlay. But
                // doing that causes the history to move forward and we need an easy way to get back to the begining.
                // consider tracking previous URL in all new calls to onStateChange .. then grab that and store it
                // when the overlay is opened .. if they overlay closes, push that saved URL .. what about title??!
              });
              //$(this).hijax();
            })

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
            var $scrollingArea = $('#gazprom-overlay > .overlay-wrapper');
            $scrollingArea.bind('mousewheel', function(e, d) {
              e.preventDefault();
              return false;
              // jScrollPane is catching mousewheel events on the content area that has scrollbar
            });
          });

        }
      }

    }, // end openInOverlay
    openPhotoInOverlay: function($anchor) {
      var href;
      if (!$anchor) {
        var State = $.hijax_getState();
        if (!State.data.photoPath) return; // something went wrong
        href = State.data.photoPath;
        $anchor = $('a[href="'+href+'"]').last(); // @TODO there seem to be duplicates!!
      } else {
        href = $anchor.attr('href');
      }
      var api = $anchor.data('overlay');
      if (api) { 
        api.load(); // @TODO .. does it make sense to attach overlay API to picture anchors?      
      } else {
        $anchor.overlay({
          target: '#photo-overlay',
          load: true,
          top: 0,
          left: 0,
          close: 'a.photo-control.close',
          onBeforeLoad: function(event) {
            var $wrap = this.getOverlay().find('.content-wrapper');
            $wrap.empty().load(this.getTrigger().attr('href') + '?overlay=true' + ' .content-main',
              function() {
                // modify content & attach photoViewer controls
                Drupal.gazprom.viewPhoto.view($wrap, $anchor.data('overlay'));
              }); // @TODO just use href variable? @TODO change this to better funciton than .load()?
              //
            // bind custom mousewheel handler so scrolling past bottom doesn't cause main window to scroll
            var $scrollingArea = $('#photo-overlay > .content-wrapper');
            $scrollingArea.bind('mousewheel', function(e, d) {
              e.preventDefault();
              return false;
            });

//            // bind custom mousewheel handler so scrolling doesn't get sent to window
//            //var $scrollingArea = $('#photo-overlay');
//            $(window).bind('mousewheel.photo-overlay', function(e, d) {
//              e.preventDefault();
//            });

          },
          onLoad: function(event) {
            this.getTrigger().addClass('overlay-open');
          },
          onClose: function(event) {
            Drupal.gazprom.viewPhoto.close();
            var $trigger = this.getTrigger();
            if ($trigger.hasClass('overlay-open')) {
              this.getTrigger().removeClass('overlay-open');
              if (Drupal.gazprom.hijaxSettings.initialized == true) {
                History.back(); // @TODO error check? @TODO what about links in the overlay that goes to another page?
              }
            }
            $(window).unbind('mousewheel.photo-overlay');
          }
        });

      } // if (api)
      
    }, // end openPhotoInOverlay
    activeAnchor: function($anchor) {
      /*
       * Makes the provided anchor the visually active link
       */
      if ($anchor.hasClass('active')) return; // already set
      if ($anchor.attr('href') == '/') {
        // special case for link to home
        $('#navigation-main a, #navigation-main li').removeClass('active active-trail');

        // adjust navigation-main indicator
        Drupal.gazprom.updateIndicator($('#navigation-main .indicator'));

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
        Drupal.gazprom.updateIndicator($indicator);
        // @TODO for second-level navigation, this has been moved into scrollToRoom

      }
    }, // end activeAnchor
    updateIndicator: function($indicator, options) {
      if ($($indicator).length == 0) return;
      var settings = $.extend({
        duration: 1500,
        easing: 'swing'
        //easing: 'easeInOutCirc'
      }, options);
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
        $indicator.fadeOut(settings.duration).css({width: 0});
        return;
      }
      if (original_width == 0) {
        $indicator.stop(true).fadeOut(0)
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

    }, // end updateIndicator
    scrollTimeout: 0,
    onScroll: function(e) {
      /*
       * Makes navigation menu adjustements as the user
       * manually scrolls (also happens during auto)
       * @TODO consider using this to adjust active navigation menu items?
       */

      clearTimeout(Drupal.gazprom.scrollTimeout);
      Drupal.gazprom.scrollTimeout = setTimeout(function() {

        var winHeight = $(window).height();
        var docViewTop = $(window).scrollTop();
        var docViewBottom = docViewTop + winHeight;
        var headerArea = $('#header').height() + $('.second-navigation:first').height() + 10;

        // for the _inView function
        var triggerPoint = docViewTop + headerArea + (winHeight / 2);

        $('.content-floor-wrapper').each(function() {
          var $floor = $(this);
          if (_isInView($floor) && !$floor.hasClass('active-floor')) {
            var $secondNav = $floor.find('nav.second-navigation');

            // trigger deactivation of previous active room
            Drupal.gazprom.deactivateRoom($('.active-room'));
            $('#navigation-main .active, #navigation-main .active-trail').removeClass('active active-trail');
            if ($secondNav.length > 0) {
              var $referencingMainNavAnchor = $floor.data('referencingAnchor'); // @TODO is this weak?
              if (typeof($referencingAnchor) != 'undefined') {
                Drupal.gazprom.activeAnchor($referencingAnchor);
              }
              var $activeAnchor = $secondNav.find('ul.menu li > a.active');
              var $room = $('#' + Drupal.gazprom.utility.urlToId($activeAnchor.attr('href')));
              //Drupal.gazprom.scrollToRoom($room);
              Drupal.gazprom.setRoomToActive($room);
              Drupal.gazprom.activateRoom($room)
              var headTitle = Drupal.gazprom.getRoomTitle($room);
              if (Drupal.gazprom.hijaxSettings.initialized == true ) {
                $.hijax_addState($activeAnchor.attr('href'), {options: {skipScroll: true}, newWindowTitle: headTitle});
                //document.title = Drupal.gazprom.getRoomTitle($room);
              }
            } else {

              // no second-level navigation, so assume home page
              // @TODO is this assumption a problem?
             $('#navigation-main .active, #navigation-main .active-trail').removeClass('active active-trail');
             Drupal.gazprom.updateIndicator($('#navigation-main').find('.indicator'));
             Drupal.gazprom.setRoomToActive($('#home'));
             Drupal.gazprom.activateRoom($('#home'))
             if (Drupal.gazprom.hijaxSettings.initialized == true ) {
              $.hijax_addState('/', {options: {skipScroll: true}});
              //document.title = Drupal.gazprom.getRoomTitle($room);
             }

            }
          }
        });

        function _isInView(floor) {

          var floorTop = $(floor).offset().top;
          var floorBottom = floorTop + $(floor).height();

          return ((triggerPoint >= floorTop) && (triggerPoint < floorBottom));
        }


      }, 150);


    }, // end onScroll
    getRoomTitle: function($room) {
      return $room.find('h1.head-title').text();
    }, // end getRoomTitle
    
    centerAlignImage: function($image, $container) {
      
    },
    
    shareThis: function(service) {
      alert('The shareThis service was called for: ' + service);
      
      // @TODO write this!!
    }
    
  };
})(jQuery);

(function($) {
  Drupal.gazprom.photoGallery = function($room) {

    // @TODO this really needs to be broken out into its own area. Maybe custom module JS code?
    if (($room.find('.stage .view-photo-grid').length == 0) && ($room.find('.stage .view-photo-list').length == 0)) return;
    
    var $stage = $room.find('.stage:first');
    var $gallery = $stage.find('.photo-gallery-content');
    var $controls = $stage.find('.photo-gallery-controls');
    var $filterDialog = $stage.find('.gallery-filter-dialog');
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
    
    // bind up TEMPORARY handlers for search and slideshow @TODO
    $stage.find('.gallery-control-show, .gallery-control-search').unbind('click.photoGallery').bind('click.photoGallery', function(e) {
      e.preventDefault();
      alert('This function is not yet available');
    })
    
    // make sure controls don't show up in other rooms
   $stage.find('.photo-gallery-controls, .grid-button').hide();
    
    
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
        $stage.find('.photo-gallery-controls').fadeOut(500, function(){
          $(this).hide();
        });
      })

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
      var $pager = $grid.find('ul.pager');
      if ($firstUL.length == 0) return; // no photos
      
      // move Views filter & sort forms into our div container to display them
      _relocateSortFilters();
      
      // bind up activation/deactivation routines
      $room.unbind('room-activation.photoGallery').bind('room-activation.photoGallery', function() {
        $stage.find('.photo-gallery-controls, .grid-button').show().fadeOut(0).fadeIn(500);
      }).unbind('room-deactivation.photoGallery').bind('room-deactivation.photoGallery', function() {
        _filterClose(0);
        $stage.find('.photo-gallery-controls, .grid-button').fadeOut(500, function(){
          $(this).hide();
        });
      })
      if ($room.is('.active-room')) $room.trigger('room-activation.photoGallery');

      
      $grid.bind('mousewheel', function(e) {
        e.preventDefault();
        // @TODO is this a good idea? maybe mousewheel should scroll grid?
      });

      // determine how many pages of View content we have and what the grid dimensions will need to be
      var currentText = $pager.find('.pager-current').text();
      if (currentText == '') {
        totalPages = 1;
        gridWidth = 1;
        gridHeight = 1;
        totalCells = 1;
      } else {
        pagerData = currentText.split(' of '); // text is like 2 of 14
        totalPages = parseInt(pagerData[1]);
        gridWidth = Math.ceil(Math.sqrt(totalPages));
        gridHeight = gridWidth;
        totalCells = gridWidth * gridHeight;
      }

      var $loadedContent = $grid.find('.view-content .item-list').children();
      // create out table grid
      $grid.find('.view-content .item-list').prepend('<table class="photo-grid"></table>');
      $table = $grid.find('.view-content .item-list table');
      for (row = 1; row <= gridHeight; row++) {
        $table.append('<tr class="row-'+row+'"></tr>');
        $row = $table.find('tr.row-' + row);
        for (column = 1; column <= gridWidth; column++) {
          $row.append('<td class="col-'+column+'"></td>')
        }
      }
      // wrap current content (first View page) in first cell
      var $firstCell = $table.find('tr.row-1 td.col-1');
      $loadedContent.appendTo($firstCell);

      // now start fetching real View pages and populating the
      // table cells with the UL content that is returned
      // VERY IMPORTANT: The photo_grid view has a random seed sort that is
      // .. provided by the View Random Seed module.. a regular sort might
      // .. return the same photos on different pages.
      var page = 0;
      var pagesLoaded = 0;
      for (row = 1; row <= gridHeight; row++) {
        for (column = 1; column <= gridWidth; column++) {
          (function() {
            var $cell = $table.find('tr.row-'+row+' td.col-'+column);
            page++;
            if ($cell.children().length == 0 && page <= totalPages) {
              //$cell.append($loadedContent.clone());
              _getViewPage(page, function($newContent) {
                $newContent = $newContent; // set in the _getViewPage function
                $cell.empty().append($newContent);
                // attach click handlers to pictures
                $cell.find('li a').not('.photo-galleryprocessed')
                  .bind('click', _viewPhoto)
                  .addClass('gazprom-click-processed photo-gallery-processed');
                pagesLoaded++
                if (pagesLoaded == totalPages - 1) {
                  // all done
                  _gridInstalled();
                }
              });
            } else if ($cell.children().length > 0) {
              // this part of the grid was already loaded
              $cell.find('li a').not('.photo-gallery-processed')
                .unbind('click')
                .bind('click', _viewPhoto)
                .addClass('gazprom-click-processed photo-gallery-processed');
            }
          })();
        }
      }
      
      $grid.find('.view-content .item-list').append('<div class="clearfix"></div>');

      $grid.addClass('scrolling-grid');

      _updateGridButtons();
    }

    function _gridInstalled() {
      // add focus ring to grid
      if ($stage.find('.photo-gallery-focus-ring').length == 0) {
        $stage.append('<div class="photo-gallery-focus-ring"></div>');
      }

      // bind up the hover-focus ring .. subsequent clicks to a photo will be captured by the focus ring
      $stage.find('div.photo-gallery-focus-ring').unbind('click.photoGallery').bind('click.photoGallery', function(e) {
        var $currentFocus = $(this).data('currentFocus');
        if ($currentFocus.length > 0) $currentFocus.find('a').trigger('click');
      }).bind('mousewheel', function(e) {
        e.preventDefault();
      });

      if ($room.is('.active-room')) {
        // make sure grid buttons are visable
        $stage.find('.grid-button, .photo-gallery-focus-ring').fadeIn(500);
      }
      
      // all done so scroll to something interesting
      var $target = $table.find('tr.row-' + Math.floor(gridHeight / 2) + ' td.col-' + Math.floor(gridWidth / 2)).find('li:last');
      //_updatePhotoFocus($target);
      $target.addClass('hover-focus');
      $grid.scrollTo($target,500, {
        offset:{
          top:-360,left:-410
        },
        onAfter: _updateHoverFocus
      });


      // bind up hover events to photos sensitivity
      $grid.find('.view-content li').hoverIntent({
        over: function(e) {
          var $newTarget = $(this);
          // check if new target is in view
//          if (($newTarget.position().left > $grid.scrollLeft())
//              && ($newTarget.position().left + $newTarget.width() < $grid.scrollLeft() + stageWidth)
//              && ($newTarget.position().top > $grid.scrollTop() + 157)
//              && ($newTarget.position().top + $newTarget.height() < $grid.scrollTop() + stageHeight - 60)) {
                $grid.find('.view-content li.hover-focus').removeClass('hover-focus');
                $(this).addClass('hover-focus');
                _updateHoverFocus();
//          }
        },
        out: function(e) {
          //$(this).removeClass('hover-focus');
        },
        interval: 150,
        timeout: 150
      });

    }
    
    function _listInstalled() {
      
      $list.jScrollPane({
        animateScroll: true,
        hideFocus: true
      });
      //$gallery.fadeIn(500);
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
    
    function _scrollGrid(e) {
      e.preventDefault();
      var $target = $(this);
      var settings = {
        onAfter: _updateGridButtons,
        margin: true,
        duration: 1000
      };
      _filterClose();
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
      } else
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
      return; // @TODO not working yet. couldn't find right and bottom edge calculations
      $grid.find('.grid-button').removeClass('deactivated');
      if ($grid.scrollLeft() == 0) {
        $grid.find('.grid-button.scroll-left').addClass('deactivated');
      }
      if ($grid.scrollTop() == 0) {
        $grid.find('.grid-button.scroll-up').addClass('deactivated');
      }
      if ($grid.scrollLeft() +$grid.width() >= $.scrollTo.max($grid, 'x')) {
        $grid.find('.grid-button.scroll-right').addClass('deactivated');
      }
      if ($grid.scrollTop() + $grid.height() >= $.scrollTo.max($grid, 'y')) {
        $grid.find('.grid-button.scroll-down').addClass('deactivated');
      }
    }
    
    function _viewPhoto(e) {
      e.preventDefault();
      var $anchor = $(e.currentTarget);
      if ($grid.length > 0) {
        _updatePhotoFocus($anchor.closest('li'));
      }

      if (Drupal.gazprom.hijaxSettings.initialized == true) {
        $.hijax_addState('/viewPhoto',{newWindowTitle: 'View Photo', photoPath: $anchor.attr('href')});
      } else {
        Drupal.gazprom.openPhotoInOverlay($anchor);
      }
      //alert('click!');
      
      return false;
    }

    function _getViewPage(pageNum, callback) {
 
      var href = '/views/ajax?';
      var viewIDdata = _getViewID();
      href = href + 'view_name=' + viewIDdata.view_name + '&view_display_id=' + viewIDdata.view_display_id + '&' + 'page=' + (pageNum - 1); // pagerNextHref.split('?')[1];
      
      // we need the view filter & sort arguments from the pager's link (pager gets updated by filter's ajax routine)
      var $pagerNext = $gallery.find('.item-list ul.pager li.pager-next')
      if ($pagerNext.length > 0) {
        var pagerNextHref = $pagerNext.find('a').attr('href');
        var hrefParts = pagerNextHref.split('?');
        if (hrefParts.length > 0) {
          var queryString = hrefParts[1];
          href = href + queryString.replace('&page=', '&ignoreThis=');
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
      
      // is this a hack? find the view_name and view_display_id values from the classes
      var classArray = $gallery.find('.view').attr('class').split(' ');
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
      //return 'view_name=' + view_name + '&view_display_id=' + display_id;
    }
    
    function _processViewAJAXresult(result, callback) {
      //var $newContent = $(result[1].data).find(vars.viewInnerSelector).children(); //.find('.view-content ul.item-list, .view-content table tbody').children();
      var $newContent = $(result[1].data).find('.view-content .item-list ul');
      // make sure new content is attached to handlers
      //Drupal.gazprom.init.room(vars.container.closest('.content-room-wrapper'));

      // must update the session vars to the new lastItem
      //vars.lastItem = vars.container.find(vars.itemSelector + ':last');

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
    
    function _gridControls(command) {
      if ($grid.length > 0) {
        switch(command) {
          case 'show':
            $stage.find('.grid-button').fadeIn(500);
            break;
          case 'hide':
            $stage.find('.grid-button').fadeOut(500);
            _filterClose(100);
            break;
        }
      }
    }
    
    function _relocateSortFilters() {
      var $filters = $gallery.find('.view-filters');
      $filterDialog.empty().append($filters.clone(false));
      $filters.remove();
      $filters = $filterDialog.find('.view-filters');
        
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

      $filterDialog.find('form').ajaxForm({
        beforeSerialize: function($form, options) { 
          _filterClose();
          var viewIDdata = _getViewID();
          options.data = viewIDdata;
          options.url = '/views/ajax';
// return false to cancel submit                  
        },
//        beforeSubmit: function(arr, $form, options) {
//          arr = arr;
//          $form = $form;
//          options = options;
//            // The array of form data takes the following form: 
//            // [ { name: 'username', value: 'jresig' }, { name: 'password', value: 'secret' } ] 
//
//            //return false;
//            // return false to cancel submit                  
//        },
        success: function showResponse(result, statusText, xhr, $form)  { 
          result = result;
          var $newContent = $(result[1].data); //.find('.view-content .item-list ul');
          
          $gallery.empty().append($newContent);
          _initializeGallery();
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
      
      _filterClose();
      // get new content
      $.get(href, function(data) {
        if ($('html').is('.ie8, .ie7, .ie6')) {
         $newContent = $(innerShiv($(data).find('.stage .view').first().html()));
        }else {
          $newContent = $(data).find('.stage .photo-gallery-content').first();
        }
        $newContent = $newContent.children(); // remove .photo-gallery-content div
        
        $stage.find('.photo-gallery-content').empty().append($newContent.unwrap());
        _initializeGallery();
      });

    }
          
  }
})(jQuery);



(function($) {
  Drupal.gazprom.viewPhoto = {
    $wrap: {},
    $image: {},
    $imageList: {},
    api: {},
    view: function($wrap, api) {
      var viewPhoto = this;
      this.$wrap = $wrap;
      this.api = api;
      $wrap.css('overflow', 'hidden');
      $wrap.find('.view-collection-contents').hide(); // @TODO temporary
      $wrap.find('.field-name-field-ref-collection').hide();

      
      
      var $image = $wrap.find('.field-name-field-image img');
//      $image.parent().css({
//        position: 'relative',
//        width: '100%',
//        height: '100%'
//      });
      $image.hide();
      this.$image = $image;
    
      // build out various
      $wrap.append('<div class="photo-controls"></div>');
      var $controls = $wrap.find('.photo-controls');
      this.$controls = $controls;
      
      $controls.append($wrap.find('.field-name-field-ref-collection'));
      var $title = $controls.find('.field-name-field-ref-collection');
      $title.show();

      $slideshow_pause = $('<div class="slideshow-pause"></div>');
      $slideshow_play = $('<div class="slideshow-play"></div>');
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
      var $currentImage = this.$imageList.find('li a[href="'+imageSrc+'"]').closest('li');
      if ($currentImage.length > 0) {
        $currentImage.addClass('active');
        // @TODO move to front of list?
      }

      $control_next = $('<div class="photo-control photo-next">');
      $control_prev = $('<div class="photo-control photo-prev"></div>');
      $control_close = $('<div class="photo-control close"></a>');
      $control_share = $('<div class="photo-control share">Share</div><div class="photo-control share-icons"></div>');

      $control_revealBottom = $('<div class="photo-control reveal"></div>');

      $wrap.append($control_next, $control_prev, $control_close,$control_share);
      $wrap.find('.photo-control').fadeOut(0);
      $wrap.append('<div class="photo-cover"></div>');

      $controls.append($control_revealBottom);


      $control_next.unbind('click').bind('click', {viewPhoto: this}, this.controllers.nextPhoto);
      $control_prev.unbind('click').bind('click', {viewPhoto: this}, this.controllers.prevPhoto);
      this.$imageList.find('li').unbind('click').bind('click', {viewPhoto: this}, this.controllers.specificPhoto)
      $control_close.unbind('click').bind('click', {overlay: api}, this.controllers.closeController);
      $control_share.unbind('click').bind('click', {viewPhoto: this}, this.controllers.share);
      $slideshow_pause.unbind('click').bind('click', {viewPhoto: this}, this.controllers.pause);
      $slideshow_play.unbind('click').bind('click', {viewPhoto: this}, this.controllers.play);
      $control_revealBottom.unbind('click').bind('click', {element: $controls, controllers: this.controllers}, this.controllers.toggleReveal);


      // make sure the image is full loaded, adjust it, and fade things in
      var tempImage = new Image();
      $(tempImage).bind('load', function() {
        // make photo fit the $wrap viewport (also binds a window resize function for vertical centering)
        viewPhoto.adjustPhoto($image);
        $image.fadeIn(500, function() {
          $controls.fadeIn(500, function() {
           //viewPhoto.controllers.slideDown($controls, true);
           viewPhoto.controllers.slideUp($controls);
          });
          $wrap.find('.photo-control').fadeIn(500);
        });
      }).attr('src', $image.attr('src'));

    },
    close: function () {
      $(window).unbind('resize.viewPhoto');
      clearTimeout(this.controllers.slideshowTimeout);
      $('#header, nav.second-navigation').fadeIn(500);
      
    },
    controllers: {
      slideshowTimeout: 0,
      nextPhoto: function(e) {
        e.preventDefault();
        e.data.viewPhoto.changePhoto('forward');
      },
      prevPhoto: function(e) {
        e.preventDefault();
        e.data.viewPhoto.changePhoto('back');
      },
      specificPhoto: function(e) {
        e.preventDefault();
        var $newPhoto = $(e.currentTarget);
        e.data.viewPhoto.loadNewPhoto($newPhoto);
      },
      closeController: function(e, api) {
        e.preventDefault();
        e.data.overlay.close();
      },
      share: function(e) {

      },
      pause: function(e) {
        e.preventDefault();
        clearTimeout(e.data.viewPhoto.controllers.slideshowTimeout);
        e.data.viewPhoto.controllers.slideUp(e.data.viewPhoto.$controls);
        e.data.viewPhoto.$controls.find('.slideshow-play').removeClass('active');
//        e.data.viewPhoto.$wrap.find('.photo-control').fadeIn(200);
        e.data.viewPhoto.$wrap.find('.photo-control:not(.reveal)').css('opacity','');
        $('#header, nav.second-navigation').fadeIn(500);
        //e.data.viewPhoto.$wrap.closest('.content-floor-wrapper').find('.second-navigation').fadeIn(500);
      },
      play: function(e) {
        e.preventDefault();
        e.data.viewPhoto.controllers.slideshowTimeout = setTimeout(_interval, 2000);
        e.data.viewPhoto.controllers.slideDown(e.data.viewPhoto.$controls, false);
        e.data.viewPhoto.$controls.find('.slideshow-play').addClass('active');
//        e.data.viewPhoto.$wrap.find('.photo-control:not(.reveal)').fadeOut(200);
        e.data.viewPhoto.$wrap.find('.photo-control:not(.reveal)').css({opacity: 0})
        $('#header, nav.second-navigation').fadeOut(500);
        //e.data.viewPhoto.$wrap.closest('.content-floor-wrapper').find('.second-navigation').fadeOut(500);
      
        function _interval() {
          e.data.viewPhoto.changePhoto('forward');
          e.data.viewPhoto.controllers.slideshowTimeout = setTimeout(_interval, 10000);
        }

      },
      slideDown: function($controls, withDelay) {
        if (!($controls.data('originalHeight'))) $controls.data('originalHeight', $controls.height());
        $controls.removeClass('expanded').addClass('collapsed');
        var delayAmount = (withDelay == true) ? 1000 : 0;
        $controls.delay(delayAmount).animate({
          height: '35px'
        }, 500);
      },
      slideUp: function($controls) {
        $controls.removeClass('collapsed').addClass('expanded');
        $controls.stop().animate({
          height: $controls.data('originalHeight')
        }, 500);
      },
      toggleReveal: function(e) {
        var $controls = e.data.element;
        var controllers = e.data.controllers; // @TODO did I go horribly wrong building this?
        if ($controls.is('.collapsed')) {
          controllers.slideUp($controls);
        } else {
          controllers.slideDown($controls);
        }
      }
      
      
    },
    changePhoto: function(direction) {
      var $currentPhoto = this.$imageList.find('.active');
      if ($currentPhoto.length == 0) $currentPhoto = this.$imageList.find('li').first();
      var $newPhoto;
      if (direction == 'back') {
        $newPhoto = $currentPhoto.prev();
        if ($newPhoto.length == 0) $newPhoto = this.$imageList.find('li').last();
      } else {
        $newPhoto = $currentPhoto.next();
        if ($newPhoto.length == 0) $newPhoto = this.$imageList.find('li').first();
      }
      this.loadNewPhoto($newPhoto);
    },
    loadNewPhoto: function($newPhoto) {
      this.$imageList.find('.active').removeClass('active');
      $newPhoto.addClass('active');
      
      var newImageSrc = $newPhoto.find('a').attr('href');
      var viewPhoto = this;
      viewPhoto.$image.css({position: 'absolute', zIndex: '1', width: viewPhoto.$image.width(), height: viewPhoto.$image.height(), top: 0, left: 0});
      var newImage = new Image();
      $(newImage)
        .bind('load', function() {
          $(this).css({zIndex: '0', position: 'absolute', top: 0, left: 0});
          viewPhoto.adjustPhoto($(newImage));
          viewPhoto.$image.after($(newImage));
          viewPhoto.$image.fadeOut(750, function(){
            viewPhoto.$image.remove();
            viewPhoto.$image = $(newImage);
            $(newImage);
          });
        })
        .attr('src', newImageSrc);
    },
    adjustPhoto: function(element) {
      
      // @TODO Make this use Drupal.gazprom.centerAlignImage() ??
      var $wrap = this.$wrap;
      var $image = element ? element : this.$image;
      // grab the image's natural width & height .. must calculate from scratch
      var tempImage = new Image();
      tempImage.src = $image.attr('src');
      var imageWidth = tempImage.width; //$image.attr('width'); //width();
      var imageHeight = tempImage.height; //$image.attr('height'); // .height();
      delete tempImage;
      $image.removeAttr('width').removeAttr('height')
      
      $(window).unbind('resize.viewPhoto').bind('resize.viewPhoto', function(){
        // grab the current viewport width & height
        var viewerHeight = $wrap.height();
        var viewerWidth = $wrap.width();
        if ((imageWidth / imageHeight) > (viewerWidth / viewerHeight)) {
          $image.css({width: 'auto', height: '100%', marginTop: '0', marginLeft: '0'});
          // see if the new width is now pushed past the viewport
          var newWidth = (viewerHeight / imageHeight) * imageWidth;
          // must calculate what the width has become (web browser might not tell us yet)
          if (newWidth > viewerWidth) {
            var horizontalOffset = Math.floor((newWidth / 2) - (viewerWidth / 2));
            $image.css({marginLeft: '-' + horizontalOffset + 'px', marginRight: 'auto'});
          }
         } else {
          $image.css({width: '100%', height: 'auto', marginTop: '0', marginLeft: '0'});
          // see if the new height is now pushed past the viewport
          var newHeight = (viewerWidth / imageWidth) * imageHeight;
          // must calculate what the height has become (web browser might not tell us yet)
          if (newHeight > viewerHeight) {
            var verticalOffset = Math.floor((newHeight / 2) - (viewerHeight / 2));
            $image.css({marginTop: '-' + verticalOffset + 'px'});
          }
         }
      }).trigger('resize.viewPhoto');
            
    }
  }
})(jQuery); // Drupal.gazprom.viewPhoto

(function($){
  
  Drupal.gazprom.init = {
    site: function() {
      /*
       * This is the main initialization routine. It loads all first and second level
       * navigation anchors, build a directory and does some additional data initialization.
       * @TODO add in various UI initializers
       */

        Drupal.gazprom.directory = new Array();
        
        // setup a temporary click disabler on all anchors until all loading/building is done
        $('a').bind('click.duringInitialization', function(e){
          e.preventDefault();
          Drupal.settings.gazprom.scrollToFirst_id = Drupal.gazprom.utility.urlToId($(e.currentTarget).attr('href'));
          return false;
          // this gets unbind'ed in Drupal.gazprom.init.page()
          // stangely (to me anyway) it seems that the additional handlers we add later
          // still work .. i wouldn've though this one gets called first.. but no worries, it
          // does disable the default click handler before our hijacks get put in place.
        });
        
        
        // record the id of the content already loaded.. we're going to want to scroll back to it when
        // .. everything is finished loading
        var $originalContent = $('.content-room-wrapper:first');
        if ($originalContent.length > 0) {
          Drupal.settings.gazprom.scrollToFirst_id = $originalContent.attr('id');
        }
        

        // initialize hijax
        if (Drupal.settings.gazprom.singlePageMode != 'true')
          $.hijax_init(Drupal.gazprom.hijaxSettings);
        
        // call stage1 init/build routine. This function populates the rest of the rooms
        // .. on the floor that our initially loaded content is on. This is done for 
        // .. deep linking situations. In the case of loading the home page first, then
        // .. this function will do nothing except call stage2
        Drupal.gazprom.build.start();
        
    },
    document: function() {
      /*
       * Initialize the document (DOM)
       * Could be a single page (if singlePageMode == true) or multiple floors and rooms
       */
      
      $('body').removeClass('simple');
      
      // tag first-rooms for different styling and other purposes
      if (Drupal.settings.gazprom.singlePageMode != 'true') $('.rooms-of-floor').each(function(){
        $(this).find('.content-room-wrapper:first').addClass('first-room');
        // @TODO this is a problem in singlePageMode since every room will get
        // .. flagged as a first-room
        // should maybe be done in template.php by checking the menu trail?
        // or by the presence of the introductory-text field? (to be done)
        // or by the node type? (i.e. Landing Page or Section Page)
      });
      
      // make sure rooms are setup correctly too
      $('.content-room-wrapper').each(function() {
        Drupal.gazprom.init.room($(this));
      });
      
    
      if (Drupal.settings.gazprom.singlePageMode != 'true') {
        // extract the background image of first-rooms and put it outside the room slider
        $('.first-room').each(function(){
          var $room = $(this);
          $backgrounder = $room.find('div.backgrounder');
          $floor = $room.closest('.content-floor-wrapper');
          //$floor.css('position', 'relative');
          $backgrounder.prependTo($floor);
          $backgrounder.wrap('<div class="relative-wrapper"></div>'); // @TODO rename this to absolute-wrapper since thats what it now is in CSS
  //        $backgrounder.remove();
        });
        
        // @TODO Make this intelligent and remove duplicate images. Maybe by filename so
        // .. that they can be uploaded separately (node title will need to be used in
        // .. file path)
      }
      
      // bind up special background image resizer
      $('div.to-background img.fancy-background-image').fluidCenterAlignImage({
        containerSelector: '.expand-top, .relative-wrapper',
        safeOffset: {top: 157, left: 0, right: 0, bottom: 0}
      });
      $('div.stage img.stage-background').fluidCenterAlignImage({
        containerSelector: '.stage',
        safeOffset: {top: 157, left: 0, right: 0, bottom: 0}
      });
      /* top: 157 = the height of first and second navigation */
      
      
      // make navigation-second items sticky
      if (Drupal.settings.gazprom.singlePageMode != 'true')
        $('.second-navigation').stickyNavigation();
      
      // window resize handler
      $(window).unbind('resize.gazprom').bind('resize.gazprom', Drupal.gazprom.windowResize);
      
      // make a reference between a main navigation anchor and the floor
      var $listOfFloors = $('.content-floor-wrapper');
      $('#navigation-main ul.menu li a').each(function(i, elem){
        var $floor = $($listOfFloors.get(i+1));
        var $anchor = $(elem);
        $floor.data('referencingAnchor', $anchor);
      });
      
      // attach room navigators to rooms (sideways scrollers)
      Drupal.gazprom.init.roomNavigators();
      
      // light up all the indicators
      $('nav .indicator').each(function() {
        Drupal.gazprom.updateIndicator($(this), {duration: 0});
      });
      
      // hookup microsite
      Drupal.gazprom.init.microsite();
      
      // attach vertical scroll handler
      if (Drupal.settings.gazprom.singlePageMode != 'true')
        $(window).bind('scroll.gazprom', Drupal.gazprom.onScroll);
      
      // release the temporary click handler
      $('a').unbind('click.duringInitialization');
      
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
      
      Drupal.gazprom.init.exitBuildMode();
        

      
    },
    room: function($room) {
      // a room has been loaded and inserted, attach click handlers, etc
      if ($($room).length == 0) return;
      
      // set the room to a fixed width & height (the window's)
      $room.sizeRoom();
      
      // initialize/build a photo gallery
      Drupal.gazprom.photoGallery($room);

      // configure scrolling-list items (i.e. home page features)
      $room.find('.scrolling-list').scrollingList({
        fluidImageSafeOffset: {top: 88, left:0, right: 0, bottom: 0}
      });
      
      // add and configure parallax scrolling layers
      $room.find('.scrolling-list.parallax').once('parallax', function() {
        var $container = $(this);
        $container.append('<div class="parallax-layer parallax-1"></div><div class="parallax-layer parallax-2"></div><div class="parallax-layer parallax-3"></div>');
        $container.find('.scrolling-list-items').parallax(
          [{
              layer: $container.find('.parallax-1'),
              speed: 6,
              label: 'arrows'
            },
            {
              layer: $container.find('.parallax-2'),
              speed: 4,
              label: 'logos'
            },
            {
              layer: $container.find('.parallax-3'),
              speed: .1,
              label: 'depth'
            },
          ]);
      });
      
      // configure step-width containers
      $room.find('.step-width').stepWidth();
      
      // configure variable scrollers (i.e. news items) -- MUST come after step-width initialization
      $room.find('.variable-scroller').not('.grid-scroller').variableScroller({
        viewInnerSelector: '.view-content ul.item-list',
        itemSelector: '.view-content ul.item-list li',
        usePager: false,
        scrollButtons: true
      });
      $room.find('.variable-scroller.grid-scroller').variableScroller({
        viewInnerSelector: '.view-content table.views-view-grid tbody',
        rowSelector: '.view-content table.views-view-grid tr',
        itemSelector: '.view-content table.views-view-grid tbody td',
        scrollButtons: false,
        usePager: true
      });
      
      // configure webforms
      this.webform($room);
      
      // @TODO testing
      // configure tooltip popups
      $room.find('XXXa[title]:not(.tooltip-processed)').tooltip({
        effect: 'slide',
        position: 'center left',
        predelay: 100
      }).dynamic({}).addClass('tooltip-processed');

      if (Drupal.settings.gazprom.singlePageMode == 'true') return;
      // @TODO is this the best way to handle this?
      
      $room.find('.breadcrumb a').once('gazprom-click', function() {
        $(this).hijax();
      });

      $room.find('nav.third-navigation a').once('gazprom-click', function() {
        $(this).bind('click.gazprom', Drupal.gazprom.click_handlers.room);
      });
      
      // external links
      $room.find('a[href^="http://"]').attr("target", "_blank").addClass('gazprom-click-processed');
      
      // deal with home page (and other?) social media links
      $room.find('.social-links a').addClass('no-hijax');
      
      // deal with home page globe link
      $room.find('.world-link a').once('gazprom-click', function() {
        var $link = $(this);
        var $overlay = $link.siblings('.world-overlay');
        var $container = $link.parent();
        var $hoverItems = $($link, $overlay, $container);
        $container.hover(function() {
          $overlay.fadeIn(200);
        }, function() {
          $overlay.fadeOut(200);
        })
        // @TODO this is a temproary hack
      });
      
      var $exclusions = $room.find('.photo-grid a'); // @TODO not sure why this is needed.. grid items should have been processed already
      $room.find('a').not('.no-hijax').once('gazprom-click', function() {
        $(this).hijax();
      })
      
      Drupal.attachBehaviors($room); // @TODO doesn't seem to work .. ajax View filters aren't working
      
    },
    roomNavigators: function() {
      $('.content-floor-wrapper').each(function(i, elem) {
        var $floor = $(elem);
        var $floorNavAnchors = $floor.find('.second-navigation ul.menu a');
        $floor.find('.content-room-wrapper').each(function(i, elem) {
          var $room = $(elem);
          var $matchingAnchor;
          if ($room.prev('.content-room-wrapper').length > 0) {
            $matchingAnchor = $($floorNavAnchors.get(i-1));
            _prevNavigator($room, $matchingAnchor);
          }
          if ($room.next('.content-room-wrapper').length > 0) {
            $matchingAnchor = $($floorNavAnchors.get(i+1));
            _nextNavigator($room, $matchingAnchor);
          }
        });
      });
      
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
    microsite: function() {
      // see also the microsite.js code in the microsite module. That handles actual SWF insertion
      if (!Drupal.microsite) {
        console.log('Drupal.microsite JS object not present');
        return;
      }
      var $microsite = $('.stage #gazprom-microsite');
      if ($microsite.length == 0 ) return;
      
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
            Drupal.microsite.install({base: Drupal.settings.microsite.pathToAssets}, function(){
              Drupal.microsite.initFlashPlayer();
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
    
    enterBuildMode: function() {
    },
    exitBuildMode: function() {
      $('body').removeClass('simple').addClass('gazprom-built')
      $('html').removeClass('build-mode');
      $('html').css('overflow','');
      // always return scroll back to the .content-floor-wrapper we started with
      // and do one more window resize event
      setTimeout(function(){
        $(window).trigger('resize');
        var $firstRoom = $('#' + Drupal.settings.gazprom.scrollToFirst_id);
        Drupal.gazprom.scrollToRoom($firstRoom, {duration:0});
        if ($('#load-screen').length > 0 ) {
          $('#load-screen').delay(200).animate({
    //        top: '-' + $(window).height() + 'px'
  //            marginTop: '-' + $(window).height() + 'px'
            opacity: 0
          }, 500, function() {
            _finish();
          });
        }else {
          //_finish();
        }
      }, 200);

      // trigger resize (cleanup) of everything on slight delay
      setTimeout(function() {
       $(window).trigger('resize');
      }, 1000);
      // @TODO this needs help.. 1 second is way too long .. and shorter doesn't seem to help
      // with scrollingList resize of background images on home page
      // there is another directly above that triggers after 200.. why do we need both? 
      

      function _finish() {
        $('#load-screen').remove();
        
      }
    },
    
    webform: function($room) {
      var $webform = $room.find('form.webform-client-form');
      if ($webform.length == 0) return;
      
      if (!$.fn.ajaxForm) return; // singlePageMode? error?
      
      $webform.ajaxForm({
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
            Drupal.gazprom.init.room($room);
          }
        }
      });

    }

  }
})(jQuery);

(function($){
  /*
   * Settings and functions associated with Hijax (history.js and AJAX loading)
   * 
   */
  Drupal.gazprom.hijaxSettings = {
    initialized: false,
    previousStateID: 0,
    doAJAX: false,
    containerSelector: '.default-ajax-receiver:first',
    contentContainer: $([]),
    animateBefore: {},
    callback: {},
//    pageHit: function (path) {
//        googleAnalytics(path);
//    },
    readyCheck: function() {
      /* check to see if document is ready for first statechange */
      return $('body').is('.gazprom-built');
    },
    onStatechange: function(href, options, State) {
      var pathExtract = /^[a-z]+:\/\/\/?[^\/]+(\/[^?]*)/i;
      var newHref = (pathExtract.exec(State.cleanUrl))[1];

      Drupal.gazprom.openPath(newHref);
      
      return;
    }
  }
  
})(jQuery);


(function($){
  /*
   * BUILD functions are used to assemble the various pages of content
   * into the room & floor metaphors. This includes actually
   * loading the content via AJAX calls.
   */
  
   Drupal.gazprom.build = {
//  var build = {
    ajaxCounter: 0,
    showLoadScreen: true,
    start: function() {
      // initialize the home page as the first elevatorDestination in the directory
      // (elevatorDestination also does an AJAX load of the content if it is not
      //  .. already in the document)
      var $homeAnchor = $('a[href="/"]:first');
      Drupal.gazprom.directory.push(this.elevatorDestination($homeAnchor, {
        floor: 0,
        room: 0
      }, $('.content-floor-wrapper:first')));

      $('html').addClass('build-mode');
      $('html').css('overflow', 'hidden');
      if (this.showLoadScreen == true && Drupal.settings.gazprom.singlePageMode != 'true') {
        $('body').prepend('<div id="load-screen"></div>');
//        $('#load-screen').css('height', 0);
//        $('#load-screen').css({
//          height: $(window).height(),
//          marginTop: '-' + $(window).height() + 'px'
//        });
//        $('#load-screen').delay(500).animate({
//          marginTop: 0
//        }, 1000, function() {
//          $('#load-screen').css({
//            position: 'relative',
//            zIndex: 50
//          });
//          _finish();
//        });
        _finish();
      } else {
        _finish();
      }
      
      function _finish() {
        Drupal.gazprom.build.stage1();
      }
      
    },
    stage1: function() {
      /*
       * Load up all the sibling pages/rooms to the initial page/room that was
       * loaded by the URL request
       */
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

        $('.second-navigation ul.menu li a').each(function(roomIndex, elem) {
          var $menuAnchor = $(elem);
            Drupal.gazprom.directory.push(build.elevatorDestination($menuAnchor, {
            floor: currentFloor,
            room: roomIndex
          }, $('<div class="temp-wrapper"></div>')));
        });
      } else {
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
        if (build.ajaxCounter <= 0) {
          $(document).unbind('roomInstalled');
          build.stage2();
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

      // loop through the anchors in first-level navigation and install/load the
      // .. matching floor (first room)
      $('#navigation-main ul.menu li a').each(function(floorIndex, elem) {
        var $menuAnchor = $(elem);
        Drupal.gazprom.directory.push(build.elevatorDestination($menuAnchor, {
          floor: floorIndex + 1,
          room: 0
        }, $('.content-floor-wrapper:first')));
      });


    },
    stage2Progress: function() {

      this.ajaxCounter = 0; // reset counter, which then gets increased in the elevatorDestination function
      var build = this;
      
      $(document).unbind('roomInstalled').bind('roomInstalled', function() {
        build.ajaxCounter--;
        if (build.ajaxCounter <= 0) {
          // all floors finished installing (and first rooms are loaded)
          // .. so now fetch all the other rooms of each floor
          // .. (the sibling rooms of the initially loaded content happen to already
          // .. .. be loaded)
          $(document).unbind('roomInstalled');
          build.stage3();
          //build.complete();

        }
      });


    },
    stage3: function() {
      /*
       * Install all the remaining rooms of each floor installed during stage 2
       */
      
      // first, bind-up a progress handler
      this.stage3Progress();
      
      var build = this;
      
      // now load the additional rooms of each floor
      $('.second-navigation ul.menu').each(function(floorIndex, elem) {
        $(this).find('li > a').each(function(roomIndex, elem) {
          var $menuAnchor = $(elem);
          var newRoom = build.elevatorDestination($menuAnchor, {
            floor: floorIndex + 1,
            room: roomIndex
          }, $('<div class="temp-wrapper"></div>'));
          if (roomIndex > 0) {
            Drupal.gazprom.directory.push(newRoom);
            // the first rooms of each floor are already in the directory, but we still want
            // to send the 2nd-level nav anchor, to that room, into the elevatorDestination function
            // so it get a click handler properly attached
          }
        });
      });
      if ($('.second-navigation ul.menu').length == 0) build.complete();

    },
    stage3Progress: function() {
      
      this.ajaxCounter = 0;
      var build = this;
      
      $(document).unbind('roomInstalled').bind('roomInstalled', function() {
        build.ajaxCounter--;
        if (build.ajaxCounter <= 0) {
          build.complete();
        }
      });

    },
    complete: function() {
      /*
       * All rooms (and floors) have been installed/loaded
       */
      
      // wrap rooms in containers for scrolling and adjust sizes
      $('.content-floor-wrapper').each(function(){
        $(this).children('.content-room-wrapper').wrapAll('<div class="floor-slider width-full"><div class="rooms-of-floor"></div></div>');
        $(this).find('.rooms-of-floor:first').append('<div class="clearfix js-added-line-95"></div>')
        $(this).find('.floor-slider').css({
          overflow: 'hidden'
        });
      });
      
      
      // @TODO make this work with rooms on a floor? (for deep linking)
      Drupal.gazprom.init.document();


    },
    elevatorDestination: function($menuAnchor, location, $divTemplate) {
      
      var build = this;
      var destination = {
        name: $menuAnchor.text(),
        href: $menuAnchor.attr('href'),
        id: Drupal.gazprom.utility.urlToId($menuAnchor.attr('href')),
        location: location,
        children: new Array() // @TODO toss this?
      };

      // rangle the id some
      if (destination.id == '') {
        destination.id = 'home';
      }

      // is this the first room of a floor or is this an interior room?
      var $nav = $menuAnchor.closest('nav');
      var isFloor = ($nav.attr('id') == 'navigation-main' || $menuAnchor.attr('href') == '/')  ? true : false;

      var $newRoomWrapper =  $divTemplate.clone().empty();
      // see if the destination already has content (i.e. home page or content for deep-linking)
      // .. and if not, create a place for it and fetch the content for it
      var $room = $('#'+destination.id);
      if ($room.length == 0) {

        // the room, referenced by the $menuAnchor, is not yet in the DOM .. so lets add it
        $newRoomWrapper.addClass('content-wrapper temp-wrapper');
        $newRoomWrapper.append('<div class="content-room-wrapper temp-wrapper"></div>');
        // set the room wrapper's ID to match the href of the $menuAnchor
        // .. (this is probably redundent since the page.tpl.php file should also be doing this)
        $newRoomWrapper.find('.content-room-wrapper:first').attr('id', destination.id); // this DIV will actually get replaced by the AJAX content, but
        // .. we need to keep it in place, with the right ID, until the AJAX content arrives, so we know where the other rooms/floors need to be
        // .. placed in relation to it (before or after)

        // is this the first room of a floor or is this an interior room?
        if (isFloor) {
          // add first room of a floor
          var floorBefore = -1;
          // the only thing in the DOM so far should be first rooms of floors, so loop through them
          // .. and find the one that was assigned a floor number right before the one we're trying
          // .. to add now. If not found, then we add our room/floor to the end
          $('.content-floor-wrapper').each(function(){
            roomID = $(this).find('.content-room-wrapper:first').attr('id');
            roomData = Drupal.gazprom.utility.findDirectoryEntry(roomID);
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
            var $floorDIVbefore = $($('.content-room-wrapper').get(floorBefore)).closest('.content-floor-wrapper');
            $floorDIVbefore.after($newRoomWrapper);
          }else {
            // never found the floor before this one, so assume that this floor is before of whatever
            // .. floors are already in place
            var $floorDIVafter = $('.content-floor-wrapper:last');
            $floorDIVafter.before($newRoomWrapper);
          }
          // AJAX fetch the first room of the floor (page)
          build.ajaxCounter++;
          $.get(destination.href, function(data) {
            if ($('html').is('.ie8, .ie7, .ie6')) {
             $newContent = $(innerShiv($(data).find('.content-floor-wrapper:first').html()));
            }else {
              $newContent = $(data).find('.content-floor-wrapper:first');
            }
            $newContent = $newContent.children().unwrap();
            $newRoomWrapper.html($newContent);
            $(document).trigger('roomInstalled');
          });

//          $.ajax(destination.href, {
//            async: false,
//            success: function(data) {
//              if ($('html').is('.ie8, .ie7, .ie6')) {
//               $newContent = $(innerShiv($(data).find('.content-floor-wrapper:first').html()));
//              } else {
//                $newContent = $(data).find('.content-floor-wrapper:first');
//              }
//              //$newContent = $newContent.children().unwrap();
//              $newRoomWrapper.html($newContent);
//              $newRoomWrapper.children().unwrap();
//              $(document).trigger('roomInstalled');
//            }
//          });

        } else {
          // add other rooms of a floor (at least one was already loaded)
          var roomBefore = -1;
          $menuAnchor.closest('.content-floor-wrapper').find('.content-room-wrapper').each(function(){
            roomID = $(this).attr('id');
            roomData = Drupal.gazprom.utility.findDirectoryEntry(roomID);
            if (roomData) {
              if (roomData.location.room < location.room) {
                roomBefore = roomData.location.room;
              }
            } else {
              roomBefore = -1;
            }
          });
          if (roomBefore >= 0) {
            // found the room before the one we're working with already in the div
            // .. so add our new room right after it
            var $roomDIVbefore = $($menuAnchor.closest('.content-floor-wrapper').children('.content-wrapper').get(roomBefore));
            $roomDIVbefore.after($newRoomWrapper);
          } else {
            // never found the room before this one, so assume that this room is before of whatever
            // .. rooms are already in place
            var $roomDIVafter = $menuAnchor.closest('.content-floor-wrapper').children('.content-wrapper:first');
            $roomDIVafter.before($newRoomWrapper);
          }
          // AJAX fetch the room (page)
          build.ajaxCounter++;
          $.get(destination.href, function(data) {
            if ($('html').is('.ie8, .ie7, .ie6')) {
              $newContent = $(innerShiv($('<div>').append($(data).find('.content-room-wrapper:first')).html()));
            } else {
              $newContent = $(data).find('.content-room-wrapper:first');
            }
            $newRoomWrapper.empty().append($newContent);
            $newRoomWrapper.children().unwrap();
            $(document).trigger('roomInstalled');
          });

//          $.ajax(destination.href, {
//            async: false,
//            success: function(data) {
//              if ($('html').is('.ie8, .ie7, .ie6')) {
//                $newContent = $(innerShiv($('<div>').append($(data).find('.content-room-wrapper:first')).html()));
//              } else {
//                $newContent = $(data).find('.content-room-wrapper:first');
//              }
//              $newRoomWrapper.empty().append($newContent);
//              $newRoomWrapper.children().unwrap();
//              $(document).trigger('roomInstalled');
//            }
//          });

        }

      } else {
        // room already in place, but needs destination data attached
        //$room.data('destination', destination);
      }

      // hijack the anchor so it scrolls to the destination
      $menuAnchor.hijax();
      // @TODO is this hiding too much in here? Maybe a better place to connect the two?

      return destination;
      
    }
  }
  
  //$.extend(Drupal.gazprom, build);
})(jQuery);


(function($){
  Drupal.gazprom.click_handlers = {
    nav: function(e) {
      
      // @TODO depreciated by hijax.js ?
      
      var id = '';
      if (typeof (e.data) == 'object') {
        if (e.data != null) {
          if (e.data.id) {
            id = e.data.id;
          }
        }
      }
      if (id == '') {
        id = Drupal.gazprom.utility.urlToId($(e.currentTarget).attr('href'));
      }
      var $room = $('#' + id);
      if ($room.length == 0) {
        return true; // something went wrong
      }
      e.preventDefault();
      
      Drupal.gazprom.activeAnchor($(e.currentTarget));

      Drupal.gazprom.scrollToRoom($room);
      return false; // to the event bubbler

   },
    room: function(e) {
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
    }
  }
})(jQuery);

(function($){
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
      // @TODO strip http://example.com?
      id = url.toLowerCase().replace(/[^a-z0-9]/g, '-');
      id = id.replace(/^-/, ''); // remove possible first -
      id = id.replace(/^-/, ''); // remove possible second - !! (some HTML4 seems to be like #./news-media) @todo find out why?
      if (id == '' || id == '-') id = 'home'; // a href of "/" becomes home
      return id;
    },
    isInView: function(elem) {
      var docViewTop = $(window).scrollTop();
      var docViewBottom = docViewTop + $(window).height();

      var elemTop = $(elem).offset().top;
      var elemBottom = elemTop + $(elem).height();

      return ((elemBottom >= docViewTop + ($(window).height() / 2)) 
          && (elemTop <= docViewTop + ($(window).height() / 2)));
    }

  }
})(jQuery);

(function($) {
  
  $.fn.scrollingList = function(options) {
    var options = $.extend({
      scrollDuration: 1500,
      autoScrollInterval: 10000,
      autoScroll: true,
      parentHeightSelector: '.expand-top',
      fluidImageSafeOffset: {top: 0, left: 0, right: 0, bottom: 0}
    }, options);
    return this.once('scrollingList', function() {
      var $this = $(this);
      var $listWrapper = $this.find('.scrolling-list-items');
      var $list = $listWrapper.find('ul:first');
      var $items = $list.find('li');
      var $index = $this.find('.scrolling-list-index ul:first');
      
      
      $(window).bind('resizeComplete.scrollingList', function() {
        var parentHeight = $this.closest(options.parentHeightSelector).height();
        $listWrapper.css({
          height: parentHeight,
          overflow: 'hidden'
        });
        //$listWrapper.find('div, ul').css('height', 'auto');
        var itemHeight = parentHeight - parseInt($items.first().css('padding-top')) - parseInt($items.first().css('padding-bottom'));
        $items.css('height', itemHeight);
      }).trigger('resizeComplete.scrollingList');
      
      $index.find('li:first').addClass('active');
      _scrollToItem($items.first(), 0);
      
      // attach resize routine to background images
      $list.find('img.fancy-background-image').fluidCenterAlignImage({
        containerSelector: '.views-field-field-background-image',
        safeOffset: options.fluidImageSafeOffset
      });

      
      // configure tooltip popups
      $index.find('li:not(.tooltip-inside)')
        .addClass('tooltip-inside')
        .prepend('<div class="tooltip-trigger"></div>')
        .find('div.tooltip-trigger')
        .tooltip({
          effect: 'slide',
          position: 'center left',
          predelay: 100,
          relative: true,
          offset: [15,4],
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
      function _autoScroll() {
        if (options.autoScroll === true && $index.closest('.content-room-wrapper').is('.activated') && ($('.overlay-open').length == 0)) {
          currentPos++;
          if (currentPos > $items.length - 1) currentPos = 0;
          var $item = $($items.get(currentPos));
          _scrollToItem($item, options.scrollDuration);
          autoScrollTimeout = setTimeout(_autoScroll, options.scrollDuration + options.autoScrollInterval);
        } else {
          // try again at the next interval
          autoScrollTimeout = setTimeout(_autoScroll, options.autoScrollInterval);
        }
      }
      autoScrollTimeout = setTimeout(_autoScroll, options.autoScrollInterval);
      
      function _scrollToItem($item, duration) {
        $listWrapper.stop(true).scrollTo($item, {
          duration: duration,
          easing: 'easeOutCubic',
          onAfter: function() {
            var pos = $items.index($item);
            $index.find('li.active').removeClass('active');
            $($index.find('li').get(pos))
              .addClass('active')
              .find('div.tooltip-trigger').tooltip().hide();
          }
        });
      }
      
    });
  }
  
  $.fn.parallax = function(configArray) {
    
    // only works with one element
    var $scroller = $($(this).get(0));
    
    // store the orginal tops of the layers (incase there are any offsets)
    var originalTops = [];
    $.each(configArray, function(index, config) {
      originalTops[index] = parseInt(config.layer.css('top'));
    });
    // bind scroller function
    $scroller.bind('scroll.parallax', function() {
      // how far have we moved
      var delta = $scroller.scrollTop();
      $.each(configArray, function(index, config) {
        //var adjustment = -1 * Math.floor(delta * config.speed);
        var adjustment = -1 * delta * config.speed;
        // adjust this layer
        config.layer.css('top', originalTops[index] + adjustment);
        //console.log('move ' + config.label + ' top to ' + (originalTops[index] + adjustment)+'px');
      })
    })
    
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
      duration: 1000
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
      $container.find('ul.pager').css('display','none');
      
      // grab the (possible) total item count from the View's footer
      vars.totalItemCount = Number($container.find('.view-footer span.view-total-count').text());
      // how many items get loaded with each AJAX call (hint, at initialization, it's the current total)
      vars.itemsPerRequest = $container.find(vars.itemSelector).length;
      // how many items fit in the current scroller view
      vars.itemsPerView = _itemsPerView(vars);
      // build the pager (if needed);
      _updatePager(vars);
      // bind a handler for change to the container width
      vars.container.closest('.step-width').bind('step-width-resize.variableScroller', function() {
        vars.itemsPerView = _itemsPerView(vars);
        _updatePager(vars);
      });
      
      // always try and load one more page of content (so content is ready to be scrolled in)
      _loadMoreContent(vars);
      
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
          vars.currentPageNum++;
          _updatePageNum(vars);
      vars.container.scrollTo({top: 0, left: '+=' + amount + 'px'}, vars.duration, {onAfter: function() {
          _updateButtons(vars);
          _loadMoreContent(vars);
      }});
    }
    
    function _scrollBack(vars) {
      var amount = vars.container.width();
          vars.currentPageNum--;
          _updatePageNum(vars);
      vars.container.scrollTo({top: 0, left: '-=' + amount + 'px'}, vars.duration, {onAfter: function() {
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
        vars.container.scrollTo({top:0, left: position+'px'}, vars.duration, {onAfter: function() {
            var $pagerItems = vars.$pager.find('.variable-scroller-pager-item');
            _updateButtons(vars);
            _loadMoreContent(vars); // always good to load one more page
        }})
      }
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
      if (!pagerNextHref) return;
      // is this a hack? find the view_name and view_display_id values from the classes
      var classArray = vars.container.find('.view:first').attr('class').split(' ');
      var view_name, display_id;
      $.each(classArray, function(index, value) {
        if (value.substring(0,8) == 'view-id-') {
          view_name = value.replace('view-id-', '');
        }
        if (value.substring(0,16) == 'view-display-id-') {
          display_id = value.replace('view-display-id-', '');
        }
      });
      if (!view_name && ! display_id) return; // something went wrong
      
      href = '/views/ajax' + '?view_name=' + view_name + '&view_display_id=' + display_id + '&' + pagerNextHref.split('?')[1];
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
          });
        } else {
          // looks to be floating LI's
          vars.container.find(vars.viewInnerSelector).append($newContent);
        }
        vars.container.find('ul.pager').empty().append($newPager); // this is the Views pager, not our page
        
        // make sure new content is attached to handlers
        Drupal.gazprom.init.room(vars.container.closest('.content-room-wrapper'));
        
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
        vars.container.find(vars.itemSelector).each(function() {
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
  
  $.fn.stickyNavigation = function(options) {
    var settings = $.extend({
      breakpointPadding: 0,
      scrollTimeout: 10
    }, options);
    
    var $navbars = $(this);
    var headerHeight = $('#header').outerHeight(); // this is soon to be the absolute top of our nav
    
    var scrollTimeout = 0;
    $(window).bind('scroll.stickyNavigation', function() {
      
      //scrollTimeout = setTimeout(function(){
        var scrollTop = $(window).scrollTop();
        var breakpoint = scrollTop + headerHeight;
        $navbars.each(function() {
          var $nav = $(this);
          var navHeight = $nav.outerHeight(true);
          var top = $nav.position().top;
          var $floorWrapper = $nav.closest('.content-floor-wrapper');
          var floorBottom = $floorWrapper.position().top + $floorWrapper.outerHeight(true);

          // check to see if we should scroll past without doing anything (see .scrollToRoom)
          if ((Drupal.gazprom.linkScrollInEffect == true) && !$nav.hasClass('scroll-destination') && !$nav.hasClass('stuck')) return;
          
          // test to see if this element needs to become stuck
          if (!$nav.hasClass('stuck') && (top <= (breakpoint + settings.breakpointPadding)) && (floorBottom - navHeight > (breakpoint + settings.breakpointPadding))) {
            // @TODO make this somehow unidirectional? (comparing scrollTop to previousScrollTop didn't seem to work well)
            _stickIt($nav);
          } else if ($nav.hasClass('stuck')) {
            var $oldPosition = $nav.parent().find('.stucks-old-position');
            // test to see if this element is stuck and should be unstuck
            if ($oldPosition.length > 0) {
              if ($oldPosition.position().top >= breakpoint) {
                // scrolling down, and old position has past the breakpoint, so release the nav element
                _unstickIt($nav);
              }
            }
            if (floorBottom - navHeight <= breakpoint) {
              // scrolling up, and the floor bottom has hit the bottom of the fixed nav, so release the nav
              // .. and make room for the new nav coming in.
                _unstickIt($nav);
            }
          }

          previousScrollTop = scrollTop;

          function _stickIt($element) {
            $element.css({
              position: 'fixed',
              top: 0 + headerHeight,
              zIndex: 49
            }).addClass('stuck');
            $element.before('<div class="stucks-old-position" style="height:' + $element.outerHeight(true) + 'px;"></div>');
          }
          function _unstickIt($element) {
            $element.css({
              position: '',
              top: '',
              zIndex: ''
            }).removeClass('stuck');
            $element.siblings('.stucks-old-position').remove();

          }
          function _adjustTop($element, newTop) {
            $element.css({top: newTop, zIndex: 48});
          }


        });

        
      //}, settings.scrollTimeout);
      
     });
    
    return $(this);
  }
  
  $.fn.sizeRoom = function () {
    
    return $(this).once('sizeRoom', function() {
      
      var $window = $(window);
      var $room = $(this);
      var footerHeight = $('#footer-page').height();
      
      $window.bind('resize.sizeRoom', function() {
        var winWidth =  $window.width(); // window.innerWidth; //$(window).width() + 10;
        var winHeight = $window.height(); // window.innerHeight; //$(window).height();


        var roomWidth = winWidth ;
        var roomHeight = winHeight - footerHeight;
        if (roomHeight < 955) roomHeight = 955;
        if (roomWidth < 980) roomWidth = 980;

        $room.css({
          width: roomWidth,
          height: roomHeight,
          'float': 'left'
        })     
      }).trigger('resize.sizeRoom'); // @TODO does this retrigger previously bound functions?
    });
  }
  
  $.fn.stepWidth = function() {
    return $(this).once('stepWidth', function() {
      var $container = $(this);
      var $parent = $container.parent();
      var settings = {
//        defaultStep: 430
        defaultStep: 200
      }, stepSize = settings.defaultStep, stepMin = 1 * stepSize, minWidth =0, maxWidth = 1920;
      
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
      });

      $(window).bind('resizeComplete.stepWidth', function() {
        var parentWidth = $parent.width();
        var newWidth = Math.floor(parentWidth / stepSize) * stepSize;
        if (newWidth < stepMin) newWidth = stepMin;
        if (newWidth < minWidth) newWidth = minWidth;
        if (newWidth > maxWidth) newWidth = maxWidth;
        $container.css('width', newWidth);
        //console.log('setWidth, newWidth = ' + newWidth);
        $container.trigger('step-width-resize'); // this signals children that this step-width container has changed size
      }).trigger('resizeComplete.stepWidth');
      
    });
  }
  
  
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
      safeOffset: {top: 0, left: 0, right: 0, bottom: 0}
    }, options);
    
    $(window).unbind('resize.fluidCenterAlignImage').bind('resize.fluidCenterAlignImage', function() {
      $('img.fluid-center-align').trigger(settings.eventName);
    });

    return $(this).each(function(){
      var $image = $(this);
      var $container = $image.closest(settings.containerSelector);
      if ($container.length == 0) return;
      
      var imageWidth, imageHeight;

      $image.unbind(settings.eventName).bind(settings.eventName, function(e) {
        if (!imageWidth || !imageHeight) {
          imageWidth = $image.width();
          imageHeight = $image.height();
        } 
        _fluidCenterAlignImage({$image: $image, width: imageWidth, height: imageHeight}, $container);
      }).addClass('fluid-center-align');
      
      imageWidth = $image.width();
      imageHeight = $image.height();
      if (!imageWidth || !imageHeight) {
        var src = $image.attr('src');
        $image.attr('src',''); // stop loading
        $image.bind('load.resizeFluidImages', function(e) {
          imageWidth = $image.width();
          imageHeight = $image.height();
          $image.trigger(settings.eventName);
        }).attr('src', src);
      } else {
        $image.trigger(settings.eventName);
      }
      
    });
 
    function _fluidCenterAlignImage(imageData, $container) {

      var $image = imageData.$image;
      var imageWidth = imageData.width;
      var imageHeight = imageData.height;
      
      // grab the container's width & height
      var viewerHeight = $container.outerHeight();
      var viewerWidth = $container.outerWidth();
      if ((imageWidth / imageHeight) > (viewerWidth / viewerHeight)) {
        $image.css({width: 'auto', height: '100%', marginTop: '0', marginLeft: '0'});
        // see if the new width is now pushed past the viewport
        var newWidth = (viewerHeight / imageHeight) * imageWidth;
        // must calculate what the width has become (web browser might not tell us yet)
        if (newWidth > viewerWidth) {
          var horizontalOffset = Math.floor((newWidth / 2) - (viewerWidth / 2) - ((settings.safeOffset.left + settings.safeOffset.right) / 2));
          $image.css({marginLeft: '-' + horizontalOffset + 'px', marginRight: 'auto'});
        }
      } else {
        $image.css({width: '100%', height: 'auto', marginTop: '0', marginLeft: '0'});
        // see if the new height is now pushed past the viewport
        var newHeight = (viewerWidth / imageWidth) * imageHeight;
        // must calculate what the height has become (web browser might not tell us yet)
        if (newHeight > viewerHeight) {
          var verticalOffset = Math.floor((newHeight / 2) - (viewerHeight / 2) - ((settings.safeOffset.top + settings.safeOffset.bottom) / 2));
          $image.css({marginTop: '-' + verticalOffset + 'px'});
        }
      }
    }

    
  }
  
 
})(jQuery);
