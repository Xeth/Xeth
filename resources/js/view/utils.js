
function parseDecimals(value){
    return Math.ceil(((value < 1.0) ? value : (value % Math.floor(value))) * 100000000);
}

function splitAmount(value){
    if(!value) return {int:"0",dec:"0"};
    var data = (""+value).split('.');
    return {int:  data[0], dec: data[1]?data[1].substr(0,8):"0"};
}

function shortify(value, length){
    if(length==undefined){
        length = 57;
    }
    if(length<4 ||!value) return "";
    value = ""+value;
    if(value.length <= length) return value;
    if(length<11) return value.substr(0, length-3)+"...";
    var half = Math.round((length-3)/2);
    var short = value.substr(0,half)+"..."+value.substr(value.length-half, value.length);
    return short;
}

function notifyError(msg){
    notie.alert(3, msg, 5.0);
}

function notifySuccess(msg){
    notie.alert(1, msg, 5.0);
}

function feeWarning(callback){
    notie.confirm('<span class="title warning">WARNING!</span>'+
      'Fee is too low!<br>'+
      'Transaction may not be mined or even propagated<br>'+
      '<span class="question">Are you sure you want to send it?<span>', 
      'Yes, Send it anyway', 
      'No, I will change fee', 
     callback);
}


function combineFee(results){
    var result = {gas:0, price:0, fee:0};
    for(var i in results){
        result.gas += parseInt(results[i].gas);
        result.price += Number(results[i].price);
        result.fee += Number(results[i].fee);
    }
    result.fee = result.fee.toString();
    return result;
}