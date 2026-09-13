# native_process_chain.ps1 - print the FULL ancestor chain of every native
# AutoControl process + every browser.
#
# Answers "who started this engine/helper, and which browser is it attached to?"
# — and demonstrates the trap that makes the process tree useless for that
# question:
#
#   * the helper's chain is alive:      ac_zone_helper <- cmd.exe <- chrome.exe
#     (so the helper's browser can be found by walking UP — that is what
#      `browserPid` does since 2026-09-13; before, the direct parent was
#      cmd.exe and the own-window gate was silently inert);
#   * the engine's chain is DEAD:       AutoCtrl_2025.4.22.0 <- pid(dead)
#     (AutoControlZero is a launcher: it hands its pipes to the engine and
#      EXITS, so no engine can be told apart from another by its parent — the
#      zone helper therefore binds by the engine's window list instead, see
#      Test/engine_window_binding.ps1).
#
# Usage:
#   powershell -ExecutionPolicy Bypass -File Test\native_process_chain.ps1
function Get-Chain([int]$p) {
  $out = @()
  for ($i = 0; $i -lt 8 -and $p -gt 0; $i++) {
    $pr = Get-CimInstance Win32_Process -Filter "ProcessId=$p" -ErrorAction SilentlyContinue
    if (-not $pr) { $out += "pid=$p(dead)"; break }
    $t = 'browser'
    if ($pr.CommandLine -match '--type=([a-z-]+)') { $t = $matches[1] }
    $out += ("{0}[pid={1},{2}]" -f $pr.Name, $pr.ProcessId, $t)
    $p = $pr.ParentProcessId
  }
  return ($out -join ' <- ')
}
Write-Output "=== ENGINES ==="
Get-CimInstance Win32_Process -Filter "Name='AutoCtrl_2025.4.22.0.exe'" | ForEach-Object { Write-Output ("  " + (Get-Chain $_.ProcessId)) }
Write-Output ""
Write-Output "=== HELPERS ==="
Get-CimInstance Win32_Process -Filter "Name='ac_zone_helper.exe'" | ForEach-Object { Write-Output ("  " + (Get-Chain $_.ProcessId)) }
Write-Output ""
Write-Output "=== ZEROS ==="
Get-CimInstance Win32_Process -Filter "Name='AutoControlZero.exe'" | ForEach-Object { Write-Output ("  " + (Get-Chain $_.ProcessId)) }
Write-Output ""
Write-Output "=== BROWSER PROCESSES ==="
# the whole Chromium family (mirrors `IsBrowserName` in Test/ac_zone_helper.cs)
$browserNames = 'chrome.exe','brave.exe','msedge.exe','opera.exe','vivaldi.exe','yandex.exe','chromium.exe','thorium.exe'
Get-CimInstance Win32_Process | Where-Object { $browserNames -contains $_.Name.ToLower() -and $_.CommandLine -notmatch '--type=' } | ForEach-Object { Write-Output ("  {0,-16} pid={1}  {2}" -f $_.Name, $_.ProcessId, $_.ExecutablePath) }
