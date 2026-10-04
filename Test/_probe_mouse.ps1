# Temporary probe (2026-09-20): minimal mouse injector for a NON-Chrome window
# (the shared _ac_mouse.ps1 / zone_fg_wheel.ps1 hardcode Chrome SxS and use the
# ALT-hold foreground trick, which OPENS THE OPERA MENU and therefore changes
# the zone answer under the cursor). This one never touches the keyboard.
# Usage:
#   powershell -NoProfile -File Test/_probe_mouse.ps1 -Action move  -X 370 -Y 560
#   powershell -NoProfile -File Test/_probe_mouse.ps1 -Action lmb   -X 800 -Y 900
#   powershell -NoProfile -File Test/_probe_mouse.ps1 -Action wheel -X 370 -Y 560 -Ticks 1 -Delta -120
param(
  [string]$Action = "move",
  [int]$X = 0, [int]$Y = 0,
  [int]$Ticks = 1,
  [int]$Delta = -120,
  [int]$HoldMs = 90
)
Add-Type @"
using System;
using System.Runtime.InteropServices;
public class Pm {
  [DllImport("user32.dll")] public static extern bool SetProcessDPIAware();
  [DllImport("user32.dll")] public static extern bool SetCursorPos(int x, int y);
  [DllImport("user32.dll")] public static extern void mouse_event(uint f, uint dx, uint dy, uint data, UIntPtr extra);
}
"@
# DPI-AWARE (2026-09-20): WITHOUT this, SetCursorPos takes LOGICAL coordinates
# and the OS scales them - the cursor landed at 1.5x the requested point on
# this 150% display, so every probe silently measured a different spot (the
# "fresh helper answers zone 3" red herring).
try { [void][Pm]::SetProcessDPIAware() } catch {}
[Pm]::SetCursorPos($X, $Y) | Out-Null
Start-Sleep -Milliseconds 250
switch ($Action) {
  "move"  { "moved to $X,$Y" }
  "lmb"   { [Pm]::mouse_event(0x0002, 0, 0, 0, [UIntPtr]::Zero); Start-Sleep -Milliseconds $HoldMs
            [Pm]::mouse_event(0x0004, 0, 0, 0, [UIntPtr]::Zero); "lmb at $X,$Y" }
  "rmb"   { [Pm]::mouse_event(0x0008, 0, 0, 0, [UIntPtr]::Zero); Start-Sleep -Milliseconds $HoldMs
            [Pm]::mouse_event(0x0010, 0, 0, 0, [UIntPtr]::Zero); "rmb at $X,$Y" }
  "wheel" {
    $d = [BitConverter]::ToUInt32([BitConverter]::GetBytes([int]$Delta), 0)
    for ($i = 0; $i -lt $Ticks; $i++) {
      [Pm]::mouse_event(0x0800, 0, 0, $d, [UIntPtr]::Zero)
      Start-Sleep -Milliseconds 120
    }
    "wheel $Ticks x $Delta at $X,$Y"
  }
  default { "unknown action $Action" }
}
