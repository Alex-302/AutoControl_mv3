// CDP: full trace of console + _Lk sends during a Ctrl+Tab hold.
// Usage: node Test/cdp_full_trace.js [holdMs]
'use strict';
const { execSync } = require('child_process');
const path = require('path');
const port = '9223';
const CDP = `http://127.0.0.1:${port}`;
const EXT_ID = 'lkaihdpfpifdlgoapbfocpmekbokmcfd';
const PS1 = path.join(__dirname, '_ac_keypress2.ps1');
const holdMs = process.argv[2] || '700';

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
  const cdpEvents = [];
  ws.onmessage = (e) => {
    const m = JSON.parse(e.data);
    if (m.id && pending.has(m.id)) { pending.get(m.id)(m); pending.delete(m.id); }
    else if (m.method === 'Runtime.consoleAPICalled') {
      const args = (m.params.args || []).map(a => a.value !== undefined ? a.value : (a.description || a.type));
      cdpEvents.push({ type: m.params.type, text: args.join(' ') });
    }
  };
  const send = (method, params) => new Promise((res) => {
    const id = ++msgId;
    pending.set(id, res);
    ws.send(JSON.stringify({ id, method, params }));
  });
  await send('Runtime.enable');

  await evalSW(ws, send, `(() => {
    window.__acTr = [];
    // wrap console
    for (const m of ['warn', 'log', 'info', 'debug']) {
      try {
        const orig = console[m] ? console[m].bind(console) : (() => {});
        console[m] = function() {
          const s = [].slice.call(arguments).join(' ');
          window.__acTr.push('[' + m + '] ' + s);
          try { orig.apply(console, arguments); } catch(e) {}
        };
      } catch(e) {}
    }
    // wrap _Lk to trace outgoing types (do NOT touch window._Lk identity —
    // only the function VALUE used by call sites that captured it early is
    // safe to change; _acNativeSend is the live choke point)
    if (!window.__acLkWrapped) {
      const orig = _Lk;
      window.__acOrigLk = orig;
      window._Lk = function(a, b, c, g) {
        let brief = '';
        try { brief = JSON.stringify(b || null); if (brief.length > 200) brief = brief.slice(0, 200) + '…'; } catch(e) {}
        window.__acTr.push('→Lk ' + a + ' ' + brief);
        return orig.apply(this, arguments);
      };
      window.__acLkWrapped = true;
    }
    return 'ok';
  })()`);

  cdpEvents.length = 0;
  console.log('--- injecting hold ' + holdMs + 'ms ---');
  const out = execSync(`powershell -NoProfile -ExecutionPolicy Bypass -File "${PS1}" -HoldMs ${holdMs}`, { encoding: 'utf8', timeout: 20000 });
  console.log('ps:', out.trim());
  await new Promise((r) => setTimeout(r, 3000));

  const cap = await evalSW(ws, send, `(() => {
    const out = { tr: window.__acTr || [] };
    const buf = [];
    try {
      if (typeof __acLogBuf !== 'undefined' && __acLogBuf) {
        for (const e of __acLogBuf) buf.push('[' + (e[0] || 'log') + '] ' + e[1].join(' '));
      }
    } catch(e) {}
    out.buf = buf;
    return out;
  })()`);
  const v = cap && cap.value || {};
  const all = [...(v.tr || []), ...(v.buf || []), ...cdpEvents.map(e => '[' + e.type + '] ' + e.text)];
  console.log('\n=== TRACE (' + all.length + ' lines) ===');
  for (const t of all) {
    if (/750|Trigger|trigger|AC-MV3|170|175|185|menu|Menu|6145|812|811|810|error|Error|type 60|key|Key/i.test(t)) {
      console.log(t.slice(0, 700));
    }
  }
  ws.close();
}
main().catch(e => { console.error('FATAL:', e); process.exit(1); });
