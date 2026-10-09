// Test whether _lr sends type 65 (advOpts/filter) to the native.
'use strict';
(async () => {
  const targets = await (await fetch('http://127.0.0.1:9223/json/list')).json();
  const sw = targets.find(t => t.url && t.url.startsWith('chrome-extension://lkaihdpfpifdlgoapbfocpmekbokmcfd') && t.type === 'service_worker');
  const ws = new WebSocket(sw.webSocketDebuggerUrl);
  await new Promise((res, rej) => { ws.onopen = res; ws.onerror = rej; });
  let id = 0;
  const pending = new Map();
  let live = [];
  ws.onmessage = (e) => {
    const m = JSON.parse(e.data);
    if (m.id && pending.has(m.id)) { pending.get(m.id)(m); pending.delete(m.id); }
    else if (m.method === 'Runtime.consoleAPICalled') {
      live.push('[' + m.params.type + '] ' + (m.params.args || []).map(a => a.value !== undefined ? a.value : (a.description || '')).join(' '));
    }
  };
  const send = (method, params) => new Promise((res) => {
    const i = ++id;
    pending.set(i, res);
    ws.send(JSON.stringify({ id: i, method, params }));
  });
  await send('Runtime.enable');
  await new Promise(r => setTimeout(r, 4000));
  live = [];
  const expr = `new Promise((res)=>{try{_lr((b)=>{res('lr-ok advOpts='+JSON.stringify(b&&b.advOpts))})}catch(e){res('ERR '+e.message)}})`;
  const r = await send('Runtime.evaluate', { expression: expr, awaitPromise: true, returnByValue: true });
  console.log('LR:', r.result && r.result.result && r.result.result.value);
  await new Promise(r => setTimeout(r, 3000));
  console.log('--- live native sends ---');
  live.filter(l => /→ Native type/.test(l)).slice(0, 10).forEach(l => console.log(l.slice(0, 170)));
  ws.close();
})().catch(e => { console.error('FATAL:', e.message); process.exit(1); });
