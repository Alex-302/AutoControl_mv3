# zone_scan3.ps1 - targeted hit-tests for the remaining zone signatures.
#
# zone_scan2.ps1 proved the element rects are PHYSICAL pixels while
# GetWindowRect is DPI-virtualized (150% -> window reported 1396 wide,
# real ~2094). This script calls SetProcessDPIAware() first so both are
# physical, then hit-tests the exact spots that matter:
#   - the "+" (New Tab) button and its neighbours (tab strip right end),
#   - the window control buttons,
#   - the right side of the toolbar (star, extension icons, profile, kebab),
#   - tab children: Close / Mute tab (zones 15/17),
#   - the toolbar band between the buttons (zone 20),
#   - the very top strip (zone 4 Title area).
#
# Usage: powershell -ExecutionPolicy Bypass -File Test\zone_scan3.ps1
param([int]$Hwnd = 0)

Add-Type -ReferencedAssemblies Accessibility @"
using System;
using System.Text;
using System.Collections.Generic;
using System.Runtime.InteropServices;
using Accessibility;

public class ZoneHit {
  [DllImport("user32.dll")] public static extern bool SetProcessDPIAware();
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

  static string RN(IAccessible a) {
    string role = "?", name = "";
    try { role = ((int)a.get_accRole(0)).ToString(); } catch { }
    try { name = (string)a.get_accName(0); } catch { }
    if (name == null) name = "";
    if (name.Length > 34) name = name.Substring(0, 34) + "\u2026";
    return role + "'" + name + "'";
  }

  // compact chain: d0 role'name' < d1 role'name' < d2 role'name'
  public static string Chain(POINT pt, int depth) {
    IAccessible acc = Aop(pt);
    if (acc == null) return "(aop-fail)";
    var parts = new List<string>();
    IAccessible cur = acc;
    for (int d = 0; d < depth && cur != null; d++) {
      parts.Add(RN(cur));
      try { cur = (IAccessible)cur.accParent; } catch { break; }
    }
    try { Marshal.ReleaseComObject(acc); } catch { }
    return string.Join(" < ", parts.ToArray());
  }
}
"@

[ZoneHit]::SetProcessDPIAware() | Out-Null

if ($Hwnd -eq 0) {
  $cands = Get-Process chrome -ErrorAction SilentlyContinue |
    Where-Object { $_.Path -like '*Chrome SxS*' -and $_.MainWindowHandle -ne 0 }
  $best = $null; $bestArea = 0
  foreach ($c in $cands) {
    $rr = New-Object ZoneHit+RECT
    if (-not [ZoneHit]::GetWindowRect([IntPtr]$c.MainWindowHandle, [ref]$rr)) { continue }
    $area = ($rr.r - $rr.l) * ($rr.b - $rr.t)
    if ($area -gt $bestArea) { $bestArea = $area; $best = $c }
  }
  if (-not $best) { Write-Output "NO SXS WINDOW FOUND"; exit 1 }
  $Hwnd = $best.MainWindowHandle
}
$r = New-Object ZoneHit+RECT
[ZoneHit]::GetWindowRect([IntPtr]$Hwnd, [ref]$r) | Out-Null
$l = $r.l; $t = $r.t; $W = $r.r - $r.l; $H = $r.b - $r.t
Write-Output "Window (physical, after SetProcessDPIAware): l=$l t=$t r=$($r.r) b=$($r.b) w=$W h=$H"

$log = Join-Path $env:TEMP 'ac_zone_hits.txt'
"" | Set-Content $log
function Emit($s) { $s | Add-Content $log; Write-Output $s }
function Hit([int]$x, [int]$y) {
  $p = New-Object ZoneHit+POINT; $p.x = $x; $p.y = $y
  return [ZoneHit]::Chain($p, 3)
}

Emit ""
Emit "=== A. TAB STRIP right end: y=31, x=1700..$($r.r-10) step 6 ==="
for ($x = 1700; $x -le $r.r - 10; $x += 6) { Emit ("  x={0,5}: {1}" -f $x, (Hit $x 31)) }

Emit ""
Emit "=== B. TOP strip (zone 4?): x=200,1500,1820,1900, y=1..14 step 3 ==="
foreach ($x in @(200, 1500, 1820, 1900)) {
  for ($y = 1; $y -le 14; $y += 3) { Emit ("  x={0,5} y={1,3}: {2}" -f $x, $y, (Hit $x $y)) }
}

Emit ""
Emit "=== C. TOOLBAR right side: y=94, x=1540..$($r.r-8) step 6 ==="
for ($x = 1540; $x -le $r.r - 8; $x += 6) { Emit ("  x={0,5}: {1}" -f $x, (Hit $x 94)) }

Emit ""
Emit "=== D. TOOLBAR left band (zone 20): y=94, x=90,270,300 =="
foreach ($x in @(90, 270, 300)) { Emit ("  x={0,5}: {1}" -f $x, (Hit $x 94)) }

Emit ""
Emit "=== E. TAB children: second tab [206..453], y=31 ==="
foreach ($x in @(216, 228, 240, 260, 395, 405, 415, 425, 440)) {
  Emit ("  x={0,5} y=31: {1}" -f $x, (Hit $x 31))
}
Emit ""
Emit "=== E2. pinned tab [137..234], y=31 (has Mute tab + Close children) ==="
foreach ($x in @(145, 155, 165, 175, 185, 195, 205, 215, 225)) {
  Emit ("  x={0,5} y=31: {1}" -f $x, (Hit $x 31))
}

Emit ""
Emit "=== F. TAB SEARCH button / strip left: y=31, x=100..150 step 5 ==="
for ($x = 100; $x -le 150; $x += 5) { Emit ("  x={0,5}: {1}" -f $x, (Hit $x 31)) }

Emit ""
Emit "=== G. PAGE + gadget areas: y=300 (page), y=94 x=1200 (omnibox mid) ==="
Emit ("  page (400,300): {0}" -f (Hit 400 300))
Emit ("  omnibox (1200,94): {0}" -f (Hit 1200 94))

Write-Output ""
Write-Output "DONE - full dump: $log"
