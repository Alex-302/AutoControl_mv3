# List the top-level windows of a process (hwnd, rect, minimized, title).
#
# Why: Chrome keeps SEVERAL windows per process, and the zone probes must be run
# against the RIGHT one (user note 2026-10-04: work with the MAXIMIZED window -
# a window with many tabs hides its close buttons, so zone-15 probing there
# measures nothing; minimized windows must not be touched at all).
#
# Usage:
#   powershell -NoProfile -File Test/_probe_winlist.ps1 -ProcId 97972
#   powershell -NoProfile -File Test/_probe_winlist.ps1 -ProcId 97972 -MinWidth 200
param([int]$ProcId = 0, [int]$MinWidth = 200)

if ($ProcId -le 0) { "usage: -ProcId <process id>"; exit 1 }

Add-Type -TypeDefinition @"
using System;
using System.Runtime.InteropServices;
using System.Text;
public class AcWinList {
  [DllImport("user32.dll")] public static extern bool EnumWindows(EnumWindowsProc cb, IntPtr l);
  public delegate bool EnumWindowsProc(IntPtr h, IntPtr l);
  [DllImport("user32.dll")] public static extern uint GetWindowThreadProcessId(IntPtr h, out uint pid);
  [DllImport("user32.dll")] public static extern bool IsWindowVisible(IntPtr h);
  [DllImport("user32.dll")] public static extern bool IsIconic(IntPtr h);
  [DllImport("user32.dll")] public static extern bool GetWindowRect(IntPtr h, out RECT r);
  [DllImport("user32.dll")] public static extern int GetWindowText(IntPtr h, StringBuilder s, int n);
  [StructLayout(LayoutKind.Sequential)] public struct RECT { public int L, T, R, B; }
}
"@

$found = New-Object System.Collections.ArrayList
$cb = [AcWinList+EnumWindowsProc]{
  param($h, $l)
  $p = 0
  [void][AcWinList]::GetWindowThreadProcessId($h, [ref]$p)
  if ($p -eq $ProcId) {
    $r = New-Object AcWinList+RECT
    [void][AcWinList]::GetWindowRect($h, [ref]$r)
    $w = $r.R - $r.L
    if ($w -gt $MinWidth) {
      $sb = New-Object System.Text.StringBuilder 400
      [void][AcWinList]::GetWindowText($h, $sb, 400)
      $title = $sb.ToString()
      if ($title.Length -gt 48) { $title = $title.Substring(0, 48) }
      [void]$found.Add([pscustomobject]@{
        hwnd = $h.ToInt64()
        vis  = [AcWinList]::IsWindowVisible($h)
        min  = [AcWinList]::IsIconic($h)
        rect = "[$($r.L),$($r.T) $($w)x$($r.B - $r.T)]"
        title = $title
      })
    }
  }
  return $true
}
[void][AcWinList]::EnumWindows($cb, [IntPtr]::Zero)

"pid $ProcId - $($found.Count) window(s):"
$found | ForEach-Object { "  hwnd={0,-12} visible={1,-6} minimized={2,-6} {3,-26} '{4}'" -f $_.hwnd, $_.vis, $_.min, $_.rect, $_.title }
