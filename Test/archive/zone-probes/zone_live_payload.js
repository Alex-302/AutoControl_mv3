// Live compile of the CURRENT storage config via the REAL _mh (no send).
// Prints the type-60 entries for the wheel map keys (22537=512, 23561=1536)
// and all entries with a mouseOver precond (type 14), plus _ek entries for
// the test trigger ids 90/91.
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
  const expr = `(async () => {
    const s = await chrome.storage.local.get(['trigActList', 'mouseGest', 'advOpts']);
    const l = s.trigActList || [];
    const t90 = l.find(x => x[0] === '90');
    const t91 = l.find(x => x[0] === '91');
    const payload = _mh(s.trigActList || [], s.mouseGest || {}, s.advOpts || {});
    const out = {};
    out.storage90 = t90 ? JSON.stringify(t90) : 'MISSING';
    out.storage91 = t91 ? JSON.stringify(t91) : 'MISSING';
    out.ek90 = _ek['90'] ? JSON.stringify(_ek['90']).slice(0, 200) : 'MISSING';
    out.ek91 = _ek['91'] ? JSON.stringify(_ek['91']).slice(0, 200) : 'MISSING';
    out.wheel = {};
    for (const k of ['22537', '23561']) {
      if (!payload.map[k]) { out.wheel[k] = 'NOT REGISTERED'; continue; }
      out.wheel[k] = payload.map[k].map(i => JSON.stringify(payload.list[i]));
    }
    out.mouseOver14 = [];
    payload.list.forEach((e, i) => {
      if (e && Array.isArray(e.preconds) && e.preconds.some(p => p && p.type === 14)) {
        out.mouseOver14.push('[' + i + '] ' + JSON.stringify(e));
      }
    });
    out.totalTriggers = l.length;
    out.mapKeys = Object.keys(payload.map).join(',');
    return JSON.stringify(out);
  })()`;
  const res = await ev(expr);
  try { console.log(JSON.stringify(JSON.parse(res), null, 1)); }
  catch (e) { console.log(res); }
  ws.close();
})().catch(e => { console.error('FATAL:', e.message); process.exit(1); });
