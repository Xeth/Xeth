var connected = false;
var reconnect;
var reconnectRetries = 0;
var reconnectCount = 0;
var GAS_price = 1;
var ETH_dec = 8;

$(document).ready(init);

function init() 
{
	initUI();
	initAccounts();
	initSend();
	initReceive();
	initAddressbook();
	initTransactions();
	initBitprofile();
	
	reconnectCount = 0;
	reconnect = setInterval(connectSlots, 1000);
	//test();
}

function test()
{
	alert('test');
	window.location.href = "#page_send";
		
	updateAccounts([
		{address:"000address000", balance:0.0},
		{address:"address01", balance:12.08},
		{address:"02address", balance:0}]);
	
	addAccount({address:"address333", balance:0.650031});
	addAccount({address:"address3sdfsd33", balance:0});
		
	updateProfile('http://oi68.tinypic.com/i539z7.jpg', 'John Peterson', false);
	
	setGASPrice(0.000000055);
	
	updateContacts([
		{avatar:'http://oi63.tinypic.com/30t13dj.jpg', alias:'John Peterson', bitprofile:false, address:'address01', transactions:0},
		{avatar:'http://oi68.tinypic.com/i539z7.jpg', alias:'Ion Bitprofileanu', bitprofile:'ion_bitprofileanu', address:'02address', transactions:685}]);
	
	addContact({avatar:'avatar1-01.png', alias:'Michael Deprofiler', address:'address333', transactions:100});
	
	updateTransactions([
		{avatar:'http://oi63.tinypic.com/30t13dj.jpg', alias:'John Peterson', bitprofile:'false', address:'address01', type:'received', amount:12.08, hash:'0xcc5151b5737ae3ffdea1a8bdd5d54cce33bc6e8905ccd954c6c830b25abcddfd', time:'2008-07-17 09:24:17'},
		{avatar:'http://oi68.tinypic.com/i539z7.jpg', alias:'Ion Bitprofileanu', bitprofile:'ion_bitprofileanu', address:'02address', type:'sent', amount:0.650031, hash:'0x3f905231b37a4763b733ffa5bdd45cb5f17e17b98855581c147532f123eb3545', time:'2015-11-05 10:46:30'}]);
		
	addTransaction({avatar:'http://oi68.tinypic.com/i539z7.jpg', alias:'Ion Bitprofileanu2', address:'address333', type:'sent', amount:0.001, hash:'0x1265sa31b37a4763b733ffa5bdd45cb5f17e17b98855581c147532f123eb3545', time:'2015-11-07 13:32:00'});
		
	//toggleSendError(false, true, true);
	
}

function pageStart()
{
    window.location.href = "#page_transactions";
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
		
		//XETH.updateProfile.connect(this, updateProfile);
		
		XETH.updateAccounts.connect(this, updateAccounts);
		XETH.addAccount.connect(this, addAccount);
		
		XETH.updateContacts.connect(this, updateContacts);
		XETH.addContact.connect(this, addContact);
		XETH.updateContactAlias.connect(this, updateContactAlias);
		XETH.updateContactTransactions.connect(this, updateContactTransactions);
		
		XETH.updateTransactions.connect(this, updateTransactions);
		XETH.addTransaction.connect(this, addTransaction);
		
		XETH.toggleSendError.connect(this, toggleSendError);
		XETH.clipboardPaste.connect(this, clipboardPaste);
		XETH.sentSuccessful.connect(this, sentSuccessful);
		
		//pageStart();
		XETH.UIReady();
	} else {
		reconnectCount++;
		
		if(reconnectCount>=reconnectRetries)
		{
			clearInterval(reconnect);
			test();
		}
	}
	
	console.log('connecting '+reconnect);
}
//! <!--  [ connect slots ] -->

//These will function as the recieving "slots" for the update signals
function updateProfile(_avatar, _alias, _bitprofile)
{
	var _myProfile = $('.myProfile');
	_myProfile.find('.avatar .img img').attr('src',_avatar);
	_myProfile.find('.name').html(_alias);
	_myProfile.find('.bitprofileIcon').toggleClass('on',_bitprofile);
	
}

function setGASPrice(_price)
{
	GAS_price = _price;
}

function notifySuccess(_msg)
{
	notie.alert(1, _msg, 5.0);
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