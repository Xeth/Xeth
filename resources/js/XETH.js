var XETH = {
	
	// signals
	testSignal: 
	{
		connect: function(){},
		dispatch: function(){console.log("testSignal", arguments.length, arguments[0]);}
	},
	pageStart: 
	{
		connect: function(){},
		dispatch: function(){pageStart();}
	},
	
	setGASPrice: 
	{
		connect: function(){},
		dispatch: function(_price){setGASPrice(_price);}
	},
	
	updateProfile: 
	{
		connect: function(){},
		dispatch: function(_avatar, _name, _bitprofile){updateProfile(_avatar, _name, _bitprofile);}
	},
	
	updateAccounts: 
	{
		connect: function(){},
		dispatch: function(_list){updateAccounts(_list);}
	},
	addAccount: 
	{
		connect: function(){},
		dispatch: function(_data){addAccount(_data);}
	},
	
	updateContacts: 
	{
		connect: function(){},
		dispatch: function(_list){updateContacts(_list);}
	},
	addContact: 
	{
		connect: function(){},
		dispatch: function(_data){addContact(_data);}
	},
	updateContactAlias: 
	{
		connect: function(){},
		dispatch: function(_data){updateContactAlias(_data);}
	},
	updateContactTransactions: 
	{
		connect: function(){},
		dispatch: function(_data){updateContactTransactions(_data);}
	},
	
	updateTransactions: 
	{
		connect: function(){},
		dispatch: function(_list){updateTransactions(_list);}
	},
	addTransaction: 
	{
		connect: function(){},
		dispatch: function(_data){addTransaction(_data);}
	},
	
	toggleSendError: 
	{
		connect: function(){},
		dispatch: function(_err){toggleSendError(_err);}
	},
	clipboardPaste: 
	{
		connect: function(){},
		dispatch: function(_data){clipboardPaste(_data);}
	},
	sentSuccessful: 
	{
		connect: function(){},
		dispatch: function(){sentSuccessful();}
	},
	
	// public
	UIReady: function(){
		console.log("XETH.UIReady:\n");
		
		XETH.testSignal.dispatch('test');
		XETH.setGASPrice.dispatch(0.000000055);
		//XETH.updateProfile.dispatch('http://oi68.tinypic.com/i539z7.jpg', 'John Peterson', false);
		
		XETH.updateAccounts.dispatch([
			{address:"0x092a5172f796d4c3cd0e03520134317fc25b74f6", balance:0, stealth:true},
			{address:"0x69d48e1d37d76d0be85be0bc717cad59644d9098", balance:12.08, stealth:true},
			{address:"0xfo2dc172f796d4c3cd0e03520134317fc25b75d1", balance:0.0}]);
	
		XETH.addAccount.dispatch({address:"0xdu258e1d37d76d0be85be0bc717cad59644d5fnb", balance:0.650031, stealth:false});
		XETH.addAccount.dispatch({address:"0x00008e1d37d76d0be85be0bc717cad59644d0000", balance:0});
		
		XETH.updateContacts.dispatch([
			{avatar:'http://oi63.tinypic.com/30t13dj.jpg', alias:'John Peterson', bitprofile:false, address:'0x092a5172f796d4c3cd0e03520134317fc25b74f6', transactions:0},
			{avatar:'http://oi68.tinypic.com/i539z7.jpg', alias:'Ion Bitprofileanu', bitprofile:'ion_bitprofileanu', address:'0x69d48e1d37d76d0be85be0bc717cad59644d9098', transactions:685}]);
		
		XETH.updateTransactions.dispatch([
			{userAddress:'0x092a5172f796d4c3cd0e03520134317fc25b74f6', type:'received', 
			avatar:'http://oi63.tinypic.com/30t13dj.jpg', alias:'John Peterson', bitprofile:'false', address:'0x69d48e1d37d76d0be85be0bc717cad59644d9098', 
			amount:12.08, hash:'0xcc5151b5737ae3ffdea1a8bdd5d54cce33bc6e8905ccd954c6c830b25abcddfd', time:'2008-07-17 09:24:17'},
			{userAddress:'0x69d48e1d37d76d0be85be0bc717cad59644d9098', type:'sent', 
			avatar:'http://oi68.tinypic.com/i539z7.jpg', alias:'Ion Bitprofileanu', bitprofile:'ion_bitprofileanu', address:'0x092a5172f796d4c3cd0e03520134317fc25b74f6', 
			amount:0.650031, hash:'0x3f905231b37a4763b733ffa5bdd45cb5f17e17b98855581c147532f123eb3545', time:'2015-11-05 10:46:30'}]);
		
		XETH.pageStart.dispatch();
	},
	
	getClipboard: function() {
		console.log("XETH.getClipboard:\n");
		XETH.clipboardPaste.dispatch('clipboard_data');
	},
	submitSend: function(_addressFrom, _toType, _addressTo, _amount, _fee, _password) {
		console.log("XETH.submitSend:\n", _addressFrom, _toType, _addressTo, _amount, _fee, _password);
		XETH.addTransaction.dispatch(
			{userAddress:'0x468a5172f796d4c3cd0e03520134317fc25b3333', type:'sent', 
			avatar:'avatar1-01.png', alias:'Michael Deprofiler', address:'0x00008e1d37d76d0be85be0bc717cad59644d0000', 
			amount:0.001, hash:'0x1265sa31b37a4763b733ffa5bdd45cb5f17e17b98855581c147532f123eb332a', time:'2015-11-07 13:32:00'});
		
		XETH.sentSuccessful.dispatch();
		
		XETH.updateContactTransactions.dispatch({bitprofile:'ion_bitprofileanu', address:'0x69d48e1d37d76d0be85be0bc717cad59644d9098', transactions:686});
		XETH.updateContactTransactions.dispatch({address:'0x092a5172f796d4c3cd0e03520134317fc25b74f6', transactions:1});
	},
	
	setClipboard: function(_data) {
		console.log("XETH.setClipboard:\n", _data);
	},
	
	newAddressContact: function(_address, _alias) {
		console.log("XETH.newAddressContact:\n", _address, _alias);
		XETH.addContact.dispatch({avatar:'avatar1-01.png', alias:'Michael Deprofiler', address:'0x468a5172f796d4c3cd0e03520134317fc25b3333', transactions:1});
	},
	newBitprofileContact: function(_id, _alias) {
		console.log("XETH.newBitprofileContact:\n", _id, _alias);
		XETH.addContact.dispatch({avatar:'avatar1-01.png', alias:'Michael Deprofiler', bitprofile:'mixh123', address:'0x468a5172f796d4c3cd0e03520134317fc25b3333', transactions:1});
	},
	updateAddressAlias: function(_address, _alias) {
		console.log("XETH.updateAddressAlias:\n", _address, _alias);
		XETH.updateContactAlias.dispatch({alias:'John Peterson1', address:'0x092a5172f796d4c3cd0e03520134317fc25b74f6'});
	},
	updateBitprofileAlias: function(_id, _alias) {
		console.log("XETH.updateBitprofileAlias:\n", _id, _alias);
		XETH.updateContactAlias.dispatch({alias:'Ion Bitprofileanu II', bitprofile:'ion_bitprofileanu', address:'0x69d48e1d37d76d0be85be0bc717cad59644d9098'});
	}
	
};