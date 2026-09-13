# engine_zone_write.ps1 - write the v19 zone table into the running engine.
#
# v19 patch (AutoControl_native/patches/patch_zones_v19.js) turns the engine's mouseOver region check
# into a TABLE LOOKUP: table[region] != 0 -> the trigger matches (and the input
# is consumed), 0 -> it does not match (the input passes through, so pages keep
# scrolling). The table + an "alive" flag live in a page the zone helper
# allocates inside the engine; this script does the same by hand so the plumbing
# can be tested without deploying a new helper.
#
# Modes
#   -Zones "12,4,1"   alive=1 and mark exactly those regions
#   -Alive 0          alive=0 -> the engine falls back to "always match" (v18)
#   -Fallback         restore the pre-filled always-match cave prefix
#   -Dump             print the cave prefix + the marked regions
#
# Usage:
#   powershell -ExecutionPolicy Bypass -File Test\engine_zone_write.ps1 -Zones "12,4,1"
#   powershell -ExecutionPolicy Bypass -File Test\engine_zone_write.ps1 -Dump
param(
  [string]$Zones = "",
  [int]$Alive = 1,
  [switch]$Fallback,
  [switch]$Dump,
  [switch]$Diag,
  [int]$EnginePid = 0
)
Add-Type @"
using System;
using System.Text;
using System.Collections.Generic;
using System.Runtime.InteropServices;

public class EngZone {
  [DllImport("kernel32.dll", SetLastError=true)] public static extern IntPtr OpenProcess(uint access, bool inherit, int pid);
  [DllImport("kernel32.dll", SetLastError=true)] public static extern bool CloseHandle(IntPtr h);
  [DllImport("kernel32.dll", SetLastError=true)] public static extern IntPtr VirtualAllocEx(IntPtr h, IntPtr addr, IntPtr size, uint type, uint protect);
  [DllImport("kernel32.dll", SetLastError=true)] public static extern bool VirtualProtectEx(IntPtr h, IntPtr addr, IntPtr size, uint newProtect, out uint oldProtect);
  [DllImport("kernel32.dll", SetLastError=true)] public static extern bool WriteProcessMemory(IntPtr h, IntPtr addr, byte[] buf, IntPtr size, out IntPtr written);
  [DllImport("kernel32.dll", SetLastError=true)] public static extern bool ReadProcessMemory(IntPtr h, IntPtr addr, byte[] buf, IntPtr size, out IntPtr read);
  [DllImport("kernel32.dll", SetLastError=true)] public static extern IntPtr CreateToolhelp32Snapshot(uint flags, uint pid);
  [DllImport("kernel32.dll", CharSet=CharSet.Unicode)] public static extern bool Process32First(IntPtr snap, ref PROCESSENTRY32 pe);
  [DllImport("kernel32.dll", CharSet=CharSet.Unicode)] public static extern bool Process32Next(IntPtr snap, ref PROCESSENTRY32 pe);
  [DllImport("kernel32.dll", CharSet=CharSet.Unicode)] public static extern bool Module32First(IntPtr snap, ref MODULEENTRY32 me);
  [DllImport("kernel32.dll", CharSet=CharSet.Unicode)] public static extern bool Module32Next(IntPtr snap, ref MODULEENTRY32 me);
  [StructLayout(LayoutKind.Sequential, CharSet=CharSet.Unicode)]
  public struct PROCESSENTRY32 { public uint dwSize, cntUsage, th32ProcessID; public IntPtr th32DefaultHeapID; public uint th32ModuleID, cntThreads, th32ParentProcessID; public int pcPriClassBase; public uint dwFlags; [MarshalAs(UnmanagedType.ByValTStr, SizeConst=260)] public string szExeFile; }
  [StructLayout(LayoutKind.Sequential, CharSet=CharSet.Unicode)]
  public struct MODULEENTRY32 { public uint dwSize, th32ModuleID, th32ProcessID, GlblcntUsage, ProccntUsage; public IntPtr modBaseAddr; public uint modBaseSize; public IntPtr hModule; [MarshalAs(UnmanagedType.ByValTStr, SizeConst=256)] public string szModule; [MarshalAs(UnmanagedType.ByValTStr, SizeConst=260)] public string szExePath; }

  public static int[] FindEngines() {
    var list = new List<int>();
    IntPtr snap = CreateToolhelp32Snapshot(0x2, 0);
    if (snap == (IntPtr)(-1) || snap == IntPtr.Zero) return list.ToArray();
    PROCESSENTRY32 pe = new PROCESSENTRY32(); pe.dwSize = (uint)Marshal.SizeOf(typeof(PROCESSENTRY32));
    if (Process32First(snap, ref pe)) {
      do {
        if (pe.szExeFile != null && pe.szExeFile.StartsWith("AutoCtrl_") && pe.szExeFile.EndsWith(".exe"))
          list.Add((int)pe.th32ProcessID);
      } while (Process32Next(snap, ref pe));
    }
    CloseHandle(snap);
    return list.ToArray();
  }
  public static long ModuleBase(int pid) {
    IntPtr snap = CreateToolhelp32Snapshot(0x8 | 0x10, (uint)pid);   // MODULE | 32BIT
    if (snap == (IntPtr)(-1) || snap == IntPtr.Zero) return 0;
    MODULEENTRY32 me = new MODULEENTRY32(); me.dwSize = (uint)Marshal.SizeOf(typeof(MODULEENTRY32));
    long baseAddr = 0;
    if (Module32First(snap, ref me)) {
      do {
        if (me.szModule != null && me.szModule.StartsWith("AutoCtrl_")) { baseAddr = me.modBaseAddr.ToInt64(); break; }
      } while (Module32Next(snap, ref me));
    }
    CloseHandle(snap);
    return baseAddr;
  }
  public static bool Write(IntPtr h, long addr, byte[] buf) {
    IntPtr w;
    return WriteProcessMemory(h, (IntPtr)addr, buf, (IntPtr)buf.Length, out w);
  }
  public static byte[] Read(IntPtr h, long addr, int n) {
    byte[] b = new byte[n]; IntPtr r;
    if (!ReadProcessMemory(h, (IntPtr)addr, b, (IntPtr)n, out r)) return null;
    return b;
  }
  public static uint Protect(IntPtr h, long addr, int n, uint prot) {
    uint old;
    VirtualProtectEx(h, (IntPtr)addr, (IntPtr)n, prot, out old);
    return old;
  }
}
"@

$CAVE_RVA = 0x7f7a3
$ORIG_BLOCK = 0x1c

$engines = [EngZone]::FindEngines()
if ($EnginePid -ne 0) { $engines = @($EnginePid) }
if ($engines.Count -eq 0) { Write-Output "no engine process"; exit 1 }

foreach ($ep in $engines) {
  $h = [EngZone]::OpenProcess(0x438, $false, $ep)   # QUERY_INFORMATION | VM_OPERATION | VM_READ | VM_WRITE
  if ($h -eq [IntPtr]::Zero) { Write-Output "pid $ep : OpenProcess failed (try running elevated)"; continue }
  $base = [EngZone]::ModuleBase($ep)
  $cave = $base + $CAVE_RVA
  Write-Output ("pid {0}: base=0x{1:X} cave=0x{2:X}" -f $ep, $base, $cave)

  if ($Dump) {
    $cur = [EngZone]::Read($h, $cave, 0x25)
    if ($cur -eq $null) { Write-Output "  read failed"; [EngZone]::CloseHandle($h) | Out-Null; continue }
    Write-Output ("  cave: " + (($cur | ForEach-Object { $_.ToString('x2') }) -join ' '))
    if ($cur[5] -eq 0x89) {
      # diagnostic build: `mov [edx*4+disp32], edx` -> report the asked-for ids
      $seen = [BitConverter]::ToInt32($cur, 8)
      Write-Output ("  DIAG build; seen table @0x{0:X}" -f $seen)
      if ($seen -gt 0x10000) {
        $tbl = [EngZone]::Read($h, $seen, 256)
        if ($tbl -ne $null) {
          $ids = @()
          for ($i = 0; $i -lt 64; $i++) { if ([BitConverter]::ToInt32($tbl, $i * 4) -ne 0) { $ids += $i } }
          Write-Output ("  ASKED-FOR REGION IDS: [" + ($ids -join ',') + "]")
        }
      }
      [EngZone]::CloseHandle($h) | Out-Null
      continue
    }
    # table build
    $tab = [long][BitConverter]::ToUInt32($cur, 0x11)
    $aliveAddr = [long][BitConverter]::ToUInt32($cur, 7)
    Write-Output ("  alive addr=0x{0:X}  table addr=0x{1:X}" -f $aliveAddr, $tab)
    if ($tab -gt 0x10000) {
      $tbl = [EngZone]::Read($h, $tab, 256)
      $aliveVal = [EngZone]::Read($h, $aliveAddr, 4)
      if ($tbl -ne $null) {
        $marked = @()
        for ($i = 0; $i -lt 64; $i++) { if ([BitConverter]::ToInt32($tbl, $i * 4) -ne 0) { $marked += $i } }
        $av = if ($aliveVal) { [BitConverter]::ToInt32($aliveVal, 0) } else { -1 }
        Write-Output ("  alive=" + $av + "  marked regions: " + ($marked -join ','))
        Write-Output ("  slot[12]=" + [BitConverter]::ToInt32($tbl, 48) + "  slot[3]=" + [BitConverter]::ToInt32($tbl, 12) + "  slot[4]=" + [BitConverter]::ToInt32($tbl, 16))
      } else { Write-Output "  table read FAILED" }
    }
    [EngZone]::CloseHandle($h) | Out-Null
    continue
  }

  if ($Diag) {
    # diagnostic cave: cmp edx,3Fh / ja ORIG / mov [edx*4+seen],edx / mov eax,1 / ret
    $page = [EngZone]::VirtualAllocEx($h, [IntPtr]::Zero, [IntPtr]4096, 0x3000, 0x04)
    if ($page -eq [IntPtr]::Zero) { Write-Output "  VirtualAllocEx failed"; [EngZone]::CloseHandle($h) | Out-Null; continue }
    $pageAddr = $page.ToInt64()
    $seenAddr = $pageAddr + 272
    $pre = New-Object byte[] 0x11
    $pre[0] = 0x83; $pre[1] = 0xFA; $pre[2] = 0x3F
    $pre[3] = 0x77; $pre[4] = 0x0C
    $pre[5] = 0x89; $pre[6] = 0x14; $pre[7] = 0x95
    [BitConverter]::GetBytes([int]$seenAddr).CopyTo($pre, 8)
    $pre[12] = 0xB8; $pre[13] = 1; $pre[16] = 0xC3
    $old = [EngZone]::Protect($h, $cave, 64, 0x40)
    [void][EngZone]::Write($h, $cave, $pre)
    [void][EngZone]::Protect($h, $cave, 64, $old)
    # zero the seen table
    [void][EngZone]::Write($h, $seenAddr, (New-Object byte[] 256))
    Write-Output ("  wrote DIAG cave: seen table @0x{0:X} (page 0x{1:X})" -f $seenAddr, $pageAddr)
    [EngZone]::CloseHandle($h) | Out-Null
    continue
  }

  # page for [alive flag][table 64 x dword]
  $page = [EngZone]::VirtualAllocEx($h, [IntPtr]::Zero, [IntPtr]4096, 0x3000, 0x04)   # COMMIT|RESERVE, PAGE_READWRITE
  if ($page -eq [IntPtr]::Zero) { Write-Output "  VirtualAllocEx failed"; [EngZone]::CloseHandle($h) | Out-Null; continue }
  $pageAddr = $page.ToInt64()
  $aliveAddr = $pageAddr
  $tabAddr = $pageAddr + 16

  $table = New-Object byte[] 256
  if ($Zones -ne "") {
    foreach ($z in $Zones.Split(',')) {
      $zi = [int]$z.Trim()
      if ($zi -ge 0 -and $zi -lt 64) { [BitConverter]::GetBytes([int]1).CopyTo($table, $zi * 4) }
    }
  }
  [void][EngZone]::Write($h, $tabAddr, $table)
  [void][EngZone]::Write($h, $aliveAddr, [BitConverter]::GetBytes([int]$Alive))

  if ($Fallback) {
    # pre-filled file version: always match (no memory reads)
    $pre = New-Object byte[] $ORIG_BLOCK
    $pre[0] = 0x83; $pre[1] = 0xFA; $pre[2] = 0x28
    $pre[3] = 0x73; $pre[4] = [byte]($ORIG_BLOCK - 5)
    $pre[5] = 0xB8; $pre[6] = 1
    $pre[10] = 0xC3
    for ($i = 11; $i -lt $ORIG_BLOCK; $i++) { $pre[$i] = 0x90 }
    $old = [EngZone]::Protect($h, $cave, 64, 0x40)   # PAGE_EXECUTE_READWRITE
    [void][EngZone]::Write($h, $cave, $pre)
    [void][EngZone]::Protect($h, $cave, 64, $old)
    Write-Output "  restored the always-match (v18) fallback"
  } else {
    # table version: cmp edx,28h / jae orig / cmp [alive],0 / je notalive /
    #                 mov eax,[edx*4+tab] / ret / mov eax,1 / ret
    $pre = New-Object byte[] $ORIG_BLOCK
    $pre[0] = 0x83; $pre[1] = 0xFA; $pre[2] = 0x28
    $pre[3] = 0x73; $pre[4] = [byte]($ORIG_BLOCK - 5)
    $pre[5] = 0x80; $pre[6] = 0x3D
    [BitConverter]::GetBytes([int]$aliveAddr).CopyTo($pre, 7)
    $pre[11] = 0x00
    $pre[12] = 0x74; $pre[13] = 0x08
    $pre[14] = 0x8B; $pre[15] = 0x04; $pre[16] = 0x95
    [BitConverter]::GetBytes([int]$tabAddr).CopyTo($pre, 17)
    $pre[21] = 0xC3                                  # ret (0x15)
    $pre[22] = 0xB8; $pre[23] = 1                    # notalive: mov eax,1 (0x16)
    $pre[27] = 0xC3                                  # ret (0x1b)
    $old = [EngZone]::Protect($h, $cave, 64, 0x40)
    [void][EngZone]::Write($h, $cave, $pre)
    [void][EngZone]::Protect($h, $cave, 64, $old)
    Write-Output ("  wrote table version: alive=0x{0:X} tab=0x{1:X} zones=[{2}] aliveFlag={3}" -f $aliveAddr, $tabAddr, $Zones, $Alive)
  }
  [EngZone]::CloseHandle($h) | Out-Null
}
