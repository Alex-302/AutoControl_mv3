// CDP: wrap the menu action implementations (_Oa/_eu/_2h) + _Lk, run a key
// sequence, dump what actually executed.
// Usage: node Test/cdp_action_probe.js [holdMs] [repeat]
'use strict';
const { execSync } = require('child_process');
const path = require('path');
const port = '9223';
const CDP = `http://127.0.0.1:${port}`;
const EXT_ID = 'lkaihdpfpifdlgoapbfocpmekbokmcfd';
const PS1 = path.join(__dirname, '_ac_keypress2.ps1');
const holdMs = process.argv[2] || 700;
const repeat = process.argv[3] === 'repeat';

async function evalSW(ws, send, expression, awaitPromise = true) {
  const r = await send('Runtime.evaluate', { expression, awaitPromise, returnByValue: true });
  return r.result && r.result.result;
}

async function main() {
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
    const id = ++msgId;
    pending.set(id, res);
    ws.send(JSON.stringify({ id, method, params }));
  });

  // install probes
  await evalSW(ws, send, `(() => {
    window.__acPr = { Oa: [], eu: [], Lk: [], Ck: null };
    try { window.__acPr.Ck = (typeof _Ck !== 'undefined') ? JSON.stringify({id: _Ck && _Ck.id, items: _Ck && _Ck.items && _Ck.items.length}) : 'UNDEF'; } catch(e) { window.__acPr.Ck = 'ERR ' + e; }
    const w = (name) => {
      try {
        const o = window[name];
        if (typeof o !== 'function') { window.__acPr[name + '_missing'] = typeof o; return; }
        window[name] = function(...a) {
          window.__acPr[name].push({ t: Date.now(), args: JSON.stringify(a).slice(0, 300) });
          try { return o.apply(this, a); } catch(e) { window.__acPr[name].push({ t: Date.now(), threw: String(e && e.stack || e).slice(0, 300) }); throw e; }
        };
      } catch(e) { window.__acPr[name + '_wrapErr'] = String(e); }
    };
    w('_Oa'); w('_eu');
    // _2h is a const (not on window) — wrap via _w lookup? skip; _Lk is enough
    const oLk = window._Lk;
    if (typeof oLk === 'function') {
      window._Lk = function(a, b, c, g) {
        window.__acPr.Lk.push({ t: Date.now(), type: a, hasCb: typeof c === 'function', b: (b === null || b === undefined) ? String(b) : JSON.stringify(b).slice(0, 150) });
        try { return oLk.apply(this, arguments); } catch(e) { window.__acPr.Lk.push({ t: Date.now(), threw: String(e && e.stack || e).slice(0, 300) }); throw e; }
      };
    } else window.__acPr.Lk_missing = typeof oLk;
    return 'probes installed';
  })()`);

  const before = await evalSW(ws, send, `new Promise(r => chrome.tabs.query({active:true,currentWindow:true}, t => r({id: t[0]&&t[0].id})))`);
  console.log('BEFORE:', JSON.stringify(before && before.value));

  const args = `-HoldMs ${holdMs}${repeat ? ' -RepeatTab' : ''}`;
  console.log('injecting:', args);
  const out = execSync(`powershell -NoProfile -ExecutionPolicy Bypass -File "${PS1}" ${args}`, { encoding: 'utf8', timeout: 20000 });
  console.log('ps:', out.trim());
  await new Promise((r) => setTimeout(r, 2500));

  const after = await evalSW(ws, send, `new Promise(r => chrome.tabs.query({active:true,currentWindow:true}, t => r({id: t[0]&&t[0].id})))`);
  console.log('AFTER :', JSON.stringify(after && after.value));

  const dump = await evalSW(ws, send, `(() => {
    const p = window.__acPr || {};
    const t0 = p.Oa[0] && p.Oa[0].t || Date.now();
    return {
      Ck: p.Ck,
      Oa_missing: p.Oa_missing, eu_missing: p.eu_missing, Lk_missing: p.Lk_missing,
      Oa: p.Oa.map(x => ({ dt: x.t - t0, ...(x.threw ? {threw: x.threw} : {args: x.args}) })),
      eu: p.eu.map(x => ({ dt: x.t - t0, ...(x.threw ? {threw: x.threw} : {args: x.args}) })),
      Lk: p.Lk.map(x => ({ dt: x.t - t0, type: x.type, hasCb: x.hasCb, b: x.b, ...(x.threw ? {threw: x.threw} : {}) })),
      LkCount: p.Lk.length
    };
  })()`);
  console.log('--- probe dump ---');
  console.log(JSON.stringify(dump && dump.value, null, 1));
  ws.close();
}
main().catch(e => { console.error('FATAL:', e); process.exit(1); });
