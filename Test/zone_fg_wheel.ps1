# zone_fg_wheel.ps1 - foreground a window BY HWND, move the cursor and inject
# real wheel notches (the verified ALT-hold foreground trick, no process/title
# lookup - the SxS window lookup in _ac_mouse.ps1 is flaky when the title
# changes mid-test).
#
# Usage:
#   powershell -ExecutionPolicy Bypass -File Test\zone_fg_wheel.ps1 -Hwnd 773928210 -Point "1200,700" -Notches 3
#   (find the HWND with Test\zone_wininfo.ps1)
param(
  [int]$Hwnd = 0,
  [string]$Point = "1200,700",
  [int]$Notches = 3,
  [int]$Delta = -120,
  [int]$SettleMs = 800
)
Add-Type @"
using System;
using System.Runtime.InteropServices;
public class ZFW {
  [DllImport("user32.dll")] public static extern bool SetProcessDPIAware();
  [DllImport("user32.dll")] public static extern void mouse_event(uint f, uint dx, uint dy, uint data, UIntPtr extra);
  [DllImport("user32.dll")] public static extern void keybd_event(byte vk, byte scan, uint flags, UIntPtr extra);
  [DllImport("user32.dll")] public static extern bool SetCursorPos(int x, int y);
  [DllImport("user32.dll")] public static extern bool SetForegroundWindow(IntPtr h);
  [DllImport("user32.dll")] public static extern IntPtr GetForegroundWindow();
  [DllImport("user32.dll")] public static extern uint GetWindowThreadProcessId(IntPtr h, out uint pid);
  [DllImport("user32.dll")] public static extern bool GetWindowRect(IntPtr h, out RECT r);
  [StructLayout(LayoutKind.Sequential)] public struct RECT { public int l, t, r, b; }
}
"@
[void][ZFW]::SetProcessDPIAware()
if ($Hwnd -eq 0) { Write-Output "need -Hwnd"; exit 1 }
$h = [IntPtr]$Hwnd

$rect = New-Object ZFW+RECT
[void][ZFW]::GetWindowRect($h, [ref]$rect)
$pid2 = 0
[void][ZFW]::GetWindowThreadProcessId($h, [ref]$pid2)
Write-Output ("window 0x{0:X} pid={1} rect=[{2},{3} {4}x{5}]" -f $Hwnd, $pid2, $rect.l, $rect.t, ($rect.r - $rect.l), ($rect.b - $rect.t))

# ALT-hold unlocks the Windows foreground lock (the caller is not the owner).
$fg = 0
for ($i = 0; $i -lt 5 -and $fg -ne $h; $i++) {
  [ZFW]::keybd_event(0x12, 0, 0, [UIntPtr]::Zero)
  Start-Sleep -Milliseconds 60
  [void][ZFW]::SetForegroundWindow($h)
  Start-Sleep -Milliseconds 150
  [ZFW]::keybd_event(0x12, 0, 2, [UIntPtr]::Zero)
  Start-Sleep -Milliseconds 350
  $fg = [ZFW]::GetForegroundWindow()
}
if ($fg -ne $h) { Write-Output ("FG FAIL (got 0x{0:X})" -f $fg.ToInt64()); exit 2 }
Write-Output "fg OK"

$xy = $Point.Split(',')
[void][ZFW]::SetCursorPos([int]$xy[0], [int]$xy[1])
Start-Sleep -Milliseconds $SettleMs
Write-Output "moved to $($xy[0]),$($xy[1])"

$dw = [BitConverter]::ToUInt32([BitConverter]::GetBytes([int]$Delta), 0)
for ($i = 0; $i -lt $Notches; $i++) {
  [ZFW]::mouse_event(0x0800, 0, 0, $dw, [UIntPtr]::Zero)   # MOUSEEVENTF_WHEEL
  Start-Sleep -Milliseconds 140
}
Write-Output "wheel delta=$Delta ticks=$Notches done"
