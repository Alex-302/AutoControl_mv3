// ac_swlog_dump.js - READ-ONLY dump of the service-worker console (including
// the session backlog that Runtime.enable replays on attach). Nothing is
// injected and no state is touched; safe to run any time.
//
// Usage: node Test/ac_swlog_dump.js <port> [regex] [maxLines]
'use strict';
const PORT = process.argv[2] || '9223';
const FILTER = process.argv[3] || '';
const MAX = Number(process.argv[4] || 80);
const EXT = 'lkaihdpfpifdlgoapbfocpmekbokmcfd';
const CDP = `http://127.0.0.1:${PORT}`;

(async () => {
  const targets = await (await fetch(CDP + '/json/list')).json();
  const sw = targets.find(t => t.url && t.url.startsWith('chrome-extension://' + EXT) && t.type === 'service_worker');
  if (!sw) { console.log('NO SW TARGET'); process.exit(2); }
  const ws = new WebSocket(sw.webSocketDebuggerUrl);
  await new Promise((res, rej) => { ws.onopen = res; ws.onerror = rej; });
  const lines = [];
  let msgId = 0;
  const pending = new Map();
  ws.onmessage = (e) => {
    const m = JSON.parse(e.data);
    if (m.id && pending.has(m.id)) { pending.get(m.id)(m); pending.delete(m.id); return; }
    if (m.method === 'Runtime.consoleAPICalled') {
      const txt = (m.params.args || []).map(a => a.value !== undefined ? a.value : (a.description !== undefined ? a.description : '')).join(' ');
      lines.push('[' + (m.params.type || 'log') + '] ' + txt);
    }
  };
  const send = (method, params) => new Promise((res) => {
    const id = ++msgId; pending.set(id, res); ws.send(JSON.stringify({ id, method, params }));
  });
  await send('Runtime.enable');
  await new Promise(r => setTimeout(r, 2500));
  const re = FILTER ? new RegExp(FILTER, 'i') : null;
  const hit = lines.filter(l => !re || re.test(l));
  console.log('total lines in SW buffer: ' + lines.length + ' | matching: ' + hit.length);
  hit.slice(-MAX).forEach(l => console.log(l));
  ws.close();
})().catch(e => { console.error('FATAL: ' + e.message); process.exit(1); });
