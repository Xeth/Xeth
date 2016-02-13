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
	
	appStatusLoader: 
	{
		connect: function(){},
		dispatch: function(_percent){appStatusLoader(_percent);}
	},
	appStatusMessage: 
	{
		connect: function(){},
		dispatch: function(_msg){appStatusMessage(_msg);}
	},
	appStatusLoaderTime: 
	{
		connect: function(){},
		dispatch: function(_time){appStatusLoaderTime(_time);}
	},
	appStatusIcon_secure: 
	{
		connect: function(){},
		dispatch: function(_status){appStatusIcon_secure(_status);}
	},
	appStatusIcon_network: 
	{
		connect: function(){},
		dispatch: function(_status){appStatusIcon_network(_status);}
	},
	appStatusIcon_updated: 
	{
		connect: function(){},
		dispatch: function(_status){appStatusIcon_updated(_status);}
	},
	/*
	updateProfile: 
	{
		connect: function(){},
		dispatch: function(_avatar, _name, _bitprofile){updateProfile(_avatar, _name, _bitprofile);}
	},
	*/	
	updateBitprofiles: 
	{
		connect: function(){},
		dispatch: function(_list){updateBitprofiles(_list);}
	},
	addBitprofile: 
	{
		connect: function(){},
		dispatch: function(_data){addBitprofile(_data);}
	},
	editBitprofile: 
	{
		connect: function(){},
		dispatch: function(_data){editBitprofile(_data);}
	},
	bitprofileCreateSuccessful: 
	{
		connect: function(){},
		dispatch: function(){bitprofileCreateSuccessful();}
	},
	bitprofileEditSuccessful: 
	{
		connect: function(){},
		dispatch: function(_bitprofile){bitprofileEditSuccessful(_bitprofile);}
	},
	bitprofileCreateError: 
	{
		connect: function(){},
		dispatch: function(_err){bitprofileCreateError(_err);}
	},
	bitprofileEditError: 
	{
		connect: function(){},
		dispatch: function(_err){bitprofileEditError(_err);}
	},
	bitprofileImportError: 
	{
		connect: function(){},
		dispatch: function(_err){bitprofileImportError(_err);}
	},
	bitprofileImportSuccessful: 
	{
		connect: function(){},
		dispatch: function(){bitprofileImportSuccessful();}
	},
	bitprofileExportSuccessful: 
	{
		connect: function(){},
		dispatch: function(_data){bitprofileExportSuccessful(_data);}
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
	updateAccountBalance: 
	{
		connect: function(){},
		dispatch: function(_data){updateAccountBalance(_data);}
	},
	/*updateAccountStealth: 
	{
		connect: function(){},
		dispatch: function(_data){updateAccountStealth(_data);}
	},*/
	newAddressError: 
	{
		connect: function(){},
		dispatch: function(_err){newAddressError(_err);}
	},
	newAddressSuccessful: 
	{
		connect: function(){},
		dispatch: function(){newAddressSuccessful();}
	},
	editAddressError: 
	{
		connect: function(){},
		dispatch: function(_err){editAddressError(_err);}
	},
	editAddressSuccessful: 
	{
		connect: function(){},
		dispatch: function(_data){editAddressSuccessful();}
	},
	exportAddressError: 
	{
		connect: function(){},
		dispatch: function(_err){exportAddressError(_err);}
	},
	exportAddressSuccessful: 
	{
		connect: function(){},
		dispatch: function(_data){exportAddressSuccessful(_data);}
	},
	importAddressError: 
	{
		connect: function(){},
		dispatch: function(_err){importAddressError(_err);}
	},
	importAddressSuccessful: 
	{
		connect: function(){},
		dispatch: function(){importAddressSuccessful();}
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
	removeContact: 
	{
		connect: function(){},
		dispatch: function(_data){removeContact(_data);}
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
	updateTransactionsContact: 
	{
		connect: function(){},
		dispatch: function(_data){updateTransactionsContact(_data);}
	},
	
	sentError: 
	{
		connect: function(){},
		dispatch: function(_err){sentError(_err);}
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
	
	setReceiveURI: 
	{
		connect: function(){},
		dispatch: function(_txt){setReceiveURI(_txt);}
	},
	
	// public
	UIReady: function(){
		console.log("XETH.UIReady:\n");
		
		XETH.testSignal.dispatch('test');
		XETH.setGASPrice.dispatch(0.000000055);
		
		XETH.appStatusLoader.dispatch(100);
		XETH.appStatusMessage.dispatch("synchronizing");
		XETH.appStatusLoaderTime.dispatch(1.1);
		XETH.appStatusIcon_secure.dispatch(false);
		XETH.appStatusIcon_network.dispatch(true);
		XETH.appStatusIcon_updated.dispatch(true);
		
		//XETH.updateProfile.dispatch('http://oi68.tinypic.com/i539z7.jpg', 'John Peterson', false);
		
		XETH.updateBitprofiles.dispatch([
			{avatar:'http://oi63.tinypic.com/30t13dj.jpg', alias:'John Peterson', bitprofile:'johny832'},
			{avatar:'http://oi68.asd.com/i539z7.jpg', alias:'Ion Bitprofileanu', bitprofile:'ion_bitprofileanu'}]);
		
				
		XETH.updateAccounts.dispatch([
			{address:"0x092a5172f796d4c3cd0e03520134317fc25b74f6", balance:0.0},
			{address:"0x69d48e1d37d76d0be85be0bc717cad59644d9098", stealth:true},
			{address:"0xfo2dc172f796d4c3cd0e03520134317fc25b75d1", balance:12.08, stealth:false},
			{address:"0x1d37d76d69d48e1d37d76d0be980bc717cad59d48e1d37d76d0be", bitprofile:'michael_deprofiler'}]);
	
		XETH.addAccount.dispatch({address:"0xdu258e1d37d76d0be85be0bc717cad59644d5fnb", balance:0.650031, originStealth:"0x69d48e1d37d76d0be85be0bc717cad59644d9098"});
		XETH.addAccount.dispatch({address:"0x00008e1d37d76d0be85be0bc717cad59644d0000", balance:0, originBitprofile:{id:"john16832", address:"0x0be85be69d4876d0be85be0bc717cad59644d90980be85be"} });
		XETH.addAccount.dispatch({address:"0xe85be0bc7100008e1d37d76d0be85be0bc717cad59644d0000e85be0bc7185be0bc717", stealth:true});
		
		XETH.updateContacts.dispatch([
			{avatar:'http://oi63.tinypic.com/30t13dj.jpg', alias:'John Peterson', bitprofile:false, address:'0x092a5172f796d4c3cd0e03520134317fc25b74f6', transactions:0},
			{avatar:'http://oi68.tinypic.com/i539z7.jpg', alias:'Ion Bitprofileanu', bitprofile:'ion_bitprofileanu', address:'0x69d48e1d37d76d0be85be0bc717cad59644d9098', transactions:685}]);
		
		XETH.updateTransactions.dispatch([
			{userAddress:'0x69d48e1d37d76d0be85be0bc717cad59644d9098', type:'received', 
			avatar:'http://oi63.tinypic.com/30t13dj.jpg', alias:'John Peterson', address:'0x092a5172f796d4c3cd0e03520134317fc25b74f6', 
			amount:12.08, hash:'0xcc5151b5737ae3ffdea1a8bdd5d54cce33bc6e8905ccd954c6c830b25abcddfd', time:'2015-12-25 09:24:17'},
			{userAddress:'0xfo2dc172f796d4c3cd0e03520134317fc25b75d1', type:'sent', 
			avatar:'http://oi68.tinypic.com/i539z7.jpg', alias:'Ion Bitprofileanu', bitprofile:'ion_bitprofileanu', address:'0x69d48e1d37d76d0be85be0bc717cad59644d9098', 
			amount:0.650031, hash:'0x3f905231b37a4763b733ffa5bdd45cb5f17e17b98855581c147532f123eb3545', time:'2015-11-05 10:46:30'},
			{userAddress:'0xfo2dc172f796d4c3cd0e03520134317fc25b75d1', type:'sent', 
			bitprofile:'asda', address:'0x0000000', 
			amount:25.582002, hash:'0x4763b733ffa5bdd45cb5f17e17b988123eb35454763b733ffa5bdd45cb5f17e17b988', time:'2015-11-05 10:46:30'}]);
		
		//setTimeout(XETH.pageStart.dispatch, 2000);
		XETH.pageStart.dispatch();
	},
	
	fileBrowseLoad: function() {
		console.log("XETH.fileBrowseLoad:\n");
		alert('X:/files/loaded_file.txt');
		return 'X:/files/loaded_file.txt';
	},
	fileBrowseSave: function(_name, _data) {
		console.log("XETH.fileBrowseSave:\n", _name, _data);
		alert('X:/files/'+_name);
		//return 'X:/files/save_file.txt';
	},
	
	getClipboard: function() {
		console.log("XETH.getClipboard:\n");
		XETH.clipboardPaste.dispatch('clipboard_data');
	},
	
	submitBitprofileCreate: function(_bitprofile, _alias, _avatar, _password, _address, _fee) {
		console.log("XETH.submitBitprofileCreate:\n", _bitprofile, _alias, _avatar, _password, _address, _fee);
		if(_password==XETH.test_password() && _bitprofile!=XETH.test_wrongAddress())
		{
			XETH.addBitprofile.dispatch({avatar:_avatar, alias:_alias, bitprofile:_bitprofile});
			XETH.bitprofileCreateSuccessful.dispatch();
		}
		else
		{
			XETH.bitprofileCreateError.dispatch({id:_bitprofile==XETH.test_wrongAddress(), password:_password!=XETH.test_password()});
		}
	},
	submitBitprofileEdit: function(_bitprofile, _alias, _avatar, _password, _address, _fee) {
		console.log("XETH.submitBitprofileEdit:\n", _bitprofile, _alias, _avatar, _password, _address, _fee);
		if(_password==XETH.test_password())
		{
			XETH.editBitprofile.dispatch({avatar:_avatar, alias:_alias, bitprofile:_bitprofile});
			XETH.bitprofileEditSuccessful.dispatch(_bitprofile);
		}
		else
		{
			XETH.bitprofileEditError.dispatch({password:true});
		}
	},
	submitBitprofileImport: function(_file, _password) {
		console.log("XETH.submitBitprofileImport:\n", _file, _password);
		if(_password==XETH.test_password())
		{
			XETH.addBitprofile.dispatch({avatar:'avatar1-01.png', alias:'Imported '+parseInt(Math.random()*100), bitprofile:'imported_'+Number(moment())+parseInt(Math.random()*100)});
			XETH.bitprofileImportSuccessful.dispatch();
		}
		else
		{
			XETH.bitprofileImportError.dispatch({password:true});
		}
	},	
	submitBitprofileExport: function(_bitprofile) {
		console.log("XETH.submitBitprofileExport:\n", _bitprofile);
		XETH.bitprofileExportSuccessful.dispatch( {bitprofile:_bitprofile, data:Number(moment())} );
	},
	
	submitNewAddressCreate: function(_hex, _stealth, _password) {
		console.log("XETH.submitNewAddressCreate:\n", _hex, _stealth, _password);
		if(_password==XETH.test_password())
		{
			XETH.addAccount.dispatch({address:XETH.test_address(), balance:0, stealth:_stealth});
		
			XETH.newAddressSuccessful.dispatch();
		}
		else
		{
			XETH.newAddressError.dispatch({password:true});
		}
	},	
	submitEditAddress: function(_address, _password, _newpassword) {
		console.log("XETH.submitEditAddress:\n", _address, _password, _newpassword);
		if(_password==XETH.test_password() && _newpassword==XETH.test_password())
		{
			XETH.editAddressSuccessful.dispatch();
		}
		else
		{
			XETH.editAddressError.dispatch({password:_password!=XETH.test_password(), newpassword:_newpassword!=XETH.test_password()});
		}
	},	
	submitExportAddress: function(_address) {
		console.log("XETH.submitExportAddress:\n", _address);
		XETH.exportAddressSuccessful.dispatch( {address:_address, data:Number(moment())} );
	},
	submitImportAddress: function(_file, _password) {
		console.log("XETH.submitImportAddress:\n", _file, _password);
		if(_password==XETH.test_password())
		{
			XETH.addAccount.dispatch({address:XETH.test_address(), balance:Math.random()*100});
			XETH.importAddressSuccessful.dispatch();
		}
		else
		{
			XETH.importAddressError.dispatch({password:true});
		}
	},
	
	submitSend: function(_addressFrom, _toType, _addressTo, _amount, _fee, _password) {
		console.log("XETH.submitSend:\n", _addressFrom, _toType, _addressTo, _amount, _fee, _password);
		if(_password==XETH.test_password() && _addressTo!=XETH.test_wrongAddress())
		{
			XETH.addTransaction.dispatch(
				{userAddress:_addressFrom, type:'sent', 
				//avatar:'avatar1-01.png', alias:'Michael Deprofiler', 
				bitprofile:(_toType==1)? _addressTo : false, 
				address:(_toType==0)? _addressTo : XETH.test_address(), 
				amount:XETH.test_amount(_amount, _fee), hash:XETH.test_hash(), time:moment().format('YYYY-MM-DD hh:mm:ss')});
			
			XETH.sentSuccessful.dispatch();
			
			//XETH.updateAccountStealth.dispatch({address:"0xfo2dc172f796d4c3cd0e03520134317fc25b75d1", stealth:true});
			XETH.updateAccountBalance.dispatch({address:"0xdu258e1d37d76d0be85be0bc717cad59644d5fnb", balance:0});
			//XETH.updateContactTransactions.dispatch({address:'0x092a5172f796d4c3cd0e03520134317fc25b74f6', transactions:1});
		}
		else
		{
			XETH.sentError.dispatch({address:_addressTo==XETH.test_wrongAddress(), password:_password!=XETH.test_password()});
		}
	},
	
	setClipboard: function(_data) {
		console.log("XETH.setClipboard:\n", _data);
	},
	submitReceiveForm: function(_address, _amount, _message) {		
		var _txt = 	"xeth:"+
					_address;
		
		var _vars = "?";
		
		if(_amount>0) _vars += "amount=" + _amount;
		
		if(_message.length>0)
		{
			if(_vars!="?") _vars += "&";
			_vars += "message=" + _message;
		}
		
		if(_vars!="?") _txt += _vars;
		
		XETH.setReceiveURI.dispatch(_txt);
	},
	
	newAddressContact: function(_address, _alias) {
		console.log("XETH.newAddressContact:\n", _address, _alias);
		XETH.addContact.dispatch({alias:_alias, address:_address, transactions:1});
		//XETH.updateTransactionsContact.dispatch({alias:_alias, address:_address});
	},
	newBitprofileContact: function(_id, _alias) {
		console.log("XETH.newBitprofileContact:\n", _id, _alias);
		XETH.addContact.dispatch({avatar:'avatar1-01.png', alias:_alias, bitprofile:_id, address:XETH.test_address(), transactions:1});
		//XETH.updateTransactionsContact.dispatch({avatar:'avatar1-01.png', alias:_alias, bitprofile:_id, address:'0x'+Number(moment()).toString().substr(0,8)+'_NEW_ADDRESS_'+Number(moment()).toString().substr(0,8)});
	},
	updateAddressAlias: function(_address, _alias) {
		console.log("XETH.updateAddressAlias:\n", _address, _alias);
		XETH.updateContactAlias.dispatch({alias:_alias, address:_address});
	},
	updateBitprofileAlias: function(_id, _alias) {
		console.log("XETH.updateBitprofileAlias:\n", _id, _alias);
		XETH.updateContactAlias.dispatch({alias:_alias, bitprofile:_id});
	},
	deleteContact: function(_alias, _bitprofile, _address) {
		console.log("XETH.deleteContact:\n", _alias, _bitprofile, _address);
		XETH.removeContact.dispatch({bitprofile:_bitprofile, address:_address});
	},
	updateContactTransaction: function(_address, _bitprofile) {
		console.log("XETH.updateContactTransaction:\n", _address, _alias);
		XETH.updateContactTransactions.dispatch({address:_address, bitprofile:_bitprofile, transactions:moment().format('s')});
	},
	
	updateTransactionContact: function(_data) {
		console.log("XETH.updateTransactionContact:\n", _data);
		XETH.updateTransactionsContact.dispatch(_data);
	},
	
	test_password: function() {
		return 'asd';
	},
	test_wrongAddress: function() {
		return 'asd';
	},
	test_address: function() {
		return '0x'+Number(moment()).toString().substr(0,8)+'_NEW_ADDRESS_'+Number(moment()).toString().substr(0,8);
	},
	test_hash: function() {
		return '0x'+Number(moment()).toString().substr(0,8)+'_GENERATED_HASH';
	},
	test_amount: function(_amount, _fee) {
		return Number(_amount)+Number((_fee*GAS_price).toFixed(ETH_dec));
	}
	
};