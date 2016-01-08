var dropdown;

//$(document).ready(initUI);

function initUI() 
{
	/*
	$(window).on('resize', resizePage).trigger('resize');
	resizePage();
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
		"startDate": "2015-11-01",
		"endDate": moment(),
		"opens": "left",
		locale: {
      		format: 'YYYY-MM-DD'
    	},
		ranges: {
           'All Time': ["2015-11-01", moment()],
           'Today': [moment(), moment()],
           'Yesterday': [moment().subtract(1, 'days'), moment().subtract(1, 'days')],
           'Last 7 Days': [moment().subtract(6, 'days'), moment()],
           'Last 30 Days': [moment().subtract(29, 'days'), moment()],
           'This Month': [moment().startOf('month'), moment().endOf('month')],
           'Last Month': [moment().subtract(1, 'month').startOf('month'), moment().subtract(1, 'month').endOf('month')]
        }
	}, function(start, end, label) {
	  console.log('New date range selected: ' + start.format('YYYY-MM-DD') + ' to ' + end.format('YYYY-MM-DD') + ' (predefined range: ' + label + ')');
	});
	
	$('.daterange').on('change.daterangepicker', function(ev, picker) {
		updateDaterange($(this),picker);
	}).trigger('change.daterangepicker');
	
	$('.nav li a').on('click', function(){ navNotifyNone($(this)) });
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

function updateDaterange(_target, _picker)
{
	if(_picker)
	{
		_target.val(_picker.chosenLabel);
		_target.attr("title", _picker.startDate.format('YYYY-MM-DD') + ' - ' + _picker.endDate.format('YYYY-MM-DD') );
	}
	else
	{
		_target.attr("title", _target.val());
		_target.val("All Time");
	}
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