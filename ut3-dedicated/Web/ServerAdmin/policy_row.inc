<tr>
  <td><input type="text" name="ipmask" value="<%policy.ipmask%>" class="monospace" /></td>
  <td><select name="policy"><option value="DENY" <%policy.selected.DENY%>>Deny</option><option value="ACCEPT" <%policy.selected.ACCEPT%>>Accept</option></select></td>
  <td>
    <button type="submit" name="update" value="<%policy.id%>">Update</button>
    <button type="submit" name="delete" value="<%policy.id%>">Delete</button>
  </td>
</tr>
