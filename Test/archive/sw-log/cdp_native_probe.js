// CDP: real native probe — getStatus + type 200 callback (bypasses 920 fast-path).
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
  // 1) SW status (connected etc — SW-internal, may not be visible)
  const r1 = await send('Runtime.evaluate', {
    expression: `new Promise(res => {
      try {
        chrome.runtime.sendMessage({ cmd: 'getStatus' }, (st) => res({ status: st }));
      } catch(e) { res({ threw: String(e) }); }
      setTimeout(() => res({ timeout: true }), 3000);
    })`,
    awaitPromise: true, returnByValue: true,
  });
  console.log('STATUS:', JSON.stringify(r1.result && r1.result.result && r1.result.result.value));

  // 2) real native callback via bundle _Lk with type 200 (thumbSize — needs engine)
  const r2 = await send('Runtime.evaluate', {
    expression: `new Promise(res => {
      let done = false;
      const fin = (x) => { if (!done) { done = true; res(x); } };
      try {
        _Lk(200, { thumbSize: 30 }, (r) => fin({ cb: String(r).slice(0, 200) }), 3000);
        setTimeout(() => fin({ timeout: true }), 3500);
      } catch(e) { fin({ threw: String(e && e.stack || e).slice(0, 200) }); }
    })`,
    awaitPromise: true, returnByValue: true,
  });
  console.log('TYPE 200:', JSON.stringify(r2.result && r2.result.result && r2.result.result.value));

  // 3) bundle _Lk binding check
  const r3 = await send('Runtime.evaluate', {
    expression: `(() => { try { return { Lk: typeof _Lk, acNativeSend: typeof _acNativeSend, Vy: typeof _Vy }; } catch(e) { return { err: String(e) }; } })()`,
    returnByValue: true,
  });
  console.log('BINDINGS:', JSON.stringify(r3.result && r3.result.result && r3.result.result.value));
  ws.close();
}
main().catch(e => { console.error('FATAL:', e); process.exit(1); });
