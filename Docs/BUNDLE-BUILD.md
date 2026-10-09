# Bundle build & encoding rules

> Moved from `AGENTS.md` (2026-10-04). Rules that gate changes stay in `AGENTS.md`.

## Bundle build (IMPORTANT — encoding!)
PS 5.1 `Get-Content` WITHOUT `-Encoding` reads files as ANSI (Windows-1252) →
UTF-8 symbols become mojibake. **ALWAYS use UTF8 explicitly.**

```text
Set-Location "mv3-build"
$f=@('sw_prelude.js','file67.js','file91.js','file10.js','file32.js','file17.js','file13.js','file34_mv3.js','file56.js','file57.js','file74.js','file47.js','file73.js','file70.js','file25.js','file8.js','file95.js','file15.js','file48.js','file77.js','file37.js','file3.js','file24.js','file18.js','file41.js','file45.js','file50.js','file52.js','file59.js','file89.js','file93.js','file62_mv3.js','mv3_native_shim.js','file26.js','file49.js')
$o=foreach($x in $f){";`n/* ===== $x ===== */`n"+(Get-Content -Raw -Encoding UTF8 $x)}
Set-Content sw_core_bundle.js $o -Encoding UTF8 -NoNewline
```

Sanity check (arrow must survive):

```text
$s=[System.Text.Encoding]::UTF8.GetString([IO.File]::ReadAllBytes("$PWD\sw_core_bundle.js"))
$s.Contains([char]0x2190)
```

After editing ANY file from the list above — rebuild the bundle. Files NOT in
the bundle: `sw.js`, `file42.js`, `mv3_shim.js`, `offscreen.js`,
`manifest.json` — no rebuild needed for those.

**Bundle rebuild gotcha (2026-08-07)**: `file77.js` MUST be in the $f list
(after `file48.js` — `_Yh` is a top-level `let` in file48, TDZ!). If the list
is missing it, userAPI breaks at runtime (`_Yh` never assigned — W()/K/
setClipboard dead) AND mh_test fails on the K non-destructive + binSwtch
guards (both check the bundle).


## Encoding rules (recurring pain)
- Never download files with PS 5.1 `Invoke-WebRequest -OutFile` — it corrupts
  UTF-8. Use `curl.exe -sSL -o`.
- All source files must stay UTF-8 (PS `Set-Content -Encoding UTF8` adds BOM —
  harmless for JS).
- If the console shows `â†` — the executing file is an OLD CACHED version.
  Fix: reload the EXTENSION on chrome://extensions (not just F5) or restart
  Chrome.
- UI mojibake (`â€”`/`âš`) — `main.html` MUST have `<meta charset="utf-8">`
  (fixed 2026-08-08: without it Chrome reads the page AND all its scripts as
  Windows-1252). All repo files are UTF-8, so the meta is correct. ext-mv2 has
  the same latent issue (no non-ASCII strings there).

