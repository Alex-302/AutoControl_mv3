// Patch AutoCtrl_2025.4.22.0.exe v4: add a NEW executable PE section (.acp)
// for the stub (no overwriting of live code — the first attempt crashed the
// engine because the "cave" 0x409570 contained real code Ghidra had not
// mapped).
//
// The stub runs after AccessibleObjectFromPoint in FUN_0040b610:
//   1. get_accName (FUN_0040bdf0) — ALWAYS. This is the Chrome 148+ MSAA
//      tree fix (honey pot + accName, crbug 416429182): the tree comes ON
//      for the whole browser and hover regions 1/3 classify correctly.
//   2. Zone diagnostics (type 792 — MSAA role under the cursor) — GATED by
//      a 1-byte toggle flag in the .acp section (printed below; for this
//      binary: VA 0x4b5000, file offset 0xaac00). 0 = silent (default,
//      production-like), 1 = emit 792. Flip it with --diag-on / --diag-off
//      or patch the single byte with a hex editor.
//
// Usage:
//   node Test/patch_accname.js             → diagnostics OFF (default)
//   node Test/patch_accname.js --diag-on   → diagnostics ON (792 stream)
//   node Test/patch_accname.js --diag-off  → explicit OFF
'use strict';
const fs = require('fs');
const path = require('path');
const crypto = require('crypto');

const DIR = process.env.TEMP + '\\ac_native_re';
const FILE = path.join(DIR, 'AutoCtrl_2025.4.22.0.exe');
const BAK = path.join(DIR, 'AutoCtrl_2025.4.22.0.exe.bak');
const OUT = FILE;

// start from the pristine backup
fs.copyFileSync(BAK, OUT);
const buf = fs.readFileSync(OUT);

// ---- PE parsing ----
const u16 = o => buf.readUInt16LE(o), u32 = o => buf.readUInt32LE(o);
if (u16(0) !== 0x5A4D) throw new Error('not a PE');
const peOff = u32(0x3C);
const numSec = u16(peOff + 6);
const optSize = u16(peOff + 20);
const secOff = peOff + 24 + optSize;
const optMagic = u16(peOff + 24);
const is64 = optMagic === 0x20b;
// PE OptionalHeader: SectionAlignment @+32, FileAlignment @+36 (both PE32/PE32+)
const sectAlignOff = peOff + 24 + 32;
const fileAlignOff = peOff + 24 + 36;
const sizeOfImageOff = peOff + 24 + 56;
const fileAlign = u32(fileAlignOff), sectAlign = u32(sectAlignOff);
const secs = [];
for (let i = 0; i < numSec; i++) {
  const o = secOff + i * 40;
  secs.push({ name: buf.toString('latin1', o, o + 8).replace(/\0/g, ''), va: u32(o + 12), vsize: u32(o + 8), raw: u32(o + 20), rsize: u32(o + 16) });
}
const rva2off = rva => {
  for (const s of secs) if (rva >= s.va && rva < s.va + Math.max(s.vsize, s.rsize)) return s.raw + (rva - s.va);
  throw new Error('rva out: ' + rva.toString(16));
};
const off = a => rva2off(a - 0x400000); // image base
const align = (v, a) => Math.ceil(v / a) * a;

// ---- add a new section ----
const IMG = 0x400000;
const last = secs[secs.length - 1];
const newRaw = align(last.raw + last.rsize, fileAlign);
const newVaRva = align(last.va + Math.max(last.vsize, last.rsize), sectAlign);
const newVa = IMG + newVaRva; // absolute VA for jump math
const NEW_SIZE = 0x2000; // 8 KB stub space
const NEW_CHARS = 0xE0000020; // CODE | EXECUTE | READ | INITIALIZED
console.log('adding section: raw=0x' + newRaw.toString(16) + ' rva=0x' + newVaRva.toString(16) + ' va=0x' + newVa.toString(16) + ' size=0x' + NEW_SIZE.toString(16));

// section header (VirtualAddress = RVA)
const newSecOff = secOff + numSec * 40;
buf.write('.acp', newSecOff, 8, 'latin1');
buf.writeUInt32LE(NEW_SIZE, newSecOff + 8);   // VirtualSize
buf.writeUInt32LE(newVaRva, newSecOff + 12);  // VirtualAddress (RVA)
buf.writeUInt32LE(NEW_SIZE, newSecOff + 16);  // SizeOfRawData
buf.writeUInt32LE(newRaw, newSecOff + 20);    // PointerToRawData
buf.writeUInt32LE(0, newSecOff + 24);         // PointerToRelocations
buf.writeUInt32LE(0, newSecOff + 28);         // PointerToLinenumbers
buf.writeUInt16LE(0, newSecOff + 32);         // NumberOfRelocations
buf.writeUInt16LE(0, newSecOff + 34);         // NumberOfLinenumbers
buf.writeUInt32LE(NEW_CHARS, newSecOff + 36); // Characteristics
buf.writeUInt16LE(numSec + 1, peOff + 6);     // NumberOfSections
buf.writeUInt32LE(newVaRva + NEW_SIZE, sizeOfImageOff); // SizeOfImage

// append section data
const grow = (b, n) => Buffer.concat([b, Buffer.alloc(n)]);
let grown = buf;
if (grown.length < newRaw) grown = grow(grown, newRaw - grown.length);
if (grown.length < newRaw + NEW_SIZE) grown = grow(grown, newRaw + NEW_SIZE - grown.length);
const out = grown;

// ---- patch: FUN_0040b610 after AccessibleObjectFromPoint ----
const PATCH_AT = 0x40b63b;
const PATCH_SIG = [0x8D, 0x44, 0x24, 0x10, 0x50]; // LEA EAX,[ESP+0x10]; PUSH EAX
const GETNAME = 0x40bdf0;   // get_accName helper (fastcall: ecx=&buf, edx=&IAccessible*)
const SENDMSG = 0x408600;   // FUN_00408600(type, contentVariant) -> stdout JSON
const RET_AT = 0x40b640;
const DIAG_TYPE = 0x318;    // 792 — zone/role diagnostics
// Diagnostics toggle: 1 byte in the .acp section, 0x1000 into it (the 8 KB
// section never gets near — the ~97 B stub sits at the start). 0 = 792
// silent (default), 1 = emit 792. The mapped image is read-only for the
// stub (`cmp byte ptr [flag]`) — flipping requires a file-level patch
// (this script or a hex editor).
const DIAG_FLAG_SECTION_OFF = 0x1000;
const diagFlagVa = newVa + DIAG_FLAG_SECTION_OFF;
const diagFlagOff = newRaw + DIAG_FLAG_SECTION_OFF;
const diagOn = process.argv.includes('--diag-on');
const po = off(PATCH_AT);
const sig = [...out.subarray(po, po + 5)];
if (JSON.stringify(sig) !== JSON.stringify(PATCH_SIG)) {
  console.error('SIG MISMATCH @0x' + PATCH_AT.toString(16) + ': ' + sig.map(b => b.toString(16)).join(' '));
  process.exit(1);
}
// stub in the new section:
//   pushad; cmp [esi],0; jz skip
//   sub esp,0x34
//   mov ecx,esp; mov edx,esi; call GETNAME        (accName -> tree ON)
//   mov eax,[esi]; test eax,eax; jz nosend
//   lea edx,[esp+0x20]; push edx; xor eax,eax; push eax x4 (varChild)
//   mov ecx,[esi]; mov eax,[ecx]; call [eax+0x34] (get_accRole)
//   add esp,0x14; mov eax,[esp+0x20]              (role)
//   mov dword[esp+0x24],1; mov [esp+0x2c],eax     (variant int)
//   mov ecx,0x318; lea edx,[esp+0x24]; call SENDMSG
//   nosend: add esp,0x34
//   skip: popad; lea eax,[esp+0x10]; push eax; jmp RET_AT
const stub = [];
const w8 = (...a) => stub.push(...a);
const w32 = v => stub.push(v & 0xff, (v >>> 8) & 0xff, (v >>> 16) & 0xff, (v >>> 24) & 0xff);
w8(0x60);                          // pushad
w8(0x83, 0x3E, 0x00);              // cmp dword [esi],0
const jzSkipIdx = stub.length;
w8(0x74, 0x00);
w8(0x83, 0xEC, 0x34);              // sub esp,0x34
w8(0x8B, 0xCC);                    // mov ecx,esp
w8(0x8B, 0xD6);                    // mov edx,esi
const callNameAt = newVa + stub.length;
w8(0xE8); w32((GETNAME - (callNameAt + 5)) >>> 0);
w8(0x8B, 0x06);                    // mov eax,[esi]
w8(0x85, 0xC0);                    // test eax,eax
const jzNoSendIdx = stub.length;
w8(0x74, 0x00);
// v4 diagnostics toggle: cmp byte ptr [diagFlagVa],0; jz nosend — the
// accName call above stays UNCONDITIONAL (the tree fix); only the 792
// role-fetch + send block is gated by the flag byte.
w8(0x80, 0x3D); w32(diagFlagVa); w8(0x00);
const jzDiagIdx = stub.length;
w8(0x74, 0x00);
w8(0x8D, 0x54, 0x24, 0x20);        // lea edx,[esp+0x20] (&role)
w8(0x52);                          // push edx
w8(0x31, 0xC0);                    // xor eax,eax
w8(0x50); w8(0x50); w8(0x50); w8(0x50); // varChild 16B
w8(0x8B, 0x0E);                    // mov ecx,[esi] (this)
w8(0x8B, 0x09);                    // mov ecx,[ecx] (vtable)
w8(0xFF, 0x51, 0x34);              // call [ecx+0x34] get_accRole
w8(0x83, 0xC4, 0x14);              // add esp,0x14
w8(0x8B, 0x44, 0x24, 0x20);        // mov eax,[esp+0x20] (role)
w8(0xC7, 0x44, 0x24, 0x24, 0x01, 0x00, 0x00, 0x00); // mov dword[esp+0x24],1 (type int)
w8(0x89, 0x44, 0x24, 0x2C);        // mov [esp+0x2c],eax (value)
w8(0xB9, (DIAG_TYPE & 0xff), (DIAG_TYPE >>> 8) & 0xff, 0, 0); // mov ecx,792
w8(0x8D, 0x54, 0x24, 0x24);        // lea edx,[esp+0x24] (&variant)
const callSendAt = newVa + stub.length;
w8(0xE8); w32((SENDMSG - (callSendAt + 5)) >>> 0);
const nosendTarget = newVa + stub.length;
stub[jzNoSendIdx + 1] = nosendTarget - (newVa + jzNoSendIdx + 2);
stub[jzDiagIdx + 1] = nosendTarget - (newVa + jzDiagIdx + 2);
w8(0x83, 0xC4, 0x34);              // nosend: add esp,0x34
stub[jzSkipIdx + 1] = (newVa + stub.length) - (newVa + jzSkipIdx + 2);
w8(0x61);                          // skip: popad
w8(0x8D, 0x44, 0x24, 0x10);        // lea eax,[esp+0x10]
w8(0x50);                          // push eax
const jmpAt = newVa + stub.length;
w8(0xE9); w32((RET_AT - (jmpAt + 5)) >>> 0);
console.log('stub (' + stub.length + 'B) at 0x' + newVa.toString(16) + ': ' + stub.map(b => b.toString(16).padStart(2, '0')).join(' '));

// write stub
for (let i = 0; i < stub.length; i++) out[newRaw + i] = stub[i];
// write the diagnostics toggle byte (0 = off default, 1 = on)
out[diagFlagOff] = diagOn ? 1 : 0;
console.log('diag flag: VA=0x' + diagFlagVa.toString(16) + ' file=0x' + diagFlagOff.toString(16) + ' = ' + out[diagFlagOff] + (diagOn ? ' (ON — 792 emits)' : ' (OFF — 792 silent, default)'));
// write jmp at PATCH_AT
const rel = (newVa - (PATCH_AT + 5)) >>> 0;
out[po] = 0xE9;
out[po + 1] = rel & 0xff; out[po + 2] = (rel >>> 8) & 0xff;
out[po + 3] = (rel >>> 16) & 0xff; out[po + 4] = (rel >>> 24) & 0xff;

fs.writeFileSync(OUT, out);
console.log('patched OK ->', OUT);
// NOTE: hash the PATCHED buffer `out` — hashing `buf` (the pristine copy)
// reported the ORIGINAL hash, not the patched one (fixed in v4).
console.log('size:', out.length, 'hash:', crypto.createHash('sha256').update(out).digest('hex'));
