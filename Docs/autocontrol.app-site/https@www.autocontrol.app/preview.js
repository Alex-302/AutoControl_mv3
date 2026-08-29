const SLIDES = [
	{files:['img/previewSlide1.png'], html: (files)=> `<img src="${files[0]}"><a more href="triggers.htm">Learn more</a>`},
	{files:['img/previewSlide2.png'], html: (files)=> `<img src="${files[0]}">`},
	{files:['img/previewSlide3.png'], html: (files)=> `<img src="${files[0]}">`},
	{files:['img/previewSlide4.png'], html: (files)=> `<img src="${files[0]}"><a more href="custom-toolbar-buttons">Learn more</a>`},
	{files:['img/previewSlide5.png'], html: (files)=> `<img src="${files[0]}"><a more href="switch-to-last-used-tab-in-chrome#tab-switcher" style="left: 40px">Learn more</a>`},
] ;

function preloadImage(url){ return new Promise((onSuccess, onError)=>{
	let img = new Image ;
	img.onload = function(){ onSuccess(this) } ;
	img.onerror = function(){ onError(this) } ;
	img.src = url ;
})}

let lastCallTime = 0 ;
function showSlide(newIdx, relativeIdx=false){
	if( Date.now() - lastCallTime < 400 ) return ;
	loadScriptIfAbsent('jquery-2.2.4.min.js')(()=>{
		$('preview slide[off]').remove() ;
		let $currSlide = $('preview slide') ;
		const currIdx = +$currSlide.attr('idx') ;
		let [inDir, outDir] = newIdx > currIdx ? ['rgt', 'lft'] : ['lft', 'rgt'] ;
		if( relativeIdx ){
			if( (newIdx > currIdx) != (newIdx > 0) )
				[inDir, outDir] = [outDir, inDir] ;
			newIdx = (SLIDES.length + currIdx + newIdx) % SLIDES.length ;
		}
		let slideData = SLIDES[newIdx] ;
		Promise.all( slideData.files.map( filePath => preloadImage(filePath) ) ).then(()=>{
			let $newSlide = $(makeSlideHtml(newIdx)).attr('off', inDir).appendTo('preview slides') ;
			requestAnimationFrame(()=> setTimeout(()=>{
				$currSlide.attr('off', outDir) ;
				$newSlide.attr('off',null) ;
				$(`preview seltrs > it:-webkit-any(.active,[idx='${newIdx}'])`).toggleClass('active') ;
				lastCallTime = Date.now() ;
			})) ;
		}) ;
	}) ;
}

function makeSlideHtml(slideIdx){
	return `<slide idx=${slideIdx}>${SLIDES[slideIdx].html(SLIDES[slideIdx].files)}</slide>` ;
}

listenEvt('DOMContentLoaded', '', ()=>{
	get('preview seltrs').innerHTML = SLIDES.map((_,idx)=> `<it idx=${idx} class="${idx?'':'active'}"></it>`).join('') ;
	get('preview slides').innerHTML = makeSlideHtml(0) ;
	setInterval(()=>{
		if( !document.querySelector('preview > :-webkit-any(slides,btn):hover, preview seltrs:hover') )
			showSlide(1, true) ;
	}, 5000) ;
}) ;

listenEvt('click', 'preview > btn', function(){
	showSlide(this.hasAttribute('frwd') ? 1 : -1, true) ;
}) ;

listenEvt('click', 'preview seltrs > it:not(.active)', function(){
	showSlide(+this.getAttribute('idx')) ;
}) ;

