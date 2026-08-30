// CDP: capture SW console output while injecting a real RMB click.
// Usage: node Test/cdp_swlog_rmb.js [port] [rmb|lmb]
'use strict';
const { execFileSync } = require('child_process');
const path = require('path');
const port = process.argv[2] || '9223';
const which = process.argv[3] || 'rmb';
const CDP = `http://127.0.0.1:${port}`;
const EXT_ID = 'lkaihdpfpifdlgoapbfocpmekbokmcfd';

async function main() {
  const targets = await (await fetch(CDP + '/json/list')).json();
  const sw = targets.find(t => t.url && t.url.startsWith('chrome-extension://' + EXT_ID) && t.type === 'service_worker');
  if (!sw) { console.log('SW not found'); process.exit(2); }
  const ws = new WebSocket(sw.webSocketDebuggerUrl);
  await new Promise((res, rej) => { ws.onopen = res; ws.onerror = rej; });
  let msgId = 0;
  const pending = new Map();
  const logs = [];
  ws.onmessage = (e) => {
    const m = JSON.parse(e.data);
    if (m.id && pending.has(m.id)) { pending.get(m.id)(m); pending.delete(m.id); }
    else if (m.method === 'Runtime.consoleAPICalled') {
      const type = m.params.type || 'log';
      const txt = (m.params.args || []).map(a => a.value !== undefined ? a.value : (a.description !== undefined ? a.description : '')).join(' ');
      logs.push('[' + type + '] ' + txt);
    }
  };
  const send = (method, params) => new Promise((res) => {
    const id = ++msgId;
    pending.set(id, res);
    ws.send(JSON.stringify({ id, method, params }));
  });
  await send('Runtime.enable');
  console.log('capturing SW console, injecting ' + which + '...');
  const ps = path.join(__dirname, '_ac_mouse.ps1');
  try {
    const out = execFileSync('powershell', ['-ExecutionPolicy', 'Bypass', '-File', ps, '-Action', which, '-HoldMs', '150'], { encoding: 'utf8' });
    console.log('PS:', out.trim().split('\n').pop());
  } catch (e) { console.log('PS ERR:', e.message); }
  await new Promise(r => setTimeout(r, 2500));
  console.log('--- SW console (' + logs.length + ' lines) ---');
  logs.forEach(l => console.log(l));
  ws.close();
}
main().catch(e => { console.error('FATAL:', e.message); process.exit(1); });
