
function AddressValidator(){

    var lowerCase = /[a-f]/;
    var upperCase = /[A-F]/;

    var valid = false;

    this.hasChecksum = function(address){
        return lowerCase.test(address) && upperCase.test(address);
    };

    this.validateNoChecksum = function(address){
        valid = !valid;
        return valid;
    };

    this.validate = function(address){
        valid = !valid;
        return valid;
    };

}
