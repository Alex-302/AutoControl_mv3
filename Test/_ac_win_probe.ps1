Add-Type @"
using System;
using System.Text;
using System.Runtime.InteropServices;
public class WinProbe {
  [DllImport("user32.dll")] public static extern IntPtr WindowFromPoint(POINT pt);
  [DllImport("user32.dll")] public static extern IntPtr ChildWindowFromPointEx(IntPtr parent, POINT pt, uint flags);
  [DllImport("user32.dll")] public static extern int GetClassName(IntPtr h, StringBuilder sb, int max);
  [DllImport("user32.dll")] public static extern IntPtr GetAncestor(IntPtr h, uint flags);
  [DllImport("user32.dll")] public static extern bool GetWindowRect(IntPtr h, out RECT r);
  [DllImport("user32.dll")] public static extern int GetWindowText(IntPtr h, StringBuilder sb, int max);
  [DllImport("user32.dll")] public static extern bool EnumChildWindows(IntPtr parent, EnumProc cb, IntPtr lParam);
  public delegate bool EnumProc(IntPtr h, IntPtr lParam);
  [StructLayout(LayoutKind.Sequential)] public struct POINT { public int x; public int y; }
  [StructLayout(LayoutKind.Sequential)] public struct RECT { public int l, t, r, b; }
  public static string Cls(IntPtr h) { if (h == IntPtr.Zero) return "(null)"; var sb = new StringBuilder(256); GetClassName(h, sb, 256); return sb.ToString(); }
}
"@
$pts = @(@{n="page"; x=600; y=400}, @{n="tabstrip"; x=600; y=50}, @{n="titlebar-left"; x=120; y=12}, @{n="titlebar-center"; x=300; y=12})
foreach ($p in $pts) {
  $pt = New-Object WinProbe+POINT; $pt.x = $p.x; $pt.y = $p.y
  $h = [WinProbe]::WindowFromPoint($pt)
  $cls = [WinProbe]::Cls($h)
  $r = New-Object WinProbe+RECT
  [WinProbe]::GetWindowRect($h, [ref]$r) | Out-Null
  Write-Output "$($p.n)($($p.x),$($p.y)): hwnd=$h class='$cls' rect=$($r.l),$($r.t),$($r.r),$($r.b)"
}
# enumerate child windows of the top Chrome window to see the page hwnd class
$top = [WinProbe]::WindowFromPoint((New-Object WinProbe+POINT -Property @{x=600;y=400}))
# find the top-level ancestor
$root = [WinProbe]::GetAncestor($top, 2)
Write-Output "root hwnd: $root class='$([WinProbe]::Cls($root))'"
$kids = [System.Collections.ArrayList]::new()
$cb = [WinProbe+EnumProc]{ param($h, $lp) [void]$kids.Add($h); return $true }
[WinProbe]::EnumChildWindows($root, $cb, [IntPtr]::Zero) | Out-Null
Write-Output "child count: $($kids.Count)"
foreach ($k in $kids) { Write-Output "  child $k class='$([WinProbe]::Cls($k))'" }
