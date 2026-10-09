# native-disasm — Ghidra export of the AutoControl engine

**What this is:** the Ghidra export of the ENGINE binary (`AutoCtrl_2025.4.22.0.exe`,
the pristine original) from the 2026-08-31 headless run:

```
Test/native-disasm/
├── decomp/            1939 × '<addr>_FUN_<addr>.c'  — the decompiled code
├── functions.csv      addr;name;size;callers        — the INDEX (fast lookups!)
├── imports.txt        imported OS APIs, per DLL
├── strings.txt        'addr len "text" refs: FUN_x@addr'
├── sections.txt       PE section layout
└── README.md          this file
```

It is the **fastest way to read the engine's logic** without re-running Ghidra.

**Why keep it in the repository:** the engine is abandoned and we patch it by
hand (`AutoControl_native/patches/`). Every address in `Docs/BUILD-NATIVE.md`
and every conclusion in `Docs/archive/NATIVE-REVERSING-2026-08-31.md` is
verifiable against these files — e.g. the patched region classifier:

| Address | File (in `decomp/`) | Why it matters |
|---|---|---|
| `0x004156F0` | `004156f0_FUN_004156f0.c` | **the mouse-over region matcher** — the function the v19 patch trampolines (`cmp edx,28h; jae ORIG; …`) |
| `0x00415B40` | `00415b40_FUN_00415b40.c` | its ONLY caller — `return FUN_004156f0(...)` == the match/consume decision |
| `0x00415660`, `0x00415570`, `0x00414760` | same naming | the classifier/zone-gate chain discussed in the RE doc §10–§12 |
| `0x0040b610`, `0x0040daf0`, `0x0040bdf0` | same naming | hover-cache refresh, honey-pot (`WM_GETOBJECT` lParam=1) and the name-query helper |

Grep for a function by its address, e.g.
`Select-String -Path Test/native-disasm/decomp/*.c -Pattern 'FUN_004156f0'`.

## Fast lookups (verified 2026-09-13 — use these FIRST)

The export is more than the `.c` files; three of its files answer structural
questions in one command and would have saved real time in the 2026-09-12
session:

| File | Format | Answers |
|---|---|---|
| `functions.csv` | `addr;name;size;callers` | **who calls what** (`callers` column!) and how big a function is |
| `imports.txt` | per DLL | which OS APIs the engine uses (MSAA story: `OLEACC.DLL` → `AccessibleObjectFromPoint`, `AccessibleChildren`, `AccessibleObjectFromWindow`, `AccessibleObjectFromEvent`… and **no `get_accName`** — exactly why Chrome's a11y tree never switches on) |
| `strings.txt` | `addr  len  'text'  refs: FUN_x@addr` | string → using function |

Concrete results from these files:

```powershell
# the region matcher has EXACTLY ONE caller (the "its return value is the
# decision" fact that cost a PE call-site scan + a live regression):
Select-String -Path Test/native-disasm/functions.csv -Pattern '004156f0'
#   004156f0;FUN_004156f0;1034;1

# ... and that caller simply RETURNS its result, i.e. match == consume:
#   Test/native-disasm/decomp/00415b40_FUN_00415b40.c:41
#     uVar5 = FUN_004156f0(param_1,param_2,hWnd);
#     return uVar5;

# the code cave is bounded by the last function of .text:
Select-String -Path Test/native-disasm/functions.csv -Pattern '^0047f' | Select-Object -Last 1
#   0047f799;FUN_0047f799;10;1     -> ends at 0x47F799 + 10 = 0x47F7A3 == CAVE
```

And `decomp/004156f0_FUN_004156f0.c` contains the engine's own region switch —
the constant set behind the whole `v5b…v17g` patch series:

```c
switch(param_2) { … }              // param_2 == the region id
this = (uint *)(param_2 - 0x3c);   // region >= 60 -> the AutoControl MENU branch
if (param_2 == 0x15) …             // 0x15 = 21  Omnibox
if (param_2 == 0x1e) …             // 0x1e = 30  browser-menu button
bVar15 = *piVar5 == 0x25;          // 0x25 = 37  the role the engine wants for a tab
```

### What the export can NOT tell you (why the live tests were still needed)

These cost most of the 2026-09-12 session and are **invisible in static code**:

- the hover cache inside `FUN_0040b610` **never refreshes** over the tab strip
  (only a live type-792 probe showed it);
- a fresh `AccessibleObjectFromPoint` **deadlocks** when called from the
  low-level input hook thread (the call looks harmless in the decompiler);
- Chrome's MSAA tree **sleeps** after ~30 s (→ every point answers "PANE")…
  and which role Chrome actually reports (41 for a tab, not the 37 the engine
  wants) is a runtime fact;
- a dead mouse hook after `taskkill /F` produces the exact symptoms of "zone
  not detected";
- "the SW must ping the helper proactively" (chicken-and-egg: the engine drops
  the 750s whose zone it cannot classify).

Rule of thumb from that session: **static export for "what are the constants,
who calls whom, which APIs are used"; live probing for "what does the system do
at runtime".**
> only differs in the 40 bytes listed in `Docs/BUILD-NATIVE.md` §B.1 (a 5-byte
> jump at `0x4156F0` + the code cave at `0x47F7A3`), so everything else in this
> export still applies to the patched engine.

## Regenerating (only if the export is ever lost)

Ghidra headless, with the Java post-scripts in `Test/` (`DumpMsaa*.java`,
`DumpRegions*.java`, `FullDump.java` — **PyGhidra is not available in this
setup**, so scripts must be Java):

```
analyzeHeadless <project-dir> AutoCtrl -import AutoCtrl_2025.4.22.0.exe -overwrite \
  -scriptPath Test -postScript FullDump.java
```

The Ghidra project used for the 2026-08-31 session lived *outside* the repo
(`E:\Temp\ac_ghidra`), so the export here is the durable artifact.

## Related tools (NOT a substitute)

| Tool | Difference |
|---|---|
| `Test/engine_abi_dump.js` | PE headers / sections / call sites / padding — structure, not logic |
| `Test/engine_find_cave.js` | finds the zero-padding code cave used by the v19 patch |
| `Test/engine_zone_write.ps1` | inspects/writes the runtime zone table in a **running** engine |
