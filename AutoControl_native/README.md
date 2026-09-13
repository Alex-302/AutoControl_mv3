# AutoControl_native — native components (original / patched / patches)

**What this folder is:** everything the extension needs *outside* the browser —
the native messaging host (the "engine" the extension talks to) plus our own
zone-classifier helper. Nothing here is loaded by Chrome directly: the files are
**copied by hand** into `%LOCALAPPDATA%\AutoControl\` and registered in the
registry (see `README.md` in the repo root, §4.2/§4.3).

> Why these binaries are in the repository at all: the AutoControl engine is
> **abandoned** (no updates will ever come) and it needs a byte patch to work on
> Chrome 148+. Keeping the pristine original next to the current build and the
> patch script makes the running engine *reproducible* — anyone can verify or
> rebuild it bit for bit.

---

## Layout

```
AutoControl_native/
├── README.md                          <- this file
├── AutoControl.manifest               <- native-host manifest of the ENGINE
│                                          (name "hrich.autocontrol", path "AutoControlZero.exe")
├── com.autocontrol.zonehelper.json    <- native-host manifest of the ZONE HELPER
├── ac_zone_helper.exe                 <- OUR OWN binary: zone classifier (no hooks)
│                                          current build: 6988B49B…, built from
│                                          Test/ac_zone_helper.cs
├── original/                          <- untouched upstream files (never edited)
│   ├── AutoCtrl_2025.4.22.0.exe       <- the PRISTINE engine      8AE9A669… (695 296 b)
│   └── AutoControlZero.exe            <- the proxy/launcher       994E14D2… (332 800 b)
├── patched/                           <- the CURRENT (fixed) build
│   └── AutoCtrl_2025.4.22.0.v19.exe   <- zone-table build         1A10EDD1… (695 296 b)
└── patches/                           <- how original/ becomes patched/
    ├── README.md                      <- exact commands + what each patch does
    └── patch_zones_v19.js             <- the ONLY active patch (original -> v19)
```

**Which one do I install?** → `patched/` (that is what actually works today).
`original/` is only the input of the patch script and a reference for hash
comparisons. Nothing in `original/` may be modified — the patch script verifies
its SHA-256 and refuses to run on anything else.

### `AutoControlZero.exe` — do not skip it
The host manifest points at `AutoControlZero.exe`, never at the engine: Zero is
a proxy/launcher that starts the engine with the argument `152`. Launching the
engine directly crashes with a C++ exception. Both exes must sit in
`%LOCALAPPDATA%\AutoControl\`.

### The zone helper (`ac_zone_helper.exe`) — ours
A ~300-line C# program (`Test/ac_zone_helper.cs`) that answers "which browser
zone is the cursor over?" over the native-messaging protocol. It exists because
the bundled engine cannot classify the browser chrome on Chrome 148+ (its hover
cache never refreshes over the tab strip, and an MSAA query from its input hook
deadlocks). The service worker asks the helper before executing any
mouse-over-gated trigger.

Install: copy `ac_zone_helper.exe` + `com.autocontrol.zonehelper.json` to
`%LOCALAPPDATA%\AutoControl\` and register the host (one `reg add` line, see the
root `README.md` §4.3). The helper runs only while a browser talks to it.

## Rebuild / verify (bit for bit)

```powershell
# both components, with SHA-256 verification (nothing is installed):
powershell -ExecutionPolicy Bypass -File Test\build_native.ps1

# ... and refresh patched/ with the freshly built engine:
powershell -ExecutionPolicy Bypass -File Test\build_native.ps1 -UpdatePatched

# deploy the current build into the running install:
powershell -ExecutionPolicy Bypass -File Test\deploy_patched_engine.ps1
```

Full byte-level explanation (addresses, the code cave, the runtime table):
**`Docs/BUILD-NATIVE.md`**.

| File | Size | SHA-256 (first 16) | Produced by |
|---|---|---|---|
| `original/AutoCtrl_2025.4.22.0.exe` | 695 296 | `8AE9A669086BEA5C` | upstream (v2025.4.22) |
| `original/AutoControlZero.exe` | 332 800 | `994E14D2BB306607` | upstream |
| `patched/AutoCtrl_2025.4.22.0.v19.exe` | 695 296 | `1A10EDD191B80A80` | `patches/patch_zones_v19.js` |
| `ac_zone_helper.exe` | 16 384 | `6988B49BCBEC162C` | `Test/build_native.ps1` (Roslyn, deterministic) |

> The engine the *extension* unpacks on a fresh install is a different file
> (`mv3-build/file76.dat`, the distro build) — it has **no** zone fix, so a fresh
> install still needs `deploy_patched_engine.ps1` (or a manual copy of
> `patched/`) before mouse-over zones work.

## History / other patch scripts

Only `patches/patch_zones_v19.js` is current. Older and diagnostic variants are
kept in `Test/` because the RE documents reference them:

| Script | What it does | Status |
|---|---|---|
| `patches/patch_zones_v19.js` | zone table in engine memory; regions ≥ 40 keep the engine's own logic | **current** |
| `Test/patch_zones_v19diag.js` | same + type-792 zone-role diagnostics | diagnostic only |
| `Test/patch_zones_v18.js` | "always match below 60" — made the engine eat the wheel everywhere (pages stopped scrolling) | obsolete, kept as evidence |
| `Test/patch_accname.js` | accName call so Chrome builds its MSAA tree | NOT needed: the helper queries `get_accName` itself |
| `Test/archive/zone-re/patch_zone12_v5b…v17g.js` | attempts to make the *engine* classify the chrome | closed dead end, see `Docs/archive/NATIVE-REVERSING-2026-08-31.md` |
