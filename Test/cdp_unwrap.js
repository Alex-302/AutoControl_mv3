// CDP: restore window._Lk to its original (saved by cdp_lk_trace) or the
// _acNativeSend alias — NEVER delete window._Lk (it is the ONLY global
// reference to the shim's _Lk; deleting breaks closeMenu/moveSelectMark
// until the SW restarts — verified 2026-08-30 the hard way).
'use strict';
(async () => {
  const targets = await (await fetch('http://127.0.0.1:9223/json/list')).json();
  const sw = targets.find(t => t.url && t.url.startsWith('chrome-extension://lkaihdpfpifdlgoapbfocpmekbokmcfd') && t.type === 'service_worker');
  if (!sw) { console.log('SW not found'); process.exit(2); }
  const ws = new WebSocket(sw.webSocketDebuggerUrl);
  await new Promise((res, rej) => { ws.onopen = res; ws.onerror = rej; });
  let id = 0; const pend = new Map();
  ws.onmessage = (e) => { const m = JSON.parse(e.data); if (m.id && pend.has(m.id)) { pend.get(m.id)(m); pend.delete(m.id); } };
  const send = (method, params) => new Promise((res) => { const i = ++id; pend.set(i, res); ws.send(JSON.stringify({ id: i, method, params })); });
  const r = await send('Runtime.evaluate', {
    expression: `(() => {
      const out = { before: typeof _Lk };
      if (typeof window.__acOrigLk === 'function') {
        window._Lk = window.__acOrigLk;
        out.restored = 'orig';
      } else if (typeof _acNativeSend === 'function') {
        window._Lk = (a, b, c, g) => _acNativeSend(a, b, c, g);
        out.restored = 'alias';
      }
      delete window.__acOrigLk;
      delete window.__acLkWrapped;
      delete window.__acLkCalls;
      if (typeof window.__acOrigW2 === 'function') {
        window._w = window.__acOrigW2;
        out.wRestored = true;
      }
      delete window.__acOrigW2;
      delete window.__acPr;
      for (const m of ['log','warn','info','debug']) {
        const k = '__acOrigConsole' + m;
        if (typeof window[k] === 'function') { try { console[m] = window[k]; } catch(e) {} delete window[k]; }
      }
      out.after = typeof _Lk;
      return out;
    })()`,
    returnByValue: true,
  });
  console.log(JSON.stringify(r.result && r.result.result && r.result.result.value));
  ws.close();
})();
