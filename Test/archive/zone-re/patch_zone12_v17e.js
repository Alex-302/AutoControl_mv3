// Patch AutoCtrl_2025.4.22.0.exe v17e — ISOLATION: always-1 via the
// tail-call site (0x4157d3) WITHOUT any AOP call.
//
// v16 (patch inside FUN_00415570 @0x4155ac) fires zone-12 750 everywhere;
// v17 (same tail-call replaced by a fresh-AOP stub) fires NOTHING and
// sends no 792. Two explanations: (a) the tail-call site is not executed
// (FUN_00415570 reached another way), or (b) the stub IS executed but
// AccessibleObjectFromPoint (FUN_0040b610) crashes the engine before the
// 792 send. v17e replaces the tail-call with an always-1 stub (no AOP):
//   - 750 fires everywhere  -> the tail-call IS the path; AOP crashes.
//   - no 750                -> the tail-call is NOT the path (v16 works
//     through something else — need to re-check where FUN_00415570 is
//     really called from).
//
// Changes:
//   1) 0x415781: jz fail -> 6x NOP                         [gate bypass]
//   2) 0x4157d3: tail call -> `e9 rel32` + nops             [jmp to stub]
//   3) .acp stub: pushad; stash 1 into the pushad EAX slot;
//      popad; pop edi/esi/ebp/ebx; add esp,0x20; ret
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

// ---- add the .acp section ----
const IMG = 0x400000;
const last = secs[secs.length - 1];
const fileAlign = u32(pe + 24 + 36), sectAlign = u32(pe + 24 + 32);
const newRaw = Math.ceil((last.raw + last.rs) / fileAlign) * fileAlign;
const newVaRva = Math.ceil((last.va + Math.max(last.vs, last.rs)) / sectAlign) * sectAlign;
const newVa = IMG + newVaRva;
const NEW_SIZE = 0x2000;
const NEW_CHARS = 0xE0000020;
const newSecOff = secOff + numSec * 40;
buf.write('.acp', newSecOff, 8, 'latin1');
buf.writeUInt32LE(NEW_SIZE, newSecOff + 8);
buf.writeUInt32LE(newVaRva, newSecOff + 12);
buf.writeUInt32LE(NEW_SIZE, newSecOff + 16);
buf.writeUInt32LE(newRaw, newSecOff + 20);
buf.writeUInt32LE(0, newSecOff + 24);
buf.writeUInt32LE(0, newSecOff + 28);
buf.writeUInt16LE(0, newSecOff + 32);
buf.writeUInt16LE(0, newSecOff + 34);
buf.writeUInt32LE(NEW_CHARS, newSecOff + 36);
buf.writeUInt16LE(numSec + 1, pe + 6);
buf.writeUInt32LE(newVaRva + NEW_SIZE, pe + 24 + 56);
let grown = buf;
if (grown.length < newRaw) grown = Buffer.concat([grown, Buffer.alloc(newRaw - grown.length)]);
if (grown.length < newRaw + NEW_SIZE) grown = Buffer.concat([grown, Buffer.alloc(newRaw + NEW_SIZE - grown.length)]);
const out = grown;

// ---- 1) gate bypass ----
check(0x415781, [0x0F, 0x84, 0x69, 0x03, 0x00, 0x00], 'gate jz');
let po = off(0x415781);
for (let i = 0; i < 6; i++) out[po + i] = 0x90;

// ---- 2) tail call -> jmp into stub ----
const AT = 0x4157d3;
check(AT, [0x8B, 0xCF, 0x5F, 0x5E, 0x5D, 0x5B, 0x83, 0xC4, 0x20, 0xE9, 0x8F, 0xFD, 0xFF], 'z12 tailcall');
po = off(AT);
out[po] = 0xE9;
let rel = (newVa - (AT + 5)) >>> 0;
out[po + 1] = rel & 0xff; out[po + 2] = (rel >>> 8) & 0xff;
out[po + 3] = (rel >>> 16) & 0xff; out[po + 4] = (rel >>> 24) & 0xff;
for (let i = 5; i < 13; i++) out[po + i] = 0x90;

// ---- 3) stub: always 1, no AOP ----
const stub = [];
const w8 = (...a) => stub.push(...a);
const w32 = v => stub.push(v & 0xff, (v >>> 8) & 0xff, (v >>> 16) & 0xff, (v >>> 24) & 0xff);
w8(0x60);                                    // pushad          esp=E-0x20
w8(0xC7, 0x44, 0x24, 0x1C, 0x01, 0x00, 0x00, 0x00); // [esp+0x1C]=1 (pushad EAX slot)
w8(0x61);                                    // popad           esp=E; AL=1
w8(0x5F); w8(0x5E); w8(0x5D); w8(0x5B);     // pop edi/esi/ebp/ebx
w8(0x83, 0xC4, 0x20);                        // add esp,0x20
w8(0xC3);                                    // ret
for (let i = 0; i < stub.length; i++) out[newRaw + i] = stub[i];
console.log('stub (' + stub.length + 'B) at 0x' + newVa.toString(16));

fs.writeFileSync(FILE, out);
console.log('v17e patch OK ->', FILE);
console.log('hash:', crypto.createHash('sha256').update(out).digest('hex'));
