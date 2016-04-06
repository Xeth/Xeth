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
    IpfsReader reader(_settings);
    QString link = _admin.getProfile().get("details").c_str();

    if(link.length())
    {
        if(link.contains("ipns://"))
        {
            IpfsNameRegistrar namereg(_settings);
            link = namereg.resolve(link.remove(0, 7));
        }
        else
        {
            link.remove(0, 7);
        }
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

    QString avatar;
    IpfsWriter writer(_settings);
    if(_details.contains("avatar")&&!_details["avatar"].isNull())
    {
        QImage image(profileData["avatar"].toString());
        QByteArray byteArray;
        QBuffer buffer(&byteArray);
        image.save(&buffer, "PNG");
        avatar = QString::fromLatin1(byteArray.toBase64().data());
        avatar.prepend("data:image/png;base64,");
        profileData["avatar"] = "ipfs://"+writer.writeData(avatar);
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
        if(!avatar.length()&&profileData.contains("avatar"))
        {
            avatar = reader.readBytes(profileData["avatar"].toString().remove(0, 7));
        }
        if(_ipns && path.contains(link))
        {
            profileData["avatar"] = avatar;
            emitData("details", profileData);
        }
        else
        {
            if(_admin.set("details", path.toStdString(), _password.toStdString()))
            {

                profileData["avatar"] = avatar;
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
