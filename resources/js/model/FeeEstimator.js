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
        return this.parseFee(result);
    };

    this.parseFee = function(result){
        result["fee"] = XETH_convert.fromWei(result["fee"]);
        return result;
    };

    this.estimateCreateProfile = function(context, name, factor){
        return this.parseFee(XETH_bitprofile.estimate({operation:"register", name:name, context:context, factor:factor}));
    };
    
    this.estimateStealthLink = function(uri, stealth, factor){
        var request = {operation:"stealth", factor: factor};
        if(uri)
        {
            request.uri = uri;
            request.stealth = stealth;
        }
        return this.parseFee(XETH_bitprofile.estimate(request));
    };

    this.estimateEdit = function(uri){
        return this.parseFee(XETH_bitprofile.estimate({operation:"edit", factor:factor, uri:uri}));
    };

    this.estimateMoveProfile = function(uri, context, name){
        return this.parseFee(XETH_bitprofile.estimate({operation:"move", uri:uri, context:context, name:name}));
    };
}
