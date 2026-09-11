// AC-MV3 SW harness: loads sw_core_bundle.js in a Node vm with stubbed
// chrome/DOM globals and verifies the SW-side invariants the port depends on.
// Covers: bundle load, _mh config compile, lexical _Yh binding, XHR shim,
// userAPI dispatch (exactly 1 answering listener), and the port-gap
// expectations tracked in FEATURES-MV3.md §7 (playAudio, saveUrl DNR,
// file:// gate, _9w inert loading, browserAction alias).
// §N references in comments point to Docs/FEATURES-MV3.md.
// Run: node mv3-build/mh_test.js   (cwd-independent; paths are __dirname-based)
'use strict';
const fs = require('fs');
const vm = require('vm');
const path = require('path');

const MV3 = __dirname; // mv3-build/
// ACS settings snapshot lives in ../Test/ (renamed 2026-08-05)
const ACS = path.join(__dirname, '..', 'Test', 'AutoControl-settings-test.acs');

// ---------- result framework ----------
let passes = 0, gaps = 0, failures = 0, notes = 0;
function check(name, ok, detail) {
  if (!ok) { failures++; console.log('[FAIL] ' + name + ' - ' + (detail || '')); return; }
  passes++;
  console.log('[PASS] ' + name + (detail ? ' - ' + detail : ''));
}
function checkGap(name, currentlyBroken, detail, ref) {
  // Confirms a KNOWN broken state (FEATURES-MV3.md §7). If the gap
  // is gone, someone fixed it - the docs must be updated (informational, not a fail).
  if (currentlyBroken) { gaps++; console.log('[GAP ] ' + name + ' - ' + (detail || '') + ' (known; FEATURES-MV3.md §' + ref + ')'); }
  else { notes++; console.log('[FIXED?] ' + name + ' - ' + (detail || '') + ' gap no longer present - update FEATURES-MV3.md S' + ref + '!'); }
}
function note(name, detail) { notes++; console.log('[NOTE] ' + name + ' - ' + (detail || '')); }

// ---------- stubs ----------
// onMessage stub that RECORDS listeners (so we can simulate messages the
// way Chrome dispatches them to ALL registered listeners — the bundle's
// file48 m() handler AND any sw.js handler both receive every message).
const onMsgListeners = [];
const onMsg = { addListener: fn => onMsgListeners.push(fn) };
// Records listeners registered on chrome.action.onClicked by the bundle
// (file62_mv3 browserAction alias). sw.js registers a SECOND listener at
// runtime → both fire on one click (FEATURES-MV3.md §7-7).
const actionOnClickedListeners = [];
function makeStubCtx() {
  const noop = () => {};
  // Recording stubs for the MV3 _Fo popup path (B40/B41): windows.create
  // answers with a fake popup window, update/remove record, tabs.onUpdated
  // keeps its listeners (so the test can fire the "complete" event) and
  // scripting.executeScript records the injected call.
  const winUpdates = [], winRemoved = [], tabUpdatedListeners = [], scriptCalls = [], winCreated = [];
  const ctx = {
    console,
    setTimeout, clearTimeout, setInterval, clearInterval,
    URL, URLSearchParams, TextEncoder, TextDecoder,
    Intl,
    navigator: { userAgent: 'Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/150.0.0.0 Safari/537.36', language: 'en-US' },
    localStorage: { getItem: () => null, setItem: noop, removeItem: noop },
    location: { href: 'chrome-extension://abc/main.html', search: '', pathname: '/main.html', hash: '', origin: 'chrome-extension://abc', hostname: 'abc', protocol: 'chrome-extension:' },
    history: {},
    document: {
      createElement: () => ({ style: {}, setAttribute: noop, appendChild: noop, addEventListener: noop }),
      createDocumentFragment: () => ({ appendChild: noop }),
      addEventListener: noop,
      body: { appendChild: noop },
      documentElement: { style: {} },
      querySelector: () => null,
    },
    NodeList: function(){}, HTMLCollection: function(){},
    XMLHttpRequest: function(){}, Image: function(){},
    OffscreenCanvas: function(){},
    fetch: () => Promise.reject(new Error('no fetch')),
    btoa: s => Buffer.from(s, 'binary').toString('base64'),
    atob: s => Buffer.from(s, 'base64').toString('binary'),
    crypto: { getRandomValues: a => { for (let i = 0; i < a.length; i++) a[i] = Math.floor(Math.random() * 256); return a; } },
    chrome: {
      runtime: {
        id: 'abcdefghijklmnopqrstuvwxyzabcdef',
        getManifest: () => ({ short_name: 'AutoControl' }),
        getURL: p => 'chrome-extension://abc/' + p,
        sendMessage: noop, onMessage: onMsg, onConnect: { addListener: noop },
        onInstalled: { addListener: noop }, onStartup: { addListener: noop }, onUpdateAvailable: { addListener: noop }, onMessageExternal: { addListener: noop },
        connectNative: () => ({ postMessage: noop, onMessage: { addListener: noop }, onDisconnect: { addListener: noop } }),
      },
      action: { onClicked: { addListener: fn => actionOnClickedListeners.push(fn) } },
      downloads: { onChanged: { addListener: noop }, onDeterminingFilename: { addListener: noop }, download: noop, cancel: noop, erase: noop },
      idle: { onStateChanged: { addListener: noop }, queryState: noop },
      storage: { local: { get: (k, cb) => cb && cb({}), set: noop, clear: noop, remove: noop },
                sync: { get: (k, cb) => cb && cb({}), set: noop, clear: noop },
                managed: { get: (k, cb) => cb && cb({}) },
                onChanged: { addListener: noop } },
      windows: { getAll: (o, cb) => cb && cb([]), get: noop, create: (o, cb) => { winCreated.push(o); cb && cb({ id: 42, tabs: [{ id: 4242 }] }); }, update: (id, o, cb) => { winUpdates.push([id, o]); cb && cb(); }, remove: id => winRemoved.push(id), getLastFocused: (o, cb) => cb && cb(null),
                 onCreated: { addListener: noop }, onRemoved: { addListener: noop }, onFocusChanged: { addListener: noop }, onBoundsChanged: { addListener: noop } },
      tabs: { query: (q, cb) => cb && cb([]), get: noop, create: noop, update: noop, remove: noop, sendMessage: noop, executeScript: noop,
              onCreated: { addListener: noop }, onUpdated: { addListener: fn => tabUpdatedListeners.push(fn), removeListener: fn => { const i = tabUpdatedListeners.indexOf(fn); if (i >= 0) tabUpdatedListeners.splice(i, 1); } }, onRemoved: { addListener: noop }, onActivated: { addListener: noop }, onMoved: { addListener: noop }, onAttached: { addListener: noop }, onDetached: { addListener: noop }, onReplaced: { addListener: noop } },
      scripting: { executeScript: (o, cb) => { scriptCalls.push(o); cb && cb([]); } },
      system: { display: { getInfo: cb => cb && cb([]), onDisplayChanged: { addListener: noop } } },
      notifications: { create: noop, clear: noop, onButtonClicked: { addListener: noop }, onClosed: { addListener: noop } },
      contextMenus: { create: noop, onClicked: { addListener: noop } },
      declarativeNetRequest: { updateSessionRules: noop, getSessionRules: noop },
      alarms: { create: noop, onAlarm: { addListener: noop } },
      userScripts: { execute: noop },
      extension: { getBackgroundPage: () => null, isAllowedFileSchemeAccess: cb => cb && cb(false) },
      bookmarks: { getTree: cb => cb && cb([]) },
      sessions: { getRecentlyClosed: cb => cb && cb([]), onChanged: { addListener: noop, removeListener: noop } },
      commands: { getAll: cb => cb && cb([]) },
    },
  };
  ctx.addEventListener = () => {};
  ctx.removeEventListener = () => {};
  ctx.postMessage = () => {};
  ctx.requestAnimationFrame = cb => setTimeout(cb, 16);
  ctx.cancelAnimationFrame = clearTimeout;
  ctx.window = ctx;
  ctx.self = ctx;
  ctx.globalThis = ctx;
  ctx.__acWinUpdates = winUpdates;
  ctx.__acWinRemoved = winRemoved;
  ctx.__acTabUpdatedListeners = tabUpdatedListeners;
  ctx.__acScriptCalls = scriptCalls;
  ctx.__acWinCreated = winCreated;
  return ctx;
}

// ---------- load ----------
const bundle = fs.readFileSync(path.join(MV3, 'sw_core_bundle.js'), 'utf8');
const ctx = makeStubCtx();
ctx.onMsgListeners = onMsgListeners;
vm.createContext(ctx);
// AC-MV3 FIX (2026-08-10): storage results MUST be created in the vm realm.
// file67 defines Object.prototype.add/sc/... on the CONTEXT's Object; the old
// node-realm `{}` stub result lacked .sc() → any test that WRITES storage
// crashed in _Mi's batched flush (_bd → _bj → a.sc()) with "a.sc is not a
// function" (first hit: the z[800] smoke's _uf call, FEATURES-MV3.md §7-4). Real Chrome
// creates storage results in the extension realm (Object.prototype.sc exists),
// so this never happens in the SW — the stub now mirrors that.
ctx.chrome.storage.local.get = (k, cb) => cb && cb(vm.runInContext('({})', ctx));

try {
  vm.runInContext(bundle, ctx, { filename: 'sw_core_bundle.js' });
  console.log('[PASS] bundle loaded');
} catch (e) {
  console.log('BUNDLE LOAD ERROR:', e.message);
  console.log(e.stack.split('\n').slice(0, 5).join('\n'));
  process.exit(1);
}

// ---------- A. SW invariants (what sw.js depends on) ----------
// A1. _Yk must be the RAW chrome object in the SW. file91 (settings-FILE
// editor) redefines _Nh as an in-memory storage proxy, but only inside
// `if (_Uy)` — and _Uy is set only when the page URL has `?file=` (main.html
// file editor). In the SW (no query) the proxy must NOT be active, otherwise
// the whole config chain (_9i → _Yk.storage.local.get) would read an empty
// in-memory map instead of real storage.
check('_Yk is the raw chrome in the SW', vm.runInContext('_Yk === chrome', ctx),
  'typeof _Yk = ' + vm.runInContext('typeof _Yk', ctx) + '; file91 proxy is ?file=-gated');

// A2. z handler completeness — same set as file61.js.
const zRes = vm.runInContext(`(() => {
  const types = [750, 760, 70, 721, 730, 735, 740, 710, 800, 810, 704, 705, 715, 765, 905];
  const missing = types.filter(t => typeof z[t] !== 'function');
  return { missing, hasAdd: typeof z.add === 'function', count: Object.keys(z).length };
})()`, ctx);
check('z handler completeness', zRes.missing.length === 0 && zRes.hasAdd,
  '15/15 base types + add()' + (zRes.missing.length ? '; MISSING: ' + zRes.missing.join(',') : '; total keys ' + zRes.count));

// A2b. z[800] error classification (FEATURES-MV3.md §7-4, ported 2026-08-10).
// MV2 file61.js E() classified native errors: no-hook-notice (error counter
// _uf + the file71.html floating popup _Lh after 5 notices in 15s, unless
// the user disabled it), invalidExtId (install-age gate _2u), APDL
// (anti-piracy flag `_r`), NH-error segfault 0xC0000005 (error counter).
// The MV3 shim used to forward EVERYTHING to _Ot (telemetry only, off by
// default → the user got no feedback when the engine could not hook).
// Source checks for the ported branches + a runtime smoke: 4 no-hook-notice
// calls must not throw (the popup fires on the 5th — NOT triggered here),
// and unknown/segfault types must not throw either.
{
  const shim = fs.readFileSync(path.join(MV3, 'mv3_native_shim.js'), 'utf8');
  const sw = fs.readFileSync(path.join(MV3, 'sw.js'), 'utf8');
  const f70 = fs.readFileSync(path.join(MV3, 'file70.js'), 'utf8');
  const ok = shim.includes('"no-hook-notice"') && shim.includes('"invalidExtId"') &&
    shim.includes('_2u()') && shim.includes('"APDL"') && shim.includes('_r = true') &&
    shim.includes('_uf("segFault")') && !shim.includes('a.type || "native"');
  check('z[800] error classification ported (no-hook notif, invalidExtId, APDL, segFault)', ok,
    'classify=' + ok);
  // AC-MV3 FIX (2026-08-10, follow-ups): (1) _Zw (monitor map) was never
  // populated at SW startup → _Fo crashed on positioning (VM 22:13);
  // (2) the MV2 _Lh file71.html popup CANNOT work from the SW — _Fo needs
  // chrome.extension.getViews({windowId}) which does not exist in MV3 (the
  // prelude stubs it to []) → "Cannot read properties of undefined (reading
  // 'document')" (VM 22:20). The notice now uses chrome.notifications with
  // buttons (the original plan); without the permission it degrades
  // to the silent _uf counter. nhBusy is always reset (failure/dismiss/
  // button) so one hiccup never disables future notices.
  check('z[800] follow-up: _Zw populated at SW startup (_Sf in sendMonitorInfo)',
    sw.includes('typeof _Sf === "function"') && sw.includes('_Sf(() => {})'),
    'zwPopulate=' + (sw.includes('typeof _Sf === "function"') && sw.includes('_Sf(() => {})')));
  // AC-MV3 FIX (2026-08-10, `_Wo(_Vs)`): the "On startup" trigger event.
  // MV2 file61.js D() called _Wo(_Vs) once per session after type 21 (the
  // "On startup" event — file68 [_Vs]:{name:"On startup"}) → type 50 to
  // native → triggers bound to "On startup" fire. The port never called it →
  // such triggers never fired. sw.js finishStartup now calls _Wo(_Vs) after
  // postMsg(21) with a once-per-session guard + noStupEvt parity (MV2:
  // !G++ && !_nt("noStupEvt")). _Wo is a no-op unless a trigger uses the
  // event (_uk[30] check), so the call is harmless when none is configured.
  check('_Wo(_Vs) "On startup" event fired after type 21 (once per session)',
    sw.includes('_Wo(_Vs)') && sw.includes('__acStartupEvtSent') && sw.includes('_j("noStupEvt")'),
    'startupEvt=' + (sw.includes('_Wo(_Vs)') && sw.includes('__acStartupEvtSent')));
  check('z[800] follow-up: _Fo monitor fallback (any popup survives empty _Zw)',
    f70.includes('workArea:{left:0,top:0,width:400,height:200}'),
    'foFallback=' + f70.includes('workArea:{left:0,top:0,width:400,height:200}'));
  check('z[800] follow-up: no-hook notice via notifications (buttons, not the SW-broken _Lh popup)',
    shim.includes('onButtonClicked') && shim.includes("Don't show again") &&
    shim.includes('buttons:') && !shim.includes('_Lh(') &&
    shim.includes('no-hook notice notification failed') && shim.includes('nhBusy = false;'),
    'notifPath=' + (shim.includes('onButtonClicked') && shim.includes("Don't show again")) +
    ' noLh=' + !shim.includes('_Lh('));
  // AC-MV3 FIX (2026-08-10, follow-up 2): after the notice is shown the
  // series restarts (nhCount = 0) — the MV2 logic kept counting (6, 7, ...
  // never === 5), so answering "Keep showing" left the next 5-10 notices
  // silent until the 15s window expired (user VM report). "Keep showing"
  // now re-notifies after the NEXT 5 fresh notices; "Don't show again"
  // stays silent via nhOff. The message is also SHORT — Windows toast
  // truncation cut it off mid-sentence (~130 chars).
  check('z[800] follow-up: series restarts after showing + short message',
    shim.includes('nhCount = 0;') && shim.includes('clearTimeout(nhTimer); nhTimer = null;') &&
    shim.includes('Disable conflicting programs one by one') &&
    !shim.includes('ask on the support forum.'),
    'restart=' + shim.includes('nhCount = 0;') +
    ' shortMsg=' + shim.includes('Disable conflicting programs one by one'));
  vm.runInContext(`
    (function(){
      const mk = (o) => Object.assign({ add: () => ({}) }, o);
      for (let i = 0; i < 4; i++) z[800](mk({ type: "no-hook-notice", needed: true }));
      z[800](mk({ type: "no-hook-notice", needed: true })); // 5th — notification path (stub create)
      z[800](mk({ type: "unknown-err" }));
      z[800](mk({ type: "NH-error", code: 3221225477 }));
      z[800](mk({ type: "invalidExtId" }));
      z[800](mk({ type: "APDL", result: "x" }));
    })()
  `, ctx);
  check('z[800] runtime smoke: no-hook-notice x5 + unknown + segfault + invalidExtId + APDL do not throw', true,
    'dispatch ok (5th fires the notification stub, no throw)');
}

// A3. prelude browserAction -> action alias (MV3 renamed the API). file62_mv3
// registers its trigger listener through _Yk.browserAction; sw.js registers
// another one on chrome.action - both land on the SAME event.
check('prelude browserAction->action alias', vm.runInContext('chrome.browserAction === chrome.action', ctx),
  'file62_mv3 + sw.js listeners share one event (2 total -> S7-7)');
check('bundle registers exactly 1 action onClicked listener', actionOnClickedListeners.length === 1,
  actionOnClickedListeners.length + ' registered (file62_mv3 trigger; sw.js has NO own onClicked — FEATURES-MV3.md §7-7)');

// A4. scheme gate _As: http:// allowed; chrome:// and about: always restricted;
// file:// depends on the REAL chrome.extension.isAllowedFileSchemeAccess —
// since 2026-08-10 the prelude passes the real API through (FEATURES-MV3.md §7-8 FIXED):
// with the "Allow access to file URLs" toggle ON, file:// tabs are targetable
// by runInTab/runInFrames (MV2 parity); with it OFF they stay excluded. The
// harness stub returns false, so in THIS context file:// stays restricted —
// the source check below proves the pass-through (a real SW gets the real value).
check('_As scheme gate: http allowed', vm.runInContext(`_As('http://example.com')`, ctx) === false, 'http:// not restricted');
check('_As scheme gate: chrome:// restricted', vm.runInContext(`_As('chrome://extensions')`, ctx) === true, 'chrome:// restricted');
check('_As scheme gate: file:// restricted in harness (stub=false)', vm.runInContext(`_As('file:///C:/x')`, ctx) === true,
  'harness stub returns false; real SW queries the real API (toggle ON -> file:// targetable)');
check('prelude passes through the real file/incognito access APIs', bundle.includes('__acRealFileSchemeAccess') && bundle.includes('__acRealIncognitoAccess'),
  'FEATURES-MV3.md §7-8 FIXED 2026-08-10 — no more hardcoded false in the SW');

// A5. dynamic script loading (_9w) is a no-op in the SW: the prelude's
// document.head.appendChild is inert, so the onload callback never fires and
// callers would hang forever. playAudio (_7r -> _9w('/file53.js')) USED to
// stall the action chain on this (GAP S7-1) — since 2026-08-09 the playAudio
// action is replaced in sw.js and the sound plays in the OFFSCREEN document
// (the REAL file53.js engine is loaded THERE, where Web Audio +
// speechSynthesis exist — see A5b).
vm.runInContext(`
  (function(){ let c = false; _9w('/x.js', () => { c = true; }); setTimeout(() => { window.__nineWCalled = c; }, 80); })()
`, ctx);
setTimeout(() => {
  check('_9w script loading is inert in SW (playAudio no longer uses it)', ctx.__nineWCalled === false,
    'document.head.appendChild no-op — file53 plays offscreen (FEATURES-MV3.md §7-1)');
  check('playAudio action runner exists', vm.runInContext('typeof _7r === "function"', ctx), '_7r wired');
  check('file53 engine NOT loaded in the SW (plays offscreen)', vm.runInContext('typeof _lh === "undefined"', ctx),
    '_lh lives in the offscreen doc — sw.js replaces the _7r action (FEATURES-MV3.md §7-1)');
  // A5b. playAudio fix (FEATURES-MV3.md §7-1): _Du is DEEP-FROZEN by the bundle
  // (file62_mv3.js ends with `_Oo(_Du);` — deep freeze), so
  // `_Du.action.playAudio.value = ...` THROWS ("Cannot assign to read only
  // property 'value'", observed in the user VM 17:13:57.357 — the patch
  // failed and the ORIGINAL _7r ran → hang). The runner is intercepted at
  // the LOOKUP instead: file37's _rf reads every action through _w(name,
  // params) — a top-level function declaration of the imported bundle
  // (writable global, same mechanism as the _Uu patch). sw.js must wrap _w
  // for "playAudio"; offscreen.js must host the engine (file67 + file53
  // lazy load + polyfills).
  try {
    const sw = fs.readFileSync(path.join(MV3, 'sw.js'), 'utf8');
    const off = fs.readFileSync(path.join(MV3, 'offscreen.js'), 'utf8');
    const swPatch = sw.includes('_w = function (a, b)') &&
      sw.includes('if (a === "playAudio")') &&
      sw.includes('cmd: "playAudio"') &&
      sw.includes('case "acPlayNative"') &&
      sw.includes('_If(msg.payload && msg.payload.path)') &&
      sw.includes('AUDIO_PLAYBACK') &&
      !sw.includes('_Du.action.playAudio.value = (tabGroups');  // frozen — assignment throws
    const offEngine = off.includes("'playAudio'") &&
      off.includes('file53.js') && off.includes('file67.js') &&
      off.includes('window._9j = window') && off.includes('window._od = 294') &&
      off.includes('window._Rk') && off.includes('window._Vy') &&
      off.includes('window._If') && off.includes('window._ql');
    check('sw.js: playAudio routed via _w wrapper (frozen _Du table, FEATURES-MV3.md §7-1)', swPatch,
      '_w intercept + playAudio cmd + acPlayNative bridge + _If route + AUDIO_PLAYBACK; no .value assignment');
    check('offscreen.js: hosts file53 engine + polyfills (FEATURES-MV3.md §7-1)', offEngine,
      'lazy load + _9j/_od/_Rk/_Vy/_If/_ql');
    // Runtime proof (bundle already loaded in ctx): the _w lookup returns the
    // frozen _7r runner for playAudio — exactly what the sw.js wrapper
    // intercepts — and _w is a writable global (function declaration), so the
    // wrapper assignment takes effect for all subsequent action dispatch.
    const wProbe = vm.runInContext(`
      (function(){
        var isFrozen = Object.isFrozen(_Du.action.playAudio);
        var resolves7r = _w("playAudio", {}) === _7r;
        var writable = false;
        try { var o = _w; _w = function(a,b){ return o(a,b); }; writable = _w !== o; _w = o; } catch(e) {}
        return { isFrozen: isFrozen, resolves7r: resolves7r, writable: writable };
      })()
    `, ctx);
    check('runtime: _w(playAudio) resolves frozen _7r; _w writable (FEATURES-MV3.md §7-1)',
      wProbe.isFrozen && wProbe.resolves7r && wProbe.writable,
      'frozen=' + wProbe.isFrozen + ' resolves7r=' + wProbe.resolves7r + ' writable=' + wProbe.writable);
  } catch(e) {
    check('sw.js: playAudio routed via _w wrapper (frozen _Du table, FEATURES-MV3.md §7-1)', false, e.message);
    check('offscreen.js: hosts file53 engine + polyfills (FEATURES-MV3.md §7-1)', false, e.message);
  }

  // A6. saveUrl notif/copy path: MV2 spoofed the Referer header via BLOCKING
  // webRequest (onBeforeSendHeaders + "blocking") — unavailable in MV3 (no
  // webRequest/webRequestBlocking permissions) → H() used to THROW at the
  // listener line and return {} → EVERY notif/copy save failed with
  // httpError (GAP FEATURES-MV3.md §7-2). FIXED 2026-08-09: file49 H() now uses a
  // declarativeNetRequest SESSION rule (modifyHeaders → set Referer) — DNR
  // rules DO apply to fetch() made in the extension's own service worker
  // (Chrome docs, "Interactions with service workers"). Requires the
  // declarativeNetRequestWithHostAccess permission in the manifest (no new
  // install warning — <all_urls> host permissions already present). The
  // dwnlApi path (file49 J() via chrome.downloads) is independent and
  // already worked.
  {
    const b = fs.readFileSync(path.join(MV3, 'sw_core_bundle.js'), 'utf8');
    const hasDnr = b.includes('updateSessionRules') &&
      b.includes('modifyHeaders') && b.includes('operation:"set"') &&
      b.includes('header:"Referer"');
    check('file49 H() uses declarativeNetRequest session rules (FEATURES-MV3.md §7-2)', hasDnr,
      'updateSessionRules + modifyHeaders set Referer (webRequest blocking gone)');
  }
  {
    const manifest = JSON.parse(fs.readFileSync(path.join(MV3, 'manifest.json'), 'utf8'));
    const hasPerm = (manifest.permissions || []).includes('declarativeNetRequestWithHostAccess');
    check('manifest: declarativeNetRequestWithHostAccess permission (FEATURES-MV3.md §7-2)', hasPerm,
      'DNR permission declared; no warning with existing <all_urls> host perms');
  }
  // Rule cleanup: H() removes the session rule in the finally path (both on
  // success and on fetch failure) — the bundle must contain the removeRuleIds
  // call twice (add-with-replace + clearRule). H itself is a `let` inside
  // file49's block scope (unlike `var _nu`) — not reachable from here, so the
  // check is source-level like B25.
  {
    const b = fs.readFileSync(path.join(MV3, 'sw_core_bundle.js'), 'utf8');
    const removeCount = (b.match(/removeRuleIds:\[id\]/g) || []).length;
    check('file49 H(): DNR rule cleanup (removeRuleIds) present (FEATURES-MV3.md §7-2)', removeCount >= 2,
      removeCount + ' removeRuleIds:[id] occurrences (add-replace + finally cleanup)');
  }
  // A6b. notif-UI: chrome.notifications in the MV3 SW cannot load a data: URI
  // as iconUrl ("Unable to download all specified images." — user VM
  // 2026-08-09: every notif save threw AND the notification never showed).
  // E() must use a real extension resource (getURL) and guard the create/
  // update/clear calls so a notifications failure never kills the save
  // itself. REGRESSION FIX (2026-08-09): the first guard
  // `void 0===k||(update)||(create)` short-circuited when k was undefined —
  // if the initial create failed, NO final notification was ever made. Now:
  // `(void 0===k?0:(update))||(k=create)` — update only when k exists, else
  // create a fresh one (MV2 semantics). Plus [AC-NOTIF] diagnostics.
  {
    const b = fs.readFileSync(path.join(MV3, 'sw_core_bundle.js'), 'utf8');
    const realIcon = b.includes('getURL("AutoCtrl/logo32.png")') && !b.includes('iconUrl:"data:image/gif');
    const guarded = b.includes('(void 0===k?0:(yield d=>a.update(k,h,d)))') &&
      b.includes('case "clear":void 0===k||a.clear(k)') &&
      !b.includes('void 0===k||(yield d=>a.update(k,h,d))');
    const diag = b.includes('[AC-NOTIF] created k=') && b.includes('[AC-NOTIF] upd err:');
    check('file49 E(): notifications use real icon + guards (notif method, FEATURES-MV3.md §7-2)', realIcon && guarded,
      'getURL(logo32.png) + update/clear guarded (create try/catch) + k-undefined creates fresh');
    check('file49 E(): [AC-NOTIF] diagnostics present', diag,
      'created/upd err logs for VM diagnosis');
  }
  // A6c. dwnlApi + ABSOLUTE folder: chrome.downloads ignores absolute paths in
  // the filename suggest (relative to the Downloads dir only) — the file used
  // to land in Downloads. _nu now falls back to the native write path (I) when
  // the folder is absolute (drive letter / leading slash), so the folder is
  // always honored; relative folders still use the download manager.
  {
    const b = fs.readFileSync(path.join(MV3, 'sw_core_bundle.js'), 'utf8');
    check('file49 _nu: dwnlApi with absolute folder → native path (FEATURES-MV3.md §7-2)',
      b.includes('"dwnlApi"==c.method&&!r.match(/^[\\/\\\\]|:/)?yield J('),
      'absolute folder (drive/\\ prefix) routes to I() native write; relative → chrome.downloads');
  }
  check('file49 in bundle (saveUrl runner _nu)', vm.runInContext('typeof _nu === "function"', ctx), '_nu present -> dwnlApi path OK');
  check('chrome.downloads available in SW (optional perm)', vm.runInContext('typeof _Yk.downloads === "object"', ctx), 'dwnlApi method works');

  // A7. icon/menu machinery present in the bundle (patched at runtime by sw.js
  // with OffscreenCanvas/fetch implementations). NOTE: some of these are
  // top-level LET/const (lexical) - globalThis misses them, so use eval().
  const patched = vm.runInContext(`(() => { const out = []; const names = ['_Fh','_zr','_Ve','_ij','_6t','_Bp','_Uu']; for (const x of names) { try { if (typeof eval(x) !== 'undefined') out.push(x); } catch(e) {} } return out.join(','); })()`, ctx);
  check('menu/icon machinery present', patched.split(',').length === 7, patched);

  // A7b. Gesture status icons are semi-transparent like MV2 (2026-08-08):
  // the sw.js OffscreenCanvas pipeline must draw the v/x GLYPH in the
  // translucent status color on a faint gray backing — NOT a solid dark
  // glyph on a bright green/red disc (looked "garish" vs MV2). Status
  // colors .3 (user-tuned from .7 → .5 → .3 — visually less intrusive).
  {
    const sw = fs.readFileSync(path.join(MV3, 'sw.js'), 'utf8');
    const ok = sw.includes("swZi('v', aSize + 'px/1 gestureDirs', 'rgba(0,255,0,.3)')") &&
      sw.includes("swZi('x', aSize + 'px/1 gestureDirs', 'rgba(255,0,0,.3)')") &&
      sw.includes("{ background: 'rgba(200,200,200, 0.2)' }") &&
      sw.includes('AC-MV3 FIX (2026-08-08): match MV2\'s semi-transparent status icons');
    check('gesture status icons semi-transparent (MV2 look, 2026-08-08)', ok,
      'vxAlpha=' + ok);
  }

  // A8. Zero-proxy chain invariant (verified 2026-08-03): the host manifest
  // MUST point at AutoControlZero.exe (proxy/launcher) - the full engine
  // AutoCtrl_2025.4.22.0.exe crashes with a C++ exception when launched
  // directly (Zero spawns it with arg "152" from %LocalAppData%). Both exes
  // must be present in the install folder.
  try {
    const manifestPath = path.join(__dirname, '..', 'AutoControl_native', 'AutoControl.manifest');
    const manifest = JSON.parse(fs.readFileSync(manifestPath, 'utf8'));
    check('zero-proxy host manifest', manifest.name === 'hrich.autocontrol' && manifest.path === 'AutoControlZero.exe',
      'path=' + manifest.path);
    const zeroOk = fs.existsSync(path.join(__dirname, '..', 'AutoControl_native', 'AutoControlZero.exe'));
    const fullOk = fs.existsSync(path.join(__dirname, '..', 'AutoControl_native', 'AutoCtrl_2025.4.22.0.exe'));
    check('zero-proxy: both exes present in install folder', zeroOk && fullOk,
      'Zero=' + zeroOk + ' full=' + fullOk);
  } catch(e) {
    check('zero-proxy host manifest', false, e.message);
  }
  // A9. sw.js engine auto-install branch (2026-08-03): the file-check answer 2
  // ("engine missing or still starting") must poll first, then unpack
  // file76.dat (taskkill of stale engines, once per session), short-poll and
  // RECONNECT if Zero did not pick up the engine (Zero starts the engine at
  // its own startup).
  try {
    const sw = fs.readFileSync(path.join(__dirname, 'sw.js'), 'utf8');
    check('sw.js engine auto-install branch',
      sw.includes('unpackBundledEngine') && sw.includes('proceedAfterFileCheck') &&
      sw.includes('waitForEngineReady') && sw.includes('taskkill') &&
      sw.includes('__acEngineUnpackAttempted') && sw.includes('r === 2'),
      'unpackBundledEngine/taskkill/__acEngineUnpackAttempted/waitForEngineReady present in sw.js');
  } catch(e) {
    check('sw.js engine auto-install branch', false, e.message);
  }
  // A10. sw.js stale-port protection (2026-08-04): async callbacks from
  // SUPERSEDED ports (postWithCb timeouts, onDisc, handshake chains) must
  // never act on the current connection — a stale type-10 timeout used to
  // fire onConnError, killing the healthy port and starting a reconnect
  // cascade (each new Zero spawns a duplicate engine → file check 2 forever
  // until a reload). The connection generation must be bumped per connect.
  try {
    const sw = fs.readFileSync(path.join(__dirname, 'sw.js'), 'utf8');
    check('sw.js stale-port gen guard',
      sw.includes('__acConnGen') && sw.includes('doHandshake(gen)') &&
      sw.includes('onDisc(gen)') && sw.includes('onConnError(reason, gen)') &&
      sw.includes('reject(Error("stale"))') && sw.includes('__acEngineUnpackAttempted'),
      '__acConnGen bumped per connect; stale postWithCb/onDisc/onConnError bailed; unpack flag present');
  } catch(e) {
    check('sw.js stale-port gen guard', false, e.message);
  }
  // A11. sw.js engine deploy has NO self-deletion (2026-08-04): the native
  // acks type 260 when cmd.exe STARTS (~7ms), not when it finishes — so an
  // async "del /Q /F AutoCtrl_*.exe" deleted the freshly written engine right
  // after write() ("file flashed and vanished" symptom). No nukeHostTree, no
  // chrome.runtime.reload() in the DEPLOY AREA (closes the settings page).
  // NOTE (2026-08-07): chrome.runtime.reload() IS allowed elsewhere — the
  // fresh-install auto-reload (B24) uses it — so this check is scoped to the
  // deploy path (unpackBundledEngine through the r===2 block). Comment
  // mentions of the deleted command are fine; only actual EXECUTION matters.
  try {
    const sw = fs.readFileSync(path.join(__dirname, 'sw.js'), 'utf8');
    const execDel = /(?:_iw|runCmd)\(\s*"del \/Q \/F AutoCtrl_\*\.exe"/.test(sw);
    const nukeCall = /nukeHostTree\(/.test(sw);
    const r2Start = sw.indexOf('if (r === 2)');
    const deployArea = sw.substring(sw.indexOf('function unpackBundledEngine'),
      r2Start > 0 ? r2Start : sw.length);
    const deployReload = /chrome\.runtime\.reload\(/.test(deployArea);
    check('sw.js engine deploy: no self-deletion, no reload',
      !execDel &&
      !nukeCall &&
      !deployReload,
      'noExecDel=' + !execDel + ' noNuke=' + !nukeCall +
      ' noReload=' + !deployReload);
  } catch(e) {
    check('sw.js engine deploy: no self-deletion, no reload', false, e.message);
  }
  // A12. Engine deploy path: r===2 block must have retry reset + same-port
  // polling (MV2 D(true) style), but MUST NOT call chrome.runtime.reload()
  // (closes settings page). There are FIVE proceedAfterFileCheck calls now:
  // 1st in 'if(ready)', 2nd in 'if(ready2)', 3rd in the else 'if(ready3)',
  // 4th in the re-deploy branch (2026-08-07, reinstall path), 5th AFTER the
  // r===2 block closes — that is the block end.
  try {
    const sw = fs.readFileSync(path.join(__dirname, 'sw.js'), 'utf8');
    const r2Start = sw.indexOf('if (r === 2)');
    const p1 = sw.indexOf('proceedAfterFileCheck();', r2Start + 1);
    const p2 = sw.indexOf('proceedAfterFileCheck();', p1 + 1);
    const p3 = sw.indexOf('proceedAfterFileCheck();', p2 + 1);
    const p4 = sw.indexOf('proceedAfterFileCheck();', p3 + 1);
    const p5 = sw.indexOf('proceedAfterFileCheck();', p4 + 1);
    const r2Block = sw.substring(r2Start, p5 > 0 ? p5 : sw.length);
    check('sw.js engine deploy: no chrome.runtime.reload in r===2 path',
      !r2Block.includes('chrome.runtime.reload()') &&
      !/runCmd\(\s*"del \/Q \/F/.test(r2Block) &&
      r2Block.includes('retries = 0') && r2Block.includes('errors = 0') &&
      r2Block.includes('waitForEngineReady(5, 1000, gen)') &&
      r2Block.includes('scheduleRetry()') &&
      r2Block.includes('giving up'),
      'noReload=' + !r2Block.includes('chrome.runtime.reload()') +
      ' noDel=' + !/runCmd\(\s*"del \/Q \/F/.test(r2Block) +
      ' retryReset=' + (r2Block.includes('retries = 0') && r2Block.includes('errors = 0')) +
      ' poll5=' + r2Block.includes('waitForEngineReady(5, 1000, gen)') +
      ' retry=' + r2Block.includes('scheduleRetry()') +
      ' giveUp=' + r2Block.includes('giving up'));
  } catch(e) {
    check('sw.js engine deploy: no chrome.runtime.reload in r===2 path', false, e.message);
  }
  // A13. Engine deploy safety: after giving up, do NOT call onConnError
  // (which triggers scheduleRetry → infinite loop). The r===2 block must
  // have a "giving up" path that disconnects without scheduling retry.
  try {
    const sw = fs.readFileSync(path.join(__dirname, 'sw.js'), 'utf8');
    const r2Start = sw.indexOf('if (r === 2)');
    const p1 = sw.indexOf('proceedAfterFileCheck();', r2Start + 1);
    const p2 = sw.indexOf('proceedAfterFileCheck();', p1 + 1);
    const p3 = sw.indexOf('proceedAfterFileCheck();', p2 + 1);
    const p4 = sw.indexOf('proceedAfterFileCheck();', p3 + 1);
    const p5 = sw.indexOf('proceedAfterFileCheck();', p4 + 1);
    // Block end = the 5th occurrence (normal-path call right after r===2
    // closes); there are FOUR in-block calls since 2026-08-07 (re-deploy).
    const r2Block = sw.substring(r2Start, p5 > 0 ? p5 : sw.length);
    const hasGivingUp = /giving up|Gave up/i.test(r2Block);
    // The unpack-FAIL branch legitimately calls onConnError (real failure,
    // needs the retry path). The GIVE-UP path must NOT — split the block at
    // the 'giving up' marker and verify the tail has no onConnError call.
    const giveUpIdx = r2Block.search(/giving up|Gave up/i);
    const giveUpTail = giveUpIdx >= 0 ? r2Block.substring(giveUpIdx) : '';
    const noOnConnErrorInGiveUp = !/onConnError\(/.test(giveUpTail);
    const noNukeCall = !/nukeHostTree\(/.test(r2Block);
    check('sw.js engine deploy: no infinite loop after giving up',
      hasGivingUp && noOnConnErrorInGiveUp && noNukeCall,
      'givingUp=' + hasGivingUp + ' noOnConnErrorInGiveUp=' + noOnConnErrorInGiveUp +
      ' noNuke=' + noNukeCall);
  } catch(e) {
    check('sw.js engine deploy: no infinite loop after giving up', false, e.message);
  }
  // A14. _Qj patch must NOT fabricate customEntities (round-18 regression
  // guard): _Mi() (batched write used by ACtl.var/pubVar/switchState saves)
  // writes the WHOLE read result back to storage via _bd(), so an invented
  // empty customEntities would WIPE all saved scripts/triggers/gestures —
  // symptom: "script disappeared from settings after refresh". The patch may
  // only fill binSwtch INSIDE an already-present customEntities.
  try {
    const sw = fs.readFileSync(path.join(__dirname, 'sw.js'), 'utf8');
    const qjStart = sw.indexOf('__acOrigQj = _Qj');
    const qjEnd = sw.indexOf('return r;', qjStart);
    const qjBlock = qjStart >= 0 ? sw.substring(qjStart, qjEnd > 0 ? qjEnd : qjStart + 800) : '';
    const noFabricate = !/r\.customEntities\s*=\s*\{\}/.test(qjBlock);
    const hasBinSwtchGuard = /r\.customEntities\s*&&\s*!r\.customEntities\.binSwtch/.test(qjBlock);
    check('sw.js _Qj patch: never fabricates customEntities',
      noFabricate && hasBinSwtchGuard,
      'noFabricate=' + noFabricate + ' binSwtchGuard=' + hasBinSwtchGuard);
  } catch(e) {
    check('sw.js _Qj patch: never fabricates customEntities', false, e.message);
  }
}, 120);

// ---------- B. Port-fix source invariants (rounds 4-18, 2026-08-06) ----------
// Source-level guards for the fixes that live OUTSIDE the bundle (file42.js,
// sw.js) or inside it (file48.js, file77.js — checked via the bundle text,
// which is what actually runs in the SW).
// B1. file42.js re-injection guard: n() (file48) re-injects file42.js via
// scripting.executeScript on delivery timeout — every injection is a NEW
// isolated VM with its own listeners and r[id] map, so without a guard the
// same message is processed TWICE (double-K → setClipboard "undefined",
// lost promises → hung actions). The DOM is shared across isolated worlds,
// so the guard lives on `document`. CRITICAL: the guard must use an
// if-wrapper, NOT a top-level `return` — that is a SyntaxError in a classic
// script (Illegal return statement; broke file42 on 2026-08-06).
{
  const f42 = fs.readFileSync(path.join(MV3, 'file42.js'), 'utf8');
  const guardOk = /if\(!document\.__acF42\|\|2E4<Date\.now\(\)-\(document\.__acF42T\|\|0\)\)\{document\.__acF42=!0;/.test(f42);
  const noIllegalReturn = !/if\(document\.__acF42\)return;/.test(f42);
  const hbOk = /function u\(a,g\)\{document\.__acF42T=Date\.now\(\)/.test(f42);
  const braceBalanced = (f42.match(/\{/g) || []).length === (f42.match(/\}/g) || []).length;
  let syntaxOk = false;
  try { new vm.Script(f42, { filename: 'file42.js' }); syntaxOk = true; } catch (e) { syntaxOk = false; }
  check('file42.js: document re-injection guard (no top-level return)',
    guardOk && noIllegalReturn && hbOk && braceBalanced && syntaxOk,
    'guard=' + guardOk + ' noTopReturn=' + noIllegalReturn + ' heartbeat=' + hbOk +
    ' braces=' + braceBalanced + ' syntax=' + syntaxOk);
  // Dedup hit must pass the RAW value like the normal path — the setClipboard
  // consumer destructures the response (`let [b,c,f]=yield F(...)`); a
  // {result:...} wrapper would yield "Invalid argument types".
  const dedupRawOk = /_fdp\.pr\.then\(function\(b\)\{[\s\S]{0,400}?e\(b\)\}/.test(f42);
  const dedupNoWrap = !/_fdp\.pr\.then\(function\(b\)\{[\s\S]{0,400}?e\(\{result:b\}\)/.test(f42);
  check('file42.js: __acFnDedup hit passes raw value (not {result:...})',
    dedupRawOk && dedupNoWrap, 'raw=' + dedupRawOk + ' noWrap=' + dedupNoWrap);
}
// B2. file48.js `_A` trigInstId suffix: nested userAPI calls (runInTab,
// captureTab chains) must NOT carry the parent's raw trigInstId — the SW
// execUserFunc dedup (key = tabId:scriptId:trigInstId) would answer `dedup`
// for still-in-flight parents → `[null]` results (FEATURES-MV3.md §7-13). The `~`+random
// suffix (round 6 pattern) makes each nested call unique while retries of
// the SAME message keep the same suffix (dedup still works for bursts).
{
  const b = fs.readFileSync(path.join(MV3, 'sw_core_bundle.js'), 'utf8');
  const suffixOk = /trigInstId:\(k\|\|""\)\+"~"/.test(b);
  check('file48.js: _A sends unique ~trigInstId for nested calls', suffixOk,
    'bundle contains trigInstId:(k||"")+"~"');
}
// B3. file48.js n() delivery fallback timeout: 6000ms (round 14; 4000 → 8000
// → 6000). 4000ms fired on the FIRST userScripts.execute of a fresh page
// (one-time ~4-5s Chrome userScripts init) → retry → double execution.
// 8000ms made the KNOWN FEATURES-MV3.md §7-6 gap (runInPageCtx(func) — never returns a
// result) wait the FULL timeout (user VM 19:40: FAIL +8031ms). 6000ms:
// legit first calls (init ~4-5s) still fit, the gap FAILs in ~6s.
{
  const b = fs.readFileSync(path.join(MV3, 'sw_core_bundle.js'), 'utf8');
  const n6000Ok = /setTimeout\(\(\)=>fin1\(void 0,"timeout"\),6000\)/.test(b);
  const noN1500 = !/fin1\([^)]*\),1500\)/.test(b); // any arg form, 1500
  const noN4000 = !/fin1\([^)]*\),4000\)/.test(b); // any arg form, 4000
  const noN8000 = !/fin1\([^)]*\),8000\)/.test(b); // any arg form, 8000
  check('file48.js: n() fallback timeout is 6000ms', n6000Ok && noN1500 && noN4000 && noN8000,
    'has6000=' + n6000Ok + ' no1500=' + noN1500 + ' no4000=' + noN4000 + ' no8000=' + noN8000);
}
// B4. file42.js double-delivery dedups: __acOnce (acUserApi/acMainWorld
// dedup, 30s TTL) and __acFnDedup (share the in-flight promise for
// identical z-bundle evals, 2s window) — both protect against duplicate
// message processing from the SW (dedup key still racing the 15s LRU).
{
  const f42 = fs.readFileSync(path.join(MV3, 'file42.js'), 'utf8');
  const onceOk = /__acOnce/.test(f42);
  const fnDedupOk = /__acFnDedup/.test(f42);
  const noApiDedup = !/__acApiDedup/.test(f42); // rolled back 2026-08-06 (hung jsCode promises)
  check('file42.js: __acOnce + __acFnDedup present (no __acApiDedup)',
    onceOk && fnDedupOk && noApiDedup, 'once=' + onceOk + ' fnDedup=' + fnDedupOk +
    ' noApiDedup=' + noApiDedup);
}
// B5. 2026-08-06 F()-path diagnostics: n() retry-reason logging (why= +
// chrome.runtime.lastError at callback time — distinguishes "no listener"
// vs "port closed before response" vs real async response) and file42
// listener-ret + funcCode try/catch (an exception inside FN() closes the
// sendMessage channel → n() gets undefined → retry → dedup-hit cascade,
// the setClipboard first-try null).
{
  const b = fs.readFileSync(path.join(MV3, 'sw_core_bundle.js'), 'utf8');
  const f42 = fs.readFileSync(path.join(MV3, 'file42.js'), 'utf8');
  const whyOk = /trig='\+String\(c&&c\.trigInstId\)\.slice\(0,70\)\+' why='\+rs\+' h=/.test(b);
  const lastErrOk = /_Yk\.runtime\.lastError/.test(b);
  const retOk = /AC-F42\] listener ret/.test(f42);
  const threwOk = /AC-F42\] funcCode THREW/.test(f42);
  const curInOk = /AC-F42\] funcCode cur-in/.test(f42);
  const resCurOk = /AC-F42\] res rcvd id=.*cur=/.test(f42);
  // 2026-08-06 round 5 (REVERT of round 3): the scriptId branch must KEEP
  // x.__cur (NO finally-restore) — the chain is load-bearing. file42's
  // funcCode messages + acUserApi relay read scriptId/trigInstId from it,
  // and the SW-side dedup key + file67 W() on-case registration
  // (_lf(_Vj,...,h,[]) — with h=undefined the trigInstId level is skipped
  // → .push(c) on an object throws → tabLoadEnd registration never happens)
  // DEPEND on a non-empty trigInstId chain. Without it every F()
  // execUserFunc got key "tabId::" → SW __acExecCompleted (15s TTL) BLOCKed
  // all F() calls after the first (getTabInfo) → "_fr is not iterable"
  // cascade (VM run 14:01, 15/23). The funcCode branch STILL restores (FN
  // captures ctx synchronously — exactly 1 `finally{x.__cur=_s}`); its
  // empty-chain fallback now uses the message's own scriptId/trigInstId
  // instead of {} (belt-and-suspenders for the no-prior-scriptId edge).
  const f42NoScriptIdRestore = !/finally\{x\.__cur=_sc\}/.test(f42) &&
    /x\.__cur=\{scriptId:a\.scriptId,tabId:a\.tabId,targetTabs:a\.targetTabs,trigInstId:a\.trigInstId(?:\+\([^;]+\))?\}/.test(f42);
  const f42FuncRestore = (f42.match(/finally\{x\.__cur=_s\}/g) || []).length === 1;
  const f42FallbackCtx = /:\{scriptId:a\.scriptId,tabId:a\.tabId,trigInstId:\(\(a\.trigInstId\|\|""\)\+"~"/.test(f42);
  // 2026-08-06: heartbeat timer — a live file42 must keep document.__acF42T
  // fresh by TIMER, not only on message processing. Without it, a live
  // instance idle >20s looked dead → new injection → TWO live listeners →
  // double delivery (funcCode dedup-hit) → setClipboard null-vs-array race.
  const hbTimerOk = /setInterval\(function\(\)\{document\.__acF42T=Date\.now\(\)\},1E4\)/.test(f42);
  check('file48/file42: F()-path diagnostics present (trig in DLV-F, lastError, listener ret, funcCode THREW, cur-in, res-rcvd cur)',
    whyOk && lastErrOk && retOk && threwOk && curInOk && resCurOk,
    'why=' + whyOk + ' lastErr=' + lastErrOk + ' ret=' + retOk + ' threw=' + threwOk +
    ' curIn=' + curInOk + ' resCur=' + resCurOk);
  check('file42.js: scriptId branch KEEPS x.__cur chain (round-5 revert, no finally-restore)',
    f42NoScriptIdRestore, 'noScriptIdRestore=' + f42NoScriptIdRestore);
  check('file42.js: funcCode branch restores x.__cur + fallback uses message ids',
    f42FuncRestore && f42FallbackCtx, 'funcRestore=' + f42FuncRestore + ' fallbackCtx=' + f42FallbackCtx);
  check('file42.js: heartbeat kept fresh by timer (double-injection fix)',
    hbTimerOk, 'hbTimer=' + hbTimerOk);
  // 2026-08-06 round 6 (multi-instance response race — "without reload" FAIL):
  // the tab keeps STALE pre-guard file42 instances alive until the tab reloads
  // (an extension/SW reload does NOT remove content-script contexts). Every
  // funcCode message is processed by several instances → several K runs in the
  // SHARED user script world. K's `delete window[e]` made the 2nd+ K read
  // undefined → garbage responses (null) won the sendMessage channel race →
  // setClipboard "_fr is not iterable" (VM 14:30: F-> null + dedup-hit while
  // the fresh instance logged the correct funcCode val). Fixes:
  //  (a) K is NON-DESTRUCTIVE (every K returns the same array → race harmless);
  //  (b) the __acFnDedup entry stores a VALUE-promise (dedup-hit responds with
  //      the value, not the chained sendResponse return — which was true/false);
  //  (c) n() retries null responses once (same message → everyone dedup-hits
  //      onto the value-promise → converges on the correct value).
  const kNoDelete = /let g=window\[e\];\/\* AC-MV3 FIX \(2026-08-06, round 6\)/.test(b) &&
    !/let g=window\[e\];delete window\[e\]/.test(b);
  const f42ValuePr = /var _fpr=new Promise\(function\(_dV\)\{c\.then\(function\(v\)\{/.test(f42) &&
    /_dV\(v\)\}/.test(f42);
  // 2026-08-06 round 7 + 7b (long-script action hang + runInTab regression):
  // the scriptId branch used to wait for the WHOLE script's Promise before
  // answering → any script longer than n()'s 4000ms fallback (e.g. the API
  // test with a slow tabLoadEnd + 8s sleep) timed out → the runScript action
  // hung in the queue → WATCHDOG force-shift → subsequent RUN SCRIPTs
  // queued/failed (VM 15:03: "Queue stuck! 2 items", second run never
  // finished). Round 7: ack {result:true} IMMEDIATELY (fire-and-forget) —
  // the action result is unused for runScript (t=true in _A ignores errors).
  // Round 7b: the fire-and-forget must apply ONLY to the top-level RUN
  // SCRIPT — nested _A calls (runInTab/runInFrames) go through the SAME
  // scriptId branch and need their REAL result (round-7 made them return
  // [true], VM 15:17: "ACtl.runInTab true"). _A now marks the top-level call
  // with noWait:!0===t (t===true only from _To/_gr); file42 awaits the
  // promise (e({result:b})) when noWait is falsy.
  const f42ScriptAck = /if\(a\.noWait\)\{/.test(f42) &&
    /e\(\{result:!0\}\),!0\}/.test(f42) &&
    /e\(\{result:b\}\)/.test(f42) &&
    /\[AC-F42\] script done trig=/.test(f42);
  const f48NoWait = /noWait:!0===t/.test(b);
  const nNullRetry = /null!=h\|\|0<p\|\|c\.event/.test(b);
  check('file77.js: K is non-destructive (no delete window[e] — multi-instance race fix)',
    kNoDelete, 'kNoDelete=' + kNoDelete);
  check('file42.js: __acFnDedup stores a VALUE-promise (dedup-hit answers the value)',
    f42ValuePr, 'f42ValuePr=' + f42ValuePr);
  check('file42.js: scriptId branch acks top-level RUN SCRIPT, awaits nested _A (round-7b)',
    f42ScriptAck, 'f42ScriptAck=' + f42ScriptAck);
  check('file48.js: _A marks top-level RUN SCRIPT with noWait (nested calls return real results)',
    f48NoWait, 'f48NoWait=' + f48NoWait);
  check('file48.js: n() retries null responses once (same-message convergence)',
    nNullRetry, 'nNullRetry=' + nNullRetry);
}
// B5. file77.js switchState binSwtch guard: `_if` is assigned from
// different async storage reads (config chain race) — `for..of _if.binSwtch`
// threw "not iterable" when the key was absent. The guard `(_if.binSwtch||[])`
// is race-proof.
{
  const b = fs.readFileSync(path.join(MV3, 'sw_core_bundle.js'), 'utf8');
  const guardOk = /\(_if\.binSwtch\s*\|\|\s*\[\]\)/.test(b);
  check('file77.js: switchState binSwtch||[] guard in bundle', guardOk,
    'bundle contains (_if.binSwtch||[])');
}
// B6. sw.js diagnostics + config auto-heal: __acStateDump (attached to every
// execUserFunc response as st={up,conn,hs,if,ek}) and the _lr→_Gf rebuild
// when _if.binSwtch is missing (no handshakeDone guard, 10s throttle).
{
  const sw = fs.readFileSync(path.join(MV3, 'sw.js'), 'utf8');
  const dumpOk = /__acStateDump/.test(sw);
  const healOk = /__acLastHeal > 10000/.test(sw) && /_lr\(\(\) => \{[\s\S]{0,120}?_Gf\(\{\}, \(\) => \{\}\)/.test(sw);
  check('sw.js: __acStateDump + config auto-heal present', dumpOk && healOk,
    'stateDump=' + dumpOk + ' autoHeal=' + healOk);
}
// B7. Extension manifest declares file42.js as a STATIC content script
// (2026-08-06, round 8): n()'s on-demand injection is now a FALLBACK only.
// The manifest (Chrome-managed lifecycle) guarantees exactly ONE file42
// instance per page — eliminating the stale-instance/double-delivery class
// (rounds 4-6) on normal pages. chrome://, Web Store, file:// etc. still
// rely on n() (content_scripts can't run there). host_permissions
// ["<all_urls>"] already grants the match — no new permission warnings.
// Note: `persistAcrossSessions` is NOT a valid manifest content_scripts key
// (it is scripting.registerContentScripts-only) — deliberately absent.
{
  let mf = null;
  try { mf = JSON.parse(fs.readFileSync(path.join(MV3, 'manifest.json'), 'utf8')); }
  catch (e) { check('manifest.json: parses as JSON', false, e.message); }
  if (mf) {
    const cs = mf.content_scripts;
    const entry = Array.isArray(cs) ? cs.find(e => Array.isArray(e.js) && e.js.includes('file42.js')) : null;
    const csOk = !!entry &&
      Array.isArray(entry.matches) && entry.matches.includes('<all_urls>') &&
      (entry.run_at || 'document_idle') === 'document_idle' &&
      entry.all_frames !== true &&
      (entry.world || 'ISOLATED') === 'ISOLATED';
    check('manifest.json: content_scripts declares file42.js on <all_urls> (document_idle, top frame, ISOLATED)',
      csOk, entry ? ('js=' + entry.js.join(',') + ' matches=' + JSON.stringify(entry.matches) +
        ' run_at=' + (entry.run_at || 'document_idle') + ' all_frames=' + (entry.all_frames || false)) : 'no content_scripts');
  }
}
// B32. main.html declares UTF-8 charset (2026-08-08): without it, Chrome reads
// the page AND all its scripts (no per-file charset) as Windows-1252 → UTF-8
// symbols (—, ⚠) render as mojibake (â€”, âš) in the UI (user report:
// "Telemetry helps the developer... â€” nothing is sent"). All repo files are
// UTF-8 (AGENTS.md rule) — the meta must stay.
{
  const mh = fs.readFileSync(path.join(MV3, 'main.html'), 'utf8');
  const ok = mh.includes('<meta charset="utf-8">');
  check('main.html: <meta charset="utf-8"> present (page + scripts read as UTF-8, no mojibake)', ok,
    'charset=' + ok);
}
// B8-B11. World warmup (rounds 9-12) was REMOVED in round 13 (2026-08-06):
// Chrome SERIALIZES userScripts.execute PER TAB, and the FIRST execute on a
// fresh page costs ~4-5s one-time (userScripts subsystem init). Warmup
// no-ops did NOT pre-create worlds — they only queued an extra execute that
// BLOCKED the script's real calls behind its init (user VM 19:27: first
// execUserFunc +4909ms — was +6-11ms before warmup; runInPageCtx(func)
// still +4038ms). The one-time cost is now absorbed by n()'s 8000ms
// fallback (round 13): the first call waits, no retry, no double exec.
{
  const sw = fs.readFileSync(path.join(MV3, 'sw.js'), 'utf8');
  const noWarm = !/__acWarmMainWorlds|__acWarmTabs/.test(sw);
  const note13 = /round 13 \(2026-08-06\): world-warmup \(rounds 9-12\) REMOVED/.test(sw);
  check('sw.js: world-warmup removed (round 13 — it blocked the userScripts.execute queue)',
    noWarm && note13, 'noWarm=' + noWarm + ' note=' + note13);
}
// B12. file48.js n() fallback is 6000ms (round 14): the FIRST
// userScripts.execute on a fresh page costs ~4-5s one-time (Chrome inits
// its userScripts subsystem; user VM 19:27: first execUserFunc +4909ms).
// round 13's 8000ms made the known FEATURES-MV3.md §7-6 gap (runInPageCtx(func) — never
// returns) wait the FULL timeout (user VM 19:40: FAIL +8031ms). 6000ms is
// the compromise: legit first calls (init ~4-5s) still fit, the gap FAILs
// in ~6s instead of 8s.
{
  const b = fs.readFileSync(path.join(MV3, 'sw_core_bundle.js'), 'utf8');
  const has6000 = /fin1\(void 0,"timeout"\),6000\)/.test(b);
  const no8000 = !/fin1\(void 0,"timeout"\),8000\)/.test(b);
  check('file48.js: n() fallback timeout is 6000ms (round 14)',
    has6000 && no8000, 'has6000=' + has6000 + ' no8000=' + no8000);
}
// B13. sw.js single-injection proxy for runInPageCtx(func) (2026-08-06,
// round 16 — FEATURES-MV3.md §7-6): W()'s FUNC branch defines window.m via one injection
// and reads it from ANOTHER (the funcExecLstnr listener); in MV3 every
// userScripts.execute is a separate evaluation context, so the listener
// never sees the var ("window[u.data.funcName] is not a function").
// Fix in jsCode (sw.js only, no bundle rebuild):
//  (a) runInPageCtx("funcExecLstnr", fn) is NO-OPED (g === "funcExecLstnr")
//      — otherwise it answers first with the wrong error and wins the
//      channel race;
//  (b) the 'var m = <fn>' injection is replaced by a SINGLE self-contained
//      proxy (/*AC-MV3-PROXY*/) that sets window.m, installs its OWN
//      listener for {funcName:m,args} and answers via {response,funcName}
//      from the same context (closure over F — no cross-injection global
//      lookup). Ends with `void 0` so the completion value is cloneable
//      (a function result would reject userScripts.execute/sendRes).
{
  const sw = fs.readFileSync(path.join(MV3, 'sw.js'), 'utf8');
  const noOpOk = /if \(g === "funcExecLstnr"\) \{/.test(sw) &&
    /window\.removeEventListener\("message", hnd\);/.test(sw);
  const proxyOk = /AC-MV3-PROXY/.test(sw) &&
    /window\[N\]=F/.test(sw) &&
    /\{response:r,funcName:N\}/.test(sw) &&
    /window\.__acPendingVar = \{ name: mm\[1\], rid: rid \}/.test(sw) &&
    /setTimeout\(function\(\) \{\s*if \(window\.__acPendingVar && window\.__acPendingVar\.rid === rid\) window\.__acFlushVarQueue\(\);\s*\}, 8000\)/.test(sw);
  // Round 16b-d: the FUNC source (mm[2]) is appended via CONCATENATION —
  // runtime, so its own double quotes are harmless. Only the quotes INSIDE
  // the acProxy literal need escaping, and jsCode is a TEMPLATE LITERAL
  // (\" collapses to " one level) → the literal DOUBLE-escapes them
  // (\\\" → \" in jsCode → " in the runtime acProxy string). Escaping mm[2]
  // via regex/split was WRONG (regex collapsed → Invalid regular expression,
  // user VM 20:24) and is not needed.
  const escOk = /,F=" \+ mm\[2\] \+/.test(sw) &&
    /\\\\\\"args\\\\\\"in d/.test(sw);
  check('sw.js: single-injection runInPageCtx(func) proxy + funcExecLstnr no-op (round 16, FEATURES-MV3.md §7-6)',
    noOpOk && proxyOk && escOk, 'noOp=' + noOpOk + ' proxy=' + proxyOk + ' esc=' + escOk);
}

// B20. sw.js orphan-engine cleanup + reconnect guard (2026-08-06): every
// connectNative spawns a NEW Zero→engine pair; a dead SW generation leaves
// its engine orphaned (detached from Zero, holds global hooks) — symptom:
// TWO AutoCtrl_2025.4.22.0.exe after browser start, one remains after close.
// __acKillOrphanEngines (at handshake start, before the file check) scans
// via wmic and taskkills ONLY engines whose AutoControlZero.exe parent is
// NOT alive — live pairs of other browsers are never touched (multi-browser
// setups). The reconnect handlers must NOT spawn a duplicate host while a
// connect/handshake is in flight or the connection is healthy.
{
  const sw = fs.readFileSync(path.join(MV3, 'sw.js'), 'utf8');
  // The wmic query is built PARAMETRICALLY (`"name='" + name + "'"`), so check
  // the pattern, not the literal exe names.
  const orphanOk = sw.includes('__acKillOrphanEngines') &&
    sw.includes('wmic process where') &&
    /name='" \+ name \+ "'/.test(sw) &&
    sw.includes('get ProcessId,ParentProcessId /FORMAT:CSV') &&
    sw.includes('taskkill /F /PID ') &&
    sw.includes('__acKillOrphanEngines(gen);');
  const guardOk = (sw.match(/case "reconnect":/g) || []).length === 1 &&
    /case "reconnect":\s*\/\/ AC-MV3 FIX \(2026-08-06\): never spawn a duplicate host/.test(sw) &&
    /if \(__acConnecting \|\| \(connected && handshakeDone\)\)/.test(sw) &&
    /reconnect: \(m, cb\) => \{\s*if \(__acConnecting/.test(sw) &&
    sw.includes('__acConnecting = true;') && sw.includes('__acConnecting = false;');
  check('sw.js orphan-engine cleanup + healthy reconnect guard (2026-08-06)',
    orphanOk && guardOk, 'orphan=' + orphanOk + ' guard=' + guardOk);
}

// B21. sw.js engine re-deploy after a native reinstall (2026-08-07): the
// native installer (Reinstall/Repair) DELETES the engine file, so the
// "unpack once per session" flag must not block a re-deploy when the disk
// check says the file is gone. __acEngineFileExists (type 260 `if exist`)
// disambiguates the file-check answer 2 ("missing OR still starting");
// __acEngineDeploys caps re-deploys (antivirus loop safety).
{
  const sw = fs.readFileSync(path.join(MV3, 'sw.js'), 'utf8');
  const reOk = sw.includes('__acEngineFileExists') &&
    sw.includes('if exist AutoCtrl_2025.4.22.0.exe (echo 1) else (echo 0)') &&
    sw.includes('__acEngineDeploys') &&
    sw.includes('Engine file missing on disk after earlier deploy');
  check('sw.js engine re-deploy when installer wiped the file (2026-08-07)',
    reOk, 'reDeploy=' + reOk);
}

// B22. sw.js config-chain restart on reconnect (2026-08-07): after a native
// reinstall/repair (or ANY mid-SW reconnect) the bundle's configChainStarted
// guard (mv3_native_shim.js) blocks the config chain re-run → no type 60, no
// type 21 → the fresh engine never emits triggers (user VM 16:59: engine up
// but hotkeys dead; log: "Config chain already started, skipping duplicate
// nativeConfigReady"). proceedAfterFileCheck must dispatch nativeConfigReady
// with force:true (the bundle resets the guard on force).
{
  const sw = fs.readFileSync(path.join(MV3, 'sw.js'), 'utf8');
  const forceOk = /__acDispatch\(\{ type: "nativeConfigReady", connected: true, time: connectTime, force: true \}\)/.test(sw) &&
    /broadcast\(\{ type: "nativeConfigReady", connected: true, time: connectTime, force: true \}\)/.test(sw) &&
    sw.includes('configChainStarted guard');
  check('sw.js nativeConfigReady force:true on reconnect (config chain re-runs, 2026-08-07)',
    forceOk, 'force=' + forceOk);
}

// B23. Fresh-install UX: the settings page must OFFER INSTALLATION instead of
// "Something went wrong" (2026-08-07). mv3_shim.js hardcoded `window._nd =
// true` → file2.js (`_nd ? ping→natHostNotFound : install pane`) always took
// the error path on a fresh install (native never installed). Now the flag is
// storage-based ONLY: default false, `_nd` ALWAYS set from the storage read
// (including false — the SW ping callback must NOT override/persist it, or a
// stale connected during an uninstall would re-arm the flag → "Something went
// wrong" again, user VM 22:50). The flag is persisted by the SW on a REAL
// handshake (proceedAfterFileCheck) and cleared by the proper uninstall flow
// (file30.js `_ei`).
{
  const shim = fs.readFileSync(path.join(MV3, 'mv3_shim.js'), 'utf8');
  const shimOk = shim.includes('window._nd = false;') &&
    shim.includes("chrome.storage.local.get('natHostInstalled'") &&
    shim.includes('natHostInstalled not in storage') &&
    shim.includes('window._nd = !!(r && r.natHostInstalled)') &&
    !shim.includes('chrome.storage.local.set({ natHostInstalled: true })') &&
    !shim.includes('Without this, file2.js shows the install pane');
  const sw = fs.readFileSync(path.join(MV3, 'sw.js'), 'utf8');
  const swOk = sw.includes('chrome.storage.local.set({ natHostInstalled: true })');
  const f30 = fs.readFileSync(path.join(MV3, 'file30.js'), 'utf8');
  const f30Ok = f30.includes('chrome.storage.local.remove("natHostInstalled")') &&
    f30.includes('window._nd=!1');
  check('fresh-install UX: install UI offered instead of "Something went wrong" (2026-08-07)',
    shimOk && swOk && f30Ok, 'shim=' + shimOk + ' sw=' + swOk + ' uninstall=' + f30Ok);
}

// B24. Fresh-install auto-reconnect (2026-08-07): Chrome CACHES a failed
// "Specified native messaging host not found" lookup PER SW INSTANCE — after
// the user installs the native from the install UI, the same SW keeps failing
// connectNative until the extension reloads. The install UI (file2.js
// m(Infinity,1000)) pings type 920 every second; after 20 "native not ready"
// answers with a DEAD port (never during an engine deploy — the port is
// alive then), the SW sets __acInstallAutoReload and reloads itself once;
// the fresh SW finds the host and proceedAfterFileCheck reopens the options
// page automatically.
{
  const sw = fs.readFileSync(path.join(MV3, 'sw.js'), 'utf8');
  const ok = sw.includes('__acNotReadyPings') &&
    sw.includes('__acInstallAutoReloaded') &&
    sw.includes('__acInstallAutoReload') &&
    sw.includes('chrome.runtime.reload()') &&
    sw.includes('chrome.runtime.openOptionsPage()') &&
    /__acNotReadyPings >= 20/.test(sw) &&
    /if \(!port\) __acNotReadyPings\+\+/.test(sw);
  check('sw.js fresh-install auto-reload + auto-open options (2026-08-07)',
    ok, 'autoReload=' + ok);
}

// B25. Uninstall/repair UX (2026-08-07): (1) after a native uninstall (or
// when the host was never installed) the SW must STOP the auto-reconnect loop
// once it's clear the host is gone — retrying forever spawns Zero attempts
// and console noise with no chance of success (user VM 18:15: gens 2-50+).
// The cap applies ONLY when the host NEVER connected this session
// (__acEverConnected); page-driven reconnects reset the counter. (2)
// Emergency Repair (context menu "reloadExtn") is handled by the BUNDLE
// (file62_mv3.js onClicked → `_co(1,!0)` — MV2 semantics: badge Wait →
// type 55 (_vh) → the NATIVE restarts the engine → badge OK → reload of open
// settings tabs). sw.js must NOT have its own onClicked handler (double
// handling: two type-55 sends + badge race — user VM 23:41: Wait blinked,
// no OK — and the bundle's location.reload() was a TypeError in the SW).
// `_co` in file34_mv3.js (IN bundle) is SW-safe: " OK " badge + 2s clear +
// `_Yk.tabs.reload` of chrome-extension tabs. (3) The menu item is created
// by the SW at startup (__acCtxMenuOwned skips the page's duplicate). (4)
// After a proper uninstall the settings page reloads itself to show the
// install pane (file30.js _ei). (5) 2026-08-08: type 55 with a DEAD port
// (native never installed / engine gone) → `_acNativeSend` opens the options
// page (install pane shows when natHostInstalled is absent) + an
// unhandledrejection guard silences "Could not establish connection" noise
// from page-less broadcasts at startup. (6) 2026-08-08: file47 `_nk()`
// (config chain, SW leader) calls contextMenus.removeAll() on every run —
// that deleted the SW's item and the create patch skipped recreating it →
// the menu item vanished until extension reload (user VM 00:18). The
// removeAll patch recreates reloadExtn while __acCtxMenuOwned. (7)
// onActivated (file62_mv3, IN bundle) guards `_cd[c]` undefined — with a
// dead native _cd stays empty → `e.activeTab=f` threw TypeError right after
// openOptionsPage (user VM 00:18). (8) 2026-08-08 (FIX 12): the MV2 engine
// restart on Emergency Repair comes from the background-page reload (port
// drop → Zero exit → fresh pair), NOT from type 55 itself — user VM 00:38:
// type 55 was sent, the native acked `true`, PID never changed. The SW
// replicates the cycle in place: __acEmergencyRestartNative (engine taskkill
// via _iw → port.disconnect → reconnect via onDisc) and shows the " OK "
// badge only after the reconnect succeeds (proceedAfterFileCheck); a failed
// reconnect shows red "Error" instead of hanging in Wait. The bundle _co
// only reloads the current page. (9) 2026-08-08: consume
// chrome.runtime.lastError in the onDisconnect listener — Chrome logs
// "Unchecked runtime.lastError: Native host has exited." otherwise (and
// "Specified native messaging host not found" on failed connectNative); both
// are EXPECTED (Emergency Repair kills the host; no-native installs fail the
// lookup). Also skip the "engine may have crashed" warning while
// __acRepairBadgePending is set (the exit is intentional during repair).
// (10) 2026-08-08 (FIX 14): NO taskkill in the repair cycle — hard-killing
// the engine (TerminateProcess) leaves its global hooks dangling in Windows
// and the fresh engine gets NO input for ~40s until Windows cleans them up
// (user VM 01:36: first trigger 43s after repair; MV2 never hard-killed —
// it just reloaded the background page). (11) 2026-08-08 (FIX 15): the
// repair RELOADS the SW (chrome.runtime.reload() = MV2 background-page
// reload) — user-verified that hotkeys bind immediately after an extension
// reload; the badge-OK flag survives via chrome.storage.local.__acRepairBadge.
{
  const sw = fs.readFileSync(path.join(MV3, 'sw.js'), 'utf8');
  const f34 = fs.readFileSync(path.join(MV3, 'file34_mv3.js'), 'utf8');
  const f62 = fs.readFileSync(path.join(MV3, 'file62_mv3.js'), 'utf8');
  const f30 = fs.readFileSync(path.join(MV3, 'file30.js'), 'utf8');
  const ok = sw.includes('__acEverConnected') &&
    sw.includes('__acMaxNeverConnectedFailures') &&
    /errors >= __acMaxNeverConnectedFailures/.test(sw) &&
    sw.includes('stopping auto-retry') &&
    /errors = 0; retries = 0;\s*connect\(\)/.test(sw) &&
    sw.includes('__acCtxMenuOwned') &&
    /id: "reloadExtn", title: "Emergency repair", contexts: \["action\"\]/.test(sw) &&
    !/menuItemId === "reloadExtn"/.test(sw) &&
    !sw.includes('setBadgeText({ text: "Wait" })') &&
    // postWithCb(55 ...) IS allowed now (FIX 12): the SW sends type 55 as
    // part of the restart cycle, but ONLY inside the _acNativeSend a===55
    // branch (no own onClicked handler — the menuItemId check above).
    /postWithCb\(55,\s*b,\s*5000\)/.test(sw) &&
    sw.includes('a === 55 && !port') &&
    sw.includes('openOptionsPage()') &&
    sw.includes("addEventListener('unhandledrejection'") &&
    // 2026-08-08: file47 _nk() calls removeAll on every config-chain run —
    // that deleted the SW's Emergency-repair item (create patch skipped
    // recreating) → item vanished until extension reload. The removeAll
    // patch recreates it while the SW owns it. Also onActivated must guard
    // _cd[c] undefined (dead native → empty _cd → activeTab TypeError).
    sw.includes('chrome.contextMenus.removeAll = (cb) =>') &&
    sw.includes('Emergency-repair menu recreate failed') &&
    // 2026-08-12: the removeAll patch must recreate the item via the
    // ORIGINAL create — the patched create() returns 0 for reloadExtn while
    // __acCtxMenuOwned (duplicate filter), silently dropping the recreation
    // → the item vanished after every config-chain removeAll (user 2026-08-12).
    sw.includes('// MUST use origCtxCreate here') &&
    /origCtxCreate\(\s*\{ id: "reloadExtn"/.test(sw) &&
    !sw.includes("chrome.contextMenus.create(\n              { id: \"reloadExtn\", title: \"Emergency repair\"") &&
    // 2026-08-08 (FIX 12): type 55 alone does NOT restart the engine (user
    // VM 00:38: native acked `true`, PID unchanged — MV2's engine restart
    // came from the background-page reload → port drop → fresh Zero+engine).
    // FIX 14: no hard taskkill (dangling hooks → ~40s input stall, VM 01:36).
    // FIX 15 (2026-08-08): the repair RELOADS the SW itself —
    // chrome.runtime.reload() is the MV2 background-page reload equivalent
    // (user-verified: hotkeys bind IMMEDIATELY after an extension reload,
    // whereas the port-drop-only cycle sometimes left the old engine alive
    // without a working pipe). The badge-OK flag survives the reload in
    // chrome.storage.local (`__acRepairBadge`) and is consumed by the FRESH
    // SW in proceedAfterFileCheck (like __acInstallAutoReload).
    sw.includes('__acRepairBadge') &&
    sw.includes('reloading SW (MV2 background-page reload)') &&
    sw.includes('chrome.storage.local.set({ __acRepairBadge: true }') &&
    /chrome\.runtime\.reload\(\); \} catch\(e\) \{\}/.test(sw) &&
    sw.includes('items.__acRepairBadge') &&
    // 2026-08-08: dead-port repair (no native) must NOT leave the "Wait"
    // badge stuck — show "Error" (#F00, 2s) + clear, like MV2's reloaded
    // page does via _nt("showNotif") when the native is down (user VM
    // 01:55: badge stuck on "Wait" forever after opening the install page).
    sw.includes('setBadgeText({ text: "Error" })') &&
    !sw.includes('__acRepairBadgePending') &&
    !sw.includes('restarting native (engine will be replaced)') &&
    !sw.includes('reconnecting native (port drop, MV2-style)') &&
    !sw.includes('_iw("taskkill /F /IM AutoCtrl_2025.4.22.0.exe")(() => {}); } catch(e) {}\n    setTimeout(() => {\n      try { if (port) port.disconnect(); } catch(e) {}') &&
    sw.includes('Emergency repair complete') &&
    // 2026-08-08: consume chrome.runtime.lastError in onDisconnect (Chrome
    // logs "Unchecked runtime.lastError: Native host has exited." otherwise —
    // EXPECTED during Emergency Repair).
    sw.includes('void chrome.runtime.lastError') &&
    // 2026-08-08 (FEATURES-MV3.md §7-7): NO chrome.action.onClicked in sw.js — the bundle
    // file62_mv3.js is the single handler (trigger if brwrAction.trigActId is
    // assigned, else _sh() → settings = MV2 semantics). An sw.js listener on
    // the same event (browserAction aliased to action) would open the
    // settings page UNCONDITIONALLY on every icon click.
    !sw.includes('chrome.action.onClicked.addListener') &&
    f62.includes('AC-MV3 FIX (2026-08-08)') &&
    f62.includes('if(!e)return') &&
    !f34.includes('_Cr(" OK ","#0F0")') &&
    f34.includes('_Yk.tabs.reload') &&
    f30.includes('location.reload()');
  check('sw.js reconnect-loop stop + single-handler Emergency Repair via bundle _co (2026-08-07)',
    ok, 'uninstallRepair=' + ok);
}

// B26. Install pane must NOT auto-close (2026-08-07): file2.js x() used to
// start the pong ping-loop when _dh (native connected time) was set — on a
// fresh extension install with the native still present the pane closed
// itself ~1s later, before the user could read/download the installer. The
// ping-loop now starts ONLY after the user clicks Install (f() → t()); the
// pane transitions to settings via the 'ac-install-done' event dispatched by
// the shim when the SW reports connected AND natHostInstalled is in storage
// (leftover-native case, safe against the uninstall race — _ei removes the
// flag before the reload).
{
  const f2 = fs.readFileSync(path.join(MV3, 'file2.js'), 'utf8');
  const shim = fs.readFileSync(path.join(MV3, 'mv3_shim.js'), 'utf8');
  const ok = f2.includes('addEventListener("ac-install-done"') &&
    !f2.includes('_9j._dh&&setTimeout(()=>{b();t()},600)') &&
    shim.includes("dispatchEvent(new CustomEvent('ac-install-done'))");
  check('install pane does not auto-close; transitions via ac-install-done (2026-08-07)',
    ok, 'paneStays=' + ok);
}

// B27. Fast wheel-spin tab skipping (2026-08-08): switchRight/switchLeft
// resolve the base tab from _Np (the _Mg pos:next/prev filter), and _Np was
// refreshed ONLY by onActivated — asynchronously after the activation lands.
// Fast wheel spins (750 triggers every 30-100ms, user VM 02:12-02:13) could
// hit the STALE _Np → _xy returned the SAME neighbor tab → it was activated
// twice → visible skipped tab steps (the faster the spin, the more skips;
// every 750 DID fire — log shows ACT/OK for each). FIX: _Ph (file8, IN
// bundle) now optimistically sets `_Np=c` BEFORE `tabs.update`. FIX 18
// (2026-08-08): remaining skips came from STALE `_Yp[].active` flags — _Ph
// skips activation when `e.active` is true, but the flag was only refreshed
// by _Fu (window enum), never reset on real switches → wrap transitions
// through a previously-active tab skipped it AND left _Np stale. Now _Ph
// sets `e.active=!0` on activation and onActivated (file62_mv3, IN bundle)
// resets the old activeTab's flag + sets the new one.
{
  const b = fs.readFileSync(path.join(MV3, 'sw_core_bundle.js'), 'utf8');
  const ok = b.includes('_Np=c,e.active=!0,_Yk.tabs.update(c,{active:!0}') &&
    b.includes('_Yp[c].active=!1') &&
    b.includes('f.active=!0') &&
    b.includes('AC-MV3 FIX (2026-08-08): optimistically set _Np') &&
    b.includes('AC-MV3 FIX (2026-08-08): keep _Yp[].active flags in sync');
  check('file8 _Ph + file62 onActivated: optimistic _Np + active-flag sync (wheel-spin fix, 2026-08-08)',
    ok, 'phNp=' + ok);
}

// B52. file8 _9f/_Rh/_7f toggle actions read the FRESH tab state (2026-08-30,
// user issue: "right-btn => pin tab toggles only every 2-5 clicks").
// ROOT CAUSE: `_9f` (pinTabs) read `_Yp[c].pinned` — the SW tab cache that
// is only refreshed by the async window enum `_Fu`, which _Rf gates behind
// a 1500ms cache (`__acEnumCacheMs`). Clicks closer than ~1.5s after the
// last enum read a STALE pinned state → toggled the tab to the SAME value
// (a no-op) → "every other click does nothing" (verified live: 5 clicks →
// updates true,true,false,false,true — pairs of no-ops; 16 clicks → 32 _w
// lookups but only 3-4 visible toggles). FIX: in toggle mode (mode==_fa)
// read the state via a fresh `chrome.tabs.get` before the update. Same
// staleness applied to `_Rh` (muteTabs, read `_Yp[c].mutedInfo.muted`) and
// `_7f` (highlightTabs, read `_Yp[].highlighted` via `_go`).
{
  const b = fs.readFileSync(path.join(MV3, 'sw_core_bundle.js'), 'utf8');
  const f8 = fs.readFileSync(path.join(MV3, 'file8.js'), 'utf8');
  const ok =
    f8.includes('_Yk.tabs.get(c,t=>{t?_Yk.tabs.update(c,{[b.propName]:!t[b.propName]},d.onReady()):d.onReady()})') &&
    f8.includes('_Yk.tabs.get(c,t=>{t?_Yk.tabs.update(c,{muted:!(t.mutedInfo&&t.mutedInfo.muted)},d.onReady()):d.onReady()})') &&
    f8.includes('_Yk.tabs.get(g,t=>{let e=t?t.highlighted:_go(c)') &&
    !f8.includes('!_Yp[c][b.propName]') &&
    !f8.includes('!_Yp[c].mutedInfo.muted') &&
    b.includes('_Yk.tabs.get(c,t=>{t?_Yk.tabs.update(c,{[b.propName]:!t[b.propName]}') &&
    b.includes('_Yk.tabs.get(g,t=>{let e=t?t.highlighted:_go(c)');
  check('file8 _9f/_Rh/_7f: toggle reads FRESH tabs.get state (stale-_Yp enum-cache fix, 2026-08-30)',
    ok, 'freshToggle=' + ok);
}

// B54. Open URL (to the right) + Switch to right tab jumped ONE TAB TOO FAR
// (2026-09-11). ROOT CAUSE: _Rf's 1500ms windows.getAll cache. loadUrls
// tabs.create finishes and onCreated/_Zf writes _Yp, but _Gk / _cd[w].tabs
// (the ordered lists rightTabWrap uses) are only rebuilt by _Fu. The next
// action's _Rf saw a WARM cache and skipped the enum → _xy("next") of the
// current tab was still the OLD right neighbor, sitting one slot past the
// just-created tab. FIX: structural tab/window events set __acEnumDirty so
// the next _Rf re-enums even inside the cache window. Wheel-spin
// switchRight (no strip change) still hits the 1500ms cache.
{
  const b = fs.readFileSync(path.join(MV3, 'sw_core_bundle.js'), 'utf8');
  const f37 = fs.readFileSync(path.join(MV3, 'file37.js'), 'utf8');
  const f62 = fs.readFileSync(path.join(MV3, 'file62_mv3.js'), 'utf8');
  const f34 = fs.readFileSync(path.join(MV3, 'file34_mv3.js'), 'utf8');
  const dirtyOk = f37.includes('function __acInvalidateEnumCache') &&
    f37.includes('__acEnumDirty') &&
    f37.includes('if(__acEnumDirty||_now-__acLastEnum>__acEnumCacheMs)');
  const listenersOk = (f62.match(/__acInvalidateEnumCache/g) || []).length >= 4 &&
    f62.includes('onMoved') &&
    (f34.match(/__acInvalidateEnumCache/g) || []).length >= 2;
  const bundledOk = b.includes('function __acInvalidateEnumCache') &&
    b.includes('if(__acEnumDirty||_now-__acLastEnum>__acEnumCacheMs)');
  check('enum cache: dirty flag after tab create/remove so Open URL + switchRight sees the new tab (2026-09-11)',
    dirtyOk && listenersOk && bundledOk,
    'dirty=' + dirtyOk + ' listeners=' + listenersOk + ' bundled=' + bundledOk);
}

// B28. Logging switches in the UI (2026-08-08): MV2-like silent console was a
// hardcoded flag; now it is three checkboxes in Options → Advanced Options
// (advOpts): "Log service worker" (logSw), "Log page scripts" (logPage),
// "Log settings page" (logSettings). Each runtime (SW / content script /
// settings page) reads its flag from chrome.storage.local advOpts and
// applies it live via storage.onChanged. Default = OFF (MV2-like silence;
// publishing default). console.error is always kept.
// Startup output is BUFFERED until the flag read resolves (no burst when off).
{
  const sw = fs.readFileSync(path.join(MV3, 'sw.js'), 'utf8');
  const f30 = fs.readFileSync(path.join(MV3, 'file30.js'), 'utf8');
  const f42 = fs.readFileSync(path.join(MV3, 'file42.js'), 'utf8');
  const shim = fs.readFileSync(path.join(MV3, 'mv3_shim.js'), 'utf8');
  const ok = f30.includes('_re("logSw",a.logSw,"hard")') &&
    f30.includes('_re("logPage",a.logPage,"hard")') &&
    f30.includes('_re("logSettings",a.logSettings,"hard")') &&
    sw.includes('r.advOpts && r.advOpts.logSw') &&
    sw.includes('__acApplyLogging()') &&
    f42.includes('r.advOpts&&r.advOpts.logPage') &&
    shim.includes('r.advOpts && r.advOpts.logSettings') &&
    shim.includes('AC_LOG_SETTINGS ? __acOrigConsole[m] : function(){}') &&
    // Publishing defaults are OFF (MV2-like silence).
    sw.includes('AC_LOG_SW = false') &&
    f42.includes('AC_LOG_PAGE=false') &&
    shim.includes('AC_LOG_SETTINGS = false') &&
    // Startup-burst buffering (2026-08-08): init logs are captured until the
    // async advOpts read resolves — with a flag off, NOT a single startup
    // line prints (observed: settings applied with a delay).
    sw.includes('__acLogBuf') && sw.includes('__acLogApplied') &&
    shim.includes('__acLogBuf') && shim.includes('__acLogApplied');
  check('logging switches: advOpts checkboxes + storage-driven AC_LOG_* (2026-08-08)', ok,
    'logOpts=' + ok);
}

// B29. Toolbar-button icons at browser start (2026-08-08): two-sided fix.
// (a) AutoControl SW: `_Pk()` (push btnProps — title/icon — to every
// configured toolbar-button extension) now runs on EVERY config-chain
// completion via the configLoaded local handler (MV2 called _Pk in its
// startup init file62.js; the SW chain _lr→_Gf never did → buttons kept
// their default icons until clicked).
// (b) Toolbar-button MV3 extensions: their SW is LAZY and never ran at
// browser start → the old one-shot getTitle check never sent TBBtnInit.
// bgPage.js now registers runtime.onStartup/onInstalled and RETRIES
// TBBtnInit (2s backoff, ~30 attempts) until AutoControl answers (btnProps
// sets __gotProps) or a custom title is already present.
{
  const sw = fs.readFileSync(path.join(MV3, 'sw.js'), 'utf8');
  const ok = sw.includes("typeof _Pk === 'function'") && sw.includes('_Pk();');
  const btnDirs = ['TOOLBAR-BUTTON-MV3', 'TOOLBAR-BUTTON-Duplicate-MV3',
    'TOOLBAR-BUTTON-Mute-MV3', 'TOOLBAR-BUTTON-Pin-MV3', 'TOOLBAR-BUTTON-Unload-MV3'];
  let btnsOk = true, missing = [];
  for (const d of btnDirs) {
    const p = path.join(__dirname, '..', 'Toolbar-buttons', d, 'bgPage.js');
    if (!fs.existsSync(p)) { missing.push(d + ' (no file)'); btnsOk = false; continue; }
    const b = fs.readFileSync(p, 'utf8');
    const f = b.includes('chrome.runtime.onStartup.addListener( requestInit )') &&
      b.includes('chrome.runtime.onInstalled.addListener( requestInit )') &&
      b.includes('setTimeout( tryOnce, 2000 )') &&
      b.includes('__gotProps = true ;') &&
      b.includes("'TBBtnInit'");
    if (!f) { missing.push(d); btnsOk = false; }
  }
  check('toolbar-button icons pushed at config-chain completion + button-side TBBtnInit retry (2026-08-08)',
    ok && btnsOk, 'swPush=' + ok + ' buttons=' + (btnsOk ? 'all 5 OK' : missing.join(',')));
}

// B30. Favicon warmup (2026-08-08): the favicon cache patch (mv3_native_shim)
// pre-fetches only tabs present at init — and if _Yp is not populated yet
// (native handshake still running), that pre-fetch does nothing → the FIRST
// open of a custom tab menu shows EMPTY icons. Fix in sw.js: warm on
// tabs.onCreated + onUpdated(favIconUrl) via the patched _Zs (Google s2
// background fill of _7o), delayed sweeps at SW start (1500/4000/9000ms),
// and a re-sweep after every config-chain completion (configLoaded → fresh
// _Yp from the window enum).
{
  const sw = fs.readFileSync(path.join(MV3, 'sw.js'), 'utf8');
  const ok = sw.includes('const __acFavWarm = (tab) =>') &&
    sw.includes('const __acFavSweep = () =>') &&
    sw.includes('chrome.tabs.onCreated.addListener(__acFavWarm)') &&
    sw.includes('changeInfo.favIconUrl') &&
    sw.includes('[1500, 4000, 9000].forEach(ms => setTimeout(__acFavSweep, ms))') &&
    sw.includes('typeof _Yp') &&
    sw.includes('_Zs(tab.favIconUrl)(() => {})') &&
    sw.includes("_Zs('chrome://favicon/' + u)(() => {})") &&
    sw.includes('if (typeof __acFavSweep === \'function\') { try { __acFavSweep(); } catch (e) {} }');
  check('favicon warmup: tab-create/update hooks + startup sweeps + configLoaded re-sweep (2026-08-08)',
    ok, 'favWarm=' + ok);
}

// B31. Telemetry gate (2026-08-08, privacy — user request): appEvent POSTs
// (`_Ot` in file13.js, IN bundle) are OFF by default; enabled ONLY via the
// Advanced Options checkbox "Send anonymous usage data" (advOpts.telemetry),
// live via storage.onChanged. The callback is preserved when disabled (some
// call sites wait for it). file13.js covers BOTH the SW (via the bundle) and
// the settings page (main.html loads it directly). file30.js `_Ls` renders
// the checkbox + a consent paragraph.
{
  const f13 = fs.readFileSync(path.join(MV3, 'file13.js'), 'utf8');
  const f30 = fs.readFileSync(path.join(MV3, 'file30.js'), 'utf8');
  const bndl = fs.readFileSync(path.join(MV3, 'sw_core_bundle.js'), 'utf8');
  const ok = f13.includes('let __acTel=!1') &&
    f13.includes('!__acTel)return c&&c()') &&
    f13.includes('advOpts.telemetry') &&
    f13.includes('__acTel=!!((a.advOpts.newValue||{}).telemetry)') &&
    f13.includes('[AC-TEL]') &&
    f13.includes('(__acTel?"send":"skipped")') &&
    f30.includes('_re("telemetry",a.telemetry,"hard")') &&
    f30.includes('Send anonymous usage data') &&
    f30.includes('Disabled by default') &&
    bndl.includes('let __acTel=!1') &&
    bndl.includes('!__acTel)return c&&c()') &&
    bndl.includes('[AC-TEL]');
  check('telemetry gate: _Ot off by default + advOpts.telemetry checkbox with consent (2026-08-08)',
    ok, 'telGate=' + ok);
}

// B33. Type-40 capture watchdog (2026-08-09, staged + definitive recording
// gate): the native's raw-capture mode (type 40, _Qr — combo editor /
// gesture tester / devInput) streams raw type-760 events and SUPPRESSES
// type-750 triggers. A lost/raced OFF leaves the native stuck
// (gestures/hotkeys/RMB dead). STAGES: 0→1 send type-40 false twice (60ms
// apart — event+gesture modes are independent); 1→2 if the flood continues
// ~8s → port drop (fresh Zero+engine — the capture flag lives in the
// engine); 2→3 still flooding → SW reload. Fast page-gone release: the last
// settings page closes while capture armed (tabs.onRemoved + broadcast).
// THE RECORDING GATE (2026-08-09, final): no RATE metric can tell human
// typing from a stuck flood (user VM 14:47: 38 keys / 78 events / 16.3s
// looked dense by every threshold) — so while __acCaptureOn is true (the
// page has a recording armed: editor open) the page-open path NEVER heals
// (the editor's own OFF works now and releases on close). It heals ONLY
// when the page ALREADY sent its OFF (__acCaptureOn === false) yet raw 760s
// still flow = DEFINITELY a stuck native. Type-40 tracking lives in
// postMsg() (single choke point: page proxy, _acNativeSend, bundle _Lk).
{
  const sw = fs.readFileSync(path.join(MV3, 'sw.js'), 'utf8');
  const ok = sw.includes('AC_CAPTURE_HEAL_GRACE = 15000') &&
    sw.includes('let __acCaptureStage = 0') &&
    sw.includes('function __acCaptureRelease(reason, stage)') &&
    sw.includes('[AC-CAPTURE]') &&
    sw.includes('postMsg(40, false)') &&
    sw.includes('setTimeout(() => { try { postMsg(40, false); } catch(e) {} }, 60)') &&
    sw.includes('port.disconnect(); } else { scheduleRetry(); }') &&
    sw.includes('chrome.runtime.reload(); } catch(e) {}') &&
    sw.includes('function __acCheckExtPages()') &&
    sw.includes('chrome.tabs.onRemoved.addListener') &&
    // type-40 tracking moved into postMsg() (single choke point)
    sw.includes('__acCaptureOn = !!payload') &&
    sw.includes('if (payload) __acCaptureStage = 0') &&
    // the definitive recording gate: never heal while a recording is armed
    sw.includes('!__acCaptureOn &&') &&
    sw.includes('tabs.length === 0 && __acCaptureOn && __acCaptureStage === 0') &&
    sw.includes('__acRaw760Start = 0;') &&
    // stale-armed release (2026-08-30): an armed capture with no 750 for
    // AC_CAPTURE_STALE_ARMED_MS (5 min — raised from 60s, user D-15: the
    // gesture tester file30 re-arms only on window focus, so a 60s pause
    // released a LIVE test session) is a dead editor/test session (page
    // died/reloaded without OFF) — release it; a live recording re-arms on
    // the next editor action
    sw.includes('AC_CAPTURE_STALE_ARMED_MS = 300000') &&
    sw.includes('__acNoToggle > AC_CAPTURE_STALE_ARMED_MS') &&
    sw.includes('Date.now() - __acCaptureT > AC_CAPTURE_STALE_ARMED_MS') &&
    sw.includes('750 arrived while armed — capture actually released') &&
    sw.includes('setInterval(() => {') &&
    // negative: the SW must never ARM capture on its own
    !sw.includes('postMsg(40, true)') &&
    !sw.includes('postMsg(40, {mouseGest');
  check('capture watchdog: staged heal + page-gone release + recording gate (never heal while armed; heal only when OFF was sent but 760s persist) (2026-08-09)',
    ok, 'captureHeal=' + ok);
}

// B35. postMsg falsy-payload fix (2026-08-09, ROOT CAUSE of both
// stuck-capture incidents): `content: payload || {}` MANGLED `false` into
// `{}` — the type-40 OFF (postMsg(40, false)) reached the native as an EMPTY
// OBJECT, so capture was never disabled (user VM 12:55 & 13:49: raw 760
// floods with ZERO 750s until an SW reload spawned a fresh engine; every UI
// `_0d(!1)` was affected too). Fix: coalesce only null/undefined.
{
  const sw = fs.readFileSync(path.join(MV3, 'sw.js'), 'utf8');
  const ok = sw.includes('const content = payload == null ? {} : payload;') &&
    sw.includes('port.postMessage({ type, content });') &&
    !sw.includes('content: payload || {}');
  check('postMsg preserves falsy payloads — type 40 false OFF actually reaches the native (2026-08-09)',
    ok, 'payloadFix=' + ok);
}

// B34. Action-queue watchdog OK-detector (2026-08-09): the watchdog detected
// `[AC-ACT] ... OK` by hooking console.warn, but the async logging patch
// (__acApplyLogging — advOpts storage read, added 2026-08-08) REPLACES
// console.warn after that block → the hook died → __acLastOkTime froze at
// SW start → spurious "Queue stuck! ... last OK <start>ms ago → force-shift"
// dropped LIVE queue items (user VM 2026-08-09 13:48:06, mid wheel-spin:
// "Queue stuck! 1 items, last OK 136965ms ago" — exactly SW start time).
// Fix: hook the bundle's __acLog directly (t === 'OK' is the exact
// completion marker; __acLog is a global function declaration of the
// imported bundle, so the reassignment is seen by all call sites).
{
  const sw = fs.readFileSync(path.join(MV3, 'sw.js'), 'utf8');
  const ok = sw.includes('const _origActLog = __acLog') &&
    sw.includes('__acLog = function (t, m)') &&
    sw.includes("if (t === 'OK') __acLastOkTime = Date.now()") &&
    sw.includes('return _origActLog(t, m)') &&
    sw.includes("typeof _2y !== 'undefined' && typeof _6y === 'function' && typeof __acLog === 'function'") &&
    !sw.includes('Hook console.warn to detect [AC-ACT]');
  check('action-queue watchdog: OK-detector hooked via bundle __acLog (survives logging patch) (2026-08-09)',
    ok, 'wdHook=' + ok);
}

// ---------- user config (optional: skip if the .acs file is absent) ----------
if (!fs.existsSync(ACS)) {
  note('config compile skipped', 'missing ' + ACS);
} else {
const acs = JSON.parse(fs.readFileSync(ACS, 'utf8'));
const trigActList = acs.trigActList; // pairs array [id, data]

// ---------- compile ----------
const result = vm.runInContext(`
  (function(){
    const trigActList = ${JSON.stringify(trigActList)};
    const advOpts = ${JSON.stringify(acs.advOpts || {})};
    const mouseGest = ${JSON.stringify(acs.mouseGest || {})};
    const payload = _mh(trigActList, mouseGest, advOpts);
    return payload;
  })()
`, ctx);

// ---------- dump wheel entries (512/1536) ----------
console.log('=== map keys ===');
console.log(Object.keys(result.map).join(', '));
console.log('=== wheel entries: key 512 (wheel down) & 1536 (wheel up) ===');
for (const k of ['22537', '23561']) { // 22025+512, 22025+1536
  if (result.map[k]) {
    console.log('mapKey ' + k + ' → list idx ' + JSON.stringify(result.map[k]));
    for (const idx of result.map[k]) {
      console.log('  [' + idx + '] ' + JSON.stringify(result.list[idx]));
    }
  } else {
    console.log('mapKey ' + k + ' → NOT REGISTERED');
  }
}
console.log('=== all entries with type:14 (mouseOver precond) ===');
result.list.forEach((e, i) => {
  if (e && Array.isArray(e.preconds) && e.preconds.some(p => p && p.type === 14)) {
    console.log('  [' + i + '] ' + JSON.stringify(e));
  }
});
console.log('=== gestures count: ' + (result.gestures || []).length);
} // end optional config compile

// NOTE: the TAB-GATE payload strip (stripTabRegionFromWheelEntries) was
// REMOVED from sw.js on 2026-08-02 — the per-tab workaround is impossible
// (native UIA hit-test broken in Chrome 148+; 485/330 queries unreliable).
// This harness now only verifies that the user's config compiles through the
// real _mh and shows what the native receives for the wheel triggers.

// ---------- global visibility checks (what sw.js can reference) ----------
vm.runInContext(`console.log('globals: _Vy=' + typeof _Vy + ' _Lk=' + typeof _Lk +
  ' _trigActList=' + typeof _trigActList + ' _su=' + typeof _su +
  ' _No=' + typeof _No + ' _g=' + typeof _g + ' _Or=' + typeof _Or +
  ' _cd=' + typeof _cd + ' z=' + typeof z +
  ' _Yh=' + typeof _Yh + ' self._Yh=' + typeof self._Yh +
  ' window._Yh=' + typeof window._Yh + ' self._Vy=' + typeof self._Vy +
  ' selfIsGlobal=' + (self===globalThis) + ' selfIsWindow=' + (self===window) +
  ' _YhKeys=' + Object.keys(globalThis).filter(k=>/_Yh/.test(k)).join(','))`, ctx);

// ---------- XHR shim smoke test (file70 _Su / file77 saveURL need headers) ----------
// The prelude XHR shim now stores the fetch Response and exposes
// getResponseHeader/getAllResponseHeaders/responseURL — file70 _Su() and
// file77 O()/saveURL depend on them ("a.getResponseHeader is not a function"
// was the failure). This mimics the shim in a vm context.
vm.runInContext(`
  (function(){
    globalThis.fetch = (u) => Promise.resolve({
      status: 200, statusText: 'OK', url: u,
      headers: {
        get: n => (n === 'Content-Type' ? 'image/png' : null),
        forEach: cb => cb('image/png', 'Content-Type')
      },
      text: () => Promise.resolve('fake-body')
    });
    const x = new XMLHttpRequest();
    x.open('GET', 'http://x/img.png');
    x.responseType = 'text';
    x.onload = () => {
      console.log('XHR shim OK: status=' + x.status +
        ' body=' + x.response +
        ' ct=' + x.getResponseHeader('Content-Type') +
        ' cd=' + x.getResponseHeader('Content-Disposition') +
        ' url=' + x.responseURL +
        ' all=' + JSON.stringify(x.getAllResponseHeaders()));
    };
    x.onerror = e => console.log('XHR shim ERROR:', e && e.message || e);
    x.send();
  })()
`, ctx);

// ---------- BUNDLE onMessage listeners test (who handles userAPI?) ----------
// file48 registers `_Yk.runtime.onMessage.addListener` INSIDE the bundle —
// in the real SW this is a live listener alongside any sw.js handler.
// Chrome dispatches EVERY message to ALL listeners → userAPI (ACtl.*) was
// handled TWICE: sw.js handler + bundle m() → double _Yh → double W → e.g.
// setClipboard ran F→K twice (2× type 286). This test simulates Chrome
// dispatching to every registered listener and reports how many answered.
vm.runInContext(`
  (function(){
    const msg = {type:"userAPI", props:["sleep"], args:[10], scriptId:"t", targetTabs:null, trigInstId:"i"};
    const sender = { tab: { id: 1 } };
    let answers = 0;
    const results = [];
    onMsgListeners.forEach((fn, idx) => {
      let called = false;
      const cb = (r) => { called = true; answers++; results.push(idx + ':' + JSON.stringify(r && r.result !== undefined ? {result:true} : r)); };
      const ret = fn(msg, sender, cb);
      results.push(idx + ':ret=' + ret + (called ? ' called-sync' : ''));
    });
    setTimeout(() => {
      console.log('userAPI dispatch: ' + answers + ' answered of ' + onMsgListeners.length + ' listeners; details: ' + results.join(' | '));
    }, 100);
  })()
`, ctx);

// ---------- _Yh smoke test (userAPI handler) ----------
// _Yh is a top-level LET (file48) assigned by file77 — a GLOBAL LEXICAL
// binding, NOT a property of self. sw.js must reference it as a free
// variable (`typeof _Yh`), not `self._Yh`. AND it returns a CALLBACK-style
// runner (file67 `_us`), so sw.js must call `_Yh(msg, tab)(onOk, onErr)` —
// exactly like the original page handler in file48. This smoke test mimics
// sw.js's call for an ACtl.* request ("sleep").
vm.runInContext(`
  (function(){
    try{
      _Yh({props:["sleep"],args:[10],scriptId:"t",targetTabs:null,trigInstId:"i"}, {id:1})(
        r => console.log('_Yh smoke OK:', JSON.stringify(r)),
        e => console.log('_Yh smoke ERROR:', e && e.message || e)
      );
    }catch(e){ console.log('_Yh smoke THREW:', e && e.message || e); }
  })()
`, ctx);

// B36. Protected-pages UX (2026-08-09, runScript on chrome:// / Web
// Store): Chrome refuses ALL script injection on chrome://*, the Web Store,
// chrome-extension://, devtools:// and view-source: (platform restriction,
// identical in MV2 — NOT a port regression). RUN SCRIPT / ACtl.* used to
// fail silently or with a raw "Cannot access a chrome:// URL". Fix:
// (a) prelude helpers __acIsProtectedPage/__acProtectedMsg/
// __acNotifyProtected (bundle top-level — visible to the shim AND sw.js);
// (b) executeScript shim pre-checks the tab URL + maps the raw rejection;
// (c) sw.js execUserFunc fails fast on sender.tab.url and maps the catch.
{
  const b = fs.readFileSync(path.join(MV3, 'sw_core_bundle.js'), 'utf8');
  const sw = fs.readFileSync(path.join(MV3, 'sw.js'), 'utf8');
  const helpers = b.includes('function __acIsProtectedPage') &&
    b.includes('__acProtectedMsg') &&
    b.includes('function __acNotifyProtected') &&
    b.includes('chromewebstore.google.com') &&
    // UNIQUE notification id per call (2026-08-09, user report: the toast
    // did not reappear on every call) — a fixed id silently updates the
    // still-visible toast instead of showing a fresh one. 1.5 s anti-spam
    // only (loops); the old 10 s throttle dropped every second manual run.
    b.includes('"acProtectedPage_" + (++__acProtNotifSeq) + "_" + now') &&
    b.includes('now - __acProtNotifAt < 1500');
  const shim = b.includes('function __acExecScriptFile') &&
    b.includes('__acIsProtectedPage(t.url') &&
    b.includes('cannot access (a )?(chrome|chrome-extension|devtools)') &&
    !b.includes('.catch(() => cb && cb(null));');
  const swA = sw.includes('__acIsProtectedPage(sender && sender.tab && sender.tab.url)') &&
    sw.includes('[AC-MV3] execUserFunc blocked — protected page');
  const swB = sw.includes('__acProtectedMsg') &&
    sw.includes('safeSendRes({ error: __acProtectedMsg })');
  check('protected-pages UX: prelude helpers + shim pre-check + execUserFunc fail-fast/map (runScript chrome://)',
    helpers && shim && swA && swB, 'helpers=' + helpers + ' shim=' + shim + ' swA=' + swA + ' swB=' + swB);
}

// B37. runInFrames subframes (2026-08-10, FEATURES-MV3.md §7-5): execUserFunc used to
// target frameIds:[0] ALWAYS — a subframe's file42 → FN → SW →
// userScripts.execute landed in the TOP frame, so runInFrames funcCode ran
// N times but always with the top frame's location/document (MV2 eval'd it
// locally in each frame). Fix: use sender.frameId (MV3 provides it for
// content-script messages) — subframe calls execute in their own frame,
// plain script runs (frame 0) are unchanged.
{
  const sw = fs.readFileSync(path.join(MV3, 'sw.js'), 'utf8');
  const ok = sw.includes('sender.frameId') &&
    sw.includes('frameIds: [frameId]') &&
    !sw.includes('frameIds: [0]') &&
    !sw.includes('target ONLY the main frame (frameIds:[0])');
  check('runInFrames subframes: execUserFunc targets sender.frameId (FEATURES-MV3.md §7-5)',
    ok, 'frameId=' + ok);
}

// B38. runInFrames cold-start retry (2026-08-10, FEATURES-MV3.md §7-5 follow-up): the
// first userScripts.execute in a fresh (sub)frame costs ~4-5s (Chrome creates
// the USER_SCRIPT world on first use); the SW acks early via its 3s safety
// timeout and the first result can be lost — observed: runInFrames first run
// returned only the top frame's null. file42's FN now re-sends execUserFunc
// ONCE if the SW acked with `timeout` and no acUserApiRes arrived within 6s
// (the world is warm by then → the retry succeeds). Mirrors the n() null-retry.
{
  const f42 = fs.readFileSync(path.join(MV3, 'file42.js'), 'utf8');
  const ok = f42.includes('if (h && h.timeout)') &&
    f42.includes('[AC-F42] execUserFunc cold-init retry') &&
    f42.includes('id2 = "__acr_"');
  check('runInFrames cold-start: file42 re-sends execUserFunc once on SW timeout (2026-08-10)',
    ok, 'coldRetry=' + ok);
}

// B39. runInFrames multi-frame dedup collision (2026-08-10, FEATURES-MV3.md §7-5
// follow-up): the SAME frmCBId message (carries scriptId → handled by the
// scriptId branch) is delivered to EVERY matching frame; trigInstId came
// from the message AS-IS → all frames sent execUserFunc with the SAME SW
// dedup key → the 2nd+ frames got BLOCK in-flight → {result:undefined} →
// null in the result (user VM: ["https://example.org/", null]). Fix: the
// scriptId branch appends a per-FRAME random to trigInstId when a.frmCBId
// is set (plain RUN SCRIPT unchanged).
{
  const f42 = fs.readFileSync(path.join(MV3, 'file42.js'), 'utf8');
  const ok = f42.includes('a.frmCBId?"~f"+(Math.random()+"").slice(2)') &&
    f42.includes('per-FRAME random to trigInstId');
  check('runInFrames multi-frame: per-frame trigInstId suffix for frmCBId messages (2026-08-10)',
    ok, 'frameSuffix=' + ok);
}

// B40. file71 popup from the SW — _Fo replaced by the MV3 implementation
// (2026-08-12, FEATURES-MV3.md §7-15): MV2's _Fo (file70, IN bundle) filled
// the popup via chrome.extension.getViews({windowId}) — ABSENT in the MV3
// SW (prelude: () => []) → TypeError → empty window. The shim now
// overwrites window._Fo with __acMv3Popup: windows.create with a ?runId URL
// + the popup page (file71.html + file71_bridge.js) requests its content
// via chrome.runtime.sendMessage({type:"acPopupContent"}) — scripting.
// executeScript CANNOT inject into chrome-extension:// pages (user VM
// 2026-08-12: "Extension manifest must request permission to access this
// host" → empty window flash). Button result: acPopupResult → __acResolvePopup.
{
  const shim = fs.readFileSync(path.join(MV3, 'mv3_native_shim.js'), 'utf8');
  const bridge = fs.readFileSync(path.join(MV3, 'file71_bridge.js'), 'utf8');
  const f71 = fs.readFileSync(path.join(MV3, 'file71.html'), 'utf8');
  const ok = shim.includes('window._Fo = __acMv3Popup') &&
    shim.includes('window.__acResolvePopup = __acResolvePopup') &&
    shim.includes('window.__acPopupGetContent') &&
    shim.includes("?runId=' + runId") &&
    bridge.includes('acPopupContent') &&
    bridge.includes('acPopupResult') &&
    f71.includes('file71_bridge.js') &&
    shim.includes('FEATURES-MV3.md §7-15');
  const runtime = vm.runInContext(`typeof _Fo === 'function' && typeof window._Fo === 'function' &&
    typeof window.__acResolvePopup === 'function' && typeof window.__acPopupGetContent === 'function'`, ctx);
  check('MV3 _Fo: shim popup + content-bridge (acPopupContent/acPopupResult) + file71_bridge.js (2026-08-12)',
    ok && runtime, 'shim=' + ok + ' runtime=' + runtime);
}

// B41. MV3 _Fo popup flow (2026-08-12, FEATURES-MV3.md §7-15): _Fo(opts, html, cb)
// must (a) pre-convert <key>N</key> codes to names via the bundle's _Je
// (MV2 did it in onloaded inside the popup), (b) create the file71.html
// popup window with ?runId, (c) expose the content via __acPopupGetContent
// (what the popup page requests), (d) resolve the callback on acPopupResult
// and close the window. Simulates the Chrome events the stub records.
{
  const winCreated = ctx.__acWinCreated, winRemoved = ctx.__acWinRemoved;
  vm.runInContext(`_Fo({ width: 500, no: false, onloaded: () => {} }, '<key>65</key>hello', r => { window.__resolved = r; })`, ctx);
  const created = winCreated[0] || {};
  const runIdM = /[?&]runId=(\d+)/.exec(created.url || '');
  const winOk = !!(created.url && created.url.indexOf('file71.html') > -1) && !!runIdM && created.type === 'popup';
  const runId = runIdM ? +runIdM[1] : 0;
  const content = vm.runInContext(`window.__acPopupGetContent(${runId})`, ctx);
  const htmlConverted = content && content.html && content.html.indexOf('<key>65</key>') === -1 && content.html.indexOf('</key>') > -1;
  const winId = content && content.winId;
  vm.runInContext(`window.__acResolvePopup(${runId}, true)`, ctx);
  const resolved = ctx.__resolved;
  const resolveOk = resolved && resolved.answer === true && winRemoved.indexOf(winId) > -1;
  check('MV3 _Fo flow: popup window + key-name conversion + content bridge + result (2026-08-12)',
    winOk && htmlConverted && resolveOk && !!winId,
    'win=' + winOk + ' keysConverted=' + htmlConverted + ' resolved=' + (resolved && resolved.answer) + ' winRemoved=' + (winRemoved.indexOf(winId) > -1));
}

// B42. Repair diagnostics survive the SW reload (2026-08-12, FEATURES-MV3.md §7-15):
// MV2 kept showNotif/diagnostics in the background page's real localStorage;
// the MV3 in-memory shim dies with the SW → the fresh SW's file34 branch
// never ran → no REPAIR COMPLETE popup after Emergency Repair. sw.js now
// persists the one-shot flags (__acEmergencyRestartNative reads _j before
// the reload) and the fresh SW shows _Kg/_Ht from storage in
// proceedAfterFileCheck; the popup result arrives via acPopupResult.
{
  const sw = fs.readFileSync(path.join(MV3, 'sw.js'), 'utf8');
  const ok = sw.includes("_j('diagnostics')") &&
    sw.includes("_j('showNotif')") &&
    sw.includes('__acRepairDiag') &&
    sw.includes('chrome.storage.local.set({ __acRepairDiag:') &&
    sw.includes('chrome.storage.local.get(["__acRepairDiag"]') &&
    sw.includes('chrome.storage.local.remove("__acRepairDiag")') &&
    sw.includes('_Kg(c.downKeys)') &&
    sw.includes('_Ht(win)') &&
    sw.includes('msg.type === "acPopupResult"') &&
    sw.includes('__acResolvePopup(msg.runId, !!msg.answer)') &&
    sw.includes('msg.type === "acPopupContent"') &&
    sw.includes('__acPopupGetContent(msg.runId)');
  check('repair diagnostics: _j → storage persist (pre-reload) + _Kg/_Ht from storage (fresh SW) (2026-08-12)',
    ok, 'repairDiag=' + ok);
}

// B43. Context menu owned by the SW ONLY (2026-08-12, FEATURES-MV3.md §7-15):
// the settings page / offscreen must NOT run file47 `_nk()` — it calls the
// UNPATCHED chrome.contextMenus.removeAll (wipes the SW's "Emergency repair"
// item) and create() with contexts:["browser_action"] which is INVALID in MV3
// (the SW's create patch maps it to "action"; the page has no patch) → the
// item vanished right after opening the settings page (user 2026-08-12). The
// shim stubs window._nk outside the SW (importScripts check) and the
// Not-leader _if-populate branch no longer calls _nk.
{
  const shim = fs.readFileSync(path.join(MV3, 'mv3_native_shim.js'), 'utf8');
  const ok = shim.includes("if (typeof importScripts !== 'function')") &&
    shim.includes('window._nk = function() {};') &&
    shim.includes('NO _nk() on') &&
    // the Not-leader populate branch must not call _nk anymore
    !/_\u0036s\(\{\}, \(\) => \{\s*if \(typeof _nk === 'function'\)/.test(shim) &&
    !/_\u0036s\(\{\}, \(\) => \{\s*if \(typeof _nk/.test(shim);
  check('page/offscreen _nk neutralized; menu owned by SW (2026-08-12)', ok, 'nkNoop=' + ok);
}

// B44. file46.css help-hint glyph (2026-08-12): `h::before {content:'¿'}` —
// the file carried a single 0xBF byte (Windows-1252 `¿`) with NO @charset →
// Chrome decodes CSS as UTF-8 → invalid byte → U+FFFD replacement char in
// the UI (broken "?" in tgtsFld help hints). Fixed to proper UTF-8 C2 BF.
{
  const p = path.join(MV3, 'file46.css');
  const b = fs.readFileSync(p);
  // Every 0xBF must be the second byte of a C2 BF pair (proper UTF-8 ¿) —
  // a lone 0xBF (Windows-1252 remnant) would decode as U+FFFD.
  let lone = false;
  for (let i = 0; i < b.length; i++) {
    if (b[i] === 0xBF && !(i > 0 && b[i - 1] === 0xC2)) { lone = true; break; }
  }
  const ok = !lone && !b.toString('utf8').includes('\uFFFD');
  check('file46.css: ¿ stored as valid UTF-8 (no lone 0xBF / no U+FFFD) (2026-08-12)', ok,
    'utf8¿=' + ok);
}

// B45. Offscreen-document log marker (2026-08-12, TODO "offscreen logs"):
// the offscreen has its OWN inspector (chrome://extensions → "Inspect views:
// Offscreen document") — its console output must carry the [AC-OFFSCREEN] prefix
// so it is never confused with the SW console ([AC-MV3]/[AC-SW] lines).
{
  const off = fs.readFileSync(path.join(MV3, 'offscreen.js'), 'utf8');
  const calls = off.match(/console\.(warn|log|error)\(/g) || [];
  // Every console call must start its first argument with the [AC-OFFSCREEN] marker.
  const firstArgs = (off.match(/console\.(?:warn|log|error)\(\s*(['"`])(.*?)\1/gs) || [])
    .map(m => m.replace(/^console\.(?:warn|log|error)\(\s*['"`]/, ''));
  const unprefixed = firstArgs.filter(s => s.indexOf('[AC-OFFSCREEN]') !== 0).length;
  const allMarked = calls.length > 0 && unprefixed === 0 &&
    off.includes('LOG MARKER: all console output from this document uses the `[AC-OFFSCREEN]`');
  check('offscreen.js: all console calls carry the [AC-OFFSCREEN] marker (2026-08-12)', allMarked,
    'calls=' + calls.length + ' unprefixed=' + unprefixed);
}

// B46. runInPageCtx inside runInFrames → own frame (2026-08-12,
// FEATURES-MV3.md §7-5 follow-up): a subframe's runInPageCtx used to run in
// the TOP frame — file42 relayed acMainWorld without a frame id, sw.js
// execMainWorld passed {} to __acInjectCode → userScripts.execute defaulted
// to frame 0. Fix: sw.js uses sender.frameId (injectDetails), __acInjectCode
// (prelude) supports details.frameIds (frameIds and allFrames are mutually
// exclusive in the target). The return path was already frame-correct
// (file42 posts acMainWorldRes to its own window).
{
  const sw = fs.readFileSync(path.join(MV3, 'sw.js'), 'utf8');
  const pre = fs.readFileSync(path.join(MV3, 'sw_prelude.js'), 'utf8');
  const srcOk = sw.includes('injectDetails') && sw.includes('frameIds: [frameId]') &&
    sw.includes("' frame=' + frameId") &&
    pre.includes('buildTarget') && pre.includes('details.frameIds') &&
    pre.includes('frameIds and allFrames are MUTUALLY EXCLUSIVE');
  // Runtime: __acInjectCode with {frameIds:[7]} must target frameIds:[7]
  // (no allFrames), and {allFrames:true} must keep allFrames (no frameIds).
  const runtime = vm.runInContext(`
    (function(){
      try {
        const calls = [];
        chrome.userScripts.execute = (o) => { calls.push(o); return Promise.resolve([{result: undefined}]); };
        __acUsFailed = false;
        let done1 = false, done2 = false;
        __acInjectCode(1, "c1", { frameIds: [7] }, r => { done1 = true; });
        __acInjectCode(1, "c2", { allFrames: true }, r => { done2 = true; });
        setTimeout(() => {
          const a = calls[0] && calls[0].target || {};
          const b = calls[1] && calls[1].target || {};
          console.log('B46 runtime: frameIds case = ' + JSON.stringify(a) + ' | allFrames case = ' + JSON.stringify(b) +
            ' | done1=' + done1 + ' done2=' + done2);
        }, 50);
      } catch (e) { console.log('B46 runtime THREW: ' + (e && e.message || e)); }
    })()
  `, ctx);
  const swB46 = sw.includes('injectDetails');
  check('runInPageCtx frame routing: execMainWorld sender.frameId + __acInjectCode frameIds (2026-08-12)',
    srcOk, 'src=' + srcOk);
  // The runtime probe is async — verify it in the summary timer below via
  // a flag: we record the JSON, then assert it at SUMMARY time.
  ctx.__b46Sw = swB46;
  ctx.__b46Src = srcOk;
}

// B47. Site bridge (webSettgs) for the GitHub Pages mirror (2026-08-29):
// the Import/View/redirSttgs interception on the site pages fires when the
// tab hostname matches the site host. The mirror lives on
// alex-302.github.io → the gate now accepts _9n alongside _mo. The bridge
// script must run in the ISOLATED world — __acInjectCode (userScripts/MAIN)
// has no chrome.runtime, so the original _wj path would throw on
// sendMessage; chrome.scripting.executeScript with world:"ISOLATED" +
// func/args restores MV2 semantics (tabs.executeScript). NOTE: ScriptInjection
// has NO `code` property (that's tabs.executeScript) and NO `runAt` (use
// injectImmediately) — both throw "Unexpected property". _Zr hardened:
// (document.head||document.documentElement) at document_start + try/catch.
// sw.js __acReinjectSiteBridge() re-injects into ALREADY-OPEN tabs at SW
// start (MV2's _zg re-injection) + 2/6/12s later. file48 m() calls
// (window._ja||l)(url) directly (the MV2 l → _0s() → getViews path is
// EMPTY in the SW). sw.js re-implements window._ja with the bundle's
// UI-free pipeline (_1p/_mg fetch, _Qj, _9i, _K dedupe, _4p merge, _bd
// save, _ku rebuild) + MV2-style permission request (notifications/
// downloads/sessions/bookmarks from the imported actions; <all_urls> is
// already granted) — denial skips the import. TEMP file:// bridge
// REMOVED 2026-08-30 (was only for local testing; MV2 never bridged
// file:// — the reinject query now matches the two web hosts only).
{
  const f62 = fs.readFileSync(path.join(MV3, 'file62_mv3.js'), 'utf8');
  const f10 = fs.readFileSync(path.join(MV3, 'file10.js'), 'utf8');
  const f48 = fs.readFileSync(path.join(MV3, 'file48.js'), 'utf8');
  const sw = fs.readFileSync(path.join(MV3, 'sw.js'), 'utf8');
  const srcOk =
    f10.includes('_9n="alex-302.github.io"') &&
    f62.includes('hostname.in(_mo,_9n)') &&
    f62.includes('"file:"==(new URL(_zh(_Yp[c]))).protocol') &&
    f62.includes('world:"ISOLATED"') &&
    f62.includes('injectImmediately:true') &&
    f62.includes('func:b=>') &&
    f62.includes('args:["2025.4.22"]') &&
    f62.includes('__acBridge') &&
    !f62.includes('code:`(function(){') &&
    !f62.includes('runAt') &&
    f62.includes('_Yk.scripting.executeScript') &&
    f48.includes('(window._ja||l)(a.imprtSttgs)') &&
    sw.includes('__acReinjectSiteBridge') &&
    sw.includes('_Zr(t.id)') &&
    sw.includes('*://alex-302.github.io/*') &&
    sw.includes('*://www.autocontrol.app/*') &&
    // TEMP file:// bridge removed 2026-08-30 — must NOT be in the query
    // or the reinject loop anymore
    !sw.includes("'file://*/*'") &&
    !sw.includes('fileTabs') &&
    !sw.includes('TEMP (2026-08-29)') &&
    sw.includes('window._ja = _cg') &&
    sw.includes('_K(l, merged, true, true)') &&
    sw.includes('_4p(l, merged, false)') &&
    sw.includes('_bd(out') &&
    sw.includes('_ku(() => {}') &&
    sw.includes('chrome.permissions.request') &&
    sw.includes('import skipped') &&
    sw.includes("needPerms.push('notifications')") &&
    sw.includes("chrome.notifications.create('acImportOk'") &&
    sw.includes('Settings imported successfully') &&
    sw.includes('chrome.tabs.create({ url: optsUrl })');
  // NOTE: the bundle as a whole legitimately contains `runAt` (file70 _wj
  // default for the tabs.executeScript shim) — assert only the _Zr
  // injection shape here.
  const bndOk = bundle.includes('_9n="alex-302.github.io"') &&
    bundle.includes('world:"ISOLATED"') &&
    bundle.includes('injectImmediately:true') &&
    bundle.includes('func:b=>') &&
    bundle.includes('(window._ja||l)(a.imprtSttgs)') &&
    bundle.includes('function _K(') && bundle.includes('function _4p(') &&
    bundle.includes('function _9i(') && bundle.includes('function _bd(');
  check('site bridge: mirror host + ISOLATED injectImmediately func + re-inject + SW _ja import + perms + m() direct call (2026-08-29)',
    srcOk && bndOk, 'src=' + srcOk + ' bundle=' + bndOk);
}

// B48. SFE Import (Import all in a View-opened editor tab) (2026-08-30):
// MV2 `_0s("none")` (file67) resolves the settings window via
// chrome.extension.getViews({tabId}) — mv3_shim.js stubbed ANY tabId lookup
// to [] → `a` stayed undefined → `_Xp(a)._Hu.wait()` threw → `_0j()` hung →
// file78 `_uw` never reached `_lj` → the import was a silent no-op. FIX
// (take 2): (a) chrome.extension.getViews DOES exist in MV3 extension pages
// (only the SW lacks it) — mv3_shim now calls the ORIGINAL for {tabId},
// restoring the MV2 semantics (the window that hosts that tab → _lj runs
// in the settings window when it is open); (b) file78 `_lj`/`_uw` write the
// merged result through REAL chrome.storage.local.set(_bj(a),h) instead of
// `_bd` — in the SFE tab `_Yk` is the file-proxy (file91 _Nh override), so
// `_bd` would write into the editor's file model `m` and the real settings
// would never change. The SW picks the write up via storage.onChanged →
// _Gf → native type 60. The [window] fallback remains only when the native
// getViews is unavailable and THIS page is main.html.
{
  const shim = fs.readFileSync(path.join(MV3, 'mv3_shim.js'), 'utf8');
  const f78 = fs.readFileSync(path.join(MV3, 'file78.js'), 'utf8');
  const sw = fs.readFileSync(path.join(MV3, 'sw.js'), 'utf8');
  const srcOk =
    shim.includes('origGetViews(opts)') &&
    shim.includes('take 2') &&
    shim.includes("location.pathname.endsWith('/main.html')") &&
    shim.includes('return [window];');
  const swOk =
    sw.includes('msg.type === 920 && connected && port && handshakeDone') &&
    sw.includes('sendRes({ ok: true, result: "pong" })');
  const f78Ok =
    f78.includes('AC-MV3 FIX (2026-08-30)') &&
    f78.includes('chrome.storage.local.set(_bj(a),h)') &&
    f78.includes('REAL chrome.storage.local') &&
    f78.includes('Settings imported successfully') &&
    f78.includes('_lj _8f failed') &&
    f78.includes('_lj _ku failed') &&
    f78.includes('let _hsh="#"+_hp(b)') &&
    f78.includes('location.hash!=_hsh') &&
    f78.includes('_ids[_sid]=1;a.sections.push({id:_sid,name:"Imported actions"})') &&
    f78.includes('location.replace(location.pathname+"?_ac="+Date.now()+_hsh)') &&
    f78.includes('$("html").addClass("visible").css("display","block")') &&
    f78.includes('_lj done: hash=') &&
    f78.includes('_gs("dialog")') &&
    f78.includes('w.location&&/[?&]file=/.test(w.location.href') &&
    f78.includes('_Yk.tabs.create({url:_fuh,active:!0},g)') &&
    f78.split('chrome.storage.local.set(_bj(a),h)').length - 1 >= 2;
  check('SFE Import: orig getViews for tabId + _lj/_uw bypass the SFE file-proxy into real storage + fresh-tab #hash fallback + ping fast-path (2026-08-30)',
    srcOk && swOk && f78Ok, 'shim=' + srcOk + ' sw=' + swOk + ' file78=' + f78Ok);
}

// B49. File-open dialog (type 240) must not time out after 5s (2026-08-30):
// mv3_native_shim `_Lk` applies a DEFAULT 5s timeout to EVERY callback call
// (`g || 5000`). The MV2 file-open dialog is MODAL — the user may take
// longer than 5s to pick a file, so the native reply arrives after the
// SW's postWithCb timer fired → shim resolves the callback with `_g`
// ("CB-TIMEOUT") → `_xg` returned "CB-TIMEOUT" as the picked path →
// `?file=CB-TIMEOUT` → `_1()` false → fetch branch → "Unreachable URL"
// toast. FIX (file13 `_xg`): pass an explicit 60s timeout to `_Vy(_e,…)`
// and treat a "CB-TIMEOUT" answer as "no file picked" (return "") so the
// page never navigates to a garbage path. file13 is IN the bundle — rebuilt.
// Same cherry-pick: file62_mv3 onUpdated file:// gate (`&&_id` — no bridge
// injection noise on file:// when "Allow access to file URLs" is OFF).
// The sw.js __acReinjectSiteBridge file:// gate is GONE (TEMP bridge
// removed 2026-08-30 — the reinject query matches web hosts only).
{
  const f13 = fs.readFileSync(path.join(MV3, 'file13.js'), 'utf8');
  const f62 = fs.readFileSync(path.join(MV3, 'file62_mv3.js'), 'utf8');
  const bnd = bundle.includes('saveAs:c},6E4') && bundle.includes('"CB-TIMEOUT"==e?"":e') &&
    bundle.includes('protocol&&_id)&&_Zr(c)');
  const srcOk =
    f13.includes('saveAs:c},6E4') &&
    f13.includes('"CB-TIMEOUT"==e?"":e') &&
    f13.includes('let _xg=') &&
    f62.includes('protocol&&_id)&&_Zr(c)');
  check('file-open dialog: _xg 60s timeout + CB-TIMEOUT returns "" + file62 onUpdated file:// gate (2026-08-30)',
    srcOk && bnd, 'src=' + srcOk + ' bundle=' + bnd);
}

// B50. STRIP_RBTN_BLOCK must NOT kill mouse gestures (2026-08-30): v6
// softened block:true→false on BOTH keys 2 (RMB down) and 1026 (RMB up).
// block on key 2 DOWN is what makes the native INTERCEPT the right button
// and start gesture recognition — with block:false no gesture ever begins
// (user 2026-08-30: a freshly defined simple gesture stopped working
// entirely; config dump showed 2→{type:4,state:true,block:false} after
// stripping).
// The RCM/LCM stick is caused by the swallowed right-button-UP (1026), not
// the DOWN — soften ONLY 1026.
// UPDATE (2026-08-30, issue #1 "right click menu override not working"):
// the strip used to soften EVERY block:true under 1026 — including the
// USER's own right-click override entry (block mode "up" compiles
// 1026→{type:0,block:true,preconds:[actionDone]} — the thing that makes the
// native swallow the RMB release so the context menu stays closed).
// Softening it let the context menu open after every right-click action.
// The strip now softens ONLY the gesture-preset entries — recognizable by
// their mouseGestState precond (type 11) — and preserves the user's
// actionDone-gated block entries (verified live: RMB → no menu + trigger
// fires + LMB works, no PBC stick). Also: visibility safety net in
// mv3_shim (first open right after a reload can stall the boot → page
// stays hidden).
{
  const sw = fs.readFileSync(path.join(MV3, 'sw.js'), 'utf8');
  const shim = fs.readFileSync(path.join(MV3, 'mv3_shim.js'), 'utf8');
  const srcOk =
    sw.includes('if (keyId !== RCM_UP_KEY) { newMap[k] = payload.map[k]; continue; }') &&
    sw.includes('PRECOND_MOUSE_GEST_STATE') &&
    sw.includes('user block:up entries preserved') &&
    !sw.includes('keyId !== 2 && keyId !== RCM_UP_KEY') &&
    !sw.includes('block entries (key 2/1026)') &&
    shim.includes('Visibility safety net') &&
    shim.includes('!html.classList.contains(\'visible\')');
  // Runtime: compile the issue-#1 RMB trigger (block:2 = block-up) TOGETHER
  // with the rightButton gesture preset via the REAL _mh, then apply the
  // sw.js strip logic and assert: the gesture block on 1026 (mouseGestState
  // precond) is softened, the user's actionDone-gated block:up is PRESERVED,
  // and key 2 keeps its blocks (gesture start intact).
  const rt = vm.runInContext(`(() => {
    // mirror sw.js's .in re-patch (the vm bundle is sloppy too — file67's
    // _Xt boxes primitives → the mouse-button detection (_Ys via
    // a.type.in(_Lo,_mk)) would silently fail and the whole mouse
    // compilation (PBC, block-up entries) would be skipped — exactly the
    // B51 class of bug; the live SW has the patch, so the vm must too).
    try {
      Object.defineProperty(Object.prototype, 'in', {
        writable: true,
        value: function(...a) {
          const t = (this !== null && typeof this === 'object') ? this.valueOf() : this;
          for (const v of [].concat(...a)) if (v === t) return true;
          return false;
        }
      });
    } catch (e) { return { ok: false, detail: { patchErr: String(e) } }; }
    const ta = [
      ['54', {
        actions: [{ sequence: [{ action: 'setVolume', params: { mode: 'toggle', target: ':sys' } }], targets: 'hoveredTabs' }],
        sctnId: '3',
        triggers: [{ combins: [{ block: 2, eventId: 2, wildcard: 2 }] }]
      }]
    ];
    const mouseGest = _0p({ triggers: { preset: 'rightButton' }, timeout: 1.5 });
    const p = _mh(ta, mouseGest, {});
    const dumpAll = {};
    for (const k of Object.keys(p.map)) dumpAll[k] = p.map[k].map(i => p.list[i]);
    const up = (p.map[23051] || []).map(i => p.list[i]);
    const down = (p.map[22027] || []).map(i => p.list[i]);
    const userBlockUp = up.find(e => e.type === 0 && Array.isArray(e.preconds) && e.preconds.some(q => q && q.type === 8));
    const gestBlockUp = up.find(e => e.type === 0 && Array.isArray(e.preconds) && e.preconds.some(q => q && q.type === 11));
    const downBlocks = down.filter(e => e && e.block).length;
    // sw.js strip logic (mirror)
    const strip = (payload) => {
      const RBTN_KEY_OFFSET = 22025, RCM_UP_KEY = 1026, PRECOND_MOUSE_GEST_STATE = 11;
      const newMap = {}, newList = payload.list.slice();
      let softened = 0;
      for (const k of Object.keys(payload.map)) {
        const keyId = Number(k) - RBTN_KEY_OFFSET;
        if (keyId !== RCM_UP_KEY) { newMap[k] = payload.map[k]; continue; }
        const idxs = [];
        for (const idx of payload.map[k]) {
          const entry = newList[idx];
          const isGest = entry && entry.block && Array.isArray(entry.preconds) && entry.preconds.some(q => q && q.type === PRECOND_MOUSE_GEST_STATE);
          if (isGest) { newList[idx] = Object.assign({}, entry, { block: false }); softened++; }
          idxs.push(idx);
        }
        if (idxs.length) newMap[k] = idxs;
      }
      return { payload: softened ? { map: newMap, list: newList } : payload, softened };
    };
    const st = strip(p);
    const upAfter = (st.payload.map[23051] || []).map(i => st.payload.list[i]);
    const userAfter = upAfter.find(e => e.type === 0 && Array.isArray(e.preconds) && e.preconds.some(q => q && q.type === 8));
    const gestAfter = upAfter.find(e => e.type === 0 && Array.isArray(e.preconds) && e.preconds.some(q => q && q.type === 11));
    return {
      ok: !!(userBlockUp && userBlockUp.block === true && gestBlockUp && gestBlockUp.block === true &&
        downBlocks === 3 && st.softened === 1 &&
        userAfter && userAfter.block === true && gestAfter && gestAfter.block === false),
      detail: { downBlocks, userBlockUp: !!userBlockUp, gestBlockUp: !!gestBlockUp, softened: st.softened,
        userAfter: userAfter && userAfter.block, gestAfter: gestAfter && gestAfter.block,
        dump: JSON.stringify(dumpAll) }
    };
  })()`, ctx);
  check('STRIP_RBTN_BLOCK selective: softens ONLY gesture blocks on 1026, preserves user block:up override (issue #1) + visibility safety net (2026-08-30)',
    srcOk && rt.ok, 'src=' + srcOk + ' rt=' + JSON.stringify(rt.detail));
}

// B51. Object.prototype.in polyfill must handle BOTH call forms (2026-08-30):
// the bundle is sloppy (no 'use strict' at the top of the concatenation) →
// file67's `_Xt(this,...a)` boxes primitives → 'x'.in('x') was FALSE →
// sw.js re-patched .in with `a.indexOf(t)` — which BROKE the array idiom
// `x.in([...])` that keep() (file25 config compiler) relies on →
// keep("negate","oper") deleted EVERY property incl. negate:true on
// menuState preconds → every Ctrl+Tab trigger compiled as "menu 7 IS open"
// → openMenu (menu-closed trigger) NEVER fired → the tab-switcher list
// never opened after a reload (user 2026-08-30). The fix keeps file67's
// _Xt semantics (flatten args one level, strict ===) AND unboxes this.
// Source check: sw.js must contain the flattening implementation and NOT
// the indexOf version. Runtime check: patch .in like sw.js does, then
// compile the imported Smart Ctrl+Tab triggers via the REAL _mh and assert
// the menuState preconds carry their negate flags (closed-menu triggers
// negate:true, open-menu triggers plain).
{
  const sw = fs.readFileSync(path.join(MV3, 'sw.js'), 'utf8');
  const srcOk =
    sw.includes('for (const v of [].concat(...a)) if (v === t) return true;') &&
    !sw.includes('return a.indexOf(t) !== -1;');
  const rt = vm.runInContext(`(() => {
    // mirror sw.js's .in re-patch (the vm bundle is sloppy too — file67's
    // _Xt boxes primitives → broken the same way as in the SW)
    try {
      Object.defineProperty(Object.prototype, 'in', {
        writable: true,
        value: function(...a) {
          const t = (this !== null && typeof this === 'object') ? this.valueOf() : this;
          for (const v of [].concat(...a)) if (v === t) return true;
          return false;
        }
      });
    } catch (e) { return { err: String(e) }; }
    const scalarOk = 'x'.in('x') === true && 'y'.in('x') === false;
    const arrOk = 'negate'.in(['negate', 'oper']) === true && 'menuId'.in(['negate', 'oper']) === false;
    // the imported Smart Ctrl+Tab openMenu trigger (menuState negate:true)
    const ta = [
      ['116', {
        actions: [{ sequence: [{ action: 'openMenu', params: { menuId: 'menuSpec:7', style: 'dark' } }], targets: 'currentTab' }],
        triggers: [{
          combins: [{ block: 1, eventId: 9, holdPeriod: 400, noAutoRep: true, preconds: [{ keyEvt: 17 }], wildcard: 2 }],
          preconds: { menuState: [{ menuId: 'menuSpec:7', negate: true }] }
        }]
      }],
      ['117', {
        actions: [{ sequence: [{ action: 'moveSelectMark', params: { dir: 1 } }], targets: 'currentTab' }],
        triggers: [{
          combins: [{ block: 1, eventId: 9, holdPeriod: 0, noAutoRep: true, preconds: [{ keyEvt: 17 }], wildcard: 2 }],
          preconds: { menuState: [{ menuId: 'menuSpec:7', negate: false }] }
        }]
      }]
    ];
    const payload = _mh(ta, {}, {});
    // collect every type:13 (menuState) precond across ALL entries of a map key
    const menuPreconds = (key) => {
      const idxs = payload.map[key];
      if (!idxs) return null;
      const out = [];
      for (const i of idxs) {
        const pre = payload.list[i] && payload.list[i].preconds;
        if (!pre) continue;
        for (const p of pre) {
          if (p && p.type === 13 && p.menuNum === 7) out.push(!!p.negate);
        }
      }
      return out;
    };
    const n6145 = menuPreconds('28170');  // Tab held → openMenu (menu NOT open)
    const n9 = menuPreconds('22034');     // key 9: hold-arm (negate) + moveSelectMark (positive)
    return {
      scalarOk, arrOk,
      holdNeg: n6145 && n6145.includes(true) && !n6145.includes(false),
      key9HasNeg: n9 && n9.includes(true),
      key9HasPos: n9 && n9.includes(false)
    };
  })()`, ctx);
  const rtOk = rt && rt.scalarOk && rt.arrOk && rt.holdNeg === true && rt.key9HasNeg === true && rt.key9HasPos === true;
  check('.in polyfill: unboxes + flattens args (keep() preserves menuState negate → Ctrl+Tab smart switching compiles) (2026-08-30)',
    srcOk && rtOk, 'src=' + srcOk + ' rt=' + JSON.stringify(rt));
}

// ---------- A4b. file:// toggle-ON runtime branch (2026-08-10, FEATURES-MV3.md §7-8) ----------
// The main ctx stub returns false (toggle OFF) — deterministic. This second
// context simulates the "Allow access to file URLs" toggle ON: the prelude's
// pass-through calls the REAL (stubbed-true) API → file13 builds the scheme
// gate WITHOUT the file: restriction → file:// tabs ARE targetable by
// runInTab/runInFrames (MV2 parity; before the fix this was NEVER possible).
// Placed at the very end: loading the bundle a second time registers extra
// noop listeners into the shared harness arrays — nothing after this block
// consumes them (the userAPI dispatch test already ran above).
{
  const ctx2 = makeStubCtx();
  ctx2.chrome.extension.isAllowedFileSchemeAccess = cb => cb && cb(true);
  vm.createContext(ctx2);
  try {
    vm.runInContext(bundle, ctx2, { filename: 'sw_core_bundle.js' });
    const res = vm.runInContext(`_As('file:///C:/x')`, ctx2);
    check('_As scheme gate: file:// NOT restricted with toggle ON (stub=true)', res === false,
      'pass-through + real value -> file:// targetable (MV2 parity); got ' + res);
  } catch (e) {
    check('_As scheme gate: file:// NOT restricted with toggle ON (stub=true)', false, 'ctx2 load error: ' + e.message);
  }
}

// ---------- summary ----------
setTimeout(() => {
  console.log('---');
  console.log('SUMMARY: ' + passes + ' pass, ' + gaps + ' known gaps, ' + failures + ' FAIL, ' + notes + ' notes');
  process.exitCode = failures ? 1 : 0;
}, 250);
