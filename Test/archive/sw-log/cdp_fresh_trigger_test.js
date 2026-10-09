// CDP: fresh config rebuild → immediate Ctrl+Tab hold → watch for 750 triggers.
// Usage: node Test/cdp_fresh_trigger_test.js [holdMs]
'use strict';
const { execSync } = require('child_process');
const path = require('path');
const port = '9223';
const CDP = `http://127.0.0.1:${port}`;
const EXT_ID = 'lkaihdpfpifdlgoapbfocpmekbokmcfd';
const PS1 = path.join(__dirname, '_ac_keypress2.ps1');
const holdMs = process.argv[2] || 700;

async function evalSW(ws, send, expression, awaitPromise = true) {
  const r = await send('Runtime.evaluate', { expression, awaitPromise, returnByValue: true });
  return r.result && r.result.result;
}

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
    }
  };
  const send = (method, params) => new Promise((res) => {
    const id = ++msgId;
    pending.set(id, res);
    ws.send(JSON.stringify({ id, method, params }));
  });
  await send('Runtime.enable');

  // capture console without breaking it (append-only, no _Lk touch)
  await evalSW(ws, send, `(() => {
    window.__acCap2 = [];
    for (const m of ['log','warn','info','debug']) {
      try {
        const orig = console[m] ? console[m].bind(console) : (()=>{});
        console[m] = function(){ window.__acCap2.push('['+m+'] '+[].slice.call(arguments).join(' ')); try{ orig.apply(console, arguments); }catch(e){} };
      } catch(e) {}
    }
    return 'cap ok';
  })()`);

  // 1) fresh rebuild
  await evalSW(ws, send, `(function(){ try { _Gf({}, function(){ console.warn('[AC-TEST] Gf done'); }); return 'started'; } catch(e) { return 'THREW: ' + (e && e.stack || e); } })()`);
  await new Promise((r) => setTimeout(r, 2500));

  // 2) hold Ctrl+Tab
  console.log('injecting hold ' + holdMs + 'ms');
  execSync(`powershell -NoProfile -ExecutionPolicy Bypass -File "${PS1}" -HoldMs ${holdMs}`, { encoding: 'utf8', timeout: 15000 });
  await new Promise((r) => setTimeout(r, 2500));

  // 3) dump filtered console
  const dump = await evalSW(ws, send, `(() => { const c = window.__acCap2 || []; return c.filter(x => /750|Trigger|trigger|openMenu|closeMenu|170|175|185|Gf done|type 60|Config loaded/i.test(x)).slice(-60); })()`);
  const cap = dump && dump.value || [];
  console.log('--- filtered events (' + cap.length + ') ---');
  for (const x of cap) console.log(x.slice(0, 400));

  // 4) current active tab
  const r = await evalSW(ws, send, `new Promise(r => chrome.tabs.query({active:true,currentWindow:true}, t => r({id: t[0]&&t[0].id, url: (t[0]&&t[0].url||'').slice(0,70)})))`);
  console.log('ACTIVE:', JSON.stringify(r && r.value));
  ws.close();
}
main().catch(e => { console.error('FATAL:', e); process.exit(1); });
