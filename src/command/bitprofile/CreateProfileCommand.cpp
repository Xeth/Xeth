#include "CreateProfileCommand.hpp"


namespace Xeth{


CreateProfileCommand::CreateProfileCommand(Ethereum::Connector::Provider &provider, DataBase &database, Synchronizer &synchronizer, const Settings &settings) :
    _resolver(provider, GetBitprofileNetwork(settings)),
    _database(database),
    _synchronizer(synchronizer)
{}


QVariant CreateProfileCommand::operator()(const QVariantMap &request)
{
    if(!request.contains("context")||!request.contains("id")||!request.contains("password")||!request.contains("account"))
    {
        return QVariant::fromValue(false);
    }
    BitProfile::Registrar registrar = _resolver.lookupRegistrar(request["context"].toString().toStdString());
    if(registrar.isNull())
    {
        return QVariant::fromValue(false);
    }

    registrar.setGasPrice(BigInt(request.contains("price") ? request["price"].toString().toStdString(): "0"));
    registrar.setGasLimit(BigInt(request.contains("gas") ? request["gas"].toString().toStdString() : "0"));

    EthereumKeyStore & keys = _database.getEthereumKeys();
    std::string payer = request["account"].toString().toStdString();
    std::string password = request["password"].toString().toStdString();
    if(keys.find(payer)==keys.end())
    {
        //trying to redeem key
        StealthSpendKeyRedeemer redeemer(_database);
        if(redeemer.redeem(payer, password))
        {
            _synchronizer.watchAddress(payer);
        }
    }
    else
    {
        StealthPaymentStore &payments = _database.getStealthPayments();
        if(!payments.get(payer).empty())
        {
            _synchronizer.watchAddress(payer);
        }
    }

    BitProfile::ProfileAdministrator profile = BitProfile::ProfileAdministrator::CreateProfile(registrar, request["id"].toString().toStdString(), payer, password);
    if(profile.isNull())
    {
        return QVariant::fromValue(false);
    }
    else
    {
        if(!_database.getBitProfiles().insert(BitProfile::ProfileDescriptor(profile)))
        {
            throw std::runtime_error("failed to save profile");
        }
    }
    return QVariant::fromValue(true);
}


}
