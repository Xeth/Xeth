var ProfileResolver = function(){

    this.getPaymentAddress = function(uri){
        return XETH_bitprofile.resolvePaymentAddress(uri);
    };

}
