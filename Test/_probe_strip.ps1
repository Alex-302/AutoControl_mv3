# Temporary probe: role chains along the title-strip row of a browser window.
# Usage: powershell -NoProfile -File Test/_probe_strip.ps1 <hwnd-hex>
Add-Type -ReferencedAssemblies Accessibility @"
using System;
using System.Runtime.InteropServices;
using Accessibility;
public static class ZStrip {
  [StructLayout(LayoutKind.Sequential)] public struct POINT { public int X, Y; }
  [StructLayout(LayoutKind.Sequential)] public struct RECT { public int L, T, R, B; }
  [DllImport("user32.dll")] static extern bool SetProcessDPIAware();
  [DllImport("user32.dll")] static extern bool GetWindowRect(IntPtr h, out RECT r);
  [DllImport("oleacc.dll")] static extern int AccessibleObjectFromPoint(POINT pt, out IAccessible acc, out object child);
  static int Role(IAccessible a){ try { return (int)a.get_accRole(0);} catch { return -1; } }
  static string Codes(IAccessible a){ try { object n=a.get_accName(0); string s=n==null?"":n.ToString(); string c=""; foreach(char ch in s) c+=((int)ch)+","; return c.TrimEnd(','); } catch { return ""; } }
  public static void Probe(int x, int y) {
    POINT pt = new POINT(); pt.X = x; pt.Y = y;
    IAccessible acc=null; object child=null;
    int hr = AccessibleObjectFromPoint(pt, out acc, out child);
    if (hr!=0 || acc==null) { System.Console.WriteLine("("+x+","+y+") aop-fail"); return; }
    try { object n=acc.get_accName(0); } catch {}
    Marshal.ReleaseComObject(acc); acc=null;
    hr = AccessibleObjectFromPoint(pt, out acc, out child);
    if (hr!=0 || acc==null) { System.Console.WriteLine("("+x+","+y+") aop-fail2"); return; }
    string line = "("+x+","+y+")";
    for (int d=0; d<5 && acc!=null; d++) {
      int r=Role(acc); string c=Codes(acc);
      line += " | d"+d+"="+r+(c.Length>0?"["+c+"]":"");
      IAccessible p=null; try { p=(IAccessible)acc.accParent; } catch {}
      try { Marshal.ReleaseComObject(acc); } catch {}
      acc = p;
    }
    System.Console.WriteLine(line);
  }
  public static void Run(long hwnd) {
    try { SetProcessDPIAware(); } catch {}
    RECT r; GetWindowRect((IntPtr)hwnd, out r);
    System.Console.WriteLine("rect " + r.L + "," + r.T + " -> " + r.R + "," + r.B);
    System.Console.WriteLine("=== strip row (T+25) ===");
    for (int x = r.R - 420; x < r.R + 5; x += 15) Probe(x, r.T + 25);
    System.Console.WriteLine("=== strip row left (T+25) ===");
    for (int x = r.L + 100; x < r.L + 400; x += 50) Probe(x, r.T + 25);
    System.Console.WriteLine("=== plus area (T+25) ===");
    for (int x = 690; x < 1400; x += 20) Probe(x, r.T + 25);
    System.Console.WriteLine("=== toolbar row (T+78) ===");
    for (int x = r.R - 420; x < r.R + 5; x += 30) Probe(x, r.T + 78);
    System.Console.WriteLine("=== page / sidebar / bottom ===");
    Probe(r.L + 800, r.T + 900);
    Probe(r.L + 800, r.B - 40);
    Probe(r.L + 30, r.T + 900);
    Probe(r.L + 30, r.T + 120);
  }
}
"@
[ZStrip]::Run([IntPtr]::new([Convert]::ToInt64($args[0], 16)))
