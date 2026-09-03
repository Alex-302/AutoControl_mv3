// CDP: dump capture state + filter the SW log buffer for AC-CAPTURE lines.
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
  };
  const send = (method, params) => new Promise((res) => {
    const id = ++msgId;
    pending.set(id, res);
    ws.send(JSON.stringify({ id, method, params }));
  });
  await send('Runtime.enable');
  const r = await send('Runtime.evaluate', {
    expression: `(() => {
      const o = {};
      try { o.on = (typeof __acCaptureOn !== 'undefined') ? __acCaptureOn : 'undef'; } catch (e) {}
      try { o.armedForMs = (typeof __acCaptureT !== 'undefined' && __acCaptureT) ? (Date.now() - __acCaptureT) : 0; } catch (e) {}
      try { o.stage = (typeof __acCaptureStage !== 'undefined') ? __acCaptureStage : 'undef'; } catch (e) {}
      try { o.pages = (typeof __acExtPagesOpen !== 'undefined') ? __acExtPagesOpen : 'undef'; } catch (e) {}
      try {
        o.captureLog = (typeof __acLogBuf !== 'undefined' && __acLogBuf)
          ? __acLogBuf.map(e => '[' + (e[0] || 'log') + '] ' + e[1].join(' ')).filter(l => /CAPTURE|capture|type 40|type40/i.test(l)).slice(-30)
          : null;
      } catch (e) { o.err = String(e); }
      return o;
    })()`,
    returnByValue: true,
  });
  const v = r.result && r.result.result && r.result.result.value;
  console.log(JSON.stringify(v, null, 1));
  ws.close();
}
main().catch(e => { console.error('FATAL:', e); process.exit(1); });
