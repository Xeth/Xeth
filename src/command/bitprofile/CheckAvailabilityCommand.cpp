#include "CheckAvailabilityCommand.hpp"

namespace Xeth{



CheckAvailabilityCommand::CheckAvailabilityCommand(Ethereum::Connector::Provider &provider, const Settings &settings) :
    _resolver(provider, GetBitprofileNetwork(settings))
{}



QVariant CheckAvailabilityCommand::operator()(const QString &uri)
{
    BitProfile::Profile profile = _resolver.lookupProfile(uri.toStdString());
    bool result = profile.isNull();
    return QVariant::fromValue(result);
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
