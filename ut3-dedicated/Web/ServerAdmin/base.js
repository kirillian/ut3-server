
$(document).ready(function(){
  if (jQuery.browser.msie && parseFloat(jQuery.browser.version) < 7) {
    // fix "buttons" to work properly in MSIE<7
    $('button[name!=""]').each(function() {
      this.realBtnName = this.name;
      this.name = '';
      $(this).click(function() {
        this.name = this.realBtnName;
        this.form.submit();
      });
    });
  } /* end if */
  $('#menu a[href='+window.location.pathname+']').addClass('active');
  windowAlert = window.alert;
  window.alert = messageAlert;
  
  $('body').append('<div id="promptDialog"><div id="promptWindow"><p></p>'+
    '<input type="text" size="40" /><br /><button type="button" id="promptOk">Ok</button>'+
    ' <button type="button" id="promptCancel">Cancel</button></div></div>');
  
  var styles = $('link[rel*="style"][title]');
  if (styles.size() > 1) {
    var cssChooser = $('<select id="cssChooser"></select>');
    var selectedCss = $.cookie('webadminstyle');
    if (selectedCss != undefined) {
      $.cookie('webadminstyle', selectedCss, { expires: 365, path: '/' });
    }
    styles.each(function() {
      var cssLink = $(this);
      if(cssLink.attr('title') != undefined) {
        if (selectedCss == undefined) {
          selectedCss = cssLink.attr('title');
        }
        var isselected = selectedCss == cssLink.attr('title');
        cssLink.attr('disabled', true); // to work around a quirk in MSIE
        cssLink.attr('disabled', !isselected);
        cssChooser.append('<option value="'+cssLink.attr('title')+'"'+(isselected?' selected="selected"':'')+'>'+cssLink.attr('title')+'</option>');
      }
    });
    cssChooser.change(chooseCss);
    $('#footer').append($('<div id="skinSelector"><h5>Select Style</h5></div>').append(cssChooser));
  }
});

function chooseCss() {
  var selectedCss = $('#cssChooser').val();
  $('link[rel*="stylesheet"][title]').each(function() {
    var cssLink = $(this);
    cssLink.attr('disabled', selectedCss != cssLink.attr('title'));
  });
  $.cookie('webadminstyle', selectedCss, { expires: 365, path: '/' });
}

function messageAlert(text, type) {
  if (text == undefined) text = "";
  if (type == undefined) type = "error";
  var old = $('#messages .oldMessage');
  text = ""+text;
  var newmsg = $('<div class="message '+type+'">'+text.replace("\n", "\n<br />")+'</div>');
  newmsg.hide();
  $('#messages').prepend(newmsg);
  newmsg.fadeIn();
  old.remove();
  $('#messages *').addClass('oldMessage');
  var pos = $('#messages').offset();
  if (pos.top < $(window).scrollTop()) {
    window.scrollTo(pos.left, pos.top);
  }
}

function messagePrompt(text, callback, defVal) {
  var promptUI = $('#promptDialog');
  if (promptUI) {
    if (callback == undefined) callback = function () {};
    var edit = $('input[type=text]', promptUI);
    edit.val(defVal);
    $('p', promptUI).remove();
    edit.before('<p>'+text+'</p>');
    var btnCancel = $('#promptCancel');
    btnCancel.click(function(){ promptUI.hide(); });
    var btnOk = $('#promptOk');
    btnOk.click(function(){ promptUI.hide(); callback(edit.val());} );
    edit.keypress(function (e) { 
      if (e.which == 13) btnOk.click();
      else if (e.keyCode == 27) btnCancel.click();
    });
    promptUI.show();
    edit.focus();
  }
  else {
    var val = window.prompt(text, defVal);
    if (val != undefined && callback != undefined) {
      callback(val);
    }
  }
}
