#include "StealthSpendKeyRedeemer.hpp"


namespace Xeth{


StealthSpendKeyRedeemer::StealthSpendKeyRedeemer(DataBase &database) :
    _database(database)
{}



bool StealthSpendKeyRedeemer::redeem(const std::string &address, const std::string &password)
{
    return redeem(address, password, password);
}


bool StealthSpendKeyRedeemer::redeem(const std::string &address, const std::string &masterPassword, const std::string &password)
{
    StealthPaymentStore &payments = _database.getStealthPayments();
    QJsonObject payment = payments.get(address);
    if(payment.empty())
    {
        return false;
    }
    EthereumKey key = createFromPaymentData(payment, masterPassword, password);
    return _database.getEthereumKeys().insert(key);
}


EthereumKey StealthSpendKeyRedeemer::createFromPaymentData(const QJsonObject &payment, const std::string &password)
{
    return createFromPaymentData(payment, password, password);
}


EthereumKey StealthSpendKeyRedeemer::createFromPaymentData(const QJsonObject &payment, const std::string &masterPassword, const std::string &keyPassword)
{
    return createFromPaymentData(payment["stealth"].toString().toStdString(), payment["secret"].toString().toStdString(), masterPassword, keyPassword);
}


EthereumKey StealthSpendKeyRedeemer::createFromPaymentData(const std::string &stealth, const std::string &secret, const std::string &password)
{
    return createFromPaymentData(stealth, secret, password, password);
}


EthereumKey StealthSpendKeyRedeemer::createFromPaymentData(const std::string &stealth, const std::string &secret, const std::string &masterPassword, const std::string &keyPassword)
{
    StealthKey stealthKey = _database.getStealthKeys().get(stealth.c_str());
    Ethereum::Stealth::SharedSecret secretData = Literal<Ethereum::Stealth::SharedSecret>(secret);
    Ethereum::Stealth::RedeemKeyFactory redeemFactory;
    CipherFactory cipherFactory;

    return redeemFactory.create(stealthKey.getSpendPrivateKeys()[0].unlock(masterPassword), secretData, cipherFactory.create(), keyPassword);
}

}
