// Patch AutoCtrl_2025.4.22.0.exe v12 — GEOMETRIC zone-12 classifier.
//
// ROOT CAUSE (proven by v9/v11): the engine's hover cache never refreshes
// over the tab strip (it tracks Chrome_RenderWidgetHostHWND only), so the
// MSAA role path can never classify zone 12 — the tab strip stays "page"
// (zone 3 fires there). The fix: classify zone 12 GEOMETRICALLY — a point
// in the top strip of the browser window (y - top < 70px) is the tab area.
//
// FUN_004156f0 case 0xc tail-call (0x4157d0, 15 bytes):
//   8b cf 5f 5e 5d 5b 83 c4 20 e9 8f fd ff ff
//   (mov ecx,edi; pop edi/esi/ebp/ebx; add esp,0x20; jmp FUN_00415570)
// is replaced with `e9 rel32` + nops -> .acp stub that:
//   - reads hwnd from [esp+0x34] and POINT* from saved EBX
//   - GetWindowRect (IAT 0x4802e0)
//   - returns 1 iff left<=x<=right && 0 <= y-top < 70
//   - then tears down the frame itself (popad; pop x4; add 0x20; ret)
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

// ---- patch the zone-12 tail-call into a jmp to the stub ----
const AT = 0x4157d3;
check(AT, [0x8B, 0xCF, 0x5F, 0x5E, 0x5D, 0x5B, 0x83, 0xC4, 0x20, 0xE9, 0x8F, 0xFD, 0xFF], 'z12 tailcall');
let po = off(AT);
out[po] = 0xE9;
let rel = (newVa - (AT + 5)) >>> 0;
out[po + 1] = rel & 0xff; out[po + 2] = (rel >>> 8) & 0xff;
out[po + 3] = (rel >>> 16) & 0xff; out[po + 4] = (rel >>> 24) & 0xff;
for (let i = 5; i < 13; i++) out[po + i] = 0x90;

// ---- stub ----
// Entry: esp=E (frame of FUN_004156f0 after prologue):
//   [E]=edi [E+4]=esi [E+8]=ebp [E+0xc]=ebx(=POINT*) [E+0x30]=ret [E+0x34]=hwnd
const w8 = (...a) => stub.push(...a);
const w32 = v => stub.push(v & 0xff, (v >>> 8) & 0xff, (v >>> 16) & 0xff, (v >>> 24) & 0xff);
const stub = [];
w8(0x60);                                    // pushad          esp=E-0x20
w8(0x83, 0xEC, 0x10);                        // sub esp,0x10    esp=E-0x30 (RECT)
w8(0x8B, 0x4C, 0x24, 0x64);                  // mov ecx,[esp+0x64] hwnd=[E+0x34]
w8(0x8D, 0x04, 0x24);                        // lea eax,[esp]   &rect
w8(0x50);                                    // push eax
w8(0x51);                                    // push ecx
w8(0xFF, 0x15, 0xE0, 0x02, 0x48, 0x00);      // call GetWindowRect
w8(0x83, 0xC4, 0x08);                        // add esp,8       esp=E-0x30
w8(0x8B, 0x5C, 0x24, 0x1C);                  // mov ebx,[esp+0x1c] POINT*=[E-0x14]
w8(0x8B, 0x03);                              // mov eax,[ebx]   x
w8(0x8B, 0x13);                              // mov edx,[ebx+4] y
w8(0x3B, 0x04, 0x24);                        // cmp eax,[esp]   x vs left
const jl = stub.length; w8(0x7C, 0x00);
w8(0x3B, 0x44, 0x24, 0x08);                  // cmp eax,[esp+8] x vs right
const jg = stub.length; w8(0x7F, 0x00);
w8(0x8B, 0x4C, 0x24, 0x04);                  // mov ecx,[esp+4] top
w8(0x2B, 0xD1);                              // sub edx,ecx    dy=y-top
w8(0x83, 0xFA, 0x46);                        // cmp edx,0x46   70
const jg2 = stub.length; w8(0x7F, 0x00);
w8(0xB0, 0x01);                              // mov al,1
w8(0xEB, 0x02);                              // jmp DONE
const failAt = stub.length;
for (const j of [jl, jg, jg2]) stub[j + 1] = failAt - (newVa + j + 2);
w8(0x32, 0xC0);                              // xor al,al
const doneAt = stub.length;                   // DONE
w8(0x83, 0xC4, 0x10);                        // add esp,0x10    esp=E-0x20
w8(0x61);                                    // popad           regs restored
w8(0x83, 0xC4, 0x20);                        // add esp,0x20    esp=E
w8(0x5F);                                    // pop edi
w8(0x5E);                                    // pop esi
w8(0x5D);                                    // pop ebp
w8(0x5B);                                    // pop ebx
w8(0x83, 0xC4, 0x20);                        // add esp,0x20    esp=E+0x30
w8(0xC3);                                    // ret
for (let i = 0; i < stub.length; i++) out[newRaw + i] = stub[i];
console.log('stub (' + stub.length + 'B) at 0x' + newVa.toString(16));

fs.writeFileSync(FILE, out);
console.log('v12 patch OK ->', FILE);
console.log('hash:', crypto.createHash('sha256').update(out).digest('hex'));
