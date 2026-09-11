;
/* ===== sw_prelude.js ===== */
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
;
/* ===== file67.js ===== */
'use strict';const _ay=()=>{};Object.freeze(_ay);
Object.defineProperties(Object.prototype,{"in":{writable:!0,value:function(...a){return _Xt(this,...a)}},includes:{writable:!0,value:function(a){for(let b in a)if(this[b]!=a[b])return!1;return!0}},add:{writable:!0,value:function(...a){for(let b of a)if(b)for(let [c,d]of b)this[c]=d;return this}},del:{writable:!0,value:function(...a){for(let b of _Ii(...a))delete this[b];return this}},keep:{writable:!0,value:function(...a){a=_Ii(...a).map(b=>String(b));for(let b in this)b.in(a)||delete this[b];return this}},
sc:{writable:!0,value:function(){let a={};for(let b in this)a[b]=this[b];return a}},[Symbol.iterator]:{writable:!0,value:function*(){for(let a in this)this.hasOwnProperty(a)&&(yield[a,this[a]])}}});NodeList.prototype.hasOwnProperty(Symbol.iterator)||Object.defineProperty(NodeList.prototype,Symbol.iterator,{writable:!0,value:[][Symbol.iterator]});HTMLCollection.prototype.hasOwnProperty(Symbol.iterator)||Object.defineProperty(HTMLCollection.prototype,Symbol.iterator,{writable:!0,value:[][Symbol.iterator]});
Object.defineProperties(Array.prototype,{add:{writable:!0,value:function(a){-1==this.indexOf(a)&&this.push(a)}},remove:{writable:!0,value:function(a,b){a=b||"object"!=typeof a||a instanceof Node?this.indexOf(a):_ki(this,a);return-1<a?this.splice(a,1)[0]:void 0}}});const _Kf=(a,b)=>a.filter(c=>0>b.indexOf(c)),_Vw=(...a)=>a.reduce((b,c)=>b.filter(d=>0<=c.indexOf(d)));Object.defineProperty(Set.prototype,"append",{writable:!0,value:function(...a){for(let b of a)this.add(b);return this}});
Object.defineProperties(String.prototype,{caplze:{writable:!0,value:function(){return this&&this[0].toUpperCase()+this.slice(1)}}});function _Ps(a){return a.split("").reverse().join("")}function _Ii(...a){return[].concat(...a)}function _Jw(a){return Array.isArray(a)}function*_Fg(a){_Jw(a)?yield*a.entries():a&&"object"==typeof a&&(yield*a)}function*_va(a){if(_Jw(a))for(let b=a.length-1;0<=b;--b)yield[b,a[b]];else a&&"object"==typeof a&&(yield*a)}
function*_Dr(a){for(let [b,c]of _Fg(a))yield[b,c,a],yield*_Dr(c)}function _Oo(a){for(let [,b]of _Fg(a))"object"==typeof b&&_Oo(b);return Object.freeze(a)}function _Xt(a,...b){for(let c of _Ii(...b))if(a===c)return!0;return!1}function _ki(a,b){for(var c=0;c<a.length;++c)if(a[c].includes(b))return c;return-1}let _Vo=(new Intl.Collator(navigator.language,{sensitivity:"accent",caseFirst:"false",numeric:!0})).compare,_Ha=a=>(null==a?"":a+"").trim().replace(/\s+/g," ");
function _ty(a){return a?JSON.parse(JSON.stringify(a)):a}function _sf(a){if(null==a||"object"!=typeof a)return a;let b=a.constructor.name.in("Boolean","Number","String","Date","RegExp")?new a.constructor(a.valueOf()):new a.constructor;for(var c in a)a.hasOwnProperty(c)&&(b[c]=_sf(a[c]));return b}
function _lf(a,...b){for(let c=0;c<b.length;++c){let d=b[c],e=b[c+1];"object"==typeof d||Number.isNaN(d)||Number.isNaN(e)||(a[d]=Number.isNaN(b[c+2])?e:a[d]||("object"==typeof e?e:"number"==typeof e?[]:{}),void 0===a[d]&&delete a[d],a=a[d])}return a}function _ji(a,...b){for(let c of b){if(!a)break;a=Number.isInteger(c)&&0>c&&_Jw(a)?a[a.length+c]:a[c]}return a}function _eo(a,...b){if(b.length&&"object"==typeof a){let c=b.shift();_eo(a[c],...b)&&(_Jw(a)?a.splice(c,1):delete a[c])}return _ul(a)}
function _ul(a){return null==a||(void 0!==a.length?!a.length:"object"==typeof a&&!Object.keys(a).length)}function _qw(a){return Math.round(+a)}function _fu(a,b,c){return Math.max(b,Math.min(a,Math.max(b,c)))}function _yd(a,b=0){b=Math.pow(10,b);return Math.round(a*b)/b}function _Bi(a,b,c="\\"){return a.replace(/./g,d=>b.includes(d)?c+d:d)}function _jf(a,b="nrt'\"\\"){b=RegExp(_Bi("\\(["+b+"])","\\"),"g");return a.replace(b,(c,d)=>({n:"\n",r:"\r",t:"\t"})[d]||d)}
function _9d(a){const b={'"':"&quot;","'":"&#39;","<":"&lt;",">":"&gt;"};return a.replace(/["'<>]/g,c=>b[c])}function _Uu(a){if(a instanceof DocumentFragment)return a;let b=document.createElement("template");b.innerHTML=a;return b.content}const _mg=a=>b=>a((...c)=>b(c)),_ti=(...a)=>_us(...a)(),_we=a=>function(...b){return _us(a,b,this)},_cg=a=>function(...b){return _us(a,b,this)()};
{let a=null,b=function(d){d.isDone=!0;for(a=d.parentGener;a&&a.isDone;)a=a.parentGener},c=function(d,e,h="next"){try{d.running=!0;var f=d[h](e);d.running=!1}catch(g){b(d);if(d.onError)return d.onError(g);if(a&&!a.running)return c(a,g,"throw");throw g;}if(f.done)return b(d),d.onSuccess?d.onSuccess(f.value):f.value;try{(f.value.then||f.value).call(f.value,g=>{c(d,g)},g=>c(d,g,"throw"))}catch(g){c(d,g,"throw")}};var _us=(d,e,h)=>{d=d.apply(h,e);d.parentGener=a;a=d;return(f,g)=>{d.onSuccess=f;d.onError=
g;return c(d)}}}function _5j(a){return(...b)=>(c,d)=>Promise[a]([].concat(...b).map(e=>"function"==typeof e?new Promise(e):e)).then(c,d)}let _Li=_5j("all"),_Yd=_5j("race"),_4y=(...a)=>b=>{let c=[],d=h=>c.push(h)&&d,e=(...h)=>{var f;if(f=c[0])h=c.shift()(...h),f="function"==typeof h?h(e):h;return f};_Li(...a)(e);return d(b)};function _wk(a){this.readyCount=this.asyncTotal=0;this.args=[];this.callback=a}
_wk.prototype={setCallback(a,b){this.callback=a;this.onReady()();b&&setTimeout(()=>this.callCallback(),b)},callCallback(){this.callback&&(this.callback(..._Ii(...this.args)),delete this.callback)},onReady(a){let b=this.asyncTotal++;return(...c)=>{a&&a(...c);this.args[b]=c;this.asyncTotal==++this.readyCount&&this.callCallback()}}};function _za(a){return b=>setTimeout(b,a)}
function _la(a){if(!new.target)return new Proxy(new _la(a),{get(b,c){return"length"==c?b.order.length:"function"==typeof b[c]?b[c].bind(b):b.dict[c]},set(b,c,d){b.set(c,d);return!0},deleteProperty(b,c){b.del(c);return!0},has(b,c){return b.has(c)},ownKeys(b){return b.order.slice()},getOwnPropertyDescriptor(b,c){if(b.has(c))return{configurable:!0,enumerable:!0,writable:!0}}});a||(a=[]);this.dict={};this.order=[];for(let [b,c]of a)this.dict[b]=c,this.order.push(""+b)}
_la.prototype={getPos(a){return this.order.indexOf(a)},set(a,b,c=-1){a+="";if(void 0===b)return this.del(a);this.dict.hasOwnProperty(a)||this.order.splice(0>c?this.order.length+1+c:c,0,a);return this.dict[a]=b},add(a){if(a)for(let [b,c]of a)this.set(b,c);return this},setPos(a,b){let c=this.order.indexOf(a);if(0>c)return!1;this.order.splice(c,1);this.order.splice(b,0,a);return!0},del(...a){for(let b of _Ii(...a))delete this.dict[b],this.order.remove(b);return this},delPos(a){this.del(this.order[0>
a?this.order.length+1+a:a])},has(a){return this.dict.hasOwnProperty(a)},[Symbol.iterator]:function*(){for(var a of this.order)yield[a,this.dict[a]]},toJSON(){return[...this]}};function _Nf(a){try{return!!new URL(a)}catch(b){return!1}}function _Xd(a){try{let b=new URL(a);return b.hostname?!0:0<="about bitcoin blob callto data file gtalk magnet mailto maps news skype sms tel urn view-source".split(" ").indexOf(b.protocol.slice(0,-1))}catch(b){return!1}}
function _1(a){try{return"file:"==(new URL(a)).protocol}catch(b){return!1}}function _5w(a){if(_Nf(a))return a;a="http://"+(a||"").trim();return _Nf(a)?a:"about:"}
function _1p(a,b,c="GET",d,e={},h){return(f,g)=>{let k=new XMLHttpRequest,l=m=>{f&&("HEAD"==c?f(k):f(m,k))};const p=b.in("dataUri","binary");k.open(c,a);k.responseType=p?"blob":b;const q=a.startsWith("data:")&&"blob"==k.responseType;q&&(k.responseType="arraybuffer");k.onload=function(){let m=q?new Blob([this.response]):this.response;if(!p)return l(m);let n=new FileReader;n.onload=function(){l(this.result)};n["readAs"+{dataUri:"DataURL",binary:"BinaryString"}[b]](m)};k.onerror=k.onabort=()=>g?g(Error(`Failed to load url '${a}' via ${c}`)):
l(void 0);for(let [m,n]of e)k.setRequestHeader(m,n);k.onprogress=h;k.send(d)}}function _wu(a,b){const c={401:"Unauthorized",403:"Forbidden",404:"Not Found",500:"Internal Server Error"};return a?c[a]?a+" "+c[a]:3<_ji(b,"statusText","length")?b.statusText:"Error "+a:"Unreachable URL"}function _ij(a,b){_1p(a,"blob")(c=>b(URL.createObjectURL(c)))}function _yp(a){let b=new FormData;for(let [c,d]of a)b.append(c,d);return b}
function _xu(a){try{var b=new URL(a)}catch(c){return a}b.hash?b.hash="":b.search?b.search="":1<b.pathname.length?b.pathname=b.pathname.replace(/[^\/:]+\/?$/,""):b.hostname.match(/\.[a-z]/i)&&(b.hostname=b.hostname.replace(/^[^\.]+\./,""));return b.href}function _yi(){return{}.add(new URLSearchParams(location.search.slice(1)))}
function _Es(a,b,c){const d=Math.abs(a),e=0<a;let h=0,f;return function(...g){clearTimeout(f);var k=Date.now()-h;if(k<d){if(e&&(f=setTimeout(()=>{b.apply(this,g);h=Date.now()},d-k)),c)return c.apply(this,g)}else if(k=b.apply(this,g),!Number.isNaN(k))return h=Date.now(),k}}function _so(a,b,c){const d=Math.abs(a),e=0>a;let h=0,f=function(...g){clearTimeout(f.timer);let k=d,l=Date.now();e&&h>l?k=h-l:h=l+k;f.timer=setTimeout(()=>{b.apply(this,g);h=0},k);if(c)return c.apply(this,g)};return f}
function _Wf(a,b){let c=a,d=b,e=[],h=function(){for(;e.length&&void 0!==c;){const [f,g]=e.shift(),k=c;d===f&&(c=void 0);Promise.resolve().then(()=>g(k))}};this.send=function(f=!0,g=0){c=f;d=g;h()};this.wait=function(f=0){return g=>{e.push([f,g]);h()}};this.clear=()=>c=void 0}function _Oh(a){let b=0;return function(...c){if(!b++)return a.apply(this,c)}}
function _sr(a,b,c){let d=document.createElement("SCRIPT");d.charset="utf-8";d.isLoaded=!1;d.onload=function(){this.isLoaded=!0;b&&b()};c&&(d.onerror=function(){c(Error(`Failed to load script file "${this.src}"`))});d.src=a;return d}function _9w(a,b){document.head.appendChild(_sr(a,b))}function _ka(a){return(b=_ay)=>{let c=document.querySelector(`script[src='${a}']`);c?null==c.isLoaded||c.isLoaded?b():c.addEventListener("load",b):_9w(a,b)}}let _vs=a=>b=>{window._=void 0;_9w(a,()=>{b(window._);window._=void 0})};
{let a=c=>1==(c+"").length?"0"+c:c,b={Y:c=>c.getFullYear(),y:c=>c.getYear(),M:c=>a(c.getMonth()+1),m:c=>c.getMonth()+1,D:c=>a(c.getDate()),d:c=>c.getDate(),H:c=>a(c.getHours()),h:c=>c.getHours(),I:c=>a(c.getMinutes()),i:c=>c.getMinutes(),S:c=>a(c.getSeconds()),s:c=>c.getSeconds()};var _8h=(c,d="Y-M-D")=>d.replace(/[dDmMyYhHiIsSTw]/g,e=>(b[e]||(()=>e))(c))}
function _Ns(a,b){let c=new Uint8Array(a.length);for(let d=0;d<a.length;++d){let e=a.charCodeAt(d);if(255<e)throw"Charcode above 255";c[d]=e}return new Blob([c],{type:b})}
let _Sr=a=>{try{return _Ns(a)}catch(b){return new Blob([a])}},_Xw=a=>b=>{let c=new FileReader;c.onload=function(){b(this.result)};c.readAsBinaryString(a)},_0u=_we(function*(a,b="deflate"){try{let c=a.stream().pipeThrough(new CompressionStream(b));return yield(new Response(c)).blob()}catch(c){}return a}),_tu=_we(function*(a,b="deflate"){try{let c=a.stream().pipeThrough(new DecompressionStream(b));return yield(new Response(c)).blob()}catch(c){}return a}),_J=_we(function*(a,b="deflate"){return yield _Xw(yield _0u(_Sr(a),
b))}),_Ro=_we(function*(a,b="deflate"){return yield _Xw(yield _tu(_Sr(a),b))});function _j(a){return JSON.parse(localStorage&&localStorage.getItem(a))}function _nt(a){let b=_j(a);localStorage.removeItem(a);return b}function _Jk(a,b){let c=_j(a);c!==b&&_9k(a,b);return c}
function _9k(a,b){let c=JSON.stringify(b);if(c)try{localStorage.setItem(a,c)}catch(d){DOMException&&d.code==DOMException.QUOTA_EXCEEDED_ERR&&(localStorage.clear(),localStorage.setItem(a,c))}else localStorage.removeItem(a);return b}
let _zf=_we(function*(a){for(let b;b=document.querySelector("import[src]"+(a?"":":not([defer])"));){let c=b.getAttribute("src");b.removeAttribute("src");if(c.match(/\.js$/i))yield(d,e)=>b.parentElement.replaceChild(_sr(c,d,e),b);else if(c.match(/\.html$/i))for(let d=0;5>d;++d){try{b.innerHTML=yield _1p(c,"text");break}catch(e){}yield _za(200)}}});var _Hu=new _Wf;document.addEventListener("DOMContentLoaded",()=>_zf(!1)(()=>_Hu.send("",!0)));let _Nh=a=>a;
;
/* ===== file91.js ===== */
'use strict';var _Uy=(t=>null==t?null:{filePath:t})(_yi().file);_Uy&&/^file:\/\//i.test(_Uy.filePath)&&(_Uy.filePath=_Uy.filePath.replace(/^file:\/\/(localhost)?/i,"").replace(/^\//,""));let _Ho=!0;
if(_Uy){let t=function(a,b,c,e){function l(...k){return new Proxy(()=>{},{get(f,g){f=[...k,g];var h=f.join(".");h=h in e?e[h]:b;if("function"===typeof h)return h(_ji(a,...f));if(h)return l(...k,g);g=_ji(a,...f);1<f.length&&"function"==typeof g&&(g=g.bind(_ji(a,...f.slice(0,-1))));return g},set(f,g,h){[...k]},apply(f,g,h){}})}return l()},m={},u={},p,q,n,y=_we(function*(){u=(yield _ru("customEntities"))||{}}),w=_we(function*(a){m=a;yield y();n&&_Ho&&n.toggleClass("noContent",_ul(m))}),z=_we(function*(a){let [b,
c]=yield _mg(_1p(a,"text","GET",void 0,{"Cache-Control":"no-cache, no-store, max-age=0"}));return 200==c.status?{content:b}:{error:_wu(c.status,c)}}),A=_we(function*(a){a=yield _9j._If(a,"text");a.error&&(a.error=yield _9j._Vy(_xo,+a.error));return a});_Uy.filePath&&(p=_we(function*(){p=null;let a=_1(_Uy.filePath)?yield A(_Uy.filePath):yield z(_Uy.filePath);if(a.error)q=a.error;else if(_Uy.fileEncode=a.charEnc,a.content)try{yield w(JSON.parse(a.content))}catch(b){q="The format of the specified file is invalid."}}));
let B=a=>b=>{chrome.storage.local.set({["__dummy__"]:a},()=>{chrome.storage.local.get("__dummy__",c=>{chrome.storage.local.remove("__dummy__");b(c.__dummy__)})})},C=_Es(400,()=>{n.addClass("unsaved").toggleClass("noContent",_ul(m));_rg()()});_Nh=function(a){return t(a,!0,"CHROME",{tabs:null,windows:null,"runtime.id":null,"runtime.getManifest":null,"runtime.getURL":null,"runtime.lastError":()=>null,"extension.getViews":null,"extension.isAllowedFileSchemeAccess":null,"extension.isAllowedIncognitoAccess":null,
bookmarks:null,"storage.sync.QUOTA_BYTES":null,"storage.sync.getBytesInUse":null,"storage.local.get":()=>(b,c)=>{let e=()=>c(_ty({}.add(b,b?m.sc().keep(Object.keys(b)):m)));p?p()(e):setTimeout(e,0)},"storage.local.set":()=>(b,c)=>{let e=()=>{B(b)(l=>{m.add(l);n&&_Ho&&C();c&&c()})};p?p()(e):e()},"permissions.getAll":()=>b=>setTimeout(()=>b({permissions:["bookmarks","sessions","background","notifications","downloads"],origins:["<all_urls>"]}),0),"runtime.sendMessage":()=>(b,c,e)=>{e&&("ping"==c?_9i({toolbarBtns:{}},
l=>{(_gj.indexOf(b)+"").in(Object.keys(l.toolbarBtns))?e("pong"):e()}):e())},"extension.getBackgroundPage":b=>()=>t(b(),!1,"BP",{"":"",_if:()=>u,_ps:()=>({}),_uy:()=>!1,_nk:!0,_ku:!0,_Gf:!0,_no:!0,_zj:!0,_8a:!0,_Jf:!0,_6t:!0,_Jp:!0,_6s:!0," ":""})})};let x=_we(function*(a,b){_Ho=!1;const c=yield f=>_9i({trigActList:[],toolbarBtns:{},sections:[]},f);let e={},l=[];"new"==b&&(b=_o(),c.sections.push({id:b,name:"Imported actions"}),e[b]=!0);for(let f of Object.keys(c.trigActList)){var k=c.trigActList[f];
if(~a.indexOf(f)){void 0===b?e[k.sctnId]=!0:k.sctnId=b;for(let [g,h]of _Dr(k.triggers))"eventId"==g&&(k=_eh(h),k.type==_cf&&_rj(k.num)&&l.push(k.num-_At))}else delete c.trigActList[f]}yield f=>_bd({trigActList:c.trigActList,sections:c.sections.filter(g=>e[g.id]),toolbarBtns:c.toolbarBtns.keep(l)},f);yield _me();m.del("mouseGest","advOpts","userVars","joysticksOrder","previewMakerParams","scrtEdtr");_Ts(m);_Ho=!0});_Uy.afterLoad=_we(function*(){function a(){let d=q||!_Uy.filePath?"New file":_Uy.filePath.replace(/^.*[\/\\]/,
"");document.title=d+" - Settings File Editor";$(window.frameElement).triggerEvt("titleChange")}let b=!1,c=()=>_1(_Uy.filePath)?_Uy.filePath.replace(/[^\\]+\.[^\\]+$/,""):"";const e=_we(function*(d,r=m){if(!_Uy.filePath||q||d){d=yield _xg(_ul(r)?c():!_Uy.filePath||_1(_Uy.filePath)?_Uy.filePath:_po(_Uy.filePath),_to,!0,_Lu);if(!d)return!1;history.replaceState(null,"",location.pathname+"?file="+encodeURIComponent(d)+location.hash);_Uy.filePath=d;q=null;n.find("> [type=text]").val(d);a()}let v;_1(_Uy.filePath)?
(r=yield _9j._4u(_Uy.filePath,_pk(JSON.stringify(r),"UTF-8",!1)))&&(v=`Error while saving to the file. <hr b=2> "${_Uy.filePath}" <hr b=2> ${yield _9j._Vy(_xo,+r)}`):v='Changes cannot be saved to an internet address. <hr b> Click on "Save as" in order to save to a local file.';if(v)return _Xp(!b&&window.frameElement?window.parent:window)._u(v,{type:"error"}),!1;n.removeClass("unsaved");return!0});let l=_Uy.safeToClose=d=>{n.is(".unsaved")?_Ng("","Unsaved changes will be lost if you continue. <hr b=2> Discard changes?")(d):
d(!0)},k,f=d=>{k=!0;location.replace(d)};$(window).on("beforeunload",d=>{if(!k&&n.is(".unsaved"))return"Discard changes?"});window.frameElement&&$(window).captureTgtEvt("mousedown",()=>$(window.frameElement).triggerEvt("mousedown",!0));p&&(yield p());if(!p&&_Uy.filePath&&_ul(m)){for(let b=0;50>b&&_ul(m);++b)yield _za(100)}a();yield d=>_4h("file40.css",d);n=$(`\n <fileEditBar helpCtx=sttgFilEdt>\n <img src="/AutoCtrl/logo32.png" width=26>\n <h h=welcm sides=br></h>\n <l>Settings file:</l>\n ${_oo("",q?"":_Uy.filePath,"No file path specified","readonly")}\n <!--btn act=new>New file</btn><h h=new></h-->\n <btn act=open>Open</btn><h h=opn sides=brl></h>\n <btn act=save>Save</btn><h h=sav sides=brl></h>\n <btn act=savAs>Save as</btn><h h=savAs sides=brl></h>\n <btn act=dscrd>Discard</btn><h h=disrd sides=brl></h>\n <btn act=impAll>Import all</btn><h h=imAll sides=brl bublCls=sharpCorner></h>\n </fileEditBar>\n `).on("click",
"btn",_cg(function*(d){d=$(this).attr("act");if(!d.in("new","open","dscrd")||(yield l))switch(d){case "new":(yield e(!0,{}))&&f(location.pathname+location.search);break;case "open":(d=yield _xg(c(),_to))&&f(location.pathname+"?file="+encodeURIComponent(d));break;case "savAs":case "save":yield e("savAs"==d);break;case "dscrd":f("?file="+encodeURIComponent(_Uy.filePath));break;case "impAll":(yield _Ng("","This will add the entire content of this settings file <br> to your AutoControl settings. <hr b=2> Continue?"))&&
_uw(yield r=>_9i(_2d,r))}})).appendTo(document.body);$(document.body).addClass("SFE_mode");let g=!0;var h=!0;if(null!=_yi().storInit){let [d,r]=window.frameElement.storInit;yield w(d);yield x(r);g=yield e(!0);h=`The actions have been successfully saved to: <hr b=2> "${_Uy.filePath}" <hr b=2> Do you want to review the file.`;h=g&&(yield _Xp(window.parent)._Ng("",h,{icon:"success"}))}else _Uy.filePath||(yield w({}));$("body > tabs").append("<perms><tit>Permissions <h h=prmLst></h></tit><cont></cont></perms>");
$(window.frameElement).triggerEvt({contentReady:h});q&&setTimeout(()=>_u(`Error while opening the file. <hr b=2> "${_Uy.filePath}" <hr b=2> ${q}`,{type:"error"}),300);_Jk("SFE_welcmShown",!0)||_Li(_Wp.wait(),_za(50))(()=>$("[h=welcm]",n).triggerEvt({mousedown:!0}));b=!0;return g});let D=_we(function*(a,b){const [c,e]=[_ty(m),_ty(u)];yield x(a,b);a=yield l=>_9i(_2d,l);[m,u]=[c,e];return a});var _dj=_cg(function*(a,b){a=a.get().map(c=>$(c).attr("actionId"));a=yield D(a,b);_uw(a,"new"!=b,!0,!0,!1,!1)})};
;
/* ===== file10.js ===== */
'use strict';const _Er={AutoCtrl:{id:"lkaihdpfpifdlgoapbfocpmekbokmcfd",name:"AutoControl"},TabThumbs:{id:"jpaiaplhepeiilhiegfnknedhjepknng",name:"Tab Thumbnails Switcher"},TabZoom:{id:"dnhodapkogdjinogphlafimejpmahoam",name:"Per Tab Zoom"}},_gj="mobdeadmeoonmekgnhfipfmhpaaneikl olhdckdaacidjfofhbnabkaibaicgdga ojmpajhbmodfdgimbaggdkeaneokdlol ofjhmfgenfjdnlcdbjfnognpokoepmao jlcblakgdlfkpbbbmhofckaieojiahpf okoojmkffinkicanmmgibmaebjlgopcc fabbjmklmjkhgalfhgcmmmgfiokkmdco cadecpfkcmceakcdhppapmkpehmhlkip mnclekklhkodkinhmlhpkleflmljopdb".split(" "),
_Zh=_Ps("lortnocotua.hcirh-emorhc-/ S/ NO:E/-exe.dmc").split("-");Object.freeze(_Zh);
const _8r=a=>a,_Yk=_Nh(window[_Zh[2]]),_Tj=_Yk.runtime.id,_Bj={alias:_Yk.runtime.getManifest().short_name},_fs="AutoCtrl_*.exe",_xd=_fs.replace("*","2025.4.22.0"),_ne="AutoControlZero.exe",_Xh="file76.dat",_7i="file69.dat",_or="Native-Component.exe",_ak="main.html",_mo="www.autocontrol.app",_Zo=`http${"s"}://${_mo}/`,_9n="alex-302.github.io",_4a={chromeWS:"https://chromewebstore.google.com/detail/",support:"https://groups.google.com/g/autocontrol_app"},_Ge=["normal","popup","devtools","panel","app"],
_fe=61472,_Ej=61488,_rw=61728,_he=61552,_is=61568,_k=0,_ri=1,_Ea=2,_Tk=3,_vk=4,_jr=5,_0r=6,_ph=7,_lt=8,_Lr=9,_g="CB-TIMEOUT",_2e=2,_jt=5,_ds=32,_Tg=193,_ht=225,_cw=258,_f=740,_Ka=786,_Nw=1260,_7d=1392,_qa=1,_kd=0,_fa=-1,_Nr=0,_La=4,_Dp=8,_ug=0,_8g=16,_2g=32,_Ui=1,_5k=2,_pw=3,_oi=4,_oe=5,_Fd=6,_I=7,_Iw=8,_wf=9,_Ff=10,_Wk=11,_Cw=12,_vp=13,_Ed=14,_4r=15,_td=16,_ik=17,_Gp=18,_Ay=30,_Vs=30,_At=50,_vt=80,_C=81,_Dj=100,_1s=1023,_Ap=0,_Io=1,_Vr=2,_uj=3,_Zy=2,_kt=0,_yj=1,_Ky=2,_rs=((navigator.userAgent||"").match(/\bchrome\/(\d+)/i)||
0)[1]|0;var _Ie=+((navigator.userAgent||"").match(/Windows NT ([\d.]+)/i)||0)[1];
const _fr=((navigator.userAgent||"").match(/\w+(?=\/\d+\b)/g)||[]).filter(a=>!a.in("Mozilla","AppleWebKit","Chrome","Safari","Version")),_Ae=0,_ao=1,_ih=2,_8t=4,_Qi=8,_hs=16,_Do=32,_fd=1,_s=13,_Dk=8,_Af=15,_4g=91,_Qd=40,_ky=16,_Rs=5,_rh=8,_Ty=7,_of=28,_Hw=36,_9e=38,_Oe=42,_Dg={profile:_Qd,desktop:_ky,downloads:15,documents:_Rs,recent:_rh,startup:_Ty,windir:_Hw,systemroot:_Hw,progfiles:_9e,progfilesx86:_Oe,appdata:_of},_Ds=2,_1o=1,_Ti=0,_ow=3,_Fe=4,_Ef=1,_V=2,_Si=3,_Ce=4,_9=5,_Ih=10,_9t=12,_6p=13,
_Pj=14,_Go=15,_xw=16,_2=17,_uu=20,_5e=21,_jo=25,_Jy=26,_qh=27,_Ru=28,_Df=29,_nj=30,_pj=31,_og=32,_Aa=33,_Hh=60,_3=80,_9r=40,_Po=59,_le=0,_1k=2,_ju=41,_gk=42,_Ch=43,_et=44,_Pg=45,_Nu=46,_yr=47,_Te=48,_Uw=49,_6o=50,_Ju=51,_gd=128,_9s=22,_Fi=26,_H=30,_jy=34,_Rr=-1,_to="AutoControl settings: *.acs;*.dat",_Wd=".acs,.dat",_Lu="acs";
;
/* ===== file32.js ===== */
'use strict';function _zr(d,b,c){return(f,a)=>{let e=new Image(b,c);e.onload=function(){f(this)};a&&(e.onerror=function(){a(Error("Failed to load image").add({fullUrl:this.src}))});e.crossOrigin="anonymous";e.src=d}}function _Ve(d,b,c){let f=document.createElement("canvas");f.width=d;f.height=b;if(c){let a=f.getContext("2d");a.fillStyle=c;a.fillRect(0,0,d,b)}return f}function _Hk(d,b="image/png"){return d.toDataURL(b).substr(`data:${b};base64,`.length)}
function _Lt(d){let b=document.createElement("dummyTag");b.style.cssText="position: fixed; visibility: hidden; top:0; left:0; padding: 0; border: none";b.style.font=d;b.innerText="a";document.body.appendChild(b);d=b.offsetHeight;b.remove();return d}
function _zi(d,b,c="black",f){let a=document.createElement("canvas"),e=a.getContext("2d",{willReadFrequently:!0});e.font=b;a.width=e.measureText(d||" ").width;a.height=_Lt(b);e.fillStyle=c;e.font=b;e.textBaseline="top";e.fillText(d||" ",0,0,f);return a}
let _Xi=_we(function*(d,b){for(var c of b){if(!c)continue;b=_Ve(d.width,d.height);let e=b.getContext("2d");if(c.resize){var f=_Jw(c.resize)?c.resize:(""+c.resize).trim().split(/\s+/);1==f.length&&(f[1]=f[0]);var a=+f[0]||parseFloat(f[0])*b.width/100;f=+f[1]||parseFloat(f[1])*b.height/100;b.width=Math.abs(a);b.height=Math.abs(f);e.scale(a/b.width,f/b.height);e.drawImage(d,0>a?a:0,0>f?f:0,b.width,b.height)}else if(c.rotate)a=c.rotate*Math.PI/180,f=(g,h,k)=>{g%=Math.PI;return 2*Math.sin((g>Math.PI/2?
Math.PI-g:g)+Math.atan2(k/2,h/2))*Math.sqrt(h*h/4+k*k/4)},b.width=f(a,d.height,d.width),b.height=f(a,d.width,d.height),e.translate(b.width/2,b.height/2),e.rotate(a),e.drawImage(d,-d.width/2,-d.height/2);else if(c.background)e.fillStyle=c.background,e.fillRect(0,0,b.width,b.height),e.drawImage(d,0,0);else if(c.margin)a=(""+c.margin).trim().split(/\s+/),1==a.length&&(a[1]=a[0]),2==a.length&&(a[2]=a[0]),3==a.length&&(a[3]=a[1]),b.width+=+a[1]+ +a[3],b.height+=+a[0]+ +a[2],e.drawImage(d,+a[3],+a[0]);
else if(c.shadow)a=c.shadow.trim().split(/\s+/,4),e.shadowOffsetX=+a[0],e.shadowOffsetY=+a[1],e.shadowBlur=+a[2],e.shadowColor=a[3],e.drawImage(d,0,0);else if(c.cornerRadius||c.blendWith)c.cornerRadius&&(c=(""+c.cornerRadius).trim().split(/\s+/),1==c.length&&(c[1]=c[0]),c={blendWith:yield _zr(`data:image/svg+xml,<svg xmlns="http://www.w3.org/2000/svg" width="${b.width}" height="${b.height}" viewBox="0 0 100 100" `+`preserveAspectRatio="none"><rect x="0" y="0" width="100" height="100" rx="${c[0]}" ry="${c[1]}"/></svg>`),
mode:"destination-in"}),c.blendWith&&(a=(c.mode||"").trim().split(/\s+/),e.drawImage(d,0,0),e.globalCompositeOperation=a[0],e.drawImage(c.blendWith,a[1]||0,a[2]||0));else continue;d=b}return d}),_Fh=_we(function*(d,b,c,f){try{var a=yield _zr(d,b,c)}catch(e){e.fullUrl.startsWith("chrome-extension")&&(yield _za(200),a=yield _zr(d,b,c))}d=yield _Xi(a,[{resize:`${b} ${c}`}]);try{return d.toDataURL(f)}catch(e){return _Ot("Canvas toDataURL",{imgUrl:a.src,stack:e.stack}),"data:image/gif;base64,R0lGODlhAQABAAAAACwAAAAAAQABAAA="}});
;
/* ===== file17.js ===== */
'use strict';function _9i(a,b,k=_Yk){k.storage.local.get(a,g=>{setTimeout(()=>b(_Qj(g||_ty(a)||{})))})}function _bd(a,b){_Yk.storage.local.set(_bj(a),()=>{b&&setTimeout(b)})}function _bj(a){a=a.sc();"trigActList"in a&&(a.trigActList=a.trigActList.toJSON());if("customEntities"in a){a.customEntities=a.customEntities.sc();for(let b in a.customEntities)a.customEntities[b]=[...a.customEntities[b]]}return a}
function _Qj(a){"trigActList"in a&&(a.trigActList=_la(a.trigActList));if("customEntities"in a)for(let b in a.customEntities)a.customEntities[b]={}.add(a.customEntities[b]);return a}function _Mw(a,b,k){a=a.sc().del(Object.keys(b));_ul(a)?k(b):_9i(a,g=>k(g.add(b)))}let _ru=(...a)=>b=>{_9i({[a[0]]:null},k=>b(_ji(k,...a)))};
{let a={},b=Symbol(),k=Symbol();var _Gu=function(...l){let r=l.pop();for(let n of l)"string"==typeof n&&(n=n.split(".")),l=""===n.slice(-1)[0]?(n.pop(),b):k,_lf(a,...n,l,[]).add(r)},_9y=function(...l){l[l.length-1].runOnce=!0;return _Gu(...l)},_B=function(...l){l[l.length-1].grpChng=-1;return _Gu(...l)};let g=function(l){function r(t,p,w){if(t){t[k]&&n.push({funcs:t[k],path:p});t[b]&&0==w.length&&n.push({funcs:t[b],path:p});p=p.concat(w.slice(0,1));let c=w.slice(1);r(t["*"],p,c);r(t[w[0]],p,c)}}let n=
[];r(a,[],l);return n},m,v=[],x=0;var _Mi=function(l,r,n=300,t){clearTimeout(m);v.push({keyPath:_Ii(l),value:r,callback:t});m=setTimeout(()=>{let p=v;v=[];let w={};for(let c of p)w[c.keyPath[0]]=null;++x;_9i(w,c=>{for(let e of p)_lf(c,...e.keyPath,e.value,NaN);_bd(c,()=>{const e=_Aw();let d={};for(let h of p){if(!e){var f=g(h.keyPath);for(let q of f){f=q.funcs;const y=_lf(d,q.path.join(),[]);for(let z=f.length;z--;){const u=f[z];u.grpChng?u.grpChng!=x&&(u.grpChng=x,u(c,q.path)):u.runOnce?(f.splice(z,
1),u(c,q.path)):0>y.indexOf(u)&&(y.push(u),u(c,q.path))}}}h.callback&&setTimeout(()=>h.callback(e))}})})},n)}}
let _sy=(a,b=0)=>(k=_ay)=>{let g=new _wk;for(let [m,v]of a)_Mi(m.split("."),v,b,g.onReady());g.setCallback((...m)=>{m=m.filter(v=>v)[0];k(m)})},_Ad=()=>a=>_Yk.storage.local.get(null,b=>a(b.del("LOCAL"))),_Sp=_we(function*(a){var b=window==_9j;if(b||(yield _Qk(_xk(a),"permMsgs/newSttgs"))){var k=yield g=>_9i({LOCAL:{}},g);
// AC-MV3: never lose entities that are missing from the imported file (e.g.
// scripts created after the last file write). Merge old customEntities in.
var _old=(yield g=>_9i({customEntities:{}},g)).customEntities;
try{console.warn("[AC-MV3] _Sp import from file: hasScript="+!!(a&&a.customEntities&&a.customEntities.script)+" oldScripts="+((_old&&_old.script)?Object.keys(_old.script).length:0)+" oldTypes="+(_old?Object.keys(_old).join(","):"-"))}catch(e){}
if(a&&a.customEntities&&_old)for(var _t in _old)if(_old[_t]&&!(String(_t) in a.customEntities)){try{a.customEntities[String(_t)]=JSON.parse(JSON.stringify(_old[_t]))}catch(e){}}
yield g=>_Yk.storage.local.clear(g);yield g=>_Yk.storage.local.set(a.add(k),g);if(_Aw())b||_u("ERROR: \n\n"+_Aw(),{type:"error"});else{yield g=>_9j._ku(g);if(b){(yield g=>_3d(a,g))||
_Yk.permissions.remove({permissions:["background"]});b=yield _zg({url:_Yk.runtime.getURL(_ak)});for(let g of b)_Yk.tabs.reload(g.id)}else _Rg("New settings imported successfully. <hr b=3> Reloading now...",1200).onHide(()=>location.href="");return!0}}}),_Xj=_we(function*(a){_9j._uy&&(yield _Ee("set",a));yield _Sp(a)});function _Ts(a){for(let [b,k]of _va(a))_Ts(k),_ul(k)&&(_Jw(a)?a.splice(b,1):k&&"object"==typeof k&&"value"==b&&a.name||delete a[b]);return a}
let _8s=_we(function*(){if((yield _ru("trigActList")).length||!_ul(_Ts(yield _ru("customEntities"))))return!1;let a=_Ts(yield _ru("mouseGest"));return!_ji(a,"triggers","preconds")&&(!_ji(a,"triggers","begin")&&!_ji(a,"triggers","end")||"other"!=_ji(a,"triggers","preset"))});
function _K(a,b,k,g){function m(c,e){for(let d=1;;++d)if(!(d in c||d in e))return d}function v(c,e,d){c.trigActList.del(e);for(let [f,h,q]of _Dr(c.customEntities.menuSpec))"type"==f&&"action"==h&&q.content==e&&(q.content=+d)}function x(c,e,d,f,h){h||(c.customEntities[e][f]=c.customEntities[e][d]);delete c.customEntities[e][d];d=e+":"+d;e=e+":"+f;e=JSON.stringify(_bj(c)).replace(RegExp(`"${d}"`,"g"),`"${e}"`);c.add(_Qj(JSON.parse(e)))}function l(c,e){return 0==_Vo(_Ha(c),_Ha(e))}function r(c,e,d=0){return JSON.stringify(e).replace(/"([a-z]+):(\d+)"/ig,
(f,h,q)=>(h=15>d&&_ji(c.customEntities[h],q,"value"))?'"'+r(c,h,d+1)+'"':f)}function n(c,e){return r(a,c)==r(b,e)}function t(){do{var c=!1;for(let e of Object.keys(b.trigActList)){let d=b.trigActList[e];for(let [f,h]of a.trigActList)!d.disabled&&h.disabled||h.title&&d.title&&!l(h.title,d.title)||!n([h.triggers,h.actions],[d.triggers,d.actions])||(c=!0,v(b,e,f),!h.title&&d.title&&(h.title=d.title),!h.icon&&d.icon&&(h.icon=d.icon))}}while(c)}function p(c,e,d){for(let [,f]of d)f.sctnId==c.id&&(f.sctnId=
e);c.id=e}function w(){for(let [c,e]of _va(b.sections))for(let d of a.sections)l(e.name,d.name)&&(p(e,d.id,b.trigActList),b.sections.splice(c,1))}for(let [,c]of a)_Ts(c);for(let [,c]of b)_Ts(c);(function(){for(let [c,e]of b.trigActList)if(a.trigActList.has(c)){let d=m(b.trigActList,a.trigActList);b.trigActList.set(d,e,b.trigActList.getPos(c));v(b,c,d)}})();(function(){a:for(;;){for(let [e,d]of b.customEntities)for(let [f]of d){var c=a.customEntities[e]||{};if(f in c){c=m(d,c);x(b,e,f,c);continue a}}break}})();
g&&t();(function(){a:for(;;){for(let [c,e]of b.customEntities)for(let [d,f]of e)if(f.name)for(let [h,q]of a.customEntities[c]||{})if(l(f.name,q.name)){if(n(q.value,f.value))x(b,c,d,h,!0);else{let y=f.name.replace(/\((\d+)\)$/,(z,u)=>`(${+u+1})`);l(y,f.name)&&(y=f.name+" (2)");b.customEntities[c][d].name=y}continue a}break}})();(function(){let c=b.sections.reduce((d,f,h)=>(d[f.id]=h,d),{}),e=a.sections.reduce((d,f,h)=>(d[f.id]=h,d),{});for(let d of b.sections)if(d.id in e){let f=m(c,e);p(d,f,b.trigActList)}})();
k&&w()}function _4p(a,b,k=!1){a.trigActList=k?b.trigActList.add(a.trigActList):a.trigActList.add(b.trigActList);a.sections.push(...b.sections);for(let [g,m]of b.customEntities)_lf(a.customEntities,g).add(m);for(let [g,m]of b.toolbarBtns)_ji(a.toolbarBtns[g],"icon","img")||(a.toolbarBtns[g]=m);return a};
;
/* ===== file13.js ===== */
'use strict';let _Rk=_we(function*(){for(let b=0;10>b;++b){var a=speechSynthesis.getVoices();if(!_ul(a))break;yield _za(5)}return a});function _Iy(a,b,c){for(let d of b)a[d]&&a[d].addListener(c)}function _Qs(a,b,c){for(let d of b)a[d]&&a[d].removeListener(c)}
window.addEventListener("error",a=>{var b=a.composedPath&&a.composedPath().map(c=>c.nodeName);b={tgtElem:_ji(a,"target","nodeName"),path:b};a.error&&b.add({error:a.error,stack:a.error.stack,elemSrc:a.error.src});b.stack||b.add({msg:a.message,file:a.filename,line:a.lineno,col:a.colno});_Ot("error",b)},!0);
const _Aw=(a,b,c)=>_Yk.runtime.lastError,_Vt=(a=!1)=>b=>{_Yk.windows.getAll({populate:a,windowTypes:_Ge},c=>b(c.filter(d=>!_9j._Ld[d.id])))},_zg=(a={})=>b=>{_Yk.tabs.query(a,c=>b(c&&c.filter(d=>!_9j._Ld[d.windowId])))},_Ms=(a,b=!1,c)=>_Yk.windows.get(a,{populate:b,windowTypes:_Ge},c),_zh=a=>a&&(a.url||a.pendingUrl)||"about:blank";function _js(a){return a.id==_Yk.tabs.TAB_ID_NONE?-a.windowId:a.id}function _Yw(a={}){return a.focused&&"minimized"!=a.state}
let _Ou=a=>b=>{_Yk.tabs.create({url:a,active:!0},c=>{_Yk.tabs.onUpdated.addListener(function g(f,e){f==c.id&&"complete"==e.status&&(_Yk.tabs.onUpdated.removeListener(g),b(c))})})},_Xu=_we(function*(a){let b=yield c=>_Yk.windows.getLastFocused(c);a.windowId!=b.id&&_Yk.tabs.move(a.id,{windowId:b.id,index:-1});return yield c=>_Yk.tabs.update(a.id,{active:!0},c)}),_Qo=_we(function*(a=""){let b=yield _zg({url:_Yk.runtime.getURL(_ak)});b=b.filter(c=>!_Ko(_zh(c)));return b[0]?yield _Xu(b[0]):yield _Ou(_ak+
"#"+a)}),_0s=_we(function*(){var a=yield _Qo("none");a=_Yk.extension.getViews({tabId:a.id})[0];yield _Xp(a)._Hu.wait();return a}),_0j=_we(function*(){return window==_9j||_Uy?window.frameElement&&!_Xp(window.parent)._Uy?window.parent:yield _0s():window}),_id,_es=/^ /;_Yk.extension.isAllowedFileSchemeAccess(a=>{_id=a;_es=new RegExp(`^(chrome|edge|about:|data:|view-source:|https:\/\/chrome.google.com\/webstore\/${a?"":"|file:"})`,"i")});const _As=a=>_es.test(a);
function _Ah(a){return a.charCodeAt(0)}function _Lj(a){return String.fromCharCode(a)}function _Gt(a,b,c=!0){return RegExp((b.in("equals","starts")?"^":"")+_3a(a)+(b.in("equals","ends")?"$":""),c?"i":"")}function _3a(a){return _Bi(a,"^$\\.*+?()[]{}|")}function _wh(a){return a.split(":")}function _hf(a){return!(!a||!_wh(a)[1])}function _gh(a,b=null){if(!a)return{};const c=_wh(a),d=1<c.length;d&&([b,a]=c);return _ji(d?_9j._if:_9j._Du,b,a)||{}}
function _w(a,b){a=_gh(a,"action").value;a.gener&&(a=a.gener(b));return a}function _1e(a,b,c,d){a=_Ii(a);let f=_wh(a.shift());_Mi(["customEntities"].concat(f,a),b,c,d)}function*_Xy(a,b=!1){const c=_9j._if[a]||{};let d=Object.keys(c).filter(f=>c[f].name&&c[f].value);b&&d.sort((f,e)=>_Vo(c[f].name,c[e].name));for(let f of d)yield a+":"+f}let _7o={};var _Zs=a=>b=>{var c=a.match(/^data:[^;]*;base64,(.+)$/);if(c)return b(c[1]);if(c=_7o[a])return b(c);_1p(a,"binary")(d=>b(_7o[a]=btoa(d)))};
/* AC-MV3 FIX (2026-08-08): telemetry OFF by default (privacy, user request) —
   enabled ONLY via Options → Advanced Options → "Send anonymous usage data"
   (advOpts.telemetry); live via storage.onChanged (no reload). The callback
   is still invoked when disabled (some call sites wait for it). */
let __acTel=!1;try{chrome.storage.local.get("advOpts",a=>{__acTel=!!(a&&a.advOpts&&a.advOpts.telemetry)});chrome.storage.onChanged.addListener((a,b)=>{if("local"==b&&a.advOpts)__acTel=!!((a.advOpts.newValue||{}).telemetry)})}catch(e){}function _Ot(a,b={},c){/* AC-MV3 (2026-08-08): log analytics actions — NOT a flood (rare events:
   install/update/error/diagnostics), and they follow the AC_LOG_* gate
   (console.warn is silenced when the SW/settings logging is unchecked). */
try{console.warn("[AC-TEL] "+(__acTel?"send":"skipped")+" event="+a)}catch(_e){}if(!__acTel)return c&&c();if(_9j._2u()&&a.in("error","NH-error","NH-except","userReload"))return c&&c();const d=navigator;var f=(d.userAgent.match(/\((.+?)\)/)||[,""])[1].split(/\s*;\s*/);const e=[..._9j._Zw].map(([,g])=>100*g.dpiX/96);f={uri:location.pathname+location.search+location.hash,natHostVer:"2025.4.22.0",brwrLang:d.language,brwrVariant:_ul(_fr)?void 0:_fr,osExtra:f[1]||d.platform,scaleFctr:1==e.length&&100==e[0]?void 0:e};_9j._dh&&(f.connectTime=Date.now()-_9j._dh);_1p(_Zo+"appEvent","json",
"POST",_yp({extName:"AutoCtrl",extVer:"2025.4.22",eventType:a,instID:_9j._7y,timeOffset:Math.floor((Date.now()-_9j._Ct)/1E3),opSys:_Ie?d.platform+" "+_Ie:d.platform.match(/^win/i)?"Windows":d.platform,brwrName:_9j._Jh||_fr[0]||"",brwrVer:_rs,ctxData:JSON.stringify(f),evtData:JSON.stringify(b),domain:location.hostname}))(c)}function _Cr(a,b){null!=b&&_Yk.browserAction.setBadgeBackgroundColor({color:b});null!=a&&_Yk.browserAction.setBadgeText({text:a})}
function _7g(a,b=!1){const c=[94,14,77,49,13];let d=b?new Uint8Array(a.length):"";for(let f=a.length;0<=--f;){let e=a.length-f-1,g=(a.charCodeAt(f)-c[e%c.length]-e)%256;0>g&&(g+=256);b?d[e]=g:d+=String.fromCharCode(g)}return d}
let _3t=_we(function*(a,b){const c="B64"==b,d="blob"==b,f=/\.dat$/.test(a);if(d&&f||c)b="binary";b=yield _1p(a,b);f&&(b=_7g(b,d),/\.gz\./.test(a)&&(b=d?yield _tu(new Blob([b]),"gzip"):yield _Ro(b,"gzip")),!d||b instanceof Blob||(b=new Blob([b])));c?b=btoa(b):b instanceof Blob&&(b=new Blob([b],{type:"application/vnd.microsoft.portable-executable"}));return b});
function _ly(a,b,c=document){"string"==typeof c&&(c=document.querySelector(c));a=c.querySelector("#"+a).innerHTML.trim();b={URLS:_4a,EXT:_Bj}.add(b);return a=a.replace(/\$\{([\w.#]+)\}/g,(d,f)=>"#"==f[0]?_ly(f.substr(1),b,c):_ji(b,...f.split(".")))}let _Xp=a=>a;
var _ve=_cg(function*(a,b){b||(b=yield _ru("toolbarBtns",a));if(_ji(b,"icon","img")){var c=yield _zr(b.icon.img);let d=_Ve(c.width,c.height).getContext("2d");d.drawImage(c,0,0);c=d.getImageData(0,0,c.width,c.height);c={data:[...c.data],width:c.width,height:c.height}}b=(_ji(b,"title")||"").replace(/<br>/g,"\n")+"\v"+Array(+a+2).join("\t");_Yk.runtime.sendMessage(_gj[a],{type:"btnProps",title:b,icon:c})});
{var _Id=function(e,g){try{switch(g){case "UTF-16LE":return f(e,!1);case "UTF-16BE":return f(e,!0);case "UTF-8":case "US-ASCII":return c(e)}}catch(h){}return e},_pk=function(e,g,h=!0){switch(g){case "UTF-16LE":return d(e,!1,h);case "UTF-16BE":return d(e,!0,h);default:try{return btoa(e),e}catch(k){}case "UTF-8":return b(e,h)}};const a=String.fromCharCode(65279),b=function(e,g){e=e.length&&65279!=e.charCodeAt(0)&&g?a+e:e;return unescape(encodeURIComponent(e))},c=function(e){e=decodeURIComponent(escape(e));
return 65279==e.charCodeAt(0)?e.substr(1):e},d=function(e,g=!1,h){e=e.length&&65279!=e.charCodeAt(0)&&h?a+e:e;h=8*+g;g=8*+!g;let k="";for(let l=0;l<e.length;++l){const m=e.charCodeAt(l);k+=String.fromCharCode(m>>h&255);k+=String.fromCharCode(m>>g&255)}return k},f=function(e,g=!1){const h=+g;g=+!g;let k="";for(let l=0;l<e.length;l+=2)k+=String.fromCharCode(e.charCodeAt(l+h)|e.charCodeAt(l+g)<<8);return 65279==k.charCodeAt(0)?k.substr(1):k}}
function _lo(...a){return 1==a.length?_j(a[0]):_9k(a[0],a[1])}function _Ko(a){"string"==typeof a&&(a=new URL(a));a=(a.hash||"").slice(1);return a.startsWith("script=")?a.split("=")[1]:!1}function _3d(a,b){_Mw({trigActList:null,mouseGest:{}},a,c=>{let d=[];for(let [,f]of c.trigActList)f.disabled||d.push(f.triggers);"other"==_ji(c.mouseGest,"triggers","preset")&&d.push(c.mouseGest.triggers);b(!!JSON.stringify(d).match(/"closed":true/))})}
let _Ee=_we(function*(a,b){if(!b){b=yield d=>_9i({trigActList:[]},d);var c=0}for(let [d,f,e]of _Dr(b.trigActList))if("preconds"==d&&f.chromeState&&(f.chromeState.inactive||f.chromeState.closed)){switch(a){case "set":e.author={};case "del":case "add":_lf(e,"author",_9j._7y,"del"==a?void 0:1,NaN);break;case "clear":e.author&&(e.author=void 0)}++c}c&&(yield d=>_bd(b,d));return!!c});
function _Bw(a){if(a.author&&_9j._uy){let b=_ji(a,"preconds","chromeState");return b&&!a.author[_9j._7y]&&(b.inactive||b.closed)}return!1}function _5h(a,b,c,d){d=d||1024;b=b||3;for(var f=0;1E3<=a;++f)a/=d;return(c||"0 1").replace(/(0|1)/g,function(e,g){return[+a.toPrecision(b-(1>a)),f?" KMGTPEZY"[f]:""][g]})}
let _xg=_we(function*(a,b="",c=!1,d="",f=!0){a=(a.match(/\b[a-z]:[^:<>|*?"]+/i)||a.match(/\\\\[a-z][^:<>|*?"]+/i)||a.match(/[^:<>|*?"]+/i)||[""])[0].replace(/\//g,"\\").replace(/(?!^)\\{2,}/g,"\\");"DIR"!=b&&(b=b.replace(/\s*[:,]\s*/g,"\x00")+"\x00");for(var e=!1,g=0;2>g&&!1===e;++g)e=yield _9j._Vy(_e,{path:a,filter:b,dfltExt:d,modal:f,saveAs:c},6E4),a="";return"CB-TIMEOUT"==e?"":e});const _Cu="chrome://favicon/";function _ig(a){return _Cu+(a.startsWith("data")||a.startsWith("javascript")?"":a)}
function _hw(a){"string"==typeof a&&(a=[{menuId:0,negate:"closed"==a}]);return a}function _po(a,b){a=_Nf(a)?new URL(a):new URL("dummy:"+a);var c=a.pathname.replace(/\/+$/g,"");if(c){if(a=c.match(/[^\/]+$/)[0].replace(/([^.]+\.\w+):.+$/,"$1"),b){c=/\.([^.]+)$/;let d=(a.match(c)||[,""])[1].toLowerCase();d?d[0]!=b[0]&&(a=a.replace(c,"."+b)):a+="."+b}}else a=a.hostname+(b?"."+b:"");return decodeURIComponent(a).replace(/[\/\\:*?"<>|]/g,"_")}
{const a=["userVars"],b=["userVars"];var _ur=(c,d,f=!0)=>(f?b:a).concat(c||"",d?(d+"").split("."):[]),_Rd=c=>null===c||Number.isNaN(c)?void 0:c,_ae=_we(function*(c,d){return yield _ru(..._ur(c,d,!1))}),_ge=(c,d,f,e)=>g=>_Mi(_ur(c,d,e),_Rd(f),0,g),_aa=(c,d)=>f=>_Mi(_ur(c,d,!1),void 0,0,f)};
;
/* ===== file34_mv3.js ===== */
'use strict';let _Gk,_Ft=[],_ea=[],_ts=[],_n=[],_Kt,_na={},_Or={},_He={},_Np;var _Yp={},_cd={},_4t,_if={},_Du={binSwtch:[]},_ps={},_dh,_Ld={};let _ek,_Sk=0,_zo,_dg=[],_hd=[],_Mo={},_da={},_5g=!1,_rr=!1,_Ek=!1,_Fy,_r;const _m={},_Vg={};var _9j=window,_Kd="",_Jh="";function _yt(){return(Math.round(_Ct/100)%parseInt("zzzzzz",36)).toString(36)}var _Ct=Date.now(),_ip=Math.floor(_Ct/1E3),_7y=_yt(),_nd,_Eu=new _Wf;function _2u(a=0){return 22025<=(Date.now()/1E3/60/60/24|0)+a}
_2u(5)&&_Yk.runtime.requestUpdateCheck((a,c)=>{"update_available"==a&&_co(2)});function _ze(a){let c=[],b=d=>{if(a){let e=a.shift();if("object"==typeof e)d[_Jw(d)?"push":"add"](...e)}else c.push(d)};b(_Ft);b(_ea);b(_n);b(_Mo);b(_hd);b(_da);b(_He);return c}function _co(a=0,c=!1,b){c&&(_Cr("Wait","#F00"),_9k("showNotif",!0));_9k("noStupEvt",!0);_Lk(_vh,null,d=>{if(a){_9k("extensionState",_ze());if(1==a){/* AC-MV3 FIX (2026-08-08): the SW performs the native restart (type 55 -> engine taskkill -> port drop -> reconnect) and shows the " OK " badge itself once reconnected (MV2 shows OK after the background-page reload reconnects). Here: reload the current page only. */try{_Yk.tabs.query({url:"chrome-extension://"+_Yk.runtime.id+"/*"},r=>{r.forEach(t=>{try{_Yk.tabs.reload(t.id)}catch(e){}})})}catch(e){}}else try{_Yk.runtime.reload()}catch(e){}}else _Xg()(b)})}_ze(_nt("extensionState"));
_nt("showNotif")&&_ti(function*(){var a=yield _Eu.wait();a?_Cr(" OK ","#0BAD01"):_Cr("Error","#F00");setTimeout(()=>_Cr(""),1E3);let c=_nt("diagnostics");if(c)if(_Ot("userReload",c.add({NHConnect:a})),_ji(c,"downKeys","length"))_Kg(c.downKeys);else if(0==c.actWinMine){let b=c.lastFocusId||c.focusedId||c.hndlToId[c.focusWin];a=b?yield d=>_Ms(b,!0,d):null;_Ht(a)}});function _Ij(){this.queue=[]}
_Ij.prototype={execNext(){let a=this.queue[0];if(a)a(()=>{this.queue.shift();this.execNext()});else if(a=this.onEmptyCallback)delete this.onEmptyCallback,a()},addFunc(a){this.queue.push(a);1==this.queue.length&&this.execNext()},empty(){return!this.queue.length},onEmpty(a){this.empty()?a():this.onEmptyCallback=a}};let _Lw=new _Ij;
{let a=!1,c=[];var _Mt=(b,d)=>e=>_ti(function*(){if(a)c.push([d,e,b]);else for(;;){a=!0;_zw=b;try{for(;;){var g=d();if(_Lw.empty())break;yield f=>_Lw.onEmpty(f)}}catch(f){_Ot("error",{stack:f.stack,context:"runAsyncSeqProc"})}a=!1;e(g);if(a||0==c.length)break;[d,e,b]=c.shift()}})}function _ai(a,c,...b){return _Mt(a,()=>c(...b))}function _3g(a,c){_Yk.windows.create(a,b=>{try{__acInvalidateEnumCache()}catch(e){}b&&"normal"==b.type&&"about:blank"==_zh(b.tabs[0])&&(_Vg[b.tabs[0].id]=!0);c(b)})}
function _6a(a,c){_Yk.tabs.create(a,b=>{try{__acInvalidateEnumCache()}catch(e){}b&&"about:blank"==_zh(b)&&(_Vg[b.id]=!0);c(b)})}function _Dw(...a){return[].concat(...a).filter(c=>_Yp[c])};
;
/* ===== file56.js ===== */
'use strict';const _7s=10,_ro=20,_zu=21,_Z=30,_6k=35,_Qr=40,_Qw=50,_vh=55,_4e=60,_hk=65,_Ma=67,_5r=70,_mu=72,_Ei=80,_Xa=90,_fk=100,_Cf=110,_Cj=122,_Yj=125,_yg=130,_1d=135,_Mu=136,_5t=140,_ta=150,_Rw=160,_b=170,_Ws=175,_rd=180,_3f=185,_vy=190,_ej=195,_wr=197,_Jo=200,_Ia=205,_Ww=210,_e=240,_Q=250,_0f=255,_vr=256,_7e=260,_Qa=270,_tl=280,_t=285,_Hi=286,_gw=292,_5f=293,_od=294,_Wj=295,_Dt=300,_bg=305,_je=310,_be=315,_8p=320,_Ua=330,_uo=335,_Eo=336,_bw=340,_6f=344,_Hr=350,_tp=355,_ng=360,_si=365,_3k=370,
_wa=375,_4s=380,_Fr=385,_0e=390,_uh=395,_ms=400,_Gs=403,_Tf=410,_cp=415,_3i=420,_Cs=450,_ya=451,_xo=460,_2p=470,_2f=475,_nw=480,_No=485,_Bf=490,_R=704,_np=705,_9p=710,_Pd=715,_Ip=720,_mj=721,_Ki=730,_Qg=735,_9g=740,_Hf=750,_fo=760,_0i=765,_rp=770,_ra=780,_7a=781,_ni=782,_9u=783,_Wr=790,_kw=800,_ny=801,_Na=802,_ef=810,_Xk=900,_io=901,_jh=905,_8d=910,_xp=920,_4k=930,_Ji=931,_wl=932,_6w=940,_Qh=941,_Wg=942,_wp=943,_hj=0;
;
/* ===== file57.js ===== */
'use strict';const _zt=256,_N=512,_9h=64512,_Lo=0,_mk=1024,_cf=2048,_th=4096,_Ar=5120,_Uh=6144,_Pu=7168,_ee=0,_xe=1,_af=10,_zk=11,_cj=98,_4j=99,_8w=32,_Od=11,_Cd=32,_hy=60,_Gj=0,_h=1,_sa=2;function _Me(a){return"keybrd mouse joystk joystk joystk joystk joystk joystk joystk joystk voice envEvt".split(" ")[a]}
function _3h(a){a="object"==typeof a?a:_eh(a);return a.isDownUp?0<=a.miscNum?a.num<_Qu?_xe:a.miscNum<_Cd?_ee:((a.miscNum-_Cd)/_hy|0)+2:_qe<=a.num&&a.num<=_Vf&&a.num!=_Pi?_xe:_ee:a.type==_Ar?_af:a.type==_th?_xe:a.type==_cf?_zk:_4j}function _gi(a){let b=a&~_zt;return 33<=b&&b<=_6||45==b||46==b||b==_7k?a:b}function _eh(a,b){if(!a)return null;a={type:a&_9h,num:a&~_9h};a.isDownUp=a.type.in(_Lo,_mk);a.num&_N?a.miscNum=a.num&~_N:a.isDownUp&&(a.num=_gi(a.num));b&&(a.devId=_3h(a));return a}
function _rj(a){return _At<=a&&a<_vt}function _Ys(a){return a&&a.isDownUp&&(!("miscNum"in a)||a.devId!=_xe)}function _5u(a){return a.isDownUp&&a.miscNum>=_Cd}function _Je(a){return a>=_N+_Cd?_Kw(a):_ji(_By,a,0)||"Key "+a}
function _Kw(a){var b=["more","less"],d=["left","right"],c=["up","down"],e="X Axis;Y Axis;Z Axis;X Rot.;Y Rot.;Z Rot.;Slider;Dial;Wheel;D-pad;D-pad".split(";");b=[d,c,["back","forward"],b,b,b,b,b,b,d,c];a=(a&~_N)-_Cd;d="Joy "+((a/_hy|0)+1)+" - ";a%=_hy;a<_8w?d+="Btn "+(a+1):(a-=_8w,c=a/2|0,d+=e[c]+" "+b[c][a%2]);return d}function _xa(a,b){for(let d of b){let [c,e,f]=d;a[c[0]]=[c[1],[e[0],f[0]]];a[e[0]]=[e[1],c[0]];a[f[0]]=[f[1],c[0]]}}
const _qe=1,_md=2,_ir=4,_Ze=5,_Vf=6,_Tr=0|_N,_ch=1|_N,_Lp=2|_N,_xr=3|_N,_Pi=3,_nf=8,_sd=20,_ye=32,_pd=144,_Cy=145,_7k=13,_cs=160,_Dh=161,_jp=162,_xs=163,_St=164,_ut=165,_Pr=255|_zt,_ma=36,_Uo=_ma|_zt,_nh=35,_Yo=_nh|_zt,_Ly=187,_Bs=189,_Va=37,_lw=38,_py=39,_6=40,_Mk=_Va|_zt,_6e=_lw|_zt,_4w=_py|_zt,_6g=_6|_zt,_1g=166,_7w=167,_Ca=168,_bo=169,_Gw=170,_0a=171,_Tw=172,_Re=173,_fg=174,_Yy=175,_ld=176,_1y=177,_xi=178,_de=179,_fh=180,_yo=181,_By={[_qe]:["Left Btn"],[_md]:["Right Btn"],[_ir]:["Middle Btn"],
[_Ze]:["4th Btn"],[_Vf]:["5th Btn"],[_Tr]:["Vert. Wheel"],[_ch]:["Horz. Wheel"],[_Pr]:["Pause"],27:["Escape"],9:["Tab"],[_ye]:["Space"],[_nf]:["Back Space"],[_sd]:["Caps Lock"],[_pd]:["Num Lock"],[_Cy]:["Scroll Lock"],[93]:["Menu"],19:["Pause"],44:["Prt Scr"],[_Ly]:["Equal"],[_Bs]:["Hyphen"],190:["Period"],188:["Comma"],186:["Colon"],191:["Slash"],220:["Backslash"],219:["Bracket ["],221:["Bracket ]"],192:["Tilde"],222:["Quote"],12:["Clear"],110:["Num Point"],106:["Multiply"],107:["Plus"],109:["Minus"],
111:["Divide"],[_1g]:["Brwr. Back"],[_7w]:["Brwr. Forward"],[_Ca]:["Brwr. Refresh"],[_bo]:["Brwr. Stop"],[_Gw]:["Brwr. Search"],[_0a]:["Brwr. Favorites"],[_Tw]:["Brwr. Home"],[_Re]:["Vol. Mute"],[_fg]:["Vol. Down"],[_Yy]:["Vol. Up"],[_ld]:["Next Track"],[_1y]:["Prev Track"],[_xi]:["Media Stop"],[_de]:["Play/Pause"],[_fh]:["e-mail"],[_yo]:["Media Player"],182:["App 1"],183:["App 2"],112:["F1"],113:["F2"],114:["F3"],115:["F4"],116:["F5"],117:["F6"],118:["F7"],119:["F8"],120:["F9"],121:["F10"],122:["F11"],
123:["F12"],124:["F13"],125:["F14"],126:["F15"],127:["F16"],128:["F17"],129:["F18"],130:["F19"],131:["F20"],132:["F21"],133:["F22"],134:["F23"],135:["F24"],65:["A"],66:["B"],67:["C"],68:["D"],69:["E"],70:["F"],71:["G"],72:["H"],73:["I"],74:["J"],75:["K"],76:["L"],77:["M"],78:["N"],79:["O"],80:["P"],81:["Q"],82:["R"],83:["S"],84:["T"],85:["U"],86:["V"],87:["W"],88:["X"],89:["Y"],90:["Z"],226:["Bracket <>"]},_Qu=4|_N,_7h=_Qu,_Zp=_7h+0,_6d=_7h+1;
_xa(_By,[[[16,"Shift"],[_cs,"Left Shift"],[_Dh,"Right Shift"]],[[17,"Control"],[_jp,"Left Ctrl"],[_xs,"Right Ctrl"]],[[18,"Alt"],[_St,"Left Alt"],[_ut,"Right Alt"]],[[_Zp,"Enter"],[_7k,"Std. Enter"],[_7k|_zt,"Numpad Enter"]],[[_6d,"Win"],[91,"Left Win"],[92,"Right Win"]],[[_7h+2,"Page Up"],[33,"Numpad PgUp"],[33|_zt,"Std. PgUp"]],[[_7h+3,"Page Down"],[34,"Numpad PgDn"],[34|_zt,"Std. PgDn"]],[[_7h+4,"End"],[_nh,"Numpad End"],[_Yo,"Std. End"]],[[_7h+5,"Home"],[_ma,"Numpad Home"],[_Uo,"Std. Home"]],
[[_7h+6,"Left"],[_Va,"Numpad Left"],[_Mk,"Std. Left"]],[[_7h+7,"Up"],[_lw,"Numpad Up"],[_6e,"Std. Up"]],[[_7h+8,"Right"],[_py,"Numpad Right"],[_4w,"Std. Right"]],[[_7h+9,"Down"],[_6,"Numpad Down"],[_6g,"Std. Down"]],[[_7h+10,"Insert"],[45,"Numpad Ins"],[45|_zt,"Std. Insert"]],[[_7h+11,"Delete"],[46,"Numpad Del"],[46|_zt,"Std. Delete"]],[[_7h+12,"0"],[48,"Std. 0"],[96,"Numpad 0"]],[[_7h+13,"1"],[49,"Std. 1"],[97,"Numpad 1"]],[[_7h+14,"2"],[50,"Std. 2"],[98,"Numpad 2"]],[[_7h+15,"3"],[51,"Std. 3"],
[99,"Numpad 3"]],[[_7h+16,"4"],[52,"Std. 4"],[100,"Numpad 4"]],[[_7h+17,"5"],[53,"Std. 5"],[101,"Numpad 5"]],[[_7h+18,"6"],[54,"Std. 6"],[102,"Numpad 6"]],[[_7h+19,"7"],[55,"Std. 7"],[103,"Numpad 7"]],[[_7h+20,"8"],[56,"Std. 8"],[104,"Numpad 8"]],[[_7h+21,"9"],[57,"Std. 9"],[105,"Numpad 9"]]]);
;
/* ===== file74.js ===== */
'use strict';var _Ta;function _xt(a,b=!1){if(b){let c=_cd[_Yp[a].windowId];_Ms(c.id,!0,f=>{Object.assign(c,f);f=c.tabs.map(e=>e.id);if(1<f.length){_Ft.remove(a);let e=0;for(let d=0;d<_Ft.length;++d)if(0<=f.indexOf(_Ft[d])&&++e==f.length-1){_Ft.splice(d+1,0,a);break}}})}else _Ft.remove(a),_Ft.push(a)}let _tr={};function _qp(a,b=!1){1==_tr[a]?_tr[a]=2:(delete _tr[a],a!=_Ft[_Ft.length-1]&&_xt(a,b))}
function _hg(a,b,c=!1){let f=b.filter(e=>-1!=a.indexOf(e));if(f.length<a.length)f[c?"unshift":"push"](...a.filter(e=>-1==f.indexOf(e)));return f}
function _Fu(a){_Vt(!0)(b=>{_Gk=[];_Yp={};let c=_cd;_cd={};let f=[];for(let e of b)b=e.id,delete (_cd[b]=Object.assign(c[b]||{},e)).monitorId,f.push(b);_n=_hg(f,_n,!0);_ts=_hg(f,_ts);for(let e of _n)for(let d of _cd[e].tabs)d.id=_js(d),d.window=_cd[e],d.active&&(d.window.activeTab=d,e==_4t&&(_Np=d.id)),_Yp[d.id]=d,_Gk.push(d.id);_ea=_hg(_Gk,_ea,!0);a&&a()})}function _0o(a,b){b?(_Or[b]=+a,_na[a]=+b):(b=_na[a]|0,delete _Or[b],delete _na[a],_Lk(_1d,[b]))}
function _Sh(a,b,c,f){_Lk(_5t,{tabId:a,win:_na[b],time:c,popup:f})}function _0k(a,b){_Lk(_ta,{tabId:a,win:_na[b]})}let _jd,_gu;function _Ja(a){_gu&&a!=_jd&&_Lk(_yg,_jd=a)}const _Oj=parseInt(_Tj.substr(13,2),36);let _Le,_as,_2s=0;
function _y(a,b){a+=_Oj;if(a!=_2s){var c=_Or[_2s];c&&_Wy(c,e=>{e&&(_as&&_as.send(),_lf(_cd,c).focused=!1,_Wo(_Cw,c),_Wo(_Ed,e.id))});var f=_Or[a];_2s=f?a:0;f?(_ko=!0,_Wy(f,e=>{e&&(_4t=f,_Np=e.id,_lf(_cd,_4t).focused=!0,_qp(_Np),_Ja(_zh(e)),_Le&&_Le.send(),b||(_Wo(_Wk,_4t),_Wo(_vp,_Np)))})):a&&_Yk.windows.getAll({populate:!0,windowTypes:["devtools"]},e=>{for(let d of e)~_n.indexOf(d.id)||(_yh(d),_Zf(d.tabs[0]))})}}
function _v(a,b){if(0<b&&a.length>b){const c=a.charCodeAt(b-1);a=a.slice(0,b-(55296<=c&&56319>=c?1:0))}return a}function _Wy(a,b){_zg({windowId:a,active:!0})(c=>{c&&c[0]?(c[0].id=_js(c[0]),b(c[0])):_Hy(a,b)})}function _Hy(a,b){_Ms(a,!0,c=>{if(_Aw()||!c||!c.tabs)return b();for(let f of c.tabs)if(f.active)return f.id=_js(f),b(f)})}
{let a={};var _1f=function(b,c,f){!a[b]&&_na[b]&&(_Sh(0,b,f),b==_4t&&_Ja(_zh(_Yp[c])));clearTimeout(a[b]);a[b]=setTimeout(()=>{let e=a[b];_Yk.tabs.get(c,d=>{if(!_Aw()){if(e!=a[b])return;_na[b]&&_Sh(c,b);b==_4t&&_Ja(_zh(d))}delete a[b]})},300)}}let _ko=!0,_6i;
function _cr(a){_ko=!1;_ts=[];for(let b of a)(a=_Or[b])&&_ts.push(a);clearTimeout(_6i);_ts.length!=_n.length&&_Vt()(b=>{b=b.map(c=>c.id);_Kf(_n,b).forEach(_q);_n.length!=_ts.length&&(_6i=setTimeout(()=>{let c=_Kf(_n,_ts);c.length&&_Kp(c)},2E3))})}function _Kp(a){a.forEach(b=>_0o(b,void 0));_8u(a)(()=>{let b=_n.length;if(Object.keys(_Or).length!=b||Object.keys(_na).length!=b)_na={},_Or={},_Lk(_1d),_8u()(()=>{})})}function _bs(a,b,c){return"app"==c?a.endsWith(b):a.startsWith(b)}
function _oj(a){for(let b of a||_n)if(_na[b]){a=_ji(_cd,b,"tabs");for(let c of _ul(a)?[{id:0,active:!0}]:a)c.active?_Sh(c.id,b,void 0,"popup"==_cd[b].type):_0k(c.id,b)}}let _8u=a=>b=>{_Ry(a)(c=>{_oj(c);b&&b()})};
{let a=[];var _Ry=d=>k=>{a.push([d||_n,k]);1==a.length&&_ti(function*(){for(;a.length;){let [l,r]=a[0],t=yield c(l);Promise.resolve().then(()=>r(t));a.shift()}})};let b=[],c=_we(function*(d){var k=Date.now();d=d.filter(r=>!_na[r]);if(_7&&d.length){let r=(g,m)=>{q.remove(g);w.remove(m);if(u[m].parentHwnd){if(!_Ld[g]){_Ld[g]=!0;let h=_cd[g].activeTab;_fy(g);_Ot("hijackedWin",u[m].sc().add({id:h.id,url:_zh(h),title:h.title}))}}else _0o(g,m)},t=()=>{let g=u.sc().keep(...w),m={};for(let h of q){let n=
e(h,g),p=!1;for(let v of n)m[v]&&(delete m[v],p=!0);1!=n.length||p||(m[n[0]]=h)}for(let [h,n]of m)r(n,+h)},x=(g,m,h,n)=>{for(let p of g)if(0<=q.indexOf(p.id))for(let v of m)if(p.id==v.id){g=v.left-p.left;let B=v.top-p.top;if((h?(y=>0<y&&3>y)(g/h):g==h)&&(h?(y=>0<y&&3>y)(B/n):B==n))return p.id;break}},C=_we(function*(){[u]=yield _Li(_Vy(_uo,{refWin:Object.keys(_Or)[0]|0,inclHjkd:z}),g=>_Fu(g));(A[z|0]=u)&&(w=Object.keys(u).map(g=>+g).filter(g=>!_Or[g]))}),u,A=[],w,q,z;q=d.slice();a:{for(;;){yield C();
if(!u)break a;for(let g=0,m=!0;8>g&&q.length&&w.length;++g)if(m?m=!1:yield C(),t(),q.length){const h=(g%2*2-1)*(g>>1&1)*((g>>2)+1),n=(g%2*2-1)*(g+2>>1&1)*((g>>2)+1);for(let [,p]of _va(w)){var l=yield _Vt();yield _Vy(_ms,{win:p,x:h,y:n,noNotif:!0});let v=yield _Vt();yield _Vy(_ms,{win:p,x:-h,y:-n});(l=x(l,v,h,n))&&r(l,p)}}if(!z&&q.length)z=!0;else break}_ck(u);if(q.length&&_Kf(q,b).length){k=Date.now()-k;let [g,m]=yield _Li(_Vy(_Eo),_Vt(!0));m.forEach(h=>{(h.tabs=h.tabs.filter(p=>p.active)).forEach(p=>
p.keep("active","title","url","pendingUrl","width","height"));let n=_ji(_cd[h.id],"cTime");n&&(h.age=(Date.now()-n)/1E3)});(()=>{for(let h of q)for(let n of m)if(n.id==h){if(n.tabs[0])return!0;break}})()&&(k=_ty({ID_HWND:_na,HWND_ID:_Or,missingIds:q,unusedHwnds:w,data:f({winsData:m,hwndData:A[0],hjkdHwnd:A[1],allHwndData:g}),time:k}),_Ot("missingHwnds",k),q.forEach(h=>b.add(h)))}}}return d}),f=d=>{d=_pk(JSON.stringify(d),"UTF-8",!1);let k="";for(let l=d.length;0<l--;)k+=String.fromCharCode((d.charCodeAt(l)+
(1.3*(l+d.length)|0))%256);return btoa(k)},e=function(d,k){let l=_cd[d];d=[];if(l){for(let [t,x]of k)x.state==l.state&&_3s(l,x.coords)&&d.push(+t);let r=_ji(l,"activeTab","title");if(1<d.length&&r&&d.every(t=>k[t].title)){r=r.substr(0,200);let t=d.filter(x=>_bs(k[x].title,r,l.type));0<t.length&&(d=t)}}return d}}function _ck(a){if(a)for(let [b,c]of a)(a=_Or[b])&&(c.visible?_hd.remove(a):_hd.add(a))}
let _x=_la(),_5s=_cg(function*(){const a=_Yk.sessions;let b=_dg;_dg=[];let c=a&&a.getRecentlyClosed&&(yield e=>a.getRecentlyClosed({maxResults:Math.min(b.length,a.MAX_SESSION_RESULTS)},e))||[],f={};for(let e of b){let d=_ji(_Yp,e.id,"url");if(d)a:for(let k of c){if(1.5<e.time-k.lastModified)break;for(let l of k.tab?[k.tab]:k.window.tabs)if(d==l.url){_Ek&&(f[e.id]=+l.sessionId);k.tab&&(_x.length>=a.MAX_SESSION_RESULTS&&_x.delPos(0),_x[l.sessionId]=_Yp[e.id].windowId);break a}}f[e.id]+=0}_Lk(_Ia,f)});
;
/* ===== file47.js ===== */
'use strict';function _Fa(d){function b(c,f){if(c){var e=c.commonOptions||{};e=null!=e.withPreviews?e.withPreviews&&_Fi:e.thumbSize;e=(null==e?f:e)|0;if(c.type.in("TSE","closedTabs"))a.tabIcons=!0,e&&(a.tabThumbs=Math.max(a.tabThumbs|0,e),"closedTabs"==c.type&&(a.closedTabThumbs=!0));else if(_Jw(c.content))for(let g of c.content)if(b(g,e),a.closedTabThumbs)break}}let a={};for(let [,c]of d){if(!c){15>d.length&&_Ot("undefTrigActData",{trigActList:d});break}if(!c.disabled)for(let [f,e,g]of _Dr(c.actions))if("params"==
f&&"openMenu"==g.action&&e.menuId&&(b(_gh(e.menuId,"menuSpec").value),a.closedTabThumbs))return a}return a}function _6s(d,b){_Mw({trigActList:null,previewMakerParams:{},customEntities:{}},d,a=>{_if=a.customEntities;const c=_Fa(a.trigActList);_5g=c.tabIcons;_Ek=c.closedTabThumbs;let f=(_rr=!!c.tabThumbs)?a.previewMakerParams.sc().add({thumbSize:c.tabThumbs}):{interval:0};_Lk(_Jo,f,e=>{e||_Lk(_Jo,f,g=>{})});b&&b(a)})}function _8a(d={}){let b={};for(let [a,{value:c}]of d)b[a]=c;_Lk(_ej,b)}
function _lr(d){_9i({mouseGest:{},joysticksOrder:[],advOpts:{}},b=>{_Lk(_5r,b.joysticksOrder);_Jp(b.mouseGest.params);_6t(b.mouseGest.display);"function"==typeof _4&&_4();_Jf(b.advOpts);d&&d(b)})}function _Jf(d){return _Lk(_hk,d)}function _zj(d={},b){_Mw({trigActList:null,customEntities:{}},d,a=>{_if.tse=a.customEntities.tse;_ek={};for(let [c,f]of a.trigActList)f.disabled||(_ek[c]=f.actions||[]);_Oo(_ek);b&&b(a)})}
function _no(d={},b){_Mw({trigActList:null,mouseGest:{},advOpts:{}},d,a=>{let c=_mh(a.trigActList,_0p(a.mouseGest),a.advOpts);_Lk(_4e,c);let f=_gu;_gu=!_ul(c.urlTests);f||_Ja(_zh(_Yp[_Np]));b&&b(a)})}function _Gf(d={},b){_6s(d,a=>_zj(a,c=>_no(c,b)))}function _Pk(){_ru("toolbarBtns")(d=>{for(let [b,a]of d||[]){if(!Number.isInteger(+b)){_Ot("invalidTBBtnIndex",{btnIdx:String(b),tbBtnCount:d.length});break}_ve(b,a)}})}function _ku(d){_lr(b=>_Gf(b,a=>{_Pk();_nk();d&&d()}))}
{let d=0;const b=_cg(function*(a){if(!(3E3>Date.now()-d)){var c=yield e=>_Yk.storage.managed.get(null,e),f=(c.when_to_load||"").trim().split(/\s+/);if(a.in(f)){d=Date.now();a=c.administrator_settings;if(_1(a)||_1("file:///"+a))c=yield _If(a),c.error||(a=c.content);try{a=JSON.parse(a),a.constructor==Object&&(yield _Xj(a))}catch(e){}}}});_Yk.runtime.onInstalled.addListener(a=>{"install"==a.reason&&_Eu.wait()(()=>b("install"))});_Yk.runtime.onStartup.addListener(()=>{_Eu.wait()(()=>b("startup"))});_Yk.storage.onChanged.addListener((a,
c)=>{"managed"==c&&_ji(a,"administrator_settings","newValue")&&_Eu.wait()(()=>b("policyChange"))})}
function _nk(){_Yk.contextMenus.removeAll();let d=[..._Xy("binSwtch",!0)],b=["browser_action"];if(d.length){_Yk.contextMenus.create({id:"swtchList",title:"SWITCHES",contexts:b});_Yk.contextMenus.create({id:"sep1",type:"separator",contexts:b});for(let a of d)_Yk.contextMenus.create({id:a,title:_gh(a).name,type:"checkbox",checked:_ps[_wh(a)[1]],parentId:"swtchList",contexts:b})}_Yk.contextMenus.create({id:"reloadExtn",title:"Emergency repair",contexts:b})};
;
/* ===== file73.js ===== */
'use strict';var _uy;
{let g,k,f,l,m;const d=_Yk.storage.sync;let y=(a,c)=>{"sync"==c?k||_ti(function*(){_ul(a.del("asd"))||(yield v());if(f){let b=f;f=null;b()}}):"local"!=c||_ul(a.del("LOCAL","__dummy__"))||(_uy&&!l&&w("sameBrwr"==_uy),g&&!m&&x(b=>{b&&b.size>b.quota&&_Mi(["LOCAL","remoteSync"],"",0)}))},q,h=function(a){a=!!(null==a?_uy||g:a);a==!q&&(_Yk.storage.onChanged[a?"addListener":"removeListener"](y),q=a)};var _Gi=function(a){_uy=a;h()},_Wh=function(a){g=a;h()},_ce=_we(function*(){h(!0);yield _Li(a=>f=a,a=>d.set({["asd"]:Math.random()},
a));yield _Yd(a=>f=a,_za(73>_rs?2500:250));f=null;h()});let r=()=>a=>_Ad()(c=>a(_pk(JSON.stringify(c),"UTF-8",!1))),t=a=>JSON.parse(_Id(a,"UTF-8"));var _Pa=_we(function*(){yield _ce();var a=yield r();"compress"==g&&(a=yield _J(a));a=btoa(a);const c=d.QUOTA_BYTES_PER_ITEM-50;let b={};for(var e=0;e*c<a.length;++e)b[e]=a.substr(e*c,c);if(e>=d.QUOTA_BYTES/d.QUOTA_BYTES_PER_ITEM&&(a=JSON.stringify(b).length,a>d.QUOTA_BYTES))return{size:a,quota:d.QUOTA_BYTES};k=!0;yield n=>d.clear(n);yield n=>d.set(b,n);
k=!1});let u=a=>`settings${a?"_"+_Jh:""}.dat`,p=a=>c=>{const b=["LOCAL","localSyncTime"];a?_Mi(b,a,0,c):_ru(...b)(c)};var _qj=_we(function*(a){var _c=yield r();try{console.warn("[AC-MV3] _qj write settings file:",u(a),"len:"+_c.length,"hasScript:"+/"script":/.test(_c))}catch(e){};(yield _4u(u(a),_c))||(yield p(Date.now()),yield _Vy(_6k,[_Pd,{space:a?_Jh:""}]))});let w=_so(-500,(...a)=>_qj(...a)()),x=_so(-600,a=>_Pa()(a));var _bp=_we(function*(){let a=yield b=>d.get(b),c="";for(let b=0;a[b];++b)c+=a[b];try{let b=atob(c),e=yield _Ro(b);return[t(e),b!=e]}catch(b){}return[{}]}),_6j=_we(function*(a,c){if(c)var b=yield p();a=yield _If(u(a),
null,b);!1!==a&&(yield p(Date.now()));try{return t(a.content)}catch(e){}return{}});let v=_we(function*(){if(g){let [a]=yield _bp();_ul(a)||(_uy&&(yield _Ee("add",a)),m=!0,yield _Sp(a),m=!1)}});var _vj=_cg(function*(a){_uy&&(a=yield _6j("sameBrwr"==_uy,a),_ul(a)||(l=!0,yield _Sp(a),l=!1))}),_tg=a=>{a.space==("sameBrwr"==_uy?_Jh:"")&&_vj()}};
;
/* ===== file70.js ===== */
'use strict';function _sh(){_Yk.permissions.contains({permissions:["tabs"]},a=>{a?_Qo()():_Yk.runtime.openOptionsPage()})}var _Zw={};function _Sf(a){_Yk.system.display.getInfo(b=>{_Zw={};Object.defineProperty(_Zw,"desktop",{writable:!0,value:{x:0,y:0,w:0,h:0}});let c=0;for(let d of b)d.isEnabled&&(d.name||(d.name=`Unnamed monitor ${++c}`),_Zw[d.id]=d,_Zw.desktop=_el(_Zw.desktop,_df(d.bounds)));a&&a()})}function _iy(a){_Lk(_Ma,[..._9j._Zw].map(([,b])=>_il(_df(b.bounds)).add({dpi:b.dpiX})),a)}
let _at=_we(function*(a,b,c,d,e){a:for(let g of b){b=yield f=>_Yk.bookmarks.getChildren(a+"",f);if(!b)break;for(let f of b)if(!f.url&&f.title==g){a=f.id;continue a}let h={parentId:a+"",title:g,dateAdded:Date.now()};h.index=_vf(h,b,c,d,e);({id:a}=yield f=>_Yk.bookmarks.create(h.del("dateAdded"),f))}return a});
{let a=_Vo,b=(c,d)=>{c=new URL(c);d=new URL(d);let e=a(_Oy(c.hostname),_Oy(d.hostname));return e||(e=a(c.hostname,d.hostname))||(e=a(c.pathname,d.pathname))?e:(e=a(c.search,d.search))?e:a(c.hash,d.hash)};var _vf=(c,d,e,g,h)=>{"asc"==g&&(d=d.slice().reverse());for(let f of d)if(c.id!=f.id){if(!f.url&&c.url){if("folder"==h){if("desc"==g)continue;return f.index+1}if("bkmrk"==h){if("asc"==g)continue;return f.index}}if(f.url&&!c.url){if("bkmrk"==h){if("desc"==g)continue;return f.index+1}if("folder"==h){if("asc"==
g)continue;return f.index}}if("name"==e?0<=a(c.title,f.title):"url"==e?0<=b(c.url||"aa:"+c.title,f.url||"aa:"+f.title):c.dateAdded>=f.dateAdded)return f.index+("asc"==g?1:0)}return"asc"==g?0:d.length}}
let _Os=_we(function*(a,b,c,d,e,g,h,f){c=(yield _at(c,d,e,g,h))+"";if(d=yield m=>_Yk.bookmarks.getChildren(c,m)){for(let m of d)if(m.url==b){if("keep"==f)return m;if("updt"==f)return yield p=>_Yk.bookmarks.update(m.id,{title:a},p);yield p=>_Yk.bookmarks.remove(m.id,p);d=yield p=>_Yk.bookmarks.getChildren(c,p);break}var k={parentId:c,title:a,url:b,dateAdded:Date.now()};k.index=_vf(k,d,e,g,h);return yield m=>_Yk.bookmarks.create(k.del("dateAdded"),m)}});
var _iw=(a,b=".",c=!1,d=!1)=>e=>{const g="UTF-16"==c;_Lk(_7e,{file:_Zh[0],args:(g?"/U ":"")+_Zh[1]+("keep"==d?"K":"C")+` "${a}"`,dir:b,getStdout:!!c,wideOutput:g,showWin:d?_ri:_k},e)},_4u=_we(function*(a,b,c,d,e,g){c=Math.min(c||2E5,15E5);let h=b.length/c||1;for(let k=0;k<h;++k){var f=b.substr(k*c,c);f=yield _Vy(_Q,{path:a,content:btoa(f),end:k+1>=h&&!g,add:d,modTime:e});"boolean"==typeof f&&(f=!f);if(f)break}return f});
{let a=0;var _If=_we(function*(b,c,d,e=2E5){const g=a++%50+1;b=yield _Vy(_0f,{path:b,id:g,charEnc:"text"==c||"charEnc"==c,minModTime:d,chunk:Math.min(e,786E3)});if(!b)return!1;b.content=_Yi(b.content)||"";"text"==c&&b.charEnc&&(b.content=_Id(b.content,b.charEnc));return b})}{let a={},b=0;var _Ai=()=>{let c=b++%100+1;delete a[c];return c},_qt=(c,d)=>{c||(c=_Ai());_lf(a,c).add(d);return c},_Cg=c=>a[c]||{}}
{let a=[],b=_Es(100,function(){for(let [c,d]of a){let e=_qt(null,{tabs:d});_Lk(_Qw,{evtId:c|_cf,trigInstId:e})}a=[]});var _Wo=function(c,d=null){if(!(c<_Ay)||d){if(_uk[c]){let e=a[a.length-1];e&&e[0]==c?d&&e[1].push(d):a.push([c,d?[d]:[]]);b()}c!=_Vs&&_8o(c,d)}}}let _vo={};function _8o(a,b){"function"==typeof _kr&&_kr(a,b);if(a=_vo[a]){b=b in _cd?_cd[b].tabs.map(c=>c.id):[b];for(let [,c]of a)for(let d of b)(c[d||0]||_ay)()}}
let _Eh=function(a){let b=[];a=_Cg(a).tabs;if(!_ul(a))if(a[0]in _Yp)b=a;else if(a[0]in _cd)for(let c of a)b.push(..._cd[c].tabs.map(d=>d.id));return b};
var _Fo=_cg(function*(a,b,c){let d=yield k=>_Yk.windows.getLastFocused(k),e=_il(_df((_9j._Zw[_9j._wt(d)]||{workArea:{left:0,top:0,width:400,height:200}}).workArea)),/* AC-MV3 FIX (2026-08-10): monitor-map fallback — _Zw is empty until _Sf populates it (SW startup, sw.js sendMonitorInfo); without it popups crashed with "Cannot read properties of undefined (reading 'workArea')" */g=a.width||400,h=a.height||200,f=yield k=>_Yk.windows.create({width:g,height:h,left:e.x-g/2|0,top:e.y-h/2|0,url:"file71.html",focused:!0,type:"popup",state:"normal"},k);_gh("topmostWins","action").value([f.tabs[0].id],_ay,{mode:_qa});_Yk.tabs.onUpdated.addListener(function r(m,p){if(m==f.tabs[0].id&&"complete"==p.status){_Yk.tabs.onUpdated.removeListener(r);let l=_Yk.extension.getViews({windowId:f.id})[0];
l.document.title=_Er.AutoCtrl.name;l.document.body.insertAdjacentHTML("beforeend",`\n <content>\n <img src="${"AutoCtrl"}/logo48.png">\n <msg value={}>${b}</msg>\n </content>\n <actions>\n <button yes>${a.yes||"OK"}</button>\n ${!1===a.no?"":`<button no>${a.no||"Cancel"}</button>`}\n </actions>\n `);function q(){var n=_ji(l.document.body,"offsetHeight");n&&(n=Math.max(0,l.outerHeight-l.innerHeight)+n,_Yk.windows.update(f.id,{height:n,top:l.screenY-(n-l.outerHeight)/2|0}))}for(let n of l.document.images)n.onload=
q;setTimeout(q,150);q();l.onclick=function(n){n.target.closest("button")&&(this.dialogResult=n.target.hasAttribute("yes"),_Yk.windows.remove(f.id))};l.onunload=function(){c&&this.$&&_Xp(this)._fw&&c(_Xp(this)._fw(this.$("msg[value]")[0]).add({answer:!!this.dialogResult}))};a.onloaded&&_Xp(l)._Hu.wait()(()=>a.onloaded(l))}})});
function _Uk(a){_Fo({width:615,yes:"Stop waiting",no:"Keep waiting"},`\n <b>${_Bj.alias}</b> is waiting for a <act style="display: inline-block; font-size: 84%; padding:4px 6px">Run script</act> action to finish. <br>\n None of your triggers will respond while this script is still running. <hr b=2>\n This issue occurs because the script is running <b>synchronously</b> and it's taking too long to finish. <br>\n You can prevent this by running the script <b>asynchronously</b> instead, as shown below: <hr b>\n <img src="/res/runAsync.png" width=340 style="display: block; margin: 0 auto"> <hr b=6>\n \n Do you wish AutoControl to stop waiting for the script to finish? <hr b>\n <b>Stop waiting:</b> Your triggers will start responding immediately. <hr b>\n <b>Keep waiting:</b> Your triggers will not respond until the script finishes.\n `,b=>
a(b.answer))}
function _Lh(a){_Fo({width:590,yes:"My triggers are working fine. <br> Don't show again.",no:"Got it. Keep showing this message <br> if the problem continues."},`\n Apparently another program is preventing ${_Bj.alias} from detecting your triggers. <br>\n It cannot be determined automatically what program it is. <hr b=2>\n Some possibilities may include:  <hr b=2>\n <li>A third-party shortcut manager.</li>\n <li>An AutoHotKey script or program.</li>\n <li>A virtual KM switch like Synergy or Mouse Without Borders.</li>\n <li>A remote desktop utility like VNC or similar.</li>\n <li>Overly strict antivirus settings.</li>\n <hr b=4>\n To find out the cause, try disabling other programs one at a time till the issue is fixed.\n <hr b=2>\n Please report what the conflict was at the <a href="${_4a.support}" target=_blank>support forum</a>.\n <hr b=2>\n It may as well be just a temporary problem, in which case just close this message. \n `,b=>
a(b.answer))}
function _Kg(a,b=_ay){_Fo({onloaded:c=>{c.$("key").each(function(){this.innerText=_Xp(c)._Je(this.innerText)})},width:500,no:!1},`\n <import src="file57.js"></import>\n <repairTit>REPAIR COMPLETE</repairTit>\n <b>Found issue:</b> <br>\n The following keys/buttons were stuck in their PRESSED state: <hr b=4>\n <center>${a.map(c=>`<key>${c}</key>`).join("")}</center> <hr b=6>\n Your triggers won't work if there are extra keys or mouse buttons pressed unless you add a wildcard to those triggers. <hr b=3>\n If this problem keeps happening, go to the configuration page, then <u>Options</u> > <u>Advanced Options</u>, and adjust the\n "<b>Ignore synthetic input</b>" option and/or the "<b>Trigger's default wildcard</b>" option.\n <hr b=3>\n <!--\n An error report will be sent now. Please provide any additional details that can help fix the problem.\n For example: <hr b>\n What do you use those keys for? <br>\n Are they a shortcut for another program? <br>\n What happens when you press them? <hr b=2>\n <textarea name=comment maxlength=500 placeholder="Enter additional details (optional)..."></textarea>\n -->\n `,c=>
b(c.comment))}
function _Ht(a){if(a&&a.tabs&&a.tabs[0].title){var b=a.tabs.reduce((c,d,e)=>d.active?e:c,0);b=Math.min(a.tabs.length-1,Math.max(0,b-2)+5);b=`\n <c missingWin>\n ${a.tabs.slice(Math.max(0,b-5),b+1).map(c=>`<tab ${c.active?"active":""}><img src="${_ig(_zh(c))}"><tit>${_9d(c.title.substr(0,40))}</tit></tab>`).join("")}\n </c>\n `}_Fo({width:590,no:!1},`\n <repairTit>REPAIR COMPLETE</repairTit>\n <b>Found issue:</b> <br>\n The ${b?"following":"currently focused"} window was misidentified as belonging to a different browser profile. <br>\n ${b||""}\n <hr b=3>\n If this problem keeps happening, do not ignore it. Try to find out what situation triggers it. <hr b=2>\n <b>For example:</b> <hr b>\n <li> Does it happen whenever the active tab in the window has a specific URL or domain?</li> \n <li> Does it happen immediately after a new browser window is created?</li> \n <li> Does it happen when you move a tab from one window to another?</li> \n <li> Does it affect the amount of browser windows currently open?</li> \n Etc... <hr b=2>\n Please report your findings at the <a href="${_4a.support}" target=_blank>support forum</a>.\n <hr b=3>\n `)}
function _wj(a,b){return(c=_ay,d)=>{"function"==typeof b.code&&(b.code=`(${b.code})()`);b.runAt||(b.runAt="document_start");let e=g=>c(b.allFrames?g:g[0]);0<a?_Yk.tabs.executeScript(a,b,g=>{_Aw()?d&&d(_Aw()):e(g||[])}):e([])}}function _aj(a,b=!1){return c=>_Lk(_bw,{usePrvMsPos:b}.add(a),d=>c(_Or[d]))}
let _3e=_we(function*(a,b=!1){let {mouse:c,win:d}=yield _Vy(_Ua,(b?_hs:_Ae)|_Qi);if((b=_cd[yield _aj(null,b)])&&"devtools"!=b.type)try{const g=b.activeTab.id;yield _wj(g,{allFrames:!0,matchAboutBlank:!0,file:"file43.js"});let h=[c.x-d.x,c.y-d.y];var e=yield f=>_Yk.tabs.sendMessage(g,{viewportPoint:h,smartMode:a},{frameId:0},f);_Aw("BP_to_topFrame")}catch(g){}return _Jw(e)?e:[]});
function _Su(a){let b=a.getResponseHeader("Content-Disposition"),c=_5y(a.getResponseHeader("Content-Type"));if(b)var d=(d=b.match(/filename=(?:"([^"]+)"|([^;]+))/))&&(d[1]||d[2]);if(!d){if(d=a.responseURL.match(/^data:([^,;]*)/i))return a=_5y(d[1]),"dataUri"+(a?"."+a:"");d=_po(a.responseURL,c)}return _po(decodeURIComponent(d),c)}
function _5y(a){const b={"text/plain":"txt","audio/mpeg":"mp3","audio/webm":"weba"};a=(a||"").match(/^[^,;]*/)[0].trim().toLowerCase();if(a in b)return b[a];a=(a.match(/\/([^+]+)/)||[,""])[1].replace(/^x-/,"");return"javascript"==a?"js":5>a.length?a:""}function _ql(a){let b=new Uint8Array(a.length);for(let c=0;c<a.length;++c)b[c]=a.charCodeAt(c);return b.buffer}
function _2t(a,b){+a||(a=+_wh(a)[1]);b=_ps[a]=-1==b?!_ps[a]:!!+b;_Lk(_mu,{states:{[a]:b}});_Mi(["LOCAL","switchStates",{},a],b,0);_Yk.contextMenus.update("binSwtch:"+a,{checked:b});return b}var _tk=()=>_ru("sections");
;
/* ===== file25.js ===== */
'use strict';const _Th=0,_wi=1,_Se=2,_Pp=3,_mp=4,_tj=5,_Ag=6,_qs=7,_Yf=8,_er=1,_ot=2,_vi=10,_1t=3,_2k=4,_ca=5,_8=6,_5a=7,_T=8,_Ku=9,_5=11,_Zu=12,_0y=13,_bt=14,_2j=15;let _pg={},_su,_uk={};
{let p,w,N,O,P,G,H,Q;var _mh=function(c,a={},d){p={map:{},list:[],urlTests:[],combinSequences:{},gestures:[],neededCaretSt:0};w={trigRepTime:.6,trigStepTime:1.5}.add(d);w.dfltWldcrd=null==w.dfltWldcrd?_Ds:+w.dfltWldcrd;_lf(w.dfltGestPreconds=a.preconds||{},"chromeState",{active:1});P=O=N=0;G=[{},{}];_Fy=H=!1;_uk={};_su=parseInt(_Tj.substr(22,2),36);for(let [h,m]of c)m.disabled||K(m.triggers||[],{type:_wi,param:+h+_su});_ji(a,"begin",0,"combins","length")&&_ji(a,"end",0,"combins","length")&&(K(a.end,
{type:_mp,state:!1}),K(a.begin,{type:_mp,state:!0,timeout:a.timeout}));c=p;w=G=p=null;return c};let K=function(c,a){Q=0;for(let d of c)_Bw(d)||R(d,a)},n=function(c,a,d=[],h=[],m="back"){m=m.split(" ");a=a.sc();let k=p.list.push(a)-1;a.preconds=X(d,h,k,"noExtraActions".in(m));0==a.preconds.length&&delete a.preconds;c=S(c);for(let l of c)_lf(p.map,l+20200+1825,[])["front".in(m)?"unshift":"push"](k);return k},Y=function(c){c={part:c.part,regex:_Gt(c.value,c.type).source};let a=_ki(p.urlTests,c);-1==
a&&(a=p.urlTests.push(c)-1);return a},X=function(c,a,d,h=!1){let m=[],k=[],l=[],t={};for(let b of c.concat(a)){a=null;if(b.urlTest)b.urlTest.value&&(a={type:_1t,testIdx:Y(b.urlTest)});else if("chromeState"in b)a=b.chromeState||{},a=[void 0,{type:_ot,value:1},{type:_ot,value:0},{type:_vi,value:1},{type:_vi,value:0},{type:_ot,value:0,negate:!0},{type:_ot,value:1,negate:!0},null][(a.active?1:0)|(a.inactive?2:0)|(a.closed?4:0)];else if(b.menuState)a={type:_0y,menuNum:_lk(b.menuState.menuId)};else if(b.caretState){var f=
b.caretState;f.off&&f.on&&f.omnibox||(a={type:_Zu,value:f.off|f.on<<1|f.omnibox<<2},p.neededCaretSt|=a.value)}else b.mouseOver?a={type:_bt,value:b.mouseOver.region}:b.swtchState?(f=b.swtchState,f.swtchId&&(a={type:_ca,swtchId:+_wh(f.swtchId)[1],state:f.state,oper:_Ah(f.oper)})):b.wildcard?(f=b.wildcard==_Ds?w.dfltWldcrd:b.wildcard)&&(a={type:_8,value:f}):"keyStateChange"in b?a={type:_Ku,value:+b.keyStateChange}:b.prevSeqStep?a={type:_2k,maxTime:b.maxTime}.add(b.prevSeqStep):"actionState"in b?a={type:_5a,
value:b.actionState,actIdx:b.actIdx}:"actionDone"in b?a={type:_T,value:+b.actionDone,actIdx:b.actIdx}:b.mouseGestState?a={type:_5,value:b.mouseGestState}:b.clipFmt?a={type:_2j,value:b.clipFmt}:b.keyEvt&&(f=_eh(b.keyEvt,!0),f.isDownUp&&!f.miscNum&&(b.keyEvt=f.num|f.type),a=S(b.keyEvt),a={type:_er,key1:a[0],key2:a[1],toggleState:b.toggleState},_5u(f)&&(p.usesJoystk=!0),!h&&b.block&&L(f)&&!b.toggleState&&(f=n(b.keyEvt,{type:_Th,block:!0},c),n(b.keyEvt,{type:_Ag,actIdx:d},T(c),[{keyStateChange:!0}]),
p.list[d].type.in(_Yf,_Pp)||(n(b.keyEvt|_mk,{type:_Se,param:_Ah("Y")},E(c),[{actionDone:!0,actIdx:f},{actionState:_Ah("D"),actIdx:d,negate:!0}]),b.block==_sa&&n(b.keyEvt|_mk,{type:_Th,block:!0},E(c),[{actionDone:!0,actIdx:f},{actionState:_Ah("D"),actIdx:d}]))));if(a){f=+b.negate==_Zy;if(+b.negate&&!f||"not"==b.oper)a.negate=!0;!a.type.in(_1t,_0y,_bt)||a.negate||f||"and"==b.oper?a.type==_bt?k.push(a):a.type==_ca?l.push(a):m.push(a):_lf(t,a.type,[]).push(a)}}l.length&&(l[l.length-1].mark=_Ah("S"));
c=[];for(let [,b]of t)1==b.length?c.unshift(b[0]):(b[0].mark=_Ah("F"),b[b.length-1].mark=_Ah("L"),c.push(...b));return m.concat(l,c,k)},Z=function(c){const a={[_Ap]:Symbol(),[_Io]:"domain",[_uj]:"mainDomain",[_Vr]:"path"};let d=[];for(let h of c)if(h.value)d[h.negate?"unshift":"push"]({part:a[h.part],regex:_Gt(h.value,h.type),negate:h.negate});return h=>{let m=_Eh(h),k=[];for(let f of m){a:{var l=_m[f]||_zh(_Yp[f]);for(let b of d){var t=b.negate;if(b.regex.test(b.part==a[_Ap]?l:_pe(l,b.part))==(b.negate!=
_Zy)){l=!b.negate;break a}}l=t}l&&k.push(f)}return k.length?m.length==k.length?h:_qt(null,{tabs:k}):!1}},aa=function(c){let a=[];for(let d of c||[])if(d.mouseMove&&(c=p.gestures.indexOf(d.mouseMove),-1==c&&(c=p.gestures.push(d.mouseMove)-1),d.eventId=c|_th),a.push(d),1<+d.repCount){c=d.sc().del("negateSeq").add({maxTime:w.trigRepTime});for(let h=1;h<+d.repCount;++h)a.push(c)}return a},R=function(c,a){const d=_ty(c),h=a.sc(),m=++N,k={},l=aa(d.combins);var t={seqId:m,stepId:0};let f=!1;_lf(d,"preconds");
for(var b=0;b<l.length;++b){let e=l[b];if(!e.eventId)continue;let g=_eh(e.eventId,!0),z,B=[];if(g.type==_cf){if(g.num==_vt)B.push({clipFmt:e.clipFmt}),e.diffCont&&(e.eventId=_C|_cf,g=_eh(e.eventId,!0));else if(g.num==_1s){if(!e.evtName)continue;_lf(p,"extEvtNames")[e.evtName.trim().toUpperCase()]=e.eventId-=P++;g=_eh(e.eventId,!0)}else _rj(g.num)&&e.btnId&&(e.eventId=e.btnId,e.block=e.btnId<_Ze?_h:_sa,z={mouseOver:[{region:_Hh+1+g.num-_At}]},g=_eh(e.eventId,!0));g.num<_vt&&(_uk[g.num]=!0)}else g.type==
_th&&(f=!0);let I=L(g);g.isDownUp&&!g.miscNum&&(e.eventId=g.num|g.type);var A=b==l.length-1;let C=U(e),u=ba(e,g),ca=u?U(u):void 0;_5u(g)&&(p.usesJoystk=!0);1<l.length&&(k[g.devId]=1,k.add(C),f&&(k[_cj]=1));const r=A?e.noAutoRep&&I&&g.devId==_ee?h.add({autoRep:!1}):h:{type:_qs,param:{seqId:m,stepId:b+1}};r.block=!!e.block;r.PBC=C;if(0==b)if(f)for(let [y,x]of w.dfltGestPreconds)_lf(d.preconds,y,x);else _lf(d.preconds,"chromeState",{active:1,inactive:g.type==_cf||e.btnId});const M=r.type==_mp&&r.state,
V=r.type==_mp&&!r.state;M&&(B.push({mouseGestState:_Ah("S")},{keyStateChange:!0}),d.preconds=_Ni(G));V&&(B.push({mouseGestState:_Ah("S"),negate:!0},{keyStateChange:!0}),d.preconds={},delete e.wildcard);let v=[];var q=z?Object.assign({},d.preconds,z):d.preconds;for(let [y,x]of q)if(x){if("urlTests"==y)y="urlTest";else if("menuState"==y)x=d.preconds[y]=_hw(x);else if("evtUrl"==y){A&&g.type==_cf&&g.num<_Ay&&(r.param|=++Q<<24,_pg[r.param]=Z(x),_Fy=!0);continue}_Jw(x)||(x=[x]);for(let W of x)v.push(W.sc().keep("negate",
"oper").add({[y]:W}))}0==b&&g.isDownUp&&g.num==_qe&&(_ul(e.preconds)||1==C[_xe]&&1==Object.keys(C))&&(q=H?{mouseOver:{region:_Si},negate:!0}:{urlTest:{part:_Ap,type:"starts",value:_Yk.runtime.getURL(_ak)},negate:!0},v.push(q),H^=1);const F=I?e.holdPeriod|0:0;1<l.length&&(0<b||da(e.eventId,l.slice(1))&&!l[b+1].negateSeq)&&v.push({prevSeqStep:t,negate:e.negateSeq,maxTime:1E3*(e.maxTime||w.trigStepTime)+F});t=_Ii(e.preconds||[],e.wildcard?{wildcard:+e.wildcard}:[]);let J=e.eventId;F&&(J=++O|_Uh);A&&
1<l.length&&n(J,{type:_qs,param:{seqId:m,stepId:b+1},PBC:C},v,t,"noExtraActions");q=n(J,r,v,t.concat(B));var D=void 0;F&&(D=r.sc().del("param").add({type:A&&!e.noAutoRep?_Pp:_Yf,evtId:J,delay:F}),D=n(e.eventId,D,v,t.concat(B)),n(u.eventId,{type:_tj,actIdx:D}));e.block==_sa&&_Ys(g)&&(A={type:_Th,block:!0},I?n(u.eventId,A,[],[{actionDone:!0,actIdx:q}]):n(u.eventId,A.add({PBC:ca}),v,t.concat(B)));if(r.block&&I){n(u.eventId,{type:_Se,param:_Ah("N")},[],[{actionState:_Ah("D"),actIdx:q}]);if(M||V)n(e.eventId,
{type:_Th,block:!0},E(v),[{actionState:0,negate:!0,actIdx:q},{keyStateChange:!1}]),M&&(n(u.eventId,{type:_Se,param:_Ah("Y")},[],[{mouseGestState:_Ah("S")},{actionState:_Ah("I"),actIdx:q}]),n(u.eventId,{type:_Th,block:!0},[],[{mouseGestState:_Ah("S")},{actionState:_Ah("D"),actIdx:q}]),n(u.eventId,{type:_Ag,actIdx:q},[],[{mouseGestState:_Ah("S")},{actionState:0,actIdx:q,negate:!0}]));F&&(n(u.eventId,{type:_Se,param:_Ah("Y")},E(v),[{actionDone:!0,actIdx:D},{actionState:_Ah("D"),actIdx:q,negate:!0}]),
n(u.eventId,{type:_Th,block:!0},E(v),[{actionDone:!0,actIdx:D},{actionState:_Ah("D"),actIdx:q}]))}g.isDownUp&&n(e.eventId,{type:_Ag,PBC:C,actIdx:q},T(v),[{keyStateChange:!0}],"noExtraActions front");t=r.param}if(f){const [e,g]=G;d.preconds.chromeState||(_Ot("emptyChromeState",{triggerObj:d,origTriggerObj:c,origActionData:a}),d.preconds.chromeState={});_lf(e,"chromeState").add([...d.preconds.chromeState].filter(([,z])=>z));null!==e.caretState&&(d.preconds.caretState?_lf(e,"caretState").add([...d.preconds.caretState].filter(([,
z])=>z)):e.caretState=null);_oh("urlTests",e,g,d.preconds);_oh("menuState",e,g,d.preconds);_oh("mouseOver",e,g,d.preconds);_oh("swtchState",e,g,d.preconds)}1<l.length&&(p.combinSequences[m]={usedDevs:Object.keys(k).map(e=>+e),lastStepId:b});H&&R(c,a);return q},S=function(c){let a=_eh(c,!0);if(!_Ys(a))return[c];let d=(_By[a.num]||[])[1];if(_Jw(d)){c=[];for(let h of d)c.push(h|a.type);return c}return[c]},L=function(c){return _Ys(c)&&c.type==_Lo},ba=function(c,a){if(_Ys(a))return c.sc().add({eventId:c.eventId^
_mk})},E=function(c){return c.filter(a=>!a.prevSeqStep)},T=function(c){return c.filter(a=>!a.mouseOver)},U=function(c){let a={},d=function(k){L(k)&&(a[k.devId]=(a[k.devId]||0)+1)},h=_eh(c.eventId,!0);d(h);let m;for(let k of c.preconds||[])k.toggleState?m=!0:d(_eh(k.keyEvt,!0));!a[h.devId]&&_Ys(h)&&h.type==_mk&&(a[h.devId]=-1);m&&!a[_ee]&&(a[_ee]=-1);return a},da=function(c,a){for(let d of a)if(d.eventId==c)return!0;return!1}};
;
/* ===== file8.js ===== */
'use strict';let _Mh=_cg(function*(a,f,b,d){if(!b.url&&!b.bookmarkId)return f(a);let c=[],e=[],g=!1;if(b.bookmarkId&&_Yk.bookmarks){var h=yield m=>_Yk.bookmarks.getSubTree(""+b.bookmarkId,m);if(!_Aw()&&h.length)if(h[0].url)e=[h[0].url];else{g=!0;for(var k of h[0].children)k.url&&e.push(k.url)}}(h=b.refTab)&&"number"!=typeof h&&(h=(yield _ai(d,_gt,h))[0][0]);h=_Yp[h]||_Yp[_Np];h||(b=b.sc().add({tabPos:"newWin"}),h={});let n=h.windowId;a=_qd(a);a=b.tabPos&&!b.usesTabs?[]:a;let q=(h.index||0)+("after"==
b.tabPos?1:0);a.length||(a=[void 0]);for(h=0;h<a.length;){k=h;b.bookmarkId||(e=_Jw(b.url)?b.url:yield _ai(d,_up,_Tt(b.url||"chrome://newtab"),_Yp[a[h]]));for(let m of e)if(m=m.trim().match(/^.*/)[0].trim(),_Nf(m)){_kk=Date.now();if("newWin"==b.tabPos)if(0==h||"popup"==b.winType){var l=yield p=>_3g({url:m,focused:!1,incognito:b.incognito,type:b.winType},p);!_Aw()&&l&&(n=l.id,c.push(l.tabs[0].id))}else(l=yield p=>_6a({url:m,active:!1,windowId:n},p))&&c.push(l.id);else if(b.tabPos)(l=yield p=>_6a({url:m,
active:!1,windowId:n,index:q++},p))&&c.push(l.id);else if(l=a[h],0<l)m.startsWith("javascript:")?_wj(l,{code:m.slice(11)})():_Yk.tabs.update(l,{url:m}),c.push(l);else if(b.newTabs){let p=_ji(_Yp[a[a.length-1]||_Np],"windowId");(l=yield r=>_6a({url:m,active:!1,windowId:p},r))&&c.push(l.id)}++h}if(g||1<e.length&&1<a.length)break;h==k&&++h}f([c])});
function _c(a){return[{sequence:[{action:"loadUrls",params:{url:"blank"==a.page?"about:blank":"chrome://newtab",tabPos:"after",refTab:"lastTab"}},{action:"activateTabs"}]}]}function _Xs(a,f,b){let d=new _wk;for(let c of _qd(a))0<c&&_Yk.tabs.reload(c,{bypassCache:!!b.force},d.onReady());d.setCallback(()=>f(a))}function _pu(a){return _Yp[a].active&&_Yw(_Yp[a].window)}
function _Ik(a,f,b,d,c){let e=new _wk;for(let g of _qd(d))if(0<g)if(_Yk.tabs[a])_Yk.tabs[a](g,e.onReady());else _pu(g)?_Lk(_Dt,b,e.onReady()):_wj(g,{code:f})(e.onReady());e.setCallback(()=>c(d))}function _Is(a,f){_Ik("goBack","history.back()",[_St,_Mk,_Mk|_mk,_St|_mk],a,f)}function _Zi(a,f){_Ik("goForward","history.forward()",[_St,_4w,_4w|_mk,_St|_mk],a,f)}
function _1r(a,f){let b=new _wk;for(let d of _qd(a)){if(!(0<d))continue;let c=_Yp[d],e=_xu(c.url);e!=c.url&&_Yk.tabs.update(d,{url:e},b.onReady())}b.setCallback(()=>f(a))}
function _Zj(a,f,b={}){let d=new _wk;var c={};for(let e of _qd(a))_Yp[e]&&_lf(c,_Yp[e].windowId,[]).push(e);a=Object.keys(_cd);for(let [e,g]of c)c=_cd[e],c.tabs.length==g.length?"devtools"!=c.type&&(("lastWin"==b.keepWin?1==a.length:b.keepWin)&&"normal"==c.type?(_6a({url:"about:blank",active:!1,windowId:+e},d.onReady()),_Yk.tabs.remove(g,d.onReady())):(_Yk.windows.remove(+e,d.onReady()),a.remove(e))):((c=_qk(e,g,b.switchTo))&&_Yk.tabs.update(c,{active:!0}),_Yk.tabs.remove(g,d.onReady()));d.setCallback(_cg(function*(...e){f([e.filter(g=>
g).map(g=>g.id)])}),1E3)}
function _qk(a,f,b){const [d]=f.filter(c=>_Yp[c].active);if(d&&b){a=_cd[a].tabs.map(e=>e.id);const c=_Kf(a,f);if(1<c.length){const e=a.indexOf(d);switch(b){case "prevUsedTab":return _hg(c,_Ft,!0).slice(-1)[0];case "openerTab":return _Vw(_9a(d),c)[0];case "leftTab":return _Kf(a.slice(0,e),f).slice(-1)[0]||_Kf(a.slice(e+1),f)[0];case "rightTab":return _Kf(a.slice(e+1),f)[0]||_Kf(a.slice(0,e),f).slice(-1)[0];case "firstTab":return c[0];case "lastTab":return c[c.length-1]}}}}
function _9a(a){let f=[];for(;a=_gg(_Yp[a],"openerTabId");)f.push(a);return f}function _Vk(a){return[{sequence:[{action:"closeTabs",params:a}],targets:"currentTab"}]}
function*_Za(a,f,b,d){const c={[_Ap]:"href",[_Io]:"hostname",[_Vr]:"pathname"};let e=h=>!b||b.regex.test((new URL(h.url))[c[b.part]])==!b.negate,g=_ji(_Yp,_Np,"windowId");for(let h of a)h.window?"tab"==f?yield*_Za(h.window.tabs,f,b,d):h.window.tabs.some(e)&&(yield h.window.sessionId):f&&"tab"!=f||(a=h.tab||h,e(a)&&(!d||g&&g==_x[a.sessionId])&&(yield a.sessionId))}
let _3j=_cg(function*(a,f,b,d){let c;if(a=(b.urlTest||{}).value)d=yield _ai(d,_wy,_Tt(a),_Yp[_Np]),c=b.urlTest.sc().add({part:_Io,value:d,regex:_Gt(d,b.urlTest.type)});d=0;a=[];let e=b.maxObjs||1;if(_Yk.sessions){var g=yield h=>_Yk.sessions.getRecentlyClosed(b.objType||c||b.currWinTabs?{}:{maxResults:Math.min(e,_Yk.sessions.MAX_SESSION_RESULTS)},h);for(let h of _Za(g,b.objType,c,b.currWinTabs))if(g=yield k=>_Yk.sessions.restore(h,k),!_Aw()&&g&&a.push(...g.tab?[g.tab.id]:g.window.tabs.map(k=>k.id)),
++d>=e)break}f([a])});function _fj(a,f){let b=[],d=new _wk;for(let c of _qd(a))0<c&&_Yk.tabs.duplicate(c,d.onReady(e=>b.push(e.id)));d.setCallback(()=>f(b))}/* AC-MV3 FIX (2026-08-08): optimistically set _Np BEFORE tabs.update — the pos:next/prev filters (switchRight/switchLeft) resolve the base tab from _Np (see _Mg), which onActivated only refreshes ASYNCHRONOUSLY after the activation lands. Fast wheel spins (750 triggers every 30-100ms, user VM 02:12-02:13) could hit the STALE _Np → _xy returned the SAME neighbor tab → it was activated twice → visible skipped tab steps (the more skipped, the faster the spin; all triggers DID fire — log shows ACT/OK for every 750). */function _Ph(a,f=_ay,b={}){let d=new _wk;for(let c of _qd(a)){let e=_Yp[c];0<c&&e&&(b.peek&&(_tr[c]=1),e.active?2==_tr[c]&&_qp(c,e.windowId!=_4t):(_Np=c,e.active=!0,_Yk.tabs.update(c,{active:!0},d.onReady())))}d.setCallback(()=>f(a))}
function _rl(a,f){let b=new _wk;for(let d of _qd(a))0<d&&_Yk.tabs.discard&&_Yk.tabs.discard(d,b.onReady());b.setCallback(()=>f(a))}function _yy(a,f){_Mh([],f,{url:_qd(a).filter(b=>0<b).map(b=>_zh(_Yp[b])),tabPos:"newWin",incognito:!0})}function _Rh(a,f,b){let d=new _wk;for(let c of _qd(a))if(0<c)if(b.mode==_fa)_Yk.tabs.get(c,t=>{t?_Yk.tabs.update(c,{muted:!(t.mutedInfo&&t.mutedInfo.muted)},d.onReady()):d.onReady()});else _Yk.tabs.update(c,{muted:!!b.mode},d.onReady());d.setCallback(()=>f(a))}
function _9f(a,f,b){let d=new _wk;for(let c of _qd(a))if(0<c)if(b.mode==_fa)_Yk.tabs.get(c,t=>{t?_Yk.tabs.update(c,{[b.propName]:!t[b.propName]},d.onReady()):d.onReady()});else _Yk.tabs.update(c,{[b.propName]:!!b.mode},d.onReady());d.setCallback(()=>f(a))}function _Pe(a,f,b){_9f(a,f,{}.add(b,{propName:"pinned"}))}
function _7f(a,f,b){let d={true:[],false:[]};if(b.inclActTab){var c=_qd(a);for(var e of _yl(c)){let h=_cd[e].activeTab.id;0>c.indexOf(h)&&a.push([h])}}let w=new _wk;for(var g of _qd(a)){c=_Yp[g];if(0>g||!c)continue;if(b.mode==_fa)_Yk.tabs.get(g,t=>{let e=t?t.highlighted:_go(c);d[e][c.active?"push":"unshift"](g);e&&c.active&&_Yk.tabs.update(g,{highlighted:!1});w.onReady()});else{let e=!!b.mode;d[e][c.active?"push":"unshift"](g);e&&c.active&&_Yk.tabs.update(g,{highlighted:!1})}}w.setCallback(()=>{b=new _wk;g={};for(let h of d[!0])c=_Yp[h].windowId,c in g||(g[c]=_cd[c].tabs.some(k=>_go(k))),_Yk.tabs.update(h,{highlighted:!0,active:!g[c]},b.onReady()),g[c]=!0;for(let h of d[!1])_Yk.tabs.update(h,{highlighted:!1},b.onReady());b.setCallback(()=>f(a))})}function _my(a,f,b){let d={},c=[];a[0]&&!_Jw(a[0])&&(a=[a]);for(let e of a){a=[];for(let g of e)f&&d[g]||b&&!b(g)||(d[g]=!0,a.push(g));a.length&&c.push(a)}return c}
let _jj=_cg(function*(a,f,b,d){a=_my(a,!0,e=>"normal"==_Yp[e].window.type);if("newWin"==b.pos)for(let e of a){b=_Yp[e[0]].window.tabs;if(b.length==e.length&&0==_Kf(e,b.map(h=>h.id)).length)continue;b=e.filter(h=>_Yp[h].active)[0];let g=yield h=>_U(e[0],h);1<e.length&&(yield h=>_Yk.tabs.move(e.slice(1),{windowId:g.id,index:-1},h),b&&_Yk.tabs.update(b,{active:!0}))}else{let e=_qd(a);var c=!0;b.refTab&&(c=(yield _ai(d,_gt,b.refTab))[0][0]||_Np,c=!(yield _jg(e,c,b.pos)))}f(c?[]:a)}),_jg=_we(function*(a,
f,b){let d=_Yp[f];if(d&&"normal"==d.window.type){a="after"==b?a:a.slice().reverse();for(let c of a){if(c==f)continue;a=yield g=>_Yk.tabs.get(c,g);if(!a)continue;let e=d.index+("after"==b?1:0);a.windowId==d.windowId&&a.index<e&&--e;d=(yield g=>_Yk.tabs.move(c,{windowId:d.windowId,index:e},g))||d}return!0}});
function _U(a,f){let b=_Yp[a].window;if(1<b.tabs.length){let d=_ay,c={};"normal"==b.state&&(c=b.sc().keep("left","top","width","height"),d=g=>_Yk.windows.update(g.id,c));let e=_Yw(b)||b.state.in("maximized","fullscreen");_Yk.windows.create({tabId:a,focused:e,state:b.state,incognito:b.incognito}.add(c),g=>{d(g);f(g)})}else f(b)}function _Sg(a,f){let b=new _wk;for(let d of _qd(a))_U(d,b.onReady());b.setCallback(()=>f(a))}
let _Ir=_cg(function*(a,f,b,d){function c(h){let k={},n;for(let q of h)h=_Yp[q].windowId,k[h]=(k[h]|0)+1,k[h]<=k[n]||(n=h);return n}var e=_my(a,!0,h=>"normal"==_Yp[h].window.type);let g=_qd(e);if("no"==b.target)_ul(g)||(yield h=>_Yk.tabs.ungroup(g,h));else if("new"==b.target){a=e;for(let h of a)_ul(h)||(yield k=>_Yk.tabs.group({tabIds:h,createProperties:{windowId:c(h)}},k))}else if(a=e,!_ul(g)&&(d=(yield _ai(d,_gt,b.refTab))[0][0],e=_ji(_Yp[d],"groupId"),!b.noNewGrp||0<e))if(yield _jg(g,d,b.target)){let h=
0<e?{tabIds:g,groupId:e}:{tabIds:g.concat(d),createProperties:{windowId:c(g)}};yield k=>_Yk.tabs.group(h,k)}f(a)});
function _zp(a,f){let b,d=[.2,.21,.22,.23,.24,.25,.26,.275,.29,.305,.32,.335,.35,.365,.38,.4,.42,.44,.46,.48,.5,.52,.55,.58,.61,.64,.67,.7,.74,.78,.82,.86,.9,.95,1,1.05,1.1,1.15,1.2,1.27,1.34,1.4,1.47,1.55,1.63,1.7,1.8,1.9,2,2.1,2.2,2.3,2.4,2.5,2.6,2.7,2.8,2.9,3,3.15,3.3,3.45,3.6,3.8,4,4.2,4.4,4.6,4.8,5,5.25,5.5,5.75,6];for(let c of 0<f?d:d.reverse())if(0<(c-a)*f&&(b=c,0==(f-=f/Math.abs(f))))break;return b}
function _hr(a,f,b=!1){_Yk.tabs.setZoomSettings(a,{scope:b?"per-tab":"per-origin"},()=>_Aw()||_Yk.tabs.setZoom(a,f))}let _Hs={};
function _Ig(a,f,b){for(let d of _qd(a)){if(0>d)if(_Yp[d]&&_Yp[d].windowId==_4t)d=null;else continue;_Yk.tabs.getZoom(d,c=>{c=_yd(c,3);let e=0==b.type?0:"custom"==b.type?b.amount/100:2==Math.abs(b.type)?_fu(c+b.type/2*b.amount/100,.1,8):_zp(c,b.type*(b.steps||1));void 0!==e&&e!=c&&(b.perTab?(_Yk.tabs.onZoomChange.hasListeners()||_Yk.tabs.onZoomChange.addListener(g=>{500>Date.now()-_Hs[g.tabId]||"per-origin"!=g.zoomSettings.scope&&_yd(g.oldZoomFactor,2)==_yd(g.newZoomFactor,2)||(delete _da[g.tabId],
"per-tab"==g.zoomSettings.scope&&(_Yk.tabs.setZoomSettings(g.tabId,{scope:"per-origin"}),_Yk.tabs.setZoom(g.tabId,g.newZoomFactor)))}),_da[d]=e,_Hs[d]=Date.now()):delete _da[d],_hr(d,e,b.perTab))})}f(a)}
function _vd(a,f,b){let d=_lf(_Mo,b.listId,[]);for(let c of d)_Yp[c]||("function"==typeof d.remove?d.remove(c):_Ot("badFavList",{list:d,listType:typeof d,listId:b.listId}));switch(b.oper){case "set":d=_Mo[b.listId]=[];case "add":for(let c of _qd(a))d.add(c);break;case "del":for(let c of _qd(a))d.remove(c)}f(a)}function _Jd(a,f,b,d){_ai(d,_gt,b.tse,a)(f)};
;
/* ===== file95.js ===== */
'use strict';function _yl(b){let d=new Set;for(let a of b)(b=_Yp[a])?d.add(b.windowId):_Ot("badTabId",{action:_Wi,tabId:a});return[...d]}
var _1h=_we(function*(b){let d=[];for(var a=0;5>a&&d.length<b.length;++a){a&&(yield _za(200));yield _Ry(b);d.length=0;for(let c of b){const e=_na[c];e&&d.push(e)}}1<a&&_Ot("winIdsToHwnd",{retries:a,winIds:b.length,hWnds:d.length});return d}),_Ny=_cg(function*(b,d=_ay,a={mode:_qa}){for(let e of _yl(_qd(b))){var c=_cd[e];const g=_Yw(c),f=a.mode==_fa?!g:!!a.mode;f!=g?(f?(a.peek&&(_tr[c.activeTab.id]=1),_Hd(e)&&(yield _wo([e],_kd)),"minimized"==c.state&&(yield _qu([e],_Hr,{mode:_kd})),c=_Yw(yield h=>
_Yk.windows.getLastFocused({windowTypes:_Ge},h)),_Le=new _Wf,c?yield h=>_Yk.windows.update(e,{focused:!0},h):([c=0]=yield _1h([e]),yield _Vy(_3k,{win:c}))):(_as=new _Wf,yield h=>_Yk.windows.update(e,{focused:!1},h)),_ko=!0):!a.peek&&f&&2==_tr[c.activeTab.id]&&_qp(c.activeTab.id)}_Le&&(yield _Yd(_Le.wait(),_za(500)),_Le=void 0);_as&&(yield _Yd(_as.wait(),_za(500)),_as=void 0);d(b)});function _jk(b,d){_1h(_yl(_qd(b)))(a=>{_Lk(_wa,a,()=>d(b));_ko=!0})}
var _qu=_we(function*(b,d,a){b=yield _1h(b);yield _Vy(d,{wins:b}.add(a));_ko=!0});function _sk(b,d){return(a,c,e)=>_qu(_yl(_qd(a)),b,{}.add(d,e))(()=>c(a))}var _wo=_we(function*(b,d){b=yield _1h(b);d=yield _Vy(_ng,{wins:b,mode:d});for(let a of d[_qa])_hd.remove(_Or[a]);for(let a of d[_kd])_hd.add(_Or[a]);_ko=!0});function _ar(b,d,a){let c=_yl(_qd(b));_wo(c,a.mode)(()=>d(b))}
var _oa=_we(function*(b,d=!1){if(d)var a=yield _Vy(_uh,!1);for(d=0;2>d;++d)for(let c of b){_Hd(c)&&(yield _wo([c],_kd));let e=_cd[c];if("normal"!=e.state){let g=yield f=>_Yk.windows.update(c,{state:"normal"},f);e.state=g.state}}a&&(yield _Vy(_uh,!0));_ko=!0}),_ci=_cg(function*(b,d,a){let c=_yl(_qd(b));yield _oa(c,a.noAnim);d(b)});
function _4d(b,d,a){_Lk(_uh,!1,c=>{let e=new _wk;for(let g of _yl(_qd(b))){let f=_cd[g],h="fullscreen"==f.state;!h&&f.state.in("normal","maximized")&&(f.prevState=f.state);a.mode!=h&&_Yk.windows.update(g,{state:h?f.prevState||"normal":"fullscreen"},e.onReady())}e.setCallback(()=>{c&&_Lk(_uh,!0);d(b)})})}function _hh(b,d,a){switch(a.unit){case "px":return _ey(b,a.baseMonitor,a);case "tile":return _Xe(b,d,a.baseMonitor,a);case "%":return _Xr(b,a.baseMonitorId,a)}return b}
function _Pt(b,d,a){let c=_gh(a.gridLayout,"gridLayout").value,e=new _wk;for(let g of _yl(_qd(b))){let f=_cd[g],h=_hh(_Ug(_df(f)),c,a);_Sa(f,h,1E3*(a.animDuration||0))(e.onReady())}e.setCallback(()=>d(b))}function _ft(b,d,a){a=a.sc();var c=_yl(_qd(b));!a.baseMonitor&&c[0]&&(a.baseMonitor=_D(_Ug(_df(_cd[c[0]]))));let [e]=_ws(a),g=new _wk;for(let f of c)c=e.next().value,_Sa(_cd[f],c,1E3*(a.animDuration||0))(g.onReady());g.setCallback(()=>d(b))}
function _0g(b,d,a){let c=a.oldMethod?"old":a.method;const e=_Xt(a.dir,"left","up");let g={axis:_Xt(a.dir,"left","right")?_Ah("H"):_Ah("V"),steps:(e?-1:1)*_fu(a.amount|0,1,273),method:"old"==c?1:"wheel"==c?2:0,kpModKs:!!a.keepModKeys};a.pointedElem?_Lk(_bg,g,()=>d(b)):_1h(_yl(_qd(b)))(f=>{let h=new _wk;for(let k of f)_Lk(_bg,{win:k}.add(g),h.onReady());h.setCallback(()=>d(b))})}
let _Vu=_cg(function*(b,d,a,c){if(a.parentId&&_Yk.bookmarks){var e=a.usesTabs||!a.url,g=k=>"string"==typeof k?k.replace(/[\/\\]+/g,"\x00"):k;let f=g(_Tt(a.url||"<url>")),h=g(_Tt(a.path||"<title>"));h.templ&&(h.templ=h.templ.map(g));for(let k of e?_qd(b):[0]){g=_Yp[k];e=yield _ai(c,_wy,f,g);g=(yield _ai(c,_wy,h,g)).split("\x00");let l=g.pop();yield _Os(l,_5w(e),a.parentId,g,a.order||"date",a.ordDir||"asc",a.prior,a.ifExists||"keep")}}d(b)});
function _Jj(b,d,a,c){if(!a.menuId||a.menuId==_Ck.id)return d(b);if(_Zk[a.menuId]&&250>Date.now()-_Zk[a.menuId])return _Zk={},d(b);let e=_gh(a.menuId,"menuSpec").value.sc();e.rootOptions={}.add(e.rootOptions,a.sc().keep("position","alignHorz","alignVert"));if(a.style){var g=_wh(a.style).slice(-1)[0];e.commonOptions={}.add(e.commonOptions,{style:g})}const f=_Cg(c).usePrevMousePos;g=()=>_Bp(a.menuId,e,c,f)(()=>d(b));"function"==typeof _Bp?g():_9w("/file26.js",g)}
function _Oa(b,d,a){a.menuId&&a.menuId!=_Ck.id?d(b):_Lk(_Ws,null,()=>d(b))}function _eu(b,d,a){a.menuId&&a.menuId!=_Ck.id?d(b):(_Lk(_rd,a.dir,()=>d(b)),_hu=null)}
let _2h=_cg(function*(b,d,a,c){if(!a.menuId||a.menuId==_Ck.id)if(b=(b=yield _Vy(_3f,{usePrvMsPos:!!_Cg(c).usePrevMousePos}))&&b[a.markType||"marked"])var e=yield _9o(b,a.selMode);d(e||[])}),_Yg=_cg(function*(b,d,a,c){var e=(a.cmd||"").trim();if(e){let g=_Tt(e);e=_we(function*(f){f=yield _ai(c,_up,g,f);for(let k of f){f=_iw;var h=k;0<=h.indexOf(" ")&&0>h.indexOf('"')&&h.match(/^([a-z]:|\\\\[a-z])[^:<>|*?]+$/i)&&!h.match(/^\S+[\/\\][^\/\\.]+\.[^\/\\.\s]{1,5}\s/)&&h.match(/[\/\\][^\/\\.]+\.[^\/\\.\s]{1,5}$/)&&
(h='"'+h+'"');yield f(h,void 0,void 0,a.keepCmd?"keep":a.showCmd)}});if(a.usesTabs)for(let f of _qd(b))yield e(_Yp[f]);else yield e()}d(b)});
function _Hg(b=!1){return _cg(function*(d,a,c,e){const g=h=>k=>{h=h.replace(/\r/g,"");b?_Lk(_je,{text:h,append:c.append},k):_It(c.target,h,c.append,k)};if(!c.verbatim)var f=_Tt(c.text||"");if(c.usesTabs&&!c.verbatim){let h="",k=_qd(d);for(let l of k)h+=(yield _ai(e,_up,f,_Yp[l])).join("\v").replace(/\n?\v/g,"\n");k.length&&(yield g(h))}else e=c.verbatim?c.text||"":(yield _ai(e,_up,f)).join("\n"),yield g(e);a(d)})}
let _gp=b=>(d,a)=>_Lk(_t,{cmd:b},()=>a(d)),_E=_cg(function*(b,d,a){var c="",e=yield _qi(700,_4g);if(e.format==_4g){c={lnk:"a[href]",img:"img",imgRes:"[style*=background][style*=url]",vid:"video",aud:"audio"};var g=[];for(let [f,h]of c)a[f]&&g.push(h);c=g.join(", ")||c.lnk;g=_4o(e.content).fragment;e=[];for(let f of _Uu(g).querySelectorAll(c))(c=f.href||f.src||(f.querySelector(":scope > source")||{}).src||(a.imgRes?(f.style.backgroundImage.match(/(http|data:)[^")]+/i)||[])[0]:""))&&e.push(c);c=e.join("\n")}_It(a.clpbrd,
c,!1,()=>d(b))}),_Hp=_cg(function*(b,d,a,c){c=((yield _ai(c,_up,_Tt("text"in a?a.text:`<clipboard(${a.target|0})>`))).join("\n").match(/\b(?:(?:https?|file|ftp|telnet|chrome|chrome-extension|edge):\/\/|(?:news|about|data|magnet|view-source):)\S+/gi)||[]).map(e=>e.replace(/\.+$/,"")).join("\n");_It(a.target,c,!1,()=>d(b))}),_Yu=_cg(function*(b,d,a){let c=yield _aw(a.target),e=[];for(let g of c.split(/\n/))(g=g.trim())&&e.add(g);yield g=>_It(a.target,e.join("\n"),!1,g);d(b)});
{let b={},d=0;var _1u=(a,c)=>{if(null==c)return b[a];1E4<Date.now()-d&&(b={});b[a]=c;d=Date.now()}}function _Ut(b,d,a,c){_3e(a.smart,_Cg(c).usePrevMousePos)(e=>{a.lnk||(e=e.filter(f=>"A"!=f[0]));a.mda||(e=e.filter(f=>f[0].in("A","IFRAME")));a.frm||(e=e.filter(f=>"IFRAME"!=f[0]));let g=_ji(e,0,1)||"";g&&_1u(g,_ji(e,0,2));_It(a.target,g,!1,()=>d(b))})}
let _ia=_cg(function*(b,d,a,c){const e=(l,n)=>m=>_ai(c,_up,l,n)(p=>m(p.join("\n").trim().split(/\s*\n\s*/)));let g=a.prtcol||"http";g.match(/^[\w.+\-]+$/)&&(g+="://");let f=[],h=_Tt(a.urlTmpl||"");var k=yield e(_Tt(a.text||""));for(let l of k)if(k=_X(l,g,a.www))f.push(k);else{k=a.usesTabs?_qd(b):[0];for(let n of k)k=new Proxy(_Yp[n]||{},{get:(m,p)=>"text"==p.toLowerCase()?l:m[p]}),f.push(...(yield e(h,k)).map(m=>_X(m,g)).filter(m=>m))}_It(a.tgtCbrd,f.join("\n"),!1,()=>d(b))});
function _X(b,d,a=!1){if(_Xd(b))return b;try{b=b.replace(/^[\/\\:]+/,"");let c=new URL(d+b);if(!c.hostname||"localhost"==c.hostname)return c.href;if(0>b.indexOf("/"))if(c.hostname.match(/^\d{1,3}\.\d{1,3}\.\d{1,3}\.\d{1,3}$/)){if(0>b.indexOf(c.hostname))return null}else if(!_sw(c.hostname))return null;if(0<=c.hostname.indexOf(".")&&0>c.hostname.indexOf("%20"))return a&&c.hostname==_Oy(c.hostname)&&(c.hostname="www."+c.hostname),c.href}catch(c){}return null}
{let b;var _sw=function(d){[,d]=d.match(/^[a-z0-9.\-]+\.([a-z0-9\-]{2,17})$/)||[];if(!d)return!1;if(d.match(/^[a-z]{2,3}$/))return!0;b||(b="abbott academy accountant accountants actor adult aero africa agency alsace amsterdam apartments apple archi army arpa asia associates attorney auction audio auto baby band bank barcelona barclays basketball bayern beer berlin best bible bike bingo black blog blue bnpparibas boston boutique broker brussels build builders business buzz cafe camera camp canon capetown capital cards care careers cars casa cash casino catering center cern charity chat cheap church city claims cleaning click clinic clothing cloud club coach codes coffee college community company computer condos construction consulting contact contractors cooking cool coop corsica country coupons courses credit cricket cymru cyou dance date dating deals degree delivery dental dentist desi design diamonds diet digital direct directory discount doctor domains download durban earth education email energy engineer engineering enterprises equipment estate events exchange expert exposed express fail faith family fans farm fashion film finance financial fish fitness flights flowers football forex forsale foundation fund furniture futbol gallery game games garden gift gifts glass global gmbh gold golf goog google graphics gratis green group guide guru hamburg haus health healthcare help here hockey holdings holiday homes horse hospital host hosting house hsbc immo industries info institute insurance insure international investments irish istanbul jetzt jewelry jobs joburg kitchen kiwi koeln kred kyoto land lawyer leclerc legal lgbt life lighting limited limo link live loan loans london love ltda luxury management market marketing markets media melbourne menu miami microsoft mobi moda money monster mortgage moscow movie museum nagoya name network neustar news ninja observer okinawa onion online organic page paris partners parts party pharmacy photo photography photos physio pics pictures pink pizza place plumbing plus poker porn post press prod productions promo properties property quebec racing radio read realestate realtor realty recipes rehab reisen rent rentals repair report rest restaurant review reviews rocks rodeo rugby saarland sale salon school schule science scot security services sexy sharp shiksha shoes shop shopping show singles site soccer social software solar solutions space sport statebank store stream studio study style sucks supplies supply support surf surgery swiss sydney systems taipei tatar tattoo taxi team tech technology tennis tienda tips tirol today tokyo tools total tours town toys trade trading training travel tube university vacations vegas ventures video villas vision vlaanderen vote voyage wales wang watch webcam weber website wedding wien wiki wine work works world xn--3e0b707e xn--54b7fta0cc xn--80adxhks xn--80asehdb xn--80aswg xn--90ais xn--c1avg xn--d1acj3b xn--fiqs8s xn--h2brj9c xn--j1amh xn--node xn--p1acf xn--p1ai yandex yoga yokohama youtube zone",
b=b.split(" ").reduce((a,c)=>(a[c]=!0,a),{}));return b.hasOwnProperty(d)}}function _yk(b){return[{sequence:[{action:"copyElemUrl",params:{[b.type]:!0,smart:!0,target:-1}},{action:"loadUrls",params:{url:"<clipboard(-1)>",tabPos:"after",refTab:"currentTab"}}]}]}
function _5o(b,d,a){let c=":brwr"==a.target?_Kd:void 0,e="mute"==a.mode?_qa:"unmute"==a.mode?_kd:"toggle"==a.mode?_fa:void 0,g=null==e?("down"==a.mode?-1:1)*(null!=a.value?a.value:100):void 0;a=_Xt(a.mode,"up","down");_Lk(_Wj,{exeName:c,volume:g,relative:a,mute:e},()=>d(b))}let _7r=_cg(function*(b,d,a,c){"function"!=typeof _lh&&(yield e=>_9w("/file53.js",e));_lh(a,b,c);d(b)}),_fp=_cg(function*(b,d,a,c){"function"!=typeof _nu&&(yield e=>_9w("/file49.js",e));yield _nu(b,a,c);d(b)});
function _Ci(b){return[{sequence:[{action:"copyElemUrl",params:{lnk:!0,mda:!0,smart:!0,target:-1}},{action:"saveUrl",params:{url:"<clipboard(-1)>",ifFileExist:"rename",ifNameExist:"rename"}.add(b)}]}]}
let _8e=_cg(function*(b,d,a,c){var e=a.oper?[{type:"tgtTabs",comp:"ne"==a.oper?"eq":a.oper,not:"ne"==a.oper,value:a.value}]:a.conds||[];let g=_qd(b),f=!0,h;for(let l of e){var k=void 0;switch(l.type){case "tgtTabs":e=l.value|0;k="eq"==l.comp?g.length==e:"lt"==l.comp?g.length<e:"gt"==l.comp?g.length>e:!1;break;case "swtchSt":k=l.swtchId&&_ps[_wh(l.swtchId)[1]]==l.state;break;case "txtMtch":let n=!0;k=_we(function*(m){n=l.usesTabs&&(!n||_sj(m));m=_Tt(m);let p="";for(let q of n?g:[0])p+=(yield _ai(c,
_up,m,_Yp[q])).join(" ");return p});e=yield k(l.txt2||"");k=yield k(l.txt1||"");k=_Gt(e,l.comp).test(k)}k=k==!l.not;switch(h){case "A":f=f&&k;break;case "O":f=f||k;break;case "E":f=f==k;break;default:f=k}h=l.oper}("contChn"==a.action?!f:f)?d({break:"stopSeq"==a.action?"outer":"inner"}):d(b)});function _ui(b,d,a){a.swtchId&&_2t(a.swtchId,a.state);d(b)}
let _Ga=_cg(function*(b,d,a,c){a.sync||_Pw();if("time"==a.event)yield _za(1E3*a.time);else{var e=g=>f=>{_lf(_vo,a.event+"",c+"")[g]=()=>f(!0)};e=a.event==_vt?e(0):_Li(_qd(b).map(e));e=yield _Yd(e,_za(1E3*a.timeout));delete (_vo[a.event]||{})[c];_eo(_vo,a.event);if(_ul(e)&&"contChn"!=a.ifTmOut){d({break:"stopSeq"==a.ifTmOut?"outer":"inner"});return}}d(b)});
function _8k(b,d,a){function c(f){(f=f.in("focus","mouse")?f:_Zw[f]?_il(_df(_Zw[f].bounds)):void 0)&&_Lk(_cp,{point:f,level:g,relat:e})}let e="set"!=a.mode,g=("down"==a.mode?-1:1)*a.level;if("all"==a.monId)for(let f in _Zw)c(f);else c(a.monId);d(b)}let _Us=(b,d)=>_Lk(_Tf,null,a=>d(null==a?[]:b)),_li=b=>(d,a)=>setTimeout(()=>_Lk(_3i,b,()=>a(d)),230);
;
/* ===== file15.js ===== */
'use strict';{let v={},t={};var _ss=function(d,b,c){let f=c.group||"0";t[f]=t[f]||0;let g=_lf(v,f,[]);g.push([d,b,c]);1==g.length&&_ti(function*(){for(;g[0];){let [e,n,l]=g[0],u=l.inputSeq||[];if("stop"==(l.intoPage?yield E(u,l.times,l.keepModKeys,f,e):yield y(u,l.times,l.keepModKeys,f)))break;g.shift();"group"!=l.queue&&n(e)}});"group"==c.queue&&b(d)},_ks=function(d,b,c){if(c.group){var f=c.group;t[f]=Date.now();v[f]=[]}else for(f in v)c=f,t[c]=Date.now(),v[c]=[];b(d)};let F=function(d,b,c,f){d=
d==_ao?f:d==_8t?_Zw.desktop:_df(_Zw[_D(f)].bounds);return{x:"M"==b?d.x+Math.round(d.w/2):"E"==b?d.x+d.w:d.x,y:"M"==c?d.y+Math.round(d.h/2):"E"==c?d.y+d.h:d.y}},z,A=function(d){clearTimeout(z);d?_Lk(_8p,!0):z=setTimeout(()=>_Lk(_8p,!1),50)},E=(d,b,c,f,g)=>e=>{let n=new _wk;for(let l of _qd(g))0<l&&y(d,b,c,f,l)(n.onReady());n.setCallback(e)},y=_we(function*(d,b=1,c,f,g){let e=[],n=Date.now();if(g){_Yk.tabs.executeScript(g,{code:B+"",allFrames:!0,matchAboutBlank:!0},_Aw);var l=g==_Np&&_ji(_Yp[g],"window",
"focused")}let u=_we(function*(a){if(e.length&&n>=t[f]){if(g)for(let h of e)G(g,h);else{if(a&&(a=e[e.length-1],a[0]==_Lp&&a[3]))var k=e.pop();yield _Vy(_Dt,e)}e=k?[k]:[]}}),w=_we(function*(a){yield u();n>=t[f]&&(yield _za(1E3*(a||0)))}),H=_we(function*(a){let k={};if(a.dX||a.dY||a.wrtObj){var h=a.keyId==_Lp;let m=a.wrtObj==_Ae,p=e[e.length-1],q=p&&p[0]==_Lp;m&&q||h&&a.wrtObj==_8t&&!a.anim||(yield u(!0),k=yield _Vy(_Ua,a.wrtObj|_Do));q&&(k.mouse={x:p[1],y:p[2]});h=m?k.mouse.sc():F(a.wrtObj,a.wrtHorz,
a.wrtVert,k.win);h.x+=a.dX||0;h.y+=a.dY||0}return[k.mouse,h]}),I=_we(function*(a,k,h,m){var p=_Mf(a,k);let q=Math.max(1,Math.round(36*h));q=Math.max(1,Math.ceil(p/Math.max(1,p/q)));p=(k.x-a.x)/q;k=(k.y-a.y)/q;m&&A(!0);for(let C=0;C<q-1;++C)a.x+=p,a.y+=k,x(Math.round(a.x),Math.round(a.y)),yield w(h/q);m&&A(!1)}),x=(a,k,h)=>{let m=e[e.length-1];m&&m[0]==_Lp&&m[3]?(m[1]=a,m[2]=k,m[3]=h):e.push([_Lp,a,k,h])};if((!g||l)&&!c)var D=yield _Vy(_be,{state:!0});for(c=0;c<b;++c)for(let a of d)for(l=0;l<(a.repeat||
1);++l){if(a.keyId==_Pr)yield w(a.hold);else{let [k,h]=yield H(a);h&&(a.anim&&(yield I(k,h,a.anim,!a.noMovBlk)),x(h.x,h.y));a.keyId!=_Lp&&(e.push(a.keyId|("U"==a.action?_mk:_Lo)),a.hold&&(yield w(a.hold)),"DU"==a.action&&e.push(a.keyId|_mk),h&&x(k.x,k.y,!0))}if(n<t[f])return"stop"}yield u();D&&_Lk(_be,{keys:D,state:!1})}),G=function(d,b){if("number"==typeof b&&(b=_eh(b,!0),b.devId==_ee)){let c=b.num&~_zt;const f=b.num&_zt,g=_ji(_By,b.num,1),e=g>_N&&(!f&&!(48<=b.num&&57>=b.num)||b.num==(_7k|_zt)),
n=0<g&&g<_N;n&&(c=g);_Yk.tabs.executeScript(d,{allFrames:!0,matchAboutBlank:!0,code:`\n ${B.name}( ${c}, ${b.type==_Lo}, ${n?f?2:1:e?3:0} )\n `},_Aw);return!0}},r,B=function g(b,c,f){if(g){"undefined"==typeof r&&(r=[]);var e=r.indexOf(b);c&&-1==e&&r.push(b);!c&&0<=e&&r.splice(e,1);document.activeElement.dispatchEvent(new KeyboardEvent(c?"keydown":"keyup",{bubbles:!0,cancelable:!0,keyCode:b,which:b,location:f,repeat:c&&0<=e,shiftKey:0<=r.indexOf(16),ctrlKey:0<=r.indexOf(17),altKey:0<=r.indexOf(18)}))}}};
;
/* ===== file48.js ===== */
'use strict';let _rk=0;function _mw(){return _rk||"undefined"!=typeof _Vj&&!_ul(_Vj)}function _To(b,f,g,l){let m=g.bkgrnd?[0]:_qd(b);++_rk;_gr(g.scriptId,m,b,l)(e=>{--_rk;g.async||f(e)});g.async&&f(b)}
let _gr=_we(function*(b,f,g,l){let m=yield _zs(b);if(m){b=yield _Ue(b,f,g,m,void 0,l,!0);f=!1;l=[];for(let e of b)if(e)if(e===(e|0)&&(e=[e]),_Jw(e))f=!0,l.push(...e.map(n=>_Jw(n)?_Dw(n):_Yp[n]?n:null).filter(n=>n));else if("object"==typeof e&&"string"==typeof e.break&&1==Object.keys(e).length)return e;if(f)return l}return g}),_Ue=_we(function*(b,f,g,l,m,e,n,r){let a=[];for(let c of f)0<=c&&a.push(_A(b,c,g,l,m,e,n,r));return yield Promise.all(a)}),_Yh;
{var _A=function(a,c,d,h,p,k,t,u){return new Promise((v,w)=>{_xj(c,{scriptId:a,tabId:c,targetTabs:d,funcCode:p?h+"":`${55>_rs?"":"async"}()=>{\n${h}\n}`,args:_Ii(p),/* AC-MV3 FIX (2026-08-05, FEATURES-MV3.md §7-13): append a per-MESSAGE ~suffix to the
      trigInstId. The nested runInTab/runInFrames execUserFunc carried the
      PARENT's raw trigInstId → the SW dedup saw the parent's key as still
      in-flight → BLOCKED every nested call → runInTab returned [null].
      The suffix is IN THE MESSAGE: the n() retry re-sends the SAME message
      (same suffix → retry-dup still dedup'd), while each nested call gets
      its own key ≠ the parent's (no false block). Deterministic per message,
      like the round-6 ~suffix in file42. */trigInstId:(k||"")+"~"+(Math.random()+"").slice(2),/* AC-MV3 FIX (2026-08-06, round 7b): noWait marks the TOP-LEVEL RUN SCRIPT (t===true from _To/_gr). The scriptId branch acks it immediately (fire-and-forget, result unused) but MUST await nested _A calls (runInTab/runInFrames — noWait falsy) and return their REAL result — round-7 made them return [true]. */noWait:!0===t,frmFlt:u})(q=>{q=q||{};!t&&"error"in q?w(q.error):v(q.result)})})},_xj=(a,c)=>(d=_ay)=>{+a?c.frmFlt?r(+a,c,d):n(+a,c,d):e(c,d)};window.addEventListener("message",a=>m(a.data,{id:0},c=>a.source.postMessage({result:c,pongId:a.data.pingId},"*")));
// FIX: Don't block SW broadcast messages (they have _sw flag)
// Only return true (async) when we actually handle the message
_Yk.runtime.onMessage.addListener((a,c,d)=>{if(a._sw)return false; // Skip SW broadcasts
m(a,c.tab,d);return!0});
let b={},f=
a=>{for(var c=1;c in b;++c);b[c]=a;return c};const g=a=>_Yk.runtime.getURL(_ak)+"?file="+encodeURIComponent(a),l=_Es(-700,a=>_0j()(c=>_Xp(c)._ja(a)));let m=function(a,c,d){if(a.pongId)b[a.pongId]&&"dontDel"!=b[a.pongId](a.result)&&delete b[a.pongId];else if(c&&"userAPI"==a.type){++_rk;let h=()=>_Yh(a,c)((...p)=>{--_rk;d(...p)});_Yh?h():_9w("/file77.js",h)}else a.imprtSttgs?(window._ja||l)(a.imprtSttgs):a.viewSttgs?_Yk.tabs.create({active:!0,url:g(a.viewSttgs)}):a.redirSttgs&&_Yk.tabs.update(c.id,{url:g(a.redirSttgs)})},
e=_cg(function*(a,c){let d=document.getElementById("BGScript");d||(d=_Uu('<iframe id=BGScript src="file23.html">').children[0],yield h=>{d.onload=h;document.body.appendChild(d)});a.pingId=f(c);d.contentWindow.postMessage(a,"*")}),n=_cg(function*(a,c,d){const t0=performance.now();let rs="";for(let p=0;;++p){var h=yield k=>{let once=!1;const fin1=(x,why)=>{if(once)return;once=!0;rs=why||("undefined"===typeof x?"cb-undef":x?"cb-val":"cb-null");k(x)};try{_Yk.tabs.sendMessage(a,c,{frameId:0},x=>fin1(x,(_Yk.runtime.lastError?"lasterr:"+_Yk.runtime.lastError.message:"cb-ok")))}catch(e){fin1(void 0,"throw:"+String(e&&e.message||e))}/* AC-MV3 FIX (2026-08-06, round 14): 8000 → 6000ms. The FIRST
   userScripts.execute on a fresh page costs ~4-5s one-time (Chrome inits
   its userScripts subsystem; user VM 19:27: first execUserFunc +4909ms).
   round 13 raised the timeout 4000 → 8000ms so legit first calls could
   wait out the init without a retry/double-exec — but the KNOWN FEATURES-MV3.md §7-6 gap
   (runInPageCtx(func)) NEVER returns its result, so the test waited the
   FULL timeout: user VM 19:40 FAIL +8031ms (was +4031-4038ms with 4000ms).
   6000ms is the compromise: legit first calls (init ~4-5s) still fit, the
   gap FAILs in ~6s instead of 8s. The document-guard in file42.js makes
   the re-injection fallback a no-op anyway; the retry still re-sends the
   SAME message (SW dedup + __acFnDedup make it harmless).
   */setTimeout(()=>fin1(void 0,"timeout"),6000)};_Aw("msgToIsolCtx");/* AC-MV3 FIX (2026-08-06, round 6): treat null like undefined — retry. A STALE file42 instance (pre-guard, survives until the tab reloads) can win the sendMessage channel race with sendResponse(null) → F() destructures null → "_fr is not iterable" (VM 14:30 logs: setClipboard F-> null while the fresh instance logged the correct funcCode val). One retry re-sends the SAME message; with the round-6 K fix (non-destructive read) and the value-promise dedup, EVERY instance answers the SAME correct value → the retry converges. */if(null!=h||0<p||c.event){0<a&&console.warn('[AC-DLV] tab='+a+' resp +'+(performance.now()-t0).toFixed(0)+'ms attempt='+(p+1));break}try{0<a&&console.warn('[AC-DLV] tab='+a+' no listener → inject file42 attempt='+(p+1));yield _wj(a,{file:"file42.js"})}catch(k){return d({error:k})}}/* AC-MV3 DIAG (2026-08-06): what exactly did n() receive from the tab? F()-path (setClipboard/runInPageCtx file) failures show funcCode val logged but the SW destructure getting a non-iterable — this shows the raw sendMessage response. */0<a&&console.warn('[AC-DLV-F] tab='+a+' trig='+String(c&&c.trigInstId).slice(0,70)+' why='+rs+' h='+(void 0===h?'UNDEF':Array.isArray(h)?'ARR['+h.length+']':typeof h+':'+String(h&&h.message||h).slice(0,120)));d(h)}),r=_cg(function*(a,c,d){try{let h=
yield _wj(a,{allFrames:!0,matchAboutBlank:!0,code:"!!window.FN"});h.filter(k=>!k).length&&(h=yield _wj(a,{allFrames:!0,matchAboutBlank:!0,file:"file42.js"}));let p=h.length;h=[];c.frmCBId=f(k=>{if(k){if("error"in k)return d(k);h.push(k.result)}if(--p)return"dontDel";d({result:h})});yield k=>_Yk.tabs.sendMessage(a,c,k);_Aw()}catch(h){return d({error:h})}})}let _zs=_we(function*(b){(b=_gh(b,"script").value)&&b.srcFile&&(b=yield _L(b.srcFile,!0));return b?b.srcCode:""});
var _L=_we(function*(b,f){b=yield _sp(b);let g=_lo(b);if(_1(b)||!_Nf(b)){f=yield _If(b,"text",_ji(g,"ldTime")||0);if(f.error)return{error:f.error};if(null!=f.content)return _lo(b,{srcCode:f.content,encode:f.charEnc,ldTime:Date.now()})}else if(!g||6E4<Date.now()-g.checkTime){let l=_we(function*(){let [m,e]=yield _mg(_1p(b,"text",void 0,void 0,{"If-Modified-Since":(new Date(_ji(g,"ldTime")||0)).toUTCString()}));return 200==e.status?_lo(b,{srcCode:m,ldTime:Date.now(),checkTime:Date.now()}):304==e.status?
_lo(b,g.add({checkTime:Date.now()})):{error:e.status}});if(f&&g)l()();else return yield l()}return g});
_Du.script={saveAllImg:{name:"Example 1: Download all images",help:"",value:{srcCode:"let count = 0 ;\n//for each image in the page\nfor(let image of document.images){\n\t//if the image is bigger than 100x100 pixels\n\tif( image.src && image.width > 100 && image.height > 100 ){\n\t\t//save it to the desktop under a folder named after the page's domain\n\t\tlet filepath = await ACtl.saveURL(image.src, `<desktop>/${location.hostname}/`) ;\n\t\tconsole.log(++count, image.src, ' --\x3e ', filepath) ;\n\t}\n}\nalert(count + ' IMAGES SAVED.') ;"}},captTabPub:{name:"Example 2: Take page screenshot and upload it",
help:"",value:{srcCode:"//Take a shot of the current tab\nlet [[, dataUri]] = await ACtl.captureTab('#currentTab') ;\n//Put the image in the clipboard\nawait ACtl.setClipboard({image: dataUri}) ;\n//Open https://snipboard.io in a new tab\nlet [tabId] = await ACtl.openURL('https://snipboard.io', {rightOf: '#currentTab'}) ;\n//Wait for the tab to finish loading\nawait ACtl.on('tabLoadEnd', tabId) ;\n//Activate the new tab and focus its window\nawait ACtl.setTabState(tabId, 'active focused') ;\n//Execute AutoControl's [CLIPBRD PASTE] action\nawait ACtl.execAction('#clpbrdPaste') ;"}}};
;
/* ===== file77.js ===== */
'use strict';{_Yh=_we(function*(e,d){try{let h=yield W(e.props,e.args,e.scriptId,d,e.targetTabs,e.trigInstId);return h instanceof z?h:{result:h}}catch(h){return{error:`ACtl.${e.props[0]}: ${h.message||h}.`}}});let z=function(e,d){if(!new.target)return new z(e,d);e=63>_rs?e+"":(e+"").replace("__IMPORT__","import");this.add({funcCode:e,args:d})},I=function(e,d){let h=_Ha(e).toUpperCase();for(let k of _Xy(d))if(_Ha(_gh(k).name).toUpperCase()==h)return k;throw`${({tse:"Tab selection",script:"Script"})[d]} "${e}" does not exist`;
},J=function(e){return Object.defineProperty(e,Symbol.iterator,{value:function*(){for(let d in this)this.hasOwnProperty(d)&&(yield[d,this[d]])}})},C=function(e,d,h,k,t,n){function p(r,g){let a=new Uint8Array(r.length);for(let b=0;b<r.length;++b)a[b]=r.charCodeAt(b);return new Blob([a],{type:g})}function v(){return new Promise((r,g)=>{let a=new Image;a.onload=()=>r(a);a.onerror=()=>g(`"${t}" is not a valid image file.`);a.src=URL.createObjectURL(x())})}let x=()=>new File([p(atob(d),h)],t,{type:h,lastModified:n});
switch(e){case "base64":return d;case "binary":return atob(d);case "blob":return p(atob(d),h);case "file":return x();case "objectUrl":return URL.createObjectURL(x());case "dataUri":return`data:${h}${k?";charset="+k:""};base64,`+d;case "image":return v();case "canvas":return v().then(r=>{{let g=document.createElement("canvas");g.width=r.width;g.height=r.height;g.getContext("2d").drawImage(r,0,0,g.width,g.height);r=g}return r})}return(new Promise(r=>{let g=new FileReader;g.onload=()=>r(g.result);g.readAsText(p(atob(d),
h),k)})).then(r=>{switch(e){case "json":try{return JSON.parse(r)}catch(a){throw`Invalid JSON in file "${t}": ${a.message}`;}case "xmlDoc":case "htmlDoc":return(new DOMParser).parseFromString(r,"text/"+("xmlDoc"==e?"xml":"html"));case "html":var g=document.createElement("template");g.innerHTML=r;return g.content;case "css":return g=document.createElement("style"),g.textContent=r,document.implementation.createHTMLDocument().head.appendChild(g);case "module":return r=new Blob([r],{type:"text/javascript"}),
r=URL.createObjectURL(r),__IMPORT__(r).catch(a=>{a.message+=` in file "${t}"`;throw a;});default:return r}})},K=function(e,d,h,k=.9){function t(a){Array.from(a.querySelectorAll("br")).forEach(b=>b.parentNode.replaceChild(new Text("\r\n"),b));return a.textContent}function n(a){return b=>{let c=new FileReader;c.onload=()=>b(btoa(c.result));c.readAsBinaryString(a)}}function p(a){a=new Uint8Array(a);let b="";for(let c=0;c<a.length;++c)b+=String.fromCharCode(a[c]);return b}function v(a){return a.substr(a.indexOf(",")+
1||a.length)}function x(a){a=a.toLowerCase();return"image/"+({ico:"x-icon",cur:"x-icon",jpg:"jpeg"}[a]||a)}function r(a){let b=document.createElement("canvas");b.width=a.width;b.height=a.height;b.getContext("2d").drawImage(a,0,0,b.width,b.height);return b}let g=window[e];/* AC-MV3 FIX (2026-08-06, round 6): NO delete window[e]. The read is shared across EVERY live file42 instance in the tab (stale pre-guard instances survive until the tab reloads — an SW/extension reload does NOT remove content-script contexts, only a tab reload does). Each instance that receives the funcCode message runs K in the SAME user script world → the FIRST K deleted window[e], the rest read undefined → garbage responses (null/undefined/"undefined") won the sendMessage channel race → setClipboard "_fr is not iterable" (VM 14:30 logs: one cur-in + one dedup-hit, F-> null). Non-destructive read makes every K idempotent → every instance answers the SAME correct array → the race is harmless. The proxy's window[name] stays until the page unloads (tiny leak, acceptable). */if("object"==typeof g){if(g instanceof Blob)return a=>n(g)(b=>a(["bin",b]));if(g instanceof ArrayBuffer)return["bin",btoa(p(g))];if(!h||0>h.indexOf("/"))h=x(h||d);if(g instanceof HTMLImageElement||g instanceof SVGImageElement)g=
r(g);if(g instanceof HTMLCanvasElement)return["image",v(g.toDataURL(h,k))];if(window.OffscreenCanvas&&g instanceof OffscreenCanvas)return a=>g.convertToBlob({type:h,quality:k}).then(b=>n(b)(c=>a(["image",c])));if(g instanceof Element){d="";if(e=document.contains(g))d=(d=document.querySelector("base[href]"))?d.href:location.href,d=`<base href="${d}">`;return["html",g.outerHTML,{srcUrl:g.sourceURL||(e?location.href:""),text:g.innerText,ctxHtml:d}]}return g instanceof DocumentFragment?["html",[].map.call(g.childNodes,
a=>a.outerHTML||a.textContent).join(""),{srcUrl:g.sourceURL,text:t(g)}]:["json",JSON.stringify(g)]}g+="";try{return["bin",btoa(g)]}catch(a){return["text",g]}},L=(e,d)=>h=>{_Lk(_xo,e,k=>h(`File system error: ${k.trim()} "${d}"`))};const X={leftmostTab:"firstTab",rightmostTab:"lastTab",selectedTabs:"highlighted",mruTabs:"currWinTabsMruOrder",mruTabsAllWins:"allTabsMruOrder"};let Q=e=>e.filter(d=>!_As(_zh(_Yp[d]))),M=e=>{throw"Invalid tab specifier: "+e;},A=()=>{throw"Invalid argument types";},R=()=>
{throw"A tab must be specified when running in the background";},D=_we(function*(e,d=!0,h,k,t=!0){t||(_Fk=!0);let n;if(null==e||""===e)n=[];else if(+e&&!0!==e&&Number.isInteger(+e))n=[+e];else if("string"==typeof e){var p=e.trim();let v;"#"==p[0]&&(v=X[p.slice(1)]||p.slice(1),"targetTabs"==v?n=h:null==_gh(v,"tse").value&&(v=null));n||(v||(v=I(p,"tse")),yield _Rf(),n=yield _ai(k,_gt,v))}else if(_Jw(e)){n=[];for(let v of e)p=yield D(v,t,h,k),p.length&&n.push(p)}else if("object"==typeof e){yield _Rf();
n=[];for(let [v,x]of e)switch(v){case "not":let r=yield D(x,!0,h,k);n.push(Object.keys(_Yp).map(g=>+g).filter(g=>-1==r.indexOf(g)));break;case "intersect":_Jw(x)||M("'intersect' must be an array");t=[];for(p of x)t.push(yield D(p,!0,h,k));n.push(t.length?_Vw(...t):[]);break;case "sameWinAs":t=yield D(x,!0,h,k);n.push(_Ii(..._yl(t).map(g=>_cd[g].tabs.map(a=>a.id))));break;default:n.push(Object.keys(_Yp).filter(g=>{g=_gg(_Yp[g],v);var a=x;void 0===g&&M(`Unknown filter '${v}'`);g=a instanceof RegExp?
a.test(g):a&&"string"==typeof a.RE&&3>Object.keys(a).length?RegExp(a.RE,a.F).test(g):g==a;return g}).map(g=>+g))}n.length&&(n=[_Vw(...n)])}if(n)return d?_qd(n):n;M(e)}),Y=_we(function*(e,d=!0){d&&(yield t=>_Fu(t));d=_Yp[e];if(!d)return null;e={window:{}};const h="active audible favIconUrl height id incognito index muted openerTabId pinned selected status title url width".split(" ");for(var k of h)e[k]=_gg(d,k);e.url+="";e.status={discarded:"unloaded",complete:"loaded"}[e.status]||e.status;k=_gg(d,
"window");d="alwaysOnTop focused height left state top type width".split(" ");for(let t of d)e.window[t]=k[t];return e}),O=_we(function*(e,d,h){d=yield N(d,e);if(_1(d)){e=h.in("text","json","module","html","htmlDoc","xmlDoc","css");e=yield _If(d,e?"charEnc":"");if(e.error)throw yield L(e.error,d);return[h,btoa(e.content),e.mime,e.charEnc,d,e.modTime]}{let [t,n]=yield _mg(_1p(d,"binary"));if(200!=n.status)throw`HTTP error '${_wu(n.status,n)}' ${d}`;var k=n.getResponseHeader("content-type")||"";e=(k.match(/^[^;]+/)||
["application/octet-stream"])[0];k=(k.match(/charset="?([^";]+)/)||[,""])[1].toUpperCase();let p=+new Date(n.getResponseHeader("last-modified"));return[h,btoa(t),e,k,d,p]}}),N=_we(function*(e,d,h=!1){e=(e+"").trim();e.startsWith("data:")||(e=yield _sp(e));if(!_Nf(e)){d=yield _sp(_ji(_gh(d),"value","srcFile"));if(h?!_1(d):!d)throw`'${e}' is not an absolute file path or URL`;e=(new URL(e,d)).href}_1(e)&&(e=new URL(e),e=decodeURI(e.href.slice(e.host?5:8)).replace(/\//g,"\\").replace(/(?!^)\\{2,}/g,"\\"));
return e}),P=_we(function*(e,d){return e=yield N(e,d,!0)}),F=function(e,d,h){return _xj(e,{funcCode:h+"",args:_Ii(d)})},G=function(e,d,h){return _xj(e,{scrtCtxVar:d,value:h})},W=_we(function*(e,d,h,k,t,n){function p(a,b=!0){return D(a,b,t,n,!1)}function v(a){return a.substr(a.indexOf(",")+1||a.length)}function x(a){a=a.toLowerCase();return"image/"+({ico:"x-icon",cur:"x-icon",jpg:"jpeg"}[a]||a)}function r(a){try{new URL(a)}catch(b){throw`'${a}' is not a valid URL`;}}let g=e[0];switch(g){case "sleep":{let [a]=
d;yield _za(a);return}case "pubVar":d.pubVar=!0;case "var":{let [a,b]=d,c=d.pubVar?"":h;if(0==d.length)return z(J,[(yield _ae(c))||{}]);if(1==d.length&&"object"==typeof a){let f={};for(let [q,m]of a)f[_ur(c,q).join(".")]=_Rd(m);let l=yield _sy(f);if(l)throw l;return}if("string"==typeof a){if(1==d.length)return yield _ae(c,a);let f=yield _ge(c,a,b);if(f)throw f;return}A()}case "getScript":{let [a]=d;return yield _zs(I(a,"script"))}case "include":{let [a,b="",c=!1]=d;2==d.length&&"string"!=typeof b&&
([c,b]=[b,""]);const f="include "+a;let l=c||!(yield G(k.id,f));if(l){let q=yield O(h,a,"text"),m=yield C(...q),u=!q[2].match(/css/)&&!a.match(/\.css$/i)&&!(b+"").match(/^css$/i)||(b+"").match(/^js$/i);if(k.id){let w=u?"executeScript":"insertCSS";yield B=>_Yk.tabs[w](k.id,{code:m,runAt:"document_start"},B)}else yield _xj(0,{insertCode:m,type:u?"js":"css"});yield G(k.id,f,!0)}return!!l}case "import":d[1]="module";case "getFile":{let [a,b="text"]=d,c=yield O(h,a,b);return z(C,c)}case "saveFile":{let [a,
b,c]=d;c=c||{};a=yield P(a,h);let f=a.match(/[^.\/\\]*$/)[0],[l,q]=yield F(k.id,[b,f,c.format,c.quality],K);q=l.in("bin","image")?atob(q):_pk(q,c.format,!c.append);let m=yield _4u(a,q,null,c.append);if(m)throw yield L(m,a);return a}case "saveURL":{let [a,b]=d;r(a);b=yield P(b,h);let [c,f]=yield _mg(_1p(a,"binary"));if("\\"==b.slice(-1)){if(a.startsWith("data:"))throw"A filename must be specified when saving a data URI";let q=_Su(f);b+=q}let l=yield _4u(b,c);if(l)throw yield L(l,b);return b}case "getTabIds":{let [a,
b=!0]=d;return yield p(a,b)}case "getTabInfo":{let [a]=d;a||0!=k.id||R();a=a?yield p(a):[k.id];_Jr=yield _O(_yl(a));let b={},c=0;for(let f of a){let l=yield Y(f,!c++);if(l||1==a.length)b[f]=l}return z(J,[b])}case "runInTab":{let [a,b,c]=d;2==d.length&&([b,c]=[c,b]);a=Q(yield p(a));if("string"==typeof c||1==d.length){let f=1==d.length?h:I(c,"script"),l=yield _zs(f);return yield _Ue(f,a,a,l,void 0,n)}if(c&&c.FUNC)return yield _Ue(h,a,a,c.FUNC,_Ii(b),n);A()}case "runInFrames":{let [a,b,c,f]=d;3==d.length&&
([c,f]=[f,c]);a=Q(yield p(a));if(f&&f.FUNC&&"object"==typeof b)return[].concat(...yield _Ue(h,a,a,f.FUNC,_Ii(c),n,!1,b));A()}case "runInPageCtx":{let [a,b]=d;if(1==d.length||2==d.length&&!b.FUNC)[a,b]=[b,a];if(0==k.id)throw"this function cannot be used in background scripts";if("string"==typeof b){b=yield N(b,h);const c="runInPageCtx "+b;let f=a||!(yield G(k.id,c));if(f){let l=b;if(_1(b)){let m=yield O(h,b,"objectUrl");l=z(C,m)}let q=yield F(k.id,l,m=>runInPageCtx(m.funcCode?FN(m.funcCode)(...m.args):
m));if(q.error)throw q.error;yield G(k.id,c,!0)}return!!f}if(b&&b.FUNC){let c=yield F(k.id,[b.FUNC,_Ii(a)],(f,l)=>q=>{runInPageCtx("funcExecLstnr",()=>{window.addEventListener("message",u=>{if(u.source==window&&u.data.funcName&&u.data.args){try{var w={result:window[u.data.funcName](...u.data.args)}}catch(y){w={error:y.message||y}}delete window[u.data.funcName];let B=y=>window.postMessage({response:y,funcName:u.data.funcName},"*");w.result instanceof Promise?w.result.then(y=>B({result:y}),y=>B({error:y})):
B(w)}})})();let m="_"+(Math.random()+"").slice(2);window.addEventListener("message",function B(w){w.source==window&&w.data.funcName==m&&w.data.response&&(q(w.data.response),window.removeEventListener("message",B))});runInPageCtx({code:`var ${m} = ${f}`})();window.postMessage({funcName:m,args:l},"*")});if(c.error)throw c.error;return c.result}A()}case "openURL":{let [a,b]=d;a=_Ii(a);for(let l of a)r(l);let c={url:a,winType:"normal",newTabs:!0},f=[];b&&(1==Object.keys(b).length&&(b.newWindow||b.leftOf||
b.rightOf)?b.leftOf?(c.tabPos="before",c.refTab=(yield p(b.leftOf))[0]):b.rightOf?(c.tabPos="after",c.refTab=(yield p(b.rightOf))[0]):(c.tabPos="newWin",c.incognito=!!(b.newWindow+"").match(/\bincognito\b/i),(b.newWindow+"").match(/\bpopup\b/i)&&(c.winType="popup")):f=yield p(b));return(yield l=>_Mh(f,l,c))[0]}case "closeTab":{let [a]=d;if(!a&&0==k.id)return[];a=a?yield p(a):[k.id];yield b=>_Zj(a,b);return a.length}case "setTabState":{let [a,b,c=_qa,f=!0]=d;if(!a&&0==k.id)return 0;a=a?yield p(a):
[k.id];const l={active:"activateTabs",focused:"focusWin",selected:"highlightTabs",pinned:"pinTabs",muted:"muteTabs",minimized:"minimizeWins",maximised:"maximizeWins",maximized:"maximizeWins",restored:"restoreWins",fullscreen:"fullscreenWins",hidden:"hideWins",topmost:"topmostWins"};b=_Ha(b).split(" ");for(let q of b){if(!l[q])throw`'${q}' is not a valid state`;yield m=>_Fu(m);yield m=>_gh(l[q],"action").value(a,m,{mode:c==_fa?+c:+!!c,noAnim:!f})}return a.length}case "execAction":{let [a,b]=d,c=a;
if(!(a instanceof RegExp)){a=_Ha(a);let m=a.slice(1),u=_gh(m,"action");if("#"==a[0]&&u){b||0!=k.id||(b="#currentTab");b=b?yield p(b,!1):[k.id];let w=_Jw(u.value)?u.value:[{sequence:[{action:m}]}];return _qd(yield _rf(w,b))}}b&&(b=yield p(b,!1));let f=[],l=yield _ru("trigActList"),q=0;for(let [m,u]of l)if(!u.disabled&&(a instanceof RegExp?a.test(u.title):!_Vo(a,_Ha(u.title)))){let w=yield _rf(_ek[m],b);f.push(...w);++q}if(0==q)throw`No action found for "${c}"`;return _qd(f)}case "favoriteTabs":{let [a,
b="",c=[]]=d;c=yield p(c);yield f=>_Fu(f);yield f=>_vd(c,f,{listId:a,oper:_Ha(b).toLowerCase()});return _Mo[a]}case "runCommand":{let [a,b="",c=!1]=d;"boolean"==typeof b&&([c,b]=[b,""]);b||(b="<desktop>");b=yield P(b,h);let f=yield _iw(a,b,c);if(f.error)throw"System error: "+(yield _Vy(_xo,f.error)).trim();return f}case "getClipboard":{let [a,b="binary"]=d;a=_Ha(a).toLowerCase();if("format"==a)return S[_zo.trueFmt];const c="text"==a,f=a.in("jpg","jpeg","png","webp");if(a&&!c&&!f)throw`'${a}' is not a valid format`;
let l=yield _yw(c?_fd:null);if(f&&l.format!=_Dk)return"";switch(l.format){case _fd:case _s:return l.content;case _Af:return c?l.content.join("\n"):l.content;case _4g:return z(q,[_4o(l.content),_Uu+""]);case _Dk:{let m=btoa(l.content),u="image/png";if(f){if("png"!=a&&(window._987654321qwerty_=yield C("canvas",m,u),[,m]=K("_987654321qwerty_",a),u=x(a)),!_Xt(b,"binary","blob","dataUri","objectUrl","base64","image"))throw`'${b}' is not a valid return type`;}else b="canvas";return z(C,[b,m,u])}}return"";
function q(m,u){u=FN(u)(m.fragment);u.sourceURL=m.sourceURL;Object.defineProperty(u,"innerHTML",{get(){return[].map.call(this.childNodes,w=>w.outerHTML||w.textContent).join("")}});return u}}case "setClipboard":{let [a]=d,_fr=yield F(k.id,[a,"png"],K);/* AC-MV3 DIAG (2026-08-06): what did F() actually return? The 10:47 log showed funcCode val (array) but destructure got "not iterable" — this pins the exact value n() delivered. */try{console.warn('[AC-F] setClipboard F-> '+JSON.stringify(_fr).slice(0,100))}catch(x){}var [b,c,f={}]=_fr,l="";switch(b){case "bin":c=atob(c);case "text":b=_fd;break;case "image":b=_Dk;break;case "json":c=JSON.parse(c);if(_Jw(c)){b=_Af;c=c.map(q=>(q+"").replace(/\//g,"\\"));c=yield _sp(c);break}if("string"==typeof c.image){b=_Dk;c=c.image.startsWith("data:")?
v(c.image):btoa(c.image);break}else"string"==typeof c.html?(c=c.html,f.srcUrl=c.sourceURL,f.text=(new DOMParser).parseFromString(c,"text/html").body.innerText):A();case "html":b=_4g;_Zt(f.text,_fd)();c=_Ra(c,f.srcUrl,f.ctxHtml);l="addFmt";break;default:A()}return yield _Zt(c,b,l)}case "captureTab":{let [a,b="dataUri"]=d;a||0!=k.id||R();if(!_Xt(b,"binary","blob","dataUri","objectUrl","base64","canvas","image"))throw`'${b}' is not a valid return type`;a=a?yield p(a):[k.id];let c={};for(let f of a){yield m=>
_Fu(m);let l=_Yp[f];if(!l)continue;l.active||(yield m=>_Ph([f],m,{peek:!1}));let q=yield m=>_Yk.tabs.captureVisibleTab(l.windowId,{format:"png"},m);_Aw()?1==a.length&&(c[f]=null):("dataUri"!=b&&(q=z(C,[b,v(q),x("png")])),c[f]=q)}return z(J,[c])}case "on":{let [a,b,c]=d;b&&b.FUNC&&([b,c]=[c,b]);b=b?yield p(b):[0];if(c&&c.FUNC){c.refCount=0;for(let f of _Ha(a).split(" ")){let l=Z(f),q=_Xt(l,_vt,_wf,_Ff,_Ui);for(let m of q?[0]:b)++c.refCount,_lf(_Vj,l,{},m,{},k.id,h,[]).push(c),m&&aa()}return z(f=>window[f]("promise"),
[c.FUNC])}A()}case "off":{let [a,b]=d;1==d.length&&_Jw(a)&&([a,b]=[b,a]);(a&&"string"!=typeof a||b&&!_Jw(b))&&A();a&&(a=_Ha(a).split(" "));let c=new _wk,f=k.id;for(let [l,q]of _Vj){let m=T(l);if(!a||0<=a.indexOf(m))for(let [u,w]of q){let B=_ji(w,f,h)||[];for(let y of B)(!b||0<=b.indexOf(y.FUNC))&&setTimeout(c.onReady(()=>{B.remove(y,!0);_eo(_Vj,l,u,f,h);1>--y.refCount&&_xj(f,{funcName:y.FUNC,event:{delete:!0}})()}))}}yield l=>c.setCallback(l);return}case "expand":{let [a,b,c]=d;"array"!=b&&"string"!=
b||null!=c||([b,c]=[c,b]);"string"!=typeof a&&A();let f=_Tt(a);_wd();let l=[];if(ba(a)){b=b?yield p(b):[k.id];for(let q of b)l.push(...yield _ai(n,_up,f,_Yp[q]))}else l=yield _ai(n,_up,f);return"array"==c?l:l.join("\v").replace(/\n?\v/g,"\n")}case "switchState":{let [a,b]=d;a=_Ha(a);/* AC-MV3 FIX (2026-08-05): _if may transiently lack binSwtch — _6s/_zj assign _if from DIFFERENT async storage reads (config chain / storage.onChanged rebuild), so a race can leave _if pointing at an object without binSwtch (intermittent "ACtl.switchState: _if.binSwtch is not iterable" from the 2nd script run). Read defensively — never fabricate storage keys (in-memory only; round-18 write-back safety preserved). */for(let [c,f]of(_if.binSwtch||[]))if(!_Vo(a,f.name))return 1==d.length?_ps[c]:_2t(c,b);return}case "getEnv":{let a=e.slice(1).concat(...d.map(b=>"string"==typeof b?b.split("."):A()));if(1==a.length&&"eventData"==a[0])return _Cg(n).data;
return}case "natMsg":return}if(g)throw"This function does not exist";}),E={},ba=e=>{if(!(e in E)){let d=Object.keys(E);5<=d.length&&delete E[d[0]];E[e]=_sj(e)}return E[e]};const U={tabOpen:_Ui,tabClose:_5k,tabActivate:_pw,tabUnload:_oi,tabLoadBegin:_oe,tabLoadEnd:_Fd,tabAudioBegin:_I,tabAudioEnd:_Iw,winOpen:_wf,winClose:_Ff,winFocus:_Wk,clipboardChange:_vt,winUnfocus:_Cw,tabFocus:_vp,tabUnfocus:_Ed,tabDeactivate:_4r,winMinimize:_td,winUnminimize:_ik,tabUrlChange:_Gp};let Z=function(e){const d=U[e];
if(d)return d;throw`'${e}' is not a valid event name`;},T=function(e){for(let [d,h]of U)if(h==e)return d},aa=function(){H.alreadyAdded||_Yk.tabs.onRemoved.addListener(H)},H=function(e){let d=!1;for(let [h,k]of _Vj)for(let [t,n]of k)if(d=0<t,t==e)for(let [p,v]of n)for(let [x,r]of v)for(let g of r)setTimeout(()=>{r.remove(g,!0);_eo(_Vj,h,t,p,x);1>--g.refCount&&_xj(p,{funcName:g.FUNC,event:{delete:!0}})()});d||(_Yk.tabs.onRemoved.removeListener(H),H.alreadyAdded=!1)},V=function(e,d,h){let k=_Vj[e][d];
if(k)for(let [t,n]of k)for(let [p,v]of n)for(let x of v)_xj(t,{funcName:x.FUNC,event:h})(r=>{r||(v.remove(x,!0),_eo(_Vj,e,d,t,p))})};var _Vj={},_kr=_cg(function*(e,d){if(_Vj[e]){let h={type:T(e)},k;if(e.in(_Wk,_Cw,_wf,_td,_ik)){let t=yield n=>_Wy(d,n);_Aw();h.tabId=t.id;e!=_wf&&(k=h.tabId)}else e!=_Ff&&(e==_vt?h.clipFormat=S[_zo.trueFmt]:k=h.tabId=d);k&&V(e,k,h);V(e,0,h)}});const S={[_fd]:"text",[_s]:"text",[_4g]:"html",[_Af]:"files",[_Dk]:"image",0:"unknown"}};
;
/* ===== file37.js ===== */
'use strict';let _2y=[],_zw,_Wi,_Fk=!0;
// AC-MV3: action diagnostics — unique run ID, timings, per-action run counter.
let __acLogSeq=0,__acActCtx=null;
function __acLog(t,m){try{const e=__acActCtx,r=e?Math.round(performance.now()-e.t0):0;console.warn('[AC-ACT] #'+(e?e.id:'-')+' '+t+' '+m+(e?' +'+r+'ms':''))}catch(x){}}
// AC-MV3: cache window enumeration to avoid ~1s+ chrome.windows.getAll before every action.
// _Fk=!0 is set after EVERY action in _rf, forcing _Rf to enumerate before the next action.
// chrome.windows.getAll({populate:true}) is expensive — cache results for 1500ms
// when the tab STRIP has not changed (rapid wheel-spin switchRight/Left).
// ⚠ onCreated/_Zf updates _Yp but NOT _Gk / _cd[w].tabs (the ordered lists
// _gt("rightTabWrap") uses). A 1.5s cache after loadUrls therefore made
// Open URL (to the right) + Switch to right tab land on the OLD right
// neighbor — one tab too far. Structural tab/window events set
// __acEnumDirty so the next _Rf MUST re-enum even inside the cache window.
let __acLastEnum=0;const __acEnumCacheMs=1500;
let __acEnumDirty=false;
function __acInvalidateEnumCache(){__acEnumDirty=true;}
var _Rf=_we(function*(a=!1){if(a||_Fk){const _now=Date.now();if(__acEnumDirty||_now-__acLastEnum>__acEnumCacheMs){__acLastEnum=_now;__acEnumDirty=!1;const t0=performance.now();yield b=>_Fu(()=>{__acLog('ENUM','windows.getAll took '+(performance.now()-t0).toFixed(0)+'ms');b()});}_wd();_Fk=!1}});function _wd(){_kg=_hu=_Bk=_1i=_Kt=null;_Jr={}}
// AC-MV3: queueing instead of blanket drop. The native component fires TWO
// trigger ids per hotkey press (~100-200ms apart, e.g. 14+34). They may be
// DUPLICATES (identical actions — drop the second) or INDEPENDENT actions
// (e.g. 14=runScript + 34=activateTabs — BOTH must run, as observed
// 2026-08-02). Decision: drop only if the arriving trigger has a DIFFERENT id
// AND arrived <__acCompanionMs after the last accepted trigger AND its action
// signature is IDENTICAL to the last accepted one. Real re-presses reuse the
// SAME trigger id and are always QUEUED, so fast pressing is never lost.
// __acLastTrigId/Time/Sig = last ACCEPTED (queued/running) trigger.
let __acLastTrigId=-1,__acLastTrigTime=0,__acLastTrigSig="";const __acCompanionMs=300;
const __acTrigSig=x=>{try{return JSON.stringify(_ek[x]||null)}catch(e){return""}};
let _Pw=_cg(function*(a=0,b=!1){const c=_2y[0];yield _za(a);if(c==_2y[0]){if(b)if("runScript"==_Wi){/* AC-MV3: the "Stop waiting" dialog cannot render in the SW (no DOM). The script has already run in the page — only the result round-trip is stuck, so force-shift the stuck head and continue with queued presses. */__acLog('STUCK','runScript head stuck '+a+'ms → force-shift')}else _Ot("stuckAction",{action:_Wi});_2y.shift();_6y()}}),_6y=_cg(function*(a,b=null){if(a){if(!_2y.length){__acActCtx={id:++__acLogSeq,t0:performance.now(),cnt:{}};__acLog('TRIG','trigger='+a)}a:if(_2y.push([a,b]),1<_2y.length){
const _now=Date.now();
if(a!==__acLastTrigId&&_now-__acLastTrigTime<__acCompanionMs&&__acTrigSig(a)===__acLastTrigSig){__acLog('DUP','companion='+a+' (same actions as '+__acLastTrigId+') → dropped');_2y.pop();return;}
__acLastTrigId=a;__acLastTrigTime=_now;__acLastTrigSig=__acTrigSig(a);
// AC-MV3 overflow cap: protect against key-repeat floods (30-60ms repeats).
// Keep the newest presses, drop the oldest queued item.
if(_2y.length>8){__acLog('DROP','queue overflow('+_2y.length+') → drop oldest');_2y.splice(1,1);}
__acLog('QUEUE','trigger='+a+' busy → queued');b=4;if("sendInput"==_Wi){a=_ji(_ek,a,0,"sequence",0)||{};if("stopSendInput"==a.action){_ks([],_ay,a.params||{});_2y.shift();break a}b=8}else"wait"==_Wi&&(b=30);_2y.length==
b&&_Pw(1200,!0);return}__acLastTrigId=a;__acLastTrigTime=Date.now();__acLastTrigSig=__acTrigSig(a);for(_Fk=!0;_2y.length;){const c=_2y[0];[a,b]=c;(a=_ek[a])&&(yield _rf(a,null,b));if(c!=_2y[0])break;_2y.shift()}}}),_Da=0;
var _rf=_we(function*(a,b,c){c||(c=_Ai());let h=0;a:for(let e of a){yield _Rf();if(h++||!b){_se=null;let f;"hoveredTabs"==e.targets&&e.sequence&&1==e.sequence.length&&(a=e.sequence[0],f="object"==typeof _w(a.action,a.params));b=e.targets&&!f?yield _ai(c,_gt,e.targets):_Np?[[_Np]]:[]}b:for(let {action:f,params:k}of e.sequence||[]){yield _Rf();let l=_w(f,k);if("object"==typeof l)b=yield _rf(l,null,c);else{_Wi=f;_se&&(b.forEach(d=>{for(let g=0;g<d.length;++g)_se[d[g]]&&(d[g]=_se[d[g]])}),_se=null);__acActCtx&&(__acActCtx.cnt[f]=(__acActCtx.cnt[f]||0)+1,__acLog('ACT','action='+f+' run#'+__acActCtx.cnt[f]));try{let d=
yield g=>l(b,g,k||{},c);if(!_Jw(d)){if("inner"==d.break)break b;if("outer"==d.break)break a}b=d;__acLog('OK','action='+f)}catch(d){_Ot("error",{action:f,stack:d.stack,params:"saveUrl"==f?k:void 0})}_Fk=!0}}}return b});
_Du.action={activateTabs:{name:"Activate tabs",grp:"tab",h:1,value:_Ph},reloadTabs:{name:"Reload tabs",grp:"tab",value:_Xs},goBackTabs:{name:"Go back",grp:"tab",value:_Is},goForwardTabs:{name:"Go forward",grp:"tab",value:_Zi},goUpURL:{name:"Go upper URL",grp:"tab",h:1,value:_1r},loadUrls:{name:"Open URL",grp:"tab",h:1,value:_Mh},highlightTabs:{name:"Select tabs",grp:"tab",h:1,value:_7f},pinTabs:{name:"Pin tabs",grp:"tab",value:_Pe},zoomTabs:{name:"Zoom tabs",grp:"tab",value:_Ig},muteTabs:{name:"Mute tabs",
grp:"tab",h:1,value:_Rh},moveTabs:{name:"Move tabs",grp:"tab",h:1,value:_jj},detachTabs:{name:"Detach tabs",grp:"tab",h:1,value:_Sg},groupTabs:{name:"Group tabs",grp:"tab",h:1,value:_Ir},duplicateTabs:{name:"Duplicate tabs",grp:"tab",h:1,value:_fj},openInIncognito:{name:"Open in incognito",grp:"tab",h:1,value:_yy},closeTabs:{name:"Close tabs",grp:"tab",h:1,value:_Zj},undoClose:{name:"Reopen tabs",grp:"tab",h:1,value:_3j,perms:"ses"},unloadTabs:{name:"Unload tabs",grp:"tab",h:1,value:_rl},favoriteTabs:{name:"Favorite tabs",
grp:"tab",h:1,value:_vd},alterTgtTabs:{name:"Alter target tabs",grp:"",value:_Jd},focusWin:{name:"Focus",grp:"win",h:1,value:_Ny},moveResizeWins:{name:"Move/Resize",grp:"win",h:1,value:_Pt},fitWinsToGrid:{name:"Fit to grid",grp:"win",h:1,value:_Pt},tileWins:{name:"Tile",grp:"win",h:1,value:_ft},minimizeWins:{name:"Minimize",grp:"win",value:_sk(_Hr)},maximizeWins:{name:"Maximize",grp:"win",value:_sk(_tp)},restoreWins:{name:"Restore",grp:"win",h:1,value:_ci},fullscreenWins:{name:"Fullscreen",grp:"win",
value:_4d},hideWins:{name:"Hide",grp:"win",h:1,value:_ar},scrollWins:{name:"Scroll",grp:"win",h:1,value:_0g},topmostWins:{name:"Stay on top",grp:"win",h:1,value:_sk(_si)},sendWinsToBottom:{name:"Send to bottom",grp:"win",h:1,value:_jk},openBookmarks:{name:"Open bookmarks",grp:"bmrk",h:1,value:_Mh,perms:"bkm"},bookmarkTabs:{name:"Bookmark tabs",grp:"bmrk",h:1,value:_Vu,perms:"bkm"},bookmarkUrls:{name:"Bookmark URL",grp:"bmrk",h:1,value:_Vu,perms:"bkm"},openMenu:{name:"Open menu",grp:"menu",h:1,value:_Jj},
closeMenu:{name:"Close menu",grp:"menu",value:_Oa},moveSelectMark:{name:"Move item mark",grp:"menu",h:1,value:_eu},selectMarkedItem:{name:"Select menu item",grp:"menu",h:1,value:_2h},clpbrdCut:{name:"Clipbrd cut",grp:"clbrd",h:1,value:_gp(_kt)},clpbrdCopy:{name:"Clipbrd copy",grp:"clbrd",h:1,value:_gp(_yj)},clpbrdPaste:{name:"Clipbrd paste",grp:"clbrd",h:1,value:_gp(_Ky)},clpbrdPut:{name:"Clipbrd put",grp:"clbrd",h:1,value:_Hg()},copyElemUrl:{name:"Copy hovered URL",grp:"clbrd",h:1,value:_Ut,perms:"hst"},
copyLinks:{name:"Copy selected URLs",grp:"clbrd",h:1,value:_E},extractURLs:{name:"Extract URLs",grp:"clbrd",h:1,value:_Hp},txtToUrl:{name:"Text to URL",grp:"clbrd",h:1,value:_ia},delDupLines:{name:"Erase dup. lines",grp:"clbrd",h:1,value:_Yu},clpbrdDiscard:{name:"Discard",grp:"",h:1,value:_ay},setVolume:{name:"Change volume",grp:"sys",h:1,value:_5o},showDesktop:{name:"Show desktop",grp:"sys",h:1,value:_Us},setMonBright:{name:"Screen brightness",grp:"sys",h:1,value:_8k},screenSaver:{name:"Screen saver",
grp:"sys",h:1,value:_li("scrSvr")},setMonPower:{name:"Turn off screen",grp:"sys",h:1,value:_li("monOff")},brkActSeq:{name:"Continue chain if",grp:"exec",h:1,value:_8e},setSwtchSt:{name:"Set switch state",grp:"exec",h:1,value:_ui},wait:{name:"Wait",grp:"exec",h:1,value:_Ga},saveUrl:{name:"Save URL",grp:"other",h:1,value:_fp},playAudio:{name:"Play audio",grp:"other",h:1,value:_7r},insertText:{name:"Insert text",grp:"other",h:1,value:_Hg(!0)},sendInput:{name:"Synthesize input",grp:"other",h:1,value:_ss},
stopSendInput:{name:"Stop synth input",grp:"other",h:1,value:_ks},runCommand:{name:"Open file/program",grp:"other",h:1,value:_Yg},runScript:{name:"Run script",grp:"other",h:1,value:_To,perms:"hst"},screenShot:{name:"Take screenshot",grp:"",h:1,value:_ay},openNTP:{name:"Open new tab",h:1,value:{gener:_c}},goBack:{name:"Back",h:1,value:[{sequence:[{action:"goBackTabs"}],targets:"currentTab"}]},goForward:{name:"Forward",h:1,value:[{sequence:[{action:"goForwardTabs"}],targets:"currentTab"}]},reload:{name:"Reload",
h:1,value:[{sequence:[{action:"reloadTabs"}],targets:"currentTab"}]},zoomIn:{name:"Zoom in",h:1,value:[{sequence:[{action:"zoomTabs",params:{type:1,steps:1}}],targets:"currentTab"}]},zoomOut:{name:"Zoom out",h:1,value:[{sequence:[{action:"zoomTabs",params:{type:-1,steps:1}}],targets:"currentTab"}]},duplicate:{name:"Duplicate tab",h:1,value:[{sequence:[{action:"duplicateTabs"}],targets:"currentTab"}]},detach:{name:"Detach tab",h:1,value:[{sequence:[{action:"detachTabs"}],targets:"currentTab"}]},switchPrev:{name:"Switch to previous tab",
h:1,value:[{sequence:[{action:"activateTabs"}],targets:"prevUsedTab"}]},switchLeft:{name:"Switch to left tab",value:[{sequence:[{action:"activateTabs"}],targets:"leftTabWrap"}]},switchRight:{name:"Switch to right tab",value:[{sequence:[{action:"activateTabs"}],targets:"rightTabWrap"}]},switchLeftmost:{name:"Switch to leftmost tab",value:[{sequence:[{action:"activateTabs"}],targets:"firstTab"}]},switchRightmost:{name:"Switch to rightmost tab",value:[{sequence:[{action:"activateTabs"}],targets:"lastTab"}]},
pin:{name:"Pin tab",h:1,value:[{sequence:[{action:"pinTabs",params:{mode:_fa}}],targets:"currentTab"}]},mute:{name:"Mute tab",h:1,value:[{sequence:[{action:"muteTabs",params:{mode:_fa}}],targets:"currentTab"}]},close:{name:"Close tab",h:1,value:{gener:_Vk}},closeLefts:{name:"Close left tabs",h:1,value:[{sequence:[{action:"closeTabs"}],targets:"allLeftTabs"}]},closeRights:{name:"Close right tabs",h:1,value:[{sequence:[{action:"closeTabs"}],targets:"allRightTabs"}]},closeOther:{name:"Close other tabs",
h:1,value:[{sequence:[{action:"closeTabs"}],targets:"otherTabs"}]},closeWin:{name:"Close window",h:1,value:[{sequence:[{action:"closeTabs"}],targets:"currWinTabs"}]},reopen:{name:"Reopen closed tab",h:1,value:[{sequence:[{action:"undoClose"}]}],perms:"ses"},openElemUrl:{name:"Open element URL",h:1,value:{gener:_yk},perms:"hst"},saveElemUrl:{name:"Save element URL",h:1,value:{gener:_Ci},perms:"hst"}};
;
/* ===== file3.js ===== */
'use strict';var _Vi={rightButton:{name:"Right button",value:_Bh(_md)},middleButton:{name:"Middle button",value:_Bh(_ir)},fourthButton:{name:"4th button",value:_Bh(_Ze)},fifthButton:{name:"5th button",value:_Bh(_Vf)},leftCtrl:{name:"Left Ctrl",value:_Bh(_jp,!1)},rightCtrl:{name:"Right Ctrl",value:_Bh(_xs,!1)}};function _Bh(a,b=!0){return{begin:[{combins:[{eventId:a,wildcard:_Ti,block:b}]}],end:[{combins:[{eventId:a|_mk,wildcard:_Ti}]}]}}
function _0p(a={}){a=a.triggers||{};let b=a.preset||"rightButton";"other"!=b&&a.add(_Vi[b].value);a.timeout=1E3*(a.timeout||1.5);return a}function _Jp(a={}){a=a.sc();"stepSize"in a&&(a.stepSize=Math.max(3,a.stepSize));"dirChangeSens"in a&&(a.dirChangeSens=_fu(a.dirChangeSens,1,9)+1);_Lk(_Ei,a)}
{let a={light:{color:"#555555",bgColor:2147483647},dark:{color:"white",bgColor:2130706432}};var _6t=function(b={}){_Ke(b)(c=>{0==b.enabled&&(c=[]);_Lk(_Xa,{icons:c}.add(b,a[b.colors||"light"]))})},_Ke=_we(function*(b){yield document.fonts.load("10px gestureDirs");var c=b.size||30;b=yield _l(c,a[b.colors||"light"].color);let d=yield _dd("v",.77*c,"rgba(0,255,0,.7)","rgba(200,200,200, 0.2)");c=yield _dd("x",.77*c,"rgba(255,0,0,.7)","rgba(200,200,200, 0.2)");return b.concat(d,c)})}
let _l=_we(function*(a,b){let c=[];for(let d=1;8>=d;++d){let e=_zi(""+d,a+"px/1 gestureDirs",b);e=yield _Xi(e,[{margin:"3 0"},{shadow:"2 2 4 rgba(0,0,0,.4)"}]);c.push(_Hk(e))}return c}),_dd=_we(function*(a,b,c,d){a=_zi(a,b+"px/1 gestureDirs",c);c=_qw(.82*b);let e=_qw(b/40);a=yield _Xi(a,[{resize:c},{margin:_qw((1-.82)*b)},{shadow:`${e} ${e} 3 rgba(0,0,0,.7)`},{background:d},{cornerRadius:"50%"}]);return _Hk(a)});
;
/* ===== file24.js ===== */
'use strict';function _df(a){return{x:a.left,y:a.top,w:a.width,h:a.height}}function _Ug(a,b=1){if(10<=_Ie){const c=7.2*b;b*=.3;a=Object.assign({},a);a.x+=c;a.y+=b;a.w-=2*c;a.h-=c+b}return a}function _1w(a){let b=Math.round(a.x),c=Math.round(a.y),d=Math.round(a.w);a=Math.round(a.h);return 60>_rs?{left:b||-1,top:c||-1,width:d+(b?0:1),height:a+(c?0:1)}:{left:b,top:c,width:d,height:a}}function _il(a){return{x:a.x+a.w/2,y:a.y+a.h/2}}
function _Mf(a,b){return Math.sqrt((a.x-b.x)*(a.x-b.x)+(a.y-b.y)*(a.y-b.y))}function _Zg(a,b){return b.x<=a.x&&a.x<=b.x+b.w&&b.y<=a.y&&a.y<=b.y+b.h}function _bu(a,b){return a.left<=b.right&&b.left<=a.right&&a.top<=b.bottom&&b.top<=a.bottom}function _Aj(a,b){let c={x:Math.max(a.x,b.x),y:Math.max(a.y,b.y)};return c.add({w:Math.min(a.x+a.w,b.x+b.w)-c.x,h:Math.min(a.y+a.h,b.y+b.h)-c.y})}
function _el(a,b){let c={x:Math.min(a.x,b.x),y:Math.min(a.y,b.y)};c.w=Math.max(a.x+a.w,b.x+b.w)-c.x;c.h=Math.max(a.y+a.h,b.y+b.h)-c.y;return c}function _ie(a){let b=0;0>=a.w&&0>=a.h?b=Math.sqrt(a.w*a.w+a.h*a.h):0>=a.w?b=-a.w:0>=a.h&&(b=-a.h);return-b||a.w*a.h}function _ls(a,b){return{cols:1,rows:1}.add(a[b]||a["*"])};
;
/* ===== file18.js ===== */
'use strict';function _Rp(c,v,l){function t(a){for(var f=1;a+"_"+f in c;++f);return a+"_"+f}function u(a,f,d){for(let w of a)try{{var b=w;a=f;var e=d;let h=[],x=0;for(let k of b){e=!x++&&e||"."==k[0];q||(q=k);let p=c[k];if(_Jw(p)){let g=u(p,a,e);a=g.str;if(l[k]){let m=l[k]();for(let y of g.nodes)m.addChild(y);h.push(m)}else h.push(...g.nodes)}else{let g=c.blank&&!e?[p,c.blank,p]:[p];for(b=0;b<g.length;++b){let m=g[b]instanceof RegExp?a.match(g[b]):a.startsWith(g[b])?[g[b]]:null;if(!m){if(!b&&1<g.length)continue;
throw 1;}a=a.substr(m[0].length);if(1!=b){a.length<r&&(r=a.length,q=null);l[k]&&h.push(l[k](m[0]));break}}}}var n={str:a,nodes:h}}return n}catch(h){h instanceof Error&&console.error(h)}throw 1;}c=Object.assign({},c);l=Object.assign({},l);for(let a=2;a--;)for(let f in c){let d=c[f];if("string"==typeof d){d=d.replace(/(["'])((?!\1)[^\\]|\\.)*\1/g,b=>{let e=t(f);c[e]=[b.slice(1,-1)];return e});do{var z=d;d=d.replace(/\([^()]+\)/g,b=>{let e=t(f);c[e]=b.slice(1,-1);return e})}while(z!=d);d=d.replace(/\b([\w]+)\s*([*+?])/g,
(b,e,n)=>{b=e+("+"==n?"*":n);c[b]=e+("?"==n?"":" "+b)+" | empty";return("+"==n?e+" ":"")+b});d=d.replace(/\.\s*([\w?*]+)/g,(b,e)=>{b="."+e;c[b]=e;return" "+b});c[f]=d}}for(let a in c)c[a]="string"==typeof c[a]?c[a].trim().split("|").map(f=>f.trim().split(/\s+/)):c[a]instanceof RegExp?RegExp("^(?:"+c[a].source+")",c[a].flags):c[a][0];c.empty=/^/;let q,r=Infinity;return a=>{try{return u([[v]],a)}catch(f){let d=a.length-Math.min(r,a.length+1)+1;throw"Syntax error at position "+d+". Expecting: "+q.match(/^\w+/)[0]+
"\n"+Array(Math.min(d,30)).join(" ")+"v\n"+a.substr(Math.max(0,d-30),60);}}};
;
/* ===== file41.js ===== */
'use strict';function _lu(){return _zo.content.length<_zo.size}function _Lf(a){_zo=void 0===a?{content:"",size:1}:a.content?a:a.add({content:"",size:0})}_Lf(void 0);function _dy(a){_lu()?_yw(_fd)(b=>{_Lf(b);a()}):a()}let _aw=_we(function*(a){if(a-=0)return _os[a]||"";yield b=>_dy(b);return _Jw(_zo.content)?_zo.content.join("\n"):_zo.content});function _yw(a){return b=>{_Lk(_tl,a,c=>b(_ag(c)))}}function _qi(a,b){return c=>{_Lk(_Bf,{timeout:a,format:b},d=>c(_ag(d)))}}
function _Zt(a,b,c=""){return d=>{b&&b!=_fd||(a=_qg(a));_Lk(_Hi,{data:a,fmt:b,[c]:!0},d)}}let _os={};function _It(a,b,c=!1,d){(a-=0)?(_os[a]=(c&&_os[a]||"")+b,d()):_Zt(b,_fd,c?"append":"")(d)}function _qg(a){return a.replace(/([^\r]|^)(?=\n)/g,"$&\r")}function _3r(a){_If(a)(b=>_Zt(btoa(b.content),_Dk)())}function _ag(a){a.format==_Dk&&"string"==typeof a.content&&(a.content=atob(a.content));a.content=_Yi(a.content);return a}
var _4o=function(a){let b=a.indexOf("\x3c!--StartFragment--\x3e");return{fragment:a.slice(b+20,a.lastIndexOf("\x3c!--EndFragment--\x3e")),sourceURL:(a.slice(0,b).match(/SourceURL:([^\n\r]+)/i)||[,""])[1]}},_Ra=function(a,b,c=""){a=_pk(`Version:0.9\nStartHTML:${"@*$&^HTML1"}\nEndHTML:${"@*$&^HTML2"}\nStartFragment:${"@*$&^FRAG1"}\nEndFragment:${"@*$&^FRAG2"}\n${b?"SourceURL:"+b:""}\n<html><head>${c}</head>\n${"<body>\x3c!--StartFragment--\x3e"}${a}${"\x3c!--EndFragment--\x3e</body></html>"}`,"UTF-8",
!1);b=a.indexOf("<body>\x3c!--StartFragment--\x3e");c=a.lastIndexOf("\x3c!--EndFragment--\x3e</body></html>")-1;return _Id(a,"UTF-8").replace("@*$&^HTML1",("0000000000"+b).slice(-10)).replace("@*$&^HTML2",("0000000000"+(c+32)).slice(-10)).replace("@*$&^FRAG1",("0000000000"+(b+26)).slice(-10)).replace("@*$&^FRAG2",("0000000000"+c).slice(-10))};
;
/* ===== file45.js ===== */
'use strict';_Du.menuSpec={mruTabsCurrWin:{name:"MRU tabs, current window",help:"cwMru",value:{type:"TSE",content:"currWinTabsMruOrder",commonOptions:{layout:_Ah("C"),itemsDistrib:["perGroup",20]},rootOptions:{position:"window",alignHorz:_La,alignVert:_8g,menuSystem:"simple"}}},mruTabsCurrWinThumbs:{name:"MRU tabs, curr. win., with thumbs.",help:"cwMruT",value:{type:"TSE",content:"currWinTabsMruOrder",commonOptions:{layout:_Ah("R"),itemsDistrib:["auto"],centerGroups:!0,thumbSize:_Fi,maxItems:20},
rootOptions:{position:"window",alignHorz:_La,alignVert:_8g,menuSystem:"simple"}}},mruTabsAllWins:{name:"MRU tabs, all windows",help:"awMru",value:{type:"TSE",content:"allTabsMruOrder",commonOptions:{layout:_Ah("C"),itemsDistrib:["perGroup",20]},rootOptions:{position:"window",alignHorz:_La,alignVert:_8g,menuSystem:"simple"}}},mruTabsAllWinsThumbs:{name:"MRU tabs, all wins., with thumbs.",help:"awMruT",value:{type:"TSE",content:"allTabsMruOrder",commonOptions:{layout:_Ah("R"),itemsDistrib:["auto"],
centerGroups:!0,thumbSize:_Fi,maxItems:20},rootOptions:{position:"window",alignHorz:_La,alignVert:_8g,menuSystem:"simple"}}},closedTabs:{name:"Closed tabs",help:"clsd",perms:"ses",value:{type:"closedTabs",commonOptions:{layout:_Ah("C")}}},closedTabsThumbs:{name:"Closed tabs with thumbnails",help:"clsdT",perms:"ses",value:{type:"closedTabs",commonOptions:{layout:_Ah("R"),itemsDistrib:["auto"],centerGroups:!0,thumbSize:_Fi,maxItems:20},rootOptions:{position:"window",alignHorz:_La,alignVert:_8g,menuSystem:"simple"}}},
bookmarksTree:{name:"Bookmarks",help:"bkm",perms:"bkm",value:{type:"custom",content:[{type:"bmFolder",content:1},{type:"bmFolder",content:2,sepLine:!0,subMenu:!0}],commonOptions:{layout:_Ah("C")}}}};
{const a={borderWidth:2,paddingHorz:4,paddingVert:4,margin:1};_Du.menuStyle={std:{name:"Standard",value:{itemMaxWidth:300}},light:{name:"Light",value:{bgColor:4043309055,itemStates:[a.sc().add({bgColor:0,txtColor:4261412864,borderColor:0}),a.sc().add({bgColor:4283205620,txtColor:4294967295,borderColor:0}),a.sc().add({bgColor:0,txtColor:4261412864,borderColor:4278190080}),a.sc().add({bgColor:4283205620,txtColor:4294967295,borderColor:4278190080})],itemMaxWidth:300}},dark:{name:"Dark",value:{bgColor:4030742592,
itemStates:[a.sc().add({bgColor:0,txtColor:4294967295,borderColor:0}),a.sc().add({bgColor:4278190080,txtColor:4294967295,borderColor:0}),a.sc().add({bgColor:0,txtColor:4294967295,borderColor:4294967295}),a.sc().add({bgColor:4278190080,txtColor:4294967295,borderColor:4294967295})],itemMaxWidth:300}}}}let _Ck={},_Zk={};function _lk(a){if(!a)return 0;let [,b]=_wh(a);return b?+b:-(Object.keys(_Du.menuSpec).indexOf(a)+1)};
;
/* ===== file50.js ===== */
'use strict';function _Tt(a){if(!a||"string"!=typeof a&&!a.templ)return a;let b=_qy(a.templ?a.templ:a).nodes[0].value;for(let c of b)_dr(c);a={templ:b,regex:a.regex,flags:a.flags,ignoreCase:a.ignoreCase};1==a.templ.length&&"string"==typeof a.templ[0]&&(a=_Kk(a,a.templ[0]));return a}function _Kk(a,b){if(a.regex)try{return new RegExp(b,a.flags||(a.ignoreCase?"i":""))}catch(c){return/.^/}return a.ignoreCase?b.toUpperCase():b}
function _dr(a){if(a&&a.expr)for(let b of a.expr)if(b.args)for(a=0;a<b.args.length;++a)_dr(b.args[a]),b.args[a]=_Tt(b.args[a])}function _wy(a,b=null){if(!a||!a.templ)return a;let c="";for(let d of a.templ)c+=d.expr?_qo(d,b):d;return _Kk(a,c)}function _up(a,b=null){if(!a||!a.templ)return[a];let c=[""];for(let d of a.templ)if(d.expr){a=[];let e=_Ii(_qo(d,b));for(let f of c)for(let g of e)a.push(f+g);c=a}else for(a=0;a<c.length;++a)c[a]+=d;return c}
function _qo(a,b){let c=_ah(a.expr[0],b);for(let e=1;null!=c&&e<a.expr.length;++e){let f=a.expr[e];var d=_ap.hasOwnProperty(f.name)?function(...g){return _Jw(this)?this.map(h=>_ap[f.name].apply(h.toString?h.toString():"",g)):_ap[f.name].apply(this.toString?this.toString():"",g)}:c[f.name];c="function"==typeof d?d.apply(c,(f.args||[]).map(g=>g.expr?_qo(g,b):_wy(g))):d}return void 0===c&&1==a.expr.length?`<${a.expr[0].name}>`:null==c?"(empty)":c}
const _ap={match(a){return(this.match(a)||[""])[0]},matches(a){return this.match(a)||[]},replace(a,b){return this.replace(a instanceof RegExp?a.global?a:RegExp(a.source,"g"+a.flags):RegExp(_3a(""+a),"g"),b)},escape(){return encodeURIComponent(this).replace(/%20/g,"+")},unescape(){return unescape(this)},lines(){return this.trim().split(/\s*\n\s*/)},words(){return this.trim().split(/\s+/)},url(){return new Proxy(new String(_5w(this)),{get:_pe})}};
let _1i,_Bk,_0={},_vg={},_Pf=_we(function*(a){if(null==_0[a]){let b=yield _Vy(_2p,_Dg[a]);_0[a]="string"==typeof b?b:""}return _0[a]}),_bh=_we(function*(a){null==_vg[a]&&(_vg[a]=yield _Vy(_2f,a));return _vg[a]});
var _sp=_we(function*(a){if(!a)return a;const b=/<(\w+)>/g;let c={};a=_Ii(a);for(let d=0;d<a.length;++d){let e=a[d].match(b);if(e){for(let f of e)f=f.slice(1,-1).toLowerCase(),c.hasOwnProperty(f)||(c[f]=_Dg[f]?yield _Pf(f):yield _bh(f));a[d]=a[d].replace(b,(f,g)=>c[g.toLowerCase()])}}return 1==a.length?a[0]:a});
{let a={};var _ah=function(b,c){switch(b.name.toLowerCase()){case "clipboard":if(c=_ji(b.args,0))return _os[c]||"";_lu()&&_Lw.addFunc(_dy);return _zo.content;case "omnibox":return null==_1i&&_na[_4t]&&_Lw.addFunc(_us(function*(){null==_1i&&(_1i=yield _Vy(_nw,_na[_4t]))})),_1i||"";case "selection":return null==_Bk&&_Lw.addFunc(_us(function*(){null==_Bk&&(_Bk=(yield _qi(1E3*(+_ji(b.args,0)||.5))).content||"")})),_Bk||"";case "date":return _8h(new Date,"string"==typeof _ji(b.args,0)?b.args[0]:"Y-M-D");
case "var":return new Proxy(a,{get(d,e){if("string"!=typeof e||_Xt(e,"toString","valueOf"))return d[e];if(d.hasOwnProperty(e)){let f=d[e];delete d[e];return void 0===f?"":f}_Lw.addFunc(_us(function*(){d[e]=yield _ae("",e)}));return" "}});case "dir":return new Proxy(_0,{get(d,e){if("string"!=typeof e||_Xt(e,"toString","valueOf"))return d[e];e=e.toLowerCase();if(!_Dg[e])return"";if(d.hasOwnProperty(e))return d[e];_Lw.addFunc(_Pf(e));return" "}});case "env":return new Proxy(_vg,{get(d,e){if("string"!=
typeof e||_Xt(e,"toString","valueOf")||d.hasOwnProperty(e))return d[e];_Lw.addFunc(_bh(e));return" "}});default:return _gg(c,b.name)}}}function _Jg(){if(null!=_Kt)return _Kt;_Lw.addFunc(_us(function*(){_Kt=(yield _aj(null,_Cg(_zw).usePrevMousePos))||0}));return 0}function _go(a){return a.active&&a.highlighted?a.window.tabs.some(b=>!b.active&&b.highlighted):a.highlighted}let _kg,_Dy;
function _ys(){if(_kg)return _kg;_Dy||(_Dy=!0,_Lw.addFunc(_us(function*(){for(var a={usePrvMsPos:!!_Cg(_zw).usePrevMousePos};;){a=(yield _Vy(_No,a))||{};const b=_Kt=_Or[a.hWnd];let c=[];if("index"in a)c=yield _zg({windowId:b,index:a.index});else if("title"in a&&((c=yield _du(b,a.title))||(c=[yield d=>_Hy(b,d)]),1!=c.length)){a={x:a.x,y:a.y,getIdx:!0};continue}a.group&&c[0]&&c[0].groupId&&(c=yield _zg({windowId:b,groupId:c[0].groupId}));_kg=c.map(d=>_js(d));break}_Dy=!1})));return[]}
let _du=_we(function*(a,b){if(!b)return[];const c=500==b.length;for(;;){var d=b.replace(/\*|\?/g,"\\$&");c&&(d+="*");if((d=yield _zg({windowId:a,title:d}))&&0==d.length){let e=b.lastIndexOf(" - ");if(0<e){b=b.slice(0,e);continue}}return d}}),_3o=_we(function*(a,b){if(!b)return[];for(let d=0;;){d=b.indexOf(" - ",d+1);-1==d&&(d=void 0);var c=b.slice(0,d).replace(/\*|\?/g,"\\$&");d&&(c+="*");c=yield _zg({windowId:a,title:c});if(!d||!c||1>=c.length)return c}});
function _Hd(a){return 0<=_hd.indexOf(a)}let _Jr={};function _ke(a){if(null!=_Jr[a])return _Jr[a];_Jr[a]=null;_Jr.pending||(_Jr.pending=!0,_Lw.addFunc(_us(function*(){yield _za();delete _Jr.pending;_Jr=yield _O(Object.keys(_Jr).map(b=>+b))})));return!1}
function _gg(a,b){if(!a)return"";switch(b){case "url":return new Proxy(new String(_zh(a)),{get:_pe});case "domain":case "mainDomain":case "dirPath":case "path":return _pe(_zh(a),b);case "muted":return a.mutedInfo.muted;case "monitorId":return _wt(a.window);case "window":return new Proxy(a.window,{get(c,d){switch(d){case "underMouse":return c.id==_Jg();case "state":return _Hd(c.id)?"hidden":c.state;case "focused":return _Yw(c);case "alwaysOnTop":return _ke(c.id)}return c[d]}});case "status":return a.discarded?
"discarded":a.status;case "index":return a.index+1;case "selected":case "highlighted":return _go(a);case "openerTabId":return a.openerTabId||_Fp(a.id);case "used":return 0<=_Ft.indexOf(a.id);case "hovered":return 0<=_ys().indexOf(a.id);case "grouped":return 0<a.groupId;case "contType":return"";default:return a[b]}}function _Fp(a){if(a=_He[a])return a in _Yp?a:_Fp(a)}
function _pe(a,b){switch(b){case "protocol":return(new URL(a)).protocol;case "user":return(new URL(a)).username;case "domain":return(new URL(a)).hostname;case "mainDomain":return _Oy((new URL(a)).hostname);case "port":return(new URL(a)).port;case "path":return(new URL(a)).pathname;case "dirPath":return(new URL(a)).pathname.replace(/[^\/]+$/,"");case "query":return new Proxy(new String((new URL(a)).search),{get:_Td});case "fragment":return(new URL(a)).hash}b=a[b];"function"==typeof b&&(b=b.bind(a));
return b}function _Td(a,b){let c=a[b];"function"==typeof c?c=c.bind(a):void 0===c&&"string"==typeof b&&(a=(new URLSearchParams(a.slice(1))).getAll(b),c=1>=a.length?a[0]:a);return c}function _Oy(a){let b=a.match(/[^.]+(?:\.(?:gov|com|org|edu|net|co|mil|eu|ac|info|biz|leg|int|nom|name|gob|web))?\.(?!\d+)[^.]+$/i);return b?b[0]:a}function _sj(a,b){let c=!1,d=Object.keys(_Yp)[0],e=new Proxy(_Yp[d]||{},{get(f,g){g in f&&(!b||"url"!=g)&&(c=!0);return f[g]}});_Mt(0,()=>_wy(_Tt(a),e))(_ay);return c}
let _qy=(()=>{let a={ident:b=>({value:b}),num:b=>({value:+b}),str:b=>({value:_jf(b.slice(1,-1),"nrt'\"\\")}),regexBody:b=>({value:_jf(b.slice(1,-1),"/")}),regexFlags:b=>({value:b}),regex:()=>({value:{regex:!0},addChild(b){this.value[this.value.templ?"flags":"templ"]=b.value}}),argList:()=>({value:[],addChild(b){this.value.push(b.value)}}),exprComp:()=>({value:{},addChild(b){this.value[this.value.name?"args":"name"]=b.value}}),expr:()=>({value:{expr:[]},addChild(b){this.value.expr.push(b.value)}}),
text:b=>({value:b}),templateStr:()=>({value:[],addChild(b){"string"==typeof this.value[this.value.length-1]&&"string"==typeof b.value?this.value[this.value.length-1]+=b.value:this.value.push(b.value)}})};a.exprComp2=a.exprComp;a.text2=a.text;return _Rp({blank:/\s*/,ident:/[a-z_]\w*/i,num:/[+-]?\d+(\.\d*)?/,str:/(["'])((?!\1)[^\\]|\\.)*\1/,regexBody:/\/([^\\\/]|\\.)*\//,regexFlags:/[a-z]{1,10}/i,regex:" regexBody regexFlags? ",value:"str|regex|num|expr",argList:'"(" (value ("," value)*)? ")"',exprComp:"ident argList?",
exprComp2:'"[" value "]" argList?',expr:' exprComp ( ("." exprComp) | exprComp2 )* ',text:/[^<]+/,text2:/<[^<]*/,templateStr:' (text | ( "<" . expr . ">" ) | text2)* '},"templateStr",a)})();
;
/* ===== file52.js ===== */
'use strict';{let m=function(a,b){return a.concat(u(b,a))},u=function(a,b){return a.filter(c=>0>_ki(b,c))},n=function(a,b){return a.filter(c=>0<=_ki(b,c))},p=function(a){let b=a.find(c=>!c.menuId);b&&(a=[b]);return a};const v={[_Si]:_Ef,[_Ce]:_Ef,[_uu]:_Ef,[_9]:_Ce,[_xw]:_Ce,[_Ih]:_Ce,[_9t]:_Ih,[_6p]:_9t,[_Pj]:_9t,[_Go]:_9t,[_2]:_9t,[_5e]:_uu,[_Ru]:_uu,[_Df]:_uu,[_Aa]:_uu,[_pj]:_uu,[_nj]:_uu,[_ju]:_9r,[_gk]:_9r,[_Ch]:_9r,[_et]:_9r,[_Pg]:_9r,[_Nu]:_9r,[_yr]:_9r,[_Te]:_9r,[_Ju]:_9r};let h=function(a,
b){for(;a;a=v[a])if(a==b)return!0},k=function(a){let b={};for(let c=0;c<a.length;++c)for(let d=0;d<a.length;++d)c!=d&&!b[d]&&h(a[c].region,a[d].region)&&(b[c]=!0);return a.filter((c,d)=>!b[d])},w=function(a,b){return h(a,b)?a:h(b,a)?b:void 0},x=function(a,b){let c,d;for(let e of a){a=b[e.swtchId]==e.state;switch(d){case "&":c=c&&a;break;case "|":c=c||a;break;case "=":c=c==a;break;default:c=a}d=e.oper}return c},q=function(a){let b=Object.keys(a.reduce((e,f)=>(e[f.swtchId]=!0,e),{})).sort(),c=Math.pow(2,
b.length),d=[];for(let e=0;e<c;++e){let f=[...e.toString(2)].map(g=>+g).reverse(),l=b.reduce((g,y,z)=>(g[y]=!!f[z],g),{});d[e]=x(a,l)}return{swtchIds:b,results:d}},r=function(a,b){return a.length==b.length?a.every((c,d)=>c==b[d]):!1},A=function*(a){let b=function*(c,d,e){for(;c<a.length;++c){let f=[...d,a[c]];f.length==e?yield f:yield*b(c+1,f,e)}};for(let c=1;c<=a.length;++c)yield*b(0,[],c)},B=function(a,b){return r(a.swtchIds,b.swtchIds)},t=function(a){let b=[];for(let c of a)for(let d=0;d<c.results.length;++d)b[d]=
b[d]||c.results[d];return{swtchIds:a[0].swtchIds,results:b}},C=function(a){let b=[];for(let c of a)c[c.length-1].oper="O",b.push(...c);return b};const D={urlTests:{[0]:a=>a.negate,[1]:m,[2]:n},menuState:{[0]:a=>a.negate,[1]:function(a,b){return p(m(a,b))},[2]:function(a,b){return p(n(a,b))}},mouseOver:{[0]:a=>"not"==a.oper,[1]:function(a,b){return k(a.concat(b))},[2]:function(a,b){a=k(a);b=k(b);let c=[];for(let d of a)for(let e of b)a=w(d.region,e.region),a==d.region?c.push(d):a==e.region&&c.push(e);
return c}},swtchState:{[0]:()=>!1,[1]:function(a,b){b=b.filter(d=>d.swtchId);if(b.length){let d=q(b);var c=a.map(q).filter(e=>B(e,d));for(let e of A(c)){c=t(e);if(r(c.results,d.results))return a;if(t([c,d]).results.every(f=>f))return null}a.push(b)}return a},[2]:()=>[]}};var _oh=function(a,b,c,d){const e=D[a];if(null!==b[a]){let f=(d[a]||[]).filter(l=>!e[0](l));b[a]=f.length?e[1](_lf(b,a,[]),f):null}if(!c[a]||c[a].length)b=(d[a]||[]).filter(e[0]),c[a]=c[a]?e[2](c[a],b):b},_Ni=function(a){const [b,
c]=a;for(let d of["urlTests","menuState","mouseOver"])b[d]=(b[d]||[]).concat(c[d]||[]);b.swtchState&&(b.swtchState=C(b.swtchState));return b}};
;
/* ===== file59.js ===== */
'use strict';const _Et={oper:"filter",params:{tgtExpr:"<windowId>",refExpr:"<windowId>"}},_te={oper:"sort",params:{order:"mru",desc:!0}};
_Du.tse={other:{value:[]},currentTab:{name:"Current tab",help:"cur",value:""},prevUsedTab:{name:"Previous tab",help:"prv",value:[_Et,_te,{oper:"filter",params:{pos:"next",wrap:!0}}]},nextUsedTab:{name:"Next tab",help:"nxt",value:[_Et,_te,{oper:"filter",params:{pos:"prev",wrap:!0}}]},prevUsedTabAnyWin:{name:"Previous tab (any win.)",help:"prvAll",value:[_te,{oper:"filter",params:{pos:"next",wrap:!0}}]},nextUsedTabAnyWin:{name:"Next tab (any win.)",help:"nxtAll",value:[_te,{oper:"filter",params:{pos:"prev",
wrap:!0}}]},activeTabs:{name:"Active tabs",help:"act",value:[{oper:"filter",params:{tgtExpr:"<active>",refExpr:"true"}}]},activeTab:{name:"Active tab",help:"act0",value:[{oper:"filter",params:{tgtExpr:"<active>",refExpr:"true"}}]},openerTab:{name:"Opener tab",help:"opnr",value:[{oper:"filter",params:{tgtExpr:"<id>",refExpr:"<openerTabId>"}}]},leftTab:{name:"Left tab",help:"lft",value:[_Et,{oper:"filter",params:{pos:"prev"}}]},leftTabWrap:{name:"Left tab (wrap)",help:"",value:[_Et,{oper:"filter",params:{pos:"prev",
wrap:!0}}]},rightTab:{name:"Right tab",help:"rgt",value:[_Et,{oper:"filter",params:{pos:"next"}}]},rightTabWrap:{name:"Right tab (wrap)",help:"",value:[_Et,{oper:"filter",params:{pos:"next",wrap:!0}}]},firstTab:{name:"Leftmost tab",help:"",value:[_Et,{oper:"slice",params:{from:1,to:1}}]},lastTab:{name:"Rightmost tab",help:"",value:[_Et,{oper:"slice",params:{from:-1,to:-1}}]},newestTab:{name:"Newest tab",help:"nwst",value:[_Et,{oper:"sort",params:{order:"creation"}},{oper:"slice",params:{from:-1,to:-1}}]},
hoveredTabs:{name:"Hovered tab",help:"hvr",value:[{oper:"filter",params:{anyHvrd:!0}}]},allLeftTabs:{name:"All tabs to the left",help:"",multi:1,value:[_Et,{oper:"filter",params:{pos:"before"}}]},allRightTabs:{name:"All tabs to the right",help:"",multi:1,value:[_Et,{oper:"filter",params:{pos:"after"}}]},eventTabs:{name:"Event tab",help:"evt",value:[{oper:"filter",params:{evtTabs:!0}}]},highlighted:{name:"Selected tabs",help:"hlt",multi:1,value:[_Et,{oper:"filter",params:{tgtExpr:"<highlighted>",refExpr:"true"}}]},
pinnedTabs:{name:"Pinned tabs",help:"pin",multi:1,value:[_Et,{oper:"filter",params:{tgtExpr:"<pinned>",refExpr:"true"}}]},audibleTabs:{name:"Audible tabs",help:"aud",multi:1,value:[{oper:"filter",params:{tgtExpr:"<audible>",refExpr:"true"}}]},nonMinimTabs:{name:"Non-minimized tabs",help:"vsbl",multi:1,value:[{oper:"filter",params:{tgtExpr:"<window.state>",refExpr:"minimized",negate:!0}},{oper:"filter",params:{tgtExpr:"<window.state>",refExpr:"hidden",negate:!0}}]},otherTabs:{name:"Other tabs (curr. window)",
help:"othr",multi:1,value:[_Et,{oper:"filter",params:{tgtExpr:"<active>",refExpr:"false"}}]},otherTabsAllWins:{name:"Other tabs (all windows)",help:"othrAll",multi:1,value:[{oper:"filter",params:{tgtExpr:"<id>",refExpr:"<id>",negate:!0}}]},currWinTabs:{name:"All tabs (curr. window)",help:"",multi:1,value:[_Et]},currWinTabsMruOrder:{name:"All tabs (curr. window, MRU order)",help:"curWmru",multi:1,value:[_Et,_te]},allTabs:{name:"All tabs (all windows)",multi:1,value:[]},allTabsMruOrder:{name:"All tabs (all windows, MRU order)",
help:"allMru",multi:1,value:[_te]}};_Du.tse.add({righTab:_Du.tse.rightTab,righTabWrap:_Du.tse.rightTabWrap});
function _My(b){if(!b.ufOper)return b;b.oper=b.ufOper;delete b.ufOper;let a=b.params||{};"string"==typeof a.refTab&&(a.refTab=_ty(_gh(a.refTab,"tse").value));"string"==typeof a.tabSet&&(a.tabSet=_ty(_gh(a.tabSet,"tse").value));if(a.compOper&&a.compOper.in("contains","starts","ends")){let d=("starts"==a.compOper?"^":"")+_Bi(a.refExpr||"","^$\\.*+?()[]{}|")+("ends"==a.compOper?"$":"");a.refExpr={templ:d,regex:!0}}delete a.compOper;a.tgtExpr&&(a.tgtExpr.in("prev","next","before","after")?(a.pos=a.tgtExpr,
delete a.tgtExpr):"openerTabId"==a.tgtExpr?(a.tgtExpr="<openerTabId>",a.refExpr="<id>"):"windowId"==a.tgtExpr?a.tgtExpr=a.refExpr="<windowId>":"groupId"==a.tgtExpr?a.tgtExpr=a.refExpr="<groupId>":"favList"==a.tgtExpr?delete a.tgtExpr:"evtTabs"==a.tgtExpr&&(delete a.tgtExpr,a.evtTabs=!0));"reverse"==a.order&&(b.oper=a.order);return b}const _M=new WeakMap;let _eg=0;
function _zy(b,a=!0){"string"==typeof b&&(b=_gh(b,"tse").value);if(!b)return b;if(a&&_M.has(b))return _M.get(b);const d=b;b=_ty(b);for(let c of b)_My(c),"filter"==c.oper?(c.params.tgtExpr=_Tt(c.params.tgtExpr),c.params.refExpr=_Tt(c.params.refExpr),c.params.refTab=_zy(c.params.refTab,!1)):"sort"==c.oper?c.params.order=_Tt(c.params.order):"addSet"==c.oper?(++_eg,c.params.tabSet=20<_eg?[]:_zy(c.params.tabSet,!1),--_eg):"groupBy"==c.oper&&(c.params.expr=_Tt(c.params.expr));a&&_M.set(d,b);return b}
function _gt(b,a){return _ou(_zy(b),a)}function _ou(b,a){if(!b)return _Np?[[_Np]]:[[]];a=a?a.slice():[_Gk];a[0]||(a[0]=[]);for(let d of b)d.oper&&(a=_kj(a,d.oper,d.params),a[0]||(a[0]=[]));return a}function _qd(b){return[...new Set(_Ii(...b))]}function _Vp(b,a,d){a=Math.max(1,(a||1)+(0>a?b.length+1:0))-1;d=Math.max(a,(d||b.length)+(0>d?b.length+1:0));return b.slice(a,d)}
function _kj(b,a,d){if("mergeGrp"==a)return[_qd(b)];if("addSet"==a){var c=_ou(d.tabSet);return d.replace?c:b.concat(c)}if("slice"==a&&d.groupWise)return _Vp(b,d.from,d.to);if("reverse"==a&&d.groupWise)return b.slice().reverse();c=[];a=_pp[a];for(let e of b)c.push(...e.length?a(e,d):[]);return c}const _pp={filter:_Mg,posFilter:_Mg,sort:_qf,groupBy:_Nj,reverse:b=>[b.slice().reverse()],slice:(b,a)=>[_Vp(b,a.from,a.to)]};
function _qf(b,a){let d=a.order;a=a.desc;switch(d){case "normal":b=_hg(b,_Gk);break;case "mru":b=_hg(b,_Ft,!0);break;case "zOrder":b=_Sd(b);break;case "creation":b=_hg(b,_ea,!0);break;default:let c={};for(let e of b)c[e]=_wy(d,_Yp[e]);b=b.slice().sort((e,f)=>{e=c[e];f=c[f];return e==f?0:e<f?-1:1})}a&&b.reverse();return[b]}
function _Sd(b){if(_ko)return _Lw.addFunc(_us(function*(){_ko&&(yield _Vy(_Yj),_ko=!1)})),b.slice();let a=0;for(let d of _ts)_cd[d].zIndex=a--;_Ft=_hg(_Gk,_Ft,!0);for(let d of b)_Yp[d].mruIndex=_Ft.indexOf(d);return b.slice().sort((d,c)=>{let e=_Yp[d].window.zIndex-_Yp[c].window.zIndex;return e?e:_Yp[d].mruIndex-_Yp[c].mruIndex})}
function _Nj(b,a){let d=_la();for(let c of b){if("overlapArea"==a.expr){let e=_df(_Yp[c].window);b=0;for(let [,f]of d){let h=_df(_Yp[f[0]].window);if(_Zg(_il(e),h)||_Zg(_il(h),e))break;++b}}else b=_wy(a.expr,_Yp[c]);d[b]||(d[b]=[]);d[b].push(c)}return[...d].map(([,c])=>c)}let _hu;function _st(){if(_hu)return _hu;_Lw.addFunc(_us(function*(){_hu=yield _Vy(_3f,{usePrvMsPos:!!_Cg(_zw).usePrevMousePos})}));return{}}
function _3u(b=!1,a=!1,d=!1){const c={TSE:g=>_Ii(..._gt(g)),tabList:g=>g,tab:g=>[g]};let e=[],f=g=>{(g=_Tu(g))&&g.type in c&&e.push(...c[g.type](g.content))},h=_st();b&&h.marked&&f(h.marked);a&&h.hilited&&f(h.hilited);d&&h.hovered&&f(h.hovered);return[...new Set(e)].filter(g=>g in _Yp)}
function _Mg(b,a){let d=[],c;if(a.favList)c=_Mo[a.favList]||[];else if(a.evtTabs)c=_Eh(_zw);else if("menuSeltn"==a.tgtExpr)c=_3u(a.marked,a.hilited,a.hovered);else if(a.anyHvrd)c=_3u(!1,!1,!0),c.length||(c=_ys(),c.length||(c=[_ji(_cd,_Jg(),"activeTab","id")]));else if("grpSize"==a.tgtExpr)return a.min<=b.length&&b.length<=a.max?[b]:[];if(c)d=b.filter(f=>0<=c.indexOf(f)==!a.negate);else{var e=_Yp[a.refTab?_ou(a.refTab,[b])[0][0]:_Np];if(e)if(a.pos)d=_xy(b,a,e.id),a.negate&&(d=b.filter(f=>-1==d.indexOf(f)));
else{e=_wy(a.refExpr,e);for(let f of b)b=_wy(a.tgtExpr,_Yp[f]),(b instanceof RegExp?b.test(e):e instanceof RegExp?e.test(b):String(b)==String(e))==!a.negate&&d.push(f)}}return[d]}function _xy(b,a,d){var c=b.indexOf(d);if(0>c)return[];b=[b.slice(0,c),b.slice(c+1).reverse()];c=a.pos.in("before","prev");let e=b[+!c].reverse();a.addRef&&e.unshift(d);a.wrap&&(e=e.concat(b[+c]));a.pos.in("prev","next")&&(e=e.slice(0,1));return e};
;
/* ===== file89.js ===== */
'use strict';var _Bg,_Md;
{let a={};var _Sa=_we(function*(b,d,c=0){let e=b.id,f=a[e]=Math.random();"normal"!=b.state&&("maximized"==b.state&&(yield _Vy(_Gs,{win:_na[e]|0})),yield _oa([e],!0),b=(yield p=>_Ms(e,!1,p))||b);let g=_8j(b);b=_Ug(_df(b),1/g);d={}.add(b,d);var l=d.x-b.x,h=d.y-b.y,m=d.w-b.w,q=d.h-b.h,k=Math.max(Math.abs(l),Math.abs(h),Math.abs(m),Math.abs(q));let r=25;c=c||r;k=Math.round(k/Math.max(1,k/c*r));const t=p=>n=>_Yk.windows.update(e,_1w(_Ug(p,-1/g)),n);if(2>=k)g=_2i(_D(d)),yield t(d);else{l/=k;h/=k;m/=k;q/=
k;r=c/k;c=-2/(k-1);for(let p=0,n=2;a[e]==f;n+=c)if(b.x+=l*n,b.y+=h*n,b.w+=m*n,b.h+=q*n,yield t(b),++p<k)yield _za(r);else{b.includes(d)||(g=_2i(_D(d)),yield t(d));break}}})}function _2i(a){return((_Zw[a]||{}).dpiX||96)/96}function _8j(a){return _2i(_wt(a))}function _3s(a,b){const d=_8j(a);return 1==d?_df(a).includes(b):Math.max(Math.abs(b.x-a.left*d),Math.abs(b.y-a.top*d),Math.abs(b.w-a.width*d),Math.abs(b.h-a.height*d))<=Math.max(2,10/Math.pow(d,2))}
function _wt(a){a.monitorId||(a.monitorId=_D(_df(a)));return a.monitorId}function _D(a){let b=-Infinity,d=0;for(let c in _Zw){let e=_ie(_Aj(a,_df(_Zw[c].bounds)));e>b&&(b=e,d=c)}return d}function _Ao(a,b){let d=Math.max(1,Math.round(a.w/b.w))*b.w,c=Math.max(1,Math.round(a.h/b.h))*b.h;return{x:b.x+b.w*Math.round((a.x-b.x+a.w/2-d/2)/b.w),y:b.y+b.h*Math.round((a.y-b.y+a.h/2-c/2)/b.h),w:d,h:c}}
function _gf(a,b){b in _Zw||(b=Object.keys(_Zw)[0]);let d=_Zw[b].workArea;a=_ls(a,b);return{x:d.left,y:d.top,w:Math.round(d.width/a.cols),h:Math.round(d.height/a.rows)}}function _8y(a){let b=0;for(let d in _Zw){let c=_ie(_Aj(a,_df(_Zw[d].workArea)));0<c&&(b+=c)}return b}function _3w(a,b,d){let c="x"==d?"w":"h";return(Math.min(a[d]+a[c],b[d]+b[c])-Math.max(a[d],b[d]))/Math.min(a[c],b[c])}
function _i(a,b,d,c){var e=b[c]-a[c];e/=Math.abs(e);for(a={}.add(a);;){let f=_8y(a)/_ie(a),g=_3w(d,a,c);if(.99<f||.99<g)break;a[c]+=e*b["x"==c?"w":"h"]}return a}function _2r(a,b,d){a={}.add(a);let c={}.add(a),e=0,f=!1;for(;;){let g=_8y(c)/_ie(c);if(.99<g){a.add(c);break}if(g>e)a.add(c),e=g;else if(f)break;else f=!0,c.add(a);c[d]-=b[d];f&&(c["w"==d?"x":"y"]+=b[d])}return a}
function _Xe(a,b,d,c){let e=_D(a),f=_gf(b,e);d=d?_gf(b,d):f;a=_Ao(a,f);let g=a.sc();for(let h of["x","y","w","h"]){let m=c[h]||{};if("val"in m){let q=+m.abs?"x"==h?d.x:"y"==h?d.y:0:a[h];var l=+m.abs?d:f;l=h.in("x","w")?l.w:l.h;a[h]=q+m.val*l;h.in("w","h")&&0>=a[h]&&(a[h]=l)}}a.includes(g)||(e=_D(a),f=_gf(b,e),a=_Ao(a,f));if(!_Zw[e])return _Ot("badMonitorId",{monId:e,rect:a,MONITORS:_Zw}),a;b=_df(_Zw[e].workArea);a=_i(a,f,b,"x");a=_i(a,f,b,"y");a=_2r(a,f,"w");return a=_2r(a,f,"h")}
function _Mr(a,b){return _ji(_Zw,a||_D(b),"workArea")||{left:0,top:0}}function _ey(a,b,d){a=a.sc();b=_Mr(b,a);for(let c of["x","y","w","h"]){let e=d[c]||{};if("val"in e){let f="x"==c?b.left:"y"==c?b.top:0;a[c]=(+e.abs?f:a[c])+e.val;"w"==c&&(a[c]=Math.max(100,a[c]));"h"==c&&(a[c]=Math.max(25,a[c]))}}return a}
function _Xr(a,b,d){a=a.sc();b=_Mr(b,a);for(let c of["x","y","w","h"]){let e=d[c]||{};if("val"in e){let f="x"==c?b.left:"y"==c?b.top:0,g=a[c.in("x","w")?"w":"h"];a[c]=(+e.abs?f:a[c])+g*e.val/100;"w"==c&&(a[c]=Math.max(100,a[c]));"h"==c&&(a[c]=Math.max(25,a[c]))}}return a}
function _ws(a){let b=_gh(a.gridLayout,"gridLayout").value,d=_ls(b,a.baseMonitor),c=+a.cols||+d.cols,e=+a.rows||+d.rows;return[function*(){let f=0,g=0;for(;;)yield _Xe({x:1,y:1,w:1,h:1},b,a.baseMonitor,{x:{abs:1,val:(a.x||0)+f},y:{abs:1,val:(a.y||0)+g},w:{abs:1,val:1},h:{abs:1,val:1}}),++f==c&&(f=0,++g==e&&(g=0))}(),c*e]}_Du.gridLayout={grid2x2:{name:"2 x 2 grid",value:{"*":{cols:2,rows:2}}},grid2x1:{name:"2 x 1 grid",value:{"*":{cols:2,rows:1}}},grid3x1:{name:"3 x 1 grid",value:{"*":{cols:3,rows:1}}}};
let _O=_we(function*(a){a=yield _Vy(_6f,yield _1h(a));let b={};for(let [d,c]of a)b[_Or[d]]=c;return b});
;
/* ===== file93.js ===== */
'use strict';function _ba(c,a){return new Date(c.replace(".","-"))<=new Date(a.replace(".","-"))}let _ad=_we(function*(){let c=yield _ru("trigActList"),a={totalTrigActs:c.length,enabledTrigActs:0,usedActions:[]};for(let [,b]of c){b.disabled||++a.enabledTrigActs;for(let [d,e,f]of _Dr(b.actions||{}))"action"!=d||f.keyId||f.conds||a.usedActions.add(e)}return a});
function _uf(c){let a=["LOCAL","errorEvts",c];_ru(...a)(b=>{b||(b={});const d=Date.now()/1E3/60/60/24|0;b[d]=(b[d]||0)+1;for(let e in b)6<d-e&&delete b[e];_Mi(a,b,0)})}function _dk(){return c=>{let a=["LOCAL","errorEvts"];_ru(...a)(b=>{let d={};b||(b={});const e=Date.now()/1E3/60/60/24|0;for(let [f,h]of b){let g=0;for(let [k,l]of h)6<e-k?delete h[k]:g+=l;d[f]=g?g/Object.keys(h).length:g}_Mi(a,b,0);c(d)})}}
function _F(c,a){_ba(c,a)&&_ti(function*(){for(var b=1;5>b;++b){var d=yield _4u(_ne,yield _3t(_7i,"binary"));if(0==d)break;yield _za(5E3)}_Ot("NH0-update",{error:d,n:b})})}function _Ye(c){2E3<c&&setTimeout(()=>{let a=_j("NHInitData")||{cnt:0,avg:0,max:0,from:Date.now()};a.avg=(c+a.avg*a.cnt)/(a.cnt+1);a.max=Math.max(c,a.max);++a.cnt;let b=(Date.now()-a.from)/864E5;5<b&&(_Ot("NHInitData",a.sc().add({days:b})),a=void 0);_9k("NHInitData",a)})};
;
/* ===== file62_mv3.js ===== */
'use strict';try{_Yk.browserAction&&_Yk.browserAction.onClicked.addListener(()=>{_ru("brwrAction","trigActId")(a=>{a&&_ek?_6y(a):_sh()})})}catch(e){}_Yk.windows.getLastFocused({populate:!0,windowTypes:_Ge},a=>{_4t=_ji(a,"id");_Np=_js(_ji(a,"tabs",0)||{})});_Yk.tabs.onCreated.addListener(_Zf);
function _Zf(a){try{__acInvalidateEnumCache()}catch(e){}let b=a.id=_js(a);_ea.push(b);_Yp[b]=a;a.openerTabId&&(_He[b]=a.openerTabId,Object.keys(_He).length.in(50,75,100,150,200,300)&&_Fu(()=>{for(let c in _He)(_He[c]=_gg(_Yp[c],"openerTabId"))||delete _He[c];for(let c in _He)c in _Yp||delete _He[c]}));a.active||_0k(b,a.windowId);_Wo(_Ui,b)}
{let a=_so(400,_5s);_Yk.tabs.onRemoved.addListener(b=>{try{__acInvalidateEnumCache()}catch(e){}b==_Np&&(_Np=null);_0k(b,0);_ea.remove(b);_Ft.remove(b);delete _da[b];delete _Hs[b];_dg.push({id:b,time:Date.now()/1E3});a();_Wo(_5k,b);_Fy&&(_m[b]=_zh(_Yp[b]),setTimeout(()=>{delete _m[b]},3E3))})}function _Cp(a,b,c){b=a.indexOf(b);~b&&(a[b]=c)}function _ew(a,b,c){b in a&&(a[c]=a[b],delete a[b])}let _se;
// Tab replacement
_Yk.tabs.onReplaced.addListener((a,b)=>{_Lk(_Mu,[b,a]);_Np==b&&(_Np=a);_Cp(_ea,b,a);_Cp(_Ft,b,a);_ew(_Yp,b,a);_ew(_da,b,a);_ew(_Hs,b,a);_ew(_He,b,a);for(let [c,d]of _He)d==b&&(_He[c]=a);for(let [,c]of _Mo)_Cp(c,b,a);_se||(_se={});_se[b]=a});
// Tab activation: track active tab per window
// AC-MV3 FIX (2026-08-08): `_cd[c]` may be undefined when the native is
// dead (window enum never ran — _cd stays empty) → `e.activeTab=f` threw
// "Cannot set properties of undefined (setting 'activeTab')" (user VM
// 00:18, right after openOptionsPage from Emergency Repair). Bail out
// early; the window gets tracked once the enum populates _cd.
{let a=0;_Yk.tabs.onActivated.addListener(({tabId:b,windowId:c})=>{var d=Date.now()-0;_1f(c,b,d);(d=c==_4t)&&(_Np=b);const e=_cd[c];if(!e)return;let f=_Yp[b];f||(f=_Yp[b]={id:b,windowId:c,window:e});const g=_Yw(e);_Vg[b]&&1E3<Date.now()-a&&(delete _Vg[b],g&&"about:blank"==_zh(f)&&(_Lk(_Dt,[_Yo,_Yo|_mk,_cs,_Uo,_Uo|_mk,_cs|_mk,_ye,_ye|_mk]),a=Date.now()));c=_ji(e,"activeTab","id");/* AC-MV3 FIX (2026-08-08): keep _Yp[].active flags in sync with reality — _Ph skips activation when e.active is true, and the flag was only refreshed by _Fu (window enum). A stale active=true on a previously-active tab made wrap transitions (rightTabWrap/leftTabWrap) skip that tab AND left _Np stale → the next trigger targeted the same tab → skipped wheel step. Reset the old activeTab's flag here and set the new one (onActivated is the source of truth). */c&&_Yp[c]&&(_Yp[c].active=!1);e.activeTab=f;f.active=!0;_qp(b,!d);c!=b&&(_Wo(_4r,c),g&&_Wo(_Ed,c));setTimeout(()=>{_Wo(_pw,b);g&&_Wo(_vp,b)},80)})}let _kk;
function _au(a,b){_kk&&(3E3>Math.abs(Date.now()-_kk)&&b.startsWith("https://www.google.com/url?q=")&&(b=decodeURIComponent(b.substr(29)),_wj(a,{code:`location.replace(${JSON.stringify(b)}) ; document.body.style.opacity=0`})()),_kk=0)}
// Tab URL/status updates
{let a={},b;_Yk.tabs.onUpdated.addListener((c,d)=>{let e="loading"==d.status?_oe:"complete"==d.status?_Fd:d.discarded?_oi:d.audible?_I:!1===d.audible?_Iw:0;if(e==_oi){if(c==b){b=null;return}b=c}d.url&&(c==_Np&&_Ja(d.url),_lf(_Yp,c).url=d.url,_kk&&_au(c,d.url),_Wo(_Gp,c));if(e){e==_oe&&c in _da&&(_Hs[c]=Date.now(),_Yk.tabs.getZoom(c,f=>{_yd(f,2)!=_da[c]&&_hr(c,_da[c],!0)}));if(e==_oe){a[c]=setTimeout(()=>{delete a[c];_Wo(e,c)},10);return}if(e==_Fd&&a[c]){clearTimeout(a[c]);return}_Wo(e,c)}_5g&&d.favIconUrl&&
(d=_ig(_zh(_Yp[c])),delete _7o[d],_Zs(d)(_ay));e==_Fd&&_rr&&_Lk(_Ww,{tabId:c});e==_Fd&&((new URL(_zh(_Yp[c]))).hostname.in(_mo,_9n)||"file:"==(new URL(_zh(_Yp[c]))).protocol&&_id)&&_Zr(c)})}
function _Zr(a){try{_Yk.scripting.executeScript({target:{tabId:a},world:"ISOLATED",injectImmediately:true,func:b=>{try{let c=d=>{try{if(d&&chrome&&chrome.runtime&&chrome.runtime.sendMessage)chrome.runtime.sendMessage({[d.value]:decodeURI(d.closest("a").href)})}catch(e){/* stale/revoked context after an extension reload — the NEW injection handles the event */}};if(!window.__acBridge){window.__acBridge=1;addEventListener("webSettgs",d=>{try{c(d.target)}catch(e){}});console.log("[AC-BRIDGE] installed ver="+b+" url="+location.href)}let el=document.querySelector("ACtlExt");if(!el){el=document.createElement("ACtlExt");(document.head||document.documentElement).appendChild(el)}el.setAttribute("ver",b);try{c(document.querySelector("a [value=redirSttgs]"))}catch(e){}}catch(e){console.error("[AC-BRIDGE] error: "+(e&&e.message||e))}},args:["2025.4.22"]}).then(()=>{console.log("[AC-SITE] bridge injected into tab "+a)}).catch(e=>{console.error("[AC-SITE] bridge injection FAILED tab "+a+": "+(e&&e.message||e))})}catch(e){console.error("[AC-SITE] bridge injection THREW tab "+a+": "+(e&&e.message||e))}}
// Tab attached to different window
_Yk.tabs.onAttached.addListener((a,b)=>{try{__acInvalidateEnumCache()}catch(e){}_lf(_Yp,a).windowId=b.newWindowId});
try{_Yk.tabs.onMoved&&_Yk.tabs.onMoved.addListener(()=>{try{__acInvalidateEnumCache()}catch(e){}})}catch(e){}

// Window event handlers
_Yk.windows.onFocusChanged.addListener(a=>{_na[a]||!_cd[a]&&!_Ld[a]||(_Ld[a]&&delete _Ld[a],_8u([a])())});
_Yk.windows.onCreated.addListener(_yh);
function _yh(a){try{__acInvalidateEnumCache()}catch(e){}a.cTime=Date.now();clearTimeout(_6i);_n.push(a.id);_cd[a.id]=a;a.state.in("normal","maximized")&&(a.prevState=a.state);_8u([a.id])();_Wo(_wf,a.id)}
_Yk.windows.onRemoved.addListener(_q);
function _fy(a){_n.remove(a);_hd.remove(a);_0o(a,null);delete _cd[a];a==_4t&&_Yk.windows.getLastFocused({windowTypes:_Ge},b=>_4t=_Aw()?null:b.id)}
function _q(a){try{__acInvalidateEnumCache()}catch(e){}_fy(a);_Wo(_Ff,a)}
// Display change
_Yk.system.display&&_Yk.system.display.onDisplayChanged.addListener(()=>{_Sf(()=>_iy())});
// Update available + idle
{let a;_Yk.runtime.onUpdateAvailable.addListener(()=>{_2u(2)&&_co(2);a=!0});_Yk.idle.onStateChanged.addListener(b=>{"active"!=b&&setTimeout(()=>_Yk.idle.queryState(60,c=>{"active"!=c&&(a?_co(2):!_mw()&&_dh&&864E5<Date.now()-_dh?_co(1):_r||_Lk(_Na))}),1E3*(15*Math.random()+5)|0)})}
// Sessions
if(_Yk.sessions){let a=_Yk.sessions.onChanged;a.addListener(_ay);a.removeListener(_ay)}
// Context menu
_Yk.contextMenus.onClicked.addListener(_cg(function*(a){if("reloadExtn"==a.menuItemId){a=yield _Vy(_ya);let b=yield _Vt(),c={allWinIds:b.map(d=>d.id),idToHndl:_na,hndlToId:_Or,actionQueue:_2y};a&&!a.actWinMine&&(c.focusedId=(b.filter(d=>d.focused)[0]||{}).id,c.lastFocusId=((yield d=>_Yk.windows.getLastFocused({windowTypes:_Ge},d))||{}).id,c.focusedId==c.lastFocusId&&(delete c.lastFocusId,_na[c.focusedId]==a.focusWin&&delete c.focusedId),c.hijackedWins=Object.keys(_Ld));_9k("diagnostics",c.add(a));
_co(1,!0)}else a.menuItemId.startsWith("binSwtch")&&_2t(a.menuItemId,a.checked)}));
// Extension installed/updated
_Yk.runtime.onInstalled.addListener(_cg(function*(a){if("update"==a.reason&&"2025.4.22"!=a.previousVersion){yield _Eu.wait();let b=yield _ad();b.errorCount=yield _dk();_Ot("update",b.add({prevVersion:a.previousVersion}));_F(a.previousVersion,"2021.4.5")}}));
// External messages
_Yk.runtime.onMessageExternal.addListener((a,b,c)=>{b=_gj.indexOf(b.id);if(0<=b)switch(a){case "TBBtnInit":_ve(b);break;case "TBBtnClick":_Wo(_At+b),c(!0)}});
// Initialize switches
_Oo(_Du);
;
/* ===== mv3_native_shim.js ===== */
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
;
/* ===== file26.js ===== */
'use strict';{let v=new _Wf,z;var _4=_cg(function*(){_8a(_Du.menuStyle);_8a(_if.menuStyle);_Lk(_wr,[yield _Zs(yield _Fh("/res/swtchOff.svg",16,16)),yield _Zs(yield _Fh("/res/swtchOn.svg",16,16))]);_ij(yield _Fh("/res/actionIcon.svg",16,16),a=>z=a);v&&v.send()});try{_4()}catch(e){try{console.warn("[AC-MV3] file26 init deferred (no DOM yet):",e&&e.message)}catch(_){}}var _Tu=function(a,b=_Ck.items){return b&&b[a]};let A=_we(function*(a,b,e){let d=_Ck.items,h=d.length,k=[];var g=0;let l=b.commonOptions||{};const n=l.withPreviews?_Fi:l.thumbSize;var f=l.sc().del("maxItems"),m=b.sc().keep("break","sepLine");
const q=f.noTitles;if(b.type.in("TSE","tabGroups")){let c="TSE"==b.type?yield _ai(e,_gt,b.content):b.content;for(let p of c){const r=!g++;k.push({noTitle:q,title:p.length+" tabs",icon:"res/tabs.png",subMenu:!0,itemType:_gk}.add(r?m:null));d.push({type:"tabList",content:p,commonOptions:f}.add(r?m:null))}1==c.length&&(b=d.pop(),k=[],g=0)}if("tabList"==b.type)for(let c of b.content)f={noTitle:q,title:_Yp[c].title,icon:_ig(_zh(_Yp[c])),itemType:_ju},0==g++&&f.add(m),n&&f.add({previewId:c,thumbSize:n}),
k.push(f),d.push({type:"tab",content:c});else if(b.type.in("closedTabs","closedWin")){a="closedWin"==b.type?b.content.tabs:_Yk.sessions?(yield c=>_Yk.sessions.getRecentlyClosed(c)).map(c=>c.tab||c.window):[];for(let c of a)a={noTitle:q,title:c.tabs?c.tabs.length+" tabs":c.title,icon:c.tabs?"res/tabs.png":_ig(c.url),subMenu:c.tabs?!0:void 0,itemType:c.tabs?_Pg:_et},0==g++&&a.add(m),n&&!c.tabs&&a.add({previewId:+c.sessionId,thumbSize:n}),k.push(a),d.push({type:c.tabs?"closedWin":"closedTab",content:c,
commonOptions:c.tabs?f:void 0})}else if(b.type.in("bmFolder","bmSubFldr")){a=_Yk.bookmarks&&(yield c=>_Yk.bookmarks.getChildren(b.content+"",c))||[];for(let c of a)k.push({noTitle:q,title:c.title,icon:c.url?_ig(c.url):"res/folder.png",subMenu:!c.url,itemType:c.url?_Nu:_yr}.add(g++?null:m)),d.push({type:c.url?"bookmark":"bmSubFldr",content:c.id,commonOptions:c.url?void 0:f})}else if("custom"==b.type){g=new x;for(let c of b.content)if(g=g.addNeighbor(1),c.subMenu||c.type.in("custom","action","switch")){let p,
r,w,t;if("TSE"==c.type)p=_gh(c.content,"tse").name||"(Unnamed tab selection)",r="res/tabs.png",w=!0,t=y(c.type);else if("closedTabs"==c.type)p=c.title||"Closed tabs",r="res/tabs.png",w=!0,t=y(c.type);else if("custom"==c.type)p=c.title||"(Unnamed submenu)",w=!0;else if("bmFolder"==c.type){if(m=(_Yk.bookmarks&&(yield E=>_Yk.bookmarks.get(c.content+"",E))||[])[0])p=m.title,r="res/folder.png",w=!0,t=y(c.type)}else if("action"==c.type)(m=yield _ru("trigActList",c.content))&&!m.disabled&&(p=m.title||"(Unnamed action)",
r=m.icon&&m.icon.img||z,t=_Te);else if("switch"==c.type&&c.content){p=_gh(c.content).name;t=_Ju;var F=+_wh(c.content)[1]}p&&(k.push({noTitle:q,title:p,icon:r,itemType:t,switchId:F,subMenu:w,break:c.break,sepLine:c.sepLine}),m={commonOptions:f.sc().add(c.commonOptions)}.add(c.sc().del("commonOptions","break","sepLine"),{parentID:a,itemIdx:g}),d.push(m))}else m={commonOptions:f.sc().add(c.commonOptions)}.add(c.sc().del("commonOptions")),m=yield A(a,m,e),k.push(...m)}l.maxItems&&(d.splice(h+l.maxItems),
k.splice(l.maxItems));return k}),y=a=>({TSE:_gk|_gd,bmFolder:_yr|_gd,closedTabs:_6o})[a]||_le,B=_we(function*(a,b,e){a=yield A(a,b,e);b=b.commonOptions||{};var d=a.length,h=b.itemsDistrib&&b.itemsDistrib[0]?b.itemsDistrib:b.layout!=_Ah("R")?["numGroups"]:["auto"];d="auto"==h[0]?Math.ceil(Math.sqrt(d)):"numGroups"==h[0]?Math.ceil(d/(h[1]||1)):h[1]||1;let k=new _wk;h=0;let g=!0;for(let l of a)l.break&&(h=0),l.break=0!=h||g?void 0:!0,l.icon&&_Zs(l.icon)(k.onReady(n=>l.icon=n)),g=!1,h=++h%d;yield l=>
k.setCallback(l);_Ck.trigInstId=e;return{style:"std",items:a}.add(b)}),G=(a,b)=>{try{B(a,_Ck.items[a],_Ck.trigInstId)(e=>_ha(b,e))}catch(e){_Ot("menuError",{stack:e.stack}),_ha(b,[])}},C=(a,b,e)=>a==b?e:a==e?b:a;var _Bp=_we(function*(a,b,e,d=!1){v&&(yield v.wait(),v=void 0);if(!_Ck.items||(yield H())){_Ck={items:[null],busy:!0};var h=b.rootOptions||{},k=h.position||"mouse";if(yield _Vy(_b,{menuData:yield B(a,b,e),menuEntityNum:_lk(a),position:_Ah(k[0].toUpperCase()),alignHorz:"mouse"==k?C(h.alignHorz,
_Nr,_Dp):h.alignHorz,alignVert:"mouse"==k?C(h.alignVert,_ug,_2g):h.alignVert,menuSystem:h.menuSystem,usePrvMsPos:d}))_Ck.id=a;delete _Ck.busy}});let u,H=()=>(a=_ay)=>{u=b=>{u=null;a(b)};_Lk(_Ws,null,b=>{b||u&&u(!1)})||_Uj(_Wr)},I=a=>{a&&(_Zk={[_Ck.id]:Date.now()});_Ck.busy||(_Ck={});u&&u(!0)};{const a=[{action:"alterTgtTabs",params:{tse:[{oper:"slice",params:{from:1,to:1}}]}},{action:"activateTabs"}],b=(e,d)=>[{sequence:[{action:"loadUrls",params:{bookmarkId:e}.add(d?{tabPos:"after",refTab:"lastTab"}:
null)}].concat(2==d?a:[]),targets:"currentTab"}];var _9o=_we(function*(e,d=0){const h=_Ck.items;let k=_Tu(e,h);if(k){yield _Rf();const g=k.type,l=k.content;let n;if("action"==g)2!=d&&(n=yield _rf(_ek[l]||[],null,_qt(null,{usePrevMousePos:!0})));else if("switch"==g)2!=d&&_2t(l,-1);else if("bookmark"==g)e=b(l,d),n=yield _rf(e);else if("bmFolder"==g||"bmSubFldr"==g)0!=d&&(n=yield _rf(b(l,d)));else if("TSE"==g||"tabList"==g){if(2==d){let f="TSE"==g?yield _ai(h.trigInstId,_gt,l):_Dw(l);yield m=>_Zj(f,
m);_Lk(_vy,e)}}else"tab"==g?2==d?(yield f=>_Zj(_Dw(l),f),_Lk(_vy,e)):(n=yield f=>_Ph(_Dw(l),f),yield f=>_Ny(n,f)):"closedTabs"!=g&&("closedWin"==g?0!=d&&(d=yield f=>_Yk.sessions.restore(l.sessionId,f),n=(_ji(d,"window","tabs")||[]).map(f=>f.id),_Lk(_vy,e)):"closedTab"==g&&2!=d&&(d=yield f=>_Yk.sessions.restore(l.sessionId,f),(d=_ji(d,"tab","id"))&&(n=[d]),_Lk(_vy,e)));_Fk=!0;return n}})}let J=_we(function*(a){let b=_Tu(a,_Ck.items);if(b)switch(b.type){case "bookmark":return _ji(yield e=>_Yk.bookmarks.get(b.content+
"",e),0,"url");case "tab":return _zh(_Yp[b.content]);case "closedTab":return b.content.url}}),D=(a,b)=>{let e=[];for(;a;){e.unshift("content",a.itemIdx);if("string"==typeof a.parentID){e.unshift(a.parentID);break}a=_Tu(a.parentID,b)}return e},K=_we(function*(a,b,e,d){var h=_Ck.items;let k=_Tu(a,h),g=4294967294==b?{parentID:e,itemIdx:new x}:_Tu(b,h);if(k&&g){if(k.type.in("bookmark","bmSubFldr")){if(4294967294==b)var l={parentId:_Tu(e,h).content};else(b=_ji(yield f=>_Yk.bookmarks.get(g.content,f),0))&&
(l={parentId:b.parentId,index:b.index+("B"==d?1:0)});return l&&(yield f=>_Yk.bookmarks.move(k.content,l,f))}e=D(k,h);var n=D(g,h);h=e[0];if(_hf(h)&&!n.join(" ").startsWith(e.join(" "))){a=_gh(h).value;e=_ji(a,...e.slice(1,-1));n=_ji(a,...n.slice(1,-1));let f=e[k.itemIdx],m=n[g.itemIdx],q=e[k.itemIdx+1];q&&(f.sepLine&&(q.sepLine=!0),f.break&&(q.break=!0));f.del("sepLine","break");4294967294==b&&(d="B");"T"==d&&(m.sepLine&&(f.sepLine=!0),m.break&&(f.break=!0),m.del("sepLine","break"));d="B"==d?1:0;
e.remove(f);n.splice(n.indexOf(m)+d,0,f);k.parentID=g.parentID;k.itemIdx.remove();k.itemIdx=g.itemIdx.addNeighbor(d);_1e([h,"value"],a,0);return!0}}}),x=function(a,b){this.list=a?a.list:[];null!=b&&this.list.splice(a+b,0,this)};x.prototype={valueOf(){return this.list.indexOf(this)},toString(){return+this},addNeighbor(a){return new x(this,a)},remove(){this.list.splice(+this,1)[0].list=null}};let L=(a,b)=>[];_cu({[_ra]:a=>G(a.itemId,a.callback),[_7a]:a=>J(a.itemId)(b=>_ha(a.callback,b)),[_ni]:a=>K(a.srcItmId,
a.tgtItmId,a.tgtParentId,_Lj(a.insertPos))(b=>_ha(a.callback,!!b)),[_rp]:a=>_9o(a.itemId,a.selMode)(),[_9u]:a=>_ha(a.callback,L(a.itemId,a.parentId)),[_Wr]:a=>I(a&&a.click)})};
;
/* ===== file49.js ===== */
'use strict';{const x=[],y=_Es(600,()=>{const b=_Yk.notifications;b.getAll(c=>{3<Object.keys(c).length&&x.length&&(b.clear(x[0]),y())})});let E=_we(function*(b,c){const a=_Yk.notifications;if(!c||!a)return _ay;b=b.slice(0,100);const m={type:"basic",contextMessage:"DOWNLOADING...",message:b,title:"",iconUrl:_Yk.runtime.getURL("AutoCtrl/logo32.png")};70<=_rs&&(m.silent=!0);let g;const n=h=>{m.add(h);"progress"!=m.type&&delete m.progress;_ti(function*(){for(;g;)yield _za(0);g=!0;try{var __acNR=(void 0===k?0:(yield d=>a.update(k,h,d)))||(k=yield d=>a.create(m,d));try{console.warn("[AC-NOTIF] "+(h.contextMessage||"upd")+" -> "+(__acNR?"ok":""))}catch(_x){}}catch(_e){try{console.warn("[AC-NOTIF] upd err: "+(_e&&_e.message||_e))}catch(_x){}}g=!1})},e=[{title:"Open"},{title:"Show in folder"}];let k,l,f;try{k=yield h=>a.create(m,h);try{console.warn("[AC-NOTIF] created k="+k)}catch(_x){}}catch(_e){try{console.warn("[AC-NOTIF] create err: "+(_e&&_e.message||_e))}catch(_x){}}return(h,...d)=>{switch(h){case "started":{let [p,r]=d;l=p;r&&(f=r,n({contextMessage:`DOWNLOADING (${_5h(f.contentSize)}B)`,message:b}));break}case "progress":h={contextMessage:`DOWNLOADING (${_5h(f.contentSize||f.loadedSize)}B)`};n(f.contentSize?h.add({type:"progress",progress:100*f.loadedSize/f.contentSize|0}):h);break;case "interrupt":[h]=d;n({type:"basic",contextMessage:`INTERRUPTED (${_5h(f.loadedSize)}B${f.contentSize?
` / ${_5h(f.contentSize)}B`:""})`,message:`${h}\n${b}`});break;case "saving":n({contextMessage:`SAVING (${_5h(f.loadedSize)}B)`,message:l});break;case "fileExists":case "done":{n({type:"basic",contextMessage:("done"==h?"SAVED":"File already exists")+` (${_5h(f.contentSize||f.loadedSize)}B)`,message:l,buttons:e});const p=["onButtonClicked","onClosed"];function r(q,t){q==k&&("number"==typeof t&&(0==t&&_iw(`"${l}"`)(),1==t&&_iw(`cmd /c start "" "${l.replace(/[^\\]+$/,"")}"`)(),void 0===k||a.clear(k)),_Qs(a,p,r),
x.remove(k))}_Iy(a,p,r);y();setTimeout(()=>{x.push(k);y()},1300);break}case "httpError":[h]=d;n({contextMessage:"ERROR",message:`${_wu(h.status,h)}\n${b}`});break;case "fileError":[h]=d;n({type:"basic",contextMessage:"ERROR",message:`${h.trim()}\n${l}`});break;case "clear":void 0===k||a.clear(k)}}}),z=(b,c)=>a=>{let m=["All Files: *.*"];c&&(c=c.slice(1).toLowerCase(),m.unshift(`${c.toUpperCase()} files (.${c}): *.${c}`));_xg(b,m.join(", "),!0)(a)},A=(b,c)=>a=>{const m=/^(.*?)(\.[^.]*)?$/;let [,g,n=""]=b.match(m);
c(g,n)(e=>{e=(e[0]||"").trim()||b;[,,n=""]=e.match(m);a([e,n])})},F=_we(function*(b,c,a,m,g,n,e){var k=_Su(b);let [l,f]=yield A(k,a);a=B(c,l);e("started",a,b);k=!1;let h=+new Date(b.getResponseHeader("last-modified"));if(c)for(let p=1,r=a;;++p){var d=yield _Vy(_vr,{path:a});if(d&&!d.error)if(d=d.size==b.contentSize&&d.modTime==h?g:n,"rename"==d){a=r.replace(/(\.[^.]+)?$/,` (${p})$1`);e("started",a);continue}else if(!m)if("cancel"==d)e("fileExists"),k=!0;else if("ask"==d){a=yield z(a,f);if(!a)return[,
,!0];e("started",a)}break}if(m||!c)if(a=yield z(a,f),!a)return[,,!0];return[a,h,k]}),C=(b,c,a,m)=>{a.abort();_4u(c,"",void 0,!0);_Lk(_xo,b,g=>m("fileError",g))},I=(b,c,a,m,g,n,e,k)=>l=>_ti(function*(){const f=yield E(b,e),h=yield(79>_rs&&!b.startsWith("data:")?G:H)(b);let d=0;if(200!=h.status)f("httpError",h),d++||l(),k(void 0);else{var [p,r,q]=yield F(h,c,a,m,g,n,f);q&&!p&&f("clear");if(q)h.abort();else for(;;){try{var t=yield h.readBody()}catch(u){f("interrupt",u.message);d++||l();k(void 0);return}if(t.done){f("saving");
if(t=yield _4u(p,t.value,void 0,void 0,r)){C(t,p,h,f);d++||l();k(void 0);return}f("done");break}f("progress");let w=yield _4u(p,t.value,void 0,void 0,void 0,!0);d++||l();if(w){C(w,p,h,f);d++||l();k(void 0);return}}d++||l();k(p)}}),v;let __acDnrSeq=0;const D=(b,c)=>{if(v[b.id])return v[b.id](b,c),!0};let J=(b,c,a,m,g,n)=>e=>{const k=_Yk.downloads;let l=0;if(k){var f,h,d,p;k.onChanged.addListener(function t(q){if(q.id==f){if(q.filename){d=q.filename.current;if("cancel"==g&&!m){let [,w,u]=d.match(/^(.+?)([^\\]+)$/);
u!=h&&(d=w+h,p=!0,k.cancel(f),k.erase({id:f}))}l++||e()}(q=q.state)&&q.current.in("complete","interrupted")&&(k.onChanged.removeListener(t),q="complete"==q.current||p?d:null,l++||e(),n(q))}});v||(v={},k.onDeterminingFilename.addListener(D));k.download({url:b,saveAs:!!m},q=>{f=q;v[f]=(t,w)=>{A(t.filename,a)(([u])=>{h=u;c.match(/^[\/\\]|:/)||(u=B(c,u));w({filename:u,conflictAction:{rename:"uniquify",cancel:"uniquify",ask:"prompt"}[g]||"overwrite"});delete v[f];_ul(v)&&(v=void 0,k.onDeterminingFilename.removeListener(D))})}})}else l++||
e(),n(void 0)},B=(...b)=>b.filter(c=>c).join("\\").replace(/[\/\\]+/g,"\\");const K=_Es(250,b=>_Lk(_gw,{sysEvent:b})),L=(b,c,a)=>(m,g)=>{const n=new Proxy(c,{get(e,k){let l=k.toLowerCase();return"filename"==l?m:"fileext"==l?g:e[k]}});return _ai(a,_up,b,n)};var _nu=_we(function*(b,c,a){const m=_Tt(c.url||""),g=_Tt(c.folder||""),n=_Tt(c.file||""),e=[];let k=d=>{"audio"==c.method&&K(d?"SystemAsterisk":"SystemHand");if(d)switch(c.doAtEnd){case "open":_iw(`"${d}"`)();break;case "openDir":_iw(`cmd /c start "" "${d.replace(/[^\\]+$/,
"")}"`)();break;case "copy":e.push(d)}};_Pw();let l=new _wk;for(let d of c.usesTabs?_qd(b):[0]){b=_Yp[d]||{};var f=yield _ai(a,_up,m,b);for(let p of f)if((p=p.trim().match(/^.*/)[0].trim())&&_Nf(p)){var h=b.sc().add({url:p});f=L(n,h,a);h=yield _ai(a,_up,g,h);for(let r of h)r=r.trim(),"dwnlApi"==c.method&&!r.match(/^[\/\\]|:/)?yield J(p,r,f,c.showSaveAs,c.ifNameExist,l.onReady(k)):yield I(p,r,f,c.showSaveAs,c.ifFileExist,c.ifNameExist,"notif"==c.method,l.onReady(k))}}yield d=>l.setCallback(d);"copy"==c.doAtEnd&&(yield d=>
_It(c.tgtClpbrd,e.join("\n"),!1,d))});let G=(b,c)=>a=>{let m=!0,g,n,e=new XMLHttpRequest;e.open("GET",b);e.responseType="blob";e.onerror=()=>{g="";a(e)};e.loadedSize=0;let k=()=>{if(n){const l=n;n=null;l(null!=g?{done:!0,value:g}:{value:""})}};e.onload=function(){m&&(e.loadedSize=e.contentSize=+e.getResponseHeader("Content-Length"),a(e));_Xw(this.response)(l=>{g=l;k()})};e.onprogress=l=>{e.contentSize=l.total;e.loadedSize=l.loaded;m?(m=!1,a(e)):k()};e.readBody=()=>l=>{n=l;null!=g&&k()};e.send()},
H=_we(function*(b,c){
  try{
    // AC-MV3 FIX (2026-08-09, FEATURES-MV3.md §7-2): MV2 spoofed the Referer header via
    // blocking webRequest (onBeforeSendHeaders + "blocking") — unavailable
    // in MV3 (no webRequest/webRequestBlocking permissions) → the listener
    // line THREW in the SW → H() returned {} → EVERY notif/copy save failed
    // with httpError. Replaced by a declarativeNetRequest SESSION rule
    // (modifyHeaders → set Referer) — DNR rules DO apply to fetch() calls
    // made in the extension's own service worker (Chrome docs, "Interactions
    // with service workers"). Requires the
    // "declarativeNetRequestWithHostAccess" permission (manifest) + the
    // existing <all_urls> host permissions. If DNR is unavailable/rejected,
    // the fetch proceeds WITHOUT the referer (plain download) instead of {}
    // — an improvement over the always-fail state.
    const dnr=_Yk.declarativeNetRequest;
    const setReferer=u=>d=>{if(!dnr||!dnr.updateSessionRules)return d(0);let id=1E6+(++__acDnrSeq)%1E6;try{dnr.updateSessionRules({addRules:[{id,priority:1,action:{type:"modifyHeaders",requestHeaders:[{header:"Referer",operation:"set",value:_1u(u)||_xu(u)}]},condition:{urlFilter:u}}],removeRuleIds:[id]}).then(()=>d(id),()=>d(0))}catch(x){d(0)}};
    const clearRule=id=>d=>{if(id&&dnr&&dnr.updateSessionRules)try{dnr.updateSessionRules({removeRuleIds:[id]}).then(()=>d(),()=>d())}catch(x){d()}else d()};
    let id=0;
    for(let g=0;2>g;++g){
      id=yield setReferer(b);
      var a;
      try{a=yield fetch(b,{redirect:"follow",mode:"cors",credentials:"include",cache:"force-cache",referrerPolicy:"unsafe-url"})}finally{yield clearRule(id)}
      if(300<=a.status)b=a.url;else break
    }
    let m=a.body.getReader();
    return a.add({loadedSize:0,contentSize:+a.headers.get("Content-Length"),responseURL:a.url,abort:()=>{m.releaseLock();a.body.cancel()},getResponseHeader:g=>a.headers.get(g),readBody:_we(function*(){let g=yield m.read();g.value=g.value?yield _Xw(new Blob([g.value])):"";a.loadedSize+=g.value.length;return g})});
  }catch(m){}
  return{}})};
