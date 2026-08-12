# HANDOFF — MV3 unstaged work (2026-08-06) — read FIRST in the next session

Goal of this file: give the next session full context WITHOUT re-reading the
chat history. Covers: git state, verified vs unverified fixes, the F()-path
regression saga (setClipboard), log-reading rules, and the rollback plan.

## 1. Git state (read-only facts, 2026-08-06 ~11:10)

- HEAD = stable baseline (round-18 `_Qj` fix etc.).
- **STAGED** (index, not committed): switchState `(_if.binSwtch||[])` in
  file77.js + bundle; file42.js `__acSeen`/`__acOnce` + st-diagnostics;
  sw.js `__acSwStart`/`__acStateDump` + `_lr→_Gf` auto-heal (10s throttle);
  Docs/TODO.md (49 lines).
- **UNSTAGED** (working tree): file42.js (re-injection guard + heartbeat +
  `__acFnDedup` + raw dedup + diag), file48.js (`~`-suffix in `_A`, n()
  4000ms, `[AC-DLV-F]`), sw.js (key in dedup response), sw_core_bundle.js,
  mh_test.js (section B), AGENTS.md, Docs/TODO.md (+86 lines).

## 2. VERIFIED fixes (proven by user runs — DO NOT roll back)

| Fix | Where | Proof |
|---|---|---|
| switchState `(_if.binSwtch\|\|[])` | file77 (STAGED) | 19:46 run: switchState PASS everywhere |
| `_A` `~`-suffix (runInTab [null]) | file48 (UNSTAGED) | 09:23 run: 22/23, `PASS ACtl.runInTab` |
| `__acOnce` (acUserApi dedup by id) | file42 (STAGED) | part of the 09:23+ stable stack |
| n() 4000ms (was 1500ms) | file48 (UNSTAGED) | fewer misfires; not a failure cause |
| auto-heal `_lr→_Gf` + state dump | sw.js (STAGED) | diagnostics only, harmless |
| mh_test section B | mh_test.js | 25 pass / 4 gaps / 0 FAIL |

## 3. VERDICT after 11:15/11:17 runs — ROLLBACK NOT NEEDED

- **11:15 (extension restarted, tab NOT reloaded) = 22-22-21-22, setClipboard
  PASS 4/4** — the same guard/__acFnDedup code! Worker: `[AC-DLV-F] h=ARR[2]`
  → `[AC-F] setClipboard F-> ["bin",...]` → type 286 → PASS. **NO
  `funcCode dedup-hit`** (single funcCode delivery).
- **11:17 (action re-added → storage.local changed → `_Gf` rebuild; page
  reloaded, extension NOT restarted) = 20/23, setClipboard FAIL**: page
  `funcCode dedup-hit` at 14.430 → worker `[AC-DLV-F] h=object:null` at
  14.434 → `[AC-F] setClipboard F-> null` → "_fr is not iterable".
- **CORRELATION PROVEN: FAIL ⇔ `funcCode dedup-hit` (double funcCode
  delivery → first n() attempt gets null); PASS ⇔ single delivery.**
- **User confirms: adding an action without restarting the extension made
  tests worse EVEN BEFORE this session's changes — NOT a regression of the
  guard/__acFnDedup/4000ms fixes.**
- **TRIGGER hypothesis: `storage.local changed → _Gf rebuild` (from adding
  the action) is the trigger for the double funcCode delivery.** Why a
  rebuild causes the first n() attempt to get null is UNRESOLVED.

## 3b. UNVERIFIED / SUSPECT fixes (keep for now, investigate via trigger)

- file42 re-injection guard + `__acF42T` heartbeat; `__acFnDedup`;
  raw-value dedup fix. Keep — they were NOT the cause (11:15 passed with
  them). Investigate the rebuild→dedup-hit chain instead.

## 3c. TEST PROCEDURE (user runs these; agent reads the logs)

### Step 1 — CURRENT STATE (NO extension reload) — regression watch
1. **Reload the test tab only** (F5 — mandatory: a fresh file42 from the
   working tree must be injected; old file42 persists in loaded tabs).
   Do NOT touch the extension.
2. Run the test (action RUN SCRIPT) **once** — wait for the final alert.
3. Record the score. Expected, if the working tree still regresses:
   setClipboard FAIL with `funcCode dedup-hit` in PAGE console and
   `[AC-DLV-F] h=object:null` / `[AC-F] F-> null` in WORKER.
   If it PASSES here — the regression is already gone; still do Step 2.
4. Capture both consoles around setClipboard (Step 4 checklist).

### Step 2 — BASELINE (WITH extension reload) — the critical check
1. `chrome://extensions` → **reload the extension**.
2. **Reload the test tab** (fresh file42 after the reload).
3. Run the test **once** — wait for the final alert, close it.
4. Expected **PASS run**: ≥21/23, **`ACtl.setClipboard/getClipboard` PASS**,
   and in the PAGE console **NO `funcCode dedup-hit`** for setClipboard.
   Worker console should show: `[AC-DLV-F] h=ARR[2]` and
   `[AC-F] setClipboard F-> ["bin",...]` → native type 286.
5. If this fails → something ELSE is broken (not the rebuild trigger);
   capture both consoles and stop.

### Step 3 — REPRODUCE THE TRIGGER (NO extension reload, after baseline)
1. **Without reloading the extension**: open settings, **add/change any
   action** (or edit the script) — this fires `storage.local changed`.
2. In the WORKER console wait for:
   `[AC-MV3] storage.local changed → rebuilding in-SW config (_Gf)`.
3. **Reload the test page** (F5 — fresh file42).
4. Run the test **once**.
5. Expected **FAIL run** (if the trigger hypothesis is right): setClipboard
   FAIL ("_fr is not iterable"), PAGE console shows `funcCode dedup-hit`,
   WORKER shows `[AC-DLV-F] h=object:null` then `[AC-F] setClipboard F-> null`.

### Step 4 — Logs to capture (BOTH consoles, around setClipboard)
- **Page**: `api rcvd props=setClipboard`, `funcCode dedup-hit`,
  `funcCode val`, `relay resp plain`, the FAIL line.
- **Worker**: `storage.local changed → rebuilding`, `[AC-DLV] tab=… resp
  +Nms attempt=1/2`, `[AC-DLV-F] tab=… h=…`, `[AC-F] setClipboard F-> …`,
  `postWithCb type 286`.

### Step 5 — Recovery
- If Step 3 left the state "broken": reload the extension → back to
  baseline (22/23). This itself confirms the trigger (reload heals).
- Step 1 vs Step 2 comparison is the regression watch: same working tree,
  only the extension reload differs — FAIL in 1 + PASS in 2 proves the
  "needs fresh SW state" nature of the bug.

### Criteria (quick reference)
| | PASS run | FAIL run |
|---|---|---|
| `funcCode dedup-hit` | absent | present |
| `[AC-DLV-F] h=` | `ARR[2]` | `object:null` |
| `[AC-F] setClipboard F->` | `["bin",...]` | `null` |
| native type 286 | yes | yes (later, wasted) |
| score | 21-22/23 | 18-20/23 |

## 4. The F()-path regression — what the logs PROVED

F()-path = SW W() → `F()` (file77) → `_xj` → `n()` (file48) → tabs.sendMessage
→ file42 `u()` funcCode branch → FN (execUserFunc K) → USER_SCRIPT world →
result → sendResponse → n() → `yield F(...)` → destructure in W().

Consumers: setClipboard (`[b,c,f]=yield F(k.id,[a,"png"],K)`), runInPageCtx
file form (`q=yield F(...)`), getClipboard-adjacent. runInTab/captureTab/
include use OTHER paths (`_A`/`_Ue`) and WORK.

### Log evidence (10:47 run, worker+page):
- `[AC-DLV-F] h=object:null` — FIRST n() attempt got **null** (attempt=1),
  while file42 sent the array (funcCode val logged) and a LATER call worked
  (native type 286 wrote the clipboard AFTER the FAIL).
- `funcCode dedup-hit` fired on EVERY F()-call — the funcCode message is
  delivered to file42 **TWICE** (same key → same winName → same userAPI).
- Two `execUserFunc` for one K with different `~`-chains.
- 11:06 run: `api rcvd props=setClipboard args0=_o2pwlo29jxf` — **ONE** userAPI
  (no acUserApi duplicates — my `__acApiDedup` idea was WRONG, rolled back).

### The unsolved core question
ONE userAPI → ONE F() → ONE n() → but TWO funcCode deliveries ⇒ **n() retry
fired instantly** (attempt 0's sendMessage callback = undefined/null WHILE
file42 was alive and processed M1 — dedup entry created!). Why the callback
fired with undefined/null before file42's sendResponse is UNKNOWN. Candidates:
(a) file42 listener returned non-true for M1 (exception in funcCode branch?);
(b) Chrome tabs.sendMessage quirk with the guard-created empty contexts;
(c) `yield F(...)` throws in `_cg` machinery before destructure (`_fr is not
iterable` = `_fr` was undefined — the `[AC-F]` log did NOT print, but it is
in the WORKER console, not page — not yet captured!).

### What was captured (11:15/11:17 WORKER logs — the missing data!)
- `[AC-F] setClipboard F-> ["bin",...]` (PASS run) vs `F-> null` (FAIL run)
- `[AC-DLV-F] h=ARR[2]` (PASS) vs `h=object:null` (FAIL) — first attempt
- `funcCode dedup-hit` present ONLY in FAIL runs
- `[AC-F42] relay resp ZBUNDLE/plain` — relay path is NOT the problem
  (setClipboard gets `plain`)

### Next session: reproduce the trigger
1. Restart extension → run test → expect 22/23 (baseline OK).
2. WITHOUT restarting: add/change any action (storage.local changed →
   `_Gf` rebuild in worker: "storage.local changed → rebuilding in-SW
   config") → reload the page → run test → EXPECT dedup-hit + setClipboard
   FAIL. If reproduced: rebuild is the trigger.
3. Then find WHY the rebuild breaks the first n() attempt: instrument
   file42's listener return value for funcCode messages and wrap the
   funcCode branch in try/catch (an exception closes the channel →
   callback(null) → retry → dedup-hit cascade). Also check `_us` global
   `parentGener` (`a`) interference between the rebuild chain and the
   userAPI chain (both run `_cg`/`_we` generators concurrently).

## 5. Other observations (NOT regressions)

- **on tabLoadEnd timeout**: VM network — example.org loads >8s in slow runs;
  dedup at ~3.94s after on-reg = n() 4s fallback on the long-lived on
  z-bundle execUserFunc (registration waits for the event). Known flake.
- **pubVar "roundtrip"**: `_ge` write doesn't await `_Mi` 300ms debounce;
  get 4ms later reads stale storage. Test-side flake (2/4 runs 11:06).
- **Fast hotkeys "don't work"**: runScript action waits for the SCRIPT
  (>4s — alerts) → n() 4s fallback + SW dedup "BLOCK completed" → action
  completes at +4s but the queue is blocked → repeated hotkeys pile up →
  WATCHDOG force-shift. Separate issue to fix AFTER setClipboard (e.g. make
  runScript fire-and-forget or extend the n() timeout for script runs).

## 6. ROLLBACK PLAN — NOT NEEDED ANYMORE (11:15 result)

The 11:15 run (22-22-21-22, setClipboard PASS with the same code) proves the
unverified fixes are NOT the regression. Do NOT roll back. Keep everything;
investigate the rebuild→dedup-hit chain instead (section 3b / next session).

## 7. NEXT SESSION — first steps

1. Read this file + Docs/TODO.md "Run 10:47" entry + session memory
   (`/memories/session/autocontrol-mv3.md`).
2. Ask user for a WORKER console log of one setClipboard moment IF still
   possible (before/after rollback): `[AC-F]`, `[AC-DLV-F]`, `[AC-DLV]`.
   If the guard/__acFnDedup is confirmed as the cause (setClipboard passes
   after rollback), re-introduce fixes ONE AT A TIME with a test run each:
   (a) `__acFnDedup` alone; (b) guard alone; (c) heartbeat; (d) raw dedup.
3. Fix the n() retry-on-live-file42 question: instrument file42's listener
   return value for funcCode messages (`return u(c,b)` — log what u() returns:
   true vs undefined) and wrap the funcCode branch in try/catch with a log
   (an exception there closes the channel → callback(undefined) → retry →
   dedup-hit cascade → the FIRST response (null/undefined) wins the race).
4. Fix fast-hotkey queue blocking (runScript waits >4s) — separate task.

## 8. Architecture cheat-sheet (for the next session)

- SW-brain: sw.js + sw_core_bundle.js (importScripts). Page = UI only.
- file42.js = content-script relay (NOT in bundle; injected per tab; line
  numbers in logs identify the version: 148=api rcvd, 159/162=api local,
  186=relay resp, 18=funcCode val/dedup-hit, 74=res rcvd, 85=sw cb).
- USER_SCRIPT world bridge: jsCode in sw.js (proxy ACtl.* → postMessage
  acUserApi → file42 → runtime userAPI → SW W() → back).
- Dedup keys: SW execUserFunc dedup = `tabId:scriptId:trigInstId` (15s LRU,
  `__acExecInFlight`/`__acExecCompleted`); file42 `__acFnDedup` = funcCode
  slice(0,100)+args slice (2s); `__acOnce` = id (30s).
- `~`-suffixes: file48 `_A` adds per-message `~`+rand to trigInstId; file42
  funcCode branch and relay add their own `~`+rand to x.__cur.trigInstId.
- Encoding: PowerShell must use `-Encoding UTF8`; bundle rebuild script in
  AGENTS.md; verify arrow `0x2190` survives.
- Bundle rebuild needed ONLY for file48/file77/etc changes (file42 outside).
- mh_test.js: `node mv3-build/mh_test.js` — [PASS]/[FAIL]/[GAP ]/[FIXED?],
  exit 1 on FAIL; currently 25 pass / 4 gaps / 0 FAIL (bundle 234425).
