var date0 = "2015-11-01";
var dateFormat = 'YYYY-MM-DD';
var connected = false;
var reconnect;
var reconnectRetries = 0;
var reconnectCount = 0;
var GAS_price = 1;
var ETH_dec = 8;
var avatarEmpty = 'avatarEmpty.png';
var avatarError = 'avatarError.png';
var aliasEmpty = 'unnamed';
var appStatusMessages = {synchronizing:'Synchronizing with network', connecting:'Connecting to network', ok:''};

$(document).ready(init);

function init() 
{
    window.onerror = function(errorMessage, errorUrl, errorLine){alert('Error: ' + errorMessage + ' Script: ' + errorUrl + ' Line: ' + errorLine);};
	initUI();
    event.Ready.connect(this, function(){
        pageStart();

    });
    initAccounts();
	initSend();
	initReceive();
	initAddressbook();
	initTransactions();
	initBitprofile();
	initNewAddress();
	initEditAddress();
	initExportAddress();
	initImportAddress() ;
//	reconnectCount = 0;
//	reconnect = setInterval(connectSlots, 1000);
}

function pageStart()
{
	pageOff("page_splash");
	setTimeout(function(){ $('body').addClass('loaded'); }, 150);
	setTimeout(startBitprofilePage, 1000);
	//setTimeout(changePage, 1000, "page_newAddress", 0);
	//setTimeout(changePage, 1000, "page_addressbook");
	
	//changePage("page_newAddress",0);
	//changePage("page_settings");
}

//We use this function because connect statements resolve their target once, imediately
//not at signal emission so they must be connected once the XETH object has been added to the frame
//! <!--  [ connect slots ] -->
function connectSlots()
{
	if ( !connected && typeof XETH !== "undefined" ) {
		clearInterval(reconnect);
		connected = true;
		
		XETH.pageStart.connect(this, pageStart);
		
		XETH.setGASPrice.connect(this, setGASPrice);
		
		XETH.appStatusLoader.connect(this, appStatusLoader);
		XETH.appStatusMessage.connect(this, appStatusMessage);
		XETH.appStatusLoaderTime.connect(this, appStatusLoaderTime);
		XETH.appStatusIcon_secure.connect(this, appStatusIcon_secure);
		XETH.appStatusIcon_network.connect(this, appStatusIcon_network);
		XETH.appStatusIcon_updated.connect(this, appStatusIcon_updated);
		
		//XETH.updateProfile.connect(this, updateProfile);
		XETH.updateBitprofiles.connect(this, updateBitprofiles);
		XETH.addBitprofile.connect(this, addBitprofile);
		XETH.editBitprofile.connect(this, editBitprofile);
		XETH.bitprofileCreateSuccessful.connect(this, bitprofileCreateSuccessful);
		XETH.bitprofileEditSuccessful.connect(this, bitprofileEditSuccessful);
		XETH.bitprofileCreateError.connect(this, bitprofileCreateError);
		XETH.bitprofileEditError.connect(this, bitprofileEditError);
		XETH.bitprofileImportError.connect(this, bitprofileImportError);
		XETH.bitprofileImportSuccessful.connect(this, bitprofileImportSuccessful);
		XETH.bitprofileExportSuccessful.connect(this, bitprofileExportSuccessful);
		
		XETH.updateAccounts.connect(this, updateAccounts);
		XETH.addAccount.connect(this, addAccount);
		XETH.updateAccountBalance.connect(this, updateAccountBalance);
		//XETH.updateAccountStealth.connect(this, updateAccountStealth);
		XETH.newAddressError.connect(this, newAddressError);
		XETH.newAddressSuccessful.connect(this, newAddressSuccessful);
		XETH.editAddressError.connect(this, editAddressError);
		XETH.editAddressSuccessful.connect(this, editAddressSuccessful);
		XETH.exportAddressError.connect(this, exportAddressError);
		XETH.exportAddressSuccessful.connect(this, exportAddressSuccessful);
		XETH.importAddressError.connect(this, importAddressError);
		XETH.importAddressSuccessful.connect(this, importAddressSuccessful);
		
		XETH.updateContacts.connect(this, updateContacts);
		XETH.addContact.connect(this, addContact);
		XETH.updateContactAlias.connect(this, updateContactAlias);
		XETH.updateContactTransactions.connect(this, updateContactTransactions);
		XETH.removeContact.connect(this, removeContact);
		
		XETH.updateTransactions.connect(this, updateTransactions);
		XETH.addTransaction.connect(this, addTransaction);
		XETH.updateTransactionsContact.connect(this, updateTransactionsContact);
		
		XETH.sentError.connect(this, sentError);
		XETH.clipboardPaste.connect(this, clipboardPaste);
		XETH.sentSuccessful.connect(this, sentSuccessful);
		
		//pageStart();
		XETH.UIReady();
	} else {
		reconnectCount++;
		
		if(reconnectCount>=reconnectRetries)
		{
			clearInterval(reconnect);
//			test();
		}
	}
	
	console.log('connecting '+reconnect);
}
//! <!--  [ connect slots ] -->

//These will function as the recieving "slots" for the update signals

/*
function updateProfile(_avatar, _alias, _bitprofile)
{
	var _myProfile = $('.myProfile');
	_myProfile.find('.avatar .img img').attr('src',_avatar);
	_myProfile.find('.name').html(_alias);
	_myProfile.find('.bitprofileIcon').toggleClass('on',_bitprofile);
	
}
*/
function setGASPrice(_price)
{
	GAS_price = _price;
}

function notifySuccess(_msg)
{
	notie.alert(1, _msg, 5.0);
}

function checkNotifyError(_obj, _msg)
{
	for(var index in _obj) 
	{ 
		if(_obj[index]==true)
		{
			console.log(_obj[index]);
			notifyError(_msg);
			return true;
		}
	}
}

function notifyError(_msg)
{
	notie.alert(3, _msg, 5.0);
}

function navNotifyNew(_target)
{
	/*
	var _nr = (_target.attr("new"))? Number(_target.attr("new")) : 0;
	_target.attr("new",_nr+1);*/
	var _nr = 0;
	var _new = _target.find('.new');
	
	if(_new.length>0)
	{
		_nr = Number(_new.text());
		_new.text(_nr+1);
	}
	else
	{
		_target.append($('<span class="new">1</span>'));
		_new = _target.find('.new');
		//_new.addClass('show');
		window.setTimeout( function(){ _new.addClass('show'); } , 500 );
	}
}

function navNotifyNone(_target)
{
	_target.find('.new').removeClass('show');
	window.setTimeout( function(){ _target.find('.new').remove(); } , 1500 );
	/*_target.find('.new').stop().animate(
		{ opacity: 0 }, {
		duration: 1000,
		delay: 500,
		complete: function() { _target.find('.new').remove(); }
	});*/
}

function checkAvatar(_avatar)
{
	return (_avatar)? _avatar : avatarEmpty;
}

function errorAvatar(_target)
{
	_target.attr('original', _target.attr('src'));
	_target.attr('src', avatarError);
}

function checkAlias(_alias)
{
	return (_alias)? _alias : aliasEmpty;
}
/*
function checkAvatarFile(_url)
{
	
    var http = new XMLHttpRequest();

	try
	{
		http.open('HEAD', _url, false);
		http.send();
		console.log(_url, http.status);
	}
	catch(err)
	{
		alert(_url);
    	return avatarError;
	}
	finally
	{
		return _url;
	}
	
	//return $.get(_url).done(function(){return _url;}).fail(function(){return avatarError;});
}
*/
function appStatusIcon_secure(_status)
{
	appStatusIcon('secure', _status);
}
function appStatusIcon_network(_status)
{
	appStatusIcon('network', _status);
}
function appStatusIcon_updated(_status)
{
	appStatusIcon('updated', _status);
}
function appStatusIcon(_icon, _status)
{
	$('.footer .icons .'+_icon).toggleClass('ok', _status);
}

function appStatusMessage(_msg)
{
	$('.footer .status .message').text(appStatusMessages[_msg]);
}
function appStatusLoader(_percent)
{
	$('.footer .status .loader .value').css('width', _percent+'%');
	$('.footer .status').attr('loader', _percent);
}
function appStatusLoaderTime(_time)
{
	var _txt = '';
	if(_time>0)
	{
		_txt = convertTime(_time)+' behind';
	}
	
	$('.footer .status .loader .txt').text(_txt);
}

function convertTime(_time)
{
	var _days = _time/24;
	
	if(Math.floor(_time)<=1)
	{
		return "a few minutes"
	}
	else if(_days>=2)
	{
		return Math.floor(_days)+" days";
	}
	else if(Math.floor(_days)==1)
	{
		return "1 day";
	}
	else
	{
		return Math.floor(_time)+" hours";
	}
}

function saveFile(_type, _data, _filename)
{
	var _types = ['text/plain', 'image/png', 'image/octet-stream'];
	var fileAsBlob = new Blob([_data], {type:_types[_type]});
	if(_type==2) _filename += ".png";
	
	var downloadLink = document.createElement("a");
	downloadLink.download = _filename;
	downloadLink.innerHTML = "Save File";
	alert(downloadLink.download); 
	if (window.webkitURL != null)
	{
		// Chrome allows the link to be clicked
		// without actually adding it to the DOM.
		downloadLink.href = (_type>0)? _data : window.webkitURL.createObjectURL(fileAsBlob);
	}
	else
	{
		// Firefox requires the link to be added to the DOM
		// before it can be clicked.
		downloadLink.href = (_type>0)? _data : window.URL.createObjectURL(fileAsBlob);
		downloadLink.onclick = function(event){ document.body.removeChild(event.target); };
		downloadLink.style.display = "none";
		document.body.appendChild(downloadLink);
	}
	
	alert('href \n'+downloadLink.href); 

	downloadLink.click();
}
