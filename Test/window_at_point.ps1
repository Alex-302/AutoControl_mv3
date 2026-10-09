# window_at_point.ps1 - WHAT is under a screen point (and where are the browser
# windows)? The first question to ask when a hover/zone test misbehaves.
#
# It answers, for one point:
#   * the window under the cursor (WindowFromPoint), its class / pid / rect / title;
#   * its top-level root (GetAncestor GA_ROOT) - i.e. WHICH application that is;
#   * the current foreground window;
#   * every Chrome browser window: pid, main HWND and install path.
#
# Why it matters: `Test/zone_probe.ps1` asks the zone helper what zones a point
# has; when that answer looks wrong the usual cause is that the point is NOT over
# the window you think (a dev-UI window sits on top - VS Code is a
# `Chrome_WidgetWin_1` window too, and the helper correctly reports NO zones
# over it). Also useful after moving/maximizing a browser: the coordinates used
# by the tests are PHYSICAL pixels (this script calls SetProcessDPIAware).
#
# Usage:
#   powershell -ExecutionPolicy Bypass -File Test\window_at_point.ps1
#   powershell -ExecutionPolicy Bypass -File Test\window_at_point.ps1 -Point "564,500"
param([string]$Point = "564,500")
Add-Type @"
using System;
using System.Text;
using System.Runtime.InteropServices;
public class WP {
  [DllImport("user32.dll")] public static extern bool SetProcessDPIAware();
  [DllImport("user32.dll")] public static extern IntPtr WindowFromPoint(POINT p);
  [DllImport("user32.dll")] public static extern IntPtr GetAncestor(IntPtr h, uint f);
  [DllImport("user32.dll")] public static extern uint GetWindowThreadProcessId(IntPtr h, out uint pid);
  [DllImport("user32.dll", CharSet=CharSet.Unicode)] public static extern int GetClassName(IntPtr h, StringBuilder s, int n);
  [DllImport("user32.dll", CharSet=CharSet.Unicode)] public static extern int GetWindowText(IntPtr h, StringBuilder s, int n);
  [DllImport("user32.dll")] public static extern bool GetWindowRect(IntPtr h, out RECT r);
  [DllImport("user32.dll")] public static extern IntPtr GetForegroundWindow();
  [StructLayout(LayoutKind.Sequential)] public struct POINT { public int x, y; }
  [StructLayout(LayoutKind.Sequential)] public struct RECT { public int l, t, r, b; }
  public static string Describe(IntPtr h) {
    if (h == IntPtr.Zero) return "(none)";
    uint pid; GetWindowThreadProcessId(h, out pid);
    var cls = new StringBuilder(256); GetClassName(h, cls, 256);
    var txt = new StringBuilder(256); GetWindowText(h, txt, 256);
    RECT r; GetWindowRect(h, out r);
    return string.Format("hwnd=0x{0:X} pid={1} class={2} rect=[{3},{4} {5}x{6}] title='{7}'",
      h.ToInt64(), pid, cls.ToString(), r.l, r.t, r.r - r.l, r.b - r.t, txt.ToString());
  }
}
"@
[void][WP]::SetProcessDPIAware()
$xy = $Point.Split(',')
$pt = New-Object WP+POINT
$pt.x = [int]$xy[0]; $pt.y = [int]$xy[1]
$h = [WP]::WindowFromPoint($pt)
Write-Output ("cursor point {0},{1}" -f $pt.x, $pt.y)
Write-Output ("  WindowFromPoint : " + [WP]::Describe($h))
Write-Output ("  GA_ROOT of it   : " + [WP]::Describe([WP]::GetAncestor($h, 2)))
Write-Output ("  FOREGROUND      : " + [WP]::Describe([WP]::GetForegroundWindow()))
Write-Output ""
Write-Output "browser windows:"
# the whole Chromium family (mirrors `IsBrowserName` in Test/ac_zone_helper.cs)
$browserNames = 'chrome.exe','brave.exe','msedge.exe','opera.exe','vivaldi.exe','yandex.exe','chromium.exe','thorium.exe'
Get-CimInstance Win32_Process | Where-Object { $browserNames -contains $_.Name.ToLower() -and $_.CommandLine -notmatch '--type=' } | ForEach-Object {
  $pr = Get-Process -Id $_.ProcessId -ErrorAction SilentlyContinue
  Write-Output ("  pid={0} hwnd={1}  {2}" -f $_.ProcessId, $pr.MainWindowHandle, $_.ExecutablePath)
}
