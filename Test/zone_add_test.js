// zone_add_test.js - create/remove a temporary test trigger with a mouseOver
// region precond (used to prove that the engine delivers type-750 for a zone
// on the v19 table build).
//
// Usage:
//   node Test/zone_add_test.js <port> add    <id> <region> <eventId> [action] [sctnId]
//   node Test/zone_add_test.js <port> remove <id>
//
// eventId: 512 = wheel up, 1536 = wheel down, 1 = LMB, 2 = RMB, 3 = MMB
// action : reload | switchLeft | switchRight | pin  (default reload)
// sctnId : OPTIONAL. Do NOT pass a section id that does not exist in the
//          settings — the UI groups actions by section tabs, so a trigger in
//          a missing section stays in storage, keeps executing, and becomes
//          UNDELETABLE from the UI (found 2026-09-12 the hard way: four test
//          triggers with sctnId "3" were invisible while still firing).
'use strict';
const PORT = process.argv[2] || '9223';
const CMD = (process.argv[3] || 'add').toLowerCase();
const ID = String(process.argv[4] || '93');
const REGION = Number(process.argv[5] || 21);
const EVENT = Number(process.argv[6] || 1536);
const ACTION = process.argv[7] || 'reload';
const SCTN = process.argv[8] || '';
const EXT = 'lkaihdpfpifdlgoapbfocpmekbokmcfd';

const PARAMS = { reload: {}, switchLeft: {}, switchRight: {}, pin: {} };

(async () => {
  const targets = await (await fetch(`http://127.0.0.1:${PORT}/json/list`)).json();
  const sw = targets.find(t => t.url && t.url.startsWith('chrome-extension://' + EXT) && t.type === 'service_worker');
  if (!sw) { console.log('NO SW'); process.exit(1); }
  const ws = new WebSocket(sw.webSocketDebuggerUrl);
  await new Promise((res, rej) => { ws.onopen = res; ws.onerror = rej; });
  let id = 0;
  const pending = new Map();
  ws.onmessage = e => { const m = JSON.parse(e.data); if (m.id && pending.has(m.id)) { pending.get(m.id)(m); pending.delete(m.id); } };
  const send = (method, params) => new Promise(res => { const i = ++id; pending.set(i, res); ws.send(JSON.stringify({ id: i, method, params })); });
  const ev = async (expr) => {
    const r = await send('Runtime.evaluate', { expression: expr, awaitPromise: true, returnByValue: true });
    if (r.result && r.result.exceptionDetails) return 'EXC: ' + String(r.result.exceptionDetails.exception && r.result.exceptionDetails.exception.description).slice(0, 300);
    return r.result && r.result.result && r.result.result.value;
  };

  if (CMD === 'remove') {
    const out = await ev(`(async () => {
      const a = await chrome.storage.local.get('trigActList');
      const l = a.trigActList || [];
      const keep = l.filter(x => String(x[0]) !== ${JSON.stringify(ID)});
      await chrome.storage.local.set({ trigActList: keep });
      return 'removed ${ID}; total=' + keep.length;
    })()`);
    console.log(out); ws.close(); return;
  }

  const out = await ev(`(async () => {
    const a = await chrome.storage.local.get('trigActList');
    const l = a.trigActList || [];
    const keep = l.filter(x => String(x[0]) !== ${JSON.stringify(ID)});
    const ent = {
      actions: [{ sequence: [{ action: ${JSON.stringify(ACTION)}, params: ${JSON.stringify(PARAMS[ACTION] || {})} }], targets: 'currentTab' }],
      triggers: [
        { combins: [{ block: 1, eventId: ${EVENT}, wildcard: 2 }], preconds: { mouseOver: [{ oper: 'or', region: ${REGION} }] } }
      ]
    };
    // VISIBILITY GUARD (user rule 2026-09-12): a trigger whose sctnId is not
    // present in storage.local.sections is never rendered by the settings UI
    // (undelatable) while the engine keeps executing it. So the section is
    // applied ONLY when it really exists; otherwise it is dropped and the
    // trigger stays visible exactly like the user's own (sctnId: undefined).
    const all = await chrome.storage.local.get(null);
    const secs = all.sections || [];
    const wantSctn = ${JSON.stringify(SCTN)};
    let sctn = '', dropped = '';
    if (wantSctn) {
      if (secs.some(s => String(s.id) === String(wantSctn))) sctn = wantSctn;
      else dropped = wantSctn;
    }
    if (sctn) ent.sctnId = sctn;
    keep.push([${JSON.stringify(ID)}, ent]);
    await chrome.storage.local.set({ trigActList: keep });
    const visible = !ent.sctnId || secs.some(s => String(s.id) === String(ent.sctnId));
    return 'added ${ID} (region ${REGION}, event ${EVENT}, action ${ACTION}' +
      (sctn ? ', sctn ' + sctn : ', NO section') + ') total=' + keep.length +
      ' | visible=' + visible + (dropped ? ' | sctn ' + dropped + ' does not exist -> dropped' : '');
  })()`);
  console.log(out);
  ws.close();
})().catch(e => { console.log('ERR ' + e.message); process.exit(1); });
