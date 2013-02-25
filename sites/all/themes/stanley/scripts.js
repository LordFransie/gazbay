(function($) {

Drupal.stanley = Drupal.stanley || {};
Drupal.behaviors.stanley = {};

//offset table header
Drupal.settings.tableHeaderOffset = 'Drupal.stanley.topbar.height';
Drupal.stanley.topbar = Drupal.stanley.topbar || {};
Drupal.stanley.topbar.height = function() {
  return $("#topbar").height();
};

//Drupal behaviours
Drupal.behaviors.stanley.attach = function(context) {
  // If there are both main column and side column buttons, only show the main
  // column buttons if the user scrolls past the ones to the side.
  $('div.form .row:has(div.column-main div.actions):not(.stanley-processed)').each(function() {
    var form = $(this);
    var offset = $('div.column-side div.actions', form).height() + $('div.column-side div.form-actions', form).offset().top - eval(Drupal.stanley.topbar.height());
    $(window).scroll(function () {
      if ($(this).scrollTop() > offset) {
        $('div.column-main div.actions', form).show();
      }
      else {
        $('div.column-main div.actions', form).hide();
      }
    });
    form.addClass('stanley-processed');
  });

  //turn buttons in to bootstrap buttons
  $('.button').addClass('btn').removeClass('button');
  $('.fake-ok').addClass('primary');

  //mark drupal messages as alerts
  //bootstrap alert only work on bootstrap classes, minor copy of alert closing
  $('.messages .close').click(function (e) {
    var $element = $(this).parent('.messages')

    e.preventDefault();
    $element.remove();
  });

  //main help
  $('#help').hide();
  $('.main-help-marker').click(function() {
    var isActive = $(this).hasClass('active');

    if (isActive) {
      $(this).removeClass('active');
      $('#help').slideUp(100);
    }
    else {
      $(this).addClass('active');
      $('#help').slideDown(100);
    }
  });
};

//extend jquery.ui dialog
var _init = $.ui.dialog.prototype._init;
$.ui.dialog.prototype._init = function() {
  var self = this;
  _init.apply(this, arguments);

  //bootstrap actions
  $('.ui-dialog-buttonpane').addClass('actions');
  $('.ui-dialog-buttonset button').addClass('btn');
  $('.ui-dialog-buttonset button:first').addClass('primary');
};


function getFormItemHelpText() {
  var description = $(this).find('.description').html();
  if (description) {
    return description;
  }
}

})(jQuery);
