# AGENTS.md — AutoControl MV3 port (rules & index)

> **What this file is**: the RULES and the INDEX. Detailed manuals live in `Docs/` and `Test/README.md`; chronology lives in `CHANGELOG.md` / `Docs/archive/`.
>
> - Fix chronology & public record → `CHANGELOG.md` (Keep a Changelog)
> - Feature/port status → `Docs/FEATURES-MV3.md` (§7 gaps, §8 impossible in MV3)
> - Coverage overview (plain language) → `Docs/MV2-MV3-coverage.md`
> - Protocol reference → `Docs/NATIVE_PROTOCOL.md`; symbol map → `Docs/DECODE.md`
> - Native build recipe (bit-for-bit) → `Docs/BUILD-NATIVE.md`
> - Historical docs (closed bug reports, session handoffs) → `Docs/archive/`

## Index — where everything lives

| Topic | File |
|---|---|
| CDP debugging; launching the debug browser | `Docs/CDP-DEBUGGING.md` |
| MV3 architecture (SW-brain) | `Docs/MV3-ARCHITECTURE.md` |
| Script execution (Run Script / userScripts / sandbox) | `Docs/MV3-ARCHITECTURE.md` § Script execution |
| Bundle build + encoding rules | `Docs/BUNDLE-BUILD.md` |
| Known pitfalls / fixes (native, capture, scripting, triggers, UI, actions, shims) | `Docs/GOTCHAS.md` |
| Test harnesses & live tool inventory | `Test/README.md` |
| Native protocol | `Docs/NATIVE_PROTOCOL.md` (short summary below) |
| Decoded symbols / deobfuscation map | `Docs/DECODE.md` |
| Feature status & port gaps | `Docs/FEATURES-MV3.md` |
| MV2→MV3 coverage | `Docs/MV2-MV3-coverage.md` |
| Scripting API reference | `Docs/SCRIPTING-API-SUMMARY.md` |
| Fix chronology | `CHANGELOG.md` |
| **Open items (mouse-over zones)** | `Docs/TODO-mouseover-zones.md` |
| **Open items (menu-item zones 41-51)** | `Docs/TODO-menu-items.md` |
| **Open items (helper auto-heal)** | `Docs/TODO-helper-autoheal.md` |
| Historical one-offs | `Docs/archive/`, `Test/archive/README.md` |

## Critical rules (read first)

1. **Scope**: work ONLY on this repository's files; any create/copy/modify outside needs the user's explicit confirmation — every time. Full text below.
2. **`ext-mv2/` is the upstream baseline — DO NOT EDIT.**
3. **`mv3-build/` is the shipped artifact**: English-only code, keep it clean; dev tools/harnesses live in `Test/`.
4. **Verify every change**: `node Test/mh_test.js` → `SUMMARY: N pass, 0 known gaps, 0 FAIL` (exit 1 on FAIL). Native patch edits → the full proof chain (`Docs/BUILD-NATIVE.md`).
5. **Bundle list edits** → rebuild `sw_core_bundle.js` (recipe: `Docs/BUNDLE-BUILD.md`); `file77.js` MUST stay after `file48.js`.
6. **CDP**: before launching a debug browser ALWAYS ask which Chrome variant/profile (`Docs/CDP-DEBUGGING.md`).
7. **Never**: delete `window._Lk`; `taskkill /F` the engine; give a test trigger a `sctnId` that does not exist; copy files outside the repo — details in `Docs/GOTCHAS.md`.
8. **Document every finding/fix in the same change** — see Documentation rules below.

---

## Scope rule — this repository is the ONLY working copy

**All work happens on the files of THIS repository.** The authoritative
source is this repo's `mv3-build/`; every edit, build, test and live check
runs against these files.

- **NEVER create, modify, copy or delete anything OUTSIDE this repository.**
  That includes "the folder the browser really loads" when it happens to be a
  different checkout: writing even one file there modifies somebody else's
  working copy.
- **Any copy/export outside the repository requires the user's explicit
  confirmation — every single time.** State which file, from where, to where
  and why, then wait for the answer. No exceptions for "just one file" or
  "only to verify".
- If a test browser serves the extension from a folder that is NOT this repo's
  `mv3-build/`, do NOT sync it silently: report the fact and ask. The preferred
  fix is to load the extension from this repo
  (`chrome://extensions` → Load unpacked → `mv3-build/`).
- Use **repo-relative paths** in commands, docs and notes (`mv3-build\sw.js`,
  `Test\mh_test.js`, `AutoControl_native\patched\AutoCtrl_2025.4.22.0.v19.exe`).
  Absolute paths are machine-specific and must not appear in this file; for
  machine folders use environment variables (e.g. `$env:LOCALAPPDATA\AutoControl\AutoCtrl_2025.4.22.0.exe`).
- Read-only inspection of an outside folder (listing, hashes, `git status`,
  `git log` of another checkout) is fine — it is the WRITE side that needs
  permission.

## Language rule (code)

**ALL code and comments in `mv3-build/` MUST be in ENGLISH.**
This includes comments, log strings, and error messages in `sw.js`,
`file42.js`, `sw_prelude.js`, and the bundle sources. Code files — English only.

## Repository layout

- **`ext-mv2/`** = the ORIGINAL MV2 extension (upstream baseline,
  `manifest_version: 2`, background page `file63.html`). **DO NOT EDIT** — it
  is the reference for the port. Contains the original Chrome Web Store
  package `AutoControl-Keyboard-shortcuts-Mouse-gestures-Chrome.crx`
  (v2025.4.22) and its extracted tree in `unpacked/` (incl. the Web Store
  `_metadata/` signature files).
- **Repo root** = `AGENTS.md`, `README.md`, `CHANGELOG.md` + the folders
  below; all other docs live in `Docs/`, test artifacts in `Test/`.
- **`Docs/`** = agent manuals & reference: `GOTCHAS.md` (all known pitfalls),
  `CDP-DEBUGGING.md` (debug browser + CDP tooling), `MV3-ARCHITECTURE.md`
  (SW-brain + script execution), `BUNDLE-BUILD.md` (bundle rebuild + encoding),
  plus `FEATURES-MV3.md` (status & open items §7),
  `MV2-MV3-coverage.md`, `NATIVE_PROTOCOL.md`, `DECODE.md`,
  `SCRIPTING-API-SUMMARY.md`, `SUMMARY-SCRIPTING-API.md`.
  **`Docs/archive/`** = historical docs:
  `✅ BUG-REPORT-runScript-duplicates.md` (closed 2026-08-05),
  `HANDOFF-2026-08-06-unstaged.md`, `RIGHT-CLICK-ISSUE.md`,
  `NATIVE-REVERSING-2026-08-31.md` (hover-region/MSAA root cause, Ghidra
  RE session — addresses, Chromium facts, live region map, patch plan).
- **`Test/`** = the LIVE toolset. **`README.md` is its source of truth**: harness
  docs, the physical-test rules (the engine DROPS synthetic input, so wheel
  tests need a real hand) and a **GENERATED inventory of every tool in the
  folder** — refresh `node Test/_tools_index.js`, verify `--check`, pinned by
  mh_test **B59**. Do NOT list tools here: describe a tool in its own header
  comment instead. Three things worth knowing without opening the README:
  `mh_test.js` is THE SW harness (**it lives here, NOT in `mv3-build/`: that
  folder is the extension itself and must stay clean**), `ac_zone_helper.cs` +
  the zone tools are the native half of the mouse-over work, and
  **`Test/archive/`** holds HISTORICAL one-offs kept for chronology only (index
  there — nothing in it is part of the build, the harness or the shipped
  extension).
- **`AutoControl_native/`** = the native side (manifests + binaries), laid out
  as `original/` (untouched upstream: engine + `AutoControlZero.exe`),
  `patched/` (**the current build**: `AutoCtrl_2025.4.22.0.v19.exe`) and
  `patches/` (the patch script that turns `original/` into `patched/`); the
  host manifests stay at the root. **Structure doc:
  `AutoControl_native/README.md`** (`patches/README.md` = exact commands).
  The extension never reads this folder — it unpacks its own engine from
  `file76.dat`, which is the UNPATCHED distro build.
- **`mv3-build/`** = the MV3 port (SW-brain). **This is where ALL work
  happens.** Load this folder in Chrome as an unpacked extension. Contains its
  own copies of the core `file*.js`/`res/` — independent from `ext-mv2/`.
  **The folder is the shipped artifact — keep it CLEAN (user rule
  2026-09-13):** only files the extension actually loads belong here. Dev-only
  material (test harnesses, probes, helpers) goes to `Test/`; the harness
  `mh_test.js` was moved there for exactly that reason.
- **`Toolbar-buttons/`** = auxiliary builds/assets (MV2/MV3 pairs: base,
  Duplicate, Mute, Pin, Unload).
- NOTE: the old loose MV3 shims at the repo root were REMOVED (cleanup
  commit) — the working copies live in `mv3-build/`. Do not recreate them.

## Contribution rules (post-task)

- You MUST verify your change with the harness:
  `node Test/mh_test.js` — expect `SUMMARY: N pass, 0 known gaps,
  0 FAIL` (exit 1 on FAIL). Filter: `2>&1 | Select-String -Pattern
  "PASS|FAIL|GAP|SUMMARY"`.
- You MUST keep `mh_test.js` current — every new fix ships with a smoke test
  (`[PASS]`/`[FAIL]`/`[GAP ]`/`[FIXED?]`). When a `[GAP ]` stops reproducing,
  update `Docs/FEATURES-MV3.md` §7.
- **After ANY edit to the native engine patch you MUST re-run the proof chain**
  (the injected code is hand-written bytes — a wrong byte is silent until the
  engine misbehaves):
  1. `node Test/patch_bytes_verify.js` → must print `PROOF HOLDS` (exit 0) and
     `40 bytes differ, all inside the documented ranges`. It checks the
     **deployed** engine by default; pass a file to check a build
     (`--orig <pristine.exe>` for another original, `--no-diff` only if you
     deliberately accept `PROOF HOLDS (PARTIAL)`).
  2. `powershell -File Test/build_native.ps1` → both hashes OK
     (engine `1A10EDD191B80A806DF66558B2B1E78BE8D6AD81E93EEAC772D13F222E212C3E`, helper `C8466CF7CE1AC40C3A56AAD175B0F545B914E670679B495C2199E469A483ABAF`).
  3. `node Test/mh_test.js` → B53b–B53g `[PASS]`: CLI + determinism,
     docs == bytes, the decoder proof, its mutation (teeth) test, the helper
     writer == the verifier's simulation, the Ghidra listing == the build.
  4. `node Test/engine_abi_dump.js <build>` → must end with `ABI AUDIT: OK`
     (exit 0): the cave page is mapped **and executable**, the matcher has
     exactly ONE direct caller and no other reference to its address exists —
     i.e. nothing can bypass the trampoline. (Also run against
     `AutoControl_native/original/` when the ABI itself is in question.)
  5. If the cave/entry BYTES changed: regenerate `ghidra-disasm.txt`
     (`Test/DisasmPatch.java`) and update the byte tables in
     `Docs/BUILD-NATIVE.md` §B.3/B.4 + `patches/README.md` in the SAME change —
     B53c/B53g fail on a stale listing or doc, by design.
- After editing ANY file from the bundle list (recipe: `Docs/BUNDLE-BUILD.md`), you MUST
  rebuild `sw_core_bundle.js` and run the arrow sanity check.
- After editing `Test/SCRIPTING-API-TEST.js` you MUST re-copy its content
  into the RUN SCRIPT editor (extension reload does NOT update saved
  scripts).
- You MUST document findings: protocol facts → `Docs/NATIVE_PROTOCOL.md`;
  decoded symbols → `Docs/DECODE.md`; gotchas → `Docs/GOTCHAS.md`;
  CDP/tooling procedures → `Docs/CDP-DEBUGGING.md`; architecture notes →
  `Docs/MV3-ARCHITECTURE.md`; feature status → `Docs/FEATURES-MV3.md`;
  user-facing record → `CHANGELOG.md`.
- You MUST keep code in `mv3-build/` English-only (see Language rule).
- When the project structure changes, keep the Repository layout section
  valid.

## Documentation rules (IMPORTANT — the code is obfuscated)

This codebase is minified/obfuscated (`_qe`, `_md`, `_6s`, `_wj`, ...). Any
logic that is uncovered, changed, or worked around MUST be documented —
otherwise the next session starts from zero. Concretely:

1. **New findings go into the docs immediately** — do not postpone "until it
   stabilizes": add to `Docs/NATIVE_PROTOCOL.md` (protocol), `Docs/DECODE.md`
   (deobfuscation map — the file `/memories/repo/deobfuscation-map.md` is
   also a good place), `Docs/FEATURES-MV3.md` (feature status & port gaps —
   single source of truth; broken items are tracked in §7 with
   section links), gotchas → `Docs/GOTCHAS.md`, CDP/tooling procedures →
   `Docs/CDP-DEBUGGING.md`, whichever fits.
1b. **Keep `README.md` (the install guide) current** — it is user-facing and
   must stay in sync with reality: extension toggles and their names
   (chrome://extensions → Details → "Allow user scripts" / "Allow access to
   file URLs"), the manual native-install steps (`AutoControl_native\` →
   `%UserProfile%\AppData\Local\AutoControl`), and the verification
   checklist. Whenever the native-install TODO is fixed or any toggle/path
   changes, update README.md in the same change.
2. **Every fix ships with a doc line** — at minimum a bullet in the relevant
   doc + a session-memory note (`/memories/session/autocontrol-mv3.md`):
   symptom → root cause → fix → rebuild status.
3. **Deobfuscation map**: when you decode a symbol/function, record it
   (`_qe=1` LMB, `_md=2` RMB, `_4e=60` config, `_zs` reads script code from
   `_if`, `_Mi` fires `_Gu`/`_B` subscriptions after storage write, etc.).
4. **Protocol changes**: any new/changed native message type, field, or
   handshake step goes into `Docs/NATIVE_PROTOCOL.md` with the exact wire
   format.
5. **Bundle rebuild notes**: state the bundle size after each rebuild in the
   session memory (quick sanity: marker present? size changed?).
6. **🔴 HIGH PRIORITY — deobfuscation & protocol DISCOVERIES and
   INACCURACY CORRECTIONS are documented THE MOMENT they are made — not only
   changes, and not only in code-changing sessions.** A session that decoded
   or observed something new (or spotted a wrong/outdated doc entry) but
   ended without updating the map is INCOMPLETE. Every session MUST land its
   findings AND fix any inaccuracies before it ends:
   - new decoded symbols/functions → `Docs/DECODE.md` (symbol tables) —
     including CORRECTIONS of wrong entries (e.g. `_9k` is
     `localStorage.setItem/removeItem`, NOT `chrome.storage.local.set`);
   - new semantic facts about the native (message meaning, side effects,
     lifecycle) → `Docs/NATIVE_PROTOCOL.md` with the exact wire format.
   Example of a MUST-document finding: "type 55 does NOT restart the engine —
   it is an ACK; the MV2 restart came from the background-page reload (port
   drop → Zero exit on EOF → fresh Zero spawns a fresh engine)" is now
   NATIVE_PROTOCOL §18, and `_co`/`_ze`/`_nk`/`_Cr`/`_j`/`_nt`/`_2u` +
   55/451 are in DECODE.md.
7. **Links to the dead AutoControl site — always use the mirror.**
   `autocontrol.app` is dead: never reintroduce its URLs (`www.autocontrol.app/…`,
   the Web Store listing, `files/Native-Component.exe`) in docs, README or code.
   The working copy is the GitHub Pages mirror
   <https://alex-302.github.io/AutoControl_mv3/> — the original paths plus
   `.htm` (`…/https@www.autocontrol.app/faq.htm`); the exact page mapping is in
   README §1.1. The ONLY intentional exceptions are the struck-through original
   website URL in `README.md` §1 (the "it's dead" notice) and the
   `web.archive.org` snapshot of the Web Store listing (the dead store URL
   itself is intentionally gone from the README).
   ⚠ The UI's own help links point at the mirror since 2026-09-13: `_Zl`
   (mirror base, `file10.js`) + the `_4a` URL map — `file78_mv3.js` AND
   `file78.js` extend the map (both are loaded by `main.html`, the LATER one
   wins — keep them in sync), and the tooltip texts in
   `file28/file33/file65/file75/file80` reference `_4a.*` keys. Every mapped
   page carries `.htm` and `scrtDoc` is the mirror's `scripting/` DIRECTORY
   (sub-page call sites append `<name>.htm`). `_Zo` (the dead base) survives for
   exactly two non-doc endpoints — telemetry `appEvent` and the animated-demo
   base in `file36`; never point new user-visible links at it. Two mapped pages
   needed restoring: `chromium-bugs` was downloaded from the Wayback snapshot
   (2023-09-03, raw `id_` URL — no archive toolbar) and lives in the mirror as
   `chromium-bugs.htm` with its 5 images; `files/Native-Component.exe` has NO
   snapshot anywhere and stays dead (the port installs the native component
   from its own `file69.dat`). Inventory: `/memories/session/autocontrol-mv3.md`.
   ⚠ **Demo entries are LINKS now (2026-09-13)** — the Help → *Show demos*
   panel (`main.html` template `demoPanel`) lists three links to mirror guides
   instead of playing `file9.js` animations: those need the dead site's
   screenshots (`/demos/<name>/imgN.png`), which were NEVER archived (a CDX
   prefix query on `/demos/` returns exactly 2 files). Do not re-wire them to
   the player (`_Be`/`_Rj`/`_Yt`). The animated illustrations on the mirror
   pages themselves (`hvrdElem*Anim.htm`, iframed by
   `determining-hovered-element.htm`) still work — they are SVG, not
   screenshots. Untouched on purpose (user decision): the switches tooltip demo
   (`file65.js`, `initDemo=setSwtchs`) and the Settings-File-Editor welcome demo
   (`file65.js`, `<demoPH demoName=SFEimport>`) — both equally broken.
8. **One fact, ONE source of truth — and the copies are CHECKED, not trusted
   (2026-10-04).** Splitting the docs (rules here, details in `Docs/`) means one
   fact can live in several files and a hand-kept copy drifts. The copies are
   machine-checked instead of trusted: `mh_test` **B57/B58** verify every doc
   claim about the current build hash/size against `Test/build_native.ps1`,
   **B59** verifies the generated tool inventory in `Test/README.md`. Never write
   a retired value into a "current" sentence — history goes into DATED blocks.
   The claim sites, the retired-hash rule and the sweep recipe:
   `Docs/BUILD-NATIVE.md` § C "Doc ⇄ build consistency".

## Where to look for docs
- Content script CSP / isolated worlds:
  <https://developer.chrome.com/docs/extensions/develop/concepts/content-scripts>
- userScripts API:
  <https://developer.chrome.com/docs/extensions/reference/api/userScripts>
- Offscreen documents:
  <https://developer.chrome.com/docs/extensions/reference/api/offscreen>
- Sandbox pages:
  <https://developer.chrome.com/docs/extensions/develop/concepts/declare-permissions#sandbox>
- `scripting.executeScript` (no matchAboutBlank):
  <https://developer.chrome.com/docs/extensions/reference/api/scripting>
- This repo's own docs: `README.md` (install guide — user-facing),
  `Docs/BUILD-NATIVE.md` (rebuild the helper / patch the engine bit-for-bit),
  `Docs/GOTCHAS.md` (known pitfalls), `Docs/CDP-DEBUGGING.md`,
  `Docs/MV3-ARCHITECTURE.md`, `Docs/BUNDLE-BUILD.md`, `Test/README.md`
  (test toolset), `Docs/NATIVE_PROTOCOL.md`, `Docs/DECODE.md`,
  `Docs/archive/RIGHT-CLICK-ISSUE.md`, `Docs/FEATURES-MV3.md`, `CHANGELOG.md`.

## Native protocol (short)

Native host `hrich.autocontrol`; messages `{type, content, callback}`,
callback `e+l` (l from ext id), echo reply type 710. Key types: 10=file check,
20=init, 21=startup, 60=config (mapKey=keyId+22025), 67=monitors, 72=switch
states, 300=SendInput, 750=trigger, 760=raw gesture, 905=keepalive, 920=ping.
Details: `Docs/NATIVE_PROTOCOL.md`.

