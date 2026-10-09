// Inject Alt+wheel over the omnibox (zone 21 control): hold left Alt,
// move the cursor to the omnibox, wheel, release Alt.
Add-Type @"
using System;
using System.Runtime.InteropServices;
public class AltWheel {
  [DllImport("user32.dll")] public static extern void keybd_event(byte bVk, byte bScan, uint dwFlags, UIntPtr dwExtraInfo);
  [DllImport("user32.dll")] public static extern void mouse_event(uint dwFlags, uint dx, uint dy, uint dwData, UIntPtr dwExtraInfo);
  [DllImport("user32.dll")] public static extern bool SetCursorPos(int x, int y);
}
"@
# left Alt down
[AltWheel]::keybd_event(0x12, 0, 0, [UIntPtr]::Zero)
Start-Sleep -Milliseconds 120
# move to omnibox (from probe: omnibox at x=1855, y=78)
[AltWheel]::SetCursorPos(1855, 78) | Out-Null
Start-Sleep -Milliseconds 800   # hover cache settle
# wheel down x4 (delta -120 = down)
for ($i = 0; $i -lt 4; $i++) {
  [AltWheel]::mouse_event(0x0800, 0, 0, [UInt32](-120 -band 0xFFFFFFFF), [UIntPtr]::Zero)
  Start-Sleep -Milliseconds 150
}
Start-Sleep -Milliseconds 200
# left Alt up
[AltWheel]::keybd_event(0x12, 0, 2, [UIntPtr]::Zero)
Write-Output "alt+wheel x4 @ omnibox (1855,78) injected"
