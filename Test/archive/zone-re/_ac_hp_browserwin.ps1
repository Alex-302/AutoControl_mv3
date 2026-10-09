# Honey-pot-per-window theory test: send WM_GETOBJECT lParam=1 (honey pot) to
# the BROWSER top-level window and check whether the tab strip / omnibox MSAA
# roles change from PANE (tree off) to real roles (tree on).
Add-Type -ReferencedAssemblies Accessibility @"
using System;
using System.Text;
using System.Runtime.InteropServices;
using Accessibility;
public class HP3 {
  [DllImport("user32.dll")] public static extern bool SendMessageTimeout(IntPtr h, uint m, IntPtr wp, IntPtr lp, uint flags, uint timeout, out IntPtr res);
  [DllImport("oleacc.dll")] public static extern int AccessibleObjectFromPoint(POINT pt, out IAccessible acc, out object varChild);
  [DllImport("user32.dll")] public static extern bool GetWindowRect(IntPtr h, out R r);
  public struct R { public int L, T, Rt, B; }
  [StructLayout(LayoutKind.Sequential)] public struct POINT { public int x; public int y; }
}
"@
function Probe2($label, $x, $y) {
  $pt = New-Object HP3+POINT; $pt.x = $x; $pt.y = $y
  $acc = $null; $var = $null
  $hr = [HP3]::AccessibleObjectFromPoint($pt, [ref]$acc, [ref]$var)
  $d = "null"
  if ($acc) { try { $d = "role=$($acc.accRole(0)) name='$($acc.accName(0))'" } catch { $d = "err" } }
  Write-Output "$label($x,$y): hr=0x$($hr.ToString('X8')) acc=$d"
}
$p = Get-Process chrome | Where-Object { $_.Path -like '*Chrome SxS*' -and $_.MainWindowHandle -ne 0 } | Select-Object -First 1
$win = $p.MainWindowHandle
$r = New-Object HP3+R; [HP3]::GetWindowRect($win, [ref]$r) | Out-Null
Write-Output "browser win: $win rect=($($r.L),$($r.T))-($($r.Rt),$($r.B))"
$px = $r.L + 300; $ty = $r.T + 40; $oy = $r.T + 90
Write-Output "--- BEFORE honey pot ---"
Probe2 "tabstrip" $px $ty
Probe2 "omnibox" $px $oy
Probe2 "page" $px ($r.T + 400)
$res = [IntPtr]::Zero
[HP3]::SendMessageTimeout($win, 0x3D, [IntPtr]::Zero, [IntPtr]1, 0x22, 1000, [ref]$res) | Out-Null
Write-Output "honey pot sent to browser win, lresult=$res"
Start-Sleep -Seconds 3
Write-Output "--- AFTER honey pot ---"
Probe2 "tabstrip" $px $ty
Probe2 "omnibox" $px $oy
Probe2 "page" $px ($r.T + 400)
