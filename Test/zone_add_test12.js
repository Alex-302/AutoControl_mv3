// zone_add_test12.js - add ONE test trigger for the v19 table check:
//   id 92: plain wheel + mouseOver region 12 (Browser tab) -> reload currentTab
// Enabled on purpose (the user's own triggers are disabled), so a firing
// trigger is unambiguous in the SW log ("trig 92: zones=[...] ∩ [12]").
//
// Usage: node Test/zone_add_test12.js [port]
'use strict';
const PORT = process.argv[2] || '9223';
const EXT = 'lkaihdpfpifdlgoapbfocpmekbokmcfd';

(async () => {
  const targets = await (await fetch(`http://127.0.0.1:${PORT}/json/list`)).json();
  const sw = targets.find(t => t.url && t.url.startsWith('chrome-extension://' + EXT) && t.type === 'service_worker');
  if (!sw) { console.log('NO SW'); process.exit(1); }
  const ws = new WebSocket(sw.webSocketDebuggerUrl);
  await new Promise((res, rej) => { ws.onopen = res; ws.onerror = rej; });
  let id = 0;
  const pending = new Map();
  ws.onmessage = e => { const m = JSON.parse(e.data); if (m.id && pending.has(m.id)) { pending.get(m.id)(m); pending.delete(m.id); } };
  const send = (method, params) => new Promise(res => { const i = ++id; pending.set(i, res); ws.send(JSON.stringify({ id: i, method, params })); });
  const ev = async (expr) => {
    const r = await send('Runtime.evaluate', { expression: expr, awaitPromise: true, returnByValue: true });
    if (r.result && r.result.exceptionDetails) return 'EXC: ' + String(r.result.exceptionDetails.exception && r.result.exceptionDetails.exception.description).slice(0, 300);
    return r.result && r.result.result && r.result.result.value;
  };
  const out = await ev(`(async () => {
    const a = await chrome.storage.local.get('trigActList');
    const l = a.trigActList || [];
    const keep = l.filter(x => String(x[0]) !== '92');
    keep.push(['92', {
      actions: [{ sequence: [{ action: 'reload', params: {} }], targets: 'currentTab' }],
      triggers: [
        { combins: [{ block: 1, eventId: 512, wildcard: 2 }], preconds: { mouseOver: [{ oper: 'or', region: 12 }] } },
        { combins: [{ block: 1, eventId: 1536, wildcard: 2 }], preconds: { mouseOver: [{ oper: 'or', region: 12 }] } }
      ]
    }]);
    await chrome.storage.local.set({ trigActList: keep });
    const zones = await new Promise(r => chrome.storage.local.get('trigActList', r));
    return 'added 92 (region 12, enabled); total=' + keep.length;
  })()`);
  console.log(out);
  ws.close();
})().catch(e => { console.log('ERR ' + e.message); process.exit(1); });
