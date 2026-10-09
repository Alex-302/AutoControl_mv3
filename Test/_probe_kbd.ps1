# Temporary probe: name + keyboard shortcut of toolbar buttons (Opera).
# Usage: powershell -NoProfile -File Test/_probe_kbd.ps1 <hwnd-hex>
Add-Type -ReferencedAssemblies Accessibility @"
using System;
using System.Runtime.InteropServices;
using Accessibility;
public static class ZKbd {
  [StructLayout(LayoutKind.Sequential)] public struct POINT { public int X, Y; }
  [StructLayout(LayoutKind.Sequential)] public struct RECT { public int L, T, R, B; }
  [DllImport("user32.dll")] static extern bool SetProcessDPIAware();
  [DllImport("user32.dll")] static extern bool GetWindowRect(IntPtr h, out RECT r);
  [DllImport("user32.dll")] static extern bool SetCursorPos(int x, int y);
  [DllImport("oleacc.dll")] static extern int AccessibleObjectFromPoint(POINT pt, out IAccessible acc, out object child);
  static int Role(IAccessible a){ try { return (int)a.get_accRole(0);} catch { return -1; } }
  static string Name(IAccessible a){ try { object n=a.get_accName(0); return n==null?"":n.ToString();} catch { return ""; } }
  static string Kbd(IAccessible a){ try { object n=a.get_accKeyboardShortcut(0); return n==null?"":n.ToString();} catch { return "(err)"; } }
  public static void Probe(int x, int y) {
    POINT pt = new POINT(); pt.X = x; pt.Y = y;
    SetCursorPos(x, y);
    System.Threading.Thread.Sleep(80);
    IAccessible acc=null; object child=null;
    int hr = AccessibleObjectFromPoint(pt, out acc, out child);
    if (hr!=0 || acc==null) { System.Console.WriteLine("("+x+","+y+") aop-fail"); return; }
    try { object n=acc.get_accName(0); } catch {}
    Marshal.ReleaseComObject(acc); acc=null;
    System.Threading.Thread.Sleep(30);
    hr = AccessibleObjectFromPoint(pt, out acc, out child);
    if (hr!=0 || acc==null) { System.Console.WriteLine("("+x+","+y+") aop-fail2"); return; }
    System.Console.WriteLine("("+x+","+y+") role="+Role(acc)+" name='"+Name(acc)+"' kbd='"+Kbd(acc)+"'");
    Marshal.ReleaseComObject(acc);
  }
  public static void Run(long hwnd) {
    try { SetProcessDPIAware(); } catch {}
    RECT r; GetWindowRect((IntPtr)hwnd, out r);
    System.Console.WriteLine("rect " + r.L + "," + r.T + " -> " + r.R + "," + r.B);
    int y = r.T + 78;
    Probe(1300, y);  // Snapshot
    Probe(1345, y);  // Privacy Protection
    Probe(1390, y);  // Send to My Flow
    Probe(1435, y);  // Add to bookmarks
    Probe(1480, y);  // Easy setup
    Probe(1525, y);  // Opera Account
  }
}
"@
[ZKbd]::Run([IntPtr]::new([Convert]::ToInt64($args[0], 16)))
