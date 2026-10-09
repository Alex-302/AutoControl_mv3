# _probe_uia.ps1 - UI Automation probe for browser chrome elements.
#
# WHY: the zone helper classifies through MSAA (oleacc / IAccessible), but
# screen readers (NVDA et al.) use IA2/UIA - different layers of the same
# Chromium accessibility tree. This probe answers "does UIA expose element X?"
# (the kebab, the profile avatar, the extension icons) for a given browser
# window, so MSAA-only conclusions can be checked against UIA before they are
# trusted (used 2026-09-20: the Chrome 150 kebab was missing from BOTH MSAA
# and UIA, while Chrome 153+ exposes it in both as "Chrome").
#
# What it prints per window:
#   * every Button / MenuButton element (name, rect, AutomationId),
#   * known Chrome AutomationIds (chrome_menu_button, profile_avatar, ...).
#
# Run: powershell -NoProfile -File Test\_probe_uia.ps1
# (edit the $w list: @{n='name'; h=<hwnd>})
Add-Type -AssemblyName UIAutomationClient
Add-Type -AssemblyName UIAutomationTypes
foreach ($w in @(@{n='Canary'; h=0x26D96854}, @{n='PortableChrome'; h=0x207A0F24})) {
  $root = [System.Windows.Automation.AutomationElement]::FromHandle([IntPtr]$w.h)
  if (-not $root) { Write-Output "$($w.n): no element"; continue }
  Start-Sleep -Milliseconds 1500
  Write-Output "=== $($w.n) ==="
  foreach ($ct in @([System.Windows.Automation.ControlType]::MenuButton, [System.Windows.Automation.ControlType]::Button)) {
    $c2 = New-Object System.Windows.Automation.PropertyCondition([System.Windows.Automation.AutomationElement]::ControlTypeProperty, $ct)
    $els = $root.FindAll([System.Windows.Automation.TreeScope]::Descendants, $c2)
    Write-Output "  ControlType=$($ct.ProgrammaticName): $($els.Count) elements"
    for ($i = 0; $i -lt [Math]::Min($els.Count, 12); $i++) {
      $e = $els.Item($i)
      $nm = $e.Current.Name; $rt = $e.Current.BoundingRectangle
      Write-Output ("    [{0}] '{1}' rect={2},{3} {4}x{5} aid={6}" -f $i, $nm, [int]$rt.X, [int]$rt.Y, [int]$rt.Width, [int]$rt.Height, $e.Current.AutomationId)
    }
  }
  foreach ($id in @('chrome_menu_button','menu_button','toolbar_button','profile_avatar','extensions_menu')) {
    $cond = New-Object System.Windows.Automation.PropertyCondition([System.Windows.Automation.AutomationElement]::AutomationIdProperty, $id)
    $el = $root.FindFirst([System.Windows.Automation.TreeScope]::Descendants, $cond)
    if ($el) {
      $nm = $el.Current.Name
      $rt = $el.Current.BoundingRectangle
      Write-Output ("  AutomationId={0} FOUND name='{1}' rect={2},{3} {4}x{5}" -f $id, $nm, [int]$rt.X, [int]$rt.Y, [int]$rt.Width, [int]$rt.Height)
    } else {
      Write-Output "  AutomationId=$id - not found"
    }
  }
}
