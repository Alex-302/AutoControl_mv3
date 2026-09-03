// CDP diagnostic: connect to a Chrome/Canary with --remote-debugging-port
// and dump the AutoControl extension's storage + SW in-memory config.
// Usage: node Test/cdp_storage_dump.js [port]   (default 9223)
'use strict';
const port = process.argv[2] || '9223';
const EXT_ID = process.argv[3] || 'lkaihdpfpifdlgoapbfocpmekbokmcfd';
const CDP = `http://127.0.0.1:${port}`;
const EXT = 'chrome-extension://' + EXT_ID;

async function getTargets() {
  const res = await fetch(CDP + '/json/list');
  return await res.json();
}

async function openExtensionPage(url) {
  // Chrome requires PUT for /json/new in modern versions
  try {
    const res = await fetch(CDP + '/json/new?' + encodeURIComponent(url), { method: 'PUT' });
    if (res.ok) return await res.json();
  } catch (e) { /* fall through to GET */ }
  try {
    const res = await fetch(CDP + '/json/new?' + encodeURIComponent(url));
    if (res.ok) return await res.json();
  } catch (e) {}
  return null;
}

function sleep(ms) { return new Promise(r => setTimeout(r, ms)); }

async function evaluate(target, expression) {
  const ws = new WebSocket(target.webSocketDebuggerUrl);
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
    expression, awaitPromise: true, returnByValue: true,
  });
  ws.close();
  return r;
}

const EXPR = `(async () => {
  const out = {};
  const j = (v, n) => { try { const s = JSON.stringify(v); return s && s.length > n ? s.slice(0, n) + '…[' + s.length + ']' : s; } catch (e) { return 'ERR ' + e; } };
  try {
    const r = await chrome.storage.local.get(null);
    out.storageKeys = Object.keys(r).sort();
    out.trigIds = (r.trigActList || []).map(t => t[0]).join(',');
    out.trigActList = j(r.trigActList, 4000);
    out.sections = j(r.sections, 1000);
    out.customEntities = j(r.customEntities, 1000);
    out.advOpts = j(r.advOpts, 1000);
  } catch (e) { out.storageErr = String(e); }
  try {
    if (typeof _Yp !== 'undefined') {
      out.Yp_keys = Object.keys(_Yp).join(',');
      out.Yp_json = j(_Yp, 6000);
    }
  } catch (e) { out.YpErr = String(e); }
  try {
    out.if_type = typeof _if;
    out.if_isMap = typeof _if !== 'undefined' && typeof _if.get === 'function';
    out.if_size = typeof _if !== 'undefined' && typeof _if.size === 'number' ? _if.size : undefined;
    if (out.if_isMap) out.if_keys = [..._if.keys()].join(',');
  } catch (e) { out.ifErr = String(e); }
  try { out.connected = typeof connected !== 'undefined' ? connected : 'undef'; } catch (e) { out.connected = 'ERR'; }
  try { out.handshakeDone = typeof handshakeDone !== 'undefined' ? handshakeDone : 'undef'; } catch (e) { out.handshakeDone = 'ERR'; }
  try { out.configChainStarted = typeof configChainStarted !== 'undefined' ? configChainStarted : 'undef'; } catch (e) {}
  try {
    if (typeof __acLogBuf !== 'undefined') out.logBuf = j(__acLogBuf, 6000);
  } catch (e) { out.logBufErr = String(e); }
  return out;
})()`;

async function main() {
  let targets = await getTargets();
  console.log('--- all targets (' + targets.length + ') ---');
  for (const t of targets) {
    console.log('  [' + t.type + '] ' + t.url + (t.title ? '  :: ' + t.title : ''));
  }
  let target = targets.find(t => t.url && t.url.startsWith(EXT) && t.type === 'service_worker') ||
               targets.find(t => t.url && t.url.startsWith(EXT) && /main\.html/.test(t.url)) ||
               targets.find(t => t.url && t.url.startsWith(EXT));
  if (!target) {
    console.log('\nNo extension target alive (SW asleep, no settings page open).');
    console.log('Opening main.html to wake the SW...');
    const opened = await openExtensionPage('chrome-extension://lkaihdpfpifdlgoapbfocpmekbokmcfd/main.html');
    console.log('open result:', opened ? opened.url || opened.title || 'ok' : 'FAILED');
    await sleep(2500);
    targets = await getTargets();
    target = targets.find(t => t.url && t.url.startsWith(EXT) && t.type === 'service_worker') ||
             targets.find(t => t.url && t.url.startsWith(EXT));
  }
  if (!target) {
    console.log('\nSTILL no extension target. Is the extension loaded in this browser?');
    process.exit(2);
  }
  console.log('\n--- evaluating in: ' + target.type + ' ' + target.url + ' ---');
  const r = await evaluate(target, EXPR);
  if (r.error) { console.log('CDP error:', JSON.stringify(r.error)); process.exit(3); }
  const res = r.result && r.result.result;
  if (!res) { console.log('unexpected response:', JSON.stringify(r).slice(0, 500)); process.exit(4); }
  if (res.subtype === 'error' || res.type === 'undefined' && res.description) {
    console.log('EVAL ERROR:', res.description || JSON.stringify(res));
    process.exit(5);
  }
  console.log(JSON.stringify(res.value, null, 2));
}
main().catch(e => { console.error('FATAL:', e); process.exit(1); });
