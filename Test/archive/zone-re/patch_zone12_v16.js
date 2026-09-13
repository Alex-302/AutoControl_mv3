// Patch AutoCtrl_2025.4.22.0.exe v16 — WORKING BASELINE (v10 semantics).
// Always-1 zone-12 classifier + gate bypass. NO 792 telemetry (proven to
// corrupt classification). This build must fire reloadTabs over the tab
// strip (proven before) — used to isolate "config didn't reach the engine"
// from "classifier doesn't work".
//
// Changes (all in-place, no .acp section needed):
//   1) 0x415781: jz fail (0F 84 69 03 00 00) -> 6x NOP  [gate bypass]
//   2) 0x4155ac: `83 7e 2c 25 75 08` (cmp [esi+0x2c],0x25; jnz)
//      -> `b0 01 90 90 90 90` (mov al,1; nops) — zone 12 always true.
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
const check = (at, sig, name) => {
  const po = off(at);
  const cur = [...buf.subarray(po, po + sig.length)];
  if (JSON.stringify(cur) !== JSON.stringify(sig)) {
    console.error('SIG MISMATCH ' + name + ' @0x' + at.toString(16) + ': ' + cur.map(b => b.toString(16)).join(' '));
    process.exit(1);
  }
};

// ---- 1) gate bypass ----
check(0x415781, [0x0F, 0x84, 0x69, 0x03, 0x00, 0x00], 'gate jz');
let po = off(0x415781);
for (let i = 0; i < 6; i++) buf[po + i] = 0x90;

// ---- 2) zone-12 always true (v10 semantics) ----
check(0x4155ac, [0x83, 0x7E, 0x2C, 0x25, 0x75, 0x08], 'hovered cmp');
po = off(0x4155ac);
buf[po] = 0xB0; buf[po + 1] = 0x01;
for (let i = 2; i < 6; i++) buf[po + i] = 0x90;

fs.writeFileSync(FILE, buf);
console.log('v16 patch OK ->', FILE);
console.log('hash:', crypto.createHash('sha256').update(buf).digest('hex'));
