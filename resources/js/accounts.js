//var acountList;

function initAccounts() 
{
	//initAccountItem();
	//filterAccounts();
	updateAccounts();
	
	$( '.accountList' ).change(function() {
			addAccountInfo($(this).children('.select'));
        }).trigger('change');
	
	$( '.accountList.mini' ).change(function() {
			shortifySelectedMiniAccount($(this).children('.select'));
        }).trigger('change');
}

function updateAccounts(_list)
{
	//accountList = [];
	
	$('.accountList .dropdownBox ul').html('');
	
	//accountList.push(null);
	initAccountItem();
		
	if(_list)
	{
		//for(var i=0; i<_list.length; i++)
		for(var i=_list.length-1; i>=0; i--)
		{
			addAccountItem(_list[i]);
		}
	}
	//else 
	filterAccounts();
}

function addAccountItem(_data)
{
    alert("adding account: "+JSON.stringify(_data));
	//accountList.push(_data);
	var _balance = "";
	if(!_data.stealth && !_data.bitprofile)
	{
		_balance = '<span class="amount txtBalance"><span class="int">'+
					parseInt(_data.balance)+
					'</span><span class="dec">'+
					(_data.balance.toFixed(ETH_dec).split('.')[1])+
					'</span></span>'
	}
	
	var _newitem =	$(
					'<li><a>'+
					_balance+
					'<span class="account"><span class="address">'+
					_data.address+
					'</span></span></a></li>'
					);
					
	_newitem.find('a').on('click', clickDropdownOption);
	
	if(_data.balance<=0) _newitem.attr('empty',"true");
	
	if(_data.stealth)
	{
		_newitem.find('.account').addClass('stealth');
		_newitem.attr('stealth',"true");
	}
	
	if(_data.bitprofile)
	{
		_newitem.find('.account').addClass('bitprofile');
		_newitem.find('.account').prepend('<span class="id">'+_data.bitprofile+'</span>');
		_newitem.attr('bitprofile',_data.bitprofile);
	}
	
	if(_data.originStealth)
	{
		//_newitem.find('.account').addClass('fromStealth');
		_newitem.find('.account').append('<span class="origin stealth"><span class="address">'+_data.originStealth+'</span></span>');
		_newitem.find('.account').addClass('originated originStealth');
	}
	
	if(_data.originBitprofile)
	{
		//_newitem.find('.account').addClass('fromStealth');
		_newitem.find('.account').append('<span class="origin bitprofile"><span class="id">'+_data.originBitprofile.id+'</span><span class="address">'+_data.originBitprofile.address+'</span></span>');
		_newitem.find('.account').addClass('originated originBitprofile');
	}
	
	shortifyAddress(_newitem.children('a'));
	
	//$('.accountList .dropdownBox ul li').prepend(_firstitem, _newitem);
	$('.accountList .dropdownBox ul .all').after(_newitem);
	
	$('.accountList').each(function(x)
	{
		var val = Number($(this).attr('value'));
		if(val>0) $(this).attr('value',val+1);
	});
}

function addAccount(_data)
{
	addAccountItem(_data);
	filterAccount(1);
}

function updateAccountBalance(_data)
{
	updateAccount(_data, function(_data, _index, _item, _send){
		
		_item.find('.amount .int').text(parseInt(_data.balance));
		_item.find('.amount .dec').text(_data.balance.toFixed(ETH_dec).split('.')[1]);
		
		if(_data.balance<=0) _item.attr('empty', "true"); 
		//console.log(_send);
		if(_item.parents('.accountList').attr('value')==_index)
		{
			if(_send.length > 0) resetAccountItem(_send);
			else changeSelect(_item.parents('.dropdownBox'),_index,0);
		}
	});
}
/*
function updateAccountStealth(_data)
{
	updateAccount(_data, function(_data, _index, _item, _send){
		if(_data.stealth)
		{
			_item.attr('stealth',"true");
			_item.find('.account').addClass('stealth');
		}
		else
		{
			_item.removeAttr('stealth');
			_item.find('.account').removeClass('stealth');
		}
		
		if(_send.length > 0 && _send.attr('value')==_index) resetAccountItem(_send);
	});
}
*/
function updateAccount(_data, _function)
{
	var _account = checkAccount(_data);
	
	if(_account)
	{
		$('.accountList .dropdownBox ul').each(function(x)
		{
			var _send = $(this).parents('.accountList.send');
			var _item = $(this).children('li').eq(_account.index);
			//console.log(_item);
			_function(_data, _account.index, _item, _send);
		});
		
		filterAccounts();
	}
}

function initAccountItem()
{
	resetAccountItem($('.accountList'));
	$('.accountList .dropdownBox ul').prepend($('<li class="all"></li>').append($('<a>All Accounts</a>').on('click', clickDropdownOption)));
}

function resetAccountItem(_target)
{
	_target.attr('value','-1');
	_target.find('.select').removeAttr('title');
	_target.find('.select').html('no available accounts');
}

function accountItem(_nr)
{
	var listItem = $( $( $('.accountList ul')[0] ).find('li')[_nr] );
	var account = { address:	listItem.find('.account').children('.address').text(),
					balance:	parseAmount(listItem.find('.amount')),
					empty:		(listItem.attr('empty'))? true : false,
					stealth:	(listItem.attr('stealth'))? true : false,
					bitprofile:	(listItem.attr('bitprofile'))? true : false,
					all:		listItem.hasClass('all')
	};
	return account;
}

function checkAccount(_data)
{
	for(var i=0; i<accountsLength(); i++)
	{
		var account = accountItem(i);
		
		if( account.address==_data.address )
		{
			return {data:account, item:$('.accountList .dropdownBox ul').children('li').eq(i), index:i};
		}
	}
}

function accountsLength()
{
	return $( $('.accountList ul')[0] ).find('li').length;
}

function parseAmount(_target)
{
	var amount = Number(_target.children('.int').text()+'.'+_target.children('.dec').text());
	if(isNaN(amount) || amount.length===0) amount=0;
	return amount
}

function filterAccounts()
{
	for(var i=0; i<accountsLength(); i++)
	{
		filterAccount(i);
	}
}

function filterAccount(_nr)
{
	$('.accountList .dropdownBox').each(function(x)
	{	
		if($(this).parents('.accountList').attr('value')=='-1')
		{
			var account = accountItem(_nr);
			
			//console.log(_target.parents('.accountList').attr('id'),accountsLength(),account);
			
			if($(this).parents('.accountList.send').length > 0)
			{ 
				if(!account.empty && !account.stealth && !account.bitprofile && !account.all)
				{
					changeSelect($(this),_nr,0);
				}
			}
			else if($(this).parents('.accountList.receive').length > 0)
			{ 
				if(!account.all)
				{
					changeSelect($(this),_nr,0);
				}
			}
			else if($(this).parents('.accountList.all').length > 0)
			{ 
				changeSelect($(this),0,0);
			}
			else
			{
				if(!account.all)
				{
					changeSelect($(this),_nr,0);
				}
			}
		}
	});
}

function shortifySelectedMiniAccount(_target)
{
	var _dec, _address;
	_target.attr("title","");
	
	if(_target.children('.amount').length>0)
	{
		_dec = Math.round( Number(_target.find('.amount .dec').text()) / Math.pow(10,ETH_dec-2) );
		if(_dec<10) _dec = "0"+_dec;
		//console.log(_target.find('.amount .dec').text(), _dec);
		_target.find('.amount .dec').text(_dec);
	}
	
	if(_target.children('.account').children('.address').length>0)
	{
		var _split = 3;
		if(_target.children('.account').hasClass('stealth')) _split = 9;
		
		_address = String(_target.children('.account').children('.address').text());
		_target.attr("title",_address);
		(_target.children('.account').hasClass('bitprofile'))? _address = "" : _address = _address.substr(0,2+_split)+"..."+_address.substr(_address.length-_split);
		
		_target.find('.account .origin.bitprofile .address').text("");
		
		var _originStealth = _target.find('.account .origin.stealth .address').text();
		if(_originStealth)
		_target.find('.account .origin.stealth .address').text( _originStealth.substr(0,2+_split)+"..."+_originStealth.substr(_originStealth.length-_split) );
		//console.log(_target.children('.address').text(),_address);
		_target.children('.account').children('.address').text(_address);
	}
	
	_target.children('.account').children('.shortAddress').css('display', 'none');
	_target.children('.account').children('.address').css('display', 'auto');
}

function shortifyAddress(_target)
{
	var _address = String(_target.children('.account').children('.address').text());
	var _bitprofile = String(_target.children('.account.bitprofile').children('.id').text());
	var _maxlength = 62;
	var _split;
	
	if( (_address.length + _bitprofile.length > _maxlength) && (_target.children('.account').hasClass("bitprofile") || _target.children('.account').hasClass("stealth")) )
	{
		_split = Math.round( (_maxlength - _bitprofile.length - 5)/2 );
		_target.attr("title",_address);
		_address = _address.substr(0,2+_split)+"..."+_address.substr(_address.length-_split);
		_target.children('.account').append('<span class="shortAddress">'+_address+'</span>');
		_target.children('.account').children('.address').css('display', 'none');
		
		$(_target).tooltip({ 
			track: true,
			show: { duration: 200 },
			hide: { duration: 200 }
		});
	}
	//console.log(_address.length, _bitprofile.length);
}


function addAccountInfo(_target)
{
	if(_target.closest('mini').length==0)
	{
		if(_target.children('.account').children('.shortAddress').length>0)
		{
			_target.attr("title", _target.children('.account').children('.address').text());
		}
		else
		{
			_target.attr("title", "");
		}
	}
}
