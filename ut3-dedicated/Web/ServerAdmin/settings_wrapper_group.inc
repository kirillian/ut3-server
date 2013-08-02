<div id="settingsWrapper">
<%settings%>
</div>
<script type="text/javascript">
//<![CDATA[
$(document).ready(function() {
    var tabs = $('<ul id="settingstabs"></ul>');
    var tabidx = 0;
    var idx = -1;
    $('#settingsWrapper').prepend(tabs);
    $('#settingsWrapper div.SettingsGroup').each(function() {
        var title = $('h4', this);
        ++idx;
        tabs.append('<li><a href="#'+this.id+'"><span>'+title.text()+'</span></a></li>');
        if ('#'+this.id == location.hash) {
          tabidx = idx;
        }
        title.remove();
    });
    tabs.tabs({ selected: tabidx });    
});
//]]>
</script>
