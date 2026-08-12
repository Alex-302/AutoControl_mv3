'use strict';

const hostExtId = 'lkaihdpfpifdlgoapbfocpmekbokmcfd' ;

chrome.browserAction.onClicked.addListener(()=>{
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
		if(message.title)
			chrome.browserAction.setTitle({title: message.title}) ;
		if(message.icon)
			chrome.browserAction.setIcon({imageData: new ImageData(new Uint8ClampedArray(message.icon.data), message.icon.width, message.icon.height)}) ;
		if(message.badge)
			chrome.browserAction.setBadgeText({text: message.badge}) ;
		if(message.badgeColor)
			chrome.browserAction.setBadgeBackgroundColor({color: message.badgeColor}) ;
	}
}) ;

chrome.browserAction.getTitle({}, title => title==chrome.runtime.getManifest().name && chrome.runtime.sendMessage(hostExtId, 'TBBtnInit') ) ;
