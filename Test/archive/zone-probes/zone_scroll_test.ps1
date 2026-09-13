# zone_scroll_test.ps1 - objective scroll test for zone-gated wheel triggers.
#
# The engine consumes a wheel event whenever a wheel trigger's mouseOver
# precondition matches (v18 patch: every region below 60 matches), so with a
# plain-wheel + zone trigger the page lost its scrolling (user report
# 2026-09-12). This script measures the settings page's main scroll
# container before/after real wheel notches injected at a point.
#
# Usage:
#   powershell -ExecutionPolicy Bypass -File Test\zone_scroll_test.ps1
#   ... -Point "1200,700" -Notches 3
param(
  [string]$Point = "1200,700",
  [int]$Notches = 3,
  [int]$SettleMs = 700,
  [string]$PageMatch = "main.html"
)
Add-Type @"
using System;
using System.Runtime.InteropServices;
public class ZST {
  [DllImport("user32.dll")] public static extern bool SetProcessDPIAware();
  [DllImport("user32.dll")] public static extern bool SetCursorPos(int x, int y);
  [DllImport("user32.dll")] public static extern void mouse_event(uint f, uint dx, uint dy, uint data, UIntPtr extra);
}
"@
[ZST]::SetProcessDPIAware() | Out-Null
$xy = $Point.Split(',')
$X = [int]$xy[0]; $Y = [int]$xy[1]

$EXPR = "(()=>{const e=[...document.querySelectorAll('*')].filter(x=>x.scrollHeight>x.clientHeight+50)[0];return e?e.scrollTop:-1;})()"

$before = (node (Join-Path $PSScriptRoot 'cdp_page_eval.js') 9223 $PageMatch $EXPR 2>&1 | Select-String -Pattern 'VALUE:' | Select-Object -First 1)
[void][ZST]::SetCursorPos($X, $Y)
Start-Sleep -Milliseconds $SettleMs
for ($i = 0; $i -lt $Notches; $i++) {
  [ZST]::mouse_event(0x0800, 0, 0, 120, [UIntPtr]::Zero)   # 0x0800 = MOUSEEVENTF_WHEEL, +120 = down
  Start-Sleep -Milliseconds 140
}
Start-Sleep -Milliseconds 500
$after = (node (Join-Path $PSScriptRoot 'cdp_page_eval.js') 9223 $PageMatch $EXPR 2>&1 | Select-String -Pattern 'VALUE:' | Select-Object -First 1)

Write-Host "point          : $X,$Y  ($Notches notches)"
Write-Host "scrollTop before: $before"
Write-Host "scrollTop after : $after"
