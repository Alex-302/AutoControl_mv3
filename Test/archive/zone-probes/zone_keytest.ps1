# zone_keytest.ps1 - inject a KEY combination while tailing the SW console.
#
# Used to prove the engine's trigger delivery pipeline independently of the
# mouse: Ctrl+Shift+M is the user's trigger 3 (openMenu). If a 750 arrives,
# the pipeline (engine -> SW) is healthy and a missing wheel trigger is a
# mouse-path issue; if nothing arrives, the engine is not delivering at all.
#
# Usage: powershell -ExecutionPolicy Bypass -File Test\zone_keytest.ps1
param([string]$Combo = "ctrl+shift+m", [int]$TailSeconds = 20)

Add-Type @"
using System;
using System.Runtime.InteropServices;
public class ZK {
  [DllImport("user32.dll")] public static extern void keybd_event(byte vk, byte scan, uint flags, UIntPtr extra);
  [DllImport("user32.dll")] public static extern bool SetForegroundWindow(IntPtr h);
}
"@

$proc = Get-Process chrome -ErrorAction SilentlyContinue |
  Where-Object { $_.Path -like '*Chrome SxS*' -and $_.MainWindowHandle -ne 0 } | Select-Object -First 1
if (-not $proc) { Write-Host "NO SXS WINDOW"; exit 1 }
[ZK]::SetForegroundWindow($proc.MainWindowHandle) | Out-Null
Start-Sleep -Milliseconds 400

$out = Join-Path $env:TEMP 'ac_keytest.txt'
Remove-Item $out -ErrorAction SilentlyContinue
Start-Process node -ArgumentList 'Test\zone_swtail.js', '9223', "$TailSeconds", 'AC-MV3-ZONE|Trigger 750|TRIGGER type|AC-ACT|type 60' -RedirectStandardOutput $out -NoNewWindow
Start-Sleep -Seconds 4

# Make sure the engine holds the CURRENT config: after a reconnect the chain
# may have been skipped (bundle-side hash), leaving the fresh engine with no
# triggers at all ("nothing fires while the SW looks healthy").
Write-Host "--- forcing config chain (_Gf) ---"
node Test/cdp_eval.js 9223 "new Promise(res=>{const t=setTimeout(()=>res('cfg TIMEOUT'),8000);try{_Gf({},()=>{clearTimeout(t);res('cfg chain done')})}catch(e){clearTimeout(t);res('cfg THREW '+e.message)}})" --await 2>&1 | Out-String
Start-Sleep -Seconds 2

function Key([string]$name, [bool]$up) {
  $flags = if ($up) { 2 } else { 0 }
  switch ($name) {
    'ctrl'  { [ZK]::keybd_event(0x11, 0, $flags, [UIntPtr]::Zero) }
    'shift' { [ZK]::keybd_event(0x10, 0, $flags, [UIntPtr]::Zero) }
    'm'     { [ZK]::keybd_event(0x4D, 0, $flags, [UIntPtr]::Zero) }
    default { Write-Host "unknown key $name" }
  }
}

Write-Host "--- injecting $Combo ---"
$parts = $Combo.Split('+')
foreach ($k in $parts[0..($parts.Count - 2)]) { Key $k $false; Start-Sleep -Milliseconds 60 }
Key $parts[-1] $false
Start-Sleep -Milliseconds 120
Key $parts[-1] $true
Start-Sleep -Milliseconds 60
foreach ($k in $parts[0..($parts.Count - 2)]) { Key $k $true; Start-Sleep -Milliseconds 40 }

Start-Sleep -Seconds ($TailSeconds - 8)
Write-Host "=== captured SW lines ==="
Get-Content $out -ErrorAction SilentlyContinue
