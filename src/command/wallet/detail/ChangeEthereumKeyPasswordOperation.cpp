#include "ChangeEthereumKeyPasswordOperation.hpp"

namespace Xeth{


EthereumKey ChangeEthereumKeyPasswordOperation::operator()(const EthereumKey &key, const QString &password, const QString &newPassword)
{
    Ethereum::PrivateKey secret = key.getPrivateKey().unlock(password.toStdString());
    CipherFactory cipherFactory;
    return EthereumKey(secret, cipherFactory.create(), newPassword.toStdString());
}


}
