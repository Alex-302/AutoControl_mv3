# zone_wheel_probe.ps1 - wheel at arbitrary points while tailing the SW log.
#
# For each "name:x,y" point: move the cursor, wait for the hover cache to
# settle, inject REAL wheel notches (mouse_event - the same path a physical
# wheel takes through the native LL hook), then continue. The SW console is
# tailed for the whole run; the report lists every Trigger-750 and zone-gate
# line that appeared.
#
# Usage:
#   powershell -ExecutionPolicy Bypass -File Test\zone_wheel_probe.ps1
#   ... -Points "close:405,31;speaker:240,31;pill:2040,94" -Notches 2
param(
  [string]$Points = "close:405,31;speaker:240,31;pill:2040,94",
  [int]$Notches = 2,
  [int]$SettleMs = 900
)

Add-Type -AssemblyName System.Windows.Forms
Add-Type @"
using System;
using System.Runtime.InteropServices;
public class ZWP {
  [DllImport("user32.dll")] public static extern bool SetProcessDPIAware();
  [DllImport("user32.dll")] public static extern bool SetCursorPos(int x, int y);
  [DllImport("user32.dll")] public static extern void mouse_event(uint f, uint dx, uint dy, uint data, UIntPtr extra);
}
"@
[ZWP]::SetProcessDPIAware() | Out-Null

$list = @()
foreach ($p in $Points.Split(';')) {
  if (-not $p.Trim()) { continue }
  $a = $p.Split(':')
  $xy = $a[1].Split(',')
  $list += [pscustomobject]@{ Name = $a[0]; X = [int]$xy[0]; Y = [int]$xy[1] }
}

$before = [System.Windows.Forms.Cursor]::Position
Write-Host "cursor before: $($before.X),$($before.Y)"
Write-Host "points: $(($list | ForEach-Object { "$($_.Name)@$($_.X),$($_.Y)" }) -join ', ')"

function Wheel([int]$n) {
  for ($i = 0; $i -lt $n; $i++) {
    [ZWP]::mouse_event(0x0800, 0, 0, 120, [UIntPtr]::Zero)
    Start-Sleep -Milliseconds 130
  }
}

$out = Join-Path $env:TEMP 'ac_zone_wheel_probe.txt'
Remove-Item $out -ErrorAction SilentlyContinue
Start-Process node -ArgumentList 'Test\zone_swtail.js', '9223', '60', 'AC-MV3-ZONE|Trigger 750|TRIGGER type' -RedirectStandardOutput $out -NoNewWindow
Start-Sleep -Seconds 4

$marks = @()
foreach ($pt in $list) {
  $stamp = Get-Date
  $marks += [pscustomobject]@{ Name = $pt.Name; At = $stamp }
  Write-Host ("--- wheel at {0} ({1},{2}) ---" -f $pt.Name, $pt.X, $pt.Y)
  [ZWP]::SetCursorPos($pt.X, $pt.Y) | Out-Null
  Start-Sleep -Milliseconds $SettleMs
  Wheel $Notches
  Start-Sleep -Seconds 3
}

Start-Sleep -Seconds 6
[System.Windows.Forms.Cursor]::Position = $before

Write-Host ""
Write-Host "=== captured SW lines ==="
Get-Content $out -ErrorAction SilentlyContinue | Where-Object { $_ -notmatch '\[tail\]' }
Write-Host ""
Write-Host "(cursor restored to $($before.X),$($before.Y))"
