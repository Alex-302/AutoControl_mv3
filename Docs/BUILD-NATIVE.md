# Building the native parts bit-for-bit

This document is the authoritative recipe for reproducing the **two native
components** of this port from their inputs:

| Component | Input | Output (deployed) |
|---|---|---|
| **Zone helper** (`ac_zone_helper.exe`) | our C# source `Test/ac_zone_helper.cs` | size **16384**, sha256 `6988B49BCBEC162CE03EFDC94F789F17AFC28C98EC890E7B26FCF0E464F262E6` (deterministic build) |
| **Patched engine** (`AutoCtrl_2025.4.22.0.v19.exe`) | `AutoControl_native/original/AutoCtrl_2025.4.22.0.exe` (untouched upstream) | size **695296**, sha256 `1A10EDD191B80A806DF66558B2B1E78BE8D6AD81E93EEAC772D13F222E212C3E` |

Everything below was verified on 2026-09-12 by rebuilding and comparing hashes
(the engine: **bit-identical**; the helper: bit-identical with the Roslyn recipe
in §A.2 — the legacy compiler in §A.3 is *not* reproducible, see the warning
there).

> **Rule of thumb.** The engine is reproduced by a **byte patch of the original
> binary** (nothing is recompiled — AutoControl is closed-source); the helper is
> **our own program** and is reproduced by **compiling its source**. Both outputs
> are content-verified by SHA-256, so "does it match what we ship?" is a single
> hash comparison.

---

## A. Zone helper — `ac_zone_helper.exe` (our own source)

A single-file C# console program (~34 KB) that speaks the Chrome
**native-messaging frame** on stdio. It classifies the browser zone under the
cursor with MSAA (no hooks, no injection) and maintains the engine's zone table.

### A.1 Prerequisites

* Windows, .NET Framework 4.x runtime (present on every Windows 10/11).
* **Roslyn compiler** — ships with the .NET SDK:
  `C:\Program Files\dotnet\sdk\<version>\Roslyn\bincore\csc.dll`
  (verified with 8.0.422). Install with `winget install Microsoft.DotNet.SDK.8`
  if missing.
* Reference assemblies are taken **from the Framework directory** (no NuGet, no
  project file, no MSBuild needed):
  `C:\Windows\Microsoft.NET\Framework64\v4.0.30319\{mscorlib,System,Accessibility}.dll`
  (`Accessibility.dll` is the MSAA interop assembly — the only non-trivial
  reference).
* Source: `Test/ac_zone_helper.cs` (uses only `System`, `System.IO`,
  `System.Runtime.InteropServices`, `Accessibility`).

### A.2 Deterministic build (recommended)

⚠ **The `/out:` file NAME is part of Roslyn's deterministic hash** (the debug
directory records the PDB path). Always build to the same file name —
`ac_zone_helper.exe` — otherwise the resulting bytes differ even though the code
is identical.

```powershell
Set-Location <repo root>

$fw   = "C:\Windows\Microsoft.NET\Framework64\v4.0.30319"
$csc  = "C:\Program Files\dotnet\sdk\8.0.422\Roslyn\bincore\csc.dll"
$out  = "$env:TEMP\ac_rebuild\ac_zone_helper.exe"     # keep this name fixed
New-Item -ItemType Directory -Force (Split-Path $out) | Out-Null

dotnet $csc /nologo /optimize+ /deterministic+ /nostdlib+ `
  /r:"$fw\mscorlib.dll" /r:"$fw\System.dll" /r:"$fw\Accessibility.dll" `
  /out:"$out" Test\ac_zone_helper.cs

Get-FileHash $out -Algorithm SHA256      # must print 6988B49B... (see the table above)
```

Notes:

* `/nostdlib+` + explicit `mscorlib` is what makes a Framework-only build
  possible without reference assemblies.
* `/deterministic+` removes the compiler timestamp; two runs to the same
  `/out:` name produce **identical bytes** (verified twice).
* The build is warning-free; any error means the source or a reference is wrong.

### A.3 Legacy build (what was deployed on 2026-09-12)

Before the deterministic recipe above, the helper was built with the .NET
Framework compiler:

```powershell
& "C:\Windows\Microsoft.NET\Framework64\v4.0.30319\csc.exe" /nologo /optimize+ `
  /r:"C:\Windows\Microsoft.NET\Framework64\v4.0.30319\Accessibility.dll" `
  /out:"$env:TEMP\ac_rebuild\ac_zone_helper.exe" Test\ac_zone_helper.cs
```

⚠ **This compiler is NOT reproducible**: two runs of the very same command
differ in ~4.6 KB of metadata (MVID/heap ordering); the legacy file
(`493A7276FA87BEA3…`, size 15872) therefore cannot be re-derived bit-for-bit
from the source. It is functionally equivalent to the deterministic build
(both answer the smoke test identically). Use §A.2 for anything new.

**Status 2026-09-12:** the deployed helper IS the deterministic §A.2 build
(`6988B49B…`); the legacy one was renamed to
`ac_zone_helper.exe.bak-493A7276` in `%LOCALAPPDATA%\AutoControl\`.

### A.4 Verify the build before installing

The smoke test speaks the native-messaging frame to the exe and prints its
answer; it accepts an explicit path, so a fresh build can be checked *before*
deployment:

```powershell
node Test/zone_helper_smoke.js $env:TEMP\ac_rebuild\ac_zone_helper.exe
# expected: RESP: {"__id":7,"zone":1,"zones":[1]}
node Test/zone_helper_smoke.js          # same test against the DEPLOYED copy
```

`zone:1 / zones:[1]` is the correct answer when the caller is not a browser
(the helper's "own browser" gate then imposes no restriction). The zone value
itself depends on where the cursor is; the point of the test is that the
process starts, parses the frame and answers.

### A.5 Install / update

```powershell
# 1. the copy the native-messaging manifest points at
Copy-Item $env:TEMP\ac_rebuild\ac_zone_helper.exe `
          "$env:LOCALAPPDATA\AutoControl\ac_zone_helper.exe" -Force

# 2. the copy that ships with the repo (keep them identical)
Copy-Item $env:TEMP\ac_rebuild\ac_zone_helper.exe `
          "AutoControl_native\ac_zone_helper.exe" -Force

# 3. registration (once per machine, per browser variant). The manifest's
#    `path` is relative, so ac_zone_helper.exe must sit NEXT TO the JSON.
#    (PowerShell: `$env:LOCALAPPDATA` expands; `%LOCALAPPDATA%` would be
#    written to the registry literally outside cmd.exe.) User-facing
#    duplicate: README §4.1 step 6.
reg add "HKCU\Software\Google\Chrome\NativeMessagingHosts\com.autocontrol.zonehelper" /ve /t REG_SZ /d "$env:LOCALAPPDATA\AutoControl\com.autocontrol.zonehelper.json" /f
```

Then **reload the extension** (chrome://extensions → Reload): Chrome kills the
old helper together with the native port and the SW starts a fresh one. Live
checks:

* `%TEMP%\ac_zone_helper.log` starts growing again with
  `table write: alive=1 zones=[...]` lines (written every ~1.2 s, faster while
  the cursor moves);
* the SW pings the helper every 2.5 s from boot (`__acZoneAsk(300)` in `sw.js`);
* the engine's zone table becomes non-zero (see §B.5 –
  `powershell -File Test/engine_zone_write.ps1 -Dump`).

### A.6 Source invariants (do not "clean up" these)

`mv3-build/mh_test.js` (B53) pins the parts that took the longest to find:

| Invariant | Why |
|---|---|
| `CAVE_RVA = 0x7F7A3`, `ORIG_BLOCK = 0x1C`, `npre[21] = 0xC3`, `npre[23] = 1`, `npre[27] = 0xC3` | the exact engine-cave layout (off-by-one here silently corrupts the table address — it cost a full evening) |
| the helper always calls `VirtualAllocEx` and claims the cave | an older build reused the address found in the cave and wrote into foreign memory |
| `TabButtonZone` + `hitLeft >= maxLeft` | the speaker icon is not hit-testable; the close button is the **rightmost** child of the tab |
| `inToolbar \|\| stripNear \|\| isTabBtn` | "Title area" = the whole top band |
| `bool ui = !inPage` | a page's ARIA roles (tablist/input/toolbar) must not be read as browser chrome |
| `browserPid` / `IsBrowserName` | zones are reported only for the browser that spawned the helper (VS Code is a `Chrome_WidgetWin_1` window with no a11y tree) |
| `Heartbeat` + `CacheStore` | Chrome's a11y tree sleeps after ~30 s; the heartbeat + 400 ms cache keep it awake and the answers stable |
| `SetProcessDPIAware()` in `Main` | MSAA rects are physical pixels; without it the window rect is DPI-virtualized |

---

## B. Patched engine — bit-for-bit

The engine is **not recompiled**: the original binary is patched in place, and
the patched file has the **same size** as the original.

### B.1 Inputs and hashes

```
original : AutoControl_native\original\AutoCtrl_2025.4.22.0.exe   (the repo copy)
           == %LOCALAPPDATA%\AutoControl\AutoCtrl_2025.4.22.0.exe.orig-pristine
           size   695296
           sha256 8AE9A669086BEA5C4344007AC4CA9797E5814285E03B6B04E5F8336329CB7E09

patched  : AutoControl_native\patched\AutoCtrl_2025.4.22.0.v19.exe  (the repo copy)
           == %LOCALAPPDATA%\AutoControl\AutoCtrl_2025.4.22.0.exe  (v19, deployed)
           size   695296
           sha256 1A10EDD191B80A806DF66558B2B1E78BE8D6AD81E93EEAC772D13F222E212C3E

patched  : %LOCALAPPDATA%\AutoControl\AutoCtrl_2025.4.22.0.exe  (deployed = the repo copy)
           size   695296
           sha256 1A10EDD191B80A806DF66558B2B1E78BE8D6AD81E93EEAC772D13F222E212C3E

differing bytes: exactly 40
  file 0x14AF0 .. 0x14AF4   (5 bytes)   entry jump
  file 0x7EBA3 .. 0x7EBA9   (7 bytes)   cave bytes 0x00..0x06
  file 0x7EBAD .. 0x7EBC8   (28 bytes)  cave bytes 0x0A..0x25
```

`AutoControl_native/patches/patch_zones_v19.js` **refuses to build** unless the
source file is that exact original (size + SHA-256 checked) and the expected
original bytes are found — so the recipe cannot silently patch an
already-patched or a foreign binary. Its input is the repo copy by default
(`../original/AutoCtrl_2025.4.22.0.exe`); pass an explicit path as the second
argument to use something else.

### B.2 Address translation (RVA → file offset)

```
.text section:  VA 0x00001000   virtual size 0x0007E7A3
                raw 0x00000400  raw size     0x0007E800
=> file offset = RVA - 0xC00      (0xC00 = 0x1000 - 0x400)
```

| name | VA | RVA | file offset |
|---|---|---|---|
| classifier entry `FUN_004156f0` | `0x004156F0` | `0x156F0` | `0x14AF0` |
| code cave (`.text` tail padding) | `0x0047F7A3` | `0x7F7A3` | `0x7EBA3` |

The cave sits exactly at the end of `.text`'s *virtual* size, i.e. in the last
mapped page of the section (93 zero bytes of padding, measured with
`Test/engine_find_cave.js` / `Test/engine_abi_dump.js`). The page is mapped
because the section's virtual size extends into it, and it inherits the
section's execute permission — that is what makes the trampoline legal.

### B.3 Patch 1 — entry jump (5 bytes at file `0x14AF0`)

```
original: 83 EC 20 53 55        sub esp,20h ; push ebx ; push ebp
patched : E9 AE A0 06 00        jmp 0x47F7A3
```

`rel32 = 0x47F7A3 - (0x4156F0 + 5) = 0x6A0AE` → little-endian `AE A0 06 00`.

### B.4 Patch 2 — the code cave (38 bytes at file `0x7EBA3`)

The cave is **pre-filled in the file** with the *helper-absent* variant (A) so
an engine started without the helper behaves like v18 (always match, and it can
never fault — it reads no memory):

```
offset  bytes                     meaning
0x00    83 FA 28                  cmp  edx, 28h          ; region id
0x03    73 17                     jae  ORIG              ; >= 40 -> engine's own logic
0x05    B8 01 00 00 00            mov  eax, 1            ; helper absent -> match
0x0A    C3                        ret                    ; eax = match
0x0B    90 x 17                   nop padding
0x1C    83 EC 20 53 55            ORIG: the original first 5 bytes of the function
0x21    E9 2C 5F F9 FF            jmp  0x4156F5          ; rel32 = 0x4156F5 - 0x47F7C9
```

At runtime the **helper rewrites bytes `0x00..0x1B`** with the table variant
(the rest of the cave is never touched):

```
0x00    83 FA 28                  cmp  edx, 28h
0x03    73 17                     jae  ORIG              ; menu regions keep the engine's logic
0x05    80 3D <ALIVE> 00          cmp  byte [ALIVE], 0   ; is the helper running?
0x0C    74 08                     je   NOTALIVE
0x0E    8B 04 95 <TABLE>          mov  eax, [edx*4 + TABLE]
0x15    C3                        ret                    ; eax = table[region] (0/1)
0x16    B8 01 00 00 00            NOTALIVE: mov eax, 1   ; fall back to "always match"
0x1B    C3                        ret
```

`<ALIVE>` and `<TABLE>` are absolute addresses computed by the helper from the
live module base (ASLR-safe: the file variant has no absolute addresses at all).

**Why the early `ret` is correct:** the caller cleans the pushed argument
(`add esp,4` immediately after the `call`) — the function uses no callee-saved
register before the trampoline returns, so `eax` alone carries the result.

### B.5 The runtime zone table (what the helper writes into the process)

```
page (VirtualAllocEx, PAGE_READWRITE, owned by the helper):
  +0x00  alive   dword                          1 while the helper lives
  +0x10  table   64 dwords, table[region] = 1   "the cursor is over this region"
```

* `table[region] == 1` → the mouse-over precond matches → the trigger may fire
  **and** the input is consumed (that is the same decision inside the engine).
* `table[region] == 0` → no match → the input passes through (the page scrolls).
* `alive == 0` (helper down) → the file's variant-A code answers `1` — the
  extension keeps working, sacrificing the zone selectivity (v18 behaviour).

Manual inspection/writing without the helper
(`Test/engine_zone_write.ps1`; stop the helper first — otherwise it overwrites
your values within ~1 s):

```powershell
powershell -File Test/engine_zone_write.ps1 -Dump            # cave + alive + table
powershell -File Test/engine_zone_write.ps1 -Zones "12,4,1"  # mark regions
powershell -File Test/engine_zone_write.ps1 -Diag            # diagnostic cave: records asked-for ids
```

### B.6 Build & verify

```powershell
Set-Location <repo root>
node AutoControl_native/patches/patch_zones_v19.js "$env:TEMP\ac_rebuild\AutoCtrl_2025.4.22.0.exe"
```

Expected output (this is the deployed build):

```
size   : 695296
sha256 : 1A10EDD191B80A806DF66558B2B1E78BE8D6AD81E93EEAC772D13F222E212C3E
entry  : e9aea00600  (jmp cave 0x47f7a3)
cave   : 83fa287317b801000000c3909090909090909090909090909090909083ec205355e92c5ff9ff
```

Verification checklist:

1. `Get-FileHash` of the built file == the hash above (bit-for-bit).
2. Byte-diff against the pristine must show exactly the three ranges of §B.1.
3. `node mv3-build/mh_test.js` → B53b–B53g check the cave layout constants
   (`ORIG_BLOCK = 0x1C`, the `ret` positions), the helper's writer, the docs and
   the Ghidra listing.
4. **Assembly ⇄ bytes proof** (`node Test/patch_bytes_verify.js`): decodes the
   injected bytes with an independent decoder, asserts every branch target, and
   compares the whole file against the original — see
   `AutoControl_native/patches/README.md` §"Proof of safety". The same bytes
   disassembled by Ghidra are stored in
   `AutoControl_native/patches/ghidra-disasm.txt` (both tools agree on all 34
   instructions).
5. Live: `Test/engine_zone_write.ps1 -Dump` prints the cave and non-zero slots;
   a wheel over the tab strip fires the zone-12 trigger while the page still
   scrolls (`Test/zone-tests/README.md` §12).
6. Artifacts that could rot silently are re-checked by the harness:
   **B53f** rebuilds the helper's `npre[]` writer **from `Test/ac_zone_helper.cs`**
   and requires byte equality with the verifier's simulated runtime variant;
   **B53g** parses `ghidra-disasm.txt` and requires its bytes to be the bytes of
   the current build (34 instructions included). Change the patch without
   regenerating the listing and the suite fails — by design.
7. `node Test/patch_bytes_verify.js --no-diff` runs only the decode half and
   prints `PROOF HOLDS (PARTIAL)`; a **missing** original is an error, and the
   default original is hash-checked against the pristine build — the
   "nothing else changed" half can never be skipped by accident. Verify a
   different build with
   `node Test/patch_bytes_verify.js <patched.exe> --orig <pristine.exe>`.
8. **ABI audit** (`node Test/engine_abi_dump.js <build>`) → must end with
   `ABI AUDIT: OK` (exit 0). It asserts the two assumptions the patch would
   otherwise silently depend on: the code cave sits in real data inside a
   mapped **and executable** page, and the matcher has exactly ONE direct (`E8`)
   caller with no other reference to its address anywhere in the file — i.e.
   nothing can bypass the trampoline. Run it against
   `AutoControl_native/original/…` too when the ABI itself is in question.

### B.7 Deploy / rollback

```powershell
powershell -ExecutionPolicy Bypass -File Test/deploy_patched_engine.ps1
# or, to deploy a freshly built file explicitly:
powershell -ExecutionPolicy Bypass -File Test/deploy_patched_engine.ps1 `
  -Source "$env:TEMP\ac_rebuild\AutoCtrl_2025.4.22.0.exe" -Force
```

The script stops **only** Chrome SxS, kills only orphan `AutoControlZero`/engine
pairs whose parent is dead, backs the current file up once (`.orig`), copies,
and verifies the hash. Then reload the extension so the SW re-runs the config
chain (type 60).

⚠ Rules learned the hard way:

* **never** `taskkill /F` the engine for experimentation — the low-level mouse
  hook can die while the keyboard keeps working, and then *no* mouse trigger
  fires anywhere (indistinguishable from "the zone does not work" until you run
  a known-good control);
* several browsers share **one** engine file — if another browser runs the
  extension, its engine locks the file: kill the engines and copy in the same
  loop;
* rollback = copy `AutoCtrl_2025.4.22.0.exe.orig-pristine` back (or
  `Test/deploy_patched_engine.ps1 -Source <pristine> -Force`).

### B.8 Optional v16 patches (OFF by default)

`node AutoControl_native/patches/patch_zones_v19.js <out> v16` additionally applies the two 2026-09-01
NOPs (zone-12 window gate + zone-12 role check). **They are not used**:
measured on 2026-09-12, with them applied the engine consumed the wheel
everywhere again (that native zone-12 check also drives the consume decision, so
the table alone is what makes both scrolling and the zone work). Do not pass
`v16` unless there is a new reason.

### B.9 Tooling map

| Tool | Purpose |
|---|---|
| `AutoControl_native/patches/patch_zones_v19.js` | build the patched engine from the original (hash-checked) |
| `Test/build_native.ps1` | one command: rebuild + verify both components (`-UpdatePatched` refreshes `patched/`) |
| `Test/patch_zones_v19diag.js` | diagnostic build: records the region ids the engine asks for |
| `Test/engine_zone_write.ps1` | write/inspect the table or a diagnostic cave in the **running** engine |
| `Test/patch_bytes_verify.js` | **the proof**: decode the injected bytes, assert every branch target, diff the whole file vs the original (`--orig`, `--no-diff`) |
| `Test/DisasmPatch.java` | regenerate `patches/ghidra-disasm.txt` (independent disassembler, headless, `-noanalysis`) |
| `Test/AbiDump.java` | regenerate the instruction-level ABI evidence (prologue of the matcher + its call site) |
| `Test/engine_abi_dump.js` | PE sections, call sites, **absolute/relocated references to the matcher**, free space, cave page mapping — as a CHECK: ends with `ABI AUDIT: OK` / exit 1 |
| `Test/engine_find_cave.js` | locate the `.text` tail cave |
| `Test/deploy_patched_engine.ps1` | deploy with locks/backup/hash verification |
| `Test/ac_zone_helper.cs` + `Test/zone_helper_smoke.js` | helper source + its protocol smoke test |
| `Docs/archive/NATIVE-REVERSING-2026-08-31.md` | the RE analysis behind every address above (§10–§13) |
