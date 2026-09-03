// CDP: wrap _w (action lookup) + _Lk (native send) + console; Esc first, then
// hold sequence. Shows exactly what closeMenu/selectMarkedItem do.
// Usage: node Test/cdp_action_probe2.js [holdMs] [repeat]
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
  const events = [];
  ws.onmessage = (e) => {
    const m = JSON.parse(e.data);
    if (m.id && pending.has(m.id)) { pending.get(m.id)(m); pending.delete(m.id); }
    else if (m.method === 'Runtime.consoleAPICalled') {
      const args = (m.params.args || []).map(a => a.value !== undefined ? a.value : (a.description || a.type));
      events.push({ type: m.params.type, text: args.join(' ') });
    }
  };
  const send = (method, params) => new Promise((res) => {
    const id = ++msgId;
    pending.set(id, res);
    ws.send(JSON.stringify({ id, method, params }));
  });
  await send('Runtime.enable');

  await evalSW(ws, send, `(() => {
    window.__acPr = { w: [], Lk: [], cap: [] };
    // wrap console for guaranteed capture (survives patch)
    for (const m of ['log','warn','info','debug']) {
      try {
        const orig = console[m] ? console[m].bind(console) : (()=>{});
        console[m] = function(){ window.__acPr.cap.push('['+m+'] '+[].slice.call(arguments).join(' ')); try{ orig.apply(console, arguments); }catch(e){} };
      } catch(e) {}
    }
    // wrap _w — the action lookup choke point (file37 _rf → _w(name, params))
    try {
      const ow = window._w;
      if (typeof ow === 'function') {
        window._w = function(a, b) {
          let r;
          try { r = ow.call(this, a, b); }
          catch(e) { window.__acPr.w.push({ t: Date.now(), name: a, THREW: String(e && e.stack || e).slice(0,300) }); throw e; }
          const rt = typeof r;
          window.__acPr.w.push({ t: Date.now(), name: a, rt, params: b ? JSON.stringify(b).slice(0,120) : String(b) });
          return r;
        };
        window.__acPr.w.push({ t: Date.now(), note: '_w wrapped, typeof=' + rt });
      } else window.__acPr.w.push({ t: Date.now(), note: '_w missing: ' + typeof ow });
    } catch(e) { window.__acPr.w.push({ t: Date.now(), note: '_w wrap err: ' + e }); }
    // wrap _Lk
    try {
      const oLk = window._Lk;
      if (typeof oLk === 'function') {
        window._Lk = function(a, b, c, g) {
          window.__acPr.Lk.push({ t: Date.now(), type: a, hasCb: typeof c === 'function', b: (b === null || b === undefined) ? String(b) : JSON.stringify(b).slice(0,150) });
          try { return oLk.apply(this, arguments); }
          catch(e) { window.__acPr.Lk.push({ t: Date.now(), type: a, THREW: String(e && e.stack || e).slice(0,300) }); throw e; }
        };
      } else window.__acPr.Lk.push({ t: Date.now(), note: '_Lk missing: ' + typeof oLk });
    } catch(e) { window.__acPr.Lk.push({ t: Date.now(), note: '_Lk wrap err: ' + e }); }
    return 'probes ok';
  })()`);

  // 1) Esc to close any open menu
  execSync(`powershell -NoProfile -ExecutionPolicy Bypass -File "${PS1}" -Esc`, { encoding: 'utf8', timeout: 10000 });
  await new Promise((r) => setTimeout(r, 600));
  // 2) the hold sequence
  const args = `-HoldMs ${holdMs}${repeat ? ' -RepeatTab' : ''}`;
  console.log('injecting:', args);
  const out = execSync(`powershell -NoProfile -ExecutionPolicy Bypass -File "${PS1}" ${args}`, { encoding: 'utf8', timeout: 20000 });
  console.log('ps:', out.trim());
  await new Promise((r) => setTimeout(r, 2500));

  const after = await evalSW(ws, send, `new Promise(r => chrome.tabs.query({active:true,currentWindow:true}, t => r({id: t[0]&&t[0].id, url:(t[0]&&t[0].url||'').slice(0,60)})))`);
  console.log('AFTER :', JSON.stringify(after && after.value));

  const dump = await evalSW(ws, send, `(() => {
    const p = window.__acPr || {};
    const t0 = Math.min(...[p.w[0]&&p.w[0].t, p.Lk[0]&&p.Lk[0].t].filter(Boolean));
    const j = (arr) => arr.map(x => ({ dt: x.t - t0, ...(x.threw||x.THREW ? {threw: x.threw||x.THREW} : {}), ...(x.note ? {note: x.note} : {}), ...(x.name !== undefined ? {name: x.name} : {}), ...(x.rt ? {rt: x.rt} : {}), ...(x.params !== undefined ? {params: x.params} : {}), ...(x.type !== undefined ? {type: x.type} : {}), ...(x.hasCb !== undefined ? {cb: x.hasCb} : {}), ...(x.b !== undefined ? {b: x.b} : {}) }));
    return { wCount: p.w.length, w: j(p.w).slice(0, 40), LkCount: p.Lk.length, Lk: j(p.Lk).slice(0, 40), capTail: p.cap.slice(-60) };
  })()`);
  console.log('--- probe dump ---');
  console.log(JSON.stringify(dump && dump.value, null, 1));
  ws.close();
}
main().catch(e => { console.error('FATAL:', e); process.exit(1); });
