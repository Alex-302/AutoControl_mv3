// CDP: watch the active page for 'contextmenu' / 'mousedown'/'mouseup' events
// to detect whether the native block lets the RMB pass through to Chrome.
// Usage: node Test/cdp_ctxmenu_watch.js <port> [seconds]
'use strict';
const port = process.argv[2] || '9223';
const seconds = +(process.argv[3] || 6);
const CDP = `http://127.0.0.1:${port}`;
(async () => {
  const targets = await (await fetch(CDP + '/json/list')).json();
  const page = targets.find(t => t.type === 'page' && t.url && t.url.startsWith('http://sxs'));
  if (!page) { console.log('no sxs page'); process.exit(2); }
  const ws = new WebSocket(page.webSocketDebuggerUrl);
  await new Promise((res, rej) => { ws.onopen = res; ws.onerror = rej; });
  let msgId = 0;
  const pending = new Map();
  const events = [];
  ws.onmessage = (e) => {
    const m = JSON.parse(e.data);
    if (m.id && pending.has(m.id)) { pending.get(m.id)(m); pending.delete(m.id); }
    else if (m.method === 'Runtime.consoleAPICalled') {
      const txt = (m.params.args || []).map(a => a.value !== undefined ? a.value : a.description || '').join(' ');
      events.push(txt);
    }
  };
  const send = (method, params) => new Promise((res) => {
    const id = ++msgId;
    pending.set(id, res);
    ws.send(JSON.stringify({ id, method, params }));
  });
  await send('Runtime.enable');
  await send('Runtime.evaluate', {
    expression: `(() => {
      window.__ctx = { mousedown: 0, mouseup: 0, contextmenu: 0, buttons: [] };
      for (const t of ['mousedown', 'mouseup', 'contextmenu']) {
        window.addEventListener(t, (e) => {
          window.__ctx[t]++;
          window.__ctx.buttons.push(t + ':' + e.button);
          console.log('[CTX]', t, 'button=' + e.button);
        }, true);
      }
      return 'listeners installed';
    })()`,
    returnByValue: true,
  });
  console.log('watching for', seconds, 's — inject the RMB click now...');
  await new Promise(r => setTimeout(r, seconds * 1000));
  const r = await send('Runtime.evaluate', {
    expression: `({ counts: window.__ctx, recent: window.__ctx.buttons.slice(-20) })`,
    returnByValue: true,
  });
  console.log('COUNTS:', JSON.stringify(r.result && r.result.result && r.result.result.value));
  console.log('--- page console ---');
  events.slice(-30).forEach(l => console.log(l));
  ws.close();
})().catch(e => { console.error('FATAL:', e.message); process.exit(1); });
