# TODO — Mouse-over zones: make ALL zones work (Chrome 148+/150)

**Created:** 2026-09-03 · **Status:** ✅ **CORE GOAL ACHIEVED (2026-09-12)** — all
12 action-editor areas verified live; ⬜ 3 follow-ups remain (below)
**Goal:** every mouse-over zone condition works on Chrome 150 (SxS Canary)
with the zone-helper architecture. Zone 12 (tab strip) and 16 (new-tab
button) were the first proofs; **all 12 areas are now verified** (§1 summary).

**Open items — the ONLY ones left in this file:**
1. **§2c — multi-browser support: UNTESTED.** The helper has never been run by
   two browsers at once (needs a second browser registered + the extension
   loaded from the same folder).
2. **§3 item 4 — menu-item types 41-51 are not individually verified.** They
   ride the same engine-classified route as type 40, which WAS verified live;
   per-kind accuracy is unproven.
3. **§6 — auto-heal for a HUNG helper.** Deferred by the user 2026-09-12
   (Emergency Repair already heals it manually).

---

## 1. How zones work now (architecture recap)

```
engine v19 (the mouseOver region check is a TABLE LOOKUP the helper fills in;
            menu regions >= 40 keep the engine's own classification)
                             ── 750 (fires for every wheel/click) ──▶ SW
                                                                          │ __acDispatchTrigger750
                                                                          │ asks the helper: "zones?"
                                                                          ▼
                                                   ac_zone_helper.exe (no hooks)
                                                   GetCursorPos + AccessibleObjectFromPoint
                                                   + accParent walk, role check → SET
                                                                          │ {zones:[12,1]}
                                                                          ▼
        trigger's regions ∩ helper's zones ≠ ∅ ──▶ dispatch action
        no intersection                        ──▶ skip (log line)
        (regions the helper cannot verify — menu items — pass through
         with the ENGINE's verdict)
```

- Engine: **v19 patched** (`AutoControl_native/patches/patch_zones_v19.js`,
  SHA-256 `1A10EDD1…`; built copy + deploy target:
  `AutoControl_native/patched/`) — the mouseOver region check now reads a
  **table the helper writes into the engine's memory** (`alive` flag + 64
  region slots), so a region matches ONLY when the cursor really is over it.
  That same check drives INPUT CONSUMPTION (match == consume), which is why
  the earlier always-match v18 made every wheel trigger swallow the wheel.
  Menu regions ≥ 40 keep the engine's own classification; with no helper
  running (`alive == 0`) the engine falls back to the v18 behaviour. v18
  (`Test/patch_zones_v18.js`, `F96BF544…`) is kept only as history — see §2e
  and §2g. The engine can never classify UI zones itself (hover cache + MSAA
  deadlock — `Docs/archive/NATIVE-REVERSING-2026-08-31.md` §12).
- Helper: `Test/ac_zone_helper.cs` → `AutoControl_native/ac_zone_helper.exe`
  (native host `com.autocontrol.zonehelper`, registered in HKCU). Answers
  `{__id:N}` → `{__id:N, zone:Z, zones:[…]}`.
- Gate: `mv3-build/sw.js` `__acDispatchTrigger750` + `__acBuildZoneMap`
  (map rebuilt live on `storage.onChanged` since 2026-09-03) +
  `__acZoneAsk`.

**Zone numbers** (decoded from `file10.js`, mouseOver region constants;
UI names from the settings list):

| # | UI name | region № | const | Status (2026-09-12) |
|---|---|---|---|---|
| 1 | Browser window | 1 | `_Ef` | ✅ works (always in the set — the point is inside the window) |
| 2 | Web page | 3 | `_Si` | ✅ works (role 15 DOCUMENT) |
| 3 | Title area | 4 | `_Ce` | ✅ works (window frame PANE outside the toolbar; the strip area outside tabs also counts — modern Chrome has no separate title bar) |
| 4 | Browser tab | 12 | `_9t` | ✅ works (role 37 at d0/d1, or the strip gap role 60) |
| 5 | Tab's close button | 15 | `_Go` | ✅ **VERIFIED 2026-09-12** (43 under a PAGETAB, right half; set `[15,4,1]`, no 12) |
| 6 | Tab's speaker icon | 17 | `_2` | ✅ **VERIFIED 2026-09-12** (43 under a PAGETAB, left half; set `[17,4,1]` — the tab must be AUDIBLE) |
| 7 | New tab button | 16 | `_xw` | ✅ **VERIFIED 2026-09-12** (43 whose parent is the PAGETABLIST; set `[16,4,1]`) — §2a closed |
| 8 | Toolbar | 20 | `_uu` | ✅ works (role 22 TOOLBAR in the ancestry) |
| 9 | Omnibox | 21 | `_5e` | ✅ works (role 42 at d0/d1, or the lock button 57 under the omnibox group 20) |
| 10 | Bookmark button | 33 | `_Aa` | ✅ works (43 inside the omnibox GROUPING 20 which sits in the toolbar) |
| 11 | Browser menu button | 30 | `_nj` | ✅ **VERIFIED 2026-09-12** — the update pill counts as the kebab (user request) |
| 12 | Any menu item | 40 | `_9r` | ✅ **VERIFIED 2026-09-12** (engine-classified via `jae ORIG`; fires over the OPEN menu only) |
| 13 | Menu item: tab | 41 | `_ju` | ⚠️ same engine-classified route as #12 — NOT individually verified (§3 item 4; only 40 was tested live) |
| 14 | Menu item: tab submenu | 42 | `_gk` | ⚠️ same route as #13 |
| 15 | Menu item: closed tab | 44 | `_et` | ⚠️ same route as #13 |
| 16 | Menu item: closed window | 45 | `_Pg` | ⚠️ same route as #13 |
| 17 | Menu item: bookmark | 46 | `_Nu` | ⚠️ same route as #13 |
| 18 | Menu item: bookmark folder | 47 | `_yr` | ⚠️ same route as #13 |
| 19 | Menu item: action | 48 | `_Te` | ⚠️ same route as #13 |
| 20 | Menu item: switch | 51 | `_Ju` | ⚠️ same route as #13 |

Legend: ✅ works · ⚠️ implemented, unverified · ❌ not implemented.

**Status summary (2026-09-12, FINAL — verified by the USER on a live browser):
ALL 12 areas of the action editor PASS.** Each area was selected in a real
action and tested with a physical wheel through the native hooks; the SW log
was used as the evidence (`zones=[...] ∩ [...] → executing`). Verified sets:

| # | Area (UI) | region | live set observed | result |
|---|---|---|---|---|
| 1 | Browser window | 1 | `[1]` (and `[…,1]` everywhere inside) | ✅ |
| 2 | Web page | 3 | `[3,1]` | ✅ (silent over the UI) |
| 3 | Title area | 4 | `[4,1]` / `[12,4,1]` / `[21,20,4,1]` / `[30,20,4,1]` | ✅ (whole top band, silent over the page) |
| 4 | Browser tab | 12 | `[12,4,1]` | ✅ (silent over the close button) |
| 5 | Tab's close button | 15 | `[15,4,1]` | ✅ (no 12 in the set) |
| 6 | Tab's speaker icon | 17 | `[17,4,1]` | ✅ (no 12/15 in the set) |
| 7 | New tab button | 16 | `[16,4,1]` | ✅ |
| 8 | Toolbar | 20 | `[20,4,1]` (+ the omnibox/menu-button rows, as in MV2) | ✅ |
| 9 | Omnibox | 21 | `[21,20,4,1]` | ✅ |
| 10 | Bookmark button | 33 | `[33,20,4,1]` | ✅ |
| 11 | Browser menu button | 30 | `[30,20,4,1]` | ✅ |
| 12 | Any menu item | 40 | engine verdict (`jae ORIG`, helper has no rule) | ✅ fires over the OPEN MENU only |

Negative controls (all silent): page / tab strip / toolbar with a menu-item
trigger armed, the close button with a tab trigger, the page with a title-area
trigger, etc. The SW gate still logs `… ∩ [N] → skipped` when the engine emits
from a stale (120 ms) burst snapshot — it re-asks the helper and cancels.

The helper answers the whole SET of matching zones per point
(`{zones:[...]}`); the SW gate fires a trigger when the sets INTERSECT.

Helper rules as of 2026-09-12 (`Test/ac_zone_helper.cs` -> `Classify()`):
`43 under 37 (right half) → 15`, `43 under 37 (left half) → 17`,
`43 under 60 → 16`, `42 at d0/d1 → 21`, `57 under 20 → 21`,
`43 inside GROUPING 20 inside TOOLBAR 22 → 33`, `TOOLBAR 22 in ancestry → 20`,
`square 43/57 hugging the window's right edge → 30`, `37 at d0/d1 → 12`,
`60 at d0/d1 (not the "+") → 12 + 4`, `PANE 16 outside toolbar/page/strip → 4`,
plus zone 1 always.

---

## 2. Live signatures — Chrome 150 SxS, collected 2026-09-12

Collected with `Test/zone_scan.ps1` .. `zone_scan4.ps1` (MSAA hit-tests +
`accLocation` rects + child enumeration) and verified with
`Test/zone_probe.ps1` (moves the cursor, asks the deployed helper).

**⚠ DPI GOTCHA (cost half an hour):** element rects from `accLocation` /
`AccessibleObjectFromPoint` are **PHYSICAL** pixels, while `GetWindowRect` in
a DPI-unaware process is **DPI-virtualized** (this display runs at 150%: the
real window is ~2094 px wide, `GetWindowRect` reported 1396). Scanners MUST
call `SetProcessDPIAware()` first (the helper does it in `Main`). Symptoms
before the fix: the tab strip seemed to end at x=1388 with no "+" button and
no toolbar buttons on the right.

| Element | MSAA walk (d0 → d1 → d2…) | zone |
|---|---|---|
| A tab (body/title) | 41 CELL (title) / 16 PANE (favicon) → **37 PAGETAB** → 16 | 12 |
| Tab-strip gap / empty strip | **60 PAGETABLIST** at d0 or d1 → 16 | 12 + 4 |
| Tab's close button | **43 PUSHBUTTON** 'Close' → 37 PAGETAB (right half of the tab) | 15 |
| Tab's speaker/audio icon | 43 PUSHBUTTON under 37 PAGETAB (left half) — appears over the favicon slot | 17 |
| New-tab button (`+`) | **43 PUSHBUTTON** 'New Tab' → **60 PAGETABLIST** → 16 | 16 |
| Tab search button | 57 BUTTONMENU 'Tab search' → 16 → 60 | (none — a strip button, not the strip) |
| Omnibox text field | **42 EDIT** 'Address and search bar' → 20 GROUPING → 22 TOOLBAR | 21 + 20 |
| Site-info (lock) | 57 BUTTONMENU 'View site information' → 20 → 22 | 21 + 20 |
| Bookmark star | **43 PUSHBUTTON** 'Bookmark this tab' → 16 → 20 GROUPING → 22 | 33 + 20 |
| Toolbar buttons (Back/Forward/Reload) | 43 → **22 TOOLBAR** → 16 | 20 |
| Extension icons / profile ('You') | 57 / 43 → 16 → 22 | 20 |
| Browser menu (kebab) | NOT EXPOSED as an element in Chrome 150 — identified by POSITION | 30 |
| Window frame / caption (above the tabs, window controls) | 16 PANE (unnamed) → 16 → 16 (60 only at d2 when above the strip) | 4 |
| Web page | **15 DOCUMENT** → 9 → 16 | 3 |
| Any point inside the window | — | 1 |

Numeric MSAA roles referenced above (Chrome 150): 15 DOCUMENT, 16 PANE,
20 GROUPING, 22 TOOLBAR, 37 PAGETAB, 41 CELL/title-text, 42 EDIT,
43 PUSHBUTTON, 57 BUTTONMENU, 60 PAGETABLIST.

The toolbar element itself: `role=22` with 15 children (Back, Forward, Reload,
Home, split-view, the omnibox GROUPING 20 with 28 children, the extension
icons, 'You', the update pill, hidden ones). The omnibox GROUPING holds
'View site information', the address EDIT and the page-action buttons
(Zoom / Bookmark this tab / Ask AI …). The tab list (60) holds the tab-search
button, one PAGETAB per tab, the "+" button and the window controls area.

---

## 2a. RESOLVED (2026-09-12) — New tab button (zone 16)

**Old report (2026-09-03):** wheel over the `+` performed no action.

**ROOT CAUSE (found 2026-09-12): the helper had no rule for it.** The 2026-09-03
claim "the helper previously classified the `+` as zone 16" was WRONG — the
deployed binary (and its source) only knew 12/21/3; everything else answered
`0`, and the zone map `{"1":[16]}` could never match. The `+` is a plain
`43 PUSHBUTTON 'New Tab'` whose parent is the PAGETABLIST (60) — a clean,
locale-independent signature; it is now the first rule of that shape.

**Verified live:** the cursor over the `+` → `{"zone":16,"zones":[16,1]}`.
Note the `+` does NOT get zone 12 despite its PAGETABLIST parent (the engine's
zone-12 check required role 37) — that keeps a zone-12 and a zone-16 trigger
from firing together.

**Status:** ✅ resolved (was ⚠️ open).

**User report:** wheel over the `+` (new-tab) button with a zone-16 trigger
performs NO action, even though the helper previously classified the `+` as
zone 16 and the zone map shows the trigger on `[16]` (log:
`zone map: {"1":[16],"2":[16],"12":[21],"55":[3]}`).

**Historical note (the four hypotheses, all now moot):** the investigation
plan assumed the 750 delivery or the engine's own region-16 gate was at
fault, but the helper simply answered `0` — no rule existed. Live check
(2026-09-12): the wheel over the `+` DOES produce a 750 (the v16 engine fires
them everywhere) and the helper now answers 16 for it.

---

## 2b. RESOLVED — zone 12 action intermittently stops after editing ANOTHER action (2026-09-03 → 09-05)

**User report:** the tab-strip trigger (zone 12, wheel → reload/switch) works,
but **sometimes** stops firing after the user edits a DIFFERENT action in the
settings and saves. No pattern yet — the user report was "sometimes"
(intermittent), and it followed a config save.

**ROOT CAUSE (found 2026-09-04): `_Sk` drift between the bundle shim and the
engine.** `mv3_native_shim.js` re-stamps `_Sk = Date.now()/864E5|0` on EVERY
`nativeConfigReady` (including the force config refresh after a settings
save). After midnight this drifts a day from the `handshakeSk` the engine
encodes trigger ids with → `z[750]` decoded every 750 off by one day →
triggerId wrong → actions silently never executed while the SW gate logged
"executing" (the gate used the correct `handshakeSk`; the real execution in
`z[750]` used the drifted shim `_Sk`).

**FIX (2026-09-04, `mv3-build/sw.js`, no bundle rebuild):**
1. at handshake: `try { _Sk = handshakeSk; } catch(e) {}` — sync the bundle
   global with the authoritative handshake value;
2. in `__acDispatchTrigger750`: `try { _Sk = handshakeSk; } catch(e) {}`
   right before every dispatch — heals any shim re-stamp (config change,
   force refresh) immediately on the next 750.

**Verified 2026-09-05 (5h of live logs):** 35 executing / 0 skipped across
two config-map rebuilds (the exact repro scenario: disable/enable actions) —
wheel actions kept working after every config change. User-confirmed.

**Status:** ✅ resolved (was ⚠️ open).
(`trig 1: zone=12 ∈ [12] → executing`; map `{"1":[12],"2":[16],"12":[21],"55":[3]}`),
so the failure is transient, likely AT the moment of the save.

**Working hypothesis (two candidates, both in `mv3-build/sw.js`):**

1. **Async zone-map rebuild race (most likely).** The map is rebuilt on
   `storage.onChanged`:
   ```js
   chrome.storage.onChanged.addListener((changes, area) => {
     if (area === 'local' && changes.trigActList) {
       __acZoneMapBuilt = false;
       __acBuildZoneMap();          // async chrome.storage.local.get inside
     }
   });
   ```
   A settings save writes `trigActList` (possibly multiple writes in a row) →
   onChanged fires several times → **parallel** `__acBuildZoneMap()` runs, each
   doing an async `get`. They can complete out of order → the map may settle
   on a STALE/INTERMEDIATE state. Also: a 750 arriving WHILE the rebuild is in
   flight is gated against the OLD map.
   → **Fix idea:** use `changes.trigActList.newValue` DIRECTLY in onChanged
   (no async re-read) — synchronous, race-free; drop `__acZoneMapBuilt`
   entirely (it no longer guards anything).

2. **Helper cold-start timeout (250 ms).** `__acZoneAsk(250)`:
   if the helper process died (SW reload, idle kill) the FIRST request =
   connectNative + process spawn + MSAA walk — can exceed 250 ms → `res(-2)`
   → `zones.includes(-2)` = false → **skip**. Looks exactly like
   "works, then suddenly doesn't for a while, then works again".
   → **Fix ideas:** raise the timeout to 500–800 ms; keep a **last-known-zone
   cache** and fall back to it on timeout instead of skipping (for zone 12 the
   cursor rarely moves far between the 750 and the answer); or retry once.

**Debugging steps (when it repeats — user will report):**
1. Immediately read the gate log (see the snippet below) — look for
   `[AC-MV3-ZONE] trig 1: zone=…` lines right after the save:
   - `zone=12 ∈ [12] → executing` + action works → not a gate problem.
   - `zone=-2 ∉ [12] → skipped` → **helper timeout** (candidate 2).
   - NO zone line at all + no `Trigger 750` → engine/config issue upstream
     (type 60 re-registration after the save).
2. Check whether the map line was re-printed at the save moment and with
   WHICH content (`zone map: …` lines around the save time) — a wrong map
   (missing `1:[12]`, or stale) confirms candidate 1.
3. `node Test/zone_helper_smoke.js` with the cursor over the tabs — helper
   answers `zone:12`? If yes, the helper itself is fine.
4. Repro recipe to try: edit ANY action of ANY trigger → Save → immediately
   wheel over the tabs 3 notches. Repeat 5×. Collect the log lines.

**Quick log dump command (after a repro):**
```js
// attach to the SW console and filter ZONE lines
// (see the node snippet in AGENTS.md / the zone session notes)
```

**Not suspected (ruled out so far):** engine v16 patch (works when the map is
fresh), helper classification itself (deterministic), the map CONTENT after a
settled rebuild (correct in logs).

---

## 2c. ✅ RESOLVED (2026-09-13) — multi-browser support: the helper binds to ITS OWN browser's engine

**User request:** verify the helper works with MULTIPLE browsers that have the
extension installed (e.g. stable Chrome + Chrome SxS/Canary + Edge running at
the same time).

**Architecture facts (why it SHOULD work):**
- Each browser's `connectNative` spawns its OWN `ac_zone_helper.exe` process —
  no cross-browser conflict (same exe, separate processes).
- The helper answers about the SYSTEM cursor (`GetCursorPos`) — one cursor
  per desktop, so any browser asking gets the same zone (correct behavior).
- The engine (Zero→engine pair) is already multi-browser; the helper follows
  the same model.

**Prerequisites per browser (to TEST):**
1. **Host registration** — Chrome looks up native hosts in ITS OWN registry
   hive. Currently registered only:
   `HKCU\Software\Google\Chrome\NativeMessagingHosts\com.autocontrol.zonehelper`
   (SxS appears to read the same key — VERIFY; for Edge/Brave add their own):
   - Chrome SxS (Canary): `HKCU\Software\Google\Chrome SxS\NativeMessagingHosts\...`
   - Edge: `HKCU\Software\Microsoft\Edge\NativeMessagingHosts\...`
   - Chromium/Brave: their own vendor path
2. **Same extension ID** — `allowed_origins` pins the helper to
   `lkaihdpfpifdlgoapbfocpmekbokmcfd`. For unpacked builds the ID derives from
   the FOLDER PATH — load the extension from the SAME `mv3-build\` dir in
   each browser to get the same ID. A different folder → different ID →
   helper refuses (edit the manifest's allowed_origins).
3. **Browser restart** after registration (Chrome caches the host list).

**Test plan:**
1. Install/register the helper for 2+ browsers (e.g. stable + SxS).
2. Load the extension from the same folder in both.
3. In browser A: wheel over the tabs → action fires; over the page → no.
4. In browser B (same cursor position): wheel over its tabs → action fires.
5. Both browsers open at the same time, cursor over A's tabs while wheeling
   in B → B executes (system cursor = A's tabs) — expected; document it.
6. Check each browser's SW console for its own `[AC-MV3-ZONE]` lines and
   `zone map:` — both must be healthy and independent.

**Result:** ✅ **RESOLVED 2026-09-13** — the two-browser run happened for real
(stable Chrome + Chrome SxS, extension loaded from the same `mv3-build\` in
both, helper registered). Findings:

1. **Each browser spawns its OWN engine** (`AutoControlZero` → engine per
   browser) and each engine keeps its **own** zone table — confirmed by
   dumping both engine processes (`Test/engine_zone_write.ps1 -Dump
   -EnginePid <pid>`).
2. **Both helpers used to write into the SAME engine** (`FindEnginePids()[0]`),
   so the other browser's engine kept the FILE fallback (`mov eax,1` = "every
   region matches") → its mouse-over conditions were satisfied EVERYWHERE:
   "wheel over the page switches tabs" with no such action configured (user
   report 2026-09-13) and "Alt+wheel only works after adding a mouse-over
   condition". The helper now binds to the engine that tracks **its** browser's
   windows (image base `+0xA2514`, `std::vector<HWND>`), never writes a foreign
   engine, and logs `waiting: none of the N engines belongs to browser <pid>`
   while it has no match. Verified: with the cursor over browser A's page, A's
   engine table gets `[3,1]` and **B's engine is left untouched**.
3. The own-window gate (§2f(f)) had been INERT: the helper's direct parent is
   `cmd.exe` (chain `browser → cmd → helper`), so `browserPid` stayed 0. It now
   walks UP the ancestor chain and really ignores foreign windows — verified by
   pointing the cursor at VS Code (`zones=[]`, no zone actions there).
4. Step 5 of the original plan behaves as "expected": the helper answers about
   the SYSTEM cursor but only for its OWN browser, so with the cursor over A's
   window B's helper reports `zones=[]` for B (not "A's zones").

**The old open questions for zones 1/4/15/17/20/30/33 are ANSWERED
(2026-09-12)** — the rules are in §1, the live signatures (and the DPI
gotcha) in §2, the implementation and verification in §2d. The menu-item
zones (40-51) were resolved afterwards too: the engine classifies them itself
(§2g), and region 40 was verified live over the OPEN menu (§3 item 6).

---

## 2d. IMPLEMENTED (2026-09-12) — 11 zones via the helper + a multi-zone SW gate

**What changed**

1. `Test/ac_zone_helper.cs` — `Classify()` returns the SET of matching zones
   (response `{"__id":N,"zone":P,"zones":[...]}`, `P` = most specific for
   logging / old SW builds); rules as listed in §1. `Main()` calls
   `SetProcessDPIAware()` (the zone-30 position rule needs physical
   coordinates — see the DPI gotcha in §2).
2. `mv3-build/sw.js` — `__acZoneAsk` resolves the ARRAY; `__acDispatchTrigger750`
   fires the trigger when the trigger's regions and the helper's set
   INTERSECT: `zones.some(z => zs.indexOf(z) !== -1)`; the log line is
   `[AC-MV3-ZONE] trig N: zones=[…] ∩ [regions] → executing|skipped`.
   (sw.js is not in the bundle — no rebuild needed.)
3. Deployment: build with `powershell -File Test/build_native.ps1`
   (deterministic Roslyn recipe — `Docs/BUILD-NATIVE.md` §A; the old
   `csc` command is NOT reproducible and is only kept as history) → copy the
   exe to `%LOCALAPPDATA%\AutoControl\` AND `AutoControl_native\`. Chrome picks
   the new binary up on its own (the SW pings the host every 2.5 s, which
   spawns a fresh process); a browser restart is only needed if the old helper
   still holds the port.

**⚠ LOAD-PATH GOTCHA (this cost 30+ minutes):** the running Chrome SxS loads
the extension from
`C:\Work\AutoControl-Keyboard-shortcuts-Mouse-gestures-Chrome\mv3-build` —
NOT from the repo's `mv3-build\`. The `Secure Preferences` entry was STALE
(it claimed the repo path). **Reliable check:**
`node Test/cdp_eval.js 9223 "fetch(chrome.runtime.getURL('sw.js'),{cache:'no-store'}).then(r=>r.text()).then(t=>({hasNew:t.includes('zones=['),len:t.length}))" --await`
— compare `len` (chars) with the file size on disk. **Copy sw.js to BOTH
folders** before reloading, otherwise the SW keeps running the old code.

**Live verification (cursor moved by `Test/zone_probe.ps1`, helper asked
directly):**

| Point | Answer |
|---|---|
| tab body / tab favicon | `[12,1]` |
| tab close button | `[15,1]` |
| new-tab `+` | `[16,1]` |
| tab search button | `[1]` (no zone — a strip button, not the strip) |
| empty strip / gap | `[12,4,1]` |
| top band above the tabs | `[4,1]` |
| window controls area | `[4,1]` |
| Back button | `[20,1]` |
| omnibox / site-info | `[21,20,1]` |
| bookmark star | `[33,20,1]` |
| extension icon / profile 'You' | `[20,1]` |
| page | `[3,1]` |

**End-to-end (real OS wheel through the native LL hook, `Test/zone_e2e_test.ps1`):**

```
[AC-MV3-ZONE] trig 1: zones=[12,1] ∩ [12] → executing   (wheel over a tab)
[AC-MV3-ZONE] trig 1: zones=[3,1] ∉ [12] → skipped       (wheel over the page)
```

**Tooling (new/changed, all in `Test/`)**

| File | Purpose |
|---|---|
| `zone_scan.ps1` | vertical + horizontal run-length sweeps of the window (roles/names per row) |
| `zone_scan2.ps1` | element map WITH `accLocation` rects (tab list, toolbar, omnibox children) |
| `zone_scan3.ps1` | targeted hit-tests (tab strip right end, close/audio, toolbar right side) |
| `zone_scan4.ps1` | full child enumeration (nulls included) + right-edge hunt for the kebab |
| `zone_probe.ps1` | moves the cursor over a list of points and prints the deployed helper's answer |
| `zone_e2e_test.ps1` | real wheel injection (mouse_event) over a tab and the page + SW log tail |
| `zone_swtail.js` | attach to the SW console and print lines matching a regex |
| `_ac_crop.ps1` | screen crops of the window (visual checks; needs the window visible) |

**Resolved afterwards (same session):** menu zones 40-51 ✅ (region 40 verified
live over the OPEN menu — §2g/§3 item 6; the ENGINE classifies them, the helper
is not involved), zone 30 ✅ (the "New Chrome available" pill counts as the
kebab — user request, §2e), zone 17 ✅ (verified on a really audible tab —
§2f(b)).

---

## 2e. ENGINE PATCH v18 + close/speaker/menu fixes (2026-09-12, later the same day)

> ⚠ **SUPERSEDED by v19 the same night (§2g)** — v18's "always match below 60"
> also made the engine CONSUME the wheel everywhere (input consumption and the
> 750 delivery are the same decision), so pages stopped scrolling. Kept for the
> chronology of the close/speaker/menu work in this section.

**The blocker found:** the extension's SW gate can only judge triggers the
ENGINE actually delivers. Measured live with a real wheel over the tab's close
button: the engine emitted the 750 for the zone-12 trigger (skipped correctly
by the gate) but NOTHING for the zone-15/16/17 triggers — its own hover-cache
based checks fail there (RE doc §10), so the trigger never reached the gate.
Patch v16 (zone 12 always-true) only covered that one zone.

**`Test/patch_zones_v18.js`** (built from the pristine `.orig`, deterministic):
1. v16 baseline (zone-12 gate NOP + always-1 role check);
2. a 21-byte code cave in the `.text` tail padding + a 5-byte `jmp` at the
   entry of the classifier `FUN_004156f0`:
   ```
   cmp edx, 3Ch        ; zone >= 60 (AutoControl MENU items, UI 40-51 + 20)
   jb  alwaysMatch     ; below 60 -> match (the SW gate decides)
   <original first 5 bytes: sub esp,20h / push ebx / push ebp>
   jmp 0x4156f5        ; back into the original body (menu items keep the
                       ; engine's own native classification)
   alwaysMatch: mov eax,1 / ret      ; caller cleans the stack (add esp,4)
   ```
   Result: every non-menu mouseOver precond passes in the engine → the 750 is
   always emitted → the SW gate (helper) has the final say.

**Helper: the update pill IS the browser-menu button** (user request):
the "New Chrome available" pill occupies the kebab's rightmost toolbar slot in
Chrome 150, so the zone-30 position rule accepts ANY toolbar button whose right
edge is within 60 px of the window's right edge (the width limit was removed).
Verified: `{"zone":30,"zones":[30,20,1]}` over the pill → `trig 95: zones=[30,20,1]
∩ [30] → executing`.

**SW gate: burst cache + menu pass-through:**
- **burst cache** (`__acZONE_CACHE_MS = 120`): one physical event makes the
  engine emit a 750 for EVERY matching trigger, and each one used to re-ask the
  helper. Between two such queries the UI can change under the cursor (Chrome
  scrolls the tab strip on wheel!), so the burst saw different zones — the
  zone-15 trigger's 750 arrived just after the strip scrolled and got 12 →
  skipped ("wheel over the close button does nothing"). All 750s of one burst
  now share ONE helper answer (short TTL + shared in-flight promise).
- **menu pass-through**: the AutoControl menu-item regions (UI 40-51 = engine
  60-71) are classified by the ENGINE (it knows the hovered item) — the helper
  has no signature for the native menu. The gate now only checks regions the
  helper CAN verify (`__AC_ZONE_KNOWN`); a trigger whose regions are all
  menu-item regions passes with the engine's verdict. Before this fix every
  menu-item trigger was silently skipped by the gate (regression vs MV2).

**Verified live (real OS wheel through the native hook, sentinel-based log
tail — the console backlog no longer confuses the result):**

| Point | Result |
|---|---|
| tab body | `trig 41: zones=[12,1] ∩ [12] → executing` (control ✓) |
| tab's close button | `trig 92: zones=[15,1] ∩ [15] → executing` ✅ |
| new-tab "+" | `trig 96: zones=[16,1] ∩ [16] → executing` ✅ |
| update pill (menu) | `trig 95: zones=[30,20,1] ∩ [30] → executing` ✅ |

**⚠ Deploy notes (learned the hard way):** the engine file is locked by the
engine process of ANY browser running this extension (the multi-browser test
left a second browser's engine holding it) — kill the engines and copy in the
same tight loop until it succeeds; then restart the test browser. **A browser
restart makes the extension import `settings.dat` into storage** (MV2
behaviour: file check → import) — the live test triggers were replaced by the
file's content; keep that in mind during testing.

**Resolved afterwards:** zone 17 (speaker) ✅ verified on an audible tab
(§2f(b)); zone 4 (title area) ✅ and 33 (bookmark) ✅ verified — the full 12-area
summary is in §1; menu items ✅ — region 40 verified live over the OPEN menu
(§3 item 6). The v18 patch itself was replaced the same night (§2g): its
always-match branch was also the CONSUMPTION decision, so it swallowed the
wheel everywhere.

---

## 2f. USER REPORT → FIXES (2026-09-12, evening)

**User report:** "title area seems broken — it is meant as the window title,
the tabs, the omnibox, i.e. everything in this rectangle bounded by the
window's left/right/top borders, its bottom edge where the panel meets the
page"; "closing a tab worked, the speaker icon did not"; "new tab, toolbar,
bookmark, browser menu are detected"; **"I cannot scroll pages when an action
is bound to wheel rotation without a modifier key"**.

### (a) Title area (4) = the WHOLE top band — FIXED + verified
The app's own illustration (`file80.js`, region `titA`) is a full-width rect
from the window's top edge down to the page, and the user's definition matches
it. Implemented **chain-based** in the helper: `inToolbar || stripNear ||
isTabBtn` → zone 4, plus the existing unnamed-PANE rule for the frame. Points
BELOW the page's top edge never get 4 (the page's chain has no toolbar, and
`roles[0]==16` is excluded for DOCUMENT points).

Verified live (Chrome 150, floating window, physical px):

| Point | Answer | |
|---|---|---|
| tab body (450,194) | `[12,4,1]` | ✅ title band includes the tabs |
| omnibox (1200,260) | `[21,20,4,1]` | ✅ includes the omnibox |
| toolbar (1200,230) | `[20,4,1]` | ✅ |
| window controls (2200,194) | `[4,1]` | ✅ |
| page (1200,320) | `[3,1]` | ✅ no false 4 below the band |

### (b) Speaker icon (17) — FIXED + verified (the real root cause)
Chrome 150 does **not** expose the tab's speaker icon to hit-testing:
`AccessibleObjectFromPoint` over the icon returns the **PAGETAB** itself
(probed at 565/575/585/595 × 190 — always role 37). The old rule classified
"a 43-button under a PAGETAB, left half of the tab" — but the tab's own a11y
rect is UNRELIABLE (measured: tab 2 `[275,164 385x62]` while its close button
sits at `[596,173 43x43]`; tab 1 is reported `97x62` wide): the speaker icon
therefore fell into the "right half" → zone **15 (close!)** — the user's
"s`peaker does not work" was actually "the speaker fires the CLOSE zone".

FIX (`TabButtonZone`): from the hovered PAGETAB, walk its a11y CHILDREN, find
the `role 43` button whose rect contains the cursor, and classify it by
SIBLING ORDER — the close button is always the rightmost one. Verified on the
audible Rammstein tab: `{"zone":17,"zones":[17,4,1]}` (before: `[12,1]` /
`[15,..]`), the close button → `{15,4,1}` ✅. A tab that is neither audible
nor muted has its mute button present but with a `0x0` rect → never hit.
The tab rules now also EXCLUDE zone 12 for points that hit a tab button.

### (c) Menu button (30) — re-verified
`role 57 'Finish update' [2093,233 167x52]` (the "New Chrome available" pill,
right edge 20 px from the window's edge) → `[30,20,4,1]` ✅; the profile avatar
(right edge 195 px away) stays `[20,4,1]` ✅.

### (d) ⚠ MENU ITEMS (40-51) ARE FORCE-MATCHED BY v18 — needs a gate fix
> **UPDATE 2026-09-12 (night): the v18 cave is GONE — the deployed build is
> v19, where the always-match branch only exists as a fallback for a
> not-running helper (`alive == 0`). See §2g.**
>
> **✅ RESOLVED:** menu regions (`edx >= 0x28`) fall through to the ENGINE's own
> classification again, so the concern below no longer applies. Verified live
> over the OPEN menu (region 40 fires, silent everywhere else) — §2g, §3 item 6.
> Regions 41-51 use the same route and remain individually unverified.

The compiled type-60 precond carries the **RAW UI region** — verified by
compiling test triggers through the real `_mh`:
`{type:14,"value":41}` for "Menu item: tab", `…"value":12/4/30/21/3` for the
others. So the v18 patch's `cmp edx,3Ch / jae original` **does not route the
menu items** to the engine's own classification (that would require 60-71) —
the whole claim in §2e is unverified and, as far as the config shows, WRONG:
menu-item regions take the "always match" branch, and because the SW gate
treats them as "engine-classified" and passes them through, a menu trigger can
fire ANYWHERE (regression vs MV2 — before the gate existed the engine's own
menu logic decided). Open for the next step: gate them with the native menu
state (type 185 → `{hilited,hovered,marked}`, `hovered == -1` = no item under
the cursor) or verify what `edx` really holds for menu preconds.

### (e) ⚠ PLAIN-WHEEL ZONE TRIGGERS BLOCK PAGE SCROLLING (v18 regression)
> **SOLVED 2026-09-12 (night) by v19 — the engine now reads a zone table the
> helper writes, so a region matches ONLY when the cursor really is over it.
> Verified live: page wheel scrolls (800 → 1100 → 2100) with the zone-12
> trigger enabled and no false 750s; wheel over the tab strip fires trigger
> 44 (`zones=[12,4,1] ∩ [12] → executing`). See §2g.**

The mouseOver precond drives CONSUMPTION, not just the 750: `FUN_004156f0` has
exactly ONE call site (`0x415bdc`) and its result is returned by the enclosing
function (the input-matching decision). With v18 **every** region below 60
matches → a wheel trigger with ANY mouseOver condition consumes the wheel
EVERYWHERE → the page never scrolls (the user's plain-wheel triggers #5/#6
(zone 21), #41 (zone 12), #43 (zone 21), #44 (zone 30) — all `wheelDn/w2/blk1`).
MV2 semantics required the opposite: over the page the zone check failed → the
wheel passed through and Chrome scrolled.
**Fix direction (agreed):** feed the REAL zone into the engine — the helper
maintains the zone set and writes a 32-bit bitmask (bit = region; `0` =
"helper not running" = fall back to always-match; `0x80000000` = "cursor over
another app" = never match) into the engine's memory; the patched check reads
it instead of matching blindly. The cave has room (93 zero bytes of .text tail
padding measured by `Test/engine_abi_dump.js`), the mask fits next to the code
and the helper already runs a 120 ms heartbeat thread (added for the a11y
sleep issue) — the write itself is the next step (needs `WriteProcessMemory`
into the engine, `VirtualProtectEx` the cave page RWX first).

### (f) Other findings from this session
- **The a11y tree sleeps**: after ~30 s without a client request Chrome turns
  its accessibility engine off; a probe run right after that pause answered
  `zone 4` (an unnamed PANE) for EVERY point, the page included, until the tree
  rebuilt. The helper now runs a **background heartbeat** (a classification
  every 120 ms while the cursor moves, at least every 1.2 s) + a 400 ms request
  cache, so the tree never sleeps while the helper lives.
- **VS Code is not a browser**: the "maximized Chrome window" in an a11y scan
  was VS Code (`Chrome_WidgetWin_1`, generic PANEs, no a11y tree) — a generic
  pane would have produced a false zone 1/4. The helper now reports zones ONLY
  for the browser that spawned it (hovered window's root process == the
  helper's parent process, when the parent is chrome/msedge/brave/opera/
  vivaldi/chromium/yandex). Outside that browser the answer is `{"zone":0,
  "zones":[]}` → every zone-gated trigger is skipped (MV2 semantics).
- **Synthesized wheel goes to the FOCUSED window** — `mouse_event` does not
  deliver the wheel to the window under the cursor, so a scroll test must
  FOREGROUND the browser first (`Test/zone_fg_wheel.ps1` does; `_ac_mouse.ps1`
  needed `[BitConverter]::ToUInt32` for the negative delta — `[uint32]-120`
  throws in PS 5.1). With the browser focused a plain wheel scrolls the page
  (measured 240 px for 3 notches) — i.e. this measurement alone cannot prove
  the consumption bug; the trigger config must be live in the engine.
- New tools: `Test/zone_chain.ps1` (MSAA ancestry for points), `zone_scan5.ps1`
  (child HWNDs + all tabs with their buttons), `zone_wininfo.ps1` (which
  process owns the window under a point), `zone_cfg_dump.js` (triggers with
  their zones/actions from storage), `cdp_page_eval.js` (evaluate in a page
  target — needed for the settings page, which `scripting` cannot touch),
  `zone_fg_wheel.ps1`, `zone_fg_scroll.ps1`, `zone_scroll_test.ps1`,
  `engine_abi_dump.js` (PE sections, call sites, padding).

## 2g. SOLUTION (2026-09-12, night) — engine v19: the ZONE TABLE

**Idea.** The engine cannot classify Chrome's UI (MSAA is unreachable from its
LL-hook thread, §12 of the RE doc) and blindly matching everything breaks
input consumption. So the *decision* moves out of the engine: the helper
(which CAN classify) writes a small table into the engine's address space and
the patched matcher reads it.

> **How to rebuild both native parts bit-for-bit** (hashes, every byte of the
> patch, helper build recipe, deploy/rollback): `Docs/BUILD-NATIVE.md`;
> one-command check: `powershell -File Test/build_native.ps1`.

**The table** (one `VirtualAllocEx` page, `PAGE_READWRITE`, owned by the
helper):
```
+0x00 : alive   (dword, 1 while the helper lives)
+0x10 : table   (64 dwords; table[region] = 1 → the precond matches)
```

**The engine patch** — `AutoControl_native/patches/patch_zones_v19.js` (deterministic build from the
original exe in `AutoControl_native/original/`; the 93 zero bytes of .text tail padding at VA `0x47F7A3` are the
cave, the function entry `0x4156F0` gets a 5-byte `jmp` to it):
```
00: 83 FA 28            cmp  edx, 28h        ; region id
03: 73 17               jae  ORIG            ; >= 40 -> engine's own logic
05: 80 3D <alive> 00    cmp  byte [alive], 0
0C: 74 08               je   NOTALIVE
0E: 8B 04 95 <table>    mov  eax, [edx*4+table]
15: C3                  ret                  ; eax = match (0/1)
16: B8 01 00 00 00      NOTALIVE: mov eax, 1  ; helper down -> v18 behaviour
1B: C3                  ret
1C: 83 EC 20 53 55      ORIG: the original first 5 bytes
21: E9 <rel32>          jmp  0x4156F5
```
The file ships the "always match" prefix (variant A) so an engine started
WITHOUT the helper behaves like v18; the helper rewrites bytes `0x00..0x1B`
with the table version within ~1 s of the first classification.

**Verified live (Chrome 150 SxS, real OS input through the native hooks):**
| test | result |
|---|---|
| wheel over the page, 3 notches | `window.scrollY` 800 → 1100 → 1800 → 2100, **0** trigger 750s |
| wheel over the tab strip | `[AC-MV3-ZONE] trig 44: zones=[12,4,1] ∩ [12] → executing` + `pinTabs` ×2 |
| helper classification | page `[3,1]`, tab strip `[12,4,1]`, omnibox `[21,20,4,1]` |
| engine cave read back | `alive=1`, `slot[12]=1`, `slot[3]=0`, `slot[4]=1` |

**Pitfalls found while building it (both cost a long hunt):**
1. **Cave off-by-one.** The first helper layout put the `ret` at offset
   `0x14` — one byte early — so it overwrote the high byte of the table
   address (`0x03950010` → `0xC3950010`) AND returned without reading. Symptom:
   the engine asked for the regions (diag build) but never matched. Fixed:
   the read ends at `0x14`, `ORIG_BLOCK = 0x1C` (bytes `0x00..0x1B` are the
   helper's, `0x1C..` is the untouched original). `mh_test` B53 pins it.
2. **Chicken-and-egg startup.** The helper only ran when the SW asked it, and
   the SW only asked on a 750 — which the engine drops when it cannot classify
   the zone. The SW now pings the helper every 2.5 s (`__acZoneAsk(300)`)
   from boot; the helper starts, fills the table and the engine's matcher
   starts answering correctly.
3. **The helper must own its page.** An early build reused the address it
   found in the cave (pointer from a previous run) → wrote its table into a
   page it did not own → the engine read stale memory.

4. **A test trigger with a missing `sctnId` is INVISIBLE but ACTIVE** (user
   rule: test triggers MUST stay visible in the settings UI). The settings UI
   renders actions per section tab; if the trigger's `sctnId` is not in
   `storage.local.sections`, nothing shows it — while the engine keeps
   executing it. Four test triggers created this way (`sctnId: "3"`, no such
   section) looked like a phantom action: every wheel over the browser-menu
   button switched tabs (trigger 95, region 30 → `switchRight`) while the
   settings page showed no such trigger. `Test/zone_add_test.js` now verifies
   the section exists and drops it otherwise (prints `visible=true/false`);
   the other add-scripts write no section at all. The four triggers were
   deleted 2026-09-12.
5. **The wheel goes to the ACTIVE tab / focused window — and a dead mouse hook
   looks exactly like "the zone does not work".** After hard-killing the engine
   (`taskkill /F`) its low-level MOUSE hook can stay dead while the keyboard
   keeps working: no 750 for any mouse event, zone tests fail everywhere
   (including region 12, which is proven). A browser restart heals it. Always
   re-run the known-good control (wheel over the tab strip → trigger 44)
   BEFORE concluding anything about a zone.

**Both former open questions here are CLOSED (2026-09-12):**

- **Regions ≥ 21**: ✅ CORRECTED 2026-09-12 (user-verified): **the omnibox
  (21), the bookmark star (33) and the browser-menu button (30) DO work** —
  the earlier negative result was measured while the engine's mouse hook was
  dead (see pitfall 5). Live proof from the SW log:
  `trig 1: zones=[21,20,4,1] ∩ [21] → executing` (omnibox),
  `… [33,20,4,1] ∩ [33] …` (bookmark),
  `… [30,20,4,1] ∩ [30] …` (menu button). The `edx-3 = 0..17` jump table is
  the ENGINE's own switch; it does not limit the patched cave.
- **Menu items (region 40 = "Any menu item")**: ✅ VERIFIED WORKING
  (2026-09-12, user). The engine's own classification (`jae ORIG` branch)
  gets them right: the trigger fired while scrolling over the OPEN menu and
  stayed silent over the page / tab strip / beside the open menu. The old
  v18 warning ("can fire anywhere") is obsolete — v18's always-match branch
  is gone.

---

## 3. Research plan

**1-3 DONE (2026-09-12)** — signatures collected by the scanners (§2),
`Classify()` extended and verified live (§2d), the helper rebuilt and
redeployed. What the plan got wrong: the button role is **43** (PUSHBUTTON)
in Chrome 150, not 44; the strip detector needs `60 at d0/d1` (a 60 at d2
is the frame ABOVE the strip); the kebab is not exposed at all (position rule
instead); "else → 1 or 0" became "1 ALWAYS plus the specific zones" (the
engine evaluated each region independently — see the multi-zone gate in §2d).

**4. Menu items (40-51) — ✅ RESOLVED (2026-09-12); the SW-side gating was NOT
needed.** The planned approach (ask the engine for the hovered index via type
185 and map index → zone from the menu spec) became unnecessary with v19: the
always-match branch is gone, the menu regions (`edx >= 0x28`) fall through to
the ENGINE's own classification, and the engine already tracks the native menu
itself (type 170 opens it, type 185 `{hilited, hovered, marked}` reports the
item indexes, type 175 closes it). Verified live: a `mouseOver = Any menu item`
(40) trigger fired over the OPEN menu and stayed silent over the page / tab
strip / beside the menu (§2g).
⚠ **Still open (minor):** the individual item kinds 41-51 were NOT each
verified — they share the same route and are expected to work, but per-kind
accuracy (does "Menu item: tab" fire on the right item?) is unproven. Verify
only if a user report appears.

**5. Zone 30 + zone 17 verification:**
- 30: ✅ RESOLVED 2026-09-12 — the pill counts as the menu button (user
  request); verified `zones=[30,20,4,1] ∩ [30] → executing`. Re-check only if a
  build exposes the kebab as a real element.
- 17: ✅ VERIFIED 2026-09-12 on an audible tab (§2f(b)) — the rule scans the
  tab's a11y CHILDREN for the button whose rect contains the cursor and
  classifies it by SIBLING ORDER (the icon is not hit-testable in Chrome 150).

**6. Menu items (40-51) — ✅ LIVE TEST DONE (2026-09-12, user-verified):**
region 40 fired while the wheel was over the OPEN AutoControl menu, and
negative controls (page / tab strip / beside the open menu) stayed silent. The
engine's verdict decides; the helper has no signature for the native menu.
⚠ Still valid: the menu is a separate layered window — the cursor must be
physically over it.

---

## 4. Test methodology (how to verify each zone)

**Setup (one-time):**
1. Chrome SxS with CDP + a11y:
     `Start-Process "$env:LOCALAPPDATA\Google\Chrome SxS\Application\chrome.exe" -ArgumentList '--remote-debugging-port=9223', "--user-data-dir=`"$env:LOCALAPPDATA\Google\Chrome SxS\User Data CDP`"", '--force-renderer-accessibility', '--lang=en-US'`
2. Engine **v19** deployed (`powershell -File Test/deploy_patched_engine.ps1`
   → it copies `AutoControl_native/patched/`, SHA-256 `1A10EDD1…`), config
   sent (`_Gf` via cdp_eval, verify `type 60`
   in the boot log — see AGENTS.md). ⚠ A browser restart re-imports
   `settings.dat` into storage (test triggers get replaced).
3. Helper registered + responding: `node Test/zone_helper_smoke.js [exe]`
   (default = the deployed copy; prints `zone` + `zones`).
4. SW logging on (`advOpts.logSw`) — the gate logs every decision:
   `[AC-MV3-ZONE] trig N: zones=[…] ∩ [regions] → executing|skipped`.

**Per-zone test trigger:** add a trigger with:
- event = wheel (or middle-click) WITHOUT modifiers,
- a `mouse over` precond = the zone under test,
- action = `Reload tabs` on currentTab (visible result).

⚠ **Use PHYSICAL input for the hover + wheel.** A synthesized wheel
(`mouse_event`, `SendInput`, another process) moves the cursor but does NOT
refresh the engine's hover cache — injected input is flagged
(`LLMHF_INJECTED`) and the engine ignores it. A wheel injected right after
`SetCursorPos` is therefore judged against the PREVIOUS hover position: my
synthetic hits "worked" only when the cache already happened to be right
(they silently produced no 750 at all in most runs, 2026-09-13). The
signed-off method is the user's own hand on the mouse, one step at a time,
with the agent reading the SW log after each step.

**Procedure for each zone Z:**
1. Hover the target element (e.g. the `+` button for zone 16).
2. Scroll the wheel 2-3 notches.
3. Expected in the SW console:
   `[AC-MV3-ZONE] trig N: zones=[16,4,1] ∩ [16] → executing` and the tab
   reloads. Read it with `node Test/ac_swlog_act.js 9223 "<command>"` — it
   prints ONLY the lines produced after the command (the console backlog is
   replayed on attach, so a naive reader mixes history with live events).
4. Repeat at 2-3 other elements — expect `zones=[…] ∉ [Z] → skipped` and NO
   reload (the page/other elements keep their normal behavior).
5. Record the result in the §1 table.

**Negative controls (must stay skipped):** page (3), omnibox (21),
another zone's element.

**Menu zones (40-51):** open the AutoControl tab menu, hover each item
type, wheel — only the OPEN menu may fire (the engine classifies these).

**⚠ Two traps that look exactly like "the zone is broken" (both cost hours):**
- **A dead MOUSE hook.** After `taskkill /F` on the engine its low-level mouse
  hook can die while the keyboard keeps working — then NO mouse trigger fires
  anywhere (even region 12, which is proven). Always re-run a known-good
  control (wheel over the tab strip → zone-12 trigger) BEFORE judging a zone;
  a browser restart heals it.
- **An INVISIBLE test trigger.** A trigger whose `sctnId` is missing from
  `storage.local.sections` is rendered nowhere in the settings UI while the
  engine keeps executing it (looks like a phantom action — user rule: test
  triggers MUST stay visible). `Test/zone_add_test.js` verifies the section
  and drops it otherwise (prints `visible=true/false`).

**Automation:** `Test/ac_swlog_dump.js` (read-only SW console dump, regex
filter) and `Test/ac_swlog_act.js` (only the lines after a command) are the
log readers; `Test/zone_probe.ps1` asks the deployed helper for a list of
points; `Test/zone_e2e_test.ps1` / `Test/zone_fg_wheel.ps1` inject a REAL
wheel (⚠ a synthesized wheel goes to the FOCUSED window — foreground the
browser first); `Test/zone_add_test.js add|remove` manages a temporary zone
trigger. The older 750 watchers and SW tails (`zone_watch750.js`,
`zone_swlog*.js`, `zone_swtail.js`) were superseded and now live in
`Test/archive/` (see `Test/archive/README.md`).

---

## 5. Files touched by this work

| File | Role | state (2026-09-13) |
|---|---|---|
| `Test/ac_zone_helper.cs` | helper source (`Classify()`, `WriteZoneTable`) | ✅ 11 zones + DPI + `zones[]` + pill→30 rule + a11y heartbeat + own-browser gate |
| `AutoControl_native/ac_zone_helper.exe` | repo copy of the helper binary | ✅ `091627630D…` (deterministic Roslyn build, 2026-09-13) |
| `%LOCALAPPDATA%\AutoControl\ac_zone_helper.exe` | **the deployed binary Chrome runs** | ✅ same hash (Chrome picks it up without an extension reload) |
| `AutoControl_native/patches/patch_zones_v19.js` | engine patch builder (zone table) | ✅ **CURRENT** — see `patches/README.md` |
| `AutoControl_native/patched/AutoCtrl_2025.4.22.0.v19.exe` | repo copy of the built engine | ✅ `1A10EDD1…` |
| `%LOCALAPPDATA%\AutoControl\AutoCtrl_2025.4.22.0.exe` | **the deployed engine** | ✅ v19 (`1A10EDD1…`) |
| `Test/patch_zones_v18.js` | previous patch (always match below 60) | ⚠️ history only — it also broke wheel consumption |
| `Test/patch_zones_v19diag.js` | diagnostic variant (records the asked-for regions) | needs the accName build; not for zone work |
| `AutoControl_native/com.autocontrol.zonehelper.json` | host manifest (`path` = the LOCALAPPDATA exe) | unchanged |
| `mv3-build/sw.js` | zone gate (`__acZoneAsk` / `__acDispatchTrigger750` / `__acBuildZoneMap`) | ✅ multi-zone intersect + menu pass-through + 120 ms burst cache + 2.5 s helper keepalive + `_Sk` re-sync |
| `Test/mh_test.js` | smoke tests | ✅ B53 (zone gate + patch/helper layout), B53b–B53g (patch CLI, docs vs bytes, the byte proof + its teeth test, helper writer, Ghidra listing) |
| `C:\Work\AutoControl-…-Chrome\mv3-build\sw.js` | **the copy Chrome actually loads** | ⚠ must be updated too (load-path gotcha, §2d) |
| `Test/patch_bytes_verify.js` | **proof**: decode the injected bytes, assert every branch target, diff vs the original | ✅ new 2026-09-13 |
| `Test/engine_abi_dump.js` | PE sections, call sites, references to the matcher, cave page mapping — **as a check** (`ABI AUDIT: OK` / exit 1) | ✅ 2026-09-13 |
| `Test/build_native.ps1` | rebuild both natives + SHA-256 check (`-UpdatePatched`) | ✅ |
| `Test/deploy_patched_engine.ps1` | deploy the patched engine (stops only SxS, backs up, verifies) | ✅ |
| `Test/zone_probe.ps1` | per-point live helper probe | ✅ |
| `Test/zone_e2e_test.ps1`, `Test/zone_fg_wheel.ps1` | real-wheel end-to-end + SW log tail | ✅ |
| `Test/ac_swlog_dump.js`, `ac_swlog_act.js` | SW console readers (read-only / only new lines) | ✅ replace the archived `zone_swlog*.js` |
| `Test/zone_helper_smoke.js` | helper smoke test | ✅ (prints `zone` + `zones`; optional exe path) |
| `Test/zone_add_test.js`, `zone_remove_test_triggers.js` | temporary zone triggers (visibility-guarded) | ✅ |
| `Test/zone-tests/` | the zone regression suite + README | ✅ new 2026-09-12 |
| `Test/zone_proto.ps1` | original MSAA walker (leader of the tab-strip solution) | keep as reference |
| `Test/archive/` (`zone-re/`, `zone-probes/`, `sw-log/`) | superseded scanners / watchers / one-offs | 📦 archived 2026-09-12 — index in `Test/archive/README.md` |
| `Docs/BUILD-NATIVE.md` | bit-for-bit rebuild recipe for BOTH natives | ✅ |
| `Docs/archive/NATIVE-REVERSING-2026-08-31.md` | RE context (§10-§13) | ✅ §13 updated |
| `Docs/FEATURES-MV3.md` §7-12 | hover-region status | ✅ updated (all 12 areas) |
| `AGENTS.md` (zone bullets) | gotchas: DPI, load path, signatures, dead mouse hook, proof chain | ✅ updated |
| `README.md` §4.3 / §4.4 | user/dev install guide (helper + patched engine) | ✅ updated |

---

## 6. Helper failure recovery — TODO (2026-09-05)

**Problem:** if `ac_zone_helper.exe` hangs (process alive but not answering
stdin), every zone request times out (250 ms) → `zone=-2` → ALL zone-gated
actions silently skip until the SW restarts. If the helper process DIES,
`onDisconnect` already resets the port → the next request spawns a fresh
process (self-healing works). Only the HANG case is unhealed.

**Manual Emergency Repair DOES work** for the hang case: it reloads the SW →
fresh SW → new `connectNative` → Chrome spawns a NEW helper process (it does
not reuse the hung one) → everything recovers. The hung process stays as a
zombie until reboot (cosmetic).

**TODO — two options (user asked to track both):**

1. **Automatic helper self-heal (preferred, ~10 lines in `sw.js`):** in
   `__acZoneAsk`, count CONSECUTIVE timeouts — after 3 in a row do
   `__acZonePort.disconnect(); __acZonePort = null;` → the next request
   creates a fresh process. Mirrors the capture-watchdog pattern. No bundle
   rebuild needed (sw.js is not in the bundle). Also log
   `[AC-MV3-ZONE] helper unresponsive — respawning` for diagnosability.
   ⚠ **MULTI-BROWSER SAFETY (user requirement, 2026-09-05):** several
   browsers may each run their OWN `ac_zone_helper.exe` (one per browser's
   connectNative). ANY process kill must target ONLY OUR helper process —
   never a blanket `taskkill /IM ac_zone_helper.exe` (would kill the other
   browsers' live helpers). Implementation: the helper replies with its own
   PID (`{__id, zone, pid}` — `Process.GetCurrentProcess().Id` in
   `ac_zone_helper.cs`); the SW stores it on the first reply and, when
   respawning, either just `port.disconnect()` (Chrome terminates the
   process it spawned — the SAFE default, no taskkill needed) or, if a
   hard kill is ever required, `taskkill /PID <stored pid>` only.
   Note: Chrome kills the native host when its port disconnects, so
   `port.disconnect()` alone should suffice for the hang case.
2. **Emergency Repair integration (already works, document only):** the
   manual repair path heals the helper via the SW reload; add a doc note
   (README §4.3 or AGENTS.md) that a hung helper is fixed by Emergency
   Repair. Optionally: kill ONLY OUR stale helper zombie during the repair
   (via the stored PID — see above; NEVER by image name).

**Status:** ⬜ open (defers — see the note below) — implement option 1 (auto-heal
with PID tracking), optionally option 2's PID-scoped zombie kill; document
option 2 in the README.

**⏸ DEFERRED (2026-09-12, user request):** tracked in the backlog, to be
implemented later ("put it in the TODO, for later"). Not blocking anything:
Emergency Repair heals a hung helper, and a DEAD helper self-heals via
`onDisconnect`.
