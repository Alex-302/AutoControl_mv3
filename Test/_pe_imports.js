// Quick PE import-table dump (no deps).
// Usage: node _pe_imports.js <file.exe> [filter]
'use strict';
const fs = require('fs');
const file = process.argv[2];
const filter = process.argv[3] ? new RegExp(process.argv[3], 'i') : null;
const buf = fs.readFileSync(file);

const u16 = (o) => buf.readUInt16LE(o);
const u32 = (o) => buf.readUInt32LE(o);
const cstr = (o) => { let e = o; while (e < buf.length && buf[e]) e++; return buf.toString('latin1', o, e); };

if (buf.readUInt16LE(0) !== 0x5A4D) { console.log('not a PE'); process.exit(1); }
const peOff = u32(0x3C);
const optMagic = u16(peOff + 24);
const is64 = optMagic === 0x20b;
const numSec = u16(peOff + 6);
const optSize = u16(peOff + 20);
const ddOff = peOff + 24 + (is64 ? 112 : 96); // data directories (import = 1)
const impRva = u32(ddOff + 8), impSize = u32(ddOff + 12);
const thunkSize = is64 ? 8 : 4;

// section headers
const secOff = peOff + 24 + optSize;
const secs = [];
for (let i = 0; i < numSec; i++) {
  const o = secOff + i * 40;
  secs.push({ name: cstr(o).replace(/\0/g, ''), va: u32(o + 12), vsize: u32(o + 8), raw: u32(o + 20), rsize: u32(o + 16) });
}
const rva2off = (rva) => {
  for (const s of secs) if (rva >= s.va && rva < s.va + Math.max(s.vsize, s.rsize)) return s.raw + (rva - s.va);
  return -1;
};

console.log('== imports of', file, '==');
let off = rva2off(impRva);
if (off < 0) { console.log('no import dir'); process.exit(0); }
const dlls = [];
for (;;) {
  const orig = u32(off);
  const nameRva = u32(off + 12);
  if (!nameRva) break;
  const noff = rva2off(nameRva);
  const dll = noff >= 0 ? cstr(noff) : '?';
  // walk thunks
  const thunkRva = orig || u32(off + 16);
  let toff = rva2off(thunkRva);
  const funcs = [];
  while (toff >= 0) {
    const t = is64 ? buf.readBigUInt64LE(toff) : u32(toff);
    if (t === 0n || t === 0) break;
    const tNum = Number(t);
    if (tNum & 0x80000000) { funcs.push('ord_' + (tNum & 0xFFFF)); }
    else { const fn = rva2off(tNum & 0x7FFFFFFF); funcs.push(fn >= 0 ? cstr(fn + 2) : '?'); }
    toff += thunkSize;
  }
  if (!filter || filter.test(dll)) {
    console.log('--- ' + dll + ' (' + funcs.length + ')');
    if (filter) console.log('   ' + funcs.join('\n   '));
  }
  off += 20;
}
if (!filter) console.log('(dlls: ' + dlls.length + ')');
