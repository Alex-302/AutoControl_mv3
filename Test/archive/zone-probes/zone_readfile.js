// Parse the settings.dat JSON via the native file read and list trigger ids.
'use strict';
(async () => {
  const targets = await (await fetch('http://127.0.0.1:9223/json/list')).json();
  const sw = targets.find(t => t.url && t.url.startsWith('chrome-extension://lkaihdpfpifdlgoapbfocpmekbokmcfd') && t.type === 'service_worker');
  const ws = new WebSocket(sw.webSocketDebuggerUrl);
  await new Promise((res, rej) => { ws.onopen = res; ws.onerror = rej; });
  let id = 0;
  const pending = new Map();
  ws.onmessage = e => {
    const m = JSON.parse(e.data);
    if (m.id && pending.has(m.id)) { pending.get(m.id)(m); pending.delete(m.id); }
  };
  const send = (method, params) => new Promise(res => { const i = ++id; pending.set(i, res); ws.send(JSON.stringify({ id: i, method, params })); });
  const ev = async (expr) => {
    const r = await send('Runtime.evaluate', { expression: expr, awaitPromise: true, returnByValue: true });
    return r.result && r.result.result && r.result.result.value;
  };
  const expr = `new Promise(r=>{_If('settings.dat')(res=>{try{const d=JSON.parse(res.content);const l=d.trigActList||[];r(JSON.stringify({total:l.length, ids:l.map(x=>x[0]).join(','), has41:l.some(x=>x[0]==='41'), has43:l.some(x=>x[0]==='43'), has93:l.some(x=>x[0]==='93')}))}catch(e){r('PARSE-ERR '+e.message)}})})`;
  console.log(await ev(expr));
  ws.close();
})().catch(e => { console.error('FATAL:', e.message); process.exit(1); });
