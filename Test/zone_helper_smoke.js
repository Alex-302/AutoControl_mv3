// Smoke test for ac_zone_helper.exe (native messaging frame).
//
// Usage: node Test/zone_helper_smoke.js [path\to\ac_zone_helper.exe]
//        (default: the DEPLOYED helper in %LOCALAPPDATA%\AutoControl\)
// Pass an explicit path to check a FRESH BUILD before deploying it.
const { spawn } = require('child_process');
const path = require('path');
const exe = process.argv[2] || path.join(process.env.LOCALAPPDATA, 'AutoControl', 'ac_zone_helper.exe');
console.log('exe: ' + exe);
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
const msg = Buffer.from('{"__id":7}');
const frame = Buffer.alloc(4 + msg.length);
frame.writeInt32LE(msg.length, 0);
msg.copy(frame, 4);
p.stdin.write(frame);
setTimeout(() => { console.log('timeout'); p.kill(); process.exit(1); }, 5000);
