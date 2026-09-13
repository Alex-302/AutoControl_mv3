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
//   request:  { "__id": 1 }
//   response: { "__id": 1, "zone": 12, "zones": [12, 1] }
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
//  * TITLE AREA (4) is the WHOLE top band of the window - the caption, the
//    tabs, the omnibox and the toolbar - down to the page (the app's own
//    illustration in file80.js "titA" + the user's definition: "the
//    rectangle bounded by the window's left/right/top borders, its bottom
//    edge is where the panel meets the page"). Implemented chain-based.
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
  private static bool Rect(IAccessible a, out RECT r) {
    r = new RECT();
    try {
      int x, y, w, h;
      a.accLocation(out x, out y, out w, out h, 0);
      r.L = x; r.T = y; r.R = x + w; r.B = y + h;
      return w > 0 && h > 0;
    } catch { return false; }
  }
  // The kebab ("Customize and control Chrome") is not exposed as a named
  // element in Chrome 150: identify it by POSITION - a button in the toolbar
  // whose right edge hugs the window's right edge (this mirrors the engine's
  // own position-based zone-30 check in FUN_004156f0). The "New Chrome
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
    IntPtr hwnd = WindowFromPoint(pt);
    if (hwnd == IntPtr.Zero) return false;
    IntPtr root = GetAncestor(hwnd, 2 /* GA_ROOT */);
    if (root == IntPtr.Zero) return false;
    RECT wr;
    if (!GetWindowRect(root, out wr)) return false;
    int gap = wr.R - er.R;
    return gap >= 0 && gap < 60;
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
  private static int TabButtonZone(IAccessible tab, POINT pt) {
    int cc = 0;
    try { cc = tab.accChildCount; } catch { cc = 0; }
    if (cc <= 0) return 0;
    int hitLeft = int.MinValue, maxLeft = int.MinValue;
    for (int i = 1; i <= cc; i++) {
      IAccessible c = null;
      try { c = (IAccessible)tab.get_accChild(i); } catch { c = null; }
      if (c == null) continue;
      try {
        if (Role(c) == 43) {                       // PUSHBUTTON
          RECT r;
          if (Rect(c, out r)) {
            if (r.L > maxLeft) maxLeft = r.L;
            if (pt.X >= r.L && pt.X <= r.R && pt.Y >= r.T && pt.Y <= r.B) {
              if (r.L > hitLeft) hitLeft = r.L;
            }
          }
        }
      } finally { try { Marshal.ReleaseComObject(c); } catch { } }
    }
    if (hitLeft == int.MinValue) return 0;         // the cursor is on the tab body
    return (hitLeft >= maxLeft) ? Z_CLOSE : Z_SPEAKER;
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
    // Chrome-role detection: the chain is walked from the hovered element
    // UPWARDS (d0 = the element, higher d = closer to the window), so the
    // page's own ARIA roles sit BELOW the DOCUMENT (d < docDepth) and the
    // browser chrome sits ABOVE it (d > docDepth). A page can expose the very
    // same roles as the UI - <input> = 42 EDIT, role=toolbar = 22,
    // role=tablist = 60, pagetab = 37 - so only depths ABOVE the DOCUMENT (or
    // every depth when no DOCUMENT is in the chain, i.e. real chrome) may
    // drive the browser-UI rules.
    bool inToolbar = false, inGroup = false;
    for (int d = 0; d < MAXDEPTH; d++) {
      if (docDepth >= 0 && d <= docDepth) continue;   // inside the page
      if (roles[d] == 22) inToolbar = true;        // TOOLBAR
      if (d > 0 && roles[d] == 20) inGroup = true; // GROUPING (the omnibox container)
    }
    // Inside a DOCUMENT = inside the page: no browser-chrome rule may fire.
    bool ui = !inPage;

    bool isTabBtn = ui && roles[0] == 43 && roles[1] == 37;   // the hovered element IS a tab button
    bool isNewTabBtn = ui && roles[0] == 43 && roles[1] == 60;
    bool stripNear = ui && (roles[0] == 37 || roles[1] == 37 || roles[0] == 60 || roles[1] == 60);

    int[] zs = new int[8];
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
      if (isTabBtn) tbZone = TabButtonZone(chain[1], pt);
      else if (roles[0] == 37) tbZone = TabButtonZone(chain[0], pt);
      else if (roles[1] == 37) tbZone = TabButtonZone(chain[1], pt);
      if (tbZone != 0) zs[n++] = tbZone;
      // 4. New tab button: a PUSHBUTTON whose parent is the PAGETABLIST.
      if (isNewTabBtn) zs[n++] = Z_NEWTAB;
      // 5. Omnibox: the address text field (42 EDIT at d0/d1) or the
      //    site-info (lock) button - a BUTTONMENU (57) inside the group.
      if (roles[0] == 42 || roles[1] == 42) zs[n++] = Z_OMNIBOX;
      else if (roles[0] == 57 && roles[1] == 20) zs[n++] = Z_OMNIBOX;
      // 6. Bookmark (star) button: a PUSHBUTTON inside the omnibox group,
      //    which itself sits inside the toolbar band.
      if (roles[0] == 43 && inGroup && inToolbar) zs[n++] = Z_BOOKMARK;
      // 7. Toolbar band (role 22 in the ancestry) + the browser menu button
      //    (the kebab, or the update pill that occupies its slot).
      if (inToolbar) {
        zs[n++] = Z_TOOLBAR;
        if ((roles[0] == 43 || roles[0] == 57) && IsRightEdgeButton(chain[0], pt)) zs[n++] = Z_MENUBTN;
      }
      // 8. Browser tab: a PAGETAB at d0/d1, or the PAGETABLIST (strip area /
      //    gap). EXCLUSIONS: the "+" button's parent IS the PAGETABLIST
      //    (handled above), and a point that hit one of the tab's BUTTONS
      //    (Close/Speaker) is not "the tab" - giving them 12 would run a
      //    zone-12 AND a zone-15/17 action at once.
      if (tbZone == 0 && (roles[0] == 37 || (roles[1] == 37 && !isTabBtn))) zs[n++] = Z_TAB;
      else if ((roles[0] == 60 || roles[1] == 60) && !isNewTabBtn) zs[n++] = Z_TAB;
      // 9. TITLE AREA = the WHOLE top band of the window: the caption, the
      //    tab strip, the omnibox and the toolbar - everything above the page
      //    (user definition 2026-09-12; the app's own illustration in
      //    file80.js "titA" is a full-width rect from the window's top edge
      //    down to the page). Chain-based: anything belonging to the tab
      //    strip (TAB / PAGETABLIST / a tab button) or to the toolbar.
      if (inToolbar || stripNear || isTabBtn) zs[n++] = Z_TITLE;
      // 10. The rest of the window frame (the border band, the strip's empty
      //     area) - an unnamed PANE that is not part of the page.
      else if (roles[0] == 16) zs[n++] = Z_TITLE;
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
    int[] zs = new int[8];
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

  // Returns the JSON body: {"zone":P,"zones":[...]} - P is the most specific
  // zone (logging / older SW builds), zones is the full matching set.
  // {"zone":-1,...} = cursor/AOP error (the SW treats it as "no match").
  // {"zone":0,"zones":[]} = the cursor is not over this browser's window.
  private static string ComputeZoneJson() {
    POINT pt;
    if (!GetCursorPos(out pt)) return "{\"zone\":-1,\"zones\":[-1]}";
    if (!OverOwnBrowser(pt)) return "{\"zone\":0,\"zones\":[]}";
    return JsonOfZones(ZonesForPoint(pt));
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
  private const int ORIG_BLOCK = 0x1C;     // offset of the untouched original bytes
  private const int TABLE_SLOTS = 64;      // regions 0..63 (>= 40 = menu, engine's own)
  private static uint engPid = 0;
  private static long engTable = 0;
  private static long engCave = 0;

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
    uint pid = (uint)pids[0];
    // (re)initialise when the engine restarted
    if (pid != engPid || engCave == 0) {
      Log("init for pid " + pid + " (engines: " + pids.Length + ")");
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
  private static POINT cachePt = new POINT();
  private static int cacheAt = 0;
  private static bool cacheOk = false;

  private static bool CacheFresh(POINT pt) {
    lock (zoneLock) {
      if (!cacheOk) return false;
      if (cachePt.X != pt.X || cachePt.Y != pt.Y) return false;
      return (Environment.TickCount - cacheAt) < 400;
    }
  }
  private static void CacheStore(POINT pt, string body) {
    lock (zoneLock) { cacheBody = body; cachePt = pt; cacheAt = Environment.TickCount; cacheOk = true; }
  }
  private static string GetZoneJson() {
    POINT pt;
    if (!GetCursorPos(out pt)) return "{\"zone\":-1,\"zones\":[-1]}";
    if (CacheFresh(pt)) { lock (zoneLock) { return cacheBody; } }
    string body = ComputeZoneJson();
    CacheStore(pt, body);
    return body;
  }
  // Keeps Chrome's accessibility tree awake (the tree is what makes the
  // classification possible), refreshes the cache whenever the cursor moved
  // or the cache got old, and keeps the ENGINE's zone table (patch v19) in
  // sync. Runs on a background thread; the answers the SW gets are at most one
  // heartbeat apart.
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
            // zones = null -> AOP error (nothing matches); [] -> the cursor is
            // not over this browser (nothing matches, the input passes through)
            int[] z = OverOwnBrowser(pt) ? ZonesForPoint(pt) : new int[0];
            WriteZoneTable(z == null ? new int[0] : z);
            CacheStore(pt, JsonOfZones(z));
          }
        }
      } catch { /* never kill the heartbeat */ }
      System.Threading.Thread.Sleep(120);
    }
  }

  private static int Main() {
    // DPI-aware: element rects (accLocation) and AccessibleObjectFromPoint
    // use PHYSICAL pixels, while GetWindowRect in a DPI-unaware process is
    // DPI-virtualized (Chrome at 150%: real window ~2094px, reported 1396).
    // The zone-30 position rule compares both - make the process aware so
    // every coordinate is physical (found 2026-09-12).
    try { SetProcessDPIAware(); } catch { }
    // The browser that spawned us (native hosts are children of the browser
    // process) - used to ignore windows of other applications. Applied only
    // when the parent really is a browser: the standalone smoke test and the
    // zone probes spawn this exe from node.
    try {
      string pname;
      uint ppid = FindParent((uint)System.Diagnostics.Process.GetCurrentProcess().Id, out pname);
      browserPid = IsBrowserName(pname) ? ppid : 0;
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
      // parse the request id (tolerate junk)
      int reqId = 0;
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
      } catch { reqId = 0; }
      string resp = "{\"__id\":" + reqId + "," + GetZoneJson().Substring(1);
      byte[] outBytes = System.Text.Encoding.UTF8.GetBytes(resp);
      byte[] outLen = BitConverter.GetBytes(outBytes.Length);
      stdout.Write(outLen, 0, 4);
      stdout.Write(outBytes, 0, outBytes.Length);
      stdout.Flush();
    }
  }
}
