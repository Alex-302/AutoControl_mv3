# Temporary probe (2026-09-20): read the ENGINE's hover-region CACHE
# (FUN_00415bf0) to find out why a wheel over a zone sometimes produces no
# 750 even though the helper's zone table is correct.
#
# FUN_00415bf0 caches each region's verdict as a BIT and recomputes it only when
#   (DAT_0049fc4c != DAT_004a26b4)  AND  (300 < counter delta OR cursor moved >3px)
# so a stale bit can survive. This probe prints the cache state next to the
# cursor position and the helper's own answer.
#
# Usage: powershell -NoProfile -File Test/_probe_enginecache.ps1 [-EnginePid N]
param([int]$EnginePid = 0)
Add-Type @"
using System;
using System.Runtime.InteropServices;
public class EngCache {
  [DllImport("user32.dll")] public static extern bool SetProcessDPIAware();
  [DllImport("user32.dll")] public static extern bool GetCursorPos(out POINT p);
  [DllImport("kernel32.dll", SetLastError=true)] public static extern IntPtr OpenProcess(uint access, bool inherit, int pid);
  [DllImport("kernel32.dll")] public static extern bool CloseHandle(IntPtr h);
  [DllImport("kernel32.dll", SetLastError=true)] public static extern bool ReadProcessMemory(IntPtr h, IntPtr addr, byte[] buf, IntPtr size, out IntPtr read);
  [StructLayout(LayoutKind.Sequential)] public struct POINT { public int X, Y; }

  static IntPtr H; static long Base;
  public static bool Attach(int pid, long baseAddr) {
    H = OpenProcess(0x410 /* QUERY_INFORMATION|VM_READ */, false, pid);
    if (H == IntPtr.Zero) return false;
    Base = baseAddr;
    return Base != 0;
  }
  public static uint U32(long va) {
    byte[] b = new byte[4]; IntPtr r;
    if (!ReadProcessMemory(H, (IntPtr)(Base + va), b, (IntPtr)4, out r)) return 0xDEADBEEF;
    return BitConverter.ToUInt32(b, 0);
  }
  public static int I32(long va) { return unchecked((int)U32(va)); }
  public static string Dump() {
    var sb = new System.Text.StringBuilder();
    POINT pt; GetCursorPos(out pt);
    sb.AppendLine("cursor            : " + pt.X + "," + pt.Y);
    sb.AppendLine("DAT_004a26b4 cnt  : " + U32(0xA26B4));
    sb.AppendLine("DAT_0049fc4c last : " + U32(0x9FC4C));
    sb.AppendLine("last point        : " + I32(0x9FC6C) + "," + I32(0x9FC70));
    sb.AppendLine("--- region RESULTS  (DAT_004a27f0 + group*4) ---");
    for (int g = 0; g < 4; g++) {
      uint v = U32(0xA27F0 + g * 4);
      uint c = U32(0xA28C0 + g * 4);
      sb.Append("  group " + g + " (regions " + (g * 32) + ".." + (g * 32 + 31) + ") results=0x" + v.ToString("X8") + " computed=0x" + c.ToString("X8") + "  set:[");
      for (int b = 0; b < 32; b++) if ((v & (1u << b)) != 0) sb.Append((g * 32 + b) + " ");
      sb.Append("]");
      sb.AppendLine();
    }
    return sb.ToString();
  }
  public static void Detach() { if (H != IntPtr.Zero) CloseHandle(H); }
}
"@
[void][EngCache]::SetProcessDPIAware()
$pids = if ($EnginePid -ne 0) { @($EnginePid) } else { (Get-Process AutoCtrl* -ErrorAction SilentlyContinue | Select-Object -ExpandProperty Id) }
if (-not $pids) { "no engine process found"; exit 1 }
foreach ($p in $pids) {
  "=== engine pid $p ==="
  $base = 0
  try { $base = (Get-Process -Id $p).Modules[0].BaseAddress.ToInt64() } catch { "  cannot read module list: $_" }
  if ($base -eq 0) { continue }
  if (-not [EngCache]::Attach($p, $base)) { "  attach failed (try elevated)"; continue }
  [EngCache]::Dump()
  [EngCache]::Detach()
}
