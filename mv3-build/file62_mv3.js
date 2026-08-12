'use strict';try{_Yk.browserAction&&_Yk.browserAction.onClicked.addListener(()=>{_ru("brwrAction","trigActId")(a=>{a&&_ek?_6y(a):_sh()})})}catch(e){}_Yk.windows.getLastFocused({populate:!0,windowTypes:_Ge},a=>{_4t=_ji(a,"id");_Np=_js(_ji(a,"tabs",0)||{})});_Yk.tabs.onCreated.addListener(_Zf);
function _Zf(a){let b=a.id=_js(a);_ea.push(b);_Yp[b]=a;a.openerTabId&&(_He[b]=a.openerTabId,Object.keys(_He).length.in(50,75,100,150,200,300)&&_Fu(()=>{for(let c in _He)(_He[c]=_gg(_Yp[c],"openerTabId"))||delete _He[c];for(let c in _He)c in _Yp||delete _He[c]}));a.active||_0k(b,a.windowId);_Wo(_Ui,b)}
{let a=_so(400,_5s);_Yk.tabs.onRemoved.addListener(b=>{b==_Np&&(_Np=null);_0k(b,0);_ea.remove(b);_Ft.remove(b);delete _da[b];delete _Hs[b];_dg.push({id:b,time:Date.now()/1E3});a();_Wo(_5k,b);_Fy&&(_m[b]=_zh(_Yp[b]),setTimeout(()=>{delete _m[b]},3E3))})}function _Cp(a,b,c){b=a.indexOf(b);~b&&(a[b]=c)}function _ew(a,b,c){b in a&&(a[c]=a[b],delete a[b])}let _se;
// Tab replacement
_Yk.tabs.onReplaced.addListener((a,b)=>{_Lk(_Mu,[b,a]);_Np==b&&(_Np=a);_Cp(_ea,b,a);_Cp(_Ft,b,a);_ew(_Yp,b,a);_ew(_da,b,a);_ew(_Hs,b,a);_ew(_He,b,a);for(let [c,d]of _He)d==b&&(_He[c]=a);for(let [,c]of _Mo)_Cp(c,b,a);_se||(_se={});_se[b]=a});
// Tab activation: track active tab per window
// AC-MV3 FIX (2026-08-08): `_cd[c]` may be undefined when the native is
// dead (window enum never ran — _cd stays empty) → `e.activeTab=f` threw
// "Cannot set properties of undefined (setting 'activeTab')" (user VM
// 00:18, right after openOptionsPage from Emergency Repair). Bail out
// early; the window gets tracked once the enum populates _cd.
{let a=0;_Yk.tabs.onActivated.addListener(({tabId:b,windowId:c})=>{var d=Date.now()-0;_1f(c,b,d);(d=c==_4t)&&(_Np=b);const e=_cd[c];if(!e)return;let f=_Yp[b];f||(f=_Yp[b]={id:b,windowId:c,window:e});const g=_Yw(e);_Vg[b]&&1E3<Date.now()-a&&(delete _Vg[b],g&&"about:blank"==_zh(f)&&(_Lk(_Dt,[_Yo,_Yo|_mk,_cs,_Uo,_Uo|_mk,_cs|_mk,_ye,_ye|_mk]),a=Date.now()));c=_ji(e,"activeTab","id");/* AC-MV3 FIX (2026-08-08): keep _Yp[].active flags in sync with reality — _Ph skips activation when e.active is true, and the flag was only refreshed by _Fu (window enum). A stale active=true on a previously-active tab made wrap transitions (rightTabWrap/leftTabWrap) skip that tab AND left _Np stale → the next trigger targeted the same tab → skipped wheel step. Reset the old activeTab's flag here and set the new one (onActivated is the source of truth). */c&&_Yp[c]&&(_Yp[c].active=!1);e.activeTab=f;f.active=!0;_qp(b,!d);c!=b&&(_Wo(_4r,c),g&&_Wo(_Ed,c));setTimeout(()=>{_Wo(_pw,b);g&&_Wo(_vp,b)},80)})}let _kk;
function _au(a,b){_kk&&(3E3>Math.abs(Date.now()-_kk)&&b.startsWith("https://www.google.com/url?q=")&&(b=decodeURIComponent(b.substr(29)),_wj(a,{code:`location.replace(${JSON.stringify(b)}) ; document.body.style.opacity=0`})()),_kk=0)}
// Tab URL/status updates
{let a={},b;_Yk.tabs.onUpdated.addListener((c,d)=>{let e="loading"==d.status?_oe:"complete"==d.status?_Fd:d.discarded?_oi:d.audible?_I:!1===d.audible?_Iw:0;if(e==_oi){if(c==b){b=null;return}b=c}d.url&&(c==_Np&&_Ja(d.url),_lf(_Yp,c).url=d.url,_kk&&_au(c,d.url),_Wo(_Gp,c));if(e){e==_oe&&c in _da&&(_Hs[c]=Date.now(),_Yk.tabs.getZoom(c,f=>{_yd(f,2)!=_da[c]&&_hr(c,_da[c],!0)}));if(e==_oe){a[c]=setTimeout(()=>{delete a[c];_Wo(e,c)},10);return}if(e==_Fd&&a[c]){clearTimeout(a[c]);return}_Wo(e,c)}_5g&&d.favIconUrl&&
(d=_ig(_zh(_Yp[c])),delete _7o[d],_Zs(d)(_ay));e==_Fd&&_rr&&_Lk(_Ww,{tabId:c});e==_Fd&&(new URL(_zh(_Yp[c]))).hostname==_mo&&_Zr(c)})}
function _Zr(a){_wj(a,{code:`(${(function(b){let c=d=>d&&chrome.runtime.sendMessage({[d.value]:decodeURI(d.closest("a").href)});window._ACtlExt||addEventListener("webSettgs",d=>c(d.target));window._ACtlExt=document.querySelector("ACtlExt")||document.head.appendChild(document.createElement("ACtlExt"));window._ACtlExt.setAttribute("ver",b);c(document.querySelector("a [value=redirSttgs]"))})})(${JSON.stringify("2025.4.22")})`})()}
// Tab attached to different window
_Yk.tabs.onAttached.addListener((a,b)=>{_lf(_Yp,a).windowId=b.newWindowId});

// Window event handlers
_Yk.windows.onFocusChanged.addListener(a=>{_na[a]||!_cd[a]&&!_Ld[a]||(_Ld[a]&&delete _Ld[a],_8u([a])())});
_Yk.windows.onCreated.addListener(_yh);
function _yh(a){a.cTime=Date.now();clearTimeout(_6i);_n.push(a.id);_cd[a.id]=a;a.state.in("normal","maximized")&&(a.prevState=a.state);_8u([a.id])();_Wo(_wf,a.id)}
_Yk.windows.onRemoved.addListener(_q);
function _fy(a){_n.remove(a);_hd.remove(a);_0o(a,null);delete _cd[a];a==_4t&&_Yk.windows.getLastFocused({windowTypes:_Ge},b=>_4t=_Aw()?null:b.id)}
function _q(a){_fy(a);_Wo(_Ff,a)}
// Display change
_Yk.system.display&&_Yk.system.display.onDisplayChanged.addListener(()=>{_Sf(()=>_iy())});
// Update available + idle
{let a;_Yk.runtime.onUpdateAvailable.addListener(()=>{_2u(2)&&_co(2);a=!0});_Yk.idle.onStateChanged.addListener(b=>{"active"!=b&&setTimeout(()=>_Yk.idle.queryState(60,c=>{"active"!=c&&(a?_co(2):!_mw()&&_dh&&864E5<Date.now()-_dh?_co(1):_r||_Lk(_Na))}),1E3*(15*Math.random()+5)|0)})}
// Sessions
if(_Yk.sessions){let a=_Yk.sessions.onChanged;a.addListener(_ay);a.removeListener(_ay)}
// Context menu
_Yk.contextMenus.onClicked.addListener(_cg(function*(a){if("reloadExtn"==a.menuItemId){a=yield _Vy(_ya);let b=yield _Vt(),c={allWinIds:b.map(d=>d.id),idToHndl:_na,hndlToId:_Or,actionQueue:_2y};a&&!a.actWinMine&&(c.focusedId=(b.filter(d=>d.focused)[0]||{}).id,c.lastFocusId=((yield d=>_Yk.windows.getLastFocused({windowTypes:_Ge},d))||{}).id,c.focusedId==c.lastFocusId&&(delete c.lastFocusId,_na[c.focusedId]==a.focusWin&&delete c.focusedId),c.hijackedWins=Object.keys(_Ld));_9k("diagnostics",c.add(a));
_co(1,!0)}else a.menuItemId.startsWith("binSwtch")&&_2t(a.menuItemId,a.checked)}));
// Extension installed/updated
_Yk.runtime.onInstalled.addListener(_cg(function*(a){if("update"==a.reason&&"2025.4.22"!=a.previousVersion){yield _Eu.wait();let b=yield _ad();b.errorCount=yield _dk();_Ot("update",b.add({prevVersion:a.previousVersion}));_F(a.previousVersion,"2021.4.5")}}));
// External messages
_Yk.runtime.onMessageExternal.addListener((a,b,c)=>{b=_gj.indexOf(b.id);if(0<=b)switch(a){case "TBBtnInit":_ve(b);break;case "TBBtnClick":_Wo(_At+b),c(!0)}});
// Initialize switches
_Oo(_Du);
