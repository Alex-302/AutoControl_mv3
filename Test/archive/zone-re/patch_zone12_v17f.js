// Patch AutoCtrl_2025.4.22.0.exe v17f — AOP-isolation diagnostic.
// v17e (always-1 via the tail-call) fires 750 everywhere -> the tail-call
// IS the path. v17/v17b (fresh AOP + get_accRole + 792 after) fire
// NOTHING -> one of those calls breaks the engine. v17f sends 792 TWICE:
//   first 792: 1 if AOP returned an object, 0 if null   (right after AOP)
//   second 792: the get_accRole value                    (after the role)
// then classifies 37/41 -> zone true. This localizes the crashing call.
//
// Changes:
//   1) 0x415781: jz fail -> 6x NOP                         [gate bypass]
//   2) 0x4157d3: tail call -> `e9 rel32` + nops             [jmp to stub]
//   3) .acp stub: pushad; sub esp,0x18;
//      EDX=[esp+0x18] (pushad EBX = POINT* event point)
//      FUN_0040b610(ecx=&pAcc, edx=pt)
//      send 792(pAcc!=null ? 1 : 0)
//      if pAcc: get_accRole (vtable+0x34); send 792(role); Release
//      role 0x25||0x29 -> stash 1 else 0 into pushad EAX slot;
//      teardown (same as v17e).
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

// ---- 3) stub ----
const SENDMSG = 0x408600;
const AOP = 0x40b610;
const stub = [];
const w8 = (...a) => stub.push(...a);
const w32 = v => stub.push(v & 0xff, (v >>> 8) & 0xff, (v >>> 16) & 0xff, (v >>> 24) & 0xff);
const callRel = (target) => { const at = newVa + stub.length; w8(0xE8); w32((target - (at + 5)) >>> 0); };
const patchDisp = (dispIdx, fromVa, toVa) => { stub[dispIdx] = toVa - (fromVa + 2); };
// send792(value in EAX, variant at [esp+0x10..]): clobbers nothing but EAX/ECX/EDX
const send792 = () => {
  w8(0x89, 0x44, 0x24, 0x0C);                 // [esp+0xC]=value (lVal)
  w8(0xC7, 0x44, 0x24, 0x10, 0x01, 0x00, 0x00, 0x00); // vt=1
  w8(0x89, 0x44, 0x24, 0x14);                 // [esp+0x14]=value
  w8(0xB9, 0x18, 0x03, 0x00, 0x00);           // ecx=792
  w8(0x8D, 0x54, 0x24, 0x10);                 // edx=&variant
  callRel(SENDMSG);
};

// pushad; sub esp,0x18  (esp=E-0x38: [0]=pAcc [4]=role [8..]=scratch; pushad EAX slot=[esp+0x34])
w8(0x60); w8(0x83, 0xEC, 0x18);
// mov edx,[esp+0x18]  ; POINT* (pushad EBX @ E-0x10)
w8(0x8B, 0x54, 0x24, 0x18);
// lea ecx,[esp]
w8(0x8D, 0x0C, 0x24);
callRel(AOP);                                // call FUN_0040b610
// send 792(pAcc!=null)
w8(0x8B, 0x04, 0x24);                        // eax=pAcc
w8(0x85, 0xC0);
const jzNull = stub.length; w8(0x74, 0x00);  // jz NULL
w8(0xB8, 0x01, 0x00, 0x00, 0x00);            // eax=1
send792();
w8(0xEB, 0x08);                              // jmp ROLE (fixed below)
const nullAt = stub.length;
patchDisp(jzNull + 1, newVa + jzNull, newVa + nullAt);
w8(0x31, 0xC0);                              // eax=0
send792();
const roleAt = stub.length;                   // ROLE (fix the EB above)
stub[nullAt - 2 + 1] = roleAt - (nullAt - 2 + 2);
// role path: ecx=this=pAcc; eax=vtable
w8(0x8B, 0x0C, 0x24);                        // ecx=pAcc
w8(0x85, 0xC9);
const jzSkip = stub.length; w8(0x74, 0x00);  // jz CHECK (no role)
w8(0x8B, 0x01);                              // eax=vtable
w8(0x6A, 0x00); w8(0x6A, 0x00); w8(0x6A, 0x00); w8(0x6A, 0x00); // varChild
w8(0x8D, 0x54, 0x24, 0x1C);                  // lea edx,[esp+0x1C] &role (esp=E-0x48 -> E-0x2C? NO: E-0x48+0x1C=E-0x2C; role slot is [esp+4]=E-0x34 -> [esp+0x14])
w8(0x8D, 0x54, 0x24, 0x14);                  // &role = E-0x34 (esp=E-0x48 after 4 push + 1? see below)
// NOTE: after 4 push esp=E-0x48; then push &role -> E-0x4C. &role should be E-0x34 = [esp+0x18] at that point.
// redo cleanly below instead of patching this — see final emit.
for (let i = 0; i < stub.length; i++) out[newRaw + i] = 0; // wipe; will re-emit
// ============ FINAL CLEAN EMIT ============
const s2 = [];
const P = (...a) => s2.push(...a);
const P32 = v => s2.push(v & 0xff, (v >>> 8) & 0xff, (v >>> 16) & 0xff, (v >>> 24) & 0xff);
const callR2 = (t) => { const at = newVa + s2.length; P(0xE8); P32((t - (at + 5)) >>> 0); };
const fixDisp = (di, fv, tv) => { s2[di] = tv - (fv + 2); };
const snd = () => {
  P(0x89, 0x44, 0x24, 0x0C);
  P(0xC7, 0x44, 0x24, 0x10, 0x01, 0x00, 0x00, 0x00);
  P(0x89, 0x44, 0x24, 0x14);
  P(0xB9, 0x18, 0x03, 0x00, 0x00);
  P(0x8D, 0x54, 0x24, 0x10);
  callR2(SENDMSG);
};
P(0x60); P(0x83, 0xEC, 0x18);                // pushad; sub 0x18
P(0x8B, 0x54, 0x24, 0x18);                   // edx=POINT* (pushad EBX)
P(0x8D, 0x0C, 0x24);                         // ecx=&pAcc
callR2(AOP);
P(0x8B, 0x04, 0x24);                         // eax=pAcc
P(0x85, 0xC0);
const jzN = s2.length; P(0x74, 0x00);
P(0xB8, 0x01, 0x00, 0x00, 0x00);             // eax=1
snd();
const jmpR = s2.length; P(0xEB, 0x00);
const nAt = s2.length;
fixDisp(jzN + 1, newVa + jzN, newVa + nAt);
P(0x31, 0xC0);                               // eax=0
snd();
const rAt = s2.length;
fixDisp(jmpR + 1, newVa + jmpR, newVa + rAt);
// role: ecx=this=pAcc; eax=vtable
P(0x8B, 0x0C, 0x24);                         // ecx=pAcc
P(0x85, 0xC9);
const jzS = s2.length; P(0x74, 0x00);        // jz CHECK
P(0x8B, 0x01);                               // eax=vtable
P(0x6A, 0x00); P(0x6A, 0x00); P(0x6A, 0x00); P(0x6A, 0x00); // varChild (esp=E-0x48)
P(0x8D, 0x54, 0x24, 0x18);                   // &role: esp=E-0x48 -> [esp+0x18]=E-0x30? role slot [esp+4]=E-0x34 -> need E-0x34 = [esp+0x14]... E-0x48+0x14=E-0x34 ✓
P(0x8D, 0x54, 0x24, 0x14);                   // &role = E-0x34
P(0x52);
P(0xFF, 0x50, 0x34);                         // call [eax+0x34] get_accRole
P(0x83, 0xC4, 0x14);                         // esp=E-0x38
P(0x8B, 0x44, 0x24, 0x04);                   // eax=role
snd();                                       // send 792(role)
// CHECK: eax=role (or 0 on null path)
const cAt = s2.length;
fixDisp(jzS + 1, newVa + jzS, newVa + cAt);
// Release pAcc if non-null
P(0x8B, 0x0C, 0x24);                         // ecx=pAcc
P(0x85, 0xC9);
const jzRel = s2.length; P(0x74, 0x00);
P(0x8B, 0x11);
P(0x51);
P(0xFF, 0x52, 0x08);                         // Release
P(0x83, 0xC4, 0x04);
const nRel = s2.length;
fixDisp(jzRel + 1, newVa + jzRel, newVa + nRel);
P(0x3D, 0x25, 0x00, 0x00, 0x00);
const je1 = s2.length; P(0x74, 0x00);
P(0x3D, 0x29, 0x00, 0x00, 0x00);
const je2 = s2.length; P(0x74, 0x00);
// FAIL
P(0xC7, 0x44, 0x24, 0x34, 0x00, 0x00, 0x00, 0x00);
const jmpD = s2.length; P(0xEB, 0x00);
// PASS
const pAt = s2.length;
fixDisp(je1 + 1, newVa + je1, newVa + pAt);
fixDisp(je2 + 1, newVa + je2, newVa + pAt);
P(0xC7, 0x44, 0x24, 0x34, 0x01, 0x00, 0x00, 0x00);
// DONE
const dAt = s2.length;
fixDisp(jmpD + 1, newVa + jmpD, newVa + dAt);
P(0x83, 0xC4, 0x18);
P(0x61);
P(0x5F); P(0x5E); P(0x5D); P(0x5B);
P(0x83, 0xC4, 0x20);
P(0xC3);
for (let i = 0; i < s2.length; i++) out[newRaw + i] = s2[i];
console.log('stub (' + s2.length + 'B) at 0x' + newVa.toString(16));

fs.writeFileSync(FILE, out);
console.log('v17f patch OK ->', FILE);
console.log('hash:', crypto.createHash('sha256').update(out).digest('hex'));
