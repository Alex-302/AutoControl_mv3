# native_uninstall.ps1 - interactive dev cleanup of the AutoControl native component; also the "component absent" fixture for real-browser autotests (keys/files removed, the extension's stored flag kept).
#
# For DEBUGGING the extension's Uninstall flow on a machine with several browsers.
# It prints ONE inventory (processes, the whole %LOCALAPPDATA%\AutoControl tree,
# all native-host registry keys), asks ONE confirmation, then performs the whole
# cleanup without further prompts: delete the 16 host keys (8 vendor branches x
# engine+helper), stop ac_zone_helper / engine / Zero processes (re-scanning for
# respawned ones), delete the component directory and the leftover
# %TEMP%\Native-Component.exe.
#
# The ORDER matters: keys first, so the browsers can no longer respawn the
# engine/helper, then processes, then files (a kill-first order left locked
# files behind - user report 2026-10-11).
#
# Why manual: the original installer removes only the Chrome engine key and
# cannot delete a directory whose files are locked by another browser's helper/
# engine.
#
# Real-browser autotests: after this pass the extension still believes the
# component is installed (natHostInstalled stays true), which is exactly the
# state that shows the "Native Component not working" dialog and exercises the
# reinstall / repair paths - a clean "component absent" fixture. Restore with
# the installer (or the dialog's Reinstall button).
#
# WARNING: it deletes the WHOLE component directory - including settings*.dat
# and *.orig backups. Use -KeepProcesses / -KeepRegistry / -KeepFiles to run a
# partial pass.
#
# Usage:
#   powershell -File Test\native_uninstall.ps1
#   Test\native_uninstall.cmd            (one-click launcher, bypasses the policy)
#   powershell -File Test\native_uninstall.ps1 -Force
#   powershell -File Test\native_uninstall.ps1 -KeepFiles -KeepProcesses
param(
  [switch]$Force,          # no prompts (still prints the inventory)
  [switch]$KeepProcesses,  # do not touch running processes
  [switch]$KeepRegistry,   # do not touch the registry
  [switch]$KeepFiles       # do not delete files
)

$ErrorActionPreference = 'Continue'
$dir = Join-Path $env:LOCALAPPDATA 'AutoControl'
$tmpExe = Join-Path $env:TEMP 'Native-Component.exe'
$procNames = @('ac_zone_helper.exe', 'AutoCtrl_2025.4.22.0.exe', 'AutoControlZero.exe')
$branches = @(
  'HKCU:\Software\Google\Chrome\NativeMessagingHosts',
  'HKCU:\Software\Google\Chrome SxS\NativeMessagingHosts',
  'HKCU:\Software\Microsoft\Edge\NativeMessagingHosts',
  'HKCU:\Software\BraveSoftware\Brave-Browser\NativeMessagingHosts',
  'HKCU:\Software\Opera Software\NativeMessagingHosts',
  'HKCU:\Software\Vivaldi\NativeMessagingHosts',
  'HKCU:\Software\Chromium\NativeMessagingHosts',
  'HKCU:\Software\Yandex\YandexBrowser\NativeMessagingHosts'
)
$hosts = @('hrich.autocontrol', 'com.autocontrol.zonehelper')

function Ask([string]$q) {
  if ($Force) { Write-Host ('  {0} [auto: yes]' -f $q) -ForegroundColor DarkGray; return $true }
  $a = Read-Host ('  {0} [y/N]' -f $q)
  return ($a -match '^(y|yes)$')
}
function Section([string]$t) { Write-Host ''; Write-Host ('=== ' + $t + ' ===') -ForegroundColor Cyan }
function Get-NativeProcs {
  $res = @()
  foreach ($n in $procNames) {
    $list = @(Get-CimInstance Win32_Process -Filter ("Name='{0}'" -f $n) -ErrorAction SilentlyContinue)
    foreach ($p in $list) {
      $parentName = (Get-CimInstance Win32_Process -Filter ("ProcessId={0}" -f $p.ParentProcessId) -ErrorAction SilentlyContinue | Select-Object -First 1).Name
      $res += [pscustomobject]@{ Name = $n; PID = $p.ProcessId; Parent = $p.ParentProcessId; ParentName = $parentName }
    }
  }
  return $res
}

# ---------- inventory (read-only) ----------
Section 'INVENTORY (nothing is changed yet)'

Write-Host 'Processes:'
$procs = @(Get-NativeProcs)
if ($procs.Count) { $procs | Format-Table Name, PID, Parent, ParentName -AutoSize | Out-String -Width 200 | Write-Host }
else { Write-Host '  (none running)' }

Write-Host ('Directory: ' + $dir)
$files = @()
if (Test-Path $dir) { $files = @(Get-ChildItem -Path $dir -Recurse -Force -ErrorAction SilentlyContinue) }
if ($files.Count) {
  $files | Select-Object @{ n = 'Rel'; e = { $_.FullName.Substring($dir.Length + 1) } }, Length, LastWriteTime |
    Format-Table -AutoSize | Out-String -Width 200 | Write-Host
  Write-Host ('  {0} item(s), {1:N0} bytes total' -f $files.Count, ($files | Measure-Object Length -Sum).Sum)
} else { Write-Host '  (directory missing or empty)' }
if (Test-Path $tmpExe) { Write-Host ('Temp leftover: ' + $tmpExe) -ForegroundColor Yellow }

Write-Host 'Registry keys (HKCU, 8 vendor branches x engine + helper):'
$regFound = @()
foreach ($b in $branches) {
  foreach ($h in $hosts) {
    $k = Join-Path $b $h
    if (Test-Path $k) {
      $v = (Get-ItemProperty -Path $k -ErrorAction SilentlyContinue).'(default)'
      $regFound += [pscustomobject]@{ Key = $k; Value = $v }
    }
  }
}
if ($regFound.Count) { $regFound | Format-Table -AutoSize | Out-String -Width 220 | Write-Host }
else { Write-Host '  (no keys found)' }
foreach ($h in $hosts) {
  $k = 'HKLM:\Software\Google\Chrome\NativeMessagingHosts\' + $h
  if (Test-Path $k) { Write-Host ('  NOTE: HKLM key present (needs admin to delete): ' + $k) -ForegroundColor Yellow }
}

# ---------- ONE confirmation for everything ----------
Write-Host ''
$plan = @()
if (-not $KeepRegistry) { $plan += ('{0} registry key(s)' -f $regFound.Count) }
if (-not $KeepProcesses) { $plan += ('{0} process(es)' -f $procs.Count) }
if (-not $KeepFiles) { $plan += ('{0} item(s) in {1}' -f $files.Count, $dir) }
Write-Host ('Plan: delete ' + $(if ($plan.Count) { $plan -join ', ' } else { 'nothing (all steps skipped)' }))
if (-not $Force -and $plan.Count) { if (-not (Ask 'Proceed with ALL of the above?')) { Write-Host 'Aborted - nothing changed.'; exit 0 } }

# ---------- step 1: registry (FIRST - otherwise the browsers respawn the processes) ----------
if (-not $KeepRegistry) {
  Section 'STEP 1/3 - DELETE REGISTRY KEYS'
  if ($regFound.Count -eq 0) { Write-Host '  nothing to delete' }
  else {
    foreach ($r in $regFound) {
      try { Remove-Item -Path $r.Key -Force -Recurse -ErrorAction Stop; Write-Host ('  deleted ' + $r.Key) -ForegroundColor Green }
      catch { Write-Host ('  FAILED ' + $r.Key + ': ' + $_.Exception.Message) -ForegroundColor Red }
    }
  }
} else { Section 'STEP 1/3 - DELETE REGISTRY KEYS (skipped: -KeepRegistry)' }

# ---------- step 2: processes (re-scan for respawned ones) ----------
if (-not $KeepProcesses) {
  Section 'STEP 2/3 - STOP PROCESSES'
  Write-Host '  NOTE: stopping the engine may leave low-level input hooks dangling for a moment (measured < 1 s).' -ForegroundColor Yellow
  for ($round = 1; $round -le 3; $round++) {
    $list = @(Get-NativeProcs)
    if ($list.Count -eq 0) { break }
    Write-Host ('  round {0}: {1} process(es)' -f $round, $list.Count)
    foreach ($p in $list) {
      try { Stop-Process -Id $p.PID -Force -ErrorAction Stop; Write-Host ('  killed ' + $p.Name + ' PID ' + $p.PID) -ForegroundColor Green }
      catch { Write-Host ('  FAILED ' + $p.Name + ' PID ' + $p.PID + ': ' + $_.Exception.Message) -ForegroundColor Red }
    }
    Start-Sleep -Milliseconds 900
  }
  $left = @(Get-NativeProcs)
  if ($left.Count) {
    Write-Host ('  WARNING: {0} process(es) still running (respawned - registry keys left in place?)' -f $left.Count) -ForegroundColor Yellow
    $left | Format-Table Name, PID, Parent, ParentName -AutoSize | Out-String -Width 200 | Write-Host
  } else { Write-Host '  all stopped' -ForegroundColor Green }
} else { Section 'STEP 2/3 - STOP PROCESSES (skipped: -KeepProcesses)' }

# ---------- step 3: files ----------
if (-not $KeepFiles) {
  Section 'STEP 3/3 - DELETE FILES'
  Start-Sleep -Milliseconds 600   # let the killed processes release their handles
  if (Test-Path $dir) {
    Remove-Item -Path $dir -Recurse -Force -ErrorAction SilentlyContinue
    if (Test-Path $dir) {
      $leftF = @(Get-ChildItem -Path $dir -Recurse -Force -ErrorAction SilentlyContinue)
      Write-Host ('  {0} item(s) could NOT be removed (locked by a running browser?):' -f $leftF.Count) -ForegroundColor Yellow
      $leftF | ForEach-Object { Write-Host ('    ' + $_.FullName) }
      Write-Host '  Close the browsers that run the extension and re-run the script.' -ForegroundColor Yellow
    } else { Write-Host '  directory removed' -ForegroundColor Green }
  } else { Write-Host '  directory already gone' }
  if (Test-Path $tmpExe) {
    Remove-Item -Path $tmpExe -Force -ErrorAction SilentlyContinue
    if (Test-Path $tmpExe) { Write-Host '  FAILED to remove the temp copy' -ForegroundColor Red }
    else { Write-Host '  temp copy removed' -ForegroundColor Green }
  }
} else { Section 'STEP 3/3 - DELETE FILES (skipped: -KeepFiles)' }

# ---------- result ----------
Section 'RESULT'
$leftProcs = @(Get-NativeProcs)
$leftKeys = @()
foreach ($b in $branches) { foreach ($h in $hosts) { if (Test-Path (Join-Path $b $h)) { $leftKeys += (Join-Path $b $h) } } }
$dirGone = -not (Test-Path $dir)

$failed = $false
if (-not $KeepProcesses -and $leftProcs.Count) { $failed = $true }
if (-not $KeepRegistry -and $leftKeys.Count) { $failed = $true }
if (-not $KeepFiles -and -not $dirGone) { $failed = $true }

$procText = if ($KeepProcesses) { 'skipped (-KeepProcesses)' } elseif ($leftProcs.Count) { ($leftProcs | ForEach-Object { $_.Name + '(' + $_.PID + ')' }) -join ', ' } else { 'none' }
$dirText = if ($KeepFiles) { 'kept (-KeepFiles)' } elseif ($dirGone) { 'removed' } else { 'STILL PRESENT (' + $dir + ')' }
$regText = if ($KeepRegistry) { 'skipped (-KeepRegistry)' } elseif ($leftKeys.Count) { ($leftKeys -join ', ') } else { 'clean' }

Write-Host ('  processes : ' + $procText)
Write-Host ('  directory : ' + $dirText)
Write-Host ('  registry  : ' + $regText)
Write-Host ''
Write-Host '  Reminder: the per-profile natHostInstalled flag is NOT touched by this script.'
Write-Host '  Reload or remove the extension in every browser that had it loaded.'

if ($failed) { exit 1 } else { exit 0 }
