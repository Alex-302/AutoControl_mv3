// CDP: record the SERVICE WORKER console to a file (background recorder).
// The session backlog is replayed on attach, so a MARKER line is written first
// and everything before it can be ignored when reading the file.
//
// Usage: node Test/ac_swlog_record.js <port> <minutes> [outfile]
'use strict';
const fs = require('fs');
const path = require('path');
const PORT = process.argv[2] || '9223';
const MINUTES = Number(process.argv[3] || 10);
const OUT = process.argv[4] || path.join(process.env.TEMP || '.', 'ac_swlog_live.txt');
const EXT = 'lkaihdpfpifdlgoapbfocpmekbokmcfd';
const CDP = `http://127.0.0.1:${PORT}`;

(async () => {
  const targets = await (await fetch(CDP + '/json/list')).json();
  const sw = targets.find(t => t.url && t.url.startsWith('chrome-extension://' + EXT) && t.type === 'service_worker');
  if (!sw) { console.log('NO SW TARGET'); process.exit(2); }
  const ws = new WebSocket(sw.webSocketDebuggerUrl);
  await new Promise((res, rej) => { ws.onopen = res; ws.onerror = rej; });
  const fd = fs.openSync(OUT, 'w');
  const t0 = Date.now();
  const write = (s) => { try { fs.writeSync(fd, s + '\n'); } catch (e) {} };
  let msgId = 0;
  const pending = new Map();
  ws.onmessage = (e) => {
    const m = JSON.parse(e.data);
    if (m.id && pending.has(m.id)) { pending.get(m.id)(m); pending.delete(m.id); return; }
    if (m.method === 'Runtime.consoleAPICalled') {
      const txt = (m.params.args || []).map(a => a.value !== undefined ? a.value : (a.description !== undefined ? a.description : '')).join(' ');
      const dt = ((Date.now() - t0) / 1000).toFixed(1);
      write('+' + dt + 's [' + (m.params.type || 'log') + '] ' + txt);
    }
  };
  const send = (method, params) => new Promise((res) => {
    const id = ++msgId; pending.set(id, res); ws.send(JSON.stringify({ id, method, params }));
  });
  await send('Runtime.enable');
  // give the backlog a moment, then mark the file so only later lines count
  setTimeout(() => write('=== MARKER ' + new Date().toISOString() + ' recording ' + MINUTES + ' min ==='), 2000);
  write('# recording started ' + new Date().toISOString() + ' | file: ' + OUT);
  console.log('RECORDING to ' + OUT + ' for ' + MINUTES + ' min');
  setTimeout(() => {
    write('=== RECORDING STOPPED ' + new Date().toISOString() + ' ===');
    try { fs.closeSync(fd); } catch (e) {}
    ws.close();
    process.exit(0);
  }, MINUTES * 60 * 1000);
})().catch(e => { console.error('FATAL: ' + e.message); process.exit(1); });
