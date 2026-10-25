# HANDOFF — zone table stale on a fast cursor move (2026-10-25)

Goal of this file: give the next session the full context WITHOUT re-reading
the chat history. Read this file first, then `AGENTS.md` and
`Docs/TODO-mouseover-zones.md` §8.

## 1. Git state (read-only facts)

- Branch: `fix/zone-table-stale-on-move`, based on `master` (`8d0ca6e`).
- Commits before the docs pass:

  ```text
  7cc7638 fix(helper): allow horizontal movement along the tab strip
  94dd718 fix(helper): invalidate the zone table from an independent watcher thread
  29db4c7 fix(helper): keep the provisional table write alive during engine re-bind
  6f44c97 fix(helper): let the periodic engine re-bind run
  e5f9ec8 fix(helper): discard zone classifications for a point the cursor has left
  cb469bc fix(helper): serialize the provisional table write with a real classification
  69fe503 test: pin the zone-table invalidation and the burst share
  67ee690 fix(sw): stop reusing a zone answer across wheel events
  48fb133 fix(helper): invalidate the engine zone table while the cursor moves
  8d0ca6e fix(helper): make the zone helper's diagnostic log opt-in
  ```

- Docs commit: `38a7298` (`docs: record the zone-table staleness fix
  (2026-10-25)`).
- Pushed to `origin/fix/zone-table-stale-on-move`; PR #22 is open:
  https://github.com/Alex-302/AutoControl_mv3/pull/22
- Engine unchanged: v19
  `1A10EDD191B80A806DF66558B2B1E78BE8D6AD81E93EEAC772D13F222E212C3E`;
  `mv3-build/file76.dat` md5 `2F878E9EB062C57D8B5C7FFBC91EAB5D`.
- Helper: `199ABE4BF6999578DDB432E25DFC0339061A3925B3A035A060B120910C8119F6`,
  **26624 bytes**.
- `mv3-build/ac_zone_helper.dat`: **26624 bytes**, sha256
  `D896167D927D8FE15F1E7FA37ED2E2C2A06A3E79C9CF716841032665C93D2457`.
- `mh_test`: `123 pass, 0 known gaps, 0 FAIL, 0 notes` (after the docs pass).
- `verify_all`: `VERDICT: PASS` (harness, tool inventory, native byte proof).

## 2. Symptom

The user scrolled the wheel over the page immediately after moving the cursor
from the tab strip. Occasionally the "wheel over Browser tab" action switched
tabs instead of scrolling the page. The action has two combos:

- `Alt+wheel` — no mouse-over condition;
- `wheel over Browser tab` — region 12.

A second symptom appeared during the fix: after the first invalidation was
added, tab switching sometimes missed a notch when the cursor moved
horizontally along the tab strip.

## 3. Root cause chain

1. The engine (v19 cave) recomputes its region verdict only when more than
   300 ms passed or the cursor moved more than 3 px, then reads the helper's
   zone table.
2. The helper wrote the real table asynchronously. A real `[12,4,1]` write
   could land after the cursor had left the tab strip. The engine then read
   `[12,4,1]` over the page and fired the 750.
3. The SW gate could not reject it. The unscoped `Alt+wheel` sibling marks the
   whole action `__acZoneFree`, so the SW dispatches without the zone check.
   The engine's table is the only filter.
4. The SW also had a 120 ms time-only zone-answer cache. It could reuse an
   answer across a cursor move.
5. The helper's provisional invalidation (`[1]`/`[]` on movement) ran on the
   heartbeat thread. That thread blocks for hundreds of ms inside the MSAA
   walk. Live log: real `[12,4,1]` at `19:36:43.652`, next fast `[1]` at
   `19:36:44.372` — a 720 ms gap — while seven SW 750s fired at
   `19:36:43.844`–`44.242`.
6. The 3 px threshold applied to both axes. A horizontal move along the tab
   strip cleared zone 12, so some wheel notches were ignored. Live log: real
   `[12,4,1]` at `19:46:54.065`, fast `[1]` at `.120` and `.151`, real
   `[12,4,1]` at `.195`.

## 4. Fix

### 4.1 Service worker (`mv3-build/sw.js`)

- Removed `__AC_ZONE_CACHE_MS` (the 120 ms time-only TTL).
- Added `__AC_ZONE_BURST_MS = 15`. One input burst shares the first helper
  answer only for 15 ms from the burst START. A generation counter guards the
  share. Later 750s re-ask the helper, so a cursor move between notches is
  seen.
- Keepalive uses `__acZoneAsk(300, true)` (`noShare`), so it never seeds or
  reuses the burst answer.
- Pins: `mh_test` B53/B53h (source + runtime burst share/noShare).

### 4.2 Helper (`Test/ac_zone_helper.cs`)

- `WriteZoneFlagsFast` — cached-handle table write.
- Provisional `[1]`/`[]` invalidation when the cursor moves. Provisional
  writes are serialized with the real classification under `engLock`
  (order `engLock -> zoneLock`).
- `ProvisionalWatcher` — a dedicated thread started in `Main`. Every 10 ms it
  reads the cursor and writes only the provisional table. It does NO MSAA, no
  classification, no tab walk, and never waits for `servingRequest` or
  `bindLock`. The heartbeat now only classifies and warms the tab cache.
- Stale classifications are discarded. The point is re-sampled after the MSAA
  walk and again inside `engLock`. The log shows `classify stale` and
  `table write skipped`.
- `cacheHasTab` — set by the last REAL classification; provisional writes
  never touch it. `StaleFor` uses it: for tab-related zones (12/15/17), a
  classification is stale only when `|now.Y - sampled.Y| > 24` px, so
  horizontal movement along the tab strip does NOT invalidate. Other zones
  keep the 3 px rule. The watcher uses the same rule.
- The periodic 1000 ms engine re-bind now actually runs (`lastBindAt` moved
  only by the slow bind path). Discovery (`FindEnginePids`/`EngineIsMine`/
  `ModuleBaseOf`/cave claim) no longer holds `engLock`. `bindLock` was added;
  publish stays short under `engLock`.

## 5. Evidence

Helper log before the watcher (the false positive):

```text
19:36:43.652  table write: alive=1 zones=[12,4,1]
19:36:43.844  SW 750 trigger 5 -> activateTabs
19:36:43.904  SW 750 trigger 5 -> activateTabs
19:36:43.988  SW 750 trigger 5 -> activateTabs
19:36:44.069  SW 750 trigger 5 -> activateTabs
19:36:44.123  SW 750 trigger 5 -> activateTabs
19:36:44.182  SW 750 trigger 5 -> activateTabs
19:36:44.242  SW 750 trigger 5 -> activateTabs
19:36:44.372  table write (fast): alive=1 zones=[1]
```

Helper log after the watcher (the false negative):

```text
19:46:54.065  table write: alive=1 zones=[12,4,1]
19:46:54.120  table write (fast): alive=1 zones=[1]
19:46:54.151  table write (fast): alive=1 zones=[1]
19:46:54.195  table write: alive=1 zones=[12,4,1]
```

The final build was made for this behavior: a horizontal move along the strip
keeps `[12,4,1]`, while a move to the page still produces fast `[1]` and then
`[3,1]`. The user's final run reports the expected behavior. The helper log
for that run was not captured.

## 6. Validation

- `node Test/patch_bytes_verify.js` → `PROOF HOLDS`, 40 bytes differ, all
  inside the documented ranges.
- `powershell -ExecutionPolicy Bypass -File Test/build_native.ps1
  -UpdateBundle` → all hashes OK; a clean rerun.
- `node Test/engine_abi_dump.js
  AutoControl_native/patched/AutoCtrl_2025.4.22.0.v19.exe` → `ABI AUDIT: OK`.
- `node Test/mh_test.js` → `SUMMARY: 123 pass, 0 known gaps, 0 FAIL,
  0 notes` (after the docs pass).
- `node Test/verify_all.js` → `VERDICT: PASS` (harness, tool inventory,
  native byte proof).
- Docs pass: all current claim sites use the new helper hash and size; the
  payload claims use `D896167D…2457`; B58 records `2ADF3898…FA4F` as retired.

## 7. Live run

The user tested on their stable Chrome with real wheel input. Moving the
cursor away from the tab strip stops the tab action immediately; wheel tab
switching over the strip works; the page scrolls normally.

The exact Chrome build and OS were NOT recorded. Record them if the next
session repeats the live run.

## 8. Risks and rollback

- The engine patch and the cave bytes are unchanged. `file76.dat` is
  unchanged.
- Helper rollback: restore the previous helper
  `2ADF3898A2DC2948FC4CD2AF0C04586B28FB2C23D250B198A1D2F56CED84FA4F`
  (22528 bytes) and its payload. The SW 15 ms burst share is independent and
  safe to keep.
- The `alive=0` fallback (helper down) still matches every region — the v18
  behaviour. A missing helper is a required-component failure; the SW
  self-heals the payload.
- The 24 px Y threshold for tab zones is a heuristic. A move from the tab
  strip to the title bar within 24 px keeps zone 12. This is acceptable. Do
  not lower the threshold without re-testing the false positive.
- The watcher polls every 10 ms. CPU is negligible. Do not move the
  provisional write back to the heartbeat.

## 9. Not verified

- Other browsers (Brave, Opera, Vivaldi) were not exercised in this round.
- The 8 individual menu-item regions 41–51 remain a separate open item
  (`Docs/TODO-menu-items.md`).
- The exact Chrome build and OS of the live run were not recorded.
- No automated test covers the physical wheel. `mh_test` pins the source and
  the runtime burst share only.

## 10. Next steps

1. PR #22 is open. Update its description to the final state if needed, then
   merge.
2. The helper hash did not change in the docs pass, so the binary under test
   is still `199ABE4B…19F6`.
3. Keep `Docs/TODO-mouseover-zones.md` §8 as the chronology.
4. If a false positive returns, capture the SW log and the helper log for the
   same second:
   - fast `[1]` before the 750 → the engine cache is stale (a v20 patch is
     needed);
   - no fast `[1]` → the watcher is not running (check the helper hash and the
     log);
   - real `[12,4,1]` while the cursor is over the page → check the watcher
     threshold and the cursor point.
5. If a false negative returns, check whether the cursor moved horizontally
   along the strip and the table was `[1]`. The `cacheHasTab`/`StaleFor` rule
   is the place to look.

## 11. File map

| File | Role |
|---|---|
| `mv3-build/sw.js` | zone gate, 15 ms burst share, `__acZoneAsk(timeoutMs, noShare)`, `__acZoneFree` |
| `Test/ac_zone_helper.cs` | helper source: watcher, stale discard, fast write, zone-aware threshold |
| `AutoControl_native/ac_zone_helper.exe` | repo helper binary |
| `mv3-build/ac_zone_helper.dat` | bundled helper payload |
| `Test/mh_test.js` | B53/B53h pins, B58 retired list |
| `Test/build_native.ps1` | `$EXPECT_HELPER`, `$EXPECT_DAT_MD5` |
| `Docs/TODO-mouseover-zones.md` | primary chronology (§8 is this fix) |
| `Docs/GOTCHAS.md` | pitfalls: watcher thread, tab-strip Y rule, burst share |
| `Docs/BUILD-NATIVE.md` | build recipe and hash claims |
| `CHANGELOG.md` | user-facing entry |

## 12. How to start the next session

1. Read this file.
2. Run `git log --oneline -12`, `git status --short`, and
   `node Test/mh_test.js`.
3. Read `Docs/TODO-mouseover-zones.md` §8 and the zone bullets in
   `Docs/GOTCHAS.md`.
4. Do not edit `ext-mv2/` or `mv3-build/` test files.
