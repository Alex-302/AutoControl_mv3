'use strict';

const hostExtId = 'lkaihdpfpifdlgoapbfocpmekbokmcfd' ;

// AC-MV3 FIX (2026-08-08): MV3 service workers are LAZY — this SW does not
// run at browser start, so the old one-shot getTitle check never sent
// TBBtnInit until the button was clicked (icons stayed default). Now: request
// the configured title/icon on onStartup/onInstalled AND retry until
// AutoControl answers (its SW may still be starting — native handshake /
// engine deploy takes seconds). Retries stop once btnProps arrives
// (__gotProps) or a custom title is already set (getTitle != manifest name).
let __gotProps = false ;
let __initStarted = false ;

/**
 * Request the configured title/icon from AutoControl (TBBtnInit) and retry
 * until it answers or a custom title is already set. The MV3 SW is lazy, so
 * this runs on onStartup/onInstalled and retries every 2 s (max ~60 s).
 */
function requestInit(){
	if( __gotProps || __initStarted ) return ;
	__initStarted = true ;
	let attempts = 0 ;
	const maxAttempts = 30 ;                 // ~60s at 2s intervals
	(function tryOnce(){
		if( __gotProps ) return ;
		chrome.action.getTitle({}, title => {
			if( __gotProps ) return ;
			if( title == chrome.runtime.getManifest().name ){
				chrome.runtime.sendMessage( hostExtId, 'TBBtnInit', ()=>chrome.runtime.lastError ) ;
				if( ++attempts < maxAttempts )
					setTimeout( tryOnce, 2000 ) ;
			}
		}) ;
	})() ;
}


chrome.action.onClicked.addListener(()=>{
	chrome.runtime.sendMessage(hostExtId, 'TBBtnClick', response =>{
		if( !response && chrome.runtime.lastError )
			chrome.tabs.query({lastFocusedWindow:true, active:true}, ([tab])=> chrome.tabs.discard(tab.id) ) ;
	}) ;
}) ;

chrome.runtime.onMessageExternal.addListener( (message, sender, sendResponse)=>{
	if(sender.id != hostExtId) return ;
	if(message=='ping'){
		sendResponse('pong') ;
	}else if(message.type=='btnProps'){
		__gotProps = true ;
		if(message.title)
			chrome.action.setTitle({title: message.title}) ;
		if(message.icon)
			chrome.action.setIcon({imageData: new ImageData(new Uint8ClampedArray(message.icon.data), message.icon.width, message.icon.height)}) ;
		if(message.badge)
			chrome.action.setBadgeText({text: message.badge}) ;
		if(message.badgeColor)
			chrome.action.setBadgeBackgroundColor({color: message.badgeColor}) ;
	}
}) ;

chrome.runtime.onStartup.addListener( requestInit ) ;
chrome.runtime.onInstalled.addListener( requestInit ) ;
chrome.action.getTitle({}, title => title==chrome.runtime.getManifest().name && requestInit() ) ;
