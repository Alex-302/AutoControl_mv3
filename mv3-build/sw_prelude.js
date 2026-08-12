/**
 * AutoControl MV3 — Service Worker Prelude
 *
 * §N references in comments point to Docs/FEATURES-MV3.md (feature status
 * & port gaps).
 *
 * Loaded FIRST via importScripts() in sw.js (SW-brain mode).
 * Provides the minimal DOM/browser shims so the legacy core scripts
 * (file67.js … mv3_native_shim.js) can run INSIDE the service worker.
 *
 * What is shimmed and why:
 * - window/document/location/history — the core scripts assume a page context
 * - localStorage — the core uses it for one-shot flags / caches
 * - chrome.extension — removed in MV3, stubbed for getBackgroundPage etc.
 * - chrome.tabs.executeScript/insertCSS — MV3 dropped them; rerouted to
 *   chrome.scripting (code strings run in the page's MAIN world, because
 *   eval/new Function are forbidden by the extension CSP in the SW)
 * - chrome.runtime.sendMessage — self-messaging never reaches the SW's own
 *   onMessage listener, so known commands are routed to __acLocalHandlers
 * - 'ac-sw-msg' event — replaces window CustomEvent for the native shim
 *
 * NOTE: deliberately NO 'use strict' directive here. The prelude is the first
 * statement of the core bundle (sw_core_bundle.js), so a 'use strict' here
 * would force strict mode onto ALL bundled legacy scripts, which rely on
 * sloppy-mode behaviors (implicit globals etc.). In main.html each file has
 * its own per-script directive; the bundle cannot replicate that.
 */

// ======== DOM GLOBAL POLYFILLS ========
// file67.js polyfills iterators on NodeList/HTMLCollection prototypes AT LOAD —
// these globals do not exist in a service worker.
function NodeList() {}
function HTMLCollection() {}
NodeList.prototype = [];
HTMLCollection.prototype = [];

// ======== GLOBAL ALIASES ========
const window = self;

const document = {
  addEventListener: () => {},
  removeEventListener: () => {},
  querySelector: () => null,
  querySelectorAll: () => [],
  getElementById: () => null,
  createElement: (tag) => {
    // Inert node. Real DOM (canvas/fonts/iframes) is NOT available in a SW;
    // UI/icon paths are overridden in sw.js (_6t, _Uu).
    return {
      isLoaded: false, onload: null, onerror: null, src: '', innerHTML: '',
      style: {}, children: [], content: null, dataset: {}, textContent: '',
      setAttribute: () => {}, removeAttribute: () => {}, appendChild: () => {},
      remove: () => {}, addEventListener: () => {}, getContext: () => null,
      getBoundingClientRect: () => ({ height: 0 }), offsetHeight: 0
    };
  },
  head: { appendChild: () => {} },
  body: { appendChild: () => {}, insertAdjacentHTML: () => {} },
  fonts: { load: () => Promise.resolve([]) },
  title: '', activeElement: null, documentElement: {}, readyState: 'complete'
};
const location = { href: '', search: '', pathname: '', hash: '', reload: () => {} };
const history = { replaceState: () => {}, pushState: () => {} };

// ======== localStorage SHIM (sync in-memory) ========
// Real settings live in chrome.storage.local (file47 _lr/_Gf read via _9i).
// localStorage only holds one-shot flags/caches, so an in-memory map is enough.
const __lsData = {};
const localStorage = {
  getItem: k => Object.prototype.hasOwnProperty.call(__lsData, k) ? __lsData[k] : null,
  setItem: (k, v) => { __lsData[k] = String(v); },
  removeItem: k => { delete __lsData[k]; },
  clear: () => { for (const k in __lsData) delete __lsData[k]; },
  key: i => Object.keys(__lsData)[i] || null,
  get length() { return Object.keys(__lsData).length; }
};

// ======== chrome.extension STUBS (removed in MV3) ========
if (!chrome.extension) chrome.extension = {};
chrome.extension.getBackgroundPage = () => self;
chrome.extension.getViews = () => [];
// AC-MV3 FIX (2026-08-10, FEATURES-MV3.md §7-8): isAllowedFileSchemeAccess /
// isAllowedIncognitoAccess DO exist in the MV3 service worker — pass the
// REAL value through instead of hardcoding false. The bundle's file13 builds
// its _id/_es/_As scheme gate from the result; file77's Q() then excludes
// file:// tabs from runInTab/runInFrames targets ONLY when the user has NOT
// enabled "Allow access to file URLs" (MV2 parity). Before the fix file://
// tabs were ALWAYS excluded even with the toggle ON. sw.js's "fileAcc" /
// "incogAcc" message cases call these too — they get the real value now.
// Fallback to false only when the API is unavailable (test harness, old
// Chrome). NOTE: the gate is read once per SW load — after toggling the
// switch on chrome://extensions, reload the extension (same as MV2).
const __acRealFileSchemeAccess = chrome.extension.isAllowedFileSchemeAccess;
const __acRealIncognitoAccess = chrome.extension.isAllowedIncognitoAccess;
chrome.extension.isAllowedFileSchemeAccess = function(cb) {
  try {
    if (typeof __acRealFileSchemeAccess === "function") { __acRealFileSchemeAccess.call(chrome.extension, cb); return; }
  } catch(e) {}
  try { cb && cb(false); } catch(e) {}
};
chrome.extension.isAllowedIncognitoAccess = function(cb) {
  try {
    if (typeof __acRealIncognitoAccess === "function") { __acRealIncognitoAccess.call(chrome.extension, cb); return; }
  } catch(e) {}
  try { cb && cb(false); } catch(e) {}
};

// ======== XMLHttpRequest SHIM ========
// XHR does not exist in service workers (fetch only), but the core engine
// (file67 _1p) uses it for text/blob/binary/dataUri loads, HEAD checks,
// custom headers and progress. Provide a minimal fetch-backed implementation.
function XMLHttpRequest() {
  this.response = null;
  this.responseType = '';
  this.status = 0;
  this.statusText = '';
  this.onload = null;
  this.onerror = null;
  this.onabort = null;
  this.onprogress = null;
  this._method = 'GET';
  this._url = '';
  this._headers = {};
  this._aborted = false;
}
XMLHttpRequest.prototype.open = function(method, url) {
  this._method = method;
  this._url = url;
};
XMLHttpRequest.prototype.setRequestHeader = function(k, v) {
  this._headers[k] = v;
};
XMLHttpRequest.prototype.abort = function() {
  this._aborted = true;
  if (this.onabort) this.onabort();
};
XMLHttpRequest.prototype.send = function(data) {
  const self = this;
  const opts = { method: this._method, headers: this._headers };
  if (data !== undefined && data !== null) opts.body = data;
  fetch(this._url, opts).then(r => {
    if (self._aborted) return;
    self.status = r.status;
    self.statusText = r.statusText;
    // AC-MV3 FIX (2026-08-02): core code reads response headers and the
    // final URL off the XHR object: file70 `_Su()` (file name from
    // Content-Disposition/Content-Type) and file77 `O()`/`saveURL`
    // (`n.getResponseHeader("content-type")`, `a.responseURL`). Without
    // these the old shim failed with "a.getResponseHeader is not a function"
    // in `ACtl.saveURL`. fetch's Headers are case-insensitive, so delegate.
    self._resp = r;
    self.responseURL = r.url || self._url;
    const t = self.responseType;
    if (t === 'blob') return r.blob();
    if (t === 'arraybuffer') return r.arrayBuffer();
    return r.text();
  }).then(body => {
    if (self._aborted || body === undefined) return;
    self.response = body;
    if (self.onload) self.onload();
  }).catch(e => {
    if (!self._aborted && self.onerror) self.onerror(e);
  });
};
XMLHttpRequest.prototype.getResponseHeader = function(name) {
  if (!this._resp) return null;
  const v = this._resp.headers.get(name);
  return (v === undefined || v === null) ? null : v;
};
XMLHttpRequest.prototype.getAllResponseHeaders = function() {
  if (!this._resp) return '';
  let out = '';
  this._resp.headers.forEach((v, k) => { out += k + ': ' + v + '\r\n'; });
  return out;
};

// chrome.browserAction was removed in MV3 — alias to chrome.action (toasts/_Cr)
if (!chrome.browserAction && chrome.action) chrome.browserAction = chrome.action;

// ======== chrome.tabs.executeScript / insertCSS → chrome.scripting ========
// NOTE: code strings cannot be evaluated in the SW (extension CSP forbids
// eval/new Function).
//
// Preferred path: chrome.userScripts.execute (Chrome 120+) — the only official
// MV3 API that runs code STRINGS inside the page without violating its CSP.
// Requires the "userScripts" permission (manifest) AND the user must enable
// the "Allow user scripts" toggle on chrome://extensions. When the toggle is
// off, Chrome rejects the call — we fall back to the MAIN-world eval wrapper
// (subject to the page's own CSP, like any page script).
let __acUsFailed = false;  // cached userScripts rejection (resets on SW restart)

/**
 * Inject code into a tab: preferred path is chrome.userScripts.execute
 * (CSP-safe); falls back to a MAIN-world eval wrapper when the userScripts
 * toggle is off.
 * @param {number} tabId — target tab
 * @param {string} code — code string to run
 * @param {object} details — {allFrames, runAt}
 * @param {function} cb — callback with the results array (or null)
 */
function __acInjectCode(tabId, code, details, cb) {
  // AC-MV3 FIX (2026-08-12, FEATURES-MV3.md §7-5 follow-up): details may
  // carry `frameIds` (runInPageCtx inside a runInFrames subframe — the SW
  // passes sender.frameId). frameIds and allFrames are MUTUALLY EXCLUSIVE
  // in the target — pick frameIds when given, else the allFrames flag.
  const buildTarget = () => (details.frameIds
    ? { tabId, frameIds: details.frameIds }
    : { tabId, allFrames: !!details.allFrames });
  const runEval = () => {
    try {
      // NOTE: `matchAboutBlank` is NOT a valid target property in MV3
      // scripting.executeScript (only tabId/frameIds/documentIds/allFrames).
      chrome.scripting.executeScript({
        target: buildTarget(),
        world: "MAIN",
        injectImmediately: true,
        func: (src) => {
          try { return (0, eval)(src); }  // eslint-disable-line no-eval
          catch (e) { return { __acError: String(e && e.message || e) }; }
        },
        args: [code]
      }).then(r => cb && cb(r.map(x => x.result)))
        .catch(e => { console.warn("[AC-MV3] injectCode failed:", e.message); cb && cb(null); });
    } catch (e) { cb && cb(null); }
  };

  if (!__acUsFailed) {
    try {
      if (chrome.userScripts && chrome.userScripts.execute) {
        chrome.userScripts.execute({
          target: buildTarget(),
          js: [{ code }],
          world: "MAIN",
          injectImmediately: true
        }).then(r => { __acUsFailed = false; cb && cb(r.map(x => x.result)); })
          .catch(e => {
            const m = String(e && e.message || e);
            if (/disabled|permission|granted|allow user scripts/i.test(m)) {
              // Toggle is off / permission missing → cache & fall back to eval.
              __acUsFailed = true;
              console.warn("[AC-MV3] userScripts.execute unavailable (" + m + ") → fallback to MAIN-world eval");
              runEval();
            } else {
              // Script ran but threw — do NOT re-run it via eval.
              console.warn("[AC-MV3] userScripts.execute error:", m);
              cb && cb(null);
            }
          });
        return;
      }
    } catch (e) { __acUsFailed = true; }
  }
  runEval();
}

// ======== PROTECTED PAGES UX (2026-08-09) ========
// Chrome refuses ANY script injection on protected pages (chrome://*,
// the Web Store, chrome-extension://, devtools://, view-source:) — a
// platform restriction identical in MV2 and MV3 (NOT a port regression).
// RUN SCRIPT / ACtl.* used to fail silently or with a raw "Cannot access
// a chrome:// URL". These helpers detect the page up front (a), map
// Chrome's raw rejection (b) and surface a friendly hint via
// chrome.notifications (c, optional permission — silent no-op when not
// granted). Declared HERE (bundle top-level) so both the prelude shim and
// sw.js can call them as free variables.
/**
 * Whether a URL is a protected page where Chrome blocks ALL script
 * injection.
 * @param {string} u — URL
 * @returns {boolean}
 */
function __acIsProtectedPage(u) {
  if (!u) return false;
  u = String(u);
  return /^(chrome|chrome-extension|devtools|view-source):/i.test(u) ||
    /^about:newtab$/i.test(u) ||
    /^https:\/\/(chrome\.google\.com\/webstore|chromewebstore\.google\.com)\//i.test(u);
}
const __acProtectedMsg = "This page is protected by Chrome (chrome://, Web Store, extension pages) — scripts cannot run here. Open a regular website and try again.";
let __acProtNotifAt = 0;
let __acProtNotifSeq = 0;
/**
 * Show a friendly notification when a script run was blocked on a protected
 * page (unique id per call, 1.5 s anti-spam; silent without the permission).
 */
function __acNotifyProtected() {
  try {
    const now = Date.now();
    // Anti-spam ONLY (a script looping on a protected page could fire a
    // notification per call). 1.5 s keeps every MANUAL run visible while
    // stopping loops. The original 10 s + a FIXED notification id made
    // notifications appear only occasionally (2026-08-09, user report) —
    // create() with the same id silently UPDATES the still-visible toast
    // instead of showing a fresh one.
    if (now - __acProtNotifAt < 1500) return;
    __acProtNotifAt = now;
    if (chrome.notifications && chrome.notifications.create) {
      // UNIQUE id per call — a new toast pops even when the previous one is
      // still on screen. Default priority (0) — no alerting/sound.
      const nid = "acProtectedPage_" + (++__acProtNotifSeq) + "_" + now;
      chrome.notifications.create(nid, {
        type: "basic",
        iconUrl: chrome.runtime.getURL("AutoCtrl/logo32.png"),
        title: "AutoControl: scripts blocked",
        message: __acProtectedMsg
      }, function () { try { void chrome.runtime.lastError; } catch (e) {} });
    }
  } catch (e) { /* notifications permission is optional — degrade silently */ }
}

/**
 * Execute a script FILE in a tab via scripting.executeScript, mapping
 * protected-page rejections to the friendly hint.
 * @param {number} tabId — target tab
 * @param {object} details — {file, allFrames, runAt}
 * @param {function} cb — callback with the results array (or null)
 */
function __acExecScriptFile(tabId, details, cb) {
  chrome.scripting.executeScript({
    target: { tabId, allFrames: !!details.allFrames },
    files: [details.file],
    injectImmediately: details.runAt === "document_start"
  }).then(r => cb && cb(r.map(x => x.result)))
    .catch(e => {
      // AC-MV3 UX (2026-08-09): protected pages reject ALL injection —
      // map the raw rejection to the friendly hint (the caller still gets
      // null; nothing else can be done — Chrome has no bypass API).
      const __acM = String(e && e.message || e);
      if (/cannot access (a )?(chrome|chrome-extension|devtools)|Cannot access a chrome/i.test(__acM)) {
        console.warn("[AC-MV3] executeScript blocked — protected page? " + __acM);
        __acNotifyProtected();
      }
      cb && cb(null);
    });
}

if (!chrome.tabs.executeScript) {
  chrome.tabs.executeScript = (tabId, details, cb) => {
    if (details && details.file) {
      // AC-MV3 UX (2026-08-09): pre-check the tab URL — protected pages
      // reject ALL script injection; notify immediately instead of after
      // the caller's (n()'s) 6s timeout.
      if (typeof chrome.tabs.get === "function") {
        try {
          chrome.tabs.get(tabId, (t) => {
            try { void chrome.runtime.lastError; } catch (x) {}
            if (t && __acIsProtectedPage(t.url || "")) {
              console.warn("[AC-MV3] executeScript blocked — protected page tab=" + tabId);
              __acNotifyProtected();
              cb && cb(null);
              return;
            }
            __acExecScriptFile(tabId, details, cb);
          });
          return;
        } catch (e) { /* tabs.get unavailable — plain path below */ }
      }
      __acExecScriptFile(tabId, details, cb);
    } else if (details && details.code) {
      __acInjectCode(tabId, details.code, details, cb);
    } else {
      cb && cb(null);
    }
  };
}
if (!chrome.tabs.insertCSS) {
  chrome.tabs.insertCSS = (tabId, details, cb) => {
    chrome.scripting.insertCSS({ target: { tabId }, files: details && details.file ? [details.file] : [] })
      .then(() => cb && cb()).catch(() => cb && cb());
  };
}

// ======== 'ac-sw-msg' EVENT DISPATCHER (replaces window CustomEvent) ========
const __acMsgListeners = [];
const __origAddEventListener = self.addEventListener.bind(self);
self.addEventListener = (type, fn, opts) => {
  if (type === 'ac-sw-msg') { __acMsgListeners.push(fn); return; }
  // 'message' events: file48.js registers a window "message" listener to
  // receive sandbox (file23.html) results. In the SW there is no real
  // window messaging — sw.js dispatches sandbox results via
  // __acDispatchSandboxMessage.
  if (type === 'message') { __acSandboxMsgListeners.push(fn); return; }
  return __origAddEventListener(type, fn, opts);
};
/**
 * Dispatch an ac-sw-msg event to the registered page listeners.
 * @param {object} detail — message detail
 */
function __acDispatch(detail) {
  for (const fn of __acMsgListeners.slice()) {
    try { fn({ detail }); } catch(e) {
      console.error("[AC-MV3] ac-sw-msg handler error:", e);
    }
  }
}
const __acSandboxMsgListeners = [];
// Called by sw.js when the offscreen document forwards a sandbox result
// (script execution result / userAPI call) from the file23.html iframe.
/**
 * Forward a sandbox result (from the offscreen file23.html iframe) to the
 * sandbox message listeners as a fake MessageEvent.
 * @param {object} data — sandbox message payload
 */
function __acDispatchSandboxMessage(data) {
  const fakeEvent = { data, source: { postMessage: () => {} } };
  for (const fn of __acSandboxMsgListeners.slice()) {
    try { fn(fakeEvent); } catch(e) {
      console.error("[AC-MV3] sandbox message handler error:", e);
    }
  }
}
self.__acDispatchSandboxMessage = __acDispatchSandboxMessage;

// ======== runtime.sendMessage BRIDGE ========
// chrome.runtime.sendMessage() from the SW does NOT reach its own onMessage
// listener, so commands emitted by the in-SW core engine are routed to the
// handler table that sw.js installs on self.__acLocalHandlers.
const __origRuntimeSend = chrome.runtime.sendMessage.bind(chrome.runtime);
chrome.runtime.sendMessage = (msg, cb) => {
  if (msg && msg.cmd && typeof self.__acLocalHandlers === 'object' &&
      typeof self.__acLocalHandlers[msg.cmd] === 'function') {
    try {
      const r = self.__acLocalHandlers[msg.cmd](msg, cb);
      if (r && typeof r.then === 'function') {
        r.then(x => cb && cb(x)).catch(() => cb && cb({ ok: false }));
      } else if (r !== undefined) {
        cb && cb(r);
      }
    } catch(e) {
      console.error("[AC-MV3] local handler error:", e);
      cb && cb({ ok: false, error: e.message });
    }
    return Promise.resolve();
  }
  return __origRuntimeSend(msg, cb);
};

// ======== LEADER: the SW is ALWAYS the leader in SW-brain mode ========
self._leader = 'sw';
self._isSW = true;
// Native-installed flag (page shim reads it from chrome.storage.local; the SW
// core reads the global — preset so nothing hangs waiting for it)
self._nd = true;
