// ============================================================================
// AutoControl Scripting API — self-test (MV3 port, 2026-08-02)
// ----------------------------------------------------------------------------
// Runs as a regular script (RUN SCRIPT action) on any normal page
// (NOT on chrome:// or the Web Store — scripts do not run there).
//
// Each test is wrapped in try/catch, results are collected into an array,
// at the end — alert() with a summary + full console log (PASS/FAIL).
//
// Notes on the "delicate" tests:
//   - openURL/closeTab/setTabState only touch their OWN test tab
//     (data:text/html) — other tabs are left alone;
//   - setClipboard overwrites the clipboard with "AC-API-TEST ...";
//   - execAction('#clpbrdPaste') pastes that text into the test tab;
//   - saveURL creates "<desktop>/AC-API-TEST.txt" (delete it after the test);
//   - runCommand executes `cmd /c echo AC-API-TEST` (safe);
//   - getFile for a LOCAL file requires the "Allow access to file
//     URLs" toggle in chrome://extensions (same as in MV2).
// ============================================================================

const results = [];
// Test name goes into the prefix (easy to search): [AC-API-TEST: <name>] PASS/FAIL …
const pass = (name, detail) => { results.push({ name, ok: true, detail }); console.log('[AC-API-TEST: ' + name + '] PASS' + (detail ? ' ' + detail : '')); };
// FAIL is logged with an unmissable banner + red styling: a failed test must
// be findable in a huge console dump by searching "[AC-API-TEST: FAIL]".
// The final FAILURES block (after SUMMARY) re-lists all of them compactly.
const fail = (name, err) => {
  const detail = String(err?.message ?? err);
  results.push({ name, ok: false, detail });
  console.error('\n============================================================');
  console.error('%c[AC-API-TEST: FAIL] ' + name, 'color:#F00;font-weight:bold;font-size:14px');
  console.error('  ' + detail);
  console.error('============================================================\n');
};
// Each test: record start/end time and duration — they land in the final
// summary (r.start/r.end/r.ms) and are printed right after the test.
const test = async (name, fn) => {
  const t0 = performance.now();
  const d0 = new Date();
  try { await fn(); } catch (e) { fail(name, e); }
  const d1 = new Date();
  const dt = performance.now() - t0;
  const last = results[results.length - 1];
  if (last && last.name === name) {
    last.start = d0;
    last.end = d1;
    last.ms = dt;
    console.log(`[AC-API-TEST: TIMING] ${name}: ${d0.toISOString().slice(11, 23)} → ${d1.toISOString().slice(11, 23)} (+${dt.toFixed(0)}ms)`);
  }
};
// Whole-run timing: [AC-API-TEST: STARTED] at start,
// [AC-API-TEST: FINISHED] + duration at the end (also in the alert).
const __acT0 = performance.now();
console.log('[AC-API-TEST: STARTED]', new Date().toISOString());
// Page CSP since 2026-08-03 (rounds 11-13) does NOT matter: import/runInPageCtx/
// include are injected via chrome.userScripts (MAIN world via API — no inline
// check applies; blob:/data: allowed by configureWorld).
// runInPageCtx(func) — FIXED 2026-08-06 (round 16, single-injection proxy):
// VM 21:52 PASS 2. Full set — 23/23 on the active tab.
// Errors come in different wrappers: direct CSP violation, blob: fetch,
// cascading TypeError from W() and "Unable to load URL" from onerror.
const isCsp = err => /Content Security Policy|CSP|script-src|blob:|dynamically imported module|Unable to load URL|Cannot read properties of undefined \(reading 'error'\)/i.test(String(err?.message ?? err));
const cspThrow = err => { throw new Error(String(err?.message ?? err) + ' — [page CSP] (if this is a runInPageCtx return — see Docs/FEATURES-MV3.md §7-6)'); };

// ---- 1. Constants ---------------------------------------------------------
await test('ACtl.TAB_ID', async () => {
  if (!ACtl.TAB_ID) throw new Error('TAB_ID falsy — is the script not running in a tab?');
  pass('ACtl.TAB_ID', 'tab ' + ACtl.TAB_ID);
});
await test('ACtl.STOP_CHAIN / STOP_FULL_SEQ', async () => {
  if (!ACtl.STOP_CHAIN || !ACtl.STOP_FULL_SEQ) throw new Error('STOP constants missing');
  pass('ACtl.STOP_CHAIN / STOP_FULL_SEQ');
});

// ---- 2. Variables (var / pubVar) ------------------------------------------
await test('ACtl.var (set/get/delete)', async () => {
  await ACtl.var('__apitest', { n: 42 });
  const v = await ACtl.var('__apitest');
  if (!v || v.n !== 42) throw new Error('roundtrip: ' + JSON.stringify(v));
  await ACtl.var('__apitest', null); // delete
  if ((await ACtl.var('__apitest')) !== undefined) throw new Error('delete did not work');
  pass('ACtl.var');
});
await test('ACtl.pubVar', async () => {
  await ACtl.pubVar('__apitest', 'pub');
  if ((await ACtl.pubVar('__apitest')) !== 'pub') throw new Error('roundtrip');
  await ACtl.pubVar('__apitest', null);
  pass('ACtl.pubVar');
});

// ---- 3. Tabs ----------------------------------------------------------------
let testTabId = null;
await test('ACtl.getTabIds("#currWinTabs")', async () => {
  const ids = await ACtl.getTabIds('#currWinTabs');
  if (!Array.isArray(ids) || !ids.length) throw new Error('no tabs in the window');
  if (!ids.includes(ACtl.TAB_ID)) throw new Error('current tab not in the list');
  pass('ACtl.getTabIds', ids.length + ' tabs');
});
await test('ACtl.getTabInfo', async () => {
  const [[, info]] = await ACtl.getTabInfo(ACtl.TAB_ID);
  if (!info || !info.id || !info.url) throw new Error('no info fields');
  pass('ACtl.getTabInfo', (info.title || '').slice(0, 30) + ' @ ' + info.url.slice(0, 40));
});
await test('ACtl.openURL (real URL, test tab)', async () => {
  // NOT data: — it loads instantly, so tabLoadEnd would fire BEFORE
  // ACtl.on manages to register (registration is a postMessage roundtrip).
  // A real URL with a cache-buster loads over the network (definitely slower
  // than the roundtrip), so the event is guaranteed to reach the handler.
  // This behavior is identical to MV2 (events are not buffered) — the doc
  // examples always use http URLs.
  const [id] = await ACtl.openURL('https://example.org/?ac-api-test=' + Date.now());
  if (!id) throw new Error('did not return a tabId');
  testTabId = id;
  pass('ACtl.openURL', 'tab ' + id);
});
await test('ACtl.on("tabLoadEnd", tabId) — no callback', async () => {
  if (!testTabId) throw new Error('no test tab');
  // Safety timeout: a COLD first load of the opened tab can take >8s (VM
  // 2026-08-07 run 1: FAIL at 8s while the load was still in flight; warm
  // runs arrive in ~0.4s). 15s covers cold starts. On timeout we FETCH the
  // tab state so the failure log shows whether the tab was still loading
  // (slow network) or the event was genuinely lost.
  const ev = await Promise.race([
    ACtl.on('tabLoadEnd', testTabId),
    ACtl.sleep(15000).then(async () => {
      let diag = '';
      try {
        const [[, info]] = await Promise.race([
          ACtl.getTabInfo(testTabId),
          ACtl.sleep(5000).then(() => [null, null])
        ]);
        diag = info
          ? 'tab=' + testTabId + ' status=' + info.status +
            ' url=' + String(info.url || '').slice(0, 90) +
            ' title=' + String(info.title || '').slice(0, 40)
          : 'getTabInfo timed out (5s)';
      } catch (e) { diag = 'getTabInfo failed: ' + String(e && e.message ? e.message : e); }
      throw new Error('timeout: tabLoadEnd did not arrive in 15s — ' + diag);
    })
  ]);
  if (!ev || !ev.tabId) throw new Error('event has no tabId');
  pass('ACtl.on', 'tabId ' + ev.tabId);
});
await test('ACtl.setTabState(pinned/unpin)', async () => {
  if (!testTabId) throw new Error('no test tab');
  const n = await ACtl.setTabState(testTabId, 'pinned');
  if (!n) throw new Error('0 tabs affected');
  await ACtl.setTabState(testTabId, 'pinned', false); // unpin
  pass('ACtl.setTabState', n + ' tab(s)');
});
await test('ACtl.runInTab(func)', async () => {
  // On the CURRENT tab (file42 is already there) — on a fresh tab n() would
  // retry with the same key → SW dedup BLOCK → [null] (flake).
  const r = await ACtl.runInTab(ACtl.TAB_ID, () => location.href);
  if (!Array.isArray(r) || !r[0]) throw new Error('result: ' + JSON.stringify(r));
  pass('ACtl.runInTab', r[0]);
});
await test('ACtl.closeTab (own test tab)', async () => {
  if (!testTabId) throw new Error('no test tab');
  const n = await ACtl.closeTab(testTabId);
  if (!n) throw new Error('0 tabs closed');
  testTabId = null;
  pass('ACtl.closeTab', n + ' closed');
});

// ---- 4. Screenshot -----------------------------------------------------------
await test('ACtl.captureTab(dataUri)', async () => {
  const [[, uri]] = await ACtl.captureTab(ACtl.TAB_ID);
  if (!uri || !uri.startsWith('data:image/png')) throw new Error('not a PNG dataUri');
  pass('ACtl.captureTab', uri.length + ' chars');
});

// ---- 5. Clipboard ------------------------------------------------------------
await test('ACtl.setClipboard(text) + getClipboard', async () => {
  const marker = 'AC-API-TEST ' + Date.now();
  const ok = await ACtl.setClipboard(marker);
  if (!ok) throw new Error('setClipboard returned false');
  const fmt = await ACtl.getClipboard('format');
  // The native component stores the text both as text and as html (for
  // rich-text compatibility) — the format may be 'text' OR 'html'.
  if (fmt !== 'text' && fmt !== 'html') throw new Error('clipboard format: ' + fmt);
  const txt = await ACtl.getClipboard('text');
  if (txt !== marker) throw new Error('text did not match: ' + JSON.stringify(txt));
  pass('ACtl.setClipboard/getClipboard', fmt);
});

// ---- 6. Files -------------------------------------------------------------------
let savedPath = null;
await test('ACtl.saveURL(dataUri → <desktop>)', async () => {
  const p = await ACtl.saveURL('data:text/plain,AC-API-TEST', '<desktop>/AC-API-TEST.txt');
  if (!p) throw new Error('did not return a path');
  savedPath = p;
  pass('ACtl.saveURL', p);
});
await test('ACtl.getFile(local file)', async () => {
  if (!savedPath) throw new Error('no saved path');
  const t = await ACtl.getFile(savedPath).catch(err => {
    // file:// access is NOT requested programmatically — it is a user toggle
    throw new Error(String(err) + ' — enable "Allow access to file URLs" on chrome://extensions');
  });
  if (t !== 'AC-API-TEST') throw new Error('content: ' + JSON.stringify(t));
  pass('ACtl.getFile', savedPath);
});
await test('ACtl.import (ES module via data: URL)', async () => {
  const mod = await ACtl.import('data:text/javascript,export const x = 42;').catch(err => {
    if (isCsp(err)) cspThrow(err); // rare: if configureWorld did not apply
    throw err;
  });
  if (!mod || mod.x !== 42) throw new Error('module: ' + JSON.stringify(mod));
  pass('ACtl.import', 'x = ' + mod.x);
});

// ---- 7. Actions / commands / placeholders --------------------------------------
await test('ACtl.execAction("#clpbrdPaste")', async () => {
  const r = await ACtl.execAction('#clpbrdPaste', ACtl.TAB_ID);
  if (!Array.isArray(r)) throw new Error('result: ' + JSON.stringify(r));
  pass('ACtl.execAction', r.join(','));
});
await test('ACtl.runCommand("cmd /c echo ...", getOutput)', async () => {
  const { exitCode, stdout } = await ACtl.runCommand('cmd /c echo AC-API-TEST', '<desktop>', true);
  if (exitCode !== 0 || !String(stdout || '').includes('AC-API-TEST'))
    throw new Error('exit=' + exitCode + ' stdout=' + JSON.stringify(stdout));
  pass('ACtl.runCommand', 'exit ' + exitCode);
});
await test('ACtl.expand("<url>")', async () => {
  const u = await ACtl.expand('<url>', ACtl.TAB_ID);
  if (!u || !u.startsWith('http')) throw new Error('expand: ' + JSON.stringify(u));
  pass('ACtl.expand', u.slice(0, 40));
});
await test('ACtl.switchState (nonexistent — undefined)', async () => {
  const s = await ACtl.switchState('__apitest_nonexistent');
  if (s !== undefined) throw new Error('expected undefined, got ' + s);
  pass('ACtl.switchState');
});

// ---- 8. Page context ------------------------------------------------------------
await test('ACtl.runInPageCtx(func)', async () => {
  // FIXED 2026-08-06 (round 16, single-injection proxy in sw.js) — the
  // return value works (VM 21:52: PASS 2). An active tab is required.
  const r = await ACtl.runInPageCtx(() => 1 + 1).catch(err => {
    if (isCsp(err)) cspThrow(err);
    throw err;
  });
  if (r !== 2) throw new Error('result: ' + r);
  pass('ACtl.runInPageCtx', r);
});

// ---- 9. include / runInPageCtx (page context) ------------------------------------
await test('ACtl.include(data:js)', async () => {
  // Unique URL: the include cache ("already included") lives on the page —
  // re-running the test on the same tab would return false without a
  // cache-buster.
  const ok = await ACtl.include('data:text/javascript,window.__acIncluded = ' + Date.now());
  if (!ok) throw new Error('include returned false');
  pass('ACtl.include');
});
await test('ACtl.runInPageCtx — file (data:js, again:true)', async () => {
  const ok = await ACtl.runInPageCtx('data:text/javascript,window.__acRipcFile = 7', true).catch(err => {
    if (isCsp(err)) cspThrow(err);
    throw err;
  });
  if (!ok) throw new Error('returned false');
  pass('ACtl.runInPageCtx (file)');
});

// ---- Summary --------------------------------------------------------------------------
const okCount = results.filter(r => r.ok).length;
const failCount = results.length - okCount;
const __acSec = ((performance.now() - __acT0) / 1000).toFixed(2);
const __acEnd = new Date();
// Align by the longest name — a readable per-test summary:
// status, name, details, start→end time and duration.
// Printed BEFORE the final lines so [AC-API-TEST: SUMMARY] stays the LAST line.
const __acW = Math.max(...results.map(r => r.name.length), 1);
for (const r of results) {
  const pad = ' '.repeat(Math.max(1, __acW - r.name.length));
  const span = (r.start && r.end)
    ? r.start.toISOString().slice(11, 23) + ' → ' + r.end.toISOString().slice(11, 23) + ' [' + r.ms.toFixed(0) + 'ms]'
    : '';
  console.log('[AC-API-TEST: ' + r.name + '] ' + (r.ok ? 'PASS' : 'FAIL') + pad + ' ' + (r.detail || '') + (span ? '  ' + span : ''));
}
console.log('[AC-API-TEST: FINISHED]', __acEnd.toISOString(), 'duration=' + __acSec + 's');
console.log('[AC-API-TEST: SUMMARY] ' + okCount + '/' + results.length + ' passed, ' + failCount + ' failed');
// Failures are re-printed at the very end as a compact, searchable block —
// even in a huge console dump, "[AC-API-TEST: FAILURES]" lands last and the
// banners above are grep-able by "[AC-API-TEST: FAIL]".
const __acFails = results.filter(r => !r.ok);
if (__acFails.length) {
  console.error('\n############################################################');
  console.error('%c[AC-API-TEST: FAILURES] ' + __acFails.length + ' failed — grep "[AC-API-TEST: FAIL]" for the banners above',
    'color:#F00;font-weight:bold;font-size:14px');
  __acFails.forEach((r, i) => {
    const span = (r.start && r.end)
      ? '  ' + r.start.toISOString().slice(11, 23) + ' → ' + r.end.toISOString().slice(11, 23) + ' [' + r.ms.toFixed(0) + 'ms]'
      : '';
    console.error('  ' + (i + 1) + '. [AC-API-TEST: FAIL] ' + r.name + span);
    console.error('     ' + r.detail);
  });
  console.error('############################################################\n');
} else {
  console.log('[AC-API-TEST: FAILURES] none — ' + results.length + '/' + results.length + ' passed');
}
// alert(`AutoControl API test:\n${okCount}/${results.length} passed, ${failCount} failed\nDuration: ${__acSec}s`);
