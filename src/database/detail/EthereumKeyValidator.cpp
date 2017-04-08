#include "EthereumKeyValidator.hpp"


namespace Xeth{


void EthereumKeyUnlocker::operator()(EthereumKey &key, const std::string &password) const
{
    key.getPrivateKey().unlock(password);
}




}
