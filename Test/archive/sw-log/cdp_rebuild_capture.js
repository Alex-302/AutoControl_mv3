// CDP: rebuild the config chain (_Gf) in the SW and capture the type-60 map log.
// Usage: node Test/cdp_rebuild_capture.js [port]
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
      events.push({ type: 'EXCEPTION', text: JSON.stringify(m.params.exceptionDetails).slice(0, 1500) });
    }
  };
  const send = (method, params) => new Promise((res) => {
    const id = ++msgId;
    pending.set(id, res);
    ws.send(JSON.stringify({ id, method, params }));
  });
  await send('Runtime.enable');
  const r = await send('Runtime.evaluate', {
    expression: `(function(){ try { _Gf({}, function(){ console.warn('[AC-MV3] _Gf rebuild finished'); }); return 'started'; } catch(e) { return 'THREW: ' + (e && e.stack || e); } })()`,
    returnByValue: true,
  });
  console.log('evaluate:', JSON.stringify(r.result && r.result.result && r.result.result.value));
  await new Promise((res) => setTimeout(res, 5000));
  console.log('--- captured ' + events.length + ' console events ---');
  for (const ev of events) {
    console.log('[' + ev.type + '] ' + ev.text.slice(0, 2000));
  }
  ws.close();
}
main().catch(e => { console.error('FATAL:', e); process.exit(1); });
