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
