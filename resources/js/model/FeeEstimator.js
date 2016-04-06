var FeeEstimator = function(){

    this.estimate = function(from, to, amount, factor){
        amount = XETH_convert.toWei(amount);
        if(!amount)
        {
            return false;
        }
        var request = {from: from, to: to, amount:amount};
        if(factor) request.factor = factor;
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

    var makeProfileRequest = function(request, factor){
        if(factor) request.factor = factor;
        return request;
    };

    this.estimateCreateProfile = function(context, name, factor){
        return this.parseFee(XETH_bitprofile.estimate(makeProfileRequest({operation:"register", name:name, context:context}, factor)));
    };
    
    this.estimateStealthLink = function(uri, stealth, factor){
        var request = {operation:"stealth"};
        if(uri)
        {
            request.uri = uri;
            request.stealth = stealth;
        }
        return this.parseFee(XETH_bitprofile.estimate(makeProfileRequest(request, factor)));
    };

    this.estimateEditProfile = function(uri, factor){
        var request = {operation:"edit", factor: factor};
        if(uri)
        {
            request.uri = uri;
        }
        return this.parseFee(XETH_bitprofile.estimate(request));
    };

    this.estimateMoveProfile = function(uri, context, name, factor){
        return this.parseFee(XETH_bitprofile.estimate(makeProfileRequest({operation:"move", uri:uri, context:context, name:name}, factor)));
    };
  
}
