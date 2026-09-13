// Live watcher: attach to the SW and print every native message (750/760/765)
// as it arrives, for 60 seconds. Run BEFORE the user tests.
'use strict';
const durMs = (process.argv[2] && parseInt(process.argv[2], 10)) || 60000;
(async () => {
  const targets = await (await fetch('http://127.0.0.1:9223/json/list')).json();
  const sw = targets.find(t => t.url && t.url.startsWith('chrome-extension://lkaihdpfpifdlgoapbfocpmekbokmcfd') && t.type === 'service_worker');
  const ws = new WebSocket(sw.webSocketDebuggerUrl);
  await new Promise((res, rej) => { ws.onopen = res; ws.onerror = rej; });
  let id = 0;
  const pending = new Map();
  ws.onmessage = e => {
    const m = JSON.parse(e.data);
    if (m.id && pending.has(m.id)) { pending.get(m.id)(m); pending.delete(m.id); }
    if (m.method === 'Runtime.consoleAPICalled') {
      const args = (m.params.args || []).map(a => a.value !== undefined ? a.value : a.description || '').join(' ');
      const d = new Date(m.params.timestamp * 1000);
      if (/750|760|765|800|Trigger|CAPTURE|RBTN/.test(args)) {
        console.log(d.toLocaleTimeString() + ' [' + m.params.type + '] ' + args.slice(0, 400));
      }
    }
  };
  const send = (method, params) => new Promise(res => { const i = ++id; pending.set(i, res); ws.send(JSON.stringify({ id: i, method, params })); });
  await send('Runtime.enable', {});
  console.log('WATCHING for 750/760/765/800 for ' + (durMs / 1000) + 's — WHEEL OVER OMNIBOX AND TAB STRIP NOW');
  await new Promise(r => setTimeout(r, durMs));
  ws.close();
  console.log('watch ended');
  process.exit(0);
})().catch(e => { console.error('FATAL:', e.message); process.exit(1); });
