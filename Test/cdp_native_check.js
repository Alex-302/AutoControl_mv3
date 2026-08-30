// CDP: ping native (type 920) + rebuild config and capture type-60 log.
// Usage: node Test/cdp_native_check.js [port]
'use strict';
const port = process.argv[2] || '9223';
const CDP = `http://127.0.0.1:${port}`;
const EXT_ID = 'lkaihdpfpifdlgoapbfocpmekbokmcfd';

async function main() {
  const targets = await (await fetch(CDP + '/json/list')).json();
  const sw = targets.find(t => t.url && t.url.startsWith('chrome-extension://' + EXT_ID) && t.type === 'service_worker');
  if (!sw) { console.log('SW not found'); process.exit(2); }
  const ws = new WebSocket(sw.webSocketDebuggerUrl);
  await new Promise((res, rej) => { ws.onopen = res; ws.onerror = rej; });
  let msgId = 0;
  const pending = new Map();
  const events = [];
  ws.onmessage = (e) => {
    const m = JSON.parse(e.data);
    if (m.id && pending.has(m.id)) { pending.get(m.id)(m); pending.delete(m.id); }
    else if (m.method === 'Runtime.consoleAPICalled') {
      const args = (m.params.args || []).map(a => a.value !== undefined ? a.value : (a.description || a.type));
      events.push({ type: m.params.type, text: args.join(' ') });
    } else if (m.method === 'Runtime.exceptionThrown') {
      events.push({ type: 'EXCEPTION', text: JSON.stringify(m.params.exceptionDetails).slice(0, 2000) });
    }
  };
  const send = (method, params) => new Promise((res) => {
    const id = ++msgId;
    pending.set(id, res);
    ws.send(JSON.stringify({ id, method, params }));
  });
  await send('Runtime.enable');

  // 1) native ping via bundle _Lk(920)
  const ping = await send('Runtime.evaluate', {
    expression: `new Promise((res) => {
      let done = false;
      const fin = (x) => { if (!done) { done = true; res(x); } };
      try {
        _Lk(920, "", (r) => fin('CB: ' + JSON.stringify(r)), 2000);
        setTimeout(() => fin('TIMEOUT(2.5s)'), 2500);
      } catch (e) { fin('THREW: ' + (e && e.stack || e)); }
    })`,
    awaitPromise: true,
    returnByValue: true,
  });
  const pingRes = ping.result && ping.result.result;
  console.log('PING 920 →', JSON.stringify(pingRes && pingRes.value));

  // 2) rebuild and capture type 60
  await send('Runtime.evaluate', {
    expression: `(function(){ try { _Gf({}, function(){}); return 'started'; } catch(e) { return 'THREW: ' + (e && e.stack || e); } })()`,
    returnByValue: true,
  });
  await new Promise((res) => setTimeout(res, 12000));
  console.log('--- captured ' + events.length + ' console events ---');
  for (const ev of events) {
    console.log('[' + ev.type + '] ' + ev.text.slice(0, 3000));
  }
  ws.close();
}
main().catch(e => { console.error('FATAL:', e); process.exit(1); });
