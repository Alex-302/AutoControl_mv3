'use strict';
const ASYNC2 = ()=>{} ;

const wildcardObj = new Proxy(()=> wildcardObj, {get: (obj, prop)=> prop==Symbol.toPrimitive ? ()=>'' : obj[prop] || wildcardObj }) ;

const get = (sel, ctx=document)=> ctx.querySelector(sel) ;
const getAll = (sel, ctx=document)=> ctx.querySelectorAll(sel) ;

function getOne(...args){
	try{
		return get(...args) || wildcardObj ;
	}catch(e){
		return wildcardObj ;
	}
}

function listenEvt(evtNames, selector, func){
	evtNames.trim().replace(/\s+/g, ' ').split(' ').forEach( evtName =>{
		document.addEventListener(evtName, evt =>{
			let hndlrTarget = evt.target ;
			if( !selector || (hndlrTarget = hndlrTarget.closest(selector)) )
				func.call(hndlrTarget, evt) ;
		}) ;
	}) ;
}

function isArray(arg){ return Array.isArray(arg) }

function initLoadDemo(evt={}){
	this.className = 'loading' ;
	loadScriptIfAbsent( window.demoBuilderFile || 'demoBuilder.min.js' )(()=> loadDemo(this, evt) ) ;
}

function loadCss(href, onload){
    let cssElem = document.createElement('LINK') ;
    cssElem.rel = 'stylesheet' ;
	cssElem.href = href ;
    cssElem.addEventListener('load', onload) ;
	return document.head.appendChild(cssElem) ;
}

function loadCssIfAbsent(url){ return (callback = ()=>{})=>{
	document.querySelector(`link[rel=stylesheet][href='${url}']`)
	?	callback()
	:	loadCss(url, callback) ;
}}

function makeScriptElem(src, onload){
    let scriptElem = document.createElement('SCRIPT') ;
    scriptElem.src = src ;
    scriptElem.isLoaded = false ;
    scriptElem.addEventListener('load', ()=>{ scriptElem.isLoaded=true ; onload && onload() }) ;
	return scriptElem ;
}

function loadScript(url, callback){
	document.head.appendChild( makeScriptElem(url, callback) ) ;
}

function loadScriptIfAbsent(url){ return ( callback = ()=>{} )=>{
	let elem = get(`script[src='${url}']`) ;
	if( !elem )
		loadScript(url, callback) ;
	else if( elem.isLoaded==null || elem.isLoaded )
		callback() ;
	else
		elem.addEventListener('load', callback) ;
}}

let loadDataFromFile = filePath => callback =>{
	window._ = undefined ;
	loadScript(filePath, ()=>{
		callback(window._) ;
		window._ = undefined ;
	}) ;
} ;

function loadAutomatDemos(){
	Array.from( getAll('demoPH[load]') ).forEach( elem => initLoadDemo.call(elem) ) ;
}

listenEvt('click', 'demoPH', initLoadDemo) ;
listenEvt('DOMContentLoaded', '', loadAutomatDemos) ;
listenEvt('click', 'a[install]', function(evt){
	//let winVer = +((navigator.userAgent || '').match(/Windows NT ([\d.]+)/i) || [])[1] ;
	let winVer = +((navigator.userAgent||'').match(/Windows NT ([\d.]+)/i) || 0)[1] ;
	if( !( 5.1 <= winVer && winVer < 11 && (/^win/i).test(navigator.platform) ) ){
		evt.preventDefault() ;
		showConfirm(`
			You don't seem to be using a supported operating system. <hr b=2>
			Currently, AutoControl is supported on: <hr b>
			&nbsp; &nbsp;&#9655;&nbsp; Windows XP  <br>
			&nbsp; &nbsp;&#9655;&nbsp; Windows Vista  <br>
			&nbsp; &nbsp;&#9655;&nbsp; Windows 7  <br>
			&nbsp; &nbsp;&#9655;&nbsp; Windows 8/8.1  <br>
			&nbsp; &nbsp;&#9655;&nbsp; Windows 10  <br>
			&nbsp; &nbsp;&#9655;&nbsp; Windows 11  <br>
			<hr b=2>
			Please read the <a href="faq.htm">FAQ</a> to learn why this limitation exists. <hr b=2>
			Do you still want to continue? <hr b>
		`).then( answer =>{
			if( answer )
				location = this.href ;
		})
	}
}) ;

listenEvt('click', 'acs a', evt => evt.target.closest('[dwnld]') || evt.preventDefault()) ;
listenEvt('click', 'acs button[value]', function(evt){
	if( get('ACtlExt[ver]') ){
		const msg = `This will add "<b>${this.closest('acs').querySelector('tit').innerText}</b>" to <br> your AutoControl settings. <hr b=2> Continue?` ;
		Promise.resolve( this.value!='imprtSttgs' || showConfirm(msg) ).then( goOn =>{
			if( goOn )
				this.dispatchEvent(new Event('webSettgs', {bubbles: true})) ;
		})
	}else{
		showAlert(`
			AutoControl is not installed. <br>
			You need AutoControl version 2023.11.26 or newer in <br> order to use this feature. <hr b=3>
			Click on the yellow button at the top of the page to <br> install AutoControl.
		`) ;
	}
}) ;

let MOUSE_X, MOUSE_Y ;
listenEvt('mousedown', '', evt =>{ MOUSE_X = evt.clientX, MOUSE_Y = evt.clientY }) ;

let htmlToDom = html => new DOMParser().parseFromString(html, 'text/html').body.firstChild ;

let showDialogBox = (msg, btns)=> new Promise(callback =>{
	let dialogElem = htmlToDom(`
		<dialog>
			<msg>${msg}</msg>
			<btns>${Object.keys(btns).map( btnName => `<button name="${btnName}">${btns[btnName]}</button>` ).join('')}</btns>
		</dialog>
	`) ;
	dialogElem.callback = callback ;
	document.body.appendChild(dialogElem) ;
	const margin = 25 ;
	dialogElem.style.left = Math.max(margin, Math.min(MOUSE_X - dialogElem.offsetWidth/2, window.innerWidth - dialogElem.offsetWidth - margin))+'px' ;
	dialogElem.style.top = Math.max(margin, Math.min(MOUSE_Y - dialogElem.offsetHeight/2, window.innerHeight - dialogElem.offsetHeight - margin))+'px' ;
	dialogElem.showModal() ;
}) ;

listenEvt('click', 'dialog button', function(){
	let dialog = this.closest('dialog') ;
	dialog.close() ;
	dialog.remove() ;
	dialog.callback(this.name) ;
}) ;

let showAlert = msg => showDialogBox(msg, {ok:'OK'}) ;
let showConfirm = msg => showDialogBox(msg, {yes:'Yes', no:'No'}).then( answer => answer=='yes' ) ;
