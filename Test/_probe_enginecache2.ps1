# Temporary probe (2026-09-20): read the engine's hover-region cache while the
# cursor sits at two known places, to see whether a region's cached verdict is
# refreshed (the v19 table is read only when FUN_00415bf0 recomputes the bit).
#
# FUN_00415bf0 (decomp/00415bf0_FUN_00415bf0.c):
#   invalidate when (DAT_0049fc4c != DAT_004a26b4) AND
#                  (300 < counter delta OR |dx| > 3 OR |dy| > 3)
#   then per region: if the "computed" bit is clear -> call the real check
#   (which reads the helper's table) and store the result bit.
#
# Addresses are VAs of the ORIGINAL image (preferred base 0x400000); the
# runtime address is  moduleBase + (VA - 0x400000).
#
# Usage: powershell -NoProfile -File Test/_probe_enginecache2.ps1 -Points "page,800,900;close,370,560"
param([string]$Points = "page,800,900;close,370,560")
Add-Type @"
using System;
using System.Runtime.InteropServices;
public class EC {
  [DllImport("user32.dll")] public static extern bool SetProcessDPIAware();
  [DllImport("user32.dll")] public static extern bool GetCursorPos(out POINT p);
  [DllImport("kernel32.dll")] public static extern IntPtr OpenProcess(uint a, bool i, int p);
  [DllImport("kernel32.dll")] public static extern bool ReadProcessMemory(IntPtr h, IntPtr a, byte[] b, IntPtr n, out IntPtr r);
  [StructLayout(LayoutKind.Sequential)] public struct POINT { public int X, Y; }
  static IntPtr H; static long B;                 // module base
  const long PREF = 0x400000;                     // preferred image base
  public static bool Attach(int pid, long modBase) { H = OpenProcess(0x410, false, pid); B = modBase; return H != IntPtr.Zero; }
  public static uint Va(long va) {                // read by ORIGINAL VA
    byte[] b = new byte[4]; IntPtr r;
    if (!ReadProcessMemory(H, (IntPtr)(B + (va - PREF)), b, (IntPtr)4, out r)) return 0xFFFFFFFF;
    return BitConverter.ToUInt32(b, 0);
  }
  public static int Iva(long va) { return unchecked((int)Va(va)); }
  static string Bits(uint v) { var s = ""; for (int b = 0; b < 32; b++) if ((v & (1u << b)) != 0) s += b + " "; return s; }
  public static string Snap() {
    POINT pt; GetCursorPos(out pt);
    var sb = new System.Text.StringBuilder();
    sb.AppendLine("  cursor=" + pt.X + "," + pt.Y + "  cnt=" + Va(0x4A26B4) + " last=" + Va(0x49FC4C) + " lastPt=" + Iva(0x49FC6C) + "," + Iva(0x49FC70));
    for (int g = 0; g < 4; g++) {
      uint res = Va(0x4A27F0 + g * 4);
      uint cmp = Va(0x4A28C0 + g * 4);
      sb.AppendLine("  group" + g + " res=0x" + res.ToString("X8") + " cmp=0x" + cmp.ToString("X8") + "  results:[ " + Bits(res) + "]  computed:[ " + Bits(cmp) + "]");
    }
    return sb.ToString();
  }
}
"@
[void][EC]::SetProcessDPIAware()
$p = Get-Process AutoCtrl* -ErrorAction SilentlyContinue | Select-Object -First 1
if (-not $p) { "no engine process"; exit 1 }
$exe = $p.Modules | Where-Object { $_.ModuleName -like "*.exe" } | Select-Object -First 1
[void][EC]::Attach($p.Id, $exe.BaseAddress.ToInt64())
"engine pid $($p.Id), module base 0x$($exe.BaseAddress.ToInt64().ToString('X'))"
foreach ($spec in $Points.Split(';')) {
  $f = $spec.Split(',')
  if ($f.Count -lt 3) { continue }
  Add-Type @"
using System;using System.Runtime.InteropServices;
public class Cur2 { [DllImport("user32.dll")] public static extern bool SetCursorPos(int x,int y); }
"@ -ErrorAction SilentlyContinue
  [Cur2]::SetCursorPos([int]$f[1], [int]$f[2]) | Out-Null
  Start-Sleep -Milliseconds 900
  "=== $($f[0]) ($($f[1]),$($f[2])) ==="
  [EC]::Snap()
}
