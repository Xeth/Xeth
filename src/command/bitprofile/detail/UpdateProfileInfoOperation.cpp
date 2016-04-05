#include "UpdateProfileInfoOperation.hpp"


namespace Xeth{


UpdateProfileInfoOperation::UpdateProfileInfoOperation
(
    const BitProfile::ProfileAdministrator &profile, 
    const QString &password,
    const Settings &settings,
    const QVariantMap &details,
    bool useIpns,
    Notifier &notifier
) :
    ProfileOperation(profile, password, notifier),
    _settings(settings),
    _details(details),
    _ipns(useIpns)
{}


void UpdateProfileInfoOperation::execute()
{

    QVariantMap profileData;
    QString link = _admin.getProfile().get("details").c_str();
    link.remove(0, 7);

    if(link.length())
    {
        IpfsReader reader(_settings);
        profileData = reader.readJson(link).toVariantMap();
        for(QVariantMap::iterator it = _details.begin(), end=_details.end(); it!=end; ++it)
        {
            if(it.value().isNull())
            {
                profileData.remove(it.key());
            }
            else
            {
                profileData[it.key()] = it.value();
            }
        }
    }
    else
    {
        for(QVariantMap::iterator it = _details.begin(), end=_details.end(); it!=end; ++it)
        {
            if(!it.value().isNull())
            {
                profileData[it.key()] = it.value();
            }
        }
    }

    IpfsWriter writer(_settings);
    if(_details.contains("avatar"))
    {
        profileData["avatar"] = "ipfs://"+writer.writeFile(_details["avatar"].toString());
    }

    QString path = writer.writeData(profileData);

    if(_ipns)
    {
        IpfsNameRegistrar namereg(_settings);
        path = namereg.publish(path);
        path.prepend("ipns://");
    }
    else
    {
        path.prepend("ipfs://");
    }

    if(!path.length())
    {
        emitError("failed to publish content on ipfs");
    }
    else
    {
        if(_ipns && path.contains(link))
        {
            emitData("details", profileData);
        }
        else
        {
            if(_admin.set("details", path.toStdString(), _password.toStdString()))
            {
                emitData("details", profileData);
            }
            else
            {
                emitError("failed to link details");
            }
        }
    }

}


}
