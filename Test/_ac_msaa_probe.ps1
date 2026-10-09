Add-Type -ReferencedAssemblies Accessibility @"
using System;
using System.Text;
using System.Runtime.InteropServices;
using Accessibility;
public class Probe4 {
  [DllImport("user32.dll")] public static extern IntPtr WindowFromPoint(POINT pt);
  [DllImport("user32.dll")] public static extern int GetClassName(IntPtr h, StringBuilder sb, int max);
  [DllImport("user32.dll")] public static extern bool GetWindowRect(IntPtr h, out RECT r);
  [DllImport("oleacc.dll")] public static extern int AccessibleObjectFromPoint(POINT pt, out IAccessible acc, out object varChild);
  [DllImport("user32.dll")] public static extern bool SetForegroundWindow(IntPtr h);
  [DllImport("user32.dll")] public static extern void keybd_event(byte vk, byte scan, uint flags, UIntPtr extra);
  [StructLayout(LayoutKind.Sequential)] public struct POINT { public int x; public int y; }
  [StructLayout(LayoutKind.Sequential)] public struct RECT { public int l, t, r, b; }
  public static string Cls(IntPtr h) { if (h == IntPtr.Zero) return "(null)"; var sb = new StringBuilder(256); GetClassName(h, sb, 256); return sb.ToString(); }
}
"@
$win = [IntPtr]1595456
# foreground unlock: ALT-hold + SetForegroundWindow
[Probe4]::keybd_event(0x12, 0, 0, [UIntPtr]::Zero); Start-Sleep -Milliseconds 60
[Probe4]::SetForegroundWindow($win) | Out-Null
Start-Sleep -Milliseconds 120
[Probe4]::keybd_event(0x12, 0, 2, [UIntPtr]::Zero)
Start-Sleep -Milliseconds 500
$pts = @(@{n="titlebar"; x=300; y=10}, @{n="tabstrip"; x=300; y=45}, @{n="page"; x=300; y=400}, @{n="page2"; x=700; y=700})
foreach ($p in $pts) {
  $pt = New-Object Probe4+POINT; $pt.x = $p.x; $pt.y = $p.y
  $h = [Probe4]::WindowFromPoint($pt)
  $acc = $null; $var = $null
  $hr = [Probe4]::AccessibleObjectFromPoint($pt, [ref]$acc, [ref]$var)
  $adesc = "null"
  if ($acc -ne $null) {
    try {
      $role = $acc.accRole(0); $name = $acc.accName(0); $state = $acc.accState(0)
      $adesc = "role=$role name='$name' state=$state"
    } catch { $adesc = "err" }
  }
  Write-Output "$($p.n)($($p.x),$($p.y)): hwnd=$h cls='$([Probe4]::Cls($h))' msaa hr=0x$($hr.ToString('X8')) $adesc"
}
