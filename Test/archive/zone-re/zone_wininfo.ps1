# zone_wininfo.ps1 - for each point: the top-level window's PID, process name
# and title. Answers "which browser owns this window?" during zone debugging.
#
# Usage: powershell -ExecutionPolicy Bypass -File Test\zone_wininfo.ps1 -Points "max,1200,60;float,300,195"
param([string]$Points = "max,1200,60;float,300,195")
Add-Type @"
using System;
using System.Text;
using System.Runtime.InteropServices;
public class ZWin {
  [DllImport("user32.dll")] public static extern bool SetProcessDPIAware();
  [DllImport("user32.dll")] public static extern IntPtr WindowFromPoint(POINT p);
  [DllImport("user32.dll")] public static extern IntPtr GetAncestor(IntPtr h, uint f);
  [DllImport("user32.dll", CharSet = CharSet.Unicode)] public static extern int GetWindowText(IntPtr h, StringBuilder s, int n);
  [DllImport("user32.dll", CharSet = CharSet.Unicode)] public static extern int GetClassName(IntPtr h, StringBuilder s, int n);
  [DllImport("user32.dll")] public static extern uint GetWindowThreadProcessId(IntPtr h, out uint pid);
  [StructLayout(LayoutKind.Sequential)] public struct POINT { public int x, y; }
}
"@
[void][ZWin]::SetProcessDPIAware()
foreach ($p in $Points.Split(';')) {
  if (-not $p.Trim()) { continue }
  $a = $p.Split(',')
  if ($a.Count -lt 3) { continue }
  $pt = New-Object ZWin+POINT
  $pt.x = [int]$a[1]; $pt.y = [int]$a[2]
  $hwnd = [ZWin]::WindowFromPoint($pt)
  $root = [ZWin]::GetAncestor($hwnd, 2)
  $pid2 = 0
  [void][ZWin]::GetWindowThreadProcessId($root, [ref]$pid2)
  $title = New-Object System.Text.StringBuilder 256
  [void][ZWin]::GetWindowText($root, $title, 256)
  $cls = New-Object System.Text.StringBuilder 256
  [void][ZWin]::GetClassName($root, $cls, 256)
  $proc = (Get-Process -Id $pid2 -ErrorAction SilentlyContinue).ProcessName
  Write-Output ("{0,-8} ({1},{2}) pid={3} proc={4} class={5} title='{6}'" -f $a[0], $pt.x, $pt.y, $pid2, $proc, $cls.ToString(), $title.ToString())
}
