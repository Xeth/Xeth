#include "MoveProfileCommand.hpp"


namespace Xeth{


MoveProfileCommand::MoveProfileCommand(Ethereum::Connector::Provider &provider, BitProfileStore &store, const Settings &settings, Notifier &notifier) :
    _provider(provider),
    _store(store),
    _settings(settings),
    _notifier(notifier)
{}


QVariant MoveProfileCommand::operator()(const QVariantMap &request)
{
    if(!request.contains("old")||!request.contains("context")||!request.contains("name")||!request.contains("password"))
    {
        return QVariant::fromValue(false);
    }

    BitProfileStore::Iterator it = _store.find(request["old"].toString());
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

    QString name = request["name"].toString();
    BigInt gas(request.contains("gas")?request["gas"].toString().toStdString():"0");
    MoveProfileAction *action = MoveProfileAction::Create(MoveProfileOperation(_store, admin, registrar, name, request["password"].toString(), gas, _notifier));
    action->run();
    return QVariant::fromValue(true);
}

}
