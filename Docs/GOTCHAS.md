# GOTCHAS - known pitfalls & fixes (current)

> Moved from `AGENTS.md` (2026-10-04). Rules that gate changes stay in `AGENTS.md`.

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
- **Modifier chips: the generic "Alt"/"Ctrl"/"Shift" (vk 18/17/16) work
  too — do NOT trust the earlier "they never match" claim** (that came from
  SYNTHETIC input, see the injected-input caveat below). The engine holds BOTH
  the concrete code the LL hook delivers (left Alt = 164 / VK_LMENU, right = 165;
  left Ctrl = 162, right = 163) and the logical key state, and how a compiled
  condition is evaluated depends on the entry's method flag — `FUN_00413170`
  either reads the hook's key map (`key & 0x3ff`) or calls
  `GetKeyState(nVirtKey) & 1`, where `VK_MENU` (18) is set by any Alt.
  VERIFIED LIVE 2026-09-13 (user's own hand): a config carrying `keyEvt:18`
  fired on a physical Alt+wheel (`TRIG trigger=5/6`), and `keyEvt:17` on Ctrl
  is used by the MRU triggers. The earlier "18 never fires" result was measured
  with `keybd_event`/`mouse_event`, which the engine does not treat like real
  input. Bundle's name table: `[[18,"Alt"],[164,"Left Alt"],[165,"Right Alt"]]`.
- **Zone classification in Chromium FORKS (2026-09-15, helper `C8466CF7CE1AC40C3A56AAD175B0F545B914E670679B495C2199E469A483ABAF`)**:
  Chrome/Canary/Brave expose the same a11y tree — all zones work. Opera and
  Vivaldi differ, and the helper now handles them:
  * **Vivaldi**: (a) its whole UI lives INSIDE the page DOCUMENT in the a11y
    tree (the omnibox chain is 42→20→22→…→15) — the naive "a DOCUMENT in the
    chain = the page" made every point classify as page; the helper now treats
    22/37/60 BELOW the document as UI (docDepth fix). (b) It must be launched
    with `--force-renderer-accessibility` — without it the UI is invisible to
    MSAA and everything classifies as the page. (c) Tabs are deeper (41→16→37
    instead of 41→37): the tab rule now accepts 37/60 anywhere in d0..d3.
  * **Opera**: tabs are also deeper; the browser-menu button is role 57
    (the localized "Menu") on the LEFT and NOT inside the toolbar — the helper
    now finds it by NAME (`Name()` contains "menu", the Russian UI name via a
    unicode escape) and no longer misreads it as the
    site-info lock (false 21).
  * **NOT implementable in Opera/Vivaldi**: the tab's SPEAKER icon — the sound
    is drawn over the favicon in a single element (role 40) present on every
    tab, so a playing tab is indistinguishable from a silent one; and the tab's
    CLOSE button (role 16 there, not a 43 button). These zones stay
    Chrome/Brave-only (README §5a "Known issues").
  * Registry: Opera/Vivaldi need their OWN `NativeMessagingHosts` hives
    (`HKCU\Software\Opera Software\NativeMessagingHosts\hrich.autocontrol` and
    `HKCU\Software\Opera Software\NativeMessagingHosts\com.autocontrol.zonehelper`;
    `HKCU\Software\Vivaldi\NativeMessagingHosts\hrich.autocontrol` and
    `HKCU\Software\Vivaldi\NativeMessagingHosts\com.autocontrol.zonehelper`).
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
  ⚠ The mouseOver (hover-region) preconds: root cause found 2026-08-31 (RE
  session — Ghidra + Chromium sources, full report in
  `Docs/archive/NATIVE-REVERSING-2026-08-31.md`). The engine classifies
  regions via MSAA `AccessibleObjectFromPoint` (OLEACC). Chrome 148+ builds
  the MSAA tree only when a client queries the honey pot (WM_GETOBJECT
  lParam=1 — the engine DOES this, FUN_0040daf0) AND queries **accName**
  (anti-abuse, crbug 416429182; the engine only queries roles → tree stays
  OFF → oleacc serves a generic PANE → the engine fail-opens every region).
  Live map (Chrome 150 SxS, tree ON): region 1 Browser window ✓, **region 3
  Web page ✓ (works!)**, region 4 Title area ✗ (engine maps it to the whole
  window — matches the page too; the issue-#1 complaint), region 5 Tab ✗
  (fail-closed). `--force-renderer-accessibility` turns the tree on
  (verified). Planned native patch: call `get_accName` (helper FUN_0040bdf0
  exists) after AccessibleObjectFromPoint → tree on for the whole browser.
  Do NOT promise region 4/5 as working on Chrome 148+; region 3 is fine
  when the tree is on. ⚠ The engine CACHES the hovered element/region —
  live tests need ≥2s between `SetCursorPos` and the click, or results
  flake.
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
- **Hover regions on Chrome 148+ — root cause found (2026-08-31)** — see
  the RE report `Docs/archive/NATIVE-REVERSING-2026-08-31.md`: MSAA tree
  activation requires honey pot + accName (the engine sends honey pot only);
  live map: region 1 ✓, region 3 ✓ (with the tree on), region 4 ✗ (engine
  maps it to the whole window), region 5 ✗ (fail-closed). Not a port loss
  (same native for MV2; Edge works because it builds the tree eagerly).
  `--force-renderer-accessibility` enables the tree (verified); the native
  patch (accName after AccessibleObjectFromPoint) is implemented (v2-v4,
  `Test/patch_accname.js`; v4 hashes in `Test/zone-tests/README.md` §1).
  ⚠ **The accName patch is NOT part of the deployed engine** (2026-09-12):
  `AutoControl_native\patches\patch_zones_v19.js` builds from
  `AutoControl_native\original\AutoCtrl_2025.4.22.0.exe`
  and applies ONLY its own cave + entry jmp (plus the two v16 NOPs when built
  with the `v16` argument), so the running engine (hash `1A10EDD191B80A806DF66558B2B1E78BE8D6AD81E93EEAC772D13F222E212C3E`) contains
  no accName stub — verified by byte comparison with the pristine at
  `FUN_0040bdf0`. It does not matter for zones: **the HELPER queries
  `get_accName` itself** (`Test/ac_zone_helper.cs`, `acc.get_accName(0)` before
  the real `AccessibleObjectFromPoint`), which switches Chrome's a11y tree ON
  for the whole browser — that is also why the engine's OWN classification
  (regions ≥ 21, menu items 40-51) works in the live tests. Consequence: the
  type-792 zone-role diagnostics (gated by the toggle byte VA 0x4b5000,
  `--diag-on`) are UNAVAILABLE on the current build — they need the
  `patch_accname.js` build. Do NOT use region 4/5 in test triggers on
  Chrome 148+; region 3 is usable when the tree is on.

- **Zone 12 (tab strip) — WORKING SOLUTION (2026-09-03)**: external zone
  helper + SW gate. The abandoned engine cannot classify zone 12 (hover
  cache never refreshes over tabs; fresh MSAA from the LL-hook deadlocks —
  RE doc §12), so the SELECTIVITY moved to the extension: the tiny native
  host `com.autocontrol.zonehelper` (source `Test/ac_zone_helper.cs`,
  built with .NET Framework csc, installed in `%LOCALAPPDATA%\AutoControl\`,
  manifest + HKCU `Software\Google\Chrome\NativeMessagingHosts\`) answers
  `{__id}` → `{__id, zone, zones:[...]}` — the answer is the full matching
  SET (2026-09-12); the SCALAR `zone` stays for older SW builds/logging.
  Supported zones: **1** window (always in the set), **3** page (role 15),
  **4** title area = the title bar / tab strip row ONLY (37/60 or a tab button
  in the chain; the UI description: "When the mouse is over the title bar or
  tab strip") + the frame PANE outside the toolbar — narrowed 2026-09-20: the
  toolbar and the omnibox are NOT part of it,
  ⚠ and a browser UI POPUP (menu/dropdown — `WS_POPUP` + `WS_EX_TOOLWINDOW`)
  is NOT chrome at all: over the open Opera main menu (419x1083, covering the
  whole tab strip) only zone 1 is reported, otherwise the unnamed-PANE frame
  rule answered "title area" (`OverBrowserPopup`, §2f(k));
  **12** tab (a PAGETAB, role 37, anywhere in d0..d3; the empty strip area —
  role 60 alone — does NOT answer 12, and neither do the tab's own buttons:
  the engine's own region-12 check `FUN_00415570` matched only a PAGETAB or
  its direct child; user correction 2026-09-20),
  **15** close (43 under a PAGETAB, right half of the tab; ⚠ Opera/Vivaldi
  expose it as a plain PANE (16) — a square 37x37 element in the RIGHT part
  of the tab, hit-testable directly, matched by `IsPaneCloseButton` since
  2026-09-20; Chrome's favicon PANE is square too but on the LEFT.
  ⚠ **Opera 135 (Chromium 151) can ALSO expose it as a real `43 'Close tab'`
  nested one level DEEPER — PAGETAB(37) → body PANE(16, 253x42) → button(43,
  25x24)** — so neither the old `roles[1]==37` tab-button rule (the parent is
  the PANE) nor `IsPaneCloseButton` (the PANE is not square) fired and hovering
  the close button answered "Title area" — a zone-15 trigger was SKIPPED there
  (found 2026-09-21 while testing the hovered-tab fix in Opera). Fixed: the
  tab-button rule accepts a PAGETAB at ANY depth (`tabDepth >= 1`) and
  `TabButtonZone` scans the tab's children TWO levels deep
  (`ScanTabButtons`), keeping the sibling-order logic — measured after the fix:
  close `(390,30)` → `[15,4,1]`, tab body → `[12,4,1]`), **17** speaker
  (43 under a PAGETAB, left half; NOT implementable in Opera/Vivaldi — the
  favicon slot is one `role 40 'Tab favicon'` element present on every tab,
  so an audible tab cannot be told from a silent one), **16** new-tab "+" (43 whose parent is
  the PAGETABLIST 60), **20** toolbar (role 22 in the ancestry), **21**
  omnibox (role 42 at d0/d1, or the lock button 57 under the GROUPING 20),
  **30** browser menu (any toolbar button whose right edge is within 60 px
  of the window's right edge — the kebab IS exposed as an element in the
  a11y tree (role 57, name "Chrome"); the earlier "missing" report was
  made on an outdated Chrome 150 and could not be re-checked then; the
  "New Chrome available" update pill occupies its slot in some builds and
  counts as the menu button (user request 2026-09-12). ⚠ The geometry rule is
  **Chromium-only** since 2026-09-20: in Opera/Vivaldi the RIGHTMOST toolbar
  button is the extensions-panel toggle (Opera 135: `57 'Extensions' 36x37`,
  right edge 38 px from the window edge), so those browsers are excluded
  (`MenuAtRightEdge()` → false for opera.exe/vivaldi.exe; their menu is on the
  LEFT and matched by name) and a button named 'Extensions'/'Расширения' never
  answers 30 — user report "the zone-30 action fires on the blue
  extensions-collapse button"), **33**
  bookmark star (43 inside the GROUPING 20 which sits BELOW the toolbar 22 —
  the group must sit BETWEEN the button and the toolbar; Opera's
  window-contents container 20 sits ABOVE the toolbar and must NOT count,
  fixed 2026-09-20: every Opera omnibox button used to answer 33), plus
  Opera's own bookmark button (the heart) matched BY NAME — 'Add to
  bookmarks' / 'Edit bookmark' (the Russian UI name via a unicode escape) —
  because it is structurally identical to the other toolbar buttons.
  NOT implemented in the helper: menu items 40-51 — those are passed
  through to the engine (see the gate note below).
  ⚠ **ENGINE v19 `AutoControl_native/patches/patch_zones_v19.js` (2026-09-12,
  DEPLOYED — replaces
  v18, do not deploy v16/v18 any more).** v18's "always match" broke page
  scrolling (see the wheel bullet below), so the DECISION moved out of the
  engine: the zone helper writes a TABLE into the engine's memory and the
  patched matcher reads it:
  `cmp edx,28h; jae ORIG; cmp byte [alive],0; je notalive;
   mov eax,[edx*4+table]; ret; notalive: mov eax,1; ret; ORIG: <orig 5 bytes>;
   jmp 0x4156F5` — table at `+0x10` of one `VirtualAllocEx` page, `alive` at
  `+0x00` (`Test/ac_zone_helper.cs` `WriteZoneTable`). Regions ≥ 0x28 keep
  the engine's own logic (menu regions). The build itself ships the
  "always match" prefix (variant A) so an engine started without the helper
  behaves like v18; the helper rewrites bytes `0x00..0x1B` within ~1 s of the
  first classification. Deployed engine hash `1A10EDD191B80A806DF66558B2B1E78BE8D6AD81E93EEAC772D13F222E212C3E`, helper `C8466CF7CE1AC40C3A56AAD175B0F545B914E670679B495C2199E469A483ABAF`
  (deterministic build; the previous non-reproducible legacy build is kept as
  `ac_zone_helper.exe.bak-493A7276` in the data dir).
  (rebuild: `powershell -File Test/build_native.ps1 -UpdatePatched`, deploy with
  `Test/deploy_patched_engine.ps1` — both default to
  `AutoControl_native/patched/AutoCtrl_2025.4.22.0.v19.exe`).
  ✅ **VERIFIED LIVE 2026-09-12 (real OS input via the native hooks):** wheel
  over the page scrolls (`scrollY` 800 → 1100 → 2100) with **0** false 750s
  and the zone-12 trigger ENABLED; wheel over the tab strip fires it
  (`[AC-MV3-ZONE] trig 44: zones=[12,4,1] ∩ [12] → executing` → `pinTabs`);
  the helper reports page `[3,1]`, tab `[12,4,1]`, omnibox `[21,20,4,1]`.
  ⚠ ~~Regions ≥ 21 do NOT reach the patched matcher~~ — **CORRECTED
  2026-09-12 (user-verified, all 12 areas PASSED)**: **omnibox (21), bookmark
  (33), browser-menu button (30) and menu items (40) all work.** The earlier
  negative result was measured while the engine's MOUSE hook was dead (a
  `taskkill /F` on the engine can kill the mouse hook while the keyboard
  keeps working — then NO mouse trigger fires anywhere and a broken engine
  looks exactly like "this zone is not detected"). Always re-run a known-good
  control (wheel over the tab strip → trigger 44) before judging a zone.
  Live proof for the high regions: `trig 1: zones=[21,20,4,1] ∩ [21] →
  executing` (omnibox), `… [33,20,4,1] ∩ [33] …` (bookmark star),
  `… [30,20,4,1] ∩ [30] …` (menu button) and for menu items
  `TRIGGER type 750 → TRIG trigger=1` while ONLY the open menu matched
  (negative controls over the page / tab strip / beside the menu were silent).
  Menu items ride the engine's own classification (`jae ORIG`); the helper has
  no rule for them — **and it works**.
  ⚠ **Helper/SW keepalive is REQUIRED**: the helper only ran when the SW
  asked it, and the SW only asked on a 750 — which the engine drops when the
  zone is unknown. `sw.js` now pings it every 2.5 s from SW start
  (`setInterval(() => __acZoneAsk(300), 2500)`).
  ⚠ Several browsers share ONE engine file — if another browser runs the
  extension its engine LOCKS the file: kill the engines and copy in the same
  loop (the deploy script stops only Chrome SxS by design).
  ⚠ **SEVERAL BROWSERS RUNNING = SEVERAL ENGINES — the helper MUST bind to
  ITS OWN (FIXED 2026-09-13, helper `091627630DA4DFD9C289126ED6620459287E2D44BC3080B35C045A9D6ECBF3E2`, now `C8466CF7CE1AC40C3A56AAD175B0F545B914E670679B495C2199E469A483ABAF`).** Every browser spawns its
  own `AutoControlZero`→engine pair and each engine keeps its OWN zone table.
  The helper used to take `FindEnginePids()[0]` ("the first engine"), so with
  two browsers open BOTH helpers wrote into the SAME engine while the other one
  kept the FILE fallback (`mov eax,1` = "every region matches") → its mouse-over
  conditions were satisfied EVERYWHERE: "wheel over the page switches tabs"
  (user report 2026-09-13) and "Alt+wheel needs a zone condition to work".
  The fix: the helper identifies its engine by the window list EVERY engine
  keeps for its own browser (image base `+0xA2514`, `std::vector<HWND>` — the
  region matcher's only caller walks exactly that list), and a provably FOREIGN
  engine is never written (the helper logs `waiting: none of the N engines
  belongs to browser <pid>` and retries on the next 2.5 s ping). Do NOT
  "simplify" this back to `pids[0]`. ⚠ The process chain cannot tell the
  engines apart — Zero is a launcher: it hands its pipes to the engine and
  EXITS, so the engine's parent is always dead for every browser.
  ⚠ Same fix, second half: `browserPid` (the "own window" gate) is now found
  by walking UP the ancestor chain — the helper's direct parent is `cmd.exe`
  (browser → cmd → helper), so before 2026-09-13 `browserPid` was 0 and the
  gate was silently INERT (zones were reported over ANY window, VS Code
  included).
  ⚠ A browser RESTART makes the extension import `settings.dat` into storage
  (MV2 startup behaviour) — live test triggers are replaced by the file's
  content.
  ⚠ **SW GATE RULES (sw.js `__acDispatchTrigger750`, 2026-09-12):**
  (a) only regions the helper can verify are checked (`__AC_ZONE_KNOWN`);
  a trigger whose regions are ALL menu-item regions passes with the ENGINE's
  verdict — before this fix every menu-item trigger was silently skipped by
  the gate; (b) **burst cache** `__AC_ZONE_CACHE_MS = 120`: one physical event
  makes the engine emit a 750 per matching trigger and each used to re-ask the
  helper — the UI can change in between (Chrome scrolls the tab strip on
  wheel!) so the burst saw different zones (zone 15 → 12 → skipped, "wheel
  over the close button does nothing"). One helper answer is now shared per
  burst.
  (c) **an action whose combos DIFFER must not be judged by its siblings'
  zones** (2026-09-13): the native's 750 names the ACTION, not the combo that
  matched (`Docs/NATIVE_PROTOCOL.md` §5), so regions collected from ALL combos
  used to gate every 750 of that action — "Left Alt + Vert. Wheel" next to
  "Vert. Wheel over Browser tab" fired ONLY over that zone (and adding "mouse
  over Browser window" "fixed" it, because zone 1 is in almost every helper
  answer). Now a combo WITHOUT a mouse-over condition marks the whole action
  `__acZoneFree` → dispatch without asking the helper; the engine still applies
  the region decision for the zone-scoped combos (v19 reads the same helper
  table). `disabled` groups are skipped while building the map (they are not
  compiled into type 60 either). Harness: B55/B55b.
  ✅ **MENU ITEMS (region 40 = "Any menu item") — VERIFIED WORKING (2026-09-12,
  user-tested).** The precond compiles to `{type:14,"value":40}`; v19 routes
  `edx >= 0x28` to the engine's own code (`jae ORIG`), so menu items are NOT
  classified by the helper — and the engine gets them right (it tracks the
  native menu state itself). User result: the action fired while scrolling
  over the OPEN MENU only; with the menu closed it stayed silent over the
  page, the tab strip and beside the menu. The old "v18 always-match →
  menu triggers fire anywhere" warning below applied to v18 and is obsolete.
  ⚠ History (do not re-introduce): with v18 (`cmp edx,3Ch; jb alwaysMatch`)
  a menu-item precond matched EVERYWHERE, so such a trigger could fire over
  the page while the SW gate passed it through unverified.
  ⚠ **PLAIN-WHEEL + mouseOver BLOCKED PAGE SCROLLING (v18 regression —
  FIXED by v19, 2026-09-12):** `FUN_004156f0` has ONE call site (`0x415bdc`)
  and its result is the input-matching decision → **the mouseOver precond
  drives CONSUMPTION**. v18 matched every region < 60 → a wheel trigger with
  any mouseOver condition ate the wheel EVERYWHERE (the user's `wheelDn/w2/
  blk1` triggers → "I cannot scroll pages"). v19 answers from the helper's
  table, so the wheel passes through over the page and is consumed only over
  the real zone. Test recipe (uses REAL OS input):
  `node Test/ac_swlog_act.js 9223 "powershell -NoProfile -File Test/zone_fg_wheel.ps1 -Hwnd <hwnd> -Point 1000,800 -Notches 3"`
  → must print `--- new lines (0) ---` for the page and
  `[AC-ACT] … TRIG trigger=44` for the tab strip (`-Point 600,90`).
  ⚠ **Test pitfalls that cost hours:** (1) the wheel goes to the ACTIVE tab —
  check `chrome.tabs.query({active:true})` before measuring `window.scrollY`
  (a Ctrl+Tab test silently switched tabs and every "scroll test" measured a
  different page); (2) an OPEN AutoControl menu (`Ctrl+M`, a Ctrl+Tab hold)
  keeps eating input — close it with `Test/ac_keys.ps1 -Combo esc`;
  (3) `%TEMP%\ac_tail.js` is broken, use `Test/zone_swtail.js`;
  (4) `Runtime.consoleAPICalled` REPLAYS the backlog on attach —
  `Test/ac_swlog_act.js` marks the buffer end and prints only fresh lines.
  ⚠ **HELPER: the a11y tree SLEEPS** (~30 s without a client) and then EVERY
  point classifies as an unnamed PANE → zone 4. The helper now runs a
  **background heartbeat** (classification every 120 ms while the cursor
  moves, else every 1.2 s) + a 400 ms request cache — do not remove it.
  ⚠ Since 2026-09-20 the poll is **30 ms** with SETTLE detection (classify the
  moment the cursor stops; a continuous move is throttled to 80 ms): the engine
  caches the region verdict (FUN_00415bf0 recomputes only when >300 ms passed
  or the cursor moved >3 px) and reads the TABLE at that moment, so a late
  table write made the first wheel notch cache a wrong 0 that the next notches
  reused ("works, but sometimes stops"). Measured write latency 170 ms → ~0 ms;
  CPU during a continuous drag 22.7% → 11.6% of one core. Probe:
  `Test/_probe_tablecheck.ps1` (reads the cave + table, verifies the cursor did
  not move in the same instant — the user's hand otherwise fakes a mismatch).
  ⚠ **HELPER: speaker icon is NOT hit-testable** — AOP over it returns the
  PAGETAB, and the tab's own a11y rect is unreliable (tab reported `97px` wide
  while its close button sits 320 px to the right). Rules now: scan the tab's
  CHILDREN for a `role 43` rect containing the cursor; the close button is the
  RIGHTMOST sibling → 15, the other → 17 (a non-audible tab's mute button has
  a `0x0` rect → never hit). Points that hit a tab button do NOT get zone 12.
  ⚠ **HELPER: title area (4) = the title bar / tab strip row ONLY**
  (`stripNear || isTabBtn`; narrowed 2026-09-20 per the UI description
  "When the mouse is over the title bar or tab strip" — the toolbar and the
  omnibox are NOT included; the frame PANE outside the toolbar still counts);
  the page (`DOCUMENT` in the chain) is excluded, and a page's ARIA roles
  (tablist 60, input 42, toolbar 22) must NOT be read as browser chrome
  (`bool ui = !inPage` gate).
  ⚠ **HELPER: zones only for its OWN browser** — the hovered window's root
  process must equal the helper's parent process (when it is a browser),
  otherwise `{"zone":0,"zones":[]}` → all zone-gated triggers skip. Prevents
  false zone 1/4 over other apps (VS Code is a `Chrome_WidgetWin_1` window
  with NO a11y tree = a generic PANE = would classify as zone 4).
  ⚠ **TESTING: synthesized wheel goes to the FOCUSED window** (`mouse_event`
  ≠ the window under the cursor) → foreground the browser first
  (`Test/zone_fg_wheel.ps1`). `_ac_mouse.ps1 -Action wheel` needed
  `[BitConverter]::ToUInt32` for a negative delta (`[uint32]-120` throws).
  ⚠ **MSAA element rects are PHYSICAL pixels; `GetWindowRect` in a
  DPI-unaware process is DPI-VIRTUALIZED** (150% display: the real window
  is ~2094 px wide, `GetWindowRect` reports 1396 — the tab strip looked
  like it ended at x=1388 with no "+"/toolbar buttons). Scanners must call
  `SetProcessDPIAware()` FIRST (the helper does it in `Main`; the zone-30
  position rule depends on it).
  ⚠ **LOAD-PATH GOTCHA (2026-09-12, cost 30 min; rule tightened
  2026-09-13):** a debug browser window can serve the extension from ANOTHER
  checkout (an older branch kept outside this repo) while `Secure Preferences`
  claims this repo's `mv3-build\`. **Never "fix" that by copying files
  outside the repo** — see the Scope rule: any copy out of this repository
  needs the user's explicit confirmation. Report what the window serves and
  ask; the preferred fix is to load the extension from this repo
  (`chrome://extensions` → Load unpacked → `mv3-build\`). Identify the folder a
  window really serves EMPIRICALLY — put a uniquely named marker file there and
  fetch it from the SW (the loaded folder returns its content, every other path
  answers `Failed to fetch`):
  `node Test/cdp_eval.js 9223 "fetch(chrome.runtime.getURL('ac_marker.txt'),{cache:'no-store'}).then(r=>r.text())" --await`
  (the same trick identifies WHICH code a window runs: fetch `sw.js` and
  compare `len` — JS chars, not bytes — with the file size).
  `sw.js` `__acDispatchTrigger750` builds the zone map from
  trigActList at start and dispatches a mouseOver-gated trigger only when
  the trigger's regions INTERSECT the helper's set
  (`zones.some(z => zs.indexOf(z) !== -1)` — the engine evaluated every
  region independently, so several zones match one point: the omnibox is
  inside the toolbar band, the page is inside the window). The engine itself
  is v19 (zone-table driven — see the v19 bullet above). Verified live
  2026-09-12: `zones=[12,1] ∩ [12] →
  executing` over a tab (real OS wheel through the native hook) and
  `zones=[3,1] ∉ [12] → skipped` over the page; per-point helper answers
  for every zone in TODO §2d. Smoke: `node Test/zone_helper_smoke.js`;
  live probe (moves the cursor): `Test/zone_probe.ps1`; end-to-end:
  `Test/zone_e2e_test.ps1`. RE doc §13.
  ⚠ The helper needs re-registration after a reinstall (registry key) and
  its exe must be rebuilt from `Test/ac_zone_helper.cs` if moved.
  ⚠ The zone MAP in sw.js is rebuilt live on `storage.onChanged`
  (2026-09-03) — a stale map made zone-gated triggers silently dead after
  config edits; the map is also rebuilt at SW start.
  ⚠ Since 2026-09-13 that map also records `__acZoneFree` (an action with a
  combo WITHOUT mouse-over) and an inconsistent/stale lookup no longer gates
  such an action — the real gate rule is the (c) bullet above.
  ⚠ **NEVER give a CDP-created test trigger a `sctnId` that the settings do
  not have** (2026-09-12, cost a long "phantom action" hunt). The settings UI
  renders actions per SECTION tab; a trigger whose `sctnId` is missing from
  `storage.local.sections` is NOT displayed (undelatable from the UI) while
  the engine keeps executing it — the user saw "some action I do not have"
  switching tabs on every wheel over the menu button while his settings
  showed nothing. **USER RULE: every test trigger must be VISIBLE in the
  settings UI** — create them WITHOUT a section (the user's own triggers have
  `sctnId: undefined` and stay visible). `Test/zone_add_test.js` verifies the
  section and drops it when it does not exist (prints `visible=true/false`).
  ⚠ **`_Sk` drift FIXED 2026-09-04 (sw.js)**: `mv3_native_shim.js` re-stamps
  `_Sk = Date.now()/864E5|0` on EVERY `nativeConfigReady` (incl. force
  refresh after a settings save) → after midnight it drifts a day from the
  engine's `handshakeSk` → `z[750]` decodes every 750 off-by-one → actions
  silently never execute while the gate logs "executing" (symptom: all
  wheel actions die after editing an action). sw.js now re-syncs
  `_Sk = handshakeSk` at handshake AND right before every 750 dispatch in
  `__acDispatchTrigger750` — the shim re-stamp is healed on the next 750.
  Verified 2026-09-05 (5h live: 35 executing / 0 skipped across 2 config
  rebuilds). TODO §2b closed.
- **Zone 12 (tab strip) deep-dive (2026-09-01/02) — engine v16 was the
  state then; the deployed engine is now v19 (see the zone bullet above,
  ~line 640)** — see RE doc §10
  for the full chain, all patch attempts (v5b..v16) and the proof:
  (a) zone 12's `FUN_00414760(...,10)` gate returns 0 over the tab strip;
  (b) Chrome 150 reports the tab role as 41 (not the 37 the engine wants);
  (c) **the engine's hover cache NEVER refreshes over the tab strip** (it
  tracks the page HWND only — a 792 probe in FUN_0040b610 got NOTHING over
  tabs even with mouse movement) → "tab = page". The classifier chain IS
  patchable (v16 fires 750 everywhere) but zone-12 SELECTIVITY is not
  achievable via MSAA roles; a geometric classifier (GetWindowRect top
  band) was designed (v12-v14) but never conclusively tested with a
  working config. **FINAL (2026-09-03, RE doc §12)**: a FRESH
  AccessibleObjectFromPoint from the engine's LL-hook context DEADLOCKS
  (Chrome does not answer WM_GETOBJECT during input processing — v17g:
  engine alive on other threads, hook thread hangs forever, no 750/792) —
  role-based selectivity inside the engine is IMPOSSIBLE. The
  external-process classifier (`Test/zone_proto.ps1`: role 37 TABITEM in
  the ancestry uniquely identifies the tab strip) is the proven route
  for a future own engine. ⚠ Config gotcha: after a Chrome restart WITHOUT an open
  settings page, type 60 never reaches the engine → "nothing works
  anywhere". Force it: `node Test/cdp_eval.js 9223 "(()=>{_Gf({},()=>{window.__cfgDone=1})})()"`
  and verify `type 60 (config)` in the boot log. Patch scripts:
  `Test/archive/zone-re/patch_zone12_v5b.js`…`patch_zone12_v16.js` (each
  deterministic from the .bak;
  **build-bug warning: section math must use `last.rs` NOT `last.rsize`** —
  v7/v8diag shipped an empty .acp and identical hashes). User's future
  direction: a prototype native engine of our own that interacts with
  Chrome window elements directly.

### UI / settings

- **"Hovered tab" target was broken on Chrome 148+ (FIXED 2026-09-20, sw.js + helper)** —
  `hoveredTabs` = `{oper:"filter",params:{anyHvrd:!0}}` → `_ys()` (file50) asks the
  NATIVE type **485** for the tab under the mouse; on Chrome 148+ the engine answers
  only `{hWnd,x,y}` (no index/title), so `_kg` became `[]` and file59's fallback
  `c = _ys(); if (!c.length) c = [activeTab]` made every "hovered tab" action hit the
  ACTIVE tab (benchmark 2026-09-20: 12 wheel notches over 4 tabs → 10 reloads of one
  tab). **Second half:** `_kg` is only cleared by `_wd()` (runs when the TAB LIST
  changed), so even a resolved tab STUCK — the user's "it sticks on the tabs where I
  scrolled". Fix: the helper answers the tab under the cursor
  (`TabIndexOf`/`TabUnderCursorJson`, request `"tab":1`, helper `C8466CF7CE1AC40C3A56AAD175B0F545B914E670679B495C2199E469A483ABAF`),
  `sw.js` wraps `window._Vy` so 485 is answered from the helper, and
  `__acSetHoveredTab()` refreshes `_kg` before EVERY dispatch. Do not remove either
  half — the wrapper alone still leaves the stale cache, the cache refresh alone has
  no tab identity to write.
- **"Hovered tab" — ROUND 2 (FIXED 2026-09-21): `_ys()` itself is now wrapped.** The
  2026-09-20 work above was NOT enough, and the user's report proved it: after the
  fix the PREVIOUS tab still reloaded on a fast cursor move, and the first wheel
  notch after moving onto a tab was sometimes ignored. Three separate causes:
  1. **`_ys()` returns the stale `_kg`.** The filter patch only acts on an EMPTY
     result, but `anyHvrd` has a fallback (`c=_ys()`, then `[activeTab]`), so the
     stale-but-non-empty answer was passed through. `_ys()` is the SINGLE resolution
     point (the `hovered` tab-filter property calls it too), so `sw.js` now wraps
     **`_ys`**: when `__acHoveredTabId` is known it returns `[__acHoveredTabId]`
     and does NOT call the original (the original would ask the native 485 →
     the helper → a SECOND accessibility walk per event; the helper is
     single-threaded, so the two walks queued and answers arrived 180-360 ms late —
     measured: `TAB-REQ` twice per wheel, the second answer 344 ms after the
     first). `_kg` is only read by `_ys` itself, so skipping the call is safe.
     Cursor NOT over a tab → the original runs (the documented active-tab
     fallback stays). Pinned by mh_test (`__acYsWrapped` + `_ys = function`).
  2. **The helper served a tab from ANOTHER point.** `CacheStore(pt, body)` (the
     zone-only path) updated the cached POINT while keeping the cached TAB of the
     previous point — the next request matched the point and got the old tab
     (log: fresh zone classification at +21 ms, tab answer in the same millisecond
     with the EARLIER index). Now `cacheTabOk` marks a tab valid only for the point
     it was computed for, and the request path samples the cursor ONCE for both
     answers (zone set + tab).
  3. **The zone query timed out.** The tab walk had been added to the helper's
     `ClassifyAndCache`, which runs on the 30 ms heartbeat — 60-104 ms per walk made
     the helper unable to answer the SW's zone query, so the gate saw the timeout
     marker `zones=[-2]`, SKIPPED the trigger and the first notch did nothing
     (`[AC-MV3-ZONE] trig 12: zones=[-2] ∉ [15] → skipped` in the SW console). The
     walk is out of the heartbeat now (the tab is walked on demand) and the SW's
     zone query waits **500 ms** instead of 250 ms.
  ⚠ Both halves must stay: the helper supplies the tab, `_ys`/`_pp.filter` make the
  bundle use it.
- **"Hovered tab" — ROUND 3: Chrome 148 answered index 0 for EVERY tab, and too late
  (FIXED 2026-10-04, helper + sw.js).** Two causes, both found with the note channel
  below (Chrome 148 has no debug port, so the SW itself is unobservable there):
  1. **`TabIndexOf` counted the wrong level.** The strip was located as *the first
     role-60 ancestor* and ITS direct children were counted — but **Chrome 148 wraps
     the tabs one level deeper**: `PAGETABLIST(60) → PANE(16, all tabs) →
     PAGETAB(37)`, while Canary/Opera hang the tabs directly off the 60. Measured
     over the strip: **8 points, every title correct, every `index:0`** → the SW took
     `list[0]` = the FIRST tab of the window (user report "reloads the first tab").
     Fix: the strip is *the level where the tabs really ARE siblings* (an ancestor
     with ≥ 2 PAGETAB children; the role-60 ancestor stays as the fallback for a
     single-tab window), and it is counted in ONE pass (was two — 2×21 COM calls).
  2. **The answer arrived after the SW gave up.** Even with the index fixed, a burst
     of wheels reloaded the ACTIVE tab: the SW→helper log showed the answer and the
     timeout in the SAME millisecond
     (`tab ask … index:15` / `SW hover FAIL answer=null` at +1 ms). Two MSAA walks
     competed for the same tree (the 30 ms heartbeat's zone walk + the request's tab
     walk) and the walk cost ~300 ms. Fixes: `servingRequest` (the heartbeat skips
     its classification while a request is served), the single-pass walk, and the SW
     waits **900 ms** instead of 300 ms for the tab answer.
     Result: `hover FAIL` 16 → 1, walk **median 125 ms** (was ~300), and
     `hover → tab` == `ys → tab` == `RELOAD tab`. mh_test pins all three.
- **⚠ CHECK THE CONFIGURED ACTION TARGET BEFORE HUNTING THE CODE** — part of "it
  reloads the active tab" in Chrome 148 was not a bug at all: the trigger's target
  was **Current tab**. The target is readable WITHOUT a debug port — the profile's
  `Local Extension Settings\<ext-id>\000003.log` (LevelDB) records every write of
  `trigActList`; open it with `[IO.File]::Open($f,'Open','Read','ReadWrite')`
  (Chrome keeps it locked, a plain read fails) and walk the `trigActList` offsets:
  the LAST one is the live config, the sequence of them is the edit history (for
  trigger 12 that history showed `reload → hoveredTabs` … `reloadTabs → currentTab`).
- **The hovered-tab refresh is CONDITIONAL — do not make it unconditional again
  (2026-10-05).** `__acSetHoveredTab()` costs an accessibility walk (79-219 ms)
  whenever the cursor sits on a point the helper has not classified yet, and it used
  to run before EVERY dispatch — including actions that never ask for the tab under
  the cursor. User report: "switching tabs with a wheel over the tabs is delayed,
  while Alt+wheel anywhere is instant" (the Alt action has no zone check, so it
  skipped both helper round trips). `__acBuildZoneMap` now computes
  **`__acHoverNeeded`** — the triggers whose actions can ask for the hovered tab
  (`targets` matching `/hvrd/i` or `eventTabs`) — and only those pay for the refresh.
  Before the map is built the refresh runs unconditionally (the safe old behaviour),
  and if a target is ever missed the `_ys` wrapper still falls back to the bundle's
  own resolution, so correctness does not depend on the list being complete.
  **Companion change in the helper:** the tab cache is warmed again in the
  background (`lastTabWarmAt`, ≤ every 150 ms) — but ONLY while the cursor has
  SETTLED over a tab-related zone (12/15/17) and NEVER while a request is being
  served. That is what makes a "hovered tab" action answer in ~1 ms again; the
  round-2 failure was a walk on EVERY heartbeat classification, which starved the
  zone query (60-104 ms answers, `zones=[-2]` timeouts).
- **A SW→helper NOTE CHANNEL replaces CDP in a browser without a debug port** — the
  SW posts `{__id, note:"…"}` on the helper port and the helper appends the text to
  `%TEMP%\ac_zone_helper.log` (`Test/ac_zone_helper.cs`, the `"note":"` branch).
  Useful when the user must NOT relaunch the browser with `--remote-debugging-port`
  (Chrome 136+ ignores that flag on a default profile anyway). The channel is NOT in
  the shipped `mv3-build/sw.js` — re-add it the same way when needed, then remove it
  again to keep the folder clean.
- **"Event tab" target resolved to NOTHING — no fallback at all (FIXED 2026-09-20,
  sw.js)** — the SAME root cause as the bullet above, but `evtTabs` has no safety
  net: `_Mg` (file59) does `else if(a.evtTabs) c=_Eh(_zw)` and `if(c)` is TRUE for an
  empty array → the group is empty → an action like "Reload tabs" iterates over zero
  tabs and **does nothing while reporting success** (user: "something does not
  work"). `_Eh(_zw)` = `_Cg(_zw).tabs` = the tab list the ENGINE attached to the
  event — empty for mouse events on Chrome 148+. ⚠ The pre-dispatch refresh of the
  bullet above is NOT enough: `_rf` does `yield _Rf()` FIRST in every action and
  `_Rf` → `_wd()` → `_kg = null`, so the cache is wiped by the action itself. Fix:
  the hovered tab is ALSO kept in **`__acHoveredTabId`** (SW-local — `_wd()` cannot
  clear it) and the **filter TABLE** `_pp` is patched (`_pp.filter` AND
  `_pp.posFilter`), NOT `window._Mg` — file59 captured the function object at load
  time, so wrapping the global is a silent no-op (verified). The patch only acts
  when the bundle's own result is EMPTY and the target is `evtTabs`/`anyHvrd`, so a
  resolved target and every other target are untouched. Over the page the result
  stays empty (no reload) — a zone-scoped trigger never gets there anyway (the SW
  gate skips it). mh_test **B56** runs the REAL patch source sliced out of sw.js
  against a stub table.
- **`noSuprt` (the red "This feature is not supported in Opera/Vivaldi" banner) is a
  browser-NAME check, not a capability test** — `file65.js`
  `noSuprt:\` ${_9j._Jh.in("opera","vivaldi")?`<noSuprt>…</noSuprt>`:""}\``, prepended
  to every mouse-dependent UI text (`tse.hvr`, the `hvr` tab filter, `mseOvr`,
  `copyElemUrl`, `openElemUrl`, `ombar`). It is OUTDATED for the tab-strip cases
  (the zone helper makes Hovered tab / Mouse over work in Opera) — do NOT treat it
  as evidence that a feature is broken; check the actual behaviour. Whether to drop
  it for the working entries is an open UI decision (TODO-mouseover-zones.md §2f(n)).
- **`Test/_probe_mouse.ps1` MUST be DPI-aware** — without `SetProcessDPIAware`,
  `SetCursorPos` takes LOGICAL coordinates and the cursor lands at 1.5× the requested
  point on this 150% display (cost an hour on 2026-09-20: probes measured a different
  spot and it looked like "a fresh helper misclassifies"). Same rule as for the MSAA
  scanners (§ DPI gotcha).
- **`zone_probe.ps1` answers are meaningless while ANOTHER app covers the browser**
  — it spawns `ac_zone_helper.exe` via `zone_helper_smoke.js`, i.e. from a process
  whose parent chain has NO browser: the "own window" gate is inert, so a point over
  a foreign window is classified as `{"zone":1,"zones":[1]}` ("browser window,
  nothing else") instead of `0`. For a REAL answer use the browser-spawned helper
  through the SW (`node Test/cdp_eval.js <port> "__acTest.zoneAsk(1000)" --await`,
  which returns `[0]` when the cursor is not over that browser). Seen 2026-09-21:
  Telegram (`Qt51519QWindowIcon`) was in the foreground and every probe point
  returned `[1]`.
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
- **Donation / rating UI REMOVED (2026-09-13, user request)** — the upstream
  project is abandoned, so the port does not solicit money or Web Store
  reviews. Deleted: the "Support the project" tab-bar button (`<contribBtn>`,
  built by file2.js `n()` — it also ran the 60 s bounce animation
  `q()`/`setInterval(q,6E4)`), the panel it opened (`<template id=contribPanel>`
  — PayPal / buymeacoffee) and the Help tab's rating box (`${#rateUs}` include
  + `<template id=rateUs>`), plus their now-dead CSS (file46.css
  `contribBtn*`, `@keyframes contribBounce`, `[contribPanel] *`, `donateBtns`,
  `[paypal]*`, `[coffee]*`, the four `rateUs*` rules; file40.css the
  `contribBtn` entry of the help-panel font group). ⚠ `ext-mv2/` still carries
  all of it — do NOT re-copy these blocks on a future merge. mh_test **B54**
  pins the removal (and guards helpPanel/installPane against an over-eager
  deletion).
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

