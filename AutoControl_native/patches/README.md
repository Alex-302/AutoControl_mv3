# patches/ — turning `original/` into `patched/`

One active patch, one file, deterministic output:

```powershell
# from the repo root (input defaults to ../original/AutoCtrl_2025.4.22.0.exe):
node AutoControl_native/patches/patch_zones_v19.js out.exe

# explicit input:
node AutoControl_native/patches/patch_zones_v19.js out.exe D:\some\pristine.exe

# legacy variant (NOT deployed, see the scope section below):
node AutoControl_native/patches/patch_zones_v19.js out.exe v16      # 8696D276…
```

`v16` is a **flag** and may appear in any position; the other arguments are
positional (`out.exe`, then an optional `in.exe`).

| | |
|---|---|
| input | `../original/AutoCtrl_2025.4.22.0.exe` — sha256 `8AE9A669086BEA5C4344007AC4CA9797E5814285E03B6B04E5F8336329CB7E09`, 695 296 bytes |
| output | sha256 `1A10EDD191B80A806DF66558B2B1E78BE8D6AD81E93EEAC772D13F222E212C3E` (identical to `../patched/AutoCtrl_2025.4.22.0.v19.exe`) |
| changed bytes | **40** — entry jump `0x14AF0..0x14AF4` (file offset), code cave `0x7EBA3..0x7EBA9` + `0x7EBAD..0x7EBC8` |

The script refuses to run if the input is not the exact pristine file (size,
SHA-256, the 5 original bytes at the patch entry and the zeroed cave are all
checked) — so a wrong input can never produce a silently different build.

## What the patch does

The engine's mouse-over region check decides **two** things at once: whether the
trigger fires *and* whether the input is consumed. The original build answers
"does not match" for most browser-chrome regions on Chrome 148+ (so zone
triggers never fire there); the naive fix "always match" (v18) made every wheel
trigger swallow the wheel **everywhere** — pages could no longer be scrolled.

v19 replaces the decision with a **table lookup in the engine's own memory**:

```
  entry (VA 0x4156F0, 5 bytes) -> jmp <cave>
  cave (VA 0x47F7A3, 93 free bytes, read-only filler):
      cmp edx, 28h            ; region id
      jae ORIG                ; >= 40 (AutoControl menu items) -> engine's own logic
      cmp byte [ALIVE], 0     ; is the zone helper running?
      je  NOTALIVE
      mov eax, [edx*4 + TABLE]; table[region] -> 0/1
      ret
  NOTALIVE:
      mov eax, 1              ; helper absent -> behave like v18 (always match)
      ret
  ORIG: original first 5 bytes + jmp back to 0x4156F5
```

`ALIVE` (4-byte flag) and `TABLE` (64 dwords) are absolute addresses that the
zone helper (`ac_zone_helper.exe`) writes into the cave at runtime, together
with the table contents for the zones under the cursor. Consequences:

- **helper absent** → engine behaves like v18 (old, always-match) — never faults;
- **helper running** → the zone under the cursor decides, so wheel-over-page
  passes through and wheel-over-a-tab fires (the service worker re-checks the
  answer before executing the trigger).

Byte-level walkthrough, addresses and the runtime layout:
`Docs/BUILD-NATIVE.md` §B.

### Why this injected code is legal (the ABI it relies on)

Everything below is verifiable in `Test/native-disasm/` — see the exact files.

| Fact | Where it comes from |
|---|---|
| `FUN_004156f0` is `uint __fastcall (POINT *param_1, uint param_2, HWND param_3)` — MSVC fastcall puts **ECX = param_1**, **EDX = param_2** (the region id), and the caller **pushes** `param_3` | `decomp/004156f0_FUN_004156f0.c:3` (signature) + its body: `switch(param_2) { case 3: … case 4: case 10: case 0x14: … }` |
| The patch overwrites the **first 5 bytes of the function body** — `83 EC 20` (`sub esp,20h`), `53` (`push ebx`), `55` (`push ebp`) — i.e. the prologue. The trampoline therefore runs **before any register is clobbered**, so `EDX` still holds the region and `ECX` the point | `decomp/004156f0_FUN_004156f0.c` (the `local_20`/`local_10` RECT locals explain the `sub esp,0x20`) |
| The return value is **EAX** (`0` = "cursor is not over this region", `1` = "it is") | same signature (`uint`) |
| A plain `ret` on the early-return paths is safe: the callee-saved registers were never pushed (the prologue is skipped) and the caller cleans the pushed argument — `add esp,4` right after the `call` | `decomp/00415b40_FUN_00415b40.c:41` |
| **The whole fix depends on this one caller**: it does `uVar5 = FUN_004156f0(...); return uVar5;` — the matcher's answer IS what the input handler uses, i.e. **match == consume**. That is why "always match" (v18) swallowed the wheel everywhere | `decomp/00415b40_FUN_00415b40.c:41-42`; the export even records the count: `functions.csv` → `004156f0;FUN_004156f0;1034;1` |
| `ORIG:` re-executes the 5 displaced bytes and jumps to `0x4156F5`, so the engine's own logic runs **byte-identically** | the entry jump is `E9 <rel32>` → cave; the cave tail is `83 EC 20 53 55` + `E9 <rel32>` → `0x4156F5` |
| Region ids ≥ `0x28` (40) are handed back to the engine because those are the **AutoControl menu items**, which the external helper cannot see (the menu is drawn by the engine itself) | `cmp edx,28h; jae ORIG` + the engine's own `switch(param_2)`/`param_2 - 0x3c` menu branch in `decomp/004156f0_FUN_004156f0.c` |
| `TABLE` has 64 slots although only regions < 40 reach the lookup — headroom so that `[edx*4]` can never run past the page even if the bound check is ever changed | `Test/ac_zone_helper.cs` (`WriteZoneTable`) |

The ABI is **not taken on faith from the decompiler**: the same facts are
visible in the instruction stream of the pristine engine (regenerate with
`Test/AbiDump.java` — Ghidra headless, `-noanalysis`; the "no other reference"
fact is **checked** by `node Test/engine_abi_dump.js`, which exits 1 unless the
cave page is mapped *and* executable, the matcher has exactly one direct caller
and no other reference to its address exists anywhere in the file). The
`MOV ESI,EDX` / `MOV EBX,ECX` pair is what proves which register carries which
argument:

```
004156f0  83 ec 20                 SUB ESP,0x20        ; <- the 5 bytes the patch replaces
004156f3  53                       PUSH EBX
004156f4  55                       PUSH EBP
004156f5  56                       PUSH ESI            ; and the body continues here (0x4156F5)
004156f6  8b f2                    MOV ESI,EDX         ; EDX = 2nd argument = the REGION
004156f8  8b d9                    MOV EBX,ECX         ; ECX = 1st argument = the POINT*
004156fa  57                       PUSH EDI
004156fb  8d 46 fd                 LEA EAX,[ESI + -0x3]
004156fe  83 f8 11                 CMP EAX,0x11
00415701  77 5c                    JA 0x0041575f
00415703  0f b6 80 08 5b 41 00     MOVZX EAX,byte ptr [EAX + 0x415b08]
0041570a  ff 24 85 fc 5a 41 00     JMP dword ptr [EAX*0x4 + 0x415afc]   ; switch (region)
```

and in its only caller, around the call site (`0x415BDC`):

```
00415bd7  56                       PUSH ESI            ; param_3 (HWND) -> on the STACK
00415bd8  8b d7                    MOV EDX,EDI         ; param_2 = the region
00415bda  8b cb                    MOV ECX,EBX         ; param_1 = the POINT
00415bdc  e8 0f fb ff ff           CALL 0x004156f0
00415be1  83 c4 04                 ADD ESP,0x4         ; the CALLER cleans the pushed arg
00415be4  5f                       POP EDI             ; ...and relies on callee-saved regs
00415be5  5e                       POP ESI
00415be6  5b                       POP EBX
00415be7  83 c4 08                 ADD ESP,0x8
00415bea  c3                       RET                 ; EAX (the matcher's answer) returned unchanged
```

Four more facts checked the same way (2026-09-13):

* **the region really is the switch value** — the jump table at `0x415AFC` is
  indexed by `ESI`, which the prologue loaded from `EDX`;
* **nothing else can call the matcher** — the absolute address `0x004156F0`
  occurs **nowhere** in the file (0 raw dword occurrences, 0 relocation
  entries) and there is exactly **one** `E8` call to it (at `0x415BDC`), so
  "the only caller" is a byte-level fact, not an estimate;
* **the trampoline is executable** — the cave (image RVA `0x7F7A3` = `.text`
  `+0x7E7A3`) sits inside the section's raw data but past its *virtual* size,
  i.e. in the last **mapped** page, which inherits the section's `r-x`
  permission (`Test/engine_abi_dump.js` → `executable=true`);
* **the early `ret` is safe** — the fast path of the trampoline touches
  **only `EAX` and the flags** (no callee-saved register), which is what makes
  the caller's `POP EDI / POP ESI / POP EBX` correct; the caller's `ADD ESP,4`
  removes the argument it pushed, and the `ORIG:` path re-enters the untouched
  original epilogue (`ADD ESP,0x20; RET`).

The complete encoding of what the patch writes, byte by byte:

```
entry @ file 0x14AF0  (5 bytes)   E9 AE A0 06 00          jmp 0x47F7A3   (rel32)

cave  @ file 0x7EBA3  (38 bytes, 93 free bytes available)
  +00  83 FA 28                    cmp  edx, 28h            ; region (2nd fastcall arg)
  +03  73 17                       jae  +0x1C (ORIG)        ; >= 40 -> the engine's own logic
  +05  B8 01 00 00 00              mov  eax, 1              ; fallback: always match
  +0A  C3                          ret                      ; EAX = 1
  +0B  90 ×17                      nop padding (unused in this variant)
  +1C  83 EC 20 53 55              ORIG: the 5 displaced bytes (sub esp,20h; push ebx; push ebp)
  +21  E9 2C 5F F9 FF              jmp  0x4156F5            ; rel32 = 0x4156F5 - 0x47F7C9
```

and the variant the helper writes over bytes `+00..+1B` while it runs:

```
  +00  83 FA 28                    cmp  edx, 28h
  +03  73 17                       jae  +0x1C (ORIG)
  +05  80 3D <ALIVE> 00            cmp  byte [ALIVE], 0     ; is the helper alive?
  +0C  74 08                       je   +0x16 (NOTALIVE)
  +0E  8B 04 95 <TABLE>            mov  eax, [edx*4 + TABLE]; EAX = table[region]
  +15  C3                          ret
  +16  B8 01 00 00 00              NOTALIVE: mov eax, 1     ; helper gone -> old behaviour
  +1B  C3                          ret
```

(`<ALIVE>`/`<TABLE>` are absolute addresses the helper computes from the live
module base — the file itself contains no absolute address, so ASLR is safe.)

## Proof of safety — the assembly IS the bytes

The concern with any hand-written byte patch is: *does the injected code really
mean what the comment above it says?* Two independent checks answer that, and
both are reproducible.

### 1. Independent decoder (`Test/patch_bytes_verify.js`)

```powershell
node Test/patch_bytes_verify.js                        # the deployed engine
node Test/patch_bytes_verify.js <any-engine.exe> --orig <original.exe>
```

It decodes the actual bytes with a **strict** mini-decoder (only the instruction
forms this patch is allowed to contain — anything unexpected is an error, never
"close enough"), prints an annotated listing, and then asserts:

* the 5 entry bytes are a `jmp` **and** it lands on the cave;
* the file prefix is **byte-identical** to the documented fallback;
* the runtime prefix decodes to exactly `cmp edx,28h / jae ORIG / cmp byte
  [alive],0 / je NOTALIVE / mov eax,[edx*4+table] / ret / mov eax,1 / ret`;
* `jae` lands **exactly** on ORIG (`cave+0x1C`), `je` on NOTALIVE (`cave+0x16`),
  and the tail `jmp` on `ENTRY+5` — a one-byte error here would be silent at
  runtime;
* the runtime prefix is exactly `0x1C` bytes, i.e. it can never clobber the
  displaced original bytes;
* **no byte outside the 3 documented ranges differs from the original**, and
  each documented range really does differ (a stale range would mask a change).

Exit code 0 and `PROOF HOLDS: …` means all of the above held.

### 2. Independent disassembler (Ghidra)

`ghidra-disasm.txt` in this folder is Ghidra 12.1.3's own disassembly of the
same bytes, produced by `Test/DisasmPatch.java` (headless, no auto-analysis) —
a different program, a different code path, no shared logic with the decoder.
Cross-check (2026-09-13): both tools agree on **all 34 instructions**, byte for
byte. Ghidra names `jae`/`je` as `JNC`/`JZ` (same opcodes 0x73/0x74).

This listing is a **frozen artifact** (nothing regenerates it), so the harness
now PARSES it and requires its bytes to be the bytes of the current build
(`mh_test.js` B53g, 34 instructions included) — a stale listing fails the suite
instead of quietly contradicting the binary.

### What the two together prove

| Question | Answer | Evidence |
|---|---|---|
| Is the 5-byte entry a jump to the cave? | yes, `JMP 0x0047f7a3` | both listings |
| Does the cave start with the region check? | yes, `CMP EDX,0x28` (EDX = region, see the ABI section) | both listings |
| Are the two branch targets exact? | yes: `+0x1C` (ORIG) and `+0x16` (NOTALIVE) | decoder assertions + both listings |
| Does the patch fall back safely without the helper? | yes: `MOV EAX,1; RET` — matches v18 behaviour, reads **no** memory, cannot fault | file variant listing |
| Does the runtime version read memory only where intended? | yes: exactly 2 memory accesses (alive flag, table slot) | decoder assertions + listing |
| Can the injected prefix damage the displaced prologue? | no: it is exactly `0x1C` bytes and the opcodes are `SUB ESP,0x20 / PUSH EBX / PUSH EBP / JMP 0x4156F5` after it | both listings |
| Was anything **else** modified? | no: 40 bytes differ from the original, all inside the 3 ranges | decoder byte-diff + `Docs/BUILD-NATIVE.md` §B.1 |

> The check is part of the test harness (`mh_test.js` B53d), so the claim cannot
> silently rot: any change to the patch script that breaks one of the
> assertions fails the suite.

### 2b. The runtime variant is simulated — and that simulation is checked too

The bytes that actually execute while the zone helper runs are not in the file:
the helper writes them from its own C# copy of the layout. Both the verifier and
`DisasmPatch.java` therefore *simulate* them, which would stay green even if the
helper drifted away from the simulation. `mh_test.js` **B53f** closes that gap:
it rebuilds the helper's `npre[]` array **from `Test/ac_zone_helper.cs`** and
requires byte equality with the verifier's `runtimePrefix()`:

```
helper (from source) : 83fa287317803d<alive>0074088b0495<table>c3b801000000c3
verifier (simulated) : 83fa287317803d<alive>0074088b0495<table>c3b801000000c3
```

### 3. The proof has teeth (mutation test)

A proof that always passes is worthless, so the suite also **mutates** copies of
the build and requires the verifier to reject each one (`mh_test.js` B53e):

| Mutation | Detected by |
|---|---|
| `jae` offset `0x17` → `0x18` (the branch would land mid-instruction) | FILE-prefix comparison |
| fallback `mov eax,1` → `mov eax,2` | FILE-prefix comparison |
| one byte changed at `0x1000` (outside the documented ranges) | byte diff |
| the entry bytes no longer decode to a single `jmp` | entry check |

All four are rejected with exit code 1 (verified 2026-09-13). This is how a real
defect was caught while building the proof: the verifier's argument parsing
excluded the file name when `--orig` was absent, so it silently verified the
**deployed** engine while a mutated file was passed in — the mutation test
showed "PROOF HOLDS" for a broken binary and the bug was fixed.

### 4. The proof cannot be weakened by accident

The verifier no longer accepts half a proof:

| Situation | Behaviour |
|---|---|
| pristine original missing | `PROOF FAILED` (exit 1) — pass `--orig <pristine.exe>` or state explicitly that you want the weaker check with `--no-diff` |
| `--no-diff` passed | the decode half runs, the diff half is skipped, and the result is printed as `PROOF HOLDS (PARTIAL)` — it never pretends to be the full proof |
| the DEFAULT original is not the pinned pristine build | `PROOF FAILED` (the diff half would be meaningless) |

### 5. What the proof does NOT cover

The proof is about **bytes vs documentation**, the ABI they rely on, and
"nothing else changed". It says nothing about design-level behaviour:

* the helper's page is allocated **inside the engine** (`VirtualAllocEx`), so it
  survives the helper's death with `alive = 1` and a stale table — the
  `je NOTALIVE` branch of the runtime variant is therefore practically
  unreachable, and after the helper dies the *consumption* decision can briefly
  use stale data while the worker's 2.5 s keepalive re-spawns it. The worker's
  own gate fails **closed** (a missing answer means "no match" → the action is
  skipped); only menu-item-only triggers ride the engine's verdict;
* the file variant (helper never started) is v18 behaviour: safe (it reads no
  memory and cannot fault) but not selective — it lasts until the helper writes
  the table;
* the **target** of the helper's page write is not checked. The layout *inside*
  that page (alive dword at `+0`, slot dwords from `+16`) is pinned by B53f/B53g
  — but only through the cave prefix. Nothing parses `WriteMem(h, engTable,
  data)` in `Test/ac_zone_helper.cs`, so a wrong target (e.g. `engTable + 16`)
  would pass every static check while the cave reads a garbage alive flag →
  "always match" (v18) → the "pages stop scrolling" symptom. Loud at runtime and
  covered by the live zone suite (`Test/zone-tests/`), not by this proof;
* B53f parses the helper's **C# source**, not the compiled binary — the link to
  what actually runs is the deterministic Roslyn build plus the SHA-256 check in
  `Test/build_native.ps1` (the IL itself is never disassembled).

These are inherent to the design, not to the encoding — grep this file before
quoting the proof as "the patch is safe".

## Scope — what this patch does and does NOT contain

**This script is the complete description of the current engine state.** Running
it with no extra arguments on `../original/` reproduces the deployed engine
**byte for byte** (0 differences out of 695 296 bytes — verified 2026-09-13
against `%LOCALAPPDATA%\AutoControl\AutoCtrl_2025.4.22.0.exe`).

| | |
|---|---|
| **included** (40 bytes) | the entry jump + the code cave — nothing else differs from the original |
| **optional, NOT applied** | `node patch_zones_v19.js <out> v16` adds two 2026-09-01 NOPs (zone-12 window gate + role check) → `8696D276…`. Measured 2026-09-12: with them the engine consumes the wheel **everywhere** again (pages stop scrolling) — do not pass `v16` |
| **not included, not needed** | the accName patch of the v2–v4 line (`Test/patch_accname.js`): the zone helper queries `get_accName` itself, which switches Chrome's accessibility tree on browser-wide. The 40-byte diff above proves no other change is present |
| **not part of this component** | `ac_zone_helper.exe` — a separate program built from `Test/ac_zone_helper.cs` (`Test/build_native.ps1` covers both) |

The file contains the **helper-absent fallback** in the cave (always-match, no
memory reads). The real behaviour comes from the helper rewriting bytes
`0x00..0x1B` of the cave **in memory** while it runs — the on-disk file never
changes at runtime:

```
file   (this script)  : 83 fa 28 73 17 b8 01 00 00 00 c3 90 …      (fallback)
memory (helper writes): 83 fa 28 73 17 80 3d <alive> 00 74 08 8b 04 95 <table> c3 …  (table)
```

## Verifying without Windows tooling

```powershell
Get-FileHash out.exe -Algorithm SHA256   # must be 1A10EDD1...
```

Prove that the **installed** engine is exactly this build (byte diff, no
tooling beyond PowerShell):

```powershell
$a=[IO.File]::ReadAllBytes('AutoControl_native\original\AutoCtrl_2025.4.22.0.exe')
$b=[IO.File]::ReadAllBytes("$env:LOCALAPPDATA\AutoControl\AutoCtrl_2025.4.22.0.exe")
(0..($a.Length-1) | Where-Object { $a[$_] -ne $b[$_] }).Count    # -> 40
```

or, for both components at once:

```powershell
powershell -ExecutionPolicy Bypass -File Test\build_native.ps1
```
