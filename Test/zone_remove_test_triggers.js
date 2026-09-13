// zone_remove_test_triggers.js - remove leftover TEST triggers from storage
// (the ones added by Test/zone_add_test.js or by the pre-baked sets that now
// live in Test/archive/zone-probes/) and restore the user's config.
//
// Usage: node Test/zone_remove_test_triggers.js [port]
'use strict';
const PORT = process.argv[2] || '9223';
const EXT = 'lkaihdpfpifdlgoapbfocpmekbokmcfd';
const REMOVE = ['92', '93', '95', '96'];

(async () => {
  const targets = await (await fetch(`http://127.0.0.1:${PORT}/json/list`)).json();
  const sw = targets.find(t => t.url && t.url.startsWith('chrome-extension://' + EXT) && t.type === 'service_worker');
  if (!sw) { console.log('NO SW'); process.exit(1); }
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
  const expr = `(async () => {
    const a = await chrome.storage.local.get('trigActList');
    const l = a.trigActList || [];
    const keep = l.filter(x => !${JSON.stringify(REMOVE)}.includes(String(x[0])));
    await chrome.storage.local.set({ trigActList: keep });
    return 'removed ${REMOVE.join(",")}; remaining triggers: ' + keep.map(x => x[0]).join(',');
  })()`;
  console.log(await ev(expr));
  ws.close();
})().catch(e => { console.error('FATAL:', e.message); process.exit(1); });
