// patch_zones_v19diag.js - DIAGNOSTIC variant of the v19 patch.
//
// Purpose: the v19 zone table is indexed by the region id the ENGINE passes to
// its mouseOver matcher (FUN_004156f0). The extension's config stores its own
// region numbers ("Browser tab" = 12, "Tab's close button" = 15, ...), but the
// engine may translate them internally (the RE session found `FUN_00414760(...,
// 10)` for the tab strip, which suggests a different internal numbering).
//
// This build records every asked-for id instead of deciding anything:
//   * the matcher writes `seen[edx] = edx` (a 64-dword table the helper/
//     engine_zone_write.ps1 allocates inside the engine) and then returns 1
//     ("match", the v18 behaviour) so normal operation is not disturbed;
//   * after one wheel event with a single zone-gated trigger enabled, dump the
//     seen table: the recorded id is the engine's number for that zone.
//
// Cave layout (27 bytes, same base address as the final v19 cave):
//   00: 83 FA 3F              cmp edx, 3Fh
//   03: 77 0C                 ja  ORIG
//   05: 89 14 95 <SEEN+4>     mov [edx*4 + SEEN], edx
//   0B: B8 01 00 00 00        mov eax, 1
//   10: C3                    ret
//   11: 83 EC 20 53 55        ORIG: original first 5 bytes
//   16: E9 <rel32>            jmp 0x4156F5
//
// Usage: node Test/patch_zones_v19diag.js [out.exe]
'use strict';
const fs = require('fs');
const path = require('path');

const SRC = path.join(process.env.LOCALAPPDATA, 'AutoControl', 'AutoCtrl_2025.4.22.0.exe.orig-pristine');
const OUT = process.argv[2] || path.join(process.env.TEMP, 'ac_native_re', 'AutoCtrl_v19diag.exe');

const ENTRY = 0x4156F0;
const RESUME = ENTRY + 5;
const CAVE = 0x47F7A3;
const FILE_DELTA = 0x400C00;
const va2off = (va) => va - FILE_DELTA;
const rel32 = (from, to) => (to - (from + 5)) >>> 0;
const ORIG_BLOCK = 0x11;

const buf = fs.readFileSync(SRC);
const origEntry = buf.slice(va2off(ENTRY), va2off(ENTRY) + 5);
if (!origEntry.equals(Buffer.from([0x83, 0xEC, 0x20, 0x53, 0x55]))) {
  console.error('ENTRY bytes differ: ' + origEntry.toString('hex'));
  process.exit(1);
}
const caveArea = buf.slice(va2off(CAVE), va2off(CAVE) + 93);
if (caveArea.some(b => b !== 0)) { console.error('cave area not zero'); process.exit(1); }

const caveOff = va2off(CAVE);
// prefix (written now with a placeholder SEEN address; the tool/helper patches
// the absolute address at runtime - the file value is a harmless default that
// the engine only uses if nothing ever initialises it)
const pre = Buffer.alloc(ORIG_BLOCK);
pre[0] = 0x83; pre[1] = 0xFA; pre[2] = 0x3F;              // cmp edx, 3Fh
pre[3] = 0x77; pre[4] = ORIG_BLOCK - 5;                   // ja ORIG (rel8)
pre[5] = 0x89; pre[6] = 0x14; pre[7] = 0x95;              // mov [edx*4+disp32], edx
pre.writeUInt32LE(0x00000000, 8);                          // placeholder address
pre[12] = 0xB8; pre[13] = 1;                               // mov eax, 1
pre[16] = 0xC3;                                            // ret
const jmpBack = Buffer.concat([
  Buffer.from([0xE9]),
  (() => { const b = Buffer.alloc(4); b.writeUInt32LE(rel32(CAVE + ORIG_BLOCK + 5, RESUME), 0); return b; })()
]);
const caveBytes = Buffer.concat([pre, Buffer.from([0x83, 0xEC, 0x20, 0x53, 0x55]), jmpBack]);
caveBytes.copy(buf, caveOff);

const e = Buffer.alloc(5);
e[0] = 0xE9;
e.writeUInt32LE(rel32(ENTRY, CAVE), 1);
e.copy(buf, va2off(ENTRY));

fs.mkdirSync(path.dirname(OUT), { recursive: true });
fs.writeFileSync(OUT, buf);
const crypto = require('crypto');
console.log('built  : ' + OUT);
console.log('sha256 : ' + crypto.createHash('sha256').update(buf).digest('hex').toUpperCase());
console.log('cave   : ' + buf.slice(caveOff, caveOff + caveBytes.length).toString('hex'));
console.log('note   : the SEEN address (offset 8) is filled at runtime by');
console.log('         Test/engine_zone_write.ps1 -Diag');
