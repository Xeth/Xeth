function initSend() 
{
	$( '#sendFrom' ).change(function() {
			setSendAmount($('#sendAmount').val());
        });
	
	$( '#sendToType' ).change(function() {
			updateSendToType();
        }).trigger('change');
		
	$( '#sendAmount' ).on('input', function() {
		setSendAmount($(this).val());
	});
	
	updateFee('#sendFee', 0);
	
	$( '#saveContact' ).change(function() {
			$('#sendAlias').parent().toggleClass('hidden', !$(this).hasClass('on'));
        }).trigger('change');
	
	$('#submitSend').on('click', submitSend);
}

function sendPaymentTo(_alias, _bitprofile, _address)
{
	var _to = _address;
	var _type = 0;
	
	if(_bitprofile)
	{
		_to = _bitprofile;
		_type = 1;
	}
	
	$('#sendToInput').val(_to);
	changeSelect($('#sendToType .dropdownBox'),_type,0);
	
	$('#sendAlias').val(_alias);
	
	toggleCheckbox($('#saveContact'), true);
	
	toggleSendError({address:false, alias:false});
}

function updateSendToType()
{
	var _placeholderMessage = [ 'address',
								'bitprofile id'];
	
	$('#sendToInput').attr('placeholder',_placeholderMessage[ $('#sendToType').attr('value') ]);
}

function setSendAmount(_eth)
{
	var _target = '#sendFee';
	var _slider = $(_target+' .slider');
	var _maxSlice = 0.3;
	var _sliderPos = _slider.slider( "value" ) / 100;
	var _balance = accountList[$('#sendFrom').attr("value")].balance;
	var _balanceAvailable = _balance / (1+_maxSlice*_sliderPos);
	var _fee = _eth*_maxSlice*_sliderPos;
	
	if(_eth>_balanceAvailable)
	{
		_eth = _balanceAvailable;
		$('#sendAmount').val(_eth.toFixed(ETH_dec));
		_fee = _balance - _eth;
	}
	
	if(isNaN(_eth) || _eth.length===0) _eth=0;
	
	//console.log(Number(_eth)+Number(_fee));
	
	$(_target+' .slider').slider({
		slide: function( event, ui ) {
			var _sliderPos = ui.value/100;
			var _currentFee = _eth*_maxSlice*_sliderPos;
			
			if(_balance-_currentFee < _eth)
			{
				_eth = _balance / (1+_maxSlice*_sliderPos);
				_currentFee = _balance - _eth;
				$('#sendAmount').val(_eth.toFixed(ETH_dec));
			}
			updateFee( _target, _currentFee );
			
			$(this).toggleClass('warning', ui.value<=0);
			//$( '#' + $(this).parent().attr("aria-describedby") ).toggleClass('warning', ui.value<=0);
	
			//console.log(Number(_eth)+Number(_currentFee));
		}
	});
	
	updateFee( _target, _fee);
}

function updateFee(_target, _val)
{
	var _maxDecimals = ETH_dec;
	var _gasLength = (_val / GAS_price).toString().split('.')[0].length;
	var _ethLength = _val.toString().split('.')[0].length;
	
	if(_gasLength+_ethLength>10) _maxDecimals = 20-(_gasLength+_ethLength);
	if(_maxDecimals<0) _maxDecimals = 0;
	
	$(_target+' .fee .gas').html( parseInt(_val / GAS_price) );
    $(_target+' .fee .eth').html( _val.toFixed(_maxDecimals) );
}

function clipboardPaste(_txt)
{
	$('#sendToInput').val(_txt);
}

function getClipboard()
{
	XETH.getClipboard();
}

function toggleSendError(_err)
{
	if(typeof _err.address !== "undefined") $("#page_send .section_to").toggleClass('error', _err.address);
	if(typeof _err.amount !== "undefined") $("#page_send .section_amount").toggleClass('error', _err.amount);
	if(typeof _err.password !== "undefined") $("#page_send .section_password").toggleClass('error', _err.password);
	if(typeof _err.alias !== "undefined") $("#page_send .section_alias").toggleClass('error', _err.alias);
}

function submitSend()
{
	var _address, _amount, _password;
	
	_address = $("#sendToInput").val().length <= 0;
	_amount = $("#sendAmount").val().length <= 0;
	_password = $("#sendPassword").val().length <= 0;
	_alias = ($('#saveContact').hasClass('on') )? $("#sendAlias").val().length <= 0 : false;
	
	toggleSendError({address:_address, amount:_amount, password:_password, alias:_alias});
	
	if(!_address && !_amount && !_password && !_alias)
	{
		$('#page_send .formpage').toggleClass('waiting', true);
		
		scheduleSaveContact($('#saveContact').hasClass('on'), $("#sendAlias").val(), $('#sendToType').attr('value'), $("#sendToInput").val());
		
		XETH.submitSend(accountList[$('#sendFrom').attr('value')].address,
					$('#sendToType').attr('value'),
					$("#sendToInput").val(),
					$("#sendAmount").val(),
					$('#sendFee .fee .gas').text(),
					$("#sendPassword").val());
	}
}

function sentSuccessful()
{
	notifySuccess('transaction sent successful!');
	resetSendForm();
	saveContact();
}

function resetSendForm()
{
	$("#sendToInput").val("");
	$("#sendAmount").val("");
	$("#sendPassword").val("");
	setSendAmount(0);
	toggleCheckbox($('#saveContact'),false);
	$("#sendAlias").val("");
	$('#page_send .formpage').toggleClass('waiting', false);
}