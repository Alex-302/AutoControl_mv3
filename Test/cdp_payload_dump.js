// CDP: build the type-60 payload in-memory (no native send) and dump the
// compiled entries for the keys involved in Ctrl+Tab smart switching.
// Usage: node Test/cdp_payload_dump.js [port]
'use strict';
const fs = require('fs');
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
    expression: `(async () => {
      const out = {};
      try {
        if (typeof _Gf !== 'function' || typeof _mh !== 'function') { out.err = 'missing _Gf/_mh'; return out; }
        await new Promise((resolve, reject) => {
          let settled = false;
          const finish = (o) => { if (!settled) { settled = true; Object.assign(out, o); resolve(); } };
          try {
            const gen = _Gf({}, c => {
              const ta = c && c.trigActList;
              if (ta) {
                try {
                  const payload = _mh(ta, {}, {});
                  window.__acPayload = payload;
                  finish({
                    mapKeys: Object.keys(payload.map).map(Number).sort((a, b) => a - b),
                    listLen: payload.list.length,
                    su: typeof _su !== 'undefined' ? _su : 'undef',
                    trig6: JSON.stringify(ta['6'] && ta['6'].triggers),
                    trig2: JSON.stringify(ta['2'] && ta['2'].triggers),
                    trig1: JSON.stringify(ta['1'] && ta['1'].triggers)
                  });
                } catch (e) { finish({ err: 'mh: ' + e.message }); }
              } else { finish({ err: 'no trigActList from _Gf' }); }
            });
            if (gen && typeof gen.next === 'function') { try { gen.next(); } catch (e) {} }
          } catch (e) { finish({ err: 'gf: ' + e.message }); }
          setTimeout(() => finish({ err: 'timeout waiting _Gf' }), 15000);
        });
        return out;
      } catch (e) { out.err = String(e); return out; }
    })()`,
    awaitPromise: true,
    returnByValue: true,
  });
  const v = r.result && r.result.result && r.result.result.value;
  console.log('BUILD:', JSON.stringify(v));

  const r2 = await send('Runtime.evaluate', {
    expression: `(() => {
      const p = window.__acPayload;
      if (!p) return null;
      const out = {};
      for (const k of Object.keys(p.map)) {
        out[k] = p.map[k].map(i => p.list[i]);
      }
      out.__listLen = p.list.length;
      return out;
    })()`,
    returnByValue: true,
  });
  const v2 = r2.result && r2.result.result && r2.result.result.value;
  fs.writeFileSync(process.env.TEMP + '/ac_payload.json', JSON.stringify(v2, null, 1));
  console.log('=== compiled entries (keys 9/6145/1033/1041/186/187) ===');
  console.log(JSON.stringify(v2, null, 1).slice(0, 9000));
  ws.close();
}
main().catch(e => { console.error('FATAL:', e); process.exit(1); });

