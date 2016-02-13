function initImportAddress() 
{		
	$('#importAddress_submit').on('click', submitImportAddress);
	/*
	$('#importAddress_file').change(function() {
			if($(this).val())
			{
				changePage('page_importAddress',0);
				$('#importAddress_address').val( this.files[0].name );
				console.log('val ',$(this).val(), document.getElementById('importAddress_file').files[0]);
			}
        });
	*/
}

function startImportAddressPage()
{
	//$('#importAddress_file').click();
	
	if(loadFileImportAddressPage())
	changePage('page_importAddress',0);
}

function loadFileImportAddressPage()
{
	var _file = XETH.fileBrowseLoad();
	
	if(_file)
	{
		resetImportAddressPage();
		$('#importAddress_address').val( _file );
		return true;
	}
	return false;
}

function resetImportAddressPage()
{
	//$('#importAddress_file').val('');
	$('#importAddress_address').val('');
	$('#importAddress_password').val('');
	$('#page_importAddress .formpage').toggleClass('waiting', false);
	toggleImportAddressError({password:false});
}

function toggleImportAddressError(_err)
{
	if(typeof _err.password !== "undefined") $("#page_importAddress .section_password").toggleClass('error', _err.password);
	
	checkNotifyError(_err, "please fill all mandatory fields correctly");
}

function submitImportAddress()
{
	var _password;
	
	_password = $("#importAddress_password").val().length <= 0;
	
	toggleImportAddressError({password:_password});
	
	if(!_password)
	{
		$('#page_importAddress .formpage').toggleClass('waiting', true);
		
		XETH.submitImportAddress(	//URL.createObjectURL( document.getElementById('importAddress_file').files[0] ),
									$('#importAddress_address').val(),
									$("#importAddress_password").val());
	}
}

function importAddressSuccessful()
{
	notifySuccess('address imported successful!');
	changeSelect($('.accountList.receive .dropdownBox'),1,0);
	changePage("page_receive");
	resetImportAddressPage();
}

function importAddressError(_err)
{
	toggleImportAddressError(_err);
	$('#page_importAddress .formpage').toggleClass('waiting', false);
}
