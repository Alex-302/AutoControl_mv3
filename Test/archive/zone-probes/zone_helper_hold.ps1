# zone_helper_hold.ps1 - start the zone helper, send one request, keep it alive
# for a few seconds (the smoke test kills it immediately, which leaves no time
# for the heartbeat / engine-table write) and then report.
#
# Usage: powershell -ExecutionPolicy Bypass -File Test\zone_helper_hold.ps1 [-Seconds 4]
param([int]$Seconds = 4, [int]$Requests = 1)
$exe = Join-Path $env:LOCALAPPDATA 'AutoControl\ac_zone_helper.exe'
if (-not (Test-Path $exe)) { Write-Output "no helper at $exe"; exit 1 }
$log = Join-Path $env:TEMP 'ac_zone_helper.log'
Remove-Item $log -ErrorAction SilentlyContinue

$psi = New-Object System.Diagnostics.ProcessStartInfo
$psi.FileName = $exe
$psi.UseShellExecute = $false
$psi.RedirectStandardInput = $true
$psi.RedirectStandardOutput = $true
$psi.RedirectStandardError = $true
$p = [System.Diagnostics.Process]::Start($psi)
Write-Output ("helper pid " + $p.Id)

for ($i = 1; $i -le $Requests; $i++) {
  $msg = '{"__id":' + $i + '}'
  $bytes = [System.Text.Encoding]::UTF8.GetBytes($msg)
  $len = [System.BitConverter]::GetBytes([int]$bytes.Length)
  $p.StandardInput.BaseStream.Write($len, 0, 4)
  $p.StandardInput.BaseStream.Write($bytes, 0, $bytes.Length)
  $p.StandardInput.BaseStream.Flush()
  Start-Sleep -Milliseconds 700
  $lb = New-Object byte[] 4
  $read = $p.StandardOutput.BaseStream.Read($lb, 0, 4)
  if ($read -eq 4) {
    $n = [System.BitConverter]::ToInt32($lb, 0)
    $body = New-Object byte[] $n
    $got = 0
    while ($got -lt $n) { $got += $p.StandardOutput.BaseStream.Read($body, $got, $n - $got) }
    Write-Output ("RESP: " + [System.Text.Encoding]::UTF8.GetString($body))
  } else { Write-Output "no response" }
}

Write-Output "--- alive for $Seconds s (heartbeat should write the engine table) ---"
Start-Sleep -Seconds $Seconds
Write-Output "--- helper log ---"
Get-Content $log -ErrorAction SilentlyContinue | Select-Object -Last 12
$p.Kill()
Write-Output "killed"
