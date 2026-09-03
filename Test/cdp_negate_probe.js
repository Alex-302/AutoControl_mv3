// CDP: run _mh on a synthetic trigActList with menuState negate:true and
// inspect whether the compiled entry keeps the negate flag.
// Usage: node Test/cdp_negate_probe.js [port]
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

  const expr = `(() => {
    const out = {};
    try {
      if (typeof _mh !== 'function') { out.err = 'no _mh'; return out; }
      // Synthetic trigActList: one trigger with a menuState negate:true precond
      // and one keyEvt precond, mirroring the imported Smart Ctrl+Tab openMenu trigger.
      const ta = [
        ['99', {
          actions: [{ sequence: [{ action: 'openMenu', params: { menuId: 'menuSpec:7' } }], targets: 'currentTab' }],
          triggers: [{
            combins: [{ block: 1, eventId: 9, holdPeriod: 400, noAutoRep: true, preconds: [{ keyEvt: 17 }], wildcard: 2 }],
            preconds: { menuState: [{ menuId: 'menuSpec:7', negate: true }] }
          }]
        }]
      ];
      const payload = _mh(ta, {}, {});
      window.__acProbePayload = payload;
      out.mapKeys = Object.keys(payload.map).map(Number).sort((a, b) => a - b);
      out.entry9 = payload.map['22034'] ? payload.map['22034'].map(i => payload.list[i]) : null;
      out.entry6145 = payload.map['28170'] ? payload.map['28170'].map(i => payload.list[i]) : null;
      // also probe how keep()/sc() behave on the precond objects
      const W = { menuId: 'menuSpec:7', negate: true };
      out.stepSc = JSON.stringify(W.sc());
      const sc2 = W.sc();
      out.stepScKeys = Object.keys(sc2).join(',');
      const kept = sc2.keep('negate', 'oper');
      out.stepKeep = JSON.stringify(kept);
      const kept2 = W.sc().keep('negate', 'oper');
      out.stepKeep2 = JSON.stringify(kept2);
      out.stepIn = '"negate".in(["negate","oper"]) = ' + 'negate'.in(['negate', 'oper']);
      out.stepIn2 = '"menuId".in(["negate","oper"]) = ' + 'menuId'.in(['negate', 'oper']);
      out.keepResult = JSON.stringify(kept2.add({ menuState: W }));
    } catch (e) { out.err = String(e); }
    return out;
  })()`;

  const r = await send('Runtime.evaluate', { expression: expr, returnByValue: true });
  const v = r.result && r.result.result && r.result.result.value;
  console.log(JSON.stringify(v, null, 1));
  ws.close();
}
main().catch(e => { console.error('FATAL:', e); process.exit(1); });
