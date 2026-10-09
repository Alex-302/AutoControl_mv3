# zone_scan2.ps1 - element map with RECTS (MSAA accLocation).
#
# zone_scan.ps1 gave roles/names per position. This script enumerates the
# CHILDREN of the interesting containers (tab list, toolbar, omnibox group)
# with their screen rectangles - that is what the zone rules need:
#   - the new-tab ("+") button and its rect (zone 16),
#   - the toolbar buttons + the right-side ones (menu/kebab 30, avatar, ...),
#   - the omnibox children (bookmark star 33, site info, ...),
#   - tab children (Close 15 / Mute tab 17).
#
# Usage: powershell -ExecutionPolicy Bypass -File Test\zone_scan2.ps1
param([int]$Hwnd = 0)

Add-Type -ReferencedAssemblies Accessibility @"
using System;
using System.Text;
using System.Collections.Generic;
using System.Runtime.InteropServices;
using Accessibility;

public class ZoneMap {
  [DllImport("user32.dll")] public static extern bool GetWindowRect(IntPtr h, out RECT r);
  [DllImport("oleacc.dll")] public static extern int AccessibleObjectFromPoint(POINT pt, out IAccessible acc, out object child);
  [StructLayout(LayoutKind.Sequential)] public struct POINT { public int x; public int y; }
  [StructLayout(LayoutKind.Sequential)] public struct RECT { public int l, t, r, b; }

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

  static string RoleName(IAccessible a) {
    string role = "?", name = "";
    try { role = ((int)a.get_accRole(0)).ToString(); } catch { }
    try { name = (string)a.get_accName(0); } catch { }
    if (name == null) name = "";
    if (name.Length > 40) name = name.Substring(0, 40) + "\u2026";
    return "role=" + role + " '" + name + "'";
  }

  static string RectStr(IAccessible a) {
    int x = 0, y = 0, w = 0, h = 0;
    try { a.accLocation(out x, out y, out w, out h, 0); } catch { return "(no-rect)"; }
    return "[" + x + "," + y + " " + w + "x" + h + "]";
  }

  static void Dump(IAccessible a, string indent, int depth, List<string> outp) {
    int n = 0; try { n = a.accChildCount; } catch { }
    outp.Add(indent + RoleName(a) + " " + RectStr(a) + (n > 0 ? " cc=" + n : ""));
    if (depth <= 0) return;
    for (int i = 1; i <= Math.Min(n, 40); i++) {
      object ch = null;
      try { ch = a.get_accChild(i); } catch { }
      IAccessible ca = ch as IAccessible;
      if (ca == null) continue;
      Dump(ca, indent + "  ", depth - 1, outp);
      try { Marshal.ReleaseComObject(ca); } catch { }
    }
  }

  // point -> walk up `up` levels -> dump that element and its subtree
  public static string Sub(POINT pt, int up, int depth) {
    IAccessible acc = Aop(pt);
    if (acc == null) return "(aop-fail)";
    IAccessible cur = acc;
    for (int i = 0; i < up && cur != null; i++) {
      IAccessible p = null;
      try { p = (IAccessible)cur.accParent; } catch { }
      if (p == null) break;
      cur = p;
    }
    var outp = new List<string>();
    Dump(cur, "", depth, outp);
    try { Marshal.ReleaseComObject(acc); } catch { }
    return string.Join("\n", outp.ToArray());
  }

  // find the first ancestor (or self) with the given role, from a point
  public static string FindRole(POINT pt, int role, int depth) {
    IAccessible acc = Aop(pt);
    if (acc == null) return "(aop-fail)";
    IAccessible cur = acc; IAccessible hit = null;
    for (int i = 0; i < 6 && cur != null; i++) {
      string r = ""; try { r = ((int)cur.get_accRole(0)).ToString(); } catch { }
      if (r == role.ToString()) { hit = cur; break; }
      try { cur = (IAccessible)cur.accParent; } catch { break; }
    }
    if (hit == null) { try { Marshal.ReleaseComObject(acc); } catch { } return "(role " + role + " not found)"; }
    var outp = new List<string>();
    Dump(hit, "", depth, outp);
    try { Marshal.ReleaseComObject(acc); } catch { }
    return string.Join("\n", outp.ToArray());
  }
}
"@

if ($Hwnd -eq 0) {
  $cands = Get-Process chrome -ErrorAction SilentlyContinue |
    Where-Object { $_.Path -like '*Chrome SxS*' -and $_.MainWindowHandle -ne 0 }
  $best = $null; $bestArea = 0
  foreach ($c in $cands) {
    $rr = New-Object ZoneMap+RECT
    if (-not [ZoneMap]::GetWindowRect([IntPtr]$c.MainWindowHandle, [ref]$rr)) { continue }
    $area = ($rr.r - $rr.l) * ($rr.b - $rr.t)
    if ($area -gt $bestArea) { $bestArea = $area; $best = $c }
  }
  if (-not $best) { Write-Output "NO SXS WINDOW FOUND"; exit 1 }
  $Hwnd = $best.MainWindowHandle
  Write-Output "Window: $($best.MainWindowTitle) hwnd=$Hwnd"
}
$r = New-Object ZoneMap+RECT
[ZoneMap]::GetWindowRect([IntPtr]$Hwnd, [ref]$r) | Out-Null
$l = $r.l; $t = $r.t; $w = $r.r - $r.l; $h = $r.b - $r.t
Write-Output ("Rect: l={0} t={1} r={2} b={3} w={4} h={5}" -f $l, $t, $r.r, $r.b, $w, $h)

$log = Join-Path $env:TEMP 'ac_zone_map.txt'
"" | Set-Content $log
function Emit($s) { $s | Add-Content $log; Write-Output $s }
function Pt([int]$x, [int]$y) { $p = New-Object ZoneMap+POINT; $p.x = $x; $p.y = $y; return $p }

# 1. TAB LIST (role 60 PAGETABLIST) - tabs + new-tab button, with rects
Emit "=== TAB LIST (role 60) via point ($($l+150),$($t+30)) ==="
Emit ([ZoneMap]::FindRole((Pt ($l + 150) ($t + 30)), 60, 3))

# 1b. same, but found from a point on the pinned tab (separate list?)
Emit ""
Emit "=== TAB LIST variant via point ($($l+90),$($t+30)) ==="
Emit ([ZoneMap]::FindRole((Pt ($l + 90) ($t + 30)), 60, 3))

# 2. TOOLBAR (role 22) - all toolbar buttons with rects
Emit ""
Emit "=== TOOLBAR (role 22) via point ($($l+120),$($t+88)) ==="
Emit ([ZoneMap]::FindRole((Pt ($l + 120) ($t + 88)), 22, 3))

# 3. OMNIBOX GROUP (role 20) - address bar + its right-side buttons (star!)
Emit ""
Emit "=== OMNIBOX GROUP (role 20) via point ($($l+[int]($w*0.5)),$($t+88)) ==="
Emit ([ZoneMap]::FindRole((Pt ($l + [int]($w * 0.5)) ($t + 88)), 20, 3))

# 4. far right of the toolbar row, probe beyond the reported window edge
Emit ""
Emit "=== TOP-RIGHT probes: y=$($t+30) and y=$($t+88), x=$($r.r-6) .. $($r.r+120) step 6 ==="
foreach ($yy in @(($t + 30), ($t + 88))) {
  for ($x = $r.r - 6; $x -le $r.r + 120; $x += 6) {
    $p = Pt $x $yy
    Emit ("  x={0,5} y={1,5}: {2}" -f $x, $yy, [ZoneMap]::Sub($p, 0, 0))
  }
}

Write-Output ""
Write-Output "DONE - full dump: $log"
