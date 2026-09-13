// Patch AutoCtrl_2025.4.22.0.exe v9 — SELECTIVE zone-12 classifier fix.
// v7's logic (stub: hovered role ∈ {0x25,0x29,0x3c,0x10} → zone 12 true,
// else original parent path with cmp 0x25) but with the section-add bug
// fixed (last.rs NOT last.rsize — v7's stub never got written, the jmp
// went into zeros) and WITHOUT the 792 send (v8diag proved the send from
// the classifier corrupts the whole zone classification — RE doc §9).
//
// Changes:
//   1) 0x415781: jz fail (0F 84 69 03 00 00) -> 6x NOP  [gate bypass]
//   2) 0x4155ac: `83 7e 2c 25 75 08` -> `e9 rel32; 90` (jmp into .acp stub)
//   3) .acp stub:
//        pushad
//        mov eax,[esi+0x2c]          ; hovered role (cached)
//        cmp eax,0x25  je PASS       ; 37 (old Chrome tab)
//        cmp eax,0x29  je PASS       ; 41 (Chrome 148+ tab)
//        cmp eax,0x3c  je PASS       ; 60 (strip container)
//        cmp eax,0x10  je PASS       ; 16 (strip LIST)
//        popad
//        jmp 0x4155ba                ; original parent path (cmp stays 0x25)
//      PASS:
//        popad
//        jmp 0x4155b2                ; mov al,1 epilogue -> return 1
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

// ---- 2) jmp into stub ----
check(0x4155ac, [0x83, 0x7E, 0x2C, 0x25, 0x75, 0x08], 'hovered cmp');
po = off(0x4155ac);
out[po] = 0xE9;
let rel = (newVa - (0x4155ac + 5)) >>> 0;
out[po + 1] = rel & 0xff; out[po + 2] = (rel >>> 8) & 0xff;
out[po + 3] = (rel >>> 16) & 0xff; out[po + 4] = (rel >>> 24) & 0xff;
out[po + 5] = 0x90;

// ---- 3) stub ----
const w8 = (...a) => stub.push(...a);
const w32 = v => stub.push(v & 0xff, (v >>> 8) & 0xff, (v >>> 16) & 0xff, (v >>> 24) & 0xff);
const stub = [];
w8(0x60);                                    // pushad
w8(0x8B, 0x46, 0x2C);                        // mov eax,[esi+0x2c]
w8(0x3D, 0x25, 0x00, 0x00, 0x00);            // cmp eax,0x25
let je1 = stub.length; w8(0x74, 0x00);
w8(0x3D, 0x29, 0x00, 0x00, 0x00);            // cmp eax,0x29
let je2 = stub.length; w8(0x74, 0x00);
w8(0x3D, 0x3C, 0x00, 0x00, 0x00);            // cmp eax,0x3c
let je3 = stub.length; w8(0x74, 0x00);
w8(0x3D, 0x10, 0x00, 0x00, 0x00);            // cmp eax,0x10
let je4 = stub.length; w8(0x74, 0x00);
w8(0x61);                                    // popad
const jmpFailAt = newVa + stub.length;
w8(0xE9); w32((0x4155ba - (jmpFailAt + 5)) >>> 0);  // -> parent path
const passAt = newVa + stub.length;
for (const j of [je1, je2, je3, je4]) stub[j + 1] = passAt - (newVa + j + 2);
w8(0x61);                                    // popad
const jmpPassAt = newVa + stub.length;
w8(0xE9); w32((0x4155b2 - (jmpPassAt + 5)) >>> 0);  // -> return-1 epilogue
for (let i = 0; i < stub.length; i++) out[newRaw + i] = stub[i];
console.log('stub (' + stub.length + 'B) at 0x' + newVa.toString(16));

fs.writeFileSync(FILE, out);
console.log('v9 patch OK ->', FILE);
console.log('hash:', crypto.createHash('sha256').update(out).digest('hex'));
