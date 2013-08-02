<%mutlisetting.predef%>
<span id="<%setting.formname%>_rawsec" class="settingsraw"><%mutlisetting.raw%></span>
<script type="text/javascript">
//<![CDATA[
$(document).ready(function() {
  $('#<%setting.formname%>_rawsec').before(' <button id=\"<%setting.formname%>_btn\" type=\"button\" title=\"Enter a custom value instead of the preselected values.\">custom value</button> ');
  $('#<%setting.formname%>_btn').click(function(){
    $(this).remove();
    elm = $('#<%setting.formname%>');
    rawelm = $('#<%setting.formname%>_raw');
    rawelm.val(elm.val());
    rawelm.attr('id', elm.attr('id'));
    rawelm.attr('name', elm.attr('name'));
    elm.remove();
    $('#<%setting.formname%>_rawsec').show();
  });
});
//]]>
</script>
