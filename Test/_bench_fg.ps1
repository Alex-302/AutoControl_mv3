# Temporary probe (2026-09-20): foreground the Opera window WITHOUT leaving the
# Opera main menu open (the ALT-hold trick used by _ac_mouse.ps1 / zone_fg_wheel
# opens it, and an open menu covers the tab strip -> the zone answer becomes
# [1] and every zone trigger is correctly skipped).
# Usage: powershell -NoProfile -File Test/_bench_fg.ps1 [-Hwnd 21575720]
param([int]$Hwnd = 0)
Add-Type -AssemblyName Microsoft.VisualBasic
Add-Type @"
using System;
using System.Runtime.InteropServices;
public class Bfg {
  [DllImport("user32.dll")] public static extern void keybd_event(byte vk, byte scan, uint flags, UIntPtr extra);
  [DllImport("user32.dll")] public static extern bool SetForegroundWindow(IntPtr h);
  [DllImport("user32.dll")] public static extern IntPtr GetForegroundWindow();
  [DllImport("user32.dll")] public static extern bool IsIconic(IntPtr h);
  [DllImport("user32.dll")] public static extern bool ShowWindow(IntPtr h, int cmd);
}
"@
$h = [IntPtr]::new($Hwnd)
if ($Hwnd -eq 0) { "need -Hwnd"; exit 1 }
if ([Bfg]::IsIconic($h)) { [void][Bfg]::ShowWindow($h, 9) ; Start-Sleep -Milliseconds 400 }  # SW_RESTORE
for ($i = 0; $i -lt 6; $i++) {
  if ([Bfg]::GetForegroundWindow() -eq $h) { break }
  # ALT tap unlocks the Windows foreground lock, then the ALT release toggles
  # the Opera menu - so close it right away with ESC.
  [Bfg]::keybd_event(0x12, 0, 0, [UIntPtr]::Zero); Start-Sleep -Milliseconds 60
  [void][Bfg]::SetForegroundWindow($h)
  Start-Sleep -Milliseconds 150
  [Bfg]::keybd_event(0x12, 0, 2, [UIntPtr]::Zero); Start-Sleep -Milliseconds 250
  [Bfg]::keybd_event(0x1B, 0, 0, [UIntPtr]::Zero); Start-Sleep -Milliseconds 40   # ESC down
  [Bfg]::keybd_event(0x1B, 0, 2, [UIntPtr]::Zero); Start-Sleep -Milliseconds 250  # ESC up
}
$fg = [Bfg]::GetForegroundWindow()
if ($fg -eq $h) { "fg OK (hwnd $Hwnd)" } else { "FG FAIL (got $fg, want $Hwnd)" }
