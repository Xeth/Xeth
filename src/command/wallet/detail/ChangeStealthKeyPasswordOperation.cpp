#include "ChangeStealthKeyPasswordOperation.hpp"


namespace Xeth{


StealthKey ChangeStealthKeyPasswordOperation::operator()(const StealthKey &key, const QString &password, const QString &newPassword)
{
    const std::vector<StealthKey::SpendSecret> & spendKeys = key.getSpendPrivateKeys();
    std::vector<StealthKey::SpendSecret> newSpendKeys;
    CipherFactory cipherFactory;

    std::string pass = password.toStdString();
    std::string newPass = newPassword.toStdString();

    for(std::vector<StealthKey::SpendSecret>::const_iterator it = spendKeys.begin(), end=spendKeys.end(); it!=end; ++it)
    {
        newSpendKeys.push_back(StealthKey::SpendSecret(it->unlock(pass), cipherFactory.create(), newPass));
    }
    return StealthKey(key.getScanPrivateKey(), key.getScanPublicKey(), newSpendKeys, key.getSpendPublicKeys());
}


}
