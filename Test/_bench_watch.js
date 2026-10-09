// Wheel benchmark WATCHER (2026-09-20) - records what the extension does while
// the USER turns the wheel by hand. Needed because the engine DROPS synthetic
// mouse input (LLMHF_INJECTED): an injected wheel scrolls the page but produces
// no 750 at all, so the benchmark cannot be automated.
//
// What it records, all with timestamps on one clock:
//   * every zone-gate decision   [AC-MV3-ZONE] trig N: zones=[...] ∩ [...] → executing|skipped
//   * every action execution     [AC-ACT] ...
//   * every page (re)load        chrome.tabs.onUpdated status=loading -> which TAB
//
// The last one is the ground truth for the user's symptom ("it sticks on the
// tabs where I scrolled"): the reload target is resolved by the engine's own
// hovered-tab state, so a stale position shows up as "tab A reloaded again
// although the wheel was over tab B".
//
// Usage: node Test/_bench_watch.js [port] [seconds] [--plan]
//   --plan prints the pass plan (4 tabs x interval, 500 ms down to 50 ms)
'use strict';
const port = process.argv[2] || '9224';
const seconds = parseInt(process.argv[3] || '120', 10);
const showPlan = process.argv.includes('--plan');
const CDP = `http://127.0.0.1:${port}`;
const EXT_ID = 'lkaihdpfpifdlgoapbfocpmekbokmcfd';

const t0 = Date.now();
const ts = () => '+' + ((Date.now() - t0) / 1000).toFixed(3) + 's';
// The SW console BACKLOG is replayed on attach (Runtime.consoleAPICalled), so
// every event older than the attach moment must be dropped - otherwise the
// capture shows history instead of the run.
const clean = s => s.replace(/\u2229/g, '&').replace(/\u2192/g, '->').replace(/[\u2013\u2014]/g, '-');
let attachAt = 0;
let live = false;      // false while the replayed console backlog is arriving

(async () => {
  const targets = await (await fetch(CDP + '/json/list')).json();
  const sw = targets.find(t => t.url && t.url.startsWith('chrome-extension://' + EXT_ID) && t.type === 'service_worker');
  if (!sw) { console.log('SW not found - is the extension running?'); process.exit(2); }
  const ws = new WebSocket(sw.webSocketDebuggerUrl);
  await new Promise((res, rej) => { ws.onopen = res; ws.onerror = rej; });
  let msgId = 0; const pending = new Map();
  ws.onmessage = e => {
    const m = JSON.parse(e.data);
    if (m.id && pending.has(m.id)) { pending.get(m.id)(m); pending.delete(m.id); return; }
    if (m.method === 'Runtime.consoleAPICalled') {
      if (!live) return;                                          // backlog replay
      const txt = (m.params.args || []).map(a => a.value !== undefined ? a.value : (a.description || '')).join(' ');
      if (txt.includes('AC-MV3-ZONE') || txt.includes('AC-ACT')) {
        const isZone = txt.includes('AC-MV3-ZONE');
        const s = clean(txt).replace(/^\s+/, '');
        events.push({ t: m.params.timestamp, kind: isZone ? 'ZONE' : 'ACT', txt: s });
        console.log(`${ts()}  ${isZone ? 'ZONE ' : 'ACT  '} ${s.replace('[AC-MV3-ZONE] ', '').replace('[AC-ACT] ', '')}`);
      }
    }
  };
  const send = (method, params) => new Promise(res => { const id = ++msgId; pending.set(id, res); ws.send(JSON.stringify({ id, method, params })); });
  const evalAwait = async expr => {
    const r = await send('Runtime.evaluate', { expression: expr, awaitPromise: true, returnByValue: true });
    if (r.result && r.result.exceptionDetails) throw new Error(r.result.exceptionDetails.text);
    const res = r.result && r.result.result;
    return res ? res.value : undefined;
  };
  const events = [];

  await send('Runtime.enable');
  attachAt = Date.now();
  // Chrome REPLAYS the whole session backlog when a debugger attaches and the
  // replayed events carry the replay moment as their timestamp, so a time
  // filter cannot separate them. Drop everything that arrives during the
  // warm-up window instead.
  await new Promise(r => setTimeout(r, 1500));
  events.length = 0;
  live = true;
  console.log('(backlog dropped - recording LIVE from now on)');

  // --- tab list ---------------------------------------------------------
  const tabs = JSON.parse(await evalAwait(`chrome.tabs.query({currentWindow:true}).then(ts=>JSON.stringify(ts.map(t=>({i:t.index,id:t.id,t:(t.title||'').slice(0,30),u:(t.url||'').slice(0,50)}))))`));
  console.log('tabs:');
  for (const t of tabs) console.log(`  index ${t.i}  tabId ${t.id}  ${t.t}   [${t.u}]`);

  if (showPlan) {
    console.log('\nPLAN (one wheel notch per tab, tabs in index order, repeat):');
    const ivs = []; for (let iv = 500; iv >= 50; iv -= 50) ivs.push(iv);
    ivs.forEach((iv, n) => console.log(`  pass ${n + 1}: interval ${iv} ms`));
    console.log('  = one wheel over each tab, then the next pass with a shorter interval.');
    console.log('\nCLOSE BUTTON points (zone 15, the reload trigger) - y=560, x by tab index:');
    tabs.forEach(t => console.log(`  index ${t.i}: (${371 + t.i * 252}, 560)`));
    console.log('\n');
  }

  // --- reload detector (tabs.onUpdated -> self.__bench) ------------------
  await evalAwait(`(()=>{ self.__bench = [];
    if (self.__benchHook) { try { chrome.tabs.onUpdated.removeListener(self.__benchHook); } catch(e){} }
    if (self.__benchAct) { try { chrome.tabs.onActivated.removeListener(self.__benchAct); } catch(e){} }
    self.__benchHook = (tabId, info, tab) => { if (info.status === 'loading') self.__bench.push({ t: Date.now(), tabId: tabId, kind: 'load', title: (tab && tab.title || '').slice(0,30) }); };
    self.__benchAct = (info) => { self.__bench.push({ t: Date.now(), tabId: info.tabId, kind: 'active', title: '' }); };
    chrome.tabs.onUpdated.addListener(self.__benchHook);
    chrome.tabs.onActivated.addListener(self.__benchAct);
    return 'ok'; })()`);

  console.log(`\nrecording for ${seconds}s - turn the wheel by hand now.\n`);
  const seen = new Set();
  const deadline = Date.now() + seconds * 1000;
  while (Date.now() < deadline) {
    let raw;
    try { raw = await evalAwait('JSON.stringify(self.__bench||[])'); } catch (e) { raw = '[]'; }
    let list = [];
    try { list = JSON.parse(raw || '[]'); } catch (e) { list = []; }
    for (const r of list) {
      const key = r.t + ':' + r.tabId + ':' + r.kind;
      if (seen.has(key)) continue;
      seen.add(key);
      const idx = (tabs.find(t => t.id === r.tabId) || {}).i;
      const label = r.kind === 'active' ? 'ACTIVE' : 'LOAD  ';
      events.push({ t: r.t, kind: r.kind === 'active' ? 'ACTIVE' : 'RELOAD', txt: `tab ${r.tabId} (index ${idx}) ${r.title}` });
      console.log(`${'+' + ((r.t - t0) / 1000).toFixed(3)}s  ${label} tab ${r.tabId} (index ${idx}) ${r.title}`);
    }
    await new Promise(r => setTimeout(r, 200));
  }

  // --- summary ----------------------------------------------------------
  console.log('\n================ SUMMARY ================');
  const z = events.filter(e => e.kind === 'ZONE');
  const a = events.filter(e => e.kind === 'ACT');
  const rl = events.filter(e => e.kind === 'RELOAD');
  console.log(`\nzone decisions: ${z.length}   actions: ${a.length}   page loads: ${rl.length}`);
  console.log('\nwheels (gap to the previous one shows the pass interval):');
  let prev = null;
  for (const e of z) {
    const gap = prev === null ? '-' : Math.round(e.t - prev) + 'ms';
    prev = e.t;
    console.log(`  +${((e.t - t0) / 1000).toFixed(3)}s  gap ${gap.padStart(6)}   ${e.txt.replace('[AC-MV3-ZONE] ', '')}`);
  }
  console.log('\npage loads (the ground truth: which tab was really reloaded):');
  prev = null;
  for (const e of rl) {
    const gap = prev === null ? '-' : Math.round(e.t - prev) + 'ms';
    prev = e.t;
    console.log(`  +${((e.t - t0) / 1000).toFixed(3)}s  gap ${gap.padStart(6)}   ${e.txt}`);
  }
  console.log('\nfull stream:');
  for (const e of events) console.log(`${'+' + ((e.t - t0) / 1000).toFixed(3)}s  ${e.kind.padEnd(7)} ${e.txt}`);
  ws.close();
})().catch(e => { console.error('FATAL:', e.message); process.exit(1); });
