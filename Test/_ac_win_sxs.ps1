Add-Type @"
using System;
using System.Text;
using System.Runtime.InteropServices;
public class WinProbe2 {
  [DllImport("user32.dll")] public static extern IntPtr WindowFromPoint(POINT pt);
  [DllImport("user32.dll")] public static extern int GetClassName(IntPtr h, StringBuilder sb, int max);
  [DllImport("user32.dll")] public static extern bool GetWindowRect(IntPtr h, out RECT r);
  [DllImport("user32.dll")] public static extern bool EnumChildWindows(IntPtr parent, EnumProc cb, IntPtr lParam);
  [DllImport("user32.dll")] public static extern bool GetWindowText(IntPtr h, StringBuilder sb, int max);
  [DllImport("user32.dll")] public static extern int GetWindowThreadProcessId(IntPtr h, out uint pid);
  [DllImport("user32.dll")] public static extern IntPtr FindWindowEx(IntPtr parent, IntPtr after, string cls, string title);
  public delegate bool EnumProc(IntPtr h, IntPtr lParam);
  [StructLayout(LayoutKind.Sequential)] public struct POINT { public int x; public int y; }
  [StructLayout(LayoutKind.Sequential)] public struct RECT { public int l, t, r, b; }
  public static string Cls(IntPtr h) { if (h == IntPtr.Zero) return "(null)"; var sb = new StringBuilder(256); GetClassName(h, sb, 256); return sb.ToString(); }
  public static string Title(IntPtr h) { var sb = new StringBuilder(256); GetWindowText(h, sb, 256); return sb.ToString(); }
}
"@
$sxsPids = @(Get-Process chrome | Where-Object { $_.Path -like '*Chrome SxS*' -and $_.MainWindowHandle -ne 0 } | ForEach-Object { $_.Id })
Write-Output "SxS pids: $($sxsPids -join ',')"
# enumerate top-level windows to find the SxS ones
Add-Type @"
using System;
using System.Text;
using System.Collections.Generic;
using System.Runtime.InteropServices;
public class TopWin {
  [DllImport("user32.dll")] public static extern bool EnumWindows(EnumProc cb, IntPtr lp);
  [DllImport("user32.dll")] public static extern int GetWindowText(IntPtr h, StringBuilder sb, int max);
  [DllImport("user32.dll")] public static extern int GetClassName(IntPtr h, StringBuilder sb, int max);
  [DllImport("user32.dll")] public static extern uint GetWindowThreadProcessId(IntPtr h, out uint pid);
  [DllImport("user32.dll")] public static extern bool GetWindowRect(IntPtr h, out RECT r);
  public delegate bool EnumProc(IntPtr h, IntPtr lp);
  [StructLayout(LayoutKind.Sequential)] public struct RECT { public int l, t, r, b; }
  public static List<string> Results = new List<string>();
  public static void Scan(uint[] pids) {
    EnumWindows((h, lp) => {
      uint pid; GetWindowThreadProcessId(h, out pid);
      if (Array.IndexOf(pids, pid) >= 0) {
        var t = new StringBuilder(256); GetWindowText(h, t, 256);
        var c = new StringBuilder(256); GetClassName(h, c, 256);
        RECT r; GetWindowRect(h, out r);
        Results.Add("hwnd=" + h + " cls='" + c + "' title='" + t + "' rect=" + r.l + "," + r.t + "," + r.r + "," + r.b);
      }
      return true;
    }, IntPtr.Zero);
  }
}
"@
[TopWin]::Scan([System.UInt32[]]$sxsPids)
[TopWin]::Results | ForEach-Object { Write-Output $_ }