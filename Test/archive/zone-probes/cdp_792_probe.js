// CDP probe: compile a SYNTHETIC RMB trigger with a mouseOver precond
// IN-MEMORY, send it to the native as type 60, and verify the engine's zone
// classification: RMB at the cursor position fires 750 iff the point is
// classified as the given region. The REAL user config is restored at the
// end via _lr/_Gf (storage-driven rebuild). Nothing in storage is modified.
//
// Usage:
//   node Test/cdp_792_probe.js <port> <arm|restore|dump> [region]
//     arm     — compile + send the synthetic config for <region>
//               (default 3), then RMB at the probe point and watch for 750
//     restore — re-run the real config chain (_lr -> _Gf) and report the
//               compiled key count (proves the user config is back)
//     dump    — print the compiled synthetic payload entries for the RMB key
'use strict';
const port = process.argv[2] || '9223';
const mode = process.argv[3] || 'dump';
const region = Number(process.argv[4] || 3);
const CDP = `http://127.0.0.1:${port}`;
const EXT_ID = 'lkaihdpfpifdlgoapbfocpmekbokmcfd';

const TRIGGER = JSON.stringify({
  natHostInstalled: true,
  sections: [{ id: 3, name: 'probe' }],
  trigActList: [['99', {
    actions: [{ sequence: [{ action: 'setVolume', params: { mode: 'toggle', target: ':sys' } }], targets: 'hoveredTabs' }],
    sctnId: '3',
    triggers: [{
      combins: [{ block: 2, eventId: 2, wildcard: 2 }],   // RMB (block-up)
      preconds: { mouseOver: [{ region }] }               // zone under test
    }]
  }]]
});

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

  const expr = mode === 'arm' ? `(async () => {
    const DATA = ${TRIGGER};
    const out = {};
    try {
      const ta = {};
      for (const [id, t] of DATA.trigActList) ta[id] = t;
      const payload = _mh(Object.entries(ta), {}, {});
      out.mapKeys = Object.keys(payload.map).map(Number).sort((a,b)=>a-b);
      out.rbtn = {};
      for (const k of Object.keys(payload.map)) {
        const keyId = Number(k) - 22025;
        if (keyId === 2 || keyId === 1026) {
          out.rbtn[k] = payload.map[k].map(i => JSON.parse(JSON.stringify(payload.list[i])));
        }
      }
      _Lk(60, payload);   // send the synthetic config to the native
      out.sent = true;
    } catch (e) { out.err = String(e && e.stack || e); }
    return out;
  })()`
  : mode === 'restore' ? `(async () => {
    const out = {};
    try {
      // Real config chain from storage (same call sw.js uses to heal _if)
      await new Promise((res) => {
        const done = () => res();
        if (typeof _lr === 'function') _lr(() => { try { _Gf({}, done); } catch (e) { done(); } });
        else if (typeof _Gf === 'function') _Gf({}, done);
        else done();
      });
      out.ek = Object.keys(_ek || {}).length;
      out.restored = true;
    } catch (e) { out.err = String(e && e.stack || e); }
    return out;
  })()`
  : `(async () => {
    const DATA = ${TRIGGER};
    const out = {};
    try {
      const ta = {};
      for (const [id, t] of DATA.trigActList) ta[id] = t;
      const payload = _mh(Object.entries(ta), {}, {});
      out.mapKeys = Object.keys(payload.map).map(Number).sort((a,b)=>a-b);
      out.entries = {};
      for (const k of Object.keys(payload.map)) {
        const keyId = Number(k) - 22025;
        if (keyId === 2 || keyId === 1026) {
          out.entries[k] = payload.map[k].map(i => JSON.parse(JSON.stringify(payload.list[i])));
        }
      }
    } catch (e) { out.err = String(e && e.stack || e); }
    return out;
  })()`;

  const r = await send('Runtime.evaluate', { expression: expr, awaitPromise: true, returnByValue: true });
  const res = r.result && r.result.result;
  if (res && res.value !== undefined) console.log(JSON.stringify(res.value, null, 1));
  else if (res && res.description !== undefined) console.log('DESC:', res.description);
  if (r.result && r.result.exceptionDetails) {
    console.log('EXC:', r.result.exceptionDetails.text, r.result.exceptionDetails.exception && r.result.exceptionDetails.exception.description);
  }
  ws.close();
}
main().catch(e => { console.error('FATAL:', e.message); process.exit(1); });
