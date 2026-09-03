param(
  [int]$HoldMs = 600,             # hold time after Tab-down
  [string]$ReleaseFirst = "tab",  # "tab" = Tab up first then Ctrl up | "ctrl" = Ctrl up first then Tab up
  [switch]$RepeatTab,             # press Tab down+up once more (move select mark) before release
  [switch]$Esc                    # send only Esc
)
Add-Type -AssemblyName Microsoft.VisualBasic
Add-Type @"
using System;
using System.Runtime.InteropServices;
public class ACKey2 {
  [DllImport("user32.dll")] public static extern void keybd_event(byte bVk, byte bScan, uint dwFlags, UIntPtr dwExtraInfo);
  [DllImport("user32.dll")] public static extern bool SetForegroundWindow(IntPtr hWnd);
}
"@
$proc = Get-Process chrome | Where-Object { $_.Path -like '*Chrome SxS*' -and $_.MainWindowHandle -ne 0 } | Select-Object -First 1
if (-not $proc) { Write-Output "NO SXS WINDOW"; exit 1 }
[ACKey2]::SetForegroundWindow($proc.MainWindowHandle) | Out-Null
Start-Sleep -Milliseconds 500
if ($Esc) {
  [ACKey2]::keybd_event(0x1B, 0, 0, [UIntPtr]::Zero)
  Start-Sleep -Milliseconds 40
  [ACKey2]::keybd_event(0x1B, 0, 2, [UIntPtr]::Zero)
  Write-Output "OK esc"
  exit 0
}
[ACKey2]::keybd_event(0x11, 0, 0, [UIntPtr]::Zero)   # Ctrl down
Start-Sleep -Milliseconds 60
[ACKey2]::keybd_event(0x09, 0, 0, [UIntPtr]::Zero)   # Tab down
Start-Sleep -Milliseconds $HoldMs
if ($RepeatTab) {
  [ACKey2]::keybd_event(0x09, 0, 2, [UIntPtr]::Zero) # Tab up (mark move happens on next down)
  Start-Sleep -Milliseconds 250
  [ACKey2]::keybd_event(0x09, 0, 0, [UIntPtr]::Zero) # Tab down again
  Start-Sleep -Milliseconds 250
  [ACKey2]::keybd_event(0x09, 0, 2, [UIntPtr]::Zero) # Tab up
  Start-Sleep -Milliseconds 150
}
if ($ReleaseFirst -eq "ctrl") {
  [ACKey2]::keybd_event(0x11, 0, 2, [UIntPtr]::Zero) # Ctrl up first
  Start-Sleep -Milliseconds 250
  [ACKey2]::keybd_event(0x09, 0, 2, [UIntPtr]::Zero) # Tab up
} else {
  [ACKey2]::keybd_event(0x09, 0, 2, [UIntPtr]::Zero) # Tab up first
  Start-Sleep -Milliseconds 250
  [ACKey2]::keybd_event(0x11, 0, 2, [UIntPtr]::Zero) # Ctrl up
}
Write-Output "OK ctrl+tab held=$HoldMs release=$ReleaseFirst repeat=$RepeatTab"
