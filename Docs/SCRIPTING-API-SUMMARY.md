# AutoControl Scripting API — status in the MV3 port (Chrome 150+)

> Summary compiled 2026-08-02 from the official docs
> (https://www.autocontrol.app/scripting + all subpages) and from the actual
> implementation of `W()` in `file77.js` / the bridges in `file42.js` / `sw.js`.
>
> Legend: ✅ works (verified) | ⚠️ works with limitations |
> ❌ does not work (needs work) | ❓ unverified, theoretically possible.

## 1. Constants

| API | Status | Comment |
|-----|--------|-------------|
| `ACtl.TAB_ID` | ✅ | proxy in jsCode (`var ACtl = __acActl`); 0 in the background |
| `ACtl.STOP_CHAIN` / `ACtl.STOP_FULL_SEQ` | ✅ | frozen `{break:'inner'/'outer'}` — returning it from a script stops the action chain |

## 2. Variables

| API | Status | Comment |
|-----|--------|-------------|
| `ACtl.var(name, value)` / `ACtl.var(name)` / `ACtl.var(obj)` / `ACtl.var()` | ✅ | `chrome.storage.local`, z-bundle (`z(J,[...])`) executed in the file42 relay; dot-path nested objects |
| `ACtl.pubVar(...)` | ✅ | shared across all scripts; available as `<var.name>` in GUI actions |

## 3. Tabs

| API | Status | Comment |
|-----|--------|-------------|
| `ACtl.getTabIds(tabSpec[, mergeGroups])` | ✅ | presets (`#currWinTabs`, `#audibleTabs`, ...), filters, groups |
| `ACtl.getTabInfo([tabSpec])` | ✅ | iterable map `[tabId, TabInfo]` — z-bundle converted to an array of pairs |
| `ACtl.openURL(urls[, tabSpec|options])` | ✅ | `rightOf/leftOf/newWindow:'incognito'/'popup'`; returns an array of tabIds |
| `ACtl.closeTab([tabSpec])` | ✅ | |
| `ACtl.setTabState(tabSpec, states[, mode][, animate])` | ✅ | `active pinned selected muted focused minimized restored hidden topmost maximized fullscreen` |
| `ACtl.runInTab(tabSpec[, args], func)` / `(tabSpec, scriptName)` | ✅ | function serialized as `{FUNC: source}` → file42 → SW; top frame only. **FIXED 2026-08-05**: the result was lost — the nested execUserFunc carried the PARENT trigInstId without a `~`-suffix → SW dedup blocked it as foreign (parent in-flight); fix: `_A` (file48) appends `~`+random in the message itself |
| `ACtl.runInFrames(tabSpec, frameFilter[, args], func)` | ✅ | **fixed 2026-08-10 (sender.frameId)** — execUserFunc targets the SENDER's frame (`frameIds:[frameId]` instead of `[0]`), so a subframe's file42→FN→SW lands in THAT subframe (MV2 semantics). Frame filtering (depth/href/...) still runs per-frame in file42 (MV2 logic) |
| `ACtl.runInPageCtx([args,] func)` / `(file[, again])` | ✅ | **FIXED rounds 10-16**: callback runner `(c)=>{...}`; injection via `userScripts.execute({world:'MAIN'})` (round 11, TamperMonkey-style) — works even on strict CSP (example.org); return value — single-injection proxy (round 16: funcExecLstnr no-op + `/*AC-MV3-PROXY*/` answers `{response,funcName}` from the same context). VM 21:52 `PASS 2` (+14ms), full reinstall 22:01: PASS on old and fresh tabs |

## 4. Screenshot and clipboard

| API | Status | Comment |
|-----|--------|-------------|
| `ACtl.captureTab([tabSpec,][returnType])` | ✅ | `dataUri/binary/objectUrl/base64/blob/image/canvas`; as in the docs: window not minimized, tab activated; protected pages not captured |
| `ACtl.setClipboard(content)` / `({image})` / `({html[, sourceURL]})` | ✅ | via native (type 286): text / image / html / files (array of paths) |
| `ACtl.getClipboard()` / `('format')` / `('text')` / `(imageFormat[, returnType])` | ✅ | via native; image → canvas/image through a z-bundle in the USER_SCRIPT world (DOM available) |

## 5. Files and commands

| API | Status | Comment |
|-----|--------|-------------|
| `ACtl.getFile(loc[, returnType])` | ⚠️ | `text/json/dataUri/binary/base64` ✅; `html/image/canvas/...` ✅ (DOM in USER_SCRIPT world); **local file:// paths — only with "Allow access to file URLs" enabled** (as in MV2) |
| `ACtl.import(loc)` / `getFile(loc,'module')` | ✅ | blob URL + dynamic `import()` in the USER_SCRIPT world; `configureWorld` allows `blob: data:` (round 12), the module object is passed via a window marker (round 13) → works on any site, verified on example.org (strict CSP) |
| `ACtl.include(file[, type][, again])` | ✅ | injection into the **MAIN world** via userScripts (API injection, CSP-safe, like runInPageCtx) — works on strict CSP; "already included" cache |
| `ACtl.saveFile(path, content[, opts])` | ✅ | write via native; serialization of string/binary/Blob/Element/Image/Canvas/Object in the USER_SCRIPT world |
| `ACtl.saveURL(srcUrl, destPath)` | ✅ | verified: `<desktop>/<domain>/` |
| `ACtl.runCommand(cmd[, dir][, getOutput])` | ✅ | native type 260; `{exitCode, stdout}` |

## 6. Actions, events, misc

| API | Status | Comment |
|-----|--------|-------------|
| `ACtl.execAction(name|RegExp[, tabs])` | ✅ | presets `#goBackTabs #reloadTabs #clpbrdPaste ...` + custom actions by name (case-insensitive) |
| `ACtl.on(events[, tabSpec][, listener])` | ✅ | without a callback — await the event (verified `tabLoadEnd`); with a callback — acEvt relay in the USER_SCRIPT world; all 20 event types. **Race (as in MV2)**: if the event already happened before registration (e.g. `openURL('data:...')` — loads instantly), `await` hangs forever — events are not buffered. Use real URLs (network load) |
| `ACtl.off([events][, listener])` | ✅ | mechanism + `acEvt del` relay |
| `ACtl.expand(template[, tabSpec][, returnType])` | ✅ | all placeholders, multiple expansion, cartesian product |
| `ACtl.switchState(name[, state])` | ✅ | get/set/toggle; `undefined` if missing. **FIXED 2026-08-02**: crashed with `_if.binSwtch is not iterable` without created switches — `_Qj` patch in sw.js adds the `binSwtch:[]` default. **Round 18 (2026-08-04)**: the patch no longer fabricates `customEntities` (that wiped all scripts from storage via `_Mi` write-back) — it only fills `binSwtch` inside an existing object |
| `ACtl.sleep(ms)` | ✅ | |
| `ACtl.favoriteTabs` / `ACtl.getEnv` / `ACtl.natMsg` | ⚠️ | present in `W()` (outside the official docs sidebar); work through the same bridges; unverified |

## 7. General MV3 limitations (Chrome 150+)

1. **Protected pages** (`chrome://`, Web Store, `chrome-extension://`, devtools) —
   scripts do not run there (`userScripts` does not work) and are excluded from
   `runInTab`/`runInFrames`/`captureTab` — the same thing the docs call
   "protected pages" in MV2.
2. **file:// access** — CANNOT be requested programmatically (no such API —
   `chrome.permissions.request` does not cover the file scheme; only
   `chrome.extension.isAllowedFileSchemeAccess` exists, but from the USER_SCRIPT
   world `chrome` is unavailable). Requires the **"Allow access to file URLs"**
   toggle on `chrome://extensions` (`host_permissions <all_urls>` is already in
   the manifest). The `ACtl.getFile` test prints a hint about this on failure.
   **FIXED 2026-08-10 (§7-8)**: the SW reads the REAL toggle value (prelude
   pass-through of `chrome.extension.isAllowedFileSchemeAccess`, which exists
   in the MV3 SW) → with the toggle ON, file:// tabs are targetable by
   `ACtl.runInTab`/`runInFrames` (MV2 parity); with it OFF they stay excluded.
   ⚠ The gate is read once per SW load — reload the extension after toggling.
3. **Page CSP** (relevant after rounds 11-13):
   - USER_SCRIPT world is **exempt from the page's CSP** ("exempt from the page's
     CSP", developer.chrome.com/docs/extensions/reference/api/userScripts) →
     eval and the whole ACtl bridge work even on strict CSPs;
   - **MAIN world** — injection via `userScripts.execute({world:'MAIN'})`
     (round 11, like TamperMonkey): API injection runs directly, the inline-
     CSP check is NOT applied → `runInPageCtx`/`include` work on strict CSPs.
     Remaining: `eval` INSIDE a user function in the MAIN world is cut by the
     page CSP without `unsafe-eval` (as in MV2);
   - **blob:/data:** in the USER_SCRIPT world are allowed via `configureWorld`
     (round 12: `script-src 'self' 'wasm-unsafe-eval' blob: data:`) →
     `import` works on any site;
   - In practice: `example.org` — strict CSP, all 23 API tests pass
     (including the `runInPageCtx(func)` return value — round 16).
4. **~~`runInFrames` subframes~~** — SOLVED 2026-08-10: execUserFunc now uses
   `sender.frameId` (`frameIds:[frameId]`); subframe calls execute in their own
   frame (previously frame 0). No bundle rebuild (sw.js only). mh_test B37.
5. **Background scripts** — via the offscreen sandbox (`file23.html`); they live
   as long as the SW lives (may sleep) — MV2 lived as long as the browser.
6. **Dynamic `import()`** — executed in the USER_SCRIPT world (SW-classic
   cannot do dynamic import); blob:/data: allowed via `configureWorld`
   (round 12).
7. **Window not minimized** for `captureTab` — as in the docs (MV2 same).
8. **The script lives as long as the page** — as in the docs; `unload` kills
   the script (except background).

## 8. Test

`../Test/SCRIPTING-API-TEST.js` — self-test of all main APIs (run via
RUN SCRIPT on any normal page). Result 2026-08-04 (after rounds 11-18):
- **The site CSP no longer matters**: `import`, `runInPageCtx` (execution) and
  `include` work even on example.org (strict CSP).
- **Scripts survive `ACtl.var`/`pubVar`** (round-18: previously the first var
  wiped ALL settings via `_Qj`-fabrication + `_Mi` write-back).
- Expected **23/23 PASS** on any page (verified: full reinstall
  2026-08-06 22:01 — 23/23 on old and fresh tabs, without reloads).
  Previously failing items closed: `runInPageCtx(func)` return (round 16,
  single-injection proxy) and `runInTab(func)` `[null]` (2026-08-05,
  `~`-suffix in `_A`).
- `getFile` of a LOCAL file — only with the "Allow access to file
  URLs" toggle on chrome://extensions (as in MV2), the test prints a hint.

## 9. Known port degradations (what to fix)

1. **(solved 2026-08-10) `runInFrames` subframes** — root cause: file42 in a
   subframe → FN (eval forbidden in isolated worlds, Chrome 133+) → SW
   `execUserFunc` → `userScripts.execute({target:{tabId, frameIds:[0]}})` → the
   funcCode ran N times (once per matching frame) but ALWAYS in the TOP frame
   (location/document = top frame). Fix: `sender.frameId` (MV3 provides it for
   content-script messages) → `frameIds:[frameId]` — subframes execute in their
   own frame; plain script runs (frame 0) unchanged. frameFilter (depth/href/…)
   stays in file42 (per-frame, MV2 logic); result aggregation via the existing
   `frmCBId`/pongId mechanism (unchanged). Note: the executed world is
   USER_SCRIPT (isolated) — same as runInTab; DOM of the subframe is reachable.
   Remaining edge: `ACtl.runInPageCtx` INSIDE a runInFrames func still routes
   to frame 0 (execMainWorld has no frame info yet) — compound, rare.
2. **(solved) `runInPageCtx(func)` return value — MV3 world isolation**
   - W()'s mechanism (listener A + `var m=fn` B + reading `window[m]` by name)
     requires a SHARED global between injections. In MV2 both were `<script>`
     in one MAIN world (synchronous) — it worked. In MV3 each
     `userScripts.execute` is a separate context (different VMs), code in a
     function scope, asynchronous → `window[m]` in A never sees m from B.
     Neither buffering nor ordering helps.
   - Tampermonkey does not have this problem: its `unsafeWindow` is a direct
     reference to the page global (synchronous access, no function injection
     and no bridge). It has NO analog of `runInTab(func)`.
   - **SOLVED (round 16, 2026-08-06; sw.js only, bundle unchanged)**: a
     single-injection proxy in jsCode — `runInPageCtx("funcExecLstnr", fn)`
     is NO-OP (otherwise listener A answers first with the wrong error and wins
     the channel race); `{code:'var m=<fn>'}` replaced by one self-contained
     `/*AC-MV3-PROXY*/` injection that sets window.m, listens for
     `{funcName:m,args}` itself and answers `{response,funcName}` from THE SAME
     context (closure over F — no cross-injection window[m] lookup). Ends with
     `void 0`. ⚠ jsCode is a template literal: double the backslashes of
     regex/string escapes (`\s`, `\"` — ES2018 "forgives" invalid escapes,
     node --check stays silent). VM 21:52: `PASS 2` (+14ms); full reinstall
     22:01: PASS on old and fresh tabs.
3. **(solved) `runInPageCtx` on strict CSP** — ✅ rounds 11-15: injection via
   `userScripts.execute({world:"MAIN"})` (TamperMonkey-style, inline-CSP not
   applied). Only one limitation remains: `eval` inside a user function in the
   MAIN world is cut by page CSP without unsafe-eval (as in MV2).
4. **(solved) `import`/`getFile('module')` on strict CSP** — ✅ rounds 12-13:
   `configureWorld` with blob:/data: + module bridge via a window marker →
   import works on any site.
5. **(solved) `runInTab(func)` → `[null]` — FIXED 2026-08-05**
   - ROOT CAUSE: a nested runInTab/runInFrames execUserFunc carried the PARENT
     `trigInstId` without a `~`-suffix → the dedup key `tabId:scriptId:trigInstId`
     = the parent's key → SW dedup saw the parent in-flight → block → `[null]`
     (in the log: `dedup key=1727756556:script:1:4/7/10/13` exactly at the
     runInTab moment).
   - FIX: `_A` (file48, in the bundle) appends `~`+random to trigInstId RIGHT IN
     THE MESSAGE — the nested call gets a unique key ≠ the parent's; the n()
     retry sends the same message (same suffix → the retry duplicate is still
     dedup'ed). Bundle rebuilt (size=233106), mh_test 18 pass / 0 FAIL.
- Real port limitations (fixed): `runInFrames` subframes (§7-5), `runInPageCtx(func)` return (§7-6).
- **IMPORTANT**: the test is stored in the AutoControl settings as script text
  (`srcCode`) — after editing the file you must RE-COPY it into RUN SCRIPT
  (the extension update does not update the saved script!).
