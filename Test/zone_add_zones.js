// zone_add_zones.js - add TEST triggers for the zones under investigation.
//
// Adds (idempotent):
//   92 - wheel over the tab's CLOSE button (region 15) -> switchRight currentTab
//   93 - wheel over the tab's SPEAKER icon  (region 17) -> switchLeft  currentTab
//   95 - wheel over the BROWSER MENU button (region 30) -> switchRight currentTab
// Distinct actions so a firing trigger is identifiable; the storage change
// makes the SW rebuild the zone map (storage.onChanged) and send type 60.
//
// Usage: node Test/zone_add_zones.js
'use strict';
const PORT = process.argv[2] || '9223';
const EXT = 'lkaihdpfpifdlgoapbfocpmekbokmcfd';

const DEFS = [
  ['92', 15],
  ['93', 17],
  ['95', 30],
  ['96', 16]
];

(async () => {
  const targets = await (await fetch(`http://127.0.0.1:${PORT}/json/list`)).json();
  const sw = targets.find(t => t.url && t.url.startsWith('chrome-extension://' + EXT) && t.type === 'service_worker');
  if (!sw) { console.log('NO SW'); process.exit(1); }
  const ws = new WebSocket(sw.webSocketDebuggerUrl);
  await new Promise((res, rej) => { ws.onopen = res; ws.onerror = rej; });
  let id = 0;
  const pending = new Map();
  ws.onmessage = e => {
    const m = JSON.parse(e.data);
    if (m.id && pending.has(m.id)) { pending.get(m.id)(m); pending.delete(m.id); }
  };
  const send = (method, params) => new Promise(res => { const i = ++id; pending.set(i, res); ws.send(JSON.stringify({ id: i, method, params })); });
  const ev = async (expr) => {
    const r = await send('Runtime.evaluate', { expression: expr, awaitPromise: true, returnByValue: true });
    const v = r.result && r.result.result && r.result.result.value;
    if (r.result && r.result.exceptionDetails) return 'EXC: ' + JSON.stringify(r.result.exceptionDetails.exception && r.result.exceptionDetails.exception.description);
    return v;
  };

  const ids = DEFS.map(d => d[0]);
  const expr = `(async () => {
    const a = await chrome.storage.local.get('trigActList');
    const l = a.trigActList || [];
    const keep = l.filter(x => !${JSON.stringify(ids)}.includes(String(x[0])));
    const defs = ${JSON.stringify(DEFS)};
    for (const [tid, region] of defs) {
      keep.push([tid, {
        actions: [{ sequence: [{ action: 'switchRight', params: {} }], targets: 'currentTab' }],
        sctnId: undefined,   // see zone_add_test12.js: a missing section hides the trigger
        triggers: [
          { combins: [{ block: 1, eventId: 512, wildcard: 2 }], preconds: { mouseOver: [{ region: region }] } },
          { combins: [{ block: 1, eventId: 1536, wildcard: 2 }], preconds: { mouseOver: [{ region: region }] } }
        ]
      }]);
    }
    await chrome.storage.local.set({ trigActList: keep });
    return 'triggers now: ' + keep.map(x => x[0] + ':[' + (x[1].triggers || []).map(tr => ((tr.preconds || {}).mouseOver || []).map(y => y.region).join('/')).join(' ') + ']').join(' ');
  })()`;
  console.log(await ev(expr));
  await new Promise(r => setTimeout(r, 2500)); // let the SW rebuild + send type 60
  console.log(await ev("(typeof __acZoneMap !== 'undefined') ? 'map: ' + JSON.stringify(__acZoneMap) : 'map var not reachable'"));
  ws.close();
})().catch(e => { console.error('FATAL:', e.message); process.exit(1); });
