// CDP: restore the test trigger to the user's original state and unwrap _Lk.
// Usage: node Test/cdp_cleanup_test.js [port]
'use strict';
const port = process.argv[2] || '9223';
const CDP = `http://127.0.0.1:${port}`;
const EXT_ID = 'lkaihdpfpifdlgoapbfocpmekbokmcfd';
(async () => {
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
  await send('Runtime.enable');
  const r = await send('Runtime.evaluate', {
    expression: `(async () => {
      const out = {};
      try {
        const a = await chrome.storage.local.get('trigActList');
        const l = a.trigActList || [];
        const t = l.find(x => x[0] === '12');
        if (t) {
          delete t[1].triggers[0].preconds;
          t[1].title = 'right-btn => pin tab';
          await chrome.storage.local.set({ trigActList: l });
          out.restored = JSON.stringify(t[1].triggers[0]);
        } else out.restored = 'no trig 12';
      } catch (e) { out.err = String(e); }
      try {
        if (window.__acOrigLk) {
          window._Lk = (a2, b, c, g) => self._acNativeSend(a2, b, c, g);
          out.lk = 'restored';
        } else out.lk = 'no wrapper';
      } catch (e) { out.lkErr = String(e); }
      return out;
    })()`,
    awaitPromise: true,
    returnByValue: true,
  });
  console.log(JSON.stringify(r.result && r.result.result && r.result.result.value));
  ws.close();
})().catch(e => { console.error('FATAL:', e.message); process.exit(1); });
