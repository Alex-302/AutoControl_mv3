// analyze_zones.js - inspect the ORIGINAL engine around the zone classifier.
//
// Goal: decide how to patch FUN_004156f0 (the mouseOver zone classifier) so the
// engine stops rejecting zones it cannot classify (15 close / 17 speaker /
// 16 plus ...). Prints:
//   - the v16 patch signature bytes (to confirm the base build),
//   - the FUN_004156f0 entry bytes,
//   - every call site of FUN_004156f0 with the following instructions
//     (reveals the calling convention: stack cleanup by caller = cdecl-like,
//      no cleanup = __fastcall/__stdcall with callee cleanup),
//   - the FUN_00415570 (zone-12 role check) bytes patched by v16.
//
// Usage: node Test/analyze_zones.js
'use strict';
const fs = require('fs');
const path = require('path');

const F = process.argv[2] || path.join(process.env.LOCALAPPDATA, 'AutoControl', 'AutoCtrl_2025.4.22.0.exe.orig');
const buf = fs.readFileSync(F);
const u16 = o => buf.readUInt16LE(o), u32 = o => buf.readUInt32LE(o);
const pe = u32(0x3C);
const nSec = u16(pe + 6), optSize = u16(pe + 20);
const secOff = pe + 24 + optSize;
const secs = [];
for (let i = 0; i < nSec; i++) {
  const o = secOff + i * 40;
  secs.push({ name: buf.toString('ascii', o, o + 8).replace(/\0+$/, ''), va: u32(o + 12), vs: u32(o + 8), raw: u32(o + 20), rs: u32(o + 16) });
}
const toOff = a => {
  const r = a - 0x400000;
  for (const s of secs) if (r >= s.va && r < s.va + Math.max(s.vs, s.rs)) return s.raw + (r - s.va);
  throw new Error('VA out of range 0x' + a.toString(16));
};
const hex = (va, n) => [...buf.subarray(toOff(va), toOff(va) + n)].map(b => b.toString(16).padStart(2, '0')).join(' ');

console.log('file:', F);
console.log('sections:', secs.map(s => s.name + '@0x' + s.va.toString(16)).join(', '));
console.log('');
console.log('v16 sig @0x415781 (gate jz):   ', hex(0x415781, 6), '  [expect 0f 84 69 03 00 00]');
console.log('v16 sig @0x4155ac (zone12):    ', hex(0x4155ac, 6), '  [expect 83 7e 2c 25 75 08]');
console.log('FUN_004156f0 entry @0x4156f0:  ', hex(0x4156f0, 12));
console.log('');

// call sites of FUN_004156f0
const TARGET = 0x4156f0;
let found = 0;
for (const s of secs) {
  if (!(s.va <= TARGET - 0x400000 && TARGET - 0x400000 < s.va + Math.max(s.vs, s.rs))) continue;
  for (let i = 0; i < s.rs - 5; i++) {
    const o = s.raw + i;
    if (buf[o] !== 0xE8) continue;
    const rel = buf.readInt32LE(o + 1);
    const tgt = 0x400000 + s.va + (o - s.raw) + 5 + rel;
    if (tgt !== TARGET) continue;
    found++;
    const va = 0x400000 + s.va + (o - s.raw);
    console.log('call @0x' + va.toString(16) + '  before: ' + hex(va - 8, 8) + '   after: ' + hex(va + 5, 10));
  }
}
console.log('call sites: ' + found);
console.log('');
// nearby code of FUN_00415570-zone12 check patched by v16: show bytes around 0x4155a0
console.log('bytes 0x415590..0x4155c0: ' + hex(0x415590, 0x30));
