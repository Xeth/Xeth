function initBitprofile() 
{
	updateBitprofiles();
	//changePage("page_bitprofile_view",0);
	
	setStepScrollbar($(".scrollpage.bitprofileList"), 80);
	
	$('#page_bitprofile_view').change(function(e,_index) {
			var length = $('.bitprofileList .nav li').length;
			if(_index>=0 && _index<length) changePageBitprofileView(_index);
			else changePageBitprofileView(0);
        });
		
	$('#page_bitprofile_view .btn.editBitprofile').on('click', setupPageBitprofileEdit);
	$('#page_bitprofile_view .btn.backupBitprofile').on('click', submitBitprofileExport);
	
	
	$('#page_bitprofile_new .btnSubmit').on('click', function(){submitBitprofileForm('new')});
	$('#page_bitprofile_edit .btnSubmit').on('click', function(){submitBitprofileForm('edit')});
	
	$('#page_bitprofile_edit .submitCancel').on('click', cancelPageBitprofileEdit);
	$('#page_bitprofile_new .submitCancel').on('click', function(){resetBitprofileForm('new')});
	
	initImportBitprofile();
}

function startBitprofilePage()
{
	changePage("page_bitprofile");
	if($('.bitprofileList .nav li').length>0) changePage("page_bitprofile_view",0);
}

function updateBitprofiles(_list)
{
	$('.bitprofileList .nav').html('');
	
	//initAccountItem();
	
	//for(var i=0; i<_list.length; i++)
	if(_list)
	{
		for(var i=_list.length-1; i>=0; i--)
		{
			addBitprofile(_list[i]);
		}
	}
	//else filterAccounts();
}

function addBitprofile(_data)
{
	var _newitem =	$(
					'<li><a><span class="avatar"><span class="img"><img src="'+
					checkAvatar(_data.avatar)+
					'" onerror="errorAvatar($(this))" /></span></span><span class="name">'+
					checkAlias(_data.alias)+
					'</span><span class="id">'+
					_data.bitprofile+
					'</span></a></li>'
					);
					
	
	_newitem.find('a').on('click', btnChangeSubpage);
	
	$('.bitprofileList .nav').prepend(_newitem);
}

function editBitprofile(_data)
{
	var _nav = $( $('#page_bitprofile .bitprofileList li')[ bitprofileItem(_data.bitprofile) ] ).children('a');
	
	_nav.find('.name').text(checkAlias(_data.alias));
	_nav.find('.avatar .img img').attr('src', checkAvatar(_data.avatar));
}

function bitprofileItem(_id)
{
	return $('.bitprofileList li').filter(function( index ) {
		return $(this).find('.id').text()==_id;
	}).index();
}

function changePageBitprofileView(_index)
{
	var _nav = $( $('#page_bitprofile .bitprofileList li')[_index] ).children('a');
	//console.log('changePageBitprofileView',_nav);
	setupPageBitprofileView( _nav.find('.id').text(),
							_nav.find('.name').text(),  
							_nav.find('.avatar .img img').attr('src'),  
							_nav.find('.avatar .img img').attr('original'))
}

function setupPageBitprofileView(_id, _name, _avatar, _avatarOriginal)
{
	var _page = $('#page_bitprofile_view');
	
	_page.find('.bitprofileID input').val(_id);
	_page.find('input.name').val((_name!=aliasEmpty)? _name : "");
	_page.find('.avatar .img img').attr('src', _avatar);
	_page.find('.avatar .img img').attr('original', _avatarOriginal);
}

function setupPageBitprofileEdit()
{
	resetBitprofileForm('edit');
	
	var _pageView = $('#page_bitprofile_view');
	var _pageEdit = $('#page_bitprofile_edit');
	var _avatarURL = _pageView.find('.avatar .img img').attr('src');
	
	_pageEdit.find('.bitprofileID input').val( _pageView.find('.bitprofileID input').val() );
	_pageEdit.find('input.name').val( _pageView.find('input.name').val() );
	//_pageEdit.find('input.avatarURL').val( (_pageView.find('.avatar .img img').attr('src')==avatarError)? _pageView.find('.avatar .img img').attr('original') : _pageView.find('.avatar .img img').attr('src') );
	
	_pageEdit.find('.avatar .img img').attr('src', _avatarURL );
	
	switch(_pageView.find('.avatar .img img').attr('src'))
	{
		case avatarError:
		{
			_avatarURL = _pageView.find('.avatar .img img').attr('original');
			break;
		}
		case avatarEmpty:
		{
			_avatarURL = "";
			break;
		}
	}
	_pageEdit.find('input.avatarURL').val( _avatarURL );
	
	pageHide(_pageView);
	pageShow(_pageEdit);
}

function cancelPageBitprofileEdit()
{
	var _pageView = $('#page_bitprofile_view');
	var _pageEdit = $('#page_bitprofile_edit');
	
	pageSubShow(_pageView);
	pageHide(_pageEdit);
}

function toggleBitprofileError(_page, _err)
{
	if(typeof _err.id !== "undefined") $(_page+" .section_id").toggleClass('error', _err.id);
	if(typeof _err.password !== "undefined") $(_page+" .section_password").toggleClass('error', _err.password);
	if(typeof _err.repassword !== "undefined" || _err.password)
	{
		if(_err.repassword || _err.password) $(_page+" .repassword").val('');
		$(_page+" .section_repassword").toggleClass('error', _err.repassword || _err.password);
	}
	
	checkNotifyError(_err, "please fill all mandatory fields correctly");
}

function submitBitprofileForm(_pagename)
{
	var _page, _id, _password, _repassword;
	
	_page = '#page_bitprofile_'+_pagename;
	_id = $(_page+" .bitprofileID input").val().length <= 0;
	_password = $(_page+" .password").val().length <= 0;
	if($(_page+" .repassword").length>0) _repassword = $(_page+" .repassword").val().length <= 0 || $(_page+" .repassword").val() != $(_page+" .password").val() || _password;
	
	toggleBitprofileError(_page, {id:_id, password:_password, repassword:_repassword});
	
	if(!_id && !_password && !_repassword)
	{
		$(_page+' .formpage').toggleClass('waiting', true);
		sendBitprofileForm(	_pagename,
							$(_page+" .bitprofileID input").val(),
							$(_page+" .name").val(),
							$(_page+" .avatarURL").val(),
							$(_page+" .password").val(),
							$(_page+" .section_fee .fee .gas").text());
	}
}

function sendBitprofileForm(_pagename, _bitprofile, _alias, _avatar, _password, _fee)
{
	switch(_pagename)
	{
		case 'new':
		{
			XETH.submitBitprofileCreate(_bitprofile, _alias, _avatar, _password, _fee);
			break;
		}
		case 'edit':
		{
			XETH.submitBitprofileEdit(_bitprofile, _alias, _avatar, _password, _fee);
			break;
		}
	}
}

function resetBitprofileForm(_pagename)
{
	var _page = '#page_bitprofile_'+_pagename;
	
	toggleBitprofileError(_page, {id:false, password:false, repassword:false});
	
	$(_page+" .bitprofileID input").val('');
	$(_page+" .password").val('');
	$(_page+" .repassword").val('');
	
	$(_page+" .name").val('');
	$(_page+" .avatarURL").val('');
	$(_page+" .avatar img").attr('src', checkAvatar());
	
	$(_page+' .formpage').toggleClass('waiting', false);
}

function bitprofileCreateSuccessful()
{
	notifySuccess('new bitprofile successfully created!');
	resetBitprofileForm('new');
	changePage('page_bitprofile_view', 0);
}

function bitprofileEditSuccessful(_id)
{
	notifySuccess('bitprofile successfully edited!');
	//resetBitprofileForm('edit');
	changePage('page_bitprofile_view', bitprofileItem(_id));
}

function submitBitprofileError(_pagename, _err)
{
	var _page = '#page_bitprofile_'+_pagename;
	
	toggleBitprofileError(_page, _err);
	$(_page+' .formpage').toggleClass('waiting', false);
}

function bitprofileCreateError(_err)
{
	submitBitprofileError('new', _err);
}

function bitprofileEditError(_err)
{
	submitBitprofileError('edit', _err);
}