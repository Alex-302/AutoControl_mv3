/**
 * AutoControl MV3 - Native Messaging Shim
 *
 * §N references in comments point to Docs/FEATURES-MV3.md (feature status
 * & port gaps).
 *
 * Replaces file61.js in MV3. Instead of connecting directly to native,
 * delegates messaging to the Service Worker.
 *
 * Provides:
 *   _Lk(a, b, c, g) - send message to native (fire-and-forget or with callback)
 *   _Vy(a, b, c)   - create callback-based _Lk wrapper
 *   _0d(a, b)      - send general message to native
 *   _Uj(a, b)      - send array [type, data] to native
 *   _ha(a, b)      - file size query
 *   z{} handlers   - process incoming messages from native (via SW)
 *   _Yi(a)         - get chunked data
 *   _cu(a)         - add handler to z
 *   _Sw()          - cleanup native connection
 */
(() => {
  'use strict';

  if (typeof _Lk !== 'undefined') return; // Already defined (file61.js loaded)

  console.log("[AC-MV3] Native shim active");

  // ======== STATE ========

  let pendingCallbacks = {};
  let chunkedDataStore = {};
  let y = _ay; // Persistent event handler (set by _0d, called by z[760])

  // Action execution queue (from file61.js _Xg)
  let _2y = [];

  // Full trigger list (populated by _Gf, used for key lookup)
  let _trigActList = null;

  // Gesture tracker (type 760 actionType=71 "G")
  let gestureState = null;

  // Queue for gestures detected before _ek is populated
  let pendingGestures = [];

  // Guards against running the _lr/_Gf config chain twice
  let configChainStarted = false;

  // _7 — native connection flag (read by file74.js etc.).
  // Declared on window so other scripts (loaded before this shim) see a stable binding.
  window._7 = false;

  /**
   * Leader election: only ONE context may run the config chain and execute
   * triggers (z[750]). Normally the offscreen head (main.html?offscreen=1) is
   * the leader; the settings page becomes leader only when the offscreen is
   * not alive (SW demotes it via leaderChange broadcasts / ping response).
   */
  function isLeader() {
    // SW-brain mode: the service worker (window._isSW) is always the leader;
    // the settings page ('page') must never execute triggers or the config chain.
    const myRole = window._isSW ? 'sw' : (window._isOffscreen ? 'offscreen' : 'page');
    const leader = window._leader || 'page'; // backward compat: page-leader default
    return myRole === leader;
  }

  // AC-MV3 FIX (2026-08-12, FEATURES-MV3.md §7-15): the context menu is built
  // ONLY by the SW (leader — it owns the contextMenus patches and rebuilds the
  // menu on every config-chain / storage change). On the settings page and the
  // offscreen document, file47's `_nk()` (called by file2.js switch toggles and
  // the page init path) would run the UNPATCHED chrome.contextMenus.removeAll
  // → wipes the SW's "Emergency repair" item — and its create() with
  // contexts:["browser_action"] is INVALID in MV3 (the SW's create patch maps
  // it to "action"; the page has no such patch) → the item NEVER comes back
  // (user 2026-08-12: the item vanished right after opening the settings
  // page). Neutralize _nk outside the SW; the SW rebuilds the menu itself.
  if (typeof importScripts !== 'function') {
    window._nk = function() {};
  }

  /**
   * Find trigger ID by key code
   */
  function findTriggerByKey(keyCode) {
    if (!_trigActList) return null;
    for (const [id, t] of Object.entries(_trigActList)) {
      if (t.eventId === keyCode) return Number(id);
    }
    return null;
  }

  /**
   * Find trigger matching a gesture pattern
   */
  function findTriggerByGesture(pattern) {
    if (!pattern) return null;

    // Try _ek first (triggerId → actions mapping, populated by _lr/_Gf)
    if (typeof _ek === 'object' && _ek) {
      const ids = Object.keys(_ek).map(Number).filter(n => !isNaN(n));
      if (ids.length > 0) return ids[0];
    }

    // Try _if (full trigActList with all trigger data)
    if (typeof _if === 'object' && _if) {
      const tse = _if.tse || _if.trigActList || _if;
      if (typeof tse === 'object') {
        const ids = Object.keys(tse).map(Number).filter(n => !isNaN(n));
        if (ids.length > 0) return ids[0];
      }
    }

    return null;
  }

  /**
   * Execute action for a trigger - retries if _ek not ready
   */
  function executeTrigger(triggerId, data) {
    if (triggerId !== null && typeof _6y === 'function') {
      try {
        const result = _6y(triggerId, data || {});
        // _6y returns a generator - catch rejections
        if (result && typeof result.catch === 'function') {
          result.catch(e => console.warn("[AC-MV3] executeTrigger async error:", e));
        } else if (result && typeof result.then === 'function') {
          result.then(null, e => console.warn("[AC-MV3] executeTrigger promise error:", e));
        }
      } catch(e) {
        console.warn("[AC-MV3] executeTrigger sync error:", e);
      }
      return true;
    }
    return false;
  }

  /**
   * _Lk - Send message to native component
   * @param {number} a - message type
   * @param {object} b - payload
   * @param {function} c - callback (optional)
   * @param {number} g - timeout in ms (optional)
   * @returns {boolean}
   *
   * With callback: uses SW's postWithCb which handles native callback protocol.
   * Without callback: fire-and-forget via postMsg.
   */
  var _Lk = function(a, b = null, c = null, g = 0) {
    // SW-brain mode: send directly to the SW's native port (self-messaging
    // would not reach the SW's own onMessage listener).
    if (typeof _acNativeSend === 'function') {
      return _acNativeSend(a, b, c, g);
    }
    // Preserve falsy payloads (empty string "" is valid for ping type 920)
    const payload = b !== null && b !== undefined ? b : {};
    const timeout = g || 5000;

    if (c) {
      // Use SW's postWithCb — it handles native callback protocol (e + l format)
      chrome.runtime.sendMessage({ cmd: "postWithCb", type: a, data: payload, timeout }, response => {
        if (response && response.ok) {
          c(response.result);
        } else {
          c(_g); // timeout / error
        }
      });
    } else {
      // Fire-and-forget: send via postMsg
      chrome.runtime.sendMessage({ cmd: "postMsg", type: a, data: payload });
    }

    return true;
  };

  /**
   * _Vy - Create a callback-based _Lk wrapper
   */
  var _Vy = (a, b, c) => g => _Lk(a, b, g, c);

  /**
   * _0d - Enable/disable event capture from native
   * @param {boolean} a - true=enable, false=disable
   * @param {function} b - persistent event handler (called for each event from native)
   *
   * Original: _Lk(_Qr, a); b && (y = b);
   * The callback is NOT a response callback — it's stored for incoming events.
   */
  var _0d = function(a, b = _ay) {
    _Lk(_Qr, a);  // Send type 40 without callback
    if (b) y = b;  // Store event handler in 'y' (called by z[760])
  };

  /**
   * _Uj - Simulate receiving a message from native (routes to local z handler)
   * Original: A([a, b], d) - calls the port message handler locally
   */
  var _Uj = (a, b) => {
    // Route to z handler as if native sent [type, data]
    const handler = z[a] || _ay;
    handler(b);
  };

  /**
   * _ha - File size response
   * _Z = 30 (file size query type)
   */
  var _ha = (l, k) => _Lk(_Z, { id: l, params: k });

  // ======== INCOMING MESSAGE HANDLING ========

  /**
   * Handle incoming native messages from SW
   */
  window.addEventListener('ac-sw-msg', (event) => {
    const msg = event.detail;

    // Handle native connection status changes
    if (msg.type === 'nativeConnected' || msg.type === 'nativeConfigReady') {
      console.log("[AC-MV3] Native " + msg.type + " event received (leader=" + (window._leader || 'page') + ", isOffscreen=" + !!window._isOffscreen + ")");
      window._7 = true;
      _nd = true;
      _dh = msg.time || Date.now();

      // nativeConnected (legacy): just signal page init to continue.
      // nativeConfigReady (new): SW finished type 10→20→72, page must now run the
      //   _lr→_Gf config chain, and ONLY after it completes tell SW → type 21 (startup).
      // Original file61.js generator D did: config chain (_lr/_Gf) → THEN type 21 last.
      if (msg.type === 'nativeConnected') {
        try { _Eu && _Eu.send(true, !0); } catch(e) {}
        // If SW still sends legacy nativeConnected (older SW), fall through to config
        // loading only if nativeConfigReady wasn't received.
        if (configChainStarted) return;
      }

      // CRITICAL: set _Sk when handshake starts (matches original generator D where
      // _Sk=Date.now()/864E5|0 is set at the top of D, before the file check resolves).
      // Native encodes trigger IDs as triggerIndex + _Sk, so we must freeze _Sk here.
      _Sk = Date.now() / 864E5 | 0;
      console.log("[AC-MV3] _Sk set at handshake:", _Sk);

      // Only the leader (offscreen head by default) runs windowEnum + config chain.
      // The settings page skips when the offscreen is alive, avoiding double
      // type 60/72/21 sends and double trigger execution.
      if (!isLeader()) {
        console.log("[AC-MV3] Not leader (" + (window._leader || 'page') + "), skipping config chain");
        // AC-MV3 FIX: the config chain (which populates _if from storage) runs
        // only in the SW. On the settings page _if would stay empty, so the UI
        // (script editor, entity menus) would not see saved entities.
        // IMPORTANT: use _6s (not a raw storage read) — it converts
        // customEntities from the storage pair-array into the Map-like object
        // ({}.add) that _Xy()/_gh() expect. A raw assign leaves _if.script as
        // [[id, value], ...] and the script list renders empty.
        try {
          if (typeof _6s === 'function') {
            _6s({}, () => {
              // AC-MV3 FIX (2026-08-12, FEATURES-MV3.md §7-15): NO _nk() on
              // the page — the context menu is built ONLY by the SW (leader).
              // The page's _nk() ran the UNPATCHED chrome.contextMenus.
              // removeAll() → wiped the SW's "Emergency repair" item, and its
              // create({contexts:["browser_action"]}) is INVALID in MV3 →
              // the item never came back (user 2026-08-12: vanished right
              // after opening the settings page). The SW rebuilds the menu on
              // every config-chain / storage change.
              console.log("[AC-MV3] Page _if populated (via _6s):", Object.keys(_if).join(',') || '(empty)');
            });
          } else {
            _Yk.storage.local.get({ customEntities: {} }, r => {
              if (r && r.customEntities) {
                _if = typeof _Qj === 'function'
                  ? _Qj({ customEntities: r.customEntities }).customEntities
                  : r.customEntities;
                console.log("[AC-MV3] Page _if populated from storage:", Object.keys(_if).join(',') || '(empty)');
              }
            });
          }
        } catch(e) { console.warn("[AC-MV3] _if populate failed:", e); }
        return;
      }

      // Settings-page config refresh / SW startup re-send (type 60 push) —
      // allow the chain to re-run (resets the duplicate guard).
      if (msg.type === 'nativeConfigReady' && msg.force) {
        console.log("[AC-MV3] Forced config refresh — allowing config chain re-run");
        configChainStarted = false;
      }

      // Guard against duplicate nativeConfigReady (SW broadcasts via both tabs + runtime).
      if (configChainStarted) {
        console.log("[AC-MV3] Config chain already started, skipping duplicate nativeConfigReady");
        return;
      }
      configChainStarted = true;

      try { _Eu && _Eu.send(true, !0); } catch(e) {}

      // Original generator D ordering (file61.js):
      //   _7=true → yield _Ry/_oj (window enum) → _Lk(_mu=72) → yield _lr/_Gf (config→type 60) → _Lk(_zu=21)
      //
      // Step 1: Window enumeration (_Ry/_oj) — matches original _iy() → yield _Ry → _oj
      // _Ry matches Chrome windows to native HWNDs via type 335/400 messages.
      // When done, tell SW to send type 72, then immediately start config chain.
      //
      // Step 2: Config chain (_lr → _Gf → _6s → _zj → _no → _mh → type 60)
      // _mh() populates _pg (transform table) and _su (index shift) used by z[750].
      // _zj() populates _ek (triggerId → actions). When done, tell SW to send type 21.

      /**
   * Run the config chain on the settings page (leader mode) and report
   * completion to the SW via nativeConfigReady + type 21.
   */
  const startConfigChain = () => {
        try {
          if (typeof _lr === 'function') {
            _lr(b => {
              if (typeof _Gf === 'function') {
                _Gf(b, c => {
                  if (c && c.trigActList) _trigActList = c.trigActList;
                  console.log("[AC-MV3] Config loaded:",
                    Object.keys(_trigActList || {}).length, "triggers,",
                    typeof _ek === 'object' ? Object.keys(_ek).length : 0, "active,",
                    "_su=", typeof _su !== 'undefined' ? _su : '(undef)',
                    "_pg keys=", typeof _pg === 'object' && _pg ? Object.keys(_pg).length : 0);

                  // Config chain done — tell SW to send type 21 (startup, LAST message)
                  console.log("[AC-MV3] Config chain done, telling SW to send type 21");
                  chrome.runtime.sendMessage({ cmd: "configLoaded" }, () => {});
                });
              }
            });
          }
        } catch(e) { console.warn("[AC-MV3] Config error:", e); }
      };

      if (typeof _Ry === 'function' && typeof _8u === 'function') {
        // Step 1: Populate _n with EXISTING windows before window enumeration.
        // In the original MV2, the background page has been running and _n gets
        // populated via _yh (onCreated) as windows appear. But in MV3, main.html
        // just loaded — existing windows never fire onCreated. So we must query
        // chrome.windows.getAll and manually add them to _n and _cd.
        // Without this, _Ry/_8u processes an empty _n → no type 335/400 sent →
        // no HWND mappings → no type 140/150 tab setup → native has no window
        // context and may not fire type 750 trigger events.
        try {
          console.log("[AC-MV3] Populating _n with existing windows...");
          _Yk.windows.getAll({ populate: true, windowTypes: _Ge }, wins => {
            const before = _n.length;
            for (const w of wins) {
              if (!_n.includes(w.id)) {
                _n.push(w.id);
                _cd[w.id] = w;
                // Store initial tab state in _Yp for each tab
                if (w.tabs) {
                  for (const t of w.tabs) {
                    const tid = _js(t);
                    _Yp[tid] = t;
                  }
                }
              }
            }
            console.log("[AC-MV3] _n populated:", _n.length, "windows (added", _n.length - before, ")");

            // Init _4t/_Np (active window + tab). "currentTab" target resolution
            // (_ou/_zy) silently produces NO tabs when _Np is unset — in MV2 the
            // long-running background page got these from onActivated events; in
            // the SW-brain they must be seeded at startup.
            for (const w of wins) {
              if (w.focused) _4t = w.id;
              if (w.tabs && w.focused) {
                for (const t of w.tabs) {
                  if (t.active) _Np = _js(t);
                }
              }
            }
            console.log("[AC-MV3] Active window _4t:", _4t, "active tab _Np:", _Np);

            // Step 2: Run window enumeration with _n now populated.
            // _Ry() will process the windows → send type 335/400 → get HWND
            // mappings → _oj() sends type 140/150 tab setup → afterWindowEnum.
            console.log("[AC-MV3] Running window enumeration (_Ry/_oj)...");
            _8u()(() => {
              // Window enum done — tell SW to send type 72, then start config chain
              console.log("[AC-MV3] Window enum done, telling SW to send type 72");
              chrome.runtime.sendMessage({ cmd: "windowEnumDone" }, () => {});
              // Immediately start config chain (original sends 72 then starts config)
              startConfigChain();
            });
          });
        } catch(e) {
          console.warn("[AC-MV3] Window enum error:", e);
          // Fallback: tell SW to send type 72 and start config anyway
          chrome.runtime.sendMessage({ cmd: "windowEnumDone" }, () => {});
          startConfigChain();
        }
      } else {
        console.log("[AC-MV3] _Ry/_8u not available, skipping window enum");
        chrome.runtime.sendMessage({ cmd: "windowEnumDone" }, () => {});
        startConfigChain();
      }

      return;
    }

    if (msg.type === 'nativeDisconnected') {
      console.log("[AC-MV3] Native disconnected event received");
      window._7 = false;
      // Allow the config chain to re-run on the next reconnect — native needs
      // fresh type 60 config + type 21 after every handshake.
      configChainStarted = false;
      return;
    }

    // Handle emergency repair broadcast from SW
    if (msg.type === 'emergencyRepair') {
      console.log("[AC-MV3] Emergency repair triggered");
      if (!isLeader()) return; // only the leader resets state
      try { _co(1, !0); } catch(e) {}
      return;
    }

    if (msg.type !== 'nativeMsg' || msg.nativeType === undefined) return;

    const nativeType = msg.nativeType;
    const data = msg.data || {};

    // Log all incoming native messages for debugging
    console.log(`[AC-MV3-NativeShim] ← Native type ${nativeType}:`, data);
    if (nativeType === 750) console.warn("[AC-MV3] >>> TRIGGER type 750 id:", data.id);

    // Handle callback responses (type 710 = promise resolution)
    if (nativeType === 710 && data.callback) {
      const cb = pendingCallbacks[data.callback];
      if (cb) {
        delete pendingCallbacks[data.callback];
        cb(data.params);
      }
      return;
    }

    // Route to z handler
    const handler = z[nativeType] || _ay;
    const handlerName = z[nativeType] ? `z[${nativeType}]` : '_ay(fallback)';
    try {
      handler(data);
    } catch(e) {
      console.error(`[AC-MV3-NativeShim] Handler ${handlerName} error:`, e);
    }
  });

  // ======== HANDLER REGISTRATION ========

  /**
   * z - Message type handlers (same as file61.js)
   * These are called when the SW forwards native messages.
   * The actual handlers are defined by other scripts (file25, file37, etc.)
   */
  const z = {
    // [_Hf] = 750 - Trigger event (keyboard, mouse, gesture)
    // Mirrors file61.js z[750] exactly:
    //   1. _pg lookup (URL/tab transform) — keyed by (a.id - _Sk + _su)
    //   2. _qt for mouseGest / extEvtData enrichment
    //   3. _6y executes action with triggerId = 16777215 & (a.id - _Sk)
    // _Sk is set at handshake time (see nativeConfigReady handler).
    // _su/_pg are populated by _mh() inside the _lr→_Gf config chain.
    [750]: (a) => {
      try {
        // Only the leader context executes triggers (offscreen head by default).
        // Without this gate, the settings page + offscreen head would both run
        // the same action when both are open → duplicate execution.
        if (!isLeader()) {
          console.log("[AC-MV3] z[750] skipped — not leader (leader=" + (window._leader || 'page') + ")");
          return;
        }
        const decoded = 16777215 & (a.id - _Sk);
        console.warn("[AC-MV3] >>> Trigger 750 id:", a.id, "_Sk:", _Sk, "→ triggerId:", decoded,
          "_su:", typeof _su !== 'undefined' ? _su : '(undef)',
          "_pg:", typeof _pg === 'object' && _pg ? Object.keys(_pg).length + ' keys' : 'none');

        // 1. URL/tab transform (built by _mh). Key includes _su shift.
        let b = _pg[a.id - _Sk + _su];
        if (b) {
          a.trigInstId = b(a.trigInstId);
          if (!a.trigInstId) {
            console.log("[AC-MV3] Trigger 750 filtered out by _pg transform");
            return;
          }
        }

        // 2. Mouse gesture enrichment
        if (a.mouseGest) {
          a.trigInstId = _qt(a.trigInstId, { usePrevMousePos: a.mouseGest });
        }

        // 3. External event data enrichment (tabs filtering etc.)
        if (a.extEvtData) {
          if ("tabs" in a.extEvtData) {
            a.extEvtData.tabs = _Dw(a.extEvtData.tabs);
          }
          a.trigInstId = _qt(a.trigInstId, a.extEvtData);
        }

        // 4. Execute action
        if (typeof _6y === 'function') {
          console.warn("[AC-MV3] Executing trigger", decoded);
          _6y(decoded, a.trigInstId);
        } else {
          console.warn("[AC-MV3] _6y not available, cannot execute trigger", decoded);
        }
      } catch(e) {
        console.warn("[AC-MV3] z[750] handler error:", e);
      }
    },
    // [_5r] = 70 - Joystick order
    [70]: (a) => { try { _bd({ joysticksOrder: a.list }); } catch(e) {} },
    // [_mj] = 721 - Window mapping
    [721]: (a) => { try { _y(a.hWnd, a.noEvt); } catch(e) {} },
    // [_Ki] = 730 - Clipboard list
    [730]: (a) => { try { _cr(a.list); } catch(e) {} },
    // [_Qg] = 735 - Window minimize/unminimize
    [735]: (a) => { try { _Wo(a.state ? _td : _ik, _Or[a.hWnd]); } catch(e) {} },
    // [_9g] = 740 - Clipboard format
    [740]: (a) => {
      try {
        _Lf(_ag(a));
        a.noEvt || _8o(_vt);
      } catch(e) {}
    },
    // [_9p] = 710 - Promise resolution (handled above)
    [710]: (a) => {},
    // [_fo] = 760 - Action/gesture events from native.
    // Matches original file61.js exactly: y(_Lj(a.actionType), a.actionSpec).
    // y is the persistent callback set by _0d (combo editor / gesture assist).
    // In normal usage y === _ay (no combo editor open), so type 760 events are
    // effectively no-ops — the actual trigger firing comes via type 750 (z[750]).
    // NOTE: type 760 is RAW input data (key codes, mouse buttons, wheel, gesture
    // coordinates). Native itself decides whether a registered trigger matches and,
    // if so, sends type 750. So we must NOT try to match triggers here.
    [760]: (a) => {
      try {
        y(_Lj(a.actionType), a.actionSpec);
      } catch(e) {
        console.warn("[AC-MV3] z[760] handler error:", e);
      }
    },
    // [_kw] = 800 - Error handling
    // MV2 file61.js E() classification (ported 2026-08-10, FEATURES-MV3.md §7-4):
    // - "no-hook-notice" → _uf error counter + a chrome.notifications notice
    //   with buttons after 5 notices/15s (the MV2 file71.html popup cannot
    //   work from the SW — no getViews in MV3; without the permission it
    //   degrades to the silent counter; noHookConflictMsg is in-memory per
    //   SW session → the notice can re-arm after a restart, acceptable).
    // - "invalidExtId" → install-age gate (_2u); "APDL" → bundle `_r` flag
    //   (stops the type-790 idle ping); "NH-error" 0xC0000005 → _uf
    //   ("segFault"); everything else → telemetry (_Ot, off by default).
    // Details: Docs/FEATURES-MV3.md §7-4.
    [800]: (() => {
      let nhCount = 0, nhTimer = null, nhBusy = false, nhOff = _j("noHookConflictMsg");
      let nhNotifId = null, nhAnswer = null;
      // One-time listeners (guarded — notifications is an optional
      // permission; everything degrades silently without it).
      try {
        if (chrome.notifications && chrome.notifications.onButtonClicked) {
          chrome.notifications.onButtonClicked.addListener((id, btn) => {
            if (id !== nhNotifId || !nhAnswer) return;
            const a = nhAnswer; nhAnswer = null; nhNotifId = null;
            a(btn === 0); // button 0 = "Don't show again" (answer true)
            try { chrome.notifications.clear(id, () => {}); } catch (e) {}
          });
        }
        if (chrome.notifications && chrome.notifications.onClosed) {
          chrome.notifications.onClosed.addListener((id) => {
            if (id !== nhNotifId) return;
            nhNotifId = null; nhAnswer = null;
            nhBusy = false; // user dismissed → allow a later re-notice
          });
        }
      } catch (e) {}
      /**
   * Show the no-hook-conflict notification (z[800] no-hook-notice path).
   * @param {string} name — counter/notice key
   * @param {object} msg — the native error message
   */
  function noHookNotice(name, msg) {
        _uf(msg.needed ? "no-hook" : "no-hook-false");
        if (nhBusy) return;
        if (!nhTimer) nhTimer = setTimeout(() => { nhCount = 0; nhTimer = null; }, 15E3);
        if (5 !== ++nhCount || nhOff) return;
        // AC-MV3 FIX (2026-08-10): restart the series AFTER the notice is
        // shown. The MV2 logic kept counting (6, 7, ... never === 5), so
        // after answering "Keep showing" the next 5-10 notices stayed silent
        // until the 15s window expired (user VM report). Resetting the
        // counter + window here means "Keep showing" → the NEXT 5 fresh
        // notices re-notify; "Don't show again" → nhOff keeps it silent.
        nhCount = 0;
        clearTimeout(nhTimer); nhTimer = null;
        if (!chrome.notifications || !chrome.notifications.create) { nhBusy = false; return; }
        nhBusy = true;
        try {
          nhNotifId = "acNoHook_" + Date.now();
          nhAnswer = (x) => {
            nhBusy = false;
            _Ot(name, msg.add({ answer: x ? "Disable notice" : "Keep showing" }));
            _9k("noHookConflictMsg", nhOff = x);
          };
          chrome.notifications.create(nhNotifId, {
            type: "basic",
            iconUrl: chrome.runtime.getURL("AutoCtrl/logo32.png"),
            title: _Bj.alias + ": triggers not detected",
            // Short message — Windows notification toasts truncate longer
            // text (user VM 2026-08-10: cut off mid-sentence ~130 chars).
            message: "Another program may be blocking " + _Bj.alias + " (shortcut manager, antivirus, VNC...). Disable conflicting programs one by one.",
            buttons: [{ title: "Don't show again" }, { title: "Keep showing" }]
          }, () => { try { void chrome.runtime.lastError; } catch (e) {} });
        } catch (e) {
          nhBusy = false;
          console.warn("[AC-MV3] no-hook notice notification failed:", e);
        }
      }
      return (a) => {
        const h = a.type;
        delete a.type;
        if ("no-hook-notice" === h) { noHookNotice(h, a); return; }
        if ("invalidExtId" === h) { if (_2u()) return; }
        else if ("APDL" === h) { _r = true; if (_ul(a.result)) return; }
        else if ("NH-error" === h && 3221225477 === a.code) { _uf("segFault"); return; }
        _Ot(h, a);
      };
    })(),
    // [_ef] = 810 - Chunked data
    [810]: (a) => {
      try {
        if (null == chunkedDataStore[a.id]) {
          chunkedDataStore[a.id] = "list" === a.type ? [] : "";
          delete chunkedDataStore[(a.id + 9) % 20 + 1];
        }
        switch (a.type) {
          case "text": chunkedDataStore[a.id] += a.chunk; break;
          case "list": chunkedDataStore[a.id].push(...a.chunk); break;
          case "bin": chunkedDataStore[a.id] += atob(a.chunk); break;
        }
      } catch(e) {}
    },
    // [_R] = 704 - Version
    [704]: (a) => { try { _Ie = a.verNum; } catch(e) {} },
    // [_np] = 705 - Browser name
    [705]: (a) => {
      try {
        _Jh = (_Kd = a.exeName.toLowerCase()).replace(/\.[^.]+$/, "");
        _Kd || _Ot("noBrwrName");
      } catch(e) {}
    },
    // [_Pd] = 715 - Settings sync
    [715]: (a) => { try { _tg(a); } catch(e) {} },
    // [_0i] = 765 - File size result
    [765]: (a) => { try { _1p(a.file, "blob")(b => _ha(a.callback, b ? b.size : _Rr)); } catch(e) {} },
    // [_jh] = 905 - No-op
    [905]: () => {},
    // add handler
    add: function(handler) { Object.assign(this, handler); }
  };

  /**
   * _Yi - Get chunked data by ID
   */
  /**
   * Retrieve chunked file data from the native (type 255/810 reassembly).
   * @param {*} a — read request
   * @returns {Promise<*>} the reassembled result
   */
  var _Yi = function(a) {
    let b = a && a.chunkedData;
    if (b) {
      a = chunkedDataStore[b];
      delete chunkedDataStore[b];
    }
    return a;
  };

  /**
   * _cu - Add handlers to z
   */
  var _cu = a => z.add(a);

  // ======== MISSING SYMBOLS FROM file61.js ========

  // _7 — native connection flag (read by file74.js etc.).
  // NOTE: a separate listener below flips window._7 on connect/disconnect events.

  // Mirror connection status to window._7 (covers nativeConfigReady + legacy nativeConnected)
  // Also reset the config-chain guard on disconnect so a reconnect re-runs _lr/_Gf.
  window.addEventListener('ac-sw-msg', (event) => {
    const t = event.detail.type;
    if (t === 'nativeConnected' || t === 'nativeConfigReady') window._7 = true;
    if (t === 'nativeDisconnected') { window._7 = false; configChainStarted = false; }
  });

  /**
   * _Xg - Native connection init (no-op stub in MV3, SW handles it)
   * Returns a resolved coroutine that returns 'CB-TIMEOUT' (disconnected)
   */
  var _Xg = _we(function*(a) {
    // In MV3, the SW manages the connection.
    // If we need to force reconnection, tell the SW
    if (a > 0) {
      chrome.runtime.sendMessage({ cmd: "reconnect" }, () => {});
    }
    // Return disconnected state
    return _g; // _g = "CB-TIMEOUT"
  });

  /**
   * _Sw - Cleanup (no-op in shim, SW handles it)
   */
  /**
   * Clean up the shim's native-connection state (legacy bridge teardown).
   */
  var _Sw = function() {
    // Clear any pending callbacks
    pendingCallbacks = {};
  };

  // ======== FILE71 POPUP FROM THE SW (AC-MV3 FIX 2026-08-12) ========
  // MV2 `_Fo` (file70, IN bundle) filled the file71.html popup window via
  // chrome.extension.getViews({windowId}) — ABSENT in the MV3 service worker
  // (sw_prelude stubs it to () => [] → `l` undefined → TypeError → the window
  // opened EMPTY). FEATURES-MV3.md §7-15 (file71 popups from the SW).
  // MV3 equivalent: chrome.windows.create still works from the SW; the popup
  // TAB (own extension page — no host permission needed) is filled via
  // chrome.scripting.executeScript, and the button result comes back via
  // chrome.runtime.sendMessage ("acPopupResult" — handled in sw.js, routed to
  // __acResolvePopup). Revives ALL file71 popups: _Kg (REPAIR COMPLETE stuck
  // keys), _Ht (foreign profile), _Lh (no-hook notice — z[800] still uses
  // notifications by design), _Uk (stop waiting).
  let __acPopupRunId = 0;
  const __acPopupCallbacks = {}; // runId -> { winId, cb }

  function __acResolvePopup(runId, answer) {
    const rec = __acPopupCallbacks[runId];
    if (!rec) return;
    delete __acPopupCallbacks[runId];
    try { if (rec.winId != null) chrome.windows.remove(rec.winId); } catch (e) {}
    try { rec.cb && rec.cb({ answer: !!answer }); } catch (e) {}
  }

  function __acMv3Popup(opts, html, cb) {
    opts = opts || {};
    // MV2 `_Kg`'s onloaded converted <key>N</key> to names inside the popup
    // (_Xp(c)._Je — framework per window). In the SW we pre-convert with the
    // bundle's own _Je (file57) — same result, no popup-side framework needed.
    if (opts.onloaded && typeof _Je === 'function') {
      html = String(html).replace(/<key>(\d+)<\/key>/g, (m, n) => '<key>' + _Je(+n) + '</key>');
    }
    // Center on the focused monitor's work area (MV2 parity; fallback if the
    // monitor map isn't populated yet — _Zw fills at SW startup).
    chrome.windows.getLastFocused({}, (win) => {
      let wa = { left: 0, top: 0, width: 1200, height: 800 };
      try {
        const zw = (_9j && _9j._Zw) || {};
        const mi = zw[win && typeof _wt === 'function' ? _wt(win) : 0];
        if (mi && mi.workArea) wa = mi.workArea;
      } catch (e) {}
      const w = opts.width || 400, h = opts.height || 200;
      const runId = ++__acPopupRunId;
      __acPopupCallbacks[runId] = { winId: 0, cb: cb || null, html: String(html), title: 'AutoControl' };
      chrome.windows.create({
        width: w, height: h,
        left: Math.max(0, (wa.left + wa.width / 2 - w / 2) | 0),
        top: Math.max(0, (wa.top + wa.height / 2 - h / 2) | 0),
        url: chrome.runtime.getURL('file71.html') + '?runId=' + runId,
        focused: true, type: 'popup', state: 'normal'
      }, (f) => {
        if (!f || !f.tabs || !f.tabs[0]) {
          console.warn('[AC-POPUP] windows.create returned no tab — aborting');
          delete __acPopupCallbacks[runId];
          try { cb && cb({ answer: false }); } catch (e) {}
          return;
        }
        const tabId = f.tabs[0].id;
        __acPopupCallbacks[runId].winId = f.id;
        // MV2 kept the popup above other windows via the native topmostWins
        // action — best effort here (the native may be mid-reconnect right
        // after a repair, so failures are ignored).
        try { if (typeof _gh === 'function' && typeof _ay === 'function') _gh('topmostWins', 'action').value([tabId], _ay, { mode: _qa }); } catch (e) {}
        // The popup page (file71.html + file71_bridge.js) requests its content
        // itself via chrome.runtime.sendMessage({type:"acPopupContent"}) —
        // scripting.executeScript CANNOT inject into chrome-extension:// pages
        // (user VM 2026-08-12: "Extension manifest must request permission to
        // access this host" → the window flashed empty).
      });
    });
  }
  window._Fo = __acMv3Popup;
  window.__acResolvePopup = __acResolvePopup;
  window.__acPopupGetContent = (runId) => {
    const rec = __acPopupCallbacks[runId];
    return rec ? { html: rec.html, winId: rec.winId, title: rec.title } : null;
  };

  // ======== CONSTANTS FROM file61.js ========

  // Re-export for compatibility
  window._2y = _2y;  window._Lk = _Lk;
  window._Vy = _Vy;
  window._0d = _0d;
  window._Uj = _Uj;
  window._ha = _ha;
  window._Yi = _Yi;
  window._cu = _cu;
  window._Sw = _Sw;
  window._Xg = _Xg;
  window.z = z;

  // ======== CHROME API FALLBACKS ========
  // In MV3 (especially Chrome 150+), some chrome.tabs APIs may return Promises
  // and ignore the callback argument, breaking the _wk counter synchronization.
  // Patch them to handle both callback and Promise patterns.
  try {
    const TABS_FALLBACKS = [
      // Format: [apiName, options]
      // 'discard' — _Yk.tabs.discard may return Promise in MV3, ignoring callback
      ['discard'],
    ];
    for (const [api] of TABS_FALLBACKS) {
      if (typeof _Yk.tabs[api] !== 'function') continue;
      const orig = _Yk.tabs[api].bind(_Yk.tabs);
      _Yk.tabs[api] = function(...args) {
        const cb = args.find(a => typeof a === 'function');
        try {
          const result = orig(...args);
          // If API returns a Promise (MV3 pattern), callback may be ignored.
          // Bridge it: call the callback when Promise resolves.
          if (result && typeof result.then === 'function') {
            if (cb) {
              result.then(r => { try { cb(r); } catch(e) {} }).catch(() => { try { cb(null); } catch(e) {} });
            }
            return result;
          }
          return result;
        } catch(e) {
          console.warn(`[AC-MV3] chrome.tabs.${api} failed from page, routing through SW:`, e.message);
          if (api === 'discard') {
            const tabIds = args.filter(a => typeof a === 'number');
            chrome.runtime.sendMessage({ cmd: 'discardTabs', tabIds }, () => {
              if (cb) setTimeout(() => cb(null), 0);
            });
          } else {
            if (cb) setTimeout(cb, 0);
          }
        }
      };
    }
    if (TABS_FALLBACKS.length > 0) console.log(`[AC-MV3] Patched ${TABS_FALLBACKS.length} chrome.tabs APIs for Promise compatibility`);
  } catch(e) {
    console.warn('[AC-MV3] Failed to patch chrome.tabs APIs:', e.message);
  }

  window.pendingCallbacks = pendingCallbacks;
  window.chunkedDataStore = chunkedDataStore;

  console.log("[AC-MV3] Native shim ready");
})();

// ======== SW: LIVE CONFIG REBUILD ON STORAGE CHANGES ========
// In MV2, file2.js v() registered _Gu/_B subscriptions that rebuilt the
// in-memory config (_if/_ek/_pg/_su) whenever the user changed settings —
// those subscriptions ran in the background page. In MV3 the SW IS the
// background, but file2.js is page-only and not part of the bundle, so the
// SW never learns about script/action changes until restart (only trigger/
// gesture changes reach it via type 60 → refreshConfigInSW).
//
// Fix: the SW listens to storage.local itself and re-runs the config chain
// (_Gf = _6s→_zj→_no), which refreshes _if/_ek and pushes type 60 to native.
// Debounced to coalesce multi-key writes; busy-guarded against re-entry.
(function() {
  // Service worker only (workers have importScripts; pages don't).
  if (typeof importScripts !== 'function') return;
  if (!(chrome && chrome.storage && chrome.storage.onChanged)) return;

  let __acRebuildTimer = null;
  let __acRebuildBusy = false;
  const RELEVANT = ['customEntities', 'trigActList', 'mouseGest', 'advOpts', 'toolbarBtns', 'sections'];

  chrome.storage.onChanged.addListener((changes, area) => {
    if (area !== 'local') return;
    const hit = RELEVANT.some(k => k in changes);
    if (!hit || __acRebuildBusy) return;
    clearTimeout(__acRebuildTimer);
    __acRebuildTimer = setTimeout(() => {
      __acRebuildBusy = true;
      try {
        console.warn("[AC-MV3] storage.local changed → rebuilding in-SW config (_Gf)");
        if (typeof _Gf === 'function') {
          _Gf({}, () => {
            if (typeof _nk === 'function') { try { _nk(); } catch(e) {} }
          });
        }
      } catch(e) {
        console.warn("[AC-MV3] in-SW config rebuild failed:", e);
      } finally {
        setTimeout(() => { __acRebuildBusy = false; }, 1000);
      }
    }, 400);
  });
  console.log("[AC-MV3] SW storage.onChanged → config rebuild armed");
})();

// ======== FAVICON CACHE PATCH ========
// In MV3, XHR to chrome://favicon/ URLs is blocked → _Zs hangs (callback never fires)
// → MRU tab list icons never load, _wk synchronizer stays positive.
//
// Fix: wrap _Zs to handle chrome://favicon URLs:
//   1. First check _7o cache (populated by _Zs's own XHR or our pre-fetch)
//   2. If cached → callback with base64 data (icon appears)
//   3. If not cached → callback() (=void 0, matches original XHR error behavior,
//      so MRU list still opens) + background load via Google favicons for cache.
//   4. Non-chrome://favicon URLs pass through to original _Zs.
//
// Pre-fetch: after init, iterate _Yp and pre-load favicons into _7o so MRU icons
// appear on the FIRST open.
(function() {
  const _Cu = "chrome://favicon/";
  const origZs = window._Zs;

  if (typeof origZs !== 'function') {
    console.warn('[AC-MV3] _Zs not found, favicon patch skipped');
    return;
  }

  // _1p is defined in file67.js (XHR loader used by _Zs internally)
  const xhrLoad = (typeof _1p !== 'undefined' ? _1p : window._1p);

  window._Zs = (url) => (callback) => {
    // Non-chrome://favicon: pass through to original (works via XHR)
    if (typeof url !== 'string' || !url.startsWith(_Cu)) {
      return origZs(url)(callback);
    }

    // chrome://favicon/... — check _7o cache
    if (typeof _7o === 'object' && _7o[url]) {
      if (callback) callback(_7o[url]);
      return;
    }

    // Not cached: return undefined now (matches original XHR error)…
    if (callback) callback();

    // …then start background load into _7o cache for future calls
    if (!xhrLoad) return;
    try {
      const tabUrl = url.slice(_Cu.length);
      const gUrl = "https://www.google.com/s2/favicons?domain_url="
        + encodeURIComponent(tabUrl) + "&sz=16";
      xhrLoad(gUrl, "binary")(function(d) {
        if (d) {
          try { _7o[url] = btoa(d); } catch(e) {}
        }
      });
    } catch(e) {/* ignore */}
  };

  // Pre-fetch: populate _7o from existing _Yp cache shortly after init.
  // CRITICAL: cache key MUST match the exact URL that _Zs receives at runtime,
  // which is tab.favIconUrl, NOT a constructed chrome://favicon/key.
  /**
   * Pre-fetch favicons for known tabs into the cache (menu first-open fix).
   */
  const prefetchFavicons = () => {
    if (typeof _Yp !== 'object' || typeof _7o !== 'object') return;
    let count = 0;
    for (const id in _Yp) {
      const tab = _Yp[id];
      if (!tab || !tab.url) continue;
      const favIconUrl = tab.favIconUrl;
      if (!favIconUrl || _7o[favIconUrl]) continue; // skip if no icon or already cached

      if (favIconUrl.startsWith('data:')) {
        // data: URI — extract base64 directly (sync, fast)
        const m = favIconUrl.match(/^data:[^;]*;base64,(.+)$/);
        if (m) { _7o[favIconUrl] = m[1]; count++; }
      } else if (favIconUrl.startsWith('chrome://favicon/')) {
        // chrome://favicon — must use Google service
        if (!xhrLoad) continue;
        const pageUrl = favIconUrl.slice('chrome://favicon/'.length);
        const gUrl = "https://www.google.com/s2/favicons?domain_url="
          + encodeURIComponent(pageUrl) + "&sz=16";
        xhrLoad(gUrl, "binary")(function(d) {
          if (d) {
            try { _7o[favIconUrl] = btoa(d); } catch(e) {}
          }
        });
      } else if (xhrLoad) {
        // https: URL — load via XHR, cache under the exact same key
        xhrLoad(favIconUrl, "binary")(function(d) {
          if (d) {
            try { _7o[favIconUrl] = btoa(d); } catch(e) {}
          }
        });
      }
    }
    if (count > 0) console.log('[AC-MV3] Pre-fetched', count, 'favicons from _Yp cache');
  };

  // Run pre-fetch after a short delay (init must complete first)
  if (document.readyState === 'complete') {
    setTimeout(prefetchFavicons, 1000);
  } else {
    window.addEventListener('load', () => setTimeout(prefetchFavicons, 1000));
  }

  console.log('[AC-MV3] Patched _Zs for chrome://favicon compatibility (deferred)');
})();
