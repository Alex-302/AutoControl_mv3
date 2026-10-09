param(
  [string]$Action = "rmb",   # rmb = right-button click | lmb = left click | move = move mouse to x,y | wheel = scroll
  [int]$X = -1,              # move target x (absolute screen)
  [int]$Y = -1,              # move target y
  [int]$HoldMs = 120,        # down→up gap
  [int]$DragPx = 0,          # move the mouse this many px (to the right) BETWEEN down and up (gesture start)
  [int]$DragSteps = 1,       # how many steps the drag is split into (smooth hand-like movement)
  [int]$Delta = 120,         # wheel delta: 120 = up, -120 = down
  [int]$Ticks = 1,           # how many wheel notches
  [string]$TitleFilter = "sxs"  # pick the Chrome SxS window whose title CONTAINS this (excludes the settings/extension windows)
)
Add-Type -AssemblyName Microsoft.VisualBasic
Add-Type @"
using System;
using System.Runtime.InteropServices;
public class ACMouse {
  [DllImport("user32.dll")] public static extern void mouse_event(uint dwFlags, uint dx, uint dy, uint dwData, UIntPtr dwExtraInfo);
  [DllImport("user32.dll")] public static extern void keybd_event(byte bVk, byte bScan, uint dwFlags, UIntPtr dwExtraInfo);
  [DllImport("user32.dll")] public static extern bool SetCursorPos(int x, int y);
  [DllImport("user32.dll")] public static extern bool SetForegroundWindow(IntPtr hWnd);
  [DllImport("user32.dll")] public static extern IntPtr GetForegroundWindow();
  [DllImport("user32.dll")] public static extern bool GetCursorPos(out POINT lpPoint);
  public struct POINT { public int X; public int Y; }
}
"@
$proc = Get-Process chrome | Where-Object { $_.Path -like '*Chrome SxS*' -and $_.MainWindowHandle -ne 0 -and $_.MainWindowTitle -like "*$TitleFilter*" } | Sort-Object MainWindowTitle | Select-Object -Last 1
if (-not $proc) {
  # fallback: any SxS window with a title (the tab title changes constantly)
  $proc = Get-Process chrome | Where-Object { $_.Path -like '*Chrome SxS*' -and $_.MainWindowHandle -ne 0 -and $_.MainWindowTitle -ne "" } | Sort-Object MainWindowTitle | Select-Object -Last 1
}
if (-not $proc) { Write-Output "NO SXS WINDOW (filter=$TitleFilter)"; exit 1 }
# Foreground the SxS window (verify + retry): the ALT-hold unlocks the
# Windows foreground lock (the caller is not the foreground owner).
$fg = 0
for ($i = 0; $i -lt 5 -and $fg -ne $proc.MainWindowHandle; $i++) {
  try { [Microsoft.VisualBasic.Interaction]::AppActivate($proc.Id) } catch {}
  Start-Sleep -Milliseconds 250
  [ACMouse]::keybd_event(0x12, 0, 0, [UIntPtr]::Zero)
  Start-Sleep -Milliseconds 60
  [ACMouse]::SetForegroundWindow($proc.MainWindowHandle) | Out-Null
  Start-Sleep -Milliseconds 120
  [ACMouse]::keybd_event(0x12, 0, 2, [UIntPtr]::Zero)
  Start-Sleep -Milliseconds 350
  $fg = [ACMouse]::GetForegroundWindow()
}
if ($fg -ne $proc.MainWindowHandle) { Write-Output "FG FAIL (got $fg)"; exit 2 }
Write-Output "fg OK ($fg)"

if ($Action -eq "move") {
  if ($X -lt 0 -or $Y -lt 0) { Write-Output "need X,Y for move"; exit 1 }
  [ACMouse]::SetCursorPos($X, $Y) | Out-Null
  Write-Output "OK moved to $X,$Y"
  exit 0
}

$p = New-Object ACMouse+POINT
[ACMouse]::GetCursorPos([ref]$p) | Out-Null
Write-Output "cursor at $($p.X),$($p.Y) -> $Action"

if ($Action -eq "wheel") {
  # mouse_event's dwData is a DWORD: a negative delta (wheel down) must be
  # sent in its two's-complement form ([uint32]-120 throws in PS 5.1).
  $dw = [BitConverter]::ToUInt32([BitConverter]::GetBytes([int]$Delta), 0)
  for ($i = 0; $i -lt $Ticks; $i++) {
    [ACMouse]::mouse_event(0x0800, 0, 0, $dw, [UIntPtr]::Zero)  # MOUSEEVENTF_WHEEL
    Start-Sleep -Milliseconds 40
  }
  Write-Output "OK wheel delta=$Delta ticks=$Ticks"
  exit 0
} elseif ($Action -eq "rmb") {
  [ACMouse]::mouse_event(0x0008, 0, 0, 0, [UIntPtr]::Zero)  # RIGHTDOWN
  if ($DragPx -gt 0) {
    $p2 = New-Object ACMouse+POINT
    [ACMouse]::GetCursorPos([ref]$p2) | Out-Null
    $steps = [Math]::Max(1, $DragSteps)
    $stepPx = $DragPx / $steps
    for ($s = 1; $s -le $steps; $s++) {
      Start-Sleep -Milliseconds ([Math]::Max(15, [int]($HoldMs / $steps)))
      [ACMouse]::SetCursorPos(($p2.X + [int]($stepPx * $s)), $p2.Y) | Out-Null
    }
  } else {
    Start-Sleep -Milliseconds $HoldMs
  }
  [ACMouse]::mouse_event(0x0010, 0, 0, 0, [UIntPtr]::Zero)  # RIGHTUP
} elseif ($Action -eq "lmb") {
  [ACMouse]::mouse_event(0x0002, 0, 0, 0, [UIntPtr]::Zero)  # LEFTDOWN
  Start-Sleep -Milliseconds $HoldMs
  [ACMouse]::mouse_event(0x0004, 0, 0, 0, [UIntPtr]::Zero)  # LEFTUP
} else { Write-Output "unknown action"; exit 1 }
Write-Output "OK $Action done"
