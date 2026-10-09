# zone_cfg_watch.ps1 - watch whether a forced config chain actually SENDS type 60.
#
# Suspicion (2026-09-12): after the engine restarts (extension reload / engine
# respawn) the bundle may skip re-sending a byte-identical config, so the fresh
# engine gets NO triggers at all — "nothing works" while the SW looks healthy.
#
# Usage: powershell -ExecutionPolicy Bypass -File Test\zone_cfg_watch.ps1
param([int]$TailSeconds = 22)

Set-Location (Split-Path $PSScriptRoot -Parent)
$out = Join-Path $env:TEMP 'ac_cfg_watch.txt'
Remove-Item $out -ErrorAction SilentlyContinue
Start-Process node -ArgumentList 'Test\zone_swtail.js', '9223', "$TailSeconds", 'type 60|config|Trigger 750|AC-MV3-ZONE|native' -RedirectStandardOutput $out -NoNewWindow
Start-Sleep -Seconds 4

Write-Host "--- forcing the config chain (_Gf) ---"
$r = node Test/cdp_eval.js 9223 "new Promise(res=>{const t=setTimeout(()=>res('TIMEOUT'),8000);try{_Gf({},()=>{clearTimeout(t);res('chain done')})}catch(e){clearTimeout(t);res('THREW '+e.message)}})" --await 2>&1
Write-Host $r

Start-Sleep -Seconds ($TailSeconds - 6)
Write-Host "=== captured SW lines ==="
Get-Content $out -ErrorAction SilentlyContinue
