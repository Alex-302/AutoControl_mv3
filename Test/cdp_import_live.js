// CDP: import a settings file via the REAL SW _ja path (site-bridge import),
// then wait for the config chain to send type 60 to the native.
// Usage: node Test/cdp_import_live.js <port> <file.acs>
'use strict';
const port = process.argv[2] || '9223';
const fs = require('fs');
const http = require('http');
const path = require('path');
const CDP = `http://127.0.0.1:${port}`;
const EXT_ID = 'lkaihdpfpifdlgoapbfocpmekbokmcfd';

const filePath = process.argv[3];
const content = fs.readFileSync(filePath, 'utf8');

// tiny static server for the file
const server = http.createServer((req, res) => {
  res.setHeader('Content-Type', 'application/json');
  res.setHeader('Access-Control-Allow-Origin', '*');
  res.end(content);
});

async function main() {
  await new Promise(res => server.listen(18777, '127.0.0.1', res));
  const url = 'http://127.0.0.1:18777/test.acs';
  const targets = await (await fetch(CDP + '/json/list')).json();
  const sw = targets.find(t => t.url && t.url.startsWith('chrome-extension://' + EXT_ID) && t.type === 'service_worker');
  if (!sw) { console.log('SW not found'); process.exit(2); }
  const ws = new WebSocket(sw.webSocketDebuggerUrl);
  await new Promise((res, rej) => { ws.onopen = res; ws.onerror = rej; });
  let msgId = 0;
  const pending = new Map();
  const events = [];
  ws.onmessage = (e) => {
    const m = JSON.parse(e.data);
    if (m.id && pending.has(m.id)) { pending.get(m.id)(m); pending.delete(m.id); }
    else if (m.method === 'Runtime.consoleAPICalled') {
      events.push((m.params.args || []).map(a => a.value !== undefined ? a.value : a.description || '').join(' '));
    }
  };
  const send = (method, params) => new Promise((res) => {
    const id = ++msgId;
    pending.set(id, res);
    ws.send(JSON.stringify({ id, method, params }));
  });
  await send('Runtime.enable');

  const r = await send('Runtime.evaluate', {
    expression: `(async () => {
      if (typeof window._ja !== 'function') return { err: 'no window._ja' };
      const gen = window._ja('${url}');
      let result = 'started';
      try { gen.next(); } catch (e) { result = 'throw: ' + e.message; }
      return { result, hasJa: true };
    })()`,
    awaitPromise: true,
    returnByValue: true,
  });
  console.log('IMPORT:', JSON.stringify(r.result && r.result.result && r.result.result.value));
  await new Promise(r => setTimeout(r, 6000));
  console.log('--- SW console (last 25) ---');
  events.slice(-25).forEach(l => console.log(l));
  ws.close();
  server.close();
}
main().catch(e => { console.error('FATAL:', e); process.exit(1); });
