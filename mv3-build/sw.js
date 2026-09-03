/**
 * AutoControl MV3 Service Worker — BRAIN
 *
 * In MV3 the extension must work WITHOUT the options page being open, so the
 * legacy core engine (config chain, window enumeration, z[750] trigger
 * execution) runs INSIDE this service worker. The core scripts are imported
 * via importScripts() after a small DOM shim (sw_prelude.js).
 *
 * Key responsibilities:
 * 1. Connect to native .exe component (riched.autocontrol)
 * 2. Run the handshake (10→20→67) and the in-SW config chain (→ type 60/21)
 * 3. Execute triggers (z[750]) directly in this worker
 * 4. Forward native messages to the settings page for UI-only updates
 * 5. Keep connection alive with retry logic + self-waker
 */
(() => {
  'use strict';

  // ======== LOGGING ========
  // §N references in comments point to Docs/FEATURES-MV3.md (feature status
  // & port gaps).
  /**
   * MV2-like silent console: SW diagnostics OFF by default (MV2 wrote
   * NOTHING to the console), enabled via Options → Advanced Options →
   * "Log service worker" (advOpts.logSw), live via storage.onChanged;
   * console.error stays. The patch runs BEFORE importScripts, so sw_prelude
   * + bundle logs are covered too. Startup output is buffered until the
   * async advOpts read resolves, then flushed (or discarded) and the final
   * sink is installed — with the flag off, NOT A SINGLE startup line appears.
   */
  const __acOrigConsole = {
    log: console.log.bind(console),
    info: console.info.bind(console),
    warn: console.warn.bind(console),
    debug: console.debug.bind(console)
  };
  let AC_LOG_SW = false;       // MV2-like silence default; corrected by the read below
  let __acLogBuf = [];         // captured startup output (until the flag is known)
  let __acLogApplied = false;  // storage read resolved → flush + final sinks
  function __acEmitLog(m, args) { try { __acOrigConsole[m].apply(console, args); } catch (e) {} }
  /**
   * Apply the current AC_LOG_SW flag to the console methods and flush the
   * buffered startup output (runs after the async advOpts read resolves).
   */
  function __acApplyLogging() {
    if (!__acLogApplied) return; // still buffering
    const on = AC_LOG_SW;
    for (const m of ['log', 'info', 'warn', 'debug']) {
      try { console[m] = on ? __acOrigConsole[m] : function(){}; } catch (e) {}
    }
    if (__acLogBuf) {
      const buf = __acLogBuf; __acLogBuf = null;
      if (on) for (const [m, args] of buf) __acEmitLog(m, args);
    }
  }
  // Buffer-mode patch — runs BEFORE importScripts, so sw_prelude + bundle
  // init logs are captured too.
  for (const m of ['log', 'info', 'warn', 'debug']) {
    try {
      console[m] = function () {
        try { __acLogBuf.push([m, Array.prototype.slice.call(arguments)]); if (__acLogBuf.length > 400) __acLogBuf.shift(); } catch (e) {}
      };
    } catch (e) {}
  }
  try {
    chrome.storage.local.get("advOpts", r => {
      AC_LOG_SW = !!(r && r.advOpts && r.advOpts.logSw);
      __acLogApplied = true;
      __acApplyLogging();
    });
  } catch (e) { __acLogApplied = true; __acApplyLogging(); }
  try {
    chrome.storage.onChanged.addListener((changes, area) => {
      if (area === "local" && changes.advOpts) {
        AC_LOG_SW = !!((changes.advOpts.newValue || {}).logSw);
        __acApplyLogging();
      }
    });
  } catch(e) {}
  // Safety net: if the read never resolves, stop buffering (keeps current flag).
  setTimeout(() => { if (!__acLogApplied) { __acLogApplied = true; __acApplyLogging(); } }, 500);

  // AC-MV3 DIAG (2026-08-05): SW session start — distinguishes a fresh SW
  // instance from a long-lived one in the [AC-SW] state log (degradation
  // across script runs correlates with SW restarts).
  const __acSwStart = Date.now();
  let __acLastHeal = 0;

  // AC-MV3 DIAG (2026-08-05): SW state snapshot, attached to EVERY
  // execUserFunc response so the PAGE console shows it (no SW console
  // needed): up=SW session age (s, resets on SW restart), conn/hs=native
  // connection+handshake, if=_if.binSwtch present (config chain ran),
  // ek=trigger map size.
  /**
   * SW session state snapshot, attached to every execUserFunc response so the
   * page console can diagnose without the SW console.
   * @returns {{up:number, conn:boolean, hs:boolean, if:string, ek:number}}
   *   up=SW age (s), conn/hs=native connection+handshake, if=binSwtch present,
   *   ek=trigger map size.
   */
  function __acStateDump() {
    let ifOk = false, ek = 0;
    try { ifOk = !!(typeof _if === 'object' && _if && _if.binSwtch); } catch(e) {}
    try { ek = _ek ? Object.keys(_ek).length : 0; } catch(e) {}
    return { up: Math.round((Date.now() - __acSwStart) / 1000), conn: !!connected, hs: !!handshakeDone, if: ifOk ? 'ok' : 'EMPTY', ek };
  }

  // ======== RIGHT-CLICK FIX (v6+v7) ========
  // RCM/LCM bug on Chrome 150: the gesture preset compiles block:true under
  // keys 2 and 1026 → the native swallowed the right-button-up → the next
  // left click was read as a rocker combo (globally blocked until a manual
  // right click). v6 softens those blocks (stripRightButtonBlocks below),
  // v7 sends a synthetic Esc after a gesture (scheduleGestureEsc) to close
  // the stray context menu. Full chronology: Docs/archive/RIGHT-CLICK-ISSUE.md.
  //
  // AC-MV3 FIX (2026-08-30): v6 softened BOTH keys 2 and 1026 — that KILLED
  // mouse gestures: block:true on key 2 (right-button DOWN) is what makes the
  // native INTERCEPT the right button and start gesture recognition; with
  // block:false no gesture ever begins (user 2026-08-30: a freshly defined
  // simple gesture stopped working entirely; config dump showed
  // 2→{type:4,state:true,block:false} after stripping). The RCM/LCM bug is
  // caused by the swallowed right-button-UP (1026), not the DOWN — soften
  // ONLY 1026 and leave key 2's block intact.
  const STRIP_RBTN_BLOCK = true; // ← flip to false to send the original config

  // Softens right-button block entries in a type 60 payload (v6, updated
  // 2026-08-30): key 1026 (right-button-up) carries the gesture preset's
  // end entries with block:true — while the gesture is in state S and the
  // action in D, the native swallows the right-button-up. Softening ONLY
  // the UP key lets the release reach the native's state machine (fixing
  // the RCM/LCM stick) WITHOUT disabling gesture start (key 2 DOWN keeps
  // its block so the native still intercepts the right button). Details:
  // Docs/archive/RIGHT-CLICK-ISSUE.md.
  /**
   * Soften the right-button-UP block entries (v6, RCM/LCM fix; key 2 DOWN is
   * deliberately left intact — its block:true is what starts gesture
   * recognition): for key 1026 every entry with block:true gets block:false,
   * so the native always sees the right-button release and never sticks its
   * pressed-button state.
   * @param {object} payload — type-60 config payload
   * @returns {object} payload with softened blocks (or the original unchanged)
   */
  function stripRightButtonBlocks(payload) {
    if (!payload || typeof payload !== 'object' || !payload.map || !payload.list) return payload;
    const RBTN_KEY_OFFSET = 22025; // mapKey = keyId + 22025 (native trigger id base)
    const RCM_UP_KEY = 1026;       // right-button-up eventId (2 | _mk)
    let softened = 0;
    const newMap = {};
    const newList = payload.list.slice();
    for (const k of Object.keys(payload.map)) {
      const keyId = Number(k) - RBTN_KEY_OFFSET;
      if (keyId !== RCM_UP_KEY) { newMap[k] = payload.map[k]; continue; }
      const idxs = [];
      for (const idx of payload.map[k]) {
        const entry = newList[idx];
        if (entry && entry.block) {
          // Keep the entry (gesture end entries are REQUIRED for the user's
          // gesture trigger to work), but drop the pass-through block so the
          // native's button-state machine sees the right-button release.
          newList[idx] = Object.assign({}, entry, { block: false });
          softened++;
        }
        idxs.push(idx);
      }
      if (idxs.length) newMap[k] = idxs; // key may now be empty → omit entirely
    }
    if (softened) {
      console.log("[AC-MV3] STRIP_RBTN_BLOCK: softened", softened, "block entries (key 1026)");
      return Object.assign({}, payload, { map: newMap, list: newList });
    }
    return payload;
  }

  // ======== POST-GESTURE ESC TAP (v7, closes the stray context menu) ========
  // v6 (soften key 1026's block:true) fixed the left-click stick, BUT the right-button-up now
  // passes through to Chrome → a context menu pops open after every gesture.
  // v7 closes it automatically: shortly after a GESTURE fires (type 750), send
  // a synthetic Esc tap via type 300 (_Dt, SendInput):
  //    payload = [ 27, 1051 ]   (Esc down, Esc up; VK_ESCAPE=27, _mk=1024)
  // The native runs SendInput → Chrome receives VK_ESCAPE → the stray context
  // menu closes. Harmless if no menu is open.
  //
  // GESTURE DETECTION: we must NOT fire Esc after every trigger (hotkeys etc.)
  // — that would close user dialogs. Two signals identify a gesture:
  //   1. type 750 with `mouseGest` (native's own gesture marker), OR
  //   2. a type 760 (raw gesture action stream) seen within GESTURE_WINDOW_MS
  //      before the 750 — type 760 only flows while a gesture is being
  //      recognized, so it is a reliable gesture fingerprint.
  //
  // v5 (RCM+Esc synth) is REPLACED: a synthetic RCM click would land INSIDE
  // the just-opened context menu and activate a menu item — bad. Esc only.
  const RBTN_ESC_ENABLE = true;     // flip false to disable v7
  const RBTN_ESC_DELAY_MS = 20;   // delay after gesture fire (menu opens ~instantly; 20ms is safe)
  const GESTURE_WINDOW_MS = 2000;  // a 750 preceded by 760 within this window counts as a gesture
  let lastRaw760Time = 0;          // ts of the most recent type 760 (gesture stream)
  let escTimer = null;

  // ============ AC-CAPTURE heal (type 40 watchdog, 2026-08-09) ============
  // While ANY capture mode (type 40) is ON, the native streams raw 760s and
  // SUPPRESSES all 750 triggers — a lost/raced OFF leaves it stuck (gestures,
  // hotkeys and RMB die). Staged heal: 0→1 re-send type 40 false twice (the
  // two modes are tracked separately); 1→2 port drop → fresh engine; 2→3 SW
  // reload. Fast page-gone release when the last settings page closes while
  // armed. RECORDING GATE: never heal while the page armed capture (human
  // typing in the combo editor looks exactly like a flood). ROOT CAUSE of
  // "OFF never worked": postMsg coalesced `false || {}` → the OFF reached
  // the native as {} — fixed in postMsg (falsy-preserving).
  // Details: Docs/NATIVE_PROTOCOL.md §4.
  let __acCaptureT = 0;            // ts of the last type-40 sent (any source)
  let __acCaptureOn = false;       // last type-40 payload was truthy (capture armed — a recording may be in progress)
  let __acRaw760 = 0;              // consecutive 760s since the last 750 / type 40 / heal
  let __acRaw760Start = 0;         // ts of the first 760 in the current streak
  let __acCaptureStage = 0;        // 0=idle 1=OFF sent 2=reconnect issued 3=SW reload issued
  let __acCaptureHealAt = 0;       // next escalation time (stage 1/2)
  let __acExtPagesOpen = 0;        // open chrome-extension:// tabs (settings page)
  const AC_CAPTURE_HEAL_EVENTS = 10;       // page-open: ≥10 raw events in a streak (wheel spam is 30+/s)
  const AC_CAPTURE_HEAL_STREAK = 8000;     // page-open: streak older than this = stuck (deliberate recordings are denser or shorter)
  const AC_CAPTURE_HEAL_GRACE = 15000;     // page-open: no toggle for this long = nobody recording
  const AC_CAPTURE_HEAL_EVENTS_NOPAGE = 6; // page-closed: nobody can record without the settings page
  const AC_CAPTURE_HEAL_STREAK_NOPAGE = 3000;
  const AC_CAPTURE_HEAL_GRACE_NOPAGE = 3000;
  // Stale-armed release threshold (2026-08-30): an armed capture with NO 750
  // for this long is treated as a dead editor/test session and released.
  // 60s was too aggressive — the gesture tester (file30) re-arms ONLY on a
  // window focus event, so a >60s pause mid-testing released the capture and
  // the next draw was NOT recorded (user 2026-08-30 D-15: "line draws but
  // the gesture is not recorded" — first draw fine, after a pause nothing).
  // 5 min keeps the heal for genuinely stuck sessions (the user's original
  // stuck-capture episodes lasted hours) without cutting a thinking pause.
  const AC_CAPTURE_STALE_ARMED_MS = 300000;
  /**
   * Release a stuck native capture mode: send type 40 false twice (the two
   * capture modes — event / gesture — are tracked separately) and arm the
   * next escalation stage.
   * @param {string} reason — log reason
   * @param {number} [stage] — stage to set after the release (default 1)
   */
  function __acCaptureRelease(reason, stage) {
    try {
      console.warn(`[AC-CAPTURE] ${reason} — sending type 40 OFF (stage ${stage || 1})`);
      postMsg(40, false);
      // The native tracks the two capture modes (event / gesture) separately
      // (NATIVE_PROTOCOL.md §4: "Both modes can be active simultaneously") —
      // send false twice so both are cleared even if false only clears one.
      setTimeout(() => { try { postMsg(40, false); } catch(e) {} }, 60);
    } catch(e) {}
    __acCaptureOn = false;
    __acRaw760 = 0;
    __acRaw760Start = 0;
    __acCaptureStage = stage || 1;
    __acCaptureHealAt = Date.now() + 8000;
  }
  /**
   * Count open extension pages; if the LAST settings page closes while
   * capture is armed, release capture immediately (nobody can finish a
   * recording without the editor UI).
   */
  function __acCheckExtPages() {
    try {
      chrome.tabs.query({ url: [`chrome-extension://${chrome.runtime.id}/*`] }, tabs => {
        __acExtPagesOpen = (tabs || []).length;
        if (__acExtPagesOpen === 0 && __acCaptureOn && __acCaptureStage === 0) {
          __acCaptureRelease("last settings page closed while capture armed", 1);
        }
      });
    } catch(e) {}
  }

  /**
   * v7 RCM fix: shortly after a gesture fires, send a synthetic Esc tap
   * (type 300, [27, 1051]) to close the stray context menu opened by the
   * now-passing right-button-up.
   */
  function scheduleGestureEsc() {
    if (!RBTN_ESC_ENABLE) return;
    if (escTimer) clearTimeout(escTimer);
    escTimer = setTimeout(() => {
      escTimer = null;
      const ESC_DOWN = 27;    // 27 | _Lo(0)
      const ESC_UP   = 1051;  // 27 | _mk(1024)
      const payload = [ESC_DOWN, ESC_UP];
      try {
        // _Dt = 300 (SendInput), defined in the bundle's global lexical env.
        postMsg(_Dt, payload);
        console.warn("[AC-MV3] RBTN-ESC: sent synth [Esc-down,Esc-up]", JSON.stringify(payload));
      } catch(e) {
        console.warn("[AC-MV3] RBTN-ESC failed:", e.message);
      }
    }, RBTN_ESC_DELAY_MS);
  }

  // Timestamp of type 21 (startup) — used to measure when the trigger pipeline
  // becomes live (first type 750). "Hotkeys don't work right after startup"
  // usually means the first press happened inside this window.
  let startupSentTime = 0;
  let first750Time = 0;

  // ======== CORE ENGINE (SW-BRAIN) ========
  // All core scripts are bundled into ONE file and imported with a single
  // importScripts call. This is REQUIRED: Chrome does not share top-level
  // let/const/class declarations between SEPARATE importScripts calls (only
  // var/function declarations survive on the global object), which would
  // break the core engine (_we/_cg/_Yk/_Tj/_Ti/... are all const/let).
  // A single script evaluation gives the same semantics as main.html's
  // <script> tags (shared global lexical environment).
  //
  // Regenerate sw_core_bundle.js after editing any core file:
  //   $f=@('sw_prelude.js','file67.js','file91.js','file10.js','file32.js','file17.js','file13.js','file34_mv3.js','file56.js','file57.js','file74.js','file47.js','file73.js','file70.js','file25.js','file8.js','file95.js','file15.js','file48.js','file37.js','file3.js','file24.js','file18.js','file41.js','file45.js','file50.js','file52.js','file59.js','file89.js','file93.js','file62_mv3.js','mv3_native_shim.js','file26.js','file49.js'); $o=foreach($x in $f){";`n/* ===== $x ===== */`n"+(Get-Content -Raw $x)}; Set-Content sw_core_bundle.js $o -Encoding utf8 -NoNewline
  // NOTE: file26.js (menu renderer) + file49.js (saveUrl) come LAST — they use
  // _cu/_Lk from mv3_native_shim.js. Deliberately NOT bundled (page/content
  // script only): file2/file30/file36/file75/file78*/file87/file0/file12 (UI),
  // file42/file43 (injected into tabs), file23.html (eval sandbox),
  // file53.js (playAudio — needs speechSynthesis), file77.js (userAPI page bridge).
  try {
    importScripts("sw_core_bundle.js");
    console.log("[AC-MV3] ✓ Core bundle loaded");
  } catch(e) {
    console.error("[AC-MV3] ✗ Core bundle load failed:", e.message);
  }

  // AC-MV3 FIX (2026-08-02, round 10): ACtl.switchState crashes with
  // "_if.binSwtch is not iterable" when the user has no binary switches —
  // _if = customEntities (set by _6s) and binSwtch key is absent → for..of
  // over undefined. Guarantee a default [] at the _Qj conversion point
  // (single choke point for all storage loads; _if/switchState read it).
  // Round 18 (2026-08-04) CRITICAL REGRESSION FIX: the round-17 "post-
  // conversion guard" fabricated `customEntities = {}` into ANY storage-read
  // result. _Mi() (batched write used by ACtl.var/pubVar/switchState saves)
  // writes the WHOLE read object back via _bd(), so an invented empty
  // customEntities WIPED all saved scripts/triggers/gestures from storage —
  // symptom: "script disappeared from settings after refresh" (runScript
  // returned OK instantly, _zs() → ""). Now: fill binSwtch ONLY inside an
  // already-present customEntities, never fabricate the key itself.
  if (typeof _Qj === 'function') {
    const __acOrigQj = _Qj;
    _Qj = function(a) {
      const r = __acOrigQj(a);
      try {
        if (r && r.customEntities && !r.customEntities.binSwtch) {
          r.customEntities.binSwtch = [];
        }
      } catch(e) {}
      return r;
    };
  }

  // AC-MV3 FIX (2026-08-29, site bridge): MV2 re-injected the webSettgs
  // bridge into ALREADY-OPEN site tabs after the config load
  // (`_zg({url:"*://www.autocontrol.app/*"})(c=>c.forEach(d=>_Zr(d.id)))`
  // in file62.js). The MV3 port (file62_mv3.js) lost that block — a tab
  // opened BEFORE the SW started (or before an extension reload) never
  // fires tabs.onUpdated "complete" again → Import/View stayed dead on
  // open pages even though the hostname gate matched. Re-inject at SW
  // start for both site hosts (mirror pages under /AutoControl_mv3/).
  // _Zr is a bundle global (top-level function declaration) — free
  // variable access from sw.js, same pattern as _Qj above.
  function __acReinjectSiteBridge() {
    if (typeof _Zr !== 'function') { console.error('[AC-SITE] reinject: _Zr not found'); return; }
    try {
      // file:// is NOT bridged (MV2 never supported it; needs the "Allow
      // access to file URLs" toggle to inject — the site bridge is for the
      // web hosts only). TEMP file:// bridge removed 2026-08-30.
      chrome.tabs.query({ url: ['*://www.autocontrol.app/*', '*://alex-302.github.io/*'] }, (tabs) => {
        const list = tabs || [];
        console.log('[AC-SITE] reinject: found ' + list.length + ' site tab(s)');
        for (const t of list) {
          try {
            const u = (t && (t.url || t.pendingUrl)) || '';
            if (!u) continue;
            if (u.indexOf('alex-302.github.io') !== -1 && u.indexOf('/AutoControl_mv3/') === -1) continue;
            console.log('[AC-SITE] reinject: tab ' + t.id + ' -> ' + u.slice(0, 120));
            try { _Zr(t.id); } catch (e) { console.error('[AC-SITE] reinject _Zr failed: ' + (e && e.message)); }
          } catch (e) {}
        }
      });
    } catch (e) { console.error('[AC-SITE] reinject query threw: ' + (e && e.message)); }
  }
  __acReinjectSiteBridge();
  // Re-inject a few times after SW start — covers tabs that reloaded after
  // the SW booted (injection is one-shot; onUpdated may have fired while
  // the SW was still starting or the page reloaded later).
  [2000, 6000, 12000].forEach((ms) => {
    setTimeout(() => { try { __acReinjectSiteBridge(); } catch (e) {} }, ms);
  });

  // AC-MV3 FIX (2026-08-29, site bridge Import): the site pages' Import
  // button reaches the SW as {imprtSttgs:<url>} and file48 m() calls
  // window._ja(url). In MV2 _ja lived in file78.js (background page); the
  // MV3 port does NOT bundle file78 (settings-page UI: jQuery, toasts,
  // permission prompts) → window._ja is undefined in the SW → the import
  // silently died (TypeError inside the onMessage listener). The SW bundle
  // DOES contain the whole merge pipeline (_9i storage load / _K dedupe /
  // _4p merge / _bd save / _ku config rebuild + native type 60, plus the
  // fetch shim _1p/_mg), so _ja is re-implemented here with the UI-free
  // parts (download → parse → merge-add → save → rebuild). _kp/_uw/_lj
  // (UI toasts, permission prompts) stay page-side.
  window._ja = _cg(function* (url) {
    const [text, xhr] = yield _mg(_1p(url, 'text'));
    if (!xhr || xhr.status !== 200) {
      console.error('[AC-MV3] site import: fetch failed - ' + url + ' (' + (xhr && xhr.status) + ')');
      return;
    }
    let data;
    try { data = JSON.parse(text); } catch (e) {
      console.error('[AC-MV3] site import: not a valid settings file - ' + url);
      return;
    }
    // AC-MV3 FIX (2026-08-30, site import permissions): MV2 asked for the
    // permissions required by the imported actions BEFORE importing
    // (file78 _lj → _Qk(_xk(a), "permMsgs/impSttgs", true)) — on denial the
    // import was skipped. The SW port skipped that step. The MV3 manifest
    // already grants scripting + <all_urls> (the "script" / site-access
    // perms), but notifications/downloads/bookmarks/sessions are OPTIONAL
    // and must be requested. Re-implement the MV2 _xk logic here (a
    // recursive walk of trigActList looking for action objects):
    //   runScript(!bkgrnd)/sendInput intoPage/copyElemUrl/openElemUrl/
    //   saveElemUrl → <all_urls> (already granted — skip)
    //   saveUrl/saveElemUrl method notif → notifications
    //   saveUrl/saveElemUrl method dwnlApi → downloads
    //   closedTabs trigger → sessions; bmFolder trigger → bookmarks
    const needPerms = [];
    const wantOrigins = [];
    (function walk(v) {
      if (!v || typeof v !== 'object') return;
      if (Array.isArray(v)) { for (const x of v) walk(x); return; }
      if (typeof v.action === 'string') {
        const a = v.action, p = (v.params || {});
        if ((a === 'runScript' && !p.bkgrnd) || (a === 'sendInput' && p.intoPage) ||
            a === 'copyElemUrl' || a === 'openElemUrl' || a === 'saveElemUrl') {
          wantOrigins.push('<all_urls>');
        } else if (a === 'saveUrl' || a === 'saveElemUrl') {
          if (p.method === 'notif') needPerms.push('notifications');
          else if (p.method === 'dwnlApi') needPerms.push('downloads');
        }
        return;
      }
      if (v.type === 'closedTabs') needPerms.push('sessions');
      else if (v.type === 'bmFolder') needPerms.push('bookmarks');
      for (const k in v) walk(v[k]);
    })(data);
    const uniq = (arr) => arr.filter((x, i) => arr.indexOf(x) === i);
    const reqPerms = uniq(needPerms);
    const reqOrigins = uniq(wantOrigins);
    if (reqPerms.length || reqOrigins.length) {
      // chrome.permissions.request: promise-style in MV3 SW, callback-style
      // in some Chrome builds — handle both through the generator's
      // callback-runner (no `yield` of a raw Promise in this codebase).
      const granted = yield (cb) => {
        let done = false;
        const fin = (res) => { if (!done) { done = true; cb(!!res); } };
        try {
          const r = chrome.permissions.request(
            { permissions: reqPerms, origins: reqOrigins },
            (res) => { if (res !== undefined) fin(res); }
          );
          if (r && typeof r.then === 'function') r.then((res) => fin(res), () => fin(false));
          else if (r === undefined && !done) setTimeout(() => fin(false), 3000);
        } catch (e) { fin(false); }
      };
      if (!granted) {
        console.warn('[AC-MV3] site import: permission(s) denied — import skipped (' +
          reqPerms.join(',') + ' ' + reqOrigins.join(',') + ')');
        return;
      }
    }
    const _2d = { trigActList: [], customEntities: {}, toolbarBtns: {}, sections: [] };
    const merged = _Qj({}.add(_2d, data));
    _9i(_2d, (l) => {
      try {
        _K(l, merged, true, true);       // dedupe/renumber imported entities (MV2 _uw)
        const out = _4p(l, merged, false); // merge-add into existing settings
        _bd(out, () => { _ku(() => {}); }); // save + rebuild config → native type 60
        console.log('[AC-MV3] site import: settings imported from ' + url);
        // MV2 parity: on a site import the settings page opened (+ toast).
        // The toast machinery (_u/_Rg/_lj) is page-side (file78, not in the
        // SW bundle) — give visible feedback from the SW instead: a
        // notification + open/focus the settings page.
        try {
          chrome.notifications.create('acImportOk', {
            type: 'basic',
            iconUrl: 'AutoCtrl/logo32.png',
            title: 'AutoControl',
            message: 'Settings imported successfully.'
          });
        } catch (e) {}
        try {
          const optsUrl = chrome.runtime.getURL('main.html');
          chrome.tabs.query({ url: optsUrl }, (tabs) => {
            if (tabs && tabs[0]) { chrome.tabs.update(tabs[0].id, { active: true }); }
            else { chrome.tabs.create({ url: optsUrl }); }
          });
        } catch (e) {}
      } catch (e) {
        console.error('[AC-MV3] site import: merge failed - ' + (e && e.message));
      }
    });
  });

  // ZERO-PROXY BUILD (2026-08-03): the native host chain is
  // AutoControlZero.exe (proxy/launcher, host manifest path) -> spawns
  // AutoCtrl_2025.4.22.0.exe (the real engine) from %LocalAppData%\AutoControl\
  // with arg "152". Verified: the full exe crashes with a C++ exception when
  // launched directly (no Zero), so Zero is REQUIRED. _F (NH0-update,
  // file93.js) refreshes Zero itself from file69.dat - keep it active.

  // AC-MV3 FIX (2026-08-02, round 12): ACtl.import / getFile('module') uses
  // dynamic import(blobUrl) in the USER_SCRIPT world. The world's DEFAULT
  // CSP is the ISOLATED-world CSP (script-src 'self' 'wasm-unsafe-eval'
  // ...chrome-extension://..., NO blob:) — so blob: module loads were
  // rejected even on pages without their own CSP (info.cern.ch). Relax the
  // default USER_SCRIPT world CSP once to allow blob:/data: (needed for
  // import and z-bundle evals). configureWorld is per-extension, one call.
  let __acWorldConfigured = false;
  /**
   * Relax the USER_SCRIPT world CSP once (per extension) to allow blob:/data:
   * module loads (ACtl.import / getFile('module')).
   */
  function __acEnsureWorld() {
    if (__acWorldConfigured) return;
    __acWorldConfigured = true;
    try {
      if (chrome.userScripts && chrome.userScripts.configureWorld) {
        chrome.userScripts.configureWorld({
          csp: "script-src 'self' 'wasm-unsafe-eval' blob: data:; object-src 'self'"
        }).then(() => console.log("[AC-MV3] userScripts world CSP relaxed (blob:/data: for import)")).catch(e => {
          console.warn("[AC-MV3] configureWorld failed:", e && e.message);
        });
      }
    } catch (e) { console.warn("[AC-MV3] configureWorld threw:", e && e.message); }
  }

  // ======== ACTION QUEUE WATCHDOG (2026-08-02) ========
  // Monitors the action queue (_2y) for stuck items. If no "OK" log for >5s
  // while the queue has items, force-shift the stuck entry and restart.
  // This prevents the "queue freeze" bug where runScript promise never resolves.
  if (typeof _2y !== 'undefined' && typeof _6y === 'function' && typeof __acLog === 'function') {
    let __acWatchdogTimer = null;
    let __acLastOkTime = Date.now();
    const __acWatchdogInterval = 5000; // 5s timeout

    // Detect [AC-ACT] ... OK by hooking the bundle's __acLog DIRECTLY.
    // NOT console.warn: the async logging patch (__acApplyLogging — advOpts
    // storage read) REPLACES console.warn after this block, which silently
    // killed the old console.warn hook → __acLastOkTime froze at SW start →
    // spurious "Queue stuck! ... last OK <start>ms ago → force-shift"
    // dropped LIVE queue items (regression 2026-08-08; user VM 2026-08-09
    // 13:48:06: "Queue stuck! 1 items, last OK 136965ms ago" mid wheel-spin —
    // a skipped tab-switch step). __acLog is a top-level function declaration
    // of the imported bundle (classic script → global object property), so
    // reassigning it here is seen by every bundle call site.
    const _origActLog = __acLog;
    __acLog = function (t, m) {
      if (t === 'OK') __acLastOkTime = Date.now();
      return _origActLog(t, m);
    };

    /**
     * Action-queue watchdog tick: if the queue has items and no action
     * completed (OK marker) within the interval, force-shift the stuck entry.
     */
    function __acWatchdogCheck() {
      if (typeof _2y === 'undefined') {
        __acWatchdogTimer = null;
        return;
      }
      const queueLen = _2y.length;
      if (queueLen > 0 && Date.now() - __acLastOkTime > __acWatchdogInterval) {
        console.warn(`[AC-WATCHDOG] Queue stuck! ${queueLen} items, last OK ${Date.now()-__acLastOkTime}ms ago → force-shift`);
        try {
          _2y.shift();
          // Restart queue processing
          _6y();
        } catch(e) {
          console.error('[AC-WATCHDOG] Force-shift failed:', e.message);
        }
      }
      __acWatchdogTimer = setTimeout(__acWatchdogCheck, 2000);
    }
    __acWatchdogTimer = setTimeout(__acWatchdogCheck, 2000);
    console.log('[AC-MV3] ✓ Action queue watchdog armed (5s timeout)');
  }

  // ======== MENU / TOOLBAR-BUTTON SUPPORT ========
  // file26.js (menu renderer _Bp/_Jj/_8o path) is loaded via the bundle now,
  // but its icon pipeline (_Fh/_zr/_Ve) relies on Image/DOM-canvas which do
  // not exist in a service worker. Re-implement with fetch/OffscreenCanvas:
  //   - _Fh (icon → data URI) — callback-style, gif fallback on failure
  //   - _zr (image loader) — fetch + createImageBitmap
  //   - _Ve (canvas factory) — OffscreenCanvas
  // Also: MV3 renamed the toolbar-button context menu context from
  // "browser_action" to "action" — file47 _nk() still uses the old name, so
  // the toolbar context menus never appeared. Patch create() to translate it.
  if (typeof _Fh === 'function') {
    _Fh = (d, b, c, f) => (cb, err) => {
      fetch(d).then(r => r.blob()).then(blob => new Promise((res, rej) => {
        const fr = new FileReader();
        fr.onload = () => res(fr.result);
        fr.onerror = rej;
        fr.readAsDataURL(blob);
      })).then(uri => cb(uri))
        .catch(() => cb("data:image/gif;base64,R0lGODlhAQABAAAAACwAAAAAAQABAAA="));
    };
  }
  if (typeof _zr === 'function') {
    _zr = (d, b, c) => (f, a) => {
      fetch(d, { mode: 'cors' }).then(r => r.blob()).then(blob => createImageBitmap(blob))
        .then(bmp => f(bmp))
        .catch(e => a ? a(Object.assign(Error("Failed to load image"), { fullUrl: d })) : f(null));
    };
  }
  if (typeof _Ve === 'function') {
    _Ve = (d, b, c) => {
      const f = new OffscreenCanvas(d || 1, b || 1);
      if (c) { const a = f.getContext('2d'); a.fillStyle = c; a.fillRect(0, 0, d, b); }
      return f;
    };
  }
  // _ij(a,b): fetch a → blob → b(objectURL). URL.createObjectURL is NOT
  // available in this SW, so pass through data URIs (from our _Fh patch) and
  // convert blobs to data URIs via FileReader (callback-style).
  if (typeof _ij === 'function') {
    _ij = (a, b) => {
      if (typeof a === 'string' && /^data:/i.test(a)) { b(a); return; }
      _1p(a, 'blob')(c => {
        if (!c) { b(void 0); return; }
        const fr = new FileReader();
        fr.onload = () => b(fr.result);
        fr.onerror = () => b(void 0);
        fr.readAsDataURL(c);
      });
    };
  }
  if (chrome.contextMenus && chrome.contextMenus.create) {
    const origCtxCreate = chrome.contextMenus.create.bind(chrome.contextMenus);
    const origCtxRemoveAll = chrome.contextMenus.removeAll.bind(chrome.contextMenus);
    chrome.contextMenus.create = (props, cb) => {
      if (props && Array.isArray(props.contexts)) {
        props.contexts = props.contexts.map(x => x === 'browser_action' ? 'action' : x);
      }
      // AC-MV3 FIX (2026-08-07): the SW creates the "Emergency repair" item
      // at startup (file47.js `_nk()` only runs on the settings page, so
      // after an extension reload the menu is gone until the page opens).
      // Once the SW owns it, skip duplicates from the page.
      if (props && props.id === 'reloadExtn' && self.__acCtxMenuOwned) return 0;
      return origCtxCreate(props, cb);
    };
    // AC-MV3 FIX (2026-08-08): file47.js `_nk()` calls contextMenus.removeAll()
    // on EVERY config-chain run (SW leader) — that deleted the SW-created
    // "Emergency repair" item, and the create patch above skipped recreating
    // it → the menu item vanished until the extension reloaded (user VM
    // 00:18). Recreate the item after any removeAll while the SW owns it.
    chrome.contextMenus.removeAll = (cb) => {
      origCtxRemoveAll(() => {
        if (self.__acCtxMenuOwned) {
          try {
            // MUST use origCtxCreate here — the patched create() returns 0
            // for reloadExtn while __acCtxMenuOwned (duplicate filter), which
            // would silently DROP the recreation → the menu item vanished
            // after every config-chain removeAll (user 2026-08-12).
            origCtxCreate(
              { id: "reloadExtn", title: "Emergency repair", contexts: ["action"] },
              () => {}
            );
          } catch(e) { console.warn("[AC-MV3] Emergency-repair menu recreate failed:", e.message); }
        }
        cb && cb();
      });
    };
    console.log("[AC-MV3] contextMenus.create patched: browser_action → action");
  }

  // ======== FIX Object.prototype .in POLYFILL ========
  // file67 defines .in as _Xt(this, ...a) with STRICT comparison (a === c).
  // In the sloppy-mode bundle, `this` of a method called on a primitive gets
  // BOXED (new String('x')), so 'x'.in('x') returned FALSE for everything.
  // (In main.html it worked because file67's own 'use strict' directive made
  // that script strict → no boxing.) This silently broke _fr (variant), _eh
  // isDownUp checks, and config compilation (spurious entries). Re-patch with
  // unboxing + indexOf so .in works in sloppy mode.
  // AC-MV3 FIX (2026-08-30): the indexOf version broke the bundle's ARRAY
  // idiom `x.in([...])` — keep() (file25 config compiler) calls `b.in(a)`
  // with a = the keep-list ARRAY; indexOf on the args array never matched →
  // keep("negate","oper") deleted EVERY property, incl. `negate:true` on
  // menuState preconds → every Ctrl+Tab trigger compiled as "menu 7 IS
  // open" → openMenu (needs menu closed) NEVER fired → the tab-switcher
  // list never opened after a reload (user 2026-08-30). Fix: keep file67's
  // _Xt semantics (flatten args one level via [].concat, strict ===) and
  // ADD the unboxing.
  try {
    // file67 defined 'in' via defineProperties → configurable:false (default),
    // but writable:true — so we can redefine the VALUE without configurable.
    Object.defineProperty(Object.prototype, 'in', {
      writable: true,
      value: function(...a) {
        const t = (this !== null && typeof this === 'object') ? this.valueOf() : this;
        for (const v of [].concat(...a)) if (v === t) return true;
        return false;
      }
    });
    console.log("[AC-MV3] .in polyfill re-patched → 'x'.in('x') =", "x".in("x"),
      "| 'y'.in('x') =", "y".in("x"),
      "| 'negate'.in(['negate','oper']) =", "negate".in(["negate", "oper"]));
  } catch(e) {
    console.warn("[AC-MV3] .in patch failed:", e.message);
  }

  // ======== GESTURE-DIRECTION ICONS (type _Xa=90) ========
  // The native shows the gesture trail/direction arrows using the icons sent
  // in type 90. The original pipeline (file3 _Ke/_l/_dd + file32 _zi/_Xi/_Hk)
  // needs canvas + fonts, so here it is re-implemented for the SW with
  // OffscreenCanvas + FontFace + FileReader (no DOM, no eval).
  /**
   * Draw a text glyph on an OffscreenCanvas (icon pipeline helper).
   * @param {string} text — glyph text
   * @param {string} font — CSS font shorthand (e.g. "16px/1 gestureDirs")
   * @param {string} color — fill color
   * @returns {OffscreenCanvas}
   */
  function swZi(text, font, color) {
    const c = new OffscreenCanvas(1, 1);
    const e = c.getContext('2d');
    e.font = font;
    const w = e.measureText(text || ' ').width;
    const h = parseInt(font, 10) || 16;
    c.width = Math.max(1, Math.ceil(w));
    c.height = h;
    const ctx = c.getContext('2d');
    ctx.font = font;
    ctx.fillStyle = color;
    ctx.textBaseline = 'top';
    ctx.fillText(text || ' ', 0, 0);
    return c;
  }

  /**
   * Apply a list of canvas effects (resize/margin/shadow/background/corner
   * radius) to an OffscreenCanvas.
   * @param {OffscreenCanvas} d — source canvas
   * @param {Array<object>} effects — effect descriptors
   * @returns {Promise<OffscreenCanvas>}
   */
  async function swXi(d, effects) {
    for (const eff of effects) {
      if (!eff) continue;
      const b = new OffscreenCanvas(d.width, d.height);
      const e = b.getContext('2d');
      if (eff.resize) {
        let f = Array.isArray(eff.resize) ? eff.resize : String(eff.resize).trim().split(/\s+/);
        if (f.length === 1) f[1] = f[0];
        let a = +f[0] || parseFloat(f[0]) * b.width / 100;
        f = +f[1] || parseFloat(f[1]) * b.height / 100;
        b.width = Math.abs(a);
        b.height = Math.abs(f);
        e.scale(a / b.width, f / b.height);
        e.drawImage(d, a < 0 ? a : 0, f < 0 ? f : 0, b.width, b.height);
      } else if (eff.background) {
        e.fillStyle = eff.background;
        e.fillRect(0, 0, b.width, b.height);
        e.drawImage(d, 0, 0);
      } else if (eff.margin) {
        const a = String(eff.margin).trim().split(/\s+/);
        if (a.length === 1) a[1] = a[0];
        if (a.length === 2) a[2] = a[0];
        if (a.length === 3) a[3] = a[1];
        b.width += +a[1] + +a[3];
        b.height += +a[0] + +a[2];
        e.drawImage(d, +a[3], +a[0]);
      } else if (eff.shadow) {
        const a = String(eff.shadow).trim().split(/\s+/, 4);
        e.shadowOffsetX = +a[0];
        e.shadowOffsetY = +a[1];
        e.shadowBlur = +a[2];
        e.shadowColor = a[3];
        e.drawImage(d, 0, 0);
      } else if (eff.cornerRadius) {
        const r = String(eff.cornerRadius).trim().split(/\s+/);
        if (r.length === 1) r[1] = r[0];
        // Rounded-rect mask via canvas path — createImageBitmap can't decode SVG
        e.drawImage(d, 0, 0);
        e.globalCompositeOperation = 'destination-in';
        e.beginPath();
        e.roundRect(0, 0, b.width, b.height,
          [parseFloat(r[0]) * b.width / 100, parseFloat(r[1]) * b.height / 100]);
        e.fill();
      }
      d = b;
    }
    return d;
  }

  /**
   * Convert an OffscreenCanvas to a base64 PNG string.
   * @param {OffscreenCanvas} c
   * @returns {Promise<string>} base64 PNG without the data: prefix
   */
  function swHk(c) {
    return c.convertToBlob({ type: 'image/png' }).then(blob => new Promise((res, rej) => {
      const fr = new FileReader();
      fr.onload = () => res(String(fr.result).replace(/^data:image\/png;base64,/, ''));
      fr.onerror = rej;
      fr.readAsDataURL(blob);
    }));
  }

  /**
   * Generate the 8 gesture-direction icons plus the translucent v/x status
   * icons (MV2 look) as base64 PNG strings.
   * @param {number} size — icon size in px
   * @param {string} color — glyph color
   * @returns {Promise<string[]>} icon data (base64 PNG)
   */
  async function swGenGestureIcons(size, color) {
    // Load the gestureDirs font (digit/arrow glyphs) — fallback to default font
    try {
      const ff = new FontFace('gestureDirs', 'url(' + chrome.runtime.getURL('res/gestureDirs.woff2') + ')');
      await ff.load();
      if (self.fonts && self.fonts.add) { try { self.fonts.add(ff); } catch(e) {} }
    } catch(e) {
      console.warn("[AC-MV3] gestureDirs font load failed:", e.message, "— using fallback font");
    }
    const icons = [];
    for (let d = 1; d <= 8; ++d) {
      let c = swZi(String(d), size + 'px/1 gestureDirs', color);
      c = await swXi(c, [{ margin: '3 0' }, { shadow: '2 2 4 rgba(0,0,0,.4)' }]);
      icons.push(await swHk(c));
    }
    const aSize = Math.round(0.77 * size);
    const r = Math.round(0.82 * size);
    const e2 = Math.round(size / 40);
    // AC-MV3 FIX (2026-08-08): match MV2's semi-transparent status icons
    // (file3 _dd): the GLYPH is drawn in the translucent status color and the
    // backing is a faint gray — NOT a solid dark glyph on a bright green/red
    // disc (that looked "garish" vs MV2's soft translucent look). The status
    // colors are slightly MORE transparent than MV2's .7 (user request
    // 2026-08-08: "make the red and green a bit more transparent") — .3 is the
    // user-tuned value (visually less intrusive).
    let v = swZi('v', aSize + 'px/1 gestureDirs', 'rgba(0,255,0,.3)');
    v = await swXi(v, [
      { resize: r },
      { margin: Math.round((1 - 0.82) * size) },
      { shadow: e2 + ' ' + e2 + ' 3 rgba(0,0,0,.7)' },
      { background: 'rgba(200,200,200, 0.2)' },
      { cornerRadius: '50%' }
    ]);
    icons.push(await swHk(v));
    let x = swZi('x', aSize + 'px/1 gestureDirs', 'rgba(255,0,0,.3)');
    x = await swXi(x, [
      { resize: r },
      { margin: Math.round((1 - 0.82) * size) },
      { shadow: e2 + ' ' + e2 + ' 3 rgba(0,0,0,.7)' },
      { background: 'rgba(200,200,200, 0.2)' },
      { cornerRadius: '50%' }
    ]);
    icons.push(await swHk(x));
    return icons;
  }

  // Display-config icons (type _Xa) — re-implemented for the SW (see above).
  // Original protocol preserved: {icons: [...base64...], ...display, colors}.
  if (typeof _6t === 'function') {
    _6t = (b = {}) => {
      const colors = b.colors === 'dark'
        ? { color: 'white', bgColor: 2130706432 }
        : { color: '#555555', bgColor: 2147483647 };
      const send = icons => {
        try { _Lk(_Xa, Object.assign({ icons }, b, colors)); }
        catch(e) { console.warn("[AC-MV3] _6t send error:", e); }
      };
      if (!b.enabled) { send([]); return; }
      swGenGestureIcons(b.size || 30, colors.color)
        .then(send)
        .catch(e => {
          console.warn("[AC-MV3] _6t icon generation failed:", e.message);
          send([]);
        });
    };
  }

  // ======== RUN SCRIPT (background mode) — OFFSCREEN SANDBOX ========
  // file48.js `_A`/`_xj(0)` → `e()` creates `<iframe id=BGScript src="file23.html">`
  // (sandbox page, `unsafe-eval` allowed by manifest sandbox CSP) and sends the
  // script via postMessage. The SW has no DOM, so `_Uu` is replaced by a proxy
  // whose iframe lives in the offscreen document (offscreen.html): SW postMessage
  // → runtime.sendMessage{sandboxPost} → offscreen → iframe; results come back
  // via {sandboxMessage} → __acDispatchSandboxMessage → file48's "message" handler.
  let _acOffscreenPromise = null;
  let _acBgIframeOnload = null;

  /**
   * Ensure the offscreen document exists (created once; reused on errors).
   * @returns {Promise<void>}
   */
  function _acEnsureOffscreen() {
    if (!_acOffscreenPromise) {
      const create = (reasons) => chrome.offscreen.createDocument({
        url: "offscreen.html",
        reasons,
        // DOM_SCRAPING: available since Chrome 109 (our minimum). IFRAME_SCRIPTING
        // is only Chrome 116+; DOM_SCRAPING covers creating DOM nodes incl. iframes.
        // AUDIO_PLAYBACK (Chrome 116+): the offscreen doc plays playAudio sounds
        // (FEATURES-MV3.md §7-1) — the reason also exempts it from autoplay restrictions.
        justification: "Run Script actions execute user JS in a sandboxed iframe (file23.html); playAudio actions play sounds (file53 engine)"
      });
      _acOffscreenPromise = create(["DOM_SCRAPING", "AUDIO_PLAYBACK"]).catch(e => {
        // "Only a single offscreen document may be created" — fine, reuse it.
        const m = String(e && e.message || e).toLowerCase();
        if (m.includes("already")) return;
        if (m.includes("reason") || m.includes("invalid")) {
          // AUDIO_PLAYBACK is Chrome 116+ — unknown reason throws on older
          // Chrome; fall back to DOM_SCRAPING only (audio may still play).
          return create(["DOM_SCRAPING"]).catch(e2 => {
            if (!String(e2 && e2.message || e2).toLowerCase().includes("already")) {
              console.warn("[AC-MV3] offscreen create failed:", e2 && e2.message || e2);
            }
          });
        }
        console.warn("[AC-MV3] offscreen create failed:", e && e.message || e);
      });
    }
    return _acOffscreenPromise;
  }

  // Replace _Uu (used by file48 e()) with a proxy fragment: .children[0] is a
  // fake iframe whose contentWindow.postMessage forwards to the offscreen
  // document's real sandbox iframe. `onload` fires once the offscreen iframe
  // is confirmed ready (file48 e() yields on it before posting the script).
  // Only the BGScript iframe case is intercepted; other _Uu callers (file95:
  // `_Uu(g).querySelectorAll`) still get the original template behavior.
  if (typeof _Uu === 'function') {
    const _origUu = _Uu;
    _Uu = (html) => {
      if (typeof html === 'string' && html.includes('BGScript')) {
        const fakeIframe = {
          set onload(cb) { _acBgIframeOnload = cb; },
          contentWindow: {
            postMessage: (data) => {
              _acEnsureOffscreen().then(() => {
                try {
                  chrome.runtime.sendMessage({ cmd: "sandboxPost", data })
                    .then(r => {
                      // iframe ready → resume file48's yield (onload callback)
                      if (r && r.ok && _acBgIframeOnload) {
                        const cb = _acBgIframeOnload;
                        _acBgIframeOnload = null;
                        cb();
                      }
                    })
                    .catch(() => {});
                } catch(e) { /* ignore */ }
              });
            }
          }
        };
        return { children: [fakeIframe] };
      }
      return _origUu(html);
    };
  }

  // ======== playAudio (FEATURES-MV3.md §7-1) — route through the offscreen document ========
  // The bundle's _7r lazy-loads file53.js via a script tag — a NO-OP in the
  // SW (inert DOM shim) → the action hung the chain AND the queue; file53
  // also needs AudioContext/speechSynthesis (no worker APIs). playAudio is
  // intercepted at the LOOKUP — file37 _rf reads every action through _w(name,
  // params), a writable bundle global; _Du is DEEP-FROZEN, so patching
  // _Du.action.playAudio.value throws. The offscreen document loads the REAL
  // file53.js engine + polyfills; voice text templates are pre-expanded here;
  // the action completes immediately (MV2 semantics).
  // Details: Docs/FEATURES-MV3.md §7-1.
  try {
    if (typeof _w === "function") {
      const __acOrigW = _w;
      _w = function (a, b) {
        if (a === "playAudio") {
          // Same runner signature as the original _7r(b,d,a,c):
          // (tabGroups, done, params, runId) — complete the action
          // immediately (MV2 semantics), play in the offscreen doc.
          return (tabGroups, done, params, runId) => {
            try { __acPlayAudio(tabGroups, params, runId); }
            catch (e) { console.warn("[AC-AUDIO] _w wrapper failed:", e && e.message || e); }
            done(tabGroups);
          };
        }
        return __acOrigW(a, b);
      };
      console.warn("[AC-AUDIO] playAudio routed to the offscreen document via _w wrapper (file53.js engine, FEATURES-MV3.md §7-1)");
    }
  } catch (e) {
    console.warn("[AC-AUDIO] playAudio patch failed:", e && e.message || e);
  }
  let __acAudioSeq = 0;
  /**
   * Expand a voice-text template (angle-bracket syntax) to plain text using
   * the bundle's template machinery; plain strings pass through unchanged.
   * @param {object} params — playAudio params (text, usesTabs)
   * @param {Array} tabGroups — target tabs for <title>/<url> templates
   * @param {function(string):void} cb — callback with the expanded text
   */
  function __acVoiceText(params, tabGroups, cb) {
    // Plain text (no template object) — fast path, no bundle machinery.
    if (!params || typeof params.text !== "object" || params.text === null) {
      cb(params && typeof params.text === "string" ? params.text : "");
      return;
    }
    let tabs;
    try {
      tabs = (params.usesTabs && typeof _qd === "function") ? (_qd(tabGroups) || []) : [0];
    } catch (e) { tabs = [0]; }
    let out = "";
    const next = (i) => {
      if (i >= tabs.length) { cb(out); return; }
      const l = tabs[i];
      let called = false;
      const settle = (txt) => {
        if (called) return;
        called = true;
        try { out += (txt || []).join("\n"); } catch (e) {}
        next(i + 1);
      };
      try {
        const tmpl = _Tt(params.text || "");
        const runner = _ai(0, _up, tmpl, _Yp[l]);
        // Safety: a template referencing clipboard/selection/etc. drains the
        // _Lw queue asynchronously — never wedge the voice path on a hang.
        const t = setTimeout(() => settle([]), 4000);
        runner((lines) => { clearTimeout(t); settle(lines); });
      } catch (e) { settle([]); }
    };
    next(0);
  }
  /**
   * Send a playAudio command to the offscreen document via runtime message.
   * @param {object} msg — {cmd:"playAudio", seq, tabGroups, runId, params}
   */
  function __acSendPlayAudio(msg) {
    _acEnsureOffscreen().then(() => {
      try {
        chrome.runtime.sendMessage(msg).then((r) => {
          if (!r || !r.ok) console.warn("[AC-AUDIO] offscreen playAudio failed:", (r && r.error) || r);
        }).catch((e) => console.warn("[AC-AUDIO] sendMessage failed:", e && e.message || e));
      } catch (e) {
        console.warn("[AC-AUDIO] sendMessage threw:", e && e.message || e);
      }
    }).catch((e) => console.warn("[AC-AUDIO] offscreen unavailable:", e && e.message || e));
  }
  /**
   * Route a playAudio action to the offscreen document (MV2 semantics: the
   * action completes immediately; the sound plays in the offscreen doc).
   * @param {Array} tabGroups
   * @param {object} params — playAudio action params
   * @param {number} [runId]
   */
  function __acPlayAudio(tabGroups, params, runId) {
    const p = params || {};
    const send = (prms) => __acSendPlayAudio({
      cmd: "playAudio",
      seq: ++__acAudioSeq,
      tabGroups: tabGroups || [],
      runId: runId || 0,
      params: prms
    });
    if (p.type === "voice") {
      // Fresh copy — never mutate the trigger-config params object (shared
      // across runs until the next config rebuild).
      __acVoiceText(p, tabGroups, (text) => {
        send(Object.assign({}, p, { text: text || "", usesTabs: false }));
      });
    } else {
      send(p);
    }
  }

  const NATIVE_HOST = "hrich.autocontrol";
  const MAX_RECONNECT_DELAY = 8000;

  let port = null, connected = false, connectTime = 0, portConnectedOk = false;
  let retries = 0, errors = 0, reconnectTimer = null;

  // _Sk captured at handshake — daily offset native uses to encode trigger IDs
  let handshakeSk = 0;
  // Tracks whether type 21 (startup) has been sent (must run AFTER config chain)
  let startupSent = false;
  // AC-MV3 FIX (2026-08-10, `_Wo(_Vs)`): "On startup" event fired once
  // per SW session (MV2 file61.js D(): `!G++ && !_nt("noStupEvt")` → _Wo(_Vs)).
  let __acStartupEvtSent = false;
  // Tracks whether type 72 (switch states) has been sent for the current handshake
  let type72Sent = false;
  // True once SW finished 10→20→67 (only then may the config chain / type 21 run)
  let handshakeDone = false;
  // Monotonic sequence counter for deduplicating broadcast messages in the shim
  let broadcastSeq = 0;
  // Engine auto-install: unpack file76.dat only ONCE per SW session. After the
  // unpack the engine file exists; a fresh Zero (via reconnect) starts it.
  let __acEngineUnpackAttempted = false;
  // AC-MV3 FIX (2026-08-07): deploy counter — the native installer
  // (Reinstall/Repair) DELETES the engine file, so a re-deploy must be
  // allowed after an earlier deploy this session; the cap prevents an
  // infinite deploy loop if something keeps removing the file (antivirus).
  let __acEngineDeploys = 0;
  // Connection generation — bumped on every connect(). Async callbacks
  // (postWithCb timeouts, onDisc, handshake chains) belonging to SUPERSEDED
  // ports must never act on the current connection: a stale type-10 timeout
  // used to fire onConnError, which killed the healthy port and started a
  // reconnect cascade (each new Zero spawns a duplicate engine → file check
  // stays 2 forever until a reload).
  let __acConnGen = 0;
  // True while a connect/handshake is in flight — page-driven reconnects must
  // NOT spawn a duplicate host mid-handshake (2026-08-06, orphan-engine fix:
  // every connectNative starts a new Zero→engine pair).
  let __acConnecting = false;
  // AC-MV3 FIX (2026-08-07): fresh-install auto-reload. Chrome CACHES a
  // failed "Specified native messaging host not found" lookup PER SW
  // INSTANCE — after the user installs the native from the install UI, the
  // same SW keeps failing connectNative until the extension reloads (the
  // reinstall path works because the SW connected once before — no cache).
  // The install UI (file2.js m(Infinity,1000)) pings type 920 every second;
  // count consecutive "native not ready" answers while the port is DEAD (a
  // live port with connected=false means Zero is up and the engine is
  // deploying — that must NEVER be interrupted). After 20 such pings, reload
  // the extension once; the fresh SW finds the host and the settings page
  // reopens automatically (see __acInstallAutoReload in proceedAfterFileCheck).
  let __acNotReadyPings = 0;
  let __acInstallAutoReloaded = false;
  // AC-MV3 FIX (2026-08-07): the native host has connected AT LEAST ONCE in
  // this SW session. Used to stop the auto-reconnect loop after an uninstall
  // (or when the host was never installed): if the host NEVER connected and
  // connectNative keeps failing, retrying forever is useless (the uninstall
  // case — user VM 18:15: gens 2-50+ "host not found" with no end). We stop
  // after __acMaxNeverConnectedFailures and wait for a page-driven reconnect
  // (install UI z() → {cmd:"reconnect"}) or an extension reload instead.
  let __acEverConnected = false;
  const __acMaxNeverConnectedFailures = 8;

  // Buffer for native messages — replay to pages that connect late
  let nativeMsgBuffer = [];
  const MAX_BUFFER_SIZE = 100;

  // ======== CONNECTION MANAGEMENT ========

  /**
   * Open the native messaging port (bumps the connection generation and
   * starts the handshake).
   */
  function connect() {
    cleanup();
    __acConnGen++;
    __acConnecting = true;
    const gen = __acConnGen;
    console.log("[AC-MV3] Connecting to native host:", NATIVE_HOST, "(gen " + gen + ")");
    try {
      port = chrome.runtime.connectNative(NATIVE_HOST);
      port.onMessage.addListener(onMsg);
      port.onDisconnect.addListener(() => {
        // AC-MV3 FIX (2026-08-08): consume the disconnect reason — Chrome
        // logs "Unchecked runtime.lastError: Native host has exited." (and
        // "Specified native messaging host not found" on a failed
        // connectNative) if the onDisconnect callback never reads
        // chrome.runtime.lastError. Both are EXPECTED here: the host exits
        // during Emergency Repair (we taskkill the engine and drop the port)
        // and when the host is not installed.
        void chrome.runtime.lastError;
        onDisc(gen);
      });
      portConnectedOk = false;
      if (chrome.runtime.lastError) {
        console.warn("[AC-MV3] Connect error:", chrome.runtime.lastError.message);
        scheduleRetry();
      } else {
        console.log("[AC-MV3] Port created, starting handshake...");
        doHandshake(gen);
      }
    } catch(e) {
      console.error("[AC-MV3] Connect exception:", e.message);
      scheduleRetry();
    }
  }

  function cleanup() {
    if (reconnectTimer) { clearTimeout(reconnectTimer); reconnectTimer = null; }
    if (port) { try { port.disconnect(); } catch(e) {} port = null; }
    connected = false;
    __acConnecting = false;
  }

  /**
   * Send monitor info to native (type 67 = _Ma).
   * Matches original _iy() in file70.js:
   *   _Lk(_Ma, [..._9j._Zw].map(([,b])=>_il(_df(b.bounds)).add({dpi:b.dpiX})), a)
   * where _df(bounds)={x:left,y:top,w:width,h:height} and _il(rect)={x:x+w/2,y:y+h/2}.
   * So each entry = {x:centerX, y:centerY, dpi:dpiX}.
   *
   * Must run in SW because chrome.system.display is only available here.
   */
  function sendMonitorInfo() {
    return new Promise(resolve => {
      if (!chrome.system || !chrome.system.display) {
        console.warn("[AC-MV3] chrome.system.display not available, sending empty monitors");
        postMsg(67, []);
        resolve();
        return;
      }
      // AC-MV3 FIX (2026-08-10): populate the bundle's monitor map _Zw via
      // file13 _Sf (MV2 called it at startup; the SW never did — only the
      // onDisplayChanged path via file62_mv3 did). _Fo/_Lh/_Uk/_Kg (the
      // file71.html popups) and monitor-based actions read _Zw for
      // positioning — with an empty map the no-hook notice popup crashed
      // ("Cannot read properties of undefined (reading 'workArea')", VM
      // 2026-08-10) and the user got no feedback at all (z[800], FEATURES-MV3.md §7-4).
      try { if (typeof _Sf === "function") _Sf(() => {}); }
      catch (e) { console.warn("[AC-MV3] _Sf (_Zw populate) error:", e); }
      chrome.system.display.getInfo(displays => {
        try {
          const monitors = displays.filter(d => d.isEnabled).map(d => {
            const b = d.bounds || {};
            // _df: {x:left, y:top, w:width, h:height}; _il: center point
            const x = (b.left || 0) + (b.width || 0) / 2;
            const y = (b.top || 0) + (b.height || 0) / 2;
            return { x, y, dpi: d.dpiX || 96 };
          });
          console.log("[AC-MV3] Sending monitor info (type 67):", monitors.length, "displays");
          postMsg(67, monitors);
        } catch(e) {
          console.warn("[AC-MV3] Monitor info error:", e);
          postMsg(67, []);
        }
        resolve();
      });
    });
  }

  /**
   * Schedule the next reconnect attempt with exponential backoff (capped at
   * MAX_RECONNECT_DELAY); stops permanently when the host never connected and
   * the failure cap is reached.
   */
  function scheduleRetry() {
    cleanup();
    const delay = Math.min(MAX_RECONNECT_DELAY,
      Math.pow(Math.max(retries, errors) + 1, 0.4) * 1000);
    reconnectTimer = setTimeout(connect, delay);
  }

  // AC-MV3 FIX (2026-08-03): engine auto-install — MV2 (file61.js generator D)
  // unpacked the bundled engine file76.dat when the file check answered 2
  // ("AutoCtrl_2025.4.22.0.exe not found") and wrote it into the host folder
  // via the running native (type 250, chunked; the Zero proxy handles it).
  // The port dropped that branch, so the engine had to be copied by hand
  // (README S2.1 step 4). Restored here.
  //
  // Stale processes: every reconnect spawns a new Zero -> new engine; the old
  // engine processes can linger and CRASH the fresh one on type 140
  // (ACCESS_VIOLATION 0xC0000005). Before unpacking we taskkill all engine
  // processes so the freshly written engine runs alone.
  /**
   * Unpack the bundled engine (file76.dat) and write it into the host folder
   * via native type 250 (chunked write). Never deletes files and never
   * hard-kills the engine — only taskkills stale engine processes.
   * @returns {Promise<void>}
   */
  function unpackBundledEngine() {
    return new Promise(resolve => {
      try {
        if (typeof _3t !== 'function' || typeof _4u !== 'function') {
          console.warn("[AC-MV3] unpackBundledEngine: _3t/_4u not available in bundle");
          resolve(false);
          return;
        }
        const url = chrome.runtime.getURL("file76.dat");
        const write = () => {
          // _3t(url, "binary") reads the bundled file76.dat and DECRYPTS it
          // (file13 _7g .dat byte-shift) - returns the raw engine bytes.
          _3t(url, "binary")(data => {
            if (!data) { console.warn("[AC-MV3] file76.dat read failed"); resolve(false); return; }
            // _4u writes in chunks (type 250); result 0 = success (MV2 _F).
            _4u("AutoCtrl_2025.4.22.0.exe", data)(res => {
              const ok = (res === 0 || res === false || res === undefined || res === null);
              console.log("[AC-MV3] Engine write result:", res, "->", ok ? "OK" : "FAILED");
              resolve(ok);
            });
          });
        };
        const runCmd = (cmd, cb) => {
          if (typeof _iw !== 'function') { cb(); return; }
          try { _iw(cmd)(() => cb()); } catch(e) { cb(); }
        };
        // Kill lingering engine processes (they crash the fresh one on 140).
        // IMPORTANT (2026-08-04): NO "del /Q /F AutoCtrl_*.exe" here! The
        // native answers type 260 as soon as cmd.exe STARTS (~7ms), NOT when
        // the command finishes — so del runs ASYNC and can delete the freshly
        // written engine right after write() ("file flashed and vanished"
        // symptom: engine started, host exited, then file check stayed 2).
        // The type-250 write overwrites any existing file anyway.
        runCmd("taskkill /F /IM AutoCtrl_2025.4.22.0.exe", () => {
          setTimeout(() => write(), 500);
        });
      } catch(e) {
        console.warn("[AC-MV3] unpackBundledEngine error:", e.message);
        resolve(false);
      }
    });
  }

  // AC-MV3 FIX (2026-08-07): does the engine FILE exist on disk? The file
  // check answer 2 means "missing OR still starting" — this disambiguates via
  // the running Zero (type 260 `if exist`, getStdout; cmd CWD == the engine
  // data dir, verified by the [AC-DIAG] listing). resolve(true) when the
  // check cannot run — the caller then keeps the poll/give-up path.
  /**
   * Disambiguate the file-check answer 2 ("missing OR still starting"): ask
   * the native shell whether the engine file actually exists on disk.
   * @param {number} gen — connection generation (stale ports must not act)
   * @returns {Promise<boolean>} true if the file exists
   */
  function __acEngineFileExists(gen) {
    return new Promise(resolve => {
      if (typeof _iw !== 'function') { resolve(true); return; }
      try {
        _iw('if exist AutoCtrl_2025.4.22.0.exe (echo 1) else (echo 0)', ".", true)(r => {
          if (gen !== __acConnGen) { resolve(false); return; }
          const out = r && r.stdout ? String(r.stdout).trim() : "";
          resolve(out === "1");
        });
      } catch(e) { resolve(true); }
    });
  }

  // AC-MV3 DIAG (2026-08-05): empirically check whether the native engine ever
  // creates .tabs/.sess files (the MV2 forfiles cleanup — FEATURES-MV3.md §7-11 — suggests
  // they can accumulate; none seen on the dev machine so far).
  //
  // v2: uses getStdout (type 260 stdout capture — MV2 file30.js uninstall flow:
  // `_iw("dir /B *.exe", ".", !0)` → a.stdout), so NO temp file and NO _If/type
  // 255 read is involved. Lists BOTH the cmd CWD (to see where cmd actually
  // runs — the v1 temp-file failure suggests cmd CWD != engine data dir) and
  // the engine data dir by ABSOLUTE path (%LOCALAPPDATA%\AutoControl — where
  // settings.dat lives, confirmed on the dev machine). Quoting verified
  // locally: `cmd /S /C "echo [CWD] & dir /b & echo [DATA-DIR] & dir /b
  // "%LOCALAPPDATA%\AutoControl""` parses and lists both.
  // Throttled to once per 5 minutes (no log spam on reconnect loops).
  let __acLastDirDiag = 0;
  const __acDirDiagMinMs = 5 * 60 * 1000;
  /**
   * List the native data folder via type 260 getStdout (diagnostics only,
   * throttled after a successful connect).
   */
  function __acDiagListNativeDir() {
    try {
      const now = Date.now();
      if (now - __acLastDirDiag < __acDirDiagMinMs) return;
      if (typeof _iw !== 'function') {
        console.warn("[AC-DIAG] _iw not available — native folder listing skipped");
        return;
      }
      __acLastDirDiag = now;
      // Show the ACTUAL paths (cmd CWD %CD%, LOCALAPPDATA as seen by the
      // engine) + listings of CWD, the data dir and the LOCALAPPDATA parent —
      // 2026-08-05 finding: the engine's cmd sees 3 files (no settings.dat)
      // while the real %LOCALAPPDATA%\AutoControl has 4 → the engine runs
      // with a different CWD/env than expected.
      _iw('echo [CD]=%CD% & echo [APPDATA]=%LOCALAPPDATA% & echo [CWD] & dir /b & echo [DATA-DIR] & dir /b "%LOCALAPPDATA%\\AutoControl" & echo [PARENT] & dir /b "%LOCALAPPDATA%"', ".", true)(r => {
        try {
          const out = r && r.stdout ? String(r.stdout) : "";
          if (out) {
            console.log("[AC-DIAG] Native folder listing (type 260 stdout):\n" + out);
            // dir /b lines end with CRLF — match per line (the $ anchor alone
            // would never hit: the string ends with \n, not .sess).
            const hasSess = out.split(/\r?\n/).some(l => /\.(tabs|sess)$/i.test(l.trim()));
            console.log("[AC-DIAG] .tabs/.sess present:", hasSess ? "YES" : "no");
          } else {
            console.warn("[AC-DIAG] no stdout in response; raw:", JSON.stringify(r));
          }
        } catch(e) { console.warn("[AC-DIAG] listing log failed:", e.message); }
      });
    } catch(e) {
      console.warn("[AC-DIAG] native folder listing failed:", e.message);
    }
  }

  // AC-MV3 FIX (2026-08-05, FEATURES-MV3.md §7-11): forfiles cleanup of old .tabs/.sess
  // files — port of MV2 file61.js generator D:
  //   !G++ && !_nt("noStupEvt") { for(let c of ["tabs","sess"])
  //   _iw(`forfiles /m *.${c} /d -10 /c "cmd /c del /F /Q @path"`)(); _Wo(_Vs) }
  // The native engine writes these internal session snapshots into its data
  // dir; forfiles deletes only files OLDER THAN 10 days (/d -10) — pure
  // housekeeping. The engine's cmd CWD == the data dir (verified 2026-08-05
  // via the [AC-DIAG] listing), so the bare `*.tabs`/`*.sess` mask hits the
  // right folder.
  // Runs ONCE per SW session (MV2's !G++ counter); skipped when the
  // `noStupEvt` flag is set (MV2 _co sets it right before an update-triggered
  // reload). Fire-and-forget: the native acks type 260 when cmd STARTS — the
  // async del is fine here (nothing depends on the deleted files, unlike the
  // engine-write path where it caused "file flashed and vanished").
  let __acForfilesDone = false;
  /**
   * Clean up session/tab files older than 10 days (forfiles) — once per SW
   * session, skipped on noStupEvt, matching the MV2 behavior.
   */
  function __acForfilesCleanup() {
    if (__acForfilesDone || typeof _iw !== 'function') return;
    __acForfilesDone = true;
    chrome.storage.local.get(["noStupEvt"], items => {
      if (items && items.noStupEvt) {
        console.log("[AC-FORFILES] skipped (noStupEvt set — right after update reload)");
        return;
      }
      try {
        for (const ext of ["tabs", "sess"]) {
          _iw('forfiles /m *.' + ext + ' /d -10 /c "cmd /c del /F /Q @path"')(() => {});
        }
        console.log("[AC-FORFILES] cleanup scheduled: *.tabs / *.sess older than 10 days");
      } catch(e) {
        console.warn("[AC-FORFILES] cleanup failed:", e.message);
      }
    });
  }

  // AC-MV3 FIX (2026-08-06): orphaned-engine cleanup at connect.
  // Every connectNative spawns a NEW Zero→engine pair; a dead SW generation
  // leaves its engine orphaned (detached from Zero, holds global hooks — TWO
  // engine processes after browser start, one lingering after close). Kill
  // ONLY engines whose Zero parent is dead (wmic) — a LIVE pair of another
  // browser must keep working. Runs at handshake start BEFORE the file check
  // (our engine is not spawned yet). Disabling it did NOT fix the reinstall
  // issue (root cause: the installer wipes the engine file —
  // __acEngineFileExists/__acEngineDeploys). Details: AGENTS.md.
  const ORPHAN_KILL_ENABLED = true;
  let __acOrphanScanDone = false;
  /**
   * Kill orphan engine processes whose Zero launcher is dead (wmic scan).
   * Live engine/launcher pairs of other browsers are never touched.
   * @param {number} gen — connection generation guard
   */
  function __acKillOrphanEngines(gen) {
    if (__acOrphanScanDone || typeof _iw !== 'function') return;
    __acOrphanScanDone = true;
    const scan = (name, cb) => {
      try {
        _iw("wmic process where \"name='" + name + "'\" get ProcessId,ParentProcessId /FORMAT:CSV", ".", true)(r => {
          cb(r && r.stdout ? String(r.stdout) : "");
        });
      } catch(e) { cb(""); }
    };
    scan("AutoCtrl_2025.4.22.0.exe", engOut => {
      if (gen !== __acConnGen) return;
      scan("AutoControlZero.exe", zeroOut => {
        if (gen !== __acConnGen) return;
        try {
          // wmic /FORMAT:CSV lines: Node,ProcessId,ParentProcessId
          const zeroPids = new Set();
          for (const line of zeroOut.split(/\r?\n/)) {
            const p = line.trim().split(',');
            if (p.length >= 3 && /^\d+$/.test(p[1])) zeroPids.add(Number(p[1]));
          }
          const orphans = [];
          for (const line of engOut.split(/\r?\n/)) {
            const p = line.trim().split(',');
            if (p.length >= 3 && /^\d+$/.test(p[1]) && !zeroPids.has(Number(p[2]))) {
              orphans.push({ pid: Number(p[1]), parent: Number(p[2]) });
            }
          }
          if (!orphans.length) {
            console.log("[AC-ORPHAN] scan: no orphan engines (all Zero parents alive or none running)");
            return;
          }
          for (const o of orphans) {
            console.warn("[AC-ORPHAN] killing orphan engine pid=" + o.pid +
              " (Zero parent " + o.parent + " is dead)");
            try { _iw("taskkill /F /PID " + o.pid)(() => {}); } catch(e) {}
          }
        } catch(e) {
          console.warn("[AC-ORPHAN] scan failed:", e.message);
        }
      });
    });
  }

  // Success path of doHandshake's file check (10/20/67 -> window enum -> 72 ->
  // config chain -> 21). Extracted so the "engine missing" branch can re-run
  // the check after unpackBundledEngine() and then continue here.
  /**
   * Continue the handshake after the file check: engine deploy/re-deploy,
   * reconnect bookkeeping, config-chain start (with force on reconnect),
   * startup event and repair/install UX flags.
   */
  function proceedAfterFileCheck() {
    // Guard: a second (stale) chain must not re-run the handshake body.
    if (handshakeDone) {
      console.log("[AC-MV3] proceedAfterFileCheck skipped (handshake already done)");
      return;
    }
    portConnectedOk = true;
    connected = true;
    __acConnecting = false;
    __acEverConnected = true;
    connectTime = Date.now();
    retries = 0; errors = 0;
    startupSent = false; // reset for new connection
    type72Sent = false;
    handshakeDone = false;

    // DIAG (2026-08-05): log the native data folder contents on a good connect
    // (fire-and-forget; throttled).
    __acDiagListNativeDir();

    // FIX (2026-08-05, FEATURES-MV3.md §7-11): forfiles cleanup of old .tabs/.sess files
    // (once per SW session).
    __acForfilesCleanup();

    // AC-MV3 FIX (2026-08-07): persist the native-installed flag. MV3 never
    // wrote it (file61.js D() isn't in the bundle) — the settings page reads
    // `natHostInstalled` to decide install-UI vs "Something went wrong"
    // (file2.js `_nd` branch). Without this the install pane would re-appear
    // after every reload even with the native working. Triggers the debounced
    // storage.onChanged config rebuild — harmless (idempotent).
    try { chrome.storage.local.set({ natHostInstalled: true }); } catch(e) {}
    __acNotReadyPings = 0;

    // AC-MV3 FIX (2026-08-08): Emergency Repair completion — the repair
    // RELOADED the SW (the MV2 background-page reload equivalent — see
    // __acEmergencyRestartNative). This FRESH SW just connected; show the
    // MV2 " OK " badge (flag was persisted in storage before the reload).
    // If the native is gone, the flag stays and the next successful connect
    // shows OK — acceptable.
    try {
      chrome.storage.local.get(["__acRepairBadge"], items => {
        if (items && items.__acRepairBadge) {
          chrome.storage.local.remove("__acRepairBadge");
          try {
            chrome.action.setBadgeBackgroundColor({ color: "#0F0" });
            chrome.action.setBadgeText({ text: " OK " });
          } catch(e) {}
          setTimeout(() => { try { chrome.action.setBadgeText({ text: "" }); } catch(e) {} }, 2000);
          console.log("[AC-MV3] Emergency repair complete — badge OK");
        }
      });
    } catch(e) {}

    // AC-MV3 FIX (2026-08-12, FEATURES-MV3.md §7-15): Emergency Repair
    // DIAGNOSTICS — __acEmergencyRestartNative persisted the one-shot
    // showNotif/diagnostics flags here (MV2: background-page localStorage,
    // file34 `_nt("showNotif")` branch). Replicate the MV2 flow with the now
    // working MV3 popup (_Fo → scripting.executeScript, shim): stuck keys →
    // _Kg (REPAIR COMPLETE + wildcard/Ignore-synthetic-input advice), foreign
    // profile → _Ht (window + report advice). Slight delay so the badge
    // settles first; failures are silent (popup is best-effort UX).
    try {
      chrome.storage.local.get(["__acRepairDiag"], items => {
        const d = items && items.__acRepairDiag;
        if (!d) {
          console.warn("[AC-MV3] repair diag: NOT found in storage (badge present, diagnostics missing) — repair ran without showNotif/diagnostics flags (update cycle / non-menu path)?");
          return;
        }
        console.warn("[AC-MV3] repair diag FOUND: show=" + !!d.showNotif + " downKeys=" + ((d.diagnostics && Array.isArray(d.diagnostics.downKeys)) ? d.diagnostics.downKeys.length : "n/a") + " actWinMine=" + (d.diagnostics && d.diagnostics.actWinMine));
        chrome.storage.local.remove("__acRepairDiag");
        const c = d.diagnostics;
        setTimeout(() => {
          try {
            if (!c) { console.warn("[AC-MV3] repair diag: diagnostics payload empty — nothing to show"); return; }
            if (Array.isArray(c.downKeys) && c.downKeys.length) {
              if (typeof _Kg === "function") { console.warn("[AC-MV3] repair diag: showing _Kg with " + c.downKeys.length + " stuck keys"); _Kg(c.downKeys); }
              else console.warn("[AC-MV3] repair diag: _Kg MISSING in bundle");
            } else if (c.actWinMine === 0) {
              console.warn("[AC-MV3] repair diag: foreign profile — showing _Ht");
              const b = c.lastFocusId || c.focusedId || (c.hndlToId && c.hndlToId[c.focusWin]);
              if (typeof _Ht === "function") {
                if (b && typeof _Ms === "function") _Ms(b, true, win => { try { _Ht(win); } catch(e) {} });
                else _Ht(null);
              }
              else console.warn("[AC-MV3] repair diag: _Ht MISSING in bundle");
            } else {
              console.warn("[AC-MV3] repair diag: no stuck keys and own profile (actWinMine=" + c.actWinMine + ") — MV2 shows nothing in this case");
            }
          } catch(e) { console.warn("[AC-MV3] repair diagnostics failed:", e.message); }
        }, 700);
      });
    } catch(e) {}

    // AC-MV3 FIX (2026-08-07): the install flow auto-reloaded the extension
    // (fresh-install host-not-found cache — see the type-920 branch). Reopen
    // the settings page now that the fresh SW connected, so the user lands on
    // the settings instead of a closed install pane. (Emergency Repair does
    // NOT set this flag — it reloads only the open page, MV2 semantics.)
    try {
      chrome.storage.local.get(["__acInstallAutoReload"], items => {
        if (items && items.__acInstallAutoReload) {
          chrome.storage.local.remove("__acInstallAutoReload");
          console.log("[AC-MV3] Install auto-reload pending — opening options page");
          try { chrome.runtime.openOptionsPage(); } catch(e) {}
        }
      });
    } catch(e) {}

    // CRITICAL: Record _Sk (daily offset) at handshake time — same value native uses.
    // Native encodes trigger IDs as triggerIndex + _Sk, so we must capture _Sk here.
    handshakeSk = Date.now() / 864E5 | 0;
    console.log("[AC-MV3] _Sk (daily offset) captured at handshake:", handshakeSk);

    // AC-CAPTURE heal: a fresh engine (escalation reconnect) starts with
    // capture OFF — reset the flood counters and give it 8s to prove itself
    // before the last-resort SW reload.
    if (__acCaptureStage === 2) {
      console.warn("[AC-CAPTURE] fresh engine after reconnect — flood must stop");
      __acRaw760 = 0;
      __acRaw760Start = 0;
      __acCaptureHealAt = Date.now() + 8000;
    }

    // CRITICAL FIX: Handshake order must EXACTLY match original (file61.js generator D):
    //   type 10 → 20 → 67(monitors, _iy) → [WINDOW ENUM _Ry/_oj] → 72 → [CONFIG CHAIN _lr/_Gf → type 60] → 21 (LAST)
    //
    // The SW sends 10/20/67, then broadcasts "nativeConfigReady" to the page.
    // The PAGE runs window enumeration (_Ry/_oj) → sends "windowEnumDone" → SW sends 72.
    // The PAGE then runs config chain (_lr/_Gf → type 60) → sends "configLoaded" → SW sends 21.
    //
    // NOTE: type 67 (monitors) MUST be sent by the SW, not the page/content script,
    // because chrome.system.display.getInfo is only available in the SW context.
    //
    // CRITICAL: Do NOT send type 40! The original never sends type 40 during startup.
    // Type 40 is only sent by _0d() when the user opens a combo editor / gesture tester.
    // Sending type 40 with `true` puts native into raw capture mode, suppressing type 750.

    const cv = (navigator.userAgent.match(/\bchrome\/(\d+)/i) || [0,"0"])[1]|0;
    chrome.storage.local.get(["installTime", "switchStates"], items => {
      const iTime = items.installTime || Date.now()/1E3|0;
      // Original file10 computes _fr by filtering UA tokens via .in(); the
      // bundle evaluated with the BROKEN .in, so _fr is unfiltered garbage.
      // Recompute the variant exactly like the original: filter out the
      // standard UA tokens → [] in modern Chrome.
      const variant = (navigator.userAgent.match(/\w+(?=\/\d+\b)/g) || [])
        .filter(x => !["Mozilla", "AppleWebKit", "Chrome", "Safari", "Version"].includes(x));
      console.log("[AC-MV3] Sending init (type 20), iTime:", iTime, "crVer:", cv, "variant:", JSON.stringify(variant));
      postMsg(20, { iTime, crVer: cv, variant });

      // Small delay for native to process init
      setTimeout(() => {
        // Send monitor info (type 67 = _Ma) — matches original _iy().
        sendMonitorInfo().then(() => {
          // SW handshake is complete (10→20→67): the config chain may now run.
          // SW-BRAIN: dispatch directly to the in-SW core engine (window enum →
          // type 72 → config chain → type 60 → type 21), and also notify the
          // settings page for UI state.
          handshakeDone = true;
          // AC-MV3 FIX (2026-08-07): dispatch with force:true so the bundle's
          // configChainStarted guard (mv3_native_shim.js) is RESET on a
          // reconnect — otherwise the config chain never re-runs after the
          // native reconnects (e.g. after a native reinstall/repair that kills
          // the host): no type 60, no type 21 → the fresh engine never starts
          // emitting triggers (user VM 16:59: engine up but hotkeys dead;
          // log: "Config chain already started, skipping duplicate
          // nativeConfigReady"). force is a no-op on the first handshake.
          __acDispatch({ type: "nativeConfigReady", connected: true, time: connectTime, force: true });
          broadcast({ type: "nativeConfigReady", connected: true, time: connectTime, force: true });
          console.log("[AC-MV3] Running in-SW config chain: window enum → 72 → config → 21");
        });
      }, 50);
    });

    // Keepalive alarm
    chrome.alarms.create("ac-keepalive", { periodInMinutes: 1 });
    startKeepalive();

    // The auto-reload flag is consumed; re-arm it for the next failure episode.
    try { chrome.storage.local.remove("__acAutoReloaded"); } catch(e) {}

    console.log("[AC-MV3] Native connected successfully!");
    // Broadcast nativeConfigReady above (inside the storage.get callback) is the
    // primary signal telling the page to run window enum + config chain.
  }

  // Kill lingering AutoCtrl engine processes via the CURRENT native connection
  // (type 260 cmd). Orphaned engines (from Zeros whose ports died) crash the
  // Zero answers the file check with 2 while the engine is STILL STARTING
  // (even when the engine file is already in place) - the engine needs a
  // moment to come up after Zero spawns it. After the unpack, POLL the file
  // check instead of failing and reconnecting: every reconnect spawns a new
  // Zero -> new engine process, lingering duplicates crash the engine on
  // type 140. Polling gives the engine time and keeps a single process.
  /**
   * Poll the file check until the engine is ready or the attempts run out.
   * @param {number} tries — max attempts
   * @param {number} intervalMs — delay between attempts
   * @param {number} gen — connection generation guard
   * @returns {Promise<boolean>} true when the engine is ready
   */
  function waitForEngineReady(tries, intervalMs, gen) {
    return new Promise(resolve => {
      let n = 0;
      const step = () => {
        if (gen !== __acConnGen) { resolve(false); return; } // superseded port
        n++;
        postWithCb(10, { fileName: "AutoCtrl_2025.4.22.0.exe" }, 9000)
          .then(r2 => {
            if (gen !== __acConnGen) return; // superseded — do not act
            if (r2 !== 2 && r2 !== undefined && r2 !== null && r2 !== "CB-TIMEOUT") {
              console.log("[AC-MV3] Engine ready (file check answer:", r2, ") after", n, "poll(s)");
              resolve(true);
              return;
            }
            if (n >= tries) { resolve(false); return; }
            setTimeout(step, intervalMs);
          })
          .catch(() => {
            if (gen !== __acConnGen) return; // superseded — do not act
            if (n >= tries) { resolve(false); return; }
            setTimeout(step, intervalMs);
          });
      };
      step();
    });
  }

  /**
   * Full handshake: file check (10) → init (20) → monitors (67) → window
   * enum (335/400) → switch states (72) → config chain → startup (21, LAST).
   * @param {number} gen — connection generation
   */
  function doHandshake(gen) {
    console.log("[AC-MV3] Handshake: sending file check (type 10)...");
    // AC-MV3 FIX (2026-08-06): kill orphaned engines from dead SW generations
    // BEFORE our file check spawns the fresh pair (fire-and-forget, gen-guarded).
    // TEMP (2026-08-07): gated by ORPHAN_KILL_ENABLED while testing without it.
    if (ORPHAN_KILL_ENABLED) __acKillOrphanEngines(gen);
    // Send file check first (original protocol)
    postWithCb(10, { fileName: "AutoCtrl_2025.4.22.0.exe" }, 9000)
      .then(r => {
        if (gen !== __acConnGen) return; // superseded connection
        console.log("[AC-MV3] Handshake response:", r);
        if (r === undefined || r === null || r === "CB-TIMEOUT") {
          console.warn("[AC-MV3] File check failed, response:", r);
          onConnError("native not found", gen);
          return;
        }

        // AC-MV3 FIX: engine auto-install (MV2 file61.js D). Answer 2 =
        // engine missing OR still starting. CLEAN FLOW (no del, no nuke, no
        // reload, no reconnect loop): poll → unpack file76.dat once per
        // session (taskkill stale engine processes; NO `del /Q /F` — the
        // native acks type 260 when cmd.exe STARTS, ~7ms) → poll on the SAME
        // port → one clean reconnect → give up with guidance.
        // Details: Docs/FEATURES-MV3.md §7-3.
        if (r === 2) {
          if (!__acEngineUnpackAttempted) {
            console.warn("[AC-MV3] Engine missing/starting (answer 2) — waiting for it to come up");
            waitForEngineReady(3, 1000, gen).then(ready => {
              if (gen !== __acConnGen) return;
              if (ready) { proceedAfterFileCheck(); return; }
              __acEngineUnpackAttempted = true;
              __acEngineDeploys++;
              console.warn("[AC-MV3] Engine not up — unpacking file76.dat → AutoCtrl_2025.4.22.0.exe");
              unpackBundledEngine().then(ok => {
                if (gen !== __acConnGen) return; // superseded
                if (!ok) {
                  console.warn("[AC-MV3] Engine unpack failed — manual copy required (README S2.1 fallback)");
                  onConnError("engine unpack failed", gen);
                  return;
                }
                // Reset retry counters for a fast single reconnect cycle.
                retries = 0; errors = 0;
                console.log("[AC-MV3] Engine written — polling on the same port (MV2 style)");
                waitForEngineReady(5, 1000, gen).then(ready2 => {
                  if (gen !== __acConnGen) return; // superseded
                  if (ready2) { proceedAfterFileCheck(); return; }
                  // Zero may only start the engine at ITS own startup — one
                  // clean reconnect; the fresh Zero finds the file.
                  console.warn("[AC-MV3] Engine written but Zero did not pick it up — clean reconnect");
                  handshakeDone = false;
                  startupSent = false;
                  type72Sent = false;
                  if (port) { try { port.disconnect(); } catch(e) {} port = null; }
                  connected = false;
                  scheduleRetry();
                });
              });
            });
          } else {
            // Unpack already attempted this session — poll patiently, then
            // check whether the engine FILE actually exists: the native
            // installer (Reinstall/Repair) DELETES it, so a re-deploy must
            // be possible even after an earlier deploy this session (user VM
            // 2026-08-07: SW reported "Engine still missing after unpack"
            // right after a reinstall wiped the file). NO onConnError
            // (infinite loop), NO nukeHostTree, NO chrome.runtime.reload.
            waitForEngineReady(5, 1000, gen).then(ready3 => {
              if (gen !== __acConnGen) return;
              if (ready3) { proceedAfterFileCheck(); return; }
              __acEngineFileExists(gen).then(exists => {
                if (gen !== __acConnGen) return; // superseded
                if (!exists && __acEngineDeploys < 2) {
                  // File is gone despite our earlier deploy — the installer
                  // wiped it. Re-deploy (capped: no infinite deploy loop).
                  __acEngineDeploys++;
                  console.warn("[AC-MV3] Engine file missing on disk after earlier deploy — re-unpacking (removed by reinstall?)");
                  console.warn("[AC-MV3] Engine not up — unpacking file76.dat → AutoCtrl_2025.4.22.0.exe");
                  unpackBundledEngine().then(ok => {
                    if (gen !== __acConnGen) return; // superseded
                    if (!ok) {
                      console.warn("[AC-MV3] Engine unpack failed — manual copy required (README S2.1 fallback)");
                      onConnError("engine unpack failed", gen);
                      return;
                    }
                    // Reset retry counters for a fast single reconnect cycle.
                    retries = 0; errors = 0;
                    console.log("[AC-MV3] Engine written — polling on the same port (MV2 style)");
                    waitForEngineReady(5, 1000, gen).then(ready2 => {
                      if (gen !== __acConnGen) return; // superseded
                      if (ready2) { proceedAfterFileCheck(); return; }
                      // Zero may only start the engine at ITS own startup —
                      // one clean reconnect; the fresh Zero finds the file.
                      console.warn("[AC-MV3] Engine written but Zero did not pick it up — clean reconnect");
                      handshakeDone = false;
                      startupSent = false;
                      type72Sent = false;
                      if (port) { try { port.disconnect(); } catch(e) {} port = null; }
                      connected = false;
                      scheduleRetry();
                    });
                  });
                  return;
                }
                console.error("[AC-MV3] Engine still missing after unpack — giving up. Check Task Manager for orphaned AutoCtrl_*.exe / AutoControlZero.exe processes (duplicates crash the fresh engine).");
                console.error("[AC-MV3] Manual fallback: copy AutoControl_native\\AutoCtrl_2025.4.22.0.exe into %UserProfile%\\AppData\\Local\\AutoControl\\ and reload the extension (README S2.1).");
                if (port) { try { port.disconnect(); } catch(e) {} port = null; }
                connected = false;
              });
            });
          }
          return;
        }

        proceedAfterFileCheck();
      })
      .catch(err => {
        if (gen !== __acConnGen) return; // superseded connection — ignore
        console.warn("[AC-MV3] Handshake failed:", err.message);
        onConnError("init failed", gen);
      });
  }

  // Called by the page (via cmd "windowEnumDone") once _Ry/_oj window enumeration completes.
  // Sends type 72 (switch states) — strictly AFTER window enum, matching the original
  // file61.js generator D ordering: window enum → type 72 → config → type 21.
  /**
   * Send the switch states (type 72) for the current handshake (once).
   */
  function sendType72() {
    if (!connected || !handshakeDone || type72Sent) return;
    type72Sent = true;
    chrome.storage.local.get(["switchStates"], items => {
      const states = items.switchStates || {};
      console.log("[AC-MV3] Window enum done — sending switch states (type 72)...");
      postMsg(72, { states });
    });
  }

  // Called by the page (via cmd "configLoaded") once _lr/_Gf config chain is complete.
  // Sends type 21 (startup) — strictly AFTER config, matching the original file61.js
  // generator D ordering: type 10→20→67→[windowEnum]→72→[config chain→type 60]→21 (LAST).
  //
  // CRITICAL: Do NOT send type 40! In the original MV2, type 40 (_Qr) is NEVER sent
  // during startup — it is only sent by _0d() when the user opens a combo editor or
  // gesture tester. Sending type 40 with `true` puts native into "raw capture mode"
  // (type 760 events flow to y callback), which SUPPRESSES normal trigger matching
  // (type 750 events stop). This was the root cause of type 750 never arriving.
  /**
   * Finish startup: fire the "On startup" trigger event once per session
   * (after type 21), matching MV2 semantics.
   */
  function finishStartup() {
    if (!connected || !handshakeDone || startupSent) {
      console.log("[AC-MV3] finishStartup skipped (connected=" + connected + " startupSent=" + startupSent + ")");
      return;
    }
    startupSent = true;
    startupSentTime = Date.now();
    first750Time = 0;
    console.log("[AC-MV3] Config chain done by page — sending type 21 (startup)");

    // Type 21 = startup signal. In original this was the VERY LAST message in handshake.
    // Native starts emitting type 750 trigger events after receiving this.
    postMsg(21, null);

    // AC-MV3 FIX (2026-08-10, `_Wo(_Vs)`): fire the "On startup" trigger
    // event. MV2 file61.js D() called _Wo(_Vs) once per session right after
    // type 21 (`!G++ && !_nt("noStupEvt")`) — this is the "On startup" event
    // (file68.js: [_Vs]:{name:"On startup"}) that users can bind actions to.
    // The port never called it → such triggers NEVER fired. _Wo(c) sends a
    // type-50 event batch to native ONLY when _uk[c] is set (a trigger uses
    // the event) and skips _8o dispatch for _Vs — so the call is a no-op
    // when no startup trigger is configured, and a real trigger otherwise.
    // noStupEvt parity: _co sets it before an update reload (in the SW it is
    // in-memory localStorage — it does not survive chrome.runtime.reload(),
    // so after a repair the event DOES fire; acceptable, even desirable).
    if (!__acStartupEvtSent && !_j("noStupEvt")) {
      __acStartupEvtSent = true;
      try { _Wo(_Vs); }
      catch (e) { console.warn("[AC-MV3] _Wo(_Vs) failed:", e); }
    }

    // No startup config re-send: proven useless (2026-08-02) — the native
    // skips byte-identical configs, and re-registering with block:true does not
    // heal the pass-through. The working fix is STRIP_RBTN_BLOCK above (the
    // sent config matches the fresh-install shape: no type-0/type-4 key-2
    // entries).
  }

  // Settings page saved changes → re-run the in-SW config chain so _ek/_pg/_su
  // stay in sync with what native re-registered (type 60).
  /**
   * Re-run the config chain in the SW (used by the live config rebuild and
   * the auto-heal path).
   */
  function refreshConfigInSW() {
    if (!connected || !handshakeDone) return;
    console.log("[AC-MV3] Config changed by settings page — refreshing in-SW config chain");
    __acDispatch({ type: "nativeConfigReady", connected: true, time: connectTime, force: true });
    broadcast({ type: "nativeConfigReady", connected: true, time: connectTime, force: true });
  }

  /**
   * Native connection error handler (stale-generation safe).
   * @param {string} reason — error description
   * @param {number} gen — connection generation the error belongs to
   */
  function onConnError(reason, gen) {
    if (gen !== undefined && gen !== __acConnGen) return; // stale port — ignore
    connected = false;
    // CRITICAL (2026-08-04): reset the handshake state so a RECONNECT re-runs
    // the FULL handshake (file check → init 20 → 67 → config → 21). Without
    // this the guard in proceedAfterFileCheck skipped the re-init and the
    // restarted engine got NO type 20 → it exited ~1s later ("Native host has
    // exited") — seen in gens 8-10 of the 00:54 log.
    handshakeDone = false;
    startupSent = false;
    type72Sent = false;
    if (port) { try { port.disconnect(); } catch(e) {} port = null; }
    // Verified install path (2026-08-03, README S2.1): the UI installer
    // ("Reinstall native component" twice, second = Repair) deploys
    // AutoControlZero.exe + manifest + the HKCU NativeMessagingHosts registry
    // key (a plain folder copy alone does NOT register the host). The engine
    // AutoCtrl_2025.4.22.0.exe is NOT deployed by the installer - copy it
    // from AutoControl_native by hand, then reload the extension.
    console.warn("[AC-MV3] Native connection failed (" + reason + "). " +
      "Install steps: in the extension choose 'Reinstall native component' twice " +
      "(second time 'Repair installation'), then copy AutoControl_native\\" +
      "AutoCtrl_2025.4.22.0.exe into %UserProfile%\\AppData\\Local\\AutoControl\\ " +
      "and reload the extension (see README.md S2).");
    scheduleRetry();
  }

  /**
   * Native port disconnect handler: consumes chrome.runtime.lastError, cleans
   * up, and schedules a reconnect (unless the failure cap was reached).
   * @param {number} gen — connection generation the port belonged to
   */
  function onDisc(gen) {
    if (gen !== __acConnGen) return; // stale port — must not touch the current one
    const wasConnected = portConnectedOk;
    const lived = connectTime ? Date.now() - connectTime : 0;
    port = null; connected = false; portConnectedOk = false;
    __acConnecting = false;
    // Same reset as onConnError: a reconnect must re-run the FULL handshake
    // (init 20 etc.) for the restarted engine.
    handshakeDone = false;
    startupSent = false;
    type72Sent = false;

    // Diagnostic (2026-08-04): the engine can start (file check 0) and then
    // die ~1s later — usually a SECOND AutoControl client (e.g. the MV2
    // extension or an orphaned Zero from the installer) spawning its own
    // engine → 140 crash. Warn when the host exits suspiciously fast.
    if (wasConnected && lived > 0 && lived < 5000) {
      console.warn("[AC-MV3] Host exited " + lived + "ms after connect — engine may have crashed. " +
        "Check Task Manager for extra AutoCtrl_2025.4.22.0.exe / AutoControlZero.exe " +
        "processes and for a second loaded AutoControl extension (MV2).");
    }

    if (!wasConnected) errors++;
    else if (lived < 500) retries = Math.min(3, retries + 0.5);
    else if (lived > 3000) retries = 0;

    // AC-MV3 FIX (2026-08-07): stop the auto-reconnect loop after N
    // CONSECUTIVE failed connects — the host is gone (uninstalled, never
    // installed, or a broken install). Retrying forever spawns Zero attempts
    // + console noise with no chance of success (user VM: gens 2-50+ after
    // uninstall — the earlier `!__acEverConnected` guard missed the
    // uninstall-after-connect case). `errors` counts CONSECUTIVE failures:
    // it resets on every successful handshake (proceedAfterFileCheck), so a
    // temporarily-down-but-alive host (e.g. a Reinstall in progress) still
    // reconnects when it comes back up. The install UI's z() sends
    // {cmd:"reconnect"} (resets errors/retries) and B24's auto-reload
    // covers the cached "host not found" case — a REAL install still
    // connects without a manual reload.
    if (errors >= __acMaxNeverConnectedFailures) {
      console.warn("[AC-MV3] Native host not found " + errors +
        "x in a row — stopping auto-retry. " +
        "Install the native component (install pane / Reinstall) or reload the extension.");
      broadcast({ type: "nativeDisconnected" });
      return; // no scheduleRetry — wait for a page-driven reconnect
    }

    scheduleRetry();
    broadcast({ type: "nativeDisconnected" });
  }

  // ======== NATIVE MESSAGING ========

  /**
   * Native protocol format (from file61.js):
   * Outgoing: {type: <num>, content: <obj>}  (callback inside content)
   * Incoming: Array [type, data] or Object {msgType: N, ...}
   */

  function onMsg(msg) {
    let type, data;
    if (Array.isArray(msg)) { type = msg[0]; data = msg[1]; }
    else { type = msg.msgType; data = Object.assign({}, msg); delete data.msgType; }

    // Log all incoming native messages for debugging (gated — chatty)
    if (AC_LOG_SW) console.log(`[AC-MV3-SW] ← Native msg type ${type}:`, data);

    // Detailed logging for version/error messages — the native's version and
    // any hook-conflict errors (type 800 "no-hook-notice") are critical for
    // diagnosing why keyboard shortcuts don't fire.
    if (type === 704 || type === 705 || type === 800) {
      try {
        console.warn("[AC-MV3-SW] native detail type", type, JSON.stringify(data));
      } catch(e) {}
    }
    // Detailed gesture-path logging — type 760 is the raw action stream the
    // native emits DURING a gesture (mouseMove/drag + action frames); type 750
    // is the final trigger fire. Logging both prominently with full fields is
    // essential for diagnosing the left-click-stick-after-gesture bug (v7 RBTN-ESC).
    if (type === 760) {
      // A 760 only flows while the native is recognizing a gesture — remember
      // it so a following 750 can be identified as a gesture fire (v7).
      lastRaw760Time = Date.now();
      // AC-CAPTURE heal (2026-08-09, staged): normal mode produces ZERO
      // 760s, so any raw stream with no recent capture toggle is suspect.
      // Page-open thresholds are CONSERVATIVE (15s grace) — a slow
      // deliberate recording (sparse gesture coords + key presses) must not
      // be interrupted (user VM 13:49: a premature OFF mid-recording broke
      // the native's gesture state → type 800 NH-except on the next trail
      // draw). With no settings page open, recording is impossible → fast
      // release. Escalation: OFF → reconnect → reload (see the stage block).
      if (!__acRaw760Start) __acRaw760Start = Date.now();
      __acRaw760++;
      const __acNow = Date.now();
      const __acNoToggle = __acNow - __acCaptureT;
      // AC-MV3 FIX (2026-08-30): stale-armed release. The page arms capture
      // (combo editor file68 / gesture tester file30 / devInput file79) and
      // is SUPPOSED to send OFF on close (file68 E(), file30 blur /
      // testGestureEnd, file79 f()). If the page died, reloaded or the OFF
      // was lost, __acCaptureOn stays true FOREVER and the recording gate
      // ("never heal while armed") blocks every heal — gestures/hotkeys die
      // silently while raw 760s keep flowing (user 2026-08-30: "gestures
      // fire on micro-moves, no trail drawn" — the native was in raw
      // capture, 750s suppressed). Release armed sessions that have seen no
      // 750 for AC_CAPTURE_STALE_ARMED_MS (5 min — NOT 60s: the gesture
      // tester file30 re-arms only on window focus, so a 60s pause released
      // a live test session, user D-15). If the user is still editing, the
      // next editor action re-arms capture immediately.
      if (__acCaptureOn && __acNoToggle > AC_CAPTURE_STALE_ARMED_MS) {
        __acCaptureRelease("capture armed for >" + (AC_CAPTURE_STALE_ARMED_MS / 60000) + "min with no 750 — stale editor/test session", 1);
      }
      if (__acCaptureStage === 0) {
        const __acNoPage = __acExtPagesOpen === 0;
        const __acEnough = __acNoPage
          ? (__acRaw760 >= AC_CAPTURE_HEAL_EVENTS_NOPAGE && __acNoToggle > AC_CAPTURE_HEAL_GRACE_NOPAGE && __acNow - __acRaw760Start > AC_CAPTURE_HEAL_STREAK_NOPAGE)
          : (
             // RECORDING GATE (2026-08-09, definitive): while __acCaptureOn
             // is true the page has a recording session armed (combo editor /
             // gesture tester) and may be typing/drawing at ANY speed — no
             // rate metric can tell human typing from a stuck flood (user VM
             // 14:47: 38 keys / 78 events / 16.3s looked "dense" by every
             // threshold). NEVER heal while armed: the editor's own OFF now
             // works and releases capture on close.
             // If the page ALREADY sent its OFF (__acCaptureOn === false)
             // yet raw 760s still flow — that is DEFINITELY a stuck native
             // (the page's OFF was lost/raced) → heal.
             !__acCaptureOn &&
             __acRaw760 >= AC_CAPTURE_HEAL_EVENTS &&
             __acNoToggle > AC_CAPTURE_HEAL_GRACE &&
             __acNow - __acRaw760Start > AC_CAPTURE_HEAL_STREAK);
        if (__acEnough) {
          __acCaptureRelease(__acNoPage
            ? "raw 760 streak (" + __acRaw760 + " events) with no settings page open and no capture toggle for " + __acNoToggle + "ms"
            : "raw 760 streak (" + __acRaw760 + " events over " + (__acNow - __acRaw760Start) + "ms) without 750s, capture OFF already sent (page released) but native still streaming, no toggle for " + __acNoToggle + "ms", 1);
        }
      } else if (__acCaptureStage === 1 && __acNow > __acCaptureHealAt) {
        // The OFF did not stop the flood → the engine is wedged (capture
        // flag lives in the engine) → fresh Zero+engine via a port drop.
        __acCaptureStage = 2;
        __acCaptureHealAt = __acNow + 12000;
        console.warn("[AC-CAPTURE] type 40 OFF did not stop the 760 flood — reconnecting native (fresh Zero+engine)");
        try { if (port) { port.disconnect(); } else { scheduleRetry(); } } catch(e) {}
      } else if (__acCaptureStage === 2 && __acNow > __acCaptureHealAt) {
        // Even a fresh engine floods → last resort: SW reload (proven heal).
        __acCaptureStage = 3;
        console.warn("[AC-CAPTURE] still flooding after reconnect — reloading SW (last resort)");
        try { chrome.runtime.reload(); } catch(e) {}
      }
      try {
        // 760 is chatty (one per gesture move frame) — log a compact summary.
        // Most diagnostic value: actionType, mouseGest, trigInstId, mouse pos.
        const aType = data && data.actionType;
        const mg = data && data.mouseGest;
        const ti = data && data.trigInstId;
        const mv = data && (data.mouse || data.x !== undefined);
        console.log(`[AC-MV3-SW] ← 760 actionType=${aType} mouseGest=${JSON.stringify(mg)} trigInstId=${ti}${mv ? ' (move)' : ''}`);
      } catch(e) {}
    }

    // Buffer native messages (except 710=promise resolution) for late-connecting pages
    if (type !== 710) {
      nativeMsgBuffer.push({ type, data, ts: Date.now() });
      if (nativeMsgBuffer.length > MAX_BUFFER_SIZE) nativeMsgBuffer.shift();
    }

    // SW-BRAIN: dispatch to the in-SW core handlers (z[750] execution etc.)
    __acDispatch({ type: "nativeMsg", nativeType: type, _live: true, data, _ts: Date.now() });
    // Also forward to extension pages for UI-only updates
    broadcast({ type: "nativeMsg", nativeType: type, _live: true, data, _ts: Date.now() });

    // Log type 750 (trigger event) prominently — page handles execution
    if (type === 750) {
      // AC-CAPTURE heal: a 750 means the trigger pipeline is alive — capture
      // is NOT stuck (or has been released). Reset the flood counter + stage.
      __acRaw760 = 0;
      __acRaw760Start = 0;
      __acCaptureStage = 0;
      // AC-MV3 FIX (2026-08-30): 750s are suppressed while the native is in
      // raw capture — their arrival proves capture is NOT active. Clear the
      // armed flag so a later 760 flood (a re-stuck native) is healable
      // instead of being blocked by the recording gate forever.
      if (__acCaptureOn) {
        __acCaptureOn = false;
        console.warn("[AC-CAPTURE] 750 arrived while armed — capture actually released, clearing armed flag");
      }
      const decoded = data && data.id ? (16777215 & (data.id - handshakeSk)) : '?';
      console.warn(`[AC-MV3-SW] ← Trigger 750 id=${data && data.id} (handshakeSk=${handshakeSk} → triggerId=${decoded})`);
      // Full payload — CRITICAL for the left-click-stick bug: we need to see whether
      // the native sets `mouseGest` (gesture fires) and what trigInstId/other
      // fields ride along. The heal (v5) gates on mouseGest; if the native
      // doesn't send it for this gesture trigger, the heal never fires.
      try { console.warn(`[AC-MV3-SW] ← 750 full data:`, JSON.stringify(data)); } catch(e) {}
      // First-trigger latency: how long after type 21 the pipeline became live.
      // A large value here explains "hotkeys missed right after startup".
      if (!first750Time && startupSentTime) {
        first750Time = Date.now();
        console.log(`[AC-MV3] First trigger ${decoded} arrived ${first750Time - startupSentTime}ms after type 21 — pipeline live`);
      }
      // Right-button post-gesture Esc tap (v7, see RBTN_ESC_ENABLE):
      // v6 (soften key 1026's block:true) fixed the left-click stick, but the
      // right-button-up
      // now passes through → Chrome opens a stray context menu after every
      // gesture. Fire a synthetic Esc (type 300/_Dt) shortly after the gesture
      // to close it. GESTURE DETECTION: `mouseGest` present in the 750, OR a
      // type 760 (raw gesture stream) arrived within GESTURE_WINDOW_MS — 760
      // only flows during gesture recognition, so this won't fire for hotkeys.
      if (RBTN_ESC_ENABLE && data && (data.mouseGest || (Date.now() - lastRaw760Time) < GESTURE_WINDOW_MS)) {
        try {
          console.log(`[AC-MV3] RBTN-ESC trigger: mouseGest=${JSON.stringify(data.mouseGest)} lastRaw760=${lastRaw760Time ? (Date.now() - lastRaw760Time) + 'ms ago' : 'never'} trigInstId=${data.trigInstId} id=${data.id}`);
          scheduleGestureEsc();
        } catch(e) {
          console.warn("[AC-MV3] RBTN-ESC failed:", e.message);
        }
      }
    }
  }

  /**
   * Send to native using original {type, content} format
   */
  function postMsg(type, payload = {}) {
    if (!port || !connected) return false;
    try {
      // Right-click fix: strip key-2 block/gesture-begin entries before the native sees
      // them (single choke point — covers startup chain, SW re-send AND settings
      // page saves, all routed through here).
      if (type === 60 && STRIP_RBTN_BLOCK) {
        payload = stripRightButtonBlocks(payload);
      }
      // AC-MV3 FIX (2026-08-09, ROOT CAUSE of the stuck-capture incidents):
      // `payload || {}` MANGLES falsy payloads — `false || {}` = `{}`, so
      // the type-40 OFF (postMsg(40, false)) reached the native as an EMPTY
      // OBJECT and capture was never disabled (user VM 12:55 & 13:49: raw
      // 760 floods until SW reload). Only coalesce null/undefined.
      const content = payload == null ? {} : payload;
      // AC-CAPTURE heal: track every type-40 at THE single choke point
      // (covers the page proxy, _acNativeSend and the bundle's _Lk — all
      // route through postMsg). Truthy = capture armed — the page may be
      // actively recording, the watchdog must NOT interrupt it; falsey = the
      // page released capture. The escalation stage is reset ONLY on ARMING
      // — the watchdog's own OFF (postMsg(40, false)) must not cancel its
      // own stage-1 escalation.
      if (type === 40) {
        __acCaptureT = Date.now();
        __acCaptureOn = !!payload;
        __acRaw760 = 0;
        __acRaw760Start = 0;
        if (payload) __acCaptureStage = 0;
      }
      port.postMessage({ type, content });
      if (type === 60) {
        const m = payload && typeof payload === 'object' ? payload : {};
        const mk = m.map ? Object.keys(m.map).map(Number) : [];
        const U = mk.filter(k => k - 22025 === 85).map(k => '[' + m.map[k].join(',') + ']');
        const keys = m.list && m.list.length ? m.list.filter(e => e && e.type === 1) : [];
        const blocks = m.list ? m.list.filter(e => e && e.block) : [];
        console.log("[AC-MV3] → Native type 60 (config) map:",
          mk.length, "keys:", mk.join(','),
          "| U(85):", U.length ? U.join(' ') : 'NONE',
          "| keyEvents:", keys.map(e => (e.key1 || 0) + '/' + (e.key2 || 0)).join(' '),
          "| blocked:", blocks.length,
          "| list:", Array.isArray(m.list) ? m.list.length : 0,
          "| urlTests:", Array.isArray(m.urlTests) ? m.urlTests.length : 0,
          "| gestures:", Array.isArray(m.gestures) ? m.gestures.length : 0);
        // Full dump of every keyboard key's list entries — what the native gets
        if (AC_LOG_SW) {
          const kbDump = [];
          for (const k of mk) {
            const key = k - 22025;
            // Keys 1..255 plus the wheel events (512=down/1536=up) — the wheel
            // entries carry the right-button-held precond (keyEvt:2) from the
            // "volume via right-click+wheel" triggers; fingerprint for
            // right-button-block issue.
            // Also key 1026 (right-button-up/_mk event) — the gesture preset's "_end"
            // entry registers under it (mapKey 22025+1026=23051).
            if (m.map[k] && ((key > 0 && key < 256) || key === 512 || key === 1536 || key === 1026)) {
              for (const idx of m.map[k]) {
                kbDump.push(key + '→' + JSON.stringify(m.list[idx]));
              }
            }
          }
          console.log("[AC-MV3] → keyboard config dump:", kbDump.join(' | '));
        }
      } else {
        console.log("[AC-MV3] → Native type", type);
      }
      // Synth-path logging — type 300 (SendInput) and 315 (input lock) are
      // emitted by RBTN-HEAL and by sendInput actions; log full payload for
      // diagnosing the left-click-stick bug.
      if (type === 300 || type === 315) {
        try { console.warn(`[AC-MV3] → synth type ${type} payload:`, JSON.stringify(payload)); } catch(e) {}
      }
      return true;
    } catch(e) { return false; }
  }

  /**
   * Send to native with callback, using original format from file61.js:
   *
   * Original: callback = e + l where e=random, l=parseInt(extId.substr(2,3),36)
   * Native echoes back just 'e' (subtracts l internally)
   *
   * So we store keyed by 'e', send 'e + l', match response against 'e'.
   */
  function postWithCb(type, payload = {}, timeout = 5000) {
    // Type 250 = file write (chunked, e.g. the 695 KB engine in 4 chunks).
    // On slow disks / with antivirus the write can take longer than 5s;
    // MV2 had NO timeout at all for such calls. Give it 30s.
    if (!timeout || timeout <= 5000) {
      if (type === 250) timeout = 30000;
      else if (type === 10) timeout = 9000; // file check (handshake)
    }
    const gen = __acConnGen; // the connection this send belongs to
    return new Promise((resolve, reject) => {
      if (!port) { reject(Error("no port")); return; }
      const e = 2130706431 * Math.random() | 0;
      const extId = chrome.runtime.id;
      const l = parseInt(extId.substr(2, 3), 36) || 13625; // "lkaihdpfpifdlgoapbfocpmekbokmcfd" -> 13625
      const sentCallback = e + l;
      const timer = timeout ? setTimeout(() => {
        // A send on a SUPERSEDED port must not act on the current connection:
        // no onConnError, no state change — just fail the promise quietly.
        if (gen !== __acConnGen) { reject(Error("stale")); return; }
        console.warn("[AC-MV3] postWithCb timeout for type", type, "e:", e);
        reject(Error("timeout"));
      }, timeout) : null;

      const handler = m => {
        let mt, md;
        if (Array.isArray(m)) { mt = m[0]; md = m[1]; }
        else { mt = m.msgType; md = m; }
        // Native echoes back just 'e' (without +l offset)
        if (mt === 710 && (md.id === e || md.id == e || md.id == sentCallback)) {
          if (gen !== __acConnGen) return; // stale — the promise is already dead
          port.onMessage.removeListener(handler);
          if (timer) clearTimeout(timer);
          console.log("[AC-MV3] postWithCb resolved type", type, "result:", md.params);
          resolve(md.params !== undefined ? md.params : md);
        }
      };
      port.onMessage.addListener(handler);

      // Build message: {type, content: payload, callback: e+l} for most types
      // For types 240,285,490: callback goes inside content
      const callbackInContent = type === 240 || type === 285 || type === 490;
      const msg = { type, content: payload };
      if (callbackInContent) {
        msg.content.callback = sentCallback;
      } else {
        msg.callback = sentCallback;
      }
      console.log("[AC-MV3] postWithCb type", type, "e:", e, "l:", l,
        "sent:", sentCallback, "msg:", JSON.stringify(msg).slice(0,120));
      try {
        port.postMessage(msg);
      } catch(e2) {
        port.onMessage.removeListener(handler);
        if (timer) clearTimeout(timer);
        reject(e2);
      }
    });
  }

  /**
   * Broadcast a native message to all extension pages (with the _sw flag so
   * page handlers skip re-processing); replays buffered messages to pages
   * that connect late.
   * @param {object} msg — message to broadcast
   */
  function broadcast(msg) {
    // The SW is ALWAYS the leader in SW-brain mode: the settings page must not
    // execute triggers or the config chain (its isLeader() gate checks _leader).
    const m = Object.assign({
      _sw: true,
      _seq: ++broadcastSeq,
      _leader: "sw"
    }, msg);
    // MV3: send to each extension page tab explicitly for reliable delivery
    chrome.tabs.query({ url: [`chrome-extension://${chrome.runtime.id}/*`] }, tabs => {
      console.log(`[AC-MV3-SW] broadcast "${msg.type}" (leader=${m._leader}) to ${tabs.length} tabs`);
      // AC-CAPTURE heal: if the last settings page is GONE while capture was
      // armed (an editor was open in it — combo editor / gesture tester /
      // devInput), nobody can ever send the type-40 OFF → the native would
      // stay stuck in capture (gestures/hotkeys/RMB dead) until a reload.
      // Release now: no page = no active recording.
      __acExtPagesOpen = tabs.length;
      if (tabs.length === 0 && __acCaptureOn && __acCaptureStage === 0) {
        __acCaptureRelease("last settings page closed while capture armed", 1);
      }
      for (const tab of tabs) {
        chrome.tabs.sendMessage(tab.id, m).then(() => {
          console.log(`[AC-MV3-SW]   ✓ tab ${tab.id}`);
        }).catch(err => {
          console.warn(`[AC-MV3-SW]   ✗ tab ${tab.id}: ${err.message}`);
        });
      }
    });
    // Also try runtime broadcast as fallback
    chrome.runtime.sendMessage(m).then(() => {
      console.log(`[AC-MV3-SW] broadcast "${msg.type}" via runtime ✓`);
    }).catch(err => {
      console.log(`[AC-MV3-SW] broadcast "${msg.type}" via runtime ✗: ${err.message}`);
    });
  }

  // ======== PAGE COMMUNICATION ========

  // Rate limiting for ping messages to native (type 920)
  let lastPingTime = 0;
  const MIN_PING_INTERVAL = 2000; // min 2s between pings

  // Cached "userScripts toggle is off" for execUserFunc (fail fast, no retries).
  let __acExecUsFailed = false;

  // ======== EXECUSERFUNC DEDUP (LRU) ========
  // Two-tier dedup to prevent multiple script executions from the same trigger:
  //   1. __acExecInFlight  — Set of keys currently executing (concurrent guard).
  //      Released when execUserFuncDone arrives or after safety timeout.
  //   2. __acExecCompleted — LRU Map of recently-completed keys (post-hoc guard).
  //      Prevents "burst" duplicates that arrive AFTER the original finished.
  //      CRITICAL: Chrome may queue userScripts.execute calls internally and
  //      flush them in a burst seconds later. TTL must cover this window.
  // Key format: "tabId:scriptId:trigInstId"
  // Each trigger press gets a unique trigInstId from _Ai(), so legitimate re-presses
  // are never blocked — only true duplicates of the same press are suppressed.
  const __acExecInFlight = new Set();
  const __acExecInFlightTimers = new Map(); // key → timeoutId
  const __acExecCompleted = new Map(); // key → timestamp
  const __acExecDedupMax  = 50;       // LRU capacity
  const __acExecDedupTTL  = 15000;    // 15 s — Chrome may batch userScripts.execute;
                                       //      burst observed ~27s after first, but 15s
                                       //      covers the gap from the LAST press to burst
  const __acExecSafetyTTL = 10000;    // 10 s — in-flight keys expire as safety net

  /**
   * Check whether an execUserFunc dedup key is known (in-flight or completed).
   * @param {string} key — tabId:scriptId:trigInstId
   * @returns {boolean}
   */
  function __acExecDedupCheck(key) {
    // 1) In-flight check (concurrent duplicate from another frame / retry)
    if (__acExecInFlight.has(key)) {
      console.warn(`[AC-DUP] BLOCK in-flight  key=${key}`);
      return 'in-flight';
    }
    // 2) Recently-completed check (post-hoc burst duplicate)
    if (__acExecCompleted.has(key)) {
      const age = Date.now() - __acExecCompleted.get(key);
      if (age < __acExecDedupTTL) {
        console.warn(`[AC-DUP] BLOCK completed (${age}ms ago) key=${key}`);
        return 'completed';
      }
      __acExecCompleted.delete(key); // expired
    }
    return false;
  }

  /**
   * Acquire the execUserFunc dedup key (in-flight set).
   * @param {string} key
   * @returns {boolean} false if the key is already in flight
   */
  function __acExecDedupAcquire(key) {
    __acExecInFlight.add(key);
    // Safety timeout: if execution never completes, move to completed (not
    // just drop) so that late-arriving burst duplicates are still blocked.
    const tid = setTimeout(() => {
      __acExecInFlight.delete(key);
      __acExecInFlightTimers.delete(key);
      if (!__acExecCompleted.has(key)) __acExecCompleted.set(key, Date.now());
    }, __acExecSafetyTTL);
    __acExecInFlightTimers.set(key, tid);
  }

  /**
   * Release an execUserFunc dedup key and remember it as completed (LRU).
   * @param {string} key
   */
  function __acExecDedupRelease(key) {
    const tid = __acExecInFlightTimers.get(key);
    if (tid) { clearTimeout(tid); __acExecInFlightTimers.delete(key); }
    __acExecInFlight.delete(key);
    // Evict oldest if at capacity
    if (__acExecCompleted.size >= __acExecDedupMax) {
      const [oldest] = __acExecCompleted.keys();
      __acExecCompleted.delete(oldest);
    }
    // Skip if already in map (don't refresh timestamp — keep FIFO eviction)
    if (!__acExecCompleted.has(key)) {
      __acExecCompleted.set(key, Date.now());
    }
  }

  chrome.runtime.onMessage.addListener((msg, sender, sendRes) => {
    if (msg._sw) return false;

    // AC-MV3 FIX (2026-08-02, round 7): DO NOT handle userAPI here!
    // The bundle's file48 registers `_Yk.runtime.onMessage.addListener`
    // (live in the SW via importScripts) and its m() handler ALREADY
    // processes userAPI correctly — callback-style `_Yh(a,c)((...p)=>
    // d(...p))`, free-variable _Yh (file77 fills the lexical binding).
    // A second handler here caused DOUBLE execution of _Yh → W: for
    // setClipboard both ran F→K; the first K did `delete window[e]`, the
    // second got undefined → clipboard overwritten with "undefined"
    // (snipboard.io: E007 image data was not found on your clipboard).
    // Verified in mh_test.js: `userAPI dispatch: 1 answered of 1 listeners`.
    if (msg.type === "userAPI") return false;

    // AC-MV3 FIX (2026-08-12, FEATURES-MV3.md §7-15): file71 popup result
    // (button click / window close). The MV3 _Fo implementation
    // (mv3_native_shim, __acMv3Popup) fills the popup via
    // scripting.executeScript; the popup page reports the dialog result here
    // → __acResolvePopup resolves the _Fo callback (MV2: getViews + onunload).
    if (msg && msg.type === "acPopupResult") {
      if (typeof __acResolvePopup === "function") __acResolvePopup(msg.runId, !!msg.answer);
      if (sendRes) sendRes({ ok: true });
      return true;
    }
    // AC-MV3 FIX (2026-08-12, FEATURES-MV3.md §7-15): the file71.html popup
    // page requests its content from the SW (it cannot be filled via
    // scripting.executeScript — chrome-extension:// pages are not
    // injectable). __acPopupGetContent (shim) returns the pre-rendered html
    // + the window id for auto-sizing.
    if (msg && msg.type === "acPopupContent") {
      const c = typeof __acPopupGetContent === "function" ? __acPopupGetContent(msg.runId) : null;
      if (sendRes) sendRes(c || { html: "" });
      return true;
    }

    // AC-MV3 FIX (2026-08-02, round 11): runInPageCtx MAIN-world injection.
    // jsCode's window.runInPageCtx bridges here via file42 (acMainWorld
    // postMessage). We inject through chrome.userScripts.execute with
    // world 'MAIN' — API-injected code runs directly (NOT as an inline
    // <script>), so strict page CSP (unsafe-inline) does NOT block it
    // (TamperMonkey-style). The old <script>-element path was blocked on
    // CSP sites. Remaining limit: eval() INSIDE the user function in MAIN
    // world is still cut by page CSP without unsafe-eval (same as MV2).
    if (msg.type === "execMainWorld") {
      const tabId = sender && sender.tab ? sender.tab.id : 0;
      if (!tabId || typeof msg.code !== "string") { sendRes({ error: "no tab or code" }); return true; }
      // AC-MV3 FIX (2026-08-12, FEATURES-MV3.md §7-5 follow-up): runInPageCtx
      // INSIDE a runInFrames function ran in the TOP frame — the message
      // came from the SUBFRAME's file42 (acMainWorld relay) but the target
      // had no frameIds → userScripts.execute defaulted to frame 0. Same fix
      // as B37 (execUserFunc): use sender.frameId. The return path was
      // already frame-correct (file42 posts acMainWorldRes to its own
      // window); only the injection target needed the frame.
      const frameId = sender && typeof sender.frameId === "number" ? sender.frameId : 0;
      const injectDetails = frameId ? { frameIds: [frameId] } : {};
      // AC-MV3 DIAG (round 16f): log what actually goes into the MAIN world
      // and what comes back — the RIPC res "ok" is silent even when the
      // injection fails (sendRes({result:undefined})), so a missing
      // [AC-MV3-PROXY] init must be correlated with the real result.
      try { console.warn('[AC-MV3-EXEC-MAIN] code=' + String(msg.code).slice(0, 150) + ' frame=' + frameId); } catch (e) {}
      // Wrap in try/catch: userScripts.execute rejects the promise when the
      // script throws (and __acInjectCode would swallow it) — catching turns
      // the error into a result value instead.
      const wrapped = "try{" + msg.code + "\n}catch(e){({__acError:String(e&&e.message||e)})}";
      // AC-MV3 FIX (2026-08-02, round 15): serialize MAIN-world injections —
      // W()'s FUNC branch injects the funcExecLstnr listener FIRST, then
      // 'var m = fn'; if they run concurrently the {funcName} message may
      // reach the listener before window.m exists. A promise chain keeps
      // the order (each execute resolves after its code ran).
      if (!self.__acMainWorldChain) self.__acMainWorldChain = Promise.resolve();
      self.__acMainWorldChain = self.__acMainWorldChain.then(() => new Promise((res) => {
        __acInjectCode(tabId, wrapped, injectDetails, (results) => {
          const r = results && results[0];
          try { console.warn('[AC-MV3-EXEC-MAIN] res=' + (r && r.__acError ? 'ERR ' + String(r.__acError).slice(0, 120) : typeof r)); } catch (e) {}
          if (r && r.__acError) sendRes({ error: String(r.__acError) });
          else sendRes({ result: r });
          res();
        });
      }));
      return true;
    }

    // file42.js fell back from eval (page CSP forbids it) — run the code in
    // the USER_SCRIPT world via chrome.userScripts, bridge ACtl via postMessage.
    if (msg.type === "execUserFunc") {
      const tabId = sender && sender.tab ? sender.tab.id : 0;
      // AC-MV3 FIX (2026-08-10, FEATURES-MV3.md §7-5): runInFrames — execute in the
      // SENDER's frame, not always frame 0. file42 in a subframe → FN → SW →
      // userScripts.execute used to land in the TOP frame (frameIds:[0]): the
      // funcCode ran N times but always with the top frame's location/document
      // (MV2 eval'd it locally in each frame). sender.frameId (MV3 provides it
      // for content-script messages) restores per-frame execution; plain
      // script runs (file42 in frame 0) are unchanged (frameId 0).
      const frameId = sender && typeof sender.frameId === "number" ? sender.frameId : 0;
      const code = msg && msg.code, args = msg.args || [], id = msg.id;
      const ctx = (msg && msg.ctx) || {};
      const key = tabId + ":" + (ctx.scriptId || "") + ":" + (ctx.trigInstId || "");
      if (!tabId || typeof code !== "string") { sendRes({ error: "no tab or code" }); return true; }
      // AC-MV3 UX (2026-08-09): fail fast on protected pages (chrome://,
      // Web Store, extension pages) — Chrome rejects ALL injection there;
      // without this check the user gets a silent FAIL or a raw "Cannot
      // access a chrome:// URL" after the n() timeout.
      if (__acIsProtectedPage(sender && sender.tab && sender.tab.url)) {
        console.warn(`[AC-MV3] execUserFunc blocked — protected page tab=${tabId}`);
        __acNotifyProtected();
        sendRes({ error: __acProtectedMsg });
        return true;
      }
      // AC-MV3 diagnostic: file42→SW hop latency (file42 stamps t=Date.now()
      // before sending). Same wall-clock → comparable. 2026-08-05: also dump
      // the SW state per call — up=session age, conn/hs=connection+handshake,
      // if=_if.binSwtch present, ek=trigger count. Decides whether the
      // switchState/_Vj/var-delete failures are SW-restart artifacts.
      if (msg.t) console.warn(`[AC-SW] execUserFunc rcvd tab=${tabId} age=${Date.now()-msg.t}ms key=${key} up=${Math.round((Date.now()-__acSwStart)/1000)}s conn=${connected} hs=${handshakeDone} if=${(_if && _if.binSwtch) ? 'ok' : 'EMPTY'} ek=${_ek ? Object.keys(_ek).length : 0}`);
      // AC-MV3 dedup: suppress concurrent and post-hoc duplicates.
      // Each trigger press has a unique trigInstId — only true duplicates are blocked.
      if (key !== "::") {
        const dup = __acExecDedupCheck(key);
        if (dup) {
          // key included so the PAGE console shows WHICH call was blocked
          // (2026-08-05: dedup correlates with the ACtl.on tabLoadEnd timeout
          // in run 3 — need the key to identify the culprit).
          sendRes({ ok: true, dedup: true, dupType: dup, key, st: __acStateDump() });
          return true;
        }
        __acExecDedupAcquire(key);
      }
      // AC-MV3 FIX (2026-08-05): if the config chain hasn't populated _if/_ek
      // yet (e.g. the SW restarted and the reconnect/config chain stalled —
      // symptom: ACtl.switchState "_if.binSwtch is not iterable" from the
      // 2nd script run), re-run the FULL config chain (_lr→_Gf) on the first
      // API call. Heals _if.binSwtch (switchState) and _ek (trigger map)
      // WITHOUT an extension reload. Idempotent; NO handshakeDone guard —
      // the chain runs off storage (type 60 send fails silently when
      // disconnected). Throttled to once per 10 s.
      if (typeof _if === 'object' && (!_if || !_if.binSwtch) && (typeof _Gf === 'function' || typeof _lr === 'function')) {
        const now = Date.now();
        if (now - __acLastHeal > 10000) {
          __acLastHeal = now;
          console.warn("[AC-MV3] _if missing binSwtch — re-running config chain (_lr→_Gf)");
          try {
            if (typeof _lr === 'function') _lr(() => { try { _Gf({}, () => {}); } catch(e) {} });
            else _Gf({}, () => {});
          } catch(e) { console.warn("[AC-MV3] _Gf heal failed:", e.message); }
        }
      }
      if (__acExecUsFailed || !(chrome.userScripts && chrome.userScripts.execute)) {
        // Cached failure (toggle off) — fail fast, no fragile retries.
        sendRes({ error: "userScripts API unavailable — enable 'Allow user scripts' on chrome://extensions (Chrome 120+)" });
        return true;
      }
      const jsCode = `
        (function(){
          // AC-MV3 FIX (2026-08-02): events for ACtl.on() are delivered to
          // file42 (isolated world), which cannot see window[g] handlers
          // created HERE in the USER_SCRIPT world — file42 relays every
          // event via postMessage('acEvt'). Forward to the local handler.
          // Guarded: jsCode runs once per execUserFunc injection — without a
          // flag, listeners would accumulate on every script run.
          if (!window.__acEvtBridge) {
            window.__acEvtBridge = true;
            window.addEventListener("message", function(ev) {
              var d = ev.data;
              if (d && d.type === "acEvt" && d.funcName) {
                if (d.del) { try { delete window[d.funcName]; } catch(e) {} return; }
                var h = window[d.funcName];
                if (h) { try { h(d.event); } catch(e) {} }
              }
            });
          }
          // AC-MV3 FIX (2026-08-02, round 8): FN (eval) must exist in the
          // USER_SCRIPT world too — the runInPageCtx file branch evaluates
          // z-bundles INSIDE a callback that runs here, but file42's FN
          // lives in the isolated world (separate window, invisible here).
          // eval IS allowed in user script worlds (not subject to page CSP).
          window.FN = function(a) { return eval("(" + a + ")"); };
          // AC-MV3 FIX (2026-08-02, round 8): runInPageCtx must exist in the
          // USER_SCRIPT world too. file42 (isolated world content script)
          // defines window.runInPageCtx in ITS world — separate JS context,
          // separate window. W()'s runInPageCtx case routes the call through
          // F() → execUserFunc, which lands HERE (USER_SCRIPT world), where
          // runInPageCtx was undefined → ReferenceError. Same semantics as
          // file42: (url[,again]) → script src; (func|{code}) → inline
          // script element (MAIN world — DOM is shared across worlds).
          // The W() FUNC branch additionally uses the 'funcExecLstnr' name
          // + postMessage roundtrip — both work because window.postMessage
          // crosses worlds (like the acEvt/acUserApi bridge).
          window.__acRipc || (window.__acRipc = {});
          // AC-MV3 FIX (2026-08-02, round 15): W()'s FUNC branch defines a
          // MAIN-world global ('var m = fn') via ASYNC userScripts.execute,
          // then IMMEDIATELY posts {funcName:m}. The message can reach the
          // MAIN-world funcExecLstnr listener BEFORE window.m exists (MV2
          // was race-free because <script> executes synchronously on
          // append). Buffer such messages in the USER_SCRIPT world and flush
          // them once the pending var injection completes.
          // Round 15: state lives on WINDOW (__acPendingVar etc.) — every
          // execUserFunc injection re-runs this jsCode and would otherwise
          // re-wrap window.postMessage with a FRESH (null) pending state,
          // so the last wrapper never buffers (seen as a chain of 10+
          // postMessage wrappers). Guard: wrap only once.
          if (!window.__acPostWrapped) {
            window.__acPostWrapped = true;
            window.__acPendingVar = null;
            window.__acVarQueue = [];
            var __acOrigPost = window.postMessage.bind(window);
            window.postMessage = function(data, target) {
              if (data && typeof data === "object" && data.funcName &&
                  window.__acPendingVar && data.funcName === window.__acPendingVar.name) {
                window.__acVarQueue.push([data, target]);
                return;
              }
              __acOrigPost(data, target);
            };
            window.__acFlushVarQueue = function() {
              window.__acPendingVar = null;
              var q = window.__acVarQueue;
              window.__acVarQueue = [];
              for (var i = 0; i < q.length; i++) __acOrigPost(q[i][0], q[i][1]);
            };
          }
          // AC-MV3 FIX (2026-08-02, round 11): runInPageCtx now injects into
          // the MAIN world via chrome.userScripts — bridge: USER_SCRIPT world
          // -> postMessage(acMainWorld) -> file42 (isolated) ->
          // runtime.sendMessage(execMainWorld) -> SW __acInjectCode ->
          // userScripts.execute({world:'MAIN'}). API-injected code runs
          // DIRECTLY (NOT as an inline <script>), so strict page CSP
          // (unsafe-inline) does NOT block it — same as TamperMonkey.
          // The old <script>-element approach was blocked on CSP sites
          // (example.org). Round 10 semantics preserved: returns a CALLBACK
          // RUNNER (c)=>{...}; execUserFunc invokes function results with
          // __post. File/URL form: fetch the text in the USER_SCRIPT world
          // (exempt from page CSP), inject as code; fallback to <script src>.
          window.runInPageCtx = function(g, e) {
            if (e === undefined) { e = g; g = undefined; }
            return function(c) {
              c = c || function(){};
              if (g) { if (window.__acRipc[g]) return c({}); window.__acRipc[g] = true; }
              var rid = "__acm_" + Math.random().toString(36).slice(2);
              var hnd = function(ev) {
                var d = ev.data;
                if (d && d.type === "acMainWorldRes" && d.id === rid) {
                  window.removeEventListener("message", hnd);
                  // AC-MV3 DIAG (round 16e): did the MAIN injection complete?
                  try { console.warn('[AC-MV3-RIPC] res id=' + rid + (d.error ? ' err=' + d.error : ' ok')); } catch (e) {}
                  // AC-MV3 round 15: this injection finished — release any
                  // buffered {funcName} postMessage for the pending var.
                  if (window.__acPendingVar && window.__acPendingVar.rid === rid) {
                    try { console.warn('[AC-MV3-RIPC] flush N=' + window.__acPendingVar.name); } catch (e) {}
                    window.__acFlushVarQueue();
                  }
                  if (d.error) { if (g) delete window.__acRipc[g]; c({ error: d.error }); }
                  else c(d.result || {});
                }
              };
              window.addEventListener("message", hnd);
              var run = function(src) {
                window.postMessage({ type: "acMainWorld", id: rid, code: src }, "*");
              };
              if (typeof e === "string") {
                try {
                  fetch(e).then(function(r) {
                    if (!r.ok) throw new Error("HTTP " + r.status);
                    return r.text();
                  }).then(function(t) { run(t); })
                    .catch(function() {
                      var d2 = document.createElement("script");
                      d2.src = e;
                      d2.onload = function(){ this.remove(); c({}); };
                      d2.onerror = function(){ if (g) delete window.__acRipc[g]; this.remove(); c({ error: 'Unable to load URL "' + e + '"' }); };
                      (document.head || document.documentElement).appendChild(d2);
                    });
                  return;
                } catch (err) { run(String(e)); }
              } else if (typeof e === "function") {
                // AC-MV3 FIX (2026-08-06, round 16 — FEATURES-MV3.md §7-6): W()'s FUNC branch
                // installs its funcExecLstnr listener via
                // runInPageCtx("funcExecLstnr", fn). That listener reads
                // window[m] defined by a SEPARATE injection — in MV3 every
                // userScripts.execute is a different evaluation context, so
                // it never sees the var ("window[u.data.funcName] is not a
                // function"; buffering/ordering cannot fix this). The
                // single-injection proxy (see the {code} branch below)
                // answers the {funcName:m,args} message ITSELF from the same
                // context — so the funcExecLstnr installer is NO-OPED here
                // (otherwise it would answer first with the wrong error and
                // win the channel race). c({}) = ack immediately; the
                // result comes from the proxy.
                if (g === "funcExecLstnr") {
                  window.removeEventListener("message", hnd);
                  c({});
                  return;
                }
                run("(" + e + ")()");
              } else if (e && typeof e.code === "string") {
                // AC-MV3 FIX (2026-08-06, round 16 — FEATURES-MV3.md §7-6, replaces rounds
                // 12-15): W()'s FUNC branch sends 'var m = <fn>' to define a
                // MAIN-world global, then IMMEDIATELY posts {funcName:m,args}
                // (buffered here until the injection completes — rounds
                // 14-15). Rounds 12-15 promoted 'var' to 'window.m' in a
                // SEPARATE injection, but the funcExecLstnr listener (also a
                // separate injection context) never saw window.m. FIX:
                // inject a SINGLE self-contained proxy that (a) sets
                // window.m, (b) installs its OWN listener for the
                // {funcName:m,args} message and answers it directly from the
                // same context via {response,funcName} — exactly what W()'s
                // callback runner (listener B) expects. No cross-injection
                // global sharing needed. Ends with void 0 so the
                // completion value is undefined (a function result would
                // make userScripts.execute/sendRes fail the structured
                // clone).
                var mm = e.code.match(/^var\\s+([A-Za-z_$][\\w$]*)\\s*=\\s*([\\s\\S]*)$/);
                if (mm) {
                  window.__acPendingVar = { name: mm[1], rid: rid };
                  // NOTE (round 16d): mm[2] (the FUNC source) is appended via
                  // CONCATENATION — runtime, so its own double quotes are
                  // harmless (the literals are already closed). Only the
                  // quotes INSIDE the acProxy literal need escaping, and this
                  // jsCode is a TEMPLATE LITERAL — \" collapses to " one
                  // level, so the acProxy literal must DOUBLE-escape them
                  // (\\\" → \" in jsCode → " in the runtime acProxy string).
                  // AC-MV3 DIAG (round 16e): console.warn in the proxy so the
                  // page console shows whether the MAIN injection ran, got
                  // the {funcName} message and answered; source check is
                  // dropped (cross-world postMessage source mapping is
                  // unreliable MAIN←USER_SCRIPT — the funcName+args+id
                  // contract is unique enough).
                  var acProxy = "(function(){/*AC-MV3-PROXY*/var N=" + JSON.stringify(mm[1]) +
                    ",F=" + mm[2] +
                    ";window[N]=F;function H(e){var d=e.data;if(d&&d.funcName===N&&\\\"args\\\"in d){try{console.warn('[AC-MV3-PROXY] msg N='+N+' args='+String(d.args))}catch(z){}window.removeEventListener(\\\"message\\\",H);var o;try{o={result:F.apply(null,d.args||[])}}catch(x){o={error:String(x&&x.message||x)}}var P=function(r){try{window.postMessage({response:r,funcName:N},\\\"*\\\")}catch(z){}};if(o.error)P(o);else if(o.result&&typeof o.result.then===\\\"function\\\")o.result.then(function(v){P({result:v})},function(x2){P({error:String(x2&&x2.message||x2)})});else P(o)}}window.addEventListener(\\\"message\\\",H);try{console.warn('[AC-MV3-PROXY] init N='+N)}catch(z){}void 0})()";
                  run(acProxy);
                  // Safety: if acMainWorldRes never arrives, release the
                  // queue after 8s (n()'s delivery timeout is 6s — the retry
                  // completes the flow; 2s was too short for the one-time
                  // userScripts init ~4-5s on fresh tabs).
                  setTimeout(function() {
                    if (window.__acPendingVar && window.__acPendingVar.rid === rid) window.__acFlushVarQueue();
                  }, 8000);
                } else {
                  run(e.code);
                }
              } else {
                c({ error: "Invalid runInPageCtx argument" });
              }
            };
          };
          var __acActl = new Proxy({}, { get: function(t, p) {
            if (p === "TAB_ID") return ${tabId};
            if (p === "STOP_CHAIN") return Object.freeze({ break: "inner" });
            if (p === "STOP_FULL_SEQ") return Object.freeze({ break: "outer" });
            return function() {
              var f = Array.prototype.slice.call(arguments);
              // AC-MV3: serialization functions in file77 W() read their data
              // from window BY NAME (K does 'let g=window[e]'), exactly like
              // file42's C() proxy does — store the data arg on window and
              // pass the name (same world: USER_SCRIPT). Unconditional, like
              // the original (even for strings — K coerces window[name]).
              if (p === "saveFile" && f.length > 1) {
                var k = "_" + Math.random().toString(36).slice(2);
                window[k] = f[1];
                f[1] = k;
              } else if (p === "setClipboard" && f.length) {
                var k = "_" + Math.random().toString(36).slice(2);
                window[k] = f[0];
                f[0] = k;
              }
              // AC-MV3 FIX (2026-08-02, round 5): ACtl.on's RESULT is a
              // Promise that resolves when the event fires. A pending
              // Promise cannot be cloned through postMessage (DataCloneError
              // in the z-bundle eval), so register the handler fire-and-
              // forget (local:1 → file42 relay skips the z-bundle eval) and
              // return the promise DIRECTLY to the script. Events arrive
              // via file42's acEvt relay → window[g](event) → promise
              // resolves (real callback functions run here too).
              if (p === "on") {
                var g = "_evt_" + Math.random().toString(36).slice(2);
                var cb = (f.length && typeof f[f.length-1] === "function") ? f.pop() : null;
                var pr = new Promise(function(res) {
                  window[g] = function(d) {
                    if (d === "promise") return pr;
                    res(d);
                    if (cb) { try { cb(d); } catch(e) {} }
                  };
                });
                f.push({ FUNC: g });
                window.postMessage({ type: "acUserApi", id: "__acreg_" + Math.random().toString(36).slice(2), local: 1, props: [p].concat(f), args: f }, "*");
                return pr;
              }
              // postMessage cannot clone functions — stringify them like
              // file42's C() proxy does ({FUNC: source}).
              f = f.map(function(h){ return typeof h === "function" ? { FUNC: h + "" } : h; });
              return new Promise(function(D, A) {
                var rid = "__ac_" + Math.random().toString(36).slice(2);
                var hnd = function(ev) {
                  var d = ev.data;
                  if (d && d.type === "acUserApiRes" && d.id === rid) {
                    window.removeEventListener("message", hnd);
                    // AC-MV3 FIX (2026-08-02, round 13): module namespace
                    // objects cannot cross postMessage — they were stashed
                    // on window (by __post) and the marker replaced back
                    // HERE (same USER_SCRIPT world → real object available).
                    var r = d.result;
                    if (r && typeof r === "object" && r.__acModule) {
                      try { r = window[r.__acModule]; } catch(e) {}
                    }
                    d.error ? A(d.error) : D(r);
                  }
                };
                window.addEventListener("message", hnd);
                window.postMessage({ type: "acUserApi", id: rid, props: [p].concat(f), args: f }, "*");
              });
            };
          }});
          var __post = function(res) {
            // AC-MV3 FIX (2026-08-02, round 5): z-bundle evaluation
            // (captureTab → z(J,[map])) attaches a GENERATOR FUNCTION as
            // Symbol.iterator to the result — postMessage cannot clone
            // functions → DataCloneError. Convert iterables to plain
            // [key, value] arrays — destructuring like
            // 'let [[, dataUri]] = await ACtl.captureTab(...)' works
            // identically on arrays.
            // AC-MV3 FIX (2026-08-02, round 13): module namespace objects
            // (ACtl.import / getFile('module')) are NOT structured-cloneable
            // at all → DataCloneError. Stash them on window and send a
            // marker; the acUserApiRes handler above swaps it back.
            try {
              if (res && typeof res === "object") {
                if (Object.prototype.toString.call(res) === "[object Module]") {
                  var mn = "__acmod_" + Math.random().toString(36).slice(2);
                  window[mn] = res;
                  res = { __acModule: mn };
                } else if (typeof res[Symbol.iterator] === "function") {
                  var arr = [];
                  for (var it = res[Symbol.iterator](), s = it.next(); !s.done; s = it.next()) arr.push(s.value);
                  res = arr;
                }
              }
            } catch(e) {}
            window.postMessage({ type: "acUserApiRes", id: ${JSON.stringify(id)}, result: res }, "*");
          };
          var __postErr = function(err) {
            window.postMessage({ type: "acUserApiRes", id: ${JSON.stringify(id)}, error: String(err && err.message || err) }, "*");
          };
          // AC-MV3 FIX (2026-08-02): user scripts reference the GLOBAL ACtl
          // (e.g. the built-in "Download all images" example uses
          // 'await ACtl.saveURL(...)'). The original MV2 made ACtl visible via
          // direct-eval closure capture (file42 new Function('ACtl',...) +
          // eval('('+funcCode+')')). In the USER_SCRIPT world no such binding
          // exists -> ReferenceError: 'ACtl is not defined'. Declare it as a
          // var of this IIFE — the evaluated function literal closes over it.
          var ACtl = __acActl;
          var p;
          // AC-MV3: pass ONLY the user args (original semantics) — ACtl comes
          // from the closure above, not from arguments[0].
          try { p = (${code}).apply(null, ${JSON.stringify(args)}); }
          catch (e) { p = Promise.reject(e); }
          // AC-MV3 FIX (2026-08-02, round 10): some W() paths return a
          // CALLBACK RUNNER instead of a value — runInPageCtx FUNC branch
          // returns q (cb-style: q(onDone)), file branch returns the
          // runInPageCtx runner. A function cannot cross postMessage
          // (DataCloneError), so invoke it callback-style with __post.
          if (typeof p === "function") {
            try { p(__post); return; }
            catch (e) { __postErr(e); return; }
          }
          Promise.resolve(p).then(__post, __postErr);
        })();`;
      // AC-MV3: guard sendRes — userScripts.execute may be slow; ensure the
      // response reaches file42 even if the promise hangs (service worker
      // suspension, Chrome throttling, etc.). Without a timeout, the action
      // queue blocks for 3–11 s.
      let responded = false;
      const safeSendRes = (r) => { if (!responded) { responded = true; sendRes(r); } };
      const t0 = performance.now();
      const timeoutId = setTimeout(() => {
        safeSendRes({ ok: true, timeout: true });
        if (key !== "::") __acExecDedupRelease(key);
        console.warn(`[AC-DUP] execUserFunc TIMEOUT tab=${tabId} script=${ctx.scriptId} +${Math.round(performance.now()-t0)}ms`);
      }, 3000); // 3 s safety timeout
      // AC-MV3 FIX (2026-08-10, FEATURES-MV3.md §7-5): target the SENDER's frame
      // (frameId) — plain script runs come from file42 in frame 0; runInFrames
      // subframe calls come from their own frame. userScripts.execute with
      // target:{tabId} alone injects into EVERY frame — each subframe creates
      // a user-script world context and delays the promise / floods the page
      // with duplicate script runs.
      __acEnsureWorld();  // AC-MV3 round 12: relax world CSP (blob:/data: for import) before first execute
      chrome.userScripts.execute({
        target: { tabId, frameIds: [frameId] },
        js: [{ code: jsCode }],
        world: "USER_SCRIPT",
        injectImmediately: true
      }).then(() => {
        clearTimeout(timeoutId);
        if (key !== "::") __acExecDedupRelease(key);
        console.log(`[AC-MV3] execUserFunc → userScripts.execute (tab ${tabId}) +${Math.round(performance.now()-t0)}ms`);
        safeSendRes({ ok: true, st: __acStateDump() });
      })
        .catch(e => {
          clearTimeout(timeoutId);
          if (key !== "::") __acExecDedupRelease(key);
          const m = String(e && e.message || e);
          if (/disabled|permission|granted|allow user scripts/i.test(m)) __acExecUsFailed = true;
          // AC-MV3 UX (2026-08-09): map Chrome's raw protected-page
          // rejection to the friendly message (the URL check also covers
          // the Web Store, whose rejection text varies across versions).
          if (/cannot access (a )?(chrome|chrome-extension|devtools)|Cannot access a chrome/i.test(m) ||
              __acIsProtectedPage(sender && sender.tab && sender.tab.url)) {
            __acNotifyProtected();
            safeSendRes({ error: __acProtectedMsg });
          } else {
            safeSendRes({ error: m });
          }
        });
      return true;
    }

    // file42.js signals completion of an execUserFunc run → move key from
    // in-flight → completed (LRU) so post-hoc burst duplicates are suppressed.
    if (msg.type === "execUserFuncDone") {
      const k = (msg.tabId || "") + ":" + (msg.scriptId || "") + ":" + (msg.trigInstId || "");
      if (k !== ":::") __acExecDedupRelease(k);
      sendRes({ ok: true });
      return true;
    }

    switch (msg.cmd) {
      case "ping":
        const pingResponse = { ok: true, connected, leader: "sw" };
        // Send buffered native messages to newly connected page
        if (nativeMsgBuffer.length > 0 && connected) {
          pingResponse.buffered = nativeMsgBuffer.map(m => ({ ...m, _live: false }));
          console.log(`[AC-MV3-SW] Replaying ${nativeMsgBuffer.length} buffered messages to new page`);
        }
        sendRes(pingResponse); return true;
      case "sandboxMessage":
        // Offscreen document relays a result/userAPI message from the
        // file23.html sandbox iframe → dispatch to file48's "message" handler
        // (registers via window.addEventListener("message") → __acSandboxMsgListeners).
        if (typeof self.__acDispatchSandboxMessage === 'function') {
          self.__acDispatchSandboxMessage(msg.data);
        }
        sendRes({ ok: true }); return true;
      case "postMsg":
        // Settings page pushed a new config → refresh the in-SW trigger tables
        if (msg.type === 60) refreshConfigInSW();
        // AC-CAPTURE heal: type-40 tracking lives inside postMsg() (single
        // choke point — every send path routes through it).
        sendRes({ ok: postMsg(msg.type, msg.data) }); return true;
      case "postWithCb":
        // The settings-page installer panel pings the native every second
        // (file2.js m(Infinity, 1000)) while it is open. Until the engine is
        // up, Zero does NOT answer type 920 (ping is handled by the engine)
        // -> every ping would hang until its 5s timeout, flooding the console
        // with "timeout for type 920". While the handshake is not complete,
        // answer immediately without sending to the native.
        if (msg.type === 920 && !connected) {
          // AC-MV3 FIX (2026-08-07): fresh-install auto-reload. The install UI
          // pings every 1s while it waits for the native; if the host lookup
          // is cached as "not found" (per SW instance), retries never succeed
          // and the user would have to reload the extension manually. After
          // 20 pings with a DEAD port (never during an engine deploy — the
          // port is alive then), reload once; the fresh SW finds the host.
          if (!port) __acNotReadyPings++;
          if (!__acInstallAutoReloaded && !port && __acNotReadyPings >= 20) {
            __acInstallAutoReloaded = true;
            console.warn("[AC-MV3] Install UI pinging but host not found — auto-reloading extension (Chrome caches host-not-found per SW instance)");
            try { chrome.storage.local.set({ __acInstallAutoReload: 1 }); } catch(e) {}
            setTimeout(() => { try { chrome.runtime.reload(); } catch(e) {} }, 500);
          }
          sendRes({ ok: false, error: "native not ready" });
          return true;
        }
        // AC-MV3 FIX (2026-08-30): page boot ping (file2 m(3,500), type 920).
        // On the FIRST import after an extension reload the fresh settings tab
        // boots while the native is still busy with the SW startup burst (wmic
        // scans, window enum, ~30 type-400 moves, config chain) — it cannot
        // answer within the page's 500ms timeout → m() returns false → FALSE
        // "Native Component not working" dialog (NH-noConnex) on a healthy
        // install (previously hidden by the invisible page, exposed by the
        // forced-visible fix). The SW holds the live native port — answer
        // "pong" directly (same semantics as the native's ping reply).
        if (msg.type === 920 && connected && port && handshakeDone) {
          sendRes({ ok: true, result: "pong" });
          return true;
        }
        // Rate limit ping messages (type 920) to prevent native component overload
        if (msg.type === 920) {
          const now = Date.now();
          if (now - lastPingTime < MIN_PING_INTERVAL) {
            const wait = MIN_PING_INTERVAL - (now - lastPingTime);
            console.log(`[AC-MV3] Rate limiting ping, waiting ${wait}ms`);
            setTimeout(() => {
              lastPingTime = Date.now();
              postWithCb(msg.type, msg.data, msg.timeout)
                .then(r => sendRes({ ok: true, result: r }))
                .catch(e => sendRes({ ok: false, error: e.message }));
            }, wait);
          } else {
            lastPingTime = now;
          }
        }
        postWithCb(msg.type, msg.data, msg.timeout)
          .then(r => sendRes({ ok: true, result: r }))
          .catch(e => sendRes({ ok: false, error: e.message }));
        return true;
      case "acPlayNative":
        // Offscreen document → SW native bridge (playAudio FEATURES-MV3.md §7-1): the
        // offscreen doc has no native port. Type 255 (file READ — playAudio
        // "Sound file" actions) uses the bundle's _If — the chunked
        // reassembly (type 810 → file61 f store) is bundle-internal and
        // unreachable from raw postWithCb. Other types (294 = system sound
        // by alias) go through postWithCb raw.
        if (msg.type === 255 && typeof _If === "function") {
          try {
            _If(msg.payload && msg.payload.path)((r) => sendRes({ ok: true, result: r }));
          } catch (e) {
            sendRes({ ok: false, error: String(e && e.message || e) });
          }
          return true;
        }
        postWithCb(msg.type, msg.data || msg.payload, 8000)
          .then(r => sendRes({ ok: true, result: r }))
          .catch(e => sendRes({ ok: false, error: e.message }));
        return true;
      case "configLoaded":
        // Page finished _lr/_Gf config chain — now safe to send type 21 (startup)
        finishStartup();
        sendRes({ ok: true }); return true;
      case "windowEnumDone":
        // Page finished _Ry/_oj window enumeration — now safe to send type 72
        sendType72();
        sendRes({ ok: true }); return true;
      case "discardTabs":
        // Some chrome.tabs APIs (like discard) may not work from extension page context
        // in Chrome 150+. Route through SW where they're guaranteed available.
        Promise.all((msg.tabIds || []).map(id => chrome.tabs.discard(id)))
          .then(r => sendRes({ ok: true, result: r }))
          .catch(e => sendRes({ ok: false, error: e.message }));
        return true;
      case "reconnect":
        // AC-MV3 FIX (2026-08-06): never spawn a duplicate host while a
        // connection exists or a handshake is in flight — every connectNative
        // starts a NEW Zero→engine pair and the old engine would linger as an
        // orphan (file2.js z() sends reconnect twice after install/repair).
        if (__acConnecting || (connected && handshakeDone)) {
          sendRes({ ok: true, already: true });
          return true;
        }
        // AC-MV3 FIX (2026-08-07): a page-driven reconnect after a fresh
        // install must reset the never-connected failure counter (the
        // auto-retry loop may have stopped — see onDisc).
        errors = 0; retries = 0;
        connect(); sendRes({}); return true;
      case "getStatus":
        sendRes({ connected, connectTime }); return true;
      case "getOptPerms":
        chrome.permissions.getAll(r => sendRes(r)); return true;

      // Tabs
      case "tabsQuery":     chrome.tabs.query(msg.query, r => sendRes(r)); return true;
      case "tabsCreate":    chrome.tabs.create(msg.props, t => sendRes(t)); return true;
      case "tabsUpdate":    chrome.tabs.update(msg.tabId, msg.props, t => sendRes(t)); return true;
      case "tabsRemove":    chrome.tabs.remove(msg.tabIds, () => sendRes({})); return true;
      case "tabsGetZoom":   chrome.tabs.getZoom(msg.tabId, z => sendRes(z)); return true;
      case "tabsSetZoom":   chrome.tabs.setZoom(msg.tabId, msg.zoom, () => sendRes({})); return true;
      case "tabsMove":      chrome.tabs.move(msg.tabIds, msg.props, r => sendRes(r)); return true;
      case "tabsReload":    chrome.tabs.reload(msg.tabId, null, () => sendRes({})); return true;
      case "tabsDuplicate": chrome.tabs.duplicate(msg.tabId, t => sendRes(t)); return true;
      case "tabsDiscard":   chrome.tabs.discard(msg.tabId, () => sendRes({})); return true;
      case "tabsCapture":   chrome.tabs.captureVisibleTab(msg.winId, { format: "png" }, d => sendRes(d)); return true;

      // Windows
      case "winsGetAll":    chrome.windows.getAll({ populate: !!msg.populate }, r => sendRes(r)); return true;
      case "winsGet":       chrome.windows.get(msg.winId, { populate: !!msg.populate }, w => sendRes(w)); return true;
      case "winsCreate":    chrome.windows.create(msg.props, w => sendRes(w)); return true;
      case "winsUpdate":    chrome.windows.update(msg.winId, msg.props, () => sendRes({})); return true;
      case "winsRemove":    chrome.windows.remove(msg.winId, () => sendRes({})); return true;

      // Bookmarks
      case "bmGetTree":    chrome.bookmarks.getTree(r => sendRes(r)); return true;
      case "bmGetChildren": chrome.bookmarks.getChildren(msg.id, r => sendRes(r)); return true;
      case "bmCreate":     chrome.bookmarks.create(msg.props, r => sendRes(r)); return true;
      case "bmUpdate":     chrome.bookmarks.update(msg.id, msg.props, r => sendRes(r)); return true;
      case "bmRemove":     chrome.bookmarks.remove(msg.id, () => sendRes({})); return true;

      // Sessions
      case "sessGetRecent": chrome.sessions.getRecentlyClosed({ maxResults: msg.max || 25 }, r => sendRes(r)); return true;
      case "sessRestore":   chrome.sessions.restore(msg.sessionId, () => sendRes({})); return true;

      // Scripting
      case "execScript":
        if (msg.files && msg.files.length) {
          // NOTE: `matchAboutBlank` is NOT a valid target property in MV3
          // scripting.executeScript (only tabId/frameIds/documentIds/allFrames).
          chrome.scripting.executeScript({
            target: { tabId: msg.tabId, allFrames: !!msg.allFrames },
            files: msg.files,
            injectImmediately: true
          }).then(r => sendRes(r.map(x => x.result))).catch(e => sendRes({ error: e.message }));
        } else if (msg.func) {
          // Code strings cannot be evaluated in the SW (extension CSP forbids
          // eval/new Function) — inject via the page's MAIN world instead.
          __acInjectCode(msg.tabId, msg.func, { allFrames: !!msg.allFrames }, r => sendRes({ result: r }));
        } else {
          sendRes({ error: "nothing to inject" });
        }
        return true;
      case "insertCSS":
        chrome.scripting.insertCSS({
          target: { tabId: msg.tabId }, files: msg.files
        }).then(() => sendRes({})).catch(e => sendRes({ error: e.message }));
        return true;

      // Permissions
      case "permsContains": chrome.permissions.contains(msg.perms, r => sendRes(r)); return true;
      case "permsRequest":  chrome.permissions.request(msg.perms, r => sendRes(r)); return true;
      case "permsRemove":   chrome.permissions.remove(msg.perms, r => sendRes(r)); return true;

      // Context menus
      case "ctxCreate":  chrome.contextMenus.create(msg.props, () => sendRes({})); return true;
      case "ctxRemoveAll": chrome.contextMenus.removeAll(() => sendRes({})); return true;
      case "ctxUpdate":  chrome.contextMenus.update(msg.id, msg.props, () => sendRes({})); return true;

      // Other
      case "getDisplayInfo": chrome.system.display.getInfo(r => sendRes(r)); return true;
      case "notifCreate": chrome.notifications.create(msg.opts, id => sendRes(id)); return true;
      case "idleQuery":   chrome.idle.queryState(msg.sec, s => sendRes(s)); return true;
      case "fileAcc":     chrome.extension.isAllowedFileSchemeAccess(r => sendRes(r)); return true;
      case "incogAcc":    chrome.extension.isAllowedIncognitoAccess(r => sendRes(r)); return true;
    }
    return false;
  });

  // ======== KEEPALIVE ========

  // Send native keepalive every 25 seconds (native {type, content} format)
  let keepaliveInterval;

  chrome.alarms.onAlarm.addListener(a => {
    if (a.name !== "ac-keepalive") return;
    if (port && connected) {
      try { port.postMessage({ type: 905, content: {} }); } catch(e) {}
    }
    console.log("[AC-MV3] alarm tick: connected=" + connected + " handshakeDone=" + handshakeDone +
      " startupSent=" + startupSent);
  });

  // Also setInterval as backup (alarms can be delayed)
  /**
   * Keep the SW alive: chrome.alarms + a self-waker + the persistent native
   * port (any API call resets the SW idle timer).
   */
  function startKeepalive() {
    if (keepaliveInterval) clearInterval(keepaliveInterval);
    const sendPing = () => {
      if (port && connected) {
        try {
          port.postMessage({ type: 905, content: {} });
          console.log("[AC-MV3] Keepalive sent (905)");
        } catch(e) {
          console.warn("[AC-MV3] Keepalive failed:", e.message);
        }
      }
    };
    // Send first ping after 10s, then every 20s
    setTimeout(sendPing, 10000);
    keepaliveInterval = setInterval(sendPing, 20000);
  }

  // ======== INIT ========

  chrome.runtime.onInstalled.addListener(det => {
    if (det.reason === "install") chrome.runtime.openOptionsPage();
  });

  // AC-MV3 FIX (2026-08-08, FEATURES-MV3.md §7-7): NO chrome.action.onClicked listener here.
  // The BUNDLE (file62_mv3.js) is the single handler — it runs the trigger
  // assigned to the toolbar-icon click (storage key brwrAction.trigActId) or
  // falls back to _sh() which opens the settings page when no trigger is
  // assigned (exact MV2 semantics). An sw.js listener on the SAME
  // chrome.action.onClicked (browserAction is aliased to action in
  // sw_prelude.js) would fire openOptionsPage() UNCONDITIONALLY — breaking
  // the "assigned trigger → trigger only, no settings" case (legacy
  // brwrAction key from old .acs imports; not reachable via the current UI).

  // AC-MV3 FIX (2026-08-07): create the "Emergency repair" context-menu item
  // from the SW at startup. file47.js `_nk()` creates it only when the
  // settings page loads, so after an extension reload the menu item is gone
  // until the page opens. The create() patch above skips the page's duplicate
  // once __acCtxMenuOwned is set. The CLICK is handled by the BUNDLE
  // (file62_mv3.js onClicked → `_co(1,!0)` — badge Wait → type 55 → native
  // restarts the engine → reload of open settings tabs; `_co` was fixed for
  // the SW in file34_mv3.js). Do NOT add a sw.js onClicked handler here — it
  // would DUPLICATE the bundle's (two type-55 sends, badge race — user VM
  // 23:41: Wait blinked, no OK).
  try {
    chrome.contextMenus.removeAll(() => {
      try {
        chrome.contextMenus.create(
          { id: "reloadExtn", title: "Emergency repair", contexts: ["action"] },
          () => { self.__acCtxMenuOwned = true; }
        );
      } catch(e) { console.warn("[AC-MV3] Emergency-repair menu create failed:", e.message); }
    });
  } catch(e) { console.warn("[AC-MV3] contextMenus.removeAll failed:", e.message); }

  // AC-MV3 round 13 (2026-08-06): world-warmup (rounds 9-12) REMOVED — it was
  // harmful. Chrome SERIALIZES userScripts.execute PER TAB, and the first
  // execute on a fresh page costs ~4-5s (one-time userScripts subsystem
  // init). Warmup no-ops did NOT pre-create worlds; they only queued an
  // extra execute that BLOCKED the script's real calls behind its init
  // (user VM 19:27: first execUserFunc +4909ms — was +6-11ms before warmup;
  // runInPageCtx(func) still +4038ms). The 4-5s one-time cost is absorbed by
  // n()'s 8000ms fallback (round 13) instead — the first call simply waits,
  // no retry, no double execution. Subsequent calls on the tab are fast.

  // ======== FAVICON WARMUP (2026-08-08) ========
  // The favicon cache patch (mv3_native_shim.js) pre-fetches ONLY the tabs
  // present at init (~1s after load, via Google s2 into the in-SW _7o cache)
  // — and if _Yp is not populated yet (native handshake / window enum still
  // running), that pre-fetch does NOTHING. Result: the FIRST open of a
  // custom tab menu (openMenu → _Zs(chrome://favicon/…)) shows EMPTY icons
  // for every tab — the background load only helps the SECOND open.
  // FIX: (a) warm new tabs on chrome.tabs.onCreated + onUpdated (favIconUrl)
  // — calls the patched _Zs, which caches via Google s2 in the background;
  // (b) delayed sweeps at SW start (the init pre-fetch may run before _Yp
  // exists); (c) re-sweep after every config-chain completion (configLoaded)
  // — the fresh window enum has just populated _Yp.
  // NOTE: `_7o` (file13) and `_Yp` (file34_mv3) are top-level let/var of the
  // imported bundle — shared global lexical environment, accessible as free
  // variables here (same mechanism as _Yh). The patched _Zs is a global
  // function (file13 declaration + mv3_native_shim wrap).
  /**
   * Warm the favicon cache for a tab (both cache keys: raw favIconUrl and the
   * chrome://favicon/ form the menu asks for).
   * @param {object} tab — chrome.tabs.Tab
   */
  const __acFavWarm = (tab) => {
    try {
      if (!tab || typeof _Zs !== 'function') return;
      // Key 1: the raw favIconUrl (data: URIs resolve synchronously; https
      // URLs fetch via XHR).
      if (tab.favIconUrl) _Zs(tab.favIconUrl)(() => {});
      // Key 2 — THE MENU KEY: custom tab menus call _Zs("chrome://favicon/"
      // + url) (file26 `_ig`), which is a DIFFERENT cache key than the raw
      // favIconUrl. Warming only the raw key left the FIRST menu open empty
      // (user VM 2026-08-08 23:00: first open partial, second open ~all —
      // the first open's own background fetches filled the cache). The
      // patched _Zs handles the chrome://favicon/ key (Google s2 background
      // fill into _7o), so this pre-warms exactly what the menu will ask.
      const u = tab.url || tab.pendingUrl;
      if (u && !/^(data|javascript|chrome|about|view-source):/i.test(u)) {
        _Zs('chrome://favicon/' + u)(() => {});
      }
    } catch (e) {}
  };
  /**
   * Sweep all known tabs and warm their favicons into the cache.
   */
  const __acFavSweep = () => {
    try {
      if (typeof _Yp === 'object' && _Yp) {
        for (const id in _Yp) {
          const t = _Yp[id];
          if (t) __acFavWarm(t);
        }
      }
    } catch (e) {}
  };
  try {
    if (chrome.tabs && chrome.tabs.onCreated) chrome.tabs.onCreated.addListener(__acFavWarm);
    if (chrome.tabs && chrome.tabs.onUpdated) {
      chrome.tabs.onUpdated.addListener((tabId, changeInfo) => {
        if (changeInfo && (changeInfo.favIconUrl || changeInfo.url)) {
          __acFavWarm({ favIconUrl: changeInfo.favIconUrl, url: changeInfo.url });
        }
      });
    }
    // Delayed passes: the bundle's init pre-fetch may run before _Yp is
    // populated (native handshake / enum) — re-sweep a few times at start.
    [1500, 4000, 9000].forEach(ms => setTimeout(__acFavSweep, ms));
    // AC-CAPTURE heal: track open extension pages — if the last settings
    // page closes while capture is armed (tester/combo editor open), release
    // capture fast (the page can no longer send its own type-40 OFF).
    if (chrome.tabs && chrome.tabs.onRemoved) chrome.tabs.onRemoved.addListener(() => __acCheckExtPages());
    __acCheckExtPages();
    // AC-MV3 FIX (2026-08-30): stale-armed sweep — independent of the 760
    // stream (a stuck capture with an IDLE mouse produces no 760s, but still
    // suppresses 750s). Every 15s: release an armed capture that has seen no
    // 750 for AC_CAPTURE_STALE_ARMED_MS (5 min — see the 760 handler; the
    // page's own OFF never came — page died/reloaded or the editor session
    // was abandoned).
    setInterval(() => {
      try {
        if (__acCaptureOn && Date.now() - __acCaptureT > AC_CAPTURE_STALE_ARMED_MS) {
          __acCaptureRelease("capture armed for >" + (AC_CAPTURE_STALE_ARMED_MS / 60000) + "min with no 750 (sweep) — stale editor/test session", 1);
        }
      } catch(e) {}
    }, 15000);
  } catch (e) {}

  // Local command bridge: the in-SW core engine emits commands via
  // chrome.runtime.sendMessage (see sw_prelude.js) which are routed here.
  self.__acLocalHandlers = {
    ping: (m, cb) => {
      const r = { ok: true, connected, leader: "sw" };
      if (nativeMsgBuffer.length > 0 && connected) {
        r.buffered = nativeMsgBuffer.map(x => ({ ...x, _live: false }));
        console.log(`[AC-MV3-SW] Replaying ${nativeMsgBuffer.length} buffered messages to new page`);
      }
      cb && cb(r);
    },
    windowEnumDone: (m, cb) => { sendType72(); cb && cb({ ok: true }); },
    configLoaded: (m, cb) => {
      // AC-MV3 FIX (2026-08-08): push toolbar-button props (title/icon) to
      // the toolbar-button extensions whenever the config chain completes
      // (startup, reconnect, force refresh). MV2 called _Pk() in its startup
      // init (file62.js); the SW chain (_lr→_Gf) never did → buttons kept
      // their default icons until clicked (their own TBBtnInit only woke the
      // SW-brain then). _Pk is bundle-global (file47) and uses the sw.js-
      // patched _zr/_Ve (fetch + OffscreenCanvas) + the real
      // chrome.runtime.sendMessage — safe in the SW. Re-pushes after a
      // reconnect are harmless (idempotent setTitle/setIcon).
      if (typeof _Pk === 'function') { try { _Pk(); } catch (e) { console.warn('[AC-MV3] _Pk (toolbar buttons) failed:', e && e.message); } }
      // Favicon warmup: the config chain just ran → _Yp is fresh from the
      // window enum → fill the _7o cache for all known tabs (first menu
      // open shows icons).
      if (typeof __acFavSweep === 'function') { try { __acFavSweep(); } catch (e) {} }
      finishStartup();
      cb && cb({ ok: true });
    },
    reconnect: (m, cb) => {
      if (__acConnecting || (connected && handshakeDone)) { cb && cb({ ok: true, already: true }); return; }
      // AC-MV3 FIX (2026-08-07): reset the never-connected failure counter so
      // a post-install reconnect works even after the auto-retry loop stopped.
      errors = 0; retries = 0;
      connect(); cb && cb({ ok: true });
    },
    getStatus: (m, cb) => cb({ connected, connectTime })
  };

  // Direct native send for the in-SW shim (bypasses self-messaging)
  self._acNativeSend = (a, b, c, g) => {
    if (c) {
      // AC-MV3 FIX (2026-08-08): Emergency Repair (type 55) with a DEAD port
      // cannot repair anything — the native host (Zero/engine) is not
      // installed or the engine files are gone. Open the options page: on a
      // fresh install the install pane shows (natHostInstalled absent);
      // otherwise the settings page. The bundle `_co(1,!0)` set the "Wait"
      // badge BEFORE the send — with no port there is no SW reload (the MV2
      // page-reload path) to replace it, so show the FINAL status here
      // (MV2's reloaded page does `_nt("showNotif")` → "Error" when the
      // native is down; user VM 01:55: badge stuck on "Wait" forever).
      if (a === 55 && !port) {
        console.warn("[AC-MV3] Emergency repair: native not connected (Zero/engine missing) — opening install page");
        try { chrome.runtime.openOptionsPage(); } catch(e) {}
        try {
          chrome.action.setBadgeBackgroundColor({ color: "#F00" });
          chrome.action.setBadgeText({ text: "Error" });
        } catch(e) {}
        setTimeout(() => { try { chrome.action.setBadgeText({ text: "" }); } catch(e) {} }, 2000);
        if (c) { try { c(_g); } catch(e) {} }
        return true;
      } else if (a === 55) {
        // MV2 semantics (file34.js _co(1) + file61.js _Lk): type 55 is sent,
        // then the extension RELOADS its background page → port drop → Zero
        // exits on EOF → the fresh page reconnects → fresh Zero+engine with
        // FRESH hooks. The SW IS the background page in MV3, so the repair
        // reloads the SW itself (chrome.runtime.reload()): user-verified
        // (VM 2026-08-08) — after an extension reload the hotkeys bind
        // IMMEDIATELY, whereas the port-drop-only cycle (FIX 14) sometimes
        // left the old engine alive without a working pipe (dead Zero) →
        // triggers never arrived. NO engine taskkill (FIX 14): hard-killing
        // leaves dangling global hooks → ~40s input stall (VM 01:36).
        // The badge OK is shown by the FRESH SW (storage flag __acRepairBadge
        // survives the reload; consumed in proceedAfterFileCheck).
        console.warn("[AC-MV3] Emergency repair: type 55 sent — reloading SW (MV2 background-page reload)");
        postWithCb(55, b, 5000).then(r => {
          try { c(r); } catch(e) {}
          __acEmergencyRestartNative();
        }).catch(() => {
          try { c(_g); } catch(e) {}
          __acEmergencyRestartNative();
        });
        return true;
      }
      // Type 250 (file write) needs a long timeout (see postWithCb).
      postWithCb(a, b, g || (a === 250 ? 30000 : 5000)).then(r => { try { c(r); } catch(e) {} })
        .catch(() => { try { c(_g); } catch(e) {} });
    } else {
      // AC-CAPTURE heal: type-40 tracking lives inside postMsg() (single
      // choke point — this path routes through it).
      postMsg(a, b);
    }
    return true;
  };

  // AC-MV3 FIX (2026-08-08): Emergency Repair = reload the SW itself — the
  // MV2 background-page-reload equivalent. A fresh SW re-runs connectNative
  // → fresh Zero → fresh engine with fresh hooks, and the settings page
  // re-arms via the shim. User-verified (VM 2026-08-08): hotkeys bind
  // IMMEDIATELY after an extension reload, whereas the port-drop-only cycle
  // (FIX 14) sometimes left the old engine alive without a working pipe.
  // The badge-OK flag is persisted in chrome.storage.local so the FRESH SW
  // can show it (consumed in proceedAfterFileCheck, like __acInstallAutoReload).
  /**
   * Emergency Repair: persist the badge-OK flag and reload the SW — the MV3
   * equivalent of the MV2 background-page reload (port drop → fresh Zero →
   * fresh engine). Never hard-kills the engine.
   */
  function __acEmergencyRestartNative() {
    // AC-MV3 FIX (2026-08-12, FEATURES-MV3.md §7-15): persist the repair
    // DIAGNOSTICS across the reload. MV2 kept showNotif/diagnostics in the
    // background page's real localStorage, which survived the reload; our
    // in-memory localStorage shim dies with the SW → the fresh SW's file34
    // `_nt("showNotif")` branch read null and never showed _Kg/_Ht. Read the
    // one-shot flags BEFORE the reload and hand them to the fresh SW via
    // chrome.storage.local (consumed in proceedAfterFileCheck, like
    // __acRepairBadge). _j reads without deleting — the memory dies anyway.
    try {
      if (typeof _j === 'function') {
        const diag = _j('diagnostics');
        const show = _j('showNotif');
        console.warn('[AC-MV3] repair persist: show=' + !!show + ' diag=' + (diag ? 'yes' : 'no'));
        if (show || diag) {
          chrome.storage.local.set({ __acRepairDiag: { showNotif: !!show, diagnostics: diag || null } }, () => {});
        }
      } else {
        console.warn('[AC-MV3] repair persist: _j MISSING — diagnostics not persisted');
      }
    } catch (e) { console.warn('[AC-MV3] repair diagnostics persist failed:', e.message); }
    try {
      chrome.storage.local.set({ __acRepairBadge: true }, () => {
        try { chrome.runtime.reload(); } catch(e) {}
      });
    } catch(e) {
      try { chrome.runtime.reload(); } catch(e2) {}
    }
  }

  // AC-MV3 FIX (2026-08-08): suppress "Could not establish connection"
  // unhandled rejections — page-less fire-and-forget broadcasts (no open
  // extension pages at SW start / after a native disconnect) reject with
  // this error and pollute the SW console ("Uncaught (in promise)"). Only
  // these connection errors are swallowed; real failures still surface.
  self.addEventListener('unhandledrejection', ev => {
    const m = ev && ev.reason && ev.reason.message;
    if (m && /Could not establish connection|Receiving end does not exist/.test(m)) {
      ev.preventDefault();
    }
  });

  connect();

  // Self-waker: calling an extension API every 20s resets the SW idle timer
  // (Chrome 110+: "calling an extension API resets this timer"). Together with
  // the permanent native messaging port (Chrome 105+: connectNative keeps the
  // SW alive) this keeps the SW alive indefinitely — critical in SW-brain mode.
  setInterval(() => { chrome.runtime.getPlatformInfo().catch(() => {}); }, 20000);

  console.log("[AC-MV3] SW started (SW-brain), connecting to native host...");
  setTimeout(() => {
    console.log("[AC-MV3] Connection status:", {
      connected, port: !!port, portOk: portConnectedOk,
      core: typeof _6y === 'function' && typeof _Gf === 'function' ? 'LOADED' : 'MISSING',
      native: typeof _acNativeSend === 'function' ? 'hooked' : 'NOT hooked'
    });
  }, 3000);
})();
