<tr>
  <td><%ban.playername%></td>
  <td><%ban.hash%></td>
  <td>
    <form method="post" action="<%page.fulluri%>">
    <div>
    <input type="hidden" name="banid" value="<%ban.banid%>" />
    <button type="submit" name="action" value="delete">Delete</button>
    </div>
    </form>
  </td>
</tr>
