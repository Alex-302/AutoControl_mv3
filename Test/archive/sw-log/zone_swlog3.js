// Dump ALL SW console lines between 17:25 and the last type-60 (22:18),
// plus any connect/handshake/reconnect lines anywhere.
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
  // print every line that mentions connect/handshake/file/reconnect/disc/60/65/72/21/40/750/760/800
  const pat = /Connecting|Handshake|file check|reconnect|disc|type 60|type 65|type 72|type 21|type 40|type 750|type 760|type 800|proceedAfter|config|_Gf|GFCB|startup|21 \(|21\)|Engine|Zero/i;
  for (const b of backlog) {
    if (pat.test(b.args)) {
      const d = new Date(b.t * 1000);
      console.log(d.toLocaleTimeString() + '.' + String(d.getMilliseconds()).padStart(3, '0') + ' [' + b.type + '] ' + b.args.slice(0, 300));
    }
  }
  console.log('--- total: ' + backlog.length);
})().catch(e => { console.error('FATAL:', e.message); process.exit(1); });
