# Zone prototype — explicit tab-strip detection via MSAA (no geometry).
#
# HYPOTHESIS TO PROVE: the tab-strip zone can be identified EXPLICITLY from
# the MSAA tree (roles TABITEM=37 / PAGETABLIST=60 in the ancestry), without
# any geometric computation. The abandoned engine fails at this because its
# hover cache never refreshes over the tab strip — but a fresh AOP call from
# OUR OWN process sees the real tree (probe6: over a tab d0=41 d1=37 d2=16;
# over the strip gap d0=16 d1=60 d2=16).
#
# What it does:
#   1. finds the Chrome SxS window (hwnd param or auto),
#   2. for a set of points (tab strip xN, omnibox, page, titlebar) calls
#      AccessibleObjectFromPoint + walks accParent up to 4 levels,
#   3. classifies each point by the EXPLICIT role markers found,
#   4. re-scans after 2s to check stability (the engine needs the pause).
#
# Usage:
#   powershell -ExecutionPolicy Bypass -File Test\zone_proto.ps1
#   powershell -ExecutionPolicy Bypass -File Test\zone_proto.ps1 -Hwnd 620632946
param([int]$Hwnd = 0)

Add-Type -ReferencedAssemblies Accessibility @"
using System;
using System.Text;
using System.Collections.Generic;
using System.Runtime.InteropServices;
using Accessibility;

public class ZoneProto {
  [DllImport("user32.dll")] public static extern IntPtr WindowFromPoint(POINT pt);
  [DllImport("user32.dll")] public static extern int GetClassName(IntPtr h, StringBuilder sb, int max);
  [DllImport("user32.dll")] public static extern bool GetWindowRect(IntPtr h, out RECT r);
  [DllImport("user32.dll")] public static extern bool SetCursorPos(int x, int y);
  [DllImport("oleacc.dll")] public static extern int AccessibleObjectFromPoint(POINT pt, out IAccessible acc, out object varChild);
  [StructLayout(LayoutKind.Sequential)] public struct POINT { public int x; public int y; }
  [StructLayout(LayoutKind.Sequential)] public struct RECT { public int l, t, r, b; }

  public static string Cls(IntPtr h) { if (h == IntPtr.Zero) return "(null)"; var sb = new StringBuilder(256); GetClassName(h, sb, 256); return sb.ToString(); }

  public static string Walk(POINT pt, int maxDepth) {
    IAccessible acc = null; object varChild = null;
    int hr = AccessibleObjectFromPoint(pt, out acc, out varChild);
    var parts = new List<string>();
    var cur = acc;
    for (int d = 0; d < maxDepth && cur != null; d++) {
      try {
        int role = (int)cur.get_accRole(0); string name = (string)cur.get_accName(0); int cc = cur.accChildCount;
        parts.Add(string.Format("d{0}:role={1}(0x{1:X}) '{2}' cc={3}", d, role, Trunc(name, 36), cc));
      } catch { parts.Add(string.Format("d{0}:ERR", d)); break; }
      try { cur = (IAccessible)cur.accParent; } catch { break; }
    }
    return string.Join(" | ", parts);
  }

  // Explicit classification by role markers in the walked ancestry.
  // Order matters: check the most specific markers first.
  // - TABITEM 37 at depth 0..2  -> tab (hard marker, no false positives)
  // - PAGETABLIST 60 at depth 1 -> strip gap between tabs (d1 only;
  //   a titlebar point also has 60 but at d2+)
  public static string Classify(string walk) {
    string[] d = walk.Split(new string[] { " | " }, StringSplitOptions.None);
    for (int i = 0; i < d.Length && i < 3; i++) {
      if (d[i].Contains("role=37")) return "TAB-STRIP   (explicit: TABITEM role 37 @ d" + i + ")";
    }
    if (d.Length > 1 && d[1].Contains("role=60")) return "TAB-STRIP   (explicit: PAGETABLIST role 60 @ d1 — strip gap)";
    if (walk.Contains("role=42") || walk.Contains("role=57")) return "OMNIBOX     (explicit: role 42/57 address bar)";
    if (walk.Contains("role=15")) return "PAGE        (explicit: DOCUMENT role 15)";
    return "UNKNOWN";
  }
  private static string Trunc(string s, int n) { if (s == null) return ""; return s.Length <= n ? s : s.Substring(0, n) + "\u2026"; }
}
"@

# ---- find the SxS window ----
if ($Hwnd -eq 0) {
  # pick the LARGEST visible SxS window (the tab window; the settings page
  # and extension pages are small)
  $cands = Get-Process chrome -ErrorAction SilentlyContinue |
    Where-Object { $_.Path -like '*Chrome SxS*' -and $_.MainWindowHandle -ne 0 }
  $best = $null; $bestArea = 0
  foreach ($c in $cands) {
    $rr = New-Object ZoneProto+RECT
    if (-not [ZoneProto]::GetWindowRect([IntPtr]$c.MainWindowHandle, [ref]$rr)) { continue }
    $area = ($rr.r - $rr.l) * ($rr.b - $rr.t)
    if ($area -gt $bestArea) { $bestArea = $area; $best = $c }
  }
  if (-not $best) { Write-Output "NO SXS WINDOW FOUND"; exit 1 }
  $Hwnd = $best.MainWindowHandle
  Write-Output "Window: $($best.MainWindowTitle) hwnd=$Hwnd area=$bestArea"
} else {
  Write-Output "Window: hwnd=$Hwnd"
}

$r = New-Object ZoneProto+RECT
[ZoneProto]::GetWindowRect([IntPtr]$Hwnd, [ref]$r) | Out-Null
$l = $r.l; $t = $r.t; $w = $r.r - $r.l; $h = $r.b - $r.t
Write-Output ("Rect: l={0} t={1} r={2} b={3} w={4} h={5}" -f $l, $t, $r.r, $r.b, $w, $h)

# ---- probe points (relative to the window) ----
$pts = @(
  @{ n = "tabstrip/1";  x = $l + [int]($w * 0.20); y = $t + 40 },
  @{ n = "tabstrip/2";  x = $l + [int]($w * 0.40); y = $t + 40 },
  @{ n = "tabstrip/3";  x = $l + [int]($w * 0.60); y = $t + 40 },
  @{ n = "tabstrip/4";  x = $l + [int]($w * 0.75); y = $t + 40 },
  @{ n = "tabstrip/5";  x = $l + [int]($w * 0.90); y = $t + 40 },
  @{ n = "omnibox";     x = $l + [int]($w * 0.50); y = $t + 85 },
  @{ n = "page";        x = $l + [int]($w * 0.50); y = $t + [int]($h * 0.55) },
  @{ n = "titlebar";    x = $l + [int]($w * 0.50); y = $t + 5 }
)

# ---- scan + classify ----
for ($pass = 1; $pass -le 2; $pass++) {
  Write-Output ""
  Write-Output "=== PASS $pass ==="
  foreach ($p in $pts) {
    $pt = New-Object ZoneProto+POINT
    $pt.x = $p.x; $pt.y = $p.y
    [ZoneProto]::SetCursorPos($p.x, $p.y) | Out-Null
    Start-Sleep -Milliseconds 250
    $walk = [ZoneProto]::Walk($pt, 4)
    $cls  = [ZoneProto]::Classify($walk)
    Write-Output ("{0,-12} ({1,5},{2,5}): {3}" -f $p.n, $p.x, $p.y, $walk)
    Write-Output ("{0,-12}  => {1}" -f '', $cls)
  }
  if ($pass -eq 1) {
    Write-Output ""
    Write-Output "--- waiting 2s (hover-cache settle) before pass 2 ---"
    Start-Sleep -Seconds 2
  }
}
Write-Output ""
Write-Output "DONE"
