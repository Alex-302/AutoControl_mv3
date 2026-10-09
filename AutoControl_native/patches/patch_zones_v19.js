// patch_zones_v19.js - engine patch that makes the mouseOver precond CONSULT
// A ZONE TABLE instead of always matching (fixes "wheel triggers swallow the
// wheel everywhere / pages stop scrolling", TODO §2f(e)).
//
// Background
// ----------
// The engine's region match decides BOTH "does the trigger fire" AND "is the
// input consumed". v18 forced "match" for every region below 60, so any wheel
// trigger with a mouse-over condition ate the wheel everywhere - the page
// could no longer be scrolled (user report 2026-09-12; MV2 semantics: over a
// non-matching zone the wheel passed through).
//
// Fix: the region check now reads a TABLE in the engine's memory that the
// zone helper (ac_zone_helper.exe) keeps up to date:
//     table[region] != 0  -> the trigger matches
//     table[region] == 0  -> it does not match (input passes through)
// Regions >= 40 (the AutoControl MENU items) keep the engine's own logic
// (the helper cannot see the native menu).
//
// Layout (ASLR-safe: every jump is relative, the absolute table/flag
// addresses are written by the helper at runtime)
// -----------------------------------------------------------------------
//   entry FUN_004156f0 (VA 0x4156F0, 5 bytes)   -> E9 rel32   (jmp cave)
//   cave  VA 0x47F7A3 (zero padding at the end of .text, 93 bytes, the last
//         page of the section is mapped and executable; v18 used 21 of them)
//
//   The cave is pre-filled with a HELPER-ABSENT fallback (= v18 semantics,
//   always match, NO memory reads, so it can never fault). When the helper
//   runs it overwrites bytes 0x00..0x1A with the table version, which takes
//   the alive flag into account:
//
//     00: 83 FA 28            cmp  edx, 28h        ; region id (see FUN prologue)
//     03: 73 17               jae  ORIG            ; >= 40 -> engine's own logic
//     05: 80 3D AAAA AAAA 00  cmp  byte [ALIVE], 0 ; helper running?
//     0C: 74 08               je   NOTALIVE
//     0E: 8B 04 95 TTTT TTTT  mov  eax, [edx*4+TAB] ; table[region] -> 0/1
//     15: C3                  ret                  ; eax = match
//     16: B8 01 00 00 00      NOTALIVE: mov eax, 1  ; helper absent -> v18
//     1B: C3                  ret
//     1C: 83 EC 20 53 55      ORIG: original first 5 bytes of the function
//     21: E9 rel32            jmp  0x4156F5
//
// The caller cleans the stack arg it pushed (`add esp,4` right after the
// call), so a plain `ret` is correct for the early-return paths.
//
// Usage: node AutoControl_native/patches/patch_zones_v19.js [out.exe] [in.exe] [v16]
//        out.exe  defaults to %TEMP%\ac_native_re\AutoCtrl_2025.4.22.0.exe
//        in.exe   defaults to ../original/AutoCtrl_2025.4.22.0.exe (the
//                 pristine engine kept next to this script)
//        v16      optional flag ANYWHERE in the arguments (see below - NOT
//                 part of the current build)
// Examples:
//   node patch_zones_v19.js D:\out.exe                    # current build
//   node patch_zones_v19.js D:\out.exe D:\other-src.exe   # explicit input
//   node patch_zones_v19.js D:\out.exe v16                # legacy variant
'use strict';
const fs = require('fs');
const path = require('path');

// Arguments: `v16` is a FLAG (it may sit in any position); everything else is
// positional - [0] = output, [1] = input. Parsing them together so that
// `patch.js out.exe v16` cannot be mistaken for "input file v16".
const ARGS = process.argv.slice(2);
const WITH_V16 = ARGS.includes('v16');
const POSITIONAL = ARGS.filter(a => a !== 'v16');

// Input: the PRISTINE engine. By default the copy that ships in this repo
// (AutoControl_native/original/), so the patch works out of a clean checkout.
// Fallback: the deployed pristine backup (%LOCALAPPDATA%\AutoControl\), which
// is where the bit-for-bit build recipe used to read from.
function resolveSource() {
  if (POSITIONAL[1]) return POSITIONAL[1];
  const repo = path.join(__dirname, '..', 'original', 'AutoCtrl_2025.4.22.0.exe');
  if (fs.existsSync(repo)) return repo;
  const deployed = path.join(process.env.LOCALAPPDATA, 'AutoControl', 'AutoCtrl_2025.4.22.0.exe.orig-pristine');
  if (fs.existsSync(deployed)) return deployed;
  console.error('PRISTINE ENGINE NOT FOUND');
  console.error('  looked for: ' + repo);
  console.error('             ' + deployed);
  console.error('  pass it explicitly: node patch_zones_v19.js <out.exe> <pristine.exe>');
  process.exit(1);
}

const SRC = resolveSource();
const OUT = POSITIONAL[0] || path.join(process.env.TEMP, 'ac_native_re', 'AutoCtrl_2025.4.22.0.exe');

// ---- addresses (VA) -------------------------------------------------------
const ENTRY = 0x4156F0;          // FUN_004156f0 entry (region matcher)
const RESUME = ENTRY + 5;        // where the original body continues
const CAVE = 0x47F7A3;           // zero padding in .text (start of the 93 free bytes)
const FILE_DELTA = 0x400C00;     // .text: VA 0x401000 == file offset 0x400
const va2off = (va) => va - FILE_DELTA;
const rel32 = (from, to) => (to - (from + 5)) >>> 0;

const buf = fs.readFileSync(SRC);

// ---- sanity: the source must be the PRISTINE engine ----------------------
// (bit-for-bit reproducibility depends on it: the same pristine file + the
//  same script always produce the same output, see Docs/BUILD-NATIVE.md)
const PRISTINE_SRC = 'AutoCtrl_2025.4.22.0.exe.orig-pristine';
const PRISTINE_SHA256 = '8AE9A669086BEA5C4344007AC4CA9797E5814285E03B6B04E5F8336329CB7E09';
{
  const sha = require('crypto').createHash('sha256').update(buf).digest('hex').toUpperCase();
  if (buf.length !== 695296 || sha !== PRISTINE_SHA256) {
    console.error('SOURCE IS NOT THE PRISTINE ENGINE');
    console.error('  file   : ' + SRC);
    console.error('  size   : ' + buf.length + ' (expected 695296)');
    console.error('  sha256 : ' + sha);
    console.error('  expected: ' + PRISTINE_SHA256 + '  (' + PRISTINE_SRC + ')');
  console.error('Restore the pristine copy (AutoControl_native\\original\\AutoCtrl_2025.4.22.0.exe)' +
      ' or the .orig-pristine backup before patching.');
    process.exit(1);
  }
}

// ---- sanity: the pristine bytes we are going to patch ---------------------
const origEntry = buf.slice(va2off(ENTRY), va2off(ENTRY) + 5);
if (!origEntry.equals(Buffer.from([0x83, 0xEC, 0x20, 0x53, 0x55]))) {
  console.error('ENTRY bytes differ: ' + origEntry.toString('hex') + ' (expected 83ec205355)');
  process.exit(1);
}
const caveArea = buf.slice(va2off(CAVE), va2off(CAVE) + 93);
if (caveArea.some(b => b !== 0)) {
  console.error('cave area is not zero padding - wrong build?');
  process.exit(1);
}

// ---- v16 patches (zone 12 = always true) ---------------------------------
// NOTE (2026-09-12, later): these are now OPTIONAL and OFF by default.
// Measured: with them applied the engine CONSUMED the wheel everywhere even
// when the v19 table said "no match" (the native zone-12 check is used for the
// block/consume decision too, not only for the match) - i.e. they re-created
// the "cannot scroll pages" symptom. The table alone makes zone 12 work, so
// build with `node AutoControl_native/patches/patch_zones_v19.js` (no v16) unless there is a reason.
const V16 = [
  { va: 0x415781, from: '0f8469030000', to: '909090909090' },
  { va: 0x4155AC, from: '837e2c257508', to: 'b00190909090' }
];
if (WITH_V16) for (const p of V16) {
  const off = va2off(p.va);
  const cur = buf.slice(off, off + p.from.length / 2).toString('hex');
  if (cur !== p.from) { console.error(`v16 patch site 0x${p.va.toString(16)}: got ${cur}, expected ${p.from}`); process.exit(1); }
  Buffer.from(p.to, 'hex').copy(buf, off);
}

// ---- the cave -------------------------------------------------------------
const caveOff = va2off(CAVE);
const ORIG_BLOCK = 0x1C;                        // offset of the original 5 bytes
const caveLen = ORIG_BLOCK + 5 + 5;             // + jmp rel32 = 0x26 = 38

// ORIG block + jump back (identical in BOTH variants - the helper only
// overwrites bytes 0x00..0x1A)
const origBytes = Buffer.from([0x83, 0xEC, 0x20, 0x53, 0x55]);
const jmpBackOff = CAVE + ORIG_BLOCK + 5;
const jmpBack = Buffer.concat([
  Buffer.from([0xE9]),
  (() => { const b = Buffer.alloc(4); b.writeUInt32LE(rel32(jmpBackOff, RESUME), 0); return b; })()
]);

// variant A (pre-filled in the file): helper absent -> always match (v18)
const variantA = Buffer.alloc(ORIG_BLOCK);
{
  const b = variantA;
  b[0] = 0x83; b[1] = 0xFA; b[2] = 0x28;                 // cmp edx, 28h
  b[3] = 0x73; b[4] = ORIG_BLOCK - 0x05;                 // jae ORIG
  b[5] = 0xB8; b[6] = 1; b[7] = 0; b[8] = 0; b[9] = 0;   // mov eax, 1
  b[10] = 0xC3;                                          // ret
  for (let i = 11; i < ORIG_BLOCK; i++) b[i] = 0x90;     // nop padding
}
const caveBytes = Buffer.concat([variantA, origBytes, jmpBack]);
if (caveBytes.length !== caveLen) { console.error('cave size mismatch'); process.exit(1); }
caveBytes.copy(buf, caveOff);

// ---- the entry jump -------------------------------------------------------
{
  const e = Buffer.alloc(5);
  e[0] = 0xE9;
  e.writeUInt32LE(rel32(ENTRY, CAVE), 1);
  e.copy(buf, va2off(ENTRY));
}

fs.mkdirSync(path.dirname(OUT), { recursive: true });
fs.writeFileSync(OUT, buf);

// ---- report ---------------------------------------------------------------
const crypto = require('crypto');
const sha = crypto.createHash('sha256').update(buf).digest('hex').toUpperCase();
console.log('built  : ' + OUT);
console.log('size   : ' + buf.length);
console.log('sha256 : ' + sha);
console.log('entry  : ' + buf.slice(va2off(ENTRY), va2off(ENTRY) + 5).toString('hex') + '  (jmp cave 0x' + CAVE.toString(16) + ')');
console.log('cave   : ' + buf.slice(caveOff, caveOff + caveLen).toString('hex'));
console.log('');
console.log('CAVE_RVA      = 0x' + (CAVE - 0x400000).toString(16));
console.log('ORIG_BLOCK    = 0x' + ORIG_BLOCK.toString(16) + ' (helper writes bytes 0x00..0x1b)');
console.log('table version (written by the helper at runtime):');
console.log('  83 FA 28 73 17 80 3D <alive+4> 00 74 08 8B 04 95 <tab+4> C3 B8 01 00 00 00 C3');
console.log('  (alive = 4-byte flag address, tab = table address - both absolute,');
console.log('   computed by the helper from the live module base)');
