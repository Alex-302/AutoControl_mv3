// CDP helper: evaluate an expression in the extension SW.
// Usage: node Test/cdp_eval.js <port> '<expression>' [--await]
'use strict';
const port = process.argv[2] || '9223';
const expr = process.argv[3];
const doAwait = process.argv.includes('--await');
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
  const r = await send('Runtime.evaluate', { expression: expr, awaitPromise: doAwait, returnByValue: true });
  const res = r.result && r.result.result;
  if (res && res.value !== undefined) console.log('VALUE:', JSON.stringify(res.value));
  else if (res && res.description !== undefined) console.log('DESC:', res.description);
  if (r.result && r.result.exceptionDetails) {
    console.log('EXC:', r.result.exceptionDetails.text, r.result.exceptionDetails.exception && r.result.exceptionDetails.exception.description);
  }
  ws.close();
})().catch(e => { console.error('FATAL:', e.message); process.exit(1); });
