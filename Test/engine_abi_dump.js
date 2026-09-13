// engine_abi_dump.js - the ABI facts the v19 trampoline relies on, read out of
// the binary: the matcher's call sites, argument setup, result usage, the cave
// page's mapping/permissions, and whether anything can BYPASS the trampoline.
//
// This is a CHECK, not a printout: it ends with `ABI AUDIT: OK` (exit 0) or
// lists the failures (`ABI AUDIT: FAILED`, exit 1). What it asserts:
//   * the code cave of the patch sits in REAL (raw) data, inside a MAPPED page
//     of an EXECUTABLE section - i.e. the trampoline can actually run;
//   * the region matcher has exactly ONE direct (E8) caller - the call the
//     trampoline intercepts - and no other reference to its address exists,
//     so there is no indirect path around the trampoline.
//
// Usage: node Test/engine_abi_dump.js [path-to-exe]
//        (default: the deployed pristine backup)
'use strict';
const fs = require('fs');
const path = require('path');

const exe = process.argv[2] || path.join(process.env.LOCALAPPDATA, 'AutoControl', 'AutoCtrl_2025.4.22.0.exe.orig-pristine');
const buf = fs.readFileSync(exe);
console.log('file: ' + exe + '  size=' + buf.length);

// every check below records its failures here; the verdict is printed at the end
const failures = [];
const fail = (msg) => { failures.push(msg); };

// --- PE headers ---
const peOff = buf.readUInt32LE(0x3C);
const nSec = buf.readUInt16LE(peOff + 6);
const optSize = buf.readUInt16LE(peOff + 20);
const imgBase = buf.readUInt32LE(peOff + 24 + 28);
const secOff = peOff + 24 + optSize;
console.log('imageBase=0x' + imgBase.toString(16) + ' sections=' + nSec);
const secs = [];
for (let i = 0; i < nSec; i++) {
  const o = secOff + i * 40;
  const name = buf.toString('ascii', o, o + 8).replace(/\0+$/, '');
  const vsize = buf.readUInt32LE(o + 8), va = buf.readUInt32LE(o + 12);
  const rsize = buf.readUInt32LE(o + 16), roff = buf.readUInt32LE(o + 20);
  const chars = buf.readUInt32LE(o + 36);
  secs.push({ name, va: imgBase + va, vsize, roff, rsize, chars });
  console.log(`  ${name.padEnd(8)} va=0x${(imgBase + va).toString(16)} vsize=${vsize} rsize=${rsize} roff=0x${roff.toString(16)} chars=0x${chars.toString(16)}`);
  if (roff + rsize > buf.length) console.log('     WARNING: raw size exceeds file!');
}
const toVa = (off) => { for (const s of secs) if (off >= s.roff && off < s.roff + s.rsize) return s.va + (off - s.roff); return null; };
const toOff = (va) => { for (const s of secs) if (va >= s.va && va < s.va + s.vsize) return s.roff + (va - s.va); return null; };

const text = secs.find(s => s.name === '.text');
const padBytes = text.rsize - ((() => { // find the last non-zero byte in .text
  let i = text.roff + text.rsize - 1;
  while (i > text.roff && buf[i] === 0) i--;
  return i - text.roff + 1;
})());
console.log(`.text: raw size ${text.rsize}, last non-zero byte at +${text.rsize - padBytes} => zero padding available: ${padBytes} bytes (VA 0x${(text.va + text.rsize - padBytes).toString(16)})`);
// The code cave of patch_zones_v19.js lives at image RVA 0x7F7A3 = .text
// +0x7E7A3 - exactly at the END of the section's VIRTUAL size, but still inside
// its RAW data (rsize is the larger of the two here). So those bytes are real
// file content (not the zero fill), and they are mapped because the loader maps
// whole pages; the section is executable, so the page inherits r-x. CHECKED
// below - "the trampoline is executable" is the assumption the whole patch
// rests on.
{
  const caveRva = 0x7F7A3;                            // image RVA (helper's CAVE_RVA)
  const caveInSec = caveRva - (text.va - imgBase);    // offset INSIDE .text
  const mapped = caveInSec < Math.ceil(text.rsize / 0x1000) * 0x1000;
  const raw = caveInSec < text.rsize;
  const exec = !!(text.chars & 0x20000000) && mapped;
  console.log(`cave (image RVA 0x${caveRva.toString(16)} = .text +0x${caveInSec.toString(16)}): ` +
    `inside the section's raw data=${raw}, inside the last MAPPED page=${mapped}, ` +
    `executable=${exec}  (section chars=0x${text.chars.toString(16)})`);
  if (!raw) fail(`cave 0x${caveRva.toString(16)} is not inside .text raw data (rsize=${text.rsize})`);
  if (!mapped) fail('the cave is not inside a mapped page - the trampoline would fault');
  if (!exec) fail('the cave page is NOT executable (section chars=0x' + text.chars.toString(16) + ')');
}

// --- call sites of FUN_004156f0 ---
const target = 0x4156f0;
console.log('\ncall sites (E8 rel32 -> 0x' + target.toString(16) + '):');
let found = 0;
for (let off = text.roff; off < text.roff + text.rsize - 5; off++) {
  if (buf[off] !== 0xE8) continue;
  const rel = buf.readInt32LE(off + 1);
  const dst = toVa(off) + 5 + rel;
  if (dst !== target) continue;
  found++;
  const va = toVa(off);
  const from = Math.max(text.roff, off - 48), to = Math.min(text.roff + text.rsize, off + 40);
  const hex = [];
  for (let i = from; i < to; i++) hex.push((i === off ? '>>' : '') + buf[i].toString(16).padStart(2, '0') + (i === off + 4 ? '' : ''));
  console.log(`\n  call at VA 0x${va.toString(16)} (file 0x${off.toString(16)})`);
  console.log('    ' + hex.join(' '));
}
console.log('  total: ' + found);
if (found !== 1) {
  fail('the matcher has ' + found + ' direct (E8) call sites; the patch assumes exactly ONE ' +
    '(the trampoline intercepts only the direct call)');
}

// --- absolute references (indirect calls / vtables) ---
// The trampoline only catches the DIRECT call. A pointer stored in .data/.rdata
// would bypass it (and would only survive ASLR if the loader fixes it up), so
// both halves matter: is the absolute address present at all, and is it
// relocated? "No relocated occurrence" = the single call above is the ONLY way
// in.
console.log('\nabsolute references to 0x' + target.toString(16) + ':');
const pat = Buffer.alloc(4); pat.writeUInt32LE(target, 0);
const hits = [];
for (let i = 0; i + 4 <= buf.length; i++) if (buf.compare(pat, 0, 4, i, i + 4) === 0) hits.push(i);
const rel = secs.find(s => s.name === '.reloc');
const relocs = new Set();
if (rel) {
  let p = rel.roff;
  const end = rel.roff + rel.rsize;
  while (p < end) {
    const page = buf.readUInt32LE(p), size = buf.readUInt32LE(p + 4);
    if (size < 8) break;
    for (let q = p + 8; q < p + size; q += 2) {
      const ent = buf.readUInt16LE(q);
      if ((ent >> 12) !== 0) relocs.add(page + (ent & 0xFFF));   // type 0 = padding
    }
    p += size;
  }
}
console.log('  raw dword occurrences: ' + hits.length + '   relocation entries in the file: ' + relocs.size);
let relHits = 0;
for (const off of hits) {
  const va = toVa(off);
  const isRel = !!va && relocs.has(va - imgBase);
  if (isRel) relHits++;
  console.log('    file 0x' + off.toString(16) + '  relocated=' + isRel);
}
console.log('  => ' + (relHits === 0
  ? 'no relocated pointer: the function is reachable ONLY through the direct call(s) listed above'
  : 'WARNING: ' + relHits + ' relocated pointer(s) - an indirect call would BYPASS the trampoline'));
// any occurrence of the absolute address is worth failing on: the patch relies
// on the direct call being the ONLY way in (a relocated pointer would be a
// bypass; a non-relocated one would not survive ASLR but is equally suspicious)
if (hits.length > 0) {
  fail(hits.length + ' raw dword occurrence(s) of 0x' + target.toString(16) +
    ' in the file (' + relHits + ' relocated) - an indirect reference could bypass the trampoline');
}

// --- function prologue ---
const foff = toOff(target);
console.log('\nFUN_004156f0 prologue (file 0x' + foff.toString(16) + '):');
console.log('  ' + Array.from(buf.slice(foff, foff + 48)).map(b => b.toString(16).padStart(2, '0')).join(' '));

// --- xrefs to the region value: search for "cmp edx, 3c" / "cmp edx,3Ch" style ---
console.log('\n83 fa 3c (cmp edx,0x3C) occurrences in .text:');
let c = 0;
for (let off = text.roff; off < text.roff + text.rsize - 3; off++) {
  if (buf[off] === 0x83 && buf[off + 1] === 0xFA && buf[off + 2] === 0x3C) { c++; if (c < 10) console.log('  VA 0x' + toVa(off).toString(16)); }
}
console.log('  total: ' + c);

// --- verdict ---
console.log('');
if (failures.length === 0) {
  console.log('ABI AUDIT: OK - the matcher has exactly one direct caller and no other reference to it, ' +
    'and the code cave sits in real data inside a mapped, executable page.');
  process.exit(0);
} else {
  console.log('ABI AUDIT: FAILED (' + failures.length + ')');
  failures.forEach((f) => console.log('  * ' + f));
  process.exit(1);
}
