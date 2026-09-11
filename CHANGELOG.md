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
  fires spontaneously. Note: hover ("mouse over …") conditions on
  triggers are broken on Chrome 148+ at the native level (the native
  ignores them entirely — an a11y hit-test regression that affects the
  original MV2 extension on this Chrome version too; on Edge the MV2
  extension still works, which is why the report only appeared on the
  MV3 port).
- **Reopen closed tab left pages blank until a manual refresh**
  (Ctrl+Shift+T equivalent). Restored tabs showed the URL in the
  address bar but a white page — both Chrome pages
  (`chrome://history`) and regular websites. Chrome's
  `sessions.restore()` from a service worker reopens the tab but
  often does not paint the renderer; the browser's own Ctrl+Shift+T
  uses a different path and paints correctly. After a successful
  restore, every restored tab is reloaded once (except `about:blank`)
  so the page actually appears. Back/forward history is kept.
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

### Known limitations

- Hover regions "Browser tab", "Tab's close button", "Tab's speaker icon",
  "New tab button" and "Any menu item" are broken in Chrome 148+ — a
  native-side regression that affects MV2 identically; the UI marks them.
- "Run code in page" nested inside a subframe function executes in the top
  frame (rare compound scenario).
- Scripts cannot run on protected pages (platform restriction, same in MV2);
  a hint is shown.
