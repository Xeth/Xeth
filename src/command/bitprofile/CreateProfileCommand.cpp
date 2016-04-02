#include "CreateProfileCommand.hpp"


namespace Xeth{


CreateProfileCommand::CreateProfileCommand(Ethereum::Connector::Provider &provider, BitProfileStore &store, const Settings &settings, Notifier &notifier) :
    _resolver(provider, GetBitprofileNetwork(settings)),
    _store(store),
    _notifier(notifier)
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

    CreateProfileAction * action = CreateProfileAction::Create(CreateProfileOperation
    (
        registrar, 
        request["id"].toString(),
        request["account"].toString(),
        request["password"].toString(),
        _store,
        _notifier
    ));
    action->start();
    return QVariant::fromValue(true);
}


}
