function submitBitprofileExport()
{
	var _pageView = $('#page_bitprofile_view');
							
	XETH.submitBitprofileExport( _pageView.find('.bitprofileID input').val() );
}

function bitprofileExportSuccessful(_data)
{
	XETH.fileBrowseSave(_data.bitprofile+'.txt', _data.data);
	notifySuccess('bitprofile backup created successful!');
}