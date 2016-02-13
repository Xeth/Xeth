function initExportAddress() 
{		
	$('#exportAddress_submit').on('click', submitExportAddress);
}

function resetExportAddressPage()
{
	$('#exportAddress_password').val('');
	$('#page_exportAddress .formpage').toggleClass('waiting', false);
	toggleExportAddressError({password:false});
}

function toggleExportAddressError(_err)
{
	if(typeof _err.password !== "undefined") $("#page_exportAddress .section_password").toggleClass('error', _err.password);
	
	checkNotifyError(_err, "please fill all mandatory fields correctly");
}

function submitExportAddress()
{
	/*
	var _password;
	
	_password = $("#exportAddress_password").val().length <= 0;
	
	toggleExportAddressError({password:_password});
	
	if(!_password)
	*/
	{
		$('#page_exportAddress .formpage').toggleClass('waiting', true);
		
		XETH.submitExportAddress(	accountItem( $('#exportAddress_account').attr('value') ).address );/*,
									$("#exportAddress_password").val());*/
	}
}

function exportAddressSuccessful(_data)
{
	//saveFile(0, _data.data, _data.address);
	XETH.fileBrowseSave(_data.address+'.txt', _data.data);
	notifySuccess('address backup created successful!');
	resetExportAddressPage();
	changePage("page_settings");
}

function exportAddressError(_err)
{
	toggleExportAddressError(_err);
	$('#page_exportAddress .formpage').toggleClass('waiting', false);
}
