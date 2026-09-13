// Patch AutoCtrl_2025.4.22.0.exe v14 — GEOMETRIC zone-12 classifier + gate bypass.
//
// v13 missed the FUN_00414760 gate bypass! The zone-12 path first calls
// FUN_00414760(point, hwnd, 10) and `jz fail`s when it returns 0 — and on
// Chrome 150 the monitor-scaled rect cache in that function returns 0 over
// the tab strip (proven earlier). v5b/v10 NOPed that gate; v13 did not, so
// the geometric stub was never reached. v14 = v13 + the gate bypass.
//
// Changes:
//   1) 0x415781: `0f 84 69 03 00 00` (jz 0x415af0 fail) -> 6x NOP
//   2) 0x4157d3: tail call (13 bytes) -> `e9 rel32` + nops into .acp stub
//   3) .acp stub: GetWindowRect(hwnd,&r); return 1 iff
//      left<=x<=right && 0 <= y-top < 70 (tab strip = top band of window);
//      result stashed into the pushad EAX slot so popad restores AL;
//      then the original frame teardown: popad; pop edi/esi/ebp/ebx;
//      add esp,0x20; ret.
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

// ---- 1) gate bypass: jz fail -> nops ----
check(0x415781, [0x0F, 0x84, 0x69, 0x03, 0x00, 0x00], 'gate jz');
let po = off(0x415781);
for (let i = 0; i < 6; i++) out[po + i] = 0x90;

// ---- 2) zone-12 tail call (0x4157d3) -> jmp into stub ----
const AT = 0x4157d3;
check(AT, [0x8B, 0xCF, 0x5F, 0x5E, 0x5D, 0x5B, 0x83, 0xC4, 0x20, 0xE9, 0x8F, 0xFD, 0xFF], 'z12 tailcall');
po = off(AT);
out[po] = 0xE9;
let rel = (newVa - (AT + 5)) >>> 0;
out[po + 1] = rel & 0xff; out[po + 2] = (rel >>> 8) & 0xff;
out[po + 3] = (rel >>> 16) & 0xff; out[po + 4] = (rel >>> 24) & 0xff;
for (let i = 5; i < 13; i++) out[po + i] = 0x90;

// ---- 3) stub ----
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
w8(0x8B, 0x5C, 0x24, 0x20);                  // mov ebx,[esp+0x20] POINT*=[E-0x10] (pushad EBX slot)
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
// PASS: stash 1 into the pushad EAX slot ([esp+0x2c] at esp=E-0x30)
w8(0xC7, 0x44, 0x24, 0x2C, 0x01, 0x00, 0x00, 0x00);
w8(0xEB, 0x0A);                              // jmp DONE
const failAt = stub.length;
for (const j of [jl, jg, jg2]) stub[j + 1] = failAt - (newVa + j + 2);
// FAIL: stash 0
w8(0xC7, 0x44, 0x24, 0x2C, 0x00, 0x00, 0x00, 0x00);
const doneAt = stub.length;                   // DONE
w8(0x83, 0xC4, 0x10);                        // add esp,0x10    esp=E-0x20 (drop RECT)
w8(0x61);                                    // popad           restores regs; EAX(AL)=result; esp=E
w8(0x5F);                                    // pop edi         (original frame)
w8(0x5E);                                    // pop esi
w8(0x5D);                                    // pop ebp
w8(0x5B);                                    // pop ebx
w8(0x83, 0xC4, 0x20);                        // add esp,0x20    esp=E+0x30
w8(0xC3);                                    // ret
for (let i = 0; i < stub.length; i++) out[newRaw + i] = stub[i];
console.log('stub (' + stub.length + 'B) at 0x' + newVa.toString(16));

fs.writeFileSync(FILE, out);
console.log('v14 patch OK ->', FILE);
console.log('hash:', crypto.createHash('sha256').update(out).digest('hex'));
