#include "ImportKeyCommand.hpp"


namespace Xeth{


ImportKeyCommand::ImportKeyCommand(const Settings &settings, DataBase &database, Synchronizer &synchronizer) : 
    _settings(settings),
    _database(database),
    _synchronizer(synchronizer)
{}


QVariant ImportKeyCommand::operator()(const QVariantMap &request)
{

    if(!request.contains("file")||!request.contains("password"))
    {
        return QVariant::fromValue(false);
    }

    QString file = request["file"].toString();
    QString password = request["password"].toString();

    if(!file.length()||!password.length())
    {
        return QVariant::fromValue(false);
    }

    QString address;

    if(!importEthereumKey(file, password, address))
    {
        if(!importStealthKey(file, password, address))
        {
            if(!importPresaleKey(file, password, address))
            {
                return QVariant::fromValue(false);
            }
        }
    }

    return QVariant::fromValue(address);
}


bool ImportKeyCommand::importEthereumKey(const QString &file, const QString &password, QString &address)
{
    ImportEthereumKeyCommand command(_database, _synchronizer);
    return command.import(file, password, address);
}


bool ImportKeyCommand::importStealthKey(const QString &file, const QString &password, QString &address)
{
    ImportStealthKeyCommand command(_database, _synchronizer);
    return command.import(file, password, address);
}


bool ImportKeyCommand::importPresaleKey(const QString &file, const QString &password, QString &address)
{
    ImportPresaleKeyCommand command(_settings, _synchronizer);
    return command.import(file, password, address);
}



}
