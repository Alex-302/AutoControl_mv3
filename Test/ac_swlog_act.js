// CDP: capture ONLY the SW console lines produced AFTER the injected action.
// The session backlog is replayed on Runtime.enable, so we mark the buffer end
// after a settle delay and print just the new lines.
//
// Usage:
//   node Test/ac_swlog_act.js 9223 "<powershell command line to run>"
//   node Test/ac_swlog_act.js 9223                      (no injection, just sit)
//
// Example (wheel over the page):
//   node Test/ac_swlog_act.js 9223 "powershell -NoProfile -ExecutionPolicy Bypass -File Test/zone_fg_wheel.ps1 -Hwnd 773928210 -Point 1000,800 -Notches 2"
'use strict';
const { execFileSync } = require('child_process');
const port = process.argv[2] || '9223';
const inject = process.argv[3] || '';
const CDP = `http://127.0.0.1:${port}`;
const EXT_ID = 'lkaihdpfpifdlgoapbfocpmekbokmcfd';

const sleep = (ms) => new Promise(r => setTimeout(r, ms));

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
  await sleep(1500);                       // let the replayed backlog arrive
  const mark = logs.length;
  console.log('backlog lines: ' + mark + (inject ? ' | injecting...' : ''));
  if (inject) {
    try {
      const out = execFileSync('powershell', ['-NoProfile', '-ExecutionPolicy', 'Bypass', '-Command', inject], { encoding: 'utf8' });
      console.log('PS: ' + out.trim().split('\n').slice(-1)[0]);
    } catch (e) { console.log('PS ERR: ' + e.message); }
  }
  await sleep(2600);
  const fresh = logs.slice(mark);
  console.log('--- new lines (' + fresh.length + ') ---');
  fresh.forEach(l => console.log(l));
  ws.close();
}
main().catch(e => { console.error('FATAL:', e.message); process.exit(1); });
