/**
 * AutoControl MV3 Compatibility Shim
 *
 * Loaded FIRST in main.html to provide MV3 compatibility for legacy scripts.
 *
 * What this does:
 * 1. Patches chrome.extension.* APIs that don't exist in MV3
 * 2. Provides a fallback for _Yk.extension.getBackgroundPage()
 * 3. Creates a bridge to the Service Worker for native messaging
 * 4. Listens for native events from SW and dispatches to page
 * 5. Reads natHostInstalled from storage (file62_mv3.js doesn't do this)
 * 6. Signals _Eu so file2.js doesn't hang waiting
 */
(function() {
  'use strict';

  // Only needed when there's no real background page (MV3)
  if (chrome.extension.getBackgroundPage && chrome.extension.getBackgroundPage()) {
    return; // Background page exists, no shim needed
  }

  /**
   * MV2-like silent console: page diagnostics OFF by default, enabled via
   * Options → Advanced Options → "Log settings page" (advOpts.logSettings),
   * live via storage.onChanged; console.error stays. Startup output is
   * buffered until the async advOpts read resolves.
   */
  const __acOrigConsole = {
    log: console.log.bind(console),
    info: console.info.bind(console),
    warn: console.warn.bind(console),
    debug: console.debug.bind(console)
  };
  let AC_LOG_SETTINGS = false; // MV2-like silence default; corrected by the read below
  let __acLogBuf = [];
  let __acLogApplied = false;
  /**
   * Emit a log line through the ORIGINAL console method (bypasses the
   * gating patch).
   * @param {string} m — method name (log/info/warn/debug)
   * @param {Array} args — arguments
   */
  function __acEmitLog(m, args) { try { __acOrigConsole[m].apply(console, args); } catch (e) {} }
  /**
   * Apply the current AC_LOG_SETTINGS flag to the page console methods and
   * flush the buffered startup output.
   */
  function __acApplyLogging() {
    if (!__acLogApplied) return; // still buffering
    const on = AC_LOG_SETTINGS;
    for (const m of ['log', 'info', 'warn', 'debug']) {
      try { console[m] = AC_LOG_SETTINGS ? __acOrigConsole[m] : function(){}; } catch (e) {}
    }
    if (__acLogBuf) {
      const buf = __acLogBuf; __acLogBuf = null;
      if (on) for (const [m, args] of buf) __acEmitLog(m, args);
    }
  }
  for (const m of ['log', 'info', 'warn', 'debug']) {
    try {
      console[m] = function () {
        try { __acLogBuf.push([m, Array.prototype.slice.call(arguments)]); if (__acLogBuf.length > 400) __acLogBuf.shift(); } catch (e) {}
      };
    } catch (e) {}
  }
  try {
    chrome.storage.local.get("advOpts", r => {
      AC_LOG_SETTINGS = !!(r && r.advOpts && r.advOpts.logSettings);
      __acLogApplied = true;
      __acApplyLogging();
    });
  } catch (e) { __acLogApplied = true; __acApplyLogging(); }
  try {
    chrome.storage.onChanged.addListener((changes, area) => {
      if (area === "local" && changes.advOpts) {
        AC_LOG_SETTINGS = !!((changes.advOpts.newValue || {}).logSettings);
        __acApplyLogging();
      }
    });
  } catch(e) {}
  setTimeout(() => { if (!__acLogApplied) { __acLogApplied = true; __acApplyLogging(); } }, 500);

  console.log("[AC-MV3] Shim active (no background page), url:", typeof location !== 'undefined' ? location.href : '(no location)');

  // ======== LEADER TRACKING ========
  // The service worker is ALWAYS the leader in SW-brain mode: the SW runs the
  // config chain and executes triggers. This page is UI-only and must NOT
  // execute triggers or the config chain (mv3_native_shim.js checks _leader).
  window._leader = 'page';

  // ======== PATCH chrome.extension.* FOR MV3 ========

  // getBackgroundPage() → return window (scripts loaded in-page)
  if (chrome.extension) {
    const origGetBg = chrome.extension.getBackgroundPage;
    chrome.extension.getBackgroundPage = () => window;

    // getViews() → search tabs for extension pages
    const origGetViews = chrome.extension.getViews;
    chrome.extension.getViews = (opts) => {
      if (opts && opts.tabId) {
        // AC-MV3 FIX (2026-08-30, SFE Import, take 2): MV2 `_0s("none")`
        // (file67) resolves the settings window via
        // `_Yk.extension.getViews({tabId: <main.html tab>})`. chrome.
        // extension.getViews DOES exist in MV3 extension pages (only the
        // SW lacks it), so the ORIGINAL function resolves the window that
        // actually hosts that tab — the MV2-equivalent answer. The old
        // stub returned [] (no-op import) and my first fix returned
        // [window] unconditionally, which routed `_lj` into the SFE tab
        // itself — where `_bd` writes through the SFE file-proxy into the
        // editor's file model `m`, NOT into chrome.storage.local (file78
        // _lj/_uw now bypass the proxy with a direct
        // chrome.storage.local.set — see file78.js). Fallback [window]
        // only when the native API is unavailable and THIS page is a
        // main.html window (a main.html tab is the only thing _Qo("none")
        // ever asks for).
        try {
          const views = origGetViews ? origGetViews(opts) : [];
          if (views && views.length) return views;
        } catch (e) {}
        if (location.pathname.endsWith('/main.html')) return [window];
        return [];
      }
      // Return this window as fallback
      return [window];
    };
  }

  // ======== NATIVE MESSAGING BRIDGE ========

  const swMessageQueue = [];
  let swConnected = false;
  let lastSeq = 0;

  // Listen for messages from SW (from both chrome.runtime.sendMessage and chrome.tabs.sendMessage)
  // The SW broadcasts via BOTH delivery methods (tabs + runtime), which means the SAME
  // message arrives TWICE in extension pages (like main.html). The _seq field lets us
  // deduplicate — only process each unique sequence number once.
  chrome.runtime.onMessage.addListener((msg, sender) => {
    if (!msg._sw) return false;

    // Track the current leader (offscreen head vs settings page) from SW broadcasts
    if (msg._leader) window._leader = msg._leader;
    if (msg.type === 'leaderChange') {
      console.log("[AC-MV3] Leader changed to:", msg.leader);
      window._leader = msg.leader;
    }

    // Dedup: same message arrives via tabs AND runtime. Skip if we've seen this seq.
    if (msg._seq && msg._seq <= lastSeq) return false;
    lastSeq = msg._seq || lastSeq;

    // Log ALL incoming SW messages (verbose — gated by AC_LOG_SETTINGS;
    // was console.error "for visibility", but real errors must stay
    // console.error and this is a debug line — 2026-08-08).
    console.warn("[AC-MV3-SHIM] MSG type=" + (msg.type || '?') + " nativeType=" + (msg.nativeType || '?'));

    // Dispatch SW messages to page
    const event = new CustomEvent('ac-sw-msg', { detail: msg });
    window.dispatchEvent(event);

    // Also store for polling
    swMessageQueue.push(msg);
    return false; // Fire-and-forget broadcast — no response needed
  });

  // ======== PAGE INIT ========

  // AC-MV3 FIX (2026-08-07): the native-installed flag MUST reflect reality.
  // file2.js branches on it: `_nd ? (ping → natHostNotFound "Something went
  // wrong. The native component is not working.") : (install pane)`. The
  // hardcoded `true` made a FRESH install (native never installed) show the
  // error dialog instead of offering installation. Default false; overridden
  // by the storage read below (fast) and by the SW ping callback
  // (connected → true). file2.js checks _nd only after _Eu.wait() (≥500ms),
  // so the async read normally wins.
  window._nd = false;

  // Read natHostInstalled from storage (file62_mv3.js skips this; file62.js
  // with its `_nd=b.natHostInstalled` init is NOT loaded on the page).
  // AC-MV3 FIX (2026-08-07): ALWAYS set _nd from storage (including false) —
  // the SW ping callback no longer overrides it. Otherwise, after a native
  // uninstall, the settings page reloading while the SW still thinks it is
  // connected (the port dies a moment later) would restore _nd=true →
  // "Something went wrong" instead of the install pane (user VM 22:50).
  chrome.storage.local.get('natHostInstalled', r => {
    window._nd = !!(r && r.natHostInstalled);
    if (window._nd) {
      console.log("[AC-MV3] natHostInstalled confirmed from storage");
    } else {
      console.log("[AC-MV3] natHostInstalled not in storage — offering the install UI");
    }
    // Signal _Eu so file2.js proceeds with the CORRECT flag even if the SW
    // ping callback hasn't fired yet (SW may be asleep — runtime.sendMessage
    // then never calls back and _Eu would otherwise stay unresolved).
    try { if (typeof _Eu !== 'undefined' && _Eu.send) _Eu.send(window._nd || false, !0); } catch(e) {}
  });

  // ======== PAGE STATE SYNC ========
  // The SW-brain owns the config chain, so the settings page never runs
  // windowEnum and its _cd/_Yp/_n stay EMPTY — which crashes the page's file62
  // listeners ("Cannot set properties of undefined (setting 'activeTab')") and
  // breaks page-side target resolution. Seed the page-local caches from
  // chrome.windows.getAll.
  /**
   * Seed the page-local window/tab caches from chrome.windows.getAll — the
   * SW owns the config chain, so the page never runs windowEnum itself.
   */
  function syncPageState() {
    try {
      if (typeof _n === 'undefined' || typeof _cd === 'undefined') return;
      chrome.windows.getAll({ populate: true, windowTypes: _Ge }, wins => {
        for (const w of wins) {
          if (!_n.includes(w.id)) _n.push(w.id);
          _cd[w.id] = w;
          if (w.tabs) for (const t of w.tabs) {
            const tid = _js(t);
            _Yp[tid] = t;
            if (w.focused && t.active) _Np = tid;
          }
          if (w.focused) _4t = w.id;
        }
      });
    } catch(e) {
      console.warn("[AC-MV3] Page state sync failed:", e.message);
    }
  }

  // Register this page with the SW
  /**
   * Register this page with the SW (ping) and adopt the leader/connected
   * state it reports.
   */
  function registerWithSW() {
    chrome.runtime.sendMessage({ cmd: "ping" }, response => {
      if (response && response.ok) {
        console.log("[AC-MV3] Registered with SW, connected:", response.connected);
        swConnected = response.connected;
        // The SW tells us who the current leader is (offscreen head or this page)
        if (response.leader) window._leader = response.leader;
        if (response.connected) {
          // Native already connected — signal legacy scripts.
          // AC-MV3 FIX (2026-08-07): do NOT set window._nd = true here and do
          // NOT persist natHostInstalled. _nd comes ONLY from the storage read
          // above (a stale connected during an uninstall would otherwise
          // re-arm the flag → "Something went wrong"). The SW persists the
          // flag in proceedAfterFileCheck (real handshake only).
          try {
            window._7 = true;
            if (typeof _Eu !== 'undefined' && _Eu.send) _Eu.send(true, !0);
            window._dh = Date.now();
          } catch(e) {
            console.warn("[AC-MV3] Failed to update legacy state:", e);
          }
          // AC-MV3 FIX (2026-08-07): if the install pane is showing (_nd was
          // false — e.g. fresh extension install with a leftover native: the
          // SW already persisted natHostInstalled on connect), transition to
          // the settings page via the 'ac-install-done' event (file2.js x()
          // listens for it and calls z()). The pane no longer auto-closes on
          // a timer (see file2.js x()). Safe against the uninstall race: _ei
          // removes the flag BEFORE the page reloads, so no dispatch then.
          if (!window._nd) {
            try {
              chrome.storage.local.get('natHostInstalled', r2 => {
                if (r2 && r2.natHostInstalled) {
                  console.log("[AC-MV3] Native up but install pane shown — transitioning to settings");
                  window.dispatchEvent(new CustomEvent('ac-install-done'));
                }
              });
            } catch(e) {}
          }
        } else {
          // SW is alive but not connected yet.
          // Signal _Eu anyway so file2.js doesn't hang.
          // The real connection status will arrive via 'nativeConnected' broadcast.
          console.log("[AC-MV3] SW alive, native not yet connected — signaling _Eu for init");
          try {
            if (typeof _Eu !== 'undefined' && _Eu.send) _Eu.send(window._nd || false, !0);
          } catch(e) {}
        }

        // Process buffered messages from SW (missed while page was loading)
        if (response.buffered && response.buffered.length > 0) {
          console.log(`[AC-MV3] Processing ${response.buffered.length} buffered messages`);
          for (const buf of response.buffered) {
            const event = new CustomEvent('ac-sw-msg', {
              detail: { type: 'nativeMsg', nativeType: buf.type, data: buf.data, _ts: buf.ts }
            });
            window.dispatchEvent(event);
          }
        }

        // After all buffered messages, dispatch nativeConnected for shim to send config
        if (response.connected) {
          console.log("[AC-MV3] Dispatching nativeConnected event for config init");
          const event = new CustomEvent('ac-sw-msg', {
            detail: { type: 'nativeConnected', connected: true, time: Date.now() }
          });
          window.dispatchEvent(event);
        }

        // Seed page-local window/tab caches (see syncPageState above)
        syncPageState();
      }
    });
  }

  // ======== EXPOSE HELPERS ========

  // Prevent settings page from closing on right-click (interferes with gesture detection)
  document.addEventListener('contextmenu', e => e.preventDefault());

  // Global error handler to prevent crashes from closing the settings page
  window.addEventListener('error', function(e) {
    console.warn("[AC-MV3] Global error caught:", e.error ? e.error.message : e.message);
    e.preventDefault();
  });
  window.addEventListener('unhandledrejection', function(e) {
    console.warn("[AC-MV3] Unhandled promise rejection:", e.reason);
    e.preventDefault();
  });

  window.__mv3 = {
    connected: false,
    sendToNative: function(type, data) {
      return new Promise((resolve, reject) => {
        chrome.runtime.sendMessage({ cmd: "postMsg", type, data }, r => {
          if (chrome.runtime.lastError) reject(chrome.runtime.lastError);
          else resolve(r && r.ok);
        });
      });
    },
    sendToNativeCb: function(type, data, timeout) {
      return new Promise((resolve, reject) => {
        chrome.runtime.sendMessage({ cmd: "postWithCb", type, data, timeout }, r => {
          if (chrome.runtime.lastError) reject(chrome.runtime.lastError);
          else if (r && r.ok) resolve(r.result);
          else reject(Error(r && r.error || "unknown"));
        });
      });
    },
    getStatus: function() {
      return new Promise(resolve => {
        chrome.runtime.sendMessage({ cmd: "getStatus" }, resolve);
      });
    }
  };

  // Register after DOM is ready
  if (document.readyState === 'loading') {
    document.addEventListener('DOMContentLoaded', registerWithSW);
  } else {
    registerWithSW();
  }

  // ======== POLYFILL chrome.tabs.* FOR MV3 ========

  // tabs.executeScript → scripting.executeScript via SW
  if (!chrome.tabs.executeScript) {
    chrome.tabs.executeScript = function(tabId, details, cb) {
      chrome.runtime.sendMessage({
        cmd: "execScript",
        tabId: tabId,
        allFrames: details.allFrames,
        files: details.file ? [details.file] : undefined,
        func: details.code || undefined,
        injectImmediately: details.runAt === "document_start"
      }, result => {
        if (cb) {
          if (chrome.runtime.lastError) cb(null);
          else if (result && result.error) cb(null);
          // SW already returns { result: [values...] } (not raw InjectionResult),
          // so no second .map(r => r.result) here — that crashed on null items.
          else cb(Array.isArray(result) ? result : []);
        }
      });
    };
  }

  // tabs.insertCSS → scripting.insertCSS
  if (!chrome.tabs.insertCSS) {
    chrome.tabs.insertCSS = function(tabId, details, cb) {
      chrome.runtime.sendMessage({
        cmd: "insertCSS",
        tabId: tabId,
        files: details.file ? [details.file] : undefined,
        code: details.code
      }, () => { if (cb) cb(); });
    };
  }

  // ======== STUBS for symbols defined in late-loading scripts ========
  if (typeof _Ew === 'undefined') { window._Ew = function(a) { /* stub */ }; }

  // ======== VISIBILITY SAFETY NET (2026-08-30) ========
  // main.html is hidden by default (no `visible` class on <html>); n()
  // (file2) reveals it after its boot chain (_Hu imports + _Eu nativeConnected
  // + SW ping). On a reload right after an extension reload (or a gesture
  // reload of the settings page) the SW is still starting, the boot can
  // stall and the page stays INVISIBLE (white/blank tab) — the user sees a
  // dead screen even though the data is there. This net reveals the page
  // EARLY and repeatedly: at DOMContentLoaded + at 2s + at 5s, idempotent.
  // (8s was too slow — the user already stared at a white screen.)
  function __acForceVisible(reason) {
    try {
      const html = document.documentElement;
      if (html && !html.classList.contains('visible')) {
        html.classList.add('visible');
        html.style.display = 'block';
        console.warn("[AC-MV3] Visibility safety net: " + reason + " — forced visible");
      }
    } catch (e) {}
  }
  if (document.readyState === 'loading') {
    document.addEventListener('DOMContentLoaded', () => __acForceVisible('DOMContentLoaded'));
  } else {
    __acForceVisible('readyState');
  }
  setTimeout(() => __acForceVisible('2s'), 2000);
  setTimeout(() => __acForceVisible('5s'), 5000);

  // Gesture display: page `_6t` (file3) uses document.fonts + canvas. MV2
  // loaded gestureDirs from the background page (file63.html @font-face);
  // the MV3 settings page never had that face, so fonts.load failed and
  // type 90 never left the page. Route `_6t` to the SW OffscreenCanvas
  // pipeline (file3 assigns `var _6t` later — re-apply after it loads).
  function __acPatchPage6t() {
    window._6t = function(b) {
      try { chrome.runtime.sendMessage({ cmd: 'gestureDisplay', data: b || {} }); }
      catch (e) {}
    };
  }
  __acPatchPage6t();
  setTimeout(__acPatchPage6t, 0);
  setTimeout(__acPatchPage6t, 500);

  console.log("[AC-MV3] Shim loaded");
})();
