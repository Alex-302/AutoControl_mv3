# Temporary probe (2026-09-20): verify the ENGINE's zone table (patch v19)
# against the cursor position IN THE SAME INSTANT, so a user moving the mouse
# cannot fake a mismatch.
#
# Reads: the cave at VA 0x47F7A3 (holds the alive + table addresses), then the
# 64-dword table itself. Prints the marked regions next to the cursor position.
#
# Usage: powershell -NoProfile -File Test/_probe_tablecheck.ps1 -Points "close,370,560" -Reps 5
param(
  [string]$Points = "close,370,560",
  [int]$Reps = 5,
  [int]$WaitMs = 500
)
Add-Type @"
using System;
using System.Runtime.InteropServices;
public class TC {
  [DllImport("user32.dll")] public static extern bool SetProcessDPIAware();
  [DllImport("user32.dll")] public static extern bool SetCursorPos(int x, int y);
  [DllImport("user32.dll")] public static extern bool GetCursorPos(out POINT p);
  [DllImport("kernel32.dll")] public static extern IntPtr OpenProcess(uint a, bool i, int p);
  [DllImport("kernel32.dll")] public static extern bool ReadProcessMemory(IntPtr h, IntPtr a, byte[] b, IntPtr n, out IntPtr r);
  [StructLayout(LayoutKind.Sequential)] public struct POINT { public int X, Y; }
  static IntPtr H; static long B;
  const long PREF = 0x400000;
  public static bool Attach(int pid, long modBase) { H = OpenProcess(0x410, false, pid); B = modBase; return H != IntPtr.Zero; }
  public static uint Va(long va) { byte[] b = new byte[4]; IntPtr r; if (!ReadProcessMemory(H, (IntPtr)(B + (va - PREF)), b, (IntPtr)4, out r)) return 0xFFFFFFFF; return BitConverter.ToUInt32(b, 0); }
  public static byte[] Bytes(long va, int n) { byte[] b = new byte[n]; IntPtr r; if (!ReadProcessMemory(H, (IntPtr)(B + (va - PREF)), b, (IntPtr)n, out r)) return null; return b; }
  public static string Now() { POINT p; GetCursorPos(out p); return p.X + "," + p.Y; }
  public static string Table() {
    byte[] cave = Bytes(0x47F7A3, 40);
    if (cave == null) return "cave read failed";
    uint alive = BitConverter.ToUInt32(cave, 7);   // 80 3D <addr32> <imm8> - the opcode is 2 bytes
    uint table = BitConverter.ToUInt32(cave, 0x11); // 8B 04 95 <addr32>
    byte[] a = new byte[1]; IntPtr r;
    if (!ReadProcessMemory(H, (IntPtr)alive, a, (IntPtr)1, out r)) return "alive read failed (0x" + alive.ToString("X") + ")";
    var sb = new System.Text.StringBuilder();
    sb.Append("alive=" + a[0] + " table=0x" + table.ToString("X") + " regions:[ ");
    byte[] t = new byte[256]; IntPtr r2;
    if (!ReadProcessMemory(H, (IntPtr)table, t, (IntPtr)256, out r2)) return "table read failed";
    for (int i = 0; i < 64; i++) { if (BitConverter.ToUInt32(t, i * 4) != 0) sb.Append(i + " "); }
    sb.Append("]");
    return sb.ToString();
  }
}
"@
[void][TC]::SetProcessDPIAware()
$p = Get-Process AutoCtrl* -ErrorAction SilentlyContinue | Select-Object -First 1
if (-not $p) { "no engine process"; exit 1 }
$exe = $p.Modules | Where-Object { $_.ModuleName -like "*.exe" } | Select-Object -First 1
[void][TC]::Attach($p.Id, $exe.BaseAddress.ToInt64())
"engine pid $($p.Id)  (move the mouse AWAY is not needed - the probe re-checks the cursor)"
foreach ($spec in $Points.Split(';')) {
  $f = $spec.Split(',')
  if ($f.Count -lt 3) { continue }
  $x = [int]$f[1]; $y = [int]$f[2]
  for ($i = 1; $i -le $Reps; $i++) {
    [void][TC]::SetCursorPos($x, $y)
    Start-Sleep -Milliseconds $WaitMs
    $cur = [TC]::Now()
    if ($cur -ne "$x,$y") { "  rep $i : SKIPPED (cursor moved by the user to $cur)"; continue }
    "  rep $i : cursor=$cur  " + [TC]::Table()
  }
}
