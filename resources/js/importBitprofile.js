function initImportBitprofile() 
{		
	$('#importBitprofile_submit').on('click', submitBitprofileImport);
}

function startImportBitprofilePage()
{
	if(loadFileImportBitprofilePage())
	{
		changePage('page_bitprofile_import',0);
		$('#page_bitprofile .nav .importBitprofile').addClass('active');
	}
}

function loadFileImportBitprofilePage()
{
	var _file = XETH.fileBrowseLoad();
	
	if(_file)
	{
		resetImportBitprofilePage();
		$('#importBitprofile_address').val( _file );
		return true;
	}
	return false;
}

function resetImportBitprofilePage()
{
	$('#importBitprofile_address').val('');
	$('#importBitprofile_password').val('');
	$('#page_bitprofile_import .formpage').toggleClass('waiting', false);
	toggleImportBitprofileError({password:false});
}

function toggleImportBitprofileError(_err)
{
	if(typeof _err.password !== "undefined") $("#page_bitprofile_import .section_password").toggleClass('error', _err.password);
	
	checkNotifyError(_err, "please fill all mandatory fields correctly");
}

function submitBitprofileImport()
{
	var _password;
	
	_password = $("#importBitprofile_password").val().length <= 0;
	
	toggleImportBitprofileError({password:_password});
	
	if(!_password)
	{
		$('#page_bitprofile_import .formpage').toggleClass('waiting', true);
		
		XETH.submitBitprofileImport($('#importBitprofile_address').val(),
									$("#importBitprofile_password").val());
	}
}

function bitprofileImportSuccessful()
{
	notifySuccess('BitProfile imported successful!');
	resetImportBitprofilePage();
	changePage("page_bitprofile_view",0);
}

function bitprofileImportError(_err)
{
	toggleImportBitprofileError(_err);
	$('#page_bitprofile_import .formpage').toggleClass('waiting', false);
}
