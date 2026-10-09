// Count 750 trigger events by decoded triggerId and check for crashes.
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
  const triggers = [];
  const crashes = [];
  for (const b of backlog) {
    const m = b.args.match(/Trigger 750 id: (\d+).*triggerId: (\d+)/);
    if (m) triggers.push({ t: b.t, id: m[1], trig: m[2] });
    if (/NH-error/.test(b.args)) {
      const d = b.args.match(/native detail type 800 (\{.*\})/);
      crashes.push({ t: b.t, data: d ? d[1] : b.args.slice(0, 200) });
    }
  }
  // group triggers by decoded id, in order
  const byId = {};
  for (const tr of triggers) {
    (byId[tr.trig] = byId[tr.trig] || []).push(new Date(tr.t * 1000).toLocaleTimeString());
  }
  console.log('=== 750 TRIGGERS by triggerId ===');
  for (const k of Object.keys(byId)) {
    console.log('triggerId ' + k + ': ' + byId[k].length + 'x  at ' + byId[k].join(', '));
  }
  console.log('total 750s: ' + triggers.length);
  console.log('=== NH-ERROR CRASHES ===');
  for (const c of crashes.slice(-5)) {
    console.log(new Date(c.t * 1000).toLocaleTimeString() + ' ' + c.data.slice(0, 200));
  }
  console.log('crashes: ' + crashes.length);
})().catch(e => { console.error('FATAL:', e.message); process.exit(1); });
