# zone_e2e_test.ps1 - end-to-end check of the SW zone gate.
#
# Injects REAL OS wheel events (mouse_event) - the same path the user's
# physical wheel takes through the native LL hook - over:
#   1. a tab (expect: zones=[12,1] in [12] -> executing),
#   2. the page (expect: zones=[3,1] -> skipped),
# while tailing the service-worker console.
# NO window activation (unlike _ac_mouse.ps1): the wheel goes to the window
# under the cursor and the native hook sees it globally.
#
# Usage: powershell -ExecutionPolicy Bypass -File Test\zone_e2e_test.ps1
param([int]$TabX = 300, [int]$TabY = 31, [int]$PageX = 400, [int]$PageY = 300)

Add-Type -AssemblyName System.Windows.Forms
Add-Type @"
using System;
using System.Runtime.InteropServices;
public class ZE2E {
  [DllImport("user32.dll")] public static extern bool SetProcessDPIAware();
  [DllImport("user32.dll")] public static extern bool SetCursorPos(int x, int y);
  [DllImport("user32.dll")] public static extern void mouse_event(uint f, uint dx, uint dy, uint data, UIntPtr extra);
}
"@
[ZE2E]::SetProcessDPIAware() | Out-Null

$before = [System.Windows.Forms.Cursor]::Position
Write-Host "cursor before: $($before.X),$($before.Y)"
function Wheel([int]$notches) {
  for ($i = 0; $i -lt $notches; $i++) {
    [ZE2E]::mouse_event(0x0800, 0, 0, 120, [UIntPtr]::Zero)   # MOUSEEVENTF_WHEEL, +120 = up
    Start-Sleep -Milliseconds 120
  }
}
function GoTo([int]$x, [int]$y) {
  [ZE2E]::SetCursorPos($x, $y) | Out-Null
  Start-Sleep -Milliseconds 900    # let Chrome + the engine hover cache settle
}

$out = Join-Path $env:TEMP 'ac_zone_e2e.txt'
Remove-Item $out -ErrorAction SilentlyContinue
Start-Process node -ArgumentList 'Test\zone_swtail.js', '9223', '40', 'AC-MV3-ZONE|Trigger 750' -RedirectStandardOutput $out -NoNewWindow
Start-Sleep -Seconds 4

Write-Host "--- 1. wheel over a TAB ($TabX,$TabY) ---"
GoTo $TabX $TabY
Wheel 2
Start-Sleep -Seconds 3

Write-Host "--- 2. wheel over the PAGE ($PageX,$PageY) ---"
GoTo $PageX $PageY
Wheel 2
Start-Sleep -Seconds 4

Write-Host "--- waiting for the capture to finish ---"
for ($i = 0; $i -lt 40; $i++) {
  Start-Sleep -Seconds 1
  if ((Test-Path $out) -and ((Get-Content $out -ErrorAction SilentlyContinue) -join "`n") -match 'zones=\[') { break }
}
Start-Sleep -Seconds 2

[System.Windows.Forms.Cursor]::Position = $before
Write-Host "cursor restored: $($before.X),$($before.Y)"
Write-Host "=== NEW-FORMAT zone lines (multi-zone SW build) ==="
Get-Content $out -ErrorAction SilentlyContinue | Where-Object { $_ -match 'zones=\[' }
Write-Host "=== last 12 captured lines ==="
Get-Content $out -ErrorAction SilentlyContinue | Select-Object -Last 12
