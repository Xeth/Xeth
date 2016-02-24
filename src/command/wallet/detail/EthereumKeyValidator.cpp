#include "EthereumKeyValidator.hpp"


namespace Xeth{


EthereumKeyValidator::EthereumKeyValidator(const std::string &password) :
    _password(password)
{}


bool EthereumKeyValidator::operator()(EthereumKey &key) const
{
    try
    {
        Ethereum::PrivateKey secret = key.getPrivateKey().unlock(_password);
        return true;
    }
    catch(...)
    {}
    return false;
}


}
