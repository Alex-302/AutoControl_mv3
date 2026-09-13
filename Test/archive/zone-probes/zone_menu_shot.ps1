# zone_menu_shot.ps1 - open the AutoControl tab menu (Ctrl+Tab hold) and take
# a screen shot so the menu geometry can be located.
#
# Usage: powershell -ExecutionPolicy Bypass -File Test\zone_menu_shot.ps1
param([int]$HoldMs = 2500)

Add-Type -AssemblyName System.Drawing
Add-Type @"
using System;
using System.Runtime.InteropServices;
public class ZMS {
  [DllImport("user32.dll")] public static extern bool SetProcessDPIAware();
  [DllImport("user32.dll")] public static extern void keybd_event(byte vk, byte scan, uint flags, UIntPtr extra);
  [DllImport("user32.dll")] public static extern bool SetForegroundWindow(IntPtr h);
  [DllImport("user32.dll")] public static extern bool GetWindowRect(IntPtr h, out RECT r);
  [StructLayout(LayoutKind.Sequential)] public struct RECT { public int l, t, r, b; }
}
"@
[ZMS]::SetProcessDPIAware() | Out-Null

$proc = Get-Process chrome -ErrorAction SilentlyContinue |
  Where-Object { $_.Path -like '*Chrome SxS*' -and $_.MainWindowHandle -ne 0 } |
  Sort-Object { $_.MainWindowTitle.Length } | Select-Object -Last 1
if (-not $proc) { Write-Host "NO SXS WINDOW"; exit 1 }
[ZMS]::SetForegroundWindow($proc.MainWindowHandle) | Out-Null
Start-Sleep -Milliseconds 400
$r = New-Object ZMS+RECT
[ZMS]::GetWindowRect($proc.MainWindowHandle, [ref]$r) | Out-Null

Write-Host "--- Ctrl+Tab hold ($HoldMs ms) ---"
[ZMS]::keybd_event(0x11, 0, 0, [UIntPtr]::Zero)   # Ctrl down
Start-Sleep -Milliseconds 80
[ZMS]::keybd_event(0x09, 0, 0, [UIntPtr]::Zero)   # Tab down
Start-Sleep -Milliseconds 900

# screenshot the whole window while the menu is up
$w = $r.r - $r.l; $h = $r.b - $r.t
$bmp = New-Object System.Drawing.Bitmap($w, $h)
$g = [System.Drawing.Graphics]::FromImage($bmp)
$g.CopyFromScreen($r.l, $r.t, 0, 0, (New-Object System.Drawing.Size($w, $h)))
$g.Dispose()
$out = Join-Path $env:TEMP 'ac_menu_shot.png'
$bmp.Save($out, [System.Drawing.Imaging.ImageFormat]::Png)
$bmp.Dispose()
Write-Host "saved: $out  (window $($r.l),$($r.t) ${w}x${h})"

Start-Sleep -Milliseconds ($HoldMs - 900)
[ZMS]::keybd_event(0x09, 0, 2, [UIntPtr]::Zero)   # Tab up
Start-Sleep -Milliseconds 60
[ZMS]::keybd_event(0x11, 0, 2, [UIntPtr]::Zero)   # Ctrl up
Write-Host "done"
