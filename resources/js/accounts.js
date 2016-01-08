var acountList;

function initAccounts() 
{
	$( '.accountList.mini' ).change(function() {
			shortifySelectedAccount($(this).children('.select'));
        });
}

function updateAccounts(_list)
{
	accountList = [];
	
	$('.accountList .dropdownBox ul').html('');
	
	accountList.push(null);
	$('.accountList .dropdownBox ul').append($('<li empty stealth></li>').append($('<a>All Accounts</a>').on('click', clickDropdownOption)));
	
	for(var i=0; i<_list.length; i++)
	{
		addAccount(_list[i]);
	}
	
	$('.accountList .dropdownBox').each(function(i)
	{
		for(var i=0; i<_list.length; i++)
		{
			if($(this).parents('.accountList.send').length > 0)
			{ 
				if(_list[i].balance>0)
				{
					changeSelect($(this),i+1,0);
					break;
				}
			}
			else if($(this).parents('.accountList.receive').length > 0)
			{ 
				if(!_list[i].stealth)
				{
					changeSelect($(this),i+1,0);
					break;
				}
			}
			else
			{
				changeSelect($(this),0,0);
				break;
			}
		}
	});
}

function addAccount(_data)
{
	accountList.push(_data);
	
	var _newitem =	$(
					'<li><a><span class="amount txtBalance"><span class="int">'+
					parseInt(_data.balance)+
					'</span><span class="dec">'+
					(_data.balance.toFixed(ETH_dec).split('.')[1])+
					'</span></span><span class="address">'+
					_data.address+
					'</span></a></li>'
					);
					
	_newitem.find('a').on('click', clickDropdownOption);
	
	if(_data.balance<=0) _newitem.attr('empty',"true");
	if(_data.stealth) _newitem.attr('stealth',"true");
	
	$('.accountList .dropdownBox ul').append(_newitem);
}

function shortifySelectedAccount(_target)
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
	
	if(_target.children('.address').length>0)
	{
		_address = String(_target.children('.address').text());
		_target.attr("title",_address);
		_address = _address.substr(0,5)+"..."+_address.substr(_address.length-3);
		//console.log(_target.children('.address').text(),_address);
		_target.children('.address').text(_address);
	}
}