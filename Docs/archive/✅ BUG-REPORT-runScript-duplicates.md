# Bug Report: runScript fires multiple times per key press + delayed execution

- **Date:** 2026-08-02
- **Build:** MV3 port (`../mv3-build/`, unpacked, SW-brain architecture)
- **Chrome:** 150 (Windows)
- **Affected feature:** Run Script action (`runScript`) executed via `chrome.userScripts` (USER_SCRIPT world)
- **Trigger under test:** Ctrl+M hotkey → runScript action, script body `console.log('aaaa')` etc.
- **Severity:** High (duplicate executions, multi-second delays, action queue pile-up)

---

## 1. Symptoms

1. **One key press → multiple executions.** A single Ctrl+M occasionally runs the script 2–4×.
2. **Presses < firings.** 9 presses produced **18 executions**: 9 singles (one per press) **plus a burst of 9 in the same millisecond**, ~1.6 s after the last press.
3. **Delayed completion.** The runScript action takes **3.6–11.2 s** to complete (`OK`) after it starts (`ACT`), even though the script itself executes in <1 ms.
4. **Queue pile-up.** While a runScript is "running", every additional press is queued (`QUEUE busy → queued`); the queue drains serially, one script per ~4 s.

---

## 2. Reproduction

1. Load `../mv3-build/` as unpacked extension (Chrome 150+, "Allow user scripts" toggle ON).
2. Create a script: `console.log('aaaa');` (plus a timestamp variant for correlation).
3. Bind a hotkey (e.g., Ctrl+M) to a trigger whose action is Run script.
4. Open DevTools console on the target page (any page with iframes; the settings page also works).
5. Press the hotkey 9 times with ~3–4 s intervals.
6. Observe: 9 `aaaa` (one per press) + **9 more `aaaa` all at the same timestamp**.

---

## 3. Evidence

### 3.1 Page console — 9 presses → 18 executions

```
05:48:36.604 VM358:31 aaaa   ← press 1 (queued, executed)
05:48:40.852 VM359:31 aaaa   ← press 2
05:48:47.604 VM360:31 aaaa   ← press 3
05:48:51.245 VM361:31 aaaa   ← press 4
05:48:55.356 VM362:31 aaaa   ← press 5
05:48:58.995 VM363:31 aaaa   ← press 6
05:49:01.027 VM364:31 aaaa   ← press 7
05:49:02.276 VM365:31 aaaa   ← press 8
05:49:04.512 VM366:31 aaaa   ← press 9
05:49:06.094 VM376:31 aaaa   ← BURST: 9 executions, same ms
05:49:06.094 VM377:31 aaaa
05:49:06.095 VM378:31 aaaa
05:49:06.095 VM379:31 aaaa
05:49:06.095 VM380:31 aaaa
05:49:06.095 VM381:31 aaaa
05:49:06.095 VM382:31 aaaa
05:49:06.096 VM383:31 aaaa
05:49:06.096 VM384:31 aaaa
```

Note: every `chrome.userScripts.execute` call creates a **new VM context** (VM358…384) →
the burst is 9 real `userScripts.execute` invocations, not console re-prints.

### 3.2 SW log — presses and queue

```
05:48:36.600 [AC-ACT] #9 TRIG trigger=14 +0ms          ← press 1
05:48:36.601 [AC-ACT] #9 ACT action=runScript run#1 +1ms
05:48:36.727 [AC-ACT] #9 QUEUE trigger=34 busy → queued +127ms
05:48:39.499 [AC-ACT] #9 QUEUE trigger=14 busy → queued +2899ms   ← press 2
05:48:39.635 [AC-ACT] #9 QUEUE trigger=34 busy → queued +3035ms
...
05:49:03.111 [AC-ACT] #9 QUEUE trigger=14 busy → queued +26511ms  ← press 9
05:49:03.309 [AC-ACT] #9 QUEUE trigger=34 busy → queued +26708ms
05:49:04.511 [AC-ACT] #9 ACT action=runScript run#9 +27911ms
05:49:07.015 [AC-ACT] #9 QUEUE trigger=34 busy → queued +30415ms  ← run#9 STILL RUNNING
```

- Each press fires trigger 14 (runScript) + companion trigger 34 (activateTabs) ~130–200 ms later.
- All presses queue because the previous runScript has not completed.
- `run#9` still had **no `OK`** 2.5 s after its script executed — result round-trip is slow/hanging.

### 3.3 SW log — one press executed 4× (earlier test, 05:37)

```
05:37:07.054 [AC-ACT] #4 ACT action=runScript run#2 +3630ms
05:37:07.055 execUserFunc → userScripts.execute (tab 338978978)
05:37:09.139 execUserFunc → userScripts.execute (tab 338978978)   ← ×3 more
05:37:09.139 execUserFunc → userScripts.execute (tab 338978978)
05:37:09.139 execUserFunc → userScripts.execute (tab 338978978)
05:37:09.744 [AC-ACT] #4 OK action=runScript +6320ms
```

One queued press → 4 `execUserFunc` calls in the same tab: 1 immediate + 3 delayed ~2 s.

### 3.4 SW log — completion delays

```
#2 ACT runScript run#1 +1ms      → OK +3622ms   (3.6 s)
#3 ACT runScript run#1 +1ms      → OK +11215ms  (11.2 s)
#4 ACT runScript run#1 +1ms      → OK +6320ms   (6.3 s)
```

The script is `console.log('aaaa')` — it executes in <1 ms. The 3.6–11.2 s is infrastructure latency
(`userScripts.execute` + result round-trip), not script runtime.

---

## 4. Architecture facts (established)

- **Delivery path:** `_To` → `_gr` → `_Ue` → `_A` → `_xj` → `n()` (file48) → `tabs.sendMessage(tabId, msg, {frameId:0})` → file42 (main frame) → `FN` → `execUserFunc` (`runtime.sendMessage`) → SW → `chrome.userScripts.execute({world:"USER_SCRIPT"})` → script runs → result posted back via `window.postMessage(acUserApiRes)` → file42 → `sendResponse` → action `OK`.
- **`trigInstId`:** native sends **no** `trigInstId` for keyboard triggers (wire data is `{"id":20681}` only). The action-level instance id comes from `_Ai()` in `_rf` — **unique per action invocation** (per queued press).
- **`n()` retry loop (file48):** if `tabs.sendMessage` returns `undefined` (no responding file42 listener), it injects `file42.js` via `_wj` and **re-sends** — each re-send re-executes the script.
- **Frames:** file42 can be loaded in every frame of the tab; messages without `frameId` reach all frames. `n()` uses `frameId:0`; the all-frames path `r()` is used only when `frmFlt` is set (currently traced as `undefined` for the runScript action — but the 4× evidence suggests multi-frame delivery or retry re-delivery).

---

## 5. Current mitigations in place (incomplete)

| File | Change | Covers |
|---|---|---|
| `file37.js` | `[AC-ACT]` diagnostics: `TRIG`/`QUEUE`/`ACT run#N`/`OK` + ms | observation only |
| `file42.js` | `execUserFuncDone` sent to SW when a run finishes | releases dedup key |
| `sw.js` | In-flight dedup: key `tabId:scriptId:trigInstId` (Set, 60 s TTL), duplicates → `{ok, dedup:true}` + `DEDUP` log | **only concurrent** duplicates of the same press |

**Why the current dedup does NOT fix symptom 2 (9 presses → 18):**
the burst of 9 arrives **after** their actions completed; `execUserFuncDone` already released the keys →
the in-flight check passes → they execute. Estimated effect: 18 → ~17 executions. Not a fix.

---

## 6. Root-cause hypotheses

1. **`n()` retry loop (file48) re-sends the script** when the first `tabs.sendMessage` gets no response
   (file42 not yet loaded / tab busy). Each re-send executes the script again. The ~2 s delay between the
   first execution and the burst matches the file42 injection latency observed in earlier tests.
2. **Chrome queues `userScripts.execute`** while the tab is busy/navigating and flushes all pending calls
   in one tick → the "same millisecond" burst of 9.
3. **Multi-frame delivery**: every frame that has file42 executes the script when the message reaches it
   (matches the 4× single-press case at 05:37). Unclear how this happens given `n()` uses `frameId:0` —
   needs verification (shimmed `tabs.sendMessage`? frame list changed?).
4. **Slow result round-trip** (3.6–11.2 s): the `acUserApiRes` postMessage / `sendResponse` path is
   delayed or the `userScripts.execute` promise itself is slow — this is what makes the queue pile up
   and turns 9 presses into 9 queued "hanging" actions whose tails all fire together.

---

## 7. Open questions (need instrumentation)

- Do the burst executions carry the **same `trigInstId`** as their originating press?
  → Add `ctx.trigInstId` to the `execUserFunc` SW log and to the `DEDUP` verdict log.
- Does `n()` actually hit the `undefined`-response retry? → Log when `h === undefined` in `n()`.
- Is the 9-burst = 9 frames of the page, or 9 re-deliveries of the 9 presses?
  → Correlate burst size with page frame count and with press count.

## 8. Proposed fix direction

- **Extend dedup to completed runs:** keep a bounded LRU (≈50) of recently **completed**
  `tabId:scriptId:trigInstId` keys; suppress any re-arrival of the same key, even after completion.
  Safe because a new press gets a **new** `trigInstId` (from `_Ai()`), so legitimate re-presses are never blocked.
- **Fix the source:** prevent `n()` re-delivery (respond promptly, avoid re-send when the message was
  already delivered) and/or make delivery single-shot per action instance.
- **Investigate the round-trip latency** (3.6–11.2 s) — possibly `userScripts.execute` itself or the
  postMessage bridge — since it is what causes queue pile-up in the first place.

---

## 9. Fixes Applied (2026-08-02)

### Fix 1: Trigger-level dedup (file37.js → bundle)

- **Problem:** Native host sends **two triggers per hotkey press** (14 + 34, ~100 ms apart), both with identical actions. With 9 presses → 18 triggers queued.
- **Fix:** In `_6y` (queue entry), when `_2y.length > 1` (queue busy), **drop** the new trigger immediately:
  ```javascript
  a:if(_2y.push([a,b]),1<_2y.length){
    const _busy=_2y.length>1;
    if(_busy){__acLog('DUP','trigger='+a+' queue busy('+_2y.length+') → dropped');_2y.pop();return;}
  ```
- **Log marker:** `[AC-ACT] #N DUP trigger=X queue busy(K) → dropped`
- **Effect:** 9 presses → 9 executions (was 18). Race condition eliminated.

### Fix 2: Window enumeration cache (file37.js → bundle)

- **Problem:** `_Rf` calls `_Fu` (window/tab enumeration via `chrome.windows.getAll({populate:true})`) **before every action**. `_Fk=true` is set after every action in `_rf`. This heavy API call adds ~2 s per cycle.
- **Fix:** Cache enumeration results; skip `_Fu` if called within 200 ms:
  ```javascript
  let __acLastEnum=0;const __acEnumCacheMs=200;
  var _Rf=_we(function*(a=!1){if(a||_Fk){const _now=Date.now();if(_now-__acLastEnum>__acEnumCacheMs){__acLastEnum=_now;yield b=>_Fu(b)}_wd();_Fk=!1}});
  ```
- **Effect:** Per-cycle delay reduced from ~2.3 s to ~1.5 s.

### Fix 3: Action queue watchdog (sw.js, not in bundle)

- **Problem:** If the queue gets stuck (e.g., `runScript` never returns `OK`), all subsequent triggers hang.
- **Fix:** 5 s watchdog timer in sw.js: if no `[AC-ACT] ... OK` for 5 s and queue > 0, force-shift + resume:
  ```javascript
  if (queueLen > 0 && Date.now() - __acLastOkTime > 5000) {
    _2y.shift(); _6y();
  }
  ```
- **Log marker:** `[AC-WATCHDOG] Queue stuck! K items → force-shift`
- **Effect:** Prevents complete freeze.

### Post-fix status (2026-08-02)

| Symptom | Before | After | Status |
|---|---|---|---|
| Duplicates (18 executions for 9 presses) | 18 | 9 | ✅ Fixed (trigger dedup) |
| Queue freeze / crash | Frequent | None | ✅ Fixed (dedup + watchdog) |
| Per-cycle delay | ~2.3–4.1 s | ~1.5 s | ⚠️ Partial (enum cache) |
| Fast pressing (<1.5 s interval) | Queue pile-up | Dropped (not executed) | ⚠️ Expected behavior (dedup drops while busy) |

**Remaining limitation:** pressing faster than ~1.5 s drops the trigger (`DUP → dropped`). This is a side-effect of the trigger dedup: while the queue is busy (one cycle ~1.5 s), new triggers are discarded. To fully remove it you would either drop the dedup (duplicates come back) or optimize the cycle to <500 ms.

---

## 11. Fix round 2 (2026-08-02) — fast re-press support + round-trip instrumentation

**Goal:** presses faster than 1.5–2 s are no longer lost; find the residual round-trip delay.

### Fix 4: Queueing instead of blanket drop (file37.js → bundle)

- **Problem:** Fix 1 dropped **all** triggers arriving while the queue was busy → fast re-presses were lost.
- **Root cause of duplicates (refined):** the native sends **two different trigger ids per one physical press** (e.g. 14 and 34, ~127 ms apart, identical actions). Re-pressing the same hotkey = **the same trigger id**.
- **Fix:** companion-detect by `(id, time)`: only the second trigger of a pair (a different id arriving <300 ms after the last accepted one) is dropped. Real re-presses (same id) are **queued** and executed.
  ```javascript
  let __acLastTrigId=-1,__acLastTrigTime=0;const __acCompanionMs=300;
  // in the busy branch of _6y:
  if(a!==__acLastTrigId&&_now-__acLastTrigTime<__acCompanionMs){__acLog('DUP','companion=...');_2y.pop();return;}
  ```
  `__acLastTrigId/Time` is updated ONLY for accepted triggers (not for dropped ones) — otherwise a re-press of 14 after a dropped 34 would be mistaken for a companion.
- **Overflow cap:** `_2y.length>8` → drop the oldest queued one (`_2y.splice(1,1)`) — protection against key-repeat floods (30–60 ms).
- **Logs:** `DUP companion=X (last=Y, Nms) → dropped`, `DROP queue overflow(N) → drop oldest`.
- **Effect:** fast presses run serially (none lost); 14/34 pair duplicates are still suppressed.

### Fix 5: Enum cache 300 → 1500 ms + measurement (file37.js → bundle)

- **Problem:** `_Rf` (called before EVERY action in `_rf`) re-enumerates windows when `_Fk=!0` if more than 300 ms passed — and between individual presses more than 300 ms ALWAYS passes → `chrome.windows.getAll({populate:true})` (~0.5–2 s) ran on EVERY press. The 300 ms cache only helped within one action sequence.
- **Fix:** `__acEnumCacheMs=1500` — covers the human pressing pace; window/tab state is maintained incrementally (file62_mv3.js: onCreated/onActivated/onRemoved/onFocusChanged), so 1.5 s staleness is harmless.
- **Measurement:** `[AC-ACT] ENUM windows.getAll took Nms` (the `_Fu` callback now logs the duration and calls `b()` — DON'T forget the generator continuation!).
- **Effect:** a series of fast presses enumerates only on the first one; subsequent cycles = round-trip only.

### Fix 6: `_Pw` — remove the "Stop waiting" dialog for runScript in SW (file37.js → bundle)

- **Problem:** with 4+ items in the queue `_Pw(1200,!0)` called `_Uk` (modal dialog) — in the SW there is no DOM, the dialog never renders, and the `_2y.length=1` branch **wiped the whole queue** of fast presses.
- **Fix:** for runScript in MV3: `__acLog('STUCK',...)` + force-shift of the head (the script already ran in the page — only the result round-trip is lost):
  ```javascript
  if(b)if("runScript"==_Wi){__acLog('STUCK','runScript head stuck '+a+'ms → force-shift')}else _Ot("stuckAction",{action:_Wi});_2y.shift();_6y()
  ```

### Fix 7: userScripts.execute — main frame only (sw.js, not in the bundle)

- **Problem:** `target:{tabId}` injects jsCode into ALL frames — every subframe creates a user-script world context and delays the promise; subframes duplicate the script execution (extra `aaaa` in the console).
- **Fix:** `target:{tabId, frameIds:[0]}` — the request always comes from file42 in the main frame (frame guard in file42).
- **Effect:** userScripts.execute no longer waits for subframes; fewer duplicate executions.

### Instrumentation (to find the residual ~1.5 s round-trip)

| Marker | Where | What it measures |
|---|---|---|
| `[AC-DLV] tab=N resp +Nms attempt=K` | file48 `n()` (in bundle) | SW sendMessage → file42 reply (full SW→page→SW round-trip) |
| `[AC-DLV] tab=N no listener → inject file42 attempt=K` | file48 `n()` | retry because file42 is missing |
| `[AC-F42] sw cb id=… +Nms ok/err/dedup/timeout` | file42 wrapper | file42 → SW → SW reply |
| `[AC-F42] res rcvd id=… +Nms` | file42 wrapper | postMessage USER_SCRIPT world → file42 (suspected Chrome batching) |
| `[AC-SW] execUserFunc rcvd tab=N age=Nms key=K` | sw.js | file42 → SW (Date.now() stamp `t` in the message) |
| `[AC-ACT] ENUM … took Nms` | file37 `_Rf` | window enumeration duration |
| `[AC-ACT] OK +Nms` | file37 `_rf` | full action cycle |

**Interpretation (after the test):**
- `res rcvd` large (≈N s) → delay in postMessage delivery (userScripts batching) → next fix: resolve the promise in file42 early on `sw cb {ok}` (the script already ran).
- `res rcvd` small, `sw cb` small, but `OK` large → delay in SW post-processing (`_A`/`_gr`/`_zs`/`Promise.all`).
- `resp` large → delay in sendMessage/file42 reply.

### Rebuild status

- `sw_core_bundle.js` rebuilt: size=230845, arrow ✓, markers `[AC-DLV]`/`__acCompanionMs`/`__acEnumCacheMs=1500` present.
- `sw.js` and `file42.js` — outside the bundle, the extension reload picks them up.
- ⚠️ **PS terminal:** the one-liner with nested quotes (`$s.Contains("'ENUM'")`) hung — use the simple command from ../AGENTS.md.

---

## 12. Fix round 3 (2026-08-02) — the 20 s sendResponse found; 34=activateTabs regression fixed

### Diagnosis from the user's logs (the instrumentation worked)

```
16:00:18.782 VM18:31 aaaa                                  ← script ran instantly
16:00:18.782 [AC-F42] res rcvd id=__acr_4mm4uw0xlou +1ms   ← postMessage USER_SCRIPT→file42: 1ms!
16:00:18.783 [AC-F42] sw cb ... +2ms ok                    ← SW replied: 2ms
16:00:44.327 [AC-DLV] tab=338979069 resp +25549ms attempt=2 ← BUT sendResponse arrived after 25.5s!!!
```

**ROOT CAUSE (of all symptoms):** the reply to an incoming `tabs.sendMessage` (sendResponse from a content script) reaches the SW with a **20–25 second** delay (Chrome throttles replies for inactive/hidden tabs). Meanwhile **outgoing** `runtime.sendMessage` from the content script (execUserFunc, age=0ms!) travel instantly. The script ran in 1-3ms, but the action (OK) waited 20s+ for sendResponse → the queue filled up → the watchdog dropped presses → "the interval grows".

**Regression (my round-2 mistake):** trigger 34 is NOT a duplicate of 14, but a **separate real action** (in the logs: `16:00:10.335 ACT action=activateTabs` — 34=activateTabs, 14=runScript). The companion-drop removed activateTabs.

### Fix 8: `n()` → frmCBId mechanism (bypassing sendResponse, file48.js → bundle)

- **Idea:** the reply should go via `runtime.sendMessage({pongId: frmCBId})` — the fast channel (the same one used by the `r()` path and execUserFunc). The mechanism is ALREADY implemented in file42 (listener `if(c.frmCBId)` → `u(c, w=>v({pongId:c.frmCBId, result:w}))`) — file42 does NOT need changes.
- **New `n()`:**
  ```javascript
  n=_cg(function*(a,c,d){const t0=performance.now();let fin=!1,res=null;const done=x=>{if(fin)return;fin=!0;res=x;d(x)};
  for(let p=0;;++p){yield k=>{let once=!1;const fin1=x=>{if(once)return;once=!0;k(x)};
    c.frmCBId=f(r=>{done(r);fin1(r);return});
    try{_Yk.tabs.sendMessage(a,c,{frameId:0}).catch(()=>{})}catch(e){}
    setTimeout(()=>fin1(),150)};
  _Aw("msgToIsolCtx");if(fin||0<p||c.event)break;
  try{0<a&&console.warn('[AC-DLV] tab='+a+' no listener → inject file42 attempt='+(p+1));yield _wj(a,{file:"file42.js"})}catch(k){return done({error:k})}}
  0<a&&console.warn('[AC-DLV] tab='+a+' resp +'+(performance.now()-t0).toFixed(0)+'ms attempt='+(p+1));fin||d(res)})
  ```
- sendMessage — fire-and-forget (promise, `.catch`); the result is awaited via pongId (5ms) OR a 150ms timer (no file42 → promise rejects, but k() fires the timer) → inject file42 → retry.
- **Effect:** the action completes in ~5-10ms instead of 20-25s (with a live file42); the first press on a tab without file42 — ~300-400ms (injection).
- Log: `[AC-DLV] tab=N resp +Nms attempt=K` now shows the REAL round-trip.

### Fix 9: signature-based companion-drop instead of a blind one (file37.js → bundle)

- **Problem:** the "different id <300ms" drop killed 34=activateTabs.
- **Fix:** drop ONLY if the action signature matches the last accepted trigger:
  ```javascript
  const __acTrigSig=x=>{try{return JSON.stringify(_ek[x]||null)}catch(e){return""}};
  if(a!==__acLastTrigId&&_now-__acLastTrigTime<__acCompanionMs&&__acTrigSig(a)===__acLastTrigSig){DUP → dropped}
  ```
  14=runScript vs 34=activateTabs — different signatures → both execute. Identical duplicates (the old "18 executions" scenario) are still suppressed.

### Rebuild status (round 3)

- `sw_core_bundle.js` rebuilt: size=231455, markers ✓ (`c.frmCBId=f(r=>{done(r)`, `__acTrigSig`, `setTimeout(()=>fin1(),150)`), ←/→ arrows in place, no mojibake.
- file42.js was NOT changed — old file42 instances in open tabs already know the frmCBId reply. Just reloading the extension is enough.

### Test protocol (round 3)

1. Reload extension (chrome://extensions → reload). Tabs do NOT need to be reloaded.
2. 5 fast presses ~300ms → expected: 5 `aaaa` (each in ~5-50ms), `[AC-DLV] resp +Nms` with a small N, `DUP` only for pairs with identical actions (if any), `QUEUE/ACT/OK` for each.
3. Verify that activateTabs (34) executes (the tab activates), not dropped.
4. If the press goes to a tab WITHOUT file42 (new/reloaded) — the first firing takes ~300-400ms (injection), then it is fast.

---

## 13. Fix round 4 (2026-08-02) — THE REAL root cause: the promise in file42 never resolved

### Diagnosis from round-3 logs (everything fits)

```
31.714 ACT runScript
31.715 execUserFunc rcvd age=0ms key=1:3          ← script ran (aaaa) in 1ms
31.715 execute +1ms → [AC-F42] res rcvd +1ms → sw cb +2ms ok
31.867 [AC-DLV] no listener → inject file42 attempt=1   ← n() did NOT get a reply within 150ms
31.869 execUserFunc rcvd + [AC-DUP] BLOCK completed (154ms ago)  ← 2nd file42, key already in completed
```

**Key facts:**
- `respond()` in file42 **was called** (execUserFuncDone went out — the key landed in `completed` after ~154ms), the script ran, **BUT `D()`/`A()` (resolve/reject of the promise) were called NOWHERE** — the promise hung forever.
- Because of the hanging promise, `u()`'s `e()` (result callback) never fired → **neither sendResponse nor pongId was sent** → the action hung until Chrome itself closed the channel (~20s). This explains ALL the delays (round 2: "sendResponse 20s" — actually the channel closed by itself, sendResponse was never called).
- Not a single `OK action=runScript` in the logs — all runScript actions hung; the queue only advanced via `_Pw`/watchdog.

### Fix 10: D/A in respond() (file42.js, not in the bundle) — THE MAIN FIX

```javascript
var respond=function(h,dontDone){
  if(responded)return;responded=!0;
  var f=r[id];delete r[id];f&&f(h);
  if(!dontDone&&sid)try{m.runtime.sendMessage({type:"execUserFuncDone",...},function(){})}catch(e){}
  // FIX: the promise was NEVER resolved — resolve/reject now
  try{h&&h.error?A(h.error):D(h&&h.result)}catch(e){}
};
```

- `postMessage` (success): `D(d.result)` → `u()`'s `e({result})` → sendResponse → SW → OK in ~5-10ms.
- SW error: `A(error)` → `e({error})`.
- dedup case: `D(undefined)`.
- **This also fixes the `r()` path (frmCBId/pongId)** — the same hanging promise blocked the reply there.

### Fix 11: n() — the simple variant + 1500ms safety net (file48.js → bundle)

- The round-3 frmCBId mechanism was removed (not needed — sendResponse is fast now).
- The classic `sendMessage(tabId, msg, {frameId:0}, cb)` is back + a 1500ms safety timer (race via the `once`-guard): if file42 is missing/dead — timer → inject → 1 retry (like the original).
- **IMPORTANT about double file42 (VMs):** every `scripting.executeScript` creates a NEW isolated context — repeated injections breed listeners (VM1064+VM1109 in the logs). Old file42 (without D/A) ran the script but did not reply → n() injected a new one → duplicates. After this fix, old file42 instances in open tabs still hang (first press on an old tab ~1.5s: safety net + injection of a fresh file42 with D/A → then fast). **Recommendation: reload the test tabs after the update** — then file42 is single and fresh.

### Rebuild status (round 4)

- `sw_core_bundle.js`: size=231354, markers ✓ (`setTimeout(()=>fin1(),1500)`, `resp +`, `__acTrigSig`).
- `file42.js`: D/A-fix ✓ (line 40).
- file42 is not in the bundle — picked up on injection into tabs.

### Test protocol (round 4)

1. Reload extension + **reload the test tab** (so it has a fresh file42 with D/A).
2. 5 fast presses ~300ms → expected: 5 `aaaa` + **5 `OK action=runScript` in ~5-50ms** (in the SW console), `[AC-DLV] resp +Nms` with a small N, `DUP companion` — only for pairs with identical actions, activateTabs (34) executes.
3. Verify there is NO `no listener → inject` on repeated presses (injection only on fresh tabs).

---

## ✅ FIXED (2026-08-02, confirmed by the user's test)

Final logs (16:56, 20+ fast presses):

```
#1: ACT runScript +1ms → no listener → inject file42 attempt=1 → resp +5ms attempt=2 → OK +6ms
#2..#26: ACT runScript +0ms → execUserFunc age=0ms → resp +1-2ms attempt=1 → OK +1-3ms
#6/#22/#27: trigger 34 → ACT activateTabs +0ms → OK +0ms   (not dropped)
trigger 12 (another hotkey): also +1-3ms
```

- Each press → exactly one script, the action completes in **1-6ms** (was 20-25s).
- **Zero** `DUP`/`QUEUE`/`WATCHDOG`/`STUCK` on fast presses.
- file42 injection — only when it is really missing (first press on a tab).

### Final fix chain (rounds 1-4)

| # | What | File |
|---|---|---|
| Fix 1 | Trigger-dedup (obsolete, replaced by Fix 9) | file37.js |
| Fix 2 | Enum cache 300ms (raised to 1500ms in Fix 5) | file37.js |
| Fix 3 | Watchdog 5s (safety net) | sw.js |
| Fix 4 | Queueing instead of blanket-drop (refined by Fix 9) | file37.js |
| Fix 5 | Enum cache → 1500ms + `[AC-ACT] ENUM` measurement | file37.js |
| Fix 6 | `_Pw` force-shift instead of dialog (no DOM in SW) | file37.js |
| Fix 7 | `userScripts.execute` → `frameIds:[0]` | sw.js |
| Fix 8 | n() frmCBId mechanism (replaced by Fix 11) | file48.js |
| Fix 9 | **Signature-based companion-drop** (34=activateTabs not dropped) | file37.js |
| Fix 10 | **D/A resolve in respond() — THE MAIN FIX** (the promise hung → the action hung ~20s) | file42.js |
| Fix 11 | n() simple + 1500ms safety net | file48.js |

### Remaining minor items (not critical)

- Diagnostic logs (`[AC-ACT]`, `[AC-DLV]`, `[AC-F42]`, `[AC-SW]`) — kept for debugging; can be removed for cleanliness.
- `broadcast "nativeMsg" via runtime ✗: Could not establish connection` at startup — harmless noise (no pages yet).
- Double file42 (VMs) on repeated injection — no longer happens (injection only when file42 is missing), but remember: every `scripting.executeScript` = a new isolated context.

### Test protocol (round 2)

1. Reload extension (chrome://extensions → reload).
2. Open the SW console + page console, script `console.log(new Date().toISOString(),'aaaa')`.
3. **Test A (fast presses):** 5 presses in a row with ~300 ms intervals. Expected: 5 `aaaa`, `TRIG`/`QUEUE`/`ACT`/`OK` for each, `DUP companion` only for 34, `ENUM` only on the first one.
4. **Test B (2 s intervals):** 5 presses with 2 s intervals. Expected: each cycle ≈ round-trip without enumeration.
5. Collect: `[AC-ACT]`/`[AC-DLV]`/`[AC-SW]`/`DUP` lines from the SW console + `[AC-F42]`/`aaaa` from the page console.


---

## 10. Test protocol (after any change)

1. Reload the extension (unpacked).
2. Page console + SW console open, script = `console.log(new Date().toISOString(), 'aaaa')`.
3. Press the hotkey **9 times** at 3–4 s intervals.
4. Expected: exactly **9** `aaaa` (one per press), no bursts.
5. Collect: page console lines + `[AC-ACT]`/`execUserFunc`/`DEDUP` SW lines for analysis.
