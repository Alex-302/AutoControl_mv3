Add-Type @"
using System;
using System.Text;
using System.Runtime.InteropServices;
public class WinProbe3 {
  [DllImport("user32.dll")] public static extern IntPtr WindowFromPoint(POINT pt);
  [DllImport("user32.dll")] public static extern int GetClassName(IntPtr h, StringBuilder sb, int max);
  [DllImport("user32.dll")] public static extern bool GetWindowRect(IntPtr h, out RECT r);
  [DllImport("user32.dll")] public static extern bool EnumChildWindows(IntPtr parent, EnumProc cb, IntPtr lParam);
  public delegate bool EnumProc(IntPtr h, IntPtr lParam);
  [StructLayout(LayoutKind.Sequential)] public struct POINT { public int x; public int y; }
  [StructLayout(LayoutKind.Sequential)] public struct RECT { public int l, t, r, b; }
  public static string Cls(IntPtr h) { if (h == IntPtr.Zero) return "(null)"; var sb = new StringBuilder(256); GetClassName(h, sb, 256); return sb.ToString(); }
}
"@
$win = [IntPtr]110843452
# children of the main window
$kids = [System.Collections.ArrayList]::new()
$cb = [WinProbe3+EnumProc]{ param($h, $lp) [void]$kids.Add($h); return $true }
[WinProbe3]::EnumChildWindows($win, $cb, [IntPtr]::Zero) | Out-Null
Write-Output "children of $win ($([WinProbe3]::Cls($win))): $($kids.Count)"
foreach ($k in $kids) { $r = New-Object WinProbe3+RECT; [WinProbe3]::GetWindowRect($k, [ref]$r) | Out-Null; Write-Output "  $k $([WinProbe3]::Cls($k)) rect=$($r.l),$($r.t),$($r.r),$($r.b)" }
# points inside the window: title bar, tab strip, page
$pts = @(@{n="titlebar"; x=700; y=180}, @{n="tabstrip"; x=700; y=210}, @{n="page"; x=700; y=600}, @{n="page2"; x=1500; y=800})
foreach ($p in $pts) {
  $pt = New-Object WinProbe3+POINT; $pt.x = $p.x; $pt.y = $p.y
  $h = [WinProbe3]::WindowFromPoint($pt)
  $r = New-Object WinProbe3+RECT; [WinProbe3]::GetWindowRect($h, [ref]$r) | Out-Null
  Write-Output "$($p.n)($($p.x),$($p.y)): hwnd=$h cls='$([WinProbe3]::Cls($h))' rect=$($r.l),$($r.t),$($r.r),$($r.b)"
}
