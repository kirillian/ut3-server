
<form method="post" action="<%page.fulluri%>" id="maplistform">
<fieldset>
  <legend><%friendlyname%></legend>
  <input type="hidden" name="maplistid" value="<%maplistid%>" />

  <div id="mleditorSections">

    <div class="mleditSection" id="modeMaps">
      <h4>Maps</h4>
      
      <textarea rows="15" cols="60" name="mapcycle" id="mapcycle"><%mapcycle%></textarea>
        
      <p id="noscriptHint">
        <em>Note:</em> you get the best map list editing experiance in a JavaScript capable browser. 
        Enter one map per line, you can include URL options like <code>?LinkSetup=...</code>. 
        The data after the map name starting with <code>&#160;extra:</code> is additional information about this map used by the
        map list manager to select the next map. It is safe to remove or alter this.
      </p>

    </div>
    
    <div class="mleditSection" id="modePrefix">
      <h4>Auto-load Prefixes</h4>
      <table width="400">
      <tr>
        <td><textarea name="autoloadprefixes" cols="10" rows="8" title="One line per prefix"><%autoloadprefixes%></textarea></td>
        <td>
          <p>The map list will automatically be filled with maps that have this prefix. Maps will only be added once. New maps are added to the end of the list.</p>
          <p>A map prefix is the file name part before the first hyphen, for example <code>DM-Morbias</code> has the prefix <code>DM</code>.</p>
        </td>
      </tr>
      </table>
    </div>
  
  </div>
  
  <div id="mlactions">
  <dl><%mapreplaylimit%></dl>
  <br />
  <button type="submit" name="action" value="save">save</button>
  <button type="submit" name="action" value="delete">delete</button>
  </div>

</fieldset>
</form>

<script type="text/javascript">
//<![CDATA[

// prevents flicker
$('#mapcycle').hide();

$(document).ready(function() {
    var tabs = $('<ul id="tabs"></ul>');
    var tabidx = 0;
    var idx = -1;
    $('#mleditorSections').prepend(tabs);
    $('#mleditorSections div.mleditSection').each(function() {
        var title = $('h4', this);
        ++idx;
        tabs.append('<li><a href="#'+this.id+'"><span>'+title.text()+'</span></a></li>');
        if ('#'+this.id == location.hash) {
          tabidx = idx;
        }
        title.remove();
    });
    tabs.tabs({ selected: tabidx });    
    
    $('#mlactions button[value="delete"]').click(function () {
      return window.confirm("Are you sure you want to delete this map list?");
    });
    
    fancyMlEditor();
});

function fancyMlEditor() {
    $('#mapcycle').hide();
    $('#noscriptHint').hide();    
    $('#mapcycle').after('<table class="noborder" id="fancyeditor"><tr><th>Available Maps</th><th>Map Cycle</th></tr><tbody id="jsmaplist"><tr><td><select id="gametypeselect"><option>(select game type)</option></select><br /><ul id="jsallmaps"></ul></td><td><ol id="jsmapcycle"></ol></td><td id="jsmlctrls"></td></tr></tbody></table>');
    $('#noscriptHint').after('<p id="jsmaplistHint"><em>Note:</em> drag items from the left list to the right list to add a map to the cycle. '+
      'To move a map to a different position in the cycle, simply drag it to the desired location. Press the "x" button next to the map cycle entry to remove it. '+
      'You can manually add a map to the cycle using the "manual add" button below.</p>');
        
    $('#gametypeselect').change(function() {
      var val = $(this).val();
      if (val == '') return;
      $.ajax({
        type: "POST",
        url: '<%webadmin.path%>/data',
        data: {ajax: 1, type: 'maps', gametype: val},
        success: populateMaps,
        error: ajaxError
      });
    });
    
    $.ajax({
        type: "POST",
        url: '<%webadmin.path%>/data',
        data: {ajax: 1, type: 'gametypes'},
        success: populateGametypes,
        error: ajaxError
    });
    
    _mapcycle = $('#mapcycle').val().split("\n");    
    _jsmapcycle = $('#jsmapcycle');    
    for (i = 0; i < _mapcycle.length; i++)
    {
        str = jQuery.trim(_mapcycle[i]);
        var splt = str.indexOf('extra:');
        var xtra = new Array();
        if (splt > -1) {
          xtra = str.substring(splt+6, str.length).split('?');
          str = str.substring(0, splt);
        }
        if (str.length > 0)
        {
            var item = jQuery('<li><span class="entry">'+str+'</span></li>');
            createDataObject(xtra, item);
            _jsmapcycle.append(item);
            addModButtons($(item));
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
    $('#jsmapcycle').parent().droppable({
        accept: "li.mapEntry",
        hoverClass: "dropHover",
        activeClass: "droppable",
        drop: function(ev, ui) {
            var item = $(ui.draggable).clone();
            item.removeClass('mapEntry');            
            addModButtons(item);
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
       $('#fancyeditor').remove();
       $('#jsmaplistHint').remove();
       $('#mapcycle').show();
       $('#noscriptHint').show();
    });
    var manualAddBtn = jQuery('<button type="button" id="manualAddBtn" title="add a map by entering the name">manual add</button>');
    manualAddBtn = $(manualAddBtn);
    manualAddBtn.click(function(){
        var res = jQuery.trim(prompt("Enter the map name (without extension) to be added to the map cycle. \nHint: you can include URL options like ?LinkSetup=...", ""));
        if (res != "") {
            item = jQuery('<li><span class="entry">'+res+'</span></li>');
            addModButtons($(item));
            _jsmapcycle.append(item);
            _jsmapcycle.sortable("refresh");
            _jsmapcycle.sortable("refreshPositions");
        }      
    });
    
    var addMissingMapsBtn = jQuery('<button type="button" id="addMissingMaps" title="add all maps that are not in the list">add missing</button>');
    addMissingMapsBtn = $(addMissingMapsBtn);
    addMissingMapsBtn.click(addMissingMaps);
    
    var resetCntBtn = jQuery('<button type="button" id="resetCntBtn" title="reset the play counters for all maps">reset counters</button>');
    resetCntBtn = $(resetCntBtn);
    resetCntBtn.click(function(){
      for (var i = 0; i < extraData.length; i++) {
        for (var j = extraData[i].data.length-1; j >= 0; j--) {
          if (extraData[i].data[j].key == 'LastPlayIdx' || extraData[i].data[j].key == 'PlayCount') {
            extraData[i].data[j].key = '';
            extraData[i].data[j].value = '';
          }
        }         	
      }
    });
    
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
    $('#jsmlctrls').append(manualAddBtn).append("<br />").append(addMissingMapsBtn).append("<br />").append(clearMapListBtn).append("<br />").append(resetCntBtn).append("<br />").append("<br />").append(simpleEditBtn);
    
    $('#maplistform').submit(function () {
        updateTextMapList();
        return true;
    });
}

var extraData = new Array();

function createDataObject(data, foritem) {
  var adata = new Array();
  for (var i = 0; i < data.length; i++) {
    var itm = jQuery.trim(data[i]);
    if (itm.length == 0) continue;
    var idx = data[i].indexOf('=');
    if (idx == -1) {
      idx = data[i].length;
    }
    var item = {'key': data[i].substring(0, idx), 'value': data[i].substring(idx+1, data[i].length)};
    adata[adata.length] = item;
  }
  if (adata.length == 0) return;
  var idx = extraData.length;
  extraData[idx] = {entry: foritem, data: adata};
  foritem.attr('extraMapData', idx);
}

function getExtraData(foritem) {
  var data = foritem.attr('extraMapData');
  if (data == undefined || data == "") return new Array();
  var idx = parseInt(data);
  return extraData[idx].data;
}

function addModButtons(forItem) {
    var res = jQuery('<span class="deleteButton" title="delete this map"></span>');
    res = $(res);
    res.click(deleteEntry);
    forItem.prepend(res);
    
    res = jQuery('<span class="editButton" title="edit additional information"></span>');
    res = $(res);
    res.click(function(){editEntry(forItem);});
    //forItem.prepend(res);
    
    forItem.hover(function() {
        $(this).addClass('sorting');
    }, function() {
        $(this).removeClass('sorting');
    });
}

function deleteEntry() {
    $(this).parent().remove();
}

function editEntry(item) {
  alert('not implemented'); 
}

function updateTextMapList() {
    // check manual mode  
    if ($('#jsmapcycle').size() == 0)
    {
        return;      
    }
    var maplist = $('#jsmapcycle li');
    var txtlist = "";
    for (var i = 0; i < maplist.size(); i++) {
        txtlist += jQuery.trim($('.entry', maplist.get(i)).text());
        var extra = getExtraData(jQuery(maplist.get(i)));
        if (extra.length > 0) {
          txtlist += '    extra:';
          for (var j = 0; j < extra.length; j++) {
            if (extra[j].key == '') continue;
            if (j > 0) txtlist += '?';
            txtlist += extra[j].key;
            txtlist += '=';
            txtlist += extra[j].value;
          }
        }
        txtlist += '\n';
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
            addModButtons($(item));
            _jsmapcycle.append(item);
        }
    }
    _jsmapcycle.sortable("refresh");
    _jsmapcycle.sortable("refreshPositions");
}

function ajaxError(XMLHttpRequest, textStatus, errorThrown) {
    if (XMLHttpRequest.status == 403) {
        document.location = '<%page.fulluri%>';
    }
}

function populateGametypes(data, textStatus) {
  if (data.length == 0) {
    alert("Network error during updating.");
  }
  var jdata = $(data);
  handleMessages(jdata, textStatus);
  
  var gtselect = $('#gametypeselect');
  $('option', gtselect).remove();
  gtselect.append('<option value="">(select game type)</option>');
  jdata.find('request gametypes gametype').each( function() {
    gtselect.append('<option value="'+$('class', this).text()+'">'+$('friendlyname', this).text()+'</option>'); 
  });
}

function populateMaps(data, textStatus) {
  if (data.length == 0) {
    alert("Network error during updating.");
  }
  var jdata = $(data);
  handleMessages(jdata, textStatus);
  
  var jsallmaps = $('#jsallmaps');
  $('li', jsallmaps).remove();
  
  jdata.find('request maps map').each( function() {
    str = jQuery.trim($('name', this).text());
    if (str.length > 0)
    {
      jsallmaps.append('<li class="mapEntry"><span class="entry">'+str+'</span></li>');
    }
  });
  
  $('li', jsallmaps).draggable({
    helper: 'clone',
    zIndex: 100,
    start: function(ev, ui) {
      $(ui.helper).addClass('dragging');
    },
    stop: function(ev, ui) {
      $(ui.helper).removeClass('dragging');
    }
  });
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

//]]>
</script>
