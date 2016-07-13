#include "ImportProfileCommand.hpp"


namespace Xeth{


ImportProfileCommand::ImportProfileCommand(Ethereum::Connector::Provider &provider, DataBase &database) :
    _provider(provider),
    _bitprofiles(database.getBitProfiles()),
    _stealthKeys(database.getStealthKeys()),
    _ethereumKeys(database.getEthereumKeys())
{}


QVariant ImportProfileCommand::operator()(const QVariantMap &request) 
{
    if(!request.contains("path"))
    {
        return QVariant::fromValue(false);
    }
    return importProfileData(request["path"].toString(), request.contains("keys")?request["keys"].toBool():true);
}


QVariant ImportProfileCommand::operator()(const QString &path)
{
    return importProfileData(path, true);
}


QVariant ImportProfileCommand::importProfileData(const QString &path, bool includeKeys)
{
    JsonReader reader;
    Json::Value backup = reader.read(path.toStdString().c_str());

    if(backup.empty()||!backup.isMember("profile")||!backup.isMember("key")||!backup.isMember("stealth"))
    {
        return QVariant::fromValue(false);
    }

    if(includeKeys)
    {
        importKeys(backup["key"], EthereumKeySerializer(), _ethereumKeys);
        importKeys(backup["stealth"], StealthKeySerializer(), _stealthKeys);
    }
    _bitprofiles.insert(BitProfile::ProfileDescriptor(backup["profile"]));
    return QVariant::fromValue(true);
}

template<class Serializer, class KeyStore>
void ImportProfileCommand::importKeys(const Json::Value &keys, const Serializer &serializer, KeyStore &store)
{
    for(Json::Value::const_iterator it = keys.begin(), end = keys.end(); it!=end; ++it)
    {
        store.replace(serializer.unserialize(*it));
    }
}


}
