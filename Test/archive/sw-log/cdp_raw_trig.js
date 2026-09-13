// cdp_raw_trig.js - dump the RAW stored JSON of selected triggers.
// Usage: node Test/cdp_raw_trig.js [port] [id1,id2,...]
'use strict';
const PORT = process.argv[2] || '9223';
const IDS = (process.argv[3] || '44,43,41,1').split(',');
const EXT = 'lkaihdpfpifdlgoapbfocpmekbokmcfd';

(async () => {
  const targets = await (await fetch(`http://127.0.0.1:${PORT}/json/list`)).json();
  const sw = targets.find(t => t.url && t.url.startsWith('chrome-extension://' + EXT) && t.type === 'service_worker');
  if (!sw) { console.log('NO SW'); process.exit(1); }
  const ws = new WebSocket(sw.webSocketDebuggerUrl);
  await new Promise((res, rej) => { ws.onopen = res; ws.onerror = rej; });
  let id = 0; const pending = new Map();
  ws.onmessage = e => { const m = JSON.parse(e.data); if (m.id && pending.has(m.id)) { pending.get(m.id)(m); pending.delete(m.id); } };
  const send = (method, params) => new Promise(res => { const i = ++id; pending.set(i, res); ws.send(JSON.stringify({ id: i, method, params })); });
  const r = await send('Runtime.evaluate', {
    expression: `chrome.storage.local.get('trigActList').then(o => {
      const list = o.trigActList || [];
      const out = {};
      for (const want of ${JSON.stringify(IDS)}) {
        const e = list.find(x => String(x[0]) === String(want));
        out[want] = e ? e[1] : null;
      }
      return JSON.stringify(out);
    })`, awaitPromise: true, returnByValue: true
  });
  const v = r.result && r.result.result && r.result.result.value;
  console.log(v || JSON.stringify(r).slice(0, 500));
  ws.close();
})().catch(e => { console.log('ERR ' + e.message); process.exit(1); });
