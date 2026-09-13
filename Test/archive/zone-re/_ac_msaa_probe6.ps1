Add-Type -ReferencedAssemblies Accessibility @"
using System;
using System.Text;
using System.Runtime.InteropServices;
using Accessibility;
public class Probe6 {
  [DllImport("user32.dll")] public static extern IntPtr WindowFromPoint(POINT pt);
  [DllImport("user32.dll")] public static extern int GetClassName(IntPtr h, StringBuilder sb, int max);
  [DllImport("user32.dll")] public static extern bool GetWindowRect(IntPtr h, out RECT r);
  [DllImport("oleacc.dll")] public static extern int AccessibleObjectFromPoint(POINT pt, out IAccessible acc, out object varChild);
  [StructLayout(LayoutKind.Sequential)] public struct POINT { public int x; public int y; }
  [StructLayout(LayoutKind.Sequential)] public struct RECT { public int l, t, r, b; }
  public static string Cls(IntPtr h) { if (h == IntPtr.Zero) return "(null)"; var sb = new StringBuilder(256); GetClassName(h, sb, 256); return sb.ToString(); }
}
"@
$h = [IntPtr]620632946
$wr = New-Object Probe6+RECT
[Probe6]::GetWindowRect($h, [ref]$wr) | Out-Null
$l = $wr.l; $t = $wr.t
$pts = @(
  @{n="tabstrip1"; x=($l+250); y=($t+40)},
  @{n="tabstrip2"; x=($l+700); y=($t+40)},
  @{n="omnibox";   x=($l+1800); y=($t+85)},
  @{n="page";      x=($l+800);  y=($t+500)}
)
foreach ($p in $pts) {
  $pt = New-Object Probe6+POINT; $pt.x = $p.x; $pt.y = $p.y
  $acc = $null; $var = $null
  $hr = [Probe6]::AccessibleObjectFromPoint($pt, [ref]$acc, [ref]$var)
  $line = "$($p.n)($($p.x),$($p.y)): hr=0x$($hr.ToString('X8'))"
  $cur = $acc
  for ($depth = 0; $depth -lt 4 -and $cur -ne $null; $depth++) {
    try {
      $role = $cur.accRole(0); $name = $cur.accName(0); $cc = $cur.accChildCount
      $line += " | d$depth role=$role name='$name' cc=$cc"
    } catch { $line += " | d$depth err"; break }
    try { $cur = $cur.accParent } catch { break }
  }
  Write-Output $line
}
