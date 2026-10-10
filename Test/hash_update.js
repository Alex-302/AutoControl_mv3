// hash_update.js - sweep/update the build hashes quoted across the repo.
//
// WHY: a rebuild changes the engine sha256, the helper sha256 and the payload
// md5; the values are quoted in many docs and machine-checked (mh_test B57/B58,
// B61). Docs/BUILD-NATIVE.md section C requires a sweep after every rebuild;
// this tool performs it as one command: it reads the CURRENT values from
// Test/build_native.ps1 (the source of truth), finds every occurrence of the
// OLD values and either updates the claim sites (--apply) or reports them.
//
// Usage:
//   node Test/hash_update.js
//   node Test/hash_update.js --engine <sha64> --helper <sha64> --dat-md5 <md5-32> [--apply]
//   node Test/hash_update.js ... --apply --no-retire
//
// Without arguments it is a CHECK: report every file:line quoting the current
// values (full and short forms) and their claim-site status; nothing changes.
// With new values it is a rebuild sweep: replace the CURRENT (old) values with
// the NEW ones; without --apply it is a dry run (prints what would change).
// --no-retire skips adding the old values to the mh_test retired fixtures.
//
// Rules: a line carrying a historical marker (date / "previous" / "was " /
// "retired" / ... - the B58 rule) is NEVER rewritten; it is reported so the
// date/marker can be checked by hand. Test/mh_test.js is special-cased: its
// RETIRED fixtures and DEFAULT_SHA are updated structurally, not by blind
// replace. ext-mv2/, Docs/archive/ and Test/archive/ are never touched.
//
// Exit code 0 = nothing left to do (or a successful apply), 1 = findings that
// need a manual look (check mode) / nothing was applied.
'use strict';
const fs = require('fs');
const path = require('path');

const ROOT = path.join(__dirname, '..');
const args = process.argv.slice(2);
const APPLY = args.includes('--apply');
const NO_RETIRE = args.includes('--no-retire');
const opt = (name) => { const i = args.indexOf(name); return i >= 0 ? args[i + 1] : null; };

const NEW_ENGINE = opt('--engine');
const NEW_HELPER = opt('--helper');
const NEW_DAT = opt('--dat-md5');

// ---------- source of truth (current values) ----------
const buildPs1Path = path.join(__dirname, 'build_native.ps1');
const buildPs1 = fs.readFileSync(buildPs1Path, 'utf8');
const cur = {
  engine: (buildPs1.match(/\$EXPECT_ENGINE\s*=\s*'([0-9A-F]{64})'/) || [])[1],
  helper: (buildPs1.match(/\$EXPECT_HELPER\s*=\s*'([0-9A-F]{64})'/) || [])[1],
  dat: (buildPs1.match(/\$EXPECT_DAT_MD5\s*=\s*'([0-9A-F]{32})'/) || [])[1]
};
if (!cur.engine || !cur.helper || !cur.dat) {
  console.error('hash_update: cannot read $EXPECT_ENGINE/$EXPECT_HELPER/$EXPECT_DAT_MD5 from build_native.ps1');
  process.exit(2);
}

const pairs = [];
if (NEW_ENGINE) pairs.push({ name: 'engine sha256', old: cur.engine, next: NEW_ENGINE.toUpperCase() });
if (NEW_HELPER) pairs.push({ name: 'helper sha256', old: cur.helper, next: NEW_HELPER.toUpperCase() });
if (NEW_DAT) pairs.push({ name: 'payload md5', old: cur.dat, next: NEW_DAT.toUpperCase() });
// check mode (no new values): scan for the CURRENT values so the user can see
// every claim site before a rebuild
if (!pairs.length) {
  pairs.push({ name: 'engine sha256', old: cur.engine, next: cur.engine, check: true });
  pairs.push({ name: 'helper sha256', old: cur.helper, next: cur.helper, check: true });
  pairs.push({ name: 'payload md5', old: cur.dat, next: cur.dat, check: true });
}

const MARKER = /2026-\d\d-\d\d|previous|legacy|was |first build|Status 20|now `|bak-|superseded|retired|non-reproducible|historical|pre-20/i;
const SKIP_DIRS = new Set(['.git', 'node_modules', 'ext-mv2', 'archive']);
const BINARY = /\.(exe|dat|png|jpg|gif|ico|zip|crx|acs|svg|woff2?|ttf)$/i;

function walk(dir, out) {
  for (const d of fs.readdirSync(dir, { withFileTypes: true })) {
    if (SKIP_DIRS.has(d.name)) continue;
    const p = path.join(dir, d.name);
    if (d.isDirectory()) walk(p, out);
    else if (!BINARY.test(d.name)) out.push(p);
  }
  return out;
}

const files = walk(ROOT, []);
const findings = [];   // { file, line, text, cls }
const edits = new Map(); // file -> [{ line, from, to }]

function classify(text, prev, next) {
  if (MARKER.test(prev + '\n' + text + '\n' + next)) return 'history';
  return 'claim';
}

for (const file of files) {
  const rel = path.relative(ROOT, file).replace(/\\/g, '/');
  const lines = fs.readFileSync(file, 'utf8').split(/\r?\n/);
  for (let i = 0; i < lines.length; i++) {
    const upper = lines[i].toUpperCase();
    for (const p of pairs) {
      // full form first; the short form only when the full one is absent (the
      // full hash CONTAINS its short prefix - matching both would double-report)
      const forms = p.name === 'payload md5'
        ? (upper.includes(p.old) ? [p.old] : [])
        : (upper.includes(p.old) ? [p.old] : (upper.includes(p.old.slice(0, 16)) ? [p.old.slice(0, 16)] : []));
      for (const form of forms) {
        const cls = classify(lines[i], lines[i - 1] || '', lines[i + 1] || '');
        findings.push({ file: rel, line: i + 1, text: lines[i].trim().slice(0, 160), cls, pair: p.name, form });
        if (cls === 'claim' && !p.check && rel !== 'Test/mh_test.js') {
          if (!edits.has(file)) edits.set(file, []);
          edits.get(file).push({ line: i, from: form, to: form === p.old ? p.next : p.next.slice(0, 16) });
        }
      }
    }
  }
}

// ---------- report ----------
if (pairs.length && pairs[0].check) {
  console.log('hash_update: check mode (current values from build_native.ps1)');
  console.log('  engine ' + cur.engine);
  console.log('  helper ' + cur.helper);
  console.log('  payload md5 ' + cur.dat);
  console.log('');
  if (!findings.length) { console.log('  no occurrences found (?)'); process.exit(1); }
  console.log('occurrences of the CURRENT values:');
  for (const f of findings) console.log(`  [${f.cls}] ${f.file}:${f.line} (${f.pair}, ${f.form.slice(0, 16)}…) ${f.text}`);
  console.log('');
  console.log('usage: node Test/hash_update.js --engine <new64> --helper <new64> --dat-md5 <new32> [--apply]');
  process.exit(0);
}

console.log('hash_update: ' + (APPLY ? 'APPLY' : 'DRY RUN'));
for (const p of pairs) console.log(`  ${p.name}: ${p.old.slice(0, 16)}… -> ${p.next.slice(0, 16)}…`);
console.log('');

let claims = 0, history = 0;
for (const f of findings) {
  if (f.cls === 'claim') claims++; else history++;
  console.log(`  [${f.cls}] ${f.file}:${f.line} ${f.text}`);
}
console.log(`\n  claim occurrences: ${claims}, history occurrences (left alone): ${history}`);

if (!APPLY) {
  console.log('\ndry run - nothing changed; add --apply to update the claim sites.');
  process.exit(0);
}

// ---------- apply: claim-site replacements ----------
let changed = 0;
for (const [file, list] of edits) {
  const lines = fs.readFileSync(file, 'utf8').split(/\r?\n/);
  for (const e of list) {
    const before = lines[e.line];
    lines[e.line] = lines[e.line].split(e.from).join(e.to);
    if (lines[e.line] !== before) changed++;
  }
  fs.writeFileSync(file, lines.join('\n'));
  console.log('  updated ' + path.relative(ROOT, file).replace(/\\/g, '/'));
}

// ---------- apply: mh_test structural edits ----------
const mhPath = path.join(__dirname, 'mh_test.js');
let mh = fs.readFileSync(mhPath, 'utf8');
let mhChanged = false;
const engPair = pairs.find(p => p.name === 'engine sha256');
const hlpPair = pairs.find(p => p.name === 'helper sha256');
const datPair = pairs.find(p => p.name === 'payload md5');

if (engPair) {
  const re = /const DEFAULT_SHA = '[0-9A-F]{64}';/;
  if (re.test(mh)) { mh = mh.replace(re, "const DEFAULT_SHA = '" + engPair.next + "';"); mhChanged = true; }
}
if (!NO_RETIRE) {
  if (hlpPair && !mh.includes("'" + hlpPair.old + "'")) {
    mh = mh.replace(/(const RETIRED = \[\n)/, "$1    '" + hlpPair.old + "',\n");
    mhChanged = true;
  }
  if (datPair && !mh.includes("'" + datPair.old + "'")) {
    mh = mh.replace(/(const RETIRED_MD5 = \[)/, "$1'" + datPair.old + "', ");
    mhChanged = true;
  }
}
if (mhChanged) { fs.writeFileSync(mhPath, mh); console.log('  updated Test/mh_test.js (DEFAULT_SHA / retired fixtures)'); }

console.log('\napplied: ' + changed + ' line(s) in ' + edits.size + ' file(s)' + (mhChanged ? ' + mh_test fixtures' : ''));
console.log('Next: re-run `node Test/verify_all.js`; fix any remaining [history] lines by hand (dated block).');
process.exit(0);
