#include "EthereumKeyValidator.hpp"


namespace Xeth{


void EthereumKeyUnlocker::operator()(EthereumKey &key, const std::string &password) const
{
    try{
    key.getPrivateKey().unlock(password);
    }catch(const std::exception &e)
    {
        qDebug()<<"unlocker exception : "<<e.what();
        throw e;
    }
}




}
