# zone_id_sweep.ps1 - find WHICH region id the engine passes to its mouseOver
# matcher (the v19 table is indexed by it).
#
# For each candidate id: kill the zone helper (so it cannot overwrite the
# table), write a table with only that id marked, inject one wheel notch over
# the page and count the new type-750 messages in the SW log. A hit means the
# trigger's mouseOver precond asked for exactly that id.
#
# Usage: powershell -ExecutionPolicy Bypass -File Test\zone_id_sweep.ps1 [-From 0 -To 31 -Hwnd 773928210]
param(
  [int]$From = 0,
  [int]$To = 31,
  [int]$Hwnd = 773928210,
  [string]$Point = "1200,700",
  [int]$TailSec = 400
)
$root = Split-Path -Parent $PSScriptRoot
$log = Join-Path $env:TEMP 'ac_sweep_tail.txt'
Remove-Item $log -ErrorAction SilentlyContinue
Start-Process node -ArgumentList 'Test\zone_swtail.js', '9223', "$TailSec", 'Native msg type 750' -RedirectStandardOutput $log -NoNewWindow -WorkingDirectory $root
Start-Sleep -Seconds 3

function Count750 { (Get-Content $log -ErrorAction SilentlyContinue | Select-String 'Native msg type 750' | Measure-Object).Count }

Write-Output "--- control: table with ALL ids marked (must match everywhere) ---"
taskkill /IM ac_zone_helper.exe /F 2>&1 | Out-Null
$all = (1..39) -join ','
& powershell -NoProfile -ExecutionPolicy Bypass -File (Join-Path $root 'Test\engine_zone_write.ps1') -Zones $all 2>&1 | Select-String 'wrote' | Out-Null
$c = Count750
& powershell -NoProfile -ExecutionPolicy Bypass -File (Join-Path $root 'Test\zone_fg_wheel.ps1') -Hwnd $Hwnd -Point $Point -Notches 1 2>&1 | Out-Null
Start-Sleep -Milliseconds 1500
$hit = (Count750) - $c
Write-Output ("control: new 750 = " + $hit + "  (expect > 0)")

Write-Output "--- sweep ---"
for ($id = $From; $id -le $To; $id++) {
  taskkill /IM ac_zone_helper.exe /F 2>&1 | Out-Null
  Start-Sleep -Milliseconds 150
  & powershell -NoProfile -ExecutionPolicy Bypass -File (Join-Path $root 'Test\engine_zone_write.ps1') -Zones "$id" 2>&1 | Out-Null
  $c = Count750
  & powershell -NoProfile -ExecutionPolicy Bypass -File (Join-Path $root 'Test\zone_fg_wheel.ps1') -Hwnd $Hwnd -Point $Point -Notches 1 2>&1 | Out-Null
  Start-Sleep -Milliseconds 1200
  $d = (Count750) - $c
  if ($d -gt 0) { Write-Output ("HIT  id=$id  (+$d)"); Get-Content $log | Select-String 'ZONE' | Select-Object -Last 2 | ForEach-Object { "      " + $_.Line } }
  else { Write-Output ("miss id=$id") }
}
