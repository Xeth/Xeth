
#include "AddressValidator.hpp"


namespace Xeth{


bool AddressValidator::validateAddress(const std::string &address)
{
    if(!address.compare(0, 2, "0x"))
    {
        if(address.length() < 22 || address.find_first_not_of("0123456789abcdefABCDEF", 2) != std::string::npos)
        {
            return false;
        }

    }
    else
    {
        if(address.length() < 20 || address.find_first_not_of("0123456789abcdefABCDEF") != std::string::npos)
        {
            return false;
        }
    }
    return true;
}


bool AddressValidator::validateStealth(const std::string &)
{
    return true; //its validated when is unserialized
}



bool StealthAddressValidator::operator()(const std::string &address)
{
    AddressValidator validator;
    return validator.validateStealth(address);
}


bool HexAddressValidator::operator()(const std::string &address)
{
    AddressValidator validator;
    return validator.validateAddress(address);
}


}
