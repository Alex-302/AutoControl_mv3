// Dump SW console backlog: everything around the type-800 at 17:25 and all
// native-message traffic after it (what has the engine been doing since).
'use strict';
(async () => {
  const targets = await (await fetch('http://127.0.0.1:9223/json/list')).json();
  const sw = targets.find(t => t.url && t.url.startsWith('chrome-extension://lkaihdpfpifdlgoapbfocpmekbokmcfd') && t.type === 'service_worker');
  const ws = new WebSocket(sw.webSocketDebuggerUrl);
  await new Promise((res, rej) => { ws.onopen = res; ws.onerror = rej; });
  let id = 0;
  const pending = new Map();
  const backlog = [];
  ws.onmessage = e => {
    const m = JSON.parse(e.data);
    if (m.id && pending.has(m.id)) { pending.get(m.id)(m); pending.delete(m.id); }
    if (m.method === 'Runtime.consoleAPICalled') {
      const args = (m.params.args || []).map(a => a.value !== undefined ? a.value : a.description || '').join(' ');
      backlog.push({ t: m.params.timestamp, type: m.params.type, args });
    }
  };
  const send = (method, params) => new Promise(res => { const i = ++id; pending.set(i, res); ws.send(JSON.stringify({ id: i, method, params })); });
  await send('Runtime.enable', {});
  await new Promise(r => setTimeout(r, 2500));
  ws.close();
  // all lines with timestamps, sorted; print from the first 800 line onwards
  const eightHundred = backlog.findIndex(b => /type 800/.test(b.args));
  const start = eightHundred >= 0 ? Math.max(0, eightHundred - 5) : 0;
  const slice = backlog.slice(start);
  // collapse the periodic 765/30 spam: show one representative line per second
  let lastT = 0;
  for (const b of slice) {
    const s = b.t;
    const is765 = /765/.test(b.args);
    if (is765 && s - lastT < 1000) continue;
    lastT = s;
    const d = new Date(s * 1000);
    console.log(d.toLocaleTimeString() + '.' + String(d.getMilliseconds()).padStart(3, '0') + ' [' + b.type + '] ' + b.args.slice(0, 500));
  }
  console.log('--- total lines from 800 point: ' + slice.length);
})().catch(e => { console.error('FATAL:', e.message); process.exit(1); });
