// CDP: with the menu (hopefully) open — query the native menu state (type 185)
// directly and dump the full result; also check _Lk bindings.
'use strict';
const port = '9223';
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
  const events = [];
  ws.onmessage = (e) => {
    const m = JSON.parse(e.data);
    if (m.id && pending.has(m.id)) { pending.get(m.id)(m); pending.delete(m.id); }
    else if (m.method === 'Runtime.consoleAPICalled') {
      const args = (m.params.args || []).map(a => a.value !== undefined ? a.value : (a.description || a.type));
      events.push({ type: m.params.type, text: args.join(' ') });
    }
  };
  const send = (method, params) => new Promise((res) => {
    const id = ++msgId;
    pending.set(id, res);
    ws.send(JSON.stringify({ id, method, params }));
  });
  await send('Runtime.enable');

  const r1 = await send('Runtime.evaluate', {
    expression: `(() => {
      const out = {};
      try { out.typeof_Lk = typeof _Lk; } catch(e) { out.typeof_Lk = 'ERR'; }
      try { out.typeof_windowLk = typeof window._Lk; } catch(e) { out.typeof_windowLk = 'ERR'; }
      try { out.typeof_acNativeSend = typeof _acNativeSend; } catch(e) { out.typeof_acNativeSend = 'ERR'; }
      try { out.LkSrc = _Lk ? String(_Lk).slice(0, 200) : 'n/a'; } catch(e) { out.LkSrc = 'ERR'; }
      try { out.Ck = JSON.stringify({ id: _Ck && _Ck.id, items: _Ck && _Ck.items && _Ck.items.length, type: _Ck && _Ck.type }); } catch(e) { out.Ck = 'ERR ' + e; }
      try { out.ifMenu = !!(_if && _if.menuSpec && _if.menuSpec['7']); } catch(e) {}
      return out;
    })()`,
    returnByValue: true,
  });
  console.log('BINDINGS:', JSON.stringify(r1.result && r1.result.result && r1.result.result.value, null, 1));

  // query native menu state via type 185 (like selectMarkedItem does)
  events.length = 0;
  const r2 = await send('Runtime.evaluate', {
    expression: `new Promise((res) => {
      let done = false;
      const fin = (x) => { if (!done) { done = true; res(x); } };
      try {
        _Vy(_3f, { usePrvMsPos: false })((r) => {
          let s;
          try { s = JSON.stringify(r); } catch(e) { s = 'UNSERIALIZABLE ' + e; }
          fin({ result: s, type: typeof r, isArray: Array.isArray(r), keys: r && typeof r === 'object' ? Object.keys(r) : null });
        });
        setTimeout(() => fin({ timeout: true }), 4000);
      } catch(e) { fin({ threw: String(e && e.stack || e) }); }
    })`,
    awaitPromise: true,
    returnByValue: true,
  });
  console.log('185 RESULT:', JSON.stringify(r2.result && r2.result.result && r2.result.result.value, null, 1));
  console.log('console during 185:', events.map(e => '[' + e.type + '] ' + e.text.slice(0, 300)).join('\n'));
  ws.close();
}
main().catch(e => { console.error('FATAL:', e); process.exit(1); });
