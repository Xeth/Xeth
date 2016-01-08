var transactionList;

function initTransactions() 
{
	$( '#filterTransactions' ).change(function() {
			filterTransactions();
        }).trigger('change');
}

function updateTransactions(_list)
{
	transactionList = [];
	
	$('.transactionList').html('');
	
	for(var i=0; i<_list.length; i++)
	{
		addTransaction(_list[i]);
	}
}

function addTransaction(_data)
{
	transactionList.push(_data);
	
	var _newitem =	$(
					'<div class="listItem '+
					_data.type+
					'"><div class="header icon"><span class="detail s_titled userAddress">'+
					_data.userAddress+
					'</span></div><span class="avatar"><span class="img"><img src="'+
					_data.avatar+
					'" /></span></span>'+
					'<div class="data"><div class="detailsRow"><span class="userProfile"><span class="name">'+
					_data.alias+
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
					
	if(_data.bitprofile) 
	{
		_newitem.attr('bitprofile',_data.bitprofile);
		_newitem.find('.bitprofileIcon').attr('title','bitprofile: '+_data.bitprofile);
	}
	_newitem.find('.bitprofileIcon').toggleClass('on', _data.bitprofile!==false && typeof _data.bitprofile!=="undefined");
	
	$('.transactionList').append(_newitem);
	
	$(_newitem).find('.detail.time').timeago();
	$(_newitem).find('.detail.time').tooltip({ 
		position: { my: "right bottom", at: "right+5 top-5" },
		show: { duration: 200 },
		hide: { duration: 200 }
	});
	
	navTransactionsNotifyNew();
}

function navTransactionsNotifyNew()
{
	navNotifyNew($('.mainNav .transactions a'));
}

function filterTransactions()
{
	var _val = $('#filterTransactions').attr('value');
	
	$(".transactionList .listItem").hide().filter(function( index ) {
		switch(_val)
		{
			case "0": return true;
			case "1": return $(this).hasClass("received");
			case "2": return $(this).hasClass("sent");
		}
	}).show();
}