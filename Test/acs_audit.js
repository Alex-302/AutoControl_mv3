// acs_audit.js - audit an AutoControl settings file (.acs/.dat) for HIDDEN or
// un-scoped actions. Read-only: prints findings, changes nothing.
//
// Why: an action can be EXECUTED by the engine while being INVISIBLE in the
// settings UI — the UI renders actions per SECTION tab, so an action whose
// `sctnId` does not exist in `sections` is undisplayable (and undeletable from
// the UI) yet perfectly alive. That looks like a "phantom action" doing things
// the user never configured (real case 2026-09-12: wheel over the browser-menu
// button switched tabs while the settings showed nothing of the sort).
//
// It also lists wheel combinations WITHOUT a "mouse over" condition (those fire
// anywhere), disabled groups with wheel triggers (the engine skips them, the SW
// zone gate used to keep gating with them - fixed 2026-09-13) and every trigger
// that switches tabs, with its regions.
//
// Usage:
//   node Test/acs_audit.js "C:\path\to\AutoControl settings.acs"
//   node Test/acs_audit.js            (defaults to Test/AutoControl-settings-test.acs)
'use strict';
const fs = require('fs');
const path = require('path');
const P = process.argv[2] || path.join(__dirname, 'AutoControl-settings-test.acs');
const j = JSON.parse(fs.readFileSync(P, 'utf8'));

const sections = new Map();
for (const s of (j.sections || [])) sections.set(String(s.id), s.name);
console.log('file            : ' + P);
console.log('sections        : ' + ([...sections.entries()].map(([i, n]) => i + '=' + (n || '?')).join(', ') || '(none)'));
const list = j.trigActList || [];
console.log('trigActList     : ' + list.length + ' entries');
console.log('mouseGest.triggers: ' + ((j.mouseGest && j.mouseGest.triggers) || []).length);

const KIND = { 512: 'wheel-DOWN 512', 1536: 'wheel-UP 1536' };
const flagsAll = [];
console.log('\n=== per-action audit ===');
for (const [id, t] of list) {
  if (!t) { console.log(`  id ${id}: NULL`); flagsAll.push(`${id}: null data`); continue; }
  const flags = [];
  const hasSctn = Object.prototype.hasOwnProperty.call(t, 'sctnId');
  if (!hasSctn) flags.push('NO sctnId key');
  else if (!sections.has(String(t.sctnId))) flags.push(`*** INVISIBLE in the UI: sctnId=${t.sctnId} is not in sections`);
  if (t.disabled) flags.push('DISABLED');
  if (!t.title) flags.push('no title');

  const wheel = [];
  let anyScoped = false, anyUnscoped = false;
  for (const tr of (t.triggers || [])) {
    const mo = (tr && tr.preconds && Array.isArray(tr.preconds.mouseOver))
      ? tr.preconds.mouseOver.filter(x => x && x.region != null).map(x => x.region) : [];
    const scoped = mo.length > 0;
    if (scoped) anyScoped = true; else anyUnscoped = true;
    for (const c of (tr.combins || [])) {
      if (c.eventId === 512 || c.eventId === 1536) {
        const keys = (c.preconds || []).map(pc => JSON.stringify(pc)).join(',');
        wheel.push(`${KIND[c.eventId]} block=${c.block} wild=${c.wildcard} keys=[${keys}] mouseOver=${scoped ? '[' + mo.join(',') + ']' : '-'}`);
      }
    }
  }
  const acts = [];
  for (const a of (t.actions || [])) {
    for (const s of (a.sequence || [])) acts.push(String(s.action));
  }
  if (wheel.length) {
    console.log(`  id ${id}  "${t.title || '(untitled)'}"  sctnId=${hasSctn ? t.sctnId : '(absent)'}${flags.length ? '   <<< ' + flags.join('; ') : ''}`);
    console.log(`      actions: ${acts.join(', ') || '(none)'}`);
    for (const w of wheel) console.log('      ' + w);
    if (anyUnscoped) flagsAll.push(`${id}: has a combo WITHOUT mouse-over (fires anywhere)`);
  } else if (flags.length) {
    console.log(`  id ${id}  "${t.title || '(untitled)'}"  actions: ${acts.join(', ') || '(none)'}`);
    console.log(`      <<< ${flags.join('; ')}`);
  }
  if (flags.some(f => f.startsWith('***'))) flagsAll.push(`id ${id} ("${t.title || 'untitled'}"): ${flags.filter(f => f.startsWith('***'))[0]}`);
}

console.log('\n=== summary of suspicious entries ===');
if (!flagsAll.length) console.log('  none');
for (const f of flagsAll) console.log('  * ' + f);

console.log('\n=== every trigger that switches tabs (switchRight/switchLeft/activateTabs/...) ===');
for (const [id, t] of list) {
  if (!t) continue;
  const acts = [];
  for (const a of (t.actions || [])) for (const s of (a.sequence || [])) acts.push(String(s.action));
  if (!acts.some(a => /switch|activate|tab/i.test(a))) continue;
  const evs = [];
  for (const tr of (t.triggers || [])) {
    const mo = (tr.preconds && Array.isArray(tr.preconds.mouseOver)) ? tr.preconds.mouseOver.map(x => x.region) : [];
    for (const c of (tr.combins || [])) evs.push(`${c.eventId}${mo.length ? '/over-' + mo.join('+') : '/anywhere'}${(c.preconds || []).length ? '/' + JSON.stringify(c.preconds) : ''}`);
  }
  console.log(`  id ${id} "${t.title || '(untitled)'}" sctnId=${t.sctnId} disabled=${!!t.disabled}  actions=[${acts.join(',')}]  combos=[${evs.join(' | ')}]`);
}
