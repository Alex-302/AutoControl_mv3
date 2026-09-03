// CDP: compile the ISSUE #1 trigger (RMB, block:2 = block-up) in-memory and
// show what stripRightButtonBlocks does to keys 2/1026.
// Usage: node Test/cdp_rbtn_block_test.js [port]
'use strict';
const port = process.argv[2] || '9223';
const CDP = `http://127.0.0.1:${port}`;
const EXT_ID = 'lkaihdpfpifdlgoapbfocpmekbokmcfd';

const TRIGGER = JSON.stringify({
  natHostInstalled: true,
  sections: [{ id: 3, name: 'test' }],
  trigActList: [['54', {
    actions: [{ sequence: [{ action: 'setVolume', params: { mode: 'toggle', target: ':sys' } }], targets: 'hoveredTabs' }],
    sctnId: '3',
    triggers: [{ combins: [{ block: 2, eventId: 2, wildcard: 2 }] }]
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

  const expr = `(async () => {
    const DATA = ${TRIGGER};
    const out = {};
    try {
      // Build the store-format trigActList map like _Qj would
      const ta = {};
      for (const [id, t] of DATA.trigActList) ta[id] = t;
      out.triggerJson = ta['54'];
      const payload = _mh(Object.entries(ta), {}, {});
      out.mapKeys = Object.keys(payload.map).map(Number).sort((a,b)=>a-b);
      const dump = {};
      for (const k of Object.keys(payload.map)) {
        dump[k] = payload.map[k].map(i => JSON.parse(JSON.stringify(payload.list[i])));
      }
      out.compiled = dump;

      // Simulate the CURRENT sw.js strip (soften ALL block entries on key 1026)
      const soft = (p) => {
        const RBTN_KEY_OFFSET = 22025, RCM_UP_KEY = 1026;
        const newMap = {}, newList = p.list.slice();
        let softened = 0;
        for (const k of Object.keys(p.map)) {
          const keyId = Number(k) - RBTN_KEY_OFFSET;
          if (keyId !== RCM_UP_KEY) { newMap[k] = p.map[k]; continue; }
          const idxs = [];
          for (const idx of p.map[k]) {
            const entry = newList[idx];
            if (entry && entry.block) { newList[idx] = Object.assign({}, entry, { block: false }); softened++; }
            idxs.push(idx);
          }
          if (idxs.length) newMap[k] = idxs;
        }
        return softened ? { map: newMap, list: newList, softened } : { ...p, softened: 0 };
      };
      const stripped = soft(payload);
      out.softened = stripped.softened;
      out.stripped1026 = {};
      for (const k of Object.keys(stripped.map)) {
        out.stripped1026[k] = stripped.map[k].map(i => stripped.list[i]);
      }
    } catch (e) { out.err = String(e && e.stack || e); }
    return out;
  })()`;

  const r = await send('Runtime.evaluate', { expression: expr, awaitPromise: true, returnByValue: true });
  const v = r.result && r.result.result && r.result.result.value;
  console.log(JSON.stringify(v, null, 1).slice(0, 12000));
  ws.close();
}
main().catch(e => { console.error('FATAL:', e); process.exit(1); });
