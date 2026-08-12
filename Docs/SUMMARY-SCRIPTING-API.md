# AutoControl MV3 — Scripting API summary (2026-08-02/04)

> Full chronology of fixing the scripting API in the MV3 port (SW-brain).
> Test: `../Test/SCRIPTING-API-TEST.js` (23 checks), run via RUN SCRIPT.

## Current state (updated 2026-08-06 — port complete)

**Test result: 23/23 PASS** — confirmed by a FULL REINSTALL
(VM 22:01, 2026-08-06): extension + native removed and installed again,
23/23 on old (self-heal via the guard) and fresh tabs, WITHOUT reloads.
Scripts survive `ACtl.var`/`pubVar` (round 18 — storage write-back safety).
All previously failing items are closed:

| Former FAIL | Status |
|---|---|
| `ACtl.runInTab(func)` → `[null]` | **FIXED 2026-08-05** — the nested execUserFunc carried the parent `trigInstId` without a `~`-suffix → SW dedup blocked it as foreign; `_A` (file48) appends `~`+random in the message |
| `ACtl.runInPageCtx(func)` → `window[u.data.funcName] is not a function` | **FIXED 2026-08-06 (round 16)** — single-injection proxy in jsCode (funcExecLstnr no-op + `/*AC-MV3-PROXY*/` answers from the same context); VM 21:52 `PASS 2` (+14ms) |

**Works (23/23 checks green):**
- Constants: `TAB_ID`, `STOP_CHAIN`/`STOP_FULL_SEQ`
- Variables: `var`, `pubVar` (✅ survive a settings refresh — round 18)
- Tabs: `getTabIds`, `getTabInfo`, `openURL`, `on`, `setTabState`, `closeTab`, `runInTab` (run), `runInPageCtx(file)`
- Screenshot: `captureTab`
- Clipboard: `setClipboard`, `getClipboard` (native puts text+html — the test accepts both)
- Files: `saveURL`, `saveFile`, `getFile` (local — with "Allow access to file URLs" enabled), **`import`** (✅ works on any site, including strict CSP!)
- Actions: `execAction`, `runCommand`, `expand`, `switchState`, `include`

**Fully working "Take a shot" scenario** (verified by the user earlier): captureTab → setClipboard → openURL → on → setTabState → execAction → snipboard.io.

## Chronology of fix attempts (rounds 1–16)

### Round 1 — `ACtl is not defined`
- **Symptom**: the script fails on `ACtl.saveURL` — `ReferenceError: ACtl is not defined`.
- **Cause**: the MV2 original executed code via `new Function("ACtl",...)` + direct `eval`, which captured `ACtl` in a closure. MV3 (userScripts USER_SCRIPT world) passed the proxy as `arguments[0]` → the free variable `ACtl` did not resolve. Plus file42 `FN(funcCode)` without `ACtl`.
- **Fix**: sw.js jsCode — `var ACtl = __acActl;` inside the IIFE; file42.js — `FN(a, ACtl)`.

### Round 2 — `userAPI handler not loaded`
- **Symptom**: `ACtl.saveURL` → "userAPI handler not loaded".
- **Cause**: `_Yh` — a top-level `let` from file48 → a global LEXICAL binding, NOT a `self` property → `typeof self._Yh` always undefined. Plus `_Yh` returns a **callback runner** (`_us` in file67), not a Promise.
- **Fix**: sw.js — the free variable `_Yh` + call `_Yh(msg, tab)(onOk, onErr)`.

### Round 3 — `a.getResponseHeader is not a function`
- **Symptom**: `ACtl.saveURL` fails while reading headers.
- **Cause**: the XHR shim in sw_prelude (fetch-backed) lacked `getResponseHeader`/`responseURL` — file70 `_Su()` and file77 `O()`/`saveURL` crashed.
- **Fix**: sw_prelude.js — `getResponseHeader`/`getAllResponseHeaders`/`responseURL`. **Bundle rebuilt** (232 060 chars).

### Round 4 — `(intermediate value) is not iterable` (shared layer)
- **Symptom**: `let [[, dataUri]] = await ACtl.captureTab(...)` → not iterable.
- **Cause**: file77 `W()` returns **z-bundles** `{funcCode, args}`; the file42 relay in MV3 did not execute them (forwarded only result/error) → `undefined`.
- **Fix**: file42.js — execute z-bundles in the acUserApi relay + a unique `~`-suffix for trigInstId (dedup protection); sw.js — `on` handled locally + acEvt bridge for events; file42 — event relay.

### Round 5 — `Object.defineProperty called on non-object`
- **Symptom**: "Take a shot" fails on captureTab.
- **Cause**: the FN wrapper dropped the first argument (`slice(arguments,1)`); u() did not await the FN Promise; `__post` did not clone a result with a generator (Symbol.iterator); `ACtl.on` returned a pending Promise.
- **Fix**: file42.js — `slice(arguments)`, await in the funcCode branch; sw.js — iterable→array in `__post`; `on` — locally in the USER_SCRIPT world.

### Round 6 — `ACtl.setClipboard: (intermediate value) is not iterable`
- **Symptom**: after round 5 setClipboard fails.
- **Cause**: nested FNs (F→K) used the parent's `x.__cur` → the dedup key matched the in-flight parent → SW answered `dedup` → `undefined`.
- **Fix**: file42.js — a unique `~`+random suffix in both nested paths.

### Round 7 — clipboard overwritten with "undefined" (E007 on snipboard.io)
- **Symptom**: "Take a shot" works in the logs, but snipboard.io says: "image data was not found on your clipboard".
- **Cause**: **double userAPI handler** — mine in sw.js (round 2) + the bundle's file48 `m()` (registers onMessage in the SW on importScripts). Both called `_Yh`→`W`→`F→K`; the second K got `undefined` after `delete window[e]` → 286 with the text "undefined" overwrote the clipboard.
- **Fix**: sw.js — `if (msg.type === "userAPI") return false;` — the single handler is the bundle's m(). Proven in mh_test.js: `userAPI dispatch: 1 answered of 1 listeners`.

### Round 8 — `runInPageCtx` ReferenceError (missing in USER_SCRIPT world)
- **Symptom**: `ACtl.runInPageCtx(() => 1+1)` → ReferenceError.
- **Cause**: W() calls runInPageCtx via F() → executed in the USER_SCRIPT world, but it was only defined in file42 (isolated world) — different windows.
- **Fix**: sw.js jsCode — `window.FN` (eval) + `window.runInPageCtx` (script element in MAIN world).

### Round 9 — the test hung on `ACtl.on` (race in the TEST, not the port)
- **Symptom**: openURL(data:) → tabLoadEnd happened BEFORE the on registration → infinite await.
- **Cause**: events are not buffered (as in MV2); data: loads instantly.
- **Fix**: the test — a real URL + 8s timeout.

### Round 10 — `switchState: _if.binSwtch is not iterable` + runInPageCtx DataCloneError
- **Symptom**: 18/23. switchState fails without created switches; runInPageCtx — DataCloneError on the function result.
- **Cause**: `_if`=customEntities without the `binSwtch` key; `runInPageCtx` returned the wrong type (not a callback runner), W()'s FUNC branch returned a function `q`.
- **Fix**: sw.js — `_Qj` patch (guarantee `binSwtch:[]`); jsCode — runInPageCtx as a callback runner + `p(__post)` for function results.

### Round 11 — runInPageCtx → chrome.userScripts (TamperMonkey-style)
- **Symptom**: runInPageCtx(file) blocked by strict CSP (inline `<script>`).
- **Cause**: a `<script>` element in the MAIN world is an inline script → page CSP without `unsafe-inline` cuts it.
- **Fix**: bridge USER_SCRIPT → postMessage(acMainWorld) → file42 → SW(execMainWorld) → `userScripts.execute({world:"MAIN"})` — API injection is not inline → CSP not applied. File form via fetch → inject as code.

### Round 12 — `runInPageCtx(func)` var scope + import world-CSP
- **Symptom**: 21/23 — runInPageCtx(func) `window[u.data.funcName] is not a function`; import blob: cut even without page CSP.
- **Cause**: userScripts.execute wraps the code → `var m` did not reach window; import was cut by the USER_SCRIPT world's own CSP (default = ISOLATED, without blob:).
- **Fix**: jsCode — `var X =` → `window.X =`; sw.js — `__acEnsureWorld()` → `configureWorld({csp: "... blob: data: ..."})`.

### Round 13 — `import` DataCloneError `[object Module]`
- **Symptom**: import LOADED (round 12), but `DataCloneError: [object Module] could not be cloned`.
- **Cause**: a module namespace object is not structured-cloneable → postMessage throws.
- **Fix**: jsCode `__post` — detect `[object Module]` → stash on `window.__acmod_*`, send the marker `{__acModule}`; the proxy handler swaps the marker back (same USER_SCRIPT world). **import works** ✅.

### Round 14 — runInPageCtx(func) RACE (the buffer in the IIFE did not work)
- **Symptom**: 21/23 — runInPageCtx(func) still fails; include flaky (cache).
- **Cause**: every jsCode injection re-wrapped postMessage → the last wrapper with an empty pending state never buffered (a chain of 10+ wrappers VM425..VM442 in the log).
- **Fix**: buffer on window (`__acPendingVar`/`__acVarQueue`) + `__acPostWrapped` guard; the test — include with a unique URL. **NOT COMPLETE** (see round 15).

### Round 15 — runInPageCtx(func) DIFFERENT MAIN world CONTEXTS (current)
- **Symptom**: 21/23 — the postMessage wrapper is now SINGLE ✅ (visible `window.postMessage @ VM494:61`), but `window[u.data.funcName] is not a function` remains.
- **Cause (main, current understanding)**: `funcExecLstnr` (listener, injection A) and `window.m` (function, injection B) execute **in DIFFERENT MAIN world contexts** — in the log `hnd @ VM512:96` (A) and `B @ VM507:1` (B) — different VMs. `window.postMessage` is shared between them (that is why the listener catches the message), but **`window` as an object is NOT shared** (each injection has its own isolated MAIN-world window? — no; but the fact: `window[m]` in A does not see m from B). Buffering and ordering do not help — W()'s mechanism (var on window + read by name) is incompatible with inter-injection isolation.

### Round 17/18 — storage REGRESSION: `_Qj` fabricated `customEntities={}` (2026-08-03/04)
- **Symptom (round 17, 2026-08-03)**: after an API-test run the next runScript
  returned OK in 1ms without execUserFunc; the script disappeared from the settings after a refresh.
  "Hello world" did not trigger it — only tests with `ACtl.var`/`pubVar`.
- **Cause**: the round-17 `_Qj` patch (`if (!r.customEntities) r.customEntities = {}`)
  fabricated an empty `customEntities` in ANY storage read result.
  `_Mi()` (batched write via `_bd()`) writes the WHOLE read object back
  → the empty customEntities WIPED all scripts/triggers/gestures.
- **Fix (round 18, 2026-08-04)**: the patch only fills `binSwtch:[]` INSIDE
  an already-existing `customEntities` — never creates the key. Test A14
  (mh_test.js); 5+ API-test runs — scripts survive var/pubVar ✅.

### Round 16 — DIAGNOSIS CONFIRMED: the MV3 sandboxes are the culprit (2026-08-03)
- **Conclusion (confirmed by log analysis + Chrome docs)**: it is exactly the MV3 world isolation that breaks W()'s `runInPageCtx(func)` mechanism. The mechanism relies on a **shared mutable global between two pieces of code** (injection A hangs a listener, injection B does `var m = fn`, postMessage → A reads `window[m]`).
- In MV2 both `<script>`s ran **in one MAIN world, synchronously** → `window.m` is guaranteed visible, the order is deterministic.
- In MV3 every `userScripts.execute` creates a **separate execution context** (different VMs in DevTools) + the code is **wrapped in a function scope** (round 12) + execution is **asynchronous** (round 14). Result: **a shared global between injections is unavailable** — neither buffering nor ordering helps.
- **Comparison with Tampermonkey** (why it does not have this problem):
  - Tampermonkey uses **`unsafeWindow`** — a direct reference to the page's global object (MAIN world). Access to page functions/globals is **synchronous, without function injection and without awaiting a result** through a bridge. Therefore the return value is plain JS (`let x = unsafeWindow.fn()`), and the "different contexts" problem does not arise at all.
  - Tampermonkey has **no** analog of `runInTab(func)` (a script is bound to one page by `@match`; the closest is `GM_openInTab` — opens a tab, but does not execute code in it). `runInTab`/`runInFrames` are unique AutoControl features.
- **PLAN (not implemented) — single-injection proxy (Tampermonkey approach)**:
  - Do not rely on a shared `window.m` between injections. **One injection per call**:
    ```js
    (function(){
      try { var r = <funcSource>.apply(null, <args>); }   // in the MAIN world, sees page globals
      Promise.resolve(r).then(
        res => window.postMessage({type:"acMainWorldRes2", id, result: res}, "*"),
        err => window.postMessage({type:"acMainWorldRes2", id, error: String(err&&err.message||err)}, "*")
      );
    })();
    ```
  - The function and the result — **in one context**; the result goes out via postMessage immediately from the same context (cross-world, like acEvt/acUserApi). The race and "different VMs" disappear.
  - **Intercept without changing the bundle**: W()'s FUNC branch sends `{code: 'var m = <fn>'}` + `postMessage({funcName:m})`. In our jsCode `window.runInPageCtx` catch the `{code}`-form of the kind `var m = <fn>` → instead of "create window.m", execute the function directly and return the result through the `acMainWorldRes2` bridge (the proxy in the USER_SCRIPT world replaces the answer for W()'s local listener via `{funcName, response}` — W()'s callback `q` expects exactly `{response, funcName}`).
  - The file form and `runInPageCtx(file)` already work (single-injection) — do not touch.

### NOT fixed (outside the scripting API) — see FEATURES-MV3.md §7
- Install: ~~copies `AutoControlZero.exe` instead of `AutoCtrl_2025.4.22.0.exe`~~ —
  **SOLVED 2026-08-04** (engine auto-deploy: poll → unpack → poll on the same
  port; root cause "flashed and vanished" = our `del /Q /F` — the native acks
  type 260 when cmd.exe STARTS, ~7ms).
- `runInTab(func)` → `[null]` — ~~diagnosed 2026-08-04~~ **SOLVED
  2026-08-05** (`~`-suffix in `_A`, file48).
- Emergency Repair does not work.
- `runInFrames` subframes (SW injects frame 0 only).
- playAudio (file53) — needs offscreen.
- Toasts `_Cr` invisible; toolbar icons `_6t` empty.
- Cyrillic in code comments (rule — English only).
- ~~Example snag.gy → snipboard.io in file48.js~~ — **SOLVED 2026-08-05**
  (the "Take a shot" example now opens https://snipboard.io; bundle rebuilt,
  mh_test 18 pass / 0 FAIL).

## Final assessment (updated 2026-08-06)

- **The port is functional and complete**: **23/23** API tests PASS — verified
  by a full reinstall (VM 22:01: old and fresh tabs, without reloads). Former
  FAILs closed: `runInPageCtx(func)` return (round 16, single-injection proxy)
  and `runInTab(func)` `[null]` (2026-08-05, `~`-suffix in `_A`).
- **Scripts survive `ACtl.var`/`pubVar`** (round 18 — storage write-back
  safety).
- **import/getFile('module') — works on any site** (including strict CSP) —
  a unique achievement of the port.
- Open port items (not API regressions): `runInFrames` subframes (§7-5),
  playAudio (§7-1), Save URL notif/copy (§7-2), toasts (§7-10) and others —
  see FEATURES-MV3.md §7.
- Documentation: ../AGENTS.md (per-round gotchas), FEATURES-MV3.md,
  SCRIPTING-API-SUMMARY.md (§7 CSP, §9 degradations), FEATURES-MV3.md §7, session memory.
