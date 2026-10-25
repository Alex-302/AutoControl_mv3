# build_native.ps1 - reproduce BOTH native components bit-for-bit.
#
#   engine : AutoCtrl_2025.4.22.0.v19.exe <- AutoControl_native/original/ +
#                                             AutoControl_native/patches/patch_zones_v19.js
#   helper : ac_zone_helper.exe           <- Test/ac_zone_helper.cs (our own source)
#   bundle : mv3-build/file76.dat         <- encode(engine) via Test/dat_codec.js
#            mv3-build/ac_zone_helper.dat <- encode(helper) via Test/dat_codec.js
#                                            (the payloads the extension deploys)
#
# Nothing is installed: the script only BUILDS into -OutDir and verifies the
# SHA-256/MD5 of every output. Deploy with Test/deploy_patched_engine.ps1 (engine),
# the copy steps in Docs/BUILD-NATIVE.md section A.5 (helper) or -UpdateBundle
# (the bundled engine payload).
#
# Usage:
#   powershell -ExecutionPolicy Bypass -File Test/build_native.ps1
#   powershell -ExecutionPolicy Bypass -File Test/build_native.ps1 -OutDir C:\build
#   powershell -ExecutionPolicy Bypass -File Test/build_native.ps1 -UpdatePatched
#     ... also refresh AutoControl_native/patched/ with the freshly built engine
#   powershell -ExecutionPolicy Bypass -File Test/build_native.ps1 -UpdateBundle
#     ... also refresh mv3-build/file76.dat + ac_zone_helper.dat with the fresh payloads
#
# See Docs/BUILD-NATIVE.md for the full explanation of every byte.
param(
  [string]$OutDir = "$env:TEMP\ac_rebuild",
  [switch]$UpdatePatched,
  [switch]$UpdateBundle
)

$ErrorActionPreference = 'Stop'
$repo = Split-Path -Parent $PSScriptRoot
Set-Location $repo

$EXPECT_ENGINE = '1A10EDD191B80A806DF66558B2B1E78BE8D6AD81E93EEAC772D13F222E212C3E'
# 2026-09-13: the helper now binds to the engine of ITS OWN browser (window-list
# check in EngineIsMine) - the old rule "first engine pid" made both helpers
# write into the same engine when two browsers ran (the other browser's engine
# kept the always-match fallback -> "wheel over the page switches tabs").
# 2026-09-15: Opera/Vivaldi support - docDepth fix (Vivaldi keeps its whole UI
# inside the page DOCUMENT), tabs found deeper (d0..d3), browser-menu button
# found BY NAME (Opera's "Menu" / Vivaldi's "Menu", left side).
# 2026-09-20: TITLE AREA (4) narrowed to the title bar / tab strip row only
# (the UI description "When the mouse is over the title bar or tab strip") -
# the toolbar and the omnibox are no longer part of it (user correction),
# and the Opera-style title row (a role-20 container WITHOUT a toolbar, which
# holds the tab-search button and the window controls) is included too.
# Same day: "Browser tab" (12) requires a real PAGETAB (role 37) - the empty
# strip area (60 alone) and the "+" no longer answer 12 (the engine's own
# region-12 check FUN_00415570 matched only a PAGETAB or its direct child),
# and the BOOKMARK zone (33) requires the omnibox GROUPING to sit BETWEEN the
# button and the toolbar - Opera's window-contents container (20) sits ABOVE
# the toolbar, so every Opera toolbar button used to answer 33; Opera's own
# bookmark button (the heart) is matched BY NAME ('Add to bookmarks' /
# 'Edit bookmark', Russian via a unicode escape).
# 2026-10-18: the helper's diagnostic log is now OPT-IN - nothing is written
# unless a marker file `ac_zone_helper.debug` sits next to the exe (the
# deployed copy is in %LOCALAPPDATA%\AutoControl\). With the marker every
# write is logged unchanged, repeats included. Zone/protocol behaviour is
# unchanged; only the %TEMP%\ac_zone_helper.log output differs.
# 2026-10-25: the engine zone table is INVALIDATED while the cursor moves - the
# heartbeat writes a provisional set ([1] over our own browser, empty
# elsewhere) through a fast path (cached engine handle, no process scan) as
# soon as the cursor is >3 px from the point the table was built for, and the
# poll dropped from 30 ms to 10 ms. Fixes "a wheel action bound to Browser tab
# fired when the cursor was already over the page" (the engine read a table
# that still said zone 12). Engine patch, cave bytes and file76.dat unchanged.
# Review follow-up (same day): the provisional decision + write and the real
# classification's table write + provOk reset + cache store are serialised by
# engLock (order engLock -> zoneLock), so a provisional [1] can never overwrite
# a real zone set that was just written (that left zone triggers dead until the
# next move / the 1.2 s tree refresh).
# Live test (same day): a classification whose MSAA walk outlived the point it
# was sampled at is DISCARDED - it used to write the real set for a point the
# cursor had LEFT, over the provisional [1] (user log: real [12,4,1] at 42.007,
# provisional [1] at 42.024), and the engine fired the scoped "Browser tab"
# combo over the page. The stale path publishes a provisional table for the
# CURRENT point, the slow write re-samples the cursor right before WriteMem,
# and the steady-state real write uses the cached engine handle (re-bind every
# 1000 ms) so engLock is no longer held during the process/module scan.
# Review follow-up (same day): only a successful SLOW bind/refresh moves
# lastBindAt - resetting it in the fast branch made the re-bind window never
# expire, so the periodic re-bind (and with it the engine-restart / multi-engine
# re-validation) never ran.
# Live test, second round (same day): the SLOW DISCOVERY (FindEnginePids /
# EngineIsMine / ModuleBaseOf / cave claim) no longer holds engLock - it took
# ~928 ms under load and blocked the heartbeat's provisional invalidation for
# that long (user log: real [12,4,1] at 42.343, provisional [1] at 43.271).
# Discovery + publish are one bindLock sequence (order bindLock -> engLock) and
# the publish takes engLock only for the install + page write. A fresh page is
# initialised to alive=1/empty before the cave points at it.
$EXPECT_HELPER = '30D11271066F2BFF19237A10DDC89DB6E9C84CB627DC719E8DABBE8E2834961F'
# The bundled engine payload (mv3-build/file76.dat): MD5 of the ENCODED blob
# (the README table quotes this form). The decoded content must equal the
# patched engine ($EXPECT_ENGINE) byte-for-byte - step 3/3 proves both.
$EXPECT_DAT_MD5 = '2F878E9EB062C57D8B5C7FFBC91EAB5D'
$PRISTINE_SHA  = '8AE9A669086BEA5C4344007AC4CA9797E5814285E03B6B04E5F8336329CB7E09'
# Pristine input: the repo copy first (clean checkout works), the deployed
# backup as fallback (that is where the recipe used to read from).
$PRISTINE_REPO = Join-Path $repo 'AutoControl_native\original\AutoCtrl_2025.4.22.0.exe'
$PRISTINE_DEP  = Join-Path $env:LOCALAPPDATA 'AutoControl\AutoCtrl_2025.4.22.0.exe.orig-pristine'
$PRISTINE      = if (Test-Path $PRISTINE_REPO) { $PRISTINE_REPO } else { $PRISTINE_DEP }
$PATCHER       = Join-Path $repo 'AutoControl_native\patches\patch_zones_v19.js'
$PATCHED_REPO  = Join-Path $repo 'AutoControl_native\patched\AutoCtrl_2025.4.22.0.v19.exe'
$CODEC         = Join-Path $repo 'Test\dat_codec.js'
$DAT_REPO      = Join-Path $repo 'mv3-build\file76.dat'
$HLP_DAT_REPO  = Join-Path $repo 'mv3-build\ac_zone_helper.dat'
$FRAMEWORK     = "$env:WINDIR\Microsoft.NET\Framework64\v4.0.30319"

New-Item -ItemType Directory -Force $OutDir | Out-Null
$engOut = Join-Path $OutDir 'AutoCtrl_2025.4.22.0.exe'
$hlpOut = Join-Path $OutDir 'ac_zone_helper.exe'      # NOTE: the NAME is part of
                                                      # Roslyn's deterministic hash
$datOut = Join-Path $OutDir 'file76.dat'
$hlpDatOut = Join-Path $OutDir 'ac_zone_helper.dat'
$fail = 0
$engineOk = $false
$helperOk = $false

function Report($what, $path, $expected) {
  if (-not (Test-Path $path)) { Write-Host ("  {0,-8} MISSING" -f $what); $script:fail++; return }
  $sha  = (Get-FileHash $path -Algorithm SHA256).Hash
  $size = (Get-Item $path).Length
  $ok   = ($sha -eq $expected)
  if (-not $ok) { $script:fail++ }
  $short  = $sha.Substring(0, 24) + '...'
  $verdict = if ($ok) { 'OK' } else { 'MISMATCH (expected ' + $expected.Substring(0, 24) + '...)' }
  Write-Host ("  {0,-8} {1,8} bytes  {2}  {3}" -f $what, $size, $short, $verdict)
}

Write-Host '=== 1/3  ENGINE (original + byte patch) ==='
if (-not (Test-Path $PRISTINE)) {
  Write-Host "  pristine not found: $PRISTINE"
  Write-Host '  (the repo copy is AutoControl_native\original\AutoCtrl_2025.4.22.0.exe)'
  $fail++
} else {
  $psha = (Get-FileHash $PRISTINE -Algorithm SHA256).Hash
  $pverdict = if ($psha -eq $PRISTINE_SHA) { 'OK' } else { 'NOT PRISTINE!' }
  Write-Host ("  source   {0}" -f $PRISTINE)
  Write-Host ("           {0}  {1}" -f ($psha.Substring(0, 24) + '...'), $pverdict)
  if ($psha -ne $PRISTINE_SHA) { $fail++ } else {
    node $PATCHER $engOut | Out-Null
    Report 'engine' $engOut $EXPECT_ENGINE
    if (Test-Path $engOut) {
      $engineOk = ((Get-FileHash $engOut -Algorithm SHA256).Hash -eq $EXPECT_ENGINE)
    }
    if ($UpdatePatched -and $engineOk) {
      Copy-Item $engOut $PATCHED_REPO -Force
      Write-Host ("           refreshed {0}" -f $PATCHED_REPO)
    } elseif ($UpdatePatched) { Write-Host '           -UpdatePatched skipped: build hash mismatch'; $fail++ }
  }
}

Write-Host '=== 2/3  HELPER (our C# source) ==='
$roslyn = Get-ChildItem "$env:ProgramFiles\dotnet\sdk\*\Roslyn\bincore\csc.dll" -ErrorAction SilentlyContinue |
          Sort-Object FullName -Descending | Select-Object -First 1
if (-not $roslyn) {
  Write-Host '  Roslyn csc.dll not found (install the .NET SDK: winget install Microsoft.DotNet.SDK.8)'
  $fail++
} else {
  Write-Host ("  compiler {0}" -f $roslyn.FullName)
  Remove-Item $hlpOut -Force -ErrorAction SilentlyContinue
  dotnet $roslyn.FullName /nologo /optimize+ /deterministic+ /nostdlib+ `
    /r:"$FRAMEWORK\mscorlib.dll" /r:"$FRAMEWORK\System.dll" /r:"$FRAMEWORK\Accessibility.dll" `
    /out:"$hlpOut" Test\ac_zone_helper.cs
  Report 'helper' $hlpOut $EXPECT_HELPER
  if (Test-Path $hlpOut) {
    $helperOk = ((Get-FileHash $hlpOut -Algorithm SHA256).Hash -eq $EXPECT_HELPER)
  }
}

Write-Host '=== 3/3  BUNDLE (mv3-build/file76.dat + ac_zone_helper.dat) ==='
if (-not $engineOk) {
  Write-Host '  skipped: the engine did not build'
  $fail++
} else {
  # encode the freshly built engine and verify the blob bit-for-bit
  node $CODEC encode $engOut $datOut | Out-Null
  $datMd5 = (Get-FileHash $datOut -Algorithm MD5).Hash
  $datOk  = ($datMd5 -eq $EXPECT_DAT_MD5)
  if (-not $datOk) { $fail++ }
  Write-Host ("  encoded  {0,8} bytes  md5 {1}  {2}" -f (Get-Item $datOut).Length, $datMd5, $(if ($datOk) { 'OK' } else { 'MISMATCH (expected ' + $EXPECT_DAT_MD5 + ')' }))
  # the REPO bundle must decode to the patched engine and carry the same md5
  if (-not (Test-Path $DAT_REPO)) {
    Write-Host "  repo bundle missing: $DAT_REPO"; $fail++
  } else {
    node $CODEC verify $DAT_REPO --exe $PATCHED_REPO --sha256 $EXPECT_ENGINE --dat-md5 $EXPECT_DAT_MD5
    if ($LASTEXITCODE -ne 0) { Write-Host '  repo bundle verification FAILED'; $fail++ }
  }
  if ($UpdateBundle) {
    if ($datOk) {
      Copy-Item $datOut $DAT_REPO -Force
      Write-Host ("  refreshed {0}" -f $DAT_REPO)
    } else { Write-Host '  -UpdateBundle skipped: encoded md5 mismatch'; $fail++ }
  }
}
# the helper payload is derived from the helper build (no extra hash constant:
# decode(ac_zone_helper.dat) must equal the deterministic helper exe)
if ($helperOk) {
  node $CODEC encode $hlpOut $hlpDatOut | Out-Null
  if (-not (Test-Path $HLP_DAT_REPO)) {
    Write-Host "  repo helper payload missing: $HLP_DAT_REPO"; $fail++
  } else {
    node $CODEC verify $HLP_DAT_REPO --exe (Join-Path $repo 'AutoControl_native\ac_zone_helper.exe') --sha256 $EXPECT_HELPER
    if ($LASTEXITCODE -ne 0) { Write-Host '  repo helper payload verification FAILED'; $fail++ }
  }
  if ($UpdateBundle) {
    Copy-Item $hlpDatOut $HLP_DAT_REPO -Force
    Write-Host ("  refreshed {0}" -f $HLP_DAT_REPO)
  }
} else {
  Write-Host '  helper payload: skipped (helper did not build)'
}

Write-Host ''
if ($fail -eq 0) {
  Write-Host 'RESULT: both components + the bundled engine payload reproduced bit-for-bit.'
  Write-Host 'Deploy: test the helper first (node Test/zone_helper_smoke.js <helper>), then'
  Write-Host '        follow Docs/BUILD-NATIVE.md section A.5 (helper) / B.7 (engine).'
} else {
  Write-Host "RESULT: $fail problem(s) - see the lines above."
  exit 1
}
