var currentBitprofilePage;

function initBitprofile() 
{
	$('#page_bitprofile .nav li a').on('click', clickBitprofileNav);
	
	$('#page_bitprofile_view .btn.editBitprofile').on('click', setupPageBitprofileEdit);
	$('#page_bitprofile_edit .submitCancel').on('click', cancelPageBitprofileEdit);
}

function clickBitprofileNav(e)
{
	if(!$(this).parent().hasClass('active'))
	{
		$(this).closest('.subNav').find('li.active').toggleClass('active',false);
		$(this).closest('.page').find('.page').toggleClass('active',false);
		
		changeBitprofileNav($(this));
	}
}

function changeBitprofileNav(_nav)
{
	var _pageName = _nav.attr('page');
	if(!_pageName) _pageName = _nav.closest('ul').attr('page');
	
	var _page = $('#'+_pageName);
	//var _changePageDelay = $('#'+_pageName)
	
	_nav.parent().toggleClass('active',true);
	
	if(_pageName=="page_bitprofile_view")
	{
		window.setTimeout( function(){
			setupPageBitprofileView( _nav.find('.id').text(),
									_nav.find('.name').text(),  
									_nav.find('.avatar .img img').attr('src'))},
			 250);
	}
	else 
	{
		_page.toggleClass('active',true);
	}
}

function setupPageBitprofileView(_id, _name, _avatar)
{
	var _page = $('#page_bitprofile_view');
	
	_page.find('.bitprofileID input').val(_id);
	_page.find('input.name').val(_name);
	_page.find('.avatar .img img').attr('src', _avatar);
	
	_page.toggleClass('active',true);
}

function showPageBitprofileView()
{
	window.setTimeout( function(){$('#page_bitprofile_view').toggleClass('active',true);} , 250 );
}

function setupPageBitprofileEdit()
{
	var _pageView = $('#page_bitprofile_view');
	var _pageEdit = $('#page_bitprofile_edit');
	
	_pageEdit.find('.bitprofileID input').val( _pageView.find('.bitprofileID input').val() );
	_pageEdit.find('input.name').val( _pageView.find('input.name').val() );
	_pageEdit.find('input.avatarURL').val( _pageView.find('.avatar .img img').attr('src') );
	_pageEdit.find('.avatar .img img').attr('src', _pageEdit.find('input.avatarURL').val() );
	
	_pageView.toggleClass('active',false);
	_pageEdit.toggleClass('active',true);
}

function cancelPageBitprofileEdit()
{
	var _pageView = $('#page_bitprofile_view');
	var _pageEdit = $('#page_bitprofile_edit');
	
	//_pageView.toggleClass('active',true);
	showPageBitprofileView();
	_pageEdit.toggleClass('active',false);
}