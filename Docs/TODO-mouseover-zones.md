# TODO — Mouse-over zones: make ALL zones work (Chrome 148+/150)

**Created:** 2026-09-03 · **Status:** ✅ **CORE GOAL ACHIEVED (2026-09-12)** — all
12 action-editor areas verified live. The follow-up rounds of **2026-09-20 … 10-05**
closed every live defect found since (§2f(g)–(r)); ⬜ **no open items are left in
this file** — the two follow-ups moved to their own TODOs (below).
**Goal:** every mouse-over zone condition works on Chrome 148+/150 with the
zone-helper architecture. Zone 12 (tab strip) and 16 (new-tab button) were the
first proofs; **all 12 areas are now verified** (§1 summary).

## Status by browser (updated 2026-10-05)

| Browser | Zones | What is missing / different |
|---|---|---|
| Chrome 148 / Canary / Brave | **11 of 11** | — |
| Opera 135 (Chromium 151) | **10 of 11** | speaker icon impossible; the "+" is reported as zone 12 (see the quirks list below) |
| Vivaldi | **8 of 11** | speaker icon impossible; the "+" still missing; the close button (15) is *reported* working (2026-10-05 — the zone-15 trigger fired) but was never probed separately |

The **"hovered tab" action** (rounds 2–3: §2f(m)(o)(q)) is verified with a
physical wheel in **all five browsers** — the tab under the cursor reloads, on the
first notch (2026-10-05). The **"event tab"** target is fixed for Chrome 148+ too
(§2f(n)).

## What was FIXED in the 2026-09-20 … 10-05 rounds

One section per finding in §2f; each was reproduced live before the fix and
re-tested after it.

| § | Symptom (as reported) | Root cause → fix |
|---|---|---|
| (g) | the empty strip area counted as a tab | zone 12 now requires a real PAGETAB |
| (h) | Opera: bookmark zone fired on every toolbar button | the omnibox GROUPING must sit BETWEEN button and toolbar; Opera's heart matched BY NAME |
| (i) | Opera: zone 30 fired on the Extensions button | the right-edge rule is Chromium-only; 'Extensions'/'Расширения' is never the menu |
| (j) | Opera: the close button never matched | it is a square PANE (16) in the right part of the tab → `IsPaneCloseButton` |
| (k) | a browser menu/dropdown was treated as chrome | a WS_POPUP+TOOLWINDOW popup answers only zone 1 |
| (l) | "works, but sometimes stops" | the zone TABLE was written up to 170 ms late → 30 ms poll + settle detection |
| (m) | hovered-tab actions hit the ACTIVE tab | native 485 lost the tab identity → the helper answers 485 |
| (n) | the "Event tab" target did nothing | `evtTabs` has no fallback and `if(c)` is true for `[]` → `_pp.filter` patch |
| (o) | the PREVIOUS tab reloaded; the first notch was ignored | stale `_kg`, a tab cached for another point, a timed-out zone query, two walks per event |
| (p) | Opera 135: hovering the close button said "Title area" | the button is nested one level deeper (`PAGETAB → PANE → 43`) → any-depth tab + a 2-level scan |
| (q) | Chrome 148: the FIRST tab reloaded / the ACTIVE one | the strip was found one level too high (index always 0) and the answer arrived after the SW gave up |
| (r) | switching tabs with a wheel was delayed | the hovered-tab refresh ran before EVERY dispatch, even for `currentTab` actions → `__acHoverNeeded` + a warm tab cache |

**Open items — none left here; the two follow-ups live in their own files:**
1. **Menu-item zones (41-51), per-kind verification** — LOW PRIORITY, split out
   2026-10-05 → `Docs/TODO-menu-items.md`.
2. **Auto-heal for a HUNG helper** → `Docs/TODO-helper-autoheal.md`
   (deferred by the user 2026-09-12; Emergency Repair already heals it manually).

**Known limitations (updated 2026-10-05; helper `C8466CF7CE1AC40C3A56AAD175B0F545B914E670679B495C2199E469A483ABAF`):**
the tab's **speaker icon cannot be implemented** in Opera/Vivaldi — the sound is
drawn over the favicon in a single element present on every tab, so a playing tab
is indistinguishable from a silent one (see README §5a). Vivaldi additionally
needs `--force-renderer-accessibility` and its UI lives inside the page document
(docDepth fix in the helper).

**Known quirks of the fork handling (see §7 "How to check"):**
- **Opera — the new-tab "+" is reported as the Browser tab (12), not as the
  new-tab button (16)** — its parent is the `22 'Tab Bar'` element, not the
  PAGETABLIST (60), so the `43+60 → 16` rule does not fire and the tab rule
  claims it. Cosmetic for a 16-trigger (a wheel over "+" runs the zone-12
  action); the 16-trigger itself never fires.
- **Opera — the RIGHTMOST toolbar button is the extensions-panel toggle**
  (role 57 'Extensions', its right edge 38 px from the window edge), so the
  Chrome-style right-edge rule used to report the browser-menu button (30)
  there. The rule is now skipped for Opera/Vivaldi (their menu is on the LEFT
  and matched BY NAME) and a button named 'Extensions' is never the menu —
  §2f(i).
- **Vivaldi — the "Workspaces" button (left, role 57, no "menu" in the
  name, nor a localized variant) is reported as the Omnibox (21)** — it is not excluded from the
  site-info-lock rule (`57+20 → 21`), so a wheel over it runs the zone-21
  action instead of nothing (or the menu action).
- **Vivaldi — the tab's close button (15) needs a dedicated probe.** The
  2026-10-04 generalization (§2f(p): any-depth PAGETAB + a 2-level button scan)
  should cover it, and the user's 2026-10-05 test had the zone-15 trigger fire
  there, but no `msaa_chain.ps1` dump of a Vivaldi tab has been taken — so the
  matrix row stays "reported", not "verified". Same for the "+" (16): re-check
  it, since the Opera "+" quirk is a PARENT-role difference (`22 'Tab Bar'`
  instead of the PAGETABLIST) that Vivaldi may or may not share.

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
  SHA-256 `1A10EDD191B80A806DF66558B2B1E78BE8D6AD81E93EEAC772D13F222E212C3E`; built copy + deploy target:
  `AutoControl_native/patched/`) — the mouseOver region check now reads a
  **table the helper writes into the engine's memory** (`alive` flag + 64
  region slots), so a region matches ONLY when the cursor really is over it.
  That same check drives INPUT CONSUMPTION (match == consume), which is why
  the earlier always-match v18 made every wheel trigger swallow the wheel.
  Menu regions ≥ 40 keep the engine's own classification; with no helper
  running (`alive == 0`) the engine falls back to the v18 behaviour. v18
  (`Test/patch_zones_v18.js`, `F96BF5442B8660AC93FCAFC0FFFAC87630DDD3A65DFCDCE1FDDDC6F26359286F`) is kept only as history — see §2e
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
| 3 | Title area | 4 | `_Ce` | ✅ works — the title bar / tab strip row ONLY (chain-based: `stripNear || isTabBtn`); the toolbar and the omnibox are NOT part of it (user correction 2026-09-20, see §2f(a)) |
| 4 | Browser tab | 12 | `_9t` | ✅ works — a PAGETAB (role 37) anywhere in d0..d3. The EMPTY strip area (role 60 alone) does NOT count: the engine's own region-12 check (`FUN_00415570`) matched only a PAGETAB or its direct child (user correction 2026-09-20) |
| 5 | Tab's close button | 15 | `_Go` | ✅ **VERIFIED 2026-09-12** (43 under a PAGETAB, right half; set `[15,4,1]`, no 12) · Opera: a square PANE in the right part of the tab (§2f(j)) |
| 6 | Tab's speaker icon | 17 | `_2` | ✅ **VERIFIED 2026-09-12** (43 under a PAGETAB, left half; set `[17,4,1]` — the tab must be AUDIBLE) |
| 7 | New tab button | 16 | `_xw` | ✅ **VERIFIED 2026-09-12** (43 whose parent is the PAGETABLIST; set `[16,4,1]`) — §2a closed |
| 8 | Toolbar | 20 | `_uu` | ✅ works (role 22 TOOLBAR in the ancestry) |
| 9 | Omnibox | 21 | `_5e` | ✅ works (role 42 at d0/d1, or the lock button 57 under the omnibox group 20) |
| 10 | Bookmark button | 33 | `_Aa` | ✅ works — Chrome: a 43 inside the omnibox GROUPING 20 which sits in the toolbar; Opera: the heart matched BY NAME (§2f(h)) |
| 11 | Browser menu button | 30 | `_nj` | ✅ **VERIFIED 2026-09-12** — the update pill counts as the kebab (user request); Chrome-style RIGHT EDGE only — Opera/Vivaldi match their LEFT-side menu BY NAME (§2f(i)) |
| 12 | Any menu item | 40 | `_9r` | ✅ **VERIFIED 2026-09-12** (engine-classified via `jae ORIG`; fires over the OPEN menu only) |
| 13 | Menu item: tab | 41 | `_ju` | ⚠️ same engine-classified route as #12 — NOT individually verified; LOW PRIORITY, moved to `Docs/TODO-menu-items.md` (2026-10-05) |
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
| 3 | Title area | 4 | `[12,4,1]` / `[4,1]` (strip / frame) | ✅ — narrowed 2026-09-20: silent over the page, the toolbar AND the omnibox (the 2026-09-12 runs used the then-broad rule, see §2f(a)) |
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

Helper rules as of 2026-09-20 (`Test/ac_zone_helper.cs` -> `Classify()`):
`43 under 37 (right half) → 15`, `43 under 37 (left half) → 17`,
`square PANE (16) under 37 in the RIGHT part of the tab → 15` (Opera/Vivaldi
expose the close button as a plain pane — §2f(j)),
`43 under 60 → 16`, `42 at d0/d1 → 21`, `57 under 20 → 21`,
`43 inside GROUPING 20 inside TOOLBAR 22 → 33` (the GROUPING must sit
BETWEEN the button and the toolbar — Opera's window-contents container 20
sits ABOVE the toolbar, see §2f(h)), `TOOLBAR 22 in ancestry → 20`,
`square 43/57 hugging the window's right edge → 30` (Chromium layouts ONLY —
Opera/Vivaldi are excluded: their rightmost toolbar button is the
EXTENSIONS toggle; a button named 'Extensions' never answers 30 either —
§2f(i)),
`37 in d0..d3 → 12` (a PAGETAB; the empty strip 60 and the tab's own
buttons do NOT answer 12 — see §2f(a) and the engine's `FUN_00415570`),
`stripNear || isTabBtn → 4` (title bar /
tab strip only — narrowed 2026-09-20),
`PANE 16 outside toolbar/page/strip → 4`, plus zone 1 always.

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
| Tab-strip gap / empty strip | **60 PAGETABLIST** at d0 or d1 → 16 | 4 (title area only — the engine never matched region 12 there, corrected 2026-09-20) |
| Tab's close button | **43 PUSHBUTTON** 'Close' → 37 PAGETAB (right half of the tab) | 15 |
| Tab's speaker/audio icon | 43 PUSHBUTTON under 37 PAGETAB (left half) — appears over the favicon slot | 17 |
| New-tab button (`+`) | **43 PUSHBUTTON** 'New Tab' → **60 PAGETABLIST** → 16 | 16 |
| Tab search button | 57 BUTTONMENU 'Tab search' → 16 → 60 | (none — a strip button, not the strip) |
| Omnibox text field | **42 EDIT** 'Address and search bar' → 20 GROUPING → 22 TOOLBAR | 21 + 20 |
| Site-info (lock) | 57 BUTTONMENU 'View site information' → 20 → 22 | 21 + 20 |
| Bookmark star | **43 PUSHBUTTON** 'Bookmark this tab' → 16 → 20 GROUPING → 22 | 33 + 20 |
| Opera bookmark heart | **43 PUSHBUTTON** 'Add to bookmarks' / 'Edit bookmark' → 22 'Navigation' → 20 'Browser contents' — no grouping below the toolbar, so it is matched BY NAME (§2f(h)) | 33 + 20 |
| Toolbar buttons (Back/Forward/Reload) | 43 → **22 TOOLBAR** → 16 | 20 |
| Extension icons / profile ('You') | 57 / 43 → 16 → 22 | 20 |
| Browser menu (kebab) | EXPOSED in the a11y tree (role 57 BUTTONMENU, name "Chrome") — identified by POSITION; the earlier "missing" report was made on an outdated Chrome 150 and could not be re-checked then | 30 |
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
// (see `Test/README.md` — `ac_swlog_dump.js` / `ac_swlog_act.js`)
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
   - Chrome SxS (Canary): `HKCU\Software\Google\Chrome SxS\NativeMessagingHosts\com.autocontrol.zonehelper`
   - Edge: `HKCU\Software\Microsoft\Edge\NativeMessagingHosts\com.autocontrol.zonehelper`
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

### (a) Title area (4) — FIXED 2026-09-12, NARROWED 2026-09-20
> **CORRECTION 2026-09-20 (user):** the action editor's own description is
> "When the mouse is over the **title bar or tab strip**", and its illustration
> highlights the tab-strip row only — NOT the toolbar/omnibox. The original
> 2026-09-12 reading ("the WHOLE top band", from the user's own earlier
> definition) was wrong. The helper now answers 4 for the tab strip
> (chain-based: `stripNear || isTabBtn`) plus the window-frame PANE outside
> the toolbar (`roles[0]==16 && !inToolbar`); the toolbar and the omnibox are
> excluded. Helper `C8466CF7CE1AC40C3A56AAD175B0F545B914E670679B495C2199E469A483ABAF`.

The 2026-09-12 implementation was chain-based: `inToolbar || stripNear ||
isTabBtn` → zone 4, plus the unnamed-PANE rule for the frame. Points
BELOW the page's top edge never get 4 (the page's chain has no toolbar, and
`roles[0]==16` is excluded for DOCUMENT points).

Verified live on 2026-09-12 (Chrome 150, floating window, physical px) — with
the then-broad rule (the omnibox/toolbar rows are superseded by the 2026-09-20
correction above):

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
> Regions 41-51 use the same route; their PER-KIND accuracy is tracked separately
> (low priority) in `Docs/TODO-menu-items.md`.

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

### (g) Browser tab (12) — the EMPTY strip area does not count (2026-09-20)

**User report:** the empty strip area right of the "+" button answers
"Browser tab". **Authority:** the engine's own region-12 check
(`Test/native-disasm/decomp/00415570_FUN_00415570.c`, called from
`FUN_004156f0` case 0xc) matched ONLY a PAGETAB (role 37) or an element whose
DIRECT parent is a PAGETAB; the old-Chrome fallback for a PANE under the
PAGETABLIST is version-gated to Chrome < 100 (`DAT_004a23a4 - 0x55 < 0x0f`)
and never applied to modern builds. The helper used to answer 12 for the
strip's own PAGETABLIST (60) via the `tabDepth` scan — that clause is gone:
`tabDepth` now requires role 37, `stripNear` (for the TITLE-AREA zone 4) still
accepts 60 so the empty strip keeps its title-area coverage. The tab's own
buttons were already excluded (a 43-button under a PAGETAB is handled by
`TabButtonZone` → 15/17). Same day as the title-area narrowing (§2f(a)) and
the "+"-exclusion fix; helper
`C8466CF7CE1AC40C3A56AAD175B0F545B914E670679B495C2199E469A483ABAF`.

### (h) Bookmark zone (33) — a button inside the omnibox GROUP, or the heart BY NAME (2026-09-20)

**User report (Opera):** the action bound to "Bookmark button" fired over
EVERY omnibox button (Snapshot, Translate, Reader, Profile).

**Root cause:** the rule was `43 inside GROUPING 20 inside TOOLBAR 22 → 33`,
where `inGroup` was "any role-20 element anywhere above" — the ORDER was never
checked. Opera's toolbar buttons carry the window-contents container
(`20 'Browser contents'`) ABOVE the toolbar (`22 'Navigation'`), so every
toolbar button satisfied both halves and looked like a button inside the
omnibox group.

**Fix 1 — the order matters.** `inGroup` now requires the GROUPING to sit
BETWEEN the element and the toolbar (`groupDepth < toolbarDepth`). Chrome's
star chain `43 → 16 → 20 GROUPING → 22 TOOLBAR` still matches; Opera's
`43 → 16 → 16 → 22 → 20` does not — the five non-bookmark buttons now answer
`[20,1]`.

**Fix 2 — Opera's own bookmark button, by NAME.** The same narrowing also
dropped 33 from the heart (right of the address bar). It is STRUCTURALLY
IDENTICAL to its neighbours: `43 'Add to bookmarks'` (or `'Edit bookmark'`
while the page is bookmarked) → 22 'Navigation' → 20 'Browser contents', no
grouping below the toolbar, and `accKeyboardShortcut` is EMPTY for all six
omnibox buttons — so the NAME is the only discriminator. The heart is now
matched as an `else if` fallback ('Add to bookmarks' / 'Edit bookmark', the
Russian UI name via a unicode escape; the same approach as the Opera/Vivaldi
menu button, §2f(d)) and only for a button inside the toolbar 22 — a page
element whose name merely contains "bookmark" cannot match. Chrome's star
('Bookmark this tab') carries the name too but is already covered by the group
rule; the `else if` prevents a double entry.

⚠ **Why the first report looked like "Opera has no bookmark button":** the
heart is shown on regular pages only — on internal and extension pages the
address bar has no bookmark button at all (that page is what was inspected
first; user correction the same day). The heart itself was always there.

**Verified (probe against the deployed helper):** heart `[33,20,1]`, the five
neighbour buttons `[20,1]`, address field `[21,20,1]`, tabs `[12,4,1]`
(no regression). Helper
`C8466CF7CE1AC40C3A56AAD175B0F545B914E670679B495C2199E469A483ABAF`.

⚠ **Known edge (unchanged by this fix):** the rule cannot tell one
omnibox-group button from another by structure, so in Chrome every `43` inside
the group answers 33 — the group also holds the page-action buttons (Zoom /
Ask AI …), which are normally hidden. In Opera the reverse case applies: the
bookmark button is OUTSIDE such a group, hence the name fallback.

### (i) Browser menu button (30) — the right-edge rule is Chromium-only (2026-09-20)

**User report (Opera):** the zone-30 action fired in TWO places — the real
Opera menu on the left (correct) and the blue button that collapses the
extensions panel in the toolbar (wrong).

**Element found by the name probe:** `role 57 'Extensions' rect=(1668,599
36x37)` — the RIGHTMOST toolbar button in Opera 135, its right edge 38 px from
the window's right edge, i.e. inside the 60 px window of the Chrome-style
kebab rule. The next button to the left ('AutoControl Configuration',
`rect=(1620,599 36x37)`, right edge 86 px away) stayed excluded, which is why
only this one misfired.

**Fix 1 — the geometry rule is Chromium-only.** The helper now remembers its
browser's exe name (`browserName`, captured in the same ancestor walk that
finds `browserPid`) and `MenuAtRightEdge()` returns false for opera.exe /
vivaldi.exe: those forks put their menu on the LEFT and it is already matched
BY NAME (§2f(d)). The old code contradicted its own comment ("the kebab rule
is Chrome only"). A standalone helper run (zone probes) keeps the Chrome
behaviour, so the probes stay representative.

**Fix 2 — 'Extensions' is never the menu.** `IsRightEdgeButton` rejects a
button whose accessible name contains "extension" / "расширен" — the
extensions-panel toggle is a rightmost button in several builds and in none of
them is it the browser menu.

**Verified (probe against the deployed helper):** the extensions button
`[20,1]` (was `[30,20,1]`), the Opera menu (110/130,553) `[30,4,1]` ✅, the
heart `[33,20,1]` ✅, the extension icons `[20,1]` ✅. Helper
`C8466CF7CE1AC40C3A56AAD175B0F545B914E670679B495C2199E469A483ABAF`.

### (j) Tab's close button (15) in Opera — a square PANE, not a button (2026-09-20)

**Why it was broken:** Chrome exposes a tab's close button as a PUSHBUTTON
(role 43) and `TabButtonZone` scans the tab's 43-children. Opera does NOT:
the button is a plain PANE (role 16) there, so nothing matched and the point
fell through to the tab rule → the zone-15 trigger never fired.

**The signature** (Opera 135, identical on all three tabs; found with
`Test/msaa_chain.ps1 -TabKids`):

```
d2 role=37 'Rammstein…' [404,534 253x42] cc=3      <- the PAGETAB
  child1: role=16 '' [404,534 253x42] cc=6         <- tab body (wide)
  child2: role=16 '' [654,542 2x28]   cc=0         <- separator (2 px)
  child3: role=16 '' [605,554 37x37]  cc=1         <- CLOSE (square, right)
```

The close button is hit-testable DIRECTLY (AOP over it returns the button, its
parent is the PAGETAB), so the rule is: `roles[0] == 16 && roles[1] == 37`,
the rect is square-ish (20..60 px, |w−h| ≤ 12) and its centre lies in the
RIGHT 40% of the tab (`IsPaneCloseButton`). The position check keeps Chrome
safe: its favicon is ALSO a square PANE, but on the LEFT — and in
Chrome/Brave the close button is a real 43 handled by `TabButtonZone` anyway.

**Verified (probe):** close buttons of all three tabs `[15,4,1]` ✅; tab body,
favicon and the separator `[12,4,1]` (no false 15) ✅.

**Speaker (17) — confirmed NOT implementable in Opera:** the favicon slot is a
single `role=40 'Tab favicon' [410,543 25x24]` element present on EVERY tab,
its name does not change when the tab plays sound, and the tab has exactly
three children (body / separator / close) — there is no audio element to
match. This is the documented limitation (README §5a).

### (k) A browser UI popup is not browser chrome (2026-09-20)

**User report:** the zone-15 action "works, but sometimes stops". The SW log
showed 9 × `zones=[15,4,1] ∩ [15] → executing` and then one
`zones=[4,1] ∉ [15] → skipped`.

**Root cause found by reproducing it:** every SECOND wheel notch flipped the
answer for the SAME point. The point was then resolved to an unnamed PANE
`[111,536 365x43]` inside a role-11 window — and that window is the **Opera
main menu**: a layered popup owned by the browser window
(`WS_POPUP | WS_VISIBLE | WS_CLIPSIBLINGS | WS_CLIPCHILDREN`,
`WS_EX_NOACTIVATE | WS_EX_LAYERED | WS_EX_TOOLWINDOW | WS_EX_TOPMOST`,
419x1083 anchored at the content-area origin), whose children are
`New tab Ctrl+T`, `New window Ctrl+N`, `History`, `Bookmarks`,
`Extensions`, `Settings Alt+P`, `Exit` … — it COVERS the whole tab strip.

**Why it alternated:** the test tool `zone_fg_wheel.ps1` foregrounds the
window by HOLDING **Alt**, and Alt toggles the Opera menu — a pure test
artifact (each wheel press = one Alt = the menu flips). The user's single
skip has the same signature: the menu was open at that moment, so the cursor
really was over the menu, not over the tab strip.

**The real defect this exposed:** over an open browser menu the helper
answered **Title area (4)** — the hit is an unnamed PANE, so the window-frame
rule fired. A zone-4 trigger would then run while the user is inside the
browser menu, and a zone-15 trigger was skipped with a confusing `[4,1]` in
the log.

**Fix:** `OverBrowserPopup(pt)` — when the root window under the cursor is
`WS_POPUP` + `WS_EX_TOOLWINDOW` (a browser menu / dropdown / extension
popup), only the **Browser window (1)** zone is reported: the cursor is over
the popup, not over the browser chrome. `Classify()` returns early in that
case, so no chrome rule can fire.

**Verified (probe):** with the menu open — the close button and the tab
`[1]` (no false 4), the page outside the menu still `[3,1]`; menu closed —
close `[15,4,1]`, tab `[12,4,1]` ✅. Helper
`C8466CF7CE1AC40C3A56AAD175B0F545B914E670679B495C2199E469A483ABAF`.

⚠ **Testing note:** do NOT use `zone_fg_wheel.ps1`'s Alt foreground trick
when a stray Opera menu would confuse the measurement — close it with Esc
(`Test/ac_keys.ps1 -Combo esc`) and re-check the known-good point.

### (l) "Works, but sometimes stops" — the zone TABLE was written too late (2026-09-20)

**User report:** the zone-15 action worked, then stopped working after a while
of clicking/scrolling; hovering the close button (no click) and scrolling did
nothing.

**How it was traced.** The helper's own answer and the engine's TABLE were
checked side by side with `Test/_probe_tablecheck.ps1` (reads the cave at VA
`0x47F7A3` → the alive + table addresses → the 64-dword table, and verifies in
the same instant that the cursor is where the probe put it — the user's hand
otherwise moves the mouse and fakes a mismatch). Result: helper `[15,4,1]`,
table `[1 4 15]` — both correct, 8/8.

**Then the LATENCY was measured** (move the cursor, poll the table every 8 ms):
the table only changed after **~170 ms**. Cause: the helper's heartbeat polls
every 120 ms and writes the table only then.

**Why that breaks a wheel trigger** — the engine caches each region's verdict
(`FUN_00415bf0`, `Test/native-disasm/decomp/00415bf0_FUN_00415bf0.c`):

```c
invalidate = (DAT_0049fc4c != DAT_004a26b4)  &&  // a new input message
             (300 < counterDelta || |dx| > 3 || |dy| > 3)
```
and it recomputes a region only when the invalidation fired. So: move onto the
close button and scroll within the stale-table window → the engine reads
`table[15] == 0` → no 750 at all → the cache keeps that 0 for up to 300 ms →
**every following notch is skipped too**. After 300 ms the region is recomputed
with the fresh table and the action starts working again — exactly the
"works, but sometimes stops" symptom. (The engine also caches the CURSOR
POSITION for 200 ms in the precond evaluator, `FUN_00420050` case 0xd, which
widens the window.)

**Fix (helper):** the poll is 30 ms now, the classification runs the moment the
cursor SETTLES (position unchanged between two polls) and a continuous move is
throttled to 80 ms. Measured: write latency ~0 ms; CPU during a continuous drag
22.7% → 11.6% of one core. Helper
`C8466CF7CE1AC40C3A56AAD175B0F545B914E670679B495C2199E469A483ABAF`.

⚠ The engine-side cache remains (it is the original engine's logic) — the fix
only shrinks the window in which the table can be stale. If a report of a
missed first notch persists, the next step is a small engine patch: force the
`200 < counterDelta` position refresh in `FUN_00420050` to always run.

### (m) "Hovered tab" actions targeted the WRONG tab — the 485 query + the _kg cache (2026-09-20)

**User report (after the wheel benchmark):** "it sticks on the tabs where I
scrolled — it works on them, but on another tab it no longer reacts."

**Benchmark evidence** (`Test/_bench_watch.js`, the user's own hand on the
wheel — the engine DROPS synthetic input, see §4): 12 wheel notches over 4
different tabs produced 12 × `zones=[15,4,1] ∩ [15] → executing` and 11 page
loads — **10 of them on one and the same tab** (the active one). So the zone
gate was fine; the ACTION targeted the wrong tab.

**Cause 1 — the native 485 answer lost its tab identity.** `hoveredTabs` is
`{oper:"filter", params:{anyHvrd:true}}` (file59); the filter calls `_ys()`
(file50), which asks the NATIVE for the tab under the mouse:

```js
function _ys(){ if(_kg) return _kg; ... a=(yield _Vy(_No,a))||{};
  if("index" in a) c=yield _zg({windowId:b,index:a.index});
  else if("title" in a && ...) ...
```

`_No` = **485**. On Chrome 148+ the engine answers only `{hWnd,x,y}` — no
`index`, no `title` (its a11y hit-test no longer finds the tabs; documented in
`Docs/archive/AGENTS-pitfalls-history.md`). So `c` stayed empty, `_kg` became
`[]`, and file59's fallback took over:
`c = _ys(); if (!c.length) c = [activeTab]` → **the active tab**.

**Cause 2 — the resolved tab is cached.** `_kg` is only cleared by `_wd()`,
which runs when the TAB LIST changed (file37 `_Rf` → `_Fk`). Verified live:
the cursor was moved onto tab 2 while `_ys()` still returned tab 1's id.

**Fix (extension-side, no native patch):**
1. The zone helper reports the tab under the cursor — `TabIndexOf` counts the
   PAGETAB siblings to the left of the hovered one, `TabUnderCursorJson`
   returns `,"hWnd":N,"index":I,"title":"…"` for a request with `"tab":1`
   (helper `C8466CF7CE1AC40C3A56AAD175B0F545B914E670679B495C2199E469A483ABAF`).
2. `sw.js` wraps `window._Vy` (the bundle's callback-native bridge): type 485
   is answered from the helper instead of the engine (falling back to the
   native when the helper is down or the cursor is not over a tab).
3. `sw.js` `__acSetHoveredTab()` runs before EVERY dispatch
   (`doDispatch = () => __acSetHoveredTab().then(...)`): it resolves the index
   from the helper and sets the bundle's `_kg = [tabId]` (via `chrome.tabs.query`
   + `_Or[hWnd]` → windowId), so the action always sees the CURRENT tab.

**Verified live:** cursor over tab 1 → `_Vy(485)` = `{hWnd:21575720,index:1,…}`;
over tab 2 → `index:2`; the resolution chain sets `_kg=[1672866628]` and
`_ys()` returns it (before the fix it returned the stale tab 1).

⚠ **Testing gotcha found on the way:** `Test/_probe_mouse.ps1` did not call
`SetProcessDPIAware`, so on this 150% display `SetCursorPos(700,610)` placed
the cursor at the PHYSICAL (1050,915) — every probe silently measured another
spot (which looked like "a fresh helper misclassifies"). The probe is
DPI-aware now; the same rule as for the scanners (§2).

### (n) The "Event tab" target resolved to NOTHING — same root cause, no fallback (2026-09-20)

**User report:** "something does not work" — the trigger fired, the action
reported OK, and no tab was reloaded. In the settings UI the user then found the
red banner **"This feature is not supported in Opera"** on the *Hovered tab*
target and asked whether it explains the failure.

**The banner is a red herring.** `noSuprt` (file65) is a **browser-NAME check**,
not a capability test:

```js
noSuprt:` ${_9j._Jh.in("opera","vivaldi")?
  `<noSuprt>This feature is not supported in ${_9j._Jh.caplze()}</noSuprt>`: ""}`
```

It is prepended to every mouse-dependent UI text (`tse.hvr` = Hovered tab,
`tse` editor's `hvr` filter, `mseOvr` = Mouse over condition, `copyElemUrl`,
`openElemUrl`, `ombar`). It was written upstream when Opera/Vivaldi exposed no
usable a11y tree — with the zone helper most of those features DO work now, so
the banner is **outdated** for the tab-strip cases (a UI-text decision, see
"Open items" below).

**The real cause is the same one as (m), but on a different target.** The user's
action (trigger 12, region **15**, action `reloadTabs`) targets
**`eventTabs`** — the **Event tab** target, not Hovered tab:

```
_ek[12] = [{"sequence":[{"action":"reloadTabs","params":{"force":0}}],"targets":"eventTabs"}]
```

`_Mg` (file59) resolves it with **no fallback at all**:

```js
function _Mg(b,a){let d=[],c;
  if(a.favList) c=_Mo[a.favList]||[];
  else if(a.evtTabs) c=_Eh(_zw);                    // ← the engine's event tabs
  else if("menuSeltn"==a.tgtExpr) c=_3u(a.marked,a.hilited,a.hovered);
  else if(a.anyHvrd) c=_3u(!1,!1,!0), c.length||(c=_ys(), c.length||(c=[_ji(_cd,_Jg(),"activeTab","id")]));
  ...
  if(c) d=b.filter(f=>0<=c.indexOf(f)==!a.negate);   // ← `if(c)` is TRUE for []
  return[d]}
```

`_Eh(_zw)` (`_Cg(_zw).tabs`) is the tab list the ENGINE attached to the event —
empty for mouse events on Chrome 148+, exactly as in (m). And because `if(c)` is
truthy for an empty array, `d` becomes `[]` → the group is empty → the action
iterates over zero tabs and **does nothing, reporting success**.

Measured (cursor over tab 2's close button, `_zw` = 2):

```
[TEST] filter(evtTabs) in=[1672866590,1672866662,1672866587,1672866628] out=[[]] kg=null
```

⚠ Note `kg=null`: the pre-dispatch refresh of (m) had already run, but `_rf`
does `yield _Rf()` **first** in every action and `_Rf` → `_wd()` (tab list
changed) → `_kg = null`. So the cache refresh alone is undone by the action
itself.

**Fix (sw.js, `_pp.filter` patch + a SW-local tab):**
1. The tab under the cursor is remembered in **`__acHoveredTabId`** — a
   SW-local variable that the bundle's `_wd()` cannot clear.
2. The **filter TABLE** is patched, not `window._Mg`: file59's `_pp` captured
   the function object at load time, so wrapping the global is a no-op
   (verified — the wrapper never ran). Both entries (`filter`, `posFilter`)
   point at the same function and both are replaced:

```js
const __acFilter = function (b, a) {
  const r = __acOrigFilter(b, a);
  const empty = !r || !r.length || !r[0] || !r[0].length;
  if (!empty) return r;                     // the bundle resolved it → never touch
  if (!(a.evtTabs || a.anyHvrd)) return r;  // unrelated target → never touch
  const hv = (__acHoveredTabId != null) ? [__acHoveredTabId] : (_kg && _kg.length ? _kg : null);
  if (hv) { const hit = b.filter(id => hv.indexOf(id) !== -1); if (hit.length) return [hit]; }
  return r;
};
```

**Verified live** (cursor over tab 2's close button, active tab = index 1):

| call | result |
| --- | --- |
| `_pp.filter(ids, {evtTabs:true})` | `[[1672866587]]` (index 2 — under the cursor) |
| `_pp.filter(ids, {anyHvrd:true})` | `[[1672866587]]` |
| `_pp.filter(ids, {})` | all 4 ids (untouched) |
| full dispatch, cursor over close of idx 0 | `RELOAD id1672866590 idx0` (not the active idx 1) |
| full dispatch, cursor over close of idx 2 | `RELOAD id1672866587 idx2` |
| full dispatch, cursor over the PAGE | no reload (cursor not over a tab → original empty result) |

`_anyHvrd` is normally already correct because `_ys()` re-resolves through the
wrapped 485 (see (m)) — the patch is the safety net for the case where `_kg` was
wiped mid-action. `evtTabs` has no other path at all.

Pinned by `Test/mh_test.js` **B56** (runs the REAL patch source sliced out of
sw.js against a stub table: fallback works, an unknown hovered tab keeps the
original result, an unrelated target is never modified, a non-empty result is
never overridden, both table entries are patched, the guard flag is set).

⚠ For a mouse event the "event tab" IS the tab under the cursor — that is what
the engine supplied before Chrome 148 (and what the *Hovered tab* tooltip
documents: "A tab in the tab strip" → that tab; "any other part of the browser
window gives the active tab"). Over the page the target stays EMPTY (no reload),
which matches the old MV2 behavior for a wheel event that names no tab — and a
zone-scoped trigger never gets there anyway (the SW gate skips it, see (e)).

**Open items from this finding:**
- the `noSuprt` banner is now WRONG for the tab-strip cases — decide whether to
  drop it for `tse.hvr` / `hvr` / `mseOvr` (they work) and keep it only for
  `copyElemUrl` / `openElemUrl` / `ombar` (never verified in Opera);
- "Copy/Open hovered URL" in Opera is still untested (needs the engine's
  element tracking, not the zone helper).

### (o) Round 2 — "the PREVIOUS tab reloads" and "the first notch is ignored" (2026-09-21)

**User report (after (m)/(n) were deployed):** "on a fast cursor move across the
tabs the PREVIOUS tab reloads" and, on a second run, "if I move across the tabs
and wheel at once, sometimes the first notch does nothing — but a FOREIGN tab is
no longer reloaded". Both reproduced in Chrome Canary 156 (not Opera-specific).

**Diagnosis — the CDP log (`Test/_probe_raceinstall.js` + `_probe_racedump.js`,
see the tool notes in `Test/README.md`).** Three independent causes:

**1. `_ys()` returns the bundle's own stale cache.** `_ys()` (file50) is THE
resolution point for "the tab under the cursor" — the `Hovered tab` target
(`_Mg` → `anyHvrd` → `_ys()`) and the `hovered` tab-filter property both call it.
It returns `_kg` when set, and `_kg` is dropped ONLY by `_wd()` (a tab-list
change), so it routinely holds the tab of the PREVIOUS wheel. The `_pp.filter`
patch of (n) could not help: it only acts on an EMPTY result, and `anyHvrd` has
a non-empty fallback (`c=_ys()`, then `[activeTab]`).
Fix: `sw.js` wraps **`_ys` itself** — when `__acHoveredTabId` (the helper's
answer) is known it returns `[__acHoveredTabId]` and does NOT call the original.
Skipping the original also removes a redundant accessibility walk (below).

**2. The helper served a tab computed for ANOTHER point.**
```csharp
private static void CacheStore(POINT pt, string body) { CacheStore(pt, body, null); }
...
  if (tabBody != null) cacheTabBody = tabBody;   // null KEEPS the previous tab
  cachePt = pt;                                   // but the point is already new
```
The SW asks for the ZONE SET on every wheel; when the cursor has moved, that is
a fresh classification → `CacheStore(pt, body)` updates the cached point while
the cached TAB still belongs to the previous point. The tab request that follows
matches the point and gets the OLD tab. The log shows it literally:
```
156637  res  id566 z=15 [15,4,1]      ← fresh zone classification (+21 ms)
156637  req  id567  TAB-REQ
156637  res  id567 ... TAB idx=14     ← answered in 0 ms = cache = PREVIOUS tab
156637  reload  tabId=61304457        ← the previous tab reloaded
```
That is also why the SLOW test always worked: while the cursor rests, the
background heartbeat stores the CORRECT tab and the request hits it.
Fix: `cacheTabOk` — a tab is valid only for the point it was computed WITH; the
zone-only store clears it. The request path now samples the cursor ONCE and uses
that single sample for both answers (zones + tab).

**3. The zone query timed out → the first notch was skipped.** Adding the tab
walk to `ClassifyAndCache` (which runs on the helper's 30 ms heartbeat) cost
60-104 ms per heartbeat and made the helper unable to answer the SW's zone query
in time: the answer came back as the timeout marker and the gate skipped the
trigger:
```
[AC-MV3-ZONE] trig 12: zones=[-2] ∉ [15] → skipped
```
Fix: the walk is OUT of the heartbeat (the tab is walked on demand, cached for
its own point), and the SW's zone query waits **500 ms** instead of 250 ms — a
fresh accessibility walk can take 100-300 ms while Chrome's window tree is
waking, and an action that runs a few hundred ms late beats an action that never
runs (the engine has already applied the same region decision on its side).

**4. Two walks per event.** Each wheel produced TWO tab requests (`TAB-REQ`
twice in the log) — one from `__acSetHoveredTab` and one from the bundle's own
`_ys()` → `_Vy(485)` → the `_Vy` wrapper → the helper. The helper is
single-threaded, so the walks QUEUED and the answers arrived 180-360 ms late
(the log: the second answer 344 ms after the first). Fix: the wrapped `_ys` no
longer calls the original when it has an answer (see 1) — measured after the
change: **one** tab request per event.

**Verified (Canary 156, helper `C8466CF7CE1AC40C3A56AAD175B0F545B914E670679B495C2199E469A483ABAF`):**
`_ys()` returns the helper's tab even with a deliberately poisoned `_kg`
(`_ys() -> [61304275]` while `_kg=[61304272]`); the log shows
`_ys ret=[61304458] kg=[61304464]` (stale cache overridden) and the reload always
targets the helper's tab; one tab request per event instead of two.
`mh_test` 105 pass / 0 FAIL (the pin now requires `__acYsWrapped` + `_ys = function`).

**User verdict (2026-09-21):** "not perfect, but good enough for real use — it is
hard to hit the situation where the action does not fire."

**Remaining imperfection (known, accepted):** during a continuous fast move the
tab identity can lag by one accessibility walk (~60-340 ms under load), so a
notch can still act on the tab the cursor was over a moment earlier. The next
cheap step, if it ever matters: let the zone gate and the tab refresh share ONE
helper request (the helper's answer already carries both the zone set and the
tab — the SW currently sends two messages).

### (p) Opera 135: the close button (15) moved one level DEEPER (FIXED 2026-09-21)

**Found while setting up the Opera test of the hovered-tab fix** — and it explains
why a zone-15 trigger was unreliable there.

In this Opera window (6 tabs, Chromium 151) hovering a tab's close button answers
**"Title area" (4)** instead of **15**, so the SW gate SKIPS the trigger
(`zones=[4,1] ∉ [15] → skipped`). `msaa_chain.ps1 -Point "390,30"` showed why:

```
d0 role=43 'Close tab' [380,21 25x24] cc=0
d1 role=16 ''          [158,12 253x42] cc=6      ← the tab's body PANE
d2 role=37 'badssl.com'[158,12 253x42] cc=3      ← the PAGETAB
d3 role=60 'Tab bar'   …
```

The close button IS a real `43` (so the 2026-09-20 "Opera exposes it as a PANE"
workaround is not the whole story), but it is nested **one level deeper** than in
Chrome: `PAGETAB(37) → body PANE(16) → button(43)`. Neither rule matched:

* `isTabBtn = roles[0] == 43 && roles[1] == 37` — the parent is the PANE, not the
  PAGETAB;
* `IsPaneCloseButton(chain[0], chain[1], pt)` — that rule expects the hovered
  element to BE a square PANE, but the hovered element is the 43 button.

**Fix (helper `C8466CF7CE1AC40C3A56AAD175B0F545B914E670679B495C2199E469A483ABAF`, 22528 bytes):**
1. the tab-button rule now accepts a PAGETAB at ANY depth within d0..d3
   (`isTabBtn = ui && roles[0] == 43 && tabDepth >= 1`) and calls
   `TabButtonZone(chain[tabDepth], …)`. It still cannot catch the "+" (a 43 under
   the PAGETABLIST 60, no PAGETAB above).
2. `TabButtonZone` scans the tab's children **two levels deep**
   (`ScanTabButtons`), so a button nested in the tab's body PANE is found; the
   classification stays by SIBLING ORDER (rightmost = close, other = speaker),
   which is what keeps the Chrome speaker/favicon logic correct.

The `IsPaneCloseButton` path stays (it covers the builds that expose the close as
a PANE, e.g. the earlier Opera window where `[15,4,1]` was verified).

**Verified (Opera 135, Chromium 151):** close `(390,30)` → `{"zone":15,"zones":[15,4,1]}`,
tab body `(300,30)` → `[12,4,1]`, second tab `(600,30)` → `[12,4,1]`; Canary unchanged.

**End-to-end verified with PHYSICAL input (2026-09-23, the user's own hand — the engine
drops synthetic input, §4).** Five consecutive wheels over the close buttons of tabs
3 → 4 → 5 → 2 → 3, captured by the runtime probe (`_probe_raceinstall.js` +
`_probe_racedump.js` + `_probe_hold.js`, held CDP session so the SW was not evicted):

```
428833  res  id319 z=15 [15,4,1]  TAB idx=3 "Rammstein - Full Concert ["
428834  _ys  ret=[1672867188] kg=null      ← the helper's tab, no stale cache
428834  reload  tabId=1672867188           ← idx 3 ✔
429000  loading idx=3 …
430188  res  id321 z=15 [15,4,1]  TAB idx=4 … reload 1672867189   ✔
431393  res  id323 z=15 [15,4,1]  TAB idx=5 … reload 1672867190   ✔
432975  res  id326 z=15 [15,4,1]  TAB idx=2 … reload 1672867187   ✔
434427  res  id328 z=15 [15,4,1]  TAB idx=3 … reload 1672867188   ✔
```

Every wheel reloaded EXACTLY the tab under the cursor, `_ys` always returned the
helper's tab (`ret=` equals `sw=`) with `kg=null`, and there is only ONE `TAB-REQ`
per event — the duplicate accessibility walk of §2f(o) is gone. The zone-15 trigger
fires in Opera on the first notch.

**Chrome regression check (2026-09-23) — the generalization does NOT change Chrome.**
Two independent proofs:

1. **The code path is the same one.** In Chrome the close button is a DIRECT child
   of the PAGETAB (`PAGETAB(37) → [43 'Mute tab', 43 'Close']`, from
   `zone_scan.ps1`), so `roles[0] == 43 && roles[1] == 37` → `tabDepth = 1` →
   `TabButtonZone(chain[1])` — byte-for-byte the call the OLD rule made. The new
   2-level scan finds nothing extra there because Chrome's tab buttons have no
   children (`cc=0`), exactly like the Opera ones.
2. **Measured: 30 points, 0 differences.** The OLD helper
   (`ac_zone_helper.exe.bak-B338B6E7`, the build from before the round-2 work) and
   the NEW one were run over the SAME points in Canary and their answers compared:
   * 18 points along the tab strip (pinned tabs, regular tab bodies, TWO different
     close buttons at x=1300 and x=2000, the strip row, the empty area right of the
     last tab) — `[12,4,1]` / `[15,4,1]` / `[4,1]`, **all identical**;
   * 12 points down a vertical line (tab strip → toolbar → omnibox → page) —
     `[12,4,1]` → `[1]` → `[20,1]` → `[21,20,1]` → `[3,1]`, **all identical**.

   Tool: `Test/_probe_zonegrid.js` (walks a grid with the DPI-aware cursor move and
   asks the browser-spawned helper through the SW); for an A/B comparison against
   another build, move the cursor with `_probe_mouse.ps1` and run
   `node Test/zone_helper_smoke.js <helper.exe>` per build.

⚠ **Probe gotcha found on the way:** `zone_probe.ps1` spawns the helper itself
(`zone_helper_smoke.js`), so its "own browser window" gate is INERT — with another
application in the foreground (Telegram, `Qt51519QWindowIcon`) every point answered
`{"zone":1,"zones":[1]}` instead of `0`. Use the browser-spawned helper through
the SW for a real answer: `node Test/cdp_eval.js 9224 "__acTest.zoneAsk(1000)" --await`
(returns `[0]` when the cursor is not over that browser).rsor is not over that browser).

### (q) Chrome 148: the tab index was ALWAYS 0, and the answer came too late (FIXED 2026-10-04)

**User report:** "in Chrome 148 the action reloads the FIRST tab instead of the
hovered one" (2026-09-23), then after the round-2 work: "it works, but not always
— sometimes the ACTIVE tab is reloaded and I cannot tell when".

**Cause 1 — `TabIndexOf` counted the wrong level.** The helper located the tab
strip as *the first role-60 ancestor* and counted ITS direct children:

```
PAGETAB(37) 'hluk/CopyQ…'      ← the hovered tab
PANE(16) cc=48                 ← ALL tabs live here
PANE(16) cc=2
PAGETABLIST(60) cc=5           ← the old rule stopped HERE and counted 0 tabs
```

Chrome 148 wraps the tabs one level deeper than Canary/Opera, so the count found
no PAGETAB children and **every** tab answered `index:0`. Measured over the strip
(8 points): **every title correct, every index 0**:

```
  150  …"index":0,"title":"hluk/CopyQ…"          ← 8 different tabs,
  500  …"index":0,"title":"Non Est Deus…"        ← the same index 0
 2400  …"index":0,"title":"0x192/universal…"
```

The SW then took `list[0]` — the FIRST tab of the window. **Fix:** the strip is
now *the level where the tabs really ARE siblings* (an ancestor with ≥ 2 PAGETAB
children), with the role-60 ancestor kept as the fallback for a single-tab window;
and the counting is done in ONE pass (the old code walked the children twice).

**Cause 2 — the answer arrived after the SW gave up.** Even with the index fixed,
a burst of wheels reloaded the ACTIVE tab. The SW→helper note channel (below)
showed the answer and the timeout in the SAME millisecond:

```
22:36:55.838 tab ask 2541,20 -> …,"index":15,"title":"Трекер"   ← the helper answered
22:36:55.839 SW hover FAIL answer=null                          ← the SW had given up
22:36:55.839 SW RELOAD tab=988342169                            ← the ACTIVE tab
```

Two MSAA walks competed for the same tree — the heartbeat's zone classification
(every 30 ms while the cursor moves) and the request's tab walk — and the walk
itself cost ~300 ms because `TabIndexOf` walked the children twice.
**Fix:** (a) `servingRequest` — the heartbeat skips its classification while a
request is being served; (b) the single-pass walk; (c) the SW waits **900 ms**
instead of 300 ms for the tab answer (an action that runs a few hundred ms late
beats an action that hits the wrong tab).

**Result (measured, all browsers):** `hover FAIL` 16 → **1**; `ys FALLBACK` → **2**;
walk time **min 79 / median 125 / max 219 ms** (was ~300); and the chain now
agrees end to end:

```
SW hover hWnd=527974158 idx=4 win=1344229309 list=8 -> tab=1344229314@4
SW ys    hWnd=527974158 -> [1344229314]
SW RELOAD hWnd=527974158 tab=1344229314 idx=4
```

**User verdict (2026-10-04):** "everywhere seems fine".

**Method notes (both are reusable and were ESSENTIAL here):**
1. **The action target can be read from the profile on disk.** Chrome 148 must not
   be relaunched with a debug port, but its `Local Extension Settings\<ext-id>\
   000003.log` (LevelDB) holds every write of `trigActList` — read it with
   `[IO.File]::Open(..., FileShare::ReadWrite)` (Chrome keeps it locked). Walking
   the writes showed the whole history of trigger 12:
   `reload → hoveredTabs` (writes 9-29), `reloadTabs → hoveredTabs` (30-41),
   **`reloadTabs → currentTab` (42-44, current)** — i.e. part of "it reloads the
   active tab" was simply the *Current tab* target, not a bug. **Always check the
   configured target before hunting the code.**
2. **A SW→helper note channel replaces CDP in a browser without a debug port.**
   The SW cannot be inspected there, but the helper CAN (it appends to
   `%TEMP%\ac_zone_helper.log`). The SW posts `{__id, note:"…"}` on the helper
   port; the helper writes the text into its log. That is how the timeout race
   above was found. The channel was REMOVED from `mv3-build/sw.js` after the fix
   (the shipped folder stays clean) — re-add it the same way when needed.

### (r) Switching tabs with a wheel became DELAYED — the refresh ran for everyone (FIXED 2026-10-05)

**User report:** "switching tabs by turning the wheel over the tabs is delayed,
while Alt+wheel anywhere is instant — is it because of the increased timeout?"

**Partly — but the timeout was not the main cost.** The Alt action is in
`__acZoneFree` (a combo without a mouse-over condition), so it skips BOTH helper
round trips; that is why it stayed instant and why it pointed at the helper.

Every dispatch ran `__acSetHoveredTab()` — an accessibility walk (79-219 ms
measured) whenever the cursor sits on a point the helper has not classified yet,
which is exactly the case right after moving onto another tab. And it ran for
**every** action, including the tab switches (`switchLeft`/`switchRight`), whose
target is `currentTab` and which therefore never asks for the tab under the
cursor. So the wheel paid ~80-220 ms for nothing.

**Fix 1 (sw.js):** `__acBuildZoneMap` now also computes **`__acHoverNeeded`** —
the triggers whose actions can ask for the hovered tab (`targets` matching
`/hovered/i` or `eventTabs`). Dispatch:

```js
const needHover = !__acHoverNeededReady || __acHoverNeeded[zid] === true;
const doDispatch = () => (needHover ? __acSetHoveredTab() : Promise.resolve()).then(…)
```

Before the map is built the refresh runs unconditionally (the safe old
behaviour), and if a target is ever missed the `_ys` wrapper still falls back to
the bundle's own resolution — so correctness never depends on the list being
complete, only the speed does.

**Fix 2 (helper):** the tab cache is warmed in the background again
(`lastTabWarmAt`, at most every 150 ms) so a hovered-tab request answers in ~1 ms
instead of paying a fresh walk. Guards — the round-2 failure was a walk on EVERY
heartbeat classification, which starved the zone query (60-104 ms answers,
`zones=[-2]` timeouts):

* only while the cursor has **SETTLED** (never during a fast pass);
* only over a tab-related zone (12 / 15 / 17) — the only place the tab can be asked for;
* **never** while a request is being served (`servingRequest`);
* throttled to 150 ms.

**Verified:** `mh_test` — the zone-map test asserts `__acHoverNeeded` for four
real cases (`currentTab` → no, `hoveredTabs` → yes, `eventTabs` → yes,
`disabled` → no) and the gate test asserts that NO dispatch pays for the refresh
when the map says it is not needed (both eval the REAL sw.js source). Helper
`C8466CF7CE1AC40C3A56AAD175B0F545B914E670679B495C2199E469A483ABAF` (22528 bytes),
`build_native.ps1` reproduces both components bit-for-bit.

⚠ **The first version of the check was wrong and the test caught it:** the
condition matched `hvrd` (the bundle's own field name for the filter), while the
STORAGE value is `hoveredTabs`. Do not "simplify" it back — `Docs/GOTCHAS.md` has
the same warning.

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
is the frame ABOVE the strip); the kebab is exposed in the a11y tree (the
earlier "missing" report was made on an outdated Chrome 150 and could not
be re-checked then); "else → 1 or 0" became "1 ALWAYS plus the specific zones" (the
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
⚠ **Still open (minor, moved out 2026-10-05):** the individual item kinds 41-51
were NOT each verified — they share the same route and are expected to work, but
per-kind accuracy (does "Menu item: tab" fire on the right item?) is unproven.
LOW PRIORITY: tracked in `Docs/TODO-menu-items.md`, verify on a user report.

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
   → it copies `AutoControl_native/patched/`, SHA-256 `1A10EDD191B80A806DF66558B2B1E78BE8D6AD81E93EEAC772D13F222E212C3E`), config
   sent (`_Gf` via cdp_eval, verify `type 60`
   in the boot log — the config-60 gotcha with the exact command is in
   `Docs/GOTCHAS.md` § Triggers & actions). ⚠ A browser restart re-imports
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
| `AutoControl_native/ac_zone_helper.exe` | repo copy of the helper binary | ✅ `C8466CF7CE1AC40C3A56AAD175B0F545B914E670679B495C2199E469A483ABAF` (deterministic Roslyn build, 2026-09-20) |
| `%LOCALAPPDATA%\AutoControl\ac_zone_helper.exe` | **the deployed binary Chrome runs** | ✅ same hash (Chrome picks it up without an extension reload) |
| `AutoControl_native/patches/patch_zones_v19.js` | engine patch builder (zone table) | ✅ **CURRENT** — see `patches/README.md` |
| `AutoControl_native/patched/AutoCtrl_2025.4.22.0.v19.exe` | repo copy of the built engine | ✅ `1A10EDD191B80A806DF66558B2B1E78BE8D6AD81E93EEAC772D13F222E212C3E` |
| `%LOCALAPPDATA%\AutoControl\AutoCtrl_2025.4.22.0.exe` | **the deployed engine** | ✅ v19 (`1A10EDD191B80A806DF66558B2B1E78BE8D6AD81E93EEAC772D13F222E212C3E`) |
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
| `Docs/GOTCHAS.md` (zone + native bullets) | gotchas: DPI, load path, signatures, dead mouse hook, proof chain | ✅ updated |
| `README.md` §4.3 / §4.4 | user/dev install guide (helper + patched engine) | ✅ updated |

---

## 6. Helper failure recovery — moved to `Docs/TODO-helper-autoheal.md`

Auto-heal for a HUNG `ac_zone_helper.exe` (consecutive-timeout respawn with
PID tracking + Emergency Repair doc note). Deferred by the user 2026-09-12.

---

## 7. How to check the fork quirks (2026-09-15)

Quick checks for the two known quirks (§ Known limitations). All read-only
(no cursor movement): `Test/msaa_chain.ps1` and `Test/zone_probe.ps1` are
safe to run at any time; the wheel tests need a browser window + a helper.

**A. Opera — new-tab "+" reports as the Browser tab (12) instead of 16**

```powershell
# 1. chain: the "+" must be role 43 whose parent is 22 'Tab Bar' (NOT 60)
powershell -ExecutionPolicy Bypass -File Test\msaa_chain.ps1 -Point "<x-of-plus>,<y-tabstrip>" -Depth 3 -Kids 0
#    expected: d0=43 'New Tab' -> d1=22 'Tab Bar' (or 20) -> d2=22 'Tabs'
# 2. helper verdict on the same point
powershell -ExecutionPolicy Bypass -File Test\zone_probe.ps1 -Points "plus,<x>,<y>"
#    expected: {zones:[12,4,1]}  (the bug: 16 is absent)
```

**B. Vivaldi — "Workspaces" button reports as the Omnibox (21) instead of
nothing/menu**

```powershell
# 1. chain: the leftmost button must be role 57 with a name that does NOT
#    contain "menu" (or a localized variant)
powershell -ExecutionPolicy Bypass -File Test\msaa_chain.ps1 -Point "<x-of-workspaces>,<y-tabstrip>" -Depth 3 -Kids 0
#    expected: d0=57 'Workspaces' -> d1=20 ...
# 2. helper verdict
powershell -ExecutionPolicy Bypass -File Test\zone_probe.ps1 -Points "ws,<x>,<y>"
#    expected: {zones:[21,1]}  (the bug: 21 is present although it is not the omnibox)
```

**C. Sanity: the same checks on Chrome (should NOT reproduce)**

```powershell
powershell -ExecutionPolicy Bypass -File Test\msaa_chain.ps1 -Point "300,31" -Depth 3 -Kids 0    # Chrome SxS tab strip
powershell -ExecutionPolicy Bypass -File Test\zone_probe.ps1 -Points "tab,300,31;addr,700,94"
#    expected: tab -> [12,4,1], omnibox -> [21,20,4,1]
```

The exact points depend on the window position — read them from
`Test/window_at_point.ps1` first (the browser window rect).

**D. Per-browser end-to-end (the real test)**

One browser at a time, physical mouse (the engine ignores synthesized
input for its hover cache — see §4). For each browser:

1. **Register the native hosts** for that browser (only Chrome/Canary/Brave
   are covered by the Chrome registration; Opera/Vivaldi need their own
   `reg add` — README §4.1 step 6), then load the extension from the same
   `mv3-build\` folder (unpacked; the ID must match `allowed_origins`).
2. **Start the browser** (Vivaldi additionally with
   `--force-renderer-accessibility`), open two tabs, play sound in one.
3. **Verify the helper is live**: `node Test/zone_helper_smoke.js` → prints
   `zone` + `zones`; `%TEMP%\ac_zone_helper.log` shows
   `init for pid N of my browser M (engines: K)`.
4. **For each zone under test**: put the cursor over the element, scroll the
   wheel 2-3 notches, read the SW log with
   `node Test/ac_swlog_act.js 9223 "<command>"` and expect
   `[AC-MV3-ZONE] trig N: zones=[…] ∩ [<region>] → executing`; over a
   wrong element expect `→ skipped` and normal page scroll.
5. **Record the result** in the compatibility matrix (README §5a) — for
   Opera/Vivaldi the expected values are: page/omnibox/toolbar/title/tab
   OK; close button + speaker missing; Opera "+" → 12 (quirk A); Vivaldi
   "Workspaces" → 21 (quirk B).
6. **Close the browser** before switching to the next one (each browser runs
   its own engine + helper; running several at once is a separate test — §2c).

The browser matrix to verify: Chrome (reference), Brave (should be 11/11),
Opera (8/11 + quirk A), Vivaldi (7/11 + quirk B).

