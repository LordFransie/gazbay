(function($) {

	// for History.js
    
    // Experimental code developed for History.js
    // version 0.2b 2011-11-27 jon@system-werks.com
	
    hijax = {};
	
	var hijax_options = {
		context: 'hijax.js',
		containerSelector: '.default-ajax-receiver:first',
		contentContainer: $([]),
		animateBefore: {},
		callback: {},
		pageHit: {},
		readyCheck: function() {
			/* this method always return false until it is overridden. When $.hijax_init is called
			 * later on, a new function will override this one and apply real logic
			 */
			return false;
		},
		onStatechange: function(href) {
			return
		},
		initialized: false
	}, rootURL = document.location.protocol+'//'+(document.location.hostname||document.location.host);

	$.hijax_init = function(options) {

		if (!hijax_options.initialized) {
			hijax_options = $.extend(hijax_options, options);
			hijax_options.initialized = true;
            options.initialized = true;
		}
		
        if (typeof History != 'undefined') if (History.Adapter) {
          History.Adapter.bind(window, 'anchorchange', function(e) {
            e = e;
          })
          History.Adapter.bind(window,'statechange', stateChanger);
          History.Adapter.bind(window,'anchorchange', anchorChanger);
        }
		return;
	}

	$.fn.hijax = function() {
      
      if (typeof window.History == 'undefined') return this;

      return this.addClass('hijaxed').unbind('click.hijax').bind('click.hijax', hijax.clickHandler);
	}
    
    hijax.clickHandler = function(e) {
      if (typeof window.History == 'undefined') return true;
      e.preventDefault();
      //var $link = $(this);
      var $link = $(e.currentTarget);
      var href = $link.attr('href');
      if (typeof href == 'undefined') return;
      if (href == '') return;
      href = decodeURI(href);
      href = href.replace(rootURL,'');
      //$(window).data('lastClick', $link); // @TODO is this incredibly lazy and weak? // @TODO get rid of this
      
      var State = window.History.getState();
      var pathExtract = /^[a-z]+:\/\/\/?[^\/]+(\/[^?]*)/i;
      var previousHref = (pathExtract.exec(State.cleanUrl))[1];

      //if (href != '#' && window.History) window.History.pushState({previousHref: previousHref}, null, href);
      if (href != '#' && window.History) window.History.pushState(null, null, href);

      /* TODO:
          consider extracting the 'title' attribute from the anchor and add to pushState ??

      */

      return false;
    }

	$.hijax_addState = function(href, data, force) {
		if (typeof(data) == 'undefined') data = {};
        
        var State = window.History.getState();
        var pathExtract = /^[a-z]+:\/\/\/?[^\/]+(\/[^?]*)/i;
        var previousHref = (pathExtract.exec(State.cleanUrl))[1];
        
        $.extend(data, {previousHref: previousHref});
        
		href = href.replace(rootURL,'');
		
		if (href != State.url.replace(rootURL,'') || force) {
          if (data.newWindowTitle) {
			//window.History.pushState(data, data.newWindowTitle, href);
			window.History.pushState(null, data.newWindowTitle, href);
          } else {
			//window.History.pushState(data, null, href);
			window.History.pushState(null, null, href);
          }
		}
	
	}
    
    $.hijax_replaceState = function(href, data, force) {
      if (typeof(data) == 'undefined') data = null;

      href = href.replace(rootURL,'');
      var State = window.History.getState();

      if (href != State.url.replace(rootURL,'') || force) {
        if (data.newWindowTitle) {
          window.History.replaceState(data, data.newWindowTitle, href);
        } else {
          window.History.replaceState(data, null, href);
        }
      }

      // @TODO not sure window.History.replaceState is working or at least it's not doing what I expect it to do
    }
    
    $.hijax_getState = function() {
      
      return window.History.getState();
    }
	
	//$(window).bind('statechange', function(){
    //History.adapter.bind(window, 'statechange', function() {
    var stateChanger = function() {  
		var options = $.extend({
          doAJAX: true,
          skipCallback: false,
          newWindowTitle: null,
          context: 'statechange'
        }, hijax_options);

		// check to see if everything is ready for a statechange (entry URL has a path)
		if (!options.readyCheck.call(this)) {
			/* document is not ready to handle a statechange yet .. so delay and try again */
			setTimeout(function(){
				$(window).trigger('statechange')
			}, 500);
			return; // exit from this statechange function
		}
		
		var
			State = window.History.getState(),
            data = State.data,
			url = State.url,
			href = url.replace(rootURL,'');
            
        if (typeof(data.options) == 'object') options = $.extend(options, data.options);
        
		if (!options.skipCallback) options.onStatechange.call(this, href, options, State);
				
        if (options.newWindowTitle) document.title = options.newWindowTitle; // @TODO not utilizing this.. good or bad idea?
        
		if (options.doAJAX && options.contentContainer.length > 0) {
			$.ajax({
				type: 'GET',
				url: href,
				beforeSend: function() {
					document.body.style.cursor = "wait";
					//$link.addClass('hijax-loading');
					$('a[href="'+href+'"]').addClass('hijax-loading');
					if (options.beforeSend) options.beforeSend.call(this, options);
				},
				success: function(htmlData, statusText, xhr) {
					document.body.style.cursor = "default";
					var htmlToInsert;
					if ($(options.containerSelector, htmlData).length > 0) {
						htmlToInsert = $(options.containerSelector, htmlData).html();
					} else {
						htmlToInsert = htmlData;
					}
					options.htmlToInsert = htmlToInsert;
					if (typeof(options.beforeAjaxInsert) == 'function') {
						options.beforeAjaxInsert.call(this, options, function () {
							options.contentContainer.html(options.htmlToInsert);
							if (options.callback) options.callback.call(this, options);		
						});
					} else {
						options.contentContainer.html(options.htmlToInsert);
						if (options.callback) options.callback.call(this, options);		
					}	
				},
				error: function(errorData, errorStatus, errorThrown) {
					document.body.style.cursor = "default";
					if (false) {
						if (typeof(options.animateBefore) == 'function') {
							options.animateBefore.call(this, options, function () {
								options.contentContainer.html(errorData.responseText);
								if (options.callback) options.callback.call(this, options);		
							});
						} else {
							options.contentContainer.html(errorData.responseText);
							if (options.callback) options.callback.call(this, options);		
						}	
					} else {
						if (errorData.status == 404) {
							alert('Page not found: ' + this.url);
						} else {
							alert(errorThrown + ': ' + this.url);	
						}
					}
				}
			});
		}
		
		return false;
	//});
    };
    
    var anchorChanger = function(e) {
      e.preventDefault();
      return false;
    }
    

	function debug(msg, displayAlert) {
		if (window.location.hostname != 'dev.atlason.com') return;
		(typeof(displayAlert) == 'undefined') ? false : displayAlert;
		if (window.console) console.log (msg);
		if (displayAlert) alert('Debug: ' + msg);
		return;
	}
	
	
})(jQuery);