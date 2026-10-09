# zone_scan5.ps1 - two things needed for the 2026-09-12 fixes:
#   A. the window's CHILD HWNDs (looking for the renderer window => the exact
#      "page top" = the bottom edge of the title/toolbar band, zone 4);
#   B. every PAGETAB of the tab strip with its child buttons (roles/rects) =>
#      locate the audible tab's SPEAKER icon (zone 17) precisely.
#
# Usage: powershell -ExecutionPolicy Bypass -File Test\zone_scan5.ps1
param([string]$Point = "300,195", [int]$Up = 2)
Add-Type -ReferencedAssemblies Accessibility @"
using System;
using System.Text;
using System.Collections.Generic;
using System.Runtime.InteropServices;
using Accessibility;

public class ZoneScan5 {
  [DllImport("user32.dll")] public static extern bool SetProcessDPIAware();
  [DllImport("user32.dll")] public static extern bool GetWindowRect(IntPtr h, out RECT r);
  [DllImport("user32.dll")] public static extern IntPtr GetAncestor(IntPtr h, uint f);
  [DllImport("user32.dll")] public static extern IntPtr WindowFromPoint(POINT pt);
  [DllImport("user32.dll", CharSet = CharSet.Unicode)] public static extern int GetClassName(IntPtr h, StringBuilder s, int n);
  [DllImport("oleacc.dll")] public static extern int AccessibleObjectFromPoint(POINT pt, out IAccessible acc, out object child);
  [StructLayout(LayoutKind.Sequential)] public struct POINT { public int x; public int y; }
  [StructLayout(LayoutKind.Sequential)] public struct RECT { public int l, t, r, b; }

  public delegate bool EnumProc(IntPtr h, IntPtr p);
  [DllImport("user32.dll")] public static extern bool EnumChildWindows(IntPtr parent, EnumProc cb, IntPtr p);

  public static string KidsHwnd(IntPtr parent) {
    var sb = new StringBuilder();
    EnumChildWindows(parent, delegate(IntPtr h, IntPtr p) {
      var cn = new StringBuilder(256); GetClassName(h, cn, 256);
      RECT r; GetWindowRect(h, out r);
      sb.AppendLine("  hwnd=0x" + h.ToInt64().ToString("X") + " class=" + cn.ToString() +
                    " [" + r.l + "," + r.t + " " + (r.r - r.l) + "x" + (r.b - r.t) + "]");
      return true;
    }, IntPtr.Zero);
    return sb.ToString();
  }

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
    return "role=" + role + " '" + name.Replace("\n", " / ") + "'";
  }
  static string RC(IAccessible a) {
    int x = 0, y = 0, w = 0, h = 0;
    try { a.accLocation(out x, out y, out w, out h, 0); } catch { return "(no-rect)"; }
    return "[" + x + "," + y + " " + w + "x" + h + "]";
  }
  static IAccessible Child(IAccessible a, int idx) {
    try { return (IAccessible)a.get_accChild(idx); } catch { return null; }
  }

  // walk up `up` levels with the cursor at `pt`, then list the children
  public static string TabStrip(POINT pt, int up) {
    IAccessible acc = Aop(pt);
    if (acc == null) return "(aop-fail)";
    IAccessible cur = acc;
    for (int i = 0; i < up && cur != null; i++) {
      IAccessible p = null; try { p = (IAccessible)cur.accParent; } catch { }
      if (p == null) break;
      cur = p;
    }
    var sb = new StringBuilder();
    sb.AppendLine("node " + RN(cur) + " " + RC(cur));
    int n = 0; try { n = cur.accChildCount; } catch { }
    for (int i = 1; i <= n; i++) {
      IAccessible c = Child(cur, i);
      if (c == null) { sb.AppendLine("  child[" + i + "] = null"); continue; }
      sb.AppendLine("  child[" + i + "] " + RN(c) + " " + RC(c));
      int cn = 0; try { cn = c.accChildCount; } catch { }
      for (int k = 1; k <= cn; k++) {
        IAccessible g = Child(c, k);
        if (g == null) { sb.AppendLine("      g[" + k + "] = null"); continue; }
        sb.AppendLine("      g[" + k + "] " + RN(g) + " " + RC(g));
      }
      try { Marshal.ReleaseComObject(c); } catch { }
    }
    try { Marshal.ReleaseComObject(acc); } catch { }
    return sb.ToString();
  }
}
"@

[void][ZoneScan5]::SetProcessDPIAware()
$pt = New-Object ZoneScan5+POINT
$pa = $Point.Split(',')
$pt.x = [int]$pa[0]; $pt.y = [int]$pa[1]
$hwnd = [ZoneScan5]::WindowFromPoint($pt)
$root = [ZoneScan5]::GetAncestor($hwnd, 2)
$r = New-Object ZoneScan5+RECT
[void][ZoneScan5]::GetWindowRect($root, [ref]$r)
Write-Host "frame hwnd=0x$($root.ToInt64().ToString('X')) rect=[$($r.l),$($r.t) $($r.r - $r.l)x$($r.b - $r.t)]"
Write-Host "--- child HWNDs ---"
Write-Host ([ZoneScan5]::KidsHwnd($root))
Write-Host "--- tab strip (point $Point, up=$Up) ---"
Write-Host ([ZoneScan5]::TabStrip($pt, $Up))
