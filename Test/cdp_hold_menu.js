// CDP: hold Ctrl+Tab, query menu state (185) WHILE holding, then release.
// Usage: node Test/cdp_hold_menu.js [holdMs]
'use strict';
const { execSync } = require('child_process');
const path = require('path');
const port = '9223';
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
  ws.onmessage = (e) => {
    const m = JSON.parse(e.data);
    if (m.id && pending.has(m.id)) { pending.get(m.id)(m); pending.delete(m.id); }
  };
  const send = (method, params) => new Promise((res) => {
    const id = ++msgId;
    pending.set(id, res);
    ws.send(JSON.stringify({ id, method, params }));
  });
  await send('Runtime.enable');

  // helper: query native menu state exactly like the bundle's H() — _Lk(175, null)
  const menuState = (label) => send('Runtime.evaluate', {
    expression: `new Promise(r => { try { _Lk(175, null, res => r({ label: ${JSON.stringify(label)}, raw: res, json: (() => { try { return JSON.stringify(res); } catch(e) { return 'circular'; } })() }), 3000); } catch(e) { r({ err: String(e) }); } })`,
    awaitPromise: true,
    returnByValue: true,
  });

  console.log('--- Ctrl down + Tab down ---');
  const out = execSync(`powershell -NoProfile -ExecutionPolicy Bypass -File "${path.join(__dirname, '_ac_keypress2.ps1')}" -HoldMs 4000`, { encoding: 'utf8', timeout: 20000 });
  console.log('ps started (will hold 4s):', out.trim());

  // wait for the hold to fire (400ms) + menu render
  await new Promise(r => setTimeout(r, 1200));
  const st1 = await menuState('at +1.2s while holding');
  console.log('MENU STATE:', JSON.stringify(st1.result && st1.result.result && st1.result.result.value).slice(0, 500));

  // press Tab again → moveSelectMark
  const out2 = execSync(`powershell -NoProfile -ExecutionPolicy Bypass -File "${path.join(__dirname, '_ac_tabtap.ps1')}"`, { encoding: 'utf8', timeout: 10000 });
  console.log('tab tap:', out2.trim());
  await new Promise(r => setTimeout(r, 800));
  const st2 = await menuState('after Tab tap');
  console.log('MENU STATE:', JSON.stringify(st2.result && st2.result.result && st2.result.result.value).slice(0, 500));

  // wait for the 4s hold to end (release)
  await new Promise(r => setTimeout(r, 3200));
  ws.close();
  console.log('done');
}
main().catch(e => { console.error('FATAL:', e); process.exit(1); });
