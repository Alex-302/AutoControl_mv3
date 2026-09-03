// Quick bundle-sync check: verify sw_core_bundle.js contains the committed
// source-file changes (file13/file91/file62_mv3/file10/file48).
'use strict';
const fs = require('fs');
const bnd = fs.readFileSync('mv3-build/sw_core_bundle.js', 'utf8');
const checks = {
  'file13 60s timeout (6E4)': bnd.includes('saveAs:c},6E4'),
  'file13 CB-TIMEOUT->""': bnd.includes('"CB-TIMEOUT"==e?"":e'),
  'file91 file:// strip': bnd.includes('filePath.replace(/^file:\\/\\/(localhost)?/i'),
  'file91 boot-race wait': bnd.includes('50>b&&_ul(m)'),
  'file62 hostname.in gate': bnd.includes('.in(_mo,_9n)'),
  'file62 executeScript bridge': bnd.includes('injectImmediately:true'),
  'file10 _9n const': bnd.includes('_9n="alex-302.github.io"'),
  'file48 _ja direct call': bnd.includes('(window._ja||l)(a.imprtSttgs)'),
};
let bad = 0;
for (const [k, v] of Object.entries(checks)) {
  if (!v) bad++;
  console.log((v ? 'OK  ' : 'MISS') + ' ' + k);
}
console.log(bad ? 'BUNDLE OUT OF SYNC (' + bad + ' missing)' : 'BUNDLE IN SYNC');
process.exit(bad ? 1 : 0);
