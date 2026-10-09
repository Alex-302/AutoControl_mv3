# TODO — Menu-item zones (41-51): per-kind verification

**Created:** 2026-10-05 · **Status:** ⬜ **OPEN, LOW PRIORITY** — deferred by the
user on 2026-10-05 ("это низкоприоритетное"). Split out of
`Docs/TODO-mouseover-zones.md`, which is otherwise complete.
**Goal:** prove that each individual *menu item* region fires on the RIGHT kind of
menu item — not just that "any menu item" fires.

## What these regions are

The action editor offers **8 item kinds** (regions 41–51). They exist so a trigger
can react to one kind of menu entry, e.g. "reload the tab of the menu item I
wheeled over".

| # | UI name (action editor) | region | bundle const |
|---|---|---|---|
| 1 | Any menu item | 40 | `_9r` |
| 2 | Menu item: tab | 41 | `_ju` |
| 3 | Menu item: tab submenu | 42 | `_gk` |
| 4 | Menu item: closed tab | 44 | `_et` |
| 5 | Menu item: closed window | 45 | `_Pg` |
| 6 | Menu item: bookmark | 46 | `_Nu` |
| 7 | Menu item: bookmark folder | 47 | `_yr` |
| 8 | Menu item: action | 48 | `_Te` |
| 9 | Menu item: switch | 51 | `_Ju` |

⚠ Regions **43, 49, 50 do not exist** in the UI — do not invent them.

## How they work (already established — do not re-derive)

* The compiled type-60 precond carries the **RAW UI region**: compiling a test
  trigger through the real `_mh` produced `{type:14,"value":41}` for
  "Menu item: tab" (and `12/4/30/21/3` for the pointer zones). So these regions
  reach the engine unchanged — the helper is NOT involved.
* The v19 trampoline lets the **menu regions through to the engine's own
  classification** (`edx >= 0x28` → the original code). The engine tracks the
  native menu itself: type **170** opens it, type **185**
  (`{usePrvMsPos}` → `{hilited, hovered, marked}` item indexes) reports the
  hovered item, type **175** closes it / answers "is a menu open".
* The SW zone gate treats a trigger whose regions are ALL menu regions as
  engine-classified and **passes it through** (the helper has no signature for the
  native menu) — see `Docs/GOTCHAS.md` and the gate test in `Test/mh_test.js`.

## What IS verified

* **"Any menu item" (40) — ✅ VERIFIED 2026-09-12:** a `mouseOver = Any menu item`
  trigger fired over the OPEN menu and stayed silent over the page, the tab strip
  and beside the menu (`Docs/TODO-mouseover-zones.md` §2g).
* The engine-classified route itself works (the same code path serves all of them).

## What is NOT verified (this TODO)

**Per-kind accuracy:** does "Menu item: tab" fire on a TAB item and stay silent on
a bookmark item, a switch item, etc.? Nothing in the current evidence distinguishes
the kinds — the region reaches the engine, but whether the engine's own item-kind
check maps to the right region was never exercised item by item.

## How to test (when it matters)

The engine **drops synthetic input**, so this needs a physical wheel
(`Test/README.md` § "Physical-test sessions" has the rules):

1. Create a test trigger with `mouseOver = <one kind>` and a harmless action
   (e.g. "Show notification" or a `runCommand` that writes to a file — something
   observable, NOT a tab reload that hides which item it was).
2. Open the matching menu: the AutoControl **tab menu** for "Menu item: tab",
   **closed tabs/windows** for 44/45, the **bookmarks tree** for 46/47, an
   **action menu** for 48, a **switch** menu for 51.
3. Wheel over an item of the EXPECTED kind → the action must fire.
4. Wheel over an item of a DIFFERENT kind in the same menu → it must NOT fire.
   This second half is the real test: a too-broad engine check would fire on
   everything.
5. Repeat for each of the 8 kinds. Record the SW console
   (`Test/ac_swlog_act.js` / `ac_swlog_dump.js`) — the gate logs
   `zones=[…] ∩ […] → executing/skipped`, and for menu-only regions it should log
   the "engine-classified regions only" pass-through.

**Evidence to keep:** the region → item-kind pairs that fired and, more
importantly, the negative cases (which kinds did NOT fire while the trigger was
bound to a specific one).

## Why it is low priority

* All of them ride a route that is verified for the umbrella region (40).
* A wrong per-kind match only shows up as "the action ran on a neighbouring item"
  in a menu — noticeable, but not a blocker for normal use.
* Verify on a **user report** rather than pre-emptively; the test costs a physical
  session per kind (8 sessions or one long one).

## References

* `Docs/TODO-mouseover-zones.md` — §1 (the region table), §2g (the engine's own
  menu classification, why the v18 gate was wrong), §2f(d) (the v18 force-match).
* `Docs/NATIVE_PROTOCOL.md` — types 170 / 175 / 185 (menu open / query / detail).
* `Docs/GOTCHAS.md` — the SW gate's menu pass-through rule.
* `Test/mh_test.js` — the gate test asserts the pass-through for menu-only regions.
