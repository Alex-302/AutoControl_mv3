// dat_codec.js - encode/decode the .dat payload codec (file76.dat, ac_zone_helper.dat).
//
// The extension ships its native payloads as obfuscated .dat blobs; file13.js `_7g`
// is a byte-wise reversible transform (fully reversed 2026-09-13, Docs/DECODE.md):
//
//   decode: exe[i] = (dat[len-1-i] - KEY[i%5] - i) mod 256
//   encode: dat[len-1-i] = (exe[i] + KEY[i%5] + i) mod 256        KEY = [94,14,77,49,13]
//
// The transform is size-preserving, so ANY engine of the same size can be packed
// back into file76.dat and the extension deploys it on a fresh install/repair.
// This tool is the packing/unpacking half of the update protocol (Docs/BUILD-NATIVE.md):
// build_native.ps1 uses it to refresh the bundle; mh_test verifies the result.
//
// Usage:
//   node Test/dat_codec.js encode <in.exe> <out.dat>
//   node Test/dat_codec.js decode <in.dat> <out.exe>
//   node Test/dat_codec.js verify <file.dat> [--exe <reference.exe>] [--sha256 <hex>] [--dat-md5 <hex>]
//   node Test/dat_codec.js roundtrip <in.exe>
//
// `verify` decodes in memory and prints size + sha256 + md5; every expectation
// passed on the command line must match (byte equality for --exe, the decoded
// engine's sha256 for --sha256, the .dat blob's md5 for --dat-md5). `roundtrip`
// encodes and decodes in memory and requires the result to be byte-identical to
// the input. Exit code 0 = OK, 1 = mismatch.
'use strict';
const fs = require('fs');
const crypto = require('crypto');

const KEY = [94, 14, 77, 49, 13];

function decode(dat) {
  const out = Buffer.alloc(dat.length);
  for (let i = 0; i < dat.length; i++) {
    let b = (dat[dat.length - 1 - i] - KEY[i % 5] - i) % 256;
    if (b < 0) b += 256;
    out[i] = b;
  }
  return out;
}

function encode(exe) {
  const out = Buffer.alloc(exe.length);
  for (let i = 0; i < exe.length; i++) {
    let b = (exe[i] + KEY[i % 5] + i) % 256;
    if (b < 0) b += 256;
    out[exe.length - 1 - i] = b;
  }
  return out;
}

const sha256 = (b) => crypto.createHash('sha256').update(b).digest('hex').toUpperCase();
const md5 = (b) => crypto.createHash('md5').update(b).digest('hex').toUpperCase();

function die(msg) {
  console.error('dat_codec: ' + msg);
  process.exit(1);
}

function main() {
  const [mode, file, outOrArg] = process.argv.slice(2);
  if (!mode || !file) {
    die('usage: encode|decode|verify|roundtrip (see the header comment)');
  }

  if (mode === 'encode' || mode === 'decode') {
    if (!outOrArg) die(mode + ' needs an output path');
    const src = fs.readFileSync(file);
    const res = mode === 'encode' ? encode(src) : decode(src);
    fs.writeFileSync(outOrArg, res);
    console.log(mode + ': ' + file + ' -> ' + outOrArg);
    console.log('  in  ' + src.length + ' bytes');
    console.log('  out ' + res.length + ' bytes  sha256 ' + sha256(res) + '  md5 ' + md5(res));
    return;
  }

  if (mode === 'roundtrip') {
    const exe = fs.readFileSync(file);
    const back = decode(encode(exe));
    const ok = back.equals(exe);
    console.log('roundtrip ' + file + ': ' + (ok ? 'OK (byte-identical)' : 'FAILED') +
      '  sha256 ' + sha256(back));
    process.exit(ok ? 0 : 1);
  }

  if (mode === 'verify') {
    const dat = fs.readFileSync(file);
    const exe = decode(dat);
    console.log('verify ' + file);
    console.log('  dat    ' + dat.length + ' bytes  sha256 ' + sha256(dat) + '  md5 ' + md5(dat));
    console.log('  decode ' + exe.length + ' bytes  sha256 ' + sha256(exe) + '  md5 ' + md5(exe));
    const args = process.argv.slice(4);
    let bad = 0;
    for (let i = 0; i < args.length; i += 2) {
      const opt = args[i];
      const val = args[i + 1];
      if (opt === '--exe') {
        const ref = fs.readFileSync(val);
        const ok = ref.equals(exe);
        console.log('  --exe ' + val + ': ' + (ok ? 'byte-identical' : 'MISMATCH'));
        if (!ok) bad++;
      } else if (opt === '--sha256') {
        const ok = sha256(exe) === val.toUpperCase();
        console.log('  --sha256 ' + (ok ? 'OK' : 'MISMATCH (have ' + sha256(exe) + ')'));
        if (!ok) bad++;
      } else if (opt === '--md5' || opt === '--dat-md5') {
        const ok = md5(dat) === val.toUpperCase();
        console.log('  ' + opt + ' ' + (ok ? 'OK' : 'MISMATCH (have ' + md5(dat) + ')'));
        if (!ok) bad++;
      } else {
        die('unknown option ' + opt);
      }
    }
    process.exit(bad ? 1 : 0);
  }

  die('unknown mode: ' + mode);
}

main();
