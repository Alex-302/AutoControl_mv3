// Patch AutoCtrl_2025.4.22.0.exe v5b — ZONE-12 classifier: bypass the
// FUN_00414760 gate AND force FUN_00415570 to always return 1.
//
// Chain for the mouseOver precond (type 13):
//   FUN_00420050 case 0xd -> FUN_00415bf0(point, zone)   (zone cache)
//     -> FUN_00415b40 -> FUN_004156f0(point, zone, hwnd)
//       zone 0xc (12): FUN_00414760(point, hwnd, 10)  <- gate
//                      jz fail                         <- BYPASS HERE
//                      FUN_00415240 (hover cache)
//                      -> FUN_00415570(hoverCache)     <- STUB: always 1
//
// Patch 1 (0x415782): `0f 84 69 03 00 00` (jz 0x415af0) -> 6x NOP.
//   The test al,al at 0x415780 stays; al is not consumed afterwards.
// Patch 2 (0x4155ac): `83 7e 2c 25 75 08` (cmp [esi+0x2c],0x25; jnz)
//   -> `b0 01 90 90 90 90` (mov al,1; nops) — FUN_00415570 returns 1.
// Diagnostic only — NOT for production.
'use strict';
const fs = require('fs');
const path = require('path');
const crypto = require('crypto');

const DIR = process.env.TEMP + '\\ac_native_re';
const FILE = path.join(DIR, 'AutoCtrl_2025.4.22.0.exe');
const BAK = path.join(DIR, 'AutoCtrl_2025.4.22.0.exe.bak');

fs.copyFileSync(BAK, FILE);
const buf = fs.readFileSync(FILE);

const u16 = o => buf.readUInt16LE(o), u32 = o => buf.readUInt32LE(o);
const pe = u32(0x3C);
const numSec = u16(pe + 6), optSize = u16(pe + 20);
const secOff = pe + 24 + optSize;
const secs = [];
for (let i = 0; i < numSec; i++) {
  const o = secOff + i * 40;
  secs.push({ va: u32(o + 12), vs: u32(o + 8), raw: u32(o + 20), rs: u32(o + 16) });
}
const off = a => {
  const r = a - 0x400000;
  for (const s of secs) if (r >= s.va && r < s.va + Math.max(s.vs, s.rs)) return s.raw + (r - s.va);
  throw new Error('out ' + a.toString(16));
};

// ---- Patch 1: bypass FUN_00414760 gate (jz fail) ----
const AT1 = 0x415781;
const SIG1 = [0x0F, 0x84, 0x69, 0x03, 0x00, 0x00];
const po1 = off(AT1);
const sig1 = [...buf.subarray(po1, po1 + 6)];
if (JSON.stringify(sig1) !== JSON.stringify(SIG1)) {
  console.error('SIG1 MISMATCH @0x' + AT1.toString(16) + ': ' + sig1.map(b => b.toString(16)).join(' '));
  process.exit(1);
}
for (let i = 0; i < 6; i++) buf[po1 + i] = 0x90;

// ---- Patch 2: FUN_00415570 -> always return 1 ----
const AT2 = 0x4155ac;
const SIG2 = [0x83, 0x7E, 0x2C, 0x25, 0x75, 0x08];
const po2 = off(AT2);
const sig2 = [...buf.subarray(po2, po2 + 6)];
if (JSON.stringify(sig2) !== JSON.stringify(SIG2)) {
  console.error('SIG2 MISMATCH @0x' + AT2.toString(16) + ': ' + sig2.map(b => b.toString(16)).join(' '));
  process.exit(1);
}
buf[po2] = 0xB0; buf[po2 + 1] = 0x01;
for (let i = 2; i < 6; i++) buf[po2 + i] = 0x90;

fs.writeFileSync(FILE, buf);
console.log('zone-12 v5b patch OK ->', FILE);
console.log('hash:', crypto.createHash('sha256').update(buf).digest('hex'));
