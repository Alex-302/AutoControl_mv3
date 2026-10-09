# zone_chain.ps1 - print the MSAA ancestry (role/name/rect) for given points.
# Debugging aid for the zone rules (title-area band, tab buttons, ...).
#
# Usage: powershell -ExecutionPolicy Bypass -File Test\zone_chain.ps1 -Points "band,1200,60;tab,1200,200;toolbar,1200,230"
param([string]$Points = "band,1200,60;tab,1200,200;toolbar,1200,230", [int]$Depth = 6, [int]$Settle = 150)
Add-Type -ReferencedAssemblies Accessibility @"
using System;
using System.Text;
using System.Collections.Generic;
using System.Runtime.InteropServices;
using Accessibility;

public class ZoneChain {
  [DllImport("user32.dll")] public static extern bool SetProcessDPIAware();
  [DllImport("user32.dll")] public static extern bool SetCursorPos(int x, int y);
  [DllImport("user32.dll")] public static extern bool GetCursorPos(out POINT p);
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
  static string RN(IAccessible a) {
    string role = "?", name = "";
    try { role = ((int)a.get_accRole(0)).ToString(); } catch { }
    try { name = (string)a.get_accName(0); } catch { }
    if (name == null) name = "";
    if (name.Length > 40) name = name.Substring(0, 40);
    return "role=" + role + " '" + name.Replace("\n", " / ") + "'";
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
      parts.Add("  d" + d + " " + RN(cur) + " " + RC(cur));
      try { cur = (IAccessible)cur.accParent; } catch { break; }
    }
    try { Marshal.ReleaseComObject(acc); } catch { }
    return string.Join("\n", parts.ToArray());
  }
}
"@
[void][ZoneChain]::SetProcessDPIAware()
foreach ($p in $Points.Split(';')) {
  if (-not $p.Trim()) { continue }
  $a = $p.Split(',')
  if ($a.Count -lt 3) { continue }
  [void][ZoneChain]::SetCursorPos([int]$a[1], [int]$a[2])
  Start-Sleep -Milliseconds $Settle
  $pt = New-Object ZoneChain+POINT
  [void][ZoneChain]::GetCursorPos([ref]$pt)
  Write-Output ("=== {0} ({1},{2}) cursor=({3},{4})" -f $a[0], $a[1], $a[2], $pt.x, $pt.y)
  Write-Output ([ZoneChain]::Chain($pt, $Depth))
}
