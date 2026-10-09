# msaa_chain.ps1 - dump the FULL MSAA chain under a screen point.
#
# The "why did the zone not match?" diagnostic: for one point it prints
#   * the Win32 window class under the cursor;
#   * every ANCESTOR of the accessibility element (role / name / rect /
#     child count), walking UP to the root;
#   * the CHILDREN of the element under the cursor (one level, role / name /
#     rect) - e.g. the close/speaker buttons inside a tab.
#
# This is what tells you WHY a zone rule missed in a browser fork: the helper
# expects role 22 (TOOLBAR) / 42 (EDIT) / 37 (PAGETAB) / 60 (PAGETABLIST) at a
# given point, and this dump shows what is actually there. Used 2026-09-13 to
# explain "the cursor was over VS Code, not the browser" (VS Code is also a
# Chrome_WidgetWin_1 window); used for the Opera/Vivaldi zone-porting scan.
#
# It does NOT move the cursor: AccessibleObjectFromPoint hits any point, and
# the a11y tree is woken exactly like ac_zone_helper.exe does (AOP ->
# accName -> re-AOP, Chrome 148+ anti-abuse crbug 416429182).
#
# Usage:
#   powershell -ExecutionPolicy Bypass -File Test\msaa_chain.ps1
#   powershell -ExecutionPolicy Bypass -File Test\msaa_chain.ps1 -Point "300,31"
#   powershell -ExecutionPolicy Bypass -File Test\msaa_chain.ps1 -Point "300,31" -Depth 6 -Kids 1
#   powershell -ExecutionPolicy Bypass -File Test\msaa_chain.ps1 -Points "tab,300,31;page,300,500;menu,1800,88"
#
# Output also goes to %TEMP%\ac_msaa_chain.txt (append per call).
param(
  [string]$Point = "",
  [string]$Points = "",
  [int]$Depth = 6,
  [int]$Kids = 1,
  [switch]$TabKids,
  [switch]$ExpectBrowser   # warn when the window under the point is not a browser
)
Add-Type -ReferencedAssemblies Accessibility @"
using System;
using System.Text;
using System.Collections.Generic;
using System.Runtime.InteropServices;
using Accessibility;

public class Msaac {
  [DllImport("user32.dll")] public static extern IntPtr WindowFromPoint(POINT pt);
  [DllImport("user32.dll")] public static extern int GetClassName(IntPtr h, StringBuilder sb, int max);
  [DllImport("user32.dll")] public static extern bool GetWindowRect(IntPtr h, out RECT r);
  [DllImport("user32.dll")] public static extern int GetWindowText(IntPtr h, StringBuilder sb, int max);
  [DllImport("oleacc.dll")] public static extern int AccessibleObjectFromPoint(POINT pt, out IAccessible acc, out object child);
  [StructLayout(LayoutKind.Sequential)] public struct POINT { public int x; public int y; }
  [StructLayout(LayoutKind.Sequential)] public struct RECT { public int l, t, r, b; }

  public static string Cls(IntPtr h) {
    if (h == IntPtr.Zero) return "(null)";
    var sb = new StringBuilder(256); GetClassName(h, sb, 256); return sb.ToString();
  }

  static IAccessible Aop(POINT pt) {
    IAccessible acc = null; object c = null;
    int hr = AccessibleObjectFromPoint(pt, out acc, out c);
    if (hr != 0 || acc == null) return null;
    try { object n = acc.get_accName(0); } catch { }   // wake the tree
    try { Marshal.ReleaseComObject(acc); } catch { }
    hr = AccessibleObjectFromPoint(pt, out acc, out c);
    if (hr != 0 || acc == null) return null;
    return acc;
  }

  public static string Rect(IAccessible a) {
    try {
      int x, y, w, h;
      a.accLocation(out x, out y, out w, out h, 0);
      return String.Format("[{0},{1} {2}x{3}]", x, y, w, h);
    } catch { return "[?]"; }
  }

  public static string Desc(IAccessible a, out int cc) {
    cc = -1;
    if (a == null) return "?";
    string role = "?", name = "";
    try { role = ((int)a.get_accRole(0)).ToString(); } catch { }
    try { name = (string)a.get_accName(0); } catch { }
    try { cc = a.accChildCount; } catch { }
    if (name == null) name = "";
    if (name.Length > 40) name = name.Substring(0, 40) + "\u2026";
    return "role=" + role + " '" + name + "' " + Rect(a) + " cc=" + cc;
  }

  // ancestry: element under the point -> parents, up to maxDepth
  public static string Chain(POINT pt, int maxDepth) {
    IAccessible acc = Aop(pt);
    if (acc == null) return "(aop-fail)";
    var parts = new List<string>();
    IAccessible cur = acc;
    for (int d = 0; d < maxDepth && cur != null; d++) {
      int cc;
      parts.Add("d" + d + " " + Desc(cur, out cc));
      IAccessible nxt = null;
      try { nxt = (IAccessible)cur.accParent; } catch { }
      if (nxt != null && nxt != cur) {
        try { Marshal.ReleaseComObject(cur); } catch { }
        cur = nxt;
      } else break;
    }
    if (cur != null) try { Marshal.ReleaseComObject(cur); } catch { }
    string cls = Cls(WindowFromPoint(pt));
    return "[" + cls + "]\n" + string.Join("\n", parts.ToArray());
  }

  // children of the element under the point (one level), with their rects.
  // When the point is inside a TAB, the useful children are those of the
  // PAGETAB (role 37): the close button and the SOUND (speaker) icon live
  // there. -TabKids 1 (default) walks up to the first role 37 and dumps ITS
  // children instead of d0's - that is how the "speaker at playing sound"
  // zone-17 check is done.
  public static string Kids(POINT pt, int max, bool tabKids) {
    IAccessible acc = Aop(pt);
    if (acc == null) return "(aop-fail)";
    IAccessible target = acc;
    string label = "children of d0 (cc=";
    if (tabKids) {
      IAccessible cur = acc;
      for (int d = 0; d < 6 && cur != null; d++) {
        string r = ""; try { r = ((int)cur.get_accRole(0)).ToString(); } catch { }
        if (r == "37") { target = cur; label = "children of the TAB (role 37, cc="; break; }
        IAccessible nxt = null;
        try { nxt = (IAccessible)cur.accParent; } catch { }
        if (nxt != null && nxt != cur) { cur = nxt; } else break;
      }
    }
    var parts = new List<string>();
    int n = 0; try { n = target.accChildCount; } catch { }
    parts.Add(label + n + "):");
    for (int i = 1; i <= Math.Min(n, max); i++) {
      object ch = null;
      try { ch = target.get_accChild(i); } catch { }
      if (ch == null) { parts.Add("  child" + i + ": (null)"); continue; }
      IAccessible ca = ch as IAccessible;
      if (ca == null) { parts.Add("  child" + i + ": (non-IAccessible)"); continue; }
      int cc;
      parts.Add("  child" + i + ": " + Desc(ca, out cc));
      try { Marshal.ReleaseComObject(ca); } catch { }
    }
    try { Marshal.ReleaseComObject(acc); } catch { }
    return string.Join("\n", parts.ToArray());
  }
}
"@

$log = Join-Path $env:TEMP 'ac_msaa_chain.txt'

# parse points: "name,x,y;name,x,y;..." or single "x,y"
# NOTE: no helper function here - `return $list` from a function ENUMERATES the
# list on the way out (classic PS gotcha), flattening the point-tuples. Parsing
# inline keeps $pts a proper array-of-arrays that foreach walks as-is.
$pts = @()
if ($Points) {
  foreach ($p in ($Points -split ';')) {
    $f = $p.Trim() -split ','
    if ($f.Count -ge 3) { $pts += ,@($f[0].Trim(), [int]$f[1], [int]$f[2]) }
  }
} elseif ($Point) {
  $f = $Point.Trim() -split ','
  if ($f.Count -ge 2) { $pts += ,@('p1', [int]$f[0], [int]$f[1]) }
}
if ($pts.Count -eq 0) { $pts += ,@('p1', 300, 31) }   # default: tab-strip-ish

foreach ($p in $pts) {
  $name = $p[0]; $x = $p[1]; $y = $p[2]
  $pt = New-Object Msaac+POINT; $pt.x = $x; $pt.y = $y
  Write-Output ""
  Write-Output "================ $name  ($x,$y) ================"
  if ($ExpectBrowser) {
    # warn when the point is NOT over a browser (a dev-UI window or another
    # monitor can swallow the point silently - VS Code is also Chrome_WidgetWin_1)
    $w = [Msaac]::WindowFromPoint($pt)
    $cls = [Msaac]::Cls($w)
    $isBrowser = $cls -match 'Chrome_WidgetWin_'
    if (-not $isBrowser) { Write-Output "  !! point is over '$cls', not a browser window - results are about the WRONG window" }
  }
  Write-Output ("chain:")
  $c = [Msaac]::Chain($pt, $Depth)
  Write-Output $c
  if ($Kids -gt 0) {
    Write-Output ("kids:")
    $k = [Msaac]::Kids($pt, $Kids, $TabKids)
    Write-Output $k
  }
  $block = "================ $name  ($x,$y) ================" + "`nchain:`n" + $c
  if ($Kids -gt 0) { $block += "`nkids:`n" + $k }
  $block | Add-Content $log
}
Write-Output ""
Write-Output "DONE - full dump: $log"
