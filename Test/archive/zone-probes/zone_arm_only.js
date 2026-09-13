// Minimal arm: send the synthetic RMB+mouseOver(region 3) config to the
// native with live verification. NO storage changes (avoids rebuilds that
// would overwrite the synthetic config).
'use strict';
(async () => {
  const targets = await (await fetch('http://127.0.0.1:9223/json/list')).json();
  const sw = targets.find(t => t.url && t.url.startsWith('chrome-extension://lkaihdpfpifdlgoapbfocpmekbokmcfd') && t.type === 'service_worker');
  const ws = new WebSocket(sw.webSocketDebuggerUrl);
  await new Promise((res, rej) => { ws.onopen = res; ws.onerror = rej; });
  let msgId = 0;
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
    const i = ++msgId;
    pending.set(i, res);
    ws.send(JSON.stringify({ id: i, method, params }));
  });
  const ev = async (expr) => {
    const r = await send('Runtime.evaluate', { expression: expr, awaitPromise: true, returnByValue: true });
    return r.result && r.result.result && r.result.result.value;
  };
  await send('Runtime.enable');
  await new Promise(r => setTimeout(r, 4000));
  live = [];
  const dataObj = {
    trigActList: [['99', {
      actions: [{ sequence: [{ action: 'setVolume', params: { mode: 'toggle', target: ':sys' } }], targets: 'hoveredTabs' }],
      sctnId: '3',
      triggers: [{ combins: [{ block: 2, eventId: 2, wildcard: 2 }], preconds: { mouseOver: [{ region: 3 }] } }]
    }]]
  };
  const expr = `(async () => {
    const DATA = ${JSON.stringify(dataObj)};
    const ta = {};
    for (const [i, v] of DATA.trigActList) ta[i] = v;
    try { _Lk(60, _mh(Object.entries(ta), {}, {})); return 'armed'; }
    catch (e) { return 'ERR ' + e.message; }
  })()`;
  console.log('arm:', await ev(expr));
  await new Promise(r => setTimeout(r, 2000));
  const t60 = live.filter(l => /→ Native type 60/.test(l)).length;
  console.log('live type-60 after arm:', t60);
  ws.close();
})().catch(e => { console.error('FATAL:', e.message); process.exit(1); });
