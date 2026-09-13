# zone_find_buttons.ps1 - locate the tab strip BUTTONS (close / speaker) live.
#
# The tab layout changes with every tab open/close, so hard-coded coordinates
# go stale. This sweeps the strip row and prints, for every x, the element
# under it when it is a PUSHBUTTON (role 43) or has a button-ish name -
# i.e. the close / mute-tab buttons inside the tabs.
#
# Usage: powershell -ExecutionPolicy Bypass -File Test\zone_find_buttons.ps1
#        ... -Y 31
param([int]$Y = 31, [int]$Step = 4, [int]$FromX = 100, [int]$ToX = 2090)

Add-Type -ReferencedAssemblies Accessibility @"
using System;
using System.Text;
using System.Collections.Generic;
using System.Runtime.InteropServices;
using Accessibility;

public class ZFB {
  [DllImport("user32.dll")] public static extern bool SetProcessDPIAware();
  [DllImport("oleacc.dll")] public static extern int AccessibleObjectFromPoint(POINT pt, out IAccessible acc, out object child);
  [StructLayout(LayoutKind.Sequential)] public struct POINT { public int x, y; }

  static IAccessible Aop(POINT pt) {
    IAccessible acc = null; object c = null;
    int hr = AccessibleObjectFromPoint(pt, out acc, out c);
    if (hr != 0 || acc == null) return null;
    try { object n = acc.get_accName(0); } catch { }
    try { Marshal.ReleaseComObject(acc); } catch { }
    acc = null;
    hr = AccessibleObjectFromPoint(pt, out acc, out c);
    if (hr != 0 || acc == null) return null;
    return acc;
  }

  // "role|name" at depth 0, plus the parent's role
  public static string Probe(POINT pt) {
    IAccessible acc = Aop(pt);
    if (acc == null) return "(aop-fail)";
    string r0 = "?", n0 = "";
    try { r0 = ((int)acc.get_accRole(0)).ToString(); } catch { }
    try { n0 = (string)acc.get_accName(0); } catch { }
    if (n0 == null) n0 = "";
    string r1 = "?";
    IAccessible p = null;
    try { p = (IAccessible)acc.accParent; } catch { }
    if (p != null) { try { r1 = ((int)p.get_accRole(0)).ToString(); } catch { } }
    try { Marshal.ReleaseComObject(acc); } catch { }
    return r0 + "|" + r1 + "|" + n0;
  }
}
"@
[ZFB]::SetProcessDPIAware() | Out-Null

$prev = ''
$startX = $FromX
$segments = @()
for ($x = $FromX; $x -le $ToX; $x += $Step) {
  $pt = New-Object ZFB+POINT; $pt.x = $x; $pt.y = $Y
  $d = [ZFB]::Probe($pt)
  if ($d -ne $prev) {
    if ($prev -ne '') { $segments += [pscustomobject]@{ From = $startX; To = ($x - $Step); Desc = $prev } }
    $prev = $d; $startX = $x
  }
}
$segments += [pscustomobject]@{ From = $startX; To = $ToX; Desc = $prev }

Write-Host "y=$Y sweep $FromX..$ToX step $Step"
foreach ($s in $segments) {
  $isBtn = $s.Desc -match '^43\|'
  $mark = if ($isBtn) { '  <== BUTTON' } else { '' }
  Write-Host ("  x={0,5}..{1,5}  {2}{3}" -f $s.From, $s.To, $s.Desc, $mark)
}
