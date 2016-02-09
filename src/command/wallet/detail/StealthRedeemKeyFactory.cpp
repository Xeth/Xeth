#include "StealthRedeemKeyFactory.hpp"


namespace Xeth{


StealthRedeemKeyFactory::StealthRedeemKeyFactory(DataBase &database) :
    _database(database)
{}


EthereumKey StealthRedeemKeyFactory::create(const QJsonObject &payment, const std::string &password)
{
    return create(payment["txid"].toString().toStdString(), payment["secret"].toString().toStdString(), password);
}


EthereumKey StealthRedeemKeyFactory::create(const std::string &txid, const std::string &secret, const std::string &password)
{
    QJsonObject transaction = _database.getTransactions().get(txid.c_str());
    StealthKey stealthKey = _database.getStealthKeys().get(transaction["stealth"].toString().toStdString().c_str());

    Ethereum::Stealth::SharedSecret secretData = Literal<Ethereum::Stealth::SharedSecret>(secret);

    Ethereum::Stealth::RedeemKeyFactory redeemFactory;
    CipherFactory cipherFactory;

    return redeemFactory.create(stealthKey.getSpendPrivateKeys()[0].unlock(password), secretData, cipherFactory.create(), password);
}


}
