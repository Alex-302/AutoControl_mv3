# _ac_crop.ps1 - screen crops of the Chrome SxS window areas (for visual checks).
# Copies from the SCREEN (physical pixels, DPI-aware) - the window must be
# visible (not covered by another window) at the requested points.
#
# Usage: powershell -ExecutionPolicy Bypass -File Test\_ac_crop.ps1
Add-Type -AssemblyName System.Drawing
Add-Type @"
using System;
using System.Runtime.InteropServices;
public class CropWin {
  [DllImport("user32.dll")] public static extern bool SetProcessDPIAware();
  [DllImport("user32.dll")] public static extern bool GetWindowRect(IntPtr h, out RECT r);
  [DllImport("user32.dll")] public static extern bool GetCursorPos(out POINT p);
  [StructLayout(LayoutKind.Sequential)] public struct RECT { public int l, t, r, b; }
  [StructLayout(LayoutKind.Sequential)] public struct POINT { public int x, y; }
}
"@
[CropWin]::SetProcessDPIAware() | Out-Null

$cands = Get-Process chrome -ErrorAction SilentlyContinue |
  Where-Object { $_.Path -like '*Chrome SxS*' -and $_.MainWindowHandle -ne 0 }
$best = $null; $bestArea = 0
foreach ($c in $cands) {
  $rr = New-Object CropWin+RECT
  if (-not [CropWin]::GetWindowRect([IntPtr]$c.MainWindowHandle, [ref]$rr)) { continue }
  $area = ($rr.r - $rr.l) * ($rr.b - $rr.t)
  if ($area -gt $bestArea) { $bestArea = $area; $best = $c }
}
if (-not $best) { Write-Output "NO SXS WINDOW"; exit 1 }
$h = $best.MainWindowHandle
$r = New-Object CropWin+RECT
[CropWin]::GetWindowRect([IntPtr]$h, [ref]$r) | Out-Null
$cur = New-Object CropWin+POINT
[CropWin]::GetCursorPos([ref]$cur) | Out-Null
Write-Output ("window: l={0} t={1} r={2} b={3}; cursor at {4},{5}" -f $r.l, $r.t, $r.r, $r.b, $cur.x, $cur.y)

function Crop([int]$x, [int]$y, [int]$w, [int]$h, [string]$name) {
  $bmp = New-Object System.Drawing.Bitmap($w, $h)
  $g = [System.Drawing.Graphics]::FromImage($bmp)
  $g.CopyFromScreen($x, $y, 0, 0, (New-Object System.Drawing.Size($w, $h)))
  $g.Dispose()
  $out = Join-Path $env:TEMP $name
  $bmp.Save($out, [System.Drawing.Imaging.ImageFormat]::Png)
  $bmp.Dispose()
  Write-Output "saved: $out (${w}x${h} at $x,$y)"
}

# 1. right end of the toolbar row (star / extension icons / profile / update pill / kebab?)
Crop 1450 55 644 90 'ac_crop_toolbar_right.png'
# 2. left part of the tab strip (tab search, pinned tab, second tab with favicon+close)
Crop 83 0 620 140 'ac_crop_tabs_left.png'
# 3. right part of the tab strip (new tab button + window controls)
Crop 1400 0 694 140 'ac_crop_tabs_right.png'
