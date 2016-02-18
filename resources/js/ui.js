var dropdown;

//$(document).ready(initUI);

function initUI() 
{
	/*
	$(window).on('resize', resizePage).trigger('resize');
	resizePage();
	*/
	/*
	$('.editableTxt').editable({
		mode: 'inline',
		onblur: function(v) {
			alert(v);
		},
		validate: function(v) {
			if(!v) return 'Required field!';
		}
	});
	
	$('.editableTxt').editable('option', 'validate', function(v) {
		if(!v) return 'Required field!';
	});
	*/
	$(document).tooltip({
		position: { my: "center bottom", at: "center top-5" },
		show: { duration: 200 },
		hide: { duration: 200 }
	});
	
	$('.section_fee').tooltip({	
		position: { my: "center top", at: "center bottom" },
		show: { duration: 200 },
		hide: { duration: 200 }});
		
	$(".scrollpage").mCustomScrollbar({
		scrollButtons:{enable:true},
		theme:"light-thick",
		scrollbarPosition:"outside",
		scrollInertia:200,
		callbacks:{
			onUpdate:function(){
			  onSelectorChange(_target);
			}
		}
	});
	
	//$(".scrollpage .holder").resize(function(){ scrollpageUpdated($(this)); });

	$(document).on('click', clickOutside);
	$('.select').on('click', clickSelect);
	$('.dropdownBox a').on('click', clickDropdownOption);
		
	$('.checkbox').on('click', clickCheckbox);
	
	$('.slider').slider(
	{
		start: function( event, ui ) {
			hideDropdowns();
		}
	});
	
	$('.section_fee .slider').slider( "value", 10 );
	
	$('.daterange').daterangepicker({
		//"autoUpdateInput": false,
		"showDropdowns": true,
		"autoApply": true,
		"startDate": date0,
		"endDate": moment(),
		"opens": "left",
		locale: {
      		format: dateFormat
    	},
		ranges: {
           'All Time': [date0, moment()],
           'Today': [moment(), moment()],
           'Yesterday': [moment().subtract(1, 'days'), moment().subtract(1, 'days')],
           'Last 7 Days': [moment().subtract(6, 'days'), moment()],
           'Last 30 Days': [moment().subtract(29, 'days'), moment()],
           'This Month': [moment().startOf('month'), moment().endOf('month')],
           'Last Month': [moment().subtract(1, 'month').startOf('month'), moment().subtract(1, 'month').endOf('month')]
        }
	}, function(start, end, label) {
	  console.log('New date range selected: ' + start.format(dateFormat) + ' to ' + end.format(dateFormat) + ' (predefined range: ' + label + ')');
	});
	
	$('.daterange').on('change.daterangepicker', function(ev, picker) {
		updateDaterange($(this),picker);
	}).trigger('change.daterangepicker');
	
	//$('.nav li a').on('click', function(){ changePage($(this).attr('page')); });
	$('a[page]').on('click', btnChangePage);
	$('ul[page] a').on('click', btnChangeSubpage);
	/*
	$('.daterange').on('apply.daterangepicker', function(ev, picker) {
		updateDaterange($(this),picker);
	}).trigger('apply.daterangepicker');
	*/
	
	/*
	$('.tabs > li > a').on('click', clickTab);
	
	$('.scrollable').addClass('default-skin');
	$('.scrollable').customScrollbar({
		updateOnWindowResize: true,
		hScroll: false
	});
	
	$('.datepicker').datepicker();
	$('.datepicker').datepicker("setDate", "0");
	$('.datepicker').datepicker("option", "dateFormat", "dd.mm.yy" );
	*/
}

function clickSelect(e) 
{
	toggleDropdown(
		$(this).parent().find('.dropdownBox'), 
		!$(this).parent().find('.dropdownBox').hasClass('off')
	);
}

function clickDropdownOption(e) 
{
	//console.log(e);
	changeSelect($(this).first().parents().eq(2),$(this).parent().index(),$(this).index());
}

function changeSelect(_target,_val1,_val2) 
{
	var val = _target.find('ul li');
	var selectedOption = $(val[_val1]).children()[_val2];
	
	if(_target.hasClass('multiOption'))
	{
		val = _target.find('ul li')[_val1];
		selectedOption = $(val).children()[_val2];
	}
	
	var selectbox = _target.parent().find('.select');
	var target = _target.parent().find('.select .value')[0];
	if(target==undefined) target = selectbox[0];
	
	if(!selectbox.hasClass('fixedVal'))
	{
		target.innerHTML = selectedOption.innerHTML;
		$(_target).parent().attr('value', _val1);
	}
	_target.trigger('change');
	
	$(val).find('.active').removeClass('active');
	$(selectedOption).addClass('active');
	
	if(!_target.hasClass('keepOpened'))
	toggleDropdown(_target, true);
}

function toggleDropdown(_target, _state)
{
	dropdown = _target;
	hideDropdowns();
	dropdown.toggleClass('off',_state); 
}


function clickCheckbox(e) 
{
	toggleCheckbox(
		$(this), 
		!$(this).hasClass('on')
	);
}

function toggleCheckbox(_target, _state)
{
	_target.toggleClass('on',_state); 
	
	_target.trigger('change');
}


function setStepScrollbar(_target, _step) 
{
	_target.mCustomScrollbar("destroy");
	_target.mCustomScrollbar({
		scrollButtons:{enable:true,scrollType:"stepped"},
		theme:"light-thick",
		scrollbarPosition:"outside",
		scrollInertia:200,
		keyboard:{scrollType:"stepped"},
		mouseWheel:{scrollAmount:_step},
		snapAmount:_step,
		callbacks:{
			onBeforeUpdate:function(){
			  scrollpageUpdated(_target);
			}
		}
	});
}

function scrollpageUpdated(_target)
{
	if(_target.find(".holder").height()==0) _target.toggleClass('empty', true);
	else _target.toggleClass('empty', false);
}

function updateDaterange(_target, _picker)
{
	if(_picker)
	{
		_target.val(_picker.chosenLabel);
		_target.attr("title", _picker.startDate.format(dateFormat) + ' - ' + _picker.endDate.format(dateFormat) );
	}
	else
	{
		_target.attr("title", _target.val());
		_target.val("All Time");
	}
}

function btnChangePage(e)
{
	changePage($(this).attr('page'));
}

function btnChangeSubpage(e)
{
	changePage($(this).closest('ul').attr('page'), $(this).closest('li').index());
}

function changePage(_pageName, _sub)
{
	var _page = $('#'+_pageName);
	
	if(!_page.hasClass('active') || _sub>=0)
	{
		//console.log(_pageName);
		pageOff(_page.parent().children('.page.active').attr('id'), _pageName);
		pageOn(_pageName, _sub);
	}
}
function pageOff(_pageName, _pageNameNew)
{
	var _page = $('#'+_pageName);
	
	//console.log(_pageName,_pageNameNew);
	_page.trigger('off');
	pageHide(_page, _pageNameNew==_pageName);	
	_page.parent().children('.menu').find('.nav li.active').toggleClass('active',false);
}
function pageHide(_page, _on)
{
	_page.toggleClass('active',false);
	if(!_on) window.setTimeout( function(){ _page.addClass('off'); } , 150 );
}
function pageOn(_pageName, _sub)
{
	var _page = $('#'+_pageName);
	var _menuItem = (_sub>=0)? $(_page.parent().children('.menu').find('.nav[page="'+_pageName+'"] li')[_sub]).children('a') : _page.parent().children('.menu').find('.nav li a[page="'+_pageName+'"]');
		
	if(_sub>=0)
	{
		pageSubShow(_page, _sub);
	}
	else
	{
		pageShow(_page);
	}
	navNotifyNone(_menuItem);
	_menuItem.parent().toggleClass('active',true);
}
function pageShow(_page)
{
	_page.removeClass('off');
	window.setTimeout( function(){ _page.toggleClass('active',true); } , 10 );
}
function pageSubShow(_page, _sub)
{
	window.setTimeout( function(){
			if(_sub>=0) _page.trigger('change', _sub);
			pageShow(_page);},
			 250);
}

/*
function clickTab(e) 
{
	changeTab($(this).first().parents().eq(2),$(this).parent().index());
}

function changeTab(_target, _index)
{
	var _tabs = _target.find('ul.tabs li');
	var _selectedTab = $(_tabs[_index]).children()[0];
	var _tabPages = _target.find('.content');
	var _selectedPage = _tabPages[_index];
	
	
	//console.log(_selectedTab);
	
	$(_tabs).find('.active').removeClass('active');
	$(_selectedTab).addClass('active');
	
	$(_tabPages).removeClass('active');
	$(_selectedPage).addClass('active');
	
	//$(window).resize();
	$('.scrollable').customScrollbar("resize", true);
}*/

function clickOutside(e) 
{
	//console.log($(e.target).parent().hasClass('select'));
	
	if(
		dropdown === undefined ||
		e.target !== dropdown.parent().find('.select').get(0) && 
		dropdown.find($(e.target)).length === 0 &&
		$(e.target).parent().hasClass('select')===false
	)
	{
		hideDropdowns();
	}
}

function hideDropdowns()
{
	$(document).find('.dropdownBox').toggleClass('off',true);
}

/*
function resizePage()
{
	var _page = $('.contentPage');
	_page.css('min-height', $(window).height() - $('.header').outerHeight() - $('.footer').outerHeight() - parseFloat(_page.css('padding-top')) - parseFloat(_page.css('padding-bottom')) );
}
*/
