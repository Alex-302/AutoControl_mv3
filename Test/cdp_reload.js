// CDP: reload the extension SW (chrome.runtime.reload), wait, reconnect.
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
    expression: `(function(){ try { chrome.runtime.reload(); return 'reload called'; } catch(e) { return 'THREW: ' + e; } })()`,
    returnByValue: true,
  });
  console.log(JSON.stringify(r.result && r.result.result && r.result.result.value));
  ws.close();
  console.log('waiting for SW restart...');
  await new Promise((res) => setTimeout(res, 12000));
  console.log('done waiting');
}
main().catch(e => { console.error('FATAL:', e); process.exit(1); });
