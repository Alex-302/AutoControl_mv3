// CDP: set a breakpoint on postMsg's type-60 branch in sw.js and capture the
// call stack when a type-60 is sent.
// Usage: node Test/cdp_break_postmsg.js [port]
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
  ws.onmessage = (e) => {
    const m = JSON.parse(e.data);
    if (m.id && pending.has(m.id)) { pending.get(m.id)(m); pending.delete(m.id); }
    else if (m.method === 'Debugger.paused') {
      console.log('=== PAUSED ===');
      const callFrames = m.params.callFrames || [];
      console.log('callFrames:', callFrames.length);
      for (const f of callFrames.slice(0, 12)) {
        console.log(`  ${f.functionName || '(anon)'} @ ${f.url.split('/').pop()}:${f.location.lineNumber + 1}`);
      }
      // resume
      ws.send(JSON.stringify({ id: ++msgId, method: 'Debugger.resume' }));
    }
  };
  const send = (method, params) => new Promise((res) => {
    const id = ++msgId;
    pending.set(id, res);
    ws.send(JSON.stringify({ id, method, params }));
  });
  await send('Debugger.enable');
  await send('Runtime.enable');
  // breakpoint on the strip line in postMsg (sw.js)
  const swUrl = 'file://' + sw.url.replace('chrome-extension://' + EXT_ID + '/', '').replace(/\//g, '\\');
  // use URL form:
  const r = await send('Debugger.setBreakpointByUrl', {
    url: 'chrome-extension://' + EXT_ID + '/sw.js',
    lineNumber: 2198, // `if (type === 60 && STRIP_RBTN_BLOCK)` (0-based)
  });
  console.log('breakpoint:', JSON.stringify(r.result));
  console.log('waiting for postMsg(60)...');
  await new Promise(r => setTimeout(r, 20000));
  ws.close();
}
main().catch(e => { console.error('FATAL:', e.message); process.exit(1); });
