// CDP key test v2: multi-channel SW log capture + active tab before/after.
// Usage: node Test/cdp_keytest2.js <hold|quick|esc> [holdMs] [repeat] [ctrlFirst]
'use strict';
const { execSync } = require('child_process');
const path = require('path');
const port = '9223';
const CDP = `http://127.0.0.1:${port}`;
const EXT_ID = 'lkaihdpfpifdlgoapbfocpmekbokmcfd';
const PS1 = path.join(__dirname, '_ac_keypress2.ps1');

const mode = process.argv[2] || 'quick';
const holdMs = process.argv[3] || 600;
const repeat = process.argv[4] === 'repeat';
const ctrlFirst = process.argv[5] === 'ctrlFirst';

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

  // install capture wrapper over the CURRENT console methods + reset __acLogBuf view
  await evalSW(ws, send, `(() => {
    window.__acCap = [];
    window.__acCapBufStart = (typeof __acLogBuf !== 'undefined' && __acLogBuf) ? __acLogBuf.length : -1;
    for (const m of ['warn','log','info','debug']) {
      try {
        const orig = console[m] ? console[m].bind(console) : (()=>{});
        console[m] = function() {
          const s = [].slice.call(arguments).join(' ');
          window.__acCap.push('[' + m + '] ' + s);
          try { orig.apply(console, arguments); } catch(e) {}
        };
      } catch(e) {}
    }
    return 'capture installed';
  })()`);

  const activeTab = async (label) => {
    const r = await evalSW(ws, send, `new Promise(r => chrome.tabs.query({active:true,currentWindow:true}, t => r({id: t[0]&&t[0].id, url: (t[0]&&t[0].url||'').slice(0,90), title: (t[0]&&t[0].title||'').slice(0,50)})))`);
    console.log(label + ':', JSON.stringify(r && r.value));
    return r && r.value;
  };

  const before = await activeTab('BEFORE');
  cdpEvents.length = 0;

  let args = '';
  if (mode === 'esc') args = '-Esc';
  else if (mode === 'quick') args = '-HoldMs 0';
  else args = `-HoldMs ${holdMs}${repeat ? ' -RepeatTab' : ''}${ctrlFirst ? ' -ReleaseFirst ctrl' : ''}`;
  console.log('\n--- injecting: ' + args + ' ---');
  const out = execSync(`powershell -NoProfile -ExecutionPolicy Bypass -File "${PS1}" ${args}`, { encoding: 'utf8', timeout: 20000 });
  console.log('ps:', out.trim());
  await new Promise((r) => setTimeout(r, mode === 'esc' ? 800 : 2500));

  const after = await activeTab('AFTER ');

  const cap = await evalSW(ws, send, `(() => {
    const out = { cap: window.__acCap || [], bufTail: [] };
    try {
      if (typeof __acLogBuf !== 'undefined' && __acLogBuf) {
        const start = window.__acCapBufStart >= 0 ? window.__acCapBufStart : 0;
        out.bufTail = __acLogBuf.slice(start).map(e => '[' + e[0] + '] ' + e[1].join(' '));
      }
    } catch(e) { out.bufErr = String(e); }
    return out;
  })()`);
  const capVal = cap && cap.value || {};
  console.log('\n--- captured (' + capVal.cap.length + ' wrapper + ' + (capVal.bufTail||[]).length + ' buf + ' + cdpEvents.length + ' cdp) ---');
  const all = [...capVal.cap, ...(capVal.bufTail||[]), ...cdpEvents.map(e => '[' + e.type + '] ' + e.text)];
  for (const t of all) {
    if (/750|Trigger|trigger|AC-MV3|key|Tab|gesture|menu|Menu|RBTN/i.test(t)) console.log(t.slice(0, 600));
  }
  const switched = before && after && before.id !== after.id;
  console.log('\nRESULT: active tab ' + (switched ? 'CHANGED ' + before.id + ' → ' + after.id + ' (' + (after.title || after.url) + ')' : 'UNCHANGED (' + (after && (after.title || after.url)) + ')'));
  ws.close();
}
main().catch(e => { console.error('FATAL:', e); process.exit(1); });
