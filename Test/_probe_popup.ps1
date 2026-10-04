# Temporary probe (2026-09-20): dump the a11y children (WITH NAMES) of the
# hit element's GRANDPARENT - used to identify the layered popup window that
# covers the Opera tab strip after every second wheel notch.
# Usage: powershell -NoProfile -File Test/_probe_popup.ps1 <x> <y>
param([int]$X = 370, [int]$Y = 560)
Add-Type -ReferencedAssemblies Accessibility @"
using System;
using System.Text;
using System.Runtime.InteropServices;
using Accessibility;
public static class Pu {
  [StructLayout(LayoutKind.Sequential)] public struct POINT { public int x, y; }
  [DllImport("user32.dll")] static extern bool SetProcessDPIAware();
  [DllImport("oleacc.dll")] static extern int AccessibleObjectFromPoint(POINT pt, out IAccessible acc, out object child);
  static int Role(IAccessible a) { try { return (int)a.get_accRole(0); } catch { return -1; } }
  static string Nm(IAccessible a) { try { object n = a.get_accName(0); return n == null ? "" : n.ToString(); } catch { return ""; } }
  static string Rc(IAccessible a) { try { int x, y, w, h; a.accLocation(out x, out y, out w, out h, 0); return "(" + x + "," + y + " " + w + "x" + h + ")"; } catch { return "(?)"; } }
  public static string Run(int x, int y) {
    try { SetProcessDPIAware(); } catch { }
    var pt = new POINT(); pt.x = x; pt.y = y;
    IAccessible a = null; object c = null;
    if (AccessibleObjectFromPoint(pt, out a, out c) != 0 || a == null) return "aop-fail";
    try { object n = a.get_accName(0); } catch { }
    if (AccessibleObjectFromPoint(pt, out a, out c) != 0 || a == null) return "aop-fail2";
    var sb = new StringBuilder();
    sb.AppendLine("hit : role=" + Role(a) + " '" + Nm(a) + "' " + Rc(a));
    IAccessible p = null; try { p = (IAccessible)a.accParent; } catch { }
    if (p == null) return sb.ToString() + "no parent";
    sb.AppendLine("par : role=" + Role(p) + " '" + Nm(p) + "' " + Rc(p));
    IAccessible g = null; try { g = (IAccessible)p.accParent; } catch { }
    if (g == null) return sb.ToString() + "no grandparent";
    sb.AppendLine("gp  : role=" + Role(g) + " '" + Nm(g) + "' " + Rc(g));
    int cc = 0; try { cc = g.accChildCount; } catch { }
    sb.AppendLine("children of gp (" + cc + "):");
    for (int i = 1; i <= cc && i <= 40; i++) {
      IAccessible ch = null; try { ch = (IAccessible)g.get_accChild(i); } catch { }
      if (ch != null) sb.AppendLine("  [" + i + "] role=" + Role(ch) + " '" + Nm(ch) + "' " + Rc(ch));
      else {
        int r = -1; string n = "";
        try { r = (int)g.get_accRole(i); } catch { }
        try { object v = g.get_accName(i); n = v == null ? "" : v.ToString(); } catch { }
        sb.AppendLine("  [" + i + "] (simple) role=" + r + " '" + n + "'");
      }
    }
    return sb.ToString();
  }
}
"@
[Pu]::Run($X, $Y)
