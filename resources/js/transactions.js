//var transactionList;

function initTransactions() 
{
	setStepScrollbar($(".scrollpage.transactions"), 106);
	
	$( '#filterTransactionType' ).change(function() {
			filterTransactions();
        });
	
	$( '#filterTransactionTime' ).change(function() {
			filterTransactions();
        });
	
	$( '#filterTransactionAddress' ).change(function() {
			filterTransactions();
        });
}

function updateTransactions(_list)
{
	//transactionList = [];
	
	$('.transactionList').html('');
	
	//for(var i=0; i<_list.length; i++)
	if(_list)
	for(var i=_list.length-1; i>=0; i--)
	{
		addTransactionItem(_list[i]);
	}
	
	filterTransactions();
}

function addTransactionItem(_data)
{
	//transactionList.push(_data);
	
	var _newitem =	$(
					'<div class="listItem '+
					_data.type+
					'"><div class="header icon"><span class="detail s_titled userAddress">'+
					_data.userAddress+
					'</span></div><span class="avatar"><span class="img"><img src="'+
					checkAvatar(_data.avatar)+
					'" onerror="errorAvatar($(this))" /></span></span>'+
					'<div class="data"><div class="detailsRow"><span class="userProfile"><span class="name editableTxt">'+
					checkAlias(_data.alias)+
					'</span> <span class="bitprofileIcon" title="no bitprofile"></span></span><span class="detail s_titled hash" title="'+
					_data.hash+'">'+
					_data.hash.toString().slice(0,10)+'...'+
					'</span><span class="detail txtBalance"><span class="int">'+
					parseInt(_data.amount)+
					'</span><span class="dec">'+
					(_data.amount.toFixed(ETH_dec).split('.')[1])+
					'</span></span></div><div class="detailsRow"><span class="address">'+
					_data.address+
					'</span><span class="detail time" title="'+
					_data.time+
					'">'+
					_data.time+
					'</span></div></div></div>'
					);
	
	if(_data.alias)
	{
		destroyTransactionEditableAlias(_newitem);
	}
	else
	{
		initTransactionEditableAlias(_newitem);
	}
	if(_data.bitprofile) 
	{
		_newitem.attr('bitprofile',_data.bitprofile);
		_newitem.find('.bitprofileIcon').attr('title','bitprofile: '+_data.bitprofile);
	}
	_newitem.find('.bitprofileIcon').toggleClass('on', _data.bitprofile!==false && typeof _data.bitprofile!=="undefined");
	
	$('.transactionList').prepend(_newitem);
	
	$(_newitem).find('.detail.time').timeago();
	$(_newitem).find('.detail.time').tooltip({ 
		position: { my: "right bottom", at: "right+5 top-5" },
		show: { duration: 200 },
		hide: { duration: 200 }
	});
}

function addTransaction(_data)
{
	addTransactionItem(_data);
	
	navTransactionsNotifyNew();
	filterTransactions();
}

function transactions(_data)
{
	return $('.transactionList .listItem').filter(function( index ) {
		var _address = $(this).find('.address').text()==_data.address;
		var _bitprofile = ($(this).attr('bitprofile'))? $(this).attr('bitprofile')==_data.bitprofile : false;//_data.bitprofile==false;
		//console.log(_data.bitprofile, $(this).attr('bitprofile'), _bitprofile);
		//console.log(_data.address, $(this).find('.address').text(), _address);
		//console.log( _bitprofile && _address );
		return ( _bitprofile || _address );
	});
}

function navTransactionsNotifyNew()
{
	navNotifyNew($('.mainNav .transactions a'));
}

function filterTransactions()
{
	var _totalReceived = 0, _totalSent = 0;
	
	$(".transactionList .listItem").hide().filter(function( index ) {
		var _typeFilter = $('#filterTransactionType').attr('value');
		var _addressFilter = $('#filterTransactionAddress').attr('value');
		var _timeFilter = String($('#filterTransactionTime').attr("title")).split(" - ");
		var _itemTime = String($(this).find(".data .time").attr("title")).split(" ")[0];
		var _balance = Number($(this).find(".data .txtBalance .int").text()+"."+$(this).find(".data .txtBalance .dec").text());
		var _result, _type, _address, _time;
		
		switch( _typeFilter )
		{
			case "0": _type = true; break;
			case "1": _type = $(this).hasClass("received"); break;
			case "2": _type = $(this).hasClass("sent"); break;
		}
		
		_address = ( _addressFilter==0 ||
					accountItem(_addressFilter).address == $(this).find('.userAddress').text());
		
		_time = (_timeFilter[0]<=_itemTime && _timeFilter[1]>=_itemTime);
		console.log(_timeFilter, _itemTime, _time);
		
		_result = _type && _address && _time;
		
		if(_result)
		{
			if($(this).hasClass("received")) _totalReceived += _balance;
			if($(this).hasClass("sent")) _totalSent += _balance;
		}
		
		return _result;
	}).show();
	
	updateTransactionsTotal(_totalReceived, _totalSent);
}

function initTransactionEditableAlias(_item)
{
	_item.find('.editableTxt').editable('destroy');
	_item.attr('contact', 'false');
	_item.find('.userProfile').off('click');
	
	_item.find('.editableTxt').attr('title','save contact');
	_item.find('.editableTxt').editable({
		mode: 'inline',
		autotext: 'never',
		value: "",
		clear: false,
		validate: function(v) {
			saveTransactionContact($($(this).context).closest('.listItem'),v);
		},
		display: false
	});
}

function destroyTransactionEditableAlias(_item)
{
	_item.find('.editableTxt').editable('destroy');
	_item.attr('contact', 'true');
	_item.find('.editableTxt').attr('title','')
	_item.find('.userProfile').on('click', function(){ findContactFromTransaction( $(this).closest('.listItem')); });
	_item.find('.avatar').on('click', function(){ findContactFromTransaction( $(this).closest('.listItem')); });
		
}

function findContactFromTransaction(_item)
{
	var _txt = ( ($(_item).attr('bitprofile'))? $(_item).attr('bitprofile') : $(_item).find('.address').text());
	searchContact( _txt );
}

function saveTransactionContact(_item, _alias)
{
	console.log(_alias, $(_item).find('.userProfile .name').text());
	if(_alias && _alias!=$(_item).find('.userProfile .name').text())
	{
		var _type = ( (_item.attr('bitprofile'))? 1 : 0 );
		var _account = ( (_type==1)? _item.attr('bitprofile') : _item.find('.address').text() );
		scheduleSaveContact(true, _alias, _type, _account);
		saveContact();
	}
}

function updateTransactionsContact(_data)
{
	var items = transactions(_data);
		
	console.log(items, _data);
	items.find('.userProfile .name').text(checkAlias(_data.alias));
	if(_data.avatar) items.find('.avatar img').attr('src', checkAvatar(_data.avatar));
	
	if(_data.alias) 
	{
		items.each(function(x){ destroyTransactionEditableAlias($(this)) });
	}
	else
	{
		items.each(function(x){ initTransactionEditableAlias($(this)) });
	}
}

function updateTransactionsTotal(_totalReceived, _totalSent)
{
	var _received = $('#page_transactions .transactions_total .total.received .txtBalance');
	var _sent = $('#page_transactions .transactions_total .total.sent .txtBalance');
	
	_totalReceived = _totalReceived.toFixed(ETH_dec).split('.');
	_totalSent = _totalSent.toFixed(ETH_dec).split('.');
	
	_received.children('.int').text(_totalReceived[0]);
	_received.children('.dec').text(_totalReceived[1]);
	
	_sent.children('.int').text(_totalSent[0]);
	_sent.children('.dec').text(_totalSent[1]);
}