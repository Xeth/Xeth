#include "ExportProfileCommand.hpp"


namespace Xeth{

ExportProfileCommand::ExportProfileCommand(Ethereum::Connector::Provider &provider, DataBase &database) :
    _provider(provider),
    _bitprofiles(database.getBitProfiles()),
    _ethereumKeys(database.getEthereumKeys()),
    _stealthKeys(database.getStealthKeys())
{}


QVariant ExportProfileCommand::operator()(const QVariantMap &request)
{
    if(!request.contains("destination")||!request.contains("uri"))
    {
        return QVariant::fromValue(false);
    }

    QString uri = request["uri"].toString();

    BitProfileStore::Iterator it = _bitprofiles.find(uri);
    if(it==_bitprofiles.end())
    {
        return QVariant::fromValue(false);
    }

    BitProfile::ProfileDescriptor descriptor = *it;

    BitProfile::ProfileAdministrator admin = BitProfile::ProfileAdministrator::FromDescriptor(_provider, descriptor);
    EthereumKeySerializer keySerializer;

    Json::Value backup;
    backup["profile"] = descriptor.toJSON();
    backup["key"] = Json::arrayValue;
    backup["key"].append(keySerializer.serializeToJson(_ethereumKeys.get(admin.getKey().getAddress().c_str())));

    std::string stealth = admin.getProfile().get("payments");
    if(stealth.size())
    {
        StealthKeySerializer stealthSerializer;
        backup["stealth"] = Json::arrayValue;
        backup["stealth"].append(stealthSerializer.serializeToJson(_stealthKeys.get(stealth.c_str())));
    }

    QString path = request["destination"].toString();
    path += QDir::separator();
    path += uri;
    path += ".";
    path += "backup";

    JsonWriter writer(path.toStdString().c_str(), true);
    return QVariant::fromValue(writer.write(backup));

}




}
