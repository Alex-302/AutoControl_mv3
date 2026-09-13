// Patch AutoCtrl_2025.4.22.0.exe v17b-diag — v17 + role telemetry (type 792).
// ONE-SHOT diagnostic: does the ENGINE's MSAA context see the tab roles
// (37/41) over the tab strip? The v17 stub returns 0 there — we need to
// know if AOP yields null, a wrong role, or the right role (in which case
// the stub logic itself is broken).
//
// The stub sends type 792 with the role it got (or -1 if AOP returned
// null), then continues with the v17 logic (37/41 -> zone true). The 792
// send may corrupt the classifier (RE §9) — acceptable for diagnostics.
//
// Changes:
//   1) 0x415781: jz fail -> 6x NOP                         [gate bypass]
//   2) 0x4157d3: tail call -> `e9 rel32` + nops             [jmp to stub]
//   3) .acp stub (all jump offsets computed automatically):
//      pushad; sub esp,0x18
//      [esp+0]=pAcc  [esp+4]=role  [esp+8..]=scratch  pushad EAX slot=[esp+0x34]
//      EDX=[esp+0x28] (pushad EBX = POINT* event point)
//      FUN_0040b610(ecx=&pAcc, edx=pt)
//      if pAcc: get_accRole (vtable+0x34, this=ecx), send 792(role)
//      else:    send 792(-1)
//      Release pAcc if any; role 0x25||0x29 -> stash 1 else 0 into
//      [esp+0x34]; add esp,0x18; popad; pop edi/esi/ebp/ebx;
//      add esp,0x20; ret
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

// ---- 3) stub (clean emit) ----
const SENDMSG = 0x408600;
const AOP = 0x40b610;
const stub = [];
const w8 = (...a) => stub.push(...a);
const w32 = v => stub.push(v & 0xff, (v >>> 8) & 0xff, (v >>> 16) & 0xff, (v >>> 24) & 0xff);
const callRel = (target) => {
  const at = newVa + stub.length;
  w8(0xE8); w32((target - (at + 5)) >>> 0);
};
const patchDisp = (dispIdx, fromVa, toVa) => { stub[dispIdx] = toVa - (fromVa + 2); };

// pushad; sub esp,0x18
w8(0x60); w8(0x83, 0xEC, 0x18);
// mov edx,[esp+0x28]   ; POINT* (pushad EBX @ E-0x10)
w8(0x8B, 0x54, 0x24, 0x28);
// lea ecx,[esp]
w8(0x8D, 0x0C, 0x24);
callRel(AOP);                               // call FUN_0040b610
// mov eax,[esp]; test eax,eax; jz NULL
w8(0x8B, 0x04, 0x24);
w8(0x85, 0xC0);
const jzNull = stub.length; w8(0x74, 0x00);
// --- pAcc ok ---
// mov ecx,eax (this); mov eax,[ecx] (vtable)
w8(0x8B, 0xC8); w8(0x8B, 0x01);
// push 0 x4 (varChild)
w8(0x6A, 0x00); w8(0x6A, 0x00); w8(0x6A, 0x00); w8(0x6A, 0x00);
// lea edx,[esp+0x14] (&role = E-0x34 when esp=E-0x48)
w8(0x8D, 0x54, 0x24, 0x14);
w8(0x52);
w8(0xFF, 0x50, 0x34);                       // call [eax+0x34] get_accRole
w8(0x83, 0xC4, 0x14);                       // esp=E-0x38
w8(0x8B, 0x44, 0x24, 0x04);                 // eax=role
// send 792(role): variant at [esp+0x10..0x17]
w8(0x89, 0x44, 0x24, 0x0C);                 // [esp+0xC]=role (lVal)
w8(0xC7, 0x44, 0x24, 0x10, 0x01, 0x00, 0x00, 0x00); // vt=1
w8(0x89, 0x44, 0x24, 0x14);                 // [esp+0x14]=role
w8(0xB9, 0x18, 0x03, 0x00, 0x00);           // ecx=792
w8(0x8D, 0x54, 0x24, 0x10);                 // edx=&variant
callRel(SENDMSG);
const jmpChk = stub.length; w8(0xEB, 0x00); // jmp CHECK (fixed below)
// --- NULL path ---
const nullAt = stub.length;
patchDisp(jzNull + 1, newVa + jzNull, newVa + nullAt);
w8(0xC7, 0x44, 0x24, 0x0C, 0xFF, 0xFF, 0xFF, 0xFF); // lVal=-1
w8(0xC7, 0x44, 0x24, 0x10, 0x01, 0x00, 0x00, 0x00);
w8(0xC7, 0x44, 0x24, 0x14, 0xFF, 0xFF, 0xFF, 0xFF);
w8(0xB9, 0x18, 0x03, 0x00, 0x00);
w8(0x8D, 0x54, 0x24, 0x10);
callRel(SENDMSG);
// --- CHECK ---
const chkAt = stub.length;
patchDisp(jmpChk + 1, newVa + jmpChk, newVa + chkAt);
w8(0x8B, 0x44, 0x24, 0x04);                 // eax=role (0 on NULL path)
// Release pAcc if non-null
w8(0x8B, 0x0C, 0x24);                       // ecx=pAcc
w8(0x85, 0xC9);
const jzRel = stub.length; w8(0x74, 0x00);
w8(0x8B, 0x11);                             // edx=vtable
w8(0x51);                                   // push ecx (this)
w8(0xFF, 0x52, 0x08);                       // call Release
w8(0x83, 0xC4, 0x04);
const noRel = stub.length;
patchDisp(jzRel + 1, newVa + jzRel, newVa + noRel);
// role check
w8(0x3D, 0x25, 0x00, 0x00, 0x00);           // cmp eax,0x25
const je1 = stub.length; w8(0x74, 0x00);
w8(0x3D, 0x29, 0x00, 0x00, 0x00);           // cmp eax,0x29
const je2 = stub.length; w8(0x74, 0x00);
// FAIL
const failAt = stub.length;
w8(0xC7, 0x44, 0x24, 0x34, 0x00, 0x00, 0x00, 0x00); // pushad EAX slot=0
const jmpDone = stub.length; w8(0xEB, 0x00);
// PASS
const passAt = stub.length;
patchDisp(je1 + 1, newVa + je1, newVa + passAt);
patchDisp(je2 + 1, newVa + je2, newVa + passAt);
w8(0xC7, 0x44, 0x24, 0x34, 0x01, 0x00, 0x00, 0x00); // pushad EAX slot=1
// DONE
const doneAt = stub.length;
patchDisp(jmpDone + 1, newVa + jmpDone, newVa + doneAt);
w8(0x83, 0xC4, 0x18);                       // add esp,0x18
w8(0x61);                                   // popad
w8(0x5F); w8(0x5E); w8(0x5D); w8(0x5B);     // pop edi/esi/ebp/ebx
w8(0x83, 0xC4, 0x20);
w8(0xC3);                                   // ret
for (let i = 0; i < stub.length; i++) out[newRaw + i] = stub[i];
console.log('stub (' + stub.length + 'B) at 0x' + newVa.toString(16));

fs.writeFileSync(FILE, out);
console.log('v17b-diag patch OK ->', FILE);
console.log('hash:', crypto.createHash('sha256').update(out).digest('hex'));
