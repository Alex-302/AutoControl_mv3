// Patch AutoCtrl_2025.4.22.0.exe v17 — SELECTIVE zone-12 via FRESH AOP.
//
// Root cause recap: the engine's hover cache (FUN_00415240) only refreshes
// when the tracked position changes, and the LL-hook only tracks positions
// over the PAGE window (Chrome_RenderWidgetHostHWND) — over the tab strip
// the cache stays "page" (role 15 DOCUMENT), so role-based checks (v9)
// always failed. v16 (always-1) proved the zone-12 path DOES run over the
// tab strip (750 fires) — the event point is available.
//
// v17: in the zone-12 check, instead of reading the STALE cache, do a
// FRESH AccessibleObjectFromPoint via the engine's own wrapper
// FUN_0040b610(ecx=&pAcc, edx=POINT*) with the EVENT point (EBX =
// FUN_004156f0 param_1), then get_accRole (vtable+0x34); if the role is
// 0x25 (37 TABITEM) or 0x29 (41 tab cell) → zone 12 true; else false.
// This is exactly what Test/zone_proto.ps1 proved works from a fresh
// process — now done inside the engine on the hot path.
//
// Changes:
//   1) 0x415781: jz fail (0F 84 69 03 00 00) -> 6x NOP   [gate bypass]
//   2) 0x4157d3: tail call (13 bytes) -> `e9 rel32` + nops [jmp to stub]
//   3) .acp stub (see the build comments for the exact bytes):
//        pushad; sub esp,8; fresh AOP; get_accRole; Release;
//        role==0x25||0x29 -> stash 1 else 0 into the pushad EAX slot;
//        teardown: add esp,8; popad; pop edi/esi/ebp/ebx; add esp,0x20; ret
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

// ---- 2) zone-12 tail call -> jmp into stub ----
const AT = 0x4157d3;
check(AT, [0x8B, 0xCF, 0x5F, 0x5E, 0x5D, 0x5B, 0x83, 0xC4, 0x20, 0xE9, 0x8F, 0xFD, 0xFF], 'z12 tailcall');
po = off(AT);
out[po] = 0xE9;
let rel = (newVa - (AT + 5)) >>> 0;
out[po + 1] = rel & 0xff; out[po + 2] = (rel >>> 8) & 0xff;
out[po + 3] = (rel >>> 16) & 0xff; out[po + 4] = (rel >>> 24) & 0xff;
for (let i = 5; i < 13; i++) out[po + i] = 0x90;

// ---- 3) stub ----
// Entry: esp=E (frame after FUN_004156f0 prologue):
//   [E+0x20]=edi [E+0x24]=esi [E+0x28]=ebp [E+0x2C]=ebx=POINT* (event point)
//   [E+0x30]=ret [E+0x34]=hwnd
// pushad -> esp=E-0x20; sub esp,8 -> esp=E-0x28:
//   [E-0x28]=pAcc, [E-0x24]=role, pushad EAX slot at [E-0x04]=[esp+0x24]
const w8 = (...a) => stub.push(...a);
const w32 = v => stub.push(v & 0xff, (v >>> 8) & 0xff, (v >>> 16) & 0xff, (v >>> 24) & 0xff);
const stub = [];
w8(0x60);                                    // pushad           esp=E-0x20
w8(0x83, 0xEC, 0x08);                        // sub esp,8        esp=E-0x28
w8(0x8B, 0x54, 0x24, 0x18);                  // mov edx,[esp+0x18] EDX=EBX=POINT* (pushad EBX slot @ E-0x10)
w8(0x8D, 0x0C, 0x24);                        // lea ecx,[esp]    &pAcc
const aopCallAt = newVa + stub.length;        // address of the E8 instruction
w8(0xE8); w32((0x40b610 - (aopCallAt + 5)) >>> 0); // call FUN_0040b610
w8(0x8B, 0x0C, 0x24);                        // mov ecx,[esp]    pAcc
w8(0x85, 0xC9);                              // test ecx,ecx
const jzFail = stub.length; w8(0x74, 0x00);  // jz FAIL1
w8(0x8B, 0x01);                              // mov eax,[ecx]    vtable
w8(0x6A, 0x00); w8(0x6A, 0x00); w8(0x6A, 0x00); w8(0x6A, 0x00); // varChild 16B (esp=E-0x38)
w8(0x8D, 0x54, 0x24, 0x14);                  // lea edx,[esp+0x14] &role (E-0x24)
w8(0x52);                                    // push edx
w8(0xFF, 0x50, 0x34);                        // call [eax+0x34]   get_accRole (vtable in EAX, this=ECX)
w8(0x83, 0xC4, 0x14);                        // add esp,0x14     esp=E-0x28
w8(0x8B, 0x44, 0x24, 0x04);                  // mov eax,[esp+4]   role
w8(0x8B, 0x0C, 0x24);                        // mov ecx,[esp]    pAcc
w8(0x8B, 0x11);                              // mov edx,[ecx]    vtable
w8(0x51);                                    // push ecx         (this for Release)
w8(0xFF, 0x52, 0x08);                        // call [edx+8]     Release
w8(0x83, 0xC4, 0x04);                        // add esp,4
w8(0x3D, 0x25, 0x00, 0x00, 0x00);            // cmp eax,0x25
const jePass1 = stub.length; w8(0x74, 0x00);
w8(0x3D, 0x29, 0x00, 0x00, 0x00);            // cmp eax,0x29
const jePass2 = stub.length; w8(0x74, 0x00);
const failAt = stub.length;                   // FAIL1 / fail path
for (const j of [jzFail]) stub[j + 1] = failAt - (newVa + j + 2);
w8(0xC7, 0x44, 0x24, 0x24, 0x00, 0x00, 0x00, 0x00); // [esp+0x24]=0 (pushad EAX slot)
const jmpDoneAt = stub.length;                // position of the EB instruction
w8(0xEB, 0x00);                              // jmp DONE (disp fixed below)
const passAt = stub.length;                   // PASS
for (const j of [jePass1, jePass2]) stub[j + 1] = passAt - (newVa + j + 2);
w8(0xC7, 0x44, 0x24, 0x24, 0x01, 0x00, 0x00, 0x00); // [esp+0x24]=1
const doneAt = stub.length;                   // DONE
stub[jmpDoneAt + 1] = (newVa + doneAt) - (newVa + jmpDoneAt + 2); // fix jmp disp
w8(0x83, 0xC4, 0x08);                        // add esp,8        esp=E-0x20
w8(0x61);                                    // popad            regs back; AL=result; esp=E
w8(0x5F);                                    // pop edi
w8(0x5E);                                    // pop esi
w8(0x5D);                                    // pop ebp
w8(0x5B);                                    // pop ebx
w8(0x83, 0xC4, 0x20);                        // add esp,0x20
w8(0xC3);                                    // ret
for (let i = 0; i < stub.length; i++) out[newRaw + i] = stub[i];
console.log('stub (' + stub.length + 'B) at 0x' + newVa.toString(16));

fs.writeFileSync(FILE, out);
console.log('v17 patch OK ->', FILE);
console.log('hash:', crypto.createHash('sha256').update(out).digest('hex'));
