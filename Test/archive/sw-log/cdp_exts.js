// CDP: list installed extensions (management API) + SW connection status.
'use strict';
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
  const r = await send('Runtime.evaluate', {
    expression: `(async () => {
      const out = { exts: [] };
      try {
        const exts = await chrome.management.getAll();
        out.exts = exts.filter(e => /autocontrol|hrich/i.test(e.name + ' ' + e.id))
          .map(e => ({ id: e.id, name: e.name, enabled: e.enabled, type: e.type }));
      } catch(e) { out.extErr = String(e); }
      try {
        const st = await new Promise(res => chrome.runtime.sendMessage({ cmd: 'getStatus' }, res));
        out.status = st;
      } catch(e) { out.statusErr = String(e); }
      return out;
    })()`,
    awaitPromise: true,
    returnByValue: true,
  });
  console.log(JSON.stringify(r.result && r.result.result && r.result.result.value, null, 2));
  ws.close();
}
main().catch(e => { console.error('FATAL:', e); process.exit(1); });
