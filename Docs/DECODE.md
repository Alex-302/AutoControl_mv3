# AutoControl Deobfuscation Map

## Core Variables
| Obfuscated | Meaning | Description |
|-----------|---------|-------------|
| `_9j` | `window` | Global window object |
| `_Yk` | `chrome` | Chrome API alias |
| `_Tj` | `chrome.runtime.id` | Extension ID |
| `_cg` | Generator wrapper | `(gen) => (...args) => { ... gen(...args).next() ... }` |
| `_we` | Same as `_cg` | Generator function creator |
| `_ti` | `setTimeout` | Async scheduler |
| `_za` | `ms => new Promise(r => setTimeout(r, ms))` | Sleep/delay |
| `_Yd` | `Promise.race` | Race two promises |
| `_Jw` | `Array.isArray` | Check if array |
| `_ul` | `x => x == null` | Is null/undefined |
| `_zh` | Tab URL getter | Gets tab URL from tab object |
| `_js` | Tab ID generator | Creates tab ID |
| `_Np` | Current tab ID | Active tab ID |
| `_4t` | Current window ID | Active window ID |
| `_na` | Window handle map | Maps window IDs to native hWnds |
| `_Or` | hWnd→windowID map | Reverse mapping |
| `_cd` | Window cache | `{windowId: window}` |
| `_Yp` | Tab cache | `{tabId: tab}` |
| `_Eu` | Init signal | `_Wf` one-shot signal emitter |
| `_Wf` | Signal class | `{send(value), wait()}` one-time event |
| `_Ot` | **Telemetry sender** | **HTTP POST to `https://www.autocontrol.app/appEvent` (NOT native)** — the single analytics endpoint (events: install/update/error/NH-error/userReload/diagnostics). MV3: gated by `__acTel` (from `advOpts.telemetry`, **off by default** — nothing is sent until the user enables it in Options → Advanced Options); the callback `c` is still invoked when disabled (some call sites wait for it). Logs `[AC-TEL] send|skipped event=<name>` (follows the AC_LOG_* gate). Payload built with `_yp` (FormData) → `_1p(_Zo+"appEvent","json","POST",...)`; fields include extName/extVer, instID `_7y`, timeOffset (`Date.now()-_Ct`), OS/browser, page URI, ctxData (natHostVer/scaleFctr), evtData, domain. |
| `_yp` | FormData builder | `a => { let b = new FormData; for (let [c,d] of a) b.append(c,d); return b }` — used by `_Ot` |
| `_mo` | (domain) | `"www.autocontrol.app"` (file10.js) — site-bridge gate host |
| `_Zo` | (endpoint base) | `"https://" + _mo + "/"` — `_Zo + "appEvent"` = the telemetry URL; `_4a` help links (file78) |
| `_9n` | (mirror host) | `"alex-302.github.io"` (file10.js) — GitHub Pages mirror of the site; accepted by the webSettgs gate since 2026-08-29 |
| `_Zr(tabId)` | Site-bridge injection (file62_mv3) | On `tabs.onUpdated` "complete" (`_Fd`=6) for a tab whose hostname is `_mo`/`_9n`: `chrome.scripting.executeScript({target:{tabId}, world:"ISOLATED", injectImmediately:true, func, args:["2025.4.22"]})` — MV2 parity (tabs.executeScript = isolated world; the MAIN-world `__acInjectCode` has no `chrome.runtime`). ⚠ `ScriptInjection` has NO `runAt` (only tabs.executeScript/contentScripts.register do) — using it throws `Unexpected property: 'runAt'` SYNCHRONOUSLY (the .catch never fires); the equivalent is `injectImmediately:true` (Chrome 102+). Injects: `window._ACtlExt[ver]`, a `webSettgs` listener sending `{[btn.value]: decodeURI(closest("a").href)}` to the SW, and an immediate `redirSttgs` probe. ⚠ Hardened 2026-08-29: `(document.head||document.documentElement)` (head can be NULL at document_start) + try/catch (listener registers FIRST). sw.js `__acReinjectSiteBridge()` also calls `_Zr` for already-open site tabs at SW start (MV2's `_zg` re-injection; a tab opened before SW start otherwise never gets the bridge — onUpdated "complete" won't re-fire). ⚠ Hardened 2026-08-30: `c()` guards `chrome.runtime.sendMessage` + the `webSettgs` listener wraps the call in try/catch — after an extension reload the OLD injected listener (dead context) throws `Extension context invalidated` / `chrome.runtime undefined` on every Import/View click (noise; the NEW injection still handles the event). The stale listener can only be purged by reloading the site tab |
| `_ja(url)` | Site-import (SW re-implementation 2026-08-29) | MV2: file78 `_ja` = fetch the `.acs` (`_1p`+`_mg`) → `_kp(b,"add",!0)` → `_uw` → `_lj` (UI: toasts, permission prompts). MV3: file78 is NOT bundled → `window._ja` undefined → file48 `m()` `imprtSttgs` died in the SW. sw.js re-implements `window._ja` with the UI-free pipeline: fetch → `JSON.parse` → `_Qj({}.add(_2d,data))` (`_2d` = default shape `{trigActList:[],customEntities:{},toolbarBtns:{},sections:[]}`) → `_9i(_2d,cb)` (load existing) → `_K(l,merged,true,true)` (dedupe/renumber) → `_4p(l,merged,false)` (merge-add) → `_bd(out)` (save) → `_ku()` (config rebuild → native type 60). No toast (page-side `_lj` not ported). ⚠ file48 `m()` routes `{imprtSttgs}` via `(window._ja||l)(url)` — the MV2 `l` (`_Es` debounce → `_0j()` → settings-page window via `_0s()`/`chrome.extension.getViews({tabId})[0]`) CANNOT work in the MV3 SW (getViews is empty) — direct `window._ja` call required |
| `webSettgs` bridge | page → extension | Site pages (basics.js) dispatch `webSettgs` from `acs button[value]` clicks ONLY when `ACtlExt[ver]` is in the DOM (i.e., the extension injected it). SW side (file48 `m()`): `imprtSttgs:<url>` → settings import (`_ja`), `viewSttgs:<url>` → open `main.html?file=<url>`, `redirSttgs:<url>` → update current tab |
| `__acTel` | Telemetry gate (MV3) | `false` by default; read from `chrome.storage.local` `advOpts.telemetry`; live via `storage.onChanged`; gating `_Ot` |
| `_9k` | localStorage setter | **`localStorage.setItem`/`removeItem`** (NOT `chrome.storage.local`!). `_9k(a,b)` = `setItem(a, JSON.stringify(b))`, `b==null` = `removeItem(a)`. Used for ephemeral flags: `showNotif`, `noStupEvt`, `extensionState`, `diagnostics`, `NHInitData`. **In the SW this is a no-op/undefined-safe — SW keeps such flags in memory instead.** |
| `_j(a)` | localStorage get | `JSON.parse(localStorage.getItem(a))` |
| `_nt(a)` | localStorage get+remove | `_j(a)` then `removeItem(a)` — one-shot flags (e.g. `_nt("showNotif")` consumes the badge request after a repair) |
| `_Aw` | lastError reader | `(a,b,c)=>_Yk.runtime.lastError` (file13) — captureTab null-guard (`_Aw()?1==a.length&&(c[f]=null)` — captureVisibleTab failed → null dataUri), event-dispatch check in `_kr` |
| `_Vt(a)` | windows.getAll | `(populate=false)=>cb=>windows.getAll({populate, windowTypes:_Ge}, c=>cb(c.filter(d=>!_9j._Ld[d.id])))` (file13) — base for `_Fu` enum |
| `_id` / `_es` | File-scheme gate | `isAllowedFileSchemeAccess` result + regex `^(chrome|edge|about:|data:|view-source:|https:\/\/chrome.google.com\/webstore\/` (+ `file:` if **NOT** allowed) — `_As(a)=_es.test(a)` (file13). In the SW the prelude passes the REAL API through (`__acRealFileSchemeAccess`; before: hardcoded `cb(false)` → file:// ALWAYS restricted → `Q()` in file77 excluded them from runInTab/runInFrames targets even with the toggle ON). Read once per SW load — reload the extension after toggling |
| `_Yh` | userAPI dispatcher | top-level `let` (file48), ASSIGNED by file77 `{_Yh=_we(...)}`; `(e,d)=>yield W(e.props, e.args, e.scriptId, d, e.targetTabs, e.trigInstId)`; z-bundle passthrough `h instanceof z?h:{result:h}`; error format ``ACtl.${props[0]}: ${msg}``; **CALLBACK-style runner, NOT a Promise** |
| `__acLog` | MV3 AC-ACT logger | bundle top-level function declaration `function __acLog(t,m){...console.warn('[AC-ACT] #... '+t+' '+m...)}` — a CLASSIC-script global object property, so reassignment from sw.js is seen by every bundle call site (the action-queue watchdog hooks it directly: `t === 'OK'` = completion marker; B34) |
| `_Ph` | activateTabs runner | (file8) `tabs.update(c,{active:!0})` executor for activateTabs actions; MV3 FIX 17/18: sets `_Np=c` OPTIMISTICALLY before the update (fast wheel-spin tab switching) + syncs `_Yp[].active` flags (onActivated is the source of truth) |

## Native Messaging
| Obfuscated | Meaning | Description |
|-----------|---------|-------------|
| `_Lk` | Send to native | `_Lk(type, payload, callback?, timeout?)` |
| `_Vy` | Callback wrapper | `(t, p, to) => cb => _Lk(t, p, cb, to)` |
| `_0d` | Capture toggle | `_0d(true/false/obj, cb)` - sends type 40 |
| `_Uj` | Simulate native msg | Routes `[type, data]` to local `z` handler |
| `_ha` | File size query | Queries native for file size |
| `_Yi` | Chunked data getter | Retrieves chunked file data |
| `_cu` | Add z handler | `handler => z.add(handler)` |
| `_Sw` | Cleanup | Cleans native connection state |
| `_Xg` | Full handshake | Connect + handshake generator |
| `_dh` | Connected timestamp | `Date.now()` when native connected |
| `_7` | Connected flag | `true` when native connected |
| `_nd` | Native installed flag | `true` if native was ever installed |
| `_g` | Timeout constant | `"CB-TIMEOUT"` |
| `z` | Message handlers | `{[type]: fn}` - routes native messages |
| `y` | Event callback | Stored by `_0d`, called by `z[760]` |
| `_ay` | No-op | `() => {}` default callback |

## Message Types
| Constant | Value | Dir | Description |
|----------|-------|-----|-------------|
| `_7s` | 10 | → | File check |
| `_ro` | 20 | → | Init `{iTime, crVer, variant}` |
| `_zu` | 21 | → | Startup signal |
| `_Z` | 30 | → | File size query |
| `_Qr` | 40 | → | Capture mode toggle |
| `_4e` | 60 | → | Config (trigActList) |
| `_hk` | 65 | → | AdvOpts |
| `_Ma` | 67 | → | Monitor/display info |
| `_5r` | 70 | → | Joystick order |
| `_mu` | 72 | → | Switch states |
| `_uf` (file93) | error counter | `["LOCAL","errorEvts",<name>]` — daily counter in storage (7-day window), fed by z[800] no-hook/segFault; read by `_dk` (used only in update telemetry `errorCount`) |
| `_Lh` (file70) | no-hook-notice popup | `_Fo` (file71.html popup via windows.create) «another program is preventing …» — yes «Don't show again» / no «Keep showing»; shown by z[800] after 5 no-hook-notice messages in 15s (MV2 E()); callback answer → `_Ot` + `noHookConflictMsg`. **MV3**: z[800] uses chrome.notifications by design; the `_Fo` path (now `__acMv3Popup`, bridge-filled) is used by `_Kg`/`_Ht` (repair diagnostics, §7-15) |
| `_Sf` / `_Zw` (file13) | monitor map | `_Sf(cb)` fills `_Zw` from `chrome.system.display.getInfo` (displayId → DisplayUnitInfo + `desktop` bounds). **MV3 FIX**: the SW never called `_Sf` at startup (only `onDisplayChanged`) → `_Zw` empty → `_Fo` (popup positioning) crashed "workArea of undefined"; sw.js `sendMonitorInfo` now calls `_Sf(() => {})` at every startup |
| `_r` (file34) | APDL flag | set `true` by z[800] "APDL" (anti-piracy verified); file62 idle handler sends the type-790 ping only while `!_r` |
| `_Wo(c,d)` (file70) | event dispatcher | `if(!(c<_Ay=30)||d){ if(_uk[c]){ batch type-50 (_Qw, evtId:c|_cf) to native }; c!=_Vs&&_8o(c,d) }` — `_uk` = custom events used by triggers (filled by _mh); `_8o` dispatches to ACtl.on listeners (`_vo`). **`_Vs=30` = "On startup" trigger event** (file68 `[_Vs]:{name:"On startup"}`) — MV2 fired `_Wo(_Vs)` once per session after type 21 (file61 D `!G++&&!_nt("noStupEvt")`); MV3 FIX: sw.js finishStartup calls `_Wo(_Vs)` after postMsg(21) (once per session, `__acStartupEvtSent` + `noStupEvt` skip) |
| `_np` | 705 | ← | Browser name |
| `_9p` | 710 | ← | Promise resolution |
| `_mj` | 721 | ← | Window focus change |
| `_9g` | 740 | ← | Clipboard format |
| `_Hf` | 750 | ← | **Trigger event** |
| `_b` | 170 | → | **Open menu** `{menuData:{style,items:[{title,icon}]}, menuEntityNum, position, alignHorz, alignVert, menuSystem, usePrvMsPos}` → `true` (file26 `_Bp`); menuNum 7 = the tab-switcher menu |
| `_Ws` | 175 | → | **Menu state query / close** — `null` content = "is a menu open?" → `true`/falsy (file26 `H()`); the `closeMenu` action also sends `175 null` |
| `_3f` | 185 | → | **Menu state detail** `{usePrvMsPos}` → `{hilited, hovered, marked}` item indices; `{}` when no menu open |
| `_fo` | 760 | ← | Action/gesture event |
| `_kw` | 800 | ← | Error |
| `_xp` | 920 | → | Ping |
| `_jh` | 905 | → | Keepalive |
| `_vh` | 55 | → | Emergency repair — **ACK ONLY, does NOT restart the engine by itself** (restart = page-reload/port-drop cycle, see NATIVE_PROTOCOL §18) |
| `_ya` | 451 | → | Native diagnostics `{PBC, actWinMine, appUserModelIDs, downKeys, focusWin, ...}` (sent before type 55) |
| `_tl` | 280 | → | Clipboard read `{format:1}` → `{content, format, size, trueFmt}` |
| `_t` | 285 | → | Native action cmd `{cmd:2}` (clpbrdPaste) |
| `_Hi` | 286 | → | Clipboard write `{data, fmt, "":true}` → true |
| `_6f` | 344 | → | Window state check `{content:[hWnd]}` → `{hWnd:bool}` |
| `_2p` | 470 | → | Special-folder path `{content:CSIDL}` (16=Desktop) |
| `_ef` | 810 | ← | File-read chunk `{chunk,id,type}` (reply to 255) |

## Storage layer (file17.js / file73.js / file77.js)
| Obfuscated | Meaning | Description |
|-----------|---------|-------------|
| `_Qj` | Storage normalization | Converts storage pair-arrays (`[[id,val],...]`) to the Map-like object `{}.add` used by the UI; ALSO the round-10/18 binSwtch patch point. **CRITICAL: must never FABRICATE keys** — `_Mi` writes the whole read result back, so an invented `customEntities={}` wiped all scripts (round-18 regression, fixed). |
| `_9i` | Storage get | `storage.local.get(keys, cb)` → cb(`_Qj(result || defaults)`) |
| `_Mw` | Merge+callback | `_Mw(defaults, keys, cb)` — merges defaults with stored values |
| `_bd` | Storage set | `storage.local.set(_bj(obj))` — writes back the WHOLE object (hence the round-18 wipe) |
| `_bj` | Serialize | `.sc()` clone + pair-array conversion for storage |
| `_Mi` | Batched write | Debounced multi-key write: reads the affected top-level keys, patches them, `_bd()` back; used by `ACtl.var`/`pubVar`/switchState saves |
| `_ur` | Key path | `["userVars"].concat(name.split('.'))` — vars live under `storage.local.userVars` |
| `_ge` | Var set | `_Mi(_ur(...), value)` |
| `_ae` | Var get | read via `_ru` (nested get) |
| `_sy` | Multi-var set | sets many vars in one batched `_Mi` |
| `_Rd` | Value sanitize | `null`/`NaN` → `undefined` (deletes the var) |
| `_ul` | Emptiness check | `null` / empty array / empty object |
| `_zs` | Read script code | `_zs(scriptId)` → `srcCode` (or loads `srcFile` via `_L`) — runScript source |
| `_iw` | Shell command | `_iw(cmd)(cb)` → type 260 (see NATIVE_PROTOCOL 260 async-ack note) |
| `_3t` | Read+decrypt file | `.dat` → byte-shift decrypt (`_7g`, keys `[94,14,77,49,13]`) |
| `_4u` | Chunked file write | type 250 chunks, result 0 = OK |
| `_Sp` | Import from file | `storage.local.clear()` + set — merges old `customEntities` missing from the file (round-17 fix: scripts survive import) |
| `_qj` | Write settings file | `settings.dat` via type 250 |

## Action Execution (file37.js)
| Obfuscated | Meaning | Description |
|-----------|---------|-------------|
| `_6y` | Execute trigger | `_6y(triggerId, data)` - main executor |
| `_2y` | Action queue | `[[triggerId, data], ...]` pending FIFO |
| `_ek` | Trigger→Actions | `{triggerId: [action, ...]}` |
| `_rf` | Run actions | Executes action chain from `_ek[id]` |
| `_ai` | Async sequence | Wraps func with queue processor |
| `_Mt` | Sequence processor | Batch async processor |
| `_Lw` | Queue instance | `_Ij` queue for action processing |
| `_Ij` | Queue class | `{addFunc, empty, onEmpty}` |
| `_pg` | Trigger transform | Maps native IDs to transform fns |
| `_Sk` | Daily offset | `Date.now() / 864E5 \| 0` |
| `_su` | Index shift | Additional trigger index offset |
| `_qt` | Instance data | Creates/manages trigInstId data |
| `_Wi` | Current action | Which action type is executing |
| `_Fk` | Ready flag | System ready flag |
| `_Pw` | Watchdog | Detects stuck actions |
| `_Mh` | loadUrls / Open URL (file8) | Creates tabs via `_6a` (`tabs.create`) or `_3g` (`windows.create`); `tabPos:"after"` = to the right of current tab |
| `_6a(props, cb)` | tabs.create wrapper (file34) | `_Yk.tabs.create` then marks about:blank in `_Vg`. SW wrap `__acWrapChromeUiCreate` reloads chrome:// after create (2026-09-11) |
| `_3g(props, cb)` | windows.create wrapper (file34) | Same about:blank mark; Open URL `tabPos:"newWin"` |

## Config Loading (file47.js)
| Obfuscated | Meaning | Description |
|-----------|---------|-------------|
| `_lr` | Load gest/joy/adv | Loads mouseGest, joysticks, advOpts from storage |
| `_Gf` | Load everything | Full chain: `_6s` → `_zj` → `_no` |
| `_zj` | Process trigActList | Builds `_ek` from loaded data |
| `_no` | Init from settings | Sends config type 60 to native |
| `_6s` | Load from storage | Loads trigActList from chrome.storage |
| `_Mw` | Merge+callback | Merge defaults, call callback with result |
| `_Jp` | Gest params | Sends mouse gesture params to native |
| `_6t` | Display config | Sends display config |
| `_Jf` | AdvOpts | Sends adv options to native |

## Combo Editor (file68.js)
| Obfuscated | Meaning | Description |
|-----------|---------|-------------|
| `C(a,b,c,d)` | Edit event | Main combo edit function |
| `D(a)` | Start edit | Opens combo editor UI |
| `E()` | End edit | Closes combo editor |
| `y(a,b,c)` | Apply event | Applies event/gesture to combo |
| `z(a,b)` | Check dup | Checks if event already exists |
| `K(a)` | Is keyboard | Checks if event is keyboard |
| `q(a)` | Get data | Gets combo data from trigActList |
| `B(a)` | Refresh | Re-renders combo HTML |
| `M(a,b)` | Remove | Removes event from combo |
| `W(a)` | Event menu | Creates event picker popup |
| `L(a)` | Render events | Renders event list HTML |
| `_eh(a)` | Decode event | Decodes eventID to event type object |
| `_Lj(a)` | Char decode | `String.fromCharCode(a)` — used by z[760] to map actionType: 71→'G' (gesture), 69→'E' (event), and by gesture state/dir decoding (73='I' Idle, 83='S' Start, 67='C' Coord) |
| `_Ah(a)` | Char code | `"B".charCodeAt(0)` = 66 |
| `_4f` | Event labels | `{eventId: {title, help}}` |

## UI Functions (file78.js etc.)
| Obfuscated | Meaning | Description |
|-----------|---------|-------------|
| `_Tp` | Switch panel | Switches settings panel |
| `_yf` | Load HTML | Loads HTML fragment |
| `_hp` | Default panel | Gets default panel ID |
| `_lj` | Import settings | Settings import flow |
| `_ct` | Permissions | Shows permissions UI |
| `_Qk` | Check perm | Checks/requests permissions |
| `_6r` | Update switches | Updates switch states in UI |
| `_xk` | Export settings | Settings export flow |
| `_8f` | Load panel | Loads and shows settings panel |
| `_Vd` | TBBtn selector | Toolbar button selection |
| `_Ew` | Toolbar buttons | Renders toolbar buttons |
| `_xf` | Menu setup | Sets up context menus |
| `_2d` | Drag-drop | Drag-and-drop handlers |
| `_uw` | Import file | Imports from file |
| `_kp` | Import JSON | Parses JSON settings |

## Windows / Focus (file74.js, file62.js)
| Obfuscated | Meaning | Description |
|-----------|---------|-------------|
| `_y(a,b)` | Focus window | Switches focus to window `a` |
| `_yh(a)` | Window created | Registers new window |
| `_fy(a)` | Window cleanup | Cleans up closed window |
| `_q(a)` | Window removed | Handles window removal |
| `_oj(a)` | Send state | Sends window state to native |
| `_Ry` | Batch processor | Rate-limited window event processor; hijack probe: type 335 `{refWin, inclHjkd}` + type 400 position probes `{win,x,y,noNotif}` (file74) |
| `_8u` | Register callback | Registers window change callback |
| `_Sh` | Tab activated | Sends tab activation to native |
| `_0k` | Tab hidden | Sends tab hide to native |
| `_Ja` | URL changed | Sends URL change to native |
| `_ko` | isFocused | Whether chrome has focus |
| `_as` | Focus signal | Window focus signal emitter |
| `_Fu(a)` | Window enum | `windows.getAll` (via `_Vt`) → rebuilds `_Yp`/`_cd`/`_n`/`_ts`/`_Gk`/`_ea`; sets `_Np` for the active tab of `_4t` |
| `_O(a)` | Window-state check | `a=yield _Vy(344, yield _1h(a))` → `{winId: bool}` (keyed via `_Or`); used by getTabInfo + `_ke` refresh |
| `_1h(a)` | winIds→hWnds | Retry resolver: `_Ry` enum loop (5×, 200ms backoff) → hWnds via `_na` |
| `_0o(a,b)` | winId↔hWnd maps | Maintains `_Or` (hWnd→winId) and `_na` (winId→hWnd) |
| `_ke(a)` / `_Jr` | Window-state cache | `_Jr` = cached `_O` result; `_ke` miss schedules a deferred `_O` refresh (1ms, `_Lw` queue) — suspected source of the doubled 344s in burst logs |
| `_Vj` / `_kr` | Event registry | `ACtl.on/off` events (tabLoadEnd…): `_Vj[event][tabId][trigInstId]=[callbacks]`; `_kr` dispatches (checks `_Aw()` after the native wait), `V` notifies registered callbacks |

## Constants (file56.js, file57.js, file10.js)
| Obfuscated | Value | Description |
|-----------|-------|-------------|
| `_qe` | 1 | Left mouse button |
| `_md` | 2 | Right mouse button |
| `_ir` | 4 | Middle mouse button |
| `_Ze` | 5 | 4th mouse button |
| `_Vf` | 6 | 5th mouse button |
| `_Lo` | 0 | Down-event type flag |
| `_mk` | 1024 | Up-event type flag (2\|_mk=1026 = RCM-up) |
| `_cf` | 2048 | Extended event flag |
| `_th` | 4096 | Gesture mouseMove flag (gesture eventId = idx\|_th) |
| `_zt` | 256 | Numpad flag (keyId\|_zt = numpad) |
| `_N` | 512 | Misc/device flag |
| `_ee` | 0 | Device: keyboard |
| `_xe` | 1 | Device: mouse |
| `_rs` | (version) | Chrome version number |
| `_ip` | (timestamp) | Install time (seconds) |
| `_fr` | `["Google Chrome"]` | Browser variant |
| `_ps` | `{...}` | Switch states |
| `_xd` | `"AutoCtrl_2025.4.22.0.exe"` | Native exe name |
| `_ne` | `"AutoControlZero.exe"` | Alternative exe name |
| `_or` | `"Native-Component.exe"` | Installer exe name |
| `_Ct` | (ms) | Install time in ms |
| `_7y` | (hash) | Install time encoded |
| `_Ie` | (version) | Native component version |
| `_Jh` | (name) | Browser name from native |
| `_Zw` | `{...}` | Monitor info cache |
| `_Sf` | function | Loads monitor info via `chrome.system.display` |
| `_iy` | function | Sends monitor info to native (type 67) |
| `_Cr(a,b)` | Badge setter | `chrome.action.setBadgeText` + `setBadgeBackgroundColor` — `_Cr("Wait","#F00")`, `_Cr(" OK ","#0F0")`; `_Cr("")` clears (toasts are invisible in SW — §7-10; badge is the SW-visible channel) |
| `_Wd` | Input element | File input for import/export |
| `_Fj` | Read file | Reads selected file |

## Config/Type-60 internals (file25.js, file3.js)
| Obfuscated | Meaning | Description |
|-----------|---------|-------------|
| `_mh` | Config compiler | Builds type 60: `{map, list, urlTests, combinSequences, gestures, neededCaretSt}` |
| `_Th` | 0 | Entry type: block (`{type:0,block:true}`) |
| `_wi` | 1 | Entry type: keyEvent |
| `_Se` | 2 | Entry type: state switch |
| `_mp` | 4 | Entry type: gesture begin/end (`{type:4,state:true/false,timeout}`) |
| `_tj` | 5 | Entry type: actIdx gate |
| `_Ag` | 6 | Entry type: keyStateChange action |
| `_qs` | 7 | Entry type: sequence step |
| `_Yf` | 8 | Entry type: hold-delay auto-repeat |
| `_Bh(a,b)` | Preset builder | `{begin:[{combins:[{eventId:a,wildcard:0,block:b(true)}]}], end:[{combins:[{eventId:a\|_mk,wildcard:0}]}]}` |
| `_Vi` | Presets | `{rightButton: _Bh(_md), ...}` — source of block:true under key 2/1026 |
| `_0p(a)` | Preset applier | `a.preset||"rightButton"; "other"!=b && a.add(_Vi[b].value)` |
| `_5a` | 7 | Precond type: actionState `{type:7,value:68('D'),actIdx}` |
| `_5` | 11 | Precond type: mouseGestState `{type:11,value:83('S')}` |
| `_Ku` | 9 | Precond type: keyStateChange |
| `_ot` | 2 | Precond type: chromeState active |
| `_8` | 6 | Precond type: wildcard |
| `_0y` | 13 | Precond type: menuState `{type:13,menuNum,negate?}` — **`negate:true` = "menu must NOT be open"** (the Smart Ctrl+Tab set depends on it; native evaluates it itself) |
| `_2k` | 4 | Precond type: prevSeqStep |
| PBC | — | Pressed-button-count: `{devId:count}`; up-event `{1:-1}` |
| mapKey | keyId+22025 | Key in payload.map (key 2→22027, 1026→23051, 85→22110) |
| `R()` (in `_mh`) | Compile | The `M||V` branch (`r.type==_mp && state/!state`) with `r.block&&I` emits `{type:0,block:true}` under key 2 AND key 1026 — **source of the RCM/LCM bug** |
| `_lk(a)` | menuNum | `menuSpec:7` → 7 (negative when the entity is missing) — the `{type:13}` precond value |

## Object.prototype patches (file67.js) — `.in` POLYFILL GOTCHA (2026-08-30)
- file67 defines on `Object.prototype`: `in` (membership via `_Xt`), `includes`
  (deep equality), `add` (merge), `del`, `keep` (in-place whitelist),
  `sc` (shallow copy), `[Symbol.iterator]` (yields `[key,value]` pairs).
- `keep(...names)` calls `b.in(a)` with **`a` = an ARRAY** — so `.in` MUST
  support the array form `'x'.in(['x','y'])` AND the scalar form `'x'.in('x','y')`.
- **The bundle is sloppy** (concatenation starts with `;` + comment, no
  `'use strict'`) → file67's `_Xt(this,...a)` gets a BOXED `this` on
  primitives (`new String('x') === 'x'` is false) → `.in` was broken for
  EVERYTHING in the SW.
- sw.js re-patches `.in` (unboxing + `[].concat(...a)` flatten + strict `===`).
  **The earlier indexOf version broke the array form** → `keep()` deleted
  every non-kept property INCLUDING `negate:true` on menuState preconds →
  every Ctrl+Tab trigger compiled as "menu 7 IS open" → openMenu never
  fired → the tab-switcher list never opened after a reload (2026-08-30).
  mh_test B51 pins both forms + the compiled negate flags.

## Trigger decode — `_pg` keying
- `b = _pg[a.id - _Sk + _su]` — lookup into the transform table (URL/tab
  filtering). The key includes `+ _su` because `_pg` is keyed by
  `{param + 20200 + 1825}` (param = seqId|stepId, see file25.js) —
  subtracting `_Sk` yields the `_pg` index.
- `_mh()` sets `param: +h + _su` in `_pg` (`h` = the same trigger index).
- Without `_su` the `_pg` lookup only breaks for triggers with URL
  pre-filters (rare).
- Final trigger ID for `_6y`: `16777215 & (a.id - _Sk)` — computed WITHOUT
  `_su`; matches `_ek` keys (0..N) built by `_zj()`.

## Gesture-state chars (`_Ah`)
| Char | Code | Meaning |
|------|------|---------|
| 'B' | 66 | Begin test gesture |
| 'C' | 67 | Coordinate/move |
| 'D' | 68 | Action state: Done/doing |
| 'I' | 73 | Idle/end gesture |
| 'N' | 78 | State name (param 78) |
| 'S' | 83 | Gesture started |
| 'Y' | 89 | State name (param 89) |

## UserAPI / W() layer (file77.js)
| Symbol | Meaning | Description |
|--------|---------|-------------|
| `W(e,d,h,k,t,n)` | userAPI switch | args: props, args, scriptId, sender-tab, targetTabs, trigInstId. Cases: sleep, var/pubVar, getScript, include, import/getFile, saveFile, getClipboard/setClipboard, captureTab, on/off, expand, runCommand, execAction, runInTab/runInFrames, switchState, getTabIds/getTabInfo, openURL/closeTab/setTabState |
| `z(e,d)` | z-bundle (file77-local) | `{funcCode, args}`; `__IMPORT__` placeholder → `import` keyword when `_rs>=63`; shadows the shim's global `z` inside the block; `_Yh` returns it unwrapped (`h instanceof z?h:{result:h}`) and the file42 relay evaluates it via `FN` |
| `J(e)` | Iterator attach | `Object.defineProperty(e, Symbol.iterator, ...)` yielding `[key,value]` pairs — z-bundle results (getTabInfo/var/captureTab) are iterable maps (`const [[,uri]] = await ...`) |
| `F(e,d,h)` | F()-path sender | `_xj(e,{funcCode:h+"",args:_Ii(d)})` — **does NOT carry trigInstId** (TODO fast-press gap); code runs in the USER_SCRIPT world; results `["bin"|"text"|"image"|"json"|"html", data, ...]` |
| `K(e,d,h,k=.9)` | Serializer (USER_SCRIPT) | `window[e]` → bin-b64 / image-dataUri / html-outerHTML+text / json / text; **non-destructive read** (round 6 — no `delete window[e]`) |
| `C(e,d,h,k,t,n)` | Format converter | base64/binary/blob/file/objectUrl/dataUri/image/canvas/json/xmlDoc/htmlDoc/html/css/module; "module" → blob URL + `__IMPORT__` |
| `G(e,d,h)` | scrtCtxVar cache | `_xj(e,{scrtCtxVar:d,value:h})` — include-dedup via file42's `x` map (`void 0===value?read:write`); cache-miss → sync `e(undefined)` → n() null-retry noise (`no listener → inject`) |
| `_Zt/_It/_3r` (file41) | Clipboard write | `_Zt(a,b,c="")` → `_Lk(286,{data,fmt,[c]:!0},cb)`; `_It` appends text (per-id buffer `_os`); `_3r` writes image from a file |
| `_yw/_aw/_ag` (file41) | Clipboard read | `_yw(fmt)` → `_Lk(280,fmt,cb)`; `_aw` = text getter (joins the `_zo` buffer); `_ag` normalizes (decodes image b64, chunked getter `_Yi`) |
| `_gp(b)` (file95) | Native action cmd | `_Lk(285,{cmd:b},...)` — `_gp(2)` = clpbrdPaste |

## MV3 Shim (mv3_native_shim.js)
| Symbol | Description |
|--------|-------------|
| `_trigActList` | Full trigger list for key/gesture lookup |
| `_live` | Flag: true for live msgs, false for buffered |
| `pendingGestures` | Queue for gestures arriving before config loads |
| `gestureState` | Current gesture tracking `{active, startX, startY}` |
| `findTriggerByKey(k)` | Find trigger by key code in `_trigActList` |
| `findTriggerByGesture(p)` | Find trigger by gesture pattern |
| `executeTrigger(id, d)` | Execute trigger with error handling |
| `window._Fo = __acMv3Popup` | **MV3 replacement for file70 `_Fo`** (2026-08-12, FEATURES-MV3.md §7-15): MV2 filled the file71.html popup via `chrome.extension.getViews({windowId})` — ABSENT in the MV3 SW. Now: `windows.create({url: file71.html + "?runId=N"})`; the popup page itself requests the content (see `file71_bridge.js`) and reports the button via `acPopupResult`. `<key>N</key>` names are pre-converted IN the SW via `_Je` (the MV2 `onloaded` path is skipped) |
| `__acResolvePopup(runId, answer)` | Resolves the `_Fo` callback (`{answer: bool}`), closes the popup window; called from sw.js on `acPopupResult` |
| `__acPopupGetContent(runId)` | Returns `{html, winId, title}` for the requesting popup page (served via sw.js `acPopupContent` handler) |
| `__acPopupRunId / __acPopupCallbacks` | Per-popup registry: runId → `{winId, cb, html, title}` (in-memory; a popup left open across an SW reload resolves via `unload` → `answer:false`) |
| `file71_bridge.js` | **NEW page script (2026-08-12)** loaded by file71.html: parses `?runId`, `sendMessage({type:"acPopupContent"})` → renders `html`, auto-sizes via `windows.update`, `acPopupResult` on button click (yes/no attributes) and on `unload` (answer:false). ⚠ `scripting.executeScript` CANNOT inject into chrome-extension:// pages ("Extension manifest must request permission to access this host") — this is why the popup loads its own content instead |
| `window._nk = function(){}` (non-SW) | Page/offscreen no-op (2026-08-12, FEATURES-MV3.md §7-15): file47 `_nk()` on the settings page ran the UNPATCHED `contextMenus.removeAll` (wiped the SW's "Emergency repair" item) and its `create({contexts:["browser_action"]})` is INVALID in MV3. The SW owns the context menu exclusively |

## Emergency Repair / update flow (file34.js, file62.js)
| Symbol | Description |
|--------|-------------|
| `_co(a=0,c=!1,b)` | Core repair/update: `c` → badge "Wait" + `_9k("showNotif",!0)`; sends `_Lk(_vh=55, null, cb)`; `a==1` → reload CURRENT page (MV2 `location.reload()` — the ACTUAL engine restart trigger via port drop; MV3: SW's `__acEmergencyRestartNative`, see NATIVE_PROTOCOL §18); `a==2` → `_Yk.runtime.reload()` (extension update); `a==0` → `_Xg()(b)` |
| `_ze()` | Extension-state snapshot: collects `_Ft,_ea,_n,_Mo,_hd,_da,_He` into a plain array (for `_9k("extensionState",...)`) |
| `_nk()` | (file47.js) Context-menu builder: `removeAll()` + "swtchList" parent (binSwtch checkboxes) + `reloadExtn` "Emergency repair" — runs on EVERY config-chain execution, hence the SW's removeAll/create patches (AGENTS.md FIX 11). **2026-08-12**: stubbed to no-op outside the SW (the SW owns the menu); the SW's removeAll patch recreates reloadExtn via the ORIGINAL create (`origCtxCreate` — the patched create returned 0 for reloadExtn while `__acCtxMenuOwned`, silently dropping the recreation) |
| `_2u(a=0)` | Date gate: `22025 <= (Date.now()/1E3/3600/24|0) + a` — used as `_2u(5)` before `requestUpdateCheck`/update flows |
| `_Eu.wait()` | (after repair) yields until the native reconnect completes — `_nt("showNotif")` path then shows the OK/Error badge (MV2 shows it AFTER the reload reconnects, not immediately) |
| `__acRepairDiag` (storage) | **2026-08-12, FEATURES-MV3.md §7-15**: `{showNotif, diagnostics}` persisted by `__acEmergencyRestartNative` (`_j` reads the in-memory one-shot flags BEFORE the reload) — MV2 kept them in the background page's real localStorage; the MV3 in-memory shim dies with the SW. The fresh SW (proceedAfterFileCheck) consumes it and shows `_Kg` (stuck keys, `downKeys` from type 451) or `_Ht` (foreign profile, `actWinMine===0`) — MV2 semantics. The stuck-keys list is REAL (user-verified 2026-08-12) |
| `_Xg()(b)` | Full handshake runner (file67 `_us`-style callback) — `_co` a==0 fallback |

## MV3 Shim (mv3_shim.js)
| Symbol | Description |
|--------|-------------|
| `chrome.runtime.onMessage` | Listens for SW broadcasts (`_sw` flag) |
| `CustomEvent('ac-sw-msg')` | Dispatches SW messages to page |
| `_nd = true` | Set synchronously to prevent install UI |
| `contextmenu` prevented | Prevents page close on right-click |
| Global error handler | `window.onerror` + `unhandledrejection` |

## SW (sw.js)
| Symbol | Description |
|--------|-------------|
| `NATIVE_HOST` | `"hrich.autocontrol"` |
| `port` | `chrome.runtime.connectNative` port |
| `connected` | Bool: native connected |
| `nativeMsgBuffer` | `[{type, data, ts}]` for late-connecting pages |
| `doHandshake()` | Type 10 → 20 → 72 → 21 → 40 sequence |
| `onMsg(msg)` | Receives native messages, logs + broadcasts |
| `postMsg(t, p)` | Fire-and-forget to native |
| `postWithCb(t, p, to)` | Promise-based send with native callback |
| `broadcast(msg)` | Sends to all extension tabs + runtime |
| `_live` flag | Added to live (non-buffered) broadcasts |
| `stripRightButtonBlocks()` | **v6**: softens block:true→false under key 2 AND 1026 in type 60 |
| `scheduleGestureEsc()` | **v7**: 20ms after a gesture sends type 300 `[27,1051]` (Esc) |
| `__acWrapChromeUiCreate()` | After importScripts: wrap `tabs.create` + `windows.create`; reload chrome:// / edge:// tabs once at 150ms (skip about:blank / newtab). Heals Open URL of history/bookmarks stuck on Loading (2026-09-11, B55) |
| `lastRaw760Time` | TS of last type 760 — gesture fingerprint for v7 |
| `handshakeSk` | `_Sk` at handshake (daily offset) |
| `startupSent` | Flag: type 21 sent (after config chain) |
| `type72Sent` | Flag: type 72 sent |
| `handshakeDone` | True after 10→20→67 |

## Message types (file56.js)
| Value | Const | Dir | Description |
|-------|-------|-----|-------------|
| 50 | `_Qw` | → | Trigger event injection `{evtId, trigInstId}` |
| 55 | `_vh` | → | Emergency repair / diagnostics |
| 90 | `_Xa` | → | Icons (toolbar buttons) |
| 100/110 | `_fk`/`_Cf` | → | Gesture trail draw/move |
| 136 | `_Mu` | → | Tab replaced `[oldId,newId]` (tabs.onReplaced) |
| 140 | `_5t` | → | Tab state `{tabId,win,time,popup}` (`_Sh`) |
| 150 | `_ta` | → | Tab focus `{tabId,win}` (`_0k`) |
| 200 | `_Jo` | → | Preview maker params `{interval}` |
| 250/255 | `_Q`/`_0f` | → | File read/write (chunked) |
| 260 | `_7e` | → | Run shell command (forfiles/del etc.) |
| 300 | `_Dt` | → | **SendInput** `[eventId,...]` (2=RCM down, 1026=up, 27/1051=Esc) |
| 315 | `_be` | → | Input lock `{state}` |
| 320 | `_8p` | → | Mouse block `{state}` |
| 330 | `_Ua` | → | Mouse pos query |
| 335 | `_uo` | → | Window enum `{refWin}` |
| 340 | `_bw` | → | Use prev mouse pos `{usePrvMsPos}` |
| 350/355/365 | `_Hr`/`_tp`/`_si` | → | Minimize/Maximize/Topmost |
| 400 | `_ms` | → | Window move `{win,x,y,noNotif}` |
| 721 | `_mj` | ← | Window focus `{hWnd,noEvt}` |
| 730/735/740 | `_Ki`/`_Qg`/`_9g` | ← | Clipboard list / minimize / clipboard fmt |
| 765 | `_0i` | ← | (file/blob data) |
| 900/901 | `_Xk`/`_io` | → | (—) |
| 910 | `_8d` | → | (—) |
| 930–943 | — | → | (—) |

## Key Files
| File | Purpose |
|------|---------|
| file56.js | All message type constants |
| file57.js | Button/event ID constants |
| file34[_mv3].js | Globals, `_co`, `_ai`, `_Mt`, `_Lw`, `_Ij` |
| file37.js | `_6y` (action executor), `_rf`, `_2y`, `_Pw` |
| file47.js | `_lr`, `_Gf`, `_zj`, `_no` (config loader chain) |
| file61.js | ORIGINAL native messaging (replaced) |
| file62[_mv3].js | Tab/window events, init flow, `_yh`, `_fy`, `_Sf` |
| file68.js | Combo editor (`C`, `D`, `E`, `y`, `z`, `K`, `q`) |
| file70.js | Monitor info (`_Sf`, `_iy`), file operations |
| file74.js | Window focus (`_y`, `_oj`, `_Ry`, `_Sh`) |
| file78[_mv3].js | UI functions (`_Tp`, etc.), MV3 init |
| file30.js | Options page panels, actions list |
| file10.js | Various constants, `_Yk=chrome` |
| sw.js | MV3 Service Worker (native messaging bridge) |
| mv3_shim.js | MV3 compat shim (loaded FIRST in main.html) |
| mv3_native_shim.js | Replaces file61.js – delegates to SW |
