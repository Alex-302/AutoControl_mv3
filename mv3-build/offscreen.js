/**
 * AutoControl MV3 — Offscreen document
 *
 * The SW has no DOM, but file48.js (Run Script, background mode) needs an
 * <iframe src="file23.html"> — the sandbox page where `unsafe-eval` is
 * allowed by manifest's sandbox CSP. This document hosts that iframe and
 * relays messages between the SW and the sandbox:
 *
 *   SW ──sendMessage{sandboxPost, data}──▶ offscreen ──postMessage──▶ iframe(file23)
 *   SW ◀──sendMessage{sandboxMessage, data}── offscreen ◀──postMessage── iframe(file23)
 *
 * file23.html loads file42.js inside the sandbox. There, `chrome.runtime` is
 * unavailable (sandbox pages have no extension APIs), so file42.js falls back
 * to the window.postMessage bridge (its `y` flag) — which is exactly what we
 * relay here.
 *
 * Since 2026-08-09 this document ALSO hosts the playAudio engine (FEATURES-MV3.md §7-1): the
 * SW has no AudioContext/speechSynthesis and the bundle's _7r (playAudio
 * action) lazy-loads file53.js via _9w — a no-op in the SW (document.head
 * shim) — which used to hang the action queue forever. The SW now routes
 * playAudio actions here:
 *
 *   SW ──sendMessage{cmd:"playAudio", tabGroups, params, runId}──▶ offscreen
 *   offscreen: lazy-load file67.js (generator machinery) + file53.js (the
 *   REAL MV2 sound engine — per-queue/enque/intrrp semantics preserved
 *   verbatim), then _lh(params, tabGroups, runId) — enqueue and ack; the
 *   sound plays in the background (the SW action already completed, MV2
 *   semantics — ack happens right after ENQUEUE, not after the sound ends).
 *
 * file53.js references bundle helpers that do NOT exist in this document —
 * replaced by tiny polyfills in __acAudioPolyfills():
 *   _9j = window        — file53 calls _9j._Vy(_od, alias) for system sounds
 *   _od = 294           — file56 constant "system sound by alias"
 *   _Tt / _up           — voice TEXT templates are pre-expanded by the SW
 *                         (the template machinery lives in the bundle); the
 *                         offscreen only ever sees plain strings → identity
 *   _ai                 — direct call (the serialized-proc machinery is not
 *                         needed for plain strings)
 *   _Yp = {}            — never consulted (see _Tt/_up)
 *   _Rk                 — speechSynthesis.getVoices poller (file13 semantics)
 *   _Vy                 — native bridge: offscreen → SW → native port
 *   _If                 — "Sound file" reads: extension resources via fetch,
 *                         disk paths via _Vy(255) → SW bundle _If (chunked);
 *                         FAILURE resolves {content:""} — file53 does
 *                         `d.content && _ql(d.content)`, so a false/undefined
 *                         would throw INSIDE the sound queue and stall it
 *   _ql                 — binary string → ArrayBuffer (file70)
 *   _Ot                 — telemetry stub (never used here)
 *
 * LOG MARKER: all console output from this document uses the `[AC-OFFSCREEN]`
 * prefix (the offscreen has its OWN inspector at chrome://extensions →
 * "Inspect views: Offscreen document") — it must never be confused with
 * the SW console (`[AC-MV3]`/`[AC-SW]` lines).
 */
(() => {
  'use strict';

  let bgIframe = null;
  let bgIframePending = null; // Promise resolved when the iframe is loaded
  let __acAudioReady = null;  // playAudio engine load promise

  /**
   * Inject a script tag into the offscreen document.
   * @param {string} name — extension-relative script path
   * @param {function} onload — success callback
   * @param {function} onerror — failure callback
   */
  function __acLoadScript(name, onload, onerror) {
    const s = document.createElement('script');
    s.src = chrome.runtime.getURL(name);
    s.onload = onload;
    s.onerror = () => onerror && onerror(new Error('Failed to load ' + name));
    (document.head || document.documentElement).appendChild(s);
  }

  // Bundle-helper polyfills required by file53.js (see header comment).
  // MUST run AFTER file67.js (uses _we/_ul/_za) and BEFORE file53.js.
  /**
   * Install the bundle-helper polyfills required by file53.js (must run
   * AFTER file67.js and BEFORE file53.js).
   */
  function __acAudioPolyfills() {
    window._9j = window;                       // file53: _9j._Vy(...)
    window._od = 294;                          // file56: system sound by alias
    window._Tt = a => a;                       // voice text arrives pre-expanded
    window._up = a => [a];                     // same
    // _ai — direct call, no serialized-proc machinery needed for plain
    // strings. MUST return a callback RUNNER — file53 does `yield _ai(...)`
    // and the generator machinery calls the yielded value (thenable OR
    // function) with the resume callback.
    window._ai = (a, c, ...b) => cb => cb(c(...b));
    window._Yp = {};                           // never consulted (plain strings)
    // _Rk — speechSynthesis.getVoices poller (file13.js semantics). Uses the
    // FREE variables _we/_ul/_za — file67 declares _we with `const`, so it is
    // a lexical global, NOT a window property (window._we is undefined).
    window._Rk = _we(function* () {
      for (let b = 0; 10 > b; ++b) {
        var a = speechSynthesis.getVoices();
        if (!_ul(a)) break;
        yield _za(5);
      }
      return a;
    });
    // _Vy — native bridge: the SW owns the native port.
    window._Vy = (type, payload) => (cb) => {
      try {
        chrome.runtime.sendMessage({ cmd: "acPlayNative", type, payload }, r => {
          if (chrome.runtime.lastError) { cb(undefined); return; }
          cb(r && r.ok === false ? undefined : (r && r.result !== undefined ? r.result : r));
        });
      } catch (e) { cb(undefined); }
    };
    // _If — sound FILE read ("Sound file" actions). Extension resources load
    // directly; disk paths fall back to the SW (bundle _If → native 255,
    // chunked reassembly is bundle-internal). Failure → {content:""} so
    // file53 skips cleanly instead of throwing inside the sound queue.
    window._If = (path) => (cb) => {
      const fail = () => cb({ content: "" });
      try {
        const url = path && String(path).indexOf("/") === 0 ? chrome.runtime.getURL(path) : path;
        fetch(url).then(r => {
          if (!r.ok) throw new Error("HTTP " + r.status);
          return r.arrayBuffer();
        }).then(buf => {
          let s = "";
          const u8 = new Uint8Array(buf);
          for (let i = 0; i < u8.length; ++i) s += String.fromCharCode(u8[i]);
          cb({ content: s });
        }).catch(fail);
      } catch (e) {
        window._Vy(255, { path: path, id: 1, charEnc: false, chunk: 786000 })(res => {
          if (res && res.content) cb(res); else fail();
        });
      }
    };
    // _ql — binary string → ArrayBuffer (file70.js)
    window._ql = a => {
      let b = new Uint8Array(a.length);
      for (let c = 0; c < a.length; ++c) b[c] = a.charCodeAt(c);
      return b.buffer;
    };
    // _Ot — telemetry stub (file13's error path never runs here)
    window._Ot = (...a) => { try { console.warn("[AC-OFFSCREEN] _Ot stub:", a && a[0]); } catch (e) {} };
  }

  // Lazy-load the playAudio engine: file67.js (generators/_1p/_lf/_ul/_za)
  // → polyfills → file53.js (the real MV2 sound engine). On failure the
  // promise resets so a later playAudio retries.
  /**
   * Lazy-load the playAudio engine (file67.js → polyfills → file53.js) and
   * cache the promise; resets on failure so a later playAudio retries.
   * @returns {Promise<void>}
   */
  function ensurePlayAudio() {
    if (__acAudioReady) return __acAudioReady;
    __acAudioReady = new Promise((resolve, reject) => {
      __acLoadScript('file67.js', () => {
        try {
          __acAudioPolyfills();
          __acLoadScript('file53.js', resolve, e => { __acAudioReady = null; reject(e); });
        } catch (e) { __acAudioReady = null; reject(e); }
      }, e => { __acAudioReady = null; reject(e); });
    });
    return __acAudioReady;
  }

  /**
   * Ensure the background-script sandbox iframe (file23.html) exists and is
   * loaded.
   * @returns {Promise<void>} resolves when the iframe finished loading
   */
  function ensureBgIframe() {
    if (bgIframe && bgIframePending) return bgIframePending;
    if (!bgIframe) {
      bgIframe = document.createElement('iframe');
      bgIframe.id = 'BGScript';
      bgIframe.src = chrome.runtime.getURL('file23.html');
      bgIframe.style.display = 'none';
      bgIframePending = new Promise((resolve, reject) => {
        bgIframe.onload = () => resolve();
        bgIframe.onerror = () => {
          bgIframe = null;
          bgIframePending = null;
          reject(new Error('Failed to load file23.html sandbox'));
        };
      });
      document.body.appendChild(bgIframe);
    }
    return bgIframePending;
  }

  // SW → sandbox: forward script execution request.
  chrome.runtime.onMessage.addListener((msg, sender, sendResponse) => {
    if (!msg) return false;

    // SW → playAudio (FEATURES-MV3.md §7-1): play a sound via Web Audio / speechSynthesis.
    // Ack right after ENQUEUE (MV2 _7r semantics — the SW action already
    // completed); the sound finishes in the background.
    if (msg.cmd === 'playAudio') {
      ensurePlayAudio().then(() => {
        try {
          _lh(msg.params || {}, msg.tabGroups || [], msg.runId || 0);
          sendResponse({ ok: true });
        } catch (e) {
          console.warn('[AC-OFFSCREEN] playAudio threw:', e && e.message || e);
          sendResponse({ ok: false, error: String(e && e.message || e) });
        }
      }).catch(e => {
        console.warn('[AC-OFFSCREEN] engine load failed:', e && e.message || e);
        sendResponse({ ok: false, error: String(e && e.message || e) });
      });
      return true;
    }

    if (msg.cmd !== 'sandboxPost') return false;
    ensureBgIframe().then(() => {
      try {
        bgIframe.contentWindow.postMessage(msg.data, '*');
        sendResponse({ ok: true });
      } catch (e) {
        sendResponse({ error: e.message });
      }
    }).catch(e => sendResponse({ error: e.message }));
    return true; // async response
  });

  // Sandbox → SW: script result / userAPI call. Relay to the SW's
  // 'message' listeners (file48.js m() handler via __acDispatchSandboxMessage).
  window.addEventListener('message', ev => {
    if (!bgIframe || ev.source !== bgIframe.contentWindow) return;
    chrome.runtime.sendMessage({ cmd: 'sandboxMessage', data: ev.data })
      .catch(() => {});
  });
})();
