# build_native.ps1 - reproduce BOTH native components bit-for-bit.
#
#   engine : AutoCtrl_2025.4.22.0.v19.exe <- AutoControl_native/original/ +
#                                             AutoControl_native/patches/patch_zones_v19.js
#   helper : ac_zone_helper.exe           <- Test/ac_zone_helper.cs (our own source)
#
# Nothing is installed: the script only BUILDS into -OutDir and verifies the
# SHA-256 of every output. Deploy with Test/deploy_patched_engine.ps1 (engine)
# and the copy steps in Docs/BUILD-NATIVE.md section A.5 (helper).
#
# Usage:
#   powershell -ExecutionPolicy Bypass -File Test/build_native.ps1
#   powershell -ExecutionPolicy Bypass -File Test/build_native.ps1 -OutDir C:\build
#   powershell -ExecutionPolicy Bypass -File Test/build_native.ps1 -UpdatePatched
#     ... also refresh AutoControl_native/patched/ with the freshly built engine
#
# See Docs/BUILD-NATIVE.md for the full explanation of every byte.
param(
  [string]$OutDir = "$env:TEMP\ac_rebuild",
  [switch]$UpdatePatched
)

$ErrorActionPreference = 'Stop'
$repo = Split-Path -Parent $PSScriptRoot
Set-Location $repo

$EXPECT_ENGINE = '1A10EDD191B80A806DF66558B2B1E78BE8D6AD81E93EEAC772D13F222E212C3E'
$EXPECT_HELPER = '6988B49BCBEC162CE03EFDC94F789F17AFC28C98EC890E7B26FCF0E464F262E6'
$PRISTINE_SHA  = '8AE9A669086BEA5C4344007AC4CA9797E5814285E03B6B04E5F8336329CB7E09'
# Pristine input: the repo copy first (clean checkout works), the deployed
# backup as fallback (that is where the recipe used to read from).
$PRISTINE_REPO = Join-Path $repo 'AutoControl_native\original\AutoCtrl_2025.4.22.0.exe'
$PRISTINE_DEP  = Join-Path $env:LOCALAPPDATA 'AutoControl\AutoCtrl_2025.4.22.0.exe.orig-pristine'
$PRISTINE      = if (Test-Path $PRISTINE_REPO) { $PRISTINE_REPO } else { $PRISTINE_DEP }
$PATCHER       = Join-Path $repo 'AutoControl_native\patches\patch_zones_v19.js'
$PATCHED_REPO  = Join-Path $repo 'AutoControl_native\patched\AutoCtrl_2025.4.22.0.v19.exe'
$FRAMEWORK     = "$env:WINDIR\Microsoft.NET\Framework64\v4.0.30319"

New-Item -ItemType Directory -Force $OutDir | Out-Null
$engOut = Join-Path $OutDir 'AutoCtrl_2025.4.22.0.exe'
$hlpOut = Join-Path $OutDir 'ac_zone_helper.exe'      # NOTE: the NAME is part of
                                                      # Roslyn's deterministic hash
$fail = 0

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

Write-Host '=== 1/2  ENGINE (original + byte patch) ==='
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
    if ($UpdatePatched -and (Test-Path $engOut)) {
      $built = (Get-FileHash $engOut -Algorithm SHA256).Hash
      if ($built -eq $EXPECT_ENGINE) {
        Copy-Item $engOut $PATCHED_REPO -Force
        Write-Host ("           refreshed {0}" -f $PATCHED_REPO)
      } else { Write-Host '           -UpdatePatched skipped: build hash mismatch'; $fail++ }
    } elseif ($UpdatePatched) { $fail++ }
  }
}

Write-Host '=== 2/2  HELPER (our C# source) ==='
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
}

Write-Host ''
if ($fail -eq 0) {
  Write-Host 'RESULT: both components reproduced bit-for-bit.'
  Write-Host 'Deploy: test them first (node Test/zone_helper_smoke.js <helper>) and then'
  Write-Host '        follow Docs/BUILD-NATIVE.md section A.5 (helper) / B.7 (engine).'
} else {
  Write-Host "RESULT: $fail problem(s) - see the lines above."
  exit 1
}
