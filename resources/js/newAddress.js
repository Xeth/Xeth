var newAddressPoolHex = null;

function initNewAddress() 
{	
	$('#page_newAddress').change(function(event,_index) {
			if(event.target.id == 'page_newAddress')
			startNewAddressPage();
        });
	$('#page_newAddress').on('off', function(event) {
			if(event.target.id == 'page_newAddress');
			newAddressSeedOFF();
        });
		
	$('#skipNewAddressSeed').on('click', skipNewAddressSeed);
	
	$('#createNewAddress').on('click', submitNewAddressCreate);
}

function skipNewAddressSeed()
{
	finishNewAddressSeed(null);
}

function startNewAddressPage()
{
	resetNewAddressPage();
	
	newAddressSeedLoader(0);
	changePage("page_newAddress_seed");
	
	ninja.seeder.init(newAddressSeedLoader, finishNewAddressSeed);
	$(document).on('mousemove', ninja.seeder.seed);
	$(document).on('click', SecureRandom.seedTime);
	$(document).on('keydown', ninja.seeder.seedKeyPress);
}

function resetNewAddressPage()
{
	$('#newAddressPassword').val('');
	$('#newAddressRepassword').val('');
	toggleCheckbox($('#newAddress_stealth'),false);
	$('#page_newAddress_create .formpage').toggleClass('waiting', false);
	toggleNewAddressError({password:false, repassword:false});
}

function newAddressSeedLoader(_percent)
{
	if(_percent>0) _percent--;
	console.log('newAddressSeedLoader'+_percent);
	$('#newAddressSeedLoader .loader .value').css('width', _percent+'%');
	$('#newAddressSeedLoader .loader .txt .percent').text(_percent);
	$('#newAddressSeedLoader').attr('loader', _percent);
}

function finishNewAddressSeed(_hex)
{
	console.log('finishNewAddressSeed'+_hex);
	newAddressPoolHex = _hex;
	newAddressSeedOFF();
	newAddressSeedLoader(101);
	changePage("page_newAddress_create");
}

function newAddressSeedOFF()
{
	console.log('newAddressSeedOFF');
	$(document).off('mousemove', ninja.seeder.seed);
	$(document).off('click', SecureRandom.seedTime);
	$(document).off('keydown', ninja.seeder.seedKeyPress);
}

function toggleNewAddressError(_err)
{
	if(typeof _err.password !== "undefined") $("#page_newAddress_create .section_password").toggleClass('error', _err.password);
	if(typeof _err.repassword !== "undefined" || _err.password)
	{
		if(_err.repassword || _err.password) $("#page_newAddress_create .repassword").val('');
		$("#page_newAddress_create .section_repassword").toggleClass('error', _err.repassword || _err.password);
	}
	
	checkNotifyError(_err, "please fill all mandatory fields correctly");
}

function submitNewAddressCreate()
{
	var _password, _repassword;
	
	_password = $("#page_newAddress_create .password").val().length <= 0;
	_repassword = $("#page_newAddress_create .repassword").val().length <= 0 || $("#page_newAddress_create .repassword").val() != $("#page_newAddress_create .password").val() || _password;
	
	toggleNewAddressError({password:_password, repassword:_repassword});
	
	if(!_password && !_repassword)
	{
		$('#page_newAddress_create .formpage').toggleClass('waiting', true);
		
		XETH.submitNewAddressCreate(	newAddressPoolHex,
										$('#newAddress_stealth').hasClass('on'),
										$("#page_newAddress_create .password").val());
	}
}

function newAddressSuccessful()
{
	notifySuccess('new address created successful!');
	//resetNewAddressPage();
	changeSelect($('.accountList.receive .dropdownBox'),1,0);
	changePage("page_receive");
}

function newAddressError(_err)
{
	toggleNewAddressError(_err);
	$('#page_newAddress_create .formpage').toggleClass('waiting', false);
}
