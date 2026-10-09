# CDP debugging (Canary with --remote-debugging-port)

> Moved from `AGENTS.md` (2026-10-04). Rules that gate changes stay in `AGENTS.md`.

- **Launching the debug browser — ALWAYS ask the user which Chrome
  variant they want** (e.g. stable `chrome.exe` vs SxS/Canary
  `"...\Chrome SxS\Application\chrome.exe"` — the user knows which
  profile carries the test extension). The reference launch (Canary SxS,
  this repo's default):
  ```powershell
  Start-Process "$env:LOCALAPPDATA\Google\Chrome SxS\Application\chrome.exe" `
    -ArgumentList '--remote-debugging-port=9223', `
                 "--user-data-dir=`"$env:LOCALAPPDATA\Google\Chrome SxS\User Data CDP`"", `
                 '--lang=en-US'
  ```
  (the backtick-escaped `` `" `` quotes around the path are REQUIRED:
  `Start-Process -ArgumentList` does NOT quote its arguments and a path with
  spaces gets split — see the detailed bullet below. When the user's own profile is
  the target, pass the `User Data CDP` junction to it; ask the user which
  profile carries the test extension.)
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
  `New-Item -ItemType Junction -Path "$env:LOCALAPPDATA\Google\Chrome SxS\User Data CDP" -Target "$env:LOCALAPPDATA\Google\Chrome SxS\User Data"`
  → launch `chrome.exe --remote-debugging-port=9223 "--user-data-dir=...\User Data CDP"`.
  The extension/toggles survive (same directory). Also: PS `Start-Process
  -ArgumentList` does NOT quote args — a path with spaces gets split into
  URL args AND a truncated `--user-data-dir` (launched a broken instance with
  the stable profile once; the same bug produced a phantom profile whose
  extension was loaded from a different checkout — see the LOAD-PATH GOTCHA
  in `Docs/GOTCHAS.md`). Always verify the profile of a running instance:
  `Get-CimInstance Win32_Process -Filter "Name='chrome.exe'" | Where-Object { $_.CommandLine -notmatch '--type=' }`.
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
  superseded by the above; **moved to `Test/archive/sw-log/` 2026-09-12**),
  `_ac_tabtap.ps1` (single Tab
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
  SW eval helper), `cdp_page_eval.js` (evaluate in a PAGE target — needed for
  the settings/test pages, `scripting` cannot touch extension pages),
  `ac_swlog_act.js` (run a PowerShell line and print ONLY the SW console
  lines produced AFTER it — kills the backlog-replay noise; use it for every
  "did trigger N fire?" question), `ac_keys.ps1` (`-Combo ctrl+m` / `esc` —
  generic OS key injection; `_ac_keypress2.ps1` is Ctrl+Tab-only and takes
  `-HoldMs`, NOT positional args), `zone_add_test.js` (`add <id> <region>
  <eventId> [action]` / `remove <id>` — a temporary zone trigger in storage,
  used to prove that the engine delivers a 750 for a given region),
  `engine_zone_write.ps1` (`-Zones "12,4,1"` / `-Alive` / `-Fallback` /
  `-Dump` / `-Diag` — write the v19 zone table into the RUNNING engine from
  outside the helper; the helper overwrites it within ~1 s unless it is
  stopped first),
  `cdp_import_live.js` (imports an .acs via the REAL
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
  2026-08-31 engine-deploy addition: `deploy_patched_engine.ps1` (deploys
  the CURRENT patched engine (`AutoControl_native\patched\`) into
  %LOCALAPPDATA%\AutoControl — stops ONLY
  Chrome SxS, kills ONLY orphan Zero/engine pairs whose parent is dead,
  backs up to `.orig` once, copies, verifies SHA-256; unknown builds need
  `-Force`; `-KeepChrome`/`-Source`; prints the relaunch + verify next steps).
  2026-09-12 additions: `ac_swlog_dump.js` (`node Test/ac_swlog_dump.js 9223
  "<regex>" [maxLines]` — READ-ONLY SW console dump, the preferred reader;
  replaces the old `zone_swlog*.js` family now in the archive),
  `zone_remove_test_triggers.js` (removes the temporary zone triggers —
  ALWAYS use `zone_add_test.js`'s `remove` or this when you are done, and
  keep every test trigger VISIBLE in the settings UI: a trigger whose
  `sctnId` does not exist in `storage.local.sections` is invisible in the UI
  yet still executed by the engine), and `Test/archive/` (historical one-off
  scripts kept for chronology — index in `Test/archive/README.md`).
  2026-09-21 additions (the "wrong hovered tab / first notch ignored" hunt —
  the engine DROPS synthetic input, so these support a PHYSICAL test):
  `_probe_raceinstall.js` (installs an in-SW diagnostic log: helper port
  traffic incl. the tab index/title, `_ys` calls with `_kg` and
  `__acHoveredTabId`, the `_pp` filter result, `tabs.reload` targets and
  `tabs.onUpdated` loading events — runtime-only, dies with the SW),
  `_probe_racedump.js` (`node Test/_probe_racedump.js 9223 [lineFilter]` —
  reads that log and hides the keepalive noise), `_probe_hold.js`
  (`node Test/_probe_hold.js 9223 900 "<regex>"` — HOLDS a CDP session on the
  SW, because **Chrome evicts an idle service worker ~30 s after the last CDP
  client detaches and that kills every runtime probe**; it also prints the SW
  console live — run it in a second terminal while the user tests),
  `_probe_zonegrid.js` (`node Test/_probe_zonegrid.js 9223 <y> <x0> <x1> <step>`
  — walks a horizontal grid with the DPI-aware cursor move and asks the
  browser-spawned helper through the SW what zones each point reports; THE zone
  regression check after a helper change — compare the output of the old and
  the new build over the same points by moving the cursor with
  `_probe_mouse.ps1` and running `zone_helper_smoke.js <helper.exe>` per build).
  - **The injected code itself is documented** (so nobody has to re-derive it):
    instruction-by-instruction listing + the ABI it relies on + verified caller
    evidence → `AutoControl_native/patches/README.md` (section "Why this
    injected code is legal"); the byte tables → `Docs/BUILD-NATIVE.md` §B.3/B.4;
    the runtime writer → `Test/ac_zone_helper.cs` (`WriteZoneTable`).
    **Proof that the assembly matches the bytes**: `node
    Test/patch_bytes_verify.js [engine.exe]` (independent decoder + exact
    branch-target assertions + "no byte outside the 3 documented ranges
    changed"; checks the DEPLOYED file by default — pass a build, or
    `--orig <pristine.exe>` for another original; a MISSING original is an
    error now, `--no-diff` opts into `PROOF HOLDS (PARTIAL)`, and the default
    original is hash-checked) and Ghidra's own disassembly in
    `AutoControl_native/patches/ghidra-disasm.txt` (`Test/DisasmPatch.java`,
    headless: `analyzeHeadless <proj> <name> -import <patched.exe> -noanalysis
    -postScript DisasmPatch.java -deleteProject`) — both agree on all 34
    instructions. mh_test B53d runs the proof, B53e proves it has teeth
    (4 mutated copies must all be rejected), **B53f** rebuilds the helper's
    `npre[]` writer from `Test/ac_zone_helper.cs` and requires byte equality
    with the verifier's simulated runtime variant, **B53g** parses the Ghidra
    listing and requires it to equal the current build (a stale listing or
    helper drift fails the suite).
    Key ABI facts (verifiable in `Test/native-disasm/`): `FUN_004156f0` is
    `uint __fastcall (POINT*, uint region, HWND)` → **EDX = the region**; the
    trampoline sits on the function's first byte, BEFORE the prologue
    (`sub esp,20h; push ebx; push ebp`), so the incoming registers are intact;
    the result is EAX and the ONLY caller (`decomp/00415b40_FUN_00415b40.c:41`)
    does `uVar5 = FUN_004156f0(...); return uVar5;` — **match == consume**
    (`functions.csv`: `004156f0;FUN_004156f0;1034;1`). Documents and bytes are
    kept in sync by mh_test B53c.
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

