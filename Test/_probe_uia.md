# _probe_uia.md — UIA probe for browser chrome elements

**File:** `Test/_probe_uia.ps1` — read-only UI Automation probe (does not move
the cursor, does not write anything outside the console).

## Purpose

The zone helper (`ac_zone_helper.cs`) classifies the cursor position through
**MSAA** (oleacc / `IAccessible`). Screen readers (NVDA and others) use
**IA2 / UIA** — different layers of the same Chromium accessibility tree, and
Chromium does not always expose the same elements in both. This probe answers
the question *"does UIA expose element X in this browser window?"* so that
MSAA-only conclusions are cross-checked against UIA before being trusted.

Used 2026-09-20 to settle the "kebab works only with the Hindi UI" report:
the kebab IS exposed in **both** MSAA and UIA as `role 57 BUTTONMENU`
named `"Chrome"`. The earlier "missing in Chrome 150" report was made
on an outdated build and could not be re-checked at the time. The language
was never involved.

## What it prints (per window)

1. Every `Button` / `MenuButton` element in the window's UIA tree:
   name, bounding rect, AutomationId (`view_*` for Chrome chrome).
2. Lookup of known Chrome AutomationIds:
   `chrome_menu_button`, `menu_button`, `toolbar_button`,
   `profile_avatar`, `extensions_menu` (all "not found" in current
   Chromium — the kebab is found by name/rect, not by AutomationId).

## Usage

```powershell
powershell -NoProfile -File Test\_probe_uia.ps1
```

Edit the `$w` list at the top of the script to point at the window(s) of
interest:

```powershell
foreach ($w in @(@{n='Canary'; h=0x26D96854}, @{n='PortableChrome'; h=0x207A0F24})) {
```

`h` = the window handle (decimal or `0x…`), e.g. from
`(Get-Process chrome | Where-Object { $_.MainWindowHandle -ne 0 }).MainWindowHandle`.

## Related

* `Test/ac_zone_helper.cs` — the MSAA zone classifier (what actually ships).
* `Test/msaa_chain.ps1` — MSAA ancestry dump for a point (role + name per level).
* `Test/zone_scan.ps1` — MSAA signature sweep over a browser window.
