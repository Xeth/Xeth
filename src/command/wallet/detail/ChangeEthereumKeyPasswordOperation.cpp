#include "ChangeEthereumKeyPasswordOperation.hpp"

namespace Xeth{


EthereumKey ChangeEthereumKeyPasswordOperation::operator()(const EthereumKey &key, const QString &password, const QString &newPassword)
{
    Ethereum::PrivateKey secret = key.getPrivateKey().unlock(password.toStdString());
    CipherFactory cipherFactory;
    EthereumKey result(secret, cipherFactory.create(), newPassword.toStdString());
    return result;
}


}
