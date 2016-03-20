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
    }

}
