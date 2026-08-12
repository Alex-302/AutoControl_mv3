# AGENTS.md — AutoControl MV3 port (working notes)

## Language rule (code)

**ALL code and comments in `mv3-build/` MUST be in ENGLISH — no Cyrillic.**
This includes comments, log strings, and error messages in `sw.js`,
`file42.js`, `sw_prelude.js`, and the bundle sources. Existing Cyrillic
comments/logs are a known debt — translating them is tracked in `TODO.md`
(the "Translate Cyrillic" item). User-facing artifacts that live OUTSIDE the
extension code (e.g. `Test/SCRIPTING-API-TEST.js`, `Docs/TODO.md`, docs) may be in
Russian if that serves the user; code files — English only.

## Repository layout

- **`ext-mv2/`** = the ORIGINAL MV2 extension (upstream baseline,
  `manifest_version: 2`, background page `file63.html`). **DO NOT EDIT** —
  it is the reference for the port.
- **Repo root** = only `AGENTS.md`, `README.md`, `CHANGELOG.md` + the folders
  below; all other docs live in `Docs/`, test artifacts in `Test/`.
- **`Docs/`** = documentation: `TODO.md`, `FEATURES-MV3.md`, `SUMMARY.md`,
  `NATIVE_PROTOCOL.md`, `DECODE.md`, `RIGHT-CLICK-ISSUE.md`,
  `SCRIPTING-API-SUMMARY.md`, `SUMMARY-SCRIPTING-API.md`, `PUBLISH-CHECKLIST.md`.
  **`Docs/archive/`** = historical docs (closed bug reports, session handoffs):
  `✅ BUG-REPORT-runScript-duplicates.md` (bug closed 2026-08-05),
  `HANDOFF-2026-08-06-unstaged.md`.
- **`Test/`** = test artifacts: `SCRIPTING-API-TEST.js` (in-browser API
  self-test, run via RUN SCRIPT) + `AutoControl-settings-test.acs`
  (settings snapshot consumed by `mv3-build/mh_test.js`).
- **`AutoControl_native/`** = native host (manifest + exe files).
- **`mv3-build/`** = the MV3 port (SW-brain). This is where ALL work happens.
  Load this folder in Chrome as unpacked extension. Contains its own copies
  of the core `file*.js`/`res/` — independent from `ext-mv2/`.
- Other folders: `Toolbar-buttons/TOOLBAR-BUTTON-*` — auxiliary builds/assets
  (MV2/MV3 pairs: base, Duplicate, Mute, Pin, Unload). Former
  `BOOKMARKS-MV2/MV3` are now `TOOLBAR-BUTTON-Mute-MV2/MV3`, former
  `TOOLBAR-Tools-MV2/MV3` are now `TOOLBAR-BUTTON-Unload-MV2/MV3`.
- **NOTE**: the old loose MV3 shims at the root (`sw.js`, `mv3_shim.js`,
  `mv3_native_shim.js`, `file*_mv3.js`, `manifest_mv3.json`,
  `mv3_manifest.json`, `manifest_v2_backup.json`) were REMOVED during the
  "Cleanup" commit — the working copies live in `mv3-build/` (see Bundle
  build above). Do not recreate loose copies at the root.
- **`Docs/TODO.md`** — backlog of ideas/plans/known issues (Russian). Check it
  before starting work; move resolved items to AGENTS.md/Docs/FEATURES-MV3.md.

## Test harnesses (used repeatedly — keep them working)

- **`mv3-build/mh_test.js`** — Node `vm` harness that loads `sw_core_bundle.js`
  with stubbed `chrome`/DOM globals. Validates: bundle loads, `_Yk===chrome`
  (file91 storage proxy is `?file=`-gated), z-handler completeness (15 base
  types), prelude browserAction→action alias + onClicked listener count,
  `_As` scheme gate (file:// GAP §7-8), `_9w` inert loading (playAudio
  re-routed to the offscreen doc — §7-1 fixed 2026-08-09, A5/A5b checks),
  webRequest absence (saveUrl notif/copy fixed 2026-08-09 via
  declarativeNetRequest — A6 checks), icon/menu
  machinery, `_mh` compiles the user config (wheel/gesture entries), global
  visibility (free-variable `_Yh` vs `self._Yh`), XHR-shim headers smoke,
  `_Yh` callback-style smoke, and **userAPI dispatch** (must be exactly 1
  answering listener — the bundle's file48 `m()`). Output: `[PASS]`/`[FAIL]`/
  `[GAP ]` (known gap, Docs/TODO.md → Docs/FEATURES-MV3.md §7)/`[FIXED?]`; exit 1 on
  FAIL. Run: `node mv3-build/mh_test.js` (filter: `2>&1 | Select-String
  -Pattern "PASS|FAIL|GAP|SUMMARY"`).
- **Rule — keep `mh_test.js` current**: every new fix ships with a smoke test
  in `mh_test.js` (format `[PASS]`/`[FAIL]`/`[GAP ]`/`[FIXED?]`; exit 1 on
  FAIL). When a `[GAP ]` stops reproducing, update `Docs/FEATURES-MV3.md` §7 and
  `Docs/TODO.md` (the gap was fixed). The harness is path-independent (`__dirname`),
  so it keeps working if the repo is moved.
- **`Test/SCRIPTING-API-TEST.js`** — in-browser self-test of the whole ACtl API
  (23 tests), run via the RUN SCRIPT action on a regular page. Results:
  alert + console PASS/FAIL. **IMPORTANT**: the script is stored in AutoControl
  settings as `srcCode` — after ANY edit you MUST re-copy the file content
  into the RUN SCRIPT editor (extension reload does NOT update saved scripts).
  FAIL visibility (2026-08-08): every failure prints an unmissable banner
  (search the console for `[AC-API-TEST: FAIL]`) and the very last block
  `[AC-API-TEST: FAILURES]` re-lists all failed tests with name/error/timing.
  The `ACtl.on("tabLoadEnd")` safety timeout is 15s — a COLD first load of
  the opened example.org tab can take >8s on the VM (known flake,
  archive/HANDOFF-2026-08-06-unstaged.md §5; warm runs ~0.4s); on timeout the test fetches the
  tab state (status/url/title) so the log shows loading vs lost event.
  For a full green run use any normal page (strict CSP no longer matters:
  `import`/`runInPageCtx`/`include` work even on example.org since rounds
  11–13 — userScripts MAIN-world injection + relaxed world CSP). Status
  2026-08-04: **21/23 PASS, stable across runs** (round-18 fixed the storage
  wipe: scripts now survive `ACtl.var`/`pubVar`); 2026-08-06 round-4
  heartbeat-timer fix (file42 multi-instance double delivery) made it
  **22/23 stable WITHOUT extension reloads** (VM: 9/9 setClipboard PASS
  post-reload; 21/23 variants = the §7-6 runInPageCtx(func) known gap);
  2026-08-07 VM: **23/23 stable across repeated runs** (§7-6 closed by the
  round-16 single-injection proxy; the only remaining flake is the cold
  first-run `ACtl.on` timeout above). `getFile` on a local file needs the
  "Allow access to file URLs" toggle.
- **`Docs/SCRIPTING-API-SUMMARY.md`** — API reference vs Chrome 150+ capabilities
  (status table, §7 CSP rules, §9 TODOs/known limitations).

## MV3 architecture (SW-brain)

> **IMPORTANT: the MV3 port must be used ONLY as an unpacked extension**
> (chrome://extensions → Developer mode → Load unpacked). It is a dev/
> work-in-progress build: it relies on dev-mode freedoms (e.g. eval fallbacks,
> `chrome.userScripts` in unpacked contexts) and has NOT been packaged for the
> Chrome Web Store. Loading the packaged/crx version will not work as expected.

- `sw.js` — main service worker. Glue: native messaging, broadcasts, sandbox
  bridge, config refresh, keepalive, RMB fixes (v6 stripRightButtonBlocks, v7
  gesture Esc), `execUserFunc`/`userAPI` handlers.
- **Telemetry (appEvent POSTs) is OFF by default (2026-08-08, privacy — user
  request)**: NOTE — the analytics is OLD MV2 behavior (the original `_Ot`
  ALWAYS POSTed to appEvent; it could not be disabled in MV2). We did NOT add
  analytics — we added ONLY the off-switch. `_Ot` (file13.js, IN bundle →
  REBUILT 238842, arrow OK) is gated
  by `__acTel` (default false — NOTHING is sent until enabled); the flag comes
  from `advOpts.telemetry`, live via `storage.onChanged`; the callback is
  preserved when disabled (some call sites wait for it). file13.js covers BOTH
  the SW (via the bundle) AND the settings page (main.html loads it directly).
  UI: Advanced Options → checkbox «Send anonymous usage data» + a consent
  paragraph (file30.js `_Ls`). `_Ot` logs each analytics action
  (`[AC-TEL] send|skipped event=<name>`) — rare events (install/update/error/
  diagnostics), follows the AC_LOG_* gate. mh_test B31.
- **Logging is ON by default in the DEV build (2026-08-08; flip to OFF before
  publishing — see `Docs/TODO.md` "Publish on GitHub"; mh_test B28 asserts the
  `true` defaults, so the flip is a visible reminder)**, and it is
  now UI-controlled: **Options → Advanced Options** → three checkboxes (advOpts keys):
  "Log service worker" (`logSw` — silences the SW + bundle console; the patch runs
  BEFORE importScripts, so sw_prelude/bundle logs are covered), "Log page scripts"
  (`logPage` — file42, tab console) and "Log settings page" (`logSettings` — mv3_shim).
  Each runtime reads its flag from `chrome.storage.local` advOpts and applies it LIVE
  via `storage.onChanged` (no reload). `console.error` is ALWAYS kept. Startup output
  is BUFFERED (`__acLogBuf`/`__acLogApplied`) until the advOpts read resolves — with a
  flag off, no init burst prints (user VM 2026-08-08 "settings apply with a delay";
  mh_test B28 asserts the buffering).
- `sw_prelude.js` — patched globals loaded BEFORE the bundle: `__acInjectCode`
  (userScripts → MAIN world eval fallback), `chrome.tabs.executeScript` shim,
  `__acDispatchSandboxMessage`. **Never put `matchAboutBlank` in scripting
  executeScript targets** (invalid in MV3 — throws TypeError).
- `sw_core_bundle.js` — concatenation of core files (list below). Loaded via
  `importScripts` in sw.js. Contains the "brain" (file61-style trigger dispatch,
  `_if`, `_ek`, `_pg`, config chain `_lr`→`_Gf`→`_6s`).
- **SW is ALWAYS the leader**: it runs window enum + config chain. The settings
  page (`main.html`) is UI-only and must NOT run the config chain
  (`isLeader()` gate in `mv3_native_shim.js`).
- Page-side shims: `mv3_shim.js` (chrome.tabs shims, SW registration),
  `mv3_native_shim.js` (native stubs delegating to SW; `_Lk`/`_Vy` → SW).

## Bundle build (IMPORTANT — encoding!)

PS 5.1 `Get-Content` WITHOUT `-Encoding` reads files as ANSI (Windows-1252) →
UTF-8 symbols (← etc.) become mojibake (â†). **ALWAYS use UTF8 explicitly.**

```powershell
Set-Location "mv3-build"
$f=@('sw_prelude.js','file67.js','file91.js','file10.js','file32.js','file17.js','file13.js','file34_mv3.js','file56.js','file57.js','file74.js','file47.js','file73.js','file70.js','file25.js','file8.js','file95.js','file15.js','file48.js','file77.js','file37.js','file3.js','file24.js','file18.js','file41.js','file45.js','file50.js','file52.js','file59.js','file89.js','file93.js','file62_mv3.js','mv3_native_shim.js','file26.js','file49.js')
$o=foreach($x in $f){";`n/* ===== $x ===== */`n"+(Get-Content -Raw -Encoding UTF8 $x)}
Set-Content sw_core_bundle.js $o -Encoding UTF8 -NoNewline
```

Sanity check (arrow must survive):
```powershell
$s=[System.Text.Encoding]::UTF8.GetString([IO.File]::ReadAllBytes("$PWD\sw_core_bundle.js"))
$s.Contains([char]0x2190)
```

After editing ANY file from the list above — rebuild the bundle. Files NOT in
the bundle: `sw.js`, `sw_prelude.js` (prelude is concatenated IN — yes it is in
the list), `file42.js`, `mv3_shim.js`, `offscreen.js`, `manifest.json` — no
rebuild needed for those.

## Encoding rules (recurring pain)

- Never download files with PS 5.1 `Invoke-WebRequest -OutFile` — it corrupts
  UTF-8. Use `curl.exe -sSL -o`.
- All source files must stay UTF-8 (no BOM issues; PS `Set-Content -Encoding
  UTF8` adds BOM — harmless for JS).
- If console shows `â†` — the executing file is an OLD CACHED version. Fix:
  reload the EXTENSION on `chrome://extensions` (not just F5) or restart Chrome.
- **UI shows `â€”` / `âš` mojibake — `main.html` had NO `<meta charset>`**
  (2026-08-08, user report: “Telemetry helps … â€” nothing is sent”). Without
  the meta, Chrome reads the page AND all its scripts (no per-file charset)
  as Windows-1252 → every UTF-8 symbol (—, ⚠, →) in the page scripts renders
  as mojibake. FIX: `<meta charset="utf-8">` added to `mv3-build/main.html`
  (all repo files are UTF-8, so declaring utf-8 is correct). ext-mv2 has the
  same latent issue (no non-ASCII strings there). mh_test B32.

## Script execution (Run Script) — MV3 rules

- Content scripts (isolated world) have their OWN CSP without `unsafe-eval`
  since Chrome 133: `eval`/`new Function` are FORBIDDEN there ALWAYS.
- Official way to run user code strings: **`chrome.userScripts.execute`**
  (Chrome 120+, permission `userScripts` + user must enable the "Allow user
  scripts" toggle on chrome://extensions).
- `file42.js` FN: sandbox/background (file23.html) has no `chrome.runtime` →
  use `eval` (sandbox CSP allows `'unsafe-eval'`); content scripts → userScripts
  bridge via SW (`execUserFunc`); toggle-off is cached (`__acUsOk=false`).
- Background scripts run in the `file23.html` sandbox IFRAME hosted in the
  **offscreen document** (`offscreen.js`, created by the SW on demand — `_Uu`
  proxy in sw.js routes `BGScript` iframe creation there). Works even when the
  settings page is closed; alive while the SW lives (may sleep → recreated).
- `matchAboutBlank` is NOT valid in `scripting.executeScript` targets.
- `chrome.userScripts` does NOT work on extension pages / chrome:// pages.

## Known pitfalls / fixes (changelog of gotchas)

- **Save URL methods notif/copy always failed with httpError (FIXED
  2026-08-09, file49.js IN the bundle → REBUILT 240719, arrow OK)**. MV2
  spoofed the Referer header via BLOCKING webRequest
  (`onBeforeSendHeaders` + `"blocking"`) — in MV3 the
  webRequest/webRequestBlocking permissions don't exist → `_Yk.webRequest`
  is undefined in the SW → the addListener line THREW → `catch` → `H()`
  returned `{}` → `h.status` undefined → `f("httpError")` → the file was
  NEVER downloaded (not just without referer). FIX: `H()` installs a
  **declarativeNetRequest SESSION rule** (`modifyHeaders` → `set` Referer =
  `_1u(u)||_xu(u)`, `urlFilter` = the download URL) before the fetch and
  removes it in `finally` — DNR rules DO apply to `fetch()` made in the
  extension's own service worker (Chrome docs, "Interactions with service
  workers"; this is the official MV3 replacement for blocking header
  rewrite). New manifest permission
  `"declarativeNetRequestWithHostAccess"` (no install warning — `<all_urls>`
  host permissions were already present). If DNR is unavailable/rejected
  the fetch proceeds WITHOUT the referer (plain download) instead of `{}`.
  notif-UI (chrome.notifications) unchanged: optional permission requested
  via the existing `_Qk` (file78) UI flow. FOLLOW-UPS (same day):
  (1) **notif method threw** — `chrome.notifications` in the MV3 SW cannot
  load a `data:` URI iconUrl ("Unable to download all specified images." →
  the generator threw → `_rf` catch → the save never ran). FIX: `iconUrl` =
  `_Yk.runtime.getURL("AutoCtrl/logo32.png")` (real web-accessible resource);
  `create` try/catch + `update`/`clear` guarded by `void 0===k` — a
  notification failure now degrades to a silent save instead of killing the
  action. (2) **dwnlApi ignored an ABSOLUTE folder** (saved into Downloads):
  `chrome.downloads` filename in suggest is relative to the Downloads dir —
  absolute paths are ignored (same in MV2: `c.match(/^[\/\\]|:/)||(u=B(c,u))`).
  FIX in `_nu`: `dwnlApi` + absolute folder (drive `:` / leading `\`) routes
  to the native write path `I()` (folder honored, like silent/notif); relative
  or empty folder keeps using `J()` (chrome.downloads). (3) **notif shown only
  occasionally — REGRESSION from (1)**: the guard `void 0===k||(update)||(create)`
  SHORT-CIRCUITED when k was undefined — if the initial `create` failed
  (DOWNLOADING…), the final SAVED notification was NEVER created (the `||`
  chain evaluated to `true` and stopped). FIX: `(void 0===k?0:(update))||
  (k=create)` — update only when the id exists, else create a fresh
  notification (MV2 semantics). Added `[AC-NOTIF]` diagnostics (created k=,
  upd err:) for VM verification. GOTCHAS: `H`/`I`/`J` are `let`
  bindings inside file49's block scope — NOT reachable from sw.js/mh_test
  (only `var _nu` is global); `__acDnrSeq` rule-id counter lives in the same
  block; rule ids ≥1, `1E6+seq%1E6`, removed after every fetch. mh_test A6
  (bundle text: updateSessionRules + modifyHeaders + `operation:"set"` +
  `removeRuleIds:[id]` ×2 + manifest permission). 63 pass / 1 gap / 0 FAIL.
  Docs: FEATURES-MV3.md §7-2 (closed), §8 webRequest row.

- **playAudio hung the action chain forever (FIXED 2026-08-09, sw.js +
  offscreen.js only — NO bundle rebuild)**. The bundle's `_7r` (file95.js)
  lazy-loads file53.js via `_9w` → `document.head.appendChild` — a NO-OP in
  the SW (prelude shim) → the onload never fires → the generator hangs at
  `yield e=>_9w(...)` → `d(b)` never runs → the action AND the queue `_2y`
  stall. file53 also needs AudioContext/speechSynthesis (no worker APIs).
  ⚠ **`_Du` is DEEP-FROZEN**: file62_mv3.js ends with `_Oo(_Du);` (recursive
  freeze, file67.js; same line in MV2 file62.js) — `_Du.action.playAudio.value
  = ...` THROWS "Cannot assign to read only property 'value'" (user VM
  17:13:57.357: the patch failed and the ORIGINAL `_7r` ran → hang). FIX:
  playAudio actions play in the **offscreen document**, intercepted at the
  LOOKUP — file37's `_rf` reads every action through `_w(name, params)` (a
  top-level function declaration of the imported bundle → writable global,
  same mechanism as the `_Uu` patch); sw.js wraps `_w`: for `a ===
  "playAudio"` it returns a runner that completes the action immediately
  (MV2 semantics — the original also acked after enqueue) and sends
  `{cmd:"playAudio", tabGroups, params, runId}`; offscreen.js lazy-loads
  file67.js + polyfills + the REAL file53.js and calls
  `_lh(params, tabGroups, runId)`. Voice TEXT TEMPLATES (`<title>`, …) are
  pre-expanded IN THE SW (`_Tt/_up/_ai/_qd/_Yp` — bundle machinery); the
  offscreen gets the final plain string + `usesTabs:false` (plain strings
  pass file53's `_Tt/_up` untouched). Offscreen→native bridge
  `{cmd:"acPlayNative"}`: type 255 (sound-file reads) uses the bundle `_If`
  (chunked 810 reassembly is bundle-internal, unreachable from raw
  postWithCb); type 294 (system sounds) raw. Offscreen reasons now include
  `AUDIO_PLAYBACK` (Chrome 116+, fallback to DOM_SCRAPING-only on older
  Chrome). POLYFILL GOTCHAS: `_we` is a `const` — lexical global,
  `window._we` is undefined; `_ai` must return a callback RUNNER (the yield
  machinery calls yielded values as function/thenable); `_If` failure
  resolves `{content:""}` — a falsy `d` makes file53 throw INSIDE the sound
  queue and stall it forever; `_od=294` is a free variable (file56 constant)
  — ReferenceError without a polyfill. mh_test A5/A5b (incl. a runtime
  probe: `_w("playAudio") === _7r`, `Object.isFrozen(_Du.action.playAudio)`,
  `_w` writable); diagnostics: `Test/_ac_audio_smoke.js` (Chrome's
  `AudioNode.connect()` returns the destination — non-spec, MV2 relied on
  it), `Test/_ac_voice_sim.js`. 60 pass / 2 gaps / 0 FAIL.
  **VM-VERIFIED 2026-08-09**: Ctrl-M (test script + playAudio after it) —
  `[AC-AUDIO] playAudio routed... via _w wrapper` at SW start, `ACT
  action=playAudio` → `OK action=playAudio +24ms` (immediate, MV2
  semantics), no `Queue stuck`, the whole API-test chain (runScript/
  setClipboard/clpbrdPaste/runInPageCtx) completes, sound plays. Docs:
  FEATURES-MV3.md §7-1, TODO.md «playAudio hangs» (closed).

- **Gestures/hotkeys/RMB dead after using the gesture tester or combo editor —
  native STUCK IN RAW CAPTURE MODE (FIXED 2026-08-09, sw.js only, no bundle
  rebuild)**. Type 40 (`_Qr`) toggles the native's raw-capture mode (combo
  editor file68 `D()/E()`, gesture tester file30, devInput file79). While ON,
  the native streams raw type-760 events and SUPPRESSES ALL type-750 triggers
  (user VM 2026-08-09: two type-40 sends at 12:55:36.599/12:55:40.876, then an
  endless 760 flood — wheel 512/1536, RMB 2/1026, keycodes — with ZERO 750s
  for ~3 min until the SW reload at 12:58:31 spawned a fresh engine; wmic
  showed no engine processes alive). The OFF (`_0d(!1)` → type 40 false) is
  page-sent and can be lost/raced (page closed mid-edit, double-mode ON — the
  native tracks event+gesture capture SEPARATELY, each needs its own OFF —
  OFF raced with a gesture completion); the SW had NO recovery (z[760] is a
  by-design no-op; capture is engine-side). FIX in sw.js: track every type-40
  (`__acCaptureT`/`__acCaptureOn` in `case "postMsg"` + `_acNativeSend`);
  (1) **760-streak watchdog**: ≥10 raw 760s over >2.5s with no 750 and no
  capture toggle in the last 3s → re-send `postMsg(40, false)` TWICE (60ms
  apart — both modes), log `[AC-CAPTURE]`; (2) **page-gone release**: last
  settings page closes while capture armed (`broadcast()` → 0 tabs) → OFF;
  (3) any 750 resets the streak (pipeline alive = no heal). Normal mode
  produces ZERO 760s, so a streak is unambiguous; legit recording is protected
  by the toggle grace. Docs: NATIVE_PROTOCOL.md §4; mh_test B33/B35 (55 pass /
  4 gaps / 0 FAIL).
  **ROOT CAUSE DISCOVERED 2026-08-09 (second incident 13:49, way 2 repro) —
  the OFF NEVER REACHED THE NATIVE**: `postMsg()` built `{type, content:
  payload || {}}` and `false || {}` = `{}` → every `type 40 false` (UI
  `_0d(!1)` AND the watchdog) was sent as an EMPTY OBJECT → native never
  disabled capture → only SW reload (fresh engine) healed (12:55 AND 13:49
  incidents; MV2 sent raw false, no fallback — always worked). FIX:
  `content: payload == null ? {} : payload` (B35). WATCHDOG REBUILT as
  STAGED: 0→1 OFF ×2 (page-open thresholds conservative: ≥10 events, streak
  >8s, no toggle >15s — a premature OFF mid-recording broke the native's
  gesture state → type 800 NH-except on the next trail draw; page-gone fast
  path: ≥6 events/3s/3s + tabs.onRemoved release); 1→2 flood continues ~8s →
  port drop (fresh Zero+engine — capture flag lives in the engine); 2→3 →
  chrome.runtime.reload(). Any 750/toggle resets to stage 0. mh_test
  B33 updated + B35 → 55 pass / 4 gaps / 0 FAIL. Log `[AC-CAPTURE]`.
- **Spurious `[AC-WATCHDOG] Queue stuck` force-shifts dropping live queue
  items (FIXED 2026-08-09, sw.js only, no bundle rebuild)**. The action-queue
  watchdog (sw.js, 2026-08-02) detected `[AC-ACT] ... OK` by HOOKING
  `console.warn` — but the async logging patch `__acApplyLogging` (advOpts
  storage read, added 2026-08-08) REPLACES console.warn after that block →
  the hook died silently → `__acLastOkTime` froze at SW start → every 2s
  check that caught the queue momentarily non-empty (mid wheel-spin / fast
  triggers) logged `Queue stuck! ... last OK <SW-start>ms ago` and
  force-shifted a LIVE queued action (user VM 2026-08-09 13:48:06:
  "Queue stuck! 1 items, last OK 136965ms ago" = exactly SW start 13:45:50 —
  one skipped tab-switch step, perceived as "gestures broke"). FIX: hook the
  bundle's `__acLog` DIRECTLY (`t === 'OK'` is the exact completion marker;
  `__acLog` is a top-level function declaration of the imported bundle →
  classic-script global object property → reassignment from sw.js is seen by
  every bundle call site; console-warn indirection removed). mh_test B34
  (54 pass / 4 gaps / 0 FAIL). ALSO: `postMsg` is IIFE-local in sw.js — NOT
  callable from the SW console (ReferenceError); the console hook is
  `self._acNativeSend(40, true)`.
- **Scripts/triggers WIPED from settings after refresh — ROOT CAUSE = our own
  round-17 `_Qj` patch fabricating `customEntities = {}` (FIXED 2026-08-04,
  round 18)**. `_Mi()` (batched storage write used by `ACtl.var`/`pubVar`/
  switchState saves) writes the WHOLE read result back via `_bd()`. The
  round-17 guard `if (!r.customEntities) r.customEntities = {}` injected an
  empty customEntities into EVERY read (even `userVars`-only reads) → the
  write-back WIPED all saved scripts/triggers/gestures. Symptom chain:
  `ACtl.var` in API test → `storage.local changed → rebuild` → next
  `runScript` returns OK instantly (`_zs()` → "") → script gone from
  settings after refresh. "hello world" never triggered it (no `ACtl.var`).
  FIX: `_Qj` patch now only fills `binSwtch: []` INSIDE an already-present
  `customEntities` — never fabricates the key. Test A14 guards this.
- **Engine file "flashed and vanished" during install — ROOT CAUSE = our own
  `del /Q /F AutoCtrl_*.exe` (FIXED 2026-08-04, clean rewrite)**. The native
  answers type 260 as soon as cmd.exe STARTS (~7ms), NOT when the command
  finishes — so `del` ran ASYNC and deleted the freshly written engine right
  after `write()` (type 250). Symptom chain in the VM test: unpack OK → file
  check 0 → engine works ~4.8s → host exits → file check 2 forever. FIX:
  `unpackBundledEngine` no longer deletes anything (taskkill only — it kills
  processes, not files; the 250 write overwrites anyway). Also cleaned the
  flag soup (`__acEngineJustDeployed`/`__acReunpackCount`/`__acEngineRedeployCount`/
  `nukeHostTree`/`diagProcesses` all REMOVED) → simple flow: poll → unpack →
  poll on the SAME port (MV2 D(true) style) → one clean reconnect → poll →
  give up with guidance. NO del, NO nuke, NO chrome.runtime.reload, NO
  infinite retry. Verified: file76.dat decrypts to the exact reference exe
  (MD5 D9BE9A...), tests A11-A13 cover the new invariants.
- **Native install requires extension reload (FIXED 2026-08-04, auto-reconnect)**.
  After the user installs the native component from the settings page
  ("Reinstall" + "Repair"), the SW didn't reconnect automatically — the user
  had to manually reload the extension. ROOT CAUSE: the settings page's `z()`
  function (file2.js) cleaned up the install UI but never notified the SW to
  reconnect. The SW's retry loop should eventually succeed, but Chrome may
  cache "host not found" or the registry propagation may take time. FIX:
  file2.js `z()` now sends `{cmd:"reconnect"}` to the SW immediately and
  again after 2 seconds (covers late registry propagation). The SW's
  `{cmd:"reconnect"}` handler calls `connect()` which tries `connectNative()`
  immediately — no reload needed. Fallback: if the connection doesn't
  establish within ~10s, the user can reload manually (README updated).
  No bundle rebuild needed (file2.js outside bundle).

- **Toolbar icon click opened settings ALWAYS — FIXED 2026-08-08 (§7-7)** — the
  bundle file62_mv3.js registers `browserAction.onClicked` → `_ru("brwrAction",
  "trigActId")` (runs the trigger assigned to the icon click, else `_sh()` →
  settings — MV2 semantics), and sw_prelude.js aliases browserAction→action.
  A sw.js `chrome.action.onClicked.addListener(() => openOptionsPage())` on the
  SAME event opened the settings page UNCONDITIONALLY on every icon click
  (double behavior when a trigger IS assigned). NOTE: `brwrAction.trigActId`
  is a legacy storage key — NO UI writes it (verified: file62 only READS it),
  it can only arrive via old .acs imports; the bug was reproduced manually by
  setting the key in the SW console. FIX: the sw.js listener was REMOVED —
  the bundle is the single handler. mh_test B25 asserts
  `!sw.includes('chrome.action.onClicked.addListener')`. sw.js only — no bundle
  rebuild.
  **VM-VERIFIED 2026-08-08**: `chrome.storage.local.set({ brwrAction:
  { trigActId: 5 } })` (Next tab) → icon click switches to the right tab and
  settings do NOT open (pre-fix: trigger + settings both ran). Reset:
  `chrome.storage.local.remove('brwrAction')`.
- **Toolbar-button icons not set at browser start until clicked — FIXED
  2026-08-08 (two-sided)** — the MV3 toolbar-button extensions
  (`Toolbar-buttons/*MV3/bgPage.js`) kept their DEFAULT logo icons until the
  user clicked them; MV2 buttons (persistent background page) always worked.
  TWO root causes: (1) **AutoControl side**: MV2 called `_Pk()` (file47 —
  pushes `btnProps` title/icon to every configured button) in its startup
  init (file62.js); the MV3 SW config chain (`_lr→_Gf`, mv3_native_shim)
  NEVER called `_Pk` → no push from the SW at startup (only page-side live
  `_ve` on toolbarBtns edits, file30 `_Gu("toolbarBtns.*")`); (2) **button
  side**: MV3 SWs are LAZY — at browser start the button SW never ran, so the
  one-shot `getTitle → TBBtnInit` check never fired. Clicking "fixed" it
  because it woke the button SW → top-level re-ran → `TBBtnInit` →
  AutoControl `_ve` → `btnProps`. FIXES: (a) sw.js `configLoaded` local
  handler now calls `_Pk()` (guarded, try/catch) before `finishStartup()` —
  push happens on EVERY config-chain completion (startup/reconnect/force
  refresh); `_Pk` is SW-safe (sw.js-patched `_zr` fetch+createImageBitmap,
  `_Ve` OffscreenCanvas, real `chrome.runtime.sendMessage` — file91 `_Nh`
  proxy override only exists in the file-editor page context); (b) all 5 MV3
  buttons (`bgPage.js`): `chrome.runtime.onStartup`/`onInstalled` +
  `requestInit()` retry loop — sends `TBBtnInit` every 2s (max ~30 attempts)
  until AutoControl answers (btnProps → `__gotProps`) or a custom title is
  already set. mh_test B29 (sw.js `_Pk` in configLoaded + all 5 buttons have
  the retry). No bundle rebuild (sw.js outside bundle).
- **First open of a custom tab menu shows EMPTY icons — FIXED 2026-08-08
  (favicon warmup, sw.js only)** — the favicon cache patch (mv3_native_shim.js,
  in bundle) pre-fetches ONLY the tabs present at init (~1s after load, Google
  s2 → in-SW `_7o`), and if `_Yp` is not populated yet (native handshake /
  window enum still running) that pre-fetch does NOTHING → the FIRST menu
  open (`openMenu` → `_Zs(chrome://favicon/…)`) showed empty icons; the
  background load only helped the SECOND open. FIX in sw.js: (a) warm new
  tabs on `chrome.tabs.onCreated` + `onUpdated` (favIconUrl) via the patched
  `_Zs` (background Google fetch into `_7o`); (b) delayed sweeps at SW start
  (1500/4000/9000ms — the bundle's init pre-fetch may run before `_Yp`
  exists); (c) re-sweep after every config-chain completion (`configLoaded` —
  fresh `_Yp` from the enum). `_7o`/`_Yp` are top-level let/var of the bundle
  — shared lexical env, accessible as free variables from sw.js (same as
  `_Yh`); the patched `_Zs` is a global function. mh_test B30. No bundle
  rebuild.
  **Follow-up (same day, key alignment)**: user VM log 23:00 showed the fix
  did NOT help — first menu open still partial, second ~all. Root cause:
  CACHE-KEY MISMATCH — the menu asks `_Zs("chrome://favicon/<url>")` (file26
  `_ig`) but the warmup cached under the RAW `tab.favIconUrl` (https URL).
  `__acFavWarm` now warms BOTH keys: raw favIconUrl + constructed
  `"chrome://favicon/" + (tab.url||tab.pendingUrl)` (scheme-gated). The
  onUpdated hook also passes `url` when present. mh_test B30 extended.
- **Chrome 148+: mouseOver «Browser tab» (region 12) never fires — BROKEN, no
  extension-side fix (2026-08-02, workaround ROLLED BACK)**. The native
  component's UIA hit-test can no longer find tabs (a11y tree changed);
  regions 4 (Title area) and 21 (Omnibox) still work. Verified: MV2 and MV3
  are BOTH affected → native/Chrome issue, not the MV3 port. UI: the region
  option is marked "Browser tab ⚠ (broken in Chrome 148+)" in file68.js
  (dropdown) and the help text in file80.js points to Title area. History of
  the failed SW workaround (TAB-GATE, sw.js only, now REMOVED): r1 gate
  disabled (`_trigActList` IIFE-local); r2 `_No`(485) returns `{}` even over
  tabs; r3/r4 `_Ua`(330) replies PIXELS and `win` = monitor WORK AREA not the
  window → fragile DPI/scale math that broke at other DPI/taskbar layouts
  (user: "fragile scheme"); r5 replaced the region with 4 — fires over the
  whole strip row (= known Title-area behavior, user rejected). Conclusion:
  per-tab hover cannot be emulated reliably; use region 4 (Title area) for
  top-row triggers. UI: the region dropdown (file68.js) marks BROKEN:
  "Browser tab", "Tab's close button", "Tab's speaker icon", "New tab
  button" and "Any menu item" — all with "⚠ (broken in Chrome 148+)"; the
  help texts in file80.js point to Omnibox/Web page as the working
  alternatives. NOTE: region 4 (Title area) itself still fires (native
  geometry) and its illustration matches the behavior — it is NOT marked
  broken (fires over the whole top row incl. new-tab button/controls, which
  matches the doc picture).
- **mv3_native_shim.js is an IIFE — NOT everything is global!** Exported to
  window: `_Lk _Vy _0d _Uj _ha _Yi _cu _Sw _Xg _2y z`. NOT exported (IIFE-local,
  invisible to sw.js): `_trigActList`, `pendingCallbacks`, `chunkedDataStore`,
  `gestureState`, `configChainStarted`, `findTriggerByKey`, `findTriggerByGesture`,
  `executeTrigger`. Round-1 TAB-GATE bug: reading `_trigActList` from sw.js
  threw ReferenceError → gate silently inactive. Always check exports before
  touching shim state from sw.js.
- **Scripts saved but UI list empty** — page `_if` is populated ONLY by the SW
  config chain (leader) or by `onChanged`. Fix in `mv3_native_shim.js`
  "Not leader" branch: read `storage.local.customEntities` → `_if` → `_nk()`.
  Log: `Page _if populated from storage`.
- **`_if` raw-assign trap** — `storage.local.customEntities` is a pair-array
  `[[id,value],...]`, but the UI (`_Xy`/`_gh`) expects the Map-like object
  (`{}.add`). NEVER assign `_if = r.customEntities` directly (list renders
  empty). Use `_6s({}, cb)` (does `_Qj` conversion, sets `_5g/_Ek/_rr`,
  sends only harmless type 200, NOT type 60) — see "Not leader" branch.
- **Changes on the settings page don't reach the SW until restart** —
  `_Gu`/`_B` subscriptions (file17.js) fire inside `_Mi` (not via
  `storage.onChanged`), and file2.js (which registers them) is page-only,
  NOT in the bundle. Only trigger/gesture edits send type 60 (`_no`).
  Script/action edits never did. Fix: SW listens to `storage.onChanged`
  (block "SW: LIVE CONFIG REBUILD" in mv3_native_shim.js, guarded by
  `typeof importScripts === 'function'`) → debounce 400 ms → `_Gf({}, cb)`
  (= `_6s→_zj→_no`: `_if`/`_ek`/`_pg`/`_su` + type 60 to native).
  Log: `storage.local changed → rebuilding in-SW config (_Gf)`.
- **Scripts lost after reload** — `_Sp` (file17.js) import does
  `storage.local.clear()` + write file contents. Fixed: merge old
  `customEntities` that are missing from the imported file.
- **Storage vs file**: settings file (.acs/.dat) is written by `_qj`
  (file73.js) on storage change (only when localSync `_uy` is on). File check
  (type 10) returning 0 = no file → no import.
- **mv3_shim double-map**: SW already returns mapped results; do NOT
  `result.map(r => r.result)` again (crashes on null items).
- **Action timing/duplicates diagnostics** — `[AC-ACT]` logs in file37.js
  (`_6y`/`_rf`): unique run ID per trigger, `TRIG`/`QUEUE`/`ACT run#N`/`OK`
  with `+Nms` from run start. `QUEUE ... busy → queued` = second trigger
  arrived while the action queue (`_2y`) was busy.
- **F()-path diagnostics (2026-08-06)** — setClipboard/runInPageCtx-file
  failures (`_fr is not iterable`): file42 logs `[AC-F42] listener ret=…`
  (true/undefined — does the listener answer async for funcCode messages),
  `[AC-F42] funcCode THREW: …` (an exception inside FN() closes the
  sendMessage channel → n() gets undefined → retry → dedup-hit cascade) +
  existing `funcCode val`/`dedup-hit`/`relay resp`/`api rcvd`. file48 n()
  logs `[AC-DLV-F] why=…`: reason the attempt resolved — `cb-ok` (real
  callback), `lasterr:…` (callback with chrome.runtime.lastError),
  `timeout` (4s fallback), `throw:…` (sendMessage threw), `cb-undef`/
  `cb-val`/`cb-null` (legacy, no why). Read `why=` + `h=` together:
  `lasterr:Could not establish connection` = no listener;
  `cb-ok` + `h=UNDEF` = listener answered sync (returned non-true);
  `timeout` = page busy/slow. Both edits: file42 outside bundle, file48 IN
  bundle → bundle rebuilt (size 234645, arrow check OK).
- **runScript hangs (FIXED 2026-08-02, round 4)** — the `execUserFunc`
  wrapper's promise in file42 was NEVER resolved: `respond()` called
  `execUserFuncDone` but never `D()`/`A()`. The action hung ~20s (until
  Chrome closed the channel). Fix: `try{h&&h.error?A(h.error):D(h&&h.result)}`
  in `respond()` (mv3-build/file42.js, line ~40). SYMPTOM of regression:
  script runs (page console) but no `OK action=runScript` in SW console.
- **`ACtl is not defined` in user scripts (FIXED 2026-08-02)** — original MV2
  exposed `ACtl` to scripts via direct-eval closure capture (`new
  Function("ACtl",...)` + `eval('('+funcCode+')')`). MV3 broke it in TWO
  paths: (1) SW `execUserFunc` USER_SCRIPT world ran `(${code}).apply(null,
  [__acActl].concat(args))` — proxy passed as `arguments[0]`, but scripts
  reference the FREE GLOBAL `ACtl` → ReferenceError; (2) file42 `B` called
  `FN(funcCode)` whose eval arrow had no `ACtl` param → sandbox path also
  broken. Fixes: sw.js jsCode adds `var ACtl = __acActl;` inside the IIFE
  (closure over evaluated function literal) and applies with args ONLY
  (original semantics); file42.js `FN` takes 2nd param `ACtl`, `B` passes it
  (`FN(funcCode,ACtl)`). NO bundle rebuild needed (neither file in bundle).
  NOTE: `ACtl.on(evt, callbackFn)` with a real function arg still fails in
  the USER_SCRIPT world (postMessage DataCloneError — functions aren't
  stringified there); handler-less `on(evt, tabId)` and all value-arg APIs
  (saveURL/captureTab/openURL/setTabState/execAction) work.
- **`userAPI handler not loaded` (FIXED 2026-08-02, round 2)** — after the
  ACtl fix the script ran but `ACtl.saveURL` failed with this error. TWO
  root causes in sw.js's userAPI handler: (1) `_Yh` is a top-level **LET**
  declared in file48 (`let _gr=...,_Ue=...,_Yh;`) and ASSIGNED by file77
  (`{_Yh=_we(...)}`) — a GLOBAL **LEXICAL** binding, NOT a property of
  `self`/globalThis → `typeof self._Yh` was ALWAYS undefined. Fix: reference
  the free variable `_Yh` (importScripts shares the SW's global lexical env;
  verified in mh_test.js: `_Yh=function self._Yh=undefined`). (2) `_Yh`
  returns a **CALLBACK-style runner** (file67 `_us=(d,e,h)=>{...; return
  (f,g)=>{d.onSuccess=f;d.onError=g;c(d)}}`), NOT a Promise —
  `Promise.resolve(_Yh(...))` passed the callback FUNCTION through as the
  result. Fix: call `_Yh(msg, tab)(onOk, onErr)` like the original page
  handler (file48: `_Yh(a,c)((...p)=>d(...p))`). Both fixes in sw.js only —
  no bundle rebuild.
- **`ACtl.saveURL: a.getResponseHeader is not a function` (FIXED 2026-08-02,
  round 3)** — the prelude's XMLHttpRequest shim (fetch-backed) lacked
  `getResponseHeader`/`responseURL`; file70 `_Su()` (filename from
  Content-Disposition/Content-Type) and file77 `O()`/`saveURL`
  (`n.getResponseHeader("content-type")`, `a.responseURL`) crashed on them.
  Fix: shim now stores the fetch Response (`this._resp`) + final URL
  (`this.responseURL = r.url || this._url`) and exposes
  `getResponseHeader(name)` (delegates to `_resp.headers.get` — case-
  insensitive) + `getAllResponseHeaders()`. **sw_prelude.js IS in the
  bundle → BUNDLE REBUILT** (232060 chars, arrow check OK, verified in
  mh_test.js XHR-shim smoke test). Note: `Extension context invalidated`
  errors in the page console are just stale file42 instances after an
  extension reload — reload the page to clear them.
- **`_us`/`_we`/`_cg` are CALLBACK-style generators** (file67) — they return
  `(onSuccess, onError)` runners, NOT Promises. `Promise.resolve(fn(...))`
  passes the function through. Any sw.js handler calling into bundle code
  must use the callback form (see userAPI handler above).
- **`(intermediate value) is not iterable` in user scripts (FIXED 2026-08-02,
  round 4 — the SHARED API layer)** — file77 `W()` returns **z-bundles**
  `{funcCode: "<source>", args: [...]}` for many ACtl APIs (captureTab →
  `z(J,[map])`, on → `z(fn,[FUNC])`, getTabInfo, pubVar, ...), and `_Yh`
  passes them through unwrapped. The original file42 evaluated them in the
  userAPI callback (`l = h.funcCode ? FN(h.funcCode)(...h.args) : h.result`
  + iterator loop); the MV3 `acUserApi` relay (USER_SCRIPT world) forwarded
  only `result`/`error` → the script got `undefined`. THREE fixes:
  (1) **file42.js acUserApi listener** now evaluates z-bundles with the
  iterator loop, awaits nested FN promises (postMessage cannot clone a
  Promise), and runs under a UNIQUE trigInstId (`~api` suffix) so nested
  execUserFunc calls are NOT deduped against the in-flight parent run;
  (2) **sw.js USER_SCRIPT proxy**: `on` without a callback now registers a
  `window[g]` handler ({FUNC: g} name, like file42 E()) — returns the event
  promise for `'promise'` and resolves it on the event; real callback
  functions work too (no more DataCloneError); `saveFile`/`setClipboard`
  name-ify their data arg on window (file77 K reads `window[e]` by NAME,
  like C() proxy); other functions stringified to {FUNC: source};
  (3) **file42.js event relay**: `u()`'s event branch postMessages
  `acEvt` (and `del` for cleanup) so events reach USER_SCRIPT-world
  handlers; sw.js jsCode has a guarded (`window.__acEvtBridge`) acEvt
  listener. NO bundle rebuild (sw.js, file42.js outside bundle).
- **`_Ii` = `(...a)=>[].concat(...a)`** — just array flattening. Object args
  to `F()`/`K` (file77 W: setClipboard/saveFile serialization) are passed as
  WINDOW NAMES — `K` does `let g=window[e]`.
- **`Object.defineProperty called on non-object` (FIXED 2026-08-02, round 5 —
  FN arg-drop + z-bundle result transport)** — the "Take a shot" example
  (`captureTab` → `setClipboard` → `openURL` → `on` → `setTabState` →
  `execAction`) exposed FOUR shared-layer bugs:
  (1) **FN wrapper dropped the first arg**: `args=Array.prototype.slice.call(
  arguments,1)` → nested `FN(JSource)(c)` sent NO args → USER_SCRIPT world
  ran `J.apply(null,[])` → `e=undefined` → `Object.defineProperty called on
  non-object`. Fix: `slice.call(arguments)`.
  (2) **u() funcCode branch didn't await FN**: `c=FN(...)(...)` returned a
  Promise (SW execUserFunc path) but the branch only handled function
  results → `sendResponse(Promise)` (uncloneable). Fix: `c&&"function"==
  typeof c.then && return c.then(e, g=>e({error:g})),!0` — pass the VALUE
  (F()/K path, e.g. setClipboard, needs the bare value, NOT {result:...}).
  (3) **jsCode __post couldn't clone z-bundle results**: J attaches a
  GENERATOR FUNCTION as Symbol.iterator → postMessage DataCloneError. Fix:
  convert iterables to plain `[key,value]` arrays in `__post` (destructuring
  `let [[, dataUri]] = await ...` works identically on arrays).
  (4) **ACtl.on result is a pending event Promise** — uncloneable. Fix:
  handled LOCALLY in the USER_SCRIPT proxy: register `window[g]` +
  fire-and-forget acUserApi (`local:1` → file42 relay skips the z-bundle
  eval) and `return pr` directly; events arrive via file42's acEvt relay.
  NO bundle rebuild (sw.js, file42.js outside bundle).
- **`_Yh` returns the z-bundle UNWRAPPED** (`h instanceof z ? h : {result:h}`)
  — file42's relay must evaluate it (`FN(h.funcCode)(...h.args)` + iterator
  loop). Results containing FUNCTIONS (J's generator) can never cross
  postMessage — the __post array-conversion is the only way.
- **`ACtl.setClipboard: (intermediate value) is not iterable` (FIXED
  2026-08-02, round 6 — dedup key collision)** — nested FN calls (F()→K
  serialization in setClipboard/saveFile, and z-bundle evals) run through
  file42 with the PARENT `x.__cur` → their execUserFunc dedup key
  (`tabId:scriptId:trigInstId`) EQUALS the still-in-flight parent run → SW
  answers `dedup` → the API gets `undefined` → `[b,c,f={}] = undefined`.
  Fix (file42.js only): BOTH nested paths (u() funcCode branch AND the
  acUserApi relay) now override `x.__cur.trigInstId` with a UNIQUE per-call
  suffix (`~` + random — NOT a static `~api`, which would collide within
  the 15s dedup LRU TTL), restoring `x.__cur` in `finally`. The parent's
  key stays intact → real burst duplicates are still suppressed.
- **DOUBLE userAPI execution (FIXED 2026-08-02, round 7 — the REAL reason
  for "duplicate" API calls)** — the bundle's file48 registers
  `_Yk.runtime.onMessage.addListener` INSIDE the bundle; in the SW
  (importScripts) that is a LIVE listener alongside any sw.js handler.
  Chrome dispatches every message to ALL listeners → ACtl.* (userAPI) was
  handled TWICE: the sw.js handler AND the bundle file48 `m()` — both call
  `_Yh` → `W`. For setClipboard both ran `F→K`; the first K did
  `delete window[e]`, the second got `undefined` → clipboard overwritten
  with the text "undefined" (snipboard.io: "E007 image data was not found
  on your clipboard"). FIX: sw.js no longer handles `userAPI` (`return
  false`) — the bundle m() is the single handler (it already calls `_Yh`
  callback-style with the free-variable lexical binding; VERIFIED in
  mh_test.js: `userAPI dispatch: 1 answered of 1 listeners`). All file42
  shared-layer fixes (z-bundle eval, funcCode await, unique ~keys) remain
  needed — they are in the file42 relay used by BOTH paths. NO bundle
  rebuild (sw.js, file42.js outside bundle).
- **`ACtl.on` in the script's chain is fine** — the SW log shows the whole
  Take-a-shot chain working: captureTab → z-bundle (dataUri present) →
  setClipboard → true (type 286) → openURL → [tabId] → on → z-bundle →
  setTabState (activateTabs) → execAction → clpbrdPaste (type 285 cmd:2).
- **`runInPageCtx` ReferenceError (FIXED 2026-08-02, round 8)** — `W()`'s
  runInPageCtx case routes the call through `F()` → execUserFunc → lands in
  the USER_SCRIPT world, but `window.runInPageCtx` was only defined in
  file42 (isolated world — SEPARATE window object). Also the file branch
  references `FN` inside its callback — also missing there. Fix in sw.js
  jsCode: `window.FN = a => eval('('+a+')')` (eval IS allowed in user
  script worlds — not subject to page CSP) + `window.runInPageCtx` with
  file42 semantics (script element in MAIN world — DOM shared; `__acRipc`
  cache on window for the again flag; W()'s FUNC branch does the
  postMessage roundtrip which crosses worlds like acEvt). Limitation: MAIN
  world injection is blocked by strict page CSP (same as MV2). NO bundle
  rebuild (sw.js outside bundle).
- **`ACtl.switchState: _if.binSwtch is not iterable` (FIXED 2026-08-02,
  round 10)** — `_if` = customEntities (set by `_6s`); with no binary
  switches created, `binSwtch` key is absent → W()'s `for..of _if.binSwtch`
  throws. Fix in sw.js: patch `_Qj` (file17, single storage-load choke
  point) to guarantee `customEntities.binSwtch = []` default.
- **`runInPageCtx` DataCloneError / "Cannot read properties of undefined
  (reading 'error')" (FIXED 2026-08-02, round 10)** — TWO issues:
  (1) our round-8 `window.runInPageCtx` returned a bare no-op cb, but the
  original file42 returns a CALLBACK RUNNER `(c)=>{...}` (W()'s file
  branch does `F(k.id, loc, m=>runInPageCtx(...))` → runner invoked
  callback-style); (2) W()'s FUNC branch returns function `q` (cb-style
  `q(onDone)`) — a function cannot cross postMessage (DataCloneError).
  Fix in sw.js jsCode: runInPageCtx now returns `function(c){...}` (runner
  semantics incl. `c({})` after inline scripts) and execUserFunc does
  `if (typeof p === "function") { p(__post); return; }` before
  Promise.resolve. Page CSP still blocks inline/data: MAIN-world scripts
  on strict-CSP sites (example.org) — same as MV2; works on non-CSP pages.
  NO bundle rebuild (sw.js outside bundle).
- **`runInFrames` subframes — KNOWN LIMITATION (TODO, 2026-08-02)** — SW
  executes `userScripts.execute` only with `target:{tabId, frameIds:[0]}`, so
  `ACtl.runInFrames` runs func ONLY in the top frame; subframes are silently
  skipped (MV2 ran all frames via sendMessage allFrames). Plan: use
  `userScripts.execute({target:{tabId, allFrames:true}})` (allFrames and
  frameIds are mutually exclusive) and aggregate results by frameId from
  InjectionResult (Chrome 135+); apply frameFilter (depth/href/...) INSIDE
  the injected code via location.*. See Docs/SCRIPTING-API-SUMMARY.md §9.
- **`runInPageCtx` on strict-CSP sites — POSSIBLE FIX (TODO, 2026-08-02)** —
  currently injects a `<script>` element into MAIN world → blocked by page
  CSP as inline. Better: inject via `userScripts.execute({world:"MAIN",
  js:[{code: fnSrc}]})` — Chrome runs API-injected code directly (NOT as an
  inline script), so the inline CSP check does NOT apply (this is how
  TamperMonkey works). Remaining limit: `eval` inside the user function in
  MAIN world is still cut by page CSP without unsafe-eval (same as MV2).
  Needs a bridge: USER_SCRIPT world → postMessage → file42 → SW →
  userScripts.execute(MAIN) → result back. See Docs/SCRIPTING-API-SUMMARY.md §9.
- **`runInPageCtx` now injects via chrome.userScripts (FIXED 2026-08-02,
  round 11 — TamperMonkey-style)** — jsCode `window.runInPageCtx` no longer
  creates `<script>` elements (blocked by strict page CSP as inline). It
  bridges: USER_SCRIPT world → `postMessage({type:"acMainWorld"})` → file42
  (new listener) → `runtime.sendMessage({type:"execMainWorld"})` → SW handler
  → `__acInjectCode(tabId, code, {}, cb)` (sw_prelude.js) → `userScripts.execute`
  with `world:"MAIN"` — API-injected code runs directly, bypassing the page's
  inline-CSP check. Code is wrapped `try{...}catch(e){({__acError:...})}` so
  thrown errors become results (userScripts.execute rejects otherwise).
  File/URL form: `fetch` the text in the USER_SCRIPT world (exempt from page
  CSP), inject as code; fallback to `<script src>` on fetch failure.
  Result flows back: SW → file42 → `acMainWorldRes` postMessage → runner cb.
  Remaining limit: `eval` INSIDE the user function in MAIN world is still cut
  by page CSP without unsafe-eval (same as MV2). NO bundle rebuild (sw.js,
  file42.js outside bundle).
- **`runInPageCtx(func): window[u.data.funcName] is not a function` (FIXED
  2026-08-02, round 12)** — W()'s FUNC branch defines a MAIN-world global via
  `var m = <fn>`, but `userScripts.execute` wraps injected code in a function
  scope → `var` never reaches window → the funcExecLstnr handler fails. Fix in
  jsCode runInPageCtx: for `{code}`-form promote top-level `var X =` →
  `window.X =` before injection.
- **`import` blob: blocked even without page CSP (FIXED 2026-08-02, round
  12)** — the USER_SCRIPT world's DEFAULT CSP is the ISOLATED-world CSP (no
  `blob:`), so dynamic import(blobUrl) was rejected everywhere. Fix in sw.js:
  `userScripts.configureWorld({csp: "script-src 'self' 'wasm-unsafe-eval'
  blob: data:; object-src 'self'"})` once before the first execute
  (`__acEnsureWorld()`). Verify with the import test.
- **`ACtl.import` DataCloneError: [object Module] could not be cloned
  (FIXED 2026-08-02, round 13)** — after round 12 the module LOADED, but a
  module namespace object is NOT structured-cloneable → postMessage threw.
  Fix in sw.js jsCode: `__post` detects `[object Module]` results (import /
  getFile('module')), stashes them on `window[__acmod_*]`, sends a marker
  `{__acModule: name}` instead; the acUserApiRes handler in the proxy swaps
  the marker back to the real object (same USER_SCRIPT world). The file42
  relay only ever sees the cloneable marker. NO bundle rebuild (sw.js only).
- **`runInPageCtx(func): window[u.data.funcName] is not a function` — RACE
  (FIXED 2026-08-02, round 15)** — W()'s FUNC branch defines `window.m` via
  ASYNC `userScripts.execute`, then IMMEDIATELY posts `{funcName:m}` — the
  message can reach the MAIN-world funcExecLstnr listener BEFORE window.m
  exists (MV2 was race-free because `<script>` executes synchronously on
  appendChild). Round-14 tried a per-injection buffer but FAILED: every
  execUserFunc injection re-ran jsCode and re-wrapped `window.postMessage`
  with a FRESH (null) pending state → the LAST wrapper never buffered
  (seen as a chain of 10+ postMessage wrappers). Round-15 fixes:
  (1) buffer state lives on `window.__acPendingVar`/`__acVarQueue` with a
  single guarded wrapper (`window.__acPostWrapped`); (2) SW serializes
  MAIN-world injections via `self.__acMainWorldChain` promise chain so the
  funcExecLstnr listener (injected first) exists BEFORE 'var m = fn'
  completes and the buffered {funcName} is flushed. NO bundle rebuild
  (sw.js only).
- **`runInPageCtx(func)` return value — FIXED by single-injection proxy
  (2026-08-06, round 16; sw.js only, no bundle rebuild)**. The root cause
  was MV3 world isolation: W()'s FUNC mechanism (listener A + `var m = fn`
  B + read `window[m]` by name) needs a SHARED global between injections.
  In MV2 both were `<script>` in one MAIN world (synchronous) — worked. In
  MV3 each `userScripts.execute` is a separate evaluation context (different
  VMs in DevTools), code is function-wrapped, execution async → `window[m]`
  in A never sees m from B; buffering/ordering cannot fix it (rounds 12-15
  tried: `var`→`window.` promotion + message buffering — still FAIL
  "window[u.data.funcName] is not a function"). Tampermonkey avoids this via
  `unsafeWindow` (direct synchronous reference — no injection bridge). FIX:
  in jsCode (sw.js), (a) `runInPageCtx("funcExecLstnr", fn)` is NO-OPED
  (`g === "funcExecLstnr"` → `c({})` — otherwise it answers first with the
  wrong error and wins the channel race); (b) the `{code:'var m=<fn>'}`
  injection is replaced by ONE self-contained proxy (`/*AC-MV3-PROXY*/`)
  that sets `window.m`, installs its OWN listener for the
  `{funcName:m,args}` message and answers via `{response, funcName}` from
  the same context (closure over F — no cross-injection lookup). Ends with
  `void 0` so the completion value is undefined (a function completion
  value would reject userScripts.execute's result serialization). The
  buffered `{funcName}` post (round 15 mechanism, 8s safety) is flushed
  when the injection completes → proxy answers → W()'s callback runner
  (listener B) resolves. Bundle untouched (file77/file42 unchanged).
  mh_test B13 checks the proxy + no-op. **VM 21:52: `[AC-API-TEST:
  ACtl.runInPageCtx] PASS 2` (+14ms, 0.95s run, 22/23 — the only FAIL was
  getTabIds on a non-active tab, environmental). §7-6 CLOSED.**
  **FULL-REINSTALL VERIFICATION (VM 22:01): after removing the extension
  + native and reinstalling — auto engine deploy (host not found → retries
  → file check 2 → unpack file76.dat → ready after 1 poll) worked with NO
  manual steps; an OLD unrefreshed tab (dead pre-reinstall file42,
  "Extension context invalidated" noise) self-healed via n() fallback
  (guard expired after 20s staleness) → 23/23, 0.92s; a REFRESHED tab
  (manifest content script) → 23/23, 0.82s. Both runInPageCtx PASS 2.**
- **file42 double-injection**: every `scripting.executeScript({files:["file42.js"]})`
  creates a NEW isolated VM/world — `window.FN||` does NOT dedupe across
  injections (window is not shared between isolated contexts). Avoid
  re-injecting file42; n() injects only when sendMessage gets no listener
  (4000ms timeout). Reloading the tab clears old file42 instances.
- **file42 re-injection guard (2026-08-06)**: top of file42.js guards on the
  SHARED `document` (`if(!document.__acF42||2E4<Date.now()-(document.__acF42T||0))`)
  — DOM is shared across isolated worlds, so a re-injection is a no-op while
  the original instance lives. Top-level `return` is ILLEGAL there (classic
  script) — use the if-wrapper. The `__acF42T` heartbeat is refreshed BOTH on
  message processing (u()/acUserApi/acMainWorld) AND by a 10s `setInterval`
  (`document.__acF42I`), so a LIVE but idle instance never looks dead to the
  guard — the interval makes duplicate injection impossible while the holder
  lives. A DEAD holder (extension reload without tab reload → "Extension
  context invalidated" → timers stop) still expires after 20s staleness → a
  fresh injection takes over. **Why this matters (2026-08-06, round 4)**: file42
  used to be injected ONLY by n() on "no listener" (content_scripts was empty
  in both MV2 and MV3 manifests — verified) — until round 8 (2026-08-06)
  declared it in the MV3 manifest as a static content script. Without the
  timer, an idle >20s instance was seen as dead → new injection →
  TWO live listeners → Chrome delivers every tabs.sendMessage to BOTH →
  `funcCode dedup-hit` + the first (null) response wins → setClipboard
  `_fr is not iterable` WITHOUT extension reload (with reload it always
  passed). Do NOT remove the heartbeat/timer — the plain flag alone would
  deadlock delivery until the tab reloads.
- **`x.__cur` context chain is LOAD-BEARING — round-3 restore REVERTED
  (2026-08-06, round 5; file42.js only)**. The scriptId branch (RUN SCRIPT)
  sets `x.__cur={scriptId,tabId,targetTabs,trigInstId}` and MUST NOT restore
  it afterwards: every later funcCode message and the acUserApi relay read
  scriptId/trigInstId from it, and two SW-side consumers depend on a
  NON-EMPTY trigInstId chain: (a) the execUserFunc dedup key
  `tabId:scriptId:trigInstId` — with an empty chain every F() call gets key
  `tabId::` → `__acExecCompleted` (15s TTL) BLOCKs all F() calls after the
  first (getTabInfo) → captureTab/setClipboard/getFile/import/runInPageCtx
  cascade `_fr is not iterable`/`[null]`/`undefined` (VM 14:01, 15/23); (b)
  file67 W()'s on-case registration `_lf(_Vj,l,{},m,{},k.id,h,[])` — with
  h=undefined the trigInstId path level is SKIPPED (`Number.isNaN(undefined)`)
  and `.push(c)` hits an object → TypeError inside W() → the tabLoadEnd
  registration never happens → `ACtl.on` 8s timeout. The round-3
  "context-leak" diagnosis (13:33 logs: runInTab ~suffix in setClipboard's
  cur-in) was a red herring — that cascade came from DOUBLE DELIVERY (two
  live file42 instances, round-4 heartbeat fix). funcCode branch still
  restores `x.__cur` in `finally` (FN captures ctx synchronously); its
  empty-chain fallback now builds `{scriptId:a.scriptId,tabId:a.tabId,
  trigInstId:a.trigInstId+"~"+random}` from the message instead of `{}`.
  VM proof: 13:47-13:51 runs (pre-round-3 file42, chain intact) = 9/9
  setClipboard PASS; 14:01 runs (round-3 restore) = 15/23. mh_test: 29 pass.
- **Stale file42 instances + destructive K + null-retry (2026-08-06,
  round 6)** — content-script contexts (file42) die ONLY on EXTENSION
  reload or TAB reload; an SW restart ("SW started" in the SW console)
  does NOT invalidate them. Without reload, stale pre-guard instances
  stay alive → every tabs.sendMessage is processed by ALL of them. For
  setClipboard/saveFile, K ran in the SHARED user script world and did
  `let g=window[e]; delete window[e]` (destructive) → the 2nd+ K read
  undefined → garbage responses won the channel race → `F-> null` →
  `_fr is not iterable`; n() accepted null as valid (`void 0!==h`).
  Fixes: (a) K is NON-DESTRUCTIVE (no delete — every K returns the same
  array; idempotent race); (b) file42 __acFnDedup stores a VALUE-promise
  (`new Promise(_dV=>c.then(v=>{e(v);_dV(v)},g=>{e({error:g});_dV({error:g})}))`)
  so dedup-hit answers the VALUE, not sendResponse's return (true/false);
  (c) n() `null!=h` — null retried once with the SAME message → everyone
  dedup-hits onto the value-promise → converges. Bundle REBUILT (236218,
  arrow OK). mh_test: 32 pass / 4 gaps / 0 FAIL.
- **RUN SCRIPT acks IMMEDIATELY (2026-08-06, round 7; file42.js only)** —
  the scriptId branch used to answer the RUN SCRIPT message only after the
  WHOLE script's Promise resolved → any script longer than n()'s 4000ms
  fallback hung the action queue → WATCHDOG force-shift → subsequent
  RUN SCRIPTs queued/failed (VM 15:03: test took 12.5s because tabLoadEnd
  was slow on a fresh tab → runScript timeout → "Queue stuck! 2 items" →
  second run never finished). Fix: fire-and-forget —
  `return c.then(logDone, logErr), e({result:!0}), !0` — start the script,
  ack {result:true} immediately (safe: the action result is unused for
  runScript, t=true in _A ignores errors), log completion/errors. mh_test:
  33 pass / 4 gaps / 0 FAIL.
- **noWait (2026-08-06, round 7b; file48 IN bundle → REBUILT 236545)** —
  round-7's fire-and-forget hit ALL scriptId messages, including NESTED
  _A calls (runInTab/runInFrames go through the same scriptId branch via
  _xj{scriptId,...}) → they returned [true] instead of the real result
  (VM 15:17: "ACtl.runInTab true"). Fix: _A adds `noWait:!0===t` — t===true
  ONLY for the top-level RUN SCRIPT (_To → _gr → _Ue(...,!0)); runInTab/
  runInFrames pass t=trigInstId or !1/undefined → noWait=false. file42
  scriptId branch: `if(c instanceof Promise){if(a.noWait){...;return
  e({result:!0}),!0} return c.then(b=>{...e({result:b})},g=>{...e({error:g})}),!0}`
  — top-level acks immediately, nested calls await the REAL result.
  mh_test: 34 pass / 4 gaps / 0 FAIL.
- **14/34 trigger pair**: native sends TWO trigger ids per hotkey press
  (~100-200ms apart) — they may be duplicates (identical actions) or
  INDEPENDENT actions (e.g. 14=runScript, 34=activateTabs). file37 `_6y`
  drops the companion ONLY if the action signature matches
  (`__acTrigSig` = `JSON.stringify(_ek[id])`, 300ms window, different id).
- **Two engines at browser start / one orphan after close (FIXED 2026-08-06)** —
  every `connectNative` spawns a NEW Zero→engine pair; when Chrome kills the
  SW (startup churn) without closing the native pipe, the old Zero exits on
  EOF but its engine (spawned detached) LINGERS with global hooks. Symptom:
  2× `AutoCtrl_2025.4.22.0.exe` in Task Manager right after browser start
  (SW console shows gen 1 — the second pair is from a PREVIOUS SW generation),
  1 remains after browser close. Fixes in sw.js ONLY (no bundle rebuild):
  (1) `__acKillOrphanEngines(gen)` at doHandshake start — wmic scan of
  engine+Zero PIDs, `taskkill /F /PID` ONLY engines whose Zero parent is NOT
  alive (orphans; a live pair of ANOTHER browser is never touched —
  multi-browser setups keep working); (2) reconnect guard
  (`__acConnecting || (connected && handshakeDone)` → skip) in both reconnect
  handlers — file2.js z() sends reconnect 2× after install/repair, and each
  reconnect on a healthy connection used to spawn a duplicate host.
  mh_test B20.
- **Engine missing after Reinstall/Repair — "giving up" (FIXED 2026-08-07)** —
  the native installer DELETES `AutoCtrl_2025.4.22.0.exe`; the "unpack once
  per SW session" flag (`__acEngineUnpackAttempted`) then blocked the
  re-deploy → "Engine still missing after unpack — giving up" right after a
  reinstall (VM 16:48: deploy OK → installer → file check 2 forever; the
  orphan-kill hypothesis was REJECTED — disabling it did not help). Fix in
  sw.js only (no bundle rebuild): `__acEngineFileExists(gen)` (type 260
  `if exist` + getStdout) disambiguates answer 2 ("missing OR still
  starting"); the deploy path re-runs when the file is gone, capped by
  `__acEngineDeploys` (<2) to avoid antivirus deploy loops. mh_test B21.
- **Config chain does not re-run after reconnect → hotkeys dead (FIXED
  2026-08-07)** — after a native reinstall (host killed mid-SW-life) the
  engine was re-deployed and the handshake completed, but triggers never
  fired: the bundle's `configChainStarted` guard (mv3_native_shim.js,
  IIFE-local) stayed true from the first handshake, so the `nativeConfigReady`
  dispatch from `proceedAfterFileCheck` was skipped → no type 60, no type 21
  (log: "Config chain already started, skipping duplicate nativeConfigReady";
  user VM 16:59: engine up but hotkeys/gestures dead). Affects ANY mid-SW
  reconnect, not just reinstall. Fix in sw.js only (no bundle rebuild):
  `proceedAfterFileCheck` dispatches/broadcasts nativeConfigReady with
  `force: true` — the bundle resets the guard on force (same path as
  refreshConfigInSW); no-op on the first handshake. mh_test B22.
- **Fresh install / proper uninstall must offer the INSTALL UI, not "Something
  went wrong" (FIXED 2026-08-07)** — `mv3_shim.js` hardcoded `window._nd =
  true`, so `file2.js` (`_nd ? ping→natHostNotFound error : install pane`)
  always took the error path on a fresh install. The flag is now
  storage-based (`natHostInstalled`): default false + async storage read
  (+ `_Eu` signaled after the read so file2.js proceeds with the correct
  value), persisted by the SW on connect (`proceedAfterFileCheck`) AND by the
  shim's ping callback (covers pages opened before the SW connected), and
  cleared by the proper uninstall flow (`file30.js _ei` →
  `chrome.storage.local.remove("natHostInstalled")` + `window._nd=!1`).
  Files: mv3_shim.js / sw.js / file30.js — all page/SW, NO bundle rebuild.
  mh_test B23.
- **Fresh-install: extension must connect to the native WITHOUT a manual
  reload (FIXED 2026-08-07)** — after the user installs the native from the
  install UI, the SW kept failing `connectNative` until the extension was
  reloaded. Root cause: Chrome CACHES the failed "Specified native messaging
  host not found" lookup PER SW INSTANCE (the reinstall path worked because
  the SW had connected once before — no cache). Fix in sw.js only (no bundle
  rebuild): the install UI (file2.js `m(Infinity,1000)`) pings type 920 every
  second; after 20 "native not ready" answers with a DEAD port (`!port` —
  never during an engine deploy, the port is alive then), the SW sets
  `__acInstallAutoReload` in storage and `chrome.runtime.reload()`s itself
  once per SW session; the fresh SW finds the host, and
  `proceedAfterFileCheck` reopens the options page automatically
  (`chrome.runtime.openOptionsPage()` when the flag is set). Note: A11 now
  scopes the "no reload" check to the deploy area only. mh_test B24.
- **Uninstall: no infinite reconnect loop; Emergency Repair actually repairs
  (FIXED 2026-08-07)** — after a native uninstall (or when the host was never
  installed) the SW retried connectNative FOREVER (user VM 18:15: gens 2-50+
  "host not found"), spawning Zero attempts + console noise with zero chance
  of success. Fixes in sw.js/file30.js only (no bundle rebuild):
  (1) `__acEverConnected` (set in proceedAfterFileCheck) + `errors >=
  __acMaxNeverConnectedFailures` (8) in onDisc → stop auto-retry and wait for
  a page-driven reconnect (install UI z() sends {cmd:"reconnect"} — resets
  errors/retries) or a reload; (2) Emergency Repair (context menu
  "reloadExtn") no longer dispatches {type:"emergencyRepair"} → bundle
  `_co(1,!0)` ("Wait" badge + `_Lk(_vh,…)` → location.reload on the native
  reply — after an uninstall the reply never comes, badge stuck at "Wait"
  forever). It now sets `__acEmergencyReload` in storage +
  `chrome.runtime.reload()` (MV2 `_co(2)` semantics); the fresh SW reopens
  the options page (same flag check as __acInstallAutoReload); (3) after a
  proper uninstall (file30.js `_ei`) the settings page auto-reloads after
  ~2.6s to show the install pane (MV2 didn't reload — it just re-enabled the
  UI and showed the error dialog on the next load). mh_test B25.
  - Follow-up (2026-08-07, VM 22:50): (a) the reconnect-loop stop missed the
    UNINSTALL-AFTER-CONNECT case — `!__acEverConnected` was true (connected
    before the uninstall) so gens kept going forever. Now the stop applies
    after `errors >= __acMaxNeverConnectedFailures` CONSECUTIVE failures
    (errors resets on every successful handshake; a temporarily-down host
    still reconnects when it returns); (b) `mv3_shim.js` no longer sets or
    persists `natHostInstalled` from the ping callback — a stale `connected`
    during an uninstall re-armed the flag → "Something went wrong" instead of
    the install pane. `_nd` now ALWAYS comes from the storage read (including
    false); the SW persists the flag only in proceedAfterFileCheck (real
    handshake); (c) the "Emergency repair" context-menu item is now created
    by the SW at startup (file47 `_nk()` only runs on the settings page —
    after an extension reload the menu item was gone until the page opened);
    the create() patch skips the page's duplicate once the SW owns it
    (`__acCtxMenuOwned`).
- **Install pane must NOT auto-close (FIXED 2026-08-07)** — file2.js `x()`
  used to start the pong ping-loop when `_dh` (native connected time) was
  set: on a fresh extension install with the native still present (leftover
  from a previous session) the pane closed itself ~1s later — before the
  user could read the instructions / download the installer (`t()` pings
  type 920; on `pong` → `z()` removes the pane). Fix in file2.js +
  mv3_shim.js (both page-side, no bundle rebuild): (1) the ping-loop now
  starts ONLY after the user clicks Install (`f() → t()`); the `_dh`
  auto-start is removed; (2) for the leftover-native case the shim, when the
  SW reports connected AND `natHostInstalled` is in storage (the SW persists
  it on a real handshake), dispatches `ac-install-done` → file2.js calls
  `z()` → settings. Safe against the uninstall race: `_ei` removes the flag
  BEFORE the reload, so no dispatch then. mh_test B26.
- **Emergency Repair now matches MV2 exactly (2026-08-07)** — the menu item
  (created by the SW at startup, `__acCtxMenuOwned`) sends **type 55**
  (`_vh`, "Emergency repair / reload native") to the NATIVE — the native
  restarts the engine (visible in Task Manager, as in MV2). Badge sequence
  Wait (red) → OK (green, 2s) → cleared, exactly like MV2 `_co(1,!0)`
  (`_Cr("Wait","#F00")` … `_Cr(" OK ")`). On the native reply the OPEN
  settings page is reloaded (`chrome.tabs.reload` — MV2 `location.reload()`
  on the current page); the options page is NOT opened (MV2 doesn't). If the
  native is down, the badge is cleared (no stuck "Wait" — the old MV3 path
  `_co(1,!0)` waited for a reply that never came after an uninstall). The
  previous `chrome.runtime.reload()`+`openOptionsPage()` approach is removed;
  `__acEmergencyReload` flag is gone (only `__acInstallAutoReload` remains).
  mh_test B25.
  - **FIX 9 (2026-08-07): SINGLE handler only — do NOT add a sw.js onClicked
    listener for "reloadExtn"!** The bundle's file62_mv3.js ALREADY registers
    `chrome.contextMenus.onClicked` → `_co(1,!0)`. A sw.js handler DUPLICATES
    it: two type-55 sends + badge race (bundle's Wait overwrites our OK;
    user VM 23:41: Wait blinked, no OK). Also `location.reload()` is a
    TypeError in the SW (WorkerLocation has no reload) — `_co` (file34_mv3.js,
    IN bundle) was fixed for the SW: badge " OK " (#0F0) + 2s clear +
    `_Yk.tabs.query({url:"chrome-extension://"+id+"/*"})` →
    `_Yk.tabs.reload(t.id)` for each (MV2 reloads the CURRENT page; the
    options page is NOT opened); a==2 still `_Yk.runtime.reload()`. sw.js
    keeps ONLY the create() with `__acCtxMenuOwned` (menu visible after
    extension restart). mh_test B25 asserts sw.js has NO `postWithCb(55` /
    NO `setBadgeText({ text: "Wait" })` / NO `menuItemId === "reloadExtn"`,
    and file34_mv3.js has `_Cr(" OK ","#0F0")` + `_Yk.tabs.reload`.
  - **Emergency Repair with NO native (2026-08-08)**: clicking the menu item
    when the host is not installed (fresh extension install, native never
    installed / engine files gone) flashed Wait→OK but nothing happened — the
    type-55 send goes nowhere (dead port). `_acNativeSend` (sw.js) now detects
    `a === 55 && !port` → `chrome.runtime.openOptionsPage()` — on a fresh
    install the install pane shows (natHostInstalled absent), otherwise the
    settings page. The badge flow still completes (callback fires with `_g`),
    nothing sticks. Also added a global `unhandledrejection` guard that
    swallows only "Could not establish connection"/"Receiving end does not
    exist" (page-less broadcast noise at SW start — TODO item closed); other
    rejections still surface. mh_test B25 checks `a === 55 && !port` +
    `openOptionsPage()` + the unhandledrejection guard. 45 pass / 4 gaps / 0 FAIL.
  - **Menu item vanished after settings page opened (2026-08-08, FIX 11)** —
    user VM 00:18: "the emergency item disappears until the extension reloads".
    ROOT CAUSE: `_nk()` (file47.js) runs inside the SW config chain and calls
    `chrome.contextMenus.removeAll()` on EVERY chain run (startup, reconnect,
    storage rebuild). That deleted the SW-created "reloadExtn" item, and the
    create() patch (`__acCtxMenuOwned` → `return 0`) skipped recreating it →
    the item was gone until the extension reloaded. FIX in sw.js: patch
    `contextMenus.removeAll` — after the real removeAll, if
    `__acCtxMenuOwned`, recreate the reloadExtn item. Same session: onActivated
    (file62_mv3.js, IN bundle) threw `Cannot set properties of undefined
    (setting 'activeTab')` — `_cd[c]` is undefined when the native is dead
    (window enum never ran) → guard `if(!e)return` added. Bundle REBUILT
    (237287, arrow OK). mh_test B25 extended (removeAll patch + guard).
  - **Engine PID never changed on Emergency Repair (2026-08-08, FIX 12)** —
    user VM 00:38: type 55 was sent (`Emergency repair: sending type 55`),
    the native acked `true` in 1ms, but the engine PID stayed the same (4
    clicks, no restart). ROOT CAUSE: in MV2 the engine restart does NOT come
    from type 55 — it comes from `_co(1)`'s `location.reload()` (file34.js):
    the BACKGROUND PAGE reloads → the native port drops → Zero exits on EOF
    → the fresh page reconnects → fresh Zero spawns a fresh engine. Type 55
    is just an ack; the reload does the work. MV3 has no background page
    (SW-brain), so the SW now replicates the cycle in place:
    `_acNativeSend` a===55 branch → `__acEmergencyRestartNative()`:
    (1) `_iw("taskkill /F /IM AutoCtrl_2025.4.22.0.exe")` through the live
    port (visible in Task Manager, as in MV2 — note the native acks type
    260 when cmd STARTS ~7ms, taskkill keeps running anyway); (2) 400ms
    later `port.disconnect()` → onDisc → scheduleRetry → reconnect (fresh
    Zero spawns a fresh engine; __acKillOrphanEngines at the next handshake
    is the fallback); (3) badge " OK " (#0F0) shown by proceedAfterFileCheck
    ONLY after the reconnect succeeds (`__acRepairBadgePending` flag — MV2
    also shows OK after the reload reconnects); (4) 20s safety timer shows
    red "Error" instead of hanging in Wait. The bundle `_co` (file34_mv3.js)
    no longer sets the OK badge for a==1 — it only reloads the current page
    (tabs.reload). mh_test B25: `postWithCb(55, b, 5000)` IS now expected in
    sw.js (inside the a===55 branch only — no own onClicked handler).
    Bundle REBUILT (237476, arrow OK). 45 pass / 4 gaps / 0 FAIL.
  - **"Unchecked runtime.lastError: Native host has exited" (2026-08-08)**:
    Chrome logs this when the onDisconnect callback never reads
    `chrome.runtime.lastError`. Both variants are EXPECTED: "Native host has
    exited" during Emergency Repair (we taskkill the engine and drop the
    port) and "Specified native messaging host not found" on a failed
    connectNative (no-native install). The onDisconnect listener now does
    `void chrome.runtime.lastError;` first. Also the "Host exited Xms after
    connect — engine may have crashed" warning is skipped while
    `__acRepairBadgePending` is set (the exit is intentional during repair).
    sw.js only — no bundle rebuild. mh_test B25 extended. 45 pass / 4 gaps / 0 FAIL.
  - **~43s input stall after Emergency Repair (2026-08-08, FIX 14)** — user
    VM 01:36: repair completed (badge OK, full handshake, type 21 at
    01:36:09.784) but the first trigger arrived only at 01:36:52.924
    ("First trigger 19 arrived 43142ms after type 21"). ROOT CAUSE: FIX 12's
    `taskkill /F` = TerminateProcess — the killed engine's global hooks
    (WH_KEYBOARD_LL/WH_MOUSE_LL) DANGLE in Windows, and the fresh engine
    receives NO input until Windows cleans them up (~40s). MV2 never
    hard-killed the engine: Emergency Repair there = background-page reload
    (port drop → Zero exits on EOF → reconnect → fresh pair; a lingering
    engine keeps LIVE hooks and events still reach ALL hooks). FIX: removed
    the taskkill from `__acEmergencyRestartNative` (port drop only, 300ms
    then disconnect) + skip `__acKillOrphanEngines` while
    `__acRepairBadgePending` (it would hard-kill the still-alive old engine
    → same stall). Log: "reconnecting native (port drop, MV2-style)".
    mh_test B25: no taskkill in the repair path + orphan-kill gate. 45 pass / 4 gaps / 0 FAIL.
  - **Emergency Repair now RELOADS the SW (2026-08-08, FIX 15)** — user
    noticed: after Emergency Repair the hotkeys/gestures bind IMMEDIATELY if
    the extension is reloaded afterwards (VM 2026-08-08), while the
    port-drop-only cycle (FIX 14) sometimes left the old engine alive
    without a working pipe (its Zero dead → triggers never arrived). A
    reload = fresh SW → fresh connectNative → fresh Zero+engine with fresh
    hooks — exactly the MV2 mechanism (repair = background-page reload).
    FIX: `__acEmergencyRestartNative` now does `chrome.storage.local.set({
    __acRepairBadge: true })` → `chrome.runtime.reload()`. The FRESH SW
    shows the " OK " badge in proceedAfterFileCheck by consuming
    `__acRepairBadge` (storage survives the reload; like __acInstallAutoReload).
    The in-memory `__acRepairBadgePending` + port drop + 20s Error timer are
    REMOVED (all references deleted). NO taskkill anywhere in the repair
    (FIX 14). mh_test B25 asserts: `__acRepairBadge` storage flag + "reloading
    SW (MV2 background-page reload)" log + NO `__acRepairBadgePending` + NO
    taskkill/port-drop strings. GOTCHA: A11's deploy-area regex matches
    `chrome.runtime.reload()` in COMMENTS — keep comments about the reload
    literal-free inside the deploy area (proceedAfterFileCheck).
    sw.js only — no bundle rebuild. 45 pass / 4 gaps / 0 FAIL.
    **VM-VERIFIED 2026-08-08**: repair works — SW reloads, badge OK,
    hotkeys bind immediately. The FIX 14 port-drop attempt was observed to
    hang in the red "Error" status and NOT restart the engine after the
    kill (user: "the previous attempt hung in red status and did not
    restart the engine after the kill") — another reason the reload approach is the
    right one.
  - **Dead-port repair left the badge stuck on "Wait" (2026-08-08, FIX 16)**
    — user VM 01:55: native not installed → clicked Emergency repair → the
    install page opened BUT the icon badge stayed "Wait" forever. ROOT
    CAUSE: the bundle `_co(1,!0)` sets the "Wait" badge BEFORE sending type
    55; in the dead-port branch (`a === 55 && !port`) there is NO SW reload
    to replace it — MV2 replaced it on the RELOADED page via `_nt("showNotif")`
    → "Error" when the native is down. FIX in sw.js: the dead-port branch
    now shows the FINAL status itself — badge "Error" (#F00) + clear after
    2s — then `c(_g)` and `return true` (skips the doomed postWithCb).
    mh_test B25: `setBadgeText({ text: "Error" })` in the dead-port branch.
    sw.js only — no bundle rebuild. 45 pass / 4 gaps / 0 FAIL.
  - **Fast wheel-spin tab skipping (2026-08-08, FIX 17)** — user VM
    02:12-02:13: the wheel-over-omnibox switch-tab action (switchRight /
    switchLeft → activateTabs/_Ph) SKIPPED tab steps — the faster the spin,
    the more skips, though the log showed every 750 trigger firing (ACT/OK
    for each). ROOT CAUSE: the pos:next/prev target filters (`rightTabWrap`/
    `leftTabWrap` → `_Mg`/`_xy`) resolve the BASE tab from `_Np` (the cached
    active tab), and `_Np` was refreshed ONLY by the `onActivated` listener —
    ASYNCHRONOUSLY after the activation landed. Fast spins (triggers every
    30-100ms) hit the STALE `_Np` → `_xy` returned the SAME neighbor tab →
    it was activated twice → one visible step lost per collision (the faster
    the spin, the more collisions). FIX: `_Ph` (file8.js, IN BUNDLE) now
    optimistically sets `_Np=c` BEFORE `tabs.update` — the next trigger
    immediately sees the new active tab. Bundle REBUILT (238015, arrow OK).
    mh_test B27. 46 pass / 4 gaps / 0 FAIL.
  - **Remaining wheel-spin skips — STALE `_Yp[].active` flags (2026-08-08,
    FIX 18)** — user VM 02:22: "much better, but short skips
    still occur". The `_Ph` skip-branch (`e.active?…:_Np=c,…`) skipped
    activation when `_Yp[c].active===true` — but that flag was ONLY
    refreshed by `_Fu` (window enum), never reset on real tab switches.
    At a wrap transition through a previously-active tab (stale
    active=true) the activation was skipped AND `_Np` stayed stale → the
    next trigger targeted the SAME tab → skipped wheel step (one per wrap
    per enum). FIX: (1) `_Ph` (file8, IN bundle) sets `e.active=!0` when
    activating; (2) `onActivated` (file62_mv3, IN bundle) resets the old
    activeTab's flag (`_Yp[c].active=!1`) and sets the new one
    (`f.active=!0`) — onActivated is the source of truth. Bundle REBUILT
    (238536, arrow OK). mh_test B27 extended. 46 pass / 4 gaps / 0 FAIL.
  - **Bundle rebuild gotcha (2026-08-07): file77.js MUST be in the $f list**
    (after file48.js — `_Yh` is a top-level `let` in file48, TDZ!). If the
    rebuild list is missing it, userAPI breaks at runtime (`_Yh` never
    assigned — W()/K/setClipboard dead) AND mh_test FAILs on K
    non-destructive + binSwtch guard (both check the bundle). Bundle size
    sanity: ~236918 (was ~218052 without file77).
- **n() (file48)**: `sendMessage(tabId,msg,{frameId:0},cb)` + 4000ms
  fallback timer (once-guard race) → if no listener, inject file42 + retry
  (1 retry max). Diagnostics: `[AC-DLV] resp/no listener`, `[AC-F42] res
  rcvd/sw cb`, `[AC-SW] execUserFunc rcvd age=`.
- **Toasts / `_Cr` (TODO §7-10) CLOSED 2026-08-09 as obsolete** — `_Cr`
  (file13) is the icon BADGE, NOT a toast — works in the SW (Emergency
  Repair Wait/OK/Error). The floating display is a `file71.html` popup
  created by `_Fo` (file70) via `chrome.windows.create` — AVAILABLE in the
  MV3 SW, so it works without the settings page (`_Uk` Stop-waiting, `_Lh`
  no-hook, `_Kg` repair/hotkeys). `_nt("showNotif")` (file67) is a
  localStorage flag bridge (read-once after reload), NOT a toast — in the
  SW it's guarded (`localStorage&&`); the repair badge is shown directly
  from sw.js (FIX 15). chrome.notifications already in use (saveUrl notif
  §7-2, protected-page hint). The only real remainder is z[800]
  classification (no-hook-notice dialog, invalidExtId, APDL→`_r`,
  segFault→`_uf`) — tracked as its own TODO item §7-4.
- **`runInFrames` subframes (TODO §7-5) FIXED 2026-08-10 (sw.js only, no
  bundle rebuild)** — the symptom was WORSE than "subframes silently
  skipped": a subframe's file42 → FN (eval forbidden in isolated worlds,
  Chrome 133+) → SW `execUserFunc` → `userScripts.execute({frameIds:[0]})`
  → the funcCode ran N times (once per matching frame) but ALWAYS in the
  TOP frame (location/document = top frame). FIX: `const frameId = sender
  && typeof sender.frameId === "number" ? sender.frameId : 0` →
  `target:{tabId, frameIds:[frameId]}`. MV3 provides sender.frameId for
  content-script messages from ANY frame. Per-frame ~suffixes (rounds 5-6)
  already kept the SW dedup keys unique across frames; the frmCBId/pongId
  aggregation (file48 `r()`) is unchanged. mh_test B37. Remaining edge:
  `ACtl.runInPageCtx` INSIDE a runInFrames func still routes to frame 0
  (execMainWorld has no frame info yet) — compound, rare.
  Follow-up (same day, "first run returned only null"): the FIRST
  userScripts.execute in a fresh (sub)frame costs ~4-5s (Chrome creates the
  USER_SCRIPT world on first use); the SW acks early via its 3s safety
  timeout and the first result can be lost — file42's FN now RE-SENDS
  execUserFunc ONCE if `h.timeout` came back and no acUserApiRes arrived
  within 6s (world warm by then → retry succeeds; fresh id; double-exec
  only if the first attempt takes >9s). mh_test B38.
  Follow-up 2 (same day, "[url, null] with several frames"): the SAME
  frmCBId message (it carries scriptId → handled by the scriptId branch)
  is delivered to EVERY matching frame; trigInstId came from the message
  AS-IS → all frames sent execUserFunc with the SAME SW dedup key → the
  2nd+ frames got BLOCK in-flight → {result:undefined} → null (user VM:
  ["https://example.org/", null]; log: two rcvd with the same key +
  BLOCK in-flight). Fix (file42.js, no bundle rebuild): the scriptId
  branch appends a per-FRAME `~f`+random suffix to trigInstId when
  a.frmCBId is set — each frame gets its own key → all execute, all
  results pushed; plain RUN SCRIPT (no frmCBId) unchanged. mh_test B39.
  VM-VERIFIED 2026-08-10: gazeta.ru with a real third-party iframe —
  `[null,"https://zvuk.com/rambler"]` ({depth:1}: top frame null by design,
  subframe returns ITS OWN url); dynamic about:blank iframe with an empty
  filter — `["https://example.org/","about:blank"]` (both frames, no null).
- **file:// tabs always untargetable by runInTab/runInFrames (FIXED
  2026-08-10, TODO §7-8 — sw_prelude.js IN the bundle → REBUILT 245807,
  arrow OK)**. The prelude hardcoded
  `chrome.extension.isAllowedFileSchemeAccess = cb => cb(false)` → the
  bundle's file13 built its `_id`/`_es`/`_As` scheme gate with `file:`
  ALWAYS restricted → file77 `Q()` filtered file:// tabs out of
  runInTab/runInFrames targets even when the user enabled "Allow access to
  file URLs" (MV2: targetable with the toggle ON). The real API DOES exist
  in the MV3 SW — the prelude now passes it through
  (`__acRealFileSchemeAccess`/`__acRealIncognitoAccess`, fallback cb(false)
  only when unavailable, e.g. the mh_test harness); sw.js's "fileAcc"/
  "incogAcc" cases get real values too. ⚠ The gate is read ONCE per SW load —
  after toggling file access, reload the extension (same as MV2). mh_test
  A4: GAP → PASS (source check + harness-stub runtime check). 72 pass /
  0 gaps / 0 FAIL — the LAST remaining GAP is closed.
- **z[800] error classification (FIXED 2026-08-10, TODO §7-4 —
  mv3_native_shim.js IN the bundle → REBUILT 248016, arrow OK)**. MV2
  file61.js `E()` classified native errors; the MV3 shim forwarded everything
  to `_Ot` (telemetry — off by default → ZERO user feedback when the engine
  could not install hooks). FIX: full port — no-hook-notice → `_uf` error
  counter + the file71.html floating popup (`_Lh` via `chrome.windows.create`,
  works from the SW) after 5 notices in 15s unless disabled
  (`noHookConflictMsg`; localStorage is in-memory in the SW → the popup can
  re-arm after an SW restart — rare error path, acceptable); invalidExtId →
  `_2u()` install-age gate; APDL → sets the bundle `_r` flag (file62_mv3 idle
  handler stops the type-790 ping once verified); NH-error 0xC0000005 →
  `_uf("segFault")`; default → `_Ot`. mh_test A2b (source checks + runtime
  smoke — the popup is 5th-only, never triggered in the harness). GOTCHA
  surfaced by the smoke: file67 defines `Object.prototype.add/sc/...` on the
  vm-realm Object — a node-realm `{}` result from the storage.local.get stub
  lacks `.sc()` → `_Mi`'s batched flush (`_bd→_bj→a.sc()`) crashed with
  "a.sc is not a function" in ANY storage-writing harness test (never in the
  real SW — chrome creates results in the extension realm). The stub now
  returns `vm.runInContext('({})', ctx)`. 75 pass / 0 gaps / 0 FAIL.
- **SW popups (file71.html) crashed — _Zw (monitor map) never populated at
  SW startup (FIXED 2026-08-10, TODO §7-4 follow-up — sw.js + file70.js +
  mv3_native_shim.js IN the bundle → REBUILT 248785, arrow OK)**. MV2
  called `_Sf(c)` (file13 — fills `_Zw` from chrome.system.display.getInfo)
  at startup; the SW never did (only the onDisplayChanged path via
  file62_mv3) → `_Zw` stayed `{}` → `_Fo` (file70, popup positioning)
  crashed with "Cannot read properties of undefined (reading 'workArea')" →
  the z[800] no-hook notice popup never appeared (VM 2026-08-10 22:13) and
  `nhBusy` stayed true forever (silent no-ops). Also degraded ALL popups
  (`_Lh`/`_Uk`/`_Kg`) and monitor-based actions (`_Xe`/`_ey`/`_gf`/`_8k`).
  FIX: (a) sw.js `sendMonitorInfo()` calls `_Sf(() => {})` at every startup
  (`_Sf` is a bundle top-level function — free variable, same as `_Qj`);
  (b) z[800] wraps `_Lh` in try/catch resetting `nhBusy` (log
  `[AC-MV3] no-hook notice popup failed`); (c) `_Fo` falls back to
  `{left:0,top:0,width:400,height:200}` when the monitor is unknown. mh_test
  A2b extended (3 checks). 78 pass / 0 gaps / 0 FAIL.
  **FIX 2 (same day, VM 22:20)**: the popup opened but stayed EMPTY — `_Fo`
  then crashed on `l.document` (bundle:586): `_Yk.extension.getViews({
  windowId:f.id})[0]` is undefined — `chrome.extension.getViews` does NOT
  exist in the MV3 SW (prelude stubs it to `[]`), and the whole file71-popup
  mechanism (`_Lh`/`_Uk`/`_Kg`/REPAIR COMPLETE) is built on it. FIX: z[800]
  no-hook now uses **chrome.notifications with buttons** (the TODO's
  original plan; API proven in the SW — saveUrl §7-2, protected pages):
  button 1 = "Don't show again" (answer true), button 2 =
  "Keep showing" (false); answer → `_Ot` + `noHookConflictMsg`; without the
  notifications permission it degrades to the silent `_uf` counter; `nhBusy`
  resets on button/close/failure. Other file71 popups from the SW stay
  broken (rare paths) — tracked as a low-priority TODO. Bundle rebuilt
  (250736, arrow OK). mh_test A2b updated (notifications path, NOT `_Lh`).
  78 pass / 0 gaps / 0 FAIL.
- **«On startup» trigger never fired (FIXED 2026-08-10, TODO «Misc» — sw.js
  only, no bundle rebuild)**. `_Vs=30` is the "On startup"
  event (file68.js `[_Vs]:{name:"On startup"}`) — users can bind actions to
  it. MV2 file61.js D() called `_Wo(_Vs)` once per session after type 21
  (`!G++ && !_nt("noStupEvt")`) → type 50 to native → the "On startup"
  trigger fired. The MV3 port never called it (file61's D() is replaced by
  mv3_native_shim) → such triggers NEVER fired. FIX: sw.js `finishStartup`
  calls `_Wo(_Vs)` after `postMsg(21)` with a once-per-session guard
  (`__acStartupEvtSent`) + `noStupEvt` skip (MV2 parity; in the SW it is
  in-memory localStorage, so after a repair reload the event DOES fire —
  acceptable). `_Wo` is a no-op unless a trigger uses the event (`_uk[30]`).
  mh_test: new check (80 pass / 0 gaps / 0 FAIL).
  **VM-VERIFIED 2026-08-10**: with an "On startup" trigger (→ Run script),
  the SW log shows `→ Native type 21` → `→ Native type 50` → `TRIGGER 750
  id=20715 → triggerId 40` → `ACT action=runScript` — the script ran right
  after startup. Side-confirm: the active tab was chrome://newtab →
  `executeScript blocked — protected page` + `[AC-DLV] why=lasterr:...`
  (expected — scripts cannot run on protected pages; hint shown).
- **file42 is a MANIFEST content script since round 8 (2026-08-06)** —
- **runScript / ACtl.* on chrome://, Web Store — SILENT FAIL (UX-FIXED
  2026-08-09; sw_prelude.js IN bundle → rebuilt 244236, arrow OK; sw.js
  outside bundle)**. Chrome refuses ALL script injection on protected pages
  (chrome://*, chrome-extension://, Web Store, devtools://, view-source:) —
  content scripts, scripting.executeScript AND userScripts.execute all
  reject; identical in MV2 (tabs.executeScript failed there too) — platform
  restriction, NOT a port regression, no bypass API exists. Before: silent
  FAIL (RUN SCRIPT acks OK — t=true ignores errors; file42 never injects
  there; n() 6s timeout + raw "Cannot access a chrome:// URL"). FIX:
  (a) prelude helpers `__acIsProtectedPage(url)`/`__acProtectedMsg`/
  `__acNotifyProtected()` — bundle top-level, visible to the shim AND sw.js;
  (b) the tabs.executeScript shim pre-checks the tab URL via chrome.tabs.get
  (instant reject + hint instead of n()'s 6s timeout) and maps the raw
  rejection in catch; (c) sw.js execUserFunc fails fast on
  sender.tab.url + maps the userScripts.execute catch; (d) hint via
  chrome.notifications (guarded — optional permission, silent no-op,
  10s throttle). mh_test B36.
  Follow-up (same day, "notification not on every call"): NOT a Chrome
  priority issue — the FIXED id "acProtectedPage" made create() silently
  UPDATE the still-visible toast instead of showing a new one, and the 10s
  throttle dropped every second manual run. FIX: unique id per call
  (acProtectedPage_<seq>_<ts>) + 1.5s throttle (anti-spam only; priority
  stays 0 — no sound/alert). Bundle rebuilt 244843.
  `mv3-build/manifest.json` now declares `content_scripts: [{matches:
  ["<all_urls>"], js: ["file42.js"], run_at: "document_idle", all_frames:
  false}]` (AdGuard-style static injection; host_permissions `<all_urls>`
  already present → no new permission warnings). Chrome now guarantees
  EXACTLY ONE file42 instance per top frame, re-injected on navigation,
  killed on extension reload — the rounds 4-6 class (stale instances,
  double delivery, "no listener → inject" 4000ms timeouts) is gone on
  normal pages. n()'s on-demand injection remains as FALLBACK for
  chrome://, Web Store, file:// and about:blank (content_scripts can't
  run there) and for post-reload recovery — the `document.__acF42` guard
  makes a fallback injection a no-op while the manifest instance lives.
  runInFrames subframes (r()/allFrames) still inject on demand (§7-5).
  file42's top-level if-wrapper guard was already classic-script-safe
  (an earlier attempt with top-level `return` broke the manifest load —
  TODO.md). NOTE: `persistAcrossSessions` is NOT a valid manifest
  content_scripts key (scripting.registerContentScripts only) — do not
  add it. After any manifest edit the extension must be reloaded at
  chrome://extensions; already-open tabs need ONE reload to get the
  manifest instance. mh_test B7 checks the manifest entry.
- **First run of a just-added script: +4-5s one-time userScripts init —
  warmup tried & REMOVED (rounds 9-12 → round 13, 2026-08-06)**. The FIRST
  `userScripts.execute` on a fresh page costs ~4-5s one-time (Chrome inits
  its userScripts subsystem; the run-2 log also showed results arriving
  871ms late). runInPageCtx(func) — the first test touching the MAIN world —
  paid it INLINE (user VM 18:25: FAIL +4031ms, repeat runs +24ms) and the
  4s tripped n()'s 4000ms fallback → retry → double execution. Rounds 9-12
  tried to warm the worlds up front (`__acWarmMainWorlds` no-ops on page
  load / SW start / first execUserFunc, self-healing + logging). **It did
  NOT work and was REMOVED in round 13**: Chrome SERIALIZES
  userScripts.execute PER TAB, and warmup no-ops did not pre-create worlds —
  they only queued an extra execute whose ~4-5s init BLOCKED the script's
  real calls (user VM 19:27 SW log: first execUserFunc +4909ms — was
  +6-11ms before warmup; runInPageCtx(func) still +4038ms). The one-time
  cost is now absorbed by **n()'s 8000ms fallback (round 13, file48 IN
  bundle → REBUILT 236317)**: the first call simply WAITS (no retry, no
  double execution); later calls on the tab are fast. Expected: the FIRST
  script run on a fresh tab takes ~4-5s (Chrome), every subsequent run is
  instant — documented in Docs/TODO.md. mh_test B8-B11 replaced by
  no-warmup + n6000 checks.
- **n() timeout 8000 → 6000ms (2026-08-06, round 14; file48 IN bundle →
  REBUILT 236454)**. round 13's 8000ms made the KNOWN §7-6 gap
  (runInPageCtx(func) — its result NEVER returns; the first attempt
  "hangs" while Chrome inits the MAIN world, the retry fails fast) wait
  the FULL timeout: user VM 19:40 FAIL +8031ms (was +4031-4038ms with
  4000ms). 6000ms is the compromise: legit first calls (init ~4-5s) still
  fit without a retry/double-exec, the gap FAILs in ~6s instead of 8s.
- **file37.js is minified** — when wrapping `if(a)a:if(...)` into
  `if(a){...a:if(...)}` add the extra closing brace (bundle compile error
  "Declaration or statement expected" otherwise).
- **PS console logs** — SW logs vs page logs are different consoles
  (SW: chrome://extensions → service worker link; page: F12 on settings tab).
- **ID stability**: `postWithCb` derives `l` from `chrome.runtime.id` substring.

## Documentation rules (IMPORTANT — the code is obfuscated)

This codebase is minified/obfuscated (`_qe`, `_md`, `_6s`, `_wj`, ...). Any
logic that is uncovered, changed, or worked around MUST be documented —
otherwise the next session starts from zero. Concretely:

1. **New findings go into the docs immediately** — do not postpone "until it
   stabilizes": add to `Docs/NATIVE_PROTOCOL.md` (protocol), `Docs/DECODE.md`
   (deobfuscation map — the file `/memories/repo/deobfuscation-map.md` is
   also a good place), `Docs/SUMMARY.md` (state/TODO), `Docs/FEATURES-MV3.md`
   (feature status & port gaps — single source of truth; broken items are
   tracked in `Docs/TODO.md` with section links) or `AGENTS.md` (gotchas),
   whichever fits.
1b. **Keep `README.md` (the install guide) current** — it is user-facing and
   must stay in sync with reality: extension toggles and their names
   (chrome://extensions → Details → "Allow user scripts" / "Allow access to
   file URLs"), the manual native-install steps (`AutoControl_native\` →
   `%UserProfile%\AppData\Local\AutoControl`), and the verification
   checklist. Whenever the native-install TODO is fixed ("Native component
   install: auto-deploy of the engine") or any toggle/path
   changes, update README.md in the same change.
2. **Every fix ships with a doc line** — at minimum a bullet in the relevant
   doc + a session-memory note (`/memories/session/autocontrol-mv3.md`):
   symptom → root cause → fix → rebuild status.
3. **Deobfuscation map**: when you decode a symbol/function, record it
   (`_qe=1` LMB, `_md=2` RMB, `_4e=60` config, `_zs` reads script code from
   `_if`, `_Mi` fires `_Gu`/`_B` subscriptions after storage write, etc.).
4. **Protocol changes**: any new/changed native message type, field, or
   handshake step goes into `Docs/NATIVE_PROTOCOL.md` with the exact wire format.
5. **Bundle rebuild notes**: state the bundle size after each rebuild in the
   session memory (quick sanity: marker present? size changed?).
6. **🔴 HIGH PRIORITY — deobfuscation & protocol DISCOVERIES and
   INACCURACY CORRECTIONS are documented THE MOMENT they are made — not only
   changes, and not only in code-changing sessions.** A session that decoded
   or observed something new (or spotted a wrong/outdated doc entry) but
   ended without updating the map is INCOMPLETE. Every session MUST land its
   findings AND fix any inaccuracies before it ends:
   - new decoded symbols/functions → `Docs/DECODE.md` (symbol tables) —
     including CORRECTIONS of wrong entries (e.g. 2026-08-08: `_9k` is
     `localStorage.setItem/removeItem`, NOT `chrome.storage.local.set`);
   - new semantic facts about the native (message meaning, side effects,
     lifecycle) → `Docs/NATIVE_PROTOCOL.md` with the exact wire format.
   Example of a MUST-document finding (2026-08-08): "type 55 does NOT
   restart the engine — it is an ACK; the MV2 restart came from the
   background-page reload (port drop → Zero exit on EOF → fresh Zero spawns
   a fresh engine)" is now NATIVE_PROTOCOL §18, and `_co`/`_ze`/`_nk`/
   `_Cr`/`_j`/`_nt`/`_2u` + 55/451 are in DECODE.md.

## Where to look for docs

- Content script CSP / isolated worlds:
  https://developer.chrome.com/docs/extensions/develop/concepts/content-scripts
- userScripts API:
  https://developer.chrome.com/docs/extensions/reference/api/userScripts
- Offscreen documents: https://developer.chrome.com/docs/extensions/reference/api/offscreen
- Sandbox pages: https://developer.chrome.com/docs/extensions/develop/concepts/declare-permissions#sandbox
- `scripting.executeScript` (no matchAboutBlank):
  https://developer.chrome.com/docs/extensions/reference/api/scripting
- This repo's own docs: `README.md` (install guide — user-facing), `Docs/NATIVE_PROTOCOL.md`, `Docs/DECODE.md`, `Docs/SUMMARY.md`,
  `Docs/RIGHT-CLICK-ISSUE.md`, `Docs/FEATURES-MV3.md`, `Docs/TODO.md`, `CHANGELOG.md`.

## Native protocol (short)

Native host `hrich.autocontrol`; messages `{type, content, callback}`,
callback `e+l` (l from ext id), echo reply type 710. Key types: 10=file check,
20=init, 21=startup, 60=config (mapKey=keyId+22025), 67=monitors, 72=switch
states, 300=SendInput, 750=trigger, 760=raw gesture, 905=keepalive, 920=ping.
Details: `Docs/NATIVE_PROTOCOL.md`.
