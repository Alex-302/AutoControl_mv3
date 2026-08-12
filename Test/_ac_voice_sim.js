// TEMP simulation: verify the SW-side voice-text pre-expansion
// (__acVoiceText logic) using the REAL bundle template machinery
// (_Tt/_up/_ai/_qd/_Yp) in the mh_test-style SW context.
'use strict';
const fs = require('fs');
const vm = require('vm');
const path = require('path');
// mv3-build/ holds the extension sources; this diagnostic lives in Test/.
const MV3 = path.join(__dirname, '..', 'mv3-build');

const noop = () => {};
const ctx = {
  console, setTimeout, clearTimeout, setInterval, clearInterval,
  URL, URLSearchParams, TextEncoder, TextDecoder, Intl,
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
  NodeList: function () {}, HTMLCollection: function () {},
  XMLHttpRequest: function () {}, Image: function () {},
  OffscreenCanvas: function () {},
  fetch: () => Promise.reject(new Error('no fetch')),
  btoa: s => Buffer.from(s, 'binary').toString('base64'),
  atob: s => Buffer.from(s, 'base64').toString('binary'),
  crypto: { getRandomValues: a => { for (let i = 0; i < a.length; i++) a[i] = Math.floor(Math.random() * 256); return a; } },
  chrome: {
    runtime: { id: 'abcdefghijklmnopqrstuvwxyzabcdef', getManifest: () => ({ short_name: 'AutoControl' }), getURL: p => 'chrome-extension://abc/' + p, sendMessage: noop, onMessage: { addListener: noop }, onConnect: { addListener: noop }, onInstalled: { addListener: noop }, onStartup: { addListener: noop }, onUpdateAvailable: { addListener: noop }, onMessageExternal: { addListener: noop }, connectNative: () => ({ postMessage: noop, onMessage: { addListener: noop }, onDisconnect: { addListener: noop } }) },
    action: { onClicked: { addListener: noop } },
    downloads: { onChanged: { addListener: noop }, onDeterminingFilename: { addListener: noop }, download: noop, cancel: noop, erase: noop },
    idle: { onStateChanged: { addListener: noop }, queryState: noop },
    storage: { local: { get: (k, cb) => cb && cb({}), set: noop, clear: noop, remove: noop }, sync: { get: (k, cb) => cb && cb({}), set: noop, clear: noop }, managed: { get: (k, cb) => cb && cb({}) }, onChanged: { addListener: noop } },
    windows: { getAll: (o, cb) => cb && cb([]), get: noop, create: noop, update: noop, remove: noop, getLastFocused: (o, cb) => cb && cb(null), onCreated: { addListener: noop }, onRemoved: { addListener: noop }, onFocusChanged: { addListener: noop }, onBoundsChanged: { addListener: noop } },
    tabs: { query: (q, cb) => cb && cb([]), get: noop, create: noop, update: noop, remove: noop, sendMessage: noop, executeScript: noop, onCreated: { addListener: noop }, onUpdated: { addListener: noop }, onRemoved: { addListener: noop }, onActivated: { addListener: noop }, onMoved: { addListener: noop }, onAttached: { addListener: noop }, onDetached: { addListener: noop }, onReplaced: { addListener: noop } },
    scripting: { executeScript: noop },
    system: { display: { getInfo: cb => cb && cb([]), onDisplayChanged: { addListener: noop } } },
    contextMenus: { create: noop, onClicked: { addListener: noop } },
    alarms: { create: noop, onAlarm: { addListener: noop } },
    userScripts: { execute: noop },
    extension: { getBackgroundPage: () => null, isAllowedFileSchemeAccess: cb => cb && cb(false) },
    bookmarks: { getTree: cb => cb && cb([]) },
    sessions: { getRecentlyClosed: cb => cb && cb([]), onChanged: { addListener: noop, removeListener: noop } },
    commands: { getAll: cb => cb && cb([]) },
  },
};
ctx.addEventListener = noop;
ctx.removeEventListener = noop;
ctx.postMessage = noop;
ctx.window = ctx;
ctx.self = ctx;
ctx.globalThis = ctx;
vm.createContext(ctx);

const bundle = fs.readFileSync(path.join(MV3, 'sw_core_bundle.js'), 'utf8');
vm.runInContext(bundle, ctx, { filename: 'sw_core_bundle.js' });

// Populate _Yp like the SW does (window enum cache).
vm.runInContext(`
  _Yp[101] = { id: 101, title: 'GitHub', url: 'https://github.com/', favIconUrl: 'https://github.com/favicon.ico', active: true, windowId: 1, index: 0 };
  _Yp[102] = { id: 102, title: 'Example Dot Com', url: 'https://example.org/', favIconUrl: '', active: false, windowId: 1, index: 1 };
  window.__expandResults = {};
  // === the __acVoiceText logic (copied from sw.js) ===
  window.__acVoiceTextSim = function(params, tabGroups) {
    var out = '';
    var tabs;
    try { tabs = (params.usesTabs && typeof _qd === 'function') ? (_qd(tabGroups) || []) : [0]; } catch (e) { tabs = [0]; }
    var i = 0;
    function next() {
      if (i >= tabs.length) { window.__expandResults.done = out; return; }
      var l = tabs[i++];
      try {
        var tmpl = _Tt(params.text || '');
        var runner = _ai(0, _up, tmpl, _Yp[l]);
        runner(function(lines) { try { out += (lines || []).join('\\n'); } catch (e) {} next(); });
      } catch (e) { next(); }
    }
    next();
  };
`, ctx, { filename: 'sw-sim.js' });

vm.runInContext(`
  // 1. plain text, usesTabs false — fast path
  __acVoiceTextSim({ text: 'hello world', usesTabs: false }, []);
  // 2. template with <title>, usesTabs true — expands per target tab (101, 102)
  __acVoiceTextSim({ text: 'Tab <title> | <url>', usesTabs: true }, [[101, 102]]);
`, ctx);

setTimeout(() => {
  vm.runInContext('__acVoiceTextSim({ text: "hello world", usesTabs: false }, [])', ctx);
  setTimeout(() => {
    const plain = ctx.__expandResults.done;
    vm.runInContext('__acVoiceTextSim({ text: "Tab <title> | <url>", usesTabs: true }, [[101, 102]])', ctx);
    setTimeout(() => {
      const tpl = ctx.__expandResults.done;
      console.log('plain text  ->', JSON.stringify(plain));
      console.log('template    ->', JSON.stringify(tpl));
      const ok = plain === 'hello world' &&
        // MV2 parity: file53 does `c+=(yield _ai(0,_up,d,_Yp[l])).join("\n")` —
        // the \n join is PER-TAB only; tab expansions concatenate w/o separator.
        tpl === 'Tab GitHub | https://github.com/Tab Example Dot Com | https://example.org/';
      console.log(ok ? 'VOICE-TEXT SIM OK' : 'VOICE-TEXT SIM FAIL');
      process.exit(ok ? 0 : 1);
    }, 50);
  }, 50);
}, 50);
