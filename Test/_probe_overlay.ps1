# Temporary probe (2026-09-20): identify the element that WINS the a11y
# hit-test at a point over the Opera tab strip after a wheel notch - it is an
# unnamed PANE inside a role-11 window that makes the helper answer [4,1]
# (zone 15 / 12 / 16 triggers get skipped while it is on top).
# Usage: powershell -NoProfile -File Test/_probe_overlay.ps1 <x> <y> [levels]
param([int]$X = 370, [int]$Y = 560, [int]$Levels = 2)
Add-Type -ReferencedAssemblies Accessibility @"
using System;
using System.Text;
using System.Runtime.InteropServices;
using Accessibility;
public static class Ov {
  [StructLayout(LayoutKind.Sequential)] public struct POINT { public int x, y; }
  [StructLayout(LayoutKind.Sequential)] public struct RECT { public int L, T, R, B; }
  [DllImport("user32.dll")] static extern bool SetProcessDPIAware();
  [DllImport("user32.dll")] static extern IntPtr WindowFromPoint(POINT pt);
  [DllImport("user32.dll")] static extern int GetClassName(IntPtr h, StringBuilder sb, int max);
  [DllImport("oleacc.dll")] static extern int AccessibleObjectFromPoint(POINT pt, out IAccessible acc, out object child);
  static int Role(IAccessible a) { try { return (int)a.get_accRole(0); } catch { return -1; } }
  static string Nm(IAccessible a) { try { object n = a.get_accName(0); return n == null ? "" : n.ToString(); } catch { return ""; } }
  static string Rc(IAccessible a) { try { int x, y, w, h; a.accLocation(out x, out y, out w, out h, 0); return "(" + x + "," + y + " " + w + "x" + h + ")"; } catch { return "(?)"; } }
  static void Walk(IAccessible a, int lvl, int max, StringBuilder sb) {
    int cc = 0; try { cc = a.accChildCount; } catch { }
    sb.AppendLine(new string(' ', lvl * 2) + "role=" + Role(a) + " '" + Nm(a) + "' " + Rc(a) + " cc=" + cc);
    if (lvl >= max) return;
    for (int i = 1; i <= cc && i <= 40; i++) {
      IAccessible c = null; try { c = (IAccessible)a.get_accChild(i); } catch { }
      if (c != null) Walk(c, lvl + 1, max, sb);
      else {
        int r = -1; string n = "";
        try { r = (int)a.get_accRole(i); } catch { }
        try { object v = a.get_accName(i); n = v == null ? "" : v.ToString(); } catch { }
        sb.AppendLine(new string(' ', (lvl + 1) * 2) + "(simple) role=" + r + " '" + n + "'");
      }
    }
  }
  public static string Run(int x, int y, int levels) {
    try { SetProcessDPIAware(); } catch { }
    var pt = new POINT(); pt.x = x; pt.y = y;
    IntPtr hwnd = WindowFromPoint(pt);
    var cls = new StringBuilder(256); GetClassName(hwnd, cls, 256);
    var sb = new StringBuilder();
    sb.AppendLine("window under point: hwnd=0x" + hwnd.ToString("X") + " class=" + cls);
    IAccessible a = null; object c = null;
    int hr = AccessibleObjectFromPoint(pt, out a, out c);
    if (hr != 0 || a == null) { sb.AppendLine("aop-fail hr=" + hr); return sb.ToString(); }
    try { object n = a.get_accName(0); } catch { }
    Marshal.ReleaseComObject(a); a = null;
    hr = AccessibleObjectFromPoint(pt, out a, out c);
    if (hr != 0 || a == null) { sb.AppendLine("aop-fail2"); return sb.ToString(); }
    // walk up to the top-level accessible, then dump from there
    IAccessible top = a;
    for (int i = 0; i < 8; i++) {
      IAccessible p = null; try { p = (IAccessible)top.accParent; } catch { }
      if (p == null) break;
      top = p;
    }
    sb.AppendLine("--- tree from the top-level accessible ---");
    Walk(top, 0, levels, sb);
    return sb.ToString();
  }
}
"@
[Ov]::Run($X, $Y, $Levels)
