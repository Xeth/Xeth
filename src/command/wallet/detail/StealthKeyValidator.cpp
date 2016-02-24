#include "StealthKeyValidator.hpp"


namespace Xeth{


StealthKeyValidator::StealthKeyValidator(const std::string &password) : 
    _password(password)
{}


bool StealthKeyValidator::operator()(StealthKey &key) const
{
    try
    {
        Ethereum::PrivateKey secret = key.getSpendPrivateKeys()[0].unlock(_password);
        return true;
    }
    catch(...)
    {}
    return false;
}


}
