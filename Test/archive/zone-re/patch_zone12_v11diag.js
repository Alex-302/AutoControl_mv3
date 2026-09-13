// Patch AutoCtrl_2025.4.22.0.exe v11-diag — role telemetry from INSIDE the
// engine. v10 proved the .acp jmp works; v9 failed because the roles the
// ENGINE sees over the tab strip are not {0x25,0x29,0x3c,0x10} (the
// PowerShell probe sees 41/37 — a different MSAA client context!).
//
// This build sends type 792 with the REAL hovered role from FUN_0040b610
// (the AccessibleObjectFromPoint wrapper — the same spot v4-diag used,
// where the 792 stream worked) WITHOUT the accName call (which crashed).
// Plus the zone-12 classifier returns 1 always (like v5b) so the zone
// still fires while we observe.
//
// Changes:
//   1) 0x415781: jz fail -> 6x NOP                        [gate bypass]
//   2) 0x4155ac: `83 7e 2c 25 75 08` -> `b0 01 90 90 90 90` [always 1]
//   3) 0x40b63b: jmp into .acp stub (after AOP) that reads the role via
//      get_accRole (vtable+0x34) and sends type 792 (FUN_00408600), then
//      restores and continues at 0x40b640 (VariantClear).
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

// ---- 2) zone-12 classifier: always return 1 (v5b style, in-place) ----
check(0x4155ac, [0x83, 0x7E, 0x2C, 0x25, 0x75, 0x08], 'hovered cmp');
po = off(0x4155ac);
out[po] = 0xB0; out[po + 1] = 0x01;
for (let i = 2; i < 6; i++) out[po + i] = 0x90;

// ---- 3) AOP-wrapper stub: role -> 792 ----
// FUN_0040b610 prologue: push esi; mov esi,ecx ... AOP ...
// at 0x40b63b: lea eax,[esp+0x10]; push eax (for VariantClear)
//   esi = param_1 = &IAccessible* (filled by AOP)
const PATCH_AT = 0x40b63b;
const RET_AT = 0x40b640;
const SENDMSG = 0x408600;
check(PATCH_AT, [0x8D, 0x44, 0x24, 0x10, 0x50], 'aop lea');
po = off(PATCH_AT);
out[po] = 0xE9;
let rel = (newVa - (PATCH_AT + 5)) >>> 0;
out[po + 1] = rel & 0xff; out[po + 2] = (rel >>> 8) & 0xff;
out[po + 3] = (rel >>> 16) & 0xff; out[po + 4] = (rel >>> 24) & 0xff;

const w8 = (...a) => stub.push(...a);
const w32 = v => stub.push(v & 0xff, (v >>> 8) & 0xff, (v >>> 16) & 0xff, (v >>> 24) & 0xff);
const stub = [];
w8(0x60);                          // pushad
w8(0x83, 0x3E, 0x00);              // cmp dword [esi],0
const jzSkip = stub.length;
w8(0x74, 0x00);
w8(0x83, 0xEC, 0x34);              // sub esp,0x34
w8(0x8B, 0x06);                    // mov eax,[esi] (IAccessible*)
w8(0x85, 0xC0);                    // test eax,eax
const jzNoSend = stub.length;
w8(0x74, 0x00);
w8(0x8D, 0x54, 0x24, 0x20);        // lea edx,[esp+0x20] (&role var)
w8(0x52);                          // push edx
w8(0x31, 0xC0);                    // xor eax,eax
w8(0x50); w8(0x50); w8(0x50); w8(0x50); // varChild (16B)
w8(0x8B, 0x0E);                    // mov ecx,[esi] (this)
w8(0x8B, 0x09);                    // mov ecx,[ecx] (vtable)
w8(0xFF, 0x51, 0x34);              // call [ecx+0x34] get_accRole
w8(0x83, 0xC4, 0x14);              // add esp,0x14
w8(0x8B, 0x44, 0x24, 0x20);        // mov eax,[esp+0x20] (role)
w8(0xC7, 0x44, 0x24, 0x24, 0x01, 0x00, 0x00, 0x00); // [esp+0x24]=1 (vt int)
w8(0x89, 0x44, 0x24, 0x2C);        // [esp+0x2c]=eax (value)
w8(0xB9, 0x18, 0x03, 0x00, 0x00);  // mov ecx,0x318 (792)
w8(0x8D, 0x54, 0x24, 0x24);        // lea edx,[esp+0x24] (&variant)
const callAt = newVa + stub.length;
w8(0xE8); w32((SENDMSG - (callAt + 5)) >>> 0); // call FUN_00408600
const noSendTarget = newVa + stub.length;
stub[jzNoSend + 1] = noSendTarget - (newVa + jzNoSend + 2);
w8(0x83, 0xC4, 0x34);              // add esp,0x34
stub[jzSkip + 1] = (newVa + stub.length) - (newVa + jzSkip + 2);
w8(0x61);                          // popad
w8(0x8D, 0x44, 0x24, 0x10);        // lea eax,[esp+0x10]
w8(0x50);                          // push eax
const jmpAt = newVa + stub.length;
w8(0xE9); w32((RET_AT - (jmpAt + 5)) >>> 0); // jmp 0x40b640 (VariantClear)
for (let i = 0; i < stub.length; i++) out[newRaw + i] = stub[i];
console.log('stub (' + stub.length + 'B) at 0x' + newVa.toString(16));

fs.writeFileSync(FILE, out);
console.log('v11-diag patch OK ->', FILE);
console.log('hash:', crypto.createHash('sha256').update(out).digest('hex'));
