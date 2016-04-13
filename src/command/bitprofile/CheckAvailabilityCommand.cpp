#include "CheckAvailabilityCommand.hpp"


namespace Xeth{



CheckAvailabilityCommand::CheckAvailabilityCommand(Ethereum::Connector::Provider &provider, const Settings &settings) :
    _resolver(provider, GetBitprofileNetwork(settings))
{}



QVariant CheckAvailabilityCommand::operator()(const QString &name)
{
    BitProfile::Profile profile = _resolver.lookupProfile(name.toStdString());
    return QVariant::fromValue(!profile.isNull());
}


QVariant CheckAvailabilityCommand::operator()(const QVariantMap &request)
{
    if(!request.contains("id")||!request.contains("context"))
    {
        return QVariant::fromValue(false);
    }

    QString uri = request["id"].toString();
    uri += '@';
    uri += request["context"].toString();

    return operator()(uri);
}


}
