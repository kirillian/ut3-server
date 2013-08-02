<input type="text" id="<%setting.formname%>" name="<%setting.formname%>" value="<%setting.value%>" />
<script type="text/javascript">
//<![CDATA[
$(document).ready(function(){
  var elm = $('#<%setting.formname%>');
  elm.numeric("");
  elm.SpinButton({min: <%setting.minval%>, max: <%setting.maxval%>, step: <%setting.increment%>, page: <%setting.increment%>*10, asint: <%setting.asint%>});
});
//]]>
</script>
