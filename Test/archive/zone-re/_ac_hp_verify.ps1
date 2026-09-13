# Verified honey-pot-per-window test: probe tab strip / omnibox roles with
# window-under-point verification, before and after the honey pot on the
# BROWSER top-level window.
Add-Type -ReferencedAssemblies Accessibility @"
using System;
using System.Text;
using System.Runtime.InteropServices;
using Accessibility;
public class HP4 {
  [DllImport("user32.dll")] public static extern bool SendMessageTimeout(IntPtr h, uint m, IntPtr wp, IntPtr lp, uint flags, uint timeout, out IntPtr res);
  [DllImport("oleacc.dll")] public static extern int AccessibleObjectFromPoint(POINT pt, out IAccessible acc, out object varChild);
  [DllImport("user32.dll")] public static extern bool GetWindowRect(IntPtr h, out R r);
  [DllImport("user32.dll")] public static extern IntPtr WindowFromPoint(POINT p);
  [DllImport("user32.dll")] public static extern IntPtr GetAncestor(IntPtr h, uint flags);
  public struct R { public int L, T, Rt, B; }
  [StructLayout(LayoutKind.Sequential)] public struct POINT { public int x; public int y; }
}
"@
function Probe3($label, $x, $y) {
  $pt = New-Object HP4+POINT; $pt.x = $x; $pt.y = $y
  $hw = [HP4]::WindowFromPoint($pt)
  $top = [HP4]::GetAncestor($hw, 2)
  $acc = $null; $var = $null
  $hr = [HP4]::AccessibleObjectFromPoint($pt, [ref]$acc, [ref]$var)
  $d = "null"
  if ($acc) { try { $d = "role=$($acc.accRole(0))" } catch { $d = "err" } }
  Write-Output "$label($x,$y): hwnd=$hw top=$top role=$d"
}
$p = Get-Process chrome | Where-Object { $_.Path -like '*Chrome SxS*' -and $_.MainWindowHandle -ne 0 } | Select-Object -First 1
$win = $p.MainWindowHandle
$r = New-Object HP4+R; [HP4]::GetWindowRect($win, [ref]$r) | Out-Null
Write-Output "browser win: $win rect=($($r.L),$($r.T))-($($r.Rt),$($r.B))"
$px = $r.L + 300; $ty = $r.T + 35; $oy = $r.T + 85
Write-Output "--- BEFORE honey pot ---"
Probe3 "tabstrip" $px $ty
Probe3 "omnibox" $px $oy
$res = [IntPtr]::Zero
[HP4]::SendMessageTimeout($win, 0x3D, [IntPtr]::Zero, [IntPtr]1, 0x22, 1000, [ref]$res) | Out-Null
Write-Output "honey pot sent to $win, lresult=$res"
Start-Sleep -Seconds 3
Write-Output "--- AFTER honey pot ---"
Probe3 "tabstrip" $px $ty
Probe3 "omnibox" $px $oy
