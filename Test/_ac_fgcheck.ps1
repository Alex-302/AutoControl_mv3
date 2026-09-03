Add-Type @"
using System;
using System.Runtime.InteropServices;
using System.Text;
public class FW3 {
  [DllImport("user32.dll")] public static extern IntPtr GetForegroundWindow();
  [DllImport("user32.dll")] public static extern int GetWindowText(IntPtr h, StringBuilder sb, int max);
  [DllImport("user32.dll")] public static extern int GetClassName(IntPtr h, StringBuilder sb, int max);
  [DllImport("user32.dll")] public static extern uint GetWindowThreadProcessId(IntPtr h, out uint pid);
}
"@
$fg = [FW3]::GetForegroundWindow()
$t = New-Object System.Text.StringBuilder 256
$c = New-Object System.Text.StringBuilder 256
[FW3]::GetWindowText($fg, $t, 256) | Out-Null
[FW3]::GetClassName($fg, $c, 256) | Out-Null
$pid2 = 0
[FW3]::GetWindowThreadProcessId($fg, [ref]$pid2) | Out-Null
Write-Output "fg hwnd=$fg title='$($t.ToString())' class='$($c.ToString())' pid=$pid2"
$p = Get-Process -Id $pid2 -ErrorAction SilentlyContinue
if ($p) { Write-Output "proc: $($p.ProcessName) path=$($p.Path)" }
