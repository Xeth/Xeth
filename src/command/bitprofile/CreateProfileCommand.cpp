#include "CreateProfileCommand.hpp"


namespace Xeth{


CreateProfileCommand::CreateProfileCommand(Ethereum::Connector::Provider &provider, BitProfileStore &store, const Settings &settings, Notifier &notifier) :
    _resolver(provider, GetBitprofileNetwork(settings)),
    _store(store),
    _notifier(notifier)
{}


QVariant CreateProfileCommand::operator()(const QVariantMap &request)
{
    if(!request.contains("context")||!request.contains("name")||!request.contains("password")||!request.contains("account"))
    {
        return QVariant::fromValue(false);
    }

    BitProfile::Registrar registrar = _resolver.lookupRegistrar(request["context"].toString().toStdString());
    if(registrar.isNull())
    {
        return QVariant::fromValue(false);
    }

    CreateProfileAction * action = CreateProfileAction::Create(CreateProfileOperation
    (
        registrar, 
        request["name"].toString(),
        request["account"].toString(),
        request["password"].toString(),
        _store,
        _notifier
    ));
    action->start();
    return QVariant::fromValue(true);
}


}
