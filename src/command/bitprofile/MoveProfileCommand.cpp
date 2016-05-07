#include "MoveProfileCommand.hpp"


namespace Xeth{


MoveProfileCommand::MoveProfileCommand(Ethereum::Connector::Provider &provider, BitProfileStore &store, const Settings &settings) :
    _provider(provider),
    _store(store),
    _settings(settings)
{}


QVariant MoveProfileCommand::operator()(const QVariantMap &request)
{
    if(!request.contains("uri")||!request.contains("context")||!request.contains("id")||!request.contains("password"))
    {
        return QVariant::fromValue(false);
    }

    BitProfileStore::Iterator it = _store.find(request["uri"].toString());
    if(it==_store.end())
    {
        return QVariant::fromValue(false);
    }

    BitProfile::ProfileDescriptor descriptor = *it;
    BitProfile::ProfileAdministrator admin = BitProfile::ProfileAdministrator::FromDescriptor(_provider, descriptor);

    BitProfile::Resolver resolver(_provider, GetBitprofileNetwork(_settings));
    BitProfile::Registrar registrar = resolver.lookupRegistrar(request["context"].toString().toStdString());
    if(registrar.isNull())
    {
        return QVariant::fromValue(false);
    }

    BigInt price(request.contains("price") ? request["price"].toString().toStdString(): "0");

    admin.setGasPrice(price);
    registrar.setGasPrice(price);

    std::string name = request["id"].toString().toStdString();
    std::string password = request["password"].toString().toStdString();
    BigInt gas(request.contains("gas")?request["gas"].toString().toStdString():"0");

    if(!admin.move(registrar, name, password, gas))
    {
        return QVariant::fromValue(false);
    }
    else
    {
        if(!_store.rename(admin.getProfile().getURI(), BitProfile::Profile::URI(registrar.getURI(), name)))
        {
            return QVariant::fromValue(false);
        }
    }

    return QVariant::fromValue(true);
}

}
