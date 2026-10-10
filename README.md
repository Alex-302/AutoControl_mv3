# AutoControl MV3 - Customize keyboard shortcuts and hotkeys, Mouse, Wheel, Rocker gestures, Bookmark shortcuts, Joystick actions

**MV3 port — installation guide (unpacked build)**

> The MV3 port **must be installed as an unpacked extension** (developer mode).
> It is a work-in-progress build: it relies on dev-mode freedoms
> (`chrome.userScripts` in unpacked contexts) and has **not** been packaged for
> the Chrome Web Store. A packaged/crx install will not work as expected.

---

## 1. About this project

**This is NOT the original AutoControl extension.** It is a **port** of the
MV2 version of "AutoControl: Keyboard shortcuts, Mouse gestures" to Manifest
V3. The original MV2 extension, its native Windows components, and
the AutoControl name belong to their respective authors — the code in this
repository is **not owned** by the port's author @AutoControl-app.

The **original AutoControl** and documentation are available at:

- ~~**Official website**: <https://www.autocontrol.app>~~ it's dead.\
  **Copy** of the site: <https://alex-302.github.io/AutoControl_mv3/>
- **Chrome Web Store**: ~~<https://chromewebstore.google.com/detail/autocontrol-keyboard-shor/lkaihdpfpifdlgoapbfocpmekbokmcfd/>~~
 **Archived**: https://web.archive.org/web/20260611075755/https://chromewebstore.google.com/detail/autocontrol-keyboard-shor/lkaihdpfpifdlgoapbfocpmekbokmcfd/

**What is original and what is ported:**

- **The bulk of the logic is the ORIGINAL obfuscated MV2 code** (`file*.js`
  sources) — triggers, actions, config chain, settings UI logic. The port
  reuses these files as-is (they are byte-identical to the MV2 originals
  where possible), some files are patched.
- **The MV3-specific pieces are written from scratch** — the service-worker
  brain (`sw.js`), the bundle glue (`sw_prelude.js`), the page-side shims
  (`mv3_shim.js`, `mv3_native_shim.js`), the offscreen document, and the
    test harness (`Test/mh_test.js` — kept OUT of the extension folder, which
    is the packaged artifact). These replace the MV2 background
  page and adapt the original code to Manifest V3 APIs.
- **The native component is based on the ORIGINAL AutoControl binaries** — the
  extension embeds and deploys the original `AutoControlZero.exe` (proxy/
  launcher, also the installer) and a **patched** `AutoCtrl_2025.4.22.0.exe`
  (the mouse-over zone fix, §4.3). The patch is a documented, reproducible
  40-byte change of the original binary (see
  [§4.0](#40-where-the-native-binaries-come-from)).

**About the port itself**: the MV3 port was made **entirely and solely with
the help of an LLM** — the MV3-specific code, the shims, the service-worker
brain, and the porting work itself were written with AI assistance, without
a human developer authoring the port by hand.
The human role was reviewing, testing and guiding the process.

> The MV2 baseline lives in `ext-mv2/` and is kept **untouched** — it is the
> reference for the port and must not be edited.

### 1.1 Original description (Chrome Web Store listing)

Customize keyboard shortcuts and hotkeys, Mouse gestures, Wheel gestures, Rocker gestures, Bookmark shortcuts, Joystick actions.[^1]

#### Summary

AutoControl is a comprehensive solution to fully customize the way you control your browser using keyboard, mouse and joysticks.

This is the only shortcut manager that can redefine and disable ALL factory keyboard and mouse shortcuts in Chrome.
This is the only shortcut manager that works on ALL browser tabs.

None of this is possible with regular Chrome extensions.
AutoControl IS NOT A REGULAR EXTENSION.

AutoControl currently works on Windows operating systems only.
If you are still interested, read on to learn why AutoControl is different.

#### AutoControl is a native extension

AutoControl brings out the power of Chrome's native extensibility to gain essential advantages over regular extensions:

- It can customize or disable ALL browser shortcuts, even those prohibited to regular extensions, such as Ctrl+Tab, Ctrl+ScrollWheel, and any other.
- Keyboard shortcuts and gestures work on ALL tabs, be it the New Tab Page, extension pages, settings pages, protected pages, PDF documents, you name it.
- It uses a single lightweight content script instead of injecting code into every page, leaving pages intact and conserving CPU and memory. [^2]
- Keyboard shortcuts and mouse gestures are implemented natively, which makes them respond instantly at all times.

Learn more about native extensions at the [FAQ](https://alex-302.github.io/AutoControl_mv3/https@www.autocontrol.app/faq.htm "AutoControl FAQ").

#### Feature list

- Customize or disable Chrome's factory keyboard and mouse shortcuts.
- Define your own custom keyboard/mouse shortcuts and gestures.
- Mouse gestures support horizontal, vertical and diagonal motion.
- Supports wheel gestures, rocker gestures and multi-directional drag.
- Keyboard shortcuts and mouse gestures work on ALL tabs. PERIOD.
- Works in incognito windows when "Allow in Incognito" option is ON.
- Shortcuts support wildcards to allow or disallow extra keys.
- A shortcut may be any combination of keyboard keys, mouse buttons, joystick buttons and mouse gestures.
- Keyboard shortcuts can have multiple steps. [🔗](https://alex-302.github.io/AutoControl_mv3/https@www.autocontrol.app/triggers.htm#multiStep "Multi-step triggers")
- Supports address bar shortcuts. [🔗](https://alex-302.github.io/AutoControl_mv3/https@www.autocontrol.app/address-bar-shortcuts.htm "Address bar shortcuts")
- Supports hover-sensitive shortcuts and gestures. [🔗](https://alex-302.github.io/AutoControl_mv3/https@www.autocontrol.app/hover-sensitive-shortcuts.htm "Hover-sensitive shortcuts")
- Keyboard shortcuts and mouse gestures can work even when the browser is unfocused or closed.
- Use keyboard shortcuts and gestures to open any bookmark/folder.
- You can restrict shortcuts and gestures to specific websites.
- Create custom toolbar buttons to perform any desired action. [🔗](https://alex-302.github.io/AutoControl_mv3/https@www.autocontrol.app/custom-toolbar-buttons.htm "Custom toolbar buttons")
- Create custom menus with your open tabs, closed tabs, bookmarks, bookmark folders and more. [🔗](https://alex-302.github.io/AutoControl_mv3/https@www.autocontrol.app/action-menus.htm "Action menus")
- Menus can display tab thumbnail previews. [🔗](https://alex-302.github.io/AutoControl_mv3/https@www.autocontrol.app/switch-to-last-used-tab-in-chrome.htm#tab-switcher "Tab switcher with thumbnail previews")
- Supports a wide variety of actions: Tab actions, Window actions, Bookmark actions, Clipboard actions and more.
- Actions can be applied to one or more tabs and windows simultaneously.
- Actions are composable, they may be simple or complex. [🔗](https://alex-302.github.io/AutoControl_mv3/https@www.autocontrol.app/actions.htm "Actions")
- Provides a scripting API and script editor that allows to build your own custom actions. [🔗](https://alex-302.github.io/AutoControl_mv3/https@www.autocontrol.app/scripting/default.htm "Scripting API")
- Can synchronize your settings across different profiles on the same computer or the same profile across different computers.
- Works entirely offline. No need for an internet connection.

See what's new at [🔗](https://alex-302.github.io/AutoControl_mv3/https@www.autocontrol.app/update-history.htm "Update history").

#### System requirements

Being a native extension demands additional development effort to support each operating system. For this reason, AutoControl is initially supported on:

- Windows 7
- Windows 8/8.1
- Windows 10
- Windows 11

#### Permissions

When installing you'll see a message saying that the extension can "Read and change all your data on the websites you visit".
This is a standard message generated by Chrome. This extension does NOT access or collect any personal data.

Please read our privacy policy to learn more: [🔗](https://alex-302.github.io/AutoControl_mv3/https@www.autocontrol.app/privacy-policy.htm "Privacy policy").

[^1]: Original Chrome Web Store description of the abandoned extension. The links point to a [mirror](https://alex-302.github.io/AutoControl_mv3/ "AutoControl site mirror") of the dead `autocontrol.app` site.
[^2]: Reworded for the MV3 port: it needs one small content script on all pages.

---

## 2. Repository structure

```text
AutoControl-Keyboard-shortcuts-Mouse-gestures-Chrome/
├── README.md               # This file (user manual)
├── AGENTS.md               # Working rules for LLM agents / contributors
├── CHANGELOG.md            # User-facing changelog (Keep a Changelog)
├── ext-mv2/                # ORIGINAL MV2 extension (reference baseline) — DO NOT EDIT
│   ├── AutoControl-Keyboard-shortcuts-Mouse-gestures-Chrome.crx  # original Web Store package (v2025.4.22)
│   └── unpacked/           #   its extracted tree (the byte-identical MV2 sources)
├── mv3-build/              # the MV3 port — load this folder as an unpacked extension
│   ├── sw.js               #   Service worker (SW-brain)
│   ├── sw_core_bundle.js   #   Concatenated core bundle (prelude + file*.js)
│   ├── manifest.json       #   Manifest V3
│   ├── main.html           #   Settings page (UI)
│   ├── file76.dat          #   PATCHED engine payload (encoded v19) — deployed by the SW
│   ├── ac_zone_helper.dat  #   zone-helper payload (encoded exe) — deployed by the SW
│   └── file*.js            #   Original obfuscated and patched MV2 files
├── AutoControl_native/     # Native host: manifests + original AND patched binaries
│   ├── README.md           #   ← structure explained (original / patched / patches)
│   ├── AutoControl.manifest                  # engine host manifest (path = Zero)
│   ├── com.autocontrol.zonehelper.json       # zone-helper host manifest template
│   ├── ac_zone_helper.exe                    # zone-classifier helper (ours, C8466CF7CE1AC40C3A56AAD175B0F545B914E670679B495C2199E469A483ABAF)
│   ├── original/           #   untouched upstream files — NEVER edited
│   │   ├── AutoControlZero.exe        # proxy/launcher (= installer)  994E14D2BB306607C158C6799E0661C90EE1A480378ACA969C9397E4712A4C38
│   │   └── AutoCtrl_2025.4.22.0.exe   # engine (global hooks)         8AE9A669086BEA5C4344007AC4CA9797E5814285E03B6B04E5F8336329CB7E09
│   ├── patched/            #   the current build — the source of the bundled payload
│   │   └── AutoCtrl_2025.4.22.0.v19.exe       # zone-table build      1A10EDD191B80A806DF66558B2B1E78BE8D6AD81E93EEAC772D13F222E212C3E
│   └── patches/            #   how original/ becomes patched/
│       └── patch_zones_v19.js                 # the only active patch
├── Test/                   # the toolset (helpers, probes, zone test suite)
│   ├── mh_test.js                 # SW regression harness (node Test/mh_test.js)
│   ├── ac_zone_helper.cs          # zone-helper SOURCE (our own C# program)
│   ├── dat_codec.js               # .dat payload codec (encode/decode/verify)
│   ├── zone_helper_smoke.js       # helper smoke test (native-messaging frame)
│   ├── build_native.ps1           # rebuilds engine + helper + payloads, verifies hashes
│   ├── deploy_patched_engine.ps1  # dev tool: installs patched/ into %LOCALAPPDATA%
│   ├── patch_zones_v18.js         # previous patch (kept for history)
│   └── zone-tests/                # zone regression suite + README
├── Docs/                   # Protocol reference, feature status, deobfuscation map
│   └── archive/            # Historical docs (closed bug reports, old snapshots)
└── Toolbar-buttons/        # Auxiliary toolbar-button extensions (MV2/MV3 pairs)
```

- **`ext-mv2/`** — the original MV2 extension (upstream baseline):
  `AutoControl-Keyboard-shortcuts-Mouse-gestures-Chrome.crx` (the original
  Chrome Web Store package, v2025.4.22) + `unpacked/` (its extracted tree,
  incl. the Web Store `_metadata/`). **Reference only — do not edit.**
- **`mv3-build/`** — the MV3 port. **This is where all work happens.** Load
  folder in Chrome as an unpacked extension (see [§3](#3-install-the-extension-unpacked)).
- **`AutoControl_native/`** — the native side, laid out so that "what runs" is
  unambiguous — see **`AutoControl_native/README.md`**:
  `original/` (untouched upstream exes — the patch input), `patched/` (**the
  current build**, the source of the bundled payload) and `patches/` (the
  script that turns one into the other). The folder also holds the host
  manifests and our zone helper.
  It is NOT a separate component: the exes are the *decrypted* copies of what
  the extension deploys, kept for verification and antivirus/security review.
  The extension never reads this folder — it deploys the **patched** engine
  from its own embedded payload (`file76.dat`, see
  [§4.0](#40-where-the-native-binaries-come-from)) and the helper from
  `ac_zone_helper.dat` (see [§4.3](#43-patched-engine-v19-zone-table--real-input-pass-through)).
- **`Test/`** — `SCRIPTING-API-TEST.js` (in-browser API self-test) and
  `AutoControl-settings-test.acs` (settings snapshot used by the test
  harness).
- **`Docs/`** — `NATIVE_PROTOCOL.md` (wire protocol), `FEATURES-MV3.md`
  (feature status & port gaps), `DECODE.md` (deobfuscation map),
  `MV2-MV3-coverage.md` (plain-language coverage); `archive/` holds
  historical documents.
- **`Toolbar-buttons/`** — auxiliary extensions (base, Duplicate, Mute, Pin,
  Unload) in MV2/MV3 pairs.

---

## 3. Install the extension (unpacked)

1. Open `chrome://extensions`.
2. Enable **Developer mode** (top-right toggle).
3. Click **Load unpacked** and select the **`mv3-build/`** folder of this repo.
4. The extension "AutoControl: Keyboard shortcuts, Mouse gestures" appears.

> Clicking the toolbar icon opens the settings page (and runs the
> toolbar-icon trigger if one is configured — original behavior).

### 3.1 Extension toggles

Open
`chrome://extensions` → `AutoControl` → **Details**

| Toggle | Required? | Purpose |
| --- | --- | --- |
| **Allow user scripts** | ✅ **REQUIRED** | The Run Script engine executes user code via `chrome.userScripts` (Chrome 120+). Without this toggle, scripts fall back to a MAIN-world eval that is blocked by strict page CSP. If the toggle is off, script actions fail with *"userScripts API unavailable — enable 'Allow user scripts' on chrome://extensions"*. |
| **Allow access to file URLs** | ⚠️ optional | Needed **only** if you use local `file://` paths: `ACtl.getFile('C:\path\to\file.txt')`, `ACtl.saveURL(..., 'C:\path\to\file.txt')`, local page access / `file://` URL conditions in triggers. Same requirement as MV2. Leave off if you don't use file paths. |
| **Allowed in Incognito** | ⚠️ optional | Only if you want AutoControl to work in incognito windows. |

---

## 4. Native component (`hrich.autocontrol`)

Almost all of AutoControl's power (hotkeys, gestures, clipboard, SendInput,
file IO, window management) is provided by the **native component** — a
Windows `.exe` that Chrome talks to via native messaging. Without it the
extension loads but nothing works.

> **Host chain**: `AutoControlZero.exe` is the
> **proxy/launcher** — the host manifest's `path` points at it, and Chrome
> always starts it. Zero spawns the real engine `AutoCtrl_2025.4.22.0.exe`
> (from the same host folder) with argument `152`. The engine **cannot** run
> as a standalone host, so **both files are required** and the manifest must keep
> `"path": "AutoControlZero.exe"`.

### 4.0 Where the native binaries come from

Both native payloads are embedded **inside the extension itself** and deployed
from there:

| Embedded in the extension | MD5 of the `.dat` blob | Decrypted content | sha256 (decrypted) |
| --- | --- | --- | --- |
| `file69.dat` (332,800 B) | `64034DE600F897CBDC131E6EBAFEBE88` | **`AutoControlZero.exe`** — the proxy/launcher; the same binary doubles as the **installer** (`Native-Component.exe`, install/uninstall mode via `/noConfirm`) | `994E14D2BB306607C158C6799E0661C90EE1A480378ACA969C9397E4712A4C38` |
| `file76.dat` (695,296 B) | `2F878E9EB062C57D8B5C7FFBC91EAB5D` | **`AutoCtrl_2025.4.22.0.exe`** — the engine, **patched v19** (zone table, §4.3) | `1A10EDD191B80A806DF66558B2B1E78BE8D6AD81E93EEAC772D13F222E212C3E` |

The engine payload is the **only modification** to the original binary in this
port: `AutoControl_native/patches/patch_zones_v19.js` turns the pristine
upstream engine into v19 (exactly 40 bytes: a 5-byte jump + a code cave — every
byte is documented in `Docs/BUILD-NATIVE.md`). Before 2026-10-10 the extension
shipped the pristine distro engine (blob MD5 `6BF791F5B2D267834A52A47E8CC3C2F4`,
decoded sha256 `8AE9A669086BEA5C4344007AC4CA9797E5814285E03B6B04E5F8336329CB7E09`);
that build is kept in `AutoControl_native/original/` and `ext-mv2/` as the
reference.

The `.dat` blobs are the **encoded** form of the executables (a reversible
byte-shift; `Docs/DECODE.md` §«.dat blobs») — that is why their MD5 differs
from the decrypted exes. To verify a binary against the table, hash the
decrypted copies in `AutoControl_native\` or decode the `.dat` first
(`node Test/dat_codec.js verify mv3-build/file76.dat`). `ext-mv2/` keeps the
**original** blobs untouched; `mv3-build/file76.dat` carries the patched
payload.

**`AutoControl_native/` in this repo is NOT a separate/custom component** —
it is the *decrypted* copy of the shipped files (plus the host manifest),
organised so that "what runs" is unambiguous
(`AutoControl_native/README.md`):

| Folder | Content |
| --- | --- |
| `original/` | the untouched upstream exes (`AutoControlZero.exe` + the engine) — the input of the patch script and the hash reference |
| `patched/` | **the current build** — `AutoCtrl_2025.4.22.0.v19.exe` (§4.3); this is the source of the bundled payload |
| `patches/` | `patch_zones_v19.js` — turns `original/` into `patched/` (deterministic) |

The extension never reads this folder: the installer is extracted from
`file69.dat` and the engine from `file76.dat` (now the patched build).

### 4.1 Installation

1. Load the extension ([§3](#3-install-the-extension-unpacked)) and open it — the
   **install pane** appears ("the native component is not installed").
2. Click **Install**, save the installer and run it.
3. That's it — the extension finishes the installation itself: it deploys the
   **patched engine** and the **zone helper**, registers **both** native hosts
   for every known browser branch and opens the settings. No file copying, no
   registry edits, no extension reload.
4. Make sure a hotkey or a gesture works.

Something does not work, or you are moving to another browser?
→ [§6 Troubleshooting](#6-troubleshooting).

---

### 4.2 Zone helper (`com.autocontrol.zonehelper`) — mouse-over zone support

**Problem (Chrome 148+):** the engine cannot classify the **hovered zone**
(tab strip, toolbar, …). Its hover cache never refreshes over the tabs, and a
fresh MSAA query from its low-level input hook **deadlocks** (Chrome does
not answer `WM_GETOBJECT` during input processing — see
`Docs/archive/NATIVE-REVERSING-2026-08-31.md` §12). Consequence: a
"mouse over → …" trigger never fires on Chrome 148+.

**Solution:** the zone decision is moved OUT of the engine. A tiny
**external helper** answers "what zones are under the cursor?" from a normal
process context (no hooks — safe) and writes the answer into a small **zone
table inside the engine's own memory**; the extension's service worker uses
the same answer to double-check the trigger:

```
     ac_zone_helper.exe (no hooks)          engine (v19)
     GetCursorPos + MSAA ancestry walk      patched matcher reads the table:
                  │                        table[region] == 1  -> match,
                  │ writes the table       otherwise the input is passed
                  ▼                        through untouched (page scrolls)
        [alive | table[64]] ─────────▶ 0x47F7A3 (code cave in the .text tail)
                  │
                  ▼
        SW gate: trigger's regions ∩ helper's zones ≠ ∅ ──▶ dispatch action
                 no intersection                       ──▶ skip (belt & braces)
```

The table (`alive` flag + one slot per region) is why a mouse-over trigger no
longer swallows the wheel everywhere: the engine matches the region only when
the helper reports the cursor really over it. If the helper is NOT running, the
file's built-in fallback matches every region (the old v18 behaviour) — the
helper is a **required component**, installed and kept in sync automatically
(§6.1).

The answer is a **set** because several zones can match one point (the
omnibox is inside the toolbar band, the page is inside the browser window) —
the original engine evaluated every trigger region independently. All 750s
of ONE input burst share a single helper answer (120 ms cache) — Chrome can
scroll the tab strip between them.

**Supported zones — ALL 12 areas verified by the user on a live browser,
2026-09-12:** 1 Browser window · 3 Web page · 4 Title area (the title bar /
tab strip row — the toolbar and the omnibox are NOT part of it) · 12 Browser tab · 15 Tab's close
button · 16 New tab button · 17 Tab's speaker icon (the tab must be playing
sound) · 20 Toolbar · 21 Omnibox · 30 Browser menu button (the "New Chrome
available" update pill counts as the kebab — it occupies its slot) ·
33 Bookmark button · 40 Any menu item (classified by the ENGINE itself, not
the helper). Each was picked in a real action and exercised with a physical
mouse wheel: over the right area the action runs, over the wrong one nothing
happens and the page keeps scrolling normally. Details and the
region-by-region evidence table: `Docs/TODO-mouseover-zones.md`.

**Files:**

| File | Role |
| --- | --- |
| `mv3-build/file76.dat` | **the deployed engine payload** — encode(patched v19), written by the extension (type 250) |
| `mv3-build/ac_zone_helper.dat` | **the deployed helper payload** — encode(ac_zone_helper.exe), written by the extension |
| `AutoControl_native/ac_zone_helper.exe` | the helper binary (our own C# program, self-contained) |
| `AutoControl_native/original/` | untouched upstream exes (patch input, hash reference) |
| `AutoControl_native/patched/` | the current engine build — the source of the bundled payload |
| `AutoControl_native/patches/patch_zones_v19.js` | engine patch builder: `original/` → `patched/` |
| `AutoControl_native/com.autocontrol.zonehelper.json` | native-host manifest template; the extension writes its own copy (`path` is **relative**, `allowed_origins` from the runtime ID) |
| `Test/ac_zone_helper.cs` | helper SOURCE — build recipe: `Docs/BUILD-NATIVE.md` §A; `Test/build_native.ps1` rebuilds it and checks the SHA-256 |
| `Test/dat_codec.js` | `.dat` payload codec (encode/decode/verify) — the packing half of the update protocol |
| `Test/zone_helper_smoke.js` | smoke test: `node Test/zone_helper_smoke.js [exe]` → `{"__id":7,"zone":…,"zones":[…]}` |
| `Test/zone_probe.ps1` | moves the cursor over a list of points and prints the helper's answer |
| `Test/zone_e2e_test.ps1` | end-to-end: injects a real wheel over a tab / the page and tails the SW zone log |
| `Test/zone_scan.ps1` .. `zone_scan4.ps1` | MSAA signature scanners (rows, element rects, children) |
| `mv3-build/sw.js` | SW gate (`__acDispatchTrigger750` + `__acBuildZoneMap` + `__acZoneAsk`) + the native bundle sync (helper install / engine replace) |

**Installation:** automatic — the extension writes
`ac_zone_helper.exe` + `com.autocontrol.zonehelper.json` into
`%UserProfile%\AppData\Local\AutoControl\` and registers the host (all known
vendor branches) on the first successful handshake; the manual `reg add`
commands are the fallback
([§6.3](#63-manual-host-registration-fallback)). The manifest's
`allowed_origins` is built from this extension's runtime ID — nothing is baked
in.

> ⚠ **Developer note:** the extension compares the deployed helper with the
> bundled payload on every SW session and overwrites it when it differs
> (`[AC-MV3-NATIVE]` log lines) — a rebuilt helper no longer needs a manual
> copy; just reload the extension. If your Chrome loads this extension from a
> COPY of the repo folder, `sw.js` **and the two `.dat` payloads** must be
> updated in that copy too — a stale copy silently keeps the old gate/helper.

---

### 4.3 Patched engine (`v19`, zone table + real input pass-through)

The mouse-over solution relies on a **patched engine** — the *only*
modification to the original binary in this port.

**What and why.** The original engine's zone classifier rejects most UI
regions on Chrome 148+ (the tab strip, the tab buttons, …), so those triggers
produce **no** 750 at all — the SW gate would have nothing to gate. An earlier
patch (`v18`) simply made the engine accept every UI zone; that turned out to
also break **input consumption**, because the same check decides whether the
wheel is consumed or passed through — pages stopped scrolling wherever a
mouse-over trigger existed.

`v19` fixes both: the classifier now **reads a zone table** that the helper
(§4.2) keeps up to date inside the engine's memory, so a region matches only
when the cursor is really over it — and the wheel passes through everywhere
else.

**The extension bundles and deploys this build itself**: `mv3-build/file76.dat`
is the encoded v19 payload; it is written into the host folder on a fresh
install/repair, and an engine that differs from the bundle (e.g. the old
unpatched distro build) is replaced automatically — the running engine is
stopped for a moment (see `Docs/BUILD-NATIVE.md` §D). The manual deploy script
below is a development tool.

| | |
| --- | --- |
| bundled payload | `mv3-build/file76.dat` (695296 bytes, md5 `2F878E9EB062C57D8B5C7FFBC91EAB5D`) — what the extension deploys |
| repo copy | `AutoControl_native/patched/AutoCtrl_2025.4.22.0.v19.exe` |
| patched file | `%LOCALAPPDATA%\AutoControl\AutoCtrl_2025.4.22.0.exe` (same size as the original — 695296 bytes) |
| bytes changed | exactly **40** (5 at the function entry + 35 in a code cave) |
| sha256 | `1A10EDD191B80A806DF66558B2B1E78BE8D6AD81E93EEAC772D13F222E212C3E` |
| pristine input | `AutoControl_native/original/AutoCtrl_2025.4.22.0.exe`, sha256 `8AE9A669086BEA5C4344007AC4CA9797E5814285E03B6B04E5F8336329CB7E09` |

At runtime the **zone helper** writes the table (`alive` flag + 64 region
slots) into the engine's memory; without the helper the file's built-in
fallback matches every region (v18 behaviour) — the helper is a **required**
component and is installed automatically (§4.2).

**Reproduce it bit-for-bit** (verified: rebuild → identical hashes):

```
powershell -ExecutionPolicy Bypass -File Test/build_native.ps1
# === 1/3  ENGINE (original + byte patch)  ... 695296 bytes  1A10EDD191B80A806DF66558B2B1E78BE8D6AD81E93EEAC772D13F222E212C3E  OK
# === 2/3  HELPER (our C# source)         ...  22528 bytes  C8466CF7CE1AC40C3A56AAD175B0F545B914E670679B495C2199E469A483ABAF  OK
# === 3/3  BUNDLE (file76.dat + ac_zone_helper.dat) ... both payloads verify OK
# (add -UpdatePatched to refresh AutoControl_native/patched/, -UpdateBundle for the .dat payloads)
```

**Full byte-level recipe** — every offset, both code variants of the cave, the
runtime table layout, the deploy/rollback steps and the helper's build
instructions: **`Docs/BUILD-NATIVE.md`**. Reverse-engineering background and
the whole patch history (v5b…v19): `Docs/archive/NATIVE-REVERSING-2026-08-31.md`
(§10–§13) and `Docs/TODO-mouseover-zones.md` §2e/§2g.

Deploy (development tool — the extension deploys/updates the engine itself):
`powershell -File Test/deploy_patched_engine.ps1` (defaults to
`AutoControl_native/patched/`; stops Chrome SxS, backs up to `.orig`, verifies
the hash; `-Source <exe> -Force` deploys something else). The engine **must**
keep the `AutoControlZero.exe` proxy chain — do not run it standalone.

> **Why not patch the engine to classify zone 12 for real?** It was
> attempted (v9: fresh role checks; v17: fresh `AccessibleObjectFromPoint`
> in the hot path). The role checks read a hover cache that never refreshes
> over the tabs, and the fresh MSAA call **deadlocks** inside the hook
> context (proven live, RE doc §12). The external helper (§4.2) is the
> proven safe way to get the real zone.

---


## 5. Run Script actions — quick check

1. Open the options page (toolbar icon → settings).
2. Create a advanced script action with, e.g., `alert('hello')`, or use
   the built-in example ("Download all images").
3. Trigger it on any normal web page (not `chrome://` / Web Store — user
   scripts don't run there).
4. The page console + SW console show `[AC-DLV]` / `[AC-SW] execUserFunc`
   lines — the script ran.

Full in-browser self-test: `Test/SCRIPTING-API-TEST.js` (23 checks, run via the
RUN SCRIPT action; the harness is described in `Test/README.md`).

---

## 5a. Known issues — mouse-over zones in Chromium forks (2026-09-15)

The zones are classified by the external helper (`ac_zone_helper.exe`) via MSAA.
Chrome / Chrome Canary / Brave expose the same accessibility tree, so **all
zones work there** (verified live, including the tab's speaker icon while a tab
plays sound). Opera and Vivaldi render their own UI and expose **different**
trees; the helper was adapted for them on 2026-09-15.

### Compatibility matrix (zone → browser)

| Zone (as shown in the action editor) | Chrome | Brave | Opera | Vivaldi |
|---|---|---|---|---|
| Browser window | ✅ | ✅ | ✅ | ✅ |
| Web page | ✅ | ✅ | ✅ | ✅ |
| Title area (title bar / tab strip) | ✅ | ✅ | ✅ | ✅ |
| Browser tab | ✅ | ✅ | ✅ | ✅ |
| New tab "+" | ✅ | ✅ | ⚠️ † | ❌ |
| Toolbar | ✅ | ✅ | ✅ | ✅ |
| Omnibox / address bar | ✅ | ✅ | ✅ | ✅ |
| Bookmark button | ✅ | ✅ | ✅ | ❌ |
| Browser menu button | ✅ | ✅ | ✅ | ✅ |
| Tab's close button | ✅ | ✅ | ✅ | ⚠️ ‡ |
| Tab's **speaker** icon | ✅ | ✅ | ❌ * | ❌ * |

\* **The tab's speaker icon cannot work in Opera/Vivaldi** — the sound is drawn
over the favicon in a single element (role 40 in Opera, an unnamed role-20
box in Vivaldi) present on **every** tab, so a playing tab is
indistinguishable from a silent one. This is not implementable via MSAA.

† **In Opera the "+" is reported as the Browser tab (12)** — its parent is the
`Tab Bar` element, not the tab list, so a trigger bound to this zone does not
fire there; a wheel over the "+" runs the zone-12 action instead. Cosmetic for
most setups, but worth knowing when a "new tab" trigger seems dead in Opera.

‡ **In Vivaldi the close button is reported working but was not probed
separately** (2026-10-05). The recognition follows the tab's actual structure
instead of a fixed layout, and the same code handles Chrome, so the earlier
"missing in Vivaldi" note is likely obsolete — a dedicated probe is still
pending (see `Docs/TODO-mouseover-zones.md`, the Vivaldi quirks).

* **Opera exposes a tab's close button as a plain pane, not a button** — the
  helper finds it by shape (a square element in the right part of the tab), so
  the zone works there too (fixed 2026-09-20; in some Opera builds the button is
  a real button nested one level deeper instead — both shapes are handled since
  2026-10-04).

Additional notes:

* **Vivaldi must be started with `--force-renderer-accessibility`** — without
  it its whole UI (toolbar, tabs) is invisible to MSAA and every point
  classifies as the page.
* Vivaldi keeps its entire UI *inside* the page document in the a11y tree —
  the helper detects this and treats it as browser chrome (fixed 2026-09-15).
* **Opera's bookmark button (the heart) is matched by its accessible name**
  ('Add to bookmarks' / 'Edit bookmark') — it is structurally identical to its
  neighbours (Snapshot, Send to My Flow…), so the tree alone cannot tell them
  apart (fixed 2026-09-20). The same day the title area (4) was narrowed to the
  title bar / tab strip row only (the toolbar and the omnibox are excluded) and
  the browser tab (12) now requires a real tab (the empty strip area no longer
  matches).
* **The tab's close button is recognized in every layout seen so far** — it is
  a real button inside the tab in Chrome and in Opera, but Opera may nest it one
  level deeper (inside the tab's body), and some builds expose it as a plain
  square element on the right of the tab. All three shapes are handled, and the
  close button is told from the tab's speaker icon by their order inside the tab
  (fixed 2026-09-21).
* **In Opera/Vivaldi the rightmost toolbar button is the extensions-panel
  toggle** ('Extensions'), not a browser menu — the menu is on the LEFT in
  those forks. The Chrome-style "right edge" rule therefore no longer runs
  there (the menu is found by name), and a button named 'Extensions' never
  counts as the menu button (fixed 2026-09-20).
* **An open browser menu is not browser chrome** — while a browser menu or
  dropdown covers the tab strip, the zones report only "Browser window" (the
  cursor is over the menu, not over the chrome), so a zone trigger cannot fire
  through it (fixed 2026-09-20).
* **Zones react instantly to a moved cursor** — the helper refreshes the zone
  data as soon as the cursor settles (a 30 ms poll), because the native engine
  caches the region verdict for a few hundred milliseconds; a late update made
  the first wheel notch after a move miss (fixed 2026-09-20).
* **Actions that target the “hovered tab” follow the cursor again** — Chrome
  148+ removed the native information about which tab the mouse is over, so
  such actions used to hit the first hovered tab (usually the active one). The
  zone helper supplies that information now (fixed 2026-09-20).
* **Actions that target the “event tab” work again** — the same removed native
  information made this target resolve to *nothing* on Chrome 148+: the action
  ran over an empty tab list and silently did nothing (for example “reload the
  tab the event happened on”). For mouse events the event tab is the tab under
  the cursor, and that tab is used now (fixed 2026-09-20).
* ⚠ **Ignore the red “This feature is not supported in Opera/Vivaldi” banner
  in the tooltips** — it is a hard-coded browser-NAME check from the original
  author, not a capability test, and it is outdated: the tab-strip features it
  warns about (Hovered tab, Mouse over) work with the zone helper. It is still
  shown for “Copy hovered URL” / “Open hovered URL” / the omnibox placeholder,
  which were not verified in those browsers.

---

## 6. Troubleshooting

| Symptom | Where to look |
| --- | --- |
| Scripts don't run / `userScripts API unavailable` | [§3.1](#31-extension-toggles) — enable "Allow user scripts" |
| `getFile` on a local file fails | [§3.1](#31-extension-toggles) — enable "Allow access to file URLs" |
| Nothing works (no hotkeys) — native not connected | §6.2 (connection), §6.4 (repair) |
| The extension "restarts" while the installer runs | §6.2 — the one-time auto-reload, expected |
| Native component broken/missing, keys lost | §6.3 (manual registry), §6.4 (uninstall/reinstall) |
| `Extension context invalidated` in the page console | stale page after an extension reload — reload the page |
| Remaining port limitations | [`Docs/FEATURES-MV3.md`](Docs/FEATURES-MV3.md) §7 (port gaps), §8 (impossible in MV3 by design) |

### 6.1 Verification checklist

> Console lines below are visible only when logging is on ([§7](#7-debugging-and-logging)).

- In the settings no error message.
- Service worker console shows `[AC-MV3] Native connected successfully!`
  and `[AC-MV3] ✓ Core bundle loaded`.
- `[AC-MV3] Handshake: sending file check (type 10)...` followed by a
  `Handshake response:` that is not `CB-TIMEOUT`.
- `[AC-MV3-NATIVE] checking deployed engine + zone helper...` followed by
  `engine OK: deployed == bundled patched build` and
  `zone helper connected: …` (the auto-deploy keeps both in sync).
- A hotkey/gesture actually triggers an action (native sends type 750 →
  `[AC-MV3-SW] ← Trigger 750 id=...` in the SW console).

**What a finished install looks like** (the automatic flow produces this):

- `%UserProfile%\AppData\Local\AutoControl\` contains `AutoControlZero.exe`
  (proxy/launcher — the same binary doubles as the installer),
  `AutoCtrl_2025.4.22.0.exe` (the patched engine), `AutoControl.manifest`,
  `ac_zone_helper.exe` and `com.autocontrol.zonehelper.json`;
- the registry keys exist for the browser you use —
  `HKCU\SOFTWARE\Google\Chrome\NativeMessagingHosts\hrich.autocontrol` and
  `…\com.autocontrol.zonehelper` (other browsers: §6.3);
- ⚠ The installer registers **only the Chrome engine key**; the helper key,
  every other branch and the engine/helper payloads are deployed by the
  extension itself (§4.2, §4.3).

### 6.2 Connection does not establish / nothing works

1. **Reload the extension** (`chrome://extensions` → reload icon) — the worker
   re-runs the whole install path (deploy engine → reconnect).
2. **Check the host files + registry** (list in §6.1). A plain folder copy alone
   does NOT register a host — re-run the installer, or use the manual `reg add`
   commands in §6.3 if a key is missing.
3. **Second browser / a fork whose branch has no key at all** — the sync
   registers every known branch (Chrome, Chrome SxS, Edge, Brave, Opera,
   Vivaldi, Chromium, Yandex), but it needs ONE successful connection to run: a
   browser with no key yet needs the first manual `reg add` (§6.3) or one run of
   the extension in a browser that already has its key. Restart the browser once
   after the key appears (the host list is cached at startup). **Brave needs
   nothing** — it falls back to Chrome's branch.
4. **The extension "restarts" by itself while the installer runs** — expected:
   while the install pane waits and the host lookup is cached as "not found"
   (per worker instance), the extension reloads itself once after ~20 failed
   pings so the fresh worker can see the new host, then reopens the settings.
   Nothing is lost; just let it finish.
5. **Manual component copy (last resort)** — the extension deploys the
   **patched** engine and the helper itself; if that keeps failing, copy
   `AutoControl_native\patched\AutoCtrl_2025.4.22.0.v19.exe` and
   `AutoControl_native\ac_zone_helper.exe` (plus
   `AutoControl_native\com.autocontrol.zonehelper.json`) into
   `%UserProfile%\AppData\Local\AutoControl\` by hand, then reload the
   extension. (These are the same builds the extension deploys — you can verify
   them against the hash table in
   [§4.0](#40-where-the-native-binaries-come-from), e.g. for an antivirus
   false-positive check.)
6. **If gestures stop working after a crash-loop** — kill all
   `AutoControlZero.exe` / `AutoCtrl_2025.4.22.0.exe` processes (Task Manager or
   `Get-Process | Where-Object {$_.ProcessName -match 'AutoControl|AutoCtrl'} | Stop-Process -Force`),
   then reload the extension — lingering duplicate engine processes conflict and
   can crash the engine (type 140).

### 6.3 Manual host registration (fallback)

Normally not needed: after the first successful connection the extension
registers **both** hosts (engine + helper) for every known branch. Chrome reads
native hosts from the registry only, and the manifest's `path` is relative to
its own folder. Run from `cmd`:

Chrome (the installer already writes the engine half):

```cmd
reg add "HKCU\Software\Google\Chrome\NativeMessagingHosts\hrich.autocontrol" /ve /t REG_SZ /d "%LOCALAPPDATA%\AutoControl\AutoControl.manifest" /f
reg add "HKCU\Software\Google\Chrome\NativeMessagingHosts\com.autocontrol.zonehelper" /ve /t REG_SZ /d "%LOCALAPPDATA%\AutoControl\com.autocontrol.zonehelper.json" /f
```

Opera and Vivaldi read native hosts only from their OWN branches:

```cmd
reg add "HKCU\Software\Opera Software\NativeMessagingHosts\hrich.autocontrol" /ve /t REG_SZ /d "%LOCALAPPDATA%\AutoControl\AutoControl.manifest" /f
reg add "HKCU\Software\Opera Software\NativeMessagingHosts\com.autocontrol.zonehelper" /ve /t REG_SZ /d "%LOCALAPPDATA%\AutoControl\com.autocontrol.zonehelper.json" /f
reg add "HKCU\Software\Vivaldi\NativeMessagingHosts\hrich.autocontrol" /ve /t REG_SZ /d "%LOCALAPPDATA%\AutoControl\AutoControl.manifest" /f
reg add "HKCU\Software\Vivaldi\NativeMessagingHosts\com.autocontrol.zonehelper" /ve /t REG_SZ /d "%LOCALAPPDATA%\AutoControl\com.autocontrol.zonehelper.json" /f
```

- From **PowerShell** use `$env:LOCALAPPDATA` instead of `%LOCALAPPDATA%`
  (PowerShell would otherwise store the variable name literally).
- The same pattern works for the other branches the sync knows (Chrome SxS,
  Chromium, Yandex); **Brave needs nothing** — Chrome's branch is enough
  (verified 2026-09-15). Its own branch, if you ever want it explicit:
  `HKCU\Software\BraveSoftware\Brave-Browser\NativeMessagingHosts\hrich.autocontrol`
  and `…\com.autocontrol.zonehelper` (same values as the Chrome ones).
- Restart the browser afterwards. These keys do not travel with a portable
  browser folder — re-run them after copying to another machine.

### 6.4 Repair / Reinstall / Uninstall

- **Native component could not be updated automatically** (a popup +
  notification says so): the settings' "Reinstall native component" button is
  NOT shown while the native is connected, so use the working path — in the
  settings select **Uninstall native component**, run the installer again, then
  restart the extension. The extension then deploys the patched engine and the
  zone helper from its bundle again.
- **Emergency Repair** (right-click the extension icon → context menu →
  **Emergency repair**, or the repair button in the settings error message):
  the extension restarts its own worker (the MV3 equivalent of reloading the
  MV2 background page), which reconnects the native and spawns a fresh engine.
  The icon badge shows **Wait → OK/Error**. The engine is **never hard-killed**
  (a forced kill can leave dangling input hooks — the 2026-08-08 measurement saw
  ~40 s without input; a 2026-10-10 re-measurement saw the first trigger in
  under a second, but avoid manual kills anyway).
- **REPAIR COMPLETE popup** — after a repair, if the diagnostics found a
  problem, a popup window shows it (same as the original MV2 extension):
  - **stuck keys/buttons** — the keys and mouse buttons that were in the
    pressed state at the moment of the repair, plus advice about adding a
    wildcard to your triggers and the **Options → Advanced Options → "Ignore
    synthetic input"** setting;
  - **foreign profile** — a window that was misidentified as belonging to a
    different browser profile, with tips on how to report the situation.
  If nothing was detected, only the badge is shown — no popup.
- **Reinstall native component** — for a host that is broken or missing (the
  installer was removed, a registry key is gone): run the installer from the
  settings error message exactly as in §4.1.
- **Uninstall native component** (in the settings) removes everything itself in
  one pass: both host registrations for all browsers, every helper/engine/Zero
  process and the whole `%UserProfile%\AppData\Local\AutoControl` folder — no
  locked-file error and no "remove the extension from all your browser
  profiles". Reinstalling brings both components back; the page reloads into the
  install view once the native is actually gone.
- **A browser that lost the component reconnects by itself (2026-10-11)** —
  when the native component comes back (for example it was reinstalled in
  another browser — that registers the host for every installed browser), a
  browser that had lost it picks it up automatically within about a minute and
  re-sends the config: no Emergency Repair and no manual reload needed. The
  error dialog's **Reload extension** button performs exactly the same restart
  as Emergency Repair. A settings page stuck on the install or error state from
  the outage returns to the normal settings view by itself once the connection
  is back (no F5).
- **Upgrading from an older build** — automatic: an engine or helper that
  differs from the bundled ones is replaced (the running engine is stopped for a
  moment — see §4.3). If that fails, use **Reinstall native component** and
  reload.
- After a reinstall/repair, the extension re-deploys the engine and re-sends the
  config automatically — hotkeys work without an extension reload.

---

## 7. Debugging and logging

All console output of the MV3 port is UI-controlled — three checkboxes in
**Options → Advanced Options** (disabled by default — MV2-like silence;
enable the checkboxes to see logs):

| Checkbox | advOpts key | Silences |
| --- | --- | --- |
| **Log service worker** | `logSw` | SW console + the whole imported bundle (`[AC-MV3]`, `[AC-DLV]`, `[AC-ACT]`, `[AC-F]` …) |
| **Log page scripts** | `logPage` | tab consoles — the file42 bridge (`[AC-F42]` lines) |
| **Log settings page** | `logSettings` | settings page console (`[AC-MV3-SHIM]` lines) |

- Changes apply **live** (`chrome.storage.onChanged`) — no extension reload
  needed, ~0.3 s debounce.
- Startup output is **buffered** until the saved flag is read — with a
  checkbox unchecked, not even the first init lines appear (no "logs show
  with a delay" after a reload).
- `console.error` is **always kept** — real failures stay visible regardless
  of the checkboxes.

**Telemetry** — the extension sends NO usage data by default (privacy) since
the extension is no longer maintained. You can enable it in **Options → Advanced Options → "Send anonymous usage data"**. The flag applies live, no reload needed.

Where to look for each console:

- **SW console**: `chrome://extensions` → AutoControl → *service worker* link.
- **Tab console**: F12 on the page where the script runs. The bridge is
  **passive** — `[AC-F42]` lines appear only while a RUN SCRIPT action or an
  `ACtl.*` call is being processed (DevTools must be open; plain browsing
  produces nothing).
- **Settings page console**: F12 on `main.html`.
