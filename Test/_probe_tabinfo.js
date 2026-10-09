// Temporary probe (2026-09-20): ask the zone helper for the tab under the
// cursor - the new "tab":1 request that feeds native type 485 (the tab under
// the mouse), which lost its tab identity on Chrome 148+.
// Usage: node Test/_probe_tabinfo.js [helper.exe]
'use strict';
const { spawn } = require('child_process');
const exe = process.argv[2] || (process.env.LOCALAPPDATA + '\\AutoControl\\ac_zone_helper.exe');
const p = spawn(exe, [], { stdio: ['pipe', 'pipe', 'inherit'] });
function send(o) {
  const b = Buffer.from(JSON.stringify(o));
  const l = Buffer.alloc(4); l.writeUInt32LE(b.length, 0);
  p.stdin.write(Buffer.concat([l, b]));
}
let buf = Buffer.alloc(0);
p.stdout.on('data', d => {
  buf = Buffer.concat([buf, d]);
  while (buf.length >= 4) {
    const n = buf.readUInt32LE(0);
    if (buf.length < 4 + n) break;
    console.log('RESP:', buf.slice(4, 4 + n).toString('utf8'));
    buf = buf.slice(4 + n);
  }
});
console.log('helper:', exe);
const t0 = Date.now();
let i = 0;
const tick = () => {
  i++;
  console.log('  +' + (Date.now() - t0) + 'ms send');
  send({ __id: i, tab: 1 });
  if (i < 8) setTimeout(tick, 400);
};
tick();
setTimeout(() => { p.kill(); process.exit(0); }, 4200);
