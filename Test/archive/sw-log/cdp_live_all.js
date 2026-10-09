// CDP: capture ALL live SW console events after a marker, print everything.
// Usage: node Test/cdp_live_all.js <port> <seconds> [regex-filter]
'use strict';
const port = process.argv[2] || '9223';
const secs = +(process.argv[3] || 15);
const filter = process.argv[4] ? new RegExp(process.argv[4]) : null;
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
  const live = [];
  ws.onmessage = (e) => {
    const m = JSON.parse(e.data);
    if (m.id && pending.has(m.id)) { pending.get(m.id)(m); pending.delete(m.id); }
    else if (m.method === 'Runtime.consoleAPICalled') {
      const ts = m.params.timestamp;
      if (ts >= global.__mark) {
        const type = m.params.type || 'log';
        const txt = (m.params.args || []).map(a => a.value !== undefined ? a.value : (a.description !== undefined ? a.description : '')).join(' ');
        live.push({ ts, type, txt });
      }
    }
  };
  const send = (method, params) => new Promise((res) => {
    const id = ++msgId;
    pending.set(id, res);
    ws.send(JSON.stringify({ id, method, params }));
  });
  await send('Runtime.enable');
  const r = await send('Runtime.evaluate', {
    expression: `(() => {
      self.__mark = Date.now() / 1000;
      if (window.__ctr) { window.__ctr.n = 0; window.__ctr.times = []; }
      return self.__mark;
    })()`,
    returnByValue: true,
  });
  global.__mark = (r.result && r.result.result && r.result.result.value) || 0;
  console.log('marker @' + global.__mark + ' — CLICK NOW for ' + secs + 's...');
  await new Promise(res => setTimeout(res, secs * 1000));
  const c = await send('Runtime.evaluate', {
    expression: `window.__ctr ? window.__ctr.n : 'no ctr'`,
    returnByValue: true,
  });
  console.log('CTR 750s:', (c.result && c.result.result && c.result.result.value));
  const lines = filter ? live.filter(l => filter.test(l.txt)) : live;
  console.log('--- ' + lines.length + ' live lines ---');
  for (const l of lines) {
    console.log('[' + l.type + ' +' + (l.ts - global.__mark).toFixed(2) + 's] ' + l.txt.slice(0, 300));
  }
  ws.close();
}
main().catch(e => { console.error('FATAL:', e.message); process.exit(1); });
