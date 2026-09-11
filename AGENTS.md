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

## CDP debugging (Canary with --remote-debugging-port)

- **Launching the debug browser — ALWAYS ask the user which Chrome
  variant they want** (e.g. stable `chrome.exe` vs SxS/Canary
  `"...\Chrome SxS\Application\chrome.exe"` — the user knows which
  profile carries the test extension). The reference launch (Canary SxS,
  this repo's default):
  ```powershell
  Start-Process "$env:LOCALAPPDATA\Google\Chrome SxS\Application\chrome.exe" `
    -ArgumentList '--remote-debugging-port=9223', `
                 '--user-data-dir=C:\Users\alxbr\AppData\Local\Google\Chrome SxS\User Data CDP', `
                 '--lang=en-US'
  ```
  - **port**: `9223` (CDP endpoint: `http://127.0.0.1:9223/json/version`).
  - **profile dir**: the junction `...\Chrome SxS\User Data CDP` → the REAL
    `...\Chrome SxS\User Data` (Chrome 136+ silently ignores
    `--remote-debugging-port` without a NON-DEFAULT `--user-data-dir`).
    The extension/toggles survive (same directory).
  - **`--lang=en-US`**: fixes the chrome://extensions UI language so the
    card's reload button is always "Reload" (test scripts match that
    label; without it the label is localized to the OS UI language and
    `cdp_ext_reload.js` fails to find the button).
  - Before launching: stop any running instance of that variant
    (`Get-Process chrome | Where-Object { $_.Path -like '*Chrome SxS*' } |
    Stop-Process -Force`) — an already-running process without the flags
    wins the profile lock and the new flags are ignored.
  - Verify the endpoint answers before running CDP scripts:
    `curl.exe -s -m 5 http://127.0.0.1:9223/json/version`.
- **Chrome 136+ gotcha**: `--remote-debugging-port=N` is SILENTLY IGNORED
  unless a NON-DEFAULT `--user-data-dir` is also passed — passing the default
  profile path counts as "not specified" (verified on Chrome 150). To debug
  the REAL profile: create a junction to it and pass the junction path:
  `New-Item -ItemType Junction -Path "...\Chrome SxS\User Data CDP" -Target "...\Chrome SxS\User Data"`
  → launch `chrome.exe --remote-debugging-port=9223 "--user-data-dir=...\User Data CDP"`.
  The extension/toggles survive (same directory). Also: PS `Start-Process
  -ArgumentList` does NOT quote args — a path with spaces gets split into
  URL args (launched a broken instance with the stable profile once).
- **SW internals are IIFE-local**: `port`/`connected`/`handshakeDone` in
  sw.js are NOT reachable from Runtime.evaluate (global scope); the bundle's
  `var`-declared globals (`_Yp` tab cache, `_if` customEntities store, `_ek`
  enabled-trigger action map, `_Qj`, `_K`, `_4p`, `_mh`, `_Gf`, `_Lk`, `_9i`,
  `_bd`, `_bj`) ARE. `_Yp` = TAB CACHE keyed by tabId — NOT the config map!
  The type-60 payload (`m.map`, `m.list`) is built by
  `_mh(trigActList, mouseGest, advOpts)` (`_no`), sent via `_Lk(_4e=60, c)`
  → sw.js postMsg.
- **Config-map keys** (mapKey = keyId + 22025): 22027 = key 2 (RMB-down,
  block:true = gesture start), 23051 = key 1026 (RMB-up, softened), 22034 =
  key 9 (Tab; Ctrl+Tab entries have evtId 6145/delay 400/menuNum 7), 23058 =
  1033 (Tab-up), 28170 = 6145 (Tab held), 23211/23212 = keys 186/187.
- **Diagnostic scripts** (`Test/cdp_*.js`, Node ≥21, run against a live
  Canary): `cdp_storage_dump.js` (storage + `_ek`/`_if`/`_Yp` dump),
  `cdp_import_sim.js` (runs the `_ja` merge pipeline in-memory with a real
  .acs file — NO save; proves `{}.add(_2d,data)`→`_Qj`→`_K`→`_4p`→`_bj`
  preserves trigActList), `cdp_sw_state.js`, `cdp_native_check.js` (ping 920
  via `_Lk`), `cdp_lk_trace.js` (wraps `_Lk` to capture type-60 payloads;
  saves the original in `window.__acOrigLk`), `cdp_unwrap.js` (restores
  `__acOrigLk` or the `_acNativeSend` alias), `cdp_menu_state.js` (type 185
  menu state query), `cdp_action_probe2.js` + `_ac_keypress2.ps1` (real OS
  key injection via `keybd_event` — passes through the native LL hooks;
  wraps `_w` to trace action execution). 2026-08-30 additions:
  `cdp_keytest2.js` (key-hold test: `hold 700` = Ctrl+Tab hold, `quick` =
  tap, `esc` = Esc — captures SW console + `__acLogBuf`; THE regression
  test for the `.in` polyfill / menu-state negate fix), `cdp_payload_dump.js`
  (rebuilds the type-60 payload in-memory via `_Gf`→`_mh` and dumps the
  compiled entries per mapKey — check `negate` on `{type:13,menuNum:7}`
  preconds; writes `%TEMP%\ac_payload.json`; ⚠ it DOES send a live type-60
  via `_no`), `cdp_hold_menu.js` (holds
  Ctrl+Tab 4s and queries the native menu state via `_Lk(175,null)` —
  `true` = menu open while holding), `cdp_negate_probe.js` (probe
  `_mh`/`sc()`/`keep()` with a synthetic negate:true menuState trigger),
  `cdp_in_probe.js` (runtime probe of `Object.prototype.in` — scalar AND
  array forms), `cdp_full_trace.js` (wraps console + `_Lk`, injects a key
  hold, dumps everything), `cdp_logbuf.js` (dump `__acLogBuf` with an
  optional regex filter — NOTE: the SW's own logs bypass `console.log`
  wrappers via `__acOrigConsole`, and `Runtime.consoleAPICalled` REPLAYS
  the session backlog on attach — a capture shows history, not only live
  events; use hooks or side effects (pin state, storage) to distinguish),
  `cdp_capture_state.js` (capture flags +
  AC-CAPTURE log lines), `cdp_bundle_sync.js` (source↔bundle marker check
  after rebuilds), `cdp_reload.js` (SW `chrome.runtime.reload()`),
  `cdp_exts.js`/`cdp_msg_watch.js`/`cdp_native_probe.js`/
  `cdp_marker.js`/`cdp_keytest.js`/`cdp_restore_lk.js`/
  `cdp_rebuild_capture.js`/`cdp_fresh_trigger_test.js` (older one-offs —
  superseded by the above, harmless to keep), `_ac_tabtap.ps1` (single Tab
  tap for menu-mark moves), `_ac_keypress.ps1` (older keypress injector).
  2026-08-30 issue-#1 additions: `cdp_rbtn_block_test.js` (compiles an RMB
  block:2 trigger in-memory, shows the strip effect on keys 2/1026),
  `cdp_rbtn_gesture_test.js` (same + rightButton gesture preset — verifies
  the selective-strip discriminator: only mouseGestState-gated blocks are
  softened), `cdp_rmb_probe.js` (installs `contextmenu` listeners on the
  page, injects a REAL OS RMB/LMB via `_ac_mouse.ps1`, reports whether the
  button reached Chrome — 0 events = native swallowed it = no menu),
  `cdp_swlog_rmb.js` (captures SW console while injecting a click),
  `cdp_ctxmenu_watch.js` (event-listener watcher), `cdp_eval.js` (generic
  SW eval helper), `cdp_import_live.js` (imports an .acs via the REAL
  `window._ja` path), `cdp_ext_reload.js` (reloads the unpacked extension
  via chrome://extensions UI — pierces the shadow DOM; the card's reload
  button is matched by its "Reload" label — launch Chrome with `--lang=en-US`
  so the UI language is fixed),
  `cdp_cleanup_test.js` (restores the test trigger + unwraps `_Lk`),
  `cdp_break_postmsg.js` (Debugger breakpoint in postMsg to capture the
  real call stack), `_ac_mouse.ps1` (REAL OS mouse injection via
  `mouse_event` — rmb/lmb/move; foregrounds the SxS window with the
  ALT-hold unlock trick and VERIFIES the foreground), `_ac_fgcheck.ps1`
  (reports which window holds the foreground).
- **⚠ NEVER `delete window._Lk`** — the shim's `_Lk` lives inside its IIFE
  and `window._Lk` is the ONLY global reference; deleting it breaks
  `closeMenu`/`moveSelectMark` (free-variable `_Lk` → ReferenceError → the
  Tab switcher menu opens but never closes, mark never moves) until the SW
  restarts (CDP attaches keep the SW alive!). Restore with
  `window._Lk = (a,b,c,g) => _acNativeSend(a,b,c,g)` (exactly the shim's SW
  behavior). Verified 2026-08-30 the hard way. Action runners take functions
  from the DEEP-FROZEN `_Du` map — wrapping `window._Oa`/`_eu` does NOT
  intercept; wrap `_w` (the lookup choke point) instead. Native-executed
  actions (moveSelectMark) produce NO `[AC-ACT] ACT` log; extension-executed
  ones do. Type 185 (menu state) returns `{hilited, hovered, marked}` item
  indices; type 175 closes the menu; type 170 opens it (menuData).
- **Import pipeline verified end-to-end (2026-08-30)**: with `! tabs test.acs`
  (triggers 116-122 + section 6 + menuSpec 7) storage ends with all 6
  triggers, `_ek` compiles 116-122, type 60 reaches the native with key 9
  (Tab) + menuNum 7 entries, native answers ping 920. The earlier
  "import left trigActList empty" reports were NOT reproducible — the
  pipeline is sound; suspect stale pre-fix builds / SFE View boot race /
  running storage scripts in the RUN SCRIPT sandbox (no `chrome` there —
  use the settings-page F12 console instead).

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
  (`__dirname`). Current: 92 pass / 0 gaps / 0 FAIL.
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
  **Stale-armed release** (`AC_CAPTURE_STALE_ARMED_MS` = 5 min): an armed
  capture with NO 750 for 5 min (760 handler + a 15s sweep) is released —
  the page's own OFF never came (page died/reloaded / editor abandoned).
  60s was TOO AGGRESSIVE (user 2026-08-30 D-15): the gesture tester
  (file30) re-arms ONLY on a window focus event, so a >60s pause
  mid-testing released the capture and the next draw was NOT recorded
  ("line draws, gesture not recorded" — first draw fine, after a pause
  nothing). 5 min keeps the heal for genuinely stuck sessions (the
  original stuck-capture episodes lasted hours) without cutting a
  thinking pause.
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
- **RCM/LCM bug (SOLVED v6+v7, updated 2026-08-30)**: gesture presets
  compile `block:true` under key 2 AND key 1026 → the native swallowed the
  RCM-up → the next left click was read as a rocker combo. v6
  `STRIP_RBTN_BLOCK` + v7 `RBTN-ESC` (synthetic Esc after a gesture closes
  the stray context menu). v6 originally softened BOTH keys — that KILLED
  mouse gestures (block on key 2 RMB-DOWN is what makes the native
  intercept the right button and start gesture recognition).
  **UPDATE (2026-08-30, issue #1 "right click menu override not working")**:
  the strip used to soften EVERY block:true under key 1026 — including the
  USER's own right-click override entry (block mode "up" compiles
  `1026→{type:0,block:true,preconds:[actionDone]}` — the thing that makes
  the native swallow the RMB release so the context menu stays closed).
  Softening it let the context menu open after every right-click action
  ("action fires but the menu appears"). The strip is now SELECTIVE:
  soften ONLY the gesture-preset entries — recognizable by their
  mouseGestState precond (`PRECOND_MOUSE_GEST_STATE=11`) — and preserve
  the user's actionDone-gated block entries. VERIFIED LIVE (real OS RMB
  injection via `Test/_ac_mouse.ps1` + page `contextmenu` event probe):
  RMB → NO menu (page gets zero events), trigger fires, LMB after RMB
  works, no spontaneous re-fires (16s idle), gestures' 1026 block still
  softened ("softened 1 gesture block entries"). The RCM/LCM stick is
  caused by the swallowed right-button-UP (1026), not the DOWN — soften
  ONLY the gesture-generated 1026 blocks and leave key 2's block intact.
  mh_test B50 pins the selective behavior (compiles the issue trigger +
  gesture preset via the REAL `_mh` and asserts user block:up preserved /
  gesture block softened — needs the `.in` re-patch first, the vm bundle
  is sloppy like the SW).
  ⚠ The mouseOver (hover-region) preconds do NOT gate triggers on Chrome
  150 AT ALL (verified live 2026-08-30: region 3 "Web page" and region 4
  "Title area" both fire everywhere — native a11y hit-test regression, ALL
  regions, not just the top-row ones; same native in MV2 — the user's
  Edge/MV2 test works because Edge's a11y differs). No extension-side
  workaround exists (no cursor-position API). Do NOT promise hover
  conditions as working on Chrome 148+.
- **Toggle actions (pin/mute) missed clicks (FIXED 2026-08-30, B52)** —
  "right-btn => pin tab toggles only every 2-5 clicks". ROOT CAUSE: `_9f`
  (file8, pinTabs) read `_Yp[c].pinned` — the SW tab cache, refreshed ONLY
  by the async window enum `_Fu`, which `_Rf` gates behind a 1500ms cache
  (`__acEnumCacheMs`). Clicks closer than ~1.5s after the last enum read a
  STALE pinned state → toggled the tab to the SAME value (no-op) →
  "working-click, dead-click" pairs (verified live: 16 user clicks → 16
  750s + 32 `_w` lookups but only 3-4 visible toggles; update log showed
  true,true,false,false,true — pairs of no-ops). FIX: toggle mode now
  reads the FRESH state via `chrome.tabs.get` before `tabs.update` (same
  for `_Rh`/muteTabs). Verified: 12/12 rapid clicks (400ms apart) all
  toggle; LMB after RMB passes. ⚠ Bundle build list: file77.js MUST be
  AFTER file48.js (the sw.js comment list is authoritative now — the old
  comment missed file77 and a rebuild dropped it → the B-tests failed).
- **Open URL + Switch to right tab skipped the new tab (FIXED 2026-09-11,
  B54)** — "opens the URL to the right, then jumps one extra tab". ROOT
  CAUSE: `_Rf`'s 1500ms `windows.getAll` cache. `loadUrls` `tabs.create`
  completes and `_Zf` writes `_Yp`, but `_Gk` / `_cd[w].tabs` (the ordered
  lists `rightTabWrap` → `_xy(pos:"next")` uses) are only rebuilt by `_Fu`.
  The next action's `_Rf` saw a WARM cache and skipped the enum → "next"
  of the current tab was still the OLD right neighbor. FIX: structural
  tab/window events (`onCreated`/`onRemoved`/`onMoved`/`onAttached`,
  window create/remove, plus `_6a`/`_3g` create callbacks) set
  `__acEnumDirty` so the next `_Rf` re-enums even inside the cache window.
  Wheel-spin switchRight (no strip change) still hits the 1500ms cache.
  mh_test B54. Bundle rebuild required (file37 + file62_mv3 + file34_mv3).
- **Hover regions broken in Chrome 148+** (ALL regions, verified 2026-08-30
  on Chrome 150: "Web page" and "Title area" included — the native a11y
  hit-test regression ignores `{type:14}` mouseOver preconds entirely;
  affects MV2 AND MV3, NOT a port loss, NO extension-side fix exists — no
  cursor-position API). Previously only the top-row regions ("Browser tab",
  "close button", "speaker icon", "new tab", "menu item") were known
  broken; testing shows the gate never fires regardless of region. Do NOT
  use hover conditions in test triggers on Chrome 148+; the UI still offers
  them (they worked pre-148).

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
- **Settings page invisible on first open after reload (FIXED 2026-08-30)** —
  main.html is hidden until n() (file2) finishes its boot chain (_Hu imports
  + _Eu nativeConnected + SW ping); right after an extension reload the SW
  is still starting and the boot can stall → blank hidden tab even for a
  PLAIN open (not just SFE import). Safety net in mv3_shim (loads first):
  after 8s, if `<html>` still lacks `visible`, force
  `addClass("visible") + display:block` (idempotent).
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
- **`Object.prototype.in` polyfill — BOTH call forms are load-bearing
  (FIXED 2026-08-30)** — file67 defines `.in` as `_Xt(this,...a)` (strict
  `===`); the bundle is SLOPPY (no `'use strict'` at the top of the
  concatenation) → `this` gets BOXED on primitives → `'x'.in('x')` was
  FALSE → sw.js re-patched `.in` with unboxing + `a.indexOf(t)`. That broke
  the ARRAY idiom `x.in([...])` that `keep()` (file25 config compiler)
  relies on → `keep("negate","oper")` deleted EVERY property → menuState
  `negate:true` was stripped → every Ctrl+Tab trigger compiled as "menu 7
  IS open" → openMenu never fired, the tab-switcher list never opened after
  a reload (user 2026-08-30). The patch MUST flatten args one level
  (`[].concat(...a)`) AND unbox AND strict-compare — mh_test B51 pins it.
  When touching this patch, re-run the key hold test
  (`Test/cdp_keytest2.js hold 700` → menu state 175 must return `true`
  while holding).
- **file37.js is minified** — when wrapping `if(a)a:if(...)` into
  `if(a){...a:if(...)}` add the extra closing brace (bundle compile error
  otherwise).
- **PS console logs** — SW logs vs page logs are DIFFERENT consoles (SW:
  chrome://extensions → service worker link; page: F12 on the settings tab).
- **ID stability** — `postWithCb` derives the callback hash `l` from
  `chrome.runtime.id` substring.
- **Site bridge (`webSettgs`) — GitHub Pages mirror (FIXED 2026-08-29)** —
  the Import/View interception on site pages only fired when the tab
  hostname == `_mo` (`www.autocontrol.app`, dead domain). The mirror lives
  on `alex-302.github.io` → the gate now accepts `_9n` (file10) via
  `hostname.in(_mo,_9n)` (file62_mv3), and `_Zr` injects the bridge with
  `chrome.scripting.executeScript` + `world:"ISOLATED"` — do NOT route it
  through `_wj`/`__acInjectCode` (MAIN world: no `chrome.runtime` →
  sendMessage throws). ⚠ FOLLOW-UP: (a) at `document_start` `document.head`
  can be NULL → `_Zr` uses `(document.head || document.documentElement)`
  and try/catch (the listener registers first); (b) MV2 re-injected the
  bridge into ALREADY-OPEN tabs after config load
  (`_zg({url:"*://www.autocontrol.app/*"})…_Zr(d.id)` in file62.js) — the
  port lost that block → a tab opened before the SW start never got the
  bridge. sw.js `__acReinjectSiteBridge()` (at SW start) restores it for
  both hosts. ⚠ FOLLOW-UP (2026-08-30): after an EXTENSION reload the old
  injected listener (dead context) throws `Extension context invalidated` /
  `chrome.runtime undefined` on every Import/View click (console noise —
  the NEW injection still handles the event, so the import works). `_Zr`'s
  `c()` now guards `chrome.runtime.sendMessage` and the `webSettgs`
  listener wraps the call in try/catch (file62_mv3, IN the bundle —
  rebuilt 2026-08-30). The stale listener of an already-open tab can only
  be purged by reloading that tab. SW handler: file48 `m()` (`imprtSttgs`
  import / `viewSttgs` open `main.html?file=` / `redirSttgs` redirect).
  mh_test B47.
- **SFE View (`main.html?file=…`) — two MV3-port bugs (FIXED 2026-08-30)** —
  (1) LOCAL `file://` URLs: `_1` (file67) matches `file:` protocol → the SFE
  read the path via the NATIVE (`_If`) which does NOT understand the
  `file://` scheme → Windows "syntax error" toast. Fix (file91.js,
  page-side, also in the SW bundle where it is inert): normalize
  `_Uy.filePath` — strip `file://`(+`localhost`) and a leading `/` BEFORE
  the load. (2) BOOT RACE: the storage proxy (`_Yk.storage.local.get`
  inside `_Nh`) starts the loader `p` on the FIRST storage read (any
  page-init read) and `p` nulls itself at start — `afterLoad` then sees
  `p=null` and SKIPS the load, `n()` renders with an empty `m` → the
  editor opens EMPTY (remote case; the manual Open works because the
  re-navigation races differently). Fix: after `p&&(yield p())`,
  `if(!p&&_Uy.filePath&&_ul(m)){for(50b&&_ul(m))yield _za(100)}` — wait
  (≤5s) for the proxy-initiated load to fill `m`. Verified in Canary via
  CDP: remote `#actions:6` + 6 triggers, local `C:/…` + 19 triggers,
  mh_test 88/0/0. ⚠ `_ul(m)` is the CORRECT wait condition (m starts
  empty) — `!_ul(m)` never waits (inverted).
- **SFE Import ("Import all" in a View-opened editor) — no-op (FIXED
  2026-08-30, take 2 — take 1 was insufficient)** — chain: file91 `impAll`
  → confirm → `_uw(…_9i…)` → `_0j()` → `_0s()` → `_Qo("none")` finds the
  first `main.html` tab → `_Yk.extension.getViews({tabId})`. TAKE 1 ROOT
  CAUSE: mv3_shim.js stubbed ANY tabId lookup to `[]` → `_Xp(a)._Hu.wait()`
  threw → `_0j()` hung → `_lj` never ran (the file78 `_uw` fallback was
  unreachable — the hang is BEFORE it). TAKE 2 ROOT CAUSE: `chrome.
  extension.getViews` DOES exist in MV3 extension pages (only the SW lacks
  it) — my first fix returned `[window]` UNCONDITIONALLY, which routed
  `_lj` into the SFE tab itself; there `_bd` writes through the SFE
  **file-proxy** (`_Nh` override in file91, `_Uy` set → `_Yk.storage.
  local.set` → `m.add` + `__dummy__` hack) into the editor's file model —
  the REAL `chrome.storage.local` never changed → "import did nothing".
  FIX: (a) mv3_shim `getViews({tabId})` calls the ORIGINAL
  `origGetViews(opts)` (restores MV2 semantics: the window hosting that
  tab → `_lj` runs in the settings window when it is open); (b) file78
  `_lj` AND `_uw` fallback write via REAL `chrome.storage.local.set(_bj(a),h)`
  instead of `_bd` (equivalent in the settings window where `_Yk===chrome`,
  bypasses the proxy in the SFE tab) → SW picks it up via storage.onChanged
  → `_Gf` → native type 60. Both files page-side (mv3_shim NOT in the
  bundle; file78 NOT in the bundle — but file62_mv3 IS and was rebuilt for
  the bridge-log guard). mh_test B48.
- **SFE Import leaves an empty `#none` tab / blank page (FIXED 2026-08-30,
  take 6 — forced `visible`; user-verified OK)** — when no settings page is
  open, `_0s`→`_Qo("none")` creates a FRESH tab (`main.html#none`, `_Ou`),
  and `_lj` runs there before its boot completed: `p()`/`n()` (file2) wait
  for `_Hu` (imports) + `_Eu` (nativeConnected from the SW) + a SW ping —
  on the FIRST import after an extension reload the SW is still starting,
  so the page's sendMessage gets "Receiving end does not exist"
  (`Unhandled promise rejection` ×N) → the boot chain aborts → `<html>`
  never gets the `visible` class → the page stays HIDDEN (blank tab) even
  though the import data is saved, the `_8f` retries render the panel and
  the hash becomes `#actions:N` (that's why no "_lj _8f failed" appears).
  Ctrl-F5 fixed it (second boot passes — SW is ready); the second import
  works because `_Qo` finds the already-open live tab. FINAL FIX (file78
  `_lj`): after the retries, force the page visible —
  `$("html").addClass("visible").css("display","block")` (idempotent) +
  diagnostic `console.log("[AC-MV3] _lj done: hash=… panels=… visible=…")`.
  Also from take 5: `_uw` guarantees the section entries IN THE MERGED
  DATA right after `_4p` (walk `a.trigActList`, for every `sctnId` missing
  from `a.sections` push `{id:_sid, name:"Imported actions"}`) — an
  imported file may carry NO `sections` array, `_4p`'s
  `a.sections.push(...b.sections)` adds nothing, the section tab never
  exists and `_8f` can never open the panel (SW config works — type 60 has
  the triggers — only the UI tab is missing). ⚠ Do NOT read storage from
  `_lj` via `yield q=>_9i({sections:[]},q,chrome)` — that call returned
  undefined in the fresh #none tab (TypeError on every retry). `_lj` keeps:
  try/catch `_9j._ku`, retry `_8f` (50×100ms), real navigation
  `?_ac=#hash` as last resort. `_uw`: the resolved window is discarded
  when it is the SFE editor itself (`/[?&]file=/.test(...)` → `w=null`) →
  no-window fallback `tabs.create({url: main.html#actions:N})`. mh_test B48.
- **False "Native Component not working" dialog after the first import
  (FIXED 2026-08-30, take 7 — ping fast-path)** — after the forced-visible
  fix, the fresh settings tab (first import after an extension reload)
  showed the `natHostNotFound` dialog (`NH-noConnex` telemetry) although
  the native WAS working (the import just read the file through it).
  ROOT CAUSE: page boot `p()` runs `m(3,500)` (file2) — a native ping
  `_9j._Vy(_xp=920,"",500)` → `_Lk(920,"",cb,500)` with a **500ms timeout**.
  Right after a reload the native is BUSY with the SW startup burst (wmic
  scans, window enum, ~30 type-400 moves, config chain) → every attempt
  times out ("CB-TIMEOUT") → `m()` returns false → dialog. Previously the
  dialog was invisible (hidden page); take-6 exposed it. FIX (sw.js
  `case "postWithCb"`): when `msg.type === 920 && connected && port &&
  handshakeDone` answer `{ok:true, result:"pong"}` DIRECTLY from the SW
  (the SW holds the live native port — same semantics as the native ping
  reply; the native's 920 answers only the SW's own keepalive). Plus a
  safety net in `_lj`: `setTimeout(()=>_gs("dialog"), 3500)` dismisses the
  modal if the handshake was too slow for `m()` to succeed (idempotent —
  `_gs("dialog")` is the standard dialog close, see file2 `z()`). sw.js /
  file78.js are NOT in the bundle — no rebuild needed. mh_test B48 (+sw
  fast-path patterns).
- **Site-bridge IMPORT (`imprtSttgs`) was dead in the SW (FIXED 2026-08-29)** —
  file48 `m()` calls `window._ja(url)`; `_ja`/`_kp`/`_uw`/`_lj` live in
  file78.js (settings-page UI: jQuery/toasts/permission prompts) which is
  NOT in the SW bundle → TypeError, silent import failure. The bundle HAS
  the whole merge pipeline (`_9i` load / `_K` dedupe / `_4p` merge / `_bd`
  save / `_ku` rebuild → native type 60, `_1p`+`_mg` fetch shim), so sw.js
  re-implements `window._ja` (download → JSON.parse → `_Qj({}.add(_2d,data))`
  → `_K(l,merged,true,true)` → `_4p(l,merged,false)` → `_bd` → `_ku`).
  MV2 showed a toast + opened the settings page on site import (file78
  `_lj`/`_Rg`/`_u` — NOT in the SW bundle) → the SW import was SILENT; the
  MV2-visible feedback is re-created in sw.js: `chrome.notifications`
  "Settings imported successfully" + open/focus `main.html` (`_Qo`
  equivalent via tabs.query/update/create). ⚠ PERMISSIONS (2026-08-30):
  MV2 requested the perms required by the imported actions BEFORE
  importing (`_lj` → `_Qk(_xk(a),"permMsgs/impSttgs",true)`; denial =
  skipped). The SW port skipped that — `window._ja` now walks the parsed
  data (recursive, MV2 `_xk` logic: runScript(!bkgrnd)/sendInput
  intoPage/copyElemUrl/openElemUrl/saveElemUrl → `<all_urls>` — already
  granted; saveUrl/saveElemUrl notif → `notifications`, dwnlApi →
  `downloads`; closedTabs → `sessions`; bmFolder → `bookmarks`) and calls
  `chrome.permissions.request` (promise+callback both handled; generator
  callback-runner, NO `yield` of a raw Promise — that codebase convention
  breaks in `_cg`). Denial → import skipped. mh_test B47.
  ⚠ ALSO (2026-08-29, follow-up 3): even with `window._ja` defined, Import
  still died — file48 `m()` routed `{imprtSttgs}` through
  `l=_Es(-700,a=>_0j()(c=>_Xp(c)._ja(a)))`, and `_0s()` resolves the
  SETTINGS-PAGE window via `chrome.extension.getViews({tabId})[0]` — EMPTY
  in the MV3 SW → TypeError before `_ja` is called. `m()` now calls
  `(window._ja||l)(a.imprtSttgs)` directly. ⚠ FOLLOW-UP 4 (user SW log):
  `scripting.executeScript` REJECTS `runAt` (that's
  `tabs.executeScript`/`contentScripts.register` territory) — the
  injection threw "Unexpected property: 'runAt'" SYNCHRONOUSLY (the
  `.catch` never fired) → `ACtlExt` never appeared → Import/View silently
  fell back to the page. Use `injectImmediately:true` (Chrome 102+).  ⚠ FOLLOW-UP 5 (2026-08-29, user: "the buttons element differs"): the
  SAVED mirror pages carry an INLINE fallback script (absent in the
  original!) that intercepted Import/View clicks: `stopPropagation()`
  killed the basics.js handler (the "not installed" nag alert broke) and
  did `download()`/`view()` instead (the download started). With the
  bridge present it returned early (no harm), but it masked missing
  injection. FIXED in the 3 saved pages
  (`switch-to-last-used-tab-in-chrome*.htm`): the inline script now ONLY
  handles the `dwnld` button; Import/View go to basics.js (bridge →
  webSettgs, no bridge → original alert). ⚠ If the site is ever
  re-downloaded, this inline script will come back — check
  `acsLink.querySelectorAll` before shipping.
  ⚠ REMOVED 2026-08-30: the TEMP `file:`-protocol bridge gate
  (`"file:"==(new URL(...)).protocol` in file62_mv3 onUpdated + the
  `file://*/*` + `fileTabs`/`isAllowedFileSchemeAccess` block in sw.js
  `__acReinjectSiteBridge`) — it existed only for testing the mirror
  pages from disk; MV2 never bridged file://. The onUpdated gate still
  has the `&&_id` guard (no injection noise on file:// when "Allow
  access to file URLs" is OFF); `__acReinjectSiteBridge` now queries
  the two web hosts only. If local file:// bridge testing is ever
  needed again, re-add it deliberately.  View (`viewSttgs` → new tab `main.html?file=…`, the in-tab Settings
  File Editor dialog) already worked (MV2 semantics — "examine in a
  separate window"). mh_test B47/B49.

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
