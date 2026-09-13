// Attach to the SW and dump the console backlog, filtering for trigger
// activity (750/760) and capture/rebuild lines.
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
  // wait for the backlog replay
  await new Promise(r => setTimeout(r, 2500));
  ws.close();
  const interesting = backlog.filter(b =>
    /750|760|Trigger|CAPTURE|rebuild|type 60|type60|→ Native|← Native|config/i.test(b.args));
  // last 60 interesting lines, oldest first
  for (const b of interesting.slice(-60)) {
    console.log(new Date(b.t * 1000).toLocaleTimeString() + ' [' + b.type + '] ' + b.args.slice(0, 400));
  }
  console.log('--- total console lines: ' + backlog.length + ', interesting: ' + interesting.length);
})().catch(e => { console.error('FATAL:', e.message); process.exit(1); });
