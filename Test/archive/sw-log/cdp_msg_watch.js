// CDP: catch ALL native messages (750/760/etc) during a key press.
'use strict';
const { execSync } = require('child_process');
const path = require('path');
const port = '9223';
const CDP = `http://127.0.0.1:${port}`;
const EXT_ID = 'lkaihdpfpifdlgoapbfocpmekbokmcfd';
const PS1 = path.join(__dirname, '_ac_keypress2.ps1');

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
      events.push({ type: m.params.type, text: args.join(' ').slice(0, 300) });
    }
  };
  const send = (method, params) => new Promise((res) => {
    const id = ++msgId;
    pending.set(id, res);
    ws.send(JSON.stringify({ id, method, params }));
  });
  await send('Runtime.enable');

  // ensure console capture without breaking
  await send('Runtime.evaluate', {
    expression: `(() => {
      window.__acCap3 = [];
      for (const m of ['log','warn','info','debug']) {
        try {
          const orig = console[m] ? console[m].bind(console) : (()=>{});
          console[m] = function(){ window.__acCap3.push('['+m+'] '+[].slice.call(arguments).join(' ').slice(0,300)); try{ orig.apply(console, arguments); }catch(e){} };
        } catch(e) {}
      }
      return 'ok';
    })()`,
    returnByValue: true,
  });

  execSync(`powershell -NoProfile -ExecutionPolicy Bypass -File "${PS1}" -HoldMs 700`, { encoding: 'utf8', timeout: 15000 });
  await new Promise((r) => setTimeout(r, 2000));

  const dump = await send('Runtime.evaluate', {
    expression: `(() => { const c = window.__acCap3 || []; return { total: c.length, filtered: c.filter(x => /750|760|Trigger|trigger|Native type|Native msg/.test(x)).slice(-80) }; })()`,
    returnByValue: true,
  });
  const v = dump.result && dump.result.result && dump.result.result.value;
  console.log('total:', v && v.total);
  for (const x of (v && v.filtered || [])) console.log(x);
  ws.close();
}
main().catch(e => { console.error('FATAL:', e); process.exit(1); });
