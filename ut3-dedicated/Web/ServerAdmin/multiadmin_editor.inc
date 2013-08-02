<form method="post" action="<%page.fulluri%>" id="profileform">
<fieldset>
  <legend><%adminid%></legend>
  <input type="hidden" name="adminid" value="<%adminid%>" />
   
  <dl>
    <dt title="Show this as the name of the administrator rather than the user name"><label for="displayname">Display name</label></dt>
    <dd><input type="text" name="displayname" id="displayname" value="<%displayname%>" size="40" maxlength="128" /></dd>
    
    <dt><label for="password1">Password</label></dt>
    <dd><input type="password" name="password1" id="password1" value="" size="40" maxlength="128" /></dd>
    
    <dt><label for="password2">Confirm password</label></dt>
    <dd><input type="password" name="password2" id="password2" value="" size="40" maxlength="128" /></dd>
    
    <dt>Access order</dt>
    <dd>
      <input type="radio" name="order" id="DenyAllow" value="DenyAllow" <%order.denyallow%> /> <label for="DenyAllow" title="Deny access unless it is eplicitly allow. Defaults to allow.">Deny, Allow</label>
      <br />
      <input type="radio" name="order" id="AllowDeny" value="AllowDeny" <%order.allowdeny%> /> <label for="AllowDeny" title="Access is denied if it is now allowed. Defaults to deny.">Allow, Deny</label>
    </dd>
  
    <dt><label for="deny">Deny patterns</label></dt>
    <dd><textarea id="deny" name="deny" cols="60" rows="6"><%deny%></textarea></dd>
    
    <dt><label for="allow">Allow patterns</label></dt>
    <dd><textarea id="allow" name="allow" cols="60" rows="6"><%allow%></textarea></dd>
    
    <dd>The allow and deny patterns are the part of the URL in the webadmin after <code><%webadmin.path%></code>. 
    For example, the pattern for this page is: <code><%page.uri%></code>, and the full URL is <code><%page.fulluri%></code>.
    The patterns may contain the wildcard <code>*</code>. The pattern <code>/foo/*/bar</code> would match <code>/foo/quux/bar</code>, but not <code>/foo/bar</code>.</dd>
  
  </dl>
  
  <div id="pfactions">
  <br />
  <button type="submit" name="action" value="save">save</button>
  <button type="submit" name="action" value="delete" <%allowdelete%>>delete</button>
  </div>
  
  <div id="menueditor"><h3>Navigation Preview</h3><%menueditor%></div>
  
</fieldset>
</form>

<script type="text/javascript">
//<![CDATA[

$(document).ready(function() {
  $('#pfactions button[value="delete"]').click(function () {
    return window.confirm("Are you sure you want to delete this administrator?\nThis will log out existing users.");
  });
  $('#pfactions button[value="delete"]:disabled').before('<small>This admin cannot be deleted.</small>').remove();
  $('#pfactions button[value="save"]').click(function () {
    if ($('#password1').val() != $('#password2').val())
    {
      alert("New password and confirmation do not match.");
      return false;
    }
    return true;
  });
  
  var menuedit = $('#menueditor');
  $('#profileform dl').prepend(menuedit.clone()); 
  menuedit.remove();
  
  reloadAccessRules();
  $('#profileform input[name="order"]').change(reloadAccessRules);
  $('#allow, #deny').change(reloadAccessRules);
  $('#menueditor a').click(function(){return false;});
  $('#menueditor').show();
  $('#menueditor a').draggable({
    helper: 'clone',
    zIndex: 100,
    appendTo: '#profileform',
    start: function(ev, ui) {
      $(ui.helper).addClass('dragging');
    },
    stop: function(ev, ui) {
      $(ui.helper).removeClass('dragging');
    }
  });
  $('#allow, #deny').droppable({
    accept: 'a',
    hoverClass: "dropHover",
    activeClass: "droppable",
    drop: function(e, ui) {
      var item = $(ui.draggable);
      var te = $(this);
      te.val(jQuery.trim(te.val()+'\n'+item.attr('href')));
      reloadAccessRules();
    }
  });
});

function toRegExp(str)
{
  str = str.replace(/\*/g, '.*');
  return new RegExp('^'+str+'$');
}

function reloadAccessRules()
{
  var allow = $('#allow').val().split('\n');
  for (var i = 0; i < allow.length; i++)
  {
    allow[i] = jQuery.trim(allow[i]);
    allow[i] = toRegExp(allow[i]);
  }
  var deny = $('#deny').val().split('\n');
  for (var i = 0; i < deny.length; i++)
  {
    deny[i] = jQuery.trim(deny[i]);
    deny[i] = toRegExp(deny[i]);
  }
  var denyallow = $('#profileform input[name="order"]:checked').val() == $('#DenyAllow').val();
  $('#menueditor a').each(function() {
    var path = $(this).attr('href');
    var inallow = false;
    var indeny = false;
    for (var i = 0; i < allow.length; i++)
    {
      if (allow[i].test(path))
      {
        inallow = true;
        break;
      }
    }
    for (var i = 0; i < deny.length; i++)
    {
      if (deny[i].test(path))
      {
        indeny = true;
        break;
      }
    }
    if (denyallow) {
      if (indeny && !inallow) $(this).addClass('denied');
      else $(this).removeClass('denied');
    }
    else {
      if (inallow) $(this).removeClass('denied');
      else $(this).addClass('denied');
    }
  });
}

//]]>
</script>
