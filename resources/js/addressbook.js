//var contactList;
var pendingContact;

function initAddressbook() 
{
	setStepScrollbar($(".scrollpage.addressbook"), 71);
	
	//$( '#btnSearchContacts' ).click(filterContacts);
	
	$( '#inputSearchContacts' ).on('input', filterContacts);
		
	$( '#filterContacts' ).change(function() {
			filterContacts();
        }).trigger('change');
}

function updateContacts(_list)
{
	//contactList = [];
	
	$('.contactList').html('');
	
	//for(var i=0; i<_list.length; i++)
	if(_list)
	for(var i=_list.length-1; i>=0; i--)
	{
		addContactItem(_list[i]);
	}
}

function addContactItem(_data)
{
	//contactList.push(_data);
	
	//var _index = $('.contactList').children().length;
	var _controls = '<div class="controls">'+
					'<a class="btn btntxt remove" href="javascript:void(0);"></a>'+
					'<a class="btn btntxt send" href="#page_send"></a>'+
					'</div>';
	var _newitem =	$(
					'<div class="listItem"><span class="avatar"><span class="img"><img src="'+
					checkAvatar(_data.avatar)+
					'" onerror="errorAvatar($(this))" /></span></span>'+
					'<div class="data"><div class="detailsRow"><span class="userProfile"><span class="name editableTxt">'+
					_data.alias+
					'</span> <span class="bitprofileIcon '+
					'" title="no bitprofile"></span></span><span class="detail s_titled transactions">'+
					_data.transactions+
					'</span>'+
					'<div class="controls"><a class="btn btntxt send" href="javascript:changePage(\'page_send\');"></a></div>'+
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
	
	_newitem.find('.btn.send').on('click', function(){btnContactSendPaymentTo( $(this).closest('.listItem') );});
	_newitem.find('.btn.remove').on('click', function(){btnContactDelete( $(this).closest('.listItem') );});
	
	initContactEditableAlias(_newitem);
	
	$('.contactList').prepend(_newitem);
}

function addContact(_data)
{
	addContactItem(_data);
	
	navAddressbookNotifyNew();
	updateTransactionsContact(_data);
	filterContacts();
}

function contactItem(_nr)
{
	var listItem = $( $('.contactList .listItem')[_nr] );
	var contact = { avatar:			listItem.find('.avatar img').attr('src'),
					alias:			listItem.find('.userProfile .name').text(),
					bitprofile:		(listItem.attr('bitprofile'))? listItem.attr('bitprofile') : false,
					transactions:	listItem.find('.transactions').text(),
					address:		listItem.find('.address').text()
	};
	return contact;
}

function checkContact(_data)
{
	for(var i=0; i<contactsLength(); i++)
	{
		var contact = contactItem(i);
		
		if( (contact.bitprofile==_data.bitprofile || !_data.bitprofile) && (contact.address==_data.address || !_data.address) )
		{
			return {data:contact, item:$('.contactList').find('.listItem').eq(i), index:i};
		}
	}
}

function contactsLength()
{
	return $('.contactList .listItem').length;
}

function navAddressbookNotifyNew()
{
	navNotifyNew($('.mainNav .addressbook a'));
}

function filterContacts()
{
	//var _val = $('#filterContacts').attr('value');
	
	$(".contactList .listItem").hide().filter(function( index ) {
		var _typeFilter = $('#filterContacts').attr('value');
		var _txtFilter = String($('#inputSearchContacts').val()).toLowerCase();
		var _result, _type, _txt=true;
		
		switch(_typeFilter)
		{
			case "0": _type = true; break;
			case "1": _type = $(this).attr("bitprofile"); break;
			case "2": _type = !$(this).attr("bitprofile"); break;
		}
		
		if(_txtFilter)
		{
			_txt = String($(this).find('.userProfile').find('.name').text()).toLowerCase().indexOf(_txtFilter) >= 0;
			if(!_txt && $(this).attr('bitprofile')) _txt = String($(this).attr('bitprofile')).toLowerCase().indexOf(_txtFilter) >= 0;
			if(!_txt) _txt = String($(this).find('.address').text()).toLowerCase().indexOf(_txtFilter) >= 0;
		}
		
		_result = _type && _txt;
		
		return _result;
	}).show();
}

function searchContact(_txt)
{
	$('#inputSearchContacts').val(_txt);
	filterContacts();
	changePage("page_addressbook");
}

function btnContactSendPaymentTo(_target)
{
	var contact = contactItem(_target.index());
	sendPaymentTo(contact.alias, contact.bitprofile, contact.address);
}

function btnContactDelete(_target)
{
	var removing = $(
                '<div class="controls removing">'+
                	'<div class="txt s_title">removing contact (<span class="time">6</span>)</div>'+
                	'<a class="btn btntxt cancel" href="javascript:void(0);"></a>'+
                '</div>');
	_target.append(removing);
	_target.addClass('removing');
	
	//_target.removeTimer = 0;
	contactDeleteTimer(_target);
	
	_target.find('.btn.cancel').on('click', function(){contactCancelDelete(_target);});
	//XETH.deleteContact(contact.alias, contact.bitprofile, contact.address);
}

function contactDeleteTimer(_target)
{
	if(_target.hasClass('removing'))
	{
		var _time = _target.find('.controls.removing .txt .time').text();
	
		console.log(_target,_time,_target.removeTimer);
	
		if(_time>0)
		{
			_target.find('.controls.removing .txt .time').text(_time-1);
			_target.removeTimer = window.setTimeout(contactDeleteTimer, 1000, _target);
		}
		else if(_time==0)
		{
			var contact = contactItem(_target.index());
			XETH.deleteContact(contact.alias, contact.bitprofile, contact.address);
		}
	}
}

function contactCancelDelete(_target)
{
	window.clearTimeout(_target.removeTimer);
	console.log(_target,_target.removeTimer);
	var contact = contactItem(_target.index());
	_target.removeClass('removing');
	_target.children('.removing').remove();
}

function scheduleSaveContact(_checkbox, _alias, _type, _account)
{
	pendingContact = {checkbox:_checkbox, alias:_alias, type:_type, account:_account};
	
	console.log(pendingContact);
}

function saveContact()
{
	//if(pendingContact.checkbox)
	{
		for(var i=0; i<contactsLength(); i++)
		{
			var contact = contactItem(i);
			
			console.log(contact);
			
			if( ( pendingContact.type=="0" && contact.address==pendingContact.account ) || 
				( pendingContact.type=="1" && contact.bitprofile==pendingContact.account ) )
			{
				XETH.updateTransactionContact({avatar:contact.avatar, alias:contact.alias, bitprofile:contact.bitprofile, address:contact.address});
				XETH.updateContactTransaction(contact.address, contact.bitprofile);
				
				if(contact.alias==pendingContact.alias)
				{
					return;
				}
				
				if(pendingContact.checkbox)
				{
					if(pendingContact.type=="0") XETH.updateAddressAlias(pendingContact.account, pendingContact.alias);
					else XETH.updateBitprofileAlias(pendingContact.account, pendingContact.alias);
				}
				return
			}
		}
		
		if(pendingContact.checkbox)
		{
			if(pendingContact.type=="0") XETH.newAddressContact(pendingContact.account, pendingContact.alias);
			else XETH.newBitprofileContact(pendingContact.account, pendingContact.alias);
		}
	}
}

function initContactEditableAlias(_item)
{
	_item.find('.editableTxt').editable('destroy');
	_item.find('.editableTxt').attr('title','edit alias')
	_item.find('.editableTxt').editable({
		mode: 'inline',
		autotext: 'always',
		clear: false,
		validate: function(v) {
			editContactAlias($($(this).context).closest('.listItem'),v);
		},
		display: false
	});
}

function editContactAlias(_item, _val)
{
	console.log($(_item).attr('bitprofile'), _val);
	if(!_val || _val!=$(_item).find('.userProfile .name').text())
	{
		if( $(_item).attr('bitprofile') ) XETH.updateBitprofileAlias($(_item).attr('bitprofile'), _val);
		else XETH.updateAddressAlias($(_item).find('.address').text(), _val);
	}
}

function updateContactAlias(_data)
{
	var contact = checkContact(_data);
	console.log(contact.data.alias, _data.alias);
	contact.item.find('.userProfile .name').text(_data.alias);
	initContactEditableAlias(contact.item);
	updateTransactionsContact(_data);
}

function updateContactTransactions(_data)
{
	var contact = checkContact(_data);
	console.log(contact.data.transactions, _data.transactions);
	contact.item.find('.transactions').text(_data.transactions);
}

function removeContact(_data)
{
	var contact = checkContact(_data);
	console.log(contact.data, _data.address);
	updateTransactionsContact({address:_data.address, bitprofile:_data.bitprofile, avatar:avatarEmpty});
	contact.item.remove();
}