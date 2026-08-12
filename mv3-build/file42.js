'use strict';/* §N references in comments point to Docs/FEATURES-MV3.md (feature status & port gaps). *//* AC-MV3 FIX (2026-08-06): re-injection guard. n() (file48) injects
   file42.js via scripting.executeScript when a delivery times out — but EVERY
   executeScript creates a NEW isolated VM/context with its own listeners and
   r[id] map, so the same messages get processed TWICE (double-K →
   setClipboard "Invalid argument types"/"undefined", lost promises → hung
   actions; seen at 09:34: repeated "no listener → inject" + WATCHDOG).
   The DOM (document) IS shared across isolated worlds — guard on it so a
   re-injection is a no-op. The original file42 keeps serving; n()'s retry
   re-delivers the SAME message → SW dedup / __acFnDedup make it harmless.
   NOTE: top-level `return` is ILLEGAL in a classic script (the manifest
   content_scripts load) — hence the if-wrapper, not an early return.
   Staleness: document.__acF42T is a heartbeat refreshed on every message
   this instance processes. If it is stale (>20s), the guard-holder is DEAD
   (extension reload without tab reload — "Extension context invalidated")
   → a fresh injection takes over and heals delivery. The 20s window means
   a mere busy/blocked page (modal alert) never triggers a takeover. */
if(!document.__acF42||2E4<Date.now()-(document.__acF42T||0)){document.__acF42=!0;document.__acF42T=Date.now();/* AC-MV3 FIX (2026-08-06): keep the heartbeat FRESH by TIMER, not only on message processing. Before this, a live file42 instance that received NO messages for >20s looked "dead" to the guard (its __acF42T went stale) → a NEW injection was allowed → TWO live listeners in the tab → every tabs.sendMessage was delivered to BOTH → funcCode dedup-hit + the first (null) response winning the channel (setClipboard "_fr is not iterable"). A fresh injection while the old instance is alive does NOT remove the old listener (separate isolated world). With the timer the guard blocks duplicates as long as the holder is alive; a truly dead holder (extension reload → context invalidated → timers stop) still expires after 20s and lets a fresh injection heal. */try{clearInterval(document.__acF42I);document.__acF42I=setInterval(function(){document.__acF42T=Date.now()},1E4)}catch(e){}/* AC-MV3 FIX (2026-08-08): MV2-like silent console (user request) — page-side (isolated world) diagnostics OFF by default (MV2-like silence; enable via Options → Advanced Options → "Log page scripts", advOpts.logPage; live via storage.onChanged). console.error stays. */try{var AC_LOG_PAGE=false,__acOrigC={log:console.log.bind(console),info:console.info.bind(console),warn:console.warn.bind(console),debug:console.debug.bind(console)};function __acApplyLog(){['log','info','warn','debug'].forEach(function(m){try{console[m]=AC_LOG_PAGE?__acOrigC[m]:function(){}}catch(e){}})}__acApplyLog();try{chrome.storage.local.get("advOpts",function(r){AC_LOG_PAGE=!!(r&&r.advOpts&&r.advOpts.logPage);__acApplyLog()})}catch(e){}try{chrome.storage.onChanged.addListener(function(c,a){if(a==="local"&&c.advOpts){AC_LOG_PAGE=!!((c.advOpts.newValue||{}).logPage);__acApplyLog()}})}catch(e){}}catch(e){}window.FN||(()=>{function u(a,g){document.__acF42T=Date.now();let e=b=>{b&&void 0!==b.error&&(console.error("AutoControl script:",b.error),b.error instanceof Error&&(b.error+=""));g(b)},c=!0;if(a.pongId)r[a.pongId](a.result),delete r[a.pongId];else if(a.event)if(a.event.delete){delete window[a.funcName];try{window.postMessage({type:"acEvt",funcName:a.funcName,del:1},"*")}catch(e){}}else{var d=window[a.funcName];d&&d(a.event);/* AC-MV3: ACtl.on handlers live in the USER_SCRIPT world (window[g] is not visible here) — relay the event so their promises/callbacks resolve. */try{window.postMessage({type:"acEvt",funcName:a.funcName,event:a.event},"*")}catch(e){}}else if(a.scriptId)try{/* AC-MV3 FIX (2026-08-06, round 5): KEEP x.__cur after this branch (NO finally-restore). Round 3 added the restore ("context leak") and that BROKE the F()-path + ACtl.on: every later funcCode message and the acUserApi relay read x.__cur (scriptId/trigInstId), and the SW-side dedup key + file67 on() registration DEPEND on a non-empty trigInstId chain. Without the chain: (a) every F() execUserFunc got key "tabId::" → the SW __acExecCompleted dedup (15s TTL) BLOCKED all F() calls after the first (getTabInfo) → captureTab/setClipboard/getFile/import/runInPageCtx "_fr is not iterable"/"[null]"/"undefined"; (b) W()'s on-case does _lf(_Vj,...,h,[]) — with h=undefined the trigInstId level is SKIPPED and .push(c) hits an object → TypeError → the tabLoadEnd registration never happened → ACtl.on 8s timeout. The "leak" IS the context chain (same as MV2); the 13:33 dedup-hit cascade was caused by DOUBLE DELIVERY (two live file42 instances — fixed by the round-4 heartbeat timer), NOT by the leak. */x.__cur={scriptId:a.scriptId,tabId:a.tabId,targetTabs:a.targetTabs,trigInstId:a.trigInstId+(a.frmCBId?"~f"+(Math.random()+"").slice(2):"")};/* AC-MV3 FIX (2026-08-10, FEATURES-MV3.md §7-5 follow-up): runInFrames — the SAME
   frmCBId message (it carries scriptId, so this scriptId branch handles it)
   is delivered to EVERY matching frame; trigInstId was taken from the
   message AS-IS → ALL frames sent execUserFunc with the SAME dedup key →
   the 2nd+ frames got the SW's in-flight BLOCK → {result:undefined} → null
   in the runInFrames result (user VM: ["https://example.org/", null]).
   Appending a per-FRAME random to trigInstId when a.frmCBId is set gives
   each frame its own key → every frame executes and its result is pushed
   (same fix class as the runInTab [null] ~suffix, but BETWEEN frames).
   Plain RUN SCRIPT (no frmCBId) is unchanged. */c=B(C(a.scriptId,a.tabId,a.targetTabs,a.trigInstId)(),a.funcCode,a.args);if(c instanceof Promise){if(a.noWait){/* AC-MV3 FIX (2026-08-06, round 7): fire-and-forget — ack the TOP-LEVEL RUN SCRIPT IMMEDIATELY (its result is unused by the runScript action — t=true in _A ignores errors). Before this, n() waited for the entire script's Promise → any script longer than the 4000ms fallback hung the action queue → WATCHDOG force-shift → subsequent RUN SCRIPTs queued/failed (VM 15:03: "Queue stuck! 2 items"). AC-MV3 FIX (2026-08-06, round 7b): nested _A calls (runInTab/runInFrames) send noWait=false — they get their REAL result below (round-7 made them return [true]). */try{console.warn('[AC-F42] script done trig='+String(a.trigInstId).slice(0,60))}catch(_z){};return e({result:!0}),!0}return c.then(function(b){/* AC-MV3 FIX (2026-08-06, round 7b): nested _A — await and return the REAL result (runInTab/runInFrames). */try{console.warn('[AC-F42] script done trig='+String(a.trigInstId).slice(0,60))}catch(_z){};e({result:b})},function(g){try{console.warn('[AC-F42] script ERR:',String(g&&g.message||g).slice(0,120))}catch(_z){};e({error:g})}),!0}
c={result:c}}catch(b){c={error:b}}else if(a.funcCode){/* AC-MV3 FIX (2026-08-02, round 6): nested FN calls (F()→K serialization for setClipboard/saveFile) reuse the PARENT x.__cur → execUserFunc dedup key = parent's (still in-flight) → SW answers 'dedup' → undefined → 'not iterable'. Give EVERY nested call a UNIQUE trigInstId. AC-MV3 FIX (2026-08-06): the SAME z-bundle (funcCode,args) can be delivered TWICE ~1ms apart (double delivery of the F()/K message — observed args=[same window name,'png'] twice) — the 2nd K reads the window name AFTER the 1st deleted it → setClipboard("undefined"). Share the in-flight promise instead of re-running (2s window; args sliced so dataUri payloads stay out of the key). */var _fdk=a.funcCode.slice(0,100)+JSON.stringify((a.args||[]).map(function(q){return"string"==typeof q?q.slice(0,100):q}));var _fdp=__acFnDedup.get(_fdk);if(_fdp&&Date.now()-_fdp.t<2E3){/* AC-MV3 DIAG (2026-08-06): did the 2s dedup window fire? setClipboard 4/4 FAIL with funcCode val logged — if this line appears, the funcCode message WAS double-delivered. */try{console.warn('[AC-F42] funcCode dedup-hit key='+_fdk.slice(0,60))}catch(x){}return _fdp.pr.then(function(b){/* AC-MV3 FIX (2026-08-06): pass the RAW value like the normal path — the setClipboard consumer destructures the response (let [b,c,f]=yield F(...)) and would get 'Invalid argument types' from a {result:...} wrapper. */e(b)},function(g){e({error:g})}),!0}var _s=x.__cur,_ex=null;/* AC-MV3 DIAG (2026-08-06): context chain at funcCode entry — shows whether TWO messages share the SAME x.__cur (double delivery of ONE n() message) or carry DIFFERENT trigInstId chains (two F()/n() calls). */try{/* AC-MV3 DIAG: log the INCOMING chain + what the branch builds. */try{console.warn('[AC-F42] funcCode cur-in='+String(_s&&_s.trigInstId).slice(0,70)+' msgTrig='+String(a&&a.trigInstId).slice(0,70))}catch(_q2){};x.__cur=_s?Object.assign({},_s,{trigInstId:(_s.trigInstId||"")+"~"+(Math.random()+"").slice(2)}):{scriptId:a.scriptId,tabId:a.tabId,trigInstId:((a.trigInstId||"")+"~"+(Math.random()+"").slice(2))};try{c=FN(a.funcCode)(...a.args)}catch(_e2){_ex=_e2}}finally{x.__cur=_s}if(_ex){/* AC-MV3 DIAG (2026-08-06): an exception inside FN(...) escapes the listener → Chrome closes the sendMessage channel → n() attempt gets undefined → retry → funcCode dedup-hit cascade (setClipboard first-try null, "_fr is not iterable"). Catch, log, and answer with the error so the caller sees the REAL cause. */try{console.warn('[AC-F42] funcCode THREW:',String(_ex&&_ex.message||_ex))}catch(_z){};e({error:String(_ex&&_ex.message||_ex)});return!0}if("function"==typeof c)return c(e),!0;if(c&&"function"==typeof c.then){var _fpr=new Promise(function(_dV){c.then(function(v){/* AC-MV3 diag (round 7): what does the nested funcCode (K serialization) return? 2026-08-05: also log the ARGS — the setClipboard "undefined" K reads window[name] missing; args show which call/name */try{console.warn('[AC-F42] funcCode val:',JSON.stringify(v&&v.slice?v.slice(0,3):v).slice(0,150),'args='+JSON.stringify((a&&a.args||[]).slice(0,3)).slice(0,120))}catch(x){};e(v);_dV(v)},function(g){/* AC-MV3 diag (round 7): nested funcCode ERROR */try{console.warn('[AC-F42] funcCode ERR:',String(g&&g.message||g))}catch(x){};e({error:g});_dV({error:g})})});try{__acFnDedup.set(_fdk,{pr:_fpr,t:Date.now()});if(100<__acFnDedup.size){var _it=__acFnDedup.keys();__acFnDedup.delete(_it.next().value)}}catch(x){}return _fpr,!0}}else if(null!=a.insertCode)d=document.createElement("js"==a.type?"script":"style"),d.textContent=a.insertCode,document.head.appendChild(d);else if(a.scrtCtxVar)void 0===a.value?c=x[a.scrtCtxVar]:x[a.scrtCtxVar]=a.value;else return;e(c)}function v(a,g){if(y){for(var e=1;e in r;++e);r[e]=g;a.pingId=e;parent.postMessage(a,"*")}else m.runtime.sendMessage(a,c=>{var d=m.runtime.lastError;
return g(d?{error:d}:c)})}function C(a,g,e,c){return function w(...b){return new Proxy(()=>{},{get(n,p){if("__proto__"==p)return n[p];if(!b.length)switch(p){case "TAB_ID":return g;case "STOP_CHAIN":return Object.freeze({break:"inner"});case "STOP_FULL_SEQ":return Object.freeze({break:"outer"})}return w(...b,p)},apply(n,p,f){if("function"==typeof f[0]&&"then"==b[b.length-1]){var z=f;f=[];b.pop()}n=new Promise((D,A)=>{if("saveFile"==b[0]){var k="_"+(Math.random()+"").slice(2);window[k]=f[1];f[1]=k}else if("setClipboard"==
b[0])k="_"+(Math.random()+"").slice(2),window[k]=f[0],f[0]=k;else if("on"==b[0])"function"!=typeof f[f.length-1]&&f.push(()=>{}),f[f.length-1]={FUNC:E(f[f.length-1])};else if("off"==b[0])"function"==typeof f[f.length-1]&&(f[f.length-1]=f[f.length-1].__assocHndlrs||[]);else if("runInFrames"==b[0]||"runInTab"==b[0])if(k=f["runInTab"==b[0]?0:1],"object"==typeof k)for(let h in k)k[h]instanceof RegExp&&(k[h]={RE:k[h].source,F:k[h].flags});f=f.map(h=>"function"==typeof h?{FUNC:h+""}:h);v({type:"userAPI",
scriptId:a,props:b,args:f,targetTabs:e,trigInstId:c},h=>{if(h.error)A(h.error);else{let l=h.funcCode?FN(h.funcCode)(...h.args):h.result;h=Promise.resolve();if(l&&"object"==typeof l&&Symbol.iterator in l)for(let [t,q]of l.entries?l.entries():l)q&&q.funcCode&&q.args&&(l[t]=FN(q.funcCode)(...q.args),l[t]instanceof Promise&&(h=h.then(()=>l[t].then(F=>l[t]=F))));h.then(()=>D(l),A)}})});return z?n.then(...z):n}})}}function E(a){let g="_evt_"+(Math.random()+"").slice(2);a.__assocHndlrs||(a.__assocHndlrs=
[]);a.__assocHndlrs.push(g);let e=new Promise(c=>{window[g]=d=>{if("promise"==d)return e;c(d);a(d)}});return g}const m=chrome;
// AC-MV3: CSP-safe code execution. eval works only on pages without a CSP.
// On CSP pages `new Function`/eval throw EvalError — we fall back to the SW,
// which runs the code via chrome.userScripts (USER_SCRIPT world) and relays
// the result back through window.postMessage (all worlds share the DOM).
Object.defineProperty(window,"FN",{value:(a,ACtl)=>{
  // Sandbox / background world (file23.html via offscreen): NO chrome.runtime
  // (stub {}), but its CSP allows 'unsafe-eval' — plain eval works there and
  // the SW bridge is unavailable anyway.
  // AC-MV3 FIX (2026-08-02): ACtl is a 2nd param so the DIRECT eval below
  // captures it in the evaluated function's closure scope — replicating the
  // original `new Function("ACtl",...)` behavior (user scripts reference the
  // free variable ACtl, e.g. `await ACtl.saveURL(...)`).
  if(!m.runtime||typeof m.runtime.sendMessage!=="function"){
    try{return eval(`(${a})`)}catch(e){return function(){return Promise.reject(e)}}
  }
  // Content scripts (Chrome 133+): eval is ALWAYS forbidden (isolated worlds
  // have their own CSP without 'unsafe-eval') — userScripts is the only path.
  if(window.__acUsOk===false)return function(){return Promise.reject(new Error("chrome.userScripts unavailable — enable 'Allow user scripts' on chrome://extensions"))};
  return function(){
    if(window.__acUsOk===false)return Promise.reject(new Error("chrome.userScripts unavailable — enable 'Allow user scripts' on chrome://extensions"));
    var id="__acr_"+Math.random().toString(36).slice(2),args=[],t0=performance.now();
    // AC-MV3 FIX (2026-08-02, round 5): keep ALL arguments — slice(1)
    // dropped the first one (e.g. the z-bundle arg for captureTab → J
    // applied with NO args → e=undefined → 'Object.defineProperty called
    // on non-object').
    try{args=Array.prototype.slice.call(arguments)}catch(e){}
    var ctx=x.__cur||{},sid=ctx.scriptId;
    return new Promise(function(D,A){
      var responded=!1;
      // AC-MV3: when the execution finishes (or is deduped), tell the SW to
      // move the key from in-flight → completed (LRU). This suppresses
      // post-hoc "burst" duplicates that arrive after the original finished.
      var respond=function(h,dontDone){
        if(responded)return;responded=!0;
        var f=r[id];delete r[id];f&&f(h);
        if(!dontDone&&sid)try{m.runtime.sendMessage({type:"execUserFuncDone",tabId:ctx.tabId,scriptId:sid,trigInstId:ctx.trigInstId},function(){})}catch(e){}
        // AC-MV3 FIX (2026-08-02, round 4 — THE root cause of all delays):
        // the promise was NEVER resolved — D/A were never called, so u()'s
        // sendResponse/pongId never fired and the action hung until Chrome
        // closed the channel (~20s). Resolve/reject now: the script already
        // ran; only the result round-trip was stuck.
        try{h&&h.error?A(h.error):D(h&&h.result)}catch(e){}
      };
      r[id]=respond;
      window.addEventListener("message",function hnd(ev){
        var d=ev.data;
        if(d&&d.type=="acUserApiRes"&&d.id==id){
          window.removeEventListener("message",hnd);
          // AC-MV3 diagnostic: postMessage from the USER_SCRIPT world back to
          // file42 — this is the suspected slow hop (Chrome batches
          // userScripts.execute; the result arrives seconds later).
          try{console.warn('[AC-F42] res rcvd id='+id+' +'+(performance.now()-t0).toFixed(0)+'ms cur='+String(x.__cur&&x.__cur.trigInstId).slice(0,70)+(d.error?' err='+d.error:''))}catch(e){}
          respond({result:d.result,error:d.error});
        }
      });
      m.runtime.sendMessage({type:"execUserFunc",code:a,args:args,id:id,ctx:ctx,t:Date.now()},function(h){
        h=h||{};
        // AC-MV3 diagnostic: SW answer latency (ok/error/dedup/timeout).
        // 2026-08-05: h.st = SW state dump (up/conn/hs/if/ek) — surfaced in
        // the PAGE console so a SW restart / missing config chain is visible
        // without opening the service worker console. h.key = the dedup key
        // (identifies which call the SW blocked).
        try{console.warn('[AC-F42] sw cb id='+id+' +'+(performance.now()-t0).toFixed(0)+'ms'+(h.error?' err='+h.error:'')+(h.dedup?' dedup':'')+(h.timeout?' timeout':'')+(h.ok?' ok':'')+(h.dedup&&h.key?' key='+h.key:'')+(h.st?' st=up'+h.st.up+'s conn='+h.st.conn+' hs='+h.st.hs+' if='+h.st.if+' ek='+h.st.ek:''))}catch(e){}
        if(h.error){
          // userScripts toggle off → remember and never retry.
          if(/userScripts|user scripts|disabled|permission/i.test(h.error))window.__acUsOk=false;
          respond({error:h.error});
        } else if(h.dedup){
          // Same (tab, script, trigger instance) already handled by SW —
          // this frame is a duplicate (another frame or post-hoc burst).
          // Resolve as no-op; don't send execUserFuncDone (dontDone=true)
          // because the SW already has the key in its LRU.
          respond({result:void 0},!0);
        }
        // AC-MV3 FIX (2026-08-10, FEATURES-MV3.md §7-5 follow-up): the FIRST
        // userScripts.execute in a fresh (sub)frame costs ~4-5s (Chrome
        // creates the USER_SCRIPT world on first use); the SW acks early via
        // its 3s safety timeout ({ok:true,timeout:true}) and releases the
        // dedup key. The result normally still arrives via the acUserApiRes
        // postMessage once the slow execute completes — but on a COLD frame
        // the first result can be lost (observed: runInFrames first run
        // returned only the top frame's null — the subframe's answer never
        // arrived). Fallback: if the SW acked with timeout and no result has
        // arrived within 6s, RE-SEND execUserFunc ONCE — the world is warm
        // by then, so the retry succeeds fast. Mirrors the n() null-retry.
        // Double-exec only if the first attempt takes >9s (cold init ~4-5s).
        if (h && h.timeout) {
          setTimeout(function(){
            if (responded) return;
            var id2 = "__acr_" + Math.random().toString(36).slice(2);
            window.addEventListener("message", function hnd2(ev){
              var d = ev.data;
              if (d && d.type == "acUserApiRes" && d.id == id2) {
                window.removeEventListener("message", hnd2);
                if (responded) return;
                respond({result:d.result, error:d.error});
              }
            });
            try{console.warn('[AC-F42] execUserFunc cold-init retry id='+id)}catch(e){}
            m.runtime.sendMessage({type:"execUserFunc",code:a,args:args,id:id2,ctx:ctx,t:Date.now()},function(h2){
              h2=h2||{};
              if (responded) return;
              if (h2.error){
                if(/userScripts|user scripts|disabled|permission/i.test(h2.error))window.__acUsOk=false;
                respond({error:h2.error});
              } else if (h2.dedup){
                respond({result:void 0},!0);
              }
              // ok → the result arrives via acUserApiRes (hnd2)
            });
          }, 6000);
        }
      });
    });
  };
}});
/**
 * Evaluate a z-bundle funcCode with the ACtl bridge in scope.
 * @param {object} ACtl — the ACtl API object (user-script world)
 * @param {string} funcCode — function source to evaluate
 * @param {Array} [args] — arguments to call it with
 * @param {*} [ch] — unused legacy channel param
 * @returns {*} the function result
 */
const B=(ACtl,funcCode,args,ch)=>{let f=FN(funcCode,ACtl);return f(...(args||[]))};
// AC-MV3 FIX (2026-08-05): dedupe acUserApi/acMainWorld messages by id. The
// USER_SCRIPT world's postMessage can be delivered to MORE THAN ONE file42
// listener (double-injected file42 contexts; each scripting.executeScript
// creates a new isolated VM) → the SW would execute the same API call twice
// (e.g. setClipboard's K serialization: the 1st K does `delete window[e]`,
// the 2nd reads undefined → clipboard overwritten with "undefined" — the
// intermittent "text did not match: undefined" in the API test, runs 3/5).
// Remember recent ids (30 s TTL, 200 cap) — a fresh script run always gets
// a fresh id, so legitimate calls are never dropped.
const __acSeen=new Map();
// AC-MV3 FIX (2026-08-06): dedupe identical z-bundle deliveries (u() funcCode
// branch) — the same (funcCode,args) can arrive twice ~1ms apart; share the
// in-flight promise instead of re-running (setClipboard "undefined" fix).
const __acFnDedup=new Map();
/**
 * Dedupe acUserApi/acMainWorld messages by id (30 s TTL, 200 cap) — a
 * USER_SCRIPT postMessage can reach more than one file42 listener.
 * @param {string} id — message id
 * @returns {boolean} true if the id is fresh (should be processed)
 */
const __acOnce=function(id){
  if(!id)return!0;
  const t=__acSeen.get(id),now=Date.now();
  if(t&&now-t<3E4)return!1;
  __acSeen.set(id,now);
  if(2E2<__acSeen.size){const it=__acSeen.keys();__acSeen.delete(it.next().value)}
  return!0;
};
// AC-MV3 FIX (2026-08-02, round 11): runInPageCtx bridge — the USER_SCRIPT
// world requests MAIN-world injection via chrome.userScripts (bypasses page
// CSP inline checks). Relay: USER_SCRIPT -> postMessage(acMainWorld) ->
// file42 -> runtime.sendMessage(execMainWorld) -> SW __acInjectCode ->
// userScripts.execute({world:'MAIN'}) -> result back the same way.
window.addEventListener("message",function(ev){
  var d=ev.data;
  if(d&&d.type=="acMainWorld"){
    document.__acF42T=Date.now(); // liveness heartbeat (see guard above)
    if(!__acOnce(d.id))return; // duplicate delivery — ignore
    m.runtime.sendMessage({type:"execMainWorld",code:d.code},function(h){
      h=h||{};
      window.postMessage({type:"acMainWorldRes",id:d.id,result:h.result,error:h.error},"*");
    });
  }
});
// ACtl bridge: userAPI requests from the USER_SCRIPT world → SW; results back.
window.addEventListener("message",function(ev){
  var d=ev.data;
  if(d&&d.type=="acUserApi"){
    document.__acF42T=Date.now(); // liveness heartbeat (see guard above)
    if(!__acOnce(d.id))return; // duplicate delivery — ignore
    /* AC-MV3 DIAG (2026-08-06): log every acUserApi arrival — shows whether
    the USER_SCRIPT world really posts twice (same props+args, fresh ids). */
    try{console.warn('[AC-F42] api rcvd id='+d.id+' props='+String(d.props&&d.props[0])+' args0='+String(d.args&&d.args[0]).slice(0,40))}catch(x){}
    var t0api=performance.now();
    var c=x.__cur||{};
    v({type:"userAPI",scriptId:d.scriptId||c.scriptId,props:d.props,args:d.args,targetTabs:c.targetTabs,trigInstId:c.trigInstId},function(h){
      h=h||{};
      if(h.error)return window.postMessage({type:"acUserApiRes",id:d.id,error:h.error},"*");
      // AC-MV3 FIX (2026-08-02, round 5): ACtl.on is handled LOCALLY in the
      // USER_SCRIPT world (its result is a pending event Promise — cannot
      // be cloned through postMessage). This registration round-trip is
      // fire-and-forget: skip the z-bundle evaluation entirely.
      if(d.local){// AC-MV3 DIAG (2026-08-05): ACtl.on registration round-trip
        // latency — the SW-side "on" case (tab resolution + _Vj registration)
        // must complete BEFORE the tabLoadEnd event fires, else the event is
        // lost (no buffering) → the 8s test timeout. Logs the total time.
        try{console.warn('[AC-F42] api local (on-reg) id='+d.id+' +'+(performance.now()-t0api).toFixed(0)+'ms')}catch(e){}
        return window.postMessage({type:"acUserApiRes",id:d.id,result:null},"*");
      }
      // AC-MV3 FIX (2026-08-02): SW may respond with a z-BUNDLE {funcCode,
      // args} — captureTab → z(J,[map]), on → z(fn,[FUNC]), getTabInfo →
      // z(J,[...]), pubVar/switchState similar. The original C() proxy
      // evaluated these here; the acUserApi relay just forwarded
      // result/error → the user script received undefined ("(intermediate
      // value) is not iterable"). Evaluate now, await nested FN promises,
      // and only post concrete data (postMessage cannot clone a Promise).
      // Dedup guard: run under a UNIQUE trigInstId (~api) so execUserFunc
      // is not deduped against the parent run (the main key
      // tabId:scriptId:trigInstId is still in-flight while the script
      // awaits its API call).
      var saved=x.__cur;
      var l;
      try{
        // AC-MV3 FIX (2026-08-02, round 6): UNIQUE per-call suffix — a
        // static '~api' would collide with the next nested call within the
        // SW dedup LRU TTL (15s) and be rejected as a post-hoc duplicate.
        x.__cur=saved?Object.assign({},saved,{trigInstId:(saved.trigInstId||"")+"~"+(Math.random()+"").slice(2)}):{scriptId:d.scriptId};
        /* AC-MV3 DIAG (2026-08-06): is the SW response a z-bundle? The 10:47
        log showed TWO execUserFunc for one setClipboard (funcCode branch +
        relay) — this tells whether the relay path really evaluates one. */
        try{console.warn('[AC-F42] relay resp '+(h&&h.funcCode?'ZBUNDLE':'plain')+' props='+String(d.props&&d.props[0]))}catch(x){}
        l=h.funcCode?FN(h.funcCode)(...h.args):h.result;
      }finally{x.__cur=saved}
      var pr=Promise.resolve();
      if(l&&"function"==typeof l.then)pr=l.then(F=>{l=F});
      pr=pr.then(()=>{
        if(l&&"object"==typeof l&&Symbol.iterator in l){
          var ps=[];
          for(let [t,q]of l.entries?l.entries():l)
            if(q&&q.funcCode&&q.args){
              l[t]=FN(q.funcCode)(...q.args);
              if(l[t]&&"function"==typeof l[t].then)ps.push(l[t].then(F=>{l[t]=F}));
            }
          return Promise.all(ps);
        }
      });
      pr.then(()=>window.postMessage({type:"acUserApiRes",id:d.id,result:l},"*"),
              e2=>window.postMessage({type:"acUserApiRes",id:d.id,error:String(e2&&e2.message||e2)},"*"));
    });
  }
});
let y=!m.runtime||!m.runtime.onMessage;if(y)window.addEventListener("message",a=>u(a.data,g=>parent.postMessage({pongId:a.data.pingId,result:g},"*")),!1);else{let a=(c,d)=>{let b=location.ancestorOrigins.length;switch(c){case "depth":return b==d;case "mindepth":return b>=d;case "maxdepth":return b<=d}},g=(c,d)=>d.RE?RegExp(d.RE,d.F).test(location[c]):location[c]==d,e=c=>{for(let d in c){let b=d.toLowerCase();if(!(b.endsWith("depth")?a:b in location?g:()=>!1)(b,c[d]))return!1}return!0};m.runtime.onMessage.addListener((c,d,b)=>{if(c.frmCBId)e(c.frmFlt)?u(c,w=>{v({pongId:c.frmCBId,result:w},()=>{})}):v({pongId:c.frmCBId,result:null},()=>{});/* AC-MV3 frame guard: skip runScript in iframes */else if(c.scriptId&&location.ancestorOrigins.length>0)return false;else{var _r=u(c,b);/* AC-MV3 DIAG (2026-08-06): does the listener answer ASYNC for funcCode messages? undefined here means the channel closes immediately → n() sees no response → retry → dedup-hit cascade (setClipboard first-try null). true/Promise = channel stays open until sendResponse. */if(c&&c.funcCode){try{console.warn('[AC-F42] listener ret='+String(_r).slice(0,40)+' prop='+String(c.args&&c.args[0]).slice(0,40)+' trig='+String(c&&c.trigInstId).slice(0,70))}catch(_q){}}return _r}})}let x={},r={};{let a={};window.runInPageCtx=(g,e)=>(c=()=>{})=>{void 0===e&&([g,
e]=[e,g]);if(g){if(a[g])return c();a[g]=!0}let d=document.createElement("script");"string"==typeof e?(d.src=e,d.onload=function(){this.remove();c({})},d.onerror=function(b){g&&delete a[g];this.remove();c({error:b.error||`Unable to load URL "${e}"`})},document.head.appendChild(d)):(d.textContent="function"==typeof e?`(${e})()`:e.code,document.head.appendChild(d),d.remove())}}})()}
