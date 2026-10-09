# Temporary probe: name-text dump of the Opera toolbar row (looking for a
# bookmark button). Usage: powershell -NoProfile -File Test/_probe_names.ps1 <hwnd-hex>
Add-Type -ReferencedAssemblies Accessibility @"
using System;
using System.Runtime.InteropServices;
using Accessibility;
public static class ZNames {
  [StructLayout(LayoutKind.Sequential)] public struct POINT { public int X, Y; }
  [StructLayout(LayoutKind.Sequential)] public struct RECT { public int L, T, R, B; }
  [DllImport("user32.dll")] static extern bool SetProcessDPIAware();
  [DllImport("user32.dll")] static extern bool GetWindowRect(IntPtr h, out RECT r);
  [DllImport("oleacc.dll")] static extern int AccessibleObjectFromPoint(POINT pt, out IAccessible acc, out object child);
  static int Role(IAccessible a){ try { return (int)a.get_accRole(0);} catch { return -1; } }
  static string Name(IAccessible a){ try { object n=a.get_accName(0); return n==null?"":n.ToString();} catch { return ""; } }
  public static void Probe(int x, int y) {
    POINT pt = new POINT(); pt.X = x; pt.Y = y;
    IAccessible acc=null; object child=null;
    int hr = AccessibleObjectFromPoint(pt, out acc, out child);
    if (hr!=0 || acc==null) { System.Console.WriteLine("("+x+","+y+") aop-fail"); return; }
    try { object n=acc.get_accName(0); } catch {}
    Marshal.ReleaseComObject(acc); acc=null;
    hr = AccessibleObjectFromPoint(pt, out acc, out child);
    if (hr!=0 || acc==null) { System.Console.WriteLine("("+x+","+y+") aop-fail2"); return; }
    string line = "("+x+","+y+") role="+Role(acc)+" name='"+Name(acc)+"'";
    int x2=0,y2=0,w2=0,h2=0;
    try { acc.accLocation(out x2,out y2,out w2,out h2,0); } catch {}
    line += " rect=("+x2+","+y2+" "+w2+"x"+h2+")";
    System.Console.WriteLine(line);
  }
  public static void Run(long hwnd) {
    try { SetProcessDPIAware(); } catch {}
    RECT r; GetWindowRect((IntPtr)hwnd, out r);
    System.Console.WriteLine("rect " + r.L + "," + r.T + " -> " + r.R + "," + r.B);
    System.Console.WriteLine("=== toolbar row (T+78) x=900..R ===");
    for (int x = 900; x < r.R + 5; x += 12) Probe(x, r.T + 78);
  }
}
"@
[ZNames]::Run([IntPtr]::new([Convert]::ToInt64($args[0], 16)))
