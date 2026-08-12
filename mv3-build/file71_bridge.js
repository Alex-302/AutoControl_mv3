// file71_bridge.js — content loader for SW-created file71.html popup windows.
//
// The service worker cannot fill the popup via chrome.scripting.executeScript:
// chrome-extension:// pages are NOT injectable ("Extension manifest must
// request permission to access this host" — user VM 2026-08-12, the window
// flashed empty). Instead the popup page (an extension page with full
// chrome.runtime access) requests its content from the SW and reports the
// button result back. FEATURES-MV3.md §7-15.
(function () {
  'use strict';
  var m = (location.search || '').match(/[?&]runId=(\d+)/);
  var runId = m ? +m[1] : 0;
  if (!runId) return; // opened manually — leave the framework page as-is

  chrome.runtime.sendMessage({ type: 'acPopupContent', runId: runId }, function (res) {
    if (!res || !res.html) return;
    document.title = res.title || 'AutoControl';
    document.body.insertAdjacentHTML('beforeend', res.html);

    // Auto-size the window to the content (MV2 `q()` in _Fo).
    var q = function () {
      var n = document.body.offsetHeight;
      if (n && res.winId) {
        var nh = Math.max(0, window.outerHeight - window.innerHeight) + n;
        chrome.windows.update(res.winId, { height: nh, top: (window.screenY - (nh - window.outerHeight) / 2) | 0 });
      }
    };
    document.querySelectorAll('img').forEach(function (img) { img.onload = q; });
    setTimeout(q, 150); q();

    // Button result → SW (yes/no attributes as in MV2).
    document.addEventListener('click', function (ev) {
      var btn = ev.target && ev.target.closest ? ev.target.closest('button') : null;
      if (!btn) return;
      chrome.runtime.sendMessage({ type: 'acPopupResult', runId: runId, answer: !!btn.hasAttribute('yes') });
    });

    // Window closed without a button (X / windows.remove) → resolve with
    // false (MV2's onunload → dialogResult undefined).
    window.addEventListener('unload', function () {
      try { chrome.runtime.sendMessage({ type: 'acPopupResult', runId: runId, answer: false }); } catch (e) {}
    });
  });
})();
