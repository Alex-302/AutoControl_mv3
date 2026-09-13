// CDP key test: inject Ctrl+Tab at OS level (via _ac_keypress.ps1), observe
// the SW trigger logs + active-tab change.
// Usage: node Test/cdp_keytest.js [quick|hold] [holdMs]
'use strict';
const { execSync } = require('child_process');
const path = require('path');
const port = '9223';
const CDP = `http://127.0.0.1:${port}`;
const EXT_ID = 'lkaihdpfpifdlgoapbfocpmekbokmcfd';
const PS1 = path.join(__dirname, '_ac_keypress.ps1');

const mode = process.argv[2] || 'quick';
const holdMs = process.argv[3] || 600;

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

  const activeTab = async (label) => {
    const r = await evalSW(ws, send, `new Promise(r => chrome.tabs.query({active:true,currentWindow:true}, t => r({id: t[0]&&t[0].id, url: (t[0]&&t[0].url||'').slice(0,80), title: (t[0]&&t[0].title||'').slice(0,60)})))`);
    console.log(label + ':', JSON.stringify(r && r.value));
    return r && r.value;
  };

  const before = await activeTab('BEFORE');
  events.length = 0;
  console.log('\n--- injecting: ' + mode + (mode === 'hold' ? ' (hold ' + holdMs + 'ms)' : '') + ' ---');
  const out = execSync(`powershell -NoProfile -ExecutionPolicy Bypass -File "${PS1}" -HoldMs ${mode === 'hold' ? holdMs : 0}`, { encoding: 'utf8', timeout: 15000 });
  console.log('ps:', out.trim());
  await new Promise((r) => setTimeout(r, mode === 'hold' ? 2500 : 1800));
  const after = await activeTab('AFTER ');
  console.log('\n--- SW console events during press (' + events.length + ') ---');
  for (const ev of events) {
    const t = ev.text;
    if (/750|trigger|Trigger|AC-MV3|key|Tab|gesture|RBTN/i.test(t)) console.log('[' + ev.type + '] ' + t.slice(0, 500));
  }
  const switched = before && after && before.id !== after.id;
  console.log('\nRESULT: active tab ' + (switched ? 'CHANGED ' + before.id + ' → ' + after.id + ' (' + (after.title || after.url) + ')' : 'UNCHANGED (' + (after && (after.title || after.url)) + ')'));
  ws.close();
}
main().catch(e => { console.error('FATAL:', e); process.exit(1); });
