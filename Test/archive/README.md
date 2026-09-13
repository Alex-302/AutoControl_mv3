# Test/archive — historical one-off scripts

**What this folder is:** the junk drawer, kept on purpose.

Scripts in `Test/` (root) are the CURRENT toolset — they are referenced from
`AGENTS.md`, `Docs/` and from each other, and they are the ones you should
reach for. Everything under `Test/archive/` is a **one-off experiment from a
past debugging session**: it did its job once, a better tool replaced it, and
nothing references it any more (verified 2026-09-12: **0 external references**).

They are NOT deleted, because they document the chronology — *what was tried,
in which order, and why it failed*. That history is expensive to re-derive
(waves of RE work are recorded in `Docs/archive/`).

> ⚠ **Path note:** if an older doc writes `Test/<name>.js` for a file listed
> below, the file now lives here. Bare file NAMES in the docs are still valid
> (`patch_zone12_v16.js` = `Test/archive/zone-re/patch_zone12_v16.js`).

Nothing here is part of the build, the test harness (`mv3-build/mh_test.js`)
or the shipped extension.

## How this archive was created (2026-09-12)

`Test/` root had grown to 160 files, of which **82 were single-use
experiments** with zero references from any doc or script. They were moved
here (plain file moves, not deletions — git shows them as renames), grouped
by the session they came from:

| Group | Files | Session |
|---|---|---|
| `zone-re/` | 36 | engine-patch iterations + MSAA / honey-pot RE (2026-08-31 … 09-03) |
| `zone-probes/` | 26 | live zone experiments (2026-09-01 … 09-12) |
| `sw-log/` | 19 | superseded console readers + early CDP plumbing (2026-08-30) |

Also removed in the same pass: **`Test/ac_zone_helper.exe`** (8192 bytes,
sha `8772CDED…`) — a stale prototype copy left over from a stash restore.
Nothing referenced it; the real helper binary ships in
`AutoControl_native/ac_zone_helper.exe` (see `Docs/BUILD-NATIVE.md` §A).

> ℹ️ Current tool inventory: `Test/` root holds only tools that are
> referenced from `AGENTS.md`/`Docs/` — if you add a one-off probe, put it
> under `Test/archive/` when the session ends (and add a row to the tables
> below) or document it in `AGENTS.md` if it is meant to last.

---

## `zone-re/` — engine patch iterations + low-level RE probes

Chronology of the mouse-over zone work (2026-08-31 … 2026-09-03) and the
MSAA / honey-pot investigations behind it. **Read this first:**
`Docs/archive/NATIVE-REVERSING-2026-08-31.md` (the RE report — it carries the
verdict table for every `v5b`…`v17g` patch below).

| Files | What they were | Why they are here |
|---|---|---|
| `patch_zone12_stub.js`, `patch_zone12_v5b…v17g.js` (18) | Successive attempts to make the ENGINE classify browser-chrome zones itself (gate NOP, always-1, geometric stub, 792 probes) | Superseded by the **external helper + table** design (`Test/patch_zones_v19.js` + `Test/ac_zone_helper.cs`). Kept as the evidence that in-engine role-based selectivity is impossible (a fresh `AccessibleObjectFromPoint` from the LL-hook thread deadlocks). |
| `analyze_zones.js` | Dump of the ORIGINAL engine around the zone classifier | Static analysis snapshot; superseded by Ghidra + `Docs/archive/NATIVE-REVERSING-2026-08-31.md` |
| `zone_engine_scan.js` | Per-region classification scan against the engine | Superseded by `Test/zone_probe.ps1` |
| `zone_id_sweep.ps1` | Find which region id the engine passes to its mouseOver matcher | Superseded by the v19 table dump (`Test/engine_zone_write.ps1 -Dump`) |
| `_ac_msaa_probe5.ps1`, `_ac_msaa_probe6.ps1` | MSAA role probes (numbered iterations) | Superseded by `Test/_ac_msaa_probe.ps1` |
| `_ac_treewake.ps1` | Proves the MSAA tree "sleeps" (~30 s without a client → everything is an unnamed PANE) | Finding is documented and FIXED in `Test/ac_zone_helper.cs` (heartbeat) |
| `_ac_hp_browserwin.ps1`, `_ac_hp_verify.ps1` | Honey-pot (`WM_GETOBJECT` lParam=1) experiments per window | Finding documented in the RE report |
| `_ac_altwheel.ps1` | Alt+wheel over the omnibox as a zone-21 control | Replaced by the standard wheel probes (`Test/zone_fg_wheel.ps1`) |
| `_ac_win_shot.ps1` | Window screenshot helper | Superseded by the `PrintWindow` one-liner used during the zone tests |

## `zone-probes/` — one-off live zone experiments

Session scripts that armed synthetic configs / tailed logs to answer ONE
question each (2026-09-01 … 09-12). The current equivalents are
`Test/zone_add_test.js`, `Test/zone_e2e_test.ps1`, `Test/zone_probe.ps1`,
`Test/zone_fg_wheel.ps1` and the suite in `Test/zone-tests/`.

| Files | What they were |
|---|---|
| `zone_one_test.js`, `zone_inst_run.js`, `zone_arm_only.js`, `zone_750count.js` | Arm a synthetic single-zone config, count 750s / crash-checks |
| `zone_add_test12.js`, `zone_add_zones.js`, `zone_add_triggers.js` | Pre-baked test-trigger sets → superseded by the generic `Test/zone_add_test.js` (visibility-guarded) |
| `zone_readfile.js`, `zone_pagestate.js`, `zone_pagelog.js` | Inspect `settings.dat` / the settings page through the native |
| `zone_cfg_watch.ps1`, `zone_live_payload.js`, `zone_modcheck.js` | Verify that a forced config chain really sent type 60 / which wheel entries were compiled |
| `zone_bootlog.js`, `zone_actlog.js` | Console dumps for the SW boot and action-execution paths |
| `zone_keytest.ps1`, `zone_btn_test.ps1`, `zone_find_buttons.ps1`, `zone_menu_shot.ps1`, `zone_wheel_probe.ps1`, `zone_helper_hold.ps1` | OS-input probes (key / wheel / menu) and the tab-strip button hunt |
| `zone_fg_scroll.ps1`, `zone_scroll_test.ps1` | Older end-to-end wheel+scroll tests → superseded by `Test/zone_fg_wheel.ps1` |
| `zone_cfg_dump.js` | Compact dump of the stored triggers |
| `cdp_792_probe.js` | Force a 792 (zone-role) probe from a synthetic trigger → superseded by `Test/patch_zones_v19diag.js` |
| `zone_lr_test.js` | Does `_lr` send type 65 (advOpts/filter)? — answered, documented |

## `sw-log/` — superseded service-worker console readers

Every one of these was "attach to the SW and print the backlog, filtered
somehow" (2026-08-30). They all suffer from the same trap:
`Runtime.consoleAPICalled` **replays the whole session backlog** on attach, so
a naive reader mixes history with live events.

**Use `Test/ac_swlog_dump.js` instead** (read-only, regex filter,
`node Test/ac_swlog_dump.js 9223 "<regex>" <maxLines>`) or
`Test/ac_swlog_act.js` (prints ONLY the lines produced after a command) —
`Test/ac_swlog_record.js` records to a file in the background.

| Files | What they were |
|---|---|
| `zone_swlog.js`, `zone_swlog2.js`, `zone_swlog3.js`, `zone_swlog4.js` | Four successive backlog filters (trigger lines, type-800 window, type-60 range, fresh-SW boot) |
| `cdp_live_all.js`, `cdp_live_triggers.js` | Marker-based live capture, print-everything |
| `cdp_capture_flags.js`, `cdp_action_probe.js`, `cdp_raw_trig.js` | Capture-mode flags / action-runner wrapping / raw stored trigger JSON |
| `zone_watch750.js`, `zone_swtail.js` | Older live 750 watcher / SW-only log tail |
| `cdp_exts.js`, `cdp_msg_watch.js`, `cdp_native_probe.js`, `cdp_marker.js`, `cdp_keytest.js`, `cdp_restore_lk.js`, `cdp_rebuild_capture.js`, `cdp_fresh_trigger_test.js` | Early CDP plumbing experiments (ext list, native-message watch, marker test, key inject, `_Lk` restore, config rebuild, fresh-trigger test) — all superseded by `ac_swlog_*` + `cdp_eval.js` |

## `zone-re/` — additional entries (moved 2026-09-12, wave 2)

| Files | What they were |
|---|---|
| `zone_scan2.ps1` … `zone_scan5.ps1` | Successive MSAA element-map / hit-test / kebab-button hunts → superseded by `Test/zone_probe.ps1` and the helper itself |
| `zone_wininfo.ps1`, `zone_chain.ps1` | Top-level-window-at-point and MSAA ancestry printers |
| `_ac_crop.ps1` | Screen crops of the Chrome SxS window (manual inspection) |
| `_ghidra_dump_msaa.py` | Ghidra post-script draft — **dead: PyGhidra is not available in this setup**, post-scripts must be Java (`DumpMsaa*.java`). See `Docs/archive/NATIVE-REVERSING-2026-08-31.md` §2 |
