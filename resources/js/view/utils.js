
function parseDecimals(value){
    return Math.ceil(((value < 1.0) ? value : (value % Math.floor(value))) * 100000000);
}

function shortify(value, length){
    if(length==undefined){
        length = 57;
    }
    value = ""+value;
    if(value.length <= length){
        return value;
    }
    var half = Math.round((length-3)/2);
    var short = value.substr(0,half)+"..."+value.substr(value.length-half, value.length);
    return short;
}
