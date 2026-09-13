<#
.SYNOPSIS
  Deploy the patched native engine (v19 — zone-table mouseOver fix) into
  %LOCALAPPDATA%\AutoControl.

.DESCRIPTION
  Deploy helper for the Chrome 148+ hover-region fix. Safe by default:
    - stops ONLY the Chrome SxS instance (the test browser);
    - kills ONLY orphan engine/Zero processes whose parent is dead —
      a LIVE pair of another browser (stable Chrome, Edge) is never touched;
    - backs up the current engine to AutoCtrl_2025.4.22.0.exe.orig (once);
    - copies the selected build and verifies its SHA-256 on disk.

  Source layout (see AutoControl_native\README.md):
    AutoControl_native\patched\AutoCtrl_2025.4.22.0.v19.exe   [default]
    AutoControl_native\original\*.exe                         pristine input
    AutoControl_native\patches\patch_zones_v19.js             original -> v19

  The default build is the CURRENT one (zone table, sha 1A10EDD1...).
  Rebuild it with:  powershell -File Test\build_native.ps1 -UpdatePatched

  Removed 2026-09-12: the old accName v4 builds and the -Diag/-NoDiag switches
  (those binaries are gone; use -Source + -Force to deploy anything else).

.EXAMPLE
  powershell -ExecutionPolicy Bypass -File Test\deploy_patched_engine.ps1
.EXAMPLE
  powershell -ExecutionPolicy Bypass -File Test\deploy_patched_engine.ps1 -KeepChrome
.EXAMPLE
  powershell -ExecutionPolicy Bypass -File Test\deploy_patched_engine.ps1 -Source C:\path\to\engine.exe -Force
#>
param(
  [switch]$KeepChrome,  # do NOT stop Chrome SxS (use only if you stopped it yourself)
  [switch]$Force,       # deploy even a build with an unknown hash
  [string]$Source = ""  # explicit path to the engine exe to deploy
)

$ErrorActionPreference = 'Stop'
$repo   = Join-Path $PSScriptRoot '..\AutoControl_native'
$destDir = Join-Path $env:LOCALAPPDATA 'AutoControl'
$dest    = Join-Path $destDir 'AutoCtrl_2025.4.22.0.exe'
$ENGINE  = 'AutoCtrl_2025.4.22.0.exe'
$ZERO    = 'AutoControlZero.exe'

# Current build = v19 zone table (AutoControl_native\patched\).
$H_V19 = '1A10EDD191B80A806DF66558B2B1E78BE8D6AD81E93EEAC772D13F222E212C3E'
$H_PRISTINE = '8AE9A669086BEA5C4344007AC4CA9797E5814285E03B6B04E5F8336329CB7E09'

# ---- resolve the source build ----
if (-not $Source) {
  $Source = Join-Path $repo 'patched\AutoCtrl_2025.4.22.0.v19.exe'
}
if (-not (Test-Path $Source)) {
  Write-Error "Source not found: $Source`nBuild it first: powershell -File Test\build_native.ps1 -UpdatePatched"
  exit 1
}
$srcHash = (Get-FileHash $Source -Algorithm SHA256).Hash.ToUpper()

$variant = if ($srcHash -eq $H_V19)      { 'CURRENT v19 (zone table, helper-driven)' }
           elseif ($srcHash -eq $H_PRISTINE) { 'PRISTINE (no zone fix at all!)' }
           else { 'UNKNOWN BUILD' }
if ($variant -eq 'UNKNOWN BUILD' -and -not $Force) {
  Write-Error "Unknown engine build ($($srcHash.Substring(0,16))...). Expected v19 (1A10EDD1...). Use -Force to deploy anyway."
}
Write-Host "Source: $Source" -ForegroundColor Cyan
Write-Host "SHA-256: $srcHash  [$variant]" -ForegroundColor Cyan
Write-Host "Dest:   $dest"

# ---- stop the test browser (Chrome SxS only) ----
if (-not $KeepChrome) {
  $sxs = @(Get-Process chrome -ErrorAction SilentlyContinue | Where-Object { $_.Path -like '*Chrome SxS*' })
  if ($sxs.Count -gt 0) {
    Write-Host "Stopping Chrome SxS ($($sxs.Count) process(es))..."
    $sxs | Stop-Process -Force -ErrorAction SilentlyContinue
    Start-Sleep -Seconds 2
  } else {
    Write-Host "Chrome SxS not running."
  }
} else {
  Write-Host "KeepChrome: skipping the SxS stop (make sure no SxS process holds the engine)."
}

# ---- kill orphan Zero/engine pairs (live pairs of other browsers are kept) ----
function Get-Cim([string]$n) {
  try { @(Get-CimInstance Win32_Process -Filter "Name='$n'" -ErrorAction Stop) } catch { @() }
}
function Get-AlivePids { @(Get-Process -ErrorAction SilentlyContinue | ForEach-Object { $_.Id }) }

for ($i = 0; $i -lt 6; $i++) {
  $engs  = @(Get-Cim $ENGINE)
  $zeros = @(Get-Cim $ZERO)
  if ($engs.Count -eq 0 -and $zeros.Count -eq 0) { break }
  $alive    = Get-AlivePids
  $zeroPids = @{}; foreach ($z in $zeros) { $zeroPids[[int]$z.ProcessId] = $true }
  $killed = $false
  foreach ($e in $engs) {
    if (-not $zeroPids.ContainsKey([int]$e.ParentProcessId)) {
      Write-Host "Killing orphan engine pid=$($e.ProcessId) (Zero parent $($e.ParentProcessId) dead)"
      taskkill /F /PID $e.ProcessId 2>$null | Out-Null; $killed = $true
    }
  }
  foreach ($z in $zeros) {
    if ($alive -notcontains [int]$z.ParentProcessId) {
      Write-Host "Killing orphan Zero pid=$($z.ProcessId) (parent $($z.ParentProcessId) gone)"
      taskkill /F /PID $z.ProcessId 2>$null | Out-Null; $killed = $true
    }
  }
  if (-not $killed) { break }
  Start-Sleep -Milliseconds 800
}
$left = @(Get-Cim $ENGINE).Count
if ($left -gt 0) {
  Write-Host "WARN: $left engine process(es) still running (likely belong to another browser — left alive)." -ForegroundColor Yellow
}

# ---- backup + copy + verify ----
if (Test-Path $dest) {
  $orig = "$dest.orig"
  if (-not (Test-Path $orig)) {
    Copy-Item $dest $orig -Force
    Write-Host "Backed up the previous engine -> $orig"
  } else {
    Write-Host "Backup $orig already exists (kept as-is)"
  }
}
Copy-Item $Source $dest -Force
$dHash = (Get-FileHash $dest -Algorithm SHA256).Hash.ToUpper()
if ($dHash -eq $srcHash) {
  Write-Host "DEPLOYED OK: $dest" -ForegroundColor Green
} else {
  Write-Host "HASH MISMATCH on disk: $dHash" -ForegroundColor Red
  exit 1
}

# ---- next steps ----
Write-Host ""
Write-Host "Next steps:" -ForegroundColor Cyan
Write-Host '  1. Relaunch Chrome SxS with CDP:'
Write-Host '     Start-Process "$env:LOCALAPPDATA\Google\Chrome SxS\Application\chrome.exe" -ArgumentList ''--remote-debugging-port=9223'', "--user-data-dir=`"$env:LOCALAPPDATA\Google\Chrome SxS\User Data CDP`"", ''--lang=en-US'''
Write-Host "  2. Verify the engine answers:  node Test/cdp_native_check.js 9223   (expect pong)"
Write-Host "  3. Reload the extension:       node Test/cdp_ext_reload.js"
Write-Host '  4. Zone check:                 node Test/zone_probe.ps1 -Point 700,90   (expect the'
Write-Host '     omnibox/helper answer) and a known-good control: wheel over the tab strip.'
Write-Host ""
Write-Host "Rollback: copy `${dest}.orig back to ${dest} (no rebuild needed)."
