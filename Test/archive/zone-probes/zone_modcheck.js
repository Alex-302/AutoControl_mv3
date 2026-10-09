// Compile the live config and dump the wheel entries (modifier preconds).
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
    if (r.result && r.result.exceptionDetails) return 'EXC: ' + (r.result.exceptionDetails.exception && r.result.exceptionDetails.exception.description || '');
    return r.result && r.result.result && r.result.result.value;
  };
  const expr = `(async()=>{
    const s = await chrome.storage.local.get(['trigActList','mouseGest','advOpts']);
    const p = _mh(s.trigActList||[], s.mouseGest||{}, s.advOpts||{});
    const out = {};
    for (const k of ['22537','23561']) {
      out[k] = (p.map[k]||[]).map(i => JSON.stringify(p.list[i]));
    }
    return JSON.stringify(out);
  })()`;
  console.log(await ev(expr));
  ws.close();
})().catch(e => { console.error('FATAL:', e.message); process.exit(1); });
