// Zone classification scan against the ENGINE (Canary): for each region,
// arm the synthetic RMB+mouseOver(region) trigger in-memory, RMB at the
// probe point, and report whether a 750 fired. Verifies what the engine's
// classifier REALLY sees at each zone — independent of the SW config.
// The real config and advOpts are restored at the end.
//
// Usage: node Test/zone_engine_scan.js [port]
'use strict';
const { execFileSync } = require('child_process');
const path = require('path');
const port = process.argv[2] || '9223';
const CDP = `http://127.0.0.1:${port}`;
const EXT_ID = 'lkaihdpfpifdlgoapbfocpmekbokmcfd';

const REGIONS = [
  { name: 'tab strip', region: 12, dx: 300, dy: 35 },
  { name: 'omnibox', region: 21, dx: 300, dy: 85 },
  { name: 'page', region: 3, dx: 300, dy: 600 },
  { name: 'window', region: 1, dx: 600, dy: 300 }
];

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
  const logs = [];
  ws.onmessage = (e) => {
    const m = JSON.parse(e.data);
    if (m.id && pending.has(m.id)) { pending.get(m.id)(m); pending.delete(m.id); }
    else if (m.method === 'Runtime.consoleAPICalled') {
      logs.push('[' + m.params.type + '] ' + (m.params.args || []).map(a => a.value !== undefined ? a.value : (a.description || '')).join(' '));
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

  // allow injected input for the scan — send the filter DIRECTLY via _Jf
  // (NO storage change: the storage-driven rebuild loop would re-send the
  // REAL config and overwrite our synthetic arm before the RMB).
  await ev(`(() => { try { _Jf('no'); return 'filter=no'; } catch (e) { return 'ERR ' + e.message; } })()`);
  await sleep(5000);

  // get the SxS window rect
  const rect = await ev(`chrome.windows.getLastFocused({}).then(w=>({top:w.top,left:w.left}))`);
  const winTop = rect && rect.top !== undefined ? rect.top : 136;
  const winLeft = rect && rect.left !== undefined ? rect.left : 150;
  console.log('SxS window top-left:', winLeft, winTop);

  for (const z of REGIONS) {
    // arm the synthetic trigger for this region
    const dataObj = {
      trigActList: [['99', {
        actions: [{ sequence: [{ action: 'setVolume', params: { mode: 'toggle', target: ':sys' } }], targets: 'hoveredTabs' }],
        sctnId: '3',
        triggers: [{ combins: [{ block: 2, eventId: 2, wildcard: 2 }], preconds: { mouseOver: [{ region: z.region }] } }]
      }]]
    };
    const armRes = await ev(`(async () => {
      const DATA = ${JSON.stringify(dataObj)};
      const ta = {};
      for (const [id, t] of DATA.trigActList) ta[id] = t;
      try { _Lk(60, _mh(Object.entries(ta), {}, {})); return 'armed ${z.region}'; }
      catch (e) { return 'ERR ' + e.message; }
    })()`);
    await sleep(1500);
    const x = winLeft + z.dx;
    const y = winTop + z.dy;
    logs.length = 0;
    ps(['-Action', 'move', '-X', String(x), '-Y', String(y)]);
    await sleep(3000);
    ps(['-Action', 'rmb', '-HoldMs', '120']);
    await sleep(2200);
    const hit = logs.filter(l => /750|Trigger/.test(l));
    console.log(`${z.name} (region ${z.region}) @ ${x},${y}: ${hit.length ? 'FIRED ✓' : 'no 750 ✗'}` + (hit.length ? ' — ' + hit[0].slice(0, 120) : ''));
  }

  // restore the real config + advOpts
  await ev(`(async () => {
    const o = await new Promise((res) => {
      const done = () => res();
      if (typeof _lr === 'function') _lr(() => { try { _Gf({}, done); } catch (e) { done(); } });
      else if (typeof _Gf === 'function') _Gf({}, done);
      else done();
    });
    const a = await chrome.storage.local.get('advOpts');
    const adv = Object.assign({}, a.advOpts || {});
    adv.ignInjInp = 'all';
    await chrome.storage.local.set({ advOpts: adv });
    return 'restored, ek=' + Object.keys(_ek || {}).length;
  })()`);
  console.log('restore done');
  ws.close();
}
main().catch(e => { console.error('FATAL:', e.message); process.exit(1); });
