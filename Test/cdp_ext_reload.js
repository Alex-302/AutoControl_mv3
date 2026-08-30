// CDP: reload the AutoControl unpacked extension via chrome://extensions
// (the extensions page UI uses shadow DOM — pierce it).
// Usage: node Test/cdp_ext_reload.js [port]
'use strict';
const port = process.argv[2] || '9223';
const CDP = `http://127.0.0.1:${port}`;
const EXT_ID = 'lkaihdpfpifdlgoapbfocpmekbokmcfd';

async function main() {
  const targets = await (await fetch(CDP + '/json/list')).json();
  const page = targets.find(t => t.type === 'page' && t.url && !t.url.startsWith('chrome-extension://'));
  if (!page) { console.log('no page target'); process.exit(2); }
  const ws = new WebSocket(page.webSocketDebuggerUrl);
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
  await send('Page.enable');
  await send('Runtime.enable');
  await send('Page.navigate', { url: 'chrome://extensions/' });
  await new Promise(r => setTimeout(r, 3500));

  // Find the reload button on the AutoControl card (pierce shadow DOM)
  const expr = `(() => {
    const mgr = document.querySelector('extensions-manager');
    if (!mgr) return { err: 'no extensions-manager' };
    const root = mgr.shadowRoot;
    const itemList = root && root.querySelector('extensions-item-list');
    if (!itemList) return { err: 'no item-list' };
    const items = itemList.shadowRoot ? itemList.shadowRoot.querySelectorAll('extensions-item') : itemList.querySelectorAll('extensions-item');
    const dump = [];
    for (const it of items) {
      const ir = it.shadowRoot;
      const name = ir && ir.querySelector('#name');
      if (name && name.textContent.includes('AutoControl')) {
        const btns = [...ir.querySelectorAll('cr-icon-button, button')].map(b => ({
          label: b.getAttribute('aria-label'), title: b.getAttribute('title'), cls: b.tagName
        }));
        dump.push({ name: name.textContent.trim(), btns });
        // Launch Chrome with --lang=en-US so the card's reload button is
        // always labeled "Reload" regardless of the OS locale.
        const btn = ir.querySelector('cr-icon-button[aria-label="Reload"]')
          || ir.querySelector('cr-icon-button[title="Reload"]');
        if (btn) { btn.click(); return { found: true, clicked: true, name: name.textContent.trim(), dump }; }
        return { found: true, clicked: false, name: name.textContent.trim(), dump };
      }
    }
    return { found: false, itemCount: items.length };
  })()`;
  const r = await send('Runtime.evaluate', { expression: expr, returnByValue: true });
  console.log('RELOAD:', JSON.stringify(r.result && r.result.result && r.result.result.value));
  ws.close();
}
main().catch(e => { console.error('FATAL:', e.message); process.exit(1); });
