// Inspect the settings page state: SFE model, filePath, storage proxy view.
'use strict';
(async () => {
  const targets = await (await fetch('http://127.0.0.1:9223/json/list')).json();
  const page = targets.find(t => t.type === 'page' && t.url.includes('main.html'));
  if (!page) { console.log('settings page not found'); process.exit(0); }
  const ws = new WebSocket(page.webSocketDebuggerUrl);
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
  const res = await ev(`(async()=>{
    const out = {};
    try { out.filePath = (typeof _Uy !== 'undefined' && _Uy) ? (_Uy.filePath || 'NONE') : '_Uy undef'; } catch(e) { out.filePath = 'EXC ' + e.message; }
    try {
      const m = (typeof _Nh !== 'undefined') ? 'proxy exists' : 'no _Nh';
      out.nh = m;
    } catch(e) { out.nh = 'EXC ' + e.message; }
    try { out.modelKeys = typeof m !== 'undefined' && m ? Object.keys(m).join(',') : 'no global m'; } catch(e) {}
    try { out.modelTrigs = typeof m !== 'undefined' && m && m.trigActList ? m.trigActList.length : 'n/a'; } catch(e) {}
    try { out.ifKeys = typeof _if !== 'undefined' && _if ? Object.keys(_if).join(',') : '_if undef'; } catch(e) {}
    try { out.storageTrigs = (await chrome.storage.local.get('trigActList')).trigActList.length; } catch(e) { out.storageTrigs = 'EXC ' + e.message; }
    try { out.sections = (await chrome.storage.local.get('sections')).sections ? 'present' : 'ABSENT'; } catch(e) {}
    return JSON.stringify(out);
  })()`);
  console.log(res);
  ws.close();
})().catch(e => { console.error('FATAL:', e.message); process.exit(1); });
