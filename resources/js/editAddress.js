function initEditAddress() 
{		
	$('#page_editAddress').change(function(event,_index) {
			if(event.target.id == 'page_editAddress')
			resetEditAddressPage();
        });
		
	$( '#editAddress_account' ).change(function() {
			resetEditAddressPage();
        });
	
	$('#editAddress_submit').on('click', submitEditAddress);
}

function resetEditAddressPage()
{
	$('#editAddress_password').val('');
	$('#editAddress_newpassword').val('');
	$('#editAddress_newrepassword').val('');
	$('#page_editAddress .formpage').toggleClass('waiting', false);
	toggleEditAddressError({password:false, newpassword:false, newrepassword:false});
}

function toggleEditAddressError(_err)
{
	if(typeof _err.password !== "undefined") $("#page_editAddress .section_password").toggleClass('error', _err.password);
	if(typeof _err.newpassword !== "undefined") $("#page_editAddress .section_newpassword").toggleClass('error', _err.newpassword);
	if(typeof _err.newrepassword !== "undefined" || _err.newpassword)
	{
		if(_err.newrepassword || _err.newpassword) $("#editAddress_newRepassword").val('');
		$("#page_editAddress .section_newrepassword").toggleClass('error', _err.newrepassword || _err.newpassword);
	}
	
	checkNotifyError(_err, "please fill all mandatory fields correctly");
}

function submitEditAddress()
{
	var _password, _newpassword, _newrepassword;
	
	_password = $("#editAddress_password").val().length <= 0;
	_newpassword = $("#editAddress_newPassword").val().length <= 0;
	_newrepassword = $("#editAddress_newRepassword").val().length <= 0 || $("#editAddress_newRepassword").val() != $("#editAddress_newPassword").val() || _newpassword;
	
	toggleEditAddressError({password:_password, newpassword:_newpassword, newrepassword:_newrepassword});
	
	if(!_password && !_newpassword && !_newrepassword)
	{
		$('#page_editAddress .formpage').toggleClass('waiting', true);
		
		XETH.submitEditAddress(	accountItem( $('#editAddress_account').attr('value') ).address,
								$("#editAddress_password").val(),
								$("#editAddress_newPassword").val());
	}
}

function editAddressSuccessful(_data)
{
	notifySuccess('password changed successful!');
	resetEditAddressPage();
	changePage("page_settings");
}

function editAddressError(_err)
{
	toggleEditAddressError(_err);
	$('#page_editAddress .formpage').toggleClass('waiting', false);
}
