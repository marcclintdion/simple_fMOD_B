(function(){var g=void 0,h=null,k=!1,m,n=this;function q(a){a=a.split(".");for(var b=n,c;c=a.shift();)if(b[c]!=h)b=b[c];else return h;return b}
function r(a){var b=typeof a;if("object"==b)if(a){if(a instanceof Array)return"array";if(a instanceof Object)return b;var c=Object.prototype.toString.call(a);if("[object Window]"==c)return"object";if("[object Array]"==c||"number"==typeof a.length&&"undefined"!=typeof a.splice&&"undefined"!=typeof a.propertyIsEnumerable&&!a.propertyIsEnumerable("splice"))return"array";if("[object Function]"==c||"undefined"!=typeof a.call&&"undefined"!=typeof a.propertyIsEnumerable&&!a.propertyIsEnumerable("call"))return"function"}else return"null";
else if("function"==b&&"undefined"==typeof a.call)return"object";return b}function s(a){return"string"==typeof a}var aa="closure_uid_"+(1E9*Math.random()>>>0),ba=0;function ca(a,b,c){return a.call.apply(a.bind,arguments)}function da(a,b,c){if(!a)throw Error();if(2<arguments.length){var d=Array.prototype.slice.call(arguments,2);return function(){var c=Array.prototype.slice.call(arguments);Array.prototype.unshift.apply(c,d);return a.apply(b,c)}}return function(){return a.apply(b,arguments)}}
function t(a,b,c){t=Function.prototype.bind&&-1!=Function.prototype.bind.toString().indexOf("native code")?ca:da;return t.apply(h,arguments)}function u(a,b){var c=a.split("."),d=n;!(c[0]in d)&&d.execScript&&d.execScript("var "+c[0]);for(var e;c.length&&(e=c.shift());)!c.length&&b!==g?d[e]=b:d=d[e]?d[e]:d[e]={}}function v(a,b){function c(){}c.prototype=b.prototype;a.s=b.prototype;a.prototype=new c}
Function.prototype.bind=Function.prototype.bind||function(a,b){if(1<arguments.length){var c=Array.prototype.slice.call(arguments,1);c.unshift(this,a);return t.apply(h,c)}return t(this,a)};var y=Array.prototype,ea=y.indexOf?function(a,b,c){return y.indexOf.call(a,b,c)}:function(a,b,c){c=c==h?0:0>c?Math.max(0,a.length+c):c;if(s(a))return!s(b)||1!=b.length?-1:a.indexOf(b,c);for(;c<a.length;c++)if(c in a&&a[c]===b)return c;return-1},z=y.forEach?function(a,b,c){y.forEach.call(a,b,c)}:function(a,b,c){for(var d=a.length,e=s(a)?a.split(""):a,f=0;f<d;f++)f in e&&b.call(c,e[f],f,a)};
function fa(a,b){var c;t:{c=a.length;for(var d=s(a)?a.split(""):a,e=0;e<c;e++)if(e in d&&b.call(g,d[e],e,a)){c=e;break t}c=-1}return 0>c?h:s(a)?a.charAt(c):a[c]}function ga(a){return y.concat.apply(y,arguments)}function ha(a){var b=a.length;if(0<b){for(var c=Array(b),d=0;d<b;d++)c[d]=a[d];return c}return[]}function ia(a,b,c){return 2>=arguments.length?y.slice.call(a,b):y.slice.call(a,b,c)};function ja(a){var b=A,c;for(c in b)if(a.call(g,b[c],c,b))return c};var B,C,D,F;function ka(){return n.navigator?n.navigator.userAgent:h}F=D=C=B=k;var G;if(G=ka()){var la=n.navigator;B=0==G.indexOf("Opera");C=!B&&-1!=G.indexOf("MSIE");D=!B&&-1!=G.indexOf("WebKit");F=!B&&!D&&"Gecko"==la.product}var I=C,J=F,ma=D;function na(){var a=n.document;return a?a.documentMode:g}var K;
t:{var L="",M;if(B&&n.opera)var N=n.opera.version,L="function"==typeof N?N():N;else if(J?M=/rv\:([^\);]+)(\)|;)/:I?M=/MSIE\s+([^\);]+)(\)|;)/:ma&&(M=/WebKit\/(\S+)/),M)var oa=M.exec(ka()),L=oa?oa[1]:"";if(I){var pa=na();if(pa>parseFloat(L)){K=String(pa);break t}}K=L}var qa=K,ra={};
function sa(a){if(!ra[a]){for(var b=0,c=String(qa).replace(/^[\s\xa0]+|[\s\xa0]+$/g,"").split("."),d=String(a).replace(/^[\s\xa0]+|[\s\xa0]+$/g,"").split("."),e=Math.max(c.length,d.length),f=0;0==b&&f<e;f++){var p=c[f]||"",l=d[f]||"",E=RegExp("(\\d*)(\\D*)","g"),H=RegExp("(\\d*)(\\D*)","g");do{var w=E.exec(p)||["","",""],x=H.exec(l)||["","",""];if(0==w[0].length&&0==x[0].length)break;b=((0==w[1].length?0:parseInt(w[1],10))<(0==x[1].length?0:parseInt(x[1],10))?-1:(0==w[1].length?0:parseInt(w[1],10))>
(0==x[1].length?0:parseInt(x[1],10))?1:0)||((0==w[2].length)<(0==x[2].length)?-1:(0==w[2].length)>(0==x[2].length)?1:0)||(w[2]<x[2]?-1:w[2]>x[2]?1:0)}while(0==b)}ra[a]=0<=b}}var ta=n.document,ua=!ta||!I?g:na()||("CSS1Compat"==ta.compatMode?parseInt(qa,10):5);if(J||I){var O;if(O=I)O=I&&9<=ua;O||J&&sa("1.9.1")}I&&sa("9");function va(){var a,b,c,d;a=document;if(a.querySelectorAll&&a.querySelector)return a.querySelectorAll(".yt-player");if(a.getElementsByClassName){var e=a.getElementsByClassName("yt-player");return e}e=a.getElementsByTagName("*");d={};for(b=c=0;a=e[b];b++){var f=a.className;"function"==typeof f.split&&0<=ea(f.split(/\s+/),"yt-player")&&(d[c++]=a)}d.length=c;return d}function wa(a,b){for(var c=0;a;){if(b(a))return a;a=a.parentNode;c++}return h};function xa(a){a=String(a);if(/^\s*$/.test(a)?0:/^[\],:{}\s\u2028\u2029]*$/.test(a.replace(/\\["\\\/bfnrtu]/g,"@").replace(/"[^"\\\n\r\u2028\u2029\x00-\x08\x0a-\x1f]*"|true|false|null|-?\d+(?:\.\d*)?(?:[eE][+\-]?\d+)?/g,"]").replace(/(?:^|:|,)(?:[\s\u2028\u2029]*\[)+/g,"")))try{return eval("("+a+")")}catch(b){}throw Error("Invalid JSON string: "+a);}function ya(){}
function P(a,b,c){switch(typeof b){case "string":za(b,c);break;case "number":c.push(isFinite(b)&&!isNaN(b)?b:"null");break;case "boolean":c.push(b);break;case "undefined":c.push("null");break;case "object":if(b==h){c.push("null");break}if("array"==r(b)){var d=b.length;c.push("[");for(var e="",f=0;f<d;f++)c.push(e),P(a,b[f],c),e=",";c.push("]");break}c.push("{");d="";for(e in b)Object.prototype.hasOwnProperty.call(b,e)&&(f=b[e],"function"!=typeof f&&(c.push(d),za(e,c),c.push(":"),P(a,f,c),d=","));
c.push("}");break;case "function":break;default:throw Error("Unknown type: "+typeof b);}}var Aa={'"':'\\"',"\\":"\\\\","/":"\\/","\b":"\\b","\f":"\\f","\n":"\\n","\r":"\\r","\t":"\\t","\x0B":"\\u000b"},Ba=/\uffff/.test("\uffff")?/[\\\"\x00-\x1f\x7f-\uffff]/g:/[\\\"\x00-\x1f\x7f-\xff]/g;function za(a,b){b.push('"',a.replace(Ba,function(a){if(a in Aa)return Aa[a];var b=a.charCodeAt(0),e="\\u";16>b?e+="000":256>b?e+="00":4096>b&&(e+="0");return Aa[a]=e+b.toString(16)}),'"')};function Q(){}Q.prototype.k=k;Q.prototype.dispose=function(){this.k||(this.k=!0,this.i())};Q.prototype.i=function(){if(this.w)for(;this.w.length;)this.w.shift()()};function R(){this.a=[];this.b={}}v(R,Q);R.prototype.u=1;R.prototype.h=0;function Ca(a,b,c,d){var e=a.b[b];e||(e=a.b[b]=[]);var f=a.u;a.a[f]=b;a.a[f+1]=c;a.a[f+2]=d;a.u=f+3;e.push(f)}function Da(a,b,c){var d=S;if(a=d.b[a]){var e=d.a;(a=fa(a,function(a){return e[a+1]==b&&e[a+2]==c}))&&Ea(d,a)}}function Ea(a,b){if(0!=a.h)a.d||(a.d=[]),a.d.push(b);else{var c=a.a[b];if(c){if(c=a.b[c]){var d=ea(c,b);0<=d&&y.splice.call(c,d,1)}delete a.a[b];delete a.a[b+1];delete a.a[b+2]}}}
R.prototype.v=function(a,b){var c=this.b[a];if(c){this.h++;for(var d=ia(arguments,1),e=0,f=c.length;e<f;e++){var p=c[e];this.a[p+1].apply(this.a[p+2],d)}this.h--;if(this.d&&0==this.h)for(;c=this.d.pop();)Ea(this,c);return 0!=e}return k};R.prototype.i=function(){R.s.i.call(this);delete this.a;delete this.b;delete this.d};var Fa=RegExp("^(?:([^:/?#.]+):)?(?://(?:([^/?#]*)@)?([^/#?]*?)(?::([0-9]+))?(?=[/#?]|$))?([^?#]+)?(?:\\?([^#]*))?(?:#(.*))?$");function Ga(a){if(Ha){Ha=k;var b=n.location;if(b){var c=b.href;if(c&&(c=(c=Ga(c)[3]||h)&&decodeURIComponent(c))&&c!=b.hostname)throw Ha=!0,Error();}}return a.match(Fa)}var Ha=ma;function Ia(a,b,c){if("array"==r(b))for(var d=0;d<b.length;d++)Ia(a,String(b[d]),c);else b!=h&&c.push("&",a,""===b?"":"=",encodeURIComponent(String(b)))};function Ja(a,b){return a.dataset?a.dataset[Ka(b)]:a.getAttribute("data-"+b)}var La={};function Ka(a){return La[a]||(La[a]=String(a).replace(/\-([a-z])/g,function(a,c){return c.toUpperCase()}))};var Ma=q("yt.dom.getNextId_");if(!Ma){Ma=function(){return++Na};u("yt.dom.getNextId_",Ma);var Na=0};u("yt.config_",window.yt&&window.yt.config_||{});u("yt.tokens_",window.yt&&window.yt.tokens_||{});u("yt.globals_",window.yt&&window.yt.globals_||{});u("yt.msgs_",window.yt&&window.yt.msgs_||{});u("yt.timeouts_",window.yt&&window.yt.timeouts_||[]);var Oa=window.yt&&window.yt.intervals_||[];u("yt.intervals_",Oa);function Pa(a){"function"==r(a)&&(a=Qa(a));a=window.setInterval(a,250);Oa.push(a);return a}
function Qa(a){return window.yterr?function(){try{return a.apply(this,arguments)}catch(b){var c=q("yt.www.onException");c&&c(b);throw b;}}:a};function Ra(a){if(a=a||window.event){for(var b in a)b in Sa||(this[b]=a[b]);this.scale=a.scale;this.rotation=a.rotation;if((b=a.target||a.srcElement)&&3==b.nodeType)b=b.parentNode;this.target=b;if(b=a.relatedTarget)try{b=b.nodeName&&b}catch(c){b=h}else"mouseover"==this.type?b=a.fromElement:"mouseout"==this.type&&(b=a.toElement);this.relatedTarget=b;this.clientX=a.clientX!=g?a.clientX:a.pageX;this.clientY=a.clientY!=g?a.clientY:a.pageY;if(document.body&&document.documentElement){b=document.body.scrollLeft+
document.documentElement.scrollLeft;var d=document.body.scrollTop+document.documentElement.scrollTop;this.pageX=a.pageX!=g?a.pageX:a.clientX+b;this.pageY=a.pageY!=g?a.pageY:a.clientY+d}this.keyCode=a.keyCode?a.keyCode:a.which;this.charCode=a.charCode||("keypress"==this.type?this.keyCode:0);this.altKey=a.altKey;this.ctrlKey=a.ctrlKey;this.shiftKey=a.shiftKey;"MozMousePixelScroll"==this.type?(this.wheelDeltaX=a.axis==a.HORIZONTAL_AXIS?a.detail:0,this.wheelDeltaY=a.axis==a.HORIZONTAL_AXIS?0:a.detail):
window.opera?(this.wheelDeltaX=0,this.wheelDeltaY=a.detail):0==a.wheelDelta%120?"WebkitTransform"in document.documentElement.style?window.a&&0==navigator.platform.indexOf("Mac")?(this.wheelDeltaX=a.wheelDeltaX/-30,this.wheelDeltaY=a.wheelDeltaY/-30):(this.wheelDeltaX=a.wheelDeltaX/-1.2,this.wheelDeltaY=a.wheelDeltaY/-1.2):(this.wheelDeltaX=0,this.wheelDeltaY=a.wheelDelta/-1.6):(this.wheelDeltaX=a.wheelDeltaX/-3,this.wheelDeltaY=a.wheelDeltaY/-3)}}m=Ra.prototype;m.type="";m.target=h;
m.relatedTarget=h;m.currentTarget=h;m.data=h;m.keyCode=0;m.charCode=0;m.altKey=k;m.ctrlKey=k;m.shiftKey=k;m.clientX=0;m.clientY=0;m.pageX=0;m.pageY=0;m.wheelDeltaX=0;m.wheelDeltaY=0;m.rotation=0;m.scale=1;var Sa={stopPropagation:1,preventMouseEvent:1,preventManipulation:1,preventDefault:1,layerX:1,layerY:1,scale:1,rotation:1};var A=q("yt.events.listeners_")||{};u("yt.events.listeners_",A);var Ta=q("yt.events.counter_")||{count:0};u("yt.events.counter_",Ta);function Ua(a,b,c){return ja(function(d){return d[0]==a&&d[1]==b&&d[2]==c&&d[4]==k})}
function Va(a,b,c){if(a&&(a.addEventListener||a.attachEvent)){var d=Ua(a,b,c);if(!d){var d=++Ta.count+"",e=!(!("mouseenter"==b||"mouseleave"==b)||!a.addEventListener||"onmouseenter"in document),f;f=e?function(d){d=new Ra(d);if(!wa(d.relatedTarget,function(b){return b==a}))return d.currentTarget=a,d.type=b,c.call(a,d)}:function(b){b=new Ra(b);b.currentTarget=a;return c.call(a,b)};f=Qa(f);A[d]=[a,b,c,f,k];a.addEventListener?"mouseenter"==b&&e?a.addEventListener("mouseover",f,k):"mouseleave"==b&&e?a.addEventListener("mouseout",
f,k):"mousewheel"==b&&"MozBoxSizing"in document.documentElement.style?a.addEventListener("MozMousePixelScroll",f,k):a.addEventListener(b,f,k):a.attachEvent("on"+b,f)}}}function Wa(a){"string"==typeof a&&(a=[a]);z(a,function(a){if(a in A){var c=A[a],d=c[0],e=c[1],f=c[3],c=c[4];d.removeEventListener?d.removeEventListener(e,f,c):d.detachEvent("on"+e,f);delete A[a]}})};var Xa={},Ya=[],S=new R;function Za(){z(Ya,function(a){a()})}function $a(a,b){S.v.apply(S,arguments)};function T(a,b){this.b=b;this.i=this.a=h;this.d=this.id=0;this.k=this.h=h;var c=s(a)?document.getElementById(a):a;if(c){if("iframe"!=c.tagName.toLowerCase()){for(var d=c,e=document.createElement("iframe"),d=d.attributes,f=0,p=d.length;f<p;f++){var l=d[f].value;l!=h&&(""!=l&&"null"!=l)&&e.setAttribute(d[f].name,l)}e.setAttribute("frameBorder",0);e.setAttribute("allowfullscreen",1);e.setAttribute("title","YouTube "+U(this.b,"title"));(d=U(this.b,"width"))&&e.setAttribute("width",d);(d=U(this.b,"height"))&&
e.setAttribute("height",d);d=this.p();d.enablejsapi=window.postMessage?1:0;window.location.host&&(d.origin=window.location.protocol+"//"+window.location.host);var f=U(this.b,"host")+this.q()+"?",p=[],E;for(E in d)Ia(E,d[E],p);p[0]="";e.src=f+p.join("");this.i=c;(E=c.parentNode)&&E.replaceChild(e,c);c=e}this.a=c;this.id=this[aa]||(this[aa]=++ba);this.a.id&&(Xa[this.a.id]=this);if(window.postMessage){this.h=new R;ab(this);var c=U(this.b,"events"),H;for(H in c)c.hasOwnProperty(H)&&this.addEventListener(H,
c[H])}}}m=T.prototype;m.K=function(){this.a.id&&(Xa[this.a.id]=h);var a=this.h;a&&"function"==typeof a.dispose&&a.dispose();if(this.i){var a=this.a,b=a.parentNode;b&&b.replaceChild(this.i,a)}else(a=this.a)&&a.parentNode&&a.parentNode.removeChild(a);V&&(V[this.id]=h);this.b=h;var a=this.a,c;for(c in A)A[c][0]==a&&Wa(c);this.i=this.a=h};function ab(a){bb(a.b,a,a.id);a.d=Pa(t(a.t,a));Va(a.a,"load",t(function(){window.clearInterval(this.d);this.d=Pa(t(this.t,this))},a))}m.p=function(){return{}};
m.t=function(){this.a&&this.a.contentWindow?cb(this,{event:"listening"}):window.clearInterval(this.d)};m.A=function(a){this.g(a.event,a)};m.addEventListener=function(a,b){var c=b;"string"==typeof b&&(c=function(){window[b].apply(window,arguments)});Ca(this.h,a,c);W(this,"addEventListener",[a]);return this};m.g=function(a,b){if(!this.h.k){var c={target:this,data:b};this.h.v(a,c);this.k&&$a(this.k+"."+a,c)}};
function W(a,b,c){c=c||[];c=Array.prototype.slice.call(c);cb(a,{event:"command",func:b,args:c})}function cb(a,b){b.id=a.id;var c;c=[];P(new ya,b,c);c=c.join("");var d=Ga(a.a.src),e=d[1],f=d[2],p=d[3],d=d[4],l="";e&&(l+=e+":");p&&(l+="//",f&&(l+=f+"@"),l+=p,d&&(l+=":"+d));a.a.contentWindow.postMessage(c,l)}m.M=function(a,b){this.a.width=a;this.a.height=b;return this};m.L=function(){return this.a};var db={0:"onEnded",1:"onPlaying",2:"onPaused",3:"onBuffering",5:"onVideoCued"};var eb="corp.google.com youtube.com youtube-nocookie.com prod.google.com sandbox.google.com docs.google.com drive.google.com play.google.com".split(" ");var fb=window.YTConfig||{};function X(a){this.b=a||{};this.a={};this.a.width=640;this.a.height=390;this.a.title="";this.a.host=("https:"==document.location.protocol?"https:":"http:")+"//www.youtube.com"}var V=h;function U(a,b){for(var c=[a.b,fb,a.a],d=0;d<c.length;d++){var e=c[d][b];if(e!=g)return e}return h}function bb(a,b,c){V||(V={},Va(window,"message",t(a.d,a)));V[c]=b}
X.prototype.d=function(a){if(a.origin==U(this,"host")||RegExp("^https?://([a-z0-9-]{1,63}\\.)*("+eb.join("|").replace(/\./g,".")+")(:[0-9]+)?([/?#]|$)","i").test(a.origin)){var b;try{b=xa(a.data)}catch(c){return}(a=V[b.id])&&a.A(b)}};function gb(a){X.call(this,a);this.a.title="video player";this.a.videoId=""}v(gb,X);function Y(a,b){T.call(this,a,new gb(b));this.k="player";this.o={};this.j={}}v(Y,T);function hb(a){if("iframe"!=a.tagName.toLowerCase()){var b=a.getAttribute("videoid")||Ja(a,"videoid");if(b){var c=a.getAttribute("width")||Ja(a,"width"),d=a.getAttribute("height")||Ja(a,"height");new Y(a,{videoId:b,width:c,height:d})}}}m=Y.prototype;m.q=function(){return"/embed/"+U(this.b,"videoId")};m.p=function(){return U(this.b,"playerVars")||{}};
m.A=function(a){switch(a.event){case "onReady":window.clearInterval(this.d);this.g("onReady");break;case "onStateChange":var b=a.info.playerState;Z(this,a);this.g("onStateChange",b);db[b]&&this.g(db[b]);break;case "onPlaybackQualityChange":Z(this,a);this.g("onPlaybackQualityChange",this.o.playbackQuality);break;case "onPlaybackRateChange":Z(this,a);this.g("onPlaybackRateChange",this.o.playbackRate);break;case "onNewLicenseSession":this.g("onNewLicenseSession",a.sessionInfo);break;case "onError":this.g("onError",
a.error);break;case "onApiChange":a=a.info||{};for(b in a)this.j[b]=a[b];this.g("onApiChange");break;case "infoDelivery":Z(this,a);break;case "initialDelivery":this.o={};this.j={};ib(this,a.apiInterface);Z(this,a);break;case "onFullScreenToggleRequest":this.g("onFullScreenToggleRequest");break;default:Z(this,a),this.g(a.event,a.info)}};function Z(a,b){var c=b.info||{},d;for(d in c)a.o[d]=c[d]}
function ib(a,b){z(b,function(a){this[a]||(0==a.search("cue")||0==a.search("load")?this[a]=function(){this.o={};this.j={};W(this,a,arguments);return this}:0==a.search("get")||0==a.search("is")?this[a]=function(){var b=0;0==a.search("get")?b=3:0==a.search("is")&&(b=2);return this.o[a.charAt(b).toLowerCase()+a.substr(b+1)]}:this[a]=function(){W(this,a,arguments);return this})},a)}
m.J=function(){var a=this.a.cloneNode(k),b=this.o.videoData,c=U(this.b,"host");a.src=b&&b.video_id?c+"/embed/"+b.video_id:a.src;b=document.createElement("div");b.appendChild(a);return b.innerHTML};m.I=function(a){return!this.j.namespaces?[]:!a?this.j.namespaces||[]:this.j[a].options||[]};m.H=function(a,b){if(this.j.namespaces&&a&&b)return this.j[a][b]};function jb(a){X.call(this,a);this.a.host="https://www.youtube.com";this.a.title="upload widget";this.a.height=0.67*U(this,"width")}v(jb,X);function $(a,b){T.call(this,a,new jb(b))}v($,T);m=$.prototype;m.q=function(){return"/upload_embed"};m.p=function(){var a={},b=U(this.b,"webcamOnly");b!=h&&(a.webcam_only=b);return a};m.g=function(a,b){$.s.g.call(this,a,b);"onApiReady"==a&&W(this,"hostWindowReady")};m.C=function(a){W(this,"setVideoDescription",arguments)};
m.D=function(a){W(this,"setVideoKeywords",arguments)};m.F=function(a){W(this,"setVideoPrivacy",arguments)};m.B=function(a){W(this,"setParentVideoId",arguments)};m.G=function(a){W(this,"setVideoTitle",arguments)};u("YT.PlayerState.UNSTARTED",-1);u("YT.PlayerState.ENDED",0);u("YT.PlayerState.PLAYING",1);u("YT.PlayerState.PAUSED",2);u("YT.PlayerState.BUFFERING",3);u("YT.PlayerState.CUED",5);u("YT.UploadWidgetEvent.API_READY","onApiReady");u("YT.UploadWidgetEvent.UPLOAD_SUCCESS","onUploadSuccess");u("YT.UploadWidgetEvent.PROCESSING_COMPLETE","onProcessingComplete");u("YT.UploadWidgetEvent.STATE_CHANGE","onStateChange");u("YT.UploadWidgetState.IDLE",0);u("YT.UploadWidgetState.PENDING",1);
u("YT.UploadWidgetState.ERROR",2);u("YT.UploadWidgetState.PLAYBACK",3);u("YT.UploadWidgetState.RECORDING",4);u("YT.UploadWidgetState.STOPPED",5);u("YT.get",function(a){return Xa[a]});u("YT.scan",Za);u("YT.subscribe",function(a,b,c){Ca(S,a,b,c)});u("YT.unsubscribe",function(a,b,c){Da(a,b,c)});u("YT.Player",Y);u("YT.UploadWidget",$);T.prototype.destroy=T.prototype.K;T.prototype.setSize=T.prototype.M;T.prototype.getIframe=T.prototype.L;T.prototype.addEventListener=T.prototype.addEventListener;
Y.prototype.getVideoEmbedCode=Y.prototype.J;Y.prototype.getOptions=Y.prototype.I;Y.prototype.getOption=Y.prototype.H;$.prototype.setParentVideoId=$.prototype.B;$.prototype.setVideoDescription=$.prototype.C;$.prototype.setVideoKeywords=$.prototype.D;$.prototype.setVideoPrivacy=$.prototype.F;$.prototype.setVideoTitle=$.prototype.G;var kb=q("onYTReady");kb&&kb();var lb=q("onYouTubeIframeAPIReady");lb&&lb();var mb=q("onYouTubePlayerAPIReady");mb&&mb();
Ya.push(function(){var a=ha(document.getElementsByTagName("yt:player")),b;b=document;b=b.querySelectorAll&&b.querySelector?b.querySelectorAll(".yt-player"):b.getElementsByClassName?b.getElementsByClassName("yt-player"):va();b=ha(b);z(ga(a,b),hb)});Za();})();
