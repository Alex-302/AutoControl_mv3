Add-Type -ReferencedAssemblies Accessibility @"
using System;
using System.Text;
using System.Runtime.InteropServices;
using Accessibility;
public class Probe5 {
  [DllImport("user32.dll")] public static extern IntPtr WindowFromPoint(POINT pt);
  [DllImport("user32.dll")] public static extern int GetClassName(IntPtr h, StringBuilder sb, int max);
  [DllImport("user32.dll")] public static extern bool GetWindowRect(IntPtr h, out RECT r);
  [DllImport("oleacc.dll")] public static extern int AccessibleObjectFromPoint(POINT pt, out IAccessible acc, out object varChild);
  [DllImport("oleacc.dll")] public static extern int AccessibleObjectFromWindow(IntPtr h, int objId, ref Guid iid, out IAccessible acc);
  [StructLayout(LayoutKind.Sequential)] public struct POINT { public int x; public int y; }
  [StructLayout(LayoutKind.Sequential)] public struct RECT { public int l, t, r, b; }
  public static string Cls(IntPtr h) { if (h == IntPtr.Zero) return "(null)"; var sb = new StringBuilder(256); GetClassName(h, sb, 256); return sb.ToString(); }
}
"@
$h = [IntPtr]620632946
$wr = New-Object Probe5+RECT
[Probe5]::GetWindowRect($h, [ref]$wr) | Out-Null
$l = $wr.l; $t = $wr.t
$pts = @(
  @{n="tabstrip1"; x=($l+250); y=($t+40)},
  @{n="tabstrip2"; x=($l+700); y=($t+40)},
  @{n="omnibox";   x=($l+1800); y=($t+85)},
  @{n="page";      x=($l+800);  y=($t+500)},
  @{n="titlebar";  x=($l+1500); y=($t-5)}
)
foreach ($p in $pts) {
  $pt = New-Object Probe5+POINT; $pt.x = $p.x; $pt.y = $p.y
  $hw = [Probe5]::WindowFromPoint($pt)
  $acc = $null; $var = $null
  $hr = [Probe5]::AccessibleObjectFromPoint($pt, [ref]$acc, [ref]$var)
  $adesc = "null"
  if ($acc -ne $null) {
    try {
      $role = $acc.accRole(0); $name = $acc.accName(0); $state = $acc.accState(0)
      # child count via IAccessible.accChildCount
      $cc = -1
      try { $cc = $acc.accChildCount } catch { $cc = -2 }
      $adesc = "role=$role name='$name' state=$state childCount=$cc"
    } catch { $adesc = "err: $_" }
  }
  Write-Output "$($p.n)($($p.x),$($p.y)): hwnd=$hw cls='$([Probe5]::Cls($hw))' msaa hr=0x$($hr.ToString('X8')) $adesc"
}
