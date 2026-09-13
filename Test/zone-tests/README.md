# Browser zone recognition — test methodology

**Created:** 2026-09-01 · **Status:** methodology (testing pending)
**Goal:** verify that every Chrome browser zone (mouseOver region) is
recognized SEPARATELY — a trigger conditioned on zone N must fire ONLY when
the cursor is over zone N, and must NOT fire over the page or a neighboring
zone.

**Verdict legend:** ⬜ not tested | ✅ works | ❌ broken | ⚠️ partial

---

## 1. Environment & prerequisites (before EVERY test session)

1. **Engine build**: the DEPLOYED engine since 2026-09-12 is **v19**
   (`AutoControl_native/patches/patch_zones_v19.js`, sha `1A10EDD1…`) — built
   from `AutoControl_native/original/AutoCtrl_2025.4.22.0.exe` (untouched
   upstream), so it carries the zone-table
   cave but **NOT** the accName patch (the older v4 build did; the helper
   queries `get_accName` itself now, which keeps Chrome's a11y tree awake).
   The type-792 diagnostics below therefore need the `patch_accname.js` build.
   **Bit-for-bit rebuild of both native parts → `Docs/BUILD-NATIVE.md`**
   (one command: `powershell -File Test/build_native.ps1`;
   `-UpdatePatched` also refreshes `AutoControl_native/patched/`).
   - the old v4 accName builds (`da8c03d8…` diag-ON, `53b42096…` diag-off)
     used to live in the repo as `…patched-v4*` — **deleted 2026-09-12** (the
     binaries are gone). Rebuild one with `node Test/patch_accname.js
     --diag-on` into a scratch folder if you really need the 792 diagnostics;
     NOTE it does NOT contain the v19 zone-table cave, so zones fall back to
     v18 behaviour (helper-down) while you run it. For zone work use the v19
     build above.
   - original pristine: `AutoControl_native/original/` = `8ae9a669…`.
2. **Chrome SxS with CDP** (the only supported test browser):
   ```powershell
   Start-Process "$env:LOCALAPPDATA\Google\Chrome SxS\Application\chrome.exe" `
     -ArgumentList '--remote-debugging-port=9223', `
     "--user-data-dir=`"$env:LOCALAPPDATA\Google\Chrome SxS\User Data CDP`"", `
     '--lang=en-US'
   ```
   Verify: `curl.exe -s -m 5 http://127.0.0.1:9223/json/version`.
3. **Engine alive:** `node Test/cdp_native_check.js 9223` → `"pong"`.
4. **MSAA tree ON** (required for zones 12/15/16/17):
   `powershell -File Test\_ac_msaa_probe.ps1` → over the page must be
   `role=15` (DOCUMENT), NOT `role=16` (PANE). If PANE → the tree is off:
   check the engine hash / restart; if still off, log it — the zones will
   fail-open or fail-closed and results are INVALID.
5. **Window rect** — always measure: `powershell -File Test\_ac_win_sxs.ps1`
   (typically `(55,0)-(654,1420)`; do NOT reuse coordinates from another run).
6. **Foreground** must be the SxS window
   (`powershell -File Test\_ac_fgcheck.ps1`).

## 2. Test trigger setup (per zone)

Reuse trigger id `12` ("right-btn => pin tab" → `pinTabs` toggle on
`hoveredTabs`) — its pin toggling is the visible action marker:

```js
chrome.storage.local.get('trigActList').then(a=>{
  const l=a.trigActList||[];
  const t=l.find(x=>x[0]==='12');
  t[1].triggers[0].preconds.mouseOver[0].region=<N>;
  return chrome.storage.local.set({trigActList:l})})
```
via `node Test/cdp_eval.js 9223 '<expr>' --await`, then **wait 3.5s** for the
config chain (type 60 reaches the native).

Arm the 750 counter (SW):
```js
window.__ctr={n:0,ids:[]};
const o=self.__acDispatch;
self.__acDispatch=function(m){if(m&&m.nativeType===750){window.__ctr.n++;
  window.__ctr.ids.push(m.data&&m.data.id)}return o(m)}
```

## 3. Click protocol (per point)

```powershell
node Test/cdp_eval.js 9223 "chrome.tabs.update(<sxsTabId>,{pinned:false}).then(()=>'r')" --await   # reset marker
Start-Sleep -Milliseconds 600
powershell -ExecutionPolicy Bypass -File "Test\_ac_mouse.ps1" -Action move -X <X> -Y <Y>
Start-Sleep -Milliseconds 2500     # ⚠ region cache: ≥2s between move and click
powershell -ExecutionPolicy Bypass -File "Test\_ac_mouse.ps1" -Action rmb -HoldMs 120
Start-Sleep -Milliseconds 1200
node Test/cdp_eval.js 9223 'window.__ctr'    # n>0 = fired
node Test/cdp_eval.js 9223 'chrome.tabs.get(<sxsTabId>).then(t=>t.pinned)' --await  # visible marker
```

**Automated scanner** (batch):
`node Test/zone-tests/zone_scan.js <region> x1,y1 x2,y2 …` (points) or
`node Test/zone-tests/zone_scan.js <region> grid x1,y1 x2,y2 step` (rect grid)
prints `FIRED/no` per point. Always confirm a FIRED point's pin change.

### ⚠ Interpreting results — the fail-open trap

A zone that the engine maps to the WHOLE window (like region 4) fires over
its own area TOO — a single-point test looks "working". This is why the scan
must cover the window grid (tab row + second row + a few PAGE points):

| Pattern | Meaning | Verdict |
|---|---|---|
| fires ONLY in its own area; blocked over page & neighbors | correctly recognized | ✅ |
| fires over its area AND over the page / everywhere | fail-open — "acts like the whole window" | ❌ |
| never fires anywhere | fail-closed | ❌ |

**Default scan sets per zone:**
- tab-row zones (12/15/16/17): `grid 60,20 640,70 25` + page controls
  `300,600` and `300,900`;
- second-row zones (20/21/33/30): `grid 60,70 640,130 25` + page controls;
- always include the page points — they are the fail-open detector.

## 4. Zone table (regions → what to test)

| # | Zone | Region | Where the point is | Expected |
|---|---|---|---|---|
| 1 | Browser tab (each tab in the strip) | 12 | middle of tab 1, tab 2, … (y ≈ tab strip) | fires over ANY tab; NOT over page/omnibox |
| 2 | Tab's close button | 15 | right edge of a tab | fires ONLY on the × area |
| 3 | Tab's speaker icon | 17 | left part of a PLAYING tab | fires only over the icon |
| 4 | New tab button | 16 | the "+" right of the last tab | fires only there |
| 5 | Toolbar (extension buttons) | 20 | right of the omnibox, left of the menu | fires only there |
| 6 | Omnibox | 21 | the address bar area | fires only there |
| 7 | Bookmark button (star) | 33 | star at the right end of the omnibox | fires only there |
| 8 | Browser menu button (⋮) | 30 | far top-right | fires only there |
| — | Web page (negative zone) | 3 | page body | reference: works (page ✓ / strip ✗) |
| — | Title area (known broken) | 4 | window top | reference: ❌ fires everywhere |

**Negative controls for EVERY zone:**
- cursor over the **page** (e.g. 300,600) → must NOT fire;
- cursor over a **neighboring zone** (e.g. zone 1 → zone 4; zone 8 → zone 5)
  → must NOT fire.

**"Recognition of individual tabs" (zone 1):** check tab 1, tab 2, … each
fires; the region is the same (12), so per-tab *distinction* is not expected —
only that the whole strip is recognized and nothing else is.

## 5. Determining zone coordinates

Window coordinates depend on the tab count and window width; locate them per
run. **Do not trust a single point — always scan the GRID** (see §3):
1. **Tab row** (y ≈ 20..70): `zone_scan.js 12 grid 60,20 640,70 25` — FIRED
   band = the tab strip; the gaps = close buttons / new-tab / right side;
2. **Close button** (15): the grid already covers it (right edge of tabs);
   refine with a fine scan over the active tab's right ~20px;
3. **Speaker icon** (17): open an AUDIO tab (e.g. youtube), then
   `zone_scan.js 17 grid <tab-x0>,20 <tab-x1>,70 5`;
4. **New tab** (16): the grid shows the "+" (right of the last tab);
5. **Second row** (20/21/33/30): `zone_scan.js <N> grid 60,70 640,130 25`.
A screenshot may help: CDP `Page.captureScreenshot` → view in an editor.

## 6. Results journal

| Date | Zone | Over zone | Over page | Over neighbor | Verdict | Notes |
|---|---|---|---|---|---|---|
| 2026-09-01 | 12 Browser tab (ad-hoc, patched engine) | ✅ | ✅ blocked | — | ✅ | wheel + RMB both |
| 2026-09-01 | 3 Web page (reference) | ✅ | — | ✅ blocked (strip) | ✅ | |
| 2026-09-01 | 4 Title area (reference) | fires | fires | — | ❌ known | engine maps it to whole window |
|  |  |  |  |  |  |  |

## 7. Known gotchas (read before testing)

- **Region cache:** the engine caches the hovered element/region — wait
  ≥2 s between `SetCursorPos` and the click, or results flake.
- **The UI no longer marks any zone as broken** — the "⚠ broken in Chrome
  148+" labels were removed 2026-09-13 (`mv3-build/file68.js`); the zones work
  with the PATCHED engine + the helper. They do depend on Chrome's MSAA tree:
  with the tree OFF every point answers as an unnamed PANE (zone 4), so the
  helper's answer is INVALID — do not record such runs (the helper's heartbeat
  keeps the tree awake while it lives).
- **Zone 4 (Title area)** IS implemented (the whole top band: caption + tabs +
  omnibox + toolbar, page excluded) and verified live — the old "the engine maps
  it to the whole window" note described the UNPATCHED engine, which is no
  longer used for zone work.
- **RMB strip interaction:** the pinTabs marker toggles pin; a FIRED click
  changes `pinned` — always reset before the next point.
- The native sends 2-3×750 per click (companion ids) — count n>0, not n==1.

## 8. Diagnostics toggle — type 792 (no-click zone probe)

The patched engine can report the MSAA role under the cursor as native
message **type 792** (`{type:792, content:<role>}`); the SW exposes the
last value as `window.__acZone` (read via `node Test/cdp_eval.js 9223
'window.__acZone'`). This probes the zone WITHOUT clicking — move the
cursor (`Test/_ac_mouse.ps1 -Action move`) and read the role.

- **Gated by a 1-byte toggle** in the engine's `.acp` section: VA
  `0x4b5000`, file offset `0xaac00` (the patcher prints both on every
  build). `0` = silent (default), `1` = emit.
- Build: `node Test/patch_accname.js --diag-on` / `--diag-off` (default
  off) — or flip the single byte with a hex editor. The `get_accName`
  call (the actual tree fix) is NOT gated and always runs.
- Repo artifacts: the `patched-v4*` engine builds were **deleted 2026-09-12**;
  rebuild one with `node Test/patch_accname.js --diag-on` (or `--diag-off`).
  Deploy any build with `Test\deploy_patched_engine.ps1 -Source <exe> -Force`.
- A vanilla (unpatched) engine never sends 792; the SW handler is a
  no-op without it.
- Hashes: `--diag-off` = `53b42096…`, `--diag-on` = `da8c03d8…`.

**⚠ WARNING (2026-08-31, live-verified): never run zone tests with the
diag-ON build** — the 792 send inside the hover path breaks the zone
classification itself (no 750 fires from any mouseOver-gated trigger; the
user's real omnibox-zone event died with diag-ON deployed and came back
immediately after rolling to diag-off). Use the diag-OFF build for all
zone work; the 792 probe is only usable to confirm the engine sends roles
in an isolated setup (zones dead while it is on).

---

## 10. Zone-12 tab-strip session results (2026-09-01/02) — see RE doc §10

**Verdict: zone 12 (tab strip) ⬜ NOT achievable on Chrome 150 SxS via the
engine's MSAA classifier.** The engine's hover cache never refreshes over
the tab strip (tracks the page HWND only) — a role probe (792) from
FUN_0040b610 got NOTHING over the tabs. PowerShell probes see 41/37, but
that is a different MSAA client; the engine's own path never gets a tab
element, so role-based selectivity is impossible.

**Current deployed engine: v18** (`F96BF544…`, built by
`Test/patch_zones_v18.js`) — v16 zone-12 semantics PLUS a code-cave
trampoline at `FUN_004156f0` entry making EVERY region below 60 match, so
the engine DELIVERS the 750 for the close button / "+" / speaker / menu
button instead of silently dropping it (with v16 those triggers never
reached the SW gate). Regions ≥ 60 (the AutoControl menu items) keep the
engine's own classification. Selectivity lives 100% in the SW gate +
`ac_zone_helper.exe`. Verified live 2026-09-12: tab 12 ✓, close 15 ✓,
"+" 16 ✓, update pill 30 ✓, page skip ✓, menu button, Alt+wheel (zone 21) ✓,
Shift+wheel (zone 3) ✓.

All patch attempts v5b→v16, the classifier chain (FUN_004156f0/
FUN_00415570/FUN_00414760), and the config-after-restart gotcha are in
`Docs/archive/NATIVE-REVERSING-2026-08-31.md` §10. Patch scripts (obsolete
iterations, kept for chronology): `Test/archive/zone-re/patch_zone12_v5b.js` …
`Test/archive/zone-re/patch_zone12_v16.js`. The CURRENT engine builder is
`AutoControl_native/patches/patch_zones_v19.js` (see §12).

## 11. Prototype: explicit zone detection IS possible (2026-09-02) ✅

**Test/zone_proto.ps1** — a fresh-process MSAA walker (AOP + accParent
x4, classify by role markers). Live result on Chrome 150 SxS:

- tab strip: d0=41 CELL (tab title) → d1=**37 TABITEM** → d2=16 LIST →
  **TAB-STRIP** (stable over 2 passes)
- omnibox: role **42** → OMNIBOX; page: role **15** DOCUMENT → PAGE;
  titlebar: role 16 (window) → window zone

**Conclusion: role 37 (TABITEM) in the ancestry uniquely identifies the
tab strip — no geometry.** The abandoned engine fails only because its
hover cache never refreshes over tabs. Reference classifier for the
future own-engine prototype (RE doc §11).

## 12. Engine v19 — the zone TABLE (2026-09-12, DEPLOYED) ✅

v18 (accept every UI region in the engine, filter in the SW) also broke INPUT
CONSUMPTION: `FUN_004156f0`'s return value IS the "consume the input" decision
(one call site, `0x415bdc`), so a wheel trigger with any mouse-over condition
swallowed the wheel everywhere and pages stopped scrolling.

v19 moves the decision OUT of the engine: the helper writes a table into the
engine's address space and the patched matcher reads it.

```
table page (helper-owned, VirtualAllocEx, PAGE_READWRITE):
  +0x00  alive   dword  1 while the helper runs
  +0x10  table   64 dwords, table[region] = 1 -> the precond matches

cave (VA 0x47F7A3, 93 zero bytes of .text tail padding; entry 0x4156F0 -> jmp):
  00: 83 FA 28            cmp  edx, 28h
  03: 73 17               jae  ORIG            ; >= 40 -> engine's own logic
  05: 80 3D <alive> 00    cmp  byte [alive], 0
  0C: 74 08               je   NOTALIVE
  0E: 8B 04 95 <table>    mov  eax, [edx*4+table]
  15: C3                  ret                  ; eax = match
  16: B8 01 00 00 00      NOTALIVE: mov eax, 1  ; helper down -> v18 behaviour
  1B: C3                  ret
  1C: 83 EC 20 53 55      ORIG (original first 5 bytes)
  21: E9 <rel32>          jmp  0x4156F5
```

Rebuild / deploy (the build is deterministic from the pristine exe):

```
node AutoControl_native/patches/patch_zones_v19.js %TEMP%\v19.exe
powershell -NoProfile -File Test/deploy_patched_engine.ps1            # already patched/
# or deploy the freshly built file:  ... -Source %TEMP%\v19.exe -Force
```

The helper (re)writes the cave prefix + the table on every classification
(`Test/ac_zone_helper.cs`, `WriteZoneTable`), so an engine started without the
helper keeps the v18 prefix from the file until the first classification.
Manual table writes without the helper: `Test/engine_zone_write.ps1
-Zones "12,4,1"` / `-Dump` / `-Diag` (the helper overwrites them within ~1 s —
stop it first).

### Verified live (real OS input through the native hooks)

| what | result |
|---|---|
| wheel over the page (3 notches) | `scrollY` 800 → 1100 → 2100, **0** false 750s |
| wheel over the tab strip | `trig 44: zones=[12,4,1] ∩ [12] → executing` → `pinTabs` |
| helper answers | page `[3,1]`, tab `[12,4,1]`, omnibox `[21,20,4,1]` |
| table readback | `alive=1`, `slot[12]=1`, `slot[3]=0`, `slot[4]=1` |

### Pitfalls (both cost hours)

1. **Cave off-by-one**: the first helper build put the `ret` at `0x14` — one
   byte early — so it overwrote the high byte of the table address
   (`0x03950010` → `0xC3950010`) and returned without reading. The engine then
   matched nothing while everything else looked healthy. `mh_test` B53 pins
   the current layout (`ORIG_BLOCK = 0x1C`, `npre[21] = 0xC3`, `npre[27] = 0xC3`).
2. **Chicken-and-egg**: the helper only ran when the SW asked (on a 750) and
   the engine drops the 750s it cannot classify → the SW now pings the helper
   every 2.5 s from boot (`__acZoneAsk(300)` in `sw.js`).
3. **The helper must own its page** (an early build reused the address found
   in the cave → wrote into foreign memory).

### Known limitation — regions ≥ 21

`FUN_004156f0`'s jump table covers `edx-3 = 0..17` (regions 3..20); a region-21
(omnibox) test trigger never fired even with `slot[21]=1` in the table. The
omnibox / browser-menu / bookmark-star / menu-item triggers therefore still
depend on the engine's own (failing on Chrome 148+) classification.

### Testing pitfalls (2026-09-12)

- The wheel goes to the ACTIVE tab: check `chrome.tabs.query({active:true})`
  before measuring `scrollY` (a Ctrl+Tab test silently switched tabs).
- An OPEN AutoControl menu keeps eating input — close it with
  `Test/ac_keys.ps1 -Combo esc`.
- `Runtime.consoleAPICalled` REPLAYS the backlog on attach: use
  `Test/ac_swlog_act.js <port> "<command>"` (prints only lines produced AFTER
  the injected action).
- `Test/zone_add_test.js add|remove <id> <region> <eventId>` creates/removes a
  temporary zone trigger to prove the engine delivers the 750 for a region.
