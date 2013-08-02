<script type="text/javascript">
//<![CDATA[
$(document).ready(function(){
    $('#webadmininfo').append('<dd id="versioncheck"><button title="Retrieve information about the latest version of the UT3 WebAdmin.">Version check</button></dd>');
    $('#versioncheck button').click(function(){
        $('#versioncheck').remove();
        $(document).append('<script type="text/javascript" src="http://ut3webadmin.elmuerte.com/releases.php?versioncheck=js2"><'+'/script>');     
    });
});

function versionUpdate(versionData) {
    if (!versionData.version) {
        $('#versioncheck').append('<em>Error retrieving version information</em>');
        return;
    }
    var type = "info";
    var reqInfo = "";
    if (versionData.mingamever) {
        reqInfo = "<br />Requires UT3 version "+versionData.mingamever+" (engine version: "+versionData.minengine+")";
    }
    if (versionData.minengine) {
        if (parseInt('<%engine.version%>') < parseInt(versionData.minengine)) {
            reqInfo = reqInfo + "<br />You need to update the game to a new version to use this patch.";
            type = "error";
        }
    }
    if (versionCompare('<%build.version%>', versionData.version) != 0) {
        type = "warn";
    }
    $('#messages').append('<div class="message '+type+'"><b>Latest version:</b> '
        + '<em>v'+versionData.version+' &#8211; '+versionData.date+'</em> '
        +reqInfo
        + '<br /><a rel="external" href="'+versionData.url+'">Download</a></div>');
}

/**
 * Compare versions. Returns 0 when the versions are equal
 */ 
function versionCompare(v1, v2) {
    var p1 = v1.split(".");
    var p2 = v2.split(".");
    for (var i = 0; i < p1.length; i++)
    {
        if (p2.length <= i) return 1;
        var diff = parseInt(p1[i]) - parseInt(p2[i]);
        if (diff != 0) return diff;
    }
    return 0;
}

//]]>
</script>
