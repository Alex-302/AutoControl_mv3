// CDP experiment: run the exact _ja import pipeline in the SW with the real
// .acs file content, WITHOUT saving anything. Shows where trigActList survives.
// Usage: node Test/cdp_import_sim.js <port> <file.acs>
'use strict';
const port = process.argv[2] || '9223';
const fs = require('fs');
const CDP = `http://127.0.0.1:${port}`;
const EXT_ID = 'lkaihdpfpifdlgoapbfocpmekbokmcfd';

const filePath = process.argv[3] || 'E:\\Downloads\\!Trash\\! tabs test.acs';
const fileContent = fs.readFileSync(filePath, 'utf8');
const dataJson = JSON.stringify(JSON.parse(fileContent)); // normalize, then embed

async function getTargets() {
  return await (await fetch(CDP + '/json/list')).json();
}

async function evaluate(target, expression) {
  const ws = new WebSocket(target.webSocketDebuggerUrl);
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
  const r = await send('Runtime.evaluate', { expression, awaitPromise: true, returnByValue: true });
  ws.close();
  return r;
}

const EXPR = `(async () => {
  const DATA = ${dataJson};
  const out = {};
  const _2d = { trigActList: [], customEntities: {}, toolbarBtns: {}, sections: [] };
  const ids = (x) => { try { return Object.keys(x || {}).join(','); } catch (e) { return 'ERR'; } };
  try {
    out.fileTrigs = (DATA.trigActList || []).map(t => t[0]);
    out.fileSections = (DATA.sections || []).map(s => s.id + ':' + s.name);
    out.fileCE = Object.keys(DATA.customEntities || {});
  } catch (e) { out.fileErr = String(e); }

  // STAGE 1: merged0 = {}.add(_2d, data) — raw
  let merged0;
  try {
    merged0 = {}.add(_2d, DATA);
    out.stage1_trigs = (merged0.trigActList || []).map(t => t[0]);
    out.stage1_ce = Object.keys(merged0.customEntities || {});
  } catch (e) { out.stage1_err = String(e); }

  // STAGE 2: merged = _Qj(merged0) — store format
  let merged;
  try {
    merged = _Qj(merged0);
    out.stage2_trigs = ids(merged.trigActList);
    out.stage2_sections = (merged.sections || []).map(s => s.id);
  } catch (e) { out.stage2_err = String(e); }

  // STAGE 3: l = _9i(_2d) — current storage (store format)
  _9i(_2d, (l) => {
    try {
      out.stage3_lTrigs = ids(l.trigActList);
      out.stage3_lSections = (l.sections || []).map(s => s.id + ':' + s.name);

      // STAGE 4: _K(l, merged, true, true) — dedupe/renumber (mutates merged)
      _K(l, merged, true, true);
      out.stage4_afterK = ids(merged.trigActList);
      out.stage4_lSections = (l.sections || []).map(s => s.id + ':' + s.name);

      // STAGE 5: _4p(l, merged, false) — merge-add
      const o = _4p(l, merged, false);
      out.stage5_outTrigs = ids(o.trigActList);
      out.stage5_outSections = (o.sections || []).map(s => s.id + ':' + s.name);
      out.stage5_outCE = Object.keys(o.customEntities || {});

      // STAGE 6: what would be SAVED (_bj → storage format)
      const bj = _bj(o);
      out.stage6_savedTrigs = (bj.trigActList || []).map(t => t[0]);
      out.stage6_savedSections = (bj.sections || []).map(s => s.id);
      out.done = true;
    } catch (e) { out.stage3_err = String(e && e.stack || e); out.done = true; }
  });
  while (!out.done) await new Promise((r) => setTimeout(r, 30));
  return out;
})()`;

async function main() {
  const targets = await getTargets();
  const sw = targets.find(t => t.url && t.url.startsWith('chrome-extension://' + EXT_ID) && t.type === 'service_worker');
  if (!sw) { console.log('SW target not found'); process.exit(2); }
  console.log('evaluating in: ' + sw.url);
  const r = await evaluate(sw, EXPR);
  if (r.error) { console.log('CDP error:', JSON.stringify(r.error)); process.exit(3); }
  const res = r.result && r.result.result;
  if (!res || res.subtype === 'error') { console.log('EVAL ERROR:', JSON.stringify(res).slice(0, 800)); process.exit(4); }
  console.log(JSON.stringify(res.value, null, 2));
}
main().catch(e => { console.error('FATAL:', e); process.exit(1); });
