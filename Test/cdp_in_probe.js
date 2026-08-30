// CDP: probe the .in() membership helper at runtime in the SW.
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
  await send('Runtime.enable');
  const r = await send('Runtime.evaluate', {
    expression: `(() => {
      const out = {};
      out.xt = typeof _Xt === 'function' ? _Xt('negate', ['negate', 'oper']) : 'NO _Xt';
      out.ii = typeof _Ii === 'function' ? JSON.stringify(_Ii(['negate', 'oper'])) : 'NO _Ii';
      out.ii2 = typeof _Ii === 'function' ? JSON.stringify(_Ii('negate', 'oper')) : 'NO _Ii';
      out.inType = typeof 'negate'.in;
      out.inFn = ('negate'.in).toString().slice(0, 160);
      out.inCall = 'negate'.in(['negate', 'oper']);
      out.inCall2 = 'negate'.in('negate');
      out.concat = JSON.stringify([].concat(['negate', 'oper']));
      out.inOnObj = ({ a: 1 }).in('a');
      out.hasOwnIn = Object.prototype.hasOwnProperty.call(Object.prototype, 'in');
      return out;
    })()`,
    returnByValue: true,
  });
  const v = r.result && r.result.result && r.result.result.value;
  console.log(JSON.stringify(v, null, 1));
  ws.close();
}
main().catch(e => { console.error('FATAL:', e); process.exit(1); });
