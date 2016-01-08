var contactList;
var pendingContact;

function initAddressbook() 
{
	$( '#filterContacts' ).change(function() {
			filterContacts();
        }).trigger('change');
}

function updateContacts(_list)
{
	contactList = [];
	
	$('.contactList').html('');
	
	for(var i=0; i<_list.length; i++)
	{
		addContact(_list[i]);
	}
}

function addContact(_data)
{
	contactList.push(_data);
	
	var _index = $('.contactList').children().length;
	var _controls = '<div class="controls">'+
					'<a class="btn btntxt remove" href="javascript:void(0);"></a>'+
					'<a class="btn btntxt send" href="#page_send"></a>'+
					'</div>';
	var _newitem =	$(
					'<div class="listItem"><span class="avatar"><span class="img"><img src="'+
					_data.avatar+
					'" /></span></span>'+
					'<div class="data"><div class="detailsRow"><span class="userProfile"><span class="name">'+
					_data.alias+
					'</span> <span class="bitprofileIcon '+
					'" title="no bitprofile"></span></span><span class="detail s_titled transactions">'+
					_data.transactions+
					'</span>'+
					'<div class="controls"><a class="btn btntxt send" href="#page_send"></a></div>'+
					'</div><div class="detailsRow"><span class="address">'+
					_data.address+
					'</span>'+
					'<div class="controls"><a class="btn btntxt remove" href="javascript:void(0);"></a></div>'+
					'</div></div></div>'
					);
					
	if(_data.bitprofile)
	{
		_newitem.attr('bitprofile',_data.bitprofile);
		_newitem.find('.bitprofileIcon').attr('title','bitprofile: '+_data.bitprofile);
	}
	_newitem.find('.bitprofileIcon').toggleClass('on', _data.bitprofile!==false && typeof _data.bitprofile!=="undefined");
	
	_newitem.find('.btn.send').on('click', function(){sendPaymentTo(_data.alias, _data.bitprofile, _data.address);});
	
	$('.contactList').append(_newitem);
	
	navAddressbookNotifyNew();
}

function navAddressbookNotifyNew()
{
	navNotifyNew($('.mainNav .addressbook a'));
}

function filterContacts()
{
	var _val = $('#filterContacts').attr('value');
	
	$(".contactList .listItem").hide().filter(function( index ) {
		switch(_val)
		{
			case "0": return true;
			case "1": return $(this).attr("bitprofile");
			case "2": return !$(this).attr("bitprofile");
		}
	}).show();
}

function scheduleSaveContact(_checkbox, _alias, _type, _account)
{
	pendingContact = {checkbox:_checkbox, alias:_alias, type:_type, account:_account};
	
	console.log(pendingContact);
}

function saveContact()
{
	if(pendingContact.checkbox)
	{
		for(var i=0; i<contactList.length; i++)
		{
			if( ( pendingContact.type=="0" && contactList[i].address==pendingContact.account ) || 
				( pendingContact.type=="1" && contactList[i].bitprofile==pendingContact.account ) )
			{
				if(contactList[i].alias==pendingContact.alias)
				{
					return;
				}
				
				if(pendingContact.type=="0") XETH.updateAddressAlias(pendingContact.account, pendingContact.alias);
				else XETH.updateBitprofileAlias(pendingContact.account, pendingContact.alias);
				return
			}
		}
		
		if(pendingContact.type=="0") XETH.newAddressContact(pendingContact.account, pendingContact.alias);
		else XETH.newBitprofileContact(pendingContact.account, pendingContact.alias);
	}
}

function updateContactAlias(_data)
{
	for(var i=0; i<contactList.length; i++)
	{
		if( (contactList[i].bitprofile==_data.bitprofile || !_data.bitprofile) && contactList[i].address==_data.address )
		{
			console.log(contactList[i].alias, _data.alias);
			contactList[i].alias=_data.alias;
			$('.contactList').find('.listItem').eq(i).find('.userProfile .name').text(_data.alias);
			return
		}
	}
}

function updateContactTransactions(_data)
{
	for(var i=0; i<contactList.length; i++)
	{
		if( (contactList[i].bitprofile==_data.bitprofile || !_data.bitprofile) && contactList[i].address==_data.address )
		{
			console.log(contactList[i].transactions, _data.transactions);
			contactList[i].transactions=_data.transactions;
			$('.contactList').find('.listItem').eq(i).find('.transactions').text(_data.transactions);
			return
		}
	}
}