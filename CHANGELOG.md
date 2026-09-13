# Changelog — AutoControl MV3 port

> This changelog follows the Keep a Changelog convention (Added / Fixed /
> Changed) and is written for readers of the project: what changed and why it
> matters, without internal implementation identifiers.
>
> The technical ledger (obfuscated-symbol analysis, protocol details, verified
> root causes) and summarizes feature coverage lives in `Docs`.

## Unreleased — MV3 port

### Added

#### Architecture

- Service worker brain replaces the always-on MV2 background page: native
  messaging, config processing and trigger dispatch all live in the worker;
  the settings page is UI-only. Keepalive (alarms + self-waker + persistent
  native port) keeps the worker alive; a message buffer replays state to
  pages that open late; live config rebuild applies trigger/script/action
  edits without an extension restart.
- Offscreen document hosts the background-script sandbox, so background
  scripts run even with the settings page closed; the same document provides
  audio playback.
- Zone gate for mouse-over triggers (2026-09-03, extended 2026-09-12): the
  bundled engine cannot classify the hovered region on Chrome 148+ (its hover
  cache never refreshes over the tabs and MSAA queries from its input hook
  deadlock). A tiny external helper (`ac_zone_helper`, a second native host,
  no hooks) classifies the zone under the cursor from a normal process
  context; the service worker asks it before executing any mouse-over-gated
  trigger and skips the action when the real zone does not match the
  trigger's regions. Wheel-over-tab-strip actions (e.g. reload the hovered
  tab) now work without modifier keys while the page keeps its normal wheel
  scrolling.
  **2026-09-12 — all non-menu regions are now classified:** Browser window,
  Web page, Title area, Browser tab, Tab's close button, Tab's speaker icon,
  New tab button, Toolbar, Omnibox, Bookmark button and the Browser menu
  button (position-based). The helper answers the whole SET of regions under
  the cursor (hovering the address bar matches both "Omnibox" and "Toolbar" —
  the engine evaluated every region independently), and the service worker
  fires a trigger when the sets intersect. This closes the earlier "New tab
  button does not work" report — the helper simply had no rule for it.
  - **Tab's close button / New tab button / Browser menu button verified
    working (2026-09-12).** The blocker was the ENGINE, not the helper: the
    bundled engine still dropped the 750 for those regions (its own
    classification fails over the tab strip), so the gate never saw the
    trigger. The engine patch (v18) now accepts **every region below 60**
    (all UI regions) while the AutoControl menu regions keep the engine's own
    classification — the selectivity moved entirely into the service worker.
    The "New Chrome available" update pill counts as the Browser menu button
    (it occupies the kebab's slot in Chrome 150).
  - **Title area now means the whole top band** (user report 2026-09-12): the
    caption, the tabs, the omnibox and the toolbar — everything above the page,
    exactly as the original UI illustrates it. Hovering a tab now matches
    "Browser tab" AND "Title area"; the page never matches it.
  - **Tab's speaker icon fixed** (user report 2026-09-12): Chrome does not
    expose the icon to the accessibility hit test and the tab's own reported
    rectangle is unreliable, so the old "left/right half of the tab" rule sent
    the speaker icon to the CLOSE zone. The helper now scans the tab's
    accessibility children (the mute button's rectangle contains the cursor)
    and identifies the close button as the rightmost one.
  - Zones are reported only for the browser that hosts the helper and only
    while its accessibility tree is awake (a background heartbeat keeps it
    awake; the tree sleeps after ~30 s of inactivity and everything then looked
    like the title area).
  - All 750s of ONE input burst now share a single helper answer (120 ms
    cache): Chrome can scroll the tab strip between them, and the burst used
    to see different regions for one physical wheel.
  - ⚠ Testing note: restarting the browser makes the extension import
    `settings.dat` into storage (original behaviour), replacing live test
    triggers with the file's content.
  - **Engine v19 — the zone decision moved into a zone TABLE (2026-09-12,
    supersedes v18).** The v18 approach (accept every UI region in the engine,
    filter in the service worker) turned out to also break input consumption:
    the engine decides "consume the wheel or pass it through" with the SAME
    check that v18 forced to true, so pages stopped scrolling whenever a
    wheel trigger carried a mouse-over condition. The helper now writes a
    small table into the engine's memory (one flag + 64 slots, one slot per
    region) and the engine matches a region only when the helper says the
    cursor is really over it — so the wheel scrolls the page as before and is
    consumed only over the zone the trigger asks for. Verified with real
    system input: page wheel scrolls (scrollY 800 → 1100 → 2100) with the
    zone-12 trigger enabled and zero false trigger events; wheel over the tab
    strip still fires it (pin/reload the hovered tab). If the helper is not
    running, the engine falls back to the v18 behaviour, so zones never
    regress into "nothing works". Menu-item regions keep the engine's own
    classification.
  - **All 12 "mouse over" areas verified in a live browser (2026-09-12,
    user-tested).** Each area of the action editor was selected in a real
    action and exercised with a physical wheel: Browser window · Web page ·
    Title area · Browser tab · Tab's close button · Tab's speaker icon ·
    New tab button · Toolbar · Omnibox · Bookmark button · Browser menu
    button · Any menu item. Over the wrong area nothing happens (the wheel
    keeps scrolling the page), over the right one the action runs — including
    the address bar and the menu, which earlier test runs had wrongly
    reported as unsupported (those runs were made while the native's mouse
    hook was down after a forced engine restart; the conclusion was wrong and
    has been corrected in the docs).
  - **Zone helper no longer loses its table address** (2026-09-12): the first
    table-writing build wrote the return instruction one byte too early, which
    corrupted the table address inside the engine and made the engine skip the
    lookup — zones looked dead while everything else worked. The helper now
    also always allocates its own memory page instead of trusting the address
    left over from a previous run.
  - **The helper is started by the service worker** (2026-09-12): it used to
    start only in response to a trigger, but the engine drops triggers for
    regions it cannot classify — a chicken-and-egg circle that made zones look
    dead after a fresh start. The worker now pings it every 2.5 s.
  - **Both native parts can now be rebuilt bit-for-bit** (2026-09-12). The
    patched engine is reproduced from the pristine original by a documented
    byte patch (exactly 40 bytes: a jump at the classifier entry plus a code
    cave in the `.text` tail padding) and the zone helper is rebuilt from its
    C# source with a deterministic compiler — the build script verifies the
    SHA-256 of both outputs, so "is this the binary we ship?" is one hash
    comparison. The engine builder also refuses to run unless its input file
    is byte-identical to the pristine original. Full recipe:
    `Docs/BUILD-NATIVE.md`; one-command check:
    `powershell -File Test/build_native.ps1`.
  - **The deployed zone helper is now the reproducible build** (2026-09-12):
    the repackaged helper binary produced by the deterministic compiler was
    installed (the previous one was rebuilt by an older compiler that embeds
    random identifiers, so it could not be reproduced from the source); the
    old file is kept next to it as `ac_zone_helper.exe.bak-493A7276`. The
    running helper was verified again in the browser afterwards (tab, address
    bar and page all classify as before).
  Helper source: `Test/ac_zone_helper.cs` (build recipe in
  `Docs/BUILD-NATIVE.md` §A); engine patch builder: `AutoControl_native/patches/patch_zones_v19.js` (supersedes
  `patch_zones_v18.js`); registration and the
  gate internals are in `Docs/archive/NATIVE-REVERSING-2026-08-31.md` §13 and
  `Docs/TODO-mouseover-zones.md` §2g.

#### Native component

- Automatic engine install: when the engine is missing, the extension unpacks
  its bundled copy, writes it through the native host and reconnects by
  itself (verified end-to-end). Follow-up fixes:
  - the engine is re-deployed after a reinstall/repair wipes it;
  - the config is re-sent after every reconnect (hotkeys/gestures stay alive
    without an extension reload);
  - the extension connects automatically after the native is installed;
  - with the native uninstalled, reconnect attempts stop instead of looping
    forever and the install pane is shown.
- Emergency Repair re-implemented for the worker world: the extension reloads
  itself (the MV2 equivalent of reloading the background page), the icon
  badge shows Wait → OK/Error, the context-menu item is always available and
  with no native installed it opens the install page. The engine is never
  hard-killed (a forced kill used to leave dangling input hooks that stalled
  keyboard/mouse for ~40 s).
- Cleanup of session/tab files older than 10 days on connect, as in the
  original; native error classification: when the engine cannot install its
  input hooks (conflict with another program), the user gets a notification
  with buttons ("Don't show again" / "Keep showing") instead of silence;
  engine crash counters and the install-age gate are preserved.
- Hover-region (mouse over …) conditions on Chrome 148+ — MSAA tree
  activation (Chrome requires honey-pot + accName, crbug 416429182) was
  investigated and implemented as an engine patch (v2–v4, `Test/patch_accname.js`,
  which also added the optional type-792 no-click zone probe; see
  `Docs/archive/NATIVE-REVERSING-2026-08-31.md` §9). **CORRECTION
  (2026-09-13):** that patch is NOT part of the shipped fix — the deployed
  engine is the v19 zone-table build, and the accessibility tree is kept awake
  by the ZONE HELPER, which queries `get_accName` itself on every
  classification. The 792 diagnostics therefore require a separate
  `patch_accname.js` build.
- Hover-region diagnostics on Chrome 150 (2026-09-01/02): the tab-strip
  region (12) cannot be made selective on this Chrome — the engine never
  sees a tab element (its hover cache tracks the page window only), so the
  tab strip classifies as the page. Root cause and every patch attempt are
  recorded in `Docs/archive/NATIVE-REVERSING-2026-08-31.md` §10. The
  classifier is proven patchable (a test build fired wheel actions over the
  whole window), but zone-12 selectivity needs a geometric classifier or a
  new engine; both are future work. Operational note: after a Chrome
  restart the config (native message 60) is only sent when a settings page
  is opened — without it, no triggers fire anywhere; force it via the CDP
  eval documented in AGENTS.md.

#### Scripting engine (Run Script / ACtl)

- User scripts run through Chrome's user-script API (works even on
  strict-CSP sites); the ACtl API is exposed to scripts; ES module import and
  module file loading work (world CSP relaxation + clone-safe module
  transport).
- Code execution in the page's main world via the user-script API — CSP-safe
  (Tampermonkey-style), including file/URL forms, with the function return
  value delivered back to the script.
- Scripts can run in iframe subframes, each frame executing in its own
  context; burst deduplication for script launches (legitimate re-presses
  still work).
- The script bridge is now a static content script — Chrome guarantees
  exactly one instance per tab, with a self-healing guard for stale
  instances after extension reloads.

#### Triggers & actions

- Reliability additions: companion-trigger dedup (a hotkey press that fires
  two trigger ids runs the action once), action-queue watchdog (a stuck
  action is force-skipped after 5 s — replaces the MV2 "Stop waiting"
  dialog, impossible in a worker), window-enumeration cache.
- Icon pipelines re-implemented for the worker: gesture and toolbar-button
  icons generated offscreen (buttons receive their icons and titles at
  browser start); favicon service for tab menus, with new tabs warmed up so
  the first menu open shows icons.

#### Settings UI, toolbar buttons & tooling

- All editors, sync and import/export ported; the script editor uses a local
  CodeMirror copy (offline/CSP-safe); settings import merges missing entries
  instead of wiping them; MV3 builds of the toolbar/bookmark button
  extensions; all manifest permissions and options ported.
- Node-based test harness for the worker (80 checks, no browser needed) and
  an in-browser API self-test (23 tests covering the ACtl surface).

### Fixed

#### Site integration

- Import / View buttons on the site pages (settings blocks `<acs>`) did not
  open the extension's import/view windows when the site was opened from the
  GitHub Pages mirror — the interception bridge only activated on the
  original `www.autocontrol.app` hostname (the domain is dead and has been
  re-registered by a third party). The mirror host
  `alex-302.github.io` is now recognized, and the bridge script runs in the
  content-script (isolated) world as in MV2. Follow-up: the bridge is also
  injected into already-open site tabs on extension start (as MV2 did after
  loading the config) and tolerates the page being injected at the very
  beginning of loading. The Import action itself was also broken in the
  port: its implementation lived in the settings-page UI code that the
  service worker does not load, so the import now runs in the worker using
  the same merge pipeline as MV2 (download → merge → save → config
  rebuild) and shows the result like MV2 did — a notification and the
  settings page opening with the imported entries. Like MV2, the import
  first asks for any permissions required by the imported actions (for
  example download or notification access) and skips the import if they
  are denied. The saved site pages also contained an added fallback script
  that hijacked the Import/View buttons (silently downloading the settings
  file instead of asking the extension); it now only powers the Download
  button, restoring the original behavior — Import, View and the
  settings-redirect work on the mirror in all cases.

#### Triggers & actions

- **Ctrl+Tab "Smart switching" no longer opened the tab list after a
  reload.** The imported action set ("Smart Ctrl+Tab switching" from the
  site) is built on menu-state conditions: the tab menu must be *closed*
  for the open-menu trigger and *open* for the mark-move/select triggers.
  Those conditions carry a "negate" flag that was silently stripped when
  the config was compiled in the service worker: a shared membership
  helper (`in`) that the config compiler relies on worked for single
  values but not for arrays, so the compiler deleted the flag from every
  condition. Result: the native believed the menu was already open,
  refused to open it again, and let Ctrl+Tab fall through to Chrome's own
  tab switching. The helper now handles both call forms (and the harness
  pins it), so holding Ctrl+Tab opens the tab list with previews, Tab
  moves the mark, and releasing Ctrl selects the marked tab and closes the
  list; a quick Ctrl+Tab press still switches to the previous tab.
- Mouse gestures could stop working entirely after a reload: the
  right-button fix softened the *pressed* button too, and the pressed
  right button is what tells the native to start gesture recognition.
  Only the right-button *release* is softened now — gestures start and
  are recognized again, while the "stuck" left-click bug stays fixed.
- **Right-click menu override did not work** ("action fires but the
  context menu still appears", GitHub issue #1). A right-button trigger
  with the block mode "up" is what makes the native swallow the
  right-button release so Chrome never opens the context menu — but the
  same release-softening that keeps mouse gestures alive also softened
  the user's own override entry, so the menu opened after every
  right-click action. The softening is now selective: only the
  gesture-generated entries are softened (recognizable by their
  gesture-state condition), and user override entries are left intact.
  Verified with a real right-click: the menu stays closed, the trigger
  still fires, the left button works normally afterwards, and nothing
  fires spontaneously. Note: at that time hover ("mouse over …") conditions
  on triggers did not fire on Chrome 148+ at the native level (an a11y
  hit-test regression that affects the original MV2 extension on this Chrome
  version too; on Edge the MV2 extension still works, which is why the report
  only appeared on the MV3 port). SOLVED later the same day by the patched
  engine + the zone helper — see the "Zone gate for mouse-over triggers"
  entry above and `Docs/TODO-mouseover-zones.md`.
- **Pin/unpin (and mute) actions only worked on every other click** —
  the action read the tab state from the extension's internal tab cache,
  which is refreshed by an asynchronous window re-enumeration gated by a
  1.5-second cache — so clicks faster than that read a stale state and
  "toggled" the tab to the same value (a visible no-op). Pin and mute
  toggles now read the live tab state from the browser right before the
  update, so every click toggles (verified: 12 rapid clicks, all
  toggled; the left button stays responsive).
- An abandoned recording session (combo editor / gesture tester left
  armed) could leave the native in raw-capture mode forever — hotkeys and
  gestures silently dead. An armed capture that sees no trigger for
  several minutes is now released automatically; a live recording re-arms
  instantly on the next editor action. (The initial one-minute threshold
  proved too aggressive — a pause of over a minute in the gesture tester
  released the recording session; the threshold is five minutes.)
- **Mouse-wheel actions (and any native trigger) could silently stop
  working after editing another action in the settings** — the trigger
  ids the native sends were decoded with a stale daily offset. The
  service worker re-stamped the offset on every config refresh (including
  the one that follows any settings save), so after midnight it drifted a
  day from the value the native actually encodes with — every incoming
  trigger decoded to a wrong id and the action never ran (while the logs
  claimed it was executing). The worker now re-syncs the offset at the
  handshake and right before every trigger dispatch, so a config edit can
  no longer desynchronize it. Verified over 5 hours of live use, including
  repeatedly toggling actions on and off.

#### Settings File Editor

- The file-open dialog timed out after 5 seconds — too short for a modal
  dialog the user may take longer to answer, which made the import/view
  flow report a failure or treat the dialog as cancelled. The dialog now
  waits up to a minute, and a timeout means "no file picked", not an
  error.

- View ("examine in a separate window") opened the Settings File Editor
  empty on the first load: the file load raced with the page boot (the
  editor's storage proxy started the loader and the boot skipped it), and
  local `file://` copies failed with a Windows "filename syntax" error
  (the `file://` scheme was passed to the native reader). The editor now
  waits for the file to finish loading and accepts `file://` paths — View
  shows the file content on the first open, for both the mirror and local
  copies.
- The "Import all" button inside a View-opened editor did nothing: the
  port stubbed `chrome.extension.getViews` with an empty result, so the
  import never found the settings window and silently gave up. The stub
  now delegates to the real API (which exists on extension pages, only
  the worker lacks it), and the import saves through the real storage
  directly instead of the editor's file proxy — so the actions are merged
  into the real settings, the config is rebuilt and the result is
  reported like the import from the settings page, whether the settings
  page is open or not.
- After such an import, when the settings page was not open, a new empty
  tab appeared instead of the actions list: the freshly opened settings
  page was not ready yet — on the first import after an extension reload
  its startup chain (which waits for the service worker) aborts, and the
  page stays hidden even though the import data is already saved. The
  import now guarantees the imported section exists in the settings data,
  retries the panel switch, forces the page visible and, if needed,
  reloads the tab onto the right section (`#actions:…` with a
  cache-busting query) — the page opens the imported section directly on
  load, matching the MV2 behavior. The settings page itself is never used
  as the import target when only the file editor tab is open; a dedicated
  tab is opened instead.
- The freshly opened settings page could show a false "Native Component
  not working" warning on the first import after an extension reload: the
  page's startup check pings the native component with a very short
  timeout, and right after a reload the native is still busy with the
  extension's own startup — so the check failed even though the component
  was working (the import itself had just read the file through it). The
  service worker now answers the liveness check itself once it holds a
  live connection (the check's purpose is exactly that), and the import
  dismisses the warning if it still appeared.

#### Scripting engine

- Scripts failed with "ACtl is not defined"; several APIs crashed or hung
  (callback-style internals misused as promises, the download shim missing
  response headers, complex results — screenshots, events, tab info — lost
  across worlds, nested calls colliding with the parent's dedup key, API
  messages answered twice overwriting the clipboard with "undefined"). The
  bridge now exposes the API correctly, preserves the original callback
  semantics, converts results to a clone-safe form, gives every nested call
  a unique identity and answers each API message exactly once.
- Repeated script runs on the same page degraded over time: missing switch
  definitions crashed the API, clipboard writes produced "undefined", events
  were lost. Root cause: multiple live copies of the content bridge (double
  delivery) plus a destructive clipboard serialization — fixed
  architecturally with the static content bridge and self-healing guard.
- The first script run on a fresh tab took +4–5 s (one-time Chrome
  user-script world initialization). Pre-warming was tried and removed (it
  only serialized the queue); the delivery timeout now absorbs the one-time
  cost — the first run is slower, everything after is instant.
- Result delivery across worlds: `runInTab` returned `[null]` (nested calls
  blocked as duplicates — each now gets a unique key); `runInFrames`
  executed code in the top frame instead of each matching iframe (now
  per-frame execution + per-frame keys + first-run retry); `runInPageCtx`
  could not return a value (MV3 world isolation) — replaced by a single
  self-contained proxy. Also: "run code in page" called INSIDE a
  `runInFrames` function used to run in the top frame instead of the
  iframe — the frame id is now propagated to the injection target.
- `switchState` crashed when no switches were defined; one intermediate fix
  caused ALL saved scripts/triggers/gestures to be wiped after an
  `ACtl.var` call (a fabricated empty config was written back to storage).
  Fixed and guarded by a regression test.
- Long scripts used to stall the action queue (the run-script action waited
  for completion); it now acknowledges immediately and runs in the
  background, while nested calls still await their real results.

#### Native integration

- Two engines could appear at browser start and an orphan engine lingered
  after close — orphaned engines are cleaned up and duplicate reconnects are
  guarded; expected native-host disconnects no longer print unhandled errors.
- "Play audio" froze the whole trigger chain (the audio loader relied on DOM
  APIs that don't exist in a worker) — audio now plays in the offscreen
  document using the original audio engine; the action completes instantly
  as in the original.
- "Save URL" (notify/copy methods) always failed with httpError (the
  original spoofed the Referer header via blocking webRequest, which does
  not exist in MV3) — replaced with declarative network rules applied to the
  worker's own download fetch. Follow-up fixes: notification icon type,
  absolute destination folders honored, the final "saved" notification no
  longer swallowed when the initial one failed.
- Trigger/action edge cases: fast wheel-spin tab switching skipped steps
  (active-tab cache now updated optimistically and on every activation
  event); the "On startup" trigger never fired (startup event now emitted
  once per session after the handshake); overlapping script runs were
  investigated — the feared dedup clash does not reproduce (unique per-call
  keys already prevent it), a residual attribution leak for multi-tab
  scripts is documented and tracked.

#### Settings & UI fixes

- Clicking the toolbar icon always opened the settings page even when a
  trigger was assigned — the trigger now runs instead (original behavior).
- `file://` tabs were excluded from script targets even with "Allow access
  to file URLs" enabled — the real permission is now consulted.
- The settings page showed mojibake — missing charset declaration fixed.
- The Emergency-repair menu item disappeared after the settings page opened;
  a startup crash occurred when the native was dead — both fixed.
- The first open of the custom tab menu showed empty icons — the favicon
  cache is warmed up and key-aligned.
- The floating popup windows (REPAIR COMPLETE diagnostics — stuck keys and
  the foreign-profile report — plus the no-hook/stop-waiting dialogs)
  opened empty from the worker: the original filled them through an API
  that does not exist in a service worker, and script injection into the
  extension's own pages is blocked by Chrome. The popup page now loads its
  content itself over the extension message channel, with the button
  results routed back to the worker.
- The "Emergency repair" context-menu item disappeared after the settings
  page opened or the config was rebuilt — the settings page could wipe the
  menu (it used a removed MV2 menu API that no longer exists in MV3), and
  the item's re-creation was dropped by its own duplicate filter. The
  context menu is now owned exclusively by the worker and rebuilt correctly
  whenever it is cleared.
- The post-repair diagnostics were lost entirely: the repair reloads the
  worker, and the flags were stored in the worker's memory. They are now
  persisted to storage before the reload, so after the repair completes you
  get the same REPAIR COMPLETE popup as in the original — the list of
  stuck keys/buttons (the repair was verified to list keys held down at the
  moment of repair) plus the advice about wildcards and the "Ignore
  synthetic input" option, or the misidentified foreign-profile window with
  reporting tips.

### Changed

#### Repository layout (native side)

- `AutoControl_native/` is now split by *role* instead of being one flat pile of
  exes — `original/` (untouched upstream binaries: the engine and the
  `AutoControlZero.exe` launcher), `patched/` (the current build you install:
  `AutoCtrl_2025.4.22.0.v19.exe`) and `patches/` (the script that turns the
  original into the current build). The host manifests and the zone helper stay
  at the folder root. New `AutoControl_native/README.md` explains which file is
  which; `patches/README.md` documents the one-command rebuild.
- The patch script now reads the original **from the repository**
  (`AutoControl_native/original/`) instead of the deployed backup in
  `%LOCALAPPDATA%`, so a clean checkout can rebuild the current engine; the
  deployed backup is still accepted as a fallback. `Test/build_native.ps1`
  verifies the same bit-for-bit hashes and can refresh `patched/`
  (`-UpdatePatched`). Its optional legacy flag (`v16`) is now parsed as a flag
  in any position instead of being mistaken for an input path.
- Removed three superseded engine builds from the repository
  (`…exe.patched-v3`, `…patched-v4`, `…patched-v4-diag` — the experiment-3/4
  line, replaced by the v19 zone-table build; ~2 MB of dead binaries). The
  deploy helper no longer takes `-Diag`/`-NoDiag`: it defaults to `patched/`
  and refuses unknown binaries unless `-Force` is passed.
- The Ghidra decompiler export of the engine (`Test/native-disasm/`, ~1 940
  files) is documented instead of being an undocumented dump — see its new
  `README.md` (which function answers which question, how to regenerate it).
- The engine patch ships with a **proof of safety** that its injected bytes
  mean exactly what the documentation says: `Test/patch_bytes_verify.js` decodes
  them with an independent decoder, checks every branch target and verifies that
  no byte outside the three documented ranges differs from the original; a
  Ghidra disassembly of the same bytes is stored next to the patch
  (`AutoControl_native/patches/ghidra-disasm.txt`) and the two agree on all 34
  instructions. The test suite runs the proof and also mutates the binary to
  make sure the proof actually rejects bad bytes.
  - **The proof is now complete and cannot degrade silently (2026-09-13):**
    a missing pristine original is an error instead of a silently skipped
    half-proof, the default original is hash-checked, and `--no-diff` has to be
    passed explicitly (the result is then reported as `PROOF HOLDS (PARTIAL)`,
    never as a full proof). The helper code that rewrites the cave at runtime is
    no longer only *simulated* by the verifier: the suite rebuilds it from the
    helper's own source and compares it byte for byte, and it parses the stored
    Ghidra listing and compares it with the current build — a stale listing or
    helper drift fails the suite.
  - The ABI the trampoline relies on (which register carries the region, that
    the caller cleans the pushed argument, that the matcher's answer is returned
    unchanged, that no indirect reference to the matcher exists anywhere in the
    binary) is documented instruction by instruction, not only via the
    decompiler. The ABI audit is now a **check** rather than a printout: it
    exits non-zero unless the code cave lands in real data inside a mapped,
    executable page and the matcher provably has a single direct caller — the
    two assumptions the patch would silently depend on otherwise.

#### Repository layout (extension & tooling)

- **The regression harness moved out of the extension folder** (2026-09-13):
  `mv3-build/mh_test.js` → `Test/mh_test.js`. `mv3-build/` is the shipped
  artifact (it is loaded as the unpacked extension and packaged as-is), so it
  must contain nothing but the files the extension actually loads — development
  tooling lives in `Test/`. The harness itself is unchanged: it still loads
  `sw_core_bundle.js` from `mv3-build/`, and its checks are the same 102 ones
  (including the new B54 for the removed donation/rating UI). Run it with
  `node Test/mh_test.js`.

#### Settings UI

- The five hover-region options no longer carry the `⚠ (broken in Chrome 148+)`
  suffix (`mv3-build/file68.js`): with the patched engine plus the zone helper
  all 12 regions work, so the mark was stale (it was added when the engine could
  not classify the browser chrome at all). A plain installation — the bundled
  UNPATCHED engine — still needs `Test/deploy_patched_engine.ps1`; that is
  documented in `README.md` §4.4 instead of a suffix in the UI. Reload the
  settings page (or the extension) to pick the change up.
- **The donation and rating prompts are removed.** The settings tab bar no longer
  shows the "Support the project" button (it opened a PayPal / Buy Me a Coffee
  panel) and the **Help** tab no longer shows the "Did you like AutoControl?"
  box with its Web Store rating link. The upstream project is abandoned.

#### Native component

- **Telemetry is off by default** — the original always sent anonymous usage
  data; nothing is sent until the user enables the new checkbox in Advanced
  Options.
- **Logging is off by default** (MV2-like silent console) and controlled
  from the settings page (separate toggles for the worker, page and settings
  consoles, applied live); startup output is buffered until preferences
  load.
- The offscreen document's console output now uses a dedicated `[AC-OFFSCREEN]`
  marker — the offscreen has its own inspector
  (`chrome://extensions` → "Inspect views: Offscreen document") and must
  not be confused with the worker console.
- **Protected pages** (chrome://, Web Store, etc.): scripts cannot run there
  in either MV2 or MV3 — a platform restriction; the port now shows a
  friendly notification instead of failing silently.
- **Status display**: the icon badge and Chrome notifications are used from
  the worker; the floating popup windows are filled by injecting content
  into the popup page (service-worker-safe equivalent of the original).

#### Project site & documentation

- The manifest's `homepage_url` now points to the **site mirror**
  (<https://alex-302.github.io/AutoControl_mv3/>) — the original
  `autocontrol.app` domain is dead.
- `README.md` gains §1.1, the **original Chrome Web Store description** of the
  abandoned extension, kept for reference: every link in it points to the
  mirror, and the one claim that no longer matches the port ("no code
  injection") was reworded to how the MV3 build actually works.
- The README headline is now the extension's **original store name**
  (`AutoControl: Keyboard shortcuts, Mouse gestures`), with the
  port/installation framing kept as a subtitle line below it.
- The dead **Chrome Web Store link** in the README is replaced by the archived
  snapshot of the listing, labelled "(archived)" — no dead store URL is kept.
- **The settings help links now work again**: every documentation link in the
  extension's tooltips/help (FAQ, triggers, actions, MRU tabs, scripting API,
  hover-sensitive shortcuts, …) pointed at the dead `autocontrol.app` and led
  nowhere; they now open the corresponding page of the site mirror. Two links
  have no mirror copy and stay dead by design: the "Chromium bugs" page and the
  installer download (`Native-Component.exe` — the port installs the native
  component from its own bundle instead).
- The "Chromium bugs" help page, missing from the site copy, was **restored into
  the mirror** from a 2023 Wayback Machine snapshot (the archive toolbar is not
  part of the restored page).
- On the mirror's home page the **"Release RAM without closing tabs"** article
  is listed again — upstream had the entry commented out (and pointed at an
  extension-less absolute path); it now uses the same relative `…​.htm` form as
  its neighbours.
- The **Help tab** now also lists *Release RAM without closing tabs* among its
  articles (the same page the *Unload tabs* action's help bubble links to).
- **The in-settings demo player became a list of links.** The step-by-step
  animations (Help → *Show demos*, and the *See a quick demo* tip in the Actions
  pane) loaded their screenshots from the now-dead project site, and those
  screenshots were never archived — the player could only spin on a missing
  image. The three entries now open the matching pages of the site mirror
  (triggers, hover-sensitive shortcuts, determining the hovered element).

### Known limitations

- Hover regions need the **patched engine + the zone helper** (see the
  "Zone gate" entry above). With the bundle's own engine (no patch) the chrome
  regions — "Browser tab", "Tab's close button", "Tab's speaker icon",
  "New tab button", "Toolbar", "Omnibox", "Bookmark button", "Browser menu
  button", "Any menu item" — do not fire at all; that is an engine-side
  regression on Chrome 148+ (identical in MV2), not a port loss. The port's
  fix is a byte patch of the engine plus a small external classifier, so it
  must be installed on top of the normal native installation.
- "Run code in page" nested inside a subframe function executes in the top
  frame (rare compound scenario).
- Scripts cannot run on protected pages (platform restriction, same in MV2);
  a hint is shown.
