// Zone scanner: set mouseOver region N on trigger 12, click RMB at each point,
// report where the trigger fired.
// Usage:
//   node Test/zone-tests/zone_scan.js <region> x1,y1 x2,y2 ...      (points)
//   node Test/zone-tests/zone_scan.js <region> grid x1,y1 x2,y2 step (rect grid)
// ⚠ A zone that fires EVERYWHERE (incl. the page) is FAIL-OPEN ("acts like
// the whole window") — the grid over the window + page points detects it.
'use strict';
const { execFileSync } = require('child_process');
const path = require('path');
const port = '9223';
const CDP = `http://127.0.0.1:${port}`;
const EXT_ID = 'lkaihdpfpifdlgoapbfocpmekbokmcfd';
const region = process.argv[2];
const args = process.argv.slice(3);
let points = [];
if (args[0] === 'grid') {
  const [x1, y1, x2, y2, step] = args.slice(1).map(Number);
  for (let y = y1; y <= y2; y += step) for (let x = x1; x <= x2; x += step) points.push([x, y]);
  console.log(`grid ${x1},${y1}..${x2},${y2} step ${step} -> ${points.length} points`);
} else {
  points = args.map(s => s.split(',').map(Number));
}

const ev = async (expr) => {
  const targets = await (await fetch(CDP + '/json/list')).json();
  const sw = targets.find(t => t.url && t.url.startsWith('chrome-extension://' + EXT_ID) && t.type === 'service_worker');
  if (!sw) throw new Error('SW not found');
  const ws = new WebSocket(sw.webSocketDebuggerUrl);
  await new Promise((res, rej) => { ws.onopen = res; ws.onerror = rej; });
  let msgId = 0; const pending = new Map();
  ws.onmessage = (e) => { const m = JSON.parse(e.data); if (m.id && pending.has(m.id)) { pending.get(m.id)(m); pending.delete(m.id); } };
  const send = (method, params) => new Promise((res) => { const id = ++msgId; pending.set(id, res); ws.send(JSON.stringify({ id, method, params })); });
  const r = await send('Runtime.evaluate', { expression: expr, awaitPromise: true, returnByValue: true });
  ws.close();
  const v = r.result && r.result.result && r.result.result.value;
  return v;
};
const ps = (args) => execFileSync('powershell', ['-ExecutionPolicy', 'Bypass', '-File', path.join(__dirname, '..', '_ac_mouse.ps1'), ...args], { encoding: 'utf8' });
const sleep = ms => new Promise(r => setTimeout(r, ms));

(async () => {
  // set region
  await ev(`chrome.storage.local.get('trigActList').then(a=>{const l=a.trigActList||[];const t=l.find(x=>x[0]==='12');if(!t)return 'no trig12';t[1].triggers[0].preconds.mouseOver[0].region=${region};return chrome.storage.local.set({trigActList:l}).then(()=>'r${region}')})`);
  await sleep(3500);
  // arm counter
  await ev(`(()=>{window.__ctr={n:0,ids:[]};const o=self.__acDispatch;self.__acDispatch=function(m){if(m&&m.nativeType===750){window.__ctr.n++;window.__ctr.ids.push(m.data&&m.data.id)}return o(m)};return 'armed'})()`);
  // find sxs tab
  const sxsId = await ev(`chrome.tabs.query({}).then(ts=>{const t=ts.find(x=>x.url&&x.url.startsWith('http://sxs'));return t?t.id:0})`);
  for (const [x, y] of points) {
    await ev(`chrome.tabs.update(${sxsId},{pinned:false}).then(()=>'r')`).catch(() => {});
    await sleep(600);
    try { ps(['-Action', 'move', '-X', String(x), '-Y', String(y)]); } catch (e) { console.log(`(${x},${y}): move err`); continue; }
    await sleep(2500);
    try { ps(['-Action', 'rmb', '-HoldMs', '120']); } catch (e) {}
    await sleep(1200);
    const c = await ev('window.__ctr');
    const n = c ? c.n : -1;
    console.log(`(${x},${y}): ${n > 0 ? 'FIRED x' + n : 'no'}`);
    await ev('window.__ctr={n:0,ids:[]};"r"');
  }
  console.log('scan done');
})().catch(e => { console.error('FATAL:', e.message); process.exit(1); });
