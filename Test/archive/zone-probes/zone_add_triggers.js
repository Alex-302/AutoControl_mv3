// Add two test triggers to the DEV config:
//   '90' — wheel over TAB STRIP (region 12) → reload hoveredTabs
//   '91' — wheel over OMNIBOX (region 21) → switchLeft currentTab
// Distinct actions so the two zones cannot be confused. The storage change
// triggers the SW rebuild → type 60 to the native.
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
  const expr = `(async () => {
    const a = await chrome.storage.local.get('trigActList');
    const l = a.trigActList || [];
    const out = l.filter(x => x[0] !== '90' && x[0] !== '91');
    out.push(['90', {
      actions: [{ sequence: [{ action: 'reload', params: {} }], targets: 'hoveredTabs' }],
      triggers: [
        { combins: [{ block: 1, eventId: 512, wildcard: 2 }], preconds: { mouseOver: [{ region: 12 }] } },
        { combins: [{ block: 1, eventId: 1536, wildcard: 2 }], preconds: { mouseOver: [{ region: 12 }] } }
      ]
    }]);
    out.push(['91', {
      actions: [{ sequence: [{ action: 'switchLeft' }], targets: 'currentTab' }],
      triggers: [
        { combins: [{ block: 1, eventId: 512, wildcard: 2 }], preconds: { mouseOver: [{ region: 21 }] } },
        { combins: [{ block: 1, eventId: 1536, wildcard: 2 }], preconds: { mouseOver: [{ region: 21 }] } }
      ]
    }]);
    await chrome.storage.local.set({ trigActList: out });
    return 'added: 90=reload@tabstrip(12), 91=switchLeft@omnibox(21); total=' + out.length;
  })()`;
  console.log(await ev(expr));
  ws.close();
})().catch(e => { console.error('FATAL:', e.message); process.exit(1); });
