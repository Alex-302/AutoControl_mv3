# Temporary probe (2026-09-20): screenshot a screen region to see what is
# drawn over the Opera tab strip when the a11y hit-test flips to the
# unnamed-PANE overlay (zone answers become [4,1] every second wheel notch).
# Usage: powershell -NoProfile -File Test/_probe_shot.ps1 -X 90 -Y 515 -W 1660 -H 190 -Out C:\Temp\shot.png
param(
  [int]$X = 90, [int]$Y = 515, [int]$W = 1660, [int]$H = 190,
  [string]$Out = "$env:TEMP\ac_flake.png"
)
Add-Type -AssemblyName System.Drawing
Add-Type @"
using System;
using System.Runtime.InteropServices;
public class Dpi { [DllImport("user32.dll")] public static extern bool SetProcessDPIAware(); }
"@
[void][Dpi]::SetProcessDPIAware()
$bmp = New-Object System.Drawing.Bitmap($W, $H)
$g = [System.Drawing.Graphics]::FromImage($bmp)
$g.CopyFromScreen($X, $Y, 0, 0, (New-Object System.Drawing.Size($W, $H)))
$g.Dispose()
$bmp.Save($Out, [System.Drawing.Imaging.ImageFormat]::Png)
$bmp.Dispose()
"shot saved: $Out ($W x $H at $X,$Y)"
