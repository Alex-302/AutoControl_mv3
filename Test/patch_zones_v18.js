// patch_zones_v18.js - engine build v18: let the EXTENSION decide the zone.
//
// WHY (2026-09-12): the engine's own mouseOver classifier cannot judge the
// regions the extension cares about on Chrome 148+ — its hover cache never
// refreshes over the tab strip, so the checks for "tab's close button" (15),
// "new tab button" (16) and "tab's speaker" (17) always fail and the engine
// never emits the 750 for such triggers (the SW gate therefore never sees
// them). Measured live: trigger on region 15/16/17 -> NO 750 at all, while a
// region-12 trigger over the same strip fires fine.
//
// FIX: make the classifier FUNCTION_004156f0 return "match" for every zone
// BELOW 0x3C (60) — the mouse-over selectivity then lives in the extension's
// SW gate (external MSAA helper, sw.js __acDispatchTrigger750), which is the
// architecture this port already uses for zone 12. Zones >= 0x3C are the
// AutoControl MENU-ITEM regions (UI 40-51 are compiled as 60-71 — see the
// engine's own decompiled menu branch) — those keep the engine's native
// classification, because the menu is drawn by the engine and has no MSAA
// signature for the helper.
//
// Implements a 21-byte code cave in the .text section's tail padding:
//   cmp edx, 3Ch        ; zone >= 60 -> menu items: run the ORIGINAL code
//   jb  alwaysMatch
//   <original first 5 bytes: 83 EC 20 53 55>
//   jmp 0x4156f5        ; back into the original function
// alwaysMatch:
//   mov eax, 1
//   ret                 ; caller cleans the stack ("add esp,4" after the call)
//
// Also keeps the v16 baseline changes:
//   1) 0x415781: jz fail (0F 84 69 03 00 00) -> 6x NOP      [zone-12 gate bypass]
//   2) 0x4155ac: cmp [esi+0x2c],0x25; jnz -> mov al,1; NOPs [zone-12 role check]
//
// Source: the pristine .orig in %LOCALAPPDATA%\AutoControl (never patch a
// patched build - always rebuild deterministically from .orig).
//
// Usage: node Test/patch_zones_v18.js [--out <path>]
'use strict';
const fs = require('fs');
const path = require('path');
const crypto = require('crypto');

const DIR = path.join(process.env.LOCALAPPDATA, 'AutoControl');
const SRC = path.join(DIR, 'AutoCtrl_2025.4.22.0.exe.orig');
const OUT = process.argv.includes('--out')
  ? process.argv[process.argv.indexOf('--out') + 1]
  : path.join(DIR, 'AutoCtrl_2025.4.22.0.exe.patched-v18');

const buf = fs.readFileSync(SRC);
const u16 = o => buf.readUInt16LE(o), u32 = o => buf.readUInt32LE(o);
const pe = u32(0x3C);
const nSec = u16(pe + 6), optSize = u16(pe + 20);
const secOff = pe + 24 + optSize;
const secs = [];
for (let i = 0; i < nSec; i++) {
  const o = secOff + i * 40;
  secs.push({
    name: buf.toString('ascii', o, o + 8).replace(/\0+$/, ''),
    va: u32(o + 12), vs: u32(o + 8), raw: u32(o + 20), rs: u32(o + 16)
  });
}
const text = secs.find(s => s.name === '.text');
const toOff = va => text.raw + (va - 0x400000 - text.va);

const show = va => [...buf.subarray(toOff(va), toOff(va) + 6)].map(b => b.toString(16).padStart(2, '0')).join(' ');
const expect = (va, bytes, what) => {
  const cur = [...buf.subarray(toOff(va), toOff(va) + bytes.length)];
  if (JSON.stringify(cur) !== JSON.stringify(bytes)) {
    console.error(`SIG MISMATCH ${what} @0x${va.toString(16)}: got ${cur.map(b => b.toString(16)).join(' ')}`);
    process.exit(1);
  }
};

// ---- verify the pristine build ----
expect(0x415781, [0x0f, 0x84, 0x69, 0x03, 0x00, 0x00], 'zone-12 gate jz');
expect(0x4155ac, [0x83, 0x7e, 0x2c, 0x25, 0x75, 0x08], 'zone-12 role check');
expect(0x4156f0, [0x83, 0xec, 0x20, 0x53, 0x55, 0x56], 'FUN_004156f0 entry');
console.log('source:', SRC);
console.log('pristine signatures OK');

// ---- 1/2: v16 baseline ----
Buffer.from([0x90,0x90,0x90,0x90,0x90,0x90]).copy(buf, toOff(0x415781));           // jz -> NOPs
Buffer.from([0xb0,0x01,0x90,0x90,0x90,0x90]).copy(buf, toOff(0x4155ac));           // mov al,1; nops
console.log('applied: zone-12 gate NOP + always-1 role check (v16 baseline)');

// ---- 3: code cave in the .text tail padding ----
const CAVE_LEN = 21;
let caveRaw = -1;
for (let i = text.rs - CAVE_LEN - 1; i > text.rs - 4096; i--) {
  let ok = true;
  for (let k = 0; k < CAVE_LEN + 8; k++) if (buf[text.raw + i + k] !== 0) { ok = false; break; }
  if (ok) { caveRaw = text.raw + i; break; }
}
if (caveRaw < 0) { console.error('no zero padding found at the end of .text for the cave'); process.exit(1); }
const caveVa = 0x400000 + text.va + (caveRaw - text.raw);
console.log(`code cave at VA 0x${caveVa.toString(16)} (file offset 0x${caveRaw.toString(16)})`);

const ENTRY = 0x4156f0;
const cave = [];
// cmp edx, 3Ch                      ; zone >= 60 -> original (menu items)
cave.push(0x83, 0xFA, 0x3C);
// jb +0x0A -> alwaysMatch
cave.push(0x72, 0x0A);
// original first bytes (5): sub esp,20h ; push ebx ; push ebp
cave.push(0x83, 0xEC, 0x20, 0x53, 0x55);
// jmp ENTRY+5 (back into the original body)
const backRel = (ENTRY + 5) - (caveVa + 10 + 5);
cave.push(0xE9, backRel & 0xff, (backRel >> 8) & 0xff, (backRel >> 16) & 0xff, (backRel >> 24) & 0xff);
// alwaysMatch: mov eax,1 ; ret
cave.push(0xB8, 0x01, 0x00, 0x00, 0x00, 0xC3);
if (cave.length !== CAVE_LEN) { console.error('cave length mismatch: ' + cave.length); process.exit(1); }
Buffer.from(cave).copy(buf, caveRaw);

// entry: jmp cave  (5 bytes) - the original first 5 bytes now live in the cave
const jmpRel = caveVa - (ENTRY + 5);
Buffer.from([0xE9, jmpRel & 0xff, (jmpRel >> 8) & 0xff, (jmpRel >> 16) & 0xff, (jmpRel >> 24) & 0xff]).copy(buf, toOff(ENTRY));
console.log('entry @0x4156f0 -> jmp cave (36-byte trampoline with the zone < 60 rule)');

fs.writeFileSync(OUT, buf);
const sha = crypto.createHash('sha256').update(buf).digest('hex').toUpperCase().slice(0, 8);
console.log('');
console.log('written:', OUT);
console.log('sha256(head):', sha, ' size:', buf.length);
console.log('');
console.log('verify:');
console.log('  entry 0x4156f0:', show(0x4156f0), '(expect e9 ..)');
console.log('  cave  @0x' + caveVa.toString(16) + ':', [...buf.subarray(caveRaw, caveRaw + CAVE_LEN)].map(b => b.toString(16).padStart(2, '0')).join(' '));

