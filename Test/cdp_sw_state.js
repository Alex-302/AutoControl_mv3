// CDP: evaluate SW state (_ek/_if/_Lk) — quick global dump.
// Usage: node Test/cdp_sw_state.js [port]
'use strict';
const port = process.argv[2] || '9223';
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
  ws.onmessage = (e) => {
    const m = JSON.parse(e.data);
    if (m.id && pending.has(m.id)) { pending.get(m.id)(m); pending.delete(m.id); }
  };
  const send = (method, params) => new Promise((res) => {
    const id = ++msgId;
    pending.set(id, res);
    ws.send(JSON.stringify({ id, method, params }));
  });
  const r = await send('Runtime.evaluate', {
    expression: `(() => {
      const out = {};
      out.ek = (typeof _ek !== 'undefined' && _ek) ? Object.keys(_ek) : 'undef';
      out.ifKeys = (typeof _if !== 'undefined' && _if) ? Object.keys(_if) : 'undef';
      out.ifBinSwtch = (typeof _if !== 'undefined' && _if && _if.binSwtch) ? 'ok' : 'EMPTY';
      out.ifMenuSpec = (typeof _if !== 'undefined' && _if && _if.menuSpec) ? Object.keys(_if.menuSpec) : 'none';
      out.ifTse = (typeof _if !== 'undefined' && _if && _if.tse) ? Object.keys(_if.tse).slice(0, 10) : 'none';
      out.LkType = typeof _Lk;
      out.VyType = typeof _Vy;
      try { out.connViaEval = (0, eval)('typeof connected'); } catch (e) { out.connViaEval = 'ERR'; }
      return out;
    })()`,
    returnByValue: true,
  });
  const res = r.result && r.result.result;
  console.log(JSON.stringify(res && res.value, null, 2));
  ws.close();
}
main().catch(e => { console.error('FATAL:', e); process.exit(1); });
