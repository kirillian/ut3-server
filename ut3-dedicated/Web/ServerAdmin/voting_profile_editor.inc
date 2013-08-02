<form method="post" action="<%page.fulluri%>" id="profileform">
<fieldset>
  <legend><%profile.friendlyname%></legend>
  <input type="hidden" name="profilename" value="<%profilename%>" />
  
  <dl>
    <dt><label for="friendlyname">Profile name</label></dt>
    <dd><input type="text" name="friendlyname" id="friendlyname" value="<%profile.friendlyname%>" size="40" maxlength="128" /></dd>
    
    <dt><label for="gameclass">Game type</label></dt>
    <dd><select id="gameclass" name="gameclass"><%gametypes%></select></dd>
    
    <dt><label for="maplist">Map list</label></dt>
    <dd><select id="maplist" name="maplist"><%maplists%></select></dd>
  
    <dt title="Additional options to configur the game. These are the same options you would use on the launch URL."><label for="options">Options</label></dt>
    <dd><textarea id="options" name="options" cols="60" rows="2"><%profile.options%></textarea></dd>
    
    <dt>Mutators</dt>
    <dd id="mutatorField"><%mutators%></dd>
    
    <dt>Excluded mutators</dt>
    <dd><p>A list of mutators which are disallowed when playing under this game profile.</p><%excludedmuts%></dd>
  
  </dl>
  <input type="hidden" name="mutatorcount" value="<%mutatorcount%>" />
  <input type="hidden" name="excludedmutcount" value="<%excludedmutcount%>" />
  
  <div id="pfactions">
  <br />
  <button type="submit" name="action" value="save">save</button>
  <button type="submit" name="action" value="delete">delete</button>
  <!--<button type="submit" name="action" value="activate">activate</button>-->
  </div>
</fieldset>
</form>

<script type="text/javascript">
//<![CDATA[

$(document).ready(function() {
  $('#pfactions button[value="delete"]').click(function () {
    return window.confirm("Are you sure you want to delete this profile?");
  });
  
  var btn = $('<span class="inlineEdit" title="Edit this value"><span>[edit]</span></span>');
  btn.click(function(){
    $('#rofriendlyname').remove();
    $('#friendlyname').show().focus();    
    $(this).remove();
  });
  $('#friendlyname').hide().before('<span id="rofriendlyname">'+$('#friendlyname').val()+'</span> ').after(btn);
  
  $('.mutatorGroup input:radio, .mutatorGroup input:checkbox').click(function(){
    changeHistory = new Array();
    updateSelection(this, this.checked);
  });
  $('.extmutator input:checkbox').click(function(){
    updateExtSelection(this, this.checked);
  });
  $('.extmutator input:checkbox').each(function() {
    updateExtSelection(this, this.checked)
  });
  
  $('#gameclass').change(function() {
        requestData = {ajax: 1, gametype: $('#gameclass').val()};
        requestData.mutatorcount = $('input[name="mutatorcount"]').val();
        $('input[name^="mutgroup"]:checked').each(function() {
            requestData[this.name] = this.value;
        });
        $.ajax({
            type: "POST",
            url: '<%page.fulluri%>/data',
            data: requestData,
            success: mutatorListUpdate,
            error: ajaxError
        });
    });
});

var changeHistory;
function updateSelection(elm, isChecked) {
    if (jQuery.inArray(elm, changeHistory) != -1) return;
    changeHistory[changeHistory.length] = elm;
    // check elements with the same value
    if (elm.value != "") {
        jQuery.each($('.mutatorGroup input[value="'+elm.value+'"]'), function(idx,obj) {
            obj.checked = isChecked;
            updateSelection(obj, isChecked);
        });
    }
    // uncheck elements in this group
    if (isChecked) {
        jQuery.each($('.mutatorGroup input[name="'+elm.name+'"]'), function(idx,obj) {
            if (obj == elm) return;
            if (obj.value == "") return;
            updateSelection(obj, false);
        });
    }
    // select 'none' if none selected
    if ($('.mutatorGroup input[name="'+elm.name+'"]:checked').length == 0 && $('input[name="'+elm.name+'"]').length > 1) {
        $('.mutatorGroup input[name="'+elm.name+'"]:first').attr("checked", "checked");
    }
}

function updateExtSelection(elm, isChecked) {
  changeHistory = new Array();
  // check elements with the same value
  if (elm.value != "") {
    jQuery.each($('.mutatorGroup input[value="'+elm.value+'"]'), function(idx,obj) {
      obj.disabled = isChecked;
      if (isChecked) {
        obj.checked = false;
        updateSelection(obj, false);
      }
    });
  }
}

function ajaxError(XMLHttpRequest, textStatus, errorThrown) {
  if (XMLHttpRequest.status == 403) {
    document.location = '<%page.fulluri%>';
  }
}

function handleMessages(jdata, textStatus) {
    var old = $('#messages .oldMessage');
    var newmsg = $(jdata.find('request messages').text());
    newmsg.hide();
    $('#messages').prepend(newmsg);
    newmsg.fadeIn();
    old.remove();
    $('#messages *').addClass('oldMessage');
}

function mutatorListUpdate(data, textStatus) {
    if (data.length == 0) {
        alert("Network error during updating.");
    }
    var jdata = $('<div>'+data+'</div>');
    $('#mutatorField fieldset').remove();
    x = jdata.children('#mutators');
    $('#mutatorField').append(x.contents().clone()).hide().fadeIn('normale');
        
    x = jdata.children('#mutatorcount');
    $('input[name="mutatorcount"]').val(x.val());
        
    $('.mutatorGroup input:radio, .mutatorGroup input:checkbox').click(function(){
        changeHistory = new Array();
        updateSelection(this, this.checked);
    });
    $('.extmutator input:checkbox').each(function() {
      updateExtSelection(this, this.checked)
    });
}

//]]>
</script>
