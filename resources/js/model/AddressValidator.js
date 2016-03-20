function AddressValidator(){

    var lowerCase = /[a-f]/;
    var upperCase = /[A-F]/;


    this.hasChecksum = function(address){
        return lowerCase.test(address) && upperCase.test(address);
    };

    this.validateNoChecksum = function(address){
        return XETH_wallet.validateAddress({address: address, checksum: false});
    };

    this.validate = function(address){
        return XETH_wallet.validateAddress(address);
    };

}
