# engine_window_binding.ps1 - WHICH BROWSER does each running engine belong to?
#
# Why this exists: every browser spawns its OWN AutoControlZero->engine pair and
# each engine keeps its OWN zone table (the v19 cave). With several browsers
# running, "which engine is mine?" is the question that decides whether the zone
# helper writes the right table — answering it WRONG (the old
# `FindEnginePids()[0]`) made one browser's engine keep the "always match"
# fallback, so its mouse-over conditions matched EVERYWHERE ("wheel over the
# page switches tabs", 2026-09-13).
#
# The process tree cannot answer it (AutoControlZero is a launcher: it hands its
# pipes to the engine and exits, so every engine's parent is dead). The engine
# itself knows: it keeps a `std::vector<HWND>` of the windows of ITS browser at
# image base +0xA2514 (the region matcher's only caller walks exactly this list,
# see Test/native-disasm/decomp/00415b40_FUN_00415b40.c). This script reads that
# list out of every engine and matches it against each browser's windows.
#
# Expected output when several browsers run:
#   engine 55392 -> matches C:\Program Files\Google\Chrome: 7  /  ...Chrome SxS: 0
#   engine 190748 -> matches C:\Program Files\Google\Chrome: 0 /  ...Chrome SxS: 1
# (An engine with an EMPTY list is either fresh or already has its windows
#  closed - the helper treats that as "cannot tell yet" and retries.)
#
# Usage:
#   powershell -ExecutionPolicy Bypass -File Test\engine_window_binding.ps1
#   powershell -ExecutionPolicy Bypass -File Test\engine_window_binding.ps1 -BaseOff 0xA2514
param([int]$BaseOff = 0xA2514)   # 0x004a2514 - image base 0x400000
Add-Type @"
using System;
using System.Collections.Generic;
using System.Runtime.InteropServices;
public class EW {
  [DllImport("kernel32.dll", SetLastError=true)] public static extern IntPtr OpenProcess(uint a, bool i, int pid);
  [DllImport("kernel32.dll", SetLastError=true)] public static extern bool ReadProcessMemory(IntPtr h, IntPtr a, byte[] b, IntPtr n, out IntPtr r);
  [DllImport("kernel32.dll")] public static extern bool CloseHandle(IntPtr h);
  [DllImport("psapi.dll")] public static extern bool EnumProcessModules(IntPtr h, IntPtr[] m, int cb, out int need);
  [DllImport("user32.dll")] public static extern bool EnumWindows(EnumProc cb, IntPtr p);
  [DllImport("user32.dll")] public static extern uint GetWindowThreadProcessId(IntPtr h, out uint pid);
  public delegate bool EnumProc(IntPtr h, IntPtr p);

  public static List<long> BrowserWindows(uint want) {
    var list = new List<long>();
    EnumWindows((h, p) => { uint pid; GetWindowThreadProcessId(h, out pid); if (pid == want) list.Add(h.ToInt64()); return true; }, IntPtr.Zero);
    return list;
  }
  public static long ModuleBase(IntPtr h) {
    var mods = new IntPtr[64]; int need;
    if (!EnumProcessModules(h, mods, 64 * IntPtr.Size, out need)) return 0;
    return mods[0].ToInt64();
  }
  public static long ReadDword(IntPtr h, long addr, out bool ok) {
    var b = new byte[4]; IntPtr r;
    ok = ReadProcessMemory(h, (IntPtr)addr, b, (IntPtr)4, out r);
    return ok ? BitConverter.ToUInt32(b, 0) : 0;
  }
  public static List<uint> ReadDwords(IntPtr h, long addr, int n) {
    var list = new List<uint>();
    var b = new byte[n * 4]; IntPtr r;
    if (!ReadProcessMemory(h, (IntPtr)addr, b, (IntPtr)(n * 4), out r)) return list;
    for (int i = 0; i < n; i++) list.Add(BitConverter.ToUInt32(b, i * 4));
    return list;
  }
}
"@

$engines = (Get-CimInstance Win32_Process -Filter "Name='AutoCtrl_2025.4.22.0.exe'").ProcessId
# Every Chromium-family browser can run the extension, so enumerate the whole
# family (mirrors `IsBrowserName` in Test/ac_zone_helper.cs). The browser
# process is the one without a `--type=` switch (children are renderers/GPU).
$browserNames = 'chrome.exe','brave.exe','msedge.exe','opera.exe','vivaldi.exe','yandex.exe','chromium.exe','thorium.exe'
$browsers = @()
foreach ($p in (Get-CimInstance Win32_Process | Where-Object { $browserNames -contains $_.Name.ToLower() -and $_.CommandLine -notmatch '--type=' })) {
  $browsers += [pscustomobject]@{ pid = $p.ProcessId; name = (($p.ExecutablePath -replace '\\[^\\]+$','') + '  (' + $p.Name + ')'); wins = [EW]::BrowserWindows($p.ProcessId) }
}
foreach ($b in $browsers) { Write-Output ("browser {0} pid={1}: {2} windows: {3}" -f $b.name, $b.pid, $b.wins.Count, (($b.wins | ForEach-Object { '0x' + $_.ToString('X') }) -join ' ')) }

foreach ($e in $engines) {
  $h = [EW]::OpenProcess(0x410, $false, $e)
  if ($h -eq [IntPtr]::Zero) { Write-Output "engine $e : OpenProcess failed"; continue }
  try {
    $baseAddr = [EW]::ModuleBase($h)
    $ok1 = $false; $ok2 = $false
    $p0 = [EW]::ReadDword($h, $baseAddr + $BaseOff, [ref]$ok1)
    $p1 = [EW]::ReadDword($h, $baseAddr + $BaseOff + 4, [ref]$ok2)
    $cnt = 0; if ($ok1 -and $ok2 -and $p1 -gt $p0) { $cnt = [int](($p1 - $p0) / 4) }
    Write-Output ("engine {0}: base=0x{1:X} list=[0x{2:X}..0x{3:X}] count={4}" -f $e, $baseAddr, $p0, $p1, $cnt)
    if ($cnt -gt 0 -and $cnt -lt 200) {
      $hwnds = [EW]::ReadDwords($h, $p0, $cnt)
      Write-Output ("   wins: " + (($hwnds | ForEach-Object { '0x' + $_.ToString('X') }) -join ' '))
      foreach ($b in $browsers) {
        $hit = 0
        foreach ($w in $hwnds) { if ($b.wins -contains [long]$w) { $hit++ } }
        Write-Output ("   -> matches {0}: {1}" -f $b.name, $hit)
      }
    }
  } finally { [void][EW]::CloseHandle($h) }
}
