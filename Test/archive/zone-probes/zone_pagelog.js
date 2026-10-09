// Dump the settings page console (the boot import runs page-side).
'use strict';
(async () => {
  const targets = await (await fetch('http://127.0.0.1:9223/json/list')).json();
  const page = targets.find(t => t.type === 'page' && t.url.includes('main.html'));
  if (!page) { console.log('settings page not found; tabs: ' + targets.filter(t=>t.type==='page').map(t=>t.url).join(' | ')); process.exit(0); }
  console.log('PAGE: ' + page.url);
  const ws = new WebSocket(page.webSocketDebuggerUrl);
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
  const pat = /import|_Hu|settings|file|trigActList|storage|visible|load|New file|error|Error/i;
  for (const b of backlog) {
    if (pat.test(b.args)) {
      const d = new Date(b.t * 1000);
      console.log(d.toLocaleTimeString() + ' ' + b.args.slice(0, 300));
    }
  }
  console.log('--- total page console lines: ' + backlog.length);
})().catch(e => { console.error('FATAL:', e.message); process.exit(1); });
