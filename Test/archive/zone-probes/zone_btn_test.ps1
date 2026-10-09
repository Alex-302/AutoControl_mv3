# zone_btn_test.ps1 - find a tab-strip BUTTON live, then wheel over it.
#
# The tab layout shifts while testing (Chrome scrolls/switches tabs on wheel),
# so hard-coded coordinates go stale between runs. This script:
#   1. scans the tab strip row with MSAA and finds the BUTTON to test
#      ('Close' = zone 15, 'New Tab' = zone 16),
#   2. asks the deployed helper what zone that point really is (sanity check),
#   3. moves the cursor there and injects ONE real wheel notch,
#   4. reports the SW zone-gate lines for the burst.
#
# Usage:
#   powershell -ExecutionPolicy Bypass -File Test\zone_btn_test.ps1 -What Close
#   powershell -ExecutionPolicy Bypass -File Test\zone_btn_test.ps1 -What New
param([string]$What = "Close", [int]$WindowTop = -1, [int]$WindowLeft = -1)

Add-Type -ReferencedAssemblies Accessibility @"
using System;
using System.Collections.Generic;
using System.Runtime.InteropServices;
using Accessibility;
public class ZBt {
  [DllImport("user32.dll")] public static extern bool SetProcessDPIAware();
  [DllImport("user32.dll")] public static extern bool SetCursorPos(int x, int y);
  [DllImport("user32.dll")] public static extern void mouse_event(uint f, uint dx, uint dy, uint d, UIntPtr e);
  [DllImport("user32.dll")] public static extern bool GetWindowRect(IntPtr h, out RECT r);
  [DllImport("oleacc.dll")] public static extern int AccessibleObjectFromPoint(POINT pt, out IAccessible acc, out object child);
  [StructLayout(LayoutKind.Sequential)] public struct POINT { public int x, y; }
  [StructLayout(LayoutKind.Sequential)] public struct RECT { public int l, t, r, b; }

  static IAccessible Aop(POINT pt) {
    IAccessible acc = null; object c = null;
    int hr = AccessibleObjectFromPoint(pt, out acc, out c);
    if (hr != 0 || acc == null) return null;
    try { object n = acc.get_accName(0); } catch { }
    try { Marshal.ReleaseComObject(acc); } catch { }
    acc = null;
    hr = AccessibleObjectFromPoint(pt, out acc, out c);
    if (hr != 0 || acc == null) return null;
    return acc;
  }
  // returns "role|name" for the element at the point
  public static string Info(POINT pt) {
    IAccessible a = Aop(pt);
    if (a == null) return "?|";
    string r = "?", n = "";
    try { r = ((int)a.get_accRole(0)).ToString(); } catch { }
    try { n = (string)a.get_accName(0); } catch { }
    try { Marshal.ReleaseComObject(a); } catch { }
    return r + "|" + (n == null ? "" : n);
  }
}
"@
[ZBt]::SetProcessDPIAware() | Out-Null

# ---- locate the browser window (physical pixels) ----
$w = Get-Process chrome -ErrorAction SilentlyContinue |
  Where-Object { $_.Path -like '*Chrome SxS*' -and $_.MainWindowHandle -ne 0 } |
  Sort-Object { $_.MainWindowTitle.Length } | Select-Object -Last 1
if (-not $w) { Write-Host "NO SXS WINDOW"; exit 1 }
$r = New-Object ZBt+RECT
[ZBt]::GetWindowRect($w.MainWindowHandle, [ref]$r) | Out-Null
$L = if ($WindowLeft -ge 0) { $WindowLeft } else { $r.l }
$T = if ($WindowTop -ge 0) { $WindowTop } else { $r.t }
Write-Host "window: l=$($r.l) t=$($r.t) r=$($r.r) b=$($r.b)  (using L=$L T=$T)"

$stripY = $T + 31

# ---- scan the strip for the wanted button ----
$hits = @()
for ($x = $L + 10; $x -le $r.r - 10; $x += 4) {
  $pt = New-Object ZBt+POINT; $pt.x = $x; $pt.y = $stripY
  $info = [ZBt]::Info($pt)
  $parts = $info.Split('|')
  if ($parts[0] -eq '43') {
    if ($What -eq 'Close' -and $parts[1] -eq 'Close') { $hits += $x }
    elseif ($What -ne 'Close' -and $parts[1] -like 'New*') { $hits += $x }
  }
}
if ($hits.Count -eq 0) { Write-Host "button '$What' NOT FOUND on the strip (y=$stripY)"; exit 1 }
# take the middle run's center
$target = $hits[[int]($hits.Count / 2)]
Write-Host "found '$What' at x=$($hits[0])..$($hits[-1])  -> target x=$target y=$stripY"

# ---- sanity: what does the helper say there? ----
[ZBt]::SetCursorPos($target, $stripY) | Out-Null
Start-Sleep -Milliseconds 600
$resp = (node (Join-Path $PSScriptRoot 'zone_helper_smoke.js') 2>&1 | Select-String 'RESP' | Select-Object -First 1)
Write-Host "helper: $resp"

# ---- wheel one notch while tailing the SW log ----
$out = Join-Path $env:TEMP 'ac_btn_test.txt'
Remove-Item $out -ErrorAction SilentlyContinue
Start-Process node -ArgumentList 'Test\zone_swtail.js', '9223', '16', 'AC-MV3-ZONE|AC-ACT' -RedirectStandardOutput $out -NoNewWindow
Start-Sleep -Seconds 5
[ZBt]::SetCursorPos($target, $stripY) | Out-Null
Start-Sleep -Milliseconds 400
[ZBt]::mouse_event(0x0800, 0, 0, 120, [UIntPtr]::Zero)
Start-Sleep -Seconds 8
Write-Host "=== SW lines ==="
Get-Content $out -ErrorAction SilentlyContinue
