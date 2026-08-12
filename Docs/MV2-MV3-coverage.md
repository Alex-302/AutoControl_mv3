# MV2 → MV3 Coverage Summary

> Plain-language overview of how much of the original MV2 extension (AutoControl)
> is preserved in the MV3 port. The authoritative, detailed source is
> `FEATURES-MV3.md` (feature status tables, port gaps §7, platform limits §8)
> and `FEATURES-MV3.md` §7 (open items). This document is a human-readable summary only —
> no internal code identifiers, no wire-protocol minutiae.
>
> Verified: 2026-08-11 (docs review + test-harness run); updated 2026-08-12
> (file71 popups, repair diagnostics and runInPageCtx-in-runInFrames closed).

**Usage reminder:** the MV3 build runs ONLY as an unpacked extension
(Developer mode → Load unpacked → `mv3-build/`). It is a dev build, not
packaged for the Chrome Web Store.

---

## Overall verdict

The functional port is **essentially complete**. All 14 documented "port
gaps" have been closed (the last one — native error classification — on
2026-08-10), plus the 2026-08-12 round: file71 floating popups from the
service worker, the post-repair diagnostics popup and the
runInPageCtx-inside-runInFrames frame routing. What remains open is a
handful of platform-level limitations that equally affect MV2.

**Rough coverage: ~98%+** of MV2 functionality. The remainder is not a
regression — it is either impossible in MV3 by design (with substitutes in
place) or broken identically in MV2 (Chrome platform changes).

---

## Coverage by area

| Area | Coverage | Notes |
|---|---|---|
| **Native integration** (connection, handshake, callbacks, keepalive) | ✅ ~100% | Same wire protocol as MV2; every message type handled |
| **Native component lifecycle** (auto-update of the engine, auto-reconnect, cleanup of old session files, install/uninstall, Emergency Repair) | ✅ ~100% | Repair now restarts the extension (equivalent of the MV2 background-page reload) — no stuck states, no dangling hooks |
| **Triggers** (hotkeys, mouse buttons, wheel, gestures, rocker, joystick, voice, bookmarks, browser events, omnibox, startup, timers, binary switches, menus, preconditions) | ✅ ~100% | Full set; trigger config compilation identical to MV2. **One exception:** hover regions "Browser tab", "close button", "speaker icon", "new tab button", "any menu item" are broken in Chrome 148+ — a native-side a11y regression that **also breaks MV2** (not a port loss; the UI marks these options as broken) |
| **Actions** (tabs, windows, bookmarks, menus, clipboard, system, SendInput, commands, scripts, screenshots, Save URL, Play audio) | ✅ ~100% | All categories. The two hardest ones were fixed: **Save URL** (Referer header now set via declarative network rules instead of the MV2 blocking webRequest) and **Play audio** (audio now plays in an offscreen document — the MV2 background page could play it directly) |
| **Scripting engine + ACtl API** (33 methods) | ✅ ~100% | All methods work, including the complex ones: code in the page's main world with return values, subframes, ES modules, events |
| **Settings UI** (trigger/action editors, script editor, import/export, sync, live config apply without restart) | ✅ ~100% | Script editor uses a local CodeMirror copy (offline-safe) |
| **Data & persistence** (config, switch states, sync, settings file) | ✅ 100% | Same storage keys/formats as MV2; guarded against accidental wipes |
| **Auxiliary extensions** (toolbar buttons) | ✅ ~100% | Work without external-connectivity declarations; icons pushed from the service worker |
| **Notifications / status display** | ✅ ~99% | Icon badge and Chrome notifications work; the extension's own floating popup windows (diagnostic dialogs, REPAIR COMPLETE) work from the service worker since 2026-08-12 (content-bridge: the popup page loads its content over the extension message channel — see FEATURES-MV3.md §7-15) |

---

## Impossible in MV3 by design (with substitutes — not losses)

| MV2 mechanism | MV3 substitute |
|---|---|
| Blocking web request interception | Declarative network rules (done — used by Save URL) |
| `eval` of user code in the background / content scripts | Chrome user-script API (done) |
| Always-on background page with full DOM | Service worker + keepalive + offscreen document (done) |
| Scripts on protected pages (chrome://, Web Store, etc.) | **Blocked by the platform in MV3 and MV2 alike**; the port adds a friendly hint instead of silent failure |

---

## Remaining open items (all low priority)

1. **Hover regions** "Browser tab", "close button", "speaker icon", "new tab
   button", "any menu item" in Chrome 148+ — a native-side a11y regression
   that breaks MV2 identically (NOT a port loss; the UI marks the broken
   options).
2. **Not Web-Store ready** — unpacked-only dev build; GitHub publication is
   a process TODO.

---

## Test coverage assessment

### Service-worker harness (`mh_test.js` — Node-based, no browser needed)

**87 checks: 87 PASS / 0 known gaps / 0 FAIL** (re-run 2026-08-12).

- Covers: bundle loading, protocol glue, config compilation, user-API
  dispatch, and a regression guard for virtually every bug fixed since the
  port started (including runtime probes for the play-audio routing and the
  save-URL network rules).
- **Strengths:** fast, repeatable, no browser needed; every fix ships with a
  test so regressions are caught immediately.
- **Limitations:** Chrome and the DOM are stubbed — it does NOT test the real
  native component, real tabs/gestures/hotkeys, or the settings page UI.

### In-browser API self-test (`Test/SCRIPTING-API-TEST.js`)

**23 tests, stable 23/23** — covers nearly the whole scripting API:
variables, tabs, screenshots, clipboard, files, ES modules, code in
subframes / page main world, events, placeholders, switch states, running
actions and commands.

- Known flake: the very first cold run on a fresh tab can exceed the event
  timeout (slow first page load) — warm runs are fast and stable.

### Auxiliary tests

- Audio-engine simulators (stubbed speech synthesis / audio context) —
  verify the play-audio logic without Chrome audio hardware.
- Settings snapshot file consumed by the harness to compile a real config.

### What is NOT automated (verified manually on the test VM)

- Real native-driven behavior: hotkeys, mouse gestures, wheel, menus,
  native clipboard.
- Install/uninstall/repair flows end-to-end.
- Toolbar-button extensions end-to-end.
- Real audio playback in Chrome.

**Bottom line:** automated coverage is strong for the service-worker brain
and the scripting API, and every bug fix is locked in with a test. The
native-driven surface is covered manually — unavoidable without a CI setup
that runs a real Chrome and the real native component.
