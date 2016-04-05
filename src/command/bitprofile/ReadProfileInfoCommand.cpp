#include "ReadProfileInfoCommand.hpp"


namespace Xeth{


ReadProfileInfoCommand::ReadProfileInfoCommand(Ethereum::Connector::Provider &provider, const Settings &settings, Notifier &notifier) :
    _resolver(provider, GetBitprofileNetwork(settings)),
    _settings(settings),
    _notifier(notifier)
{}



QVariant ReadProfileInfoCommand::operator()(const QString &uri)
{
    BitProfile::Profile profile = _resolver.lookupProfile(uri.toStdString());
    if(profile.isNull())
    {
        return QVariant::fromValue(false);
    }

    ReadProfileInfoAction *action = ReadProfileInfoAction::Create(ReadProfileInfoOperation(profile, _settings, _notifier));
    action->start();
    return QVariant::fromValue(true);
}



}
