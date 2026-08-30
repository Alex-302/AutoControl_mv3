# Single quick Tab tap (down+up, 120ms) — for moving the menu mark.
Add-Type -AssemblyName Microsoft.VisualBasic
Add-Type @"
using System;
using System.Runtime.InteropServices;
public class ACTabTap {
  [DllImport("user32.dll")] public static extern void keybd_event(byte bVk, byte bScan, uint dwFlags, UIntPtr dwExtraInfo);
}
"@
[ACTabTap]::keybd_event(0x09, 0, 0, [UIntPtr]::Zero)
Start-Sleep -Milliseconds 120
[ACTabTap]::keybd_event(0x09, 0, 2, [UIntPtr]::Zero)
Write-Output "OK tab tap"
