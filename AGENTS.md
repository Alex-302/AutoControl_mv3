# AGENTS.md — AutoControl MV3 port (working notes)

> **What this file is**: rules + current gotchas for working on the MV3 port.
> It is a working reference for agents/contributors, not a changelog.
>
> - Fix chronology & public record → `CHANGELOG.md` (Keep a Changelog)
> - Open items → `Docs/FEATURES-MV3.md` §7
> - Feature/port status → `Docs/FEATURES-MV3.md` (§7 gaps, §8 impossible in MV3)
> - Coverage overview (plain language) → `Docs/MV2-MV3-coverage.md`
> - Protocol reference → `Docs/NATIVE_PROTOCOL.md`; symbol map → `Docs/DECODE.md`
> - Historical docs (closed bug reports, session handoffs) → `Docs/archive/`

## Language rule (code)

**ALL code and comments in `mv3-build/` MUST be in ENGLISH.**
This includes comments, log strings, and error messages in `sw.js`,
`file42.js`, `sw_prelude.js`, and the bundle sources. Code files — English only.

## Repository layout

- **`ext-mv2/`** = the ORIGINAL MV2 extension (upstream baseline,
  `manifest_version: 2`, background page `file63.html`). **DO NOT EDIT** — it
  is the reference for the port.
- **Repo root** = `AGENTS.md`, `README.md`, `CHANGELOG.md` + the folders
  below; all other docs live in `Docs/`, test artifacts in `Test/`.
- **`Docs/`** = `FEATURES-MV3.md` (status & open items §7),
  `MV2-MV3-coverage.md`, `NATIVE_PROTOCOL.md`, `DECODE.md`,
  `SCRIPTING-API-SUMMARY.md`, `SUMMARY-SCRIPTING-API.md`.
  **`Docs/archive/`** = historical docs:
  `✅ BUG-REPORT-runScript-duplicates.md` (closed 2026-08-05),
  `HANDOFF-2026-08-06-unstaged.md`, `RIGHT-CLICK-ISSUE.md`.
- **`Test/`** = `SCRIPTING-API-TEST.js` (in-browser API self-test) +
  `AutoControl-settings-test.acs` (settings snapshot for mh_test).
- **`AutoControl_native/`** = native host (manifest + decrypted exes).
- **`mv3-build/`** = the MV3 port (SW-brain). **This is where ALL work
  happens.** Load this folder in Chrome as an unpacked extension. Contains its
  own copies of the core `file*.js`/`res/` — independent from `ext-mv2/`.
- **`Toolbar-buttons/`** = auxiliary builds/assets (MV2/MV3 pairs: base,
  Duplicate, Mute, Pin, Unload).
- NOTE: the old loose MV3 shims at the repo root were REMOVED (cleanup
  commit) — the working copies live in `mv3-build/`. Do not recreate them.

## Contribution rules (post-task)

- You MUST verify your change with the harness:
  `node mv3-build/mh_test.js` — expect `SUMMARY: N pass, 0 known gaps,
  0 FAIL` (exit 1 on FAIL). Filter: `2>&1 | Select-String -Pattern
  "PASS|FAIL|GAP|SUMMARY"`.
- You MUST keep `mh_test.js` current — every new fix ships with a smoke test
  (`[PASS]`/`[FAIL]`/`[GAP ]`/`[FIXED?]`). When a `[GAP ]` stops reproducing,
  update `Docs/FEATURES-MV3.md` §7.
- After editing ANY file from the bundle list (see Bundle build), you MUST
  rebuild `sw_core_bundle.js` and run the arrow sanity check.
- After editing `Test/SCRIPTING-API-TEST.js` you MUST re-copy its content
  into the RUN SCRIPT editor (extension reload does NOT update saved
  scripts).
- You MUST document findings: protocol facts → `Docs/NATIVE_PROTOCOL.md`;
  decoded symbols → `Docs/DECODE.md`; gotchas → this file;
  feature status → `Docs/FEATURES-MV3.md`; user-facing record →
  `CHANGELOG.md`.
- You MUST keep code in `mv3-build/` English-only (see Language rule).
- When the project structure changes, keep the Repository layout section
  valid.

## Test harnesses (used repeatedly — keep them working)

- **`mv3-build/mh_test.js`** — Node `vm` harness loading `sw_core_bundle.js`
  with stubbed `chrome`/DOM globals. Validates: bundle loads, `_Yk===chrome`,
  z-handler completeness (15 base types), prelude browserAction→action alias
  and onClicked listener count, `_As` scheme gate (file://), `_9w` inert
  loading (playAudio routed to the offscreen doc), webRequest absence (saveUrl
  via declarativeNetRequest), icon/menu machinery, `_mh` user-config
  compilation (wheel/gesture entries), global visibility (free-variable
  `_Yh` vs `self._Yh`), XHR-shim headers smoke, `_Yh` callback-style smoke,
  and userAPI dispatch (must be exactly 1 answering listener). Output
  `[PASS]`/`[FAIL]`/`[GAP ]`/`[FIXED?]`; exit 1 on FAIL. Path-independent
  (`__dirname`). Current: 80 pass / 0 gaps / 0 FAIL.
- **`Test/SCRIPTING-API-TEST.js`** — in-browser self-test of the whole ACtl
  API (23 tests), run via RUN SCRIPT on a normal page. 23/23 stable. Every
  failure prints an unmissable banner (`[AC-API-TEST: FAIL]`) + a final
  `[AC-API-TEST: FAILURES]` re-list. Known flake: the cold first
  `ACtl.on("tabLoadEnd")` on a fresh tab can exceed 15s on the VM (warm runs
  ~0.4s). `getFile` on a local file needs the "Allow access to file URLs"
  toggle.
- **`Docs/SCRIPTING-API-SUMMARY.md`** — API reference vs Chrome capabilities
  (status table, CSP rules, known limitations).

## MV3 architecture (SW-brain)

> **IMPORTANT: the MV3 port MUST be used ONLY as an unpacked extension**
> (chrome://extensions → Developer mode → Load unpacked). It is a dev/
> work-in-progress build: it relies on dev-mode freedoms (userScripts in
> unpacked contexts, eval fallbacks) and has NOT been packaged for the Chrome
> Web Store.

- `sw.js` — main service worker (glue): native messaging, broadcasts, sandbox
  bridge, config refresh, keepalive, RMB fixes (v6 stripRightButtonBlocks, v7
  gesture Esc), `execUserFunc`/`userAPI` handlers, capture watchdog.
- `sw_prelude.js` — patched globals loaded BEFORE the bundle:
  `__acInjectCode` (userScripts → MAIN-world eval fallback),
  `chrome.tabs.executeScript` shim, `__acDispatchSandboxMessage`,
  protected-page helpers. **Never put `matchAboutBlank` in scripting
  executeScript targets** (invalid in MV3 — throws TypeError).
- `sw_core_bundle.js` — concatenation of core files (list in Bundle build),
  loaded via `importScripts` in sw.js. Contains the "brain" (trigger dispatch,
  `_if`, `_ek`, `_pg`, config chain `_lr`→`_Gf`→`_6s`).
- **SW is ALWAYS the leader**: window enum + config chain run only in the SW;
  the settings page is UI-only and must NOT run the config chain
  (`isLeader()` gate in `mv3_native_shim.js`).
- Page-side shims: `mv3_shim.js` (chrome.tabs shims, SW registration),
  `mv3_native_shim.js` (native stubs delegating to SW; `_Lk`/`_Vy` → SW).
- **Telemetry is OFF by default (2026-08-08, user request)**: the analytics is
  OLD MV2 behavior (`_Ot` ALWAYS POSTed to appEvent; could not be disabled in
  MV2). We added ONLY the off-switch: `_Ot` is gated by `__acTel` (default
  false — NOTHING is sent until enabled), the flag comes from
  `advOpts.telemetry` (live via `storage.onChanged`); the callback is
  preserved when disabled (some call sites wait for it). UI: Advanced Options
  → «Send anonymous usage data».
- **Logging is OFF by default (MV2-like silence)** — publishing default.
  Options → Advanced Options → `logSw`/`logPage`/`logSettings` (applied LIVE
  via `storage.onChanged`; `console.error` always kept). Startup output is
  BUFFERED (`__acLogBuf`/`__acLogApplied`) until the advOpts read resolves.
- Offscreen document (`offscreen.js/html`): hosts the `file23.html` sandbox
  iframe (background Run Script) AND the playAudio engine — works even with
  the settings page closed.

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

## Script execution (Run Script) — MV3 rules

- Content scripts (isolated world) have their OWN CSP without `unsafe-eval`
  since Chrome 133: `eval`/`new Function` are FORBIDDEN there ALWAYS.
- Official way to run user code strings: **`chrome.userScripts.execute`**
  (Chrome 120+, permission `userScripts` + the "Allow user scripts" toggle on
  chrome://extensions).
- `file42.js` FN: sandbox/background (file23.html) has no `chrome.runtime` →
  use `eval` (sandbox CSP allows `'unsafe-eval'`); content scripts →
  userScripts bridge via SW (`execUserFunc`); toggle-off is cached
  (`__acUsOk=false`).
- Background scripts run in the `file23.html` sandbox IFRAME hosted in the
  **offscreen document** (created by the SW on demand — `_Uu` proxy routes
  BGScript iframe creation there).
- `matchAboutBlank` is NOT valid in `scripting.executeScript` targets.
- `chrome.userScripts` does NOT work on extension pages / chrome:// pages.

## Known pitfalls / fixes (current gotchas)

Each bullet: symptom → cause → fix → pointer. Dates = fix chronology (kept
intentionally). Full round-by-round narratives live in `Docs/archive/`
(closed bug reports, session handoffs) and the git history.

### Native lifecycle

- **Engine auto-install (FIXED 2026-08-04, clean rewrite)** — `sw.js`
  answers file check `2` by unpacking bundled `file76.dat` (MD5 = distro) via
  type 250 → poll on the SAME port (MV2 style) → one clean reconnect → give
  up with guidance. ROOT CAUSE of "file flashed and vanished": our own
  `del /Q /F AutoCtrl_*.exe` — the native acks type 260 when cmd.exe STARTS
  (~7ms), NOT when the command finishes → the async del deleted the fresh
  engine. **No del, no nuke, no chrome.runtime.reload, no infinite retry**;
  taskkill only (processes, not files); write overwrites. mh_test A11-A13.
- **Zero proxy chain is MANDATORY**: manifest `path` MUST point at
  `AutoControlZero.exe` (proxy/launcher, spawns the engine with arg 152).
  No-Zero is impossible — the engine crashes standalone with a C++ exception.
- **Two engines at browser start / orphan after close (FIXED 2026-08-06)** —
  every `connectNative` spawns a NEW Zero→engine pair; when Chrome kills the
  SW without closing the pipe, Zero exits on EOF but its engine lingers.
  `__acKillOrphanEngines(gen)` at doHandshake start: wmic scan, `taskkill /F
  /PID` ONLY engines whose Zero parent is dead (live pairs of another browser
  are never touched). Reconnect guard `__acConnecting || (connected &&
  handshakeDone)` prevents duplicate hosts. mh_test B20.
- **Engine missing after Reinstall/Repair (FIXED 2026-08-07)** — the
  installer DELETES the engine exe; the once-per-session unpack flag blocked
  re-deploy → "Engine still missing after unpack — giving up".
  `__acEngineFileExists` (type 260 `if exist` + getStdout) disambiguates
  answer `2` ("missing OR still starting"); deploy re-runs when the file is
  gone, capped by `__acEngineDeploys` < 2. mh_test B21.
- **Config chain does not re-run after reconnect → hotkeys dead (FIXED
  2026-08-07)** — `configChainStarted` stayed true from the first handshake →
  no type 60/21 to the fresh engine. `proceedAfterFileCheck` now dispatches
  `nativeConfigReady` with `force: true` (bundle resets the guard; no-op on
  the first handshake). Affects ANY mid-SW reconnect. mh_test B22.
- **Fresh install must offer the INSTALL UI, not "Something went wrong"
  (FIXED 2026-08-07)** — `natHostInstalled` is storage-based (default false,
  async read + `_Eu` signal), persisted by the SW on connect, cleared by the
  proper uninstall flow (file30 `_ei`). `window._nd` always comes from the
  storage read. mh_test B23.
- **Auto-connect after native install (FIXED 2026-08-07)** — Chrome CACHES a
  failed connectNative per SW instance → the install UI pings type 920 every
  second; after 20 "not ready" answers with a DEAD port the SW sets
  `__acInstallAutoReload` in storage and reloads itself once; the fresh SW
  reopens the options page. mh_test B24.
- **No infinite reconnect loop after uninstall (FIXED 2026-08-07)** —
  auto-retry stops after 8 CONSECUTIVE failures (`errors` resets on every
  successful handshake); a temporarily-down host still reconnects when it
  returns. mh_test B25.
- **Install pane must NOT auto-close (FIXED 2026-08-07)** — the ping-loop
  starts ONLY after the user clicks Install; for the leftover-native case the
  shim dispatches `ac-install-done` when the SW reports connected AND
  `natHostInstalled` is in storage. mh_test B26.
- **Emergency Repair (final semantics, 2026-08-08 FIX 15)** — **type 55 is
  an ACK ONLY, it does NOT restart the engine** (verified: PID unchanged).
  The restart in MV2 came from `location.reload()` (background page → port
  drop → Zero exits on EOF → reconnect → fresh Zero+engine). MV3 equivalent:
  `__acEmergencyRestartNative` sets `__acRepairBadge` in storage →
  `chrome.runtime.reload()`; the FRESH SW shows " OK " after the reconnect
  succeeded. **NEVER hard-kill the engine (taskkill /F)** — TerminateProcess
  leaves WH_KEYBOARD_LL/WH_MOUSE_LL hooks DANGLING → no input for ~40s.
  No `__acRepairBadgePending`, no port-drop-only cycle, no 20s Error timer.
  Dead port (`a===55 && !port`) → openOptionsPage + "Error" badge (no stuck
  Wait). Menu item is created by the SW at startup (`__acCtxMenuOwned`); the
  `contextMenus.removeAll` patch re-creates it after config-chain runs; the
  bundle `_co` is the SINGLE onClicked handler (sw.js must NOT add its own).
  onDisconnect reads `void chrome.runtime.lastError` first. mh_test B25.
- **Fast wheel-spin tab skipping (FIXED 2026-08-08, FIX 17/18)** — the
  pos:next/prev target filters used the cached active tab `_Np`, refreshed
  only by onActivated ASYNC → fast triggers hit the stale tab and skipped
  steps. `_Ph` (file8) now sets `_Np=c` OPTIMISTICALLY before `tabs.update`
  AND `_Yp[].active` flags are synced (onActivated = source of truth).
  Bundle rebuilt. mh_test B27.
- **«On startup» trigger never fired (FIXED 2026-08-10)** — MV2 fired
  `_Wo(_Vs)` (`_Vs=30`) once per session after type 21; the port never did.
  sw.js `finishStartup` calls `_Wo(_Vs)` after `postMsg(21)` (once per
  session, `__acStartupEvtSent` + `noStupEvt` skip; no-op without a trigger
  on the event). After a repair reload the event DOES fire (in-memory flag) —
  acceptable.
- **`Unchecked runtime.lastError: Native host has exited` (FIXED 2026-08-08)**
  — onDisconnect now reads `void chrome.runtime.lastError` first. Both
  variants are EXPECTED (repair: we drop the host; no-native: connectNative
  fails).
- **Type 260 exitCode 259 = STATUS_STILL_ACTIVE (0x103)** — normal for
  taskkill (async kill), NOT a failure. The native resolves the 260 callback
  when cmd.exe STARTS, not when it finishes — never sequence file deletion
  via this callback.

### Capture mode (type 40) — stuck-capture watchdog (FIXED 2026-08-09)

- **ROOT CAUSE**: `postMsg()` built `{type, content: payload || {}}` — so
  `type 40 false` was sent as `{}` and the native never disabled capture
  (the MV2 original sent the raw false). FIX: coalesce only
  `null`/`undefined` payloads. The OFF now always reaches the native.
- While ANY capture mode is ON, the native streams raw type-760 and
  **suppresses ALL type-750 triggers** (hotkeys/gestures/RMB die).
- **Staged recovery in sw.js** (tracking in `postMsg()` — single choke point
  covering the page proxy, `_acNativeSend` and the bundle `_Lk`): any 750 or
  new toggle resets. Stage 0→1: raw-760 streak with no 750 and no recent
  toggle → re-send `type 40 false` TWICE (60ms apart — two independent
  modes). **Recording gate**: while `__acCaptureOn` is true (page armed an
  editor session) the page-open path NEVER heals — the editor's own OFF works
  now; the page-open path heals only when the page ALREADY sent its OFF yet
  760s still flow (thresholds ≥10 events, streak >8s, no toggle >15s). No
  page open: ≥6 events, streak >3s, no toggle >3s. **Page-gone release**: the
  last settings page closes while armed → immediate OFF (~1s). Stage 1→2:
  flood ~8s after the OFF → `port.disconnect()` → fresh Zero+engine. Stage
  2→3: `chrome.runtime.reload()` (proven heal). Normal mode produces ZERO
  760s — any streak is unambiguous. Log `[AC-CAPTURE]`. mh_test B33/B35.
- **Why no rate metric can detect recording**: each key = a down/up PAIR
  (vk + vk+1024, ~120-250ms apart) — human typing in the combo editor looks
  "dense" by every threshold. The `__acCaptureOn` flag is the ONLY reliable
  discriminator.

### Scripting engine (Run Script / ACtl)

- **file42 is a MANIFEST content script since round 8 (2026-08-06)** —
  `content_scripts: [{matches: ["<all_urls>"], js: ["file42.js"], run_at:
  "document_idle", all_frames: false}]` — Chrome guarantees EXACTLY ONE
  instance per top frame (re-injected on navigation, killed on extension
  reload). This killed the whole class of stale-instance/double-delivery
  bugs (rounds 4-6). n()'s on-demand injection remains as FALLBACK for
  chrome://, Web Store, file://, about:blank and post-reload recovery. The
  top-level guard is classic-script-safe (if-wrapper, NO top-level `return`):
  `if(!document.__acF42){...}` + a 10s `setInterval` heartbeat
  (`document.__acF42T`) + 20s staleness — a LIVE instance never looks dead to
  the guard; a truly dead one (extension reload) self-heals. ⚠
  `persistAcrossSessions` is NOT a valid manifest content_scripts key.
- **`x.__cur` context chain is LOAD-BEARING** — the scriptId branch sets it
  and MUST NOT restore it afterwards (SW dedup + `ACtl.on` registration read
  it); the funcCode branch restores in `finally`; its empty-chain fallback
  builds the context FROM THE MESSAGE (`scriptId/tabId/trigInstId+~random`),
  never `{}`. A restore here caused the 15/23 regression (round 3, reverted
  round 5). Unique `~`-suffixes per nested call prevent SW dedup-key
  collisions (rounds 5-6; `_A` appends the suffix IN the message so n()
  retries still dedup).
- **RUN SCRIPT acks IMMEDIATELY** (fire-and-forget) — the scriptId branch
  answers `{result:true}` at once and logs completion/errors; long scripts
  no longer stall the action queue. Nested calls (`runInTab`/`runInFrames`)
  still await the REAL result — `_A` marks the message `noWait:!0===t`
  (t===true only for the top-level RUN SCRIPT).
- **`ACtl` global in user scripts** — jsCode adds `var ACtl = __acActl;`
  inside the wrapper IIFE; file42 `FN` takes the ACtl param. Without it:
  ReferenceError in the USER_SCRIPT world.
- **`_Yh` (userAPI dispatcher)** — top-level `let` in file48, ASSIGNED by
  file77 → it is a GLOBAL LEXICAL binding, NOT a property of self/globalThis
  (`typeof self._Yh` is undefined). Reference it as a free variable. It
  returns a CALLBACK-STYLE runner, not a Promise — call
  `_Yh(msg, tab)(onOk, onErr)`. Same for `_us`/`_we`/`_cg` (file67
  generators).
- **userAPI must be handled EXACTLY ONCE** — the bundle's file48 `m()` is
  the single answering listener; sw.js must NOT handle `userAPI` (double
  execution overwrote the clipboard with "undefined"). mh_test asserts
  exactly 1 answering listener.
- **z-bundle results** (captureTab/on/getTabInfo/pubVar/...) are
  `{funcCode, args}` objects with a GENERATOR attached as Symbol.iterator —
  the file42 relay must evaluate them (`FN(funcCode)(...args)` + iterator
  loop) and convert iterables to plain arrays before postMessage
  (DataCloneError otherwise). `_Ii` is just `(...a)=>[].concat(...a)`.
- **XHR shim in the SW prelude** — fetch-backed; MUST expose
  `getResponseHeader`/`getAllResponseHeaders`/`responseURL` (file70 filename
  logic and saveURL need them).
- **`runInTab(func)` `[null]` (FIXED 2026-08-05)** — nested calls carried
  the PARENT `trigInstId` → dedup blocked them as the in-flight parent.
  `_A` appends `~`+random IN the message. Bundle rebuilt. Same class: per-
  frame keys in runInFrames.
- **`runInFrames` subframes (FIXED 2026-08-10)** — subframe file42 → FN →
  SW execUserFunc used `frameIds:[0]` → code ran N times but ALWAYS in the
  TOP frame. FIX: `sender.frameId` → `frameIds:[frameId]` (sw.js). First
  run in a fresh subframe: cold USER_SCRIPT world ~4-5s → `h.timeout` →
  file42 re-sends execUserFunc ONCE after 6s (B38). Per-frame `~f`+random
  suffixes when `a.frmCBId` so every frame executes (B39). Remaining edge:
  `ACtl.runInPageCtx` INSIDE a runInFrames func still routes to frame 0
  (TODO, rare).
- **`runInPageCtx(func)` return value (FIXED 2026-08-06, round 16)** — MV3
  world isolation broke the original call-by-name mechanism; replaced by a
  single self-contained proxy (`/*AC-MV3-PROXY*/`) answering
  `{response,funcName}` from the same context. ⚠ jsCode is a TEMPLATE
  LITERAL: ALL backslashes in regexes/strings must be DOUBLED (`\\s`, `\\\"`)
  or they silently collapse (node --check won't catch it).
- **`runInPageCtx` inside `runInFrames` ran in frame 0 (FIXED 2026-08-12)** —
  the SW's `execMainWorld` (runInPageCtx bridge) passed `{}` to
  `__acInjectCode` → `userScripts.execute` defaulted to the TOP frame. Now:
  `execMainWorld` uses `sender.frameId` (`injectDetails = {frameIds:[frameId]}`)
  and `__acInjectCode` (sw_prelude) supports `details.frameIds` — frameIds
  and allFrames are MUTUALLY EXCLUSIVE in the target (`buildTarget()`). The
  return path was already frame-correct (file42 posts `acMainWorldRes` to
  its own window). Bundle rebuilt. mh_test B46.
- **`import` / `getFile('module')` (FIXED rounds 12-13)** —
  `userScripts.configureWorld({csp: "script-src 'self' 'wasm-unsafe-eval'
  blob: data:; object-src 'self'"})` + module namespace objects stashed on
  `window` (`__acmod_*`) and transported as a marker.
- **`switchState` / storage wipe (FIXED round 18)** — `_Qj` (single
  storage-load choke point) must NEVER fabricate keys: a fabricated
  `customEntities={}` was written back by `_Mi`'s batched write and WIPED
  all scripts/triggers/gestures after the first `ACtl.var`/`pubVar`. Patch
  only fills `binSwtch:[]` INSIDE an existing `customEntities`. Test A14.
- **First script run on a fresh tab takes +4-5s** — one-time Chrome
  userScripts world initialization (per tab). Pre-warming was tried and
  REMOVED (Chrome serializes executes per tab — warmup only blocked the real
  calls). n()'s 6000ms fallback absorbs the cost — first run slower,
  everything after instant. Do NOT re-add warmup.
- **Overlapping script runs (CLOSED 2026-08-09 as not reproducible)** — the
  feared dedup clash does NOT happen (unique ~suffixes). Residual: an
  attribution leak for targetTabs-dependent APIs under heavy overlap (rare;
  plan documented in the archive). The API test must run SEQUENTIALLY (the
  shared `__apitest` key is a test artifact).
- **Protected pages** (chrome://, Web Store, chrome-extension://, devtools,
  view-source:) — Chrome blocks ALL injection there (identical in MV2 — not
  a port regression). UX fix: prelude helpers
  (`__acIsProtectedPage`/`__acProtectedMsg`/`__acNotifyProtected`), the
  tabs.executeScript shim pre-checks the tab URL (instant reject instead of
  the 6s timeout), execUserFunc fails fast, hint via chrome.notifications
  (unique id per call, 1.5s throttle). mh_test B36.
- **F()-path diagnostics** — `[AC-F42] listener ret/…`, `[AC-F42] funcCode
  THREW: …`, `[AC-DLV-F] why=…` (`cb-ok`/`lasterr:…`/`timeout`/`throw:…`/
  `cb-undef|cb-val|cb-null`). Read `why=` + `h=` together:
  `lasterr:Could not establish connection` = no listener; `cb-ok` + `h=UNDEF`
  = listener answered sync; `timeout` = page busy/slow.

### Triggers & actions

- **14/34 trigger pair** — the native sends TWO trigger ids per hotkey press
  (~100-200ms apart); they may be duplicates or INDEPENDENT actions. The
  companion is dropped ONLY when the action signature matches (300ms window,
  different id).
- **Action-queue watchdog** — hook the bundle's `__acLog` DIRECTLY
  (`t === 'OK'` is the exact completion marker; `__acLog` is a top-level
  function declaration → classic-script global, reassignment from sw.js is
  seen by every call site). ⚠ Do NOT hook `console.warn` — the async logging
  patch replaces it and the hook dies silently (that caused spurious
  "Queue stuck" force-shifts).
- **RCM/LCM bug (SOLVED v6+v7)** — gesture presets compile `block:true`
  under key 2 AND key 1026 → the native swallowed the RCM-up → LCM read as a
  rocker combo. v6 `STRIP_RBTN_BLOCK` (soften block:true→false for both
  keys) + v7 `RBTN-ESC` (synthetic Esc after a gesture closes the stray
  context menu). Details: `Docs/archive/RIGHT-CLICK-ISSUE.md`.
- **Hover regions broken in Chrome 148+** ("Browser tab", "close button",
  "speaker icon", "new tab", "menu item") — native a11y hit-test regression,
  affects MV2 AND MV3 (NOT a port loss, NO extension-side fix exists; a
  TAB-GATE workaround was tried and ROLLED BACK). Use region 4 (Title area)
  for top-row triggers; the UI marks the broken options.

### UI / settings

- **Toolbar icon click** — the bundle file62_mv3.js is the SINGLE
  `onClicked` handler (trigger if `brwrAction.trigActId` is assigned —
  legacy storage key, no UI writes it — else settings page). sw.js must NOT
  add its own listener (double behavior). mh_test B25.
- **Toolbar button icons (FIXED 2026-08-08)** — `_Pk()` (push btnProps)
  runs on EVERY config-chain completion (`configLoaded`), and all 5 MV3
  buttons retry `TBBtnInit` (2s × 30) via onStartup/onInstalled. Without
  both sides, buttons keep default icons until clicked. mh_test B29.
- **First open of the custom tab menu shows empty icons (FIXED 2026-08-08)**
  — the favicon warmup must cache BOTH keys: the raw `tab.favIconUrl` AND
  `"chrome://favicon/" + (tab.url||tab.pendingUrl)` (the menu asks for the
  latter; a key mismatch made the warmup useless). Delayed sweeps at SW start
  (1500/4000/9000ms) + re-sweep on configLoaded + warm on onCreated/onUpdated.
  mh_test B30.
- **`_if` raw-assign trap** — `storage.local.customEntities` is a pair-array;
  NEVER assign `_if = r.customEntities` directly (the UI expects the
  Map-like object — list renders empty). Use `_6s({}, cb)`. The "Not leader"
  page branch populates `_if` via `_6s` from storage.
- **Live config rebuild** — the SW listens to `storage.onChanged` (debounced
  400ms) → `_Gf({}, cb)` → type 60: trigger/script/action edits apply
  without an extension restart. Log: `storage.local changed → rebuilding
  in-SW config (_Gf)`.
- **Scripts lost after reload** — `_Sp` (settings import) did
  `storage.local.clear()` + write; fixed: merge old `customEntities`
  missing from the imported file.
- **Storage vs file** — the settings file (.acs/.dat) is written by `_qj`
  on storage change (only when localSync `_uy` is on). File check (type 10)
  returning 0 = no file → no import.
- **mv3_shim double-map** — the SW already returns mapped results; do NOT
  `result.map(r => r.result)` again (crashes on null items).
- **Mojibake in UI** — see Encoding rules (`<meta charset="utf-8">`).
- **Toasts vs badge** — `_Cr` is the icon BADGE (works in the SW). The
  file71.html floating popups WORK from the SW since 2026-08-12 (FEATURES-MV3.md
  §7-15): the shim overwrites `window._Fo` (file70's MV2 version used
  `chrome.extension.getViews` — absent in MV3) with `__acMv3Popup`
  (windows.create with a `?runId=N` URL) + **content-bridge**: `file71_bridge.js`
  (loaded by file71.html) requests its content via
  `chrome.runtime.sendMessage({type:"acPopupContent"})` → sw.js →
  `__acPopupGetContent` (shim), renders, auto-sizes, and reports the button
  via `{type:"acPopupResult"}` → sw.js → `__acResolvePopup`; `<key>N</key>`
  names are pre-converted via `_Je` IN the SW (the MV2 onloaded path is
  skipped). ⚠ **NEVER use scripting.executeScript into the popup tab** —
  Chrome refuses injection into chrome-extension:// pages ("Extension
  manifest must request permission to access this host", user VM
  2026-08-12: the window flashed empty). mh_test B40/B41. z[800] no-hook
  keeps chrome.notifications by design.
- **Emergency-repair menu item vanishing (FIXED 2026-08-12)** — TWO causes:
  (a) the `contextMenus.removeAll` patch recreated reloadExtn via the PATCHED
  `create()`, which returns 0 for that id while `__acCtxMenuOwned`
  (duplicate filter) → the recreation was silently dropped → the item
  vanished after every config-chain run. The patch now uses the ORIGINAL
  create (`origCtxCreate`). (b) the settings page (non-leader) called file47
  `_nk()` → UNPATCHED `chrome.contextMenus.removeAll` wiped the SW's item,
  and its `create({contexts:["browser_action"]})` is INVALID in MV3 → the
  item never came back. The shim stubs `window._nk = function(){}` outside
  the SW (importScripts check) — the SW owns the menu exclusively. B25 + B43
  assert both.
- **Repair diagnostics survive the SW reload (FIXED 2026-08-12, §7-15)** —
  MV2 kept `showNotif`/`diagnostics` in the background page's real
  localStorage; the MV3 in-memory shim dies with `chrome.runtime.reload()`
  → the fresh SW's file34 `_nt("showNotif")` branch never ran. `sw.js`
  `__acEmergencyRestartNative` now reads the one-shot flags via `_j` BEFORE
  the reload and persists `__acRepairDiag` to `chrome.storage.local`;
  `proceedAfterFileCheck` (fresh SW) shows `_Kg` (stuck keys + advice) or
  `_Ht` (foreign profile + advice) — MV2 semantics. The stuck-keys list is
  REAL (user-verified 2026-08-12: keys held down at repair time are listed).
- **file:// URL conditions (FIXED 2026-08-10)** — the prelude passes the
  REAL `chrome.extension.isAllowedFileSchemeAccess` through (it EXISTS in
  the MV3 SW; the old shim hardcoded false) → file:// tabs are script
  targets only when the "Allow access to file URLs" toggle is ON (MV2
  parity). The gate is read ONCE per SW load — reload the extension after
  toggling. mh_test A4.

### Actions (misc)

- **Play audio (FIXED 2026-08-09)** — the original lazy-loads file53.js via
  a script tag (a NO-OP in the SW) → the action hung the chain AND the
  queue; file53 also needs AudioContext/speechSynthesis (no worker APIs).
  FIX: playAudio is intercepted at the LOOKUP — file37 `_rf` reads every
  action through `_w(name, params)` (a top-level function declaration of the
  imported bundle → writable global); sw.js wraps `_w` for `"playAudio"`
  with a runner that completes the action IMMEDIATELY (MV2 semantics) and
  sends `{cmd:"playAudio", tabGroups, params, runId}`; the offscreen
  document lazy-loads file67.js + polyfills + the REAL file53.js and calls
  `_lh(params, tabGroups, runId)`. ⚠ `_Du` is DEEP-FROZEN (`_Oo(_Du);`) —
  patching `_Du.action.playAudio.value` THROWS. Voice TEXT TEMPLATES are
  pre-expanded IN THE SW; the offscreen gets the final plain string +
  `usesTabs:false`. Offscreen→native bridge `{cmd:"acPlayNative"}` (type
  255 via bundle `_If` — chunked reassembly is bundle-internal; type 294
  raw). POLYFILL GOTCHAS: `_we` is a `const` (lexical — `window._we`
  undefined); `_ai` must return a callback RUNNER; `_If` failure resolves
  `{content:""}`; `_od=294` is a free variable (file56 constant). mh_test
  A5/A5b; sims: `Test/_ac_audio_smoke.js`, `Test/_ac_voice_sim.js`.
- **Save URL notif/copy (FIXED 2026-08-09)** — MV2 spoofed the Referer via
  blocking webRequest (unavailable in MV3) → every notif/copy save failed
  with httpError. FIX: file49 `H()` installs a **declarativeNetRequest
  SESSION rule** (`modifyHeaders` → set Referer) before the fetch, removed
  in `finally` — DNR rules DO apply to the extension's own SW fetch.
  Permission `declarativeNetRequestWithHostAccess` (no new install warning).
  Follow-ups: notifications reject `data:` iconUrl → real resource
  (`AutoCtrl/logo32.png`), failures degrade to a silent save; `dwnlApi` with
  an ABSOLUTE folder routes to the native write path (chrome.downloads
  filename is Downloads-relative); the final "SAVED" notification must be
  CREATED when the initial create failed (no short-circuit). mh_test A6.
- **z[800] error classification (FIXED 2026-08-10)** — full MV2 `E()` port
  in mv3_native_shim.js z[800]: no-hook-notice → `_uf` counter +
  **chrome.notifications with buttons** ("Don't show again"/"Keep showing";
  `nhCount` resets when shown; short message text — Windows toasts truncate
  ~130 chars); invalidExtId → install-age gate; APDL → `_r` flag (idle
  type-790 ping stops); NH-error 0xC0000005 → `_uf("segFault")`; default →
  telemetry. GOTCHAS: the monitor map `_Zw` MUST be populated at SW startup
  (`sendMonitorInfo` → `_Sf(() => {})`) or ALL popups/monitor-based actions
  crash ("workArea of undefined"); `_Fo` falls back to a default rect;
  `nhBusy` resets on button/close/failure; `noHookConflictMsg` lives in
  in-memory localStorage → the notice can re-arm after an SW restart (rare,
  acceptable). mh_test A2b.
- **Save URL audio method** — type 294 system sounds need "Allow access to
  file URLs" (same as MV2).

### Shims & globals

- **mv3_native_shim.js is an IIFE — NOT everything is global!** Exported to
  window: `_Lk _Vy _0d _Uj _ha _Yi _cu _Sw _Xg _2y z`. NOT exported
  (IIFE-local): `_trigActList`, `pendingCallbacks`, `chunkedDataStore`,
  `gestureState`, `configChainStarted`, `findTriggerByKey`,
  `findTriggerByGesture`, `executeTrigger`. Always check exports before
  touching shim state from sw.js (a ReferenceError there fails SILENTLY as
  an inactive gate).
- **Free-variable access from sw.js** — bundle top-level `let`/`var`/function
  declarations (`_Yh`, `_7o`, `_Yp`, `_Qj`, `_Sf`, `_w`, `__acLog`, ...) are
  shared lexical env globals, accessible as free variables from sw.js
  (importScripts shares the SW's global lexical env) — but NOT as
  `self.X` properties (lexical bindings are not object properties).
- **file37.js is minified** — when wrapping `if(a)a:if(...)` into
  `if(a){...a:if(...)}` add the extra closing brace (bundle compile error
  otherwise).
- **PS console logs** — SW logs vs page logs are DIFFERENT consoles (SW:
  chrome://extensions → service worker link; page: F12 on the settings tab).
- **ID stability** — `postWithCb` derives the callback hash `l` from
  `chrome.runtime.id` substring.

## Documentation rules (IMPORTANT — the code is obfuscated)

This codebase is minified/obfuscated (`_qe`, `_md`, `_6s`, `_wj`, ...). Any
logic that is uncovered, changed, or worked around MUST be documented —
otherwise the next session starts from zero. Concretely:

1. **New findings go into the docs immediately** — do not postpone "until it
   stabilizes": add to `Docs/NATIVE_PROTOCOL.md` (protocol), `Docs/DECODE.md`
   (deobfuscation map — the file `/memories/repo/deobfuscation-map.md` is
   also a good place), `Docs/FEATURES-MV3.md` (feature status & port gaps —
   single source of truth; broken items are tracked in §7 with
   section links) or `AGENTS.md` (gotchas), whichever fits.
1b. **Keep `README.md` (the install guide) current** — it is user-facing and
   must stay in sync with reality: extension toggles and their names
   (chrome://extensions → Details → "Allow user scripts" / "Allow access to
   file URLs"), the manual native-install steps (`AutoControl_native\` →
   `%UserProfile%\AppData\Local\AutoControl`), and the verification
   checklist. Whenever the native-install TODO is fixed or any toggle/path
   changes, update README.md in the same change.
2. **Every fix ships with a doc line** — at minimum a bullet in the relevant
   doc + a session-memory note (`/memories/session/autocontrol-mv3.md`):
   symptom → root cause → fix → rebuild status.
3. **Deobfuscation map**: when you decode a symbol/function, record it
   (`_qe=1` LMB, `_md=2` RMB, `_4e=60` config, `_zs` reads script code from
   `_if`, `_Mi` fires `_Gu`/`_B` subscriptions after storage write, etc.).
4. **Protocol changes**: any new/changed native message type, field, or
   handshake step goes into `Docs/NATIVE_PROTOCOL.md` with the exact wire
   format.
5. **Bundle rebuild notes**: state the bundle size after each rebuild in the
   session memory (quick sanity: marker present? size changed?).
6. **🔴 HIGH PRIORITY — deobfuscation & protocol DISCOVERIES and
   INACCURACY CORRECTIONS are documented THE MOMENT they are made — not only
   changes, and not only in code-changing sessions.** A session that decoded
   or observed something new (or spotted a wrong/outdated doc entry) but
   ended without updating the map is INCOMPLETE. Every session MUST land its
   findings AND fix any inaccuracies before it ends:
   - new decoded symbols/functions → `Docs/DECODE.md` (symbol tables) —
     including CORRECTIONS of wrong entries (e.g. `_9k` is
     `localStorage.setItem/removeItem`, NOT `chrome.storage.local.set`);
   - new semantic facts about the native (message meaning, side effects,
     lifecycle) → `Docs/NATIVE_PROTOCOL.md` with the exact wire format.
   Example of a MUST-document finding: "type 55 does NOT restart the engine —
   it is an ACK; the MV2 restart came from the background-page reload (port
   drop → Zero exit on EOF → fresh Zero spawns a fresh engine)" is now
   NATIVE_PROTOCOL §18, and `_co`/`_ze`/`_nk`/`_Cr`/`_j`/`_nt`/`_2u` +
   55/451 are in DECODE.md.

## Where to look for docs

- Content script CSP / isolated worlds:
  <https://developer.chrome.com/docs/extensions/develop/concepts/content-scripts>
- userScripts API:
  <https://developer.chrome.com/docs/extensions/reference/api/userScripts>
- Offscreen documents:
  <https://developer.chrome.com/docs/extensions/reference/api/offscreen>
- Sandbox pages:
  <https://developer.chrome.com/docs/extensions/develop/concepts/declare-permissions#sandbox>
- `scripting.executeScript` (no matchAboutBlank):
  <https://developer.chrome.com/docs/extensions/reference/api/scripting>
- This repo's own docs: `README.md` (install guide — user-facing),
  `Docs/NATIVE_PROTOCOL.md`, `Docs/DECODE.md`, `Docs/archive/RIGHT-CLICK-ISSUE.md`,
  `Docs/FEATURES-MV3.md`, `CHANGELOG.md`.

## Native protocol (short)

Native host `hrich.autocontrol`; messages `{type, content, callback}`,
callback `e+l` (l from ext id), echo reply type 710. Key types: 10=file check,
20=init, 21=startup, 60=config (mapKey=keyId+22025), 67=monitors, 72=switch
states, 300=SendInput, 750=trigger, 760=raw gesture, 905=keepalive, 920=ping.
Details: `Docs/NATIVE_PROTOCOL.md`.
