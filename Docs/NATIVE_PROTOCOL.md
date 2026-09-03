# AutoControl ↔ Native Component Protocol Specification

## 1. Transport

- **Channel:** `chrome.runtime.connectNative("hrich.autocontrol")`
- **Encoding:** JSON over stdin/stdout
- **Port:** Single persistent bidirectional port
- **Reconnection:** Exponential backoff, max ~8s delay

---

## 2. Wire Format

### Outgoing (Extension → Native)

```json
// Without callback:
{"type": <number>, "content": <object|null>}

// With callback (normal types):
{"type": <number>, "content": <object>, "callback": <number>}

// With callback (types 240, 285, 490 — callback INSIDE content):
{"type": <number>, "content": {..., "callback": <number>}}
```

**Callback encoding:**
- `e = 2130706431 * Math.random() | 0` — random 31-bit ID
- `l = parseInt(chrome.runtime.id.substr(2, 3), 36) || 13625` — extension ID hash
- `sentCallback = e + l`
- Native echoes back type **710** with `{id: e, params: <result>}` (strips `l`)

### Incoming (Native → Extension)

Two formats, handled interchangeably:

```json
// Array format:
[<type_number>, <data_object>]

// Object format:
{"msgType": <type_number>, <field1>: ..., <field2>: ...}
```

---

## 3. Handshake Sequence

This is the COMPLETE startup sequence, ORDER MATTERS.

```
Step  Time    Type  Dir  Payload                        Description
────  ────    ────  ───  ─────────────────────────────── ─────────────────────
  1     0ms   10    →    {fileName:"AutoCtrl_2025.4.22.0.exe"}  File existence check
        ↑     wait  9s  ← 710 {id:e, params: 0|1|2}           Response (0=ok)

  2   +0ms   20    →    {iTime:<installSec>, crVer:<chromeVer>, variant:["Google Chrome"]}  INIT

  3   +0ms   67    →    [{x,y,w,h,dpi}, ...]                    Monitor/display info
        ↑     call  ←   (no response expected)

  4   +0ms   72    →    {states:{<id>:<bool>, ...}}             Switch states
        ↑     call  ←   (no response expected)

  5   +0ms   21    →    null/{}                                 STARTUP signal
        ↑     call  ←   (no response expected)

  6   async  200   →    {interval:0}                            Preview maker params
        ↑     wait  ←   710 {id:e, params: true}                Response

  7   async  70    →    [...]                                   Joystick order
  8   async  (??)  →    Mouse gesture params                    (sent by _Jp)
  9   async  (??)  →    Display config                          (sent by _6t)
 10   async  65    →    {...}                                   Advanced options
 11   async  60    →    {...}                                   Main config (trigActList)
```

### In MV2, steps 2-5 execute in a SINGLE generator yield chain:

```javascript
_Lk(20, {iTime:_ip, crVer:_rs, variant:_fr});  // step 2
_iy();                                           // step 3  (type 67)
_7 = true;                                       // connected flag
yield c => _Ry()(() => { _oj(); c() });         // wait for window init
_Lk(72, {states:_ps});                           // step 4
yield c => _lr(g => _Gf(g, c));                 // steps 6-11 (config chain)
_Lk(21, null);                                   // step 5 — STARTUP LAST!
```

**IMPORTANT:** Type 21 (startup) is sent AFTER all config! Not before.

---

## 4. Type 40 — Capture Mode Control

### Original calls:

```javascript
// 1. Enable combo editor capture (file68.js D function):
_9j._0d(!0, (d,e)=>{...});  // type 40 + true

// 2. Disable capture (file68.js E function):
_9j._0d(!1);                 // type 40 + false

// 3. Gesture assist test (file30.js):
_9j._0d({mouseGest:66}, (g,l)=>{...});  // type 40 + {mouseGest:66}
```

**Effect on native:**
- `true` → enables input event capture (native starts sending type 760 with key/button codes)
- `{mouseGest: 66}` → enables gesture coordinate mode (native sends type 760 with {state, dir, x, y})
- `false` → disables capture

**Both modes can be active simultaneously** (separate calls).

### Stuck-capture failure mode (2026-08-09)

While ANY capture mode is ON, the native streams raw type-760 events and
**suppresses ALL type-750 triggers** — gestures, hotkeys and the right mouse
button die until capture is disabled. The OFF (`type 40 false`) is sent by the
page when an editor closes (`_0d(!1)` — file68 `E()`, file30 `[testGestureEnd]`/
blur), but it can be lost: page closed mid-edit, a second editor opened on top
(one OFF only clears what it clears), or the OFF raced with a gesture
completion. Observed (user VM 2026-08-09): two type-40 sends at 12:55:36.599
and 12:55:40.876, then an endless 760 flood (wheel 512/1536, RMB 2/1026,
keycodes as raw events) with ZERO 750s until the SW reload at 12:58:31 spawned
a fresh engine (wmic scan showed no engine processes alive).

**ROOT CAUSE DISCOVERY (2026-08-09, second incident 13:49):** in MV3 the OFF
**never actually reached the native** — `sw.js postMsg()` built the message as
`{ type, content: payload || {} }`, and `false || {}` = `{}`. So every
`type 40 false` (from the UI `_0d(!1)` AND from the SW watchdog) was sent as
an **empty object**, which the native does not interpret as "disable capture".
Both incidents healed only via SW reload (fresh engine = capture off). The MV2
original sent the raw `false` (no `|| {}` fallback) — capture release always
worked there. Fixed: coalesce only `null`/`undefined` payloads.

**MV3 heal (sw.js, no bundle rebuild)** — staged recovery:
1. **Track every type-40** (`__acCaptureT`/`__acCaptureOn`/`__acCaptureStage`
   in `case "postMsg"` + `_acNativeSend`); any 750 or new toggle resets.
2. **Stage 0 → 1 (release)**: a raw-760 streak with no 750 and no recent
   toggle → re-send `type 40 false` TWICE (60ms apart — covers the two
   independent modes). **THE RECORDING GATE (2026-08-09, final)**: no rate
   metric can distinguish a human typing in the combo editor from a stuck
   flood (user VM 14:47: 38 keys / 78 events / 16.3s looked "dense" by every
   threshold; earlier attempts used avg-gap <800ms and a rolling 2s window
   ≥12 events — both were fooled). So: **while `__acCaptureOn` is true (the
   page armed capture — an editor session is open) the page-open path NEVER
   heals** — the editor's own OFF now works (payload fix) and releases on
   close. The page-open path heals ONLY when the page ALREADY sent its OFF
   (`__acCaptureOn === false`) yet raw 760s still flow — that is DEFINITELY
   a stuck native (the OFF was lost/raced), with thresholds ≥10 events,
   streak >8s, no toggle >15s. No page open = ≥6 events, streak >3s, no
   toggle >3s (recording is impossible without the tester UI; page-gone
   release fires first when the page closes while armed). Type-40 tracking
   lives in `postMsg()` (single choke point — covers the page proxy,
   `_acNativeSend` and the bundle's `_Lk`); the escalation stage resets only
   on ARMING, so the watchdog's own OFF does not cancel its escalation.
3. **Page-gone release (fast)**: the last settings page closes while capture
   is armed (`tabs.onRemoved` → `__acCheckExtPages()`, plus the `broadcast()`
   0-tabs check) → immediate OFF. This heals the user's exact repro (close
   settings during gesture recording) in ~1s.
4. **Stage 1 → 2 (escalation)**: flood continues ~8s after the OFF → the
   engine is wedged → `port.disconnect()` → fresh Zero+engine (the capture
   flag lives in the engine; a fresh engine starts clean).
5. **Stage 2 → 3 (last resort)**: even the fresh engine floods →
   `chrome.runtime.reload()` (the proven heal in both incidents).

Normal mode produces ZERO 760s, so any 760 streak is unambiguous. Log prefix
`[AC-CAPTURE]`. mh_test B33/B35.

---

## 5. Trigger Event Processing (type 750)

### Trigger ID Decoding

```javascript
_Sk = Date.now() / 864E5 | 0;  // Days since epoch, changes daily
_su = <additional shift>       // (from original code, typically small integer)

// Transform table lookup:
let transformFn = _pg[a.id - _Sk + _su];

// If transform function exists, apply it:
if (transformFn) {
    a.trigInstId = transformFn(a.trigInstId);
    if (!a.trigInstId) return;  // Transform rejected
}

// Gesture data enrichment:
if (a.mouseGest) {
    a.trigInstId = _qt(a.trigInstId, {usePrevMousePos: a.mouseGest});
}

// External event data:
if (a.extEvtData) {
    if ("tabs" in a.extEvtData) a.extEvtData.tabs = _Dw(a.extEvtData.tabs);
    a.trigInstId = _qt(a.trigInstId, a.extEvtData);
}

// Final trigger execution:
_6y(16777215 & a.id - _Sk, a.trigInstId);
// triggerId = 16777215 & (a.id - _Sk)
```

### Trigger Event Fields (from native):

| Field | Type | Description |
|-------|------|-------------|
| `id` | number | Raw trigger ID (includes daily offset) |
| `trigInstId` | any | Trigger instance data (may be null) |
| `mouseGest` | bool | Whether this is a mouse gesture trigger |
| `extEvtData` | object | External event data (optional) |

---

## 6. Gesture Data (type 760, actionType 71)

### When native is in gesture mode (type 40 `{mouseGest:66}` sent):

```javascript
// z[760] handler:
y(_Lj(a.actionType), a.actionSpec);

// Where:
// a.actionType = 71  →  _Lj(71) = "G" (Gesture)
// a.actionSpec = {state: <num>, dir: <num>, len: <num>, x: <num>, y: <num>}

// State decoding (via String.fromCharCode):
// 73 = 'I' = Idle/End of gesture
// 83 = 'S' = Start of gesture
// 67 = 'C' = Coordinate/Movement

// Direction decoding (via _Lj = String.fromCharCode):
// dir values map to direction characters
```

### When native is in capture mode (type 40 `true` sent):

```javascript
// a.actionType = 69  →  _Lj(69) = "E" (Event)
// a.actionSpec = key code (number)
// Special codes:
//   2    = right button down
//   4    = middle button down
//   512  = wheel/scroll
//   1024+code = release (e.g. 1026 = right button up)
```

### Key-press pair pattern (observed 2026-08-09, user VM logs)

In event-capture mode each physical key press produces TWO type-760 events
(69): **down = vk code, up = vk + 1024** (`_mk`), ~120-250ms apart — e.g.
65/1089 (A), 87/1111 (W), 162/1186 (LCtrl), 160/1184 (LShift).
Interleaved actionType-71 (gesture coords) events appear during editor
recording sessions alongside the 69s.

Observed vk codes (`actionSpec` of 69):

| vk | Key | vk | Key | vk | Key | vk | Key |
|----|-----|----|-----|----|-----|----|-----|
| 48-57 | 0-9 | 65-90 | A-Z | 160 | LShift | 186 | `;` |
| 188 | `,` | 190 | `.` | 191 | `/` | 219 | `[` |
| 221 | `]` | 222 | `'` | 162 | LCtrl | 164 | LAlt |

IMPLICATION for the MV3 capture watchdog: every key = a down/up PAIR, so
any rate-based "density" metric (avg gap, events-per-2s window) is fooled by
human typing in the combo editor — the definitive recording discriminator is
the SW-side `__acCaptureOn` flag (NATIVE_PROTOCOL §4), not event rates.

### Type 100 (outgoing, gesture trail)

`type 100` (`_fk`) is **OUTGOING** (SW → native) — the settings page sends it
while a recording is in progress to draw the gesture trail (observed as
`→ Native type 100` in SW logs, interleaved with 760s during recordings;
not present in stuck-capture floods). Earlier watchdog designs used it as a
"recording active" signal (trail gate); superseded 2026-08-09 by the
`__acCaptureOn` gate.

---

## 7. Config Loading Chain (file47.js)

### Messages sent during config load:

```
_lr():
  type 70 → [joystickOrder]
  (??)   → mouseGest.params (via _Jp)
  (??)   → mouseGest.display (via _6t)
  type 65 → advOpts (via _Jf)

_6s():
  type 200 → {interval:0} (preview params)
  (waits for callback)

_no():
  type 60 → {triggers, urlTests, ...} (main config, built by _mh())
```

---

## 8. Window Focus Tracking (type 721)

```javascript
// Native sends type 721 when window focus changes:
{hWnd: <number>, noEvt: <bool>}

// Handler:
[721]: a => _y(a.hWnd, a.noEvt);

// _y() looks up the window by hWnd and focuses it
```

---

## 9. Error Handling

```javascript
// type 800 — Error from native
[800]: a => E(a);  // E is the error handler factory

// The error handler checks error types:
// "no-hook-notice"     → shows hook conflict notice
// "invalidExtId"      → checks if extension is still valid
// "APDL"              → Anti-Piracy check
// "NH-error" + code 3221225477 → segfault
// Everything else     → _Ot(h, e) logs error
//
// MV3 (2026-08-10): fully ported into mv3_native_shim.js z[800] — the
// no-hook-notice popup (_Lh, file71.html via windows.create) works from the
// SW; noHookConflictMsg lives in localStorage (in-memory in the SW → can
// re-arm after an SW restart). mh_test A2b + 75 pass / 0 gaps / 0 FAIL.
// NOTE: _Ot is NOT a native call — it is the HTTP telemetry sender
// (appEvent POST to www.autocontrol.app/appEvent, see DECODE.md). In MV3 it
// is gated by __acTel (advOpts.telemetry, off by default, 2026-08-08).
```

---

## 10. Keepalive & Ping

```javascript
// Type 905 (keepalive) — sent periodically, no-op handler
[905]: () => {};

// Type 920 (ping) — sent with empty string, expects "pong" response
_Lk(_xp, "");  // type 920 with empty string payload
// Native responds with 710 {params: "pong"}
```

---

## 11. Key Constants

| Constant | Value | Purpose |
|----------|-------|---------|
| `_7s` | 10 | File check |
| `_ro` | 20 | Init |
| `_zu` | 21 | Startup |
| `_Qr` | 40 | Capture toggle |
| `_4e` | 60 | Main config |
| `_hk` | 65 | AdvOpts |
| `_Ma` | 67 | Monitor info |
| `_5r` | 70 | Joystick order |
| `_mu` | 72 | Switch states |
| `_Jo` | 200 | Preview params |
| `_ms` | 400 | Window move |
| `_R` | 704 | Version (native→ext) |
| `_np` | 705 | Browser name (native→ext) |
| `_9p` | 710 | Promise resolution (native→ext) |
| `_mj` | 721 | Window focus (native→ext) |
| `_9g` | 740 | Clipboard (native→ext) |
| `_Hf` | 750 | **Trigger event** (native→ext) |
| `_fo` | 760 | Action/gesture (native→ext) |
| `_kw` | 800 | Error (native→ext) |
| `_xp` | 920 | Ping |
| `_jh` | 905 | Keepalive |
| `_xd` | `"AutoCtrl_2025.4.22.0.exe"` | Native exe name |

---

## 12. SW-Brain Architecture (current, 2026-08-02)

In the working port (`../mv3-build/`) the core engine runs **inside the Service Worker**, and the settings page is UI-only.

### Execution

- `sw.js` — SW-brain: `importScripts("sw_core_bundle.js")` (single file = prelude + 31 core files; separate importScripts calls do NOT share top-level const/let in Chrome).
- The settings page (`main.html`) uses `mv3_shim.js` (API substitution) — its z[750]/config chain are **stubbed** by the `isLeader()` gate (`'sw' === leader`).
- The SW itself: handshake, config chain (`_lr→_Gf→_no→_mh`), window enum, z[750] (via `_6y`), keepalive.
- `_Lk` in the shim: when `_acNativeSend` exists it sends directly to the SW port (self-messaging does NOT reach the SW's own onMessage listener).

### Handshake (SW) — exact order

```
type 10 (file check, postWithCb) → 20 (init) → 67 (monitors, chrome.system.display)
  → nativeConfigReady (broadcast to shim)
  → window enum: type 335 {refWin:0} → type 400 {win,x,y,noNotif} (per window, 2 calls: y=-1 and y=1)
  → type 72 (switch states) → config chain (types 200/65/70/60) → type 21 (startup) — LAST
```

- **Type 40 is NEVER sent at startup** (it would put native into raw capture and suppress type 750).
- `_Sk = Date.now()/864E5|0` captured at handshake (in SW and in shim at nativeConfigReady).
- `_su = parseInt(extId.substr(22,2),36)` — trigger index shift (806 for the user's extension).
- `triggerId = 16777215 & (a.id - _Sk)`.

### SW-specific fixes

- **STRIP_RBTN_BLOCK (v6)** — see section 14.
- **RBTN-ESC (v7)** — post-gesture Esc synth — see section 14.
- **Region 12 (Browser tab) BROKEN on Chrome 148+ — no extension-side fix
  (2026-08-02)** — the native's UIA hit-test cannot find tabs (MV2 and MV3
  both affected → native/Chrome issue, not the port). A SW workaround
  (TAB-GATE: replace the region with 4 in type 60 + right-margin gate via
  `_Ua`(330)) was attempted and ROLLED BACK — per-tab hover cannot be
  emulated reliably. Use region 4 (Title area) for top-row triggers. The UI
  option is marked broken in file68.js.
- Keepalive: `chrome.alarms` + `setInterval` 20s + the native port keeps the SW alive.

---

## 13. Type 60 — Config Payload (format, verified 2026-08-02)

Payload of type 60 is an object assembled by `_mh()` (file25.js):

```json
{
  "map":        {"<mapKey>": [list indices, ...]},
  "list":       [entries],
  "urlTests":   [],
  "combinSequences": {},
  "gestures":   [gesture patterns],
  "neededCaretSt": 0
}
```

**mapKey = keyId + 22025** (e.g.: key 2 → 22027, key 1026 (RCM-up) → 23051, key 85 → 22110).

### Entry types in list (entry.type)

| type | Const | Purpose |
|------|-----------|------------|
| 0 | `_Th` | Global block: `{type:0, block:true, preconds:[...]}` |
| 1 | `_wi` | Key-event (key sequence): `{type:1, param, block, PBC, preconds}` |
| 2 | `_Se` | State switch (enable/disable state N/Y) |
| 3 | `_Pp` | Auto-repeat |
| 4 | `_mp` | Gesture begin/end: `{type:4, state:true/false, timeout, block, PBC, preconds}` |
| 5 | `_tj` | Action gate (actIdx) |
| 6 | `_Ag` | keyStateChange (action): `{type:6, PBC, actIdx, preconds}` |
| 7 | `_qs` | Sequence step: `{type:7, param:{seqId, stepId}, PBC, preconds}` |
| 8 | `_Yf` | Hold-delay auto-repeat |

### Precond types (entry.preconds[i].type)

| type | Meaning | Description |
|------|----------|-------|
| 1 | keyEvt | `{type:1, key1, key2}` — another key is held |
| 2 | `_ot` | chromeState active (value:1) |
| 4 | `_2k` | prevSeqStep `{type:4, maxTime, seqId, stepId}` |
| 6 | `_8` | wildcard (value) |
| 7 | `_5a` | actionState `{type:7, value:68('D'), actIdx}` |
| 9 | `_Ku` | keyStateChange (value:0/1) |
| 11 | `_5` | mouseGestState `{type:11, value:83('S')}` (83='S', 73='I', 67='C') |
| 13 | `_0y` | menuState `{type:13, menuNum, negate?}` — menuNum = the menu entity id (`_lk("menuSpec:7")` → 7). **`negate:true` = the menu must NOT be open.** The native evaluates this itself (it owns the menu overlay). Verified 2026-08-30: the Smart Ctrl+Tab set compiles openMenu (menu-closed) as `{type:13,menuNum:7,negate:true}` and moveSelectMark/selectMarkedItem (menu-open) as `{type:13,menuNum:7}` — with the negation the native fires the closed-menu triggers only when NO menu is open |
| 14 | `_bt` | mouseOver region |

### PBC (Pressed Button Count)

`PBC: {"<devId>": <count>}` — how many buttons of the device must be held for activation.
- `{1:1}` — one mouse button held; `{1:-1}` — release (up-event).
- devId 0 = keyboard, 1 = mouse.

---

## 14. RCM/LCM bug on Chrome 150 — root cause and fixes (v6+v7, 2026-08-02)

### Cause

The gesture preset `_Bh(_md)` (file3.js, `_Vi.rightButton`) compiles begin/end entries with `block:true` under **key 2 (RCM press)** AND under **key 1026 (RCM-up, 2|_mk)**:

```
2→{type:4,state:true,timeout:1500,block:true,PBC:{1:1},...}   // gesture begin
2→{type:0,block:true,...}                                      // global block (M||V branch in _mh R())
1026→{type:0,block:true,preconds:[{type:11,value:83},{type:7,value:68,actIdx:40}]}
     // blocks RCM-up while gesture is in S and action in D
```

The `M||V` branch in `_mh R()`: `if(r.block && I) { ...; if(M||V) n(e.eventId,{type:_Th,block:!0},...) }` — for begin (M: type==_mp && state) and end (V: type==_mp && !state).

**Consequence:** while the gesture is in state S (83='S') and the action is running (D=68), native swallows the RCM-up and does not update its PBC counter → after the gesture it still thinks RCM is held → the next LCM is read as a rocker combo and globally blocked until a manual RCM click (on that click the gesture is no longer in S → the block doesn't match → the up reaches native).

### v6 — block softening (STRIP_RBTN_BLOCK)

`sw.js: stripRightButtonBlocks(payload)` — for key 2 **and key 1026** every entry with `block:true` gets `block:false` (entries are kept — gestures still work). RCM-up is never blocked → native always sees the release → no sticking. Single choke point in `postMsg()` for type 60.

**v6 side effect:** RCM-up now passes through to Chrome → a context menu pops open after every gesture.

**UPDATE (2026-08-30, issue #1 "right click menu override not working"):**
1. v6 softened BOTH keys — that KILLED mouse gestures (the `block:true` on key 2 DOWN is what makes the native intercept the right button and start gesture recognition). The strip now leaves key 2 untouched and softens ONLY key 1026.
2. Softening EVERY 1026 block also killed the user's **right-click menu override** — the trigger "RMB, block mode 'up'" compiles
   ```
   1026→{type:0, block:true, preconds:[{type:8(actionDone), value:1, actIdx}]}
   ```
   which is what makes the native swallow the RMB release so the context menu stays closed (MV2 behavior). The strip is now SELECTIVE: only entries gated on the native gesture state machine (mouseGestState precond, `type:11`) are softened — the gesture-preset blocks — while the user's actionDone-gated block:up entries are PRESERVED.
3. VERIFIED LIVE (2026-08-30, Chrome 150, real OS RMB via `Test/_ac_mouse.ps1` + page `contextmenu` event probe): with the user's block:up intact — RMB → **NO contextmenu event reaches the page** (native swallows down+up), the trigger fires (pinTabs executed), LMB after RMB passes through normally, no spontaneous re-fires, no PBC stick. The gesture-preset 1026 block still gets softened ("STRIP_RBTN_BLOCK: softened 1 gesture block entries").
4. ⚠ `{type:14}` mouseOver preconds do NOT gate triggers on Chrome 150 AT ALL (verified 2026-08-30: region 3 "Web page" and region 4 "Title area" both fire everywhere — native a11y hit-test regression; affects MV2 AND MV3; no extension-side fix — no cursor-position API).

### v7 — auto-Esc after gesture

`scheduleGestureEsc()` — after a gesture (type 750) sends a synthetic Esc after 50ms:

```
type 300 (SendInput) → [27, 1051]   // Esc down (27), Esc up (27|_mk=1024)
```

Gesture detection (so Esc is NOT sent after hotkeys): `data.mouseGest` OR a type 760 (raw gesture stream) within 2000ms before the 750.

---

## 15. Type 300 — SendInput (synthesized input)

Payload format: **array of eventIds** (not an object):

```json
[<eventId>, <eventId>, ...]
```

Each eventId = keyId | type bits (`_eh()` from file57.js: `type = a & 64512`, `num = a & ~64512`):

| eventId | Meaning |
|---------|-------|
| 2 | RCM down (keyId 2, type `_Lo`=0) |
| 1026 | RCM up (2 \| `_mk`=1024) |
| 27 | Esc down (VK_ESCAPE=27) |
| 1051 | Esc up (27 \| _mk) |
| 512 | Vert. wheel |
| 1536 | Vert. wheel up-event (512\|_mk) |

Tuples `[2|_N, x, y, hold]` (mouse moves) are only used by the full sendInput engine (file15.js y()); plain numbers suffice for simple taps. The synthesis goes through Windows SendInput — events reach the native's low-level hook.

---

## 16. Message types — complete list (file56.js)

| # | Const | Dir | Purpose |
|---|-----------|-------|------------|
| 10 | `_7s` | → | File check `{fileName}` — answer `0`=ready, `2`=missing OR engine still starting (see sec. 18) |
| 20 | `_ro` | → | Init `{iTime, crVer, variant}` |
| 21 | `_zu` | → | Startup (last in handshake) |
| 30 | `_Z` | → | File size query |
| 35 | `_6k` | → | (—) |
| 40 | `_Qr` | → | Capture toggle (raw input / mouseGest:66) |
| 50 | `_Qw` | → | Trigger event injection `{evtId, trigInstId}` |
| 55 | `_vh` | → | Emergency repair — **ACK ONLY, does NOT restart the engine by itself** (see sec. 18) |
| 60 | `_4e` | → | **Config (trigActList, see sec. 13)** |
| 65 | `_hk` | → | AdvOpts |
| 67 | `_Ma` | → | Monitor info `[{x,y,dpi}]` |
| 70 | `_5r` | → | Joystick order |
| 72 | `_mu` | → | Switch states `{states:{id:bool}}` |
| 80 | `_Ei` | → | (—) |
| 90 | `_Xa` | → | Icons (toolbar buttons) |
| 100 | `_fk` | → | Gesture trail (draw) |
| 110 | `_Cf` | → | Gesture trail (move) |
| 122/125/130/135 | — | → | (—) |
| 136 | `_Mu` | → | Tab replaced `[oldTabId, newTabId]` |
| 140 | `_5t` | → | Tab state `{tabId, win, time, popup}` |
| 150 | `_ta` | → | Tab focus `{tabId, win}` |
| 160–197 | — | → | (—) — see 170/175/185 below |
| 170 | `_b` | → | **Open menu** `{menuData:{style,items:[{title,icon(base64),...}]}, menuEntityNum, position, alignHorz, alignVert, menuSystem, usePrvMsPos}` → `true` = accepted/drawn (file26 `_Bp`; the tab-switcher list is such a menu, menuNum 7) |
| 175 | `_Ws` | → | **Menu state query / close** — with `null` content it is the bundle's `H()` "is a menu open?" check (file26): → `true` = a menu is open, `false`/falsy = none; the `closeMenu` action ALSO sends `175 null` (the actual close happens native-side, e.g. after `selectMarkedItem` selection). Verified 2026-08-30: `true` while the tab-switcher menu is open |
| 185 | `_3f` | → | **Menu state detail query** `{usePrvMsPos}` → `{hilited, hovered, marked}` item indices; `{}` when no menu is open (per 2026-08-30 CDP probe) |
| 200 | `_Jo` | → | Preview maker params `{interval}` |
| 205 | `_Ia` | → | (—) |
| 210 | `_Ww` | → | (—) |
| 240 | `_e` | → | (—) |
| 250 | `_Q` | → | **File WRITE (chunked)** `{path, content, end:true}` → 710 `0` = OK (saveURL flow; AGENTS: `_4u` chunked write; **NOT read — corrected 2026-08-09** from the API-test log) |
| 255 | `_0f` | → | **File READ (chunked)** `{path, id, charEnc:true, chunk:200000}` → 810 chunk `{chunk, id, type}` → 710 `{charEnc, content, mime, modTime, size}` (getFile flow; **NOT write — corrected 2026-08-09**) |
| 256 | `_vr` | → | (—) |
| 260 | `_7e` | → | Run shell command `{file,args,dir,...}` — **IMPORTANT (2026-08-04): the native resolves the callback (710) as soon as cmd.exe STARTS (~7 ms), NOT when the command finishes**. An async `del /Q /F AutoCtrl_*.exe` therefore ran AFTER the type-250 engine write and deleted the freshly written engine ("file flashed and vanished" during install). Commands that MUST complete before the next step (file deletion, etc.) cannot be sequenced via this callback — keep the 710 round-trip for stdout/exitCode (`getStdout:true`) and use taskkill/write-overwrite instead of del. **exitCode 259 = STATUS_STILL_ACTIVE (0x103) — normal for taskkill (async kill), not a failure (see sec. 18).** |
| 270 | `_Qa` | → | (—) |
| 280 | `_tl` | → | Clipboard read `{format:1}` → `{content, format, size, trueFmt}` (format 13 = text `_fd`) |
| 285 | `_t` | → | Native action cmd `{cmd:2}` (clpbrdPaste) → null; callback INSIDE content (with 240/490 — file61.js `_Lk`) |
| 286 | `_Hi` | → | Clipboard write `{data, fmt, "":true}` → true; **clears the extension's clipboard text buffer** (`_Lf(void 0)` after send — file61.js) |
| 292–295 | — | → | (—) |
| 300 | `_Dt` | → | **SendInput (see sec. 15)** |
| 305 | `_bg` | → | (—) |
| 310 | `_je` | → | (—) |
| 315 | `_be` | → | Input lock `{state:true/false}` |
| 320 | `_8p` | → | Mouse block `{state}` |
| 330 | `_Ua` | → | Mouse pos query |
| 335 | `_uo` | → | Window enum / hijack probe `{refWin, inclHjkd}` (file74 `_Ry`) |
| 336 | `_Eo` | → | (—) |
| 340 | `_bw` | → | Use previous mouse pos `{usePrvMsPos}` |
| 344 | `_6f` | → | Window state check `{content:[hWnd]}` → `{hWnd: bool}` (file89 `_O`; feeds the `_Jr` cache + getTabInfo) |
| 350 | `_Hr` | → | Minimize |
| 355 | `_tp` | → | Maximize |
| 360 | `_ng` | → | (—) |
| 365 | `_si` | → | Topmost |
| 370+ | — | → | (—) |
| 400 | `_ms` | → | Window move `{win,x,y,noNotif}` |
| 403–450, 452–490 | — | → | (—) |
| 451 | `_ya` | → | Native diagnostics `{PBC, actWinMine, appUserModelIDs, downKeys, focusWin, ...}` (sent before type 55, see sec. 18) |
| 470 | `_2p` | → | Resolve special-folder path `{content:CSIDL}` → path string (16 = Desktop; file50 `_Pf` cache) |
| 704 | `_R` | ← | Version `{verNum}` |
| 705 | `_np` | ← | Browser name `{exeName}` |
| 710 | `_9p` | ← | **Promise resolution `{id, params}`** (callback echo) |
| 715/720 | — | ← | (—) |
| 721 | `_mj` | ← | Window focus `{hWnd, noEvt}` |
| 730 | `_Ki` | ← | Clipboard list |
| 735 | `_Qg` | ← | Window minimize state |
| 740 | `_9g` | ← | Clipboard format |
| 750 | `_Hf` | ← | **Trigger event `{id, trigInstId, mouseGest?, extEvtData?}`** |
| 760 | `_fo` | ← | **Action/gesture event `{actionType, actionSpec}`** (raw gesture stream) |
| 765 | `_0i` | ← | (—) |
| 770–790 | — | ← | (—) |
| 800 | `_kw` | ← | Error `{type, ...}` ("no-hook-notice" etc.) |
| 801/802 | — | ← | (—) |
| 810 | `_ef` | ← | File-read chunk `{chunk, id, type}` (reply to 255) |
| 900/901 | — | → | (—) |
| 905 | `_jh` | → | Keepalive |
| 910 | `_8d` | → | (—) |
| 920 | `_xp` | → | Ping (reply "pong" via 710) |
| 930–943 | — | → | (—) |

---

## 18. Emergency Repair (type 55) — semantics & engine restart cycle (2026-08-08)

**KEY INSIGHT (verified on VM 00:38 / 00:53, 2026-08-08): type 55 does NOT
restart the engine by itself.** The native acks it with `710 {params:true}`
in ~1ms and nothing else happens (engine PID unchanged, 4 clicks — no
restart). The engine restart in MV2 came from a SIDE EFFECT: `_co(1)`'s
`location.reload()` reloaded the BACKGROUND PAGE → the native port dropped →
Zero exits on EOF → the fresh page reconnects → a fresh Zero spawns a fresh
engine. Type 55 is just an ack.

### MV2 flow (file62.js onClicked "reloadExtn" → file34.js `_co(1,!0)`)

```
1. onClicked → _Vy(_ya)        // type 451 — native diagnostics
2. _co(1,!0):                  // c=true → badge "Wait" (#F00) + _9k("showNotif",!0)
3. _Lk(_vh=55, null, cb)       // type 55, content:null → native acks 710 true
4. location.reload()           // ← THE restart: page reload → port drop →
                               //   Zero exits → next connect spawns fresh engine
5. new page: _nt("showNotif")  // badge " OK " (#0BAD01) or "Error" (#F00)
   → yield _Eu.wait()          // shown AFTER the reconnect, 1s then cleared
```

### Type 451 response shape (observed)

```
710 {params: {PBC: Array(10), actWinMine: bool, appUserModelIDs: {...},
     downKeys: Array, focusWin: hWnd, ...}}
```

### MV3 (SW-brain) equivalent — repair = SW reload (FIX 15, 2026-08-08)

The SW implements MV2's "background-page reload" as its own reload — this is
what actually restarts the engine (port drop → Zero exits on EOF → the fresh
SW reconnects → fresh Zero spawns a fresh engine):

```
1. type 55 → native acks true (fire the bundle callback → tabs.reload of
   open settings pages only)
2. _acNativeSend a===55 branch → __acEmergencyRestartNative():
   chrome.storage.local.set({ __acRepairBadge: true }) →
   chrome.runtime.reload()   // ← THE restart (fresh SW = fresh engine)
3. fresh SW: proceedAfterFileCheck consumes __acRepairBadge (storage
   survives the reload) → badge " OK " (#0F0) + clear 2s — shown ONLY
   after the reconnect succeeded (MV2 shows OK after the reload reconnects)
```

NOTES (FIX 12/14 history — do NOT resurrect):
- **NO taskkill /F of the engine.** TerminateProcess leaves its global hooks
  (WH_KEYBOARD_LL/WH_MOUSE_LL) DANGLING — the next engine gets no input for
  ~40s (user VM 01:36: first trigger 43s after a taskkill-based repair).
- **NO in-memory `__acRepairBadgePending`** — the badge flag must survive the
  SW reload, so it lives in `chrome.storage.local` as `__acRepairBadge`.
- **NO port.disconnect() / 20s Error timer** — the reload IS the cycle.
  A lingering old engine keeps LIVE hooks (events reach ALL hooks), so no
  kill is needed; hooks are cleaned when the fresh engine takes over.
- User-verified: hotkeys bind IMMEDIATELY after the reload.

### Related protocol facts (same session)

- **Type 10 file check**: `0` = engine ready; `2` = file missing OR engine
  still starting (Zero answers 2 until the engine is up, even when the file
  exists). Disambiguate with type 260 `if exist` (getStdout) —
  `__acEngineFileExists`.
- **Zero→engine lifecycle**: EVERY `connectNative` spawns a NEW Zero→engine
  pair. Orphan engines (from Zeros whose ports died without closing them)
  linger and CRASH the fresh engine on type 140 (ACCESS_VIOLATION
  0xC0000005) → `__acKillOrphanEngines` (wmic: kill engines whose Zero
  parent is dead; a live pair of ANOTHER browser is never touched).
- **Type 260 exitCode 259** = STATUS_STILL_ACTIVE (0x103) — the command is
  still running; for taskkill this is NORMAL (async kill). Do not treat it
  as a failure.
- **NEVER hard-kill the engine with taskkill /F (2026-08-08, FIX 14)**:
  TerminateProcess leaves its global hooks (WH_KEYBOARD_LL/WH_MOUSE_LL)
  DANGLING in Windows — the next engine gets NO input for ~40s until the
  system cleans the hooks up (user VM 01:36: first trigger 43s after a
  repair that used taskkill). MV2 semantics: restart = background-page
  reload → port drop → Zero exits on EOF → reconnect → fresh Zero+engine; a
  lingering (detached) engine keeps LIVE hooks and events still reach all
  hooks, so no kill is needed.
- **MV3 Emergency Repair = SW reload (2026-08-08, FIX 15)**: the MV2
  "background-page reload" is implemented as `chrome.runtime.reload()` in
  the SW — a fresh SW re-runs connectNative → fresh Zero → fresh engine
  with fresh hooks. User-verified: hotkeys bind IMMEDIATELY after an
  extension reload (a port-drop-only cycle sometimes left the old engine
  alive without a working pipe). The " OK " badge survives the reload via a
  storage flag (`__acRepairBadge`), consumed by the fresh SW in
  proceedAfterFileCheck.

---

## 19. Type 760 — action/gesture (detail)

```
type 760: { actionType: <number>, actionSpec: <...> }
```

- actionType **71** ('G') — gesture: `actionSpec = {state, dir, len, x, y}`
  - state: 73('I')=idle/end, 83('S')=start, 67('C')=move
  - dir: direction code (via `_Lj(dir)` = `String.fromCharCode`)
- actionType **69** ('E') — capture event (when type 40=true): `actionSpec = keyId`
  - 2=RCM down, 4=Middle down, 512=wheel, 1024+keyId=up (1026=RCM up)
- **type 760 flows only while a gesture is being recognized** — used as a gesture fingerprint for v7 (see sec. 14).

---

---

> **§20 removed 2026-08-11** — the old "Known MV3 degradations" table was
> stale (playAudio/Toasts/`_6t` closed since 2026-08-09/10). Canonical status
> list: `FEATURES-MV3.md` §7 (port gaps), §8 (impossible in MV3).



---

## 20. Ctrl+Tab "Smart switching" — compiled trigger map (verified 2026-08-30)

The imported set "Smart Ctrl+Tab switching" (site
`switch-to-last-used-tab-in-chrome.htm`, 6 triggers) compiles to this map
(`mapKey = keyId + 22025`):

| mapKey | keyId | What the native sees |
|--------|-------|----------------------|
| 22034 | 9 (Tab down) | hold-arm `{type:8, evtId:6145, delay:400, block:true, preconds:[menuState 7 negate:true, chromeState, keyEvt Ctrl(162), wildcard 2]}` + moveSelectMark entries (param 811 = entry+_su, no menuState negate) |
| 28170 | 6145 (Tab held, fired by the native after the 400ms delay) | **openMenu** `{type:1, param:812, block:true, preconds:[menuState 7 negate:true, chromeState, keyEvt Ctrl, wildcard 2]}` → the extension builds the tab list (menuData, TSE currWinTabsMruOrder) and sends type 170 |
| 23058 | 1033 (Tab-up) | activateTabs prevUsedTab (menuState 7 negate:true, block:2) — quick-press MRU switch |
| 23211/23212 | 186/187 (Ctrl left/right; up-events encoded as PBC `{"0":-1}`) | selectMarkedItem+closeMenu (no negate — menu open), activateTabs prevUsedTab (Ctrl-up with Tab held, negate), activateTabs currentTab (Ctrl-up, negate) |

Trigger ids on the wire: `triggerId = entryId + _su` (`_su` = salt from the
extension id, `parseInt(id.substr(22,2),36)`; entry 6 → 812 for the current
build). The SW decodes with `16777215 & (id - _Sk)` where `_Sk =
Date.now()/864E5|0` frozen at handshake.

**Root cause found 2026-08-30 ("tab list does not open after reload")**:
the SW-side `Object.prototype.in` re-patch used `a.indexOf(t)` which broke
the bundle's array-passing idiom `x.in([...])`; `keep()` (file25 config
compiler) then deleted the `negate:true` flag from every menuState precond →
ALL triggers compiled as "menu 7 IS open" → openMenu (menu-closed trigger)
never fired, Tab/Ctrl passed through to Chrome's own Ctrl+Tab. Fixed by
restoring file67's `_Xt` semantics (flatten args one level, strict `===`)
plus the unboxing. See AGENTS.md "Object.prototype .in" gotcha.
