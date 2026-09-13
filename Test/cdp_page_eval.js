// cdp_page_eval.js - evaluate an expression in a PAGE target (not the SW).
// Used to read scroll positions / DOM state of the settings page, which
// chrome.scripting cannot touch (extension pages are not injectable).
//
// Usage: node Test/cdp_page_eval.js <port> <urlSubstring> "<expr>" [--await]
'use strict';
const PORT = process.argv[2] || '9223';
const MATCH = process.argv[3] || 'main.html';
const EXPR = process.argv[4] || '1';
const AWAIT = process.argv.includes('--await');

(async () => {
  const targets = await (await fetch(`http://127.0.0.1:${PORT}/json/list`)).json();
  const page = targets.find(t => t.type === 'page' && (t.url || '').indexOf(MATCH) !== -1);
  if (!page) { console.log('NO PAGE for ' + MATCH); process.exit(1); }
  const ws = new WebSocket(page.webSocketDebuggerUrl);
  await new Promise((res, rej) => { ws.onopen = res; ws.onerror = rej; });
  const send = (method, params) => new Promise(res => {
    const id = send.n = (send.n || 0) + 1;
    const onMsg = e => { const m = JSON.parse(e.data); if (m.id === id) { ws.removeEventListener('message', onMsg); res(m); } };
    ws.addEventListener('message', onMsg);
    ws.send(JSON.stringify({ id, method, params }));
  });
  const r = await send('Runtime.evaluate', { expression: EXPR, awaitPromise: AWAIT, returnByValue: true });
  const res = r.result || {};
  if (res.exceptionDetails) console.log('EXC: ' + (res.exceptionDetails.exception && res.exceptionDetails.exception.description || res.exceptionDetails.text));
  if (res.result) console.log('VALUE: ' + JSON.stringify(res.result.value));
  ws.close();
})().catch(e => { console.log('ERR ' + e.message); process.exit(1); });
