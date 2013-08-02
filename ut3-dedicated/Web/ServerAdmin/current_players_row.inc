<tr class="<%evenodd%>">
  <td style="background: <%player.teamcolor%>; color: <%player.teamcolor%>;"><%player.teamid%>&#160;</td>
  <td><%player.name%></td>
  <td class="right"><%player.ping%></td>
  <td><%player.ip%></td>
  <td><%player.uniqueid%></td>
  <td><%player.hashresponse%></td>  
  <td class="center"><%player.admin%></td>
  <td class="center"><%player.spectator%></td>
  
  <td>
    <form method="post" action="<%page.fulluri%>">
      <div>
        <input type="hidden" name="playerid" value="<%player.playerid%>" />
        <input type="hidden" name="playerkey" value="<%player.playerkey%>" />
        <select name="action">
          <option value=""></option>
          <option value="kick">Kick</option>
          <option value="sessionban">Session Ban</option>
          <option value="banip">Ban IP</option>
          <option value="banid">Ban Unique ID</option>
          <option value="banhash">Ban Hash</option>
          <option value="mutevoice">Voice Mute</option>
          <option value="unmutevoice">Voice Unmute</option>
          <option value="toggletext"><%player.mutetext%></option>
        </select>
        <button type="submit">go</button>
      </div>
    </form>
  </td>
</tr>
