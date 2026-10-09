Add-Type -ReferencedAssemblies Accessibility @"
using System;
using System.Text;
using System.Runtime.InteropServices;
using Accessibility;
public class HoneyPot {
  [DllImport("user32.dll")] public static extern IntPtr FindWindowEx(IntPtr parent, IntPtr after, string cls, string title);
  [DllImport("user32.dll")] public static extern bool SendMessageTimeout(IntPtr h, uint m, IntPtr wp, IntPtr lp, uint flags, uint timeout, out IntPtr res);
  [DllImport("user32.dll")] public static extern IntPtr SendMessage(IntPtr h, uint m, IntPtr wp, IntPtr lp);
  [DllImport("oleacc.dll")] public static extern int AccessibleObjectFromWindow(IntPtr h, uint id, ref Guid iid, out IAccessible acc);
  [DllImport("oleacc.dll")] public static extern int AccessibleObjectFromPoint(POINT pt, out IAccessible acc, out object varChild);
  [DllImport("user32.dll")] public static extern int GetClassName(IntPtr h, StringBuilder sb, int max);
  [StructLayout(LayoutKind.Sequential)] public struct POINT { public int x; public int y; }
  public static readonly Guid IID_IAccessible = new Guid("618736e0-3c3d-11cf-810c-00aa00389b71");
  public static string Cls(IntPtr h) { if (h == IntPtr.Zero) return "(null)"; var sb = new StringBuilder(256); GetClassName(h, sb, 256); return sb.ToString(); }
}
"@
function Probe-Msaa($label, $x, $y) {
  $pt = New-Object HoneyPot+POINT; $pt.x = $x; $pt.y = $y
  $acc = $null; $var = $null
  $hr = [HoneyPot]::AccessibleObjectFromPoint($pt, [ref]$acc, [ref]$var)
  $d = "null"
  if ($acc) { try { $d = "role=$($acc.accRole(0)) name='$($acc.accName(0))'" } catch { $d = "err" } }
  Write-Output "$label($x,$y): hr=0x$($hr.ToString('X8')) acc=$d"
}
# find the SxS top window + legacy page window
$win = $null
$procs = Get-Process chrome | Where-Object { $_.Path -like '*Chrome SxS*' -and $_.MainWindowHandle -ne 0 }
foreach ($p in $procs) { if ($p.MainWindowTitle -match 'sxs') { $win = $p.MainWindowHandle } }
if (-not $win) { $win = $procs | Select-Object -First 1 | ForEach-Object MainWindowHandle }
Write-Output "sxs window: $win class=$([HoneyPot]::Cls($win))"
$legacy = [HoneyPot]::FindWindowEx($win, [IntPtr]::Zero, "Chrome_RenderWidgetHostHWND", $null)
Write-Output "legacy page hwnd: $legacy class=$([HoneyPot]::Cls($legacy))"
Write-Output "--- BEFORE (baseline) ---"
Probe-Msaa "page" 700 400
Probe-Msaa "tabstrip" 700 45
# 1) honey pot: WM_GETOBJECT wParam=0 lParam=1
$res = [IntPtr]::Zero
[HoneyPot]::SendMessageTimeout($legacy, 0x3D, [IntPtr]::Zero, [IntPtr]1, 0x22, 1000, [ref]$res) | Out-Null
Write-Output "honey pot sent, lresult=$res"
# 2) accName query: AccessibleObjectFromWindow(OBJID_CLIENT) + get_accName
$acc = $null
$hr = [HoneyPot]::AccessibleObjectFromWindow($legacy, 0xFFFFFFFC, [ref][HoneyPot]::IID_IAccessible, [ref]$acc)
$nm = ""
if ($acc) { try { $nm = $acc.accName(0) } catch { $nm = "(name err)" } ; Write-Output "root accName: '$nm'" }
Write-Output "--- AFTER honey pot + accName ---"
Start-Sleep -Milliseconds 1500
Probe-Msaa "page" 700 400
Probe-Msaa "tabstrip" 700 45
