<div id="mleditor">
<table class="noborder">
<thead>
<tr>
    <th>Available Maps</th>
    <th>Map Cycle</th>
</tr>
</thead>

<tbody id="noscript">
<tr>
    <td><textarea rows="15" cols="30" id="allmaps" readonly="readonly"><%allmaps.plain%></textarea></td>
    <td><textarea rows="15" cols="30" name="mapcycle" id="mapcycle"><%cycle.plain%></textarea></td>
</tr>
</tbody>

</table>

<p id="noscriptHint"><em>Note:</em> you get the best map list editing experiance in a JavaScript capable browser. Enter one map per line, you can include URL options like ?LinkSetup=...</p>

</div>

<script type="text/javascript">
//<![CDATA[

// prevents flicker
$('#noscript').hide();

$(document).ready(function() {
    $('#noscript').hide();
    $('#noscriptHint').hide();    
    $('#noscript').after('<tbody id="jsmaplist"><tr><td><ul id="jsallmaps"></ul></td><td><ol id="jsmapcycle"></ol></td><td id="jsmlctrls"></td></tr></tbody>');
    $('#noscriptHint').after('<p id="jsmaplistHint"><em>Note:</em> drag items from the left list to the right list to add a map to the cycle. '+
      'To move a map to a different position in the cycle, simply drag it to the desired location. Press the "x" button next to the map cycle entry to remove it. '+
      'You can manually add a map to the cycle using the "manual add" button below.</p>');
    
    _allmaps = $('#allmaps').val().split("\n");
    _jsallmaps = $('#jsallmaps');
    for (i = 0; i < _allmaps.length; i++)
    {
        str = jQuery.trim(_allmaps[i]);
        if (str.length > 0)
        {
            _jsallmaps.append('<li class="mapEntry"><span class="entry">'+str+'</span></li>');
        }
    }
    
    _mapcycle = $('#mapcycle').val().split("\n");    
    _jsmapcycle = $('#jsmapcycle');    
    for (i = 0; i < _mapcycle.length; i++)
    {
        str = jQuery.trim(_mapcycle[i]);
        if (str.length > 0)
        {
            var item = jQuery('<li><span class="entry">'+str+'</span></li>');
            _jsmapcycle.append(item);
            getDeleteMe($(item));
        }
    }
    _jsmapcycle.sortable({ 
        axis: "y", 
        containment: "parent",
        cancel: ".deleteButton",
        start: function(ev, ui) {
            $(ui.helper).addClass('dragging');
        },
        stop: function(ev, ui) {
            $(ui.helper).removeClass('dragging');
        }
    });
    $('#jsallmaps li').draggable({
        helper: 'clone',
        zIndex: 100,
        start: function(ev, ui) {
            $(ui.helper).addClass('dragging');
        },
        stop: function(ev, ui) {
            $(ui.helper).removeClass('dragging');
        }
    });
    $('#jsmapcycle').parent().droppable({
        accept: "li.mapEntry",
        hoverClass: "dropHover",
        activeClass: "droppable",
        drop: function(ev, ui) {
            var item = $(ui.draggable).clone();
            item.removeClass('mapEntry');            
            getDeleteMe(item);
            _jsmapcycle.append(item);            
            _jsmapcycle.sortable("refresh");
            _jsmapcycle.sortable("refreshPositions");
        }
    });
    
    $('#jsmaplist').show();
    $('#jsmaplistHint').show();
    
    var simpleEditBtn = jQuery('<button type="button" id="simpleEditBtn" title="switch to basic map cycle editing mode">basic edit mode</button>');
    simpleEditBtn = $(simpleEditBtn);
    simpleEditBtn.click(function(){
       $(this).remove();
       $('#manualAddBtn').remove();
       updateTextMapList();
       $('#jsmaplist').remove();
       $('#jsmaplistHint').remove();
       $('#noscript').show();
       $('#noscriptHint').show();
    });
    var manualAddBtn = jQuery('<button type="button" id="manualAddBtn" title="add a map by entering the name">manual add</button>');
    manualAddBtn = $(manualAddBtn);
    manualAddBtn.click(function(){
        var res = jQuery.trim(prompt("Enter the map name (without extension) to be added to the map cycle. \nHint: you can include URL options like ?LinkSetup=...", ""));
        if (res != "") {
            item = jQuery('<li><span class="entry">'+res+'</span></li>');
            getDeleteMe($(item));
            _jsmapcycle.append(item);
            _jsmapcycle.sortable("refresh");
            _jsmapcycle.sortable("refreshPositions");
        }      
    });
    
    var addMissingMapsBtn = jQuery('<button type="button" id="addMissingMaps" title="add all maps that are not in the list">add missing</button>');
    addMissingMapsBtn = $(addMissingMapsBtn);
    addMissingMapsBtn.click(addMissingMaps);
    
    var clearMapListBtn = jQuery('<button type="button" id="clearMapList" title="clear the current map list">clear</button>');
    clearMapListBtn = $(clearMapListBtn);
    clearMapListBtn.click(function () {
        if (confirm('Are you sure you want to clear this map list?')) {
            $('#jsmapcycle li').remove();
            _jsmapcycle.sortable("refresh");
            _jsmapcycle.sortable("refreshPositions");
        }      
    });
    
    $('#mleditor table thead tr').append("<td></td>");
    $('#jsmlctrls').append(manualAddBtn).append("<br />").append(addMissingMapsBtn).append("<br />").append(clearMapListBtn);
    
    $('#mlactions').append(simpleEditBtn).append(" ");
    $('#maplistform').submit(function () {
        updateTextMapList();
        return true;
    });
});

function getDeleteMe(forItem) {
    var res = jQuery('<span class="deleteButton" title="delete this map"></span>');
    res = $(res);
    res.click(deleteme);
    forItem.prepend(res);
    forItem.hover(function() {
        $(this).addClass('sorting');
    }, function() {
        $(this).removeClass('sorting');
    });
}

function deleteme() {
    $(this).parent().remove();
}

function updateTextMapList() {
    // check manual mode  
    if ($('#jsmapcycle').size() == 0)
    {
        return;      
    }
    var maplist = $('#jsmapcycle li');
    var txtlist = "";
    for (i = 0; i < maplist.size(); i++) {
        txtlist += jQuery.trim($('.entry', maplist.get(i)).text())+'\n';
    }
    $('#mapcycle').val(txtlist);
}

function addMissingMaps() {
    var maplist = $('#jsmapcycle li');
    var maps = new Array();
    for (var i = 0; i < maplist.size(); i++) {
        maps[i] = jQuery.trim($('.entry', maplist.get(i)).text());
    }
    maplist = $('#jsallmaps li');
    for (var i = 0; i < maplist.size(); i++) {
        var item = jQuery.trim($('.entry', maplist.get(i)).text());
        if (jQuery.inArray(item, maps) == -1) {
            var item = jQuery('<li><span class="entry">'+item+'</span></li>');
            getDeleteMe($(item));
            _jsmapcycle.append(item);
        }
    }
    _jsmapcycle.sortable("refresh");
    _jsmapcycle.sortable("refreshPositions");
}

//]]>
</script>
