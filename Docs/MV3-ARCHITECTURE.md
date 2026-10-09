# MV3 architecture & script execution (SW-brain)

> Moved from `AGENTS.md` (2026-10-04). Rules that gate changes stay in `AGENTS.md`.

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
- `sw_core_bundle.js` — concatenation of core files (list in `Docs/BUNDLE-BUILD.md`),
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

