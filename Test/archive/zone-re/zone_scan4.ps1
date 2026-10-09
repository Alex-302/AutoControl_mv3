# zone_scan4.ps1 - hunt for the kebab (menu) button + full toolbar children.
#
# Chrome 150 SxS: the toolbar's right side is currently covered by the
# "New Chrome available" update pill (x 1834..2068), which hides the real
# kebab from hit-testing. This script:
#   1. prints the physical window rect (SetProcessDPIAware),
#   2. dense-probes the far right of the toolbar row,
#   3. enumerates the toolbar's children INDEX BY INDEX, printing null
#      children too (the kebab may be an unexposed child),
#   4. enumerates the window-controls element (min/max/close) for reference.
#
# Usage: powershell -ExecutionPolicy Bypass -File Test\zone_scan4.ps1
param([int]$Hwnd = 0)

Add-Type -ReferencedAssemblies Accessibility @"
using System;
using System.Text;
using System.Collections.Generic;
using System.Runtime.InteropServices;
using Accessibility;

public class ZoneKids {
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
    name = name.Replace("\n", " / ");
    return "role=" + role + " '" + name + "'";
  }
  static string RC(IAccessible a) {
    int x = 0, y = 0, w = 0, h = 0;
    try { a.accLocation(out x, out y, out w, out h, 0); } catch { return "(no-rect)"; }
    return "[" + x + "," + y + " " + w + "x" + h + "]";
  }

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

  // walk up `up` levels from the point, then list ALL children (nulls included)
  public static string Kids(POINT pt, int up) {
    IAccessible acc = Aop(pt);
    if (acc == null) return "(aop-fail)";
    IAccessible cur = acc;
    for (int i = 0; i < up && cur != null; i++) {
      IAccessible p = null; try { p = (IAccessible)cur.accParent; } catch { }
      if (p == null) break;
      cur = p;
    }
    int n = 0; try { n = cur.accChildCount; } catch { }
    var outp = new List<string>();
    outp.Add("node " + RN(cur) + " " + RC(cur) + " cc=" + n);
    for (int i = 1; i <= Math.Min(n, 40); i++) {
      object ch = null; string err = "";
      try { ch = cur.get_accChild(i); } catch (Exception e) { err = " (throw: " + e.GetType().Name + ")"; }
      if (ch == null) { outp.Add("  #" + i + ": (null)" + err); continue; }
      IAccessible ca = ch as IAccessible;
      if (ca == null) { outp.Add("  #" + i + ": (not IAccessible)"); continue; }
      outp.Add("  #" + i + ": " + RN(ca) + " " + RC(ca));
      try { Marshal.ReleaseComObject(ca); } catch { }
    }
    try { Marshal.ReleaseComObject(acc); } catch { }
    return string.Join("\n", outp.ToArray());
  }
}
"@

[ZoneKids]::SetProcessDPIAware() | Out-Null

if ($Hwnd -eq 0) {
  $cands = Get-Process chrome -ErrorAction SilentlyContinue |
    Where-Object { $_.Path -like '*Chrome SxS*' -and $_.MainWindowHandle -ne 0 }
  $best = $null; $bestArea = 0
  foreach ($c in $cands) {
    $rr = New-Object ZoneKids+RECT
    if (-not [ZoneKids]::GetWindowRect([IntPtr]$c.MainWindowHandle, [ref]$rr)) { continue }
    $area = ($rr.r - $rr.l) * ($rr.b - $rr.t)
    if ($area -gt $bestArea) { $bestArea = $area; $best = $c }
  }
  if (-not $best) { Write-Output "NO SXS WINDOW FOUND"; exit 1 }
  $Hwnd = $best.MainWindowHandle
}
$r = New-Object ZoneKids+RECT
[ZoneKids]::GetWindowRect([IntPtr]$Hwnd, [ref]$r) | Out-Null

$log = Join-Path $env:TEMP 'ac_zone_kids.txt'
"" | Set-Content $log
function Emit($s) { $s | Add-Content $log; Write-Output $s }
function Hit([int]$x, [int]$y) {
  $p = New-Object ZoneKids+POINT; $p.x = $x; $p.y = $y
  return [ZoneKids]::Chain($p, 3)
}
function Kids([int]$x, [int]$y, [int]$up) {
  $p = New-Object ZoneKids+POINT; $p.x = $x; $p.y = $y
  return [ZoneKids]::Kids($p, $up)
}

Emit ("WINDOW (physical): l={0} t={1} r={2} b={3} w={4} h={5}" -f $r.l, $r.t, $r.r, $r.b, ($r.r - $r.l), ($r.b - $r.t))

Emit ""
Emit "=== A. TOOLBAR children, full list (from Back button, up 1) ==="
Emit (Kids 130 94 1)

Emit ""
Emit "=== B. window-controls element at (1950,31) + children ==="
Emit (Kids 1950 31 0)

Emit ""
Emit "=== C. dense right-edge probes y=94, x=1990..$($r.r-4) step 4 ==="
for ($x = 1990; $x -le $r.r - 4; $x += 4) { Emit ("  x={0,5}: {1}" -f $x, (Hit $x 94)) }

Emit ""
Emit "=== D. right-edge column x=$($r.r-30), y=60..130 step 5 ==="
for ($y = 60; $y -le 130; $y += 5) { Emit ("  y={0,5}: {1}" -f $y, (Hit ($r.r - 30) $y)) }

Emit ""
Emit "=== E. tab-list right end children (from x=1765, y=31, up 1) ==="
Emit (Kids 1765 31 1)

Write-Output ""
Write-Output "DONE - full dump: $log"
