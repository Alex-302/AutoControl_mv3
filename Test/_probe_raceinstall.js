// CDP helper: install the in-SW diagnostic log for the "wrong hovered tab"
// investigation (pairs with Test/_probe_racedump.js).
//
// The SW is IIFE-local, so the probes are installed into its global scope from
// here. Everything is runtime-only - no file is modified and nothing is
// persisted (the log dies with the service worker; re-run this tool after any
// SW restart).
//
// Captured: the zone-helper port traffic (request / answer incl. the tab index
// and title), `_ys()` calls with the bundle's `_kg` cache and the SW-local
// `__acHoveredTabId`, the filter-table result for every target, `tabs.reload`
// targets and `tabs.onUpdated` loading events.
//
// Usage: node Test/_probe_raceinstall.js [port]
'use strict';
const port = process.argv[2] || '9223';
const CDP = `http://127.0.0.1:${port}`;
const EXT_ID = 'lkaihdpfpifdlgoapbfocpmekbokmcfd';

const INSTALL = `(() => {
  if (self.__acRaceLog) return 'already installed (clear it with __acRaceClear())';
  const buf = self.__acRaceLog = [];
  const rec = (tag, data) => { try { buf.push({ t: Date.now(), tag, data }); if (buf.length > 1500) buf.shift(); } catch (e) {} };
  self.__acRaceClear = () => { buf.length = 0; return 'cleared'; };
  const oConnect = chrome.runtime.connectNative;
  chrome.runtime.connectNative = function (name) {
    const p = oConnect.apply(this, arguments);
    if (name === 'com.autocontrol.zonehelper') {
      rec('port', 'open');
      const oPost = p.postMessage.bind(p);
      p.postMessage = function (m) { rec('req', m); return oPost(m); };
      try { p.onMessage.addListener(m => rec('res', m)); } catch (e) {}
      try { p.onDisconnect.addListener(() => rec('port', 'disconnect')); } catch (e) {}
    }
    return p;
  };
  const oReload = chrome.tabs.reload;
  chrome.tabs.reload = function (id) { rec('reload', id); return oReload.apply(this, arguments); };
  const oUpdate = chrome.tabs.update;
  chrome.tabs.update = function (id, props) {
    rec('update', { id: id, url: props && props.url ? String(props.url).slice(0, 60) : null });
    return oUpdate.apply(this, arguments);
  };
  try { chrome.tabs.onUpdated.addListener((id, info, tab) => { if (info.status === 'loading') rec('loading', { id: id, idx: tab ? tab.index : null, title: tab ? String(tab.title || '').slice(0, 30) : null }); }); } catch (e) {}
  try {
    const oYs = _ys;
    _ys = function () {
      const r = oYs.apply(this, arguments);
      try { rec('_ys', { ret: (r && r.length) ? r : null, kg: _kg, sw: window.__acTest ? window.__acTest.hoveredId() : 'n/a' }); } catch (e) {}
      return r;
    };
  } catch (e) { rec('err', 'ys: ' + e.message); }
  try {
    const oFilter = _pp.filter;
    _pp.filter = function (b, a) {
      const r = oFilter.apply(this, arguments);
      try {
        rec('filter', { evt: !!(a && a.evtTabs), hv: !!(a && a.anyHvrd), n: b ? b.length : -1,
          out: (r && r[0]) ? r[0] : r, kg: _kg,
          sw: window.__acTest ? window.__acTest.hoveredId() : 'n/a' });
      } catch (e) {}
      return r;
    };
    _pp.posFilter = _pp.filter;
  } catch (e) { rec('err', 'filter: ' + e.message); }
  return 'installed';
})()`;

(async () => {
  const targets = await (await fetch(CDP + '/json/list')).json();
  const sw = targets.find(t => t.url && t.url.startsWith('chrome-extension://' + EXT_ID) && t.type === 'service_worker');
  if (!sw) { console.log('SW not found'); process.exit(2); }
  const ws = new WebSocket(sw.webSocketDebuggerUrl);
  await new Promise((res, rej) => { ws.onopen = res; ws.onerror = rej; });
  let msgId = 0;
  const pending = new Map();
  ws.onmessage = (e) => {
    const m = JSON.parse(e.data);
    if (m.id && pending.has(m.id)) { pending.get(m.id)(m); pending.delete(m.id); }
  };
  const send = (method, params) => new Promise((res) => {
    const id = ++msgId; pending.set(id, res);
    ws.send(JSON.stringify({ id, method, params }));
  });
  await send('Runtime.enable');
  const r = await send('Runtime.evaluate', { expression: INSTALL, awaitPromise: true, returnByValue: true });
  const v = r.result && r.result.result && r.result.result.value;
  console.log('install:', v !== undefined ? JSON.stringify(v) : JSON.stringify(r.result));
  if (r.result && r.result.exceptionDetails) console.log('EXC:', JSON.stringify(r.result.exceptionDetails.text));
  ws.close();
})().catch(e => { console.error('FATAL:', e.message); process.exit(1); });
