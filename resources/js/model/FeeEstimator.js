var FeeEstimator = function(){

    this.estimate = function(from, to, amount, factor){
        amount = XETH_convert.toWei(amount);
        if(!amount)
        {
            return false;
        }
        var request = {from: from, to: to, amount:amount, factor: factor};
        var result = XETH_wallet.estimateFee(request);
        if(!result)
        {
            return false;
        }
        result["fee"] = XETH_convert.fromWei(result["fee"]);
        return result;
    };

    this.estimateCreateProfile = function(context, name, factor){
        return XETH_bitprofile.estimate({operation:"create", name:name, context:context, factor:factor});
    };
    
    this.estimateStealthLink = function(uri, stealth, factor){
        var request = {operation:"stealth", factor: factor};
        if(uri)
        {
            request.uri = uri;
            request.stealth = stealth;
        }
        return XETH_bitprofile.estimate(request);
    };

    this.estimateEdit = function(uri, key, value, factor){
        return XETH_bitprofile.estimate({operation:"edit", factor:factor, uri:uri, key:key, value:value});
    };

    this.estimateMoveProfile = function(uri, context, name){
        return XETH_bitprofile.estimate({operation:"move", uri:uri, context:context, name:name});
    };
}
