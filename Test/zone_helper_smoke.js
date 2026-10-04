// Smoke test for ac_zone_helper.exe (native messaging frame).
//
// Usage: node Test/zone_helper_smoke.js [path\to\ac_zone_helper.exe] [--tab]
//        (default: the DEPLOYED helper in %LOCALAPPDATA%\AutoControl\\)
// Pass an explicit path to check a FRESH BUILD before deploying it.
//
// --tab (2026-10-04) adds `"tab":1` to the request, so the answer also carries
// the tab under the cursor: `,"hWnd":N,"index":I,"title":"..."`. Used to check
// whether the helper can identify a tab in a given browser build at all — the
// first thing to verify when an action targets the wrong tab (the helper being
// blind there sends the action down the bundle's fallback path). The default
// request is unchanged, so the documented answer stays `{"__id":7,"zone":…}`.
const { spawn } = require('child_process');
const path = require('path');
const wantTab = process.argv.includes('--tab');
const exe = process.argv.slice(2).find(a => !a.startsWith('--'))
  || path.join(process.env.LOCALAPPDATA, 'AutoControl', 'ac_zone_helper.exe');
console.log('exe: ' + exe + (wantTab ? '  (tab request)' : ''));
const p = spawn(exe);
let buf = Buffer.alloc(0);
p.stdout.on('data', d => {
  buf = Buffer.concat([buf, d]);
  if (buf.length >= 4) {
    const len = buf.readInt32LE(0);
    if (buf.length >= 4 + len) {
      console.log('RESP:', buf.slice(4, 4 + len).toString());
      p.kill();
      process.exit(0);
    }
  }
});
p.on('error', e => { console.log('ERR', e.message); process.exit(1); });
const msg = Buffer.from(wantTab ? '{"__id":7,"tab":1}' : '{"__id":7}');
const frame = Buffer.alloc(4 + msg.length);
frame.writeInt32LE(msg.length, 0);
msg.copy(frame, 4);
p.stdin.write(frame);
setTimeout(() => { console.log('timeout'); p.kill(); process.exit(1); }, 5000);
