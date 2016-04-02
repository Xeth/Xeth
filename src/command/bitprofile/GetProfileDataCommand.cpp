#include "GetProfileDataCommand.hpp"


namespace Xeth{


GetProfileDataCommand::GetProfileDataCommand(Ethereum::Connector::Provider &provider, const Settings &settings) :
    _resolver(provider, GetBitprofileNetwork(settings))
{}


QVariant GetProfileDataCommand::operator()(const QVariantMap &request)
{
    if(!request.contains("key")||!request.contains("uri"))
    {
        return QVariant::fromValue(false);
    }

    BitProfile::Profile profile = _resolver.lookupProfile(request["uri"].toString().toStdString());

    if(profile.isNull())
    {
        return QVariant::fromValue(false);
    }

    return QString(profile.get(request["key"].toString().toStdString()).c_str());
}


}
