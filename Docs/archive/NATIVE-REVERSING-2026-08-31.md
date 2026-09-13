# Native reverse-engineering — MSAA hover-region root cause (2026-08-31)

**Status: root cause found, patch planned (not applied).** This file records
the full RE session: tools, binary findings (Ghidra), Chromium source facts,
live experiments and the resulting region map. Companion docs:
`NATIVE_PROTOCOL.md` (short protocol facts), `AGENTS.md` (gotchas).

> ⚠ **Path note (2026-09-12):** the obsolete patch iterations
> (`patch_zone12_stub.js`, `patch_zone12_v5b…v17g.js`) and the retired probes
> (`analyze_zones.js`, `zone_engine_scan.js`, `zone_id_sweep.ps1`,
> `_ac_msaa_probe5/6.ps1`, `_ac_treewake.ps1`, `_ac_hp_browserwin.ps1`,
> `_ac_hp_verify.ps1`, `_ac_altwheel.ps1`, `_ac_win_shot.ps1`) were moved to
> **`Test/archive/zone-re/`** — see `Test/archive/README.md`. File NAMES below
> are unchanged; only the folder differs. The live engine builder is
> `AutoControl_native/patches/patch_zones_v19.js` (the current engine builder).

---

## 1. Goal

The `mouseOver` preconds (`{type:14, value:region}`) stopped gating triggers
on Chrome 148+ — triggers fire in every region ("right click anywhere
activates the trigger", issue #1). We need to know WHY and whether the native
binary can be patched (the engine is abandoned — no updates will ever come).

## 2. Toolchain

- Ghidra (portable, `E:\Downloads\Tools\Ghidra`, ghidra_12.1.3_PUBLIC) +
  Temurin JDK 25 portable (`E:\Downloads\Tools\jdk-25.0.4.1+1`).
- Headless analysis: `analyzeHeadless E:\Temp\ac_ghidra AutoCtrl -import
  AutoCtrl_2025.4.22.0.exe -overwrite -scriptPath <repo>\Test -postScript
  DumpMsaa.java` (project dir `E:\Temp\ac_ghidra`).
- ⚠ PyGhidra is NOT available in this setup — post-scripts MUST be Java
  (`DumpMsaa.java` etc.), not `.py`.
- Scripts (repo `Test/`): `DumpMsaa*.java`, `DumpRegions*.java`,
  `_pe_imports.js` (PE import-table dump, no deps), `_ac_msaa_probe.ps1`,
  `_ac_win_probe.ps1`, `_ac_win_sxs.ps1`, `_ac_win_sxs2.ps1`,
  `_ac_honeypot.ps1`.

## 3. Binary facts (AutoCtrl_2025.4.22.0.exe, 32-bit PE, ~680 KB)

Imports: USER32 (108), SHELL32, GDI32, ole32, **HID.DLL** (joystick),
gdiplus (menu rendering), **OLEACC.dll (MSAA only — NO UIAutomationCore)**,
OLEAUT32, dxva2, ADVAPI32, KERNEL32.

### Key functions (Ghidra addresses)

| Addr | Role |
|---|---|
| `FUN_0040b610` | `AccessibleObjectFromPoint` wrapper — `*out=0; AccessibleObjectFromPoint(pt, out, &var); VariantClear` |
| `FUN_0040b5f0` | `AccessibleObjectFromWindow(hwnd, 0, IID_IAccessible, out)` wrapper |
| `FUN_0040bdf0` | **get_accName** helper (IAccessible vtable +0x28), copies into a string; `SysFreeString` after |
| `FUN_0040b930` | accNavigate (+0x5c) helper |
| `FUN_0040ba70` / `FUN_0040bcc0` | get_accRole (+0x34) ancestor walk helpers |
| `FUN_0040daf0` | `FindWindowExA(hwnd, 0, "Chrome_RenderWidgetHostHWND", 0)` + `SendMessageTimeoutA(hWnd, WM_GETOBJECT=0x3d, 0, 1, SMTO_ABORTIFHUNG, 1000, &res)` — **this is the MSAA honey-pot probe** (lParam=1 = kIdScreenReaderHoneyPot) |
| `FUN_0040db30` | start/stop browser tracking: `SetWinEventHook(2,2,…)` + calls `FUN_0040daf0` on the first tracked window; sets `DAT_004a2a38` |
| `FUN_0040d060` | browser-brand detection (msedge/brave/slimjet/Arc/…): **patches global class-name pointers** `PTR_s_Chrome_RenderWidgetHostHWND_0049d9f0`, `PTR_s_Chrome_WidgetWin__0049d9f8`, `PTR_s_Chrome__0049da10` |
| `FUN_004096c0` | class check: starts with `Chrome_WidgetWin_` AND is NOT exactly `Chrome_WidgetWin_0` |
| `FUN_00409750` | "is this a browser window" (class + style `GetWindowLongA(-0x10)&0x30000` + title) |
| `FUN_00415b40` | window under point (`FUN_00404e30`) → find in the tracked-window list (`DAT_004a2514`..`DAT_004a2518`) |
| `FUN_00415240` | hovered-element cache: `AccessibleObjectFromPoint` + cache (global `DAT_004a2b10`), refreshed when `DAT_004a2a44 != DAT_004a26b4` (position changed) |
| `FUN_00416270` | MSAA event handler (`AccessibleObjectFromEvent`); role checks 0xc/0x22/0x2/0x15/0xb/0x14; class checks vs `Chrome_`/`Chrome_RenderWidgetHostHWND` |

Window-class strings live in **global data pointers** (not inline compares),
so the engine can adapt to Edge/Brave/Slimjet/Arc by swapping the strings.

## 4. Chromium source facts (main branch)

`content/browser/renderer_host/legacy_render_widget_host_win.cc`:
- `Chrome_RenderWidgetHostHWND` = `kLegacyRenderWidgetHostHwnd` — a FAKE HWND
  created per web-content container **for screen readers** ("Some screen
  readers expect every tab to be in its own HWND"). Root of the MSAA tree per
  tab. (`ui/base/win/internal_constants.h`.)
- `OnGetObject`:
  - `kIdScreenReaderHoneyPot == 1` → `AXPlatform::OnScreenReaderHoneyPotQueried()`, returns 0.
  - `OBJID_CLIENT` → `AXPlatform::SetMsaaRequested()`; returns
    `LresultFromObject(IID_IAccessible, …)` ONLY if
    `GetOrCreateWindowRootAccessible(false)` returns non-null — i.e. **only if
    the a11y tree exists**. Otherwise returns 0 → oleacc serves a generic
    proxy (role PANE) for the window.

`ui/accessibility/platform/ax_platform.cc`:
- `OnScreenReaderHoneyPotQueried()`: **anti-abuse** (crbug 416429182) — the
  honey pot alone does NOT enable the full tree anymore. It only sets
  `screen_reader_honeypot_queried_`. The full tree
  (`OnPropertiesUsedInWebContent()`) is enabled only when the client ALSO
  queried **accName** (`is_name_used_`, set via `OnMinimalPropertiesUsed(true)`
  from a `get_accName` call). Role and location queries deliberately do NOT
  count (MSTSF probes role of every new window).

## 5. Root cause

The engine sends the honey pot once (FUN_0040db30/FUN_0040daf0) but NEVER
queries `accName` (its hovered-element code queries roles, navigate, title —
and `get_accName` only inside TSE "title"-based hovered-element actions, which
the region check does not use). On Chrome 148+ the MSAA tree stays OFF
(`kWebContents` AXMode not activated) → `AccessibleObjectFromPoint` returns a
generic PANE for every point → the engine cannot classify the region →
**fail-open: every region matches**. On Edge (and older Chrome) the tree was
built more eagerly → MV2 on Edge works.

This is NOT a port bug (same native, same behavior for MV2 on Chrome 148+).

## 6. Live experiments (Chrome 150 SxS)

- MSAA probe (`_ac_msaa_probe.ps1`): with the tree active — page =
  `role=15 (DOCUMENT)`, chrome/tab strip = `role=41 (TITLEBAR)`; window classes
  `Chrome_RenderWidgetHostHWND` / `Chrome_WidgetWin_1`. With the tree off
  (stable Chrome fullscreen) — everything = `role=16 (PANE)`.
- `--force-renderer-accessibility` launch flag: tree ON, regions
  distinguishable (verified).
- The earlier "regions fire everywhere" tests were hitting the FULLSCREEN
  stable Chrome (tree off); the SxS window itself has the tree active even
  without the flag in this environment (reason unknown — Canary build or a
  system AT present).
- ⚠ The engine CACHES the hovered element / region (FUN_00415240-style):
  tests need ≥ 2 s between `SetCursorPos` and the click, otherwise results
  flake (seen: r4/tabstrip true at 300 ms, false at 400 ms, stable at 2 s).

### Stable region map (SxS, tree ON, 2 s pauses)

| Region | Page click | Tab-strip click | Verdict |
|---|---|---|---|
| 1 Browser window | fires | fires | works (whole window) |
| **3 Web page** | fires | blocked | **works correctly** |
| **4 Title area** | fires | fires | **BROKEN: behaves like region 1 (matches the page too)** — exactly the issue-#1 complaint |
| 5 Tab | blocked | blocked | broken (fail-closed) |

## 7. Fix options

1. **Launch flag** (user-side, verified): `--force-renderer-accessibility`.
   Trade-off: permanent a11y overhead; needs the flag on every launch.
2. **Native patch (planned)**: add a `get_accName` call right after
   `AccessibleObjectFromPoint` in `FUN_0040b610` (the helper `FUN_0040bdf0`
   already exists in the binary) — one targeted code patch (~20-30 bytes,
   jump into a free padding area). Once the client used accName, the honey pot
   flag + `is_name_used_` enable the full tree **for the whole browser** →
   region 3 (and 1) work on Chrome 148+. Region 4 remains broken at the
   engine's classifier level (it maps region 4 to the whole window) — that
   needs a separate classifier patch or the extension-side mouse-tracking
   filter (see AGENTS.md "Hover regions").
3. Extension-side workaround (no binary): content-script cursor tracker +
   SW filter for regions 3/4 (designed, not implemented).

## 8. Files produced

- `Test/DumpMsaa.java`, `DumpMsaa2..4.java`, `DumpRegions.java`,
  `DumpRegions2..5.java` — Ghidra post-scripts (Java).
- `Test/_pe_imports.js` — PE import dumper.
- `Test/_ac_msaa_probe.ps1`, `_ac_win_probe.ps1`, `_ac_win_sxs.ps1`,
  `_ac_win_sxs2.ps1`, `_ac_honeypot.ps1` — live probes.
- Ghidra project: `E:\Temp\ac_ghidra\AutoCtrl.rep` (engine imported,
  analyzed).

## 9. Patch versions & the diagnostics toggle (v4, 2026-08-31)

`Test/patch_accname.js` builds the patched engine deterministically from
the pristine `.bak` (adds the `.acp` PE section + stub + the 5-byte jump
at 0x40b63b):

| Artifact | SHA-256 | 792 diagnostics |
|---|---|---|
| original | `8ae9a669…` | n/a (no stub) |
| v2 (deployed) | `f6024079…` | none (accName only) |
| v3 | `90c3b526…` | always on (unconditional send) |
| v4 `--diag-off` | `53b42096…` | gated, default OFF |
| v4 `--diag-on` | `da8c03d8…` | gated, ON |

> ⚠ The v2/v3/v4 **builds** are not in the repo any more (deleted 2026-09-12
> together with the other superseded engine binaries); rebuild with
> `Test/patch_accname.js --diag-on|--diag-off` if the 792 diagnostics are
> needed again. The deployed engine today is the v19 zone-table build
> (`AutoControl_native/patched/`).

Deploy: `Test/deploy_patched_engine.ps1` (stops SxS, kills only orphan
Zero/engine pairs, backs up to `.orig`, copies, verifies SHA-256); deploy any
other build with `-Source <exe> -Force`.

**Toggle bit:** 1 byte in the `.acp` section at VA `0x4b5000` (file
offset `0xaac00` for this binary — the script prints both on every run).
`0` = 792 silent, `1` = emit. The stub checks it with
`cmp byte ptr [0x4b5000],0; jz nosend` right before the role-fetch/send
block — the `get_accName` call (the actual Chrome 148+ tree fix) is NOT
gated and always runs.

Flip via `node Test/patch_accname.js --diag-on|--diag-off` (default off)
or a hex-edit of that single byte (no rebuild needed — the stub is
already in place; the script re-patches deterministically anyway).

Why: the 792 stream is only needed during zone testing; the fixed engine
can run in daily use with the flag off (no console noise, no extra native
messages). The v3 stub (always-on send) is superseded — kept only as a
hash reference.

**⚠ CRITICAL (2026-08-31, live-verified): the 792-ON build BREAKS the
hover-region (mouseOver) classification.** With the flag=1 build deployed,
NO mouseOver-gated trigger fires at all (the user's omnibox-zone event died
in real use; SxS probes: no 750 from any zone event). The same binary with
flag=0 classifies correctly (synthetic RMB+mouseOver region-3 trigger fired
750; the user's omnibox event worked again immediately). ROOT CAUSE
hypothesis: the role query + FUN_00408600 send INSIDE the hot hover path
(FUN_0040b610 → zone classification) corrupts the classification flow. The
792 block must NEVER be enabled for normal use — the toggle exists only for
isolated diagnostics, and even then zones are dead while it is on. A
future 792 redesign must move the send OUT of the hot path (e.g., a
delayed/queued send or a separate timer reading the cached hover element
from FUN_00415240's cache).

## 10. Zone-12 (tab strip) deep-dive — 2026-09-01/02 (live session)

Goal (user): wheel over the TAB STRIP without modifiers → action
(tab switch / reload). Result: **classifier patching works, zone-12
selectivity does NOT on Chrome 150** — root cause found and proven.

### 10.1 Classifier chain (deobfuscated)

MouseOver precond (compiled type 13) → FUN_00420050 case 0xd →
FUN_00415bf0 (zone cache) → FUN_00415b40 (point→hwnd→zone) →
FUN_004156f0(point, zone, hwnd):

- zone 3 (page): pure geometry — FUN_0040e5c0 rect + PtInRect → WORKS
- zone 21 (omnibox): role == 0x2a (42) on the hover cache → WORKS
- zone 0xc (12, tab strip): FUN_00414760(point, hwnd, 10) gate →
  if 0 → fail; then hover cache FUN_00415240; then FUN_00415570
  (role-based: hovered/parent role == 0x25 (37), or for crVer<100
  LIST+childCount fallback)

### 10.2 Why zone 12 is dead on Chrome 150 (proven)

1. FUN_00414760(...,10) returns 0 over the tab strip (its monitor-
   scaled rect cache is broken for the modern maximized window) — the
   gate alone kills zone 12. Bypassing it (NOP the jz at 0x415781)
   still does not help because:
2. FUN_00415570 needs hovered role 0x25 (37) — but Chrome 150 reports
   the tab itself as role **41** (0x29, CELL-ish) with parent 37, and the
   strip gap as 16/60. The crVer gate (150-0x55 >= 0xf) disables the
   old LIST+childCount fallback. v9 accepted {37,41,60,16} — still dead,
   because:
3. **The engine's hover cache NEVER refreshes over the tab strip** — it
   tracks Chrome_RenderWidgetHostHWND (page) only. A 792-role probe
   placed in FUN_0040b610 (AOP wrapper, fires on cache refresh)
   produced NO 792 over the tabs even with mouse movement — the cache
   stays on the last page element (role 15 DOCUMENT) → "tab = page".

PowerShell MSAA probes see 41/37 over the tabs — but that is a DIFFERENT
MSAA client; the engine's own AOP/cache path never gets a tab element.

### 10.3 Patch attempts (all built from the pristine .bak, deterministic)

| Build | Script | What it did | Live result |
|---|---|---|---|
| v5b 7814065e… | patch_zone12_stub.js | gate NOP + FUN_00415570 = always 1 (in-place) | ✅ zone 12 fires EVERYWHERE (750+reload) — proves the chain works |
| v7 e3e6e63… | patch_zone12_v7.js | gate NOP + .acp stub, roles {37,41,60,16} | ❌ **build bug: section math used undefined last.rsize → .acp raw=0, jmp into zeros** — hash identical to v8diag |
| v8diag e3e6e63… | patch_zone12_v8diag.js | gate NOP + .acp stub + 792 send from FUN_00415570 | ❌ same build bug (empty .acp) |
| v9 63be26d… | patch_zone12_v9.js | fixed section math; roles {37,41,60,16} → else original parent path | ❌ no 750 over tabs (roles the ENGINE sees are not in the set) |
| v10 905444f… | patch_zone12_v10.js | jmp→.acp stub, ALWAYS 1 (isolation test) | ✅ works like v5b ("everywhere") — .acp jmp itself is fine |
| v11diag 963a9f84… | patch_zone12_v11diag.js | always-1 + 792 send from FUN_0040b610 | ❌ no 792 (cache never refreshes over tabs) + 792-in-hot-path corrupts classification |
| v12 11cd00f… | patch_zone12_v12.js | gate NOP + geometric stub (GetWindowRect, y-top<70) | ❌ stub bugs: POINT* read from wrong pushad slot; result in AL wiped by popad |
| v13 57541e76… | patch_zone12_v13.js | geometric stub fixed | ❌ **forgot the gate NOP** — FUN_00414760 gate still kills zone 12; also config had not reached the engine |
| v14 658c1a48… | patch_zone12_v14.js | v13 + gate NOP | ❌ "nothing anywhere" — the CONFIG (type 60) had NOT reached the engine after restart (see 10.4) |
| v15diag 963a9f84… | patch_zone12_v15diag.js | always-1 + 792 from FUN_0040b610 | ❌ 792 corrupts classification (RE §9); no 750 |
| **v16 94f0984…** | patch_zone12_v16.js | gate NOP + always-1 (== v5b) | ✅ **FINAL WORKING BASELINE**: Alt+wheel on omnibox ✓, Shift+wheel on page ✓, plain wheel fires everywhere (expected for always-1) |

v16 == v5b semantics (hash b94f0984 == earlier v5b build) and is the
**currently deployed engine**.

### 10.4 Operational gotcha: config (type 60) after a restart

The config chain is driven by the SETTINGS PAGE (_Gf → type 60), not
the SW alone. After a Chrome restart without an open settings page, the
type 60 never reaches the engine → "nothing anywhere" (all zones dead,
even the previously-working 3/21). Force it via:

ode Test/cdp_eval.js 9223 "(()=>{_Gf({},()=>{window.__cfgDone=1})})()"
then verify in the boot log: 	ype 60 (config) map: N keys. This
explained most of the "nothing works" reports during the session.

### 10.5 Conclusions & the future direction

- The engine's zone classification IS patchable (v16 proof) and zones
  3/21 work on Chrome 150.
- Zone 12 (tab strip) cannot be made selective **inside the abandoned
  engine** — its hover cache never refreshes over the tab strip (tracks
  the page HWND only), so it never sees a tab element. A geometric
  classifier (GetWindowRect top band) was designed (v12-v14) but never
  conclusively tested with a working config + fixed stub.
- **UPDATE (2026-09-02, §11): explicit detection IS possible from our
  own process** — Test/zone_proto.ps1 proves role 37 (TABITEM) in the
  point's MSAA ancestry uniquely identifies the tab strip, no geometry.
  The abandoned engine's failure is a cache limitation, not an MSAA one.
- Recommended future work (user's idea, now validated): a prototype of
  our own native engine that does a fresh AccessibleObjectFromPoint +
  ancestry walk per event — Test/zone_proto.ps1 is the reference
  classifier.

## 11. Prototype result — EXPLICIT tab-strip detection IS possible (2026-09-02)

Test/zone_proto.ps1 (a fresh-process MSAA walker: AccessibleObjectFromPoint
+ accParent x4, classifies by role markers) proves the hypothesis:

| Point | d0 | d1 | d2 | Classified |
|---|---|---|---|---|
| tabstrip 5/5 (y=40) | 41 CELL (tab title) | **37 TABITEM** | 16 LIST | **TAB-STRIP** (explicit) |
| tabstrip/4 (edge) | **37 TABITEM** | 16 | 16 | TAB-STRIP (37 @ d0) |
| omnibox | 42 'Address and search bar' | 20 | 22 | OMNIBOX |
| omnibox (dropdown open) | 57 (0x39) | 20 | 22 | OMNIBOX (57 added) |
| page (regular site) | 15 DOCUMENT | 9 | 16 | PAGE |
| titlebar | 16 (window) | 16 | 60 PAGETABLIST @d2 | UNKNOWN (60 @ d2 rejected) |

Stable across 2 passes with 2s pause (identical walks). The marker
**role 37 (TABITEM) at depth 0-1 uniquely identifies the tab strip** —
no geometry involved. PAGETABLIST 60 counts ONLY at depth 1 (strip gap);
a titlebar point also has 60 in its ancestry but at depth 2+ (rejected).
A page's role-41 content element (Chrome error page) has NO 37 parent →
correctly NOT classified as tabs. Omnibox = 42 (edit) or 57 (0x39,
autocomplete/dropdown state).

**Conclusion:** the ABANDONED engine cannot do this only because its hover
cache never refreshes over the tab strip (it tracks the page HWND). A
replacement engine of our own (fresh AOP per event, walk the ancestry)
CAN classify every zone explicitly. Test/zone_proto.ps1 is the
reference implementation for the classifier part.

## 12. Why role-based patching inside the engine is impossible (2026-09-03)

Final isolation chain (v17e/v17g, live):

- v17e (tail-call stub, ALWAYS-1, no MSAA) fires 750 everywhere → the
  zone-12 tail-call at 0x4157d3 IS the executed path.
- v17g (same stub + fresh AccessibleObjectFromPoint via FUN_0040b610 +
  type-792 send + always-1) fires NOTHING, sends NO 792, but the engine
  stays alive (type 185 still answers from another thread).

Conclusion: **AccessibleObjectFromPoint called from the engine's LL-hook
context DEADLOCKS** — Chrome does not answer WM_GETOBJECT while input is
being processed (input-hook reentrancy deadlock). The hook thread hangs
inside the AOP call forever; the engine process survives (other threads
serve 185/920), but no further 750 are ever generated and no 792 is sent.

This closes the loop on every previous attempt:

| Path | Result |
|---|---|
| role from the hover CACHE (v9, [esi+0x2c]) | cache never refreshes over the tab strip (engine tracks page HWND only) → stale role 15 |
| fresh AOP in the hot path (v17..v17g) | **deadlock** (WM_GETOBJECT unanswered from the LL-hook) |
| always-1 (v16/v17e) | works, but non-selective |
| **external process** (Test/zone_proto.ps1) | **works** — outside input processing Chrome answers; role 37 (TABITEM) in ancestry uniquely identifies the tab strip |

**Definitive verdict: zone-12 selectivity cannot be patched into the
abandoned engine. The proven path is our own external engine using the
zone_proto classifier (fresh AOP outside the input hook).** v16
(b94f0984, always-1) remains the deployed working baseline.

## 13. Zone-12 WORKING SOLUTION: external zone helper (2026-09-03) ✅

The deadlock (§12) closed in-engine patching — so the zone gate moved OUT
of the engine into the extension SW + a tiny external helper:

- **Helper** (native host com.autocontrol.zonehelper, source
  Test/ac_zone_helper.cs, built with .NET Framework csc → installed in
  %LOCALAPPDATA%\AutoControl\ac_zone_helper.exe): answers
  {"__id":N} → {"__id":N,"zone":Z,"zones":[...]} where the SET is classified
  from a NORMAL process context (no hooks): SetProcessDPIAware +
  GetCursorPos + AccessibleObjectFromPoint + accParent walk. Roles: 15 → 3;
  37 @d0-1 → 12; 60 @d0-1 → 12 (+4 for the strip gap); 43 under a PAGETAB →
  15 (right half) / 17 (left half); 43 under the PAGETABLIST → 16; 42 → 21;
  57 under the GROUPING → 21; 22 in the ancestry → 20; 43/57 in the toolbar
  inside the GROUPING → 33; toolbar button hugging the window's right edge →
  30; unnamed PANE outside toolbar/page/strip → 4; 1 always. Proven live:
  (300..900,35) → [12,1], page → [3,1], close → [15,1], "+" → [16,1],
  pill → [30,20,1].
- **SW gate** (mv3-build/sw.js, __acDispatchTrigger750): for triggers
  with mouseOver preconds the SW asks the helper and dispatches the action
  ONLY if the real zone SET intersects the trigger's regions. Zone map is
  built from storage trigActList at SW start (rebuilt live on storage
  changes). Triggers whose regions are ALL outside the helper's known set
  (menu items 40-51 — the native classifies those itself) are passed
  through with the engine's verdict. All 750s of one input burst share one
  helper answer (120 ms cache).
- **Engine strategy CHANGED in v18** (2026-09-12): the "engine stays v16"
  note below was only half of the story — with v16 the engine still DROPPED
  the 750 for regions it cannot classify (measured: a real wheel over the
  close button produced a 750 for the zone-12 trigger only), so the gate had
  nothing to judge. `Test/patch_zones_v18.js` (deployed hash F96BF544…)
  therefore makes every precond region BELOW 60 match in the engine (code
  cave + `jmp` trampoline at FUN_004156f0) and leaves regions ≥ 60 (the
  AutoControl menu) to the engine's own classification. Selectivity now
  lives 100% in the SW gate.
- **Verified live (2026-09-12)**: zone map per trigger; over a tab
  `trig 41: zones=[12,1] ∩ [12] → executing`; the page → skipped; close
  button → zone 15 executing; "+" → 16 executing; update pill → 30
  executing. User-confirmed working (also with two browsers side by side —
  no cross-actions).
- Files: Test/ac_zone_helper.cs, Test/zone_helper_smoke.js,
  %LOCALAPPDATA%\AutoControl\com.autocontrol.zonehelper.json (+HKCU
  Software\Google\Chrome\NativeMessagingHosts\com.autocontrol.zonehelper).

### 13.1 ALL non-menu regions classified (2026-09-12)

The helper was extended from the single role-based rule set (12/21/3) to
**11 regions**, and the answer became the full matching SET:

```
{"__id":N,"zone":P,"zones":[...]}      P = most specific (logging / old SW)
```

- New rules: **16** "+" = 43 PUSHBUTTON under the PAGETABLIST 60;
  **15/17** = 43 under a PAGETAB (close = right half of the tab, speaker =
  left half — position decides, no localized names); **20** = role 22
  TOOLBAR in the ancestry; **33** = 43 inside the omnibox GROUPING 20 which
  sits in the toolbar; **4** = the unnamed frame PANE outside the
  toolbar/page/strip; **1** = always (the cursor is inside the window);
  **30** = a square 43/57 hugging the window's right edge (the kebab is NOT
  exposed as an element in Chrome 150, and the "New Chrome available" pill
  covers its slot, so this rule is implemented but unverified).
- The SW gate now intersects sets: `zones.some(z => zs.indexOf(z) !== -1)`
  (log: `zones=[12,1] ∩ [12] → executing`), matching the engine's semantics
  (every region is evaluated independently — the omnibox is also "toolbar",
  the page is also "browser window").
- The helper calls `SetProcessDPIAware()`: element rects are PHYSICAL
  pixels, `GetWindowRect` is DPI-virtualized for unaware processes (150%:
  real ~2094 px, reported 1396) — this broke the scanners until fixed.
- Verified: per-point answers for all 11 regions (TODO §2d) + end-to-end
  with REAL OS wheel events (`Test/zone_e2e_test.ps1`): tab → executing,
  page → skipped. Menu-item regions (40-51) remain open — the native
  already tracks the hovered item (type 185), so the SW-side path is the
  cheap one.
- Tooling added: `Test/zone_scan.ps1`..`zone_scan4.ps1` (signature
  scanners), `zone_probe.ps1` (live per-point probe), `zone_e2e_test.ps1`
  (real wheel + SW log tail), `zone_swtail.js` (SW console tail).
- ⚠ The running Chrome SxS loads the extension from
  `C:\Work\AutoControl-Keyboard-shortcuts-Mouse-gestures-Chrome\mv3-build`,
  not from the repo — `sw.js` must be copied to BOTH folders (the
  `Secure Preferences` path is stale; verify with a `fetch()` of sw.js in
  the SW, see AGENTS.md).
