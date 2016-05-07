#include "ReadProfileInfoCommand.hpp"


namespace Xeth{


ReadProfileInfoCommand::ReadProfileInfoCommand(Ethereum::Connector::Provider &provider, const Settings &settings) :
    _resolver(provider, GetBitprofileNetwork(settings)),
    _settings(settings)
{}



QVariant ReadProfileInfoCommand::operator()(const QString &uri)
{
    BitProfile::Profile profile = _resolver.lookupProfile(uri.toStdString());
    if(profile.isNull())
    {
        return QVariant::fromValue(false);
    }

    QString detailsPath =  profile.get("details").c_str();

    if(!detailsPath.length())
    {
        return QString("");
    }
    else
    {
        IpfsReader reader(_settings);
        if(detailsPath.contains("ipns://"))
        {
            IpfsNameRegistrar namereg(_settings);
            detailsPath = namereg.resolve(detailsPath.remove(0, 7));
            if(!detailsPath.length())
            {
                return QString("");
            }
        }
        else
        {
            detailsPath.remove(0, 7);
        }
        QVariantMap details = reader.readJson(detailsPath).toVariantMap();
        if(details.contains("avatar"))
        {
            details["avatar"] = QString(reader.readBytes(details["avatar"].toString().remove(0,7)));
        }
        return details;
    }
}



}
