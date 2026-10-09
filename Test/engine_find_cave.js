// engine_find_cave.js - find usable code caves (runs of 0xCC / 0x00 padding)
// inside .text and report free space in .data's zero-filled tail, for the
// zone-mask patch (v19). Addresses are printed as RVAs relative to 0x400000
// (the engine's preferred base) so the code stays ASLR-agnostic.
//
// Usage: node Test/engine_find_cave.js [minBytes]
'use strict';
const fs = require('fs');
const path = require('path');
const MIN = parseInt(process.argv[2] || '64', 10);
const exe = path.join(process.env.LOCALAPPDATA, 'AutoControl', 'AutoCtrl_2025.4.22.0.exe.orig-pristine');
const buf = fs.readFileSync(exe);

const peOff = buf.readUInt32LE(0x3C);
const nSec = buf.readUInt16LE(peOff + 6);
const optSize = buf.readUInt16LE(peOff + 20);
const imgBase = buf.readUInt32LE(peOff + 28);
const secOff = peOff + 24 + optSize;
const secs = [];
for (let i = 0; i < nSec; i++) {
  const o = secOff + i * 40;
  secs.push({
    name: buf.toString('ascii', o, o + 8).replace(/\0+$/, ''),
    va: imgBase + buf.readUInt32LE(o + 12),
    vsize: buf.readUInt32LE(o + 8),
    rsize: buf.readUInt32LE(o + 16),
    roff: buf.readUInt32LE(o + 20),
    chars: buf.readUInt32LE(o + 36)
  });
}
const text = secs.find(s => s.name === '.text');
const data = secs.find(s => s.name === '.data');
console.log(`imageBase=0x${imgBase.toString(16)}  .text mapped 0x${text.va.toString(16)}..0x${(text.va + text.rsize).toString(16)}`);
console.log(`.data   mapped 0x${data.va.toString(16)}..0x${(data.va + data.rsize).toString(16)}  virtual end 0x${(data.va + data.vsize).toString(16)} (RW, zero-filled tail)`);
console.log(`.data zero tail available: ${data.vsize - data.rsize} bytes`);

// ---- runs of 0xCC (int3 alignment padding) in .text ----
const runs = [];
let start = -1;
for (let i = text.roff; i < text.roff + text.rsize; i++) {
  if (buf[i] === 0xCC) { if (start < 0) start = i; }
  else {
    if (start >= 0 && i - start >= MIN) runs.push([start, i]);
    start = -1;
  }
}
if (start >= 0) runs.push([start, text.roff + text.rsize]);
console.log(`\n0xCC runs >= ${MIN} bytes in .text: ${runs.length}`);
for (const [s, e] of runs.slice(0, 25)) {
  const va = text.va + (s - text.roff);
  const pageEnd = Math.floor((va + 0x1000) / 0x1000) * 0x1000;
  const usable = Math.min(e - s, Math.max(0, pageEnd - va));   // don't cross a page end
  console.log(`  RVA 0x${va.toString(16)} (off 0x${s.toString(16)}) len=${e - s} usable-in-page=${usable} align16=${va % 16 === 0}`);
}

// ---- also: runs of 0x00 in .text (may be real data, check carefully) ----
const zruns = [];
start = -1;
for (let i = text.roff; i < text.roff + text.rsize; i++) {
  if (buf[i] === 0x00) { if (start < 0) start = i; }
  else {
    if (start >= 0 && i - start >= 200) zruns.push([start, i]);
    start = -1;
  }
}
console.log(`\n0x00 runs >= 200 bytes in .text: ${zruns.length}`);
for (const [s, e] of zruns.slice(0, 10)) console.log(`  RVA 0x${(text.va + (s - text.roff)).toString(16)} len=${e - s}`);
