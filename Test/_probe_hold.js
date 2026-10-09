// CDP helper: HOLD a DevTools session on the extension service worker.
//
// Why: Chrome evicts an idle service worker ~30 s after the last CDP client
// detaches, and that kills every runtime-installed probe (the in-SW diagnostic
// log of Test/_probe_raceinstall.js). With a session attached the worker stays
// alive, so a probe survives while the USER performs a physical test (the
// engine ignores synthetic input, so wheel tests cannot be scripted).
//
// It also prints the SW console live (filtered), which is the fastest way to
// see the zone gate while the test is running.
//
// Usage:
//   node Test/_probe_hold.js [port] [seconds] [consoleRegex]
//   node Test/_probe_hold.js 9223 900 "AC-MV3-ZONE|AC-ACT"
//
// Run it in the BACKGROUND (a second terminal) while the user tests, then read
// the log with Test/_probe_racedump.js and stop this tool.
'use strict';
const port = process.argv[2] || '9223';
const seconds = Number(process.argv[3] || 600);
const filter = process.argv[4] || '';
const CDP = `http://127.0.0.1:${port}`;
const EXT_ID = 'lkaihdpfpifdlgoapbfocpmekbokmcfd';

(async () => {
  const targets = await (await fetch(CDP + '/json/list')).json();
  const sw = targets.find(t => t.url && t.url.startsWith('chrome-extension://' + EXT_ID) && t.type === 'service_worker');
  if (!sw) { console.log('SW not found'); process.exit(2); }
  const ws = new WebSocket(sw.webSocketDebuggerUrl);
  await new Promise((res, rej) => { ws.onopen = res; ws.onerror = rej; });
  const re = filter ? new RegExp(filter, 'i') : null;
  const t0 = Date.now();
  const stamp = () => ((Date.now() - t0) / 1000).toFixed(1).padStart(6) + 's';
  let msgId = 0;
  const send = (method, params) => new Promise((res) => {
    const id = ++msgId;
    ws.send(JSON.stringify({ id, method, params }));
    setTimeout(() => res(null), 3000);
  });
  ws.onmessage = (e) => {
    const m = JSON.parse(e.data);
    if (m.method === 'Runtime.consoleAPICalled') {
      const txt = (m.params.args || []).map(a => a.value !== undefined ? a.value : (a.description || '')).join(' ');
      if (!re || re.test(txt)) console.log(stamp() + '  [' + (m.params.type || 'log') + '] ' + txt.slice(0, 200));
    }
  };
  ws.onclose = () => console.log(stamp() + '  !! SESSION CLOSED (SW was evicted or restarted - the probe is gone)');
  await send('Runtime.enable');
  console.log(stamp() + '  session attached (SW kept alive; console filter: ' + (filter || '<all>') + ')');
  console.log(stamp() + '  holding for ' + seconds + 's ...');
  await new Promise(r => setTimeout(r, seconds * 1000));
  console.log(stamp() + '  hold finished');
  ws.close();
})().catch(e => { console.error('FATAL:', e.message); process.exit(1); });
