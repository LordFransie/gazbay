
(function($, Drupal) {
Drupal.behaviors.gazprom = {
    attach: function (context, settings) {

      var $context = $(context);
      
      $context.find('.inline-content-cycler').inlineContentCycler({
        noIndex: true,
        videoImmediately: true
      });

      //$context.find('.inline-content-cycler ul li img')
      return;
    }
  };
  
  $(document).bind('pageinit', function (e) {
    Drupal.attachBehaviors();
  });
  
  $(document).bind('pageshow', function(e) {
    var path = window.location.pathname;
    
    if ((typeof(_gaq) == 'object') && path) {
        _gaq.push(['_trackPageview', path]);
    }
  })
  
})(jQuery, Drupal);

(function($, Drupal) {

Drupal.gazprom_mobile = {
  init: null
}


  $.fn.inlineContentCycler = function(options) {
    
    var defaults = {
      duration: 1000,
      easing: 'swing',
      noIndex: false,
      videoImmediately: false
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

      if (!settings.videoImmediately) {
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
      } else {
        $listItems.each(function() {
          var $listItem = $(this);
          var $item = $listItem.children('img:first');
          _playVideo($item, false);
          $listItem.children().not('iframe').remove();
        });
      }


      if ($listItems.length > 3 && !settings.noIndex) {
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

        if (typeof $.fn.variableScroller != 'undefined') {
          $wrapper.find('.inline-content-cycler-index').variableScroller({
            viewInnerSelector: null,
            itemSelector: 'ul.index-list li',
            staticContent: true
          });
          //$listItems.first().addClass('active');
        }
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
        _playVideo($item, true);
//        var $player = $('<iframe width="' + $item.width() + '" height="' + $item.height() + '" src="" frameborder="0" allowfullscreen></iframe>');
//        $item.after($player);
//        $player.attr('src', 'http://www.youtube.com/embed/' + $item.attr('data-youtube') + '?rel=0&autoplay=1&autohide=1');
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
    
    function _playVideo($item, autoPlay) {
      var width = $item.width();
      var height = $item.height();
      if (width == 0 || height == 0) {
        width = '100%';
        height = 'auto';
      }
      var $player = $('<iframe width="' + width + '" height="' + height + '" src="" frameborder="0" allowfullscreen></iframe>');
      $item.after($player);
      if (!autoPlay) {
        $player.attr('src', 'http://www.youtube.com/embed/' + $item.attr('data-youtube') + '?rel=0&autoplay=0&autohide=1');
      } else {
        $player.attr('src', 'http://www.youtube.com/embed/' + $item.attr('data-youtube') + '?rel=0&autoplay=1&autohide=1');
      }
    }
  }

})(jQuery, Drupal);