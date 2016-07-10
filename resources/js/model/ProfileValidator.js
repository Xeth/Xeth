function ProfileValidator(){};


ProfileValidator.prototype.isValidName = function(name){
    return XETH_bitprofile.isIdValid(name);
}

ProfileValidator.prototype.isAvailable = function(data){
    return XETH_bitprofile.isIdAvailable(data);
}
