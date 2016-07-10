#include "UpdateProfileInfoCommand.hpp"


namespace Xeth{


UpdateProfileInfoCommand::UpdateProfileInfoCommand(Ethereum::Connector::Provider &provider, BitProfileStore &store, const Settings &settings) :
    _provider(provider),
    _store(store),
    _settings(settings)
{}


QVariant UpdateProfileInfoCommand::operator()(const QVariantMap &request)
{
    if(!request.contains("uri")||!request.contains("details")||!request.contains("password"))
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

    QVariantMap details = request["details"].toMap();
    std::string password = request["password"].toString().toStdString();
    bool ipns = request.contains("ipns") ? request["ipns"].toBool() : false;
    QVariantMap profileData;
    IpfsReader reader(_settings);
    QString link = admin.getProfile().get("details").c_str();

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
        for(QVariantMap::iterator it = details.begin(), end=details.end(); it!=end; ++it)
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
        for(QVariantMap::iterator it = details.begin(), end=details.end(); it!=end; ++it)
        {
            if(!it.value().isNull())
            {
                profileData[it.key()] = it.value();
            }
        }
    }

    QString avatar;
    IpfsWriter writer(_settings);
    if(details.contains("avatar")&&!details["avatar"].isNull())
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

    if(ipns)
    {
        IpfsNameRegistrar namereg(_settings);
        path = namereg.publish(path);
        path.prepend("ipns://");
    }
    else
    {
        path.prepend("ipfs://");
    }

    if(path.length())
    {
        if(!avatar.length()&&profileData.contains("avatar"))
        {
            avatar = reader.readBytes(profileData["avatar"].toString().remove(0, 7));
        }
        if(ipns && path.contains(link))
        {
            profileData["avatar"] = avatar;
            return profileData;
        }
        else
        {
            if(admin.set("details", path.toStdString(), password))
            {
                profileData["avatar"] = avatar;
                return profileData;
            }
        }
    }

    return QVariant::fromValue(false);

}




}
