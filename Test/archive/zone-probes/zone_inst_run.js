// Fully instrumented zone test: direct _Jf('no'), arm synthetic region 3,
// verify the sends went out live, RMB at the page, capture ALL live lines.
'use strict';
const { execFileSync } = require('child_process');
const path = require('path');
const CDP = 'http://127.0.0.1:9223';
const EXT_ID = 'lkaihdpfpifdlgoapbfocpmekbokmcfd';

const ps = (a) => execFileSync('powershell', ['-ExecutionPolicy', 'Bypass', '-File', path.join('Test', '_ac_mouse.ps1'), ...a], { encoding: 'utf8' });
const sleep = (ms) => new Promise(r => setTimeout(r, ms));

(async () => {
  const targets = await (await fetch(CDP + '/json/list')).json();
  const sw = targets.find(t => t.url && t.url.startsWith('chrome-extension://' + EXT_ID) && t.type === 'service_worker');
  const ws = new WebSocket(sw.webSocketDebuggerUrl);
  await new Promise((res, rej) => { ws.onopen = res; ws.onerror = rej; });
  let msgId = 0;
  const pending = new Map();
  let live = [];
  ws.onmessage = (e) => {
    const m = JSON.parse(e.data);
    if (m.id && pending.has(m.id)) { pending.get(m.id)(m); pending.delete(m.id); }
    else if (m.method === 'Runtime.consoleAPICalled') {
      live.push('[' + m.params.type + '] ' + (m.params.args || []).map(a => a.value !== undefined ? a.value : (a.description || '')).join(' '));
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
  await sleep(4000);   // drain replay
  live = [];

  console.log('1) filter via direct _lr (type 65 object) + arm:');
  // 0. release any stuck capture mode (type 40 false suppresses nothing;
  //    capture ON would swallow ALL 750s — the classic silent-death state)
  console.log('   capture-off:', await ev(`(()=>{try{_Lk(40,false);return 'sent'}catch(e){return 'ERR '+e.message}})()`));
  await sleep(1000);
  // 1a. storage: ignInjInp='no'
  await ev(`chrome.storage.local.get('advOpts').then(a=>{const o=Object.assign({},a.advOpts||{});o.ignInjInp='no';return chrome.storage.local.set({advOpts:o})})`);
  await sleep(1500);
  // 1b. direct _lr — PROVEN to send type 65 with the advOpts OBJECT
  console.log('   lr:', await ev(`new Promise((res)=>{try{_lr(()=>res('lr-ok'))}catch(e){res('ERR '+e.message)}})`));
  await sleep(2000);
  const sends1 = live.filter(l => /→ Native type/.test(l));
  console.log('   sends after lr:', sends1.length ? sends1.join(' ;; ').slice(0, 300) : 'NONE');
  // 1c. arm the synthetic (AFTER the chain's real type-60)
  const dataObj = {
    trigActList: [['99', {
      actions: [{ sequence: [{ action: 'setVolume', params: { mode: 'toggle', target: ':sys' } }], targets: 'hoveredTabs' }],
      sctnId: '3',
      triggers: [{ combins: [{ block: 2, eventId: 2, wildcard: 2 }], preconds: { mouseOver: [{ region: 3 }] } }]
    }]]
  };
  console.log('   ', await ev(`(async () => {
    const DATA = ${JSON.stringify(dataObj)};
    const ta = {};
    for (const [id, t] of DATA.trigActList) ta[id] = t;
    try { _Lk(60, _mh(Object.entries(ta), {}, {})); return 'armed'; }
    catch (e) { return 'ERR ' + e.message; }
  })()`));
  await sleep(2000);
  const sends = live.filter(l => /→ Native type/.test(l));
  console.log('   sends after arm:', sends.length ? sends.join(' ;; ').slice(0, 400) : 'NONE');
  live = [];

  console.log('2) RMB at page (450,736) — drift-free:');
  ps(['-Action', 'move', '-X', '450', '-Y', '736']);
  await sleep(800);
  const rmbOut = ps(['-Action', 'rmb', '-HoldMs', '120']);
  const posLine = rmbOut.trim().split(/\r?\n/).filter(l => /cursor at/.test(l)).pop();
  console.log('   ' + (posLine || 'no pos line'));
  await sleep(2500);
  const hit = live.filter(l => /750|Trigger/.test(l));
  console.log('   750:', hit.length ? 'FIRED' : 'no', '| live lines:', live.length);
  hit.slice(0, 3).forEach(l => console.log('   ', l.slice(0, 140)));
  live.slice(0, 6).forEach(l => console.log('   ', l.slice(0, 140)));
  ws.close();
})().catch(e => { console.error('FATAL:', e.message); process.exit(1); });
