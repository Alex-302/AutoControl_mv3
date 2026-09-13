// Patch AutoCtrl_2025.4.22.0.exe v17g — AOP + 792(flag) + always-1.
// v17f sent 792 only AFTER get_accRole — nothing arrived; engine alive.
// v17g isolates: AOP -> send 792(pAcc!=null?1:0) -> ALWAYS return 1.
//   - 750 everywhere AND 792 arrives  -> AOP + channel OK; the problem
//     is get_accRole/Release/classification.
//   - 750 everywhere, no 792           -> FUN_00408600 doesn't work from
//     this context (792 diagnostics impossible; try classification w/o 792).
//   - no 750                           -> the AOP call itself breaks the
//     engine (SEH swallows it) — role-based patching is impossible.
//
// Changes:
//   1) 0x415781: jz fail -> 6x NOP
//   2) 0x4157d3: tail call -> jmp into .acp stub
//   3) stub: pushad; sub esp,0x18; AOP via FUN_0040b610(ecx=&pAcc,
//      edx=pushad-EBX=POINT*); send 792(pAcc?1:0); stash 1 into the
//      pushad EAX slot; teardown.
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
const patchDisp = (di, fv, tv) => { stub[di] = tv - (fv + 2); };

w8(0x60); w8(0x83, 0xEC, 0x18);              // pushad; sub 0x18 (esp=E-0x38)
w8(0x8B, 0x54, 0x24, 0x18);                 // edx=POINT* (pushad EBX @ E-0x10)
w8(0x8D, 0x0C, 0x24);                       // ecx=&pAcc
callRel(AOP);                               // call FUN_0040b610
w8(0x8B, 0x04, 0x24);                       // eax=pAcc
w8(0x85, 0xC0);
const jzN = stub.length; w8(0x74, 0x00);
w8(0xB8, 0x01, 0x00, 0x00, 0x00);           // eax=1
const ebPos = stub.length; w8(0xEB, 0x00);  // jmp SEND (disp fixed below)
const nAt = stub.length;
patchDisp(jzN + 1, newVa + jzN, newVa + nAt);
w8(0x31, 0xC0);                             // eax=0
const sAt = stub.length;                    // SEND
stub[ebPos + 1] = sAt - (ebPos + 2);        // fix jmp SEND disp
// emit send (value in eax, variant at [esp+0x10..])
w8(0x89, 0x44, 0x24, 0x0C);
w8(0xC7, 0x44, 0x24, 0x10, 0x01, 0x00, 0x00, 0x00);
w8(0x89, 0x44, 0x24, 0x14);
w8(0xB9, 0x18, 0x03, 0x00, 0x00);
w8(0x8D, 0x54, 0x24, 0x10);
callRel(SENDMSG);
// always-1: stash 1 into pushad EAX slot [esp+0x34]
w8(0xC7, 0x44, 0x24, 0x34, 0x01, 0x00, 0x00, 0x00);
// teardown
w8(0x83, 0xC4, 0x18);
w8(0x61);
w8(0x5F); w8(0x5E); w8(0x5D); w8(0x5B);
w8(0x83, 0xC4, 0x20);
w8(0xC3);
for (let i = 0; i < stub.length; i++) out[newRaw + i] = stub[i];
console.log('stub (' + stub.length + 'B) at 0x' + newVa.toString(16));

fs.writeFileSync(FILE, out);
console.log('v17g patch OK ->', FILE);
console.log('hash:', crypto.createHash('sha256').update(out).digest('hex'));
