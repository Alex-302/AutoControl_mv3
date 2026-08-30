// CDP: install contextmenu listeners on the page, inject a REAL OS RMB click
// (via _ac_mouse.ps1), and report whether the native block let the button
// through to Chrome (contextmenu event = block failed → menu appears).
// Usage: node Test/cdp_rmb_probe.js [port] [lmb|rmb] [seconds]
'use strict';
const { execFileSync } = require('child_process');
const path = require('path');
const port = process.argv[2] || '9223';
const which = process.argv[3] || 'rmb';
const waitMs = +(process.argv[4] || 3000);
const CDP = `http://127.0.0.1:${port}`;

async function main() {
  const targets = await (await fetch(CDP + '/json/list')).json();
  const page = targets.find(t => t.type === 'page' && t.url && t.url.startsWith('http://sxs'));
  if (!page) { console.log('no sxs page'); process.exit(2); }
  const ws = new WebSocket(page.webSocketDebuggerUrl);
  await new Promise((res, rej) => { ws.onopen = res; ws.onerror = rej; });
  let msgId = 0;
  const pending = new Map();
  const logs = [];
  ws.onmessage = (e) => {
    const m = JSON.parse(e.data);
    if (m.id && pending.has(m.id)) { pending.get(m.id)(m); pending.delete(m.id); }
    else if (m.method === 'Runtime.consoleAPICalled') {
      const txt = (m.params.args || []).map(a => a.value !== undefined ? a.value : a.description || '').join(' ');
      logs.push(txt);
    }
  };
  const send = (method, params) => new Promise((res) => {
    const id = ++msgId;
    pending.set(id, res);
    ws.send(JSON.stringify({ id, method, params }));
  });
  await send('Runtime.enable');
  await send('Page.enable');
  // make the watched tab the ACTIVE tab and bring the Chrome window to front
  try { await send('Page.bringToFront'); } catch (e) {}
  await new Promise(r => setTimeout(r, 600));
  await send('Runtime.evaluate', {
    expression: `(() => {
      window.__ctx = { mousedown: 0, mouseup: 0, contextmenu: 0, seq: [] };
      for (const t of ['mousedown', 'mouseup', 'contextmenu']) {
        window.addEventListener(t, (e) => {
          window.__ctx[t]++;
          window.__ctx.seq.push(t + ':' + e.button);
          console.log('[CTX]', t, 'button=' + e.button);
        }, true);
      }
      return 'ok';
    })()`,
    returnByValue: true,
  });

  console.log('injecting ' + which + '...');
  const ps = path.join(__dirname, '_ac_mouse.ps1');
  try {
    const out = execFileSync('powershell', ['-ExecutionPolicy', 'Bypass', '-File', ps, '-Action', which, '-HoldMs', '150'], { encoding: 'utf8' });
    console.log('PS:', out.trim().split('\n').pop());
  } catch (e) {
    console.log('PS ERR:', e.message);
  }
  await new Promise(r => setTimeout(r, waitMs));

  const r = await send('Runtime.evaluate', {
    expression: `({ counts: window.__ctx, seq: window.__ctx.seq.slice(-30) })`,
    returnByValue: true,
  });
  console.log('COUNTS:', JSON.stringify(r.result && r.result.result && r.result.result.value));
  console.log('--- page console ---');
  logs.slice(-20).forEach(l => console.log(l));
  ws.close();
}
main().catch(e => { console.error('FATAL:', e.message); process.exit(1); });
