// CDP helper: walk a horizontal (or vertical) GRID of screen points and ask the
// browser-spawned zone helper what zones each point reports. This is the
// regression check for zone rules: it uses the SW's own helper request
// (`__acTest.zoneAsk`), so the answer comes from the helper instance that is
// bound to THIS browser (a standalone `zone_probe.ps1` run has no browser in
// its parent chain, so its "own window" gate is inert and it reports zones over
// foreign windows too).
//
// The cursor is moved with the DPI-aware `Test/_probe_mouse.ps1` (150% display:
// without SetProcessDPIAware the cursor lands at 1.5x the requested point).
//
// Usage:
//   node Test/_probe_zonegrid.js [port] [y] [x0] [x1] [step]
//   node Test/_probe_zonegrid.js 9223 30 140 700 20     # a row of the tab strip
//
// Output: one line per point: x  zones  (zone set)  [tab index/title if known]
'use strict';
const { execFileSync } = require('child_process');
const port = process.argv[2] || '9223';
const Y = Number(process.argv[3] || 30);
const X0 = Number(process.argv[4] || 140);
const X1 = Number(process.argv[5] || 700);
const STEP = Number(process.argv[6] || 20);
const CDP = `http://127.0.0.1:${port}`;
const EXT_ID = 'lkaihdpfpifdlgoapbfocpmekbokmcfd';
const MOVE = require('path').join(__dirname, '_probe_mouse.ps1');

const ASK = `new Promise(res => {
  const t = performance.now();
  __acTest.zoneAsk(1200).then(z => {
    const tab = (typeof __acTest.hoveredId === 'function') ? __acTest.hoveredId() : null;
    res({ ms: Math.round(performance.now() - t), zones: z, tab: tab });
  });
})`;

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

  console.log(`grid: y=${Y}  x=${X0}..${X1} step ${STEP}  (port ${port})`);
  const seen = new Map();
  for (let x = X0; x <= X1; x += STEP) {
    execFileSync('powershell', ['-NoProfile', '-File', MOVE, '-Action', 'move', '-X', String(x), '-Y', String(Y)], { stdio: 'pipe' });
    // let the helper's heartbeat classify the new point (30 ms poll + settle)
    await new Promise(r => setTimeout(r, 120));
    const r = await send('Runtime.evaluate', { expression: ASK, awaitPromise: true, returnByValue: true });
    const v = r.result && r.result.result && r.result.result.value;
    if (!v) { console.log(`${String(x).padStart(5)}  (no answer)`); continue; }
    const zs = Array.isArray(v.zones) ? v.zones : [v.zones];
    const key = zs.join(',');
    seen.set(key, (seen.get(key) || 0) + 1);
    console.log(`${String(x).padStart(5)}  [${key}]${v.tab != null ? '  tab=' + v.tab : ''}  ${v.ms}ms`);
  }
  console.log('--- summary (zone set -> points) ---');
  for (const [k, n] of [...seen.entries()].sort((a, b) => b[1] - a[1])) console.log(`  [${k}]  x${n}`);
  ws.close();
})().catch(e => { console.error('FATAL:', e.message); process.exit(1); });
