// Clean single-zone test: set the input filter to 'no' via STORAGE (proper
// rebuild), let everything settle, arm the synthetic RMB+mouseOver(region)
// trigger, RMB at the point, and report 750 with LIVE console capture
// (backlog replay drained first). Restores filter + real config at the end.
//
// Usage: node Test/zone_one_test.js [port] [region] [dx] [dy]
'use strict';
const { execFileSync } = require('child_process');
const path = require('path');
const port = process.argv[2] || '9223';
const region = Number(process.argv[3] || 3);
const dx = Number(process.argv[4] || 300);
const dy = Number(process.argv[5] || 600);
const CDP = `http://127.0.0.1:${port}`;
const EXT_ID = 'lkaihdpfpifdlgoapbfocpmekbokmcfd';

const ps = (a) => execFileSync('powershell', ['-ExecutionPolicy', 'Bypass', '-File', path.join('Test', '_ac_mouse.ps1'), ...a], { encoding: 'utf8' });
const sleep = (ms) => new Promise(r => setTimeout(r, ms));

async function main() {
  const targets = await (await fetch(CDP + '/json/list')).json();
  const sw = targets.find(t => t.url && t.url.startsWith('chrome-extension://' + EXT_ID) && t.type === 'service_worker');
  if (!sw) { console.log('SW not found'); process.exit(2); }
  const ws = new WebSocket(sw.webSocketDebuggerUrl);
  await new Promise((res, rej) => { ws.onopen = res; ws.onerror = rej; });
  let msgId = 0;
  const pending = new Map();
  let live = [];
  ws.onmessage = (e) => {
    const m = JSON.parse(e.data);
    if (m.id && pending.has(m.id)) { pending.get(m.id)(m); pending.delete(m.id); }
    else if (m.method === 'Runtime.consoleAPICalled') {
      const txt = '[' + m.params.type + '] ' + (m.params.args || []).map(a => a.value !== undefined ? a.value : (a.description || '')).join(' ');
      live.push(txt);
    }
  };
  const send = (method, params) => new Promise((res) => {
    const id = ++msgId;
    pending.set(id, res);
    ws.send(JSON.stringify({ id, method, params }));
  });
  const ev = async (expr) => {
    const r = await send('Runtime.evaluate', { expression: expr, awaitPromise: true, returnByValue: true });
    return r.result && r.result.result && r.result.result.value;
  };
  await send('Runtime.enable');
  await sleep(4000);   // drain the backlog replay
  live = [];

  // proper filter change via storage + settle
  console.log('set ignInjInp=no (storage)...');
  await ev(`chrome.storage.local.get('advOpts').then(a=>{const o=Object.assign({},a.advOpts||{});o.ignInjInp='no';return chrome.storage.local.set({advOpts:o})})`);
  await sleep(12000);

  // arm the synthetic trigger
  const dataObj = {
    trigActList: [['99', {
      actions: [{ sequence: [{ action: 'setVolume', params: { mode: 'toggle', target: ':sys' } }], targets: 'hoveredTabs' }],
      sctnId: '3',
      triggers: [{ combins: [{ block: 2, eventId: 2, wildcard: 2 }], preconds: { mouseOver: [{ region }] } }]
    }]]
  };
  const armRes = await ev(`(async () => {
    const DATA = ${JSON.stringify(dataObj)};
    const ta = {};
    for (const [id, t] of DATA.trigActList) ta[id] = t;
    try { _Lk(60, _mh(Object.entries(ta), {}, {})); return 'armed'; }
    catch (e) { return 'ERR ' + e.message; }
  })()`);
  console.log('arm:', armRes);
  await sleep(2000);

  // window rect + click
  const rect = await ev(`chrome.windows.getLastFocused({}).then(w=>({top:w.top,left:w.left}))`);
  const x = (rect && rect.left !== undefined ? rect.left : 150) + dx;
  const y = (rect && rect.top !== undefined ? rect.top : 136) + dy;
  console.log('click at', x, y, '(region', region + ')');
  live = [];
  ps(['-Action', 'move', '-X', String(x), '-Y', String(y)]);
  await sleep(3000);
  ps(['-Action', 'rmb', '-HoldMs', '120']);
  await sleep(2500);
  const hit = live.filter(l => /750|Trigger/.test(l));
  const t60 = live.filter(l => /→ Native type 60/.test(l)).length;
  console.log('750:', hit.length ? 'FIRED ✓' : 'no ✗', '| live type-60 during test:', t60);
  hit.slice(0, 3).forEach(l => console.log('  ', l.slice(0, 140)));
  if (!hit.length && t60 === 0) console.log('  (no config sends either — arm may not have reached the native)');

  // restore
  await ev(`(async () => {
    await new Promise((res) => {
      const done = () => res();
      if (typeof _lr === 'function') _lr(() => { try { _Gf({}, done); } catch (e) { done(); } });
      else if (typeof _Gf === 'function') _Gf({}, done);
      else done();
    });
    const a = await chrome.storage.local.get('advOpts');
    const adv = Object.assign({}, a.advOpts || {});
    adv.ignInjInp = 'all';
    await chrome.storage.local.set({ advOpts: adv });
    return 'restored';
  })()`);
  console.log('restore done');
  ws.close();
}
main().catch(e => { console.error('FATAL:', e.message); process.exit(1); });
