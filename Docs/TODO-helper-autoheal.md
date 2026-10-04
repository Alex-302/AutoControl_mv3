# TODO — Helper auto-recovery for a HUNG `ac_zone_helper.exe` (2026-09-05)

**Status:** ⬜ open — DEFERRED by the user 2026-09-12 ("put it in the TODO,
for later"). Not blocking anything: Emergency Repair heals a hung helper
manually, and a DEAD helper self-heals via `onDisconnect`.

**Problem:** if `ac_zone_helper.exe` hangs (process alive but not answering
stdin), every zone request times out (250 ms) → `zone=-2` → ALL zone-gated
actions silently skip until the SW restarts. If the helper process DIES,
`onDisconnect` already resets the port → the next request spawns a fresh
process (self-healing works). Only the HANG case is unhealed.

**Manual Emergency Repair DOES work** for the hang case: it reloads the SW →
fresh SW → new `connectNative` → Chrome spawns a NEW helper process (it does
not reuse the hung one) → everything recovers. The hung process stays as a
zombie until reboot (cosmetic).

**TODO — two options (user asked to track both):**

1. **Automatic helper self-heal (preferred, ~10 lines in `sw.js`):** in
   `__acZoneAsk`, count CONSECUTIVE timeouts — after 3 in a row do
   `__acZonePort.disconnect(); __acZonePort = null;` → the next request
   creates a fresh process. Mirrors the capture-watchdog pattern. No bundle
   rebuild needed (sw.js is not in the bundle). Also log
   `[AC-MV3-ZONE] helper unresponsive — respawning` for diagnosability.
   ⚠ **MULTI-BROWSER SAFETY (user requirement, 2026-09-05):** several
   browsers may each run their OWN `ac_zone_helper.exe` (one per browser's
   connectNative). ANY process kill must target ONLY OUR helper process —
   never a blanket `taskkill /IM ac_zone_helper.exe` (would kill the other
   browsers' live helpers). Implementation: the helper replies with its own
   PID (`{__id, zone, pid}` — `Process.GetCurrentProcess().Id` in
   `ac_zone_helper.cs`); the SW stores it on the first reply and, when
   respawning, either just `port.disconnect()` (Chrome terminates the
   process it spawned — the SAFE default, no taskkill needed) or, if a
   hard kill is ever required, `taskkill /PID <stored pid>` only.
   Note: Chrome kills the native host when its port disconnects, so
   `port.disconnect()` alone should suffice for the hang case.
2. **Emergency Repair integration (already works, document only):** the
   manual repair path heals the helper via the SW reload; add a doc note
   (README §4.3, or the helper-recovery note in `Docs/GOTCHAS.md`) that a hung helper is fixed by Emergency
   Repair. Optionally: kill ONLY OUR stale helper zombie during the repair
   (via the stored PID — see above; NEVER by image name).

**Status:** ⬜ open — implement option 1 (auto-heal with PID tracking),
optionally option 2's PID-scoped zombie kill; document option 2 in the
README.

**⏸ DEFERRED (2026-09-12, user request):** tracked in the backlog, to be
implemented later. Not blocking anything: Emergency Repair heals a hung
helper, and a DEAD helper self-heals via `onDisconnect`.
