// zone_cfg_dump.js - compact dump of the stored triggers: which events they
// listen to (wheel / click / key), their mouseOver regions and their actions.
// Used to reason about zone / scroll behaviour without touching the config.
//
// Usage: node Test/zone_cfg_dump.js [port]
'use strict';
const PORT = process.argv[2] || '9223';
const EXT = 'lkaihdpfpifdlgoapbfocpmekbokmcfd';

const EVT = { 1: 'LMB', 2: 'RMB', 3: 'MMB', 4: 'LMB+', 512: 'wheelUp', 1536: 'wheelDn', 1024: 'LMBup', 0: 'any' };

(async () => {
  const targets = await (await fetch(`http://127.0.0.1:${PORT}/json/list`)).json();
  const sw = targets.find(t => t.url && t.url.startsWith('chrome-extension://' + EXT) && t.type === 'service_worker');
  if (!sw) { console.log('NO SW'); process.exit(1); }
  const ws = new WebSocket(sw.webSocketDebuggerUrl);
  await new Promise((res, rej) => { ws.onopen = res; ws.onerror = rej; });
  let id = 0; const pending = new Map();
  ws.onmessage = e => { const m = JSON.parse(e.data); if (m.id && pending.has(m.id)) { pending.get(m.id)(m); pending.delete(m.id); } };
  const send = (method, params) => new Promise(res => { const i = ++id; pending.set(i, res); ws.send(JSON.stringify({ id: i, method, params })); });
  const ev = async (expr) => {
    const r = await send('Runtime.evaluate', { expression: expr, awaitPromise: true, returnByValue: true });
    if (r.result && r.result.exceptionDetails) return { err: String(r.result.exceptionDetails.text || '').slice(0, 300) };
    return r.result && r.result.result && r.result.result.value;
  };
  const out = await ev(`(async () => {
    const a = await chrome.storage.local.get(['trigActList']);
    const list = a.trigActList || [];
    const res = [];
    for (const [id, o] of list) {
      if (!o || typeof o !== 'object') { res.push({ id: String(id), raw: String(o).slice(0,40) }); continue; }
      const tg = (o.triggers || [])[0] || {};
      const comb = (tg.combins || []).map(c => ({
        block: c.block, evt: c.eventId, wc: c.wildcard, hold: c.holdPeriod,
        keys: ((c.preconds || []).filter(p => p.keyEvt != null).map(p => p.keyEvt))
      }));
      const pre = tg.preconds || {};
      const acts = [];
      for (const act of (o.actions || [])) {
        for (const s of (act.sequence || [])) {
          let p = '';
          try { p = JSON.stringify(s.params || {}).slice(0, 60); } catch (e) { }
          acts.push((s.action || '?') + (p && p !== '{}' ? ' ' + p : '') + ' → ' + (s.targets || act.targets || '?'));
        }
      }
      res.push({
        id: String(id),
        name: String(o.name || o.title || tg.name || '').slice(0, 30),
        combins: comb,
        mouseOver: (pre.mouseOver || []).map(m => m.region),
        otherPre: Object.keys(pre).filter(k => k !== 'mouseOver'),
        menuState: (pre.menuState || []).map(m => (m.menuId || '') + (m.negate ? '(not)' : '')),
        url: pre.url ? 1 : 0, acts
      });
    }
    return res;
  })()`);
  if (!Array.isArray(out)) { console.log('DUMP FAILED:', JSON.stringify(out)); process.exit(1); }
  console.log('triggers: ' + out.length);
  for (const t of out) {
    const mo = t.mouseOver && t.mouseOver.length ? ' zone[' + t.mouseOver.join(',') + ']' : '';
    const comb = (t.combins || []).map(c => (c.evt != null ? (EVT[c.evt + 1024] || EVT[c.evt] || 'e' + c.evt) : '?') +
      (c.wc != null ? '/w' + c.wc : '') + (c.keys && c.keys.length ? '/k' + c.keys.join('.') : '') + (c.block ? '/blk' + c.block : '')).join(' + ');
    console.log('#' + t.id + (t.name ? ' "' + t.name + '"' : '') + '  [' + comb + ']' + mo +
      (t.otherPre && t.otherPre.length ? ' pre:' + t.otherPre.join(',') : '') +
      (t.menuState && t.menuState.length ? ' menu:' + t.menuState.join(',') : '') +
      ' => ' + (t.acts || []).join(' | '));
  }
  ws.close();
})().catch(e => { console.log('ERR ' + e.message); process.exit(1); });
