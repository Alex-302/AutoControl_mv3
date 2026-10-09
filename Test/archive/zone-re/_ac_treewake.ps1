# Verify the MSAA tree-sleep hypothesis: first AOP -> PANE (16), after
# get_accName the tree wakes and the roles become real (41/37 over tabs).
Add-Type -ReferencedAssemblies Accessibility @"
using System;
using System.Runtime.InteropServices;
using Accessibility;
public class TreeWake {
  [DllImport("user32.dll")] public static extern bool GetCursorPos(out POINT p);
  [DllImport("oleacc.dll")] public static extern int AccessibleObjectFromPoint(POINT pt, out IAccessible acc, out object child);
  [StructLayout(LayoutKind.Sequential)] public struct POINT { public int X, Y; }
  public static int Role(IAccessible a) { try { return (int)a.get_accRole(0); } catch { return -1; } }
  public static string Name(IAccessible a) { try { return (string)a.get_accName(0); } catch { return ""; } }
}
"@
# Cursor is on the tab strip (user hovered). Read its position.
$c = New-Object TreeWake+POINT
[TreeWake]::GetCursorPos([ref]$c) | Out-Null
Write-Host "cursor at ($($c.X), $($c.Y))"
for ($i = 1; $i -le 3; $i++) {
  $acc = $null; $child = $null
  $hr = [TreeWake]::AccessibleObjectFromPoint($c, [ref]$acc, [ref]$child)
  $role = -1; $name = ""
  if ($acc -ne $null) {
    $role = [TreeWake]::Role($acc)
    $name = [TreeWake]::Name($acc)   # <-- the accName query (tree wake)
  }
  Write-Host "pass $i`: hr=0x$($hr.ToString('X8')) role=$role name='$name'"
  Start-Sleep -Milliseconds 300
}
