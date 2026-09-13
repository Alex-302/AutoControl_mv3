// patch_bytes_verify.js - PROOF that the injected bytes mean what we claim.
//
// The user-facing claim is "the patch adds 5 bytes of jump + a small code cave
// and nothing else", and the code is described in prose as
//
//     cmp edx,28h ; jae ORIG ; cmp byte [ALIVE],0 ; je NOTALIVE ;
//     mov eax,[edx*4+TABLE] ; ret ; NOTALIVE: mov eax,1 ; ret
//
// This script decodes the ACTUAL bytes with a strict mini-decoder (only the
// instruction forms the patch is allowed to contain - anything else is an
// error, never a "close enough") and prints an annotated listing:
//
//     <VA>  <bytes>          <mnemonic>            ; <label / comment>
//
// Two independent checks run on top of the decode:
//   1. every branch target must land EXACTLY on the label it claims
//      (jae -> ORIG at cave+0x1C, je -> NOTALIVE at cave+0x16, jmp back ->
//       ENTRY+5), because a one-byte offset error here is silent at runtime;
//   2. the rest of the file must differ from the original ONLY inside the
//      3 documented byte ranges (the "nothing else changed" half of the proof).
//
// Usage:
//   node Test/patch_bytes_verify.js [engine.exe]        # default: deployed
//   node Test/patch_bytes_verify.js <patched.exe> --orig <original.exe>
//   node Test/patch_bytes_verify.js --no-diff           # skip the byte diff
//
// The "nothing else changed" half needs the PRISTINE engine, so a MISSING
// original is an ERROR (exit 1) unless `--no-diff` says explicitly that the
// weaker, decode-only check is what you want (a silently skipped diff used to
// print a green "PROOF HOLDS" for half a proof). The default original is also
// hash-checked against the pinned pristine build, so a swapped file cannot
// turn the diff half into a no-op.
//
// Exit code 0 = proof holds, 1 = mismatch (details on stdout).
//
// The module also EXPORTS `runtimePrefix()` and the address constants: mh_test
// uses them (B53f/B53g) so the harness verifies the SAME writer and the same
// bytes instead of yet another hand-written copy of the layout.
'use strict';
const fs = require('fs');
const path = require('path');

// ---- addresses (identical to patch_zones_v19.js) --------------------------
const ENTRY = 0x4156F0;              // FUN_004156f0 (region matcher), VA
const RESUME = ENTRY + 5;            // where the original body continues
const CAVE = 0x47F7A3;               // code cave in the .text tail
const ORIG_BLOCK = 0x1C;             // size of the injected prefix
const FILE_DELTA = 0x400C00;         // VA -> file offset (.text)
const va2off = (va) => va - FILE_DELTA;

const CAVE_LEN = ORIG_BLOCK + 5 + 5; // prefix + displaced bytes + jmp back

// documented byte ranges that may differ from the original
const DIFF_RANGES = [
  [0x14AF0, 5, 'entry jump'],
  [0x7EBA3, 7, 'cave 0x00..0x06'],
  [0x7EBD0 - 0x23, 28, 'cave 0x0A..0x25']   // 0x7EBAD
];

// the file variant: always-match fallback, reads no memory (can never fault)
const FILE_PREFIX_HEX = '83fa287317b801000000c3' + '90'.repeat(17);
// the displaced original bytes
const ORIG_BLOCK_HEX = '83ec205355';

// sha256 of the pristine engine the patch is built from (same constant as
// patch_zones_v19.js / build_native.ps1) - the diff half is only meaningful
// against THIS file
const PRISTINE_SHA = '8AE9A669086BEA5C4344007AC4CA9797E5814285E03B6B04E5F8336329CB7E09';

// absolute addresses the zone helper writes at runtime (values observed live;
// any address would decode the same way - they are computed from the module
// base, so ASLR does not matter for the byte pattern)
const RT_ALIVE = 0x005D0000, RT_TABLE = 0x005D0010;

// ---- the instruction forms the patch may contain --------------------------
// buf: whole file, off: file offset of the instruction, va: its virtual address
// (targets MUST be computed in VA space - file offsets differ by 0x400C00)
function decode(buf, off, va) {
  const b = (i) => buf[off + i];
  const u32 = (i) => buf.readUInt32LE(off + i);
  const rel8 = (i) => (b(i) << 24) >> 24;
  const rel32 = (i) => buf.readInt32LE(off + i);

  if (b(0) === 0x83 && b(1) === 0xFA) return { len: 3, mnem: `cmp edx, ${b(2)}`, kind: 'cmpEdx', imm: b(2), note: 'region id (2nd fastcall arg)' };
  if (b(0) === 0x83 && b(1) === 0xEC) return { len: 3, mnem: `sub esp, ${b(2)}`, kind: 'subEsp', note: 'displaced original prologue' };
  if (b(0) === 0x73) return { len: 2, mnem: `jae 0x${(va + 2 + rel8(1)).toString(16)}`, kind: 'jae', target: va + 2 + rel8(1) };
  if (b(0) === 0x74) return { len: 2, mnem: `je  0x${(va + 2 + rel8(1)).toString(16)}`, kind: 'je', target: va + 2 + rel8(1) };
  if (b(0) === 0x80 && b(1) === 0x3D) return { len: 7, mnem: `cmp byte [0x${u32(2).toString(16)}], ${b(6)}`, kind: 'cmpMem', addr: u32(2), imm: b(6) };
  if (b(0) === 0x8B && b(1) === 0x04 && b(2) === 0x95) return { len: 7, mnem: `mov eax, [edx*4 + 0x${u32(3).toString(16)}]`, kind: 'movTable', addr: u32(3) };
  if (b(0) === 0xC3) return { len: 1, mnem: 'ret', kind: 'ret' };
  if (b(0) === 0xB8) return { len: 5, mnem: `mov eax, 0x${u32(1).toString(16)}`, kind: 'movEax', imm: u32(1) };
  if (b(0) === 0x53) return { len: 1, mnem: 'push ebx', kind: 'push' };
  if (b(0) === 0x55) return { len: 1, mnem: 'push ebp', kind: 'push' };
  if (b(0) === 0x90) return { len: 1, mnem: 'nop', kind: 'nop' };
  if (b(0) === 0xE9) return { len: 5, mnem: `jmp 0x${(va + 5 + rel32(1)).toString(16)}`, kind: 'jmp', target: va + 5 + rel32(1) };
  return { len: 1, mnem: `db 0x${b(0).toString(16).padStart(2, '0')}`, kind: 'unknown' };
}

/** Decode [va, va+len) into a list of instructions. */
function disasm(buf, va, len) {
  const out = [];
  let o = 0;
  while (o < len) {
    const d = decode(buf, va2off(va) + o, va + o);
    d.off = o;
    d.va = va + o;
    d.hex = Array.from(buf.slice(va2off(va) + o, va2off(va) + o + d.len))
      .map((x) => x.toString(16).padStart(2, '0')).join(' ');
    out.push(d);
    if (d.kind === 'unknown') break;
    o += d.len;
  }
  return out;
}

function printListing(title, list, out) {
  out.push('');
  out.push(`--- ${title} ---`);
  for (const d of list) {
    out.push(`${d.va.toString(16).padStart(8, '0')}  ${d.hex.padEnd(24)} ${d.mnem}` + (d.note ? `   ; ${d.note}` : ''));
  }
}

/** Build the runtime (table) prefix exactly as Test/ac_zone_helper.cs writes it. */
function runtimePrefix(ALIVE, TABLE) {
  const b = Buffer.alloc(ORIG_BLOCK);
  const put = (i, arr) => arr.forEach((x, k) => { b[i + k] = x; });
  put(0, [0x83, 0xFA, 0x28]);                 // cmp edx,28h
  put(3, [0x73, 0x17]);                       // jae ORIG
  put(5, [0x80, 0x3D]);                       // cmp byte [ALIVE],0
  b.writeUInt32LE(ALIVE, 7); b[11] = 0x00;
  put(12, [0x74, 0x08]);                      // je NOTALIVE
  put(14, [0x8B, 0x04, 0x95]);                // mov eax,[edx*4+TABLE]
  b.writeUInt32LE(TABLE, 17);
  b[21] = 0xC3;                               // ret
  put(22, [0xB8, 0x01, 0x00, 0x00, 0x00]);    // NOTALIVE: mov eax,1
  b[27] = 0xC3;                               // ret
  return b;
}

// set by main() when --no-diff skipped the strongest half of the proof
let skippedDiff = false;

function main() {
  const args = process.argv.slice(2);
  // `--orig <path>` takes a value; every other non-flag argument is positional:
  // [0] = the engine to verify. (A previous version excluded index 0 here it
  // treated as the --orig value, so an explicitly passed engine was silently
  // ignored and the DEPLOYED one was checked instead - which made the whole
  // proof vacuous for mutation tests.)
  const origIdx = args.indexOf('--orig');
  const origArg = origIdx >= 0 ? args[origIdx + 1] : null;
  const noDiff = args.includes('--no-diff');
  // only the VALUE of --orig is skipped; with no --orig nothing is skipped
  const positional = args.filter((a, i) => !a.startsWith('--') && !(origIdx >= 0 && i === origIdx + 1));
  const explicitOrig = !!origArg;
  const origPath = explicitOrig
    ? path.resolve(origArg)
    : path.join(__dirname, '..', 'AutoControl_native', 'original', 'AutoCtrl_2025.4.22.0.exe');
  const exePath = positional[0] ? path.resolve(positional[0])
    : path.join(process.env.LOCALAPPDATA, 'AutoControl', 'AutoCtrl_2025.4.22.0.exe');

  const out = [], fail = [];
  if (!fs.existsSync(exePath)) { console.error('engine not found: ' + exePath); process.exit(1); }
  const buf = fs.readFileSync(exePath);
  const orig = fs.existsSync(origPath) ? fs.readFileSync(origPath) : null;
  const shaOf = (b) => require('crypto').createHash('sha256').update(b).digest('hex').toUpperCase();
  const sha = shaOf(buf);
  const origSha = orig ? shaOf(orig) : null;

  out.push('PATCH BYTES PROOF (assembly <-> bytes)');
  out.push('  engine  : ' + exePath);
  out.push('  sha256  : ' + sha);
  out.push('  original: ' + (orig ? origPath : '(NOT FOUND)'));
  if (orig) {
    out.push('            sha256 ' + origSha + (origSha === PRISTINE_SHA
      ? '  (the pinned pristine build)'
      : '  (NOT the pinned pristine build - only a range diff against this file is meaningful)'));
    // A swapped/silently different default original would make the strongest
    // half of the proof meaningless (or trivially empty), so check it. An
    // EXPLICIT --orig may legitimately point at another build.
    if (!explicitOrig && origSha !== PRISTINE_SHA) {
      fail.push('the DEFAULT original is not the pinned pristine build (sha ' + origSha + ', expected ' + PRISTINE_SHA + ')');
    }
  } else if (!noDiff) {
    fail.push('pristine original not found at ' + origPath + ' - the "nothing else changed" half cannot run; pass --orig <pristine.exe> or --no-diff to accept the decode-only check');
  }

  // ---------- PATCH 1: the entry jump ----------
  const entry = disasm(buf, ENTRY, 5);
  printListing(`PATCH 1 - entry jump (VA 0x${ENTRY.toString(16)}, 5 bytes)`, entry, out);
  if (entry.length !== 1 || entry[0].kind !== 'jmp') fail.push('entry is not a single jmp instruction');
  else if (entry[0].target !== CAVE) fail.push(`entry jmp targets 0x${entry[0].target.toString(16)}, expected 0x${CAVE.toString(16)}`);
  else out.push(`  -> OK: jumps to the code cave (0x${CAVE.toString(16)})`);

  // ---------- PATCH 2: the cave (both variants) ----------
  const cavePre = buf.slice(va2off(CAVE), va2off(CAVE) + ORIG_BLOCK);
  const cave = disasm(buf, CAVE, CAVE_LEN);
  printListing(`PATCH 2 - code cave, FILE variant (VA 0x${CAVE.toString(16)}, ${CAVE_LEN} bytes)`, cave, out);

  if (cavePre.toString('hex') !== FILE_PREFIX_HEX) {
    fail.push('FILE prefix differs from the documented fallback: got ' + cavePre.toString('hex') +
      ', expected ' + FILE_PREFIX_HEX);
  } else out.push('  -> OK: the file prefix is byte-identical to the documented fallback (always match, reads no memory)');

  const origBlock = buf.slice(va2off(CAVE) + ORIG_BLOCK, va2off(CAVE) + ORIG_BLOCK + 5);
  if (origBlock.toString('hex') !== ORIG_BLOCK_HEX) fail.push('ORIG block != ' + ORIG_BLOCK_HEX);
  else out.push('  -> OK: ORIG block re-executes the displaced bytes (sub esp,20h; push ebx; push ebp)');

  const tail = disasm(buf, CAVE + ORIG_BLOCK + 5, 5);
  if (tail.length !== 1 || tail[0].kind !== 'jmp') fail.push('cave tail is not a jmp instruction');
  else if (tail[0].target !== RESUME) fail.push(`cave tail jumps to 0x${tail[0].target.toString(16)}, expected 0x${RESUME.toString(16)}`);
  else out.push(`  -> OK: the tail returns to 0x${RESUME.toString(16)} (the rest of the function body)`);

  // ---------- PATCH 2b: the RUNTIME variant (the code that actually runs) ----------
  // The helper rewrites bytes 0x00..0x1B in the process; the absolute addresses
  // are computed from the live module base (values below were observed live).
  const ALIVE = RT_ALIVE, TABLE = RT_TABLE;
  const rt = Buffer.from(buf);
  runtimePrefix(ALIVE, TABLE).copy(rt, va2off(CAVE));
  const rtList = disasm(rt, CAVE, ORIG_BLOCK);
  printListing(`PATCH 2b - code cave, RUNTIME variant written by the helper (VA 0x${CAVE.toString(16)}, ${ORIG_BLOCK} bytes)`, rtList, out);

  const seq = rtList.map((d) => d.kind);
  const seqOk = rtList.length === 8 && seq[0] === 'cmpEdx' && rtList[0].imm === 0x28 &&
    seq[1] === 'jae' && seq[2] === 'cmpMem' && rtList[2].imm === 0 &&
    seq[3] === 'je' && seq[4] === 'movTable' && seq[5] === 'ret' &&
    seq[6] === 'movEax' && rtList[6].imm === 1 && seq[7] === 'ret';
  if (!seqOk) fail.push('runtime variant does not decode to the documented sequence: ' + rtList.map((d) => d.mnem).join(' ; '));
  else out.push('  -> OK: decodes to cmp edx,28h / jae / cmp byte[alive],0 / je / mov eax,[edx*4+table] / ret / mov eax,1');

  const jae = rtList.find((d) => d.kind === 'jae');
  const je = rtList.find((d) => d.kind === 'je');
  if (!jae || jae.target !== CAVE + ORIG_BLOCK) fail.push(`jae does not land on ORIG (cave+0x${ORIG_BLOCK.toString(16)})`);
  else out.push(`  -> OK: jae lands exactly on ORIG (cave+0x${ORIG_BLOCK.toString(16)})`);
  if (!je || je.target !== CAVE + 0x16) fail.push('je does not land on NOTALIVE (cave+0x16)');
  else out.push('  -> OK: je lands exactly on NOTALIVE (cave+0x16)');

  const rets = rtList.filter((d) => d.kind === 'ret').length;
  const mem = rtList.filter((d) => d.kind === 'cmpMem' || d.kind === 'movTable').length;
  if (rets !== 2) fail.push(`runtime variant has ${rets} ret instructions, expected 2`);
  if (mem !== 2) fail.push(`runtime variant has ${mem} memory accesses, expected 2 (alive flag + table)`);
  const last = rtList[rtList.length - 1];
  if (!last || last.va + last.len !== CAVE + ORIG_BLOCK) {
    fail.push('runtime prefix does not exactly fill the reserved 0x1c bytes (it would clobber the ORIG block)');
  } else out.push('  -> OK: the runtime prefix fills exactly 0x1c bytes and stops before the ORIG block');

  // ---------- the "nothing else changed" half ----------
  if (orig && !noDiff) {
    out.push('');
    out.push('--- byte diff vs the original ---');
    out.push('  allowed to differ: ' + DIFF_RANGES.map(([s, l, n]) => `0x${s.toString(16)}+${l} (${n})`).join(', '));
    if (buf.length !== orig.length) {
      fail.push(`size differs: ${buf.length} vs ${orig.length}`);
    } else {
      let changed = 0, outside = 0, firstOutside = -1;
      for (let i = 0; i < buf.length; i++) {
        if (buf[i] === orig[i]) continue;
        changed++;
        if (!DIFF_RANGES.some(([s, l]) => i >= s && i < s + l)) { outside++; if (firstOutside < 0) firstOutside = i; }
      }
      if (outside) fail.push(`${outside} changed byte(s) OUTSIDE the documented ranges (first at 0x${firstOutside.toString(16)})`);
      else out.push(`  -> OK: ${changed} bytes differ, all inside the documented ranges; nothing else changed`);
      for (const [s, l, n] of DIFF_RANGES) {
        if (buf.slice(s, s + l).equals(orig.slice(s, s + l))) fail.push(`documented range "${n}" (0x${s.toString(16)}) is UNCHANGED - stale entry?`);
      }
    }
  } else {
    out.push('');
    out.push('--- byte diff SKIPPED (' + (noDiff ? '--no-diff' : 'original not found') + ') ---');
    out.push('  WARNING: the strongest half of the proof did NOT run - "nothing else changed" is');
    out.push('           UNPROVEN for this file. Only the decode + branch-target half is green.');
    skippedDiff = true;
  }

  out.push('');
  out.push(fail.length === 0
    ? (skippedDiff
      ? 'PROOF HOLDS (PARTIAL): the bytes decode to the documented assembly and every branch target is exact - but the byte diff was SKIPPED (--no-diff), so "nothing outside the documented ranges changed" is NOT proven.'
      : 'PROOF HOLDS: the bytes decode to the documented assembly, every branch target is exact, and nothing outside the documented ranges changed.')
    : 'PROOF FAILED:');
  fail.forEach((f) => out.push('  * ' + f));
  console.log(out.join('\n'));
  process.exit(fail.length ? 1 : 0);
}

// `skippedDiff` is declared above main() and set inside it.
// Only run when invoked as a script: mh_test requires this module to reuse the
// SAME runtimePrefix() the proof checks (B53f/B53g) instead of copying it.
if (require.main === module) main();
module.exports = {
  runtimePrefix,
  ENTRY, RESUME, CAVE, ORIG_BLOCK, CAVE_LEN, FILE_DELTA, va2off,
  FILE_PREFIX_HEX, ORIG_BLOCK_HEX, DIFF_RANGES, PRISTINE_SHA,
  RT_ALIVE, RT_TABLE,
};
