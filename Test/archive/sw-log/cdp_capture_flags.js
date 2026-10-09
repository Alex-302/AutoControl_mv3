// CDP: capture flags check + idle console watch.
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
  await new Promise((r) => setTimeout(r, 3000));
  const r = await send('Runtime.evaluate', {
    expression: `(() => {
      const out = {};
      try { out.acCaptureOn = __acCaptureOn; } catch(e) { out.acCaptureOn = 'ERR'; }
      try { out.acCaptureT = __acCaptureT ? new Date(__acCaptureT).toISOString() : null; } catch(e) {}
      try { out.acRaw760 = __acRaw760; } catch(e) { out.acRaw760 = 'ERR'; }
      try { out.acCaptureStage = __acCaptureStage; } catch(e) {}
      try { out.up = Math.round((Date.now() - __acSwStart)/1000); } catch(e) {}
      return out;
    })()`,
    returnByValue: true,
  });
  console.log('STATE:', JSON.stringify(r.result && r.result.result && r.result.result.value));
  console.log('--- console during 3s idle (' + events.length + ') ---');
  for (const ev of events.slice(-20)) console.log('[' + ev.type + '] ' + ev.text.slice(0, 250));
  ws.close();
}
main().catch(e => { console.error('FATAL:', e); process.exit(1); });
