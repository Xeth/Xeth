#include "ExportKeyCommand.hpp"

namespace Xeth{

ExportKeyCommand::ExportKeyCommand(const DataBase &database ) :
    _database(database)
{}


QVariant ExportKeyCommand::operator ()(const QVariantMap &request)
{
    QString address = request["address"].toString();
    QString destinationPath = request["destination"].toString();

    if(!address.length() || !destinationPath.length())
    {
        return QVariant::fromValue(false);
    }

    const EthereumKeyStore & keyStore = _database.getEthereumKeys();

    EthereumKeyStore::Iterator it = keyStore.find(address.toStdString().c_str());

    if(it==keyStore.end())
    {
        return QVariant::fromValue(false);
    }

    const boost::filesystem::path & path = it.path();
    QString destinationFile = destinationPath;
    destinationFile +=  QDir::separator();
    destinationFile += path.filename().c_str();
    return QVariant::fromValue(QFile::copy(path.string().c_str(), destinationFile));
}


}
