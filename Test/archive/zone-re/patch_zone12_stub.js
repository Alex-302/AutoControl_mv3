// Patch AutoCtrl_2025.4.22.0.exe v5a — ZONE-12 classifier test stub.
// Turns FUN_00415570 (zone-12 check) into "always true" so we can verify
// empirically that the precond reaches the classifier at all.
//
// FUN_00415570 prologue:  push ecx; push esi; mov esi,ecx; push edi
//   415570: 83 ec 1c 56 8b f1 57
//   ... role fetch into [esi+0x2c] ...
//   4155ac: 83 7e 2c 25 75 08     cmp dword [esi+0x2c],0x25; jnz +8
//   4155b2: b0 01                 mov al,1          <- return 1
//   4155b4: 5f 5e 83 c4 1c c3     pop edi; pop esi; add esp,0x1c; ret
//   FAIL path: 415658: 5f 32 c0 5e 83 c4 1c c3  (pop edi; xor al,al; ...)
//
// We overwrite 4155ac..4155b1 (6 bytes: cmp+jnz) with: mov al,1; nop x5
// -> always falls through to the return-1 epilogue. Zone 12 = everywhere.
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

const AT = 0x4155ac;
const SIG = [0x83, 0x7E, 0x2C, 0x25, 0x75, 0x08]; // cmp [esi+0x2c],0x25; jnz +8
const po = off(AT);
const sig = [...buf.subarray(po, po + 6)];
if (JSON.stringify(sig) !== JSON.stringify(SIG)) {
  console.error('SIG MISMATCH @0x' + AT.toString(16) + ': ' + sig.map(b => b.toString(16)).join(' '));
  process.exit(1);
}
// mov al,1; nop x5
buf[po] = 0xB0; buf[po + 1] = 0x01;
for (let i = 2; i < 6; i++) buf[po + i] = 0x90;

fs.writeFileSync(FILE, buf);
console.log('zone-12 STUB patch OK ->', FILE);
console.log('hash:', crypto.createHash('sha256').update(buf).digest('hex'));
