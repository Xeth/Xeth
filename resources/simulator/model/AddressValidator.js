function AddressValidator(){
    var currentAddress;
    var result = true;
    this.hasChecksum = function(address){
        if(currentAddress!=address)
        {
            result = !result;
            currentAddress = address;
        }
        return result;
    }
}
