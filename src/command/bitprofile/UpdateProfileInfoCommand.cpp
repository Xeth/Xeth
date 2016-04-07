#include "UpdateProfileInfoCommand.hpp"


namespace Xeth{


UpdateProfileInfoCommand::UpdateProfileInfoCommand(Ethereum::Connector::Provider &provider, BitProfileStore &store, Notifier &notifier, const Settings &settings) :
    _provider(provider),
    _store(store),
    _notifier(notifier),
    _settings(settings)
{}


QVariant UpdateProfileInfoCommand::operator()(const QVariantMap &request)
{
    if(!request.contains("uri")||!request.contains("details"))
    {
        return QVariant::fromValue(false);
    }

    BitProfileStore::Iterator it = _store.find(request["uri"].toString());
    if(it==_store.end())
    {
        return QVariant::fromValue(false);
    }

    BitProfile::ProfileAdministrator admin = BitProfile::ProfileAdministrator::FromDescriptor(_provider, *it);

    admin.setGasPrice(BigInt(request.contains("price") ? request["price"].toString().toStdString(): "0"));
    admin.setGasLimit(BigInt(request.contains("gas") ? request["gas"].toString().toStdString() : "0"));

    UpdateProfileInfoAction * action = UpdateProfileInfoAction::Create(UpdateProfileInfoOperation
    (
        admin, 
        request["password"].toString(),
        _settings,
        request["details"].toMap(),
        request.contains("ipns")?request["ipns"].toBool():false,
        _notifier
    ));
    action->start();
    return QVariant::fromValue(true);

}




}
