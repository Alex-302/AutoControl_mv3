// CDP helper: dump the in-SW diagnostic log installed by the "race" probe
// (__acRaceLog - helper port traffic, _ys, the _pp filter table, tabs.reload
// and tabs.onUpdated). Used to chase the "the PREVIOUS tab reloads" race.
//
// Usage:
//   node Test/_probe_racedump.js [port] [lineFilter]
//   node Test/_probe_racedump.js 9223 TAB        # only tab-related lines
//
// The log itself is installed from the SW console (see the session notes);
// this tool only reads it. It is a DEV tool - it is not part of the extension.
'use strict';
const port = process.argv[2] || '9223';
const lineFilter = process.argv[3] || '';
const CDP = `http://127.0.0.1:${port}`;
const EXT_ID = 'lkaihdpfpifdlgoapbfocpmekbokmcfd';

const DUMP = `(() => {
  const L = (typeof __acRaceLog === 'undefined') ? [] : __acRaceLog;
  if (!L.length) return 'EMPTY (is the probe installed? see the session notes)';
  const t0 = L[0].t;
  const out = [];
  for (let i = 0; i < L.length; i++) {
    const e = L[i], d = e.data;
    // skip the helper keepalive chatter (zone 0 = cursor outside the browser)
    if (e.tag === 'res' && d.index === undefined && (d.zone === 0 || d.zone === undefined)) continue;
    if (e.tag === 'req') {
      const nx = L[i + 1];
      if (nx && nx.tag === 'res' && nx.data.index === undefined && (nx.data.zone === 0 || nx.data.zone === undefined)) continue;
    }
    let x;
    if (e.tag === 'req') x = 'id' + d.__id + (d.tab ? '  TAB-REQ' : '');
    else if (e.tag === 'res') x = 'id' + d.__id + ' z=' + d.zone + ' [' + (d.zones || []).join(',') + ']' +
      (d.index !== undefined ? '  TAB idx=' + d.index + ' "' + String(d.title || '').slice(0, 26) + '"' : '');
    else if (e.tag === 'filter') x = 'evt=' + d.evt + ' hv=' + d.hv + ' n=' + d.n +
      ' out=' + JSON.stringify(d.out) + ' kg=' + JSON.stringify(d.kg) + ' sw=' + d.sw;
    else if (e.tag === 'reload') x = 'tabId=' + d;
    else if (e.tag === 'loading') x = 'idx=' + d.idx + ' id=' + d.id + ' "' + String(d.title).slice(0, 26) + '"';
    else if (e.tag === '_ys') x = 'ret=' + JSON.stringify(d.ret) + ' kg=' + JSON.stringify(d.kg);
    else x = JSON.stringify(d);
    out.push((e.t - t0) + '  ' + e.tag + '  ' + x);
  }
  return 'kept=' + out.length + ' of ' + L.length + '\\n' + out.join('\\n');
})()`;

(async () => {
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
    const id = ++msgId; pending.set(id, res);
    ws.send(JSON.stringify({ id, method, params }));
  });
  await send('Runtime.enable');
  const r = await send('Runtime.evaluate', { expression: DUMP, awaitPromise: true, returnByValue: true });
  const v = r.result && r.result.result && r.result.result.value;
  if (v === undefined) console.log('DESC:', JSON.stringify(r.result));
  else {
    let s = String(v);
    if (lineFilter) s = s.split('\n').filter(l => l.indexOf(lineFilter) >= 0).join('\n');
    console.log(s);
  }
  ws.close();
})().catch(e => { console.error('FATAL:', e.message); process.exit(1); });
