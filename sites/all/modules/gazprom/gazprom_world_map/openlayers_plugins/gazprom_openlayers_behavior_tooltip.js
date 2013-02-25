

(function($, Drupal) {
  /**
  * @file
  * JS Implementation of OpenLayers behavior.
  */

  /**
  * Javascript Drupal Theming function for inside of Tooltips
  *
  * To override
  *
  * @param feature
  *  OpenLayers feature object.
  * @return
  *  Formatted HTML.
  */
  Drupal.theme.prototype.gazpromOpenlayersTooltip = function(feature) {
    var output = '';

	output += '<div class="olPopup-container openlayers-tooltip">';
    output += '<div class="openlayers-tooltip-graphic"></div>';
    output += '<div class="content">'
    if (feature.attributes.name) {
//      output += '<div class="openlayers-tooltip-name">' + feature.attributes.name + '</div>';
    }
    if (feature.attributes.description) {
      output += '<div class="openlayers-tooltip-description">' + feature.attributes.description + '</div>';
    }
	output += '<div class="clearfix"></div></div></div>';

    return output;
  };

  /**
  * OpenLayers Tooltip Behavior
  */
  Drupal.openlayers.addBehavior('gazprom_openlayers_behavior_tooltip', function (data, options) {
    var map = data.openlayers;
    var layers = [];

    // For backwards compatiability, if layers is not
    // defined, then include all vector layers
    if (typeof options.layers == 'undefined' || options.layers.length == 0) {
      layers = map.getLayersByClass('OpenLayers.Layer.Vector');
    }
    else {
      for (var i in options.layers) {
        var selectedLayer = map.getLayersBy('drupalID', options.layers[i]);
        if (typeof selectedLayer[0] != 'undefined') {
          layers.push(selectedLayer[0]);
        }
      }
    }
    
    var timeout;

    // Define feature select events for selected layers.
    var popupSelect = new OpenLayers.Control.SelectFeature(layers, {
      activeByDefault: true,
      highlightOnly: false,
      multiple: false,
      hover: false,
      callbacks: {
//        'over': function(feature) {
//          //console.log('over feature');
//          // @TODO select it?
//          //this.select(feature);
//        },
//        'click': function(feature) {
//          this.select(feature);
//        },
        'touchstart': function(feature) {
          this.select(feature);
        }
      },
        onSelect: function(feature) {
          // Create Anchored popup for tooltip.
          var output = Drupal.theme('gazpromOpenlayersTooltip', feature);
          if (typeof output != 'undefined') {
            // deal with client request to center the map
            setTimeout(function(){
              var map = feature.layer.map;
              var mapCenterLonLat = map.getCenter();
              var mapCenterPx = map.getViewPortPxFromLonLat(mapCenterLonLat);
              var featureLonLat = feature.geometry.getBounds().getCenterLonLat();
              var featurePx = map.getViewPortPxFromLonLat(featureLonLat);
              map.pan(featurePx.x - mapCenterPx.x, featurePx.y - mapCenterPx.y);
            }, 50);
            var popup = Drupal.openlayers.gazprom.popup.full(feature);

            feature.layer.map.addPopup(popup);
            feature.popup = popup;
            popup.draw();
            var $popup = $(popup.div);
            var $desc = $popup.find('.openlayers-tooltip-description');
            if ($desc.find('.views-field-field-image').length > 0) {
              $desc.addClass('contains-image');
            } else {
              $desc.addClass('no-image');
            }
            $popup.css('filter',''); // no idea why (maybe for IE7?), but OpenLayers(?) adds "filter: alpha(opacity=100);" to DIV and this causes black halo around flame on IE8
            popup.updateSize();
            $popup.find('.openlayers-tooltip .content').fadeOut(0).fadeIn(750);
            Drupal.attachBehaviors($popup);
            feature.layer.drawFeature(feature, 'visibility: hidden;');
          }
        },
        onUnselect: function(feature) {
          // Remove popup.
          if (typeof feature.popup != 'undefined') {
            feature.layer.map.removePopup(feature.popup);
            feature.popup.destroy();
            feature.popup = null;
          }
          feature.layer.drawFeature(feature, 'visibility: visible;');
        }
      }
    );

    // Actiate the popups
    map.addControl(popupSelect);
    popupSelect.activate();
  });
  
  
  Drupal.openlayers.gazprom = {};
  Drupal.openlayers.gazprom.popup = {
    test: function(feature) {
        var popup = new OpenLayers.Popup.Anchored(
          'popup',
          feature.geometry.getBounds().getCenterLonLat(),
//          new OpenLayers.Size(200, 100),
          null,
          Drupal.theme('gazpromOpenlayersTooltip', feature),
          null,
          false
        );
          
        popup.calculateRelativePosition = function () {
          return 'br';
        }
        popup.anchor.offset.y = -93; // this is the hight of the RELEVANT pixels of the Gazprom Large Flame Lit graphic (there is padding for flame effect)
        popup.backgroundColor = 'rgba(255,0,0,.3)';
        popup.panMapIfOutOfView = true
        popup.keepInMap = false;
        
        
        
        return popup;
      
    },
    full: function(feature) {
      
        var popupSize = new OpenLayers.Size(300, 138);
        var popupAnchor = {
          size: new OpenLayers.Size(1,1),
          offset: new OpenLayers.Pixel(-41, -93) // needed to compensate for the padding around the flame glow
        };
        var popup = new OpenLayers.Popup.Anchored(
          'gazprom-tooltip',
          feature.geometry.getBounds().getCenterLonLat(),
          popupSize,
          Drupal.theme('gazpromOpenlayersTooltip', feature),
          popupAnchor,
          false
        );
          
        popup.calculateRelativePosition = function () {
          return 'br';
        }
        popup.backgroundColor = 'transparent';
//        popup.backgroundColor = 'rgba(255,0,0,.3)';
        popup.panMapIfOutOfView = false
        popup.keepInMap = false;
        popup.padding = 0;
        popup.autoSize = false;

        var $popup = $(popup.div);
        $popup.addClass(popup.relativePosition);

        return popup;
    }
    
  }
})(jQuery, Drupal);
