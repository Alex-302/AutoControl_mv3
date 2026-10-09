// Patch AutoCtrl_2025.4.22.0.exe v6 — SELECTIVE zone-12 classifier fix.
// Replaces the diagnostic all-true stubs (v5b) with the real classifier
// adapted to Chrome 148+ MSAA roles.
//
// Facts (live probe, Chrome 150 SxS, tree ON):
//   over a TAB:      role 41 (0x29, CELL-ish tab), parent role 37 (0x25)
//   over tab strip:  role 16 (LIST), parent role 60 (0x3c)
//   over omnibox:    role 42 (0x2a) — zone 21 already matches
//   over page:       role 15 (DOCUMENT)
// The engine's zone-12 check (FUN_00415570) matched 0x25 (37) only — old
// Chrome role; Chrome 150 reports the tab itself as 0x29 (41). The
// FUN_00414760(...,10) gate (zone 12 path) fails on modern maximized
// windows — reuse the zone-21 gate value (0x14) which works.
//
// Changes:
//   1) 0x415776: `6a 0a` -> `6a 14`   (zone-12 window check: 10 -> 0x14)
//   2) 0x4155ac: `83 7e 2c 25` -> `83 7e 2c 29`  (hovered role 0x25 -> 0x29)
//   3) 0x4155fe: `83 fa 25` -> `83 fa 29`        (parent role  0x25 -> 0x29)
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
const patch = (at, sig, rep, name) => {
  const po = off(at);
  const cur = [...buf.subarray(po, po + sig.length)];
  if (JSON.stringify(cur) !== JSON.stringify(sig)) {
    console.error('SIG MISMATCH ' + name + ' @0x' + at.toString(16) + ': ' + cur.map(b => b.toString(16)).join(' '));
    process.exit(1);
  }
  rep.forEach((b, i) => { buf[po + i] = b; });
  console.log('patched ' + name + ' @0x' + at.toString(16));
};

// 1) zone-12 path: window-check gate arg 10 -> 0x14 (same as zone 21)
patch(0x415775, [0x6A, 0x0A], [0x6A, 0x14], 'zone12 window-check arg (10->0x14)');
// 2) hovered role 0x25 -> 0x29 (Chrome 148+ tab role)
patch(0x4155ac, [0x83, 0x7E, 0x2C, 0x25], [0x83, 0x7E, 0x2C, 0x29], 'hovered role 0x25->0x29');
// 3) parent role 0x25 -> 0x29
patch(0x4155fb, [0x83, 0xFA, 0x25], [0x83, 0xFA, 0x29], 'parent role 0x25->0x29');

fs.writeFileSync(FILE, buf);
console.log('v6 patch OK ->', FILE);
console.log('hash:', crypto.createHash('sha256').update(buf).digest('hex'));
