// Dump ALL action-execution related console lines: Executing trigger, AC-ACT,
// action errors, plus recent 750s.
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
      backlog.push({ t: m.params.timestamp, args });
    }
  };
  const send = (method, params) => new Promise(res => { const i = ++id; pending.set(i, res); ws.send(JSON.stringify({ id: i, method, params })); });
  await send('Runtime.enable', {});
  await new Promise(r => setTimeout(r, 2500));
  ws.close();
  const pat = /Executing trigger|AC-ACT|action|Trigger 750|switchLeft|reload|scrollWins|_6y|ERROR|error|stuck|Queue/;
  for (const b of backlog) {
    if (pat.test(b.args)) {
      const d = new Date(b.t * 1000);
      console.log(d.toLocaleTimeString() + ' ' + b.args.slice(0, 300));
    }
  }
  console.log('--- total: ' + backlog.length);
})().catch(e => { console.error('FATAL:', e.message); process.exit(1); });
