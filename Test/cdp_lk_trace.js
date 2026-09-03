// CDP: wrap _Lk to intercept type-60 sends, run _Gf, report.
// Usage: node Test/cdp_lk_trace.js [port]
'use strict';
const port = process.argv[2] || '9223';
const CDP = `http://127.0.0.1:${port}`;
const EXT_ID = 'lkaihdpfpifdlgoapbfocpmekbokmcfd';

async function evalIn(ws, send, expression, awaitPromise = false) {
  const r = await send('Runtime.evaluate', { expression, awaitPromise, returnByValue: true });
  const res = r.result && r.result.result;
  return res;
}

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

  // wrap _Lk (save the ORIGINAL on window.__acOrigLk so cdp_unwrap.js can
  // restore it — NEVER delete window._Lk: it is the only global reference
  // to the shim's _Lk; deleting breaks closeMenu/moveSelectMark until the
  // SW restarts).
  await evalIn(ws, send, `(() => {
    if (window.__acLkWrapped) return 'already';
    const orig = _Lk;
    window.__acOrigLk = orig;
    window.__acLkCalls = [];
    window._Lk = function (a, b, c, g) {
      if (a === 60) {
        const keys = b && b.map ? Object.keys(b.map).map(Number).sort((x,y)=>x-y) : null;
        const kb = [];
        if (b && b.map && b.list) {
          for (const k of Object.keys(b.map)) {
            const key = +k - 22025;
            if (key > 0 && key < 256 || key === 512 || key === 1536 || key === 1026) {
              kb.push(key + '→' + JSON.stringify(b.list[b.map[k][0]]));
            }
          }
        }
        window.__acLkCalls.push({ t: Date.now(), keys, kb });
      }
      return orig.apply(this, arguments);
    };
    window.__acLkWrapped = true;
    return 'wrapped';
  })()`);

  // run the rebuild
  const r = await evalIn(ws, send, `(function(){ try { _Gf({}, function(){ console.warn('[AC-MV3] GFCB fired'); }); return 'started'; } catch(e) { return 'THREW: ' + (e && e.stack || e); } })()`);
  console.log('started:', JSON.stringify(r && r.value));
  await new Promise((res) => setTimeout(res, 15000));

  const dump = await evalIn(ws, send, `(() => {
    const calls = window.__acLkCalls || [];
    return { count: calls.length, calls: calls.map(c => ({ dt: Date.now() - c.t, keys: c.keys, kb: c.kb })) };
  })()`);
  console.log(JSON.stringify(dump && dump.value, null, 2));
  ws.close();
}
main().catch(e => { console.error('FATAL:', e); process.exit(1); });
