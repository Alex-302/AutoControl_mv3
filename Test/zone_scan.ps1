# zone_scan.ps1 - MSAA signature scanner for AutoControl mouse-over zones.
#
# DOES NOT MOVE THE CURSOR: AccessibleObjectFromPoint() takes an arbitrary
# screen point, so we can hit-test any coordinate without disturbing the user.
#
# What it does:
#   1. finds the window (any browser or an explicit HWND), gets its rect,
#   2. finds the UI ROWS automatically (a vertical probe locates the tab
#      strip / toolbar / omnibox rows by their roles - see -Auto), or falls
#      back to the Chrome SxS defaults when the roles are not found,
#   3. VERTICAL scans at 3 x-positions to locate the UI rows
#      (title strip / tab strip / toolbar / page),
#   4. HORIZONTAL run-length sweeps at those rows: prints each element
#      (role/name/child-count) with its x-range - this is where the
#      distinguishing signatures for the zones come from,
#   5. enumerates the CHILDREN of one tab element (close button? audio
#      indicator?) - needed for zones 15/17,
#   6. dumps everything to %TEMP%\ac_zone_scan.txt.
#
# The MSAA tree of Chrome 148+ sleeps until accName is queried (crbug
# 416429182); every probe below wakes it first (AOP -> accName -> re-AOP),
# exactly like ac_zone_helper.exe does.
#
# Window selection (first that matches):
#   -Hwnd <n>            explicit window handle
#   -Browser <name>      chrome | sxs | brave | vivaldi | opera | edge | yandex
#                        (looks up the process by name/path)
#   -Exe <path>          explicit exe path (e.g. the portable Vivaldi/Opera)
#   -ProcessName <name>  process name, e.g. "vivaldi"
#   (default: the largest Chrome SxS window)
#
# Usage:
#   powershell -ExecutionPolicy Bypass -File Test\zone_scan.ps1 -Browser brave
#   powershell -ExecutionPolicy Bypass -File Test\zone_scan.ps1 -Exe "C:\Work\Portable\Vivaldi\Application\vivaldi.exe"
#   powershell -ExecutionPolicy Bypass -File Test\zone_scan.ps1 -Hwnd 123456 -Step 6 -NoAuto
param(
  [int]$Hwnd = 0,
  [int]$Step = 8,
  [int]$Dump = 0,
  [string]$Browser = "",
  [string]$Exe = "",
  [string]$ProcessName = "",
  [switch]$NoAuto
)

Add-Type -ReferencedAssemblies Accessibility @"
using System;
using System.Text;
using System.Collections.Generic;
using System.Runtime.InteropServices;
using Accessibility;

public class ZoneScan {
  [DllImport("user32.dll")] public static extern IntPtr WindowFromPoint(POINT pt);
  [DllImport("user32.dll")] public static extern int GetClassName(IntPtr h, StringBuilder sb, int max);
  [DllImport("user32.dll")] public static extern bool GetWindowRect(IntPtr h, out RECT r);
  [DllImport("oleacc.dll")] public static extern int AccessibleObjectFromPoint(POINT pt, out IAccessible acc, out object child);
  [StructLayout(LayoutKind.Sequential)] public struct POINT { public int x; public int y; }
  [StructLayout(LayoutKind.Sequential)] public struct RECT { public int l, t, r, b; }

  public static string Cls(IntPtr h) {
    if (h == IntPtr.Zero) return "(null)";
    var sb = new StringBuilder(256); GetClassName(h, sb, 256); return sb.ToString();
  }

  static IAccessible Aop(POINT pt) {
    IAccessible acc = null; object c = null;
    int hr = AccessibleObjectFromPoint(pt, out acc, out c);
    if (hr != 0 || acc == null) return null;
    // wake the tree (Chrome 148+ anti-abuse): ask accName, release, re-query
    try { object n = acc.get_accName(0); } catch { }
    try { Marshal.ReleaseComObject(acc); } catch { }
    acc = null;
    hr = AccessibleObjectFromPoint(pt, out acc, out c);
    if (hr != 0 || acc == null) return null;
    return acc;
  }

  public static string Desc(object o, out int cc) {
    cc = -1;
    IAccessible a = o as IAccessible;
    if (a == null) return "?";
    string role = "?", name = "";
    try { role = ((int)a.get_accRole(0)).ToString(); } catch { }
    try { name = (string)a.get_accName(0); } catch { }
    try { cc = a.accChildCount; } catch { }
    if (name == null) name = "";
    if (name.Length > 44) name = name.Substring(0, 44) + "\u2026";
    return "role=" + role + " '" + name + "'";
  }

  // full ancestry walk + window class at the point
  public static string Walk(POINT pt, int maxDepth) {
    IAccessible acc = Aop(pt);
    if (acc == null) return "(aop-fail)";
    var parts = new List<string>();
    IAccessible cur = acc;
    for (int d = 0; d < maxDepth && cur != null; d++) {
      int cc;
      parts.Add("d" + d + ":" + Desc(cur, out cc) + " cc=" + cc);
      try { cur = (IAccessible)cur.accParent; } catch { break; }
    }
    try { Marshal.ReleaseComObject(acc); } catch { }
    string cls = Cls(WindowFromPoint(pt));
    return "[" + cls + "] " + string.Join(" | ", parts.ToArray());
  }

  // children of the element under the point (for the tab: close/audio buttons?)
  public static string Kids(POINT pt) {
    IAccessible acc = Aop(pt);
    if (acc == null) return "(aop-fail)";
    var parts = new List<string>();
    IAccessible tab = null;
    // prefer the walk level that looks like a tab (role 37) if any
    IAccessible cur = acc;
    for (int d = 0; d < 3 && cur != null; d++) {
      string r = ""; try { r = ((int)cur.get_accRole(0)).ToString(); } catch { }
      if (r == "37") { tab = cur; break; }
      try { cur = (IAccessible)cur.accParent; } catch { break; }
    }
    if (tab == null) tab = acc;
    int n = 0; try { n = tab.accChildCount; } catch { }
    int n2 = 0;
    parts.Add("parent: " + Desc(tab, out n2));
    for (int i = 1; i <= Math.Min(n, 12); i++) {
      object ch = null;
      try { ch = tab.get_accChild(i); } catch { }
      if (ch == null) { parts.Add("  child" + i + ": (null)"); continue; }
      int cc; string dsc = Desc(ch, out cc);
      // also try the child's own children (one level deeper)
      string sub = "";
      try {
        IAccessible ca = ch as IAccessible;
        if (ca != null && ca.accChildCount > 0 && ca.accChildCount < 8) {
          var subs = new List<string>();
          for (int k = 1; k <= ca.accChildCount; k++) {
            object sc = null; try { sc = ca.get_accChild(k); } catch { }
            if (sc == null) continue;
            int cc2; subs.Add(Desc(sc, out cc2));
            try { Marshal.ReleaseComObject(sc); } catch { }
          }
          if (subs.Count > 0) sub = " {sub: " + string.Join(", ", subs.ToArray()) + "}";
        }
      } catch { }
      parts.Add("  child" + i + ": " + dsc + sub);
      try { Marshal.ReleaseComObject(ch); } catch { }
    }
    try { Marshal.ReleaseComObject(acc); } catch { }
    return string.Join("\n", parts.ToArray());
  }
}
"@

# ---------- find the window ----------
if ($Hwnd -eq 0) {
  # resolve the process to look at: -Browser/-Exe/-ProcessName, else Chrome SxS
  $lookup = ''
  if ($Browser) {
    $map = @{
      'chrome' = 'chrome.exe'; 'sxs' = '*Chrome SxS*'; 'brave' = 'brave.exe';
      'vivaldi' = 'vivaldi.exe'; 'opera' = 'opera.exe'; 'edge' = 'msedge.exe';
      'yandex' = 'yandex.exe'
    }
    $lookup = $map[$Browser.ToLower()]
    if (-not $lookup) { Write-Output "UNKNOWN -Browser '$Browser' (chrome|sxs|brave|vivaldi|opera|edge|yandex)"; exit 1 }
  } elseif ($Exe) {
    $lookup = Split-Path $Exe -Leaf
  } elseif ($ProcessName) {
    $lookup = $ProcessName + '.exe'
  } else {
    $lookup = '*Chrome SxS*'
  }
  $cands = @()
  if ($lookup -like '*SxS*') {
    $cands = Get-Process chrome -ErrorAction SilentlyContinue |
      Where-Object { $_.Path -like $lookup -and $_.MainWindowHandle -ne 0 }
  } elseif ($Exe) {
    $cands = Get-Process -ErrorAction SilentlyContinue |
      Where-Object { $_.Path -and $_.Path -eq $Exe -and $_.MainWindowHandle -ne 0 }
  } else {
    $cands = Get-Process -Name ($lookup -replace '\.exe$','') -ErrorAction SilentlyContinue |
      Where-Object { $_.MainWindowHandle -ne 0 }
  }
  $best = $null; $bestArea = 0
  foreach ($c in $cands) {
    $rr = New-Object ZoneScan+RECT
    if (-not [ZoneScan]::GetWindowRect([IntPtr]$c.MainWindowHandle, [ref]$rr)) { continue }
    $area = ($rr.r - $rr.l) * ($rr.b - $rr.t)
    if ($area -gt $bestArea) { $bestArea = $area; $best = $c }
  }
  if (-not $best) { Write-Output "NO WINDOW FOUND for '$lookup' - is the browser running?"; exit 1 }
  $Hwnd = $best.MainWindowHandle
  Write-Output "Window: $($best.MainWindowTitle) hwnd=$Hwnd path=$($best.Path)"
}
$r = New-Object ZoneScan+RECT
[ZoneScan]::GetWindowRect([IntPtr]$Hwnd, [ref]$r) | Out-Null
$l = $r.l; $t = $r.t; $w = $r.r - $r.l; $h = $r.b - $r.t
Write-Output ("Rect: l={0} t={1} r={2} b={3} w={4} h={5}  (step={6}px)" -f $l, $t, $r.r, $r.b, $w, $h, $Step)

$log = Join-Path $env:TEMP 'ac_zone_scan.txt'
"" | Set-Content $log
function Emit($s) { $s | Add-Content $log; }

# ---------- helpers ----------
function Probe([int]$x, [int]$y) {
  $pt = New-Object ZoneScan+POINT; $pt.x = $x; $pt.y = $y
  return [ZoneScan]::Walk($pt, 5)
}
function SweepH([int]$y, [string]$tag) {
  Write-Output ""
  Write-Output "=== H-SWEEP [$tag] y=$y  (x from $($l+8) to $($r.r-8) step $Step) ==="
  Emit "=== H-SWEEP [$tag] y=$y ==="
  $prev = ''; $startX = $l + 8
  for ($x = $l + 8; $x -le $r.r - 8; $x += $Step) {
    $d = Probe $x $y
    if ($d -ne $prev) {
      if ($prev -ne '') {
        $line = ("  x={0,5}..{1,5}  {2}" -f $startX, ($x - $Step), $prev)
        Write-Output $line; Emit $line
      }
      $prev = $d; $startX = $x
    }
  }
  $line = ("  x={0,5}..{1,5}  {2}" -f $startX, ($x - $Step), $prev)
  Write-Output $line; Emit $line
}
function SweepV([int]$x, [string]$tag) {
  Write-Output ""
  Write-Output "=== V-SWEEP [$tag] x=$x  (y from $($t+2) to $($t+150) step 4) ==="
  Emit "=== V-SWEEP [$tag] x=$x ==="
  $prev = ''; $startY = $t + 2
  for ($y = $t + 2; $y -le $t + 150; $y += 4) {
    $d = Probe $x $y
    if ($d -ne $prev) {
      if ($prev -ne '') {
        $line = ("  y={0,5}..{1,5}  {2}" -f $startY, ($y - 4), $prev)
        Write-Output $line; Emit $line
      }
      $prev = $d; $startY = $y
    }
  }
  $line = ("  y={0,5}..{1,5}  {2}" -f $startY, ($y - 4), $prev)
  Write-Output $line; Emit $line
}

# ---------- 1. vertical scans (find the rows) ----------
SweepV ($l + 150)              'left (x=l+150)'
SweepV ($l + [int]($w * 0.55)) 'middle'
SweepV ($r.r - 180)            'right (x=r-180)'

# ---------- 2. find the UI rows (auto) or fall back to Chrome defaults ----------
$yTitle = $t + 5
$yTab   = $t + 30
$yTab2  = $t + 44
$yTool  = $t + 88
$yOmn   = $t + 88
if (-not $NoAuto) {
  Write-Output ""
  Write-Output "=== AUTO-ROWS: vertical probe at x=$($l+150), y=$($t+2)..$($t+180) ==="
  Emit "=== AUTO-ROWS: x=$($l+150) ==="
  $roleAt = @{}   # role -> first y where it appears at d0/d1
  for ($y = $t + 2; $y -le $t + 180; $y += 2) {
    $d = Probe ($l + 150) $y
    # roles of interest: 60=PAGETABLIST, 37=PAGETAB, 22=TOOLBAR, 42=EDIT
    foreach ($role in 60, 37, 22, 42) {
      if ($d -match ("role=" + $role + "\b")) {
        if (-not $roleAt.ContainsKey($role)) { $roleAt[$role] = $y }
      }
    }
  }
  if ($roleAt.ContainsKey(60)) { $yTab = $roleAt[60] + 3; $yTab2 = $yTab + 8 }
  elseif ($roleAt.ContainsKey(37)) { $yTab = $roleAt[37]; $yTab2 = $yTab + 8 }
  if ($roleAt.ContainsKey(22)) { $yTool = $roleAt[22] + 3 }
  if ($roleAt.ContainsKey(42)) { $yOmn = $roleAt[42] + 3 }
  $summary = "tablist/tab first at y=" + $(if ($roleAt.ContainsKey(60)) { $roleAt[60] } elseif ($roleAt.ContainsKey(37)) { $roleAt[37] } else { '?' }) +
    "  toolbar at y=" + $(if ($roleAt.ContainsKey(22)) { $roleAt[22] } else { '?' }) +
    "  edit(omnibox) at y=" + $(if ($roleAt.ContainsKey(42)) { $roleAt[42] } else { '?' })
  Write-Output $summary
  Emit $summary
}

# ---------- 3. horizontal sweeps on the found rows ----------
SweepH $yTitle 'title strip'
SweepH $yTab   'tab strip A'
SweepH $yTab2  'tab strip B'
SweepH $yTool  'toolbar row'
if ($yOmn -ne $yTool) { SweepH $yOmn 'omnibox row' }

# ---------- 4. stop at the first tab element (close/speaker children) ----------
Write-Output ""
Write-Output "=== ZOOM-IN: tab children (x=l+150, y=$yTab) ==="
$pt = New-Object ZoneScan+POINT; $pt.x = $l + 150; $pt.y = $yTab
$kids = [ZoneScan]::Kids($pt)
Write-Output $kids; Emit "=== TAB CHILDREN ==="; Emit $kids

# ---------- 5. zoom-in on the far right of the toolbar row (kebab/menu) ----------
Write-Output ""
Write-Output "=== ZOOM-IN: right end of the toolbar row (x=r-40..r-150) ==="
for ($x = $r.r - 30; $x -ge $r.r - 260; $x -= 20) {
  $d = Probe $x $yTool
  $line = ("  x={0,5} y={1,5}  {2}" -f $x, $yTool, $d)
  Write-Output $line; Emit $line
}

Write-Output ""
Write-Output "DONE - full dump: $log"
