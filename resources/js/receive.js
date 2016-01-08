var receiveQR;

function initReceive() 
{
	receiveQR = new QRCode( document.getElementById("receiveQR"), {
		width : 480,
		height : 480,
		colorDark: "#1C2E30",
		colorLight: "rgba(255,255,255,0)",
		correctLevel : QRCode.CorrectLevel.M
	});
	
	$( '#receiveTo' ).change(generateReceiveCode);
	$( '#receiveAmount' ).on('input', generateReceiveCode);
	$( '#receiveMessage' ).on('input', generateReceiveCode);
	
	$('#saveReceiveQR').on('click', saveReceiveQR);
	$('#copyReceiveURI').on('click', copyReceiveURI);
}

function generateReceiveCode () 
{		
	var _txt = 	"xeth:"+
				accountList[$('#receiveTo').attr("value")].address;
	
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

function saveReceiveQR () 
{
	$( '#receiveQR img' ).attr("name","QR_"+moment());
	window.location.href = ($( '#receiveQR img' ).attr("src").replace('image/png', 'image/octet-stream'));
}


function copyReceiveURI()
{
	XETH.setClipboard($('.receive .txtURI').val());
}