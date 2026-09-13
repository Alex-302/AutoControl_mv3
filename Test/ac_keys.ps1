# ac_keys.ps1 - inject a key combination via keybd_event (goes through the
# native low-level hooks, like a real key press).
#
# Usage:
#   powershell -ExecutionPolicy Bypass -File Test\ac_keys.ps1 -Combo "ctrl+m"
#   powershell -ExecutionPolicy Bypass -File Test\ac_keys.ps1 -Combo "alt+e77"
#   (vk numbers may be given directly: "162+77" = Ctrl + 'M')
param(
  [string]$Combo = "ctrl+m",
  [int]$HoldMs = 80,
  [int]$AfterMs = 150,
  [switch]$NoForeground
)

Add-Type @"
using System;
using System.Runtime.InteropServices;
public class ACKeys {
  [DllImport("user32.dll")] public static extern void keybd_event(byte vk, byte scan, uint flags, UIntPtr extra);
  [DllImport("user32.dll")] public static extern bool SetForegroundWindow(IntPtr h);
  [DllImport("user32.dll")] public static extern IntPtr GetForegroundWindow();
}
"@

$map = @{ 'ctrl' = 0x11; 'shift' = 0x10; 'alt' = 0x12; 'win' = 0x5B; 'tab' = 0x09; 'esc' = 0x1B; 'enter' = 0x0D; 'space' = 0x20 }
$parts = $Combo.Split('+') | ForEach-Object { $_.Trim().ToLower() }
$vks = @()
foreach ($p in $parts) {
  if ($p -match '^e\d+$') { $vks += [int]$p.Substring(1) }
  elseif ($map.ContainsKey($p)) { $vks += $map[$p] }
  elseif ($p -match '^[a-z]$') { $vks += [int][char]([char]::ToUpper($p)) }
  elseif ($p -match '^\d+$') { $vks += [int]$p }
  else { Write-Output "unknown key token '$p'"; exit 1 }
}

if (-not $NoForeground) {
  $proc = Get-Process chrome | Where-Object { $_.Path -like '*Chrome SxS*' -and $_.MainWindowHandle -ne 0 } | Select-Object -First 1
  if ($proc) {
    for ($i = 0; $i -lt 5; $i++) {
      [ACKeys]::keybd_event(0x12, 0, 0, [UIntPtr]::Zero)
      Start-Sleep -Milliseconds 50
      [void][ACKeys]::SetForegroundWindow($proc.MainWindowHandle)
      Start-Sleep -Milliseconds 120
      [ACKeys]::keybd_event(0x12, 0, 2, [UIntPtr]::Zero)
      Start-Sleep -Milliseconds 250
      if ([ACKeys]::GetForegroundWindow() -eq $proc.MainWindowHandle) { break }
    }
  }
}

foreach ($vk in $vks) { [ACKeys]::keybd_event([byte]$vk, 0, 0, [UIntPtr]::Zero); Start-Sleep -Milliseconds 40 }
Start-Sleep -Milliseconds $HoldMs
for ($i = $vks.Count - 1; $i -ge 0; $i--) { [ACKeys]::keybd_event([byte]$vks[$i], 0, 2, [UIntPtr]::Zero); Start-Sleep -Milliseconds 40 }
Start-Sleep -Milliseconds $AfterMs
Write-Output ("OK keys " + ($vks -join '+'))
