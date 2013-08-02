<input type="text" id="<%setting.formname%>" name="<%setting.formname%>" value="<%setting.value%>" title="Minimum: <%setting.minval%>; Maximum: <%setting.maxval%>" />
<script type="text/javascript">
//<![CDATA[
$(document).ready(function(){
  var elm = $('#<%setting.formname%>');
  if (<%setting.asint%>) elm.numeric("\n");
  else elm.numeric();
  elm.SpinButton({min: <%setting.minval%>, max: <%setting.maxval%>, step: <%setting.increment%>, page: <%setting.increment%>*10, asint: <%setting.asint%>});
});
//]]>
</script>
