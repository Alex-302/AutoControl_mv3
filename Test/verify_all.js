// verify_all.js - one-command validation pass: the harness, the tool inventory
// and (when native files changed) the byte proof; ends with a single verdict.
//
// WHY: the check set from AGENTS.md is several separate commands, and a partial
// run is easy to mistake for a full one. This tool runs them in one go and
// prints PASS/FAIL, so "the checks were run" has one answer.
//
// Usage:
//   node Test/verify_all.js            # harness + inventory (+ byte proof when native files changed)
//   node Test/verify_all.js --native   # always include the byte proof
//   node Test/verify_all.js --quiet    # verdict block only
//
// Deliberately NOT included: the live run and the doc updates - they cannot be
// checked from here; the verdict block reminds about them.
'use strict';
const { spawnSync } = require('child_process');
const path = require('path');

const ROOT = path.join(__dirname, '..');
const QUIET = process.argv.includes('--quiet');
const FORCE_NATIVE = process.argv.includes('--native');

function runNode(script, args) {
  const r = spawnSync(process.execPath, [path.join(__dirname, script)].concat(args || []), {
    cwd: ROOT, encoding: 'utf8'
  });
  return { code: r.status === null ? 1 : r.status, out: (r.stdout || '') + (r.stderr || '') };
}

// Native = the files whose proof is the byte-level one (Docs/BUILD-NATIVE.md).
function nativeTouched() {
  if (FORCE_NATIVE) return true;
  const r = spawnSync('git', ['status', '--porcelain'], { cwd: ROOT, encoding: 'utf8' });
  if (r.error || r.status !== 0) return false;   // no git -> treat as not native
  return (r.stdout || '').split(/\r?\n/).some(l => {
    const p = l.slice(3).trim().replace(/\\/g, '/');
    return /^Test\/ac_zone_helper\.cs$/.test(p) || /^AutoControl_native\//.test(p);
  });
}

const NATIVE = nativeTouched();
const steps = [];
const add = (name, ok, detail) => steps.push({ name, ok, detail });
const line = (text, re, fallback) => (text.match(re) || [fallback])[0];

if (!QUIET) {
  console.log('verify_all: start (native proof: ' +
    (NATIVE ? 'included' : 'skipped - no native files changed, use --native to force') + ')');
}

// 1. the SW harness
{
  const r = runNode('mh_test.js');
  const summary = line(r.out, /SUMMARY:.*/m, '(no SUMMARY line)');
  if (!QUIET) console.log('\n== mh_test.js ==\n' + summary);
  add('harness (mh_test.js)', r.code === 0, summary);
}

// 2. the generated tool inventory
{
  const r = runNode('_tools_index.js', ['--check']);
  const detail = line(r.out, /TOOLS INVENTORY:.*/m, '(no verdict line)');
  if (!QUIET) console.log('\n== _tools_index.js --check ==\n' + detail);
  add('tool inventory (Test/README.md)', r.code === 0, detail);
}

// 3. the byte proof - only when the native side moved
if (NATIVE) {
  const r = runNode('patch_bytes_verify.js');
  const detail = line(r.out, /PROOF HOLDS.*/m, '(no PROOF HOLDS line)');
  if (!QUIET) console.log('\n== patch_bytes_verify.js ==\n' + detail);
  add('native byte proof (patch_bytes_verify.js)', r.code === 0, detail);
} else {
  add('native byte proof', true, 'skipped (no native files changed)');
}

console.log('\n================ VERDICT ================');
for (const s of steps) console.log((s.ok ? 'PASS' : 'FAIL') + '  ' + s.name + ' - ' + s.detail);
const failed = steps.filter(s => !s.ok);
console.log(failed.length ? 'VERDICT: FAIL (' + failed.length + ' step(s))' : 'VERDICT: PASS');
console.log('Still manual: the live-run line (browser + OS + physical action + observation) ' +
  'and the doc/CHANGELOG updates - Docs/CHANGE-HANDOFF.md.');
process.exit(failed.length ? 1 : 0);
