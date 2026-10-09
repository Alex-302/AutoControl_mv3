// zone_swtail.js - capture ONLY the service-worker console lines that appear
// AFTER this script attaches.
//
// WHY (2026-09-12): Runtime.consoleAPICalled REPLAYS the whole session backlog
// on attach, and its `timestamp` is NOT a wall clock (it is time since the
// worker started) — so "newest line wins" reasoning is unreliable and the old
// new/old tagging was meaningless. This version injects a unique sentinel
// marker into the SW console right after enabling Runtime; every line that
// arrives AFTER the sentinel is genuinely live and is printed with a "»"
// prefix. Replayed backlog lines are dropped.
//
// Usage: node Test/zone_swtail.js <port> <seconds> [regex]
//   node Test/zone_swtail.js 9223 20 "AC-MV3-ZONE|Trigger 750"
'use strict';
const PORT = process.argv[2] || '9223';
const seconds = Number(process.argv[3] || 15);
const re = new RegExp(process.argv[4] || 'AC-MV3-ZONE|Trigger 750', 'i');
const EXT = 'lkaihdpfpifdlgoapbfocpmekbokmcfd';

(async () => {
  const targets = await (await fetch(`http://127.0.0.1:${PORT}/json/list`)).json();
  const sw = targets.find(t => t.type === 'service_worker' && t.url.includes(EXT));
  if (!sw) { console.log('NO SERVICE WORKER'); process.exit(1); }
  const ws = new WebSocket(sw.webSocketDebuggerUrl);
  await new Promise((res, rej) => { ws.onopen = res; ws.onerror = rej; });

  const sentinel = 'TAILSTART_' + Math.random().toString(36).slice(2, 8);
  let armed = false;
  let shown = 0;

  ws.onmessage = e => {
    const m = JSON.parse(e.data);
    if (m.method !== 'Runtime.consoleAPICalled') return;
    const text = (m.params.args || [])
      .map(a => a.value !== undefined ? a.value : a.description || '')
      .join(' ');
    if (!armed) {
      if (text.indexOf(sentinel) !== -1) { armed = true; console.log(`[tail] armed (sentinel ${sentinel}) - live lines follow`); }
      return; // drop the replayed backlog
    }
    if (!re.test(text)) return;
    shown++;
    console.log('> ' + text.slice(0, 240));
  };

  ws.send(JSON.stringify({ id: 1, method: 'Runtime.enable', params: {} }));
  await new Promise(r => setTimeout(r, 600));
  // Inject the sentinel (this also proves the console pipeline works).
  ws.send(JSON.stringify({
    id: 2, method: 'Runtime.evaluate', params: {
      expression: `console.warn('[AC-TEST] ${sentinel}'); 'ok'`, returnByValue: true
    }
  }));
  await new Promise(r => setTimeout(r, 800));
  if (!armed) { console.log('[tail] WARN: sentinel not seen - console pipeline may be broken'); }

  setTimeout(() => {
    console.log(`[tail] done (${shown} live lines shown)`);
    try { ws.close(); } catch (e) {}
    process.exit(0);
  }, seconds * 1000);
})().catch(e => { console.error('ERR', e.message); process.exit(1); });
