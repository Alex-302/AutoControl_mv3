# zone_fg_scroll.ps1 - end-to-end wheel test WITH the browser foregrounded.
#
# Windows delivers synthesized wheel input to the FOCUSED window, so a test
# that just moves the cursor (zone_scroll_test.ps1) never reaches Chrome
# while the terminal/VS Code has the focus. This script foregrounds the
# Chrome SxS window first (the verified ALT-hold trick from _ac_mouse.ps1),
# then measures a page's window.scrollY before/after real wheel notches and
# prints the SW's trigger/zone lines captured meanwhile.
#
# Usage:
#   powershell -ExecutionPolicy Bypass -File Test\zone_fg_scroll.ps1
#   ... -Point "1200,700" -Notches 3 -TabMatch "youtube.com/watch"
param(
  [string]$Point = "1200,700",
  [int]$Notches = 3,
  [int]$Delta = -120,
  [int]$TailSec = 14,
  [string]$TabMatch = "youtube.com/watch"
)
$xy = $Point.Split(',')
$X = [int]$xy[0]; $Y = [int]$xy[1]
$log = Join-Path $env:TEMP 'ac_fg_scroll_tail.txt'
Remove-Item $log -ErrorAction SilentlyContinue

$MEASURE = "(async()=>{const ts=await chrome.tabs.query({});const t=ts.find(x=>x.url.indexOf('$TabMatch')!==-1);if(!t)return 'no tab';const r=await chrome.scripting.executeScript({target:{tabId:t.id},func:()=>Math.round(window.scrollY)});return t.id+' | '+r[0].result})()"

Start-Process node -ArgumentList 'Test\zone_swtail.js', '9223', "$TailSec", '750|ZONE|Trigger' -RedirectStandardOutput $log -NoNewWindow
Start-Sleep -Seconds 3

Write-Host "--- foreground + move to $X,$Y ---"
$fg = powershell -NoProfile -ExecutionPolicy Bypass -File (Join-Path $PSScriptRoot '_ac_mouse.ps1') -Action move -X $X -Y $Y -TitleFilter "Google Chrome" 2>&1
Write-Host ($fg -join ' ')
Start-Sleep -Milliseconds 600

$before = (node (Join-Path $PSScriptRoot 'cdp_eval.js') 9223 $MEASURE --await 2>&1 | Select-String -Pattern 'VALUE:' | Select-Object -First 1)
Write-Host "scrollY before : $before"

Write-Host "--- wheel delta=$Delta x$Notches ---"
$wh = powershell -NoProfile -ExecutionPolicy Bypass -File (Join-Path $PSScriptRoot '_ac_mouse.ps1') -Action wheel -Delta $Delta -Ticks $Notches -TitleFilter "Google Chrome" 2>&1
Write-Host (($wh | Select-Object -Last 1) -join ' ')
Start-Sleep -Milliseconds 1000

$after = (node (Join-Path $PSScriptRoot 'cdp_eval.js') 9223 $MEASURE --await 2>&1 | Select-String -Pattern 'VALUE:' | Select-Object -First 1)
Write-Host "scrollY after  : $after"
Write-Host "--- SW lines ---"
Get-Content $log -ErrorAction SilentlyContinue | Where-Object { $_ -match '750|ZONE|Trigger' } | Select-Object -First 25
