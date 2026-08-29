# AutoControl MV3 — Installation Guide (unpacked build)

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
- **Chrome Web Store**: <https://chromewebstore.google.com/detail/autocontrol-keyboard-shor/lkaihdpfpifdlgoapbfocpmekbokmcfd/>

**What is original and what is ported:**

- **The bulk of the logic is the ORIGINAL obfuscated MV2 code** (`file*.js`
  sources) — triggers, actions, config chain, settings UI logic. The port
  reuses these files as-is (they are byte-identical to the MV2 originals
  where possible), some files are patched.
- **The MV3-specific pieces are written from scratch** — the service-worker
  brain (`sw.js`), the bundle glue (`sw_prelude.js`), the page-side shims
  (`mv3_shim.js`, `mv3_native_shim.js`), the offscreen document, and the
  test harness (`mv3-build/mh_test.js`). These replace the MV2 background
  page and adapt the original code to Manifest V3 APIs.
- **The native component is the ORIGINAL AutoControl binaries** — the
  extension embeds and deploys the original `AutoControlZero.exe` (proxy/
  launcher, also the installer) and `AutoCtrl_2025.4.22.0.exe` (engine). No
  modified or rebuilt copies are shipped (see [§4.0](#40-where-the-native-binaries-come-from-they-are-the-originals)).

**About the port itself**: the MV3 port was made **entirely and solely with
the help of an LLM** — the MV3-specific code, the shims, the service-worker
brain, and the porting work itself were written with AI assistance, without
a human developer authoring the port by hand.
The human role was reviewing, testing and guiding the process.

> The MV2 baseline lives in `ext-mv2/` and is kept **untouched** — it is the
> reference for the port and must not be edited.

---

## 2. Repository structure

```text
AutoControl-Keyboard-shortcuts-Mouse-gestures-Chrome/
├── README.md               # This file (user manual)
├── AGENTS.md               # Working rules for LLM agents / contributors
├── CHANGELOG.md            # User-facing changelog (Keep a Changelog)
├── ext-mv2/                # ORIGINAL MV2 extension (reference baseline) — DO NOT EDIT
├── mv3-build/              # the MV3 port — load this folder as an unpacked extension
│   ├── sw.js               #   Service worker (SW-brain)
│   ├── sw_core_bundle.js   #   Concatenated core bundle (prelude + file*.js)
│   ├── manifest.json       #   Manifest V3
│   ├── main.html           #   Settings page (UI)
│   └── file*.js            #   Original obfuscated and patched MV2 files
├── AutoControl_native/     # Native host: manifest + decrypted original exes
│   ├── AutoControl.manifest
│   ├── AutoControlZero.exe        # proxy/launcher (= installer)
│   └── AutoCtrl_2025.4.22.0.exe   # engine (global hooks)
├── Test/                   # Test artifacts: API self-test + settings snapshot
├── Docs/                   # Protocol reference, feature status, deobfuscation map
│   └── archive/            # Historical docs (closed bug reports, old snapshots)
└── Toolbar-buttons/        # Auxiliary toolbar-button extensions (MV2/MV3 pairs)
```

- **`ext-mv2/`** — the original MV2 extension (upstream baseline). **Reference only — do not edit.**
- **`mv3-build/`** — the MV3 port. **This is where all work happens.** Load
  folder in Chrome as an unpacked extension (see [§3](#3-install-the-extension-unpacked)).
- **`AutoControl_native/`** — NOT a separate component: it is the *decrypted*
  copy of the two original executables plus the host manifest, kept **for
  manual installation** and for antivirus/security review. The extension
  never reads it — it deploys the binaries from its own embedded blobs
  (`file69.dat` / `file76.dat`, see [§4.0](#40-where-the-native-binaries-come-from-they-are-the-originals)). Manual install path: copy this
  folder's contents to `%UserProfile%\AppData\Local\AutoControl\` and
  register the host (see [§4.1 Installation](#41-installation)).
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
| **Allow access to file URLs** | ⚠️ optional | Needed **only** if you use local `file://` paths: `ACtl.getFile('C:\\...')`, `ACtl.saveURL(..., 'C:\\...')`, local page access / `file://` URL conditions in triggers. Same requirement as MV2. Leave off if you don't use file paths. |
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

### 4.0 Where the native binaries come from (they are the ORIGINALS)

The installer and the native component are the **original AutoControl
binaries** — this MV3 port does not ship any modified/rebuilt copies. Both
are embedded **inside the extension itself** and deployed from there:

| Embedded in the extension | MD5 of the `.dat` blob (encrypted) | Decrypted content | MD5 (decrypted) |
| --- | --- | --- | --- |
| `file69.dat` (332,800 B) | `64034DE600F897CBDC131E6EBAFEBE88` | **`AutoControlZero.exe`** — the proxy/launcher; the same binary doubles as the **installer** (`Native-Component.exe`, install/uninstall mode via `/noConfirm`) | `FF33A86EC873836A51CEC8F77B8C0B49` |
| `file76.dat` (695,296 B) | `6BF791F5B2D267834A52A47E8CC3C2F4` | **`AutoCtrl_2025.4.22.0.exe`** — the engine (global hooks, triggers, input) | `D9BE9A1099D70FAFCEB59EF22DA5B44A` |

The `.dat` blobs are the **encrypted** form of the executables — that is why
their MD5 differs from the decrypted exes. To verify a binary against the
table, hash the files in `AutoControl_native\` (the decrypted copies) or
decrypt the `.dat` first; both `ext-mv2/` and `mv3-build/` carry
**byte-identical** blobs (same MD5).

**`AutoControl_native/` in this repo is NOT a separate/custom component** —
it is simply the *decrypted* copy of those same two files (plus the host
manifest) for manual installation and for antivirus/security review. The
extension never reads it: the installer is extracted from `file69.dat` and
the engine from `file76.dat`.

### 4.1 Installation

**Normal flow** (recommended):

1. Load the extension (`chrome://extensions` → `Developer mode` → `Load unpacked`
   → `mv3-build/`).
2. Open the extension — the **install pane** will be shown ("the native component
   is not installed").
3. Click **Install**. The extension will extract the original installer from its
   own bundle (nothing is downloaded from anywhere).
4. Run it.
5. Everything after the installer finishes is **automatic** (no manual file
   copying, no extension reload):
   - the installer deploys `AutoControlZero.exe` + `AutoControl.manifest` to
     `%UserProfile%\AppData\Local\AutoControl\` and registers the host in the
     registry (`HKCU\SOFTWARE\Google\Chrome\NativeMessagingHosts\hrich.autocontrol`);
   - the extension reconnects on its own; if the engine
     `AutoCtrl_2025.4.22.0.exe` is missing, it **unpacks it itself** from the
     bundled `file76.dat` and writes it into the host folder — the whole
     install takes ~8 seconds, before the settings import/verification even
     starts;
   - the install pane closes and the settings page opens.
6. Verify:
   - Task Manager shows a running `AutoCtrl_2025.4.22.0.exe` process;
   - no native error in the settings;
   - ServiceWorker console log: `Engine missing/starting (answer 2) — waiting for it to come
   up` → `Engine written — polling on the same port (MV2 style)` →
   `Engine ready ... after N poll(s)` → `Native connected successfully!`;
   - gestures and hotkeys work.

**When something goes wrong — Repair:**

- **Emergency Repair** (right-click the extension icon → context menu → **Emergency
  repair**, or the repair button in the settings error message): the
  extension restarts its own worker (the MV3 equivalent of reloading the MV2
  background page), which reconnects the native and spawns a fresh engine.
  The icon badge shows **Wait → OK/Error**. The engine is **never hard-
  killed** (a forced kill leaves dangling input hooks that stall keyboard/
  mouse for ~40 s).
- **REPAIR COMPLETE popup** — after a repair, if the diagnostics found
  a problem, a popup window shows it (same as the original MV2 extension):
  - **stuck keys/buttons** — the keys and mouse buttons that were in the
    pressed state at the moment of the repair (e.g. if you held a key while
    repairing, it is listed), plus advice about adding a wildcard to your
    triggers and the **Options → Advanced Options → "Ignore synthetic
    input"** setting;
  - **foreign profile** — a window that was misidentified as belonging to a
    different browser profile, with tips on how to report the situation.
  If nothing was detected, only the badge is shown — no popup.
- **Reinstall native component** — use this when the host itself is broken
  or missing (e.g. after the installer was removed or the registry key is
  gone): run the installer from the settings error message exactly as in the
  normal flow above.
- After a reinstall/repair, the extension re-deploys the engine and re-sends
  the config automatically — hotkeys work without an extension reload.

> **Troubleshooting — if the connection does not establish within ~15 seconds:**
>
> 1. **Reload the extension** (`chrome://extensions` → reload icon) — the SW
>    re-runs the whole install path (deploy engine → reconnect).
> 2. **Check the host files + registry** — `%UserProfile%\AppData\Local\AutoControl\`
>    must contain `AutoControlZero.exe` + `AutoCtrl_2025.4.22.0.exe` +
>    `AutoControl.manifest`, and the key
>    `HKCU\SOFTWARE\Google\Chrome\NativeMessagingHosts\hrich.autocontrol`
>    must point at that manifest (a plain folder copy alone does NOT register
>    the host — re-run the installer if the registry key is missing).
> 3. **Manual engine copy (last resort)**: if the auto-deploy keeps failing,
>    copy `AutoControl_native\AutoCtrl_2025.4.22.0.exe` from this repo into
>    `%UserProfile%\AppData\Local\AutoControl\` by hand, then reload the
>    extension. (These files are the same originals the extension deploys —
>    see [§4.0](#40-where-the-native-binaries-come-from-they-are-the-originals); you can verify them against the MD5 table there, e.g. for an
>    antivirus false-positive check.)
> 4. **If gestures stop working after a crash-loop**: kill all
>    `AutoControlZero.exe` / `AutoCtrl_2025.4.22.0.exe` processes (Task Manager
>    or `Get-Process | Where-Object {$_.ProcessName -match 'AutoControl|AutoCtrl'}
>    | Stop-Process -Force`), then reload the extension — lingering duplicate
>    engine processes conflict and can crash the engine (type 140).

### 4.2 Verification checklist

> Following is visible only when logging is on.

- In the settings no error message
- Service worker console shows `[AC-MV3] Native connected successfully!`
  and `[AC-MV3] ✓ Core bundle loaded`.
- `[AC-MV3] Handshake: sending file check (type 10)...` followed by a
  `Handshake response:` that is not `CB-TIMEOUT`.
- A hotkey/gesture actually triggers an action (native sends type 750 →
  `[AC-MV3-SW] ← Trigger 750 id=...` in the SW console).

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
RUN SCRIPT action; see `AGENTS.md`).

---

## 6. Troubleshooting references

| Symptom | Where to look |
| --- | --- |
| Scripts don't run / `userScripts API unavailable` | [§3.1](#31-extension-toggles) — enable "Allow user scripts" |
| `getFile` on a local file fails | [§3.1](#31-extension-toggles) — enable "Allow access to file URLs" |
| Nothing works (no hotkeys) | [§4](#4-native-component-hrichautocontrol) — native component not connected |
| `Extension context invalidated` in the page console | stale page after an extension reload — reload the page |
| Remaining port limitations | [`Docs/FEATURES-MV3.md`](Docs/FEATURES-MV3.md) §7 (port gaps), §8 (impossible in MV3 by design) |

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
