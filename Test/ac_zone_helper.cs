// ac_zone_helper — AutoControl zone classifier helper (2026-09-03).
//
// WHY: the abandoned native engine cannot classify zone 12 (tab strip) on
// Chrome 148+ — its hover cache never refreshes over the tabs, and a FRESH
// AccessibleObjectFromPoint from the LL-hook context DEADLOCKS (Chrome
// does not answer WM_GETOBJECT during input processing; RE doc §12).
// This helper answers "what zone is under the cursor?" from a NORMAL
// process context (no hooks) — proven safe by Test/zone_proto.ps1.
//
// Protocol (Chrome native messaging): 4-byte LE length + UTF-8 JSON.
//   request:  { "__id": 1 }                 - zones only
//             { "__id": 1, "tab": 1 }      - + the tab under the cursor
//   response: { "__id": 1, "zone": 12, "zones": [12, 1] }
//             { "__id": 1, "zone": 12, "zones": [12,1], "hWnd": N, "index": I, "title": "..." }
// "tab":1 exists because native type 485 (the tab under the mouse) lost its
// tab identity on Chrome 148+; the SW answers 485 from here (see TabIndexOf).
// "zones" = every zone matching the cursor (the original engine evaluated
// each trigger's region independently - several zones can be true at once:
// the omnibox is inside the toolbar band, the page is inside the browser
// window). "zone" = the most specific one (logging / older SW builds).
// Zones: 1 window, 3 page, 4 title area, 12 tab, 15 close, 16 new-tab "+",
//        17 speaker, 20 toolbar, 21 omnibox, 30 menu button, 33 bookmark;
//        -1 = cursor/AOP error, -2 = SW-side timeout.
// Signatures live-verified on Chrome 150 SxS (Docs/TODO-mouseover-zones.md
// sections 2/2d/2e); scanners: Test/zone_scan.ps1 .. zone_scan5.ps1,
// Test/zone_chain.ps1, Test/zone_probe.ps1.
//
// 2026-09-12 fixes (user report):
//  * TITLE AREA (4) = the title bar / tab strip row ONLY (the UI description
//    in the action editor: "When the mouse is over the title bar or tab
//    strip"). The toolbar and the omnibox are NOT part of it - user
//    correction 2026-09-20 (the earlier "whole top band" reading of the
//    illustration was wrong). Implemented chain-based.
//  * SPEAKER (17): Chrome 150 does NOT expose the tab's speaker icon to
//    hit-testing (AOP over it returns the PAGETAB itself), so the tab's
//    a11y CHILDREN are scanned for the button whose rect contains the
//    cursor; the close button is always the rightmost of them (the tab's
//    own a11y rect is unreliable - it can be reported shifted/narrow).
//  * The browser-UI rules are gated on "not inside a DOCUMENT" - a web page
//    can expose the same ARIA roles (tablist = 60, <input> = 42,
//    role=toolbar = 22) and must never look like the omnibox/tab strip.
//  * Zones are reported ONLY for the browser that spawned this helper
//    (the hovered window's root process == the helper's parent process):
//    the original engine never fired over foreign applications.
//
// 2026-09-20 fixes (Opera end-to-end run, user reports):
//  * TAB (12) requires a real PAGETAB (37) - the empty strip area (60 alone)
//    and the "+" do not answer 12 (the engine's own FUN_00415570 did the
//    same).
//  * BOOKMARK (33): the omnibox GROUPING must sit BETWEEN the button and the
//    toolbar, plus Opera's heart matched BY NAME.
//  * MENU BUTTON (30): the right-edge rule is Chromium-only (Opera/Vivaldi
//    keep the menu on the LEFT, matched by name) and a button named
//    'Extensions' never answers 30.
//  * CLOSE BUTTON (15) in Opera/Vivaldi: not a PUSHBUTTON there but a square
//    PANE in the RIGHT part of the tab, hit-testable directly - see
//    IsPaneCloseButton.
//  * SPEAKER (17) is NOT implementable in Opera/Vivaldi: the only element in
//    the favicon slot is a role-40 'Tab favicon' present on EVERY tab, so an
//    audible tab cannot be told from a silent one (documented limitation).
//
// Build (no .NET SDK needed, .NET Framework csc):
//   csc /nologo /optimize+ /r:Accessibility.dll /out:ac_zone_helper.exe ac_zone_helper.cs
// (Accessibility.dll is in the GAC; csc lives in
//  C:\Windows\Microsoft.NET\Framework64\v4.0.30319\csc.exe)
using System;
using System.IO;
using System.Runtime.InteropServices;
using Accessibility;

public static class ZoneHelper {
  [DllImport("user32.dll")] private static extern bool SetProcessDPIAware();
  [DllImport("user32.dll")] private static extern bool GetCursorPos(out POINT p);
  [DllImport("user32.dll")] private static extern IntPtr WindowFromPoint(POINT pt);
  [DllImport("user32.dll")] private static extern IntPtr GetAncestor(IntPtr h, uint flags);
  [DllImport("user32.dll")] private static extern bool GetWindowRect(IntPtr h, out RECT r);
  [DllImport("user32.dll")] private static extern int GetWindowLong(IntPtr h, int index);
  [DllImport("user32.dll")] private static extern uint GetWindowThreadProcessId(IntPtr h, out uint pid);
  [DllImport("oleacc.dll")] private static extern int AccessibleObjectFromPoint(POINT pt, out IAccessible acc, out object child);
  [DllImport("kernel32.dll", SetLastError = true)] private static extern IntPtr CreateToolhelp32Snapshot(uint flags, uint pid);
  [DllImport("kernel32.dll", CharSet = CharSet.Unicode)] private static extern bool Process32First(IntPtr snap, ref PROCESSENTRY32 pe);
  [DllImport("kernel32.dll", CharSet = CharSet.Unicode)] private static extern bool Process32Next(IntPtr snap, ref PROCESSENTRY32 pe);
  [DllImport("kernel32.dll")] private static extern bool CloseHandle(IntPtr h);
  [DllImport("kernel32.dll", SetLastError = true)] private static extern IntPtr OpenProcess(uint access, bool inherit, uint pid);
  [DllImport("kernel32.dll", SetLastError = true)] private static extern IntPtr VirtualAllocEx(IntPtr h, IntPtr addr, IntPtr size, uint type, uint protect);
  [DllImport("kernel32.dll", SetLastError = true)] private static extern bool VirtualProtectEx(IntPtr h, IntPtr addr, IntPtr size, uint newProtect, out uint oldProtect);
  [DllImport("kernel32.dll", SetLastError = true)] private static extern bool WriteProcessMemory(IntPtr h, IntPtr addr, byte[] buf, IntPtr size, out IntPtr written);
  [DllImport("kernel32.dll", SetLastError = true)] private static extern bool ReadProcessMemory(IntPtr h, IntPtr addr, byte[] buf, IntPtr size, out IntPtr read);
  [DllImport("kernel32.dll", CharSet = CharSet.Unicode)] private static extern bool Module32First(IntPtr snap, ref MODULEENTRY32 me);
  [DllImport("kernel32.dll", CharSet = CharSet.Unicode)] private static extern bool Module32Next(IntPtr snap, ref MODULEENTRY32 me);
  [StructLayout(LayoutKind.Sequential)] private struct POINT { public int X, Y; }
  [StructLayout(LayoutKind.Sequential)] private struct RECT { public int L, T, R, B; }
  [StructLayout(LayoutKind.Sequential, CharSet = CharSet.Unicode)]
  private struct PROCESSENTRY32 {
    public uint dwSize; public uint cntUsage; public uint th32ProcessID; public IntPtr th32DefaultHeapID;
    public uint th32ModuleID; public uint cntThreads; public uint th32ParentProcessID; public int pcPriClassBase;
    public uint dwFlags;
    [MarshalAs(UnmanagedType.ByValTStr, SizeConst = 260)] public string szExeFile;
  }
  [StructLayout(LayoutKind.Sequential, CharSet = CharSet.Unicode)]
  private struct MODULEENTRY32 {
    public uint dwSize; public uint th32ModuleID; public uint th32ProcessID; public uint GlblcntUsage; public uint ProccntUsage;
    public IntPtr modBaseAddr; public uint modBaseSize; public IntPtr hModule;
    [MarshalAs(UnmanagedType.ByValTStr, SizeConst = 256)] public string szModule;
    [MarshalAs(UnmanagedType.ByValTStr, SizeConst = 260)] public string szExePath;
  }

  // Zone ids (decoded from file10.js; the settings UI lists the same numbers).
  private const int Z_WINDOW = 1;    // Browser window (any point inside it)
  private const int Z_PAGE = 3;      // Web page (DOCUMENT)
  private const int Z_TITLE = 4;     // Title area (window frame / caption band)
  private const int Z_TAB = 12;      // Browser tab (PAGETAB / PAGETABLIST gap)
  private const int Z_CLOSE = 15;    // Tab's close button
  private const int Z_NEWTAB = 16;   // New tab button ("+")
  private const int Z_SPEAKER = 17;  // Tab's speaker (audio) icon
  private const int Z_TOOLBAR = 20;  // Toolbar band (role 22 TOOLBAR in the ancestry)
  private const int Z_OMNIBOX = 21;  // Omnibox (role 42 EDIT / lock button)
  private const int Z_MENUBTN = 30;  // Browser menu button (kebab at the right edge)
  private const int Z_BOOKMARK = 33; // Bookmark button (star inside the omnibox group)

  // The browser process that spawned this helper (native hosts are children
  // of the browser process) - zones are reported only for ITS windows when
  // the parent really is a browser (the standalone smoke test / zone probes
  // spawn this exe from node, where the gate must not apply).
  private static uint browserPid = 0;
  // The browser's exe name (lowercased; empty for a standalone run). Needed by
  // the menu-button rules: Opera and Vivaldi put their menu on the LEFT, so
  // the right-edge geometry below must not run there.
  private static string browserName = "";

  private static bool IsBrowserName(string n) {
    if (string.IsNullOrEmpty(n)) return false;
    n = n.ToLowerInvariant();
    return n.StartsWith("chrome") || n.StartsWith("msedge") || n.StartsWith("brave")
        || n.StartsWith("opera") || n.StartsWith("vivaldi") || n.StartsWith("chromium")
        || n.StartsWith("yandex");
  }

  private static uint FindParent(uint pid, out string parentName) {
    parentName = "";
    IntPtr snap = CreateToolhelp32Snapshot(0x00000002 /* SNAPPROCESS */, 0);
    if (snap == IntPtr.Zero || snap == (IntPtr)(-1)) return 0;
    try {
      PROCESSENTRY32 pe = new PROCESSENTRY32();
      pe.dwSize = (uint)Marshal.SizeOf(typeof(PROCESSENTRY32));
      uint ppid = 0;
      if (!Process32First(snap, ref pe)) return 0;
      do {
        if (pe.th32ProcessID == pid) { ppid = pe.th32ParentProcessID; break; }
      } while (Process32Next(snap, ref pe));
      if (ppid == 0) return 0;
      pe = new PROCESSENTRY32();
      pe.dwSize = (uint)Marshal.SizeOf(typeof(PROCESSENTRY32));
      if (!Process32First(snap, ref pe)) return ppid;
      do {
        if (pe.th32ProcessID == ppid) { parentName = pe.szExeFile ?? ""; break; }
      } while (Process32Next(snap, ref pe));
      return ppid;
    } finally { CloseHandle(snap); }
  }

  private static int Role(IAccessible a) {
    try { return (int)a.get_accRole(0); } catch { return -1; }
  }
  private static string Name(IAccessible a) {
    try { object n = a.get_accName(0); return n == null ? "" : n.ToString(); } catch { return ""; }
  }
  private static bool Rect(IAccessible a, out RECT r) {
    r = new RECT();
    try {
      int x, y, w, h;
      a.accLocation(out x, out y, out w, out h, 0);
      r.L = x; r.T = y; r.R = x + w; r.B = y + h;
      return w > 0 && h > 0;
    } catch { return false; }
  }
  // The kebab IS exposed in the a11y tree as role 57 BUTTONMENU named "Chrome"
  // (the earlier "missing" report was made on an outdated Chrome 150 and could
  // not be re-checked then). It is identified by POSITION - a button in the
  // toolbar whose right edge hugs the window's right edge (this mirrors the
  // engine's own position-based zone-30 check in FUN_004156f0). The "New Chrome
  // available" update pill occupies that same rightmost slot in some builds
  // (user request 2026-09-12: "the update pill area is equivalent to the
  // three-dot button - make it work the same"), so it is accepted too: the
  // ONLY requirements are "in the toolbar" + "right edge near the window's
  // right edge". The profile avatar and the extension icons sit further left
  // (hundreds of px) and stay excluded.
  private static bool IsRightEdgeButton(IAccessible a, POINT pt) {
    RECT er;
    if (!Rect(a, out er)) return false;
    int w = er.R - er.L, h = er.B - er.T;
    if (w <= 0 || h <= 0) return false;
    if (h > 90) return false;                     // not a toolbar-row element (defensive)
    // The extensions-panel toggle is a RIGHTMOST button in several builds
    // (Opera 135: role 57 'Extensions' 36x37, its right edge 38 px from the
    // window edge) - it is never the browser menu (user report 2026-09-20:
    // the zone-30 action fired on the blue extensions-collapse button).
    string nm = Name(a);
    if (nm.IndexOf("extension", StringComparison.OrdinalIgnoreCase) >= 0 ||
        nm.IndexOf("\u0440\u0430\u0441\u0448\u0438\u0440\u0435\u043d", StringComparison.OrdinalIgnoreCase) >= 0)
      return false;
    IntPtr hwnd = WindowFromPoint(pt);
    if (hwnd == IntPtr.Zero) return false;
    IntPtr root = GetAncestor(hwnd, 2 /* GA_ROOT */);
    if (root == IntPtr.Zero) return false;
    RECT wr;
    if (!GetWindowRect(root, out wr)) return false;
    int gap = wr.R - er.R;
    return gap >= 0 && gap < 60;
  }

  // The right-edge rule mirrors Chrome's kebab / the "New Chrome available"
  // update pill. Opera and Vivaldi render their own UI with the menu on the
  // LEFT (matched BY NAME above), and there the RIGHTMOST toolbar button is
  // usually the extensions-panel toggle - so the geometry rule is skipped for
  // them entirely (user report 2026-09-20: the zone-30 action fired on the
  // blue extensions-collapse button). A standalone run (empty name) keeps the
  // Chrome behaviour so the zone probes stay representative.
  private static bool MenuAtRightEdge() {
    return !(browserName.StartsWith("opera") || browserName.StartsWith("vivaldi"));
  }

  // A browser UI POPUP covers the chrome (a menu, a dropdown, an extension
  // popup). Measured 2026-09-20: Opera's main menu is a layered WS_POPUP +
  // WS_EX_TOOLWINDOW window 419x1083 anchored at the content-area origin, so
  // it covers the whole tab strip; while it is open, every tab-strip point
  // resolved to an unnamed PANE and the frame rule below answered "title
  // area" (4) - a zone-4 trigger would fire while the user is inside the
  // browser menu, and a zone-15 trigger was silently skipped with a confusing
  // [4,1] in the log. The cursor is over the POPUP then, not over the browser
  // chrome, so only the browser-window zone (1) is reported.
  private static bool OverBrowserPopup(POINT pt) {
    IntPtr h = WindowFromPoint(pt);
    if (h == IntPtr.Zero) return false;
    IntPtr root = GetAncestor(h, 2 /* GA_ROOT */);
    if (root == IntPtr.Zero) return false;
    int style = GetWindowLong(root, -16 /* GWL_STYLE */);
    int ex = GetWindowLong(root, -20 /* GWL_EXSTYLE */);
    const int WS_POPUP = unchecked((int)0x80000000);
    const int WS_EX_TOOLWINDOW = 0x00000080;
    return (style & WS_POPUP) != 0 && (ex & WS_EX_TOOLWINDOW) != 0;
  }

  // The window rectangle under a point (physical pixels - the helper is
  // DPI-aware). Used by the title-row band check below.
  private static bool WindowRectAt(POINT pt, out RECT wr) {
    wr = new RECT();
    IntPtr hwnd = WindowFromPoint(pt);
    if (hwnd == IntPtr.Zero) return false;
    IntPtr root = GetAncestor(hwnd, 2 /* GA_ROOT */);
    if (root == IntPtr.Zero) return false;
    return GetWindowRect(root, out wr);
  }

  // A tab's buttons: the speaker (left) and the close button (right).
  // Chrome 150 does NOT expose the speaker icon to hit-testing (AOP over it
  // returns the PAGETAB), so the caller passes the tab element and the cursor
  // point: the tab's a11y children are scanned for the button whose rect
  // contains the point, and it is classified by SIBLING ORDER — the close
  // button is always the rightmost one. (The tab's own a11y rect cannot be
  // used: it can be reported shifted/narrow — e.g. 97px for a 385px tab — so
  // a "left/right half of the tab" test picks the wrong button; that made
  // the speaker icon report zone 15, user report 2026-09-12.) A tab that is
  // neither audible nor muted has its mute button present but with a 0x0
  // rect, so it is simply never hit. Returns 0, Z_CLOSE or Z_SPEAKER.
  // The scan goes TWO levels deep: Chrome exposes the buttons as DIRECT
  // children of the PAGETAB, while Opera 135 (Chromium 151) nests the close
  // button inside the tab's body PANE — PAGETAB(37) → body PANE(16, 253x42) →
  // 'Close tab'(43, 25x24), which the flat scan never found (measured
  // 2026-09-21: hovering it answered "Title area" because the 43-based rule
  // needs the PAGETAB and the PANE-based rule needs a SQUARE pane).
  private static int TabButtonZone(IAccessible tab, POINT pt) {
    int cc = 0;
    try { cc = tab.accChildCount; } catch { cc = 0; }
    if (cc <= 0) return 0;
    int hitLeft = int.MinValue, maxLeft = int.MinValue;
    for (int i = 1; i <= cc; i++) {
      IAccessible c = null;
      try { c = (IAccessible)tab.get_accChild(i); } catch { c = null; }
      if (c == null) continue;
      try { ScanTabButtons(c, pt, ref hitLeft, ref maxLeft, 2); }
      finally { try { Marshal.ReleaseComObject(c); } catch { } }
    }
    if (hitLeft == int.MinValue) return 0;         // the cursor is on the tab body
    return (hitLeft >= maxLeft) ? Z_CLOSE : Z_SPEAKER;
  }

  // Collects the tab's PUSHBUTTONS (role 43) at `depth` levels below `el`,
  // remembering the leftmost hit and the rightmost button overall (see
  // TabButtonZone for why the ordering, not geometry, decides).
  private static void ScanTabButtons(IAccessible el, POINT pt, ref int hitLeft, ref int maxLeft, int depth) {
    if (el == null || depth < 0) return;
    if (Role(el) == 43) {
      RECT r;
      if (Rect(el, out r)) {
        if (r.L > maxLeft) maxLeft = r.L;
        if (pt.X >= r.L && pt.X <= r.R && pt.Y >= r.T && pt.Y <= r.B) {
          if (r.L > hitLeft) hitLeft = r.L;
        }
      }
    }
    if (depth == 0) return;
    int cc = 0;
    try { cc = el.accChildCount; } catch { cc = 0; }
    for (int i = 1; i <= cc; i++) {
      IAccessible c = null;
      try { c = (IAccessible)el.get_accChild(i); } catch { c = null; }
      if (c == null) continue;
      try { ScanTabButtons(c, pt, ref hitLeft, ref maxLeft, depth - 1); }
      finally { try { Marshal.ReleaseComObject(c); } catch { } }
    }
  }

  // Opera/Vivaldi do NOT expose a tab's close button as a PUSHBUTTON - it is
  // a plain PANE (role 16) and it IS hit-testable DIRECTLY (the hovered
  // element is the button itself, whose parent is the PAGETAB). Signature
  // (Opera 135, all three tabs): the PAGETAB children are
  //   body PANE (253x42) · separator PANE (2x28) · close PANE (37x37, right)
  // The square shape + the RIGHT-half position separate it from the tab body
  // (too wide), the separator (too narrow) and Chrome's favicon PANE (square
  // but on the LEFT - and in Chrome/Brave the close button is a real 43
  // button, handled by TabButtonZone). Returns true when the element IS the
  // close button of the given tab.
  private static bool IsPaneCloseButton(IAccessible el, IAccessible tab, POINT pt) {
    RECT er, tr;
    if (!Rect(el, out er) || !Rect(tab, out tr)) return false;
    int w = er.R - er.L, h = er.B - er.T;
    if (w < 20 || w > 60 || h < 20 || h > 60) return false;   // square-ish icon slot
    if (Math.Abs(w - h) > 12) return false;
    if (pt.X < er.L || pt.X > er.R || pt.Y < er.T || pt.Y > er.B) return false;
    int tabW = tr.R - tr.L;
    if (tabW <= 0) return false;
    return (er.L + er.R) / 2 - tr.L > tabW * 6 / 10;          // the right 40% of the tab
  }

  // 0-based position of a PAGETAB among the tabs of its strip: the number of
  // PAGETAB siblings whose centre lies to the LEFT of this one (tabs are laid
  // out left to right, so that is the index). Returns -1 when the strip cannot
  // be found.
  //
  // WHY THIS EXISTS: native type 485 ("which tab is under the mouse") answers
  // only {hWnd,x,y} on Chrome 148+ - it no longer identifies the tab (the a11y
  // hit-test that produced index/title is gone), so the bundle's _ys()
  // resolved NOTHING and every "hoveredTabs" action silently fell back to the
  // ACTIVE tab (benchmark 2026-09-20: 10 wheel notches over 4 different tabs
  // reloaded the active one 10 times). The SW answers 485 from here instead.
  //
  // WHERE THE SIBLINGS ARE (2026-10-04): the strip is the nearest ancestor that
  // has at least TWO PAGETAB children - i.e. the level where the tabs really
  // are siblings. Chrome 148 WRAPS them: PAGETAB(37) -> PANE(16, all 48 tabs)
  // -> PANE(16) -> PAGETABLIST(60), while Chrome 156 and Opera hang the tabs
  // directly off the 60. The old rule ("walk up to the first role-60 ancestor,
  // then count ITS direct children") therefore answered **index 0 for every
  // tab** on Chrome 148 - measured over the strip: 8 points, every title
  // correct, every index 0 - because that 60 holds container children, not
  // tabs. The SW then took list[0], the FIRST tab of the window, so every
  // hovered-tab action ignored the hover (user report 2026-10-04).
  private static int TabIndexOf(IAccessible tab) {
    RECT tr;
    if (!Rect(tab, out tr)) return -1;
    int cx = (tr.L + tr.R) / 2;
    // ONE pass per ancestor level: find the level where the tabs really ARE
    // siblings (>= 2 PAGETAB children) and count the tabs left of this one at
    // the same time. The children walk is the expensive part (one COM round
    // trip per child - 21 tabs in a full strip), so it must not be done twice:
    // the two-pass version (count, then re-walk to count the left ones) was one
    // of the reasons a tab answer took ~300 ms and the SW gave up (2026-10-04).
    IAccessible cur = tab;
    for (int d = 0; d < 6 && cur != null; d++) {
      IAccessible p = null; try { p = (IAccessible)cur.accParent; } catch { p = null; }
      if (p == null) break;
      int cc = 0; try { cc = p.accChildCount; } catch { cc = 0; }
      int n37 = 0, left = 0;
      for (int i = 1; i <= cc; i++) {
        IAccessible c = null; try { c = (IAccessible)p.get_accChild(i); } catch { c = null; }
        if (c == null) continue;
        try {
          if (Role(c) == 37) {
            n37++;
            RECT r;
            if (Rect(c, out r) && (r.L + r.R) / 2 < cx) left++;
          }
        } finally { try { Marshal.ReleaseComObject(c); } catch { } }
      }
      if (n37 >= 2) return left;
      cur = p;
    }
    // Fallback: a single-tab window (index 0 there) or a layout whose tabs hang
    // directly under the PAGETABLIST - walk up to the role-60 ancestor.
    cur = tab;
    for (int d = 0; d < 6 && cur != null; d++) {
      IAccessible p = null; try { p = (IAccessible)cur.accParent; } catch { p = null; }
      if (p == null) break;
      if (Role(p) == 60) {
        int cc = 0; try { cc = p.accChildCount; } catch { cc = 0; }
        int idx = 0;
        for (int i = 1; i <= cc; i++) {
          IAccessible c = null; try { c = (IAccessible)p.get_accChild(i); } catch { c = null; }
          if (c == null) continue;
          try {
            if (Role(c) == 37) { RECT r; if (Rect(c, out r) && (r.L + r.R) / 2 < cx) idx++; }
          } finally { try { Marshal.ReleaseComObject(c); } catch { } }
        }
        return idx;
      }
      cur = p;
    }
    return -1;
  }

  // "which tab is under the cursor" for native type 485 (see TabIndexOf).
  // Returns "" when the point is not over a tab, else a JSON fragment
  //   ,"hWnd":N,"index":I,"title":"..."
  // The caller must have woken the a11y tree already (the heartbeat does).
  // Diagnostic: why the last TabUnderCursorJson() call returned nothing (logged
  // by the request path). "hit-role/name" is the element that WAS under the
  // cursor - that tells "the cursor was not over a tab" (the empty strip area,
  // the "+", the page) from "the accessibility tree did not answer".
  private static string lastTabReason = "";

  private static string TabUnderCursorJson(POINT pt) {
    lastTabReason = "";
    IAccessible acc = null; object child = null;
    if (AccessibleObjectFromPoint(pt, out acc, out child) != 0 || acc == null) { lastTabReason = "aop-failed"; return ""; }
    try { object nm = acc.get_accName(0); } catch { }        // wake a sleeping tree
    try { Marshal.ReleaseComObject(acc); } catch { }
    acc = null;
    if (AccessibleObjectFromPoint(pt, out acc, out child) != 0 || acc == null) { lastTabReason = "aop-failed-2"; return ""; }
    IAccessible tab = null, cur = acc;
    for (int d = 0; d <= 3 && cur != null; d++) {
      if (Role(cur) == 37) { tab = cur; break; }
      IAccessible p = null; try { p = (IAccessible)cur.accParent; } catch { p = null; }
      cur = p;
    }
    if (tab == null) {
      // What WAS under the cursor matters: over the empty strip area or the "+"
      // the answer is legitimately empty (the documented "any other part of the
      // browser window gives the ACTIVE tab"), while a role-37 chain that is
      // simply not there means the tree did not answer.
      lastTabReason = "no-PAGETAB hit-role=" + Role(acc) + " hit-name='" + Name(acc) + "'";
      try { Marshal.ReleaseComObject(acc); } catch { }
      return "";
    }
    int idx = TabIndexOf(tab);
    string title = Name(tab);
    IntPtr hwnd = WindowFromPoint(pt);
    IntPtr root = hwnd != IntPtr.Zero ? GetAncestor(hwnd, 2 /* GA_ROOT */) : IntPtr.Zero;
    try { Marshal.ReleaseComObject(acc); } catch { }
    if (root == IntPtr.Zero || idx < 0) {
      lastTabReason = (root == IntPtr.Zero ? "no-root" : "no-strip(idx=" + idx + ")") +
        " tab-name='" + title + "'";
      return "";
    }
    title = title.Replace("\\", "\\\\").Replace("\"", "\\\"");
    return ",\"hWnd\":" + root.ToInt64() + ",\"index\":" + idx + ",\"title\":\"" + title + "\"";
  }

  // Classify the point into the SET of matching zones (the original engine
  // evaluated every trigger's region independently, so several zones can be
  // true at once - e.g. the omnibox is inside the toolbar band inside the
  // title band, the page is inside the browser window). Rules are ordered
  // from the most specific (tab buttons, "+") to the band fallbacks;
  // signatures were collected live with Test/zone_scan.ps1..zone_scan5.ps1 /
  // zone_chain.ps1 on Chrome 150 SxS (Docs/TODO-mouseover-zones.md §2/§2f).
  //
  // The chain walk is DEEP (16 levels) and the DOCUMENT search is exhaustive:
  // a real web page (YouTube etc.) nests its elements much deeper than the
  // browser chrome, so a 6-level walk found no DOCUMENT -> the point was not
  // recognized as "Web page" AND the page's own ARIA roles could be misread as
  // browser chrome (a page <input> is role 42 = "omnibox", role=toolbar = 22,
  // role=tablist = 60). Rule: a chrome role counts only ABOVE the DOCUMENT
  // (when a DOCUMENT is in the chain, the cursor is inside the page).
  private const int MAXDEPTH = 16;
  private static void Classify(IAccessible acc, POINT pt, ref int[] outZones, ref int count) {
    int[] roles = new int[MAXDEPTH];
    IAccessible[] chain = new IAccessible[MAXDEPTH];
    IAccessible cur = acc;
    for (int d = 0; d < MAXDEPTH; d++) {
      if (cur == null) { roles[d] = -1; chain[d] = null; continue; }
      chain[d] = cur;
      roles[d] = Role(cur);
      IAccessible p = null;
      try { p = (IAccessible)cur.accParent; } catch { p = null; }
      cur = p;
    }
    int docDepth = -1;
    for (int d = 0; d < MAXDEPTH; d++) if (roles[d] == 15) { docDepth = d; break; }
    bool inPage = docDepth >= 0;
    // Over a browser UI POPUP (menu / dropdown / extension popup) the cursor
    // is over the POPUP, not over the browser chrome - report only the
    // browser-window zone (see OverBrowserPopup; the Opera main menu covering
    // the tab strip used to answer "title area").
    if (OverBrowserPopup(pt)) {
      outZones[0] = Z_WINDOW;
      count = 1;
      return;
    }
    // Vivaldi (2026-09-15): its whole UI lives INSIDE the page document - the
    // omnibox's chain is 42 -> 20 -> 22 (Address) -> ... -> 15 (the page
    // DOCUMENT), so the naive "a DOCUMENT in the chain = the page" rule made
    // every point of the browser look like the page (zones always [3,1]).
    // Chrome never has chrome roles BELOW the document; a page can only have
    // ARIA roles (input=42, toolbar=22) below it. Distinguish: a TOOLBAR (22)
    // or PAGETAB/PAGETABLIST (37/60) below the document is Vivaldi's UI.
    if (inPage) {
      for (int d = 0; d < docDepth && d < 8; d++) {
        if (roles[d] == 22 || roles[d] == 37 || roles[d] == 60) { inPage = false; break; }
      }
    }
    // Chrome-role detection: the chain is walked from the hovered element
    // UPWARDS (d0 = the element, higher d = closer to the window), so the
    // page's own ARIA roles sit BELOW the DOCUMENT (d < docDepth) and the
    // browser chrome sits ABOVE it (d > docDepth). A page can expose the very
    // same roles as the UI - <input> = 42 EDIT, role=toolbar = 22,
    // role=tablist = 60, pagetab = 37 - so only depths ABOVE the DOCUMENT (or
    // every depth when no DOCUMENT is in the chain, i.e. real chrome) may
    // drive the browser-UI rules.
    int toolbarDepth = -1, groupDepth = -1;
    for (int d = 0; d < MAXDEPTH; d++) {
      if (inPage && d <= docDepth) continue;        // inside the page
      if (roles[d] == 22 && toolbarDepth < 0) toolbarDepth = d;   // TOOLBAR
      if (d > 0 && roles[d] == 20 && groupDepth < 0) groupDepth = d;  // GROUPING
    }
    bool inToolbar = toolbarDepth >= 0;
    // The omnibox GROUPING must sit BETWEEN the element and the toolbar
    // (Chrome: 43 -> 16 -> 20 GROUPING -> 22 TOOLBAR). Opera's toolbar
    // buttons have the window-contents container (20 'Browser contents')
    // ABOVE the toolbar (22 'Navigation') - the old "any 20 above" test made
    // EVERY toolbar button look like a button inside the omnibox group, so
    // Snapshot/Translate/Reader/Profile all answered the bookmark zone
    // (user report 2026-09-20). Opera's OWN bookmark button (the heart) sits
    // outside any such group and is matched BY NAME below - it is
    // structurally identical to its neighbours.
    bool inGroup = groupDepth >= 0 && (toolbarDepth < 0 || groupDepth < toolbarDepth);
    // Inside a DOCUMENT = inside the page: no browser-chrome rule may fire.
    bool ui = !inPage;

    // The TAB itself: a PAGETAB (role 37) anywhere in d0..d3 (Chrome: 37 at
    // d1; Opera/Vivaldi: deeper - 41 -> 16 -> 37). The engine's OWN region-12
    // check (FUN_00415570) matched ONLY a PAGETAB or an element whose DIRECT
    // parent is a PAGETAB - the EMPTY strip area (the PAGETABLIST itself,
    // role 60) and the "+" button never matched region 12 (user report
    // 2026-09-20: the empty strip right of the "+" answered "Browser tab").
    int tabDepth = -1;
    for (int d = 0; d <= 3; d++) {
      if (ui && roles[d] == 37) { tabDepth = d; break; }
    }
    // The hovered element IS a tab button (a PUSHBUTTON inside a tab): in
    // Chrome it is a DIRECT child of the PAGETAB (43 -> 37), in Opera 135
    // (Chromium 151) it is nested one level deeper - PAGETAB -> body PANE ->
    // 'Close tab' (43 -> 16 -> 37), so ANY PAGETAB ancestor counts. It must
    // not catch the "+" (a 43 under the PAGETABLIST 60, no PAGETAB above).
    bool isTabBtn = ui && roles[0] == 43 && tabDepth >= 1;
    bool isNewTabBtn = ui && roles[0] == 43 && roles[1] == 60;
    // The strip ROW for the TITLE-AREA zone (4) covers the whole band,
    // including its empty area (the PAGETABLIST 60 itself).
    bool stripNear = tabDepth >= 0;
    if (!stripNear) {
      for (int d = 0; d <= 3; d++) {
        if (ui && roles[d] == 60) { stripNear = true; break; }
      }
    }
    // The browser-menu button has a NAME in Opera/Vivaldi (the localized
    // "Menu"; the Russian UI name is matched via the unicode escape below)
    // and sits on the LEFT - the kebab rule (right edge) is Chrome only.
    // A site-info lock (57) in Chrome is named by the page title.
    bool menuByName = ui && (roles[0] == 43 || roles[0] == 57) &&
      (Name(chain[0]).IndexOf("menu", StringComparison.OrdinalIgnoreCase) >= 0 ||
       Name(chain[0]).IndexOf("\u043c\u0435\u043d\u044e", StringComparison.OrdinalIgnoreCase) >= 0);
    // Opera's bookmark button ('Add to bookmarks' / 'Edit bookmark'; the
    // Russian UI name is matched via the unicode escape below) is
    // STRUCTURALLY IDENTICAL to the other toolbar buttons (43 under the
    // toolbar 22, no omnibox group below, no keyboard shortcut exposed), so
    // it is matched BY NAME - the same approach as the menu button above.
    // Chrome's star ('Bookmark this tab') also matches the name, but it is
    // already covered by the group rule below (the else-if avoids a double).
    bool bookmarkByName = ui && (roles[0] == 43 || roles[0] == 57) &&
      (Name(chain[0]).IndexOf("bookmark", StringComparison.OrdinalIgnoreCase) >= 0 ||
       Name(chain[0]).IndexOf("\u0437\u0430\u043a\u043b\u0430\u0434\u043a", StringComparison.OrdinalIgnoreCase) >= 0);

    int[] zs = new int[16];
    int n = 0;
    // 1. Browser window: the cursor is inside a Chrome window by definition.
    zs[n++] = Z_WINDOW;
    // 2. Web page: a DOCUMENT in the ancestry.
    if (inPage) zs[n++] = Z_PAGE;

    if (ui) {
      // 3. Tab's close button / speaker icon. The hovered element may be the
      //    button itself (Close IS hit-testable) or the tab (the speaker icon
      //    is NOT) - both go through the tab's children (see TabButtonZone).
      int tbZone = 0;
      if (isTabBtn) tbZone = TabButtonZone(chain[tabDepth], pt);
      else if (roles[0] == 37) tbZone = TabButtonZone(chain[0], pt);
      else if (roles[1] == 37) tbZone = TabButtonZone(chain[1], pt);
      else if (tabDepth >= 2 && roles[tabDepth] == 37) tbZone = TabButtonZone(chain[tabDepth], pt);
      // 3b. Opera/Vivaldi tab close button: a square PANE (16) whose parent
      //     is the PAGETAB and which sits in the RIGHT part of the tab - see
      //     IsPaneCloseButton. Without this the zone-15 trigger never fires
      //     in those forks (the 43-based TabButtonZone finds nothing there).
      if (tbZone == 0 && roles[0] == 16 && roles[1] == 37 &&
          IsPaneCloseButton(chain[0], chain[1], pt)) tbZone = Z_CLOSE;
      if (tbZone != 0) zs[n++] = tbZone;
      // 4. New tab button: a PUSHBUTTON whose parent is the PAGETABLIST.
      if (isNewTabBtn) zs[n++] = Z_NEWTAB;
      // 5. Omnibox: the address text field (42 EDIT at d0/d1) or the
      //    site-info (lock) button - a BUTTONMENU (57) inside the group.
      //    NOT the browser-menu button of Opera/Vivaldi (also 57, but NAMED
      //    as the menu button - handled below).
      if (roles[0] == 42 || roles[1] == 42) zs[n++] = Z_OMNIBOX;
      else if (roles[0] == 57 && roles[1] == 20 && !menuByName) zs[n++] = Z_OMNIBOX;
      // 6. Bookmark (star) button: a PUSHBUTTON inside the omnibox group,
      //    which itself sits inside the toolbar band.
      if (roles[0] == 43 && inGroup && inToolbar) zs[n++] = Z_BOOKMARK;
      // 6c. Opera's bookmark button BY NAME (see bookmarkByName above): its
      //     chain has NO omnibox group (Opera's window-contents container 20
      //     sits ABOVE the toolbar), so the group rule misses it - without
      //     this the bookmark zone would not work in Opera at all.
      else if (bookmarkByName && inToolbar) zs[n++] = Z_BOOKMARK;
      // 6b. Browser menu button BY NAME - Opera (role 57) and Vivaldi
      //     ("Menu", role 43) put it on the LEFT, NOT inside the
      //     toolbar (the kebab rule below is Chrome-only geometry). The name
      //     also stops it from being read as the omnibox site-info lock.
      if (menuByName) zs[n++] = Z_MENUBTN;
      // 7. Toolbar band (role 22 in the ancestry) + the browser menu button
      //    (the kebab / update pill at the right edge in Chrome; Opera's
      //    and Vivaldi's menu buttons on the LEFT, found by name).
      if (inToolbar) {
        zs[n++] = Z_TOOLBAR;
        if (MenuAtRightEdge() && (roles[0] == 43 || roles[0] == 57) &&
            IsRightEdgeButton(chain[0], pt))
          zs[n++] = Z_MENUBTN;
      }
      // 8. Browser tab: a PAGETAB (37) anywhere in d0..d3 (Chrome: d0/d1;
      //    Opera/Vivaldi: deeper - see tabDepth above). EXCLUSIONS: the "+"
      //    button (no PAGETAB in its chain), the tab's own BUTTONS (Close /
      //    Speaker - tbZone handles those; a 43-button under a PAGETAB is
      //    not "the tab"), and the EMPTY strip area (60 without a 37) - the
      //    engine's own region-12 check never matched it (see tabDepth).
      if (tbZone == 0 && tabDepth >= 0 && roles[0] != 43) zs[n++] = Z_TAB;
      // 9. TITLE AREA = the title bar / tab strip row ONLY (the UI
      //    description: "When the mouse is over the title bar or tab
      //    strip"; user correction 2026-09-20). Chain-based: anything
      //    belonging to the tab strip (TAB / PAGETABLIST / a tab button).
      //    The toolbar and the omnibox are NOT part of it.
      if (stripNear || isTabBtn) zs[n++] = Z_TITLE;
      // 9b. Opera-style title row ('Top bar container', role 20): the band
      //     that holds the tab bar, the tab-search button AND the window
      //     controls. Unlike Chrome's GROUPING (always inside the TOOLBAR
      //     22), this band has NO 22 in its chain - and the window controls
      //     have no 37/60 either, so without this rule they get no zone at
      //     all (user report 2026-09-20: the minimize/maximize/close buttons
      //     and the tab-search button are part of the title area).
      //     Guard: the container must be a BAND (much shorter than the
      //     window) and the point must be inside it, so the content-area
      //     containers of other UIs cannot claim the title row.
      else if (!inToolbar) {
        for (int d = 1; d < MAXDEPTH; d++) {
          if (inPage && d <= docDepth) break;
          if (roles[d] != 20) continue;
          RECT rr, wr;
          if (Rect(chain[d], out rr) && WindowRectAt(pt, out wr) &&
              (rr.B - rr.T) * 2 < (wr.B - wr.T) && pt.Y >= rr.T && pt.Y <= rr.B) {
            zs[n++] = Z_TITLE;
          }
          break;
        }
      }
      // 10. The rest of the window frame (the border band, the caption area
      //     outside the strip) - an unnamed PANE that is not part of the page
      //     and not inside the toolbar.
      if (!inToolbar && roles[0] == 16) zs[n++] = Z_TITLE;
    }

    outZones = zs;
    count = n;
  }

  // Is the cursor over a window of the browser that spawned this helper?
  // Zones are reported ONLY then: the original engine never fired a trigger
  // when the cursor was over another application, and a false zone 1/4
  // elsewhere would run actions there.
  private static bool OverOwnBrowser(POINT pt) {
    if (browserPid == 0) return true;                 // standalone (smoke test / probes)
    IntPtr hwnd0 = WindowFromPoint(pt);
    IntPtr root0 = hwnd0 != IntPtr.Zero ? GetAncestor(hwnd0, 2 /* GA_ROOT */) : IntPtr.Zero;
    uint wpid = 0;
    if (root0 != IntPtr.Zero) GetWindowThreadProcessId(root0, out wpid);
    return wpid == browserPid;
  }

  // Classify the point; returns the zones ordered by specificity, or null when
  // the accessibility query failed (the SW treats that as "no match").
  private static int[] ZonesForPoint(POINT pt) {
    IAccessible acc = null; object child = null;
    int hr = AccessibleObjectFromPoint(pt, out acc, out child);
    if (hr != 0 || acc == null) return null;
    // Chrome 148+ anti-abuse (crbug 416429182): the MSAA tree stays OFF
    // until a client queries accName (is_name_used_) - a single AOP on a
    // sleeping tree returns a generic PANE (16) -> zone 0 for everything
    // ("all zone actions died after a Chrome restart", 2026-09-04).
    // Wake the tree: query accName, then re-query AOP and classify the
    // REAL object. The wake is global for the whole browser (per Chrome),
    // so this also helps every later request.
    try {
      object name = acc.get_accName(0);
      Marshal.ReleaseComObject(acc);
      acc = null;
    } catch { /* older object without name - ignore */ }
    if (acc != null) { try { Marshal.ReleaseComObject(acc); } catch {} }
    hr = AccessibleObjectFromPoint(pt, out acc, out child);
    if (hr != 0 || acc == null) return null;
    int[] zs = new int[16];
    int n = 0;
    try { Classify(acc, pt, ref zs, ref n); }
    catch { n = 0; }
    finally { try { Marshal.ReleaseComObject(acc); } catch {} }
    // Order by specificity (priority list) and drop duplicates.
    int[] prio = new int[] { 16, 15, 17, 33, 30, 21, 12, 20, 3, 4, 1 };
    int[] ordered = new int[16];
    int m = 0;
    for (int i = 0; i < prio.Length; i++) {
      for (int k = 0; k < n; k++) { if (zs[k] == prio[i]) { ordered[m++] = prio[i]; break; } }
    }
    int[] res = new int[m];
    Array.Copy(ordered, res, m);
    return res;
  }

  // JSON for a zone set: null = AOP error, empty = not over this browser.
  private static string JsonOfZones(int[] z) {
    if (z == null) return "{\"zone\":-1,\"zones\":[-1]}";
    if (z.Length == 0) return "{\"zone\":0,\"zones\":[]}";
    string s = "";
    for (int i = 0; i < z.Length; i++) { if (i > 0) s += ","; s += z[i]; }
    return "{\"zone\":" + z[0] + ",\"zones\":[" + s + "]}";
  }

  // Classify ONE point and cache the COMPLETE answer for it: the zone set, the
  // engine's zone table and the tab under the cursor. Everything is sampled at
  // the SAME moment - that is the whole point of this method (see CacheStore).
  // The zone body is {"zone":P,"zones":[...]} - P is the most specific zone
  // (logging / older SW builds), zones is the full matching set.
  // {"zone":-1,...} = cursor/AOP error (the SW treats it as "no match").
  // {"zone":0,"zones":[]} = the cursor is not over this browser's window.
  // ⚠ NO tab walk here: `TabUnderCursorJson` costs 60-104 ms (measured) and this
  // runs on the 30 ms heartbeat - adding it made the helper unable to answer the
  // SW's zone query in time (250 ms), so the first wheel notch after a fast move
  // was SKIPPED (`zones=[-2]`, user report 2026-09-21). The tab is walked on
  // demand by the request path, which stores it for the very point it was
  // computed for (cacheTabOk).
  private static int[] ClassifyAndCache(POINT pt) {
    int[] z = OverOwnBrowser(pt) ? ZonesForPoint(pt) : new int[0];
    WriteZoneTable(z == null ? new int[0] : z);
    CacheStore(pt, JsonOfZones(z));
    return z;
  }

  // ---- engine zone table (patch v19, see Test/patch_zones_v19.js) --------
  // The engine's mouseOver region check reads a TABLE from its own memory:
  // table[region] != 0 -> the trigger matches (and the input is consumed),
  // 0 -> it does not match (the input passes through -> pages keep scrolling).
  // The table is maintained here: [dword alive][12 pad][64 dwords], one page
  // allocated inside the engine with VirtualAllocEx. The cave in the engine's
  // .text is pre-filled with an "always match" fallback and this class
  // overwrites its prefix with the table version (absolute addresses computed
  // from the live module base, so Windows ASLR is handled).
  private const long CAVE_RVA = 0x7F7A3;   // zero padding in .text (v19 cave)
  // std::vector<HWND> of the windows the engine tracks = the windows of ITS
  // OWN browser (VA 0x004a2514..0x004a2518; the region matcher's only caller
  // walks exactly this list - see Test/native-disasm/decomp/00415b40_FUN_00415b40.c).
  private const long WINS_RVA = 0xA2514;   // 0x004a2514 - image base 0x400000
  private const int ORIG_BLOCK = 0x1C;     // offset of the untouched original bytes
  private const int TABLE_SLOTS = 64;      // regions 0..63 (>= 40 = menu, engine's own)
  private static uint engPid = 0;
  private static long engTable = 0;
  private static long engCave = 0;

  // Which engine belongs to MY browser? 2026-09-13, user report "wheel over the
  // page switches tabs": with SEVERAL browsers running there are SEVERAL engines
  // and the old rule `pids[0]` made EVERY helper write into the same one - the
  // other browser's engine kept the file fallback ("always match"), so its
  // mouseOver conditions matched EVERYWHERE. The process tree cannot tell them
  // apart (AutoControlZero is a launcher: it hands the pipes to the engine and
  // exits, so the engine's parent is always dead), but the engine itself knows:
  // it tracks the windows of its own browser. Bind by that list.
  // Returns true only when a window of MY browser is in the engine's list;
  // `known` = false means "could not tell" (empty list, fresh engine, or no
  // browser ancestor at all - e.g. the standalone probes).
  private static bool EngineIsMine(uint pid, out bool known) {
    known = false;
    if (browserPid == 0) return false;
    IntPtr h = OpenProcess(0x410 /* QUERY_INFORMATION | VM_READ */, false, pid);
    if (h == IntPtr.Zero) return false;
    try {
      long baseAddr = ModuleBaseOf(pid);
      if (baseAddr == 0) return false;
      byte[] hdr = new byte[8];
      IntPtr got;
      if (!ReadProcessMemory(h, (IntPtr)(baseAddr + WINS_RVA), hdr, (IntPtr)8, out got)) return false;
      long p0 = BitConverter.ToUInt32(hdr, 0), p1 = BitConverter.ToUInt32(hdr, 4);
      if (p1 <= p0) return false;                      // empty -> unknown
      int n = (int)((p1 - p0) / 4);
      if (n <= 0 || n > 512) return false;
      byte[] arr = new byte[n * 4];
      if (!ReadProcessMemory(h, (IntPtr)p0, arr, (IntPtr)(n * 4), out got)) return false;
      known = true;
      for (int i = 0; i < n; i++) {
        uint hw = BitConverter.ToUInt32(arr, i * 4);
        if (hw == 0) continue;
        uint wp;
        GetWindowThreadProcessId((IntPtr)hw, out wp);
        if (wp == browserPid) return true;
      }
      return false;
    } catch { return false; }
    finally { CloseHandle(h); }
  }

  private static int[] FindEnginePids() {
    IntPtr snap = CreateToolhelp32Snapshot(0x00000002 /* SNAPPROCESS */, 0);
    if (snap == IntPtr.Zero || snap == (IntPtr)(-1)) return new int[0];
    var list = new System.Collections.Generic.List<int>();
    try {
      PROCESSENTRY32 pe = new PROCESSENTRY32();
      pe.dwSize = (uint)Marshal.SizeOf(typeof(PROCESSENTRY32));
      if (Process32First(snap, ref pe)) {
        do {
          string n = pe.szExeFile ?? "";
          if (n.StartsWith("AutoCtrl_", StringComparison.OrdinalIgnoreCase) && n.EndsWith(".exe", StringComparison.OrdinalIgnoreCase))
            list.Add((int)pe.th32ProcessID);
        } while (Process32Next(snap, ref pe));
      }
    } finally { CloseHandle(snap); }
    return list.ToArray();
  }
  private static long ModuleBaseOf(uint pid) {
    IntPtr snap = CreateToolhelp32Snapshot(0x00000008 | 0x00000010 /* MODULE|32BIT */, pid);
    if (snap == IntPtr.Zero || snap == (IntPtr)(-1)) return 0;
    long baseAddr = 0;
    try {
      MODULEENTRY32 me = new MODULEENTRY32();
      me.dwSize = (uint)Marshal.SizeOf(typeof(MODULEENTRY32));
      if (Module32First(snap, ref me)) {
        do {
          string n = me.szModule ?? "";
          if (n.StartsWith("AutoCtrl_", StringComparison.OrdinalIgnoreCase)) { baseAddr = me.modBaseAddr.ToInt64(); break; }
        } while (Module32Next(snap, ref me));
      }
    } finally { CloseHandle(snap); }
    return baseAddr;
  }
  private static bool WriteMem(IntPtr h, long addr, byte[] buf) {
    IntPtr w;
    return WriteProcessMemory(h, (IntPtr)addr, buf, (IntPtr)buf.Length, out w);
  }
  // Diagnostic log (kept small: only the table-writer path writes here).
  private static void Log(string s) {
    try {
      string p = Path.Combine(Path.GetTempPath(), "ac_zone_helper.log");
      if (File.Exists(p) && new FileInfo(p).Length > 200000) File.Delete(p);
      File.AppendAllText(p, DateTime.Now.ToString("HH:mm:ss.fff") + " " + s + "\r\n");
    } catch { }
  }
  private static byte[] ReadMem(IntPtr h, long addr, int n) {
    byte[] b = new byte[n]; IntPtr r;
    if (!ReadProcessMemory(h, (IntPtr)addr, b, (IntPtr)n, out r)) return null;
    return b;
  }

  // zones: the regions that currently match; empty = "the cursor is not over
  // this browser" (nothing matches -> all input passes through, like MV2 over
  // a foreign window). Silent on any failure (an unpatched engine is skipped).
  private static void WriteZoneTable(int[] zones) {
   try {
    int[] pids = FindEnginePids();
    if (pids.Length == 0) { Log("no engine process"); engPid = 0; engTable = 0; engCave = 0; return; }
    // Pick MY engine (2026-09-13). Rule order:
    //  1. an engine already bound to me stays bound (only MY engine can pass
    //     the window test, so the binding is trustworthy - but re-check it when
    //     its window list is readable);
    //  2. otherwise take the engine that tracks MY browser's windows;
    //  3. a single engine is unambiguous even while its list is still empty;
    //  4. never write into an engine that provably belongs to another browser -
    //     wait for the next request instead (the SW pings every 2.5 s).
    uint pid = 0;
    if (engPid != 0 && engCave != 0) {
      for (int i = 0; i < pids.Length; i++) {
        if ((uint)pids[i] != engPid) continue;
        bool known;
        if (EngineIsMine(engPid, out known) || !known) pid = engPid;
        else Log("DROP binding to pid " + engPid + ": its windows belong to a different browser");
      }
    }
    if (pid == 0) {
      for (int i = 0; i < pids.Length; i++) {
        bool known;
        if (EngineIsMine((uint)pids[i], out known)) { pid = (uint)pids[i]; break; }
      }
    }
    if (pid == 0 && pids.Length == 1) pid = (uint)pids[0];
    if (pid == 0) {
      Log("waiting: none of the " + pids.Length + " engines belongs to browser " + browserPid +
          " (or the list is not ready yet) - not writing a foreign engine");
      return;
    }
    // (re)initialise when the engine restarted
    if (pid != engPid || engCave == 0) {
      Log("init for pid " + pid + " of my browser " + browserPid + " (engines: " + pids.Length + ")");
      engPid = pid; engTable = 0; engCave = 0;
      IntPtr h0 = OpenProcess(0x438 /* QUERY|VM_OP|VM_READ|VM_WRITE */, false, pid);
      if (h0 == IntPtr.Zero) { Log("OpenProcess failed: " + Marshal.GetLastWin32Error()); return; }
      try {
        long baseAddr = ModuleBaseOf(pid);
        if (baseAddr == 0) { Log("ModuleBaseOf failed"); return; }
        long cave = baseAddr + CAVE_RVA;
        Log("base=0x" + baseAddr.ToString("X") + " cave=0x" + cave.ToString("X"));
        byte[] sig = ReadMem(h0, cave, 5);
        if (sig == null) { Log("ReadMem(cave) failed: " + Marshal.GetLastWin32Error()); return; }
        if (sig[0] != 0x83 || sig[1] != 0xFA || sig[2] != 0x28 || sig[3] != 0x73 || sig[4] != (byte)(ORIG_BLOCK - 5)) {
          Log("cave signature mismatch: " + BitConverter.ToString(sig));
          return; // not a v19 engine
        }
        long tab = 0;
        // NOTE (2026-09-12): the previous version reused whatever table address
        // was already in the cave. That broke as soon as ANYTHING else had
        // written the cave (the manual test tool allocates its own page): the
        // cave pointed at that foreign page while this helper kept updating its
        // own one, so the engine read a stale/empty table and nothing matched.
        // Always claim the cave for OUR page.
        {
          IntPtr page = VirtualAllocEx(h0, IntPtr.Zero, (IntPtr)4096, 0x3000 /* COMMIT|RESERVE */, 0x04 /* PAGE_READWRITE */);
          if (page == IntPtr.Zero) return;
          tab = page.ToInt64();
          // table version of the cave prefix
          byte[] npre = new byte[ORIG_BLOCK];
          npre[0] = 0x83; npre[1] = 0xFA; npre[2] = 0x28;                 // cmp edx, 28h
          npre[3] = 0x73; npre[4] = (byte)(ORIG_BLOCK - 5);               // jae ORIG
          npre[5] = 0x80; npre[6] = 0x3D;                                 // cmp byte [alive], 0
          BitConverter.GetBytes((int)tab).CopyTo(npre, 7);
          npre[11] = 0x00;
          npre[12] = 0x74; npre[13] = 0x08;                               // je notalive (0x16)
          npre[14] = 0x8B; npre[15] = 0x04; npre[16] = 0x95;              // mov eax, [edx*4+tab]
          BitConverter.GetBytes((int)(tab + 16)).CopyTo(npre, 17);
          npre[21] = 0xC3;                                                // ret      (0x15)
          npre[22] = 0xB8; npre[23] = 1;                                  // notalive: mov eax,1 (0x16)
          npre[27] = 0xC3;                                                // ret      (0x1b)
          uint old;
          VirtualProtectEx(h0, (IntPtr)cave, (IntPtr)64, 0x40 /* PAGE_EXECUTE_READWRITE */, out old);
          bool ok = WriteMem(h0, cave, npre);
          VirtualProtectEx(h0, (IntPtr)cave, (IntPtr)64, old, out old);
          if (!ok) { Log("write cave failed: " + Marshal.GetLastWin32Error()); return; }
          Log("page=0x" + tab.ToString("X") + " cave written");
        }
        engTable = tab; engCave = cave;
      } finally { CloseHandle(h0); }
    }
    if (engTable == 0) return;
    IntPtr h = OpenProcess(0x438, false, pid);
    if (h == IntPtr.Zero) { engTable = 0; engCave = 0; return; }
    try {
      byte[] data = new byte[16 + TABLE_SLOTS * 4];
      BitConverter.GetBytes(1).CopyTo(data, 0);                       // alive = 1
      if (zones != null) {
        for (int i = 0; i < zones.Length; i++) {
          int z = zones[i];
          if (z >= 0 && z < TABLE_SLOTS) BitConverter.GetBytes(1).CopyTo(data, 16 + z * 4);
        }
      }
      WriteMem(h, engTable, data);
      Log("table write: alive=1 zones=[" + (zones == null ? "" : string.Join(",", Array.ConvertAll(zones, x => x.ToString()))) + "]");
    } finally { CloseHandle(h); }
   } catch (Exception ex) { Log("EXCEPTION " + ex.GetType().Name + ": " + ex.Message); }
  }

  // ---- zone cache + heartbeat -------------------------------------------
  // The MSAA tree falls ASLEEP after ~30 s without a client request (Chrome
  // shuts its accessibility engine down) and the first queries after the wake
  // see GENERIC panes: measured 2026-09-12 — a probe run right after a longer
  // pause answered "zone 4" (an unnamed PANE) for EVERY point, the page
  // included, until the tree finished rebuilding. A background heartbeat
  // keeps the tree awake and caches the last answer so a request that arrives
  // a few ms after the last heartbeat can be served from the cache.
  private static readonly object zoneLock = new object();
  private static string cacheBody = "{\"zone\":0,\"zones\":[]}";
  private static string cacheTabBody = "";      // tab-under-cursor fragment for cachePt
  private static bool cacheTabOk = false;       // ... and it was computed WITH the zone set of cachePt
  private static POINT cachePt = new POINT();
  private static int cacheAt = 0;
  private static bool cacheOk = false;
  private static POINT lastPollPt = new POINT();   // cursor position at the previous poll
  private static int lastClassifyAt = 0;           // throttle for classifications during a move
  private static int lastTabWarmAt = 0;            // throttle for the tab-cache warm-up (see Heartbeat)
  // Set while a request is being served. The heartbeat SKIPS its own
  // classification then: two accessibility walks (the heartbeat's zone walk and
  // the request's tab walk) compete for the same tree and both get slower -
  // measured 2026-10-04 in Chrome 148, where a tab answer took ~300 ms and the
  // SW gave up, reloading the ACTIVE tab instead of the hovered one.
  private static volatile bool servingRequest = false;

  private static bool CacheFresh(POINT pt) {
    lock (zoneLock) {
      if (!cacheOk) return false;
      if (cachePt.X != pt.X || cachePt.Y != pt.Y) return false;
      return (Environment.TickCount - cacheAt) < 400;
    }
  }
  // A ZONE-ONLY answer carries no tab information: the point changed, so the
  // tab computed for the previous point must NOT be served for this one. That
  // is exactly what produced "the PREVIOUS tab reloads" when the cursor moved
  // fast (user report 2026-09-21): the fresh zone classification updated
  // cachePt while cacheTabBody still held the tab of the previous wheel, and
  // GetCachedTab - matching on the point alone - returned it.
  private static void CacheStore(POINT pt, string body) {
    lock (zoneLock) {
      cacheBody = body;
      cacheTabBody = "";
      cacheTabOk = false;
      cachePt = pt; cacheAt = Environment.TickCount; cacheOk = true;
    }
  }
  // The tab-under-cursor answer for the SAME point the zone cache was built for
  // (null = no valid cached answer). Served instantly, so the SW's 485 bridge
  // never has to wait for an accessibility walk (measured 59-104 ms - right at
  // the SW's timeout, which made the hovered-tab refresh fail intermittently).
  // Valid ONLY when it was computed together with the zone set of this very
  // point (cacheTabOk).
  private static string GetCachedTab(POINT pt) {
    lock (zoneLock) {
      if (!cacheOk || !cacheTabOk) return null;
      if (cachePt.X != pt.X || cachePt.Y != pt.Y) return null;
      return cacheTabBody;
    }
  }
  // Zone JSON for a point (null = read the cursor now). A FRESH classification
  // caches the zone set AND the tab under the cursor for that point.
  private static string GetZoneJson(POINT? at) {
    POINT pt;
    if (at.HasValue) pt = at.Value;
    else if (!GetCursorPos(out pt)) return "{\"zone\":-1,\"zones\":[-1]}";
    if (CacheFresh(pt)) { lock (zoneLock) { return cacheBody; } }
    ClassifyAndCache(pt);
    lock (zoneLock) { return cacheBody; }
  }
  // Keeps Chrome's accessibility tree awake (the tree is what makes the
  // classification possible), refreshes the cache whenever the cursor moved
  // or the cache got old, and keeps the ENGINE's zone table (patch v19) in
  // sync. Runs on a background thread; the answers the SW gets are at most one
  // heartbeat apart.
  //
  // POLL RATE (2026-09-20): the engine CACHES the region verdict and only
  // recomputes it when >300 ms passed or the cursor moved >3 px since the last
  // computation (FUN_00415bf0), and it reads the table at that moment. With a
  // 120 ms poll the table could still hold the PREVIOUS zone when the user
  // moved onto a zone and scrolled immediately: the first notch then read a
  // stale 0 for that region, the cache kept it for up to 300 ms and every
  // following notch was skipped too (user report: "works, but sometimes
  // stops"). Measured write latency was ~170 ms; the poll is now 30 ms, so
  // the stale-table window shrinks to one classification (~1-3 ms) plus the
  // poll. The classification itself runs only when the cursor MOVED, so an
  // idle helper costs one GetCursorPos per 30 ms and nothing else.
  private static void Heartbeat() {
    while (true) {
      try {
        POINT pt;
        if (GetCursorPos(out pt)) {
          bool stale;
          lock (zoneLock) {
            stale = !cacheOk || cachePt.X != pt.X || cachePt.Y != pt.Y ||
                    (Environment.TickCount - cacheAt) > 1200;
          }
          if (stale) {
            // Classifying EVERY intermediate position of a fast move is wasted
            // work: the engine only reads the table when an input event
            // arrives, i.e. when the hand has settled. So while the cursor is
            // moving the classification is throttled, and the moment the
            // position stops changing it runs at once (settle detection) -
            // that keeps the measured write latency at ~0 ms for the case that
            // matters while cutting the CPU cost of a continuous drag.
            bool settled = (pt.X == lastPollPt.X && pt.Y == lastPollPt.Y);
            bool movingGate = (Environment.TickCount - lastClassifyAt) > 80;
            bool keepTreeAwake = (Environment.TickCount - cacheAt) > 1200;
            if (!servingRequest && (settled || movingGate || keepTreeAwake)) {
              // zones = null -> AOP error (nothing matches); [] -> the cursor is
              // not over this browser (nothing matches, the input passes through)
              int[] z = ClassifyAndCache(pt);
              lastClassifyAt = Environment.TickCount;
              // WARM THE TAB CACHE while the cursor RESTS over a tab-related zone.
              // The SW's hovered-tab request then answers in ~1 ms instead of a
              // fresh 79-219 ms accessibility walk - which is what makes a wheel
              // over a tab feel instant for a "hovered tab" action too.
              // GUARDS (the round-2 failure was a walk on EVERY classification):
              //   * only when the cursor has SETTLED (never during a fast pass);
              //   * only over a tab-related zone (12/15/17) - the only case where
              //     the tab under the cursor can be asked for;
              //   * NEVER while a request is being served (that contention is what
              //     made the zone query time out);
              //   * at most every 150 ms (the walk is expensive).
              if (settled && !servingRequest && z != null &&
                  (Array.IndexOf(z, Z_TAB) >= 0 || Array.IndexOf(z, Z_CLOSE) >= 0 ||
                   Array.IndexOf(z, Z_SPEAKER) >= 0) &&
                  (Environment.TickCount - lastTabWarmAt) > 150) {
                string tb = TabUnderCursorJson(pt);
                // Store it for THIS point only (the cursor may have moved during
                // the walk; CacheStore keeps point and tab consistent by design).
                lock (zoneLock) {
                  if (cacheOk && cachePt.X == pt.X && cachePt.Y == pt.Y) {
                    cacheTabBody = tb; cacheTabOk = true;
                  }
                }
                lastTabWarmAt = Environment.TickCount;
              }
            }
          }
          lastPollPt = pt;
        }
      } catch { /* never kill the heartbeat */ }
      System.Threading.Thread.Sleep(30);
    }
  }

  private static int Main() {
    // DPI-aware: element rects (accLocation) and AccessibleObjectFromPoint
    // use PHYSICAL pixels, while GetWindowRect in a DPI-unaware process is
    // DPI-virtualized (Chrome at 150%: real window ~2094px, reported 1396).
    // The zone-30 position rule compares both - make the process aware so
    // every coordinate is physical (found 2026-09-12).
    try { SetProcessDPIAware(); } catch { }
    // The browser that spawned us. The native-host chain is
    //     browser -> cmd.exe -> this exe
    // (Chrome's launcher inserts the cmd), so walk UP until a browser-named
    // process appears - the direct parent is cmd.exe, which is why this used to
    // end up as 0 and the own-window gate was silently inert (found 2026-09-13
    // while fixing the multi-browser engine binding). Applied only when such an
    // ancestor exists: the standalone smoke test and the zone probes spawn this
    // exe from node/powershell and must keep the gate off.
    try {
      uint cur = (uint)System.Diagnostics.Process.GetCurrentProcess().Id;
      for (int lvl = 0; lvl < 8; lvl++) {
        string pname;
        uint ppid = FindParent(cur, out pname);
        if (ppid == 0 || string.IsNullOrEmpty(pname)) break;
        if (IsBrowserName(pname)) { browserPid = ppid; browserName = pname.ToLowerInvariant(); break; }
        cur = ppid;
      }
    } catch { browserPid = 0; }
    // Background heartbeat: keeps Chrome's a11y tree awake + warms the cache.
    try {
      System.Threading.Thread hb = new System.Threading.Thread(Heartbeat);
      hb.IsBackground = true;
      hb.Start();
    } catch { }
    Stream stdin = Console.OpenStandardInput();
    Stream stdout = Console.OpenStandardOutput();
    byte[] lenBuf = new byte[4];
    while (true) {
      // read 4-byte length
      int got = 0;
      while (got < 4) {
        int n = stdin.Read(lenBuf, got, 4 - got);
        if (n <= 0) return 0;
        got += n;
      }
      int len = BitConverter.ToInt32(lenBuf, 0);
      if (len <= 0 || len > 65536) return 0;
      byte[] body = new byte[len];
      got = 0;
      while (got < len) {
        int n = stdin.Read(body, got, len - got);
        if (n <= 0) return 0;
        got += n;
      }
      // parse the request id (tolerate junk) + the optional "tab" flag (the
      // SW asks for the tab under the cursor to answer native type 485)
      int reqId = 0;
      bool wantsTab = false;
      try {
        string msg = System.Text.Encoding.UTF8.GetString(body);
        int i = msg.IndexOf("\"__id\"", StringComparison.Ordinal);
        if (i >= 0) {
          int j = msg.IndexOf(':', i);
          if (j >= 0) {
            int k = j + 1;
            while (k < msg.Length && (msg[k] == ' ' || msg[k] == '\t')) k++;
            int e = k;
            while (e < msg.Length && msg[e] >= '0' && msg[e] <= '9') e++;
            if (e > k) int.TryParse(msg.Substring(k, e - k), out reqId);
          }
        }
        wantsTab = msg.IndexOf("\"tab\":1", StringComparison.Ordinal) >= 0 ||
                   msg.IndexOf("\"tab\":true", StringComparison.Ordinal) >= 0;
        // Diagnostic channel (2026-10-04): the SW sends a free-form note that is
        // written into this log. It is the only way to observe the SERVICE
        // WORKER in a browser that must not be relaunched with a debug port
        // (Chrome 148 = the user's main browser). Plain text only - no escapes,
        // the SW keeps the note free of quotes.
        int ni = msg.IndexOf("\"note\":\"", StringComparison.Ordinal);
        if (ni >= 0) {
          int ns = ni + 8, ne = msg.IndexOf('"', ns);
          if (ne > ns) Log("SW " + msg.Substring(ns, ne - ns));
        }
      } catch { reqId = 0; }
      // Sample the cursor ONCE: the zone set and the tab must belong to the
      // SAME point, otherwise the tab answer is useless (see GetCachedTab).
      servingRequest = true;
      POINT cpt;
      bool havePt = GetCursorPos(out cpt);
      string zj = GetZoneJson(havePt ? (POINT?)cpt : null);   // {"zone":Z,"zones":[...]}
      string resp = "{\"__id\":" + reqId + "," + zj.Substring(1, zj.Length - 2);
      if (wantsTab && havePt) {
        string cached = GetCachedTab(cpt);          // instant, valid for THIS point
        bool fromCache = cached != null;
        int walkMs = 0;
        if (cached == null) {
          int t0 = Environment.TickCount;
          cached = TabUnderCursorJson(cpt);         // 59-104 ms accessibility walk
          walkMs = Environment.TickCount - t0;
          // Remember it for this point: the SW sends a SECOND tab request in the
          // same wheel burst (the bundle's own 485 resolution).
          lock (zoneLock) {
            if (cacheOk && cachePt.X == cpt.X && cachePt.Y == cpt.Y) {
              cacheTabBody = cached; cacheTabOk = true;
            }
          }
        }
        // Diagnostic (2026-10-04): "works, but not always" needs the exact answer
        // per wheel - an EMPTY or LATE answer makes the SW fall back to the ACTIVE
        // tab. walk= is how long the accessibility walk took (the SW gives up
        // after its own timeout, so a walk longer than that = the wrong tab).
        Log("tab ask " + cpt.X + "," + cpt.Y + " -> " +
            (cached.Length == 0 ? "EMPTY (" + lastTabReason + ")" : cached) +
            (fromCache ? " [cached]" : " walk=" + walkMs + "ms"));
        resp += cached;
      }
      resp += "}";
      byte[] outBytes = System.Text.Encoding.UTF8.GetBytes(resp);
      byte[] outLen = BitConverter.GetBytes(outBytes.Length);
      stdout.Write(outLen, 0, 4);
      stdout.Write(outBytes, 0, outBytes.Length);
      stdout.Flush();
      servingRequest = false;
    }
  }
}
