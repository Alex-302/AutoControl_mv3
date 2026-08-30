param(
  [int]$HoldMs = 0,      # hold Ctrl+Tab for this long (0 = quick tap)
  [switch]$Esc,          # send only Esc (close menu)
  [switch]$TabRepeat     # press Tab once while Ctrl is already down (move select mark)
)
Add-Type -AssemblyName Microsoft.VisualBasic
Add-Type @"
using System;
using System.Runtime.InteropServices;
public class ACKey {
  [DllImport("user32.dll")] public static extern void keybd_event(byte bVk, byte bScan, uint dwFlags, UIntPtr dwExtraInfo);
  [DllImport("user32.dll")] public static extern bool SetForegroundWindow(IntPtr hWnd);
}
"@
$proc = Get-Process chrome | Where-Object { $_.Path -like '*Chrome SxS*' -and $_.MainWindowHandle -ne 0 } | Select-Object -First 1
if (-not $proc) { Write-Output "NO SXS WINDOW"; exit 1 }
[ACKey]::SetForegroundWindow($proc.MainWindowHandle) | Out-Null
Start-Sleep -Milliseconds 500
if ($Esc) {
  [ACKey]::keybd_event(0x1B, 0, 0, [UIntPtr]::Zero)   # Esc down
  Start-Sleep -Milliseconds 40
  [ACKey]::keybd_event(0x1B, 0, 2, [UIntPtr]::Zero)   # Esc up
  Write-Output "OK esc"
  exit 0
}
[ACKey]::keybd_event(0x11, 0, 0, [UIntPtr]::Zero)      # Ctrl down
Start-Sleep -Milliseconds 60
[ACKey]::keybd_event(0x09, 0, 0, [UIntPtr]::Zero)      # Tab down
if ($HoldMs -gt 0) { Start-Sleep -Milliseconds $HoldMs }
[ACKey]::keybd_event(0x09, 0, 2, [UIntPtr]::Zero)      # Tab up
Start-Sleep -Milliseconds 60
[ACKey]::keybd_event(0x11, 0, 2, [UIntPtr]::Zero)      # Ctrl up
Write-Output "OK ctrl+tab held=$HoldMs focus=$($proc.MainWindowTitle)"
