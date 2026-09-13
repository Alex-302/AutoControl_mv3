# zone_probe.ps1 - live probe of the deployed zone helper.
#
# Moves the cursor to each given screen point and asks the deployed
# ac_zone_helper.exe (via Test/zone_helper_smoke.js) what zones are there.
# Physical pixels (the Chrome window is on the primary monitor; the display
# runs at 150%, so logical*1.5 = physical).
#
# Usage:
#   powershell -ExecutionPolicy Bypass -File Test\zone_probe.ps1
#   powershell -ExecutionPolicy Bypass -File Test\zone_probe.ps1 -Points "tab,300,31;close,405,31"
param([string]$Points = "", [int]$Settle = 150)

Add-Type @"
using System;
using System.Runtime.InteropServices;
public class ZP {
  [DllImport("user32.dll")] public static extern bool SetProcessDPIAware();
  [DllImport("user32.dll")] public static extern bool SetCursorPos(int x, int y);
  [DllImport("user32.dll")] public static extern bool GetCursorPos(out POINT p);
  [StructLayout(LayoutKind.Sequential)] public struct POINT { public int x, y; }
}
"@
[ZP]::SetProcessDPIAware() | Out-Null

if (-not $Points) {
  # Defaults for the Chrome 150 SxS window at l=83 t=0 r=2094 b=2170 (150%):
  # tabs ~y=31, toolbar ~y=94, page below ~y=130.
  $Points = @(
    "tab-body,300,31",
    "tab-favicon,240,31",
    "tab-close,405,31",
    "newtab-plus,1776,31",
    "tabsearch,120,31",
    "strip-empty,1810,31",
    "top-band,200,4",
    "window-controls,1950,31",
    "back-btn,130,94",
    "omnibox,1200,94",
    "site-info,300,94",
    "bookmark-star,1590,94",
    "ext-icon,1700,94",
    "profile-you,1800,94",
    "kebab-area,2040,94",
    "page,400,300"
  ) -join ";"
}

$log = Join-Path $env:TEMP 'ac_zone_probe.txt'
"" | Set-Content $log
Write-Output ("{0,-18} {1,-12} {2}" -f "POINT", "COORDS", "HELPER RESPONSE")
foreach ($p in $Points.Split(';')) {
  if (-not $p.Trim()) { continue }
  $a = $p.Split(',')
  if ($a.Count -lt 3) { continue }
  $name = $a[0]; $x = [int]$a[1]; $y = [int]$a[2]
  [ZP]::SetCursorPos($x, $y) | Out-Null
  Start-Sleep -Milliseconds $Settle
  $resp = (node (Join-Path $PSScriptRoot 'zone_helper_smoke.js') 2>&1 | Select-String -Pattern 'RESP:|timeout|ERR' | Select-Object -First 1) -replace '^\s*', ''
  $line = ("{0,-18} ({1,5},{2,5})  {3}" -f $name, $x, $y, $resp)
  Write-Output $line
  $line | Add-Content $log
}
Write-Output ""
Write-Output "DONE - saved: $log"
