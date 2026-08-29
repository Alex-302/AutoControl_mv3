let mark = false ;
Prism.hooks.add('wrap', env =>{
	if(env.type=='maybe-class-name' && env.content=='ACtl'){
		env.attributes.actl = '' ;
		return mark = true ;
	}
	if(env.type=='punctuation' && env.content=='.')
		return ;
	if((env.type=='method' || env.type=='constant') && mark){
		env.tag = 'a' ;
		env.attributes.href = './' + env.content + '.htm' ;
		env.attributes.acApi = '' ;
	}

	mark = false ;
});
Prism.languages.js.identifier = /[$_a-z][$\w]*/i ;
Prism.languages.insertBefore('js', 'operator', {propLiteral: {lookbehind:true, pattern: /([{,]\s*)[$_a-z][$\w]*(?=\s*:)/i } } ) ;

listenEvt('click', 'code [actl]', function(){ this.nextElementSibling.nextElementSibling.click() }) ;

let pageCache = {}, currPagePath = location.pathname ;

function loadPage(urlObj, pushState){
	let updateState = (path, fragment, title)=>{
		getOne('apiMenu [selected]').removeAttribute('selected') ;
		getOne(`apiMenu a[href='${path}']`).setAttribute('selected','') ;
		currPagePath = path ;
		document.title = title ;
		if(pushState)
			history.pushState(null, title, path+fragment) ;
		getOne(fragment || 'h1').scrollIntoView(true) ;
	} ;

	let oldContCol = get('contCol') ;
	pageCache[currPagePath] = {title: document.title, cont: oldContCol} ;

	let cache = pageCache[urlObj.pathname] ;
	if(cache){
		oldContCol.parentElement.replaceChild(cache.cont, oldContCol) ;
		updateState(urlObj.pathname, urlObj.hash, cache.title) ;
	}else{
		showBusySign() ;
		urlObj = new URL(urlObj.href) ; //clone the object to avoid modifying the passed argument
		urlObj.search = 'mode=content' ;
		fetch(urlObj.href)
		.then( res => res.text() )
		.then( contHtml =>{
			showBusySign(false) ;
			if( !contHtml || /<!doctype|^\s*<html/i.test(contHtml) ){ // сервер не поддержал mode=content — обычный переход
				location.href = urlObj.href ;
				return ;
			}
			oldContCol.insertAdjacentHTML('afterend',contHtml) ;
			oldContCol.remove() ;
			let newTitle = get('body title').innerText ;
			get('body title').remove() ;
			updateState(urlObj.pathname, urlObj.hash, newTitle) ;
			Prism.highlightAll() ;
			loadAutomatDemos() ;
		})
		.catch( err =>{ // fetch недоступен (file:// и т.п.) — обычный переход
			showBusySign(false) ;
			location.href = urlObj.href ;
		}) ;
	}
}

listenEvt('click', 'a[href^="../scripting"], a[locRef]', function(evt){
	//console.log('LINK CLICK:', this.pathname) ;
	if(evt.button!=0 || evt.ctrlKey || evt.shiftKey) return ;
	if(location.protocol=='file:') return ; // локально fetch запрещён — обычная навигация
	if(this.pathname!=location.pathname)
		loadPage(this, true) ;
	evt.preventDefault() ;
}) ;
window.onpopstate = evt =>{
	//console.log('HISTORY', location.pathname) ;
	loadPage(location) ;
}

let apiMenu ;
listenEvt('scroll', '', ()=>{
	if(!apiMenu) apiMenu = get('apiMenu') ;

	let boundRect = apiMenu.getBoundingClientRect() ;

	let topGap = boundRect.top ;
	if(topGap > 0){
		apiMenu.style.top = Math.max(0, parseFloat(apiMenu.style.top || 0) - topGap ) + 'px' ;
		return ;
	}
	let bottomGap = Math.min(window.innerHeight, apiMenu.parentElement.getBoundingClientRect().bottom) - boundRect.bottom ;
	if(bottomGap > 0)
		apiMenu.style.top = parseFloat(apiMenu.style.top || 0) + Math.min(bottomGap, -topGap) + 'px' ;
}) ;

function showBusySign(state=true){
	if( !state )
		getOne('busySign').remove() ;
	else if( !get('busySign') )
		document.body.insertAdjacentHTML('beforeend', '<busySign float><i></i><i></i><i></i><i></i><i></i><i></i><i></i><i></i><i></i><i></i><i></i><i></i></busySign>') ;
}
