// CDP: dump the SW's __acLogBuf (startup log buffer), filtered.
// Usage: node Test/cdp_logbuf.js [filter]
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
      try {
        out.buf = (typeof __acLogBuf !== 'undefined' && __acLogBuf) ? __acLogBuf.map(e => '[' + (e[0] || 'log') + '] ' + e[1].join(' ')) : null;
      } catch (e) { out.err = String(e); }
      try { out.su = (typeof _su !== 'undefined') ? _su : 'undef'; } catch (e) {}
      try { out.pg = (typeof _pg !== 'undefined' && _pg) ? Object.keys(_pg).length : 'undef'; } catch (e) {}
      try { out.trigActList = (typeof _trigActList !== 'undefined' && _trigActList) ? Object.keys(_trigActList).length : 'undef'; } catch (e) {}
      return out;
    })()`,
    returnByValue: true,
  });
  const v = r.result && r.result.result && r.result.result.value;
  if (!v || !v.buf) { console.log('no buffer:', JSON.stringify(v)); ws.close(); return; }
  const filter = process.argv[3] ? new RegExp(process.argv[3], 'i') : null;
  const lines = filter ? v.buf.filter(l => filter.test(l)) : v.buf;
  console.log('BUFFER ' + v.buf.length + ' lines' + (filter ? ', filtered ' + lines.length : '') + ' | _su=' + v.su + ' _pg=' + v.pg + ' trigActList=' + v.trigActList);
  console.log(lines.slice(-120).join('\n'));
  ws.close();
}
main().catch(e => { console.error('FATAL:', e); process.exit(1); });
