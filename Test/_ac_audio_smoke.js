// TEMP simulation: verify the offscreen-document playAudio engine works.
// Loads file67.js + the polyfills from offscreen.js + file53.js into a vm,
// then plays a preset sound (oscillator path) and a voice (TTS path).
'use strict';
const fs = require('fs');
const vm = require('vm');
const path = require('path');
// mv3-build/ holds the extension sources; this diagnostic lives in Test/.
const MV3 = path.join(__dirname, '..', 'mv3-build');

// --- audio stubs ---
// NOTE: Chrome's AudioNode.connect() returns the destination node (non-spec
// but MV2 relied on it — file53 chains g=c.connect(g); g.connect(l); ...).
function makeChainableNode() {
  return {
    gain: { value: 1, exponentialRampToValueAtTime() {} },
    channelCount: 1, pan: { value: 0 },
    panningModel: 'HRTF', coneOuterGain: 1,
    positionY: { value: 0 }, positionX: { value: 0, setValueAtTime() {}, linearRampToValueAtTime() {} },
    positionZ: { value: 0, setValueAtTime() {}, linearRampToValueAtTime() {} },
    connect(target) { return target || this; },
  };
}
function makeSource() {
  return {
    buffer: null, playbackRate: { value: 1 }, type: 'sine', frequency: { value: 440, exponentialRampToValueAtTime() {} },
    setPeriodicWave() {}, connect(target) { return target || this; },
    start(t) { const s = this; setTimeout(() => { if (s.onended) s.onended(); }, 5); },
    stop() {}, onended: null,
  };
}
const speech = {
  getVoices() { return []; },
  speak(u) { setTimeout(() => u.onend && u.onend(), 5); },
  cancel() {},
};
function makeAudioCtx() {
  return {
    currentTime: 100, destination: {},
    close() {}, decodeAudioData(buf, ok) { ok(buf); },
    createBufferSource: makeSource,
    createOscillator: makeSource,
    createGain() { return makeChainableNode(); },
    createStereoPanner() { return makeChainableNode(); },
    createPanner() { return makeChainableNode(); },
    createPeriodicWave() { return {}; },
  };
}

const noop = () => {};
const ctx = {
  console, setTimeout, clearTimeout, setInterval, clearInterval,
  URL, URLSearchParams, TextEncoder, TextDecoder, Intl, btoa, atob,
  navigator: { userAgent: 'Mozilla/5.0', language: 'en-US' },
  localStorage: { getItem: () => null, setItem: noop, removeItem: noop },
  location: { href: 'chrome-extension://abc/offscreen.html', search: '', pathname: '/offscreen.html', hash: '', origin: 'chrome-extension://abc', hostname: 'abc', protocol: 'chrome-extension:' },
  history: {},
  document: {
    createElement: () => ({ style: {}, setAttribute: noop, appendChild: noop, addEventListener: noop, removeEventListener: noop }),
    createDocumentFragment: () => ({ appendChild: noop }),
    addEventListener: noop,
    body: { appendChild: noop },
    documentElement: { style: {} },
    querySelector: () => null,
    head: { appendChild: noop },
  },
  NodeList: function () {}, HTMLCollection: function () {},
  XMLHttpRequest: function () {}, Image: function () {},
  OffscreenCanvas: function () {},
  fetch: () => Promise.reject(new Error('no fetch')),
  crypto: { getRandomValues: a => { for (let i = 0; i < a.length; i++) a[i] = Math.floor(Math.random() * 256); return a; } },
  SpeechSynthesisUtterance: function (t) { this.text = t; },
  speechSynthesis: speech,
  AudioContext: makeAudioCtx,
  AudioBuffer: function () {},
  chrome: {
    runtime: {
      id: 'abcdefghijklmnopqrstuvwxyzabcdef',
      getURL: p => 'chrome-extension://abc/' + p,
      sendMessage: (m, cb) => cb && cb({ ok: true, result: undefined }),
    },
  },
};
ctx.addEventListener = noop;
ctx.removeEventListener = noop;
ctx.postMessage = noop;
ctx.window = ctx;
ctx.self = ctx;
ctx.globalThis = ctx;
ctx.results = {};
vm.createContext(ctx);

function load(name) {
  vm.runInContext(fs.readFileSync(path.join(MV3, name), 'utf8'), ctx, { filename: name });
}

// --- simulate offscreen.js __acAudioPolyfills (extract from offscreen.js) ---
const offscreenSrc = fs.readFileSync(path.join(MV3, 'offscreen.js'), 'utf8');
const pfStart = offscreenSrc.indexOf('function __acAudioPolyfills()');
const pfEnd = offscreenSrc.indexOf('// Lazy-load the playAudio engine');
if (pfStart < 0 || pfEnd < 0) { console.log('FAIL: polyfills block not found in offscreen.js'); process.exit(1); }
const polyfillSrc = offscreenSrc.slice(pfStart, pfEnd)
  .replace('function __acAudioPolyfills() {', 'window.__acAudioPolyfills = function () {')
  .replace(/}$/, '};');

console.log('-- load file67.js --');
load('file67.js');
console.log('-- apply polyfills --');
vm.runInContext(polyfillSrc, ctx, { filename: 'offscreen-polyfills.js' });
vm.runInContext('window.__acAudioPolyfills()', ctx);
// file67 defines _9w/_sr using document — fine.
console.log('-- load file53.js --');
load('file53.js');

const t0 = Date.now();
vm.runInContext(`
  (function(){
    var done = 0;
    function fin(name){ results[name] = Date.now() - ${t0}; if (++done === 3) console.log('ALL CALLS RETURNED'); }
    // 1. preset sound (oscillator path)
    _lh({ type: "preset", sndId: "ding", mode: undefined, vol: 100, len: 0.7, freq: 400, times: 1, gap: 0 }, [], 1);
    setTimeout(function(){ console.log('preset: _lh returned (no throw)'); fin('preset'); }, 20);
    // 2. voice (TTS path, pre-expanded plain text — usesTabs:false)
    _lh({ type: "voice", text: "hello from AutoControl", lang: "en", voice: 0, usesTabs: false, rate: 100, pitch: 5, vol: 100 }, [], 2);
    setTimeout(function(){ console.log('voice: _lh returned (no throw)'); fin('voice'); }, 20);
    // 3. system sound (evtAlias -> _Vy bridge -> chrome.runtime stub returns undefined -> clean skip)
    _lh({ type: "system", evtAlias: "Windows Notify System Generic", mode: undefined }, [], 3);
    setTimeout(function(){ console.log('system(evtAlias): _lh returned (no throw, undefined reply skipped cleanly)'); fin('system'); }, 20);
  })();
`, ctx, { filename: 'engine-smoke.js' });

setTimeout(() => {
  const keys = Object.keys(ctx.results);
  if (keys.length === 3) {
    console.log('SMOKE OK: preset/voice/system calls all returned within', Math.max(...keys.map(k => ctx.results[k])), 'ms');
    process.exit(0);
  } else {
    console.log('SMOKE FAIL: only', keys.length, 'of 3 calls returned:', keys);
    process.exit(1);
  }
}, 1500);
