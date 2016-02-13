var receiveQR;
var receiveSubmitTimeout;

function initReceive() 
{
	receiveQR = new QRCode( document.getElementById("receiveQR"), {
		width : 480,
		height : 480,
		colorDark: "#1C2E30",
		colorLight: "rgba(255,255,255,0)",
		correctLevel : QRCode.CorrectLevel.M
	});
	
	$( '#receiveTo' ).change(submitReceiveForm);
	$( '#receiveAmount' ).on('change', submitReceiveForm);
	$( '#receiveMessage' ).on('change', submitReceiveForm);
	$( '#receiveAmount' ).on('input', delaySubmitReceiveForm);
	$( '#receiveMessage' ).on('input', delaySubmitReceiveForm);
	
	$('#saveReceiveQR').on('click', saveReceiveQR);
	$('#copyReceiveURI').on('click', copyReceiveURI);
	
	generateReceiveCode();
}

function generateReceiveCode () 
{		
	var _address = $('#receiveTo .select .account > .address').text();
	if(_address)
	{
		var _txt = 	"xeth:"+
					_address;
					//accountList[$('#receiveTo').attr("value")].address;
		
		var _vars = "?";
		
		if($('#receiveAmount').val()>0) _vars += "amount=" + $('#receiveAmount').val();
		
		if($('#receiveMessage').val().length>0)
		{
			if(_vars!="?") _vars += "&";
			_vars += "message=" + $('#receiveMessage').val();
		}
		
		if(_vars!="?") _txt += _vars;
		
		//console.log(_txt);
			
		$('.receive .txtURI').val(_txt);
		
		receiveQR.makeCode(_txt);
	}
	else
	{
		$('.receive .txtURI').val("");
		receiveQR.clear();
	}
}

function submitReceiveForm() 
{		
	var _address = $('#receiveTo .select .account.bitprofile .id').text();
	if(!_address) _address = $('#receiveTo .select .account > .address').text();
	
	if(_address)
	{
		XETH.submitReceiveForm(	_address,
								$('#receiveAmount').val(),
								$('#receiveMessage').val());
	}
	else
	{
		setReceiveURI("");
	}
}

function delaySubmitReceiveForm()
{
	window.clearTimeout(receiveSubmitTimeout);
	receiveSubmitTimeout = window.setTimeout( submitReceiveForm , 1000 );
}

function saveReceiveQR () 
{
	var _img = ($( '#receiveQR img' ).attr("src").replace('image/png', 'image/octet-stream'));
	var _name = "QR_"+moment()+'.png';
	//$( '#receiveQR img' ).attr("name",_name);
	//window.location.href = _img;
	//saveFile(2, _img, _name);
	XETH.fileBrowseSave(_name, _img);
}


function copyReceiveURI()
{
	XETH.setClipboard($('.receive .txtURI').val());
}

function setReceiveURI(_txt)
{		
	$('.receive .txtURI').val(_txt);
	(_txt.length>0)? receiveQR.makeCode(_txt) : receiveQR.clear();
}
