<form method="post" action="<%page.fulluri%>">
<fieldset>
<legend>Settings for <em><%editmutator.name%></em></legend>
<input type="hidden" name="mutator" value="<%editmutator.class%>" />
<p><%editmutator.description%></p>
<dl>
<%settings%>
</dl>
<button type="submit" name="action" value="save" id="btnsave">save settings</button>
</fieldset>
</form>
