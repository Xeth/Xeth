#include "ExportKeyCommand.hpp"

namespace Xeth{


ExportKeyCommand::ExportKeyCommand(DataBase &database) : 
    _database(database)
{}


QVariant ExportKeyCommand::operator()(const QVariantMap &request)
{
    if(!request.contains("address")||!request.contains("path"))
    {
        return QVariant::fromValue(false);
    }

    QString address = request["address"].toString();
    QString path = request["path"].toString();
    size_t addrSize = address.length();

    if(addrSize==40||addrSize==42)
    {
        return exportEthereumKey(address, path);
    }
    return exportStealthKey(address, path);
}


QVariant ExportKeyCommand::exportEthereumKey(const QString &address, const QString &path)
{
    ExportEthereumKeyCommand command(_database);
    if(!command.execute(address, path))
    {
        //try stealth payments
        StealthPaymentStore &payments = _database.getStealthPayments();
        StealthPaymentStore::Iterator it = payments.find(address.toStdString().c_str());
        if(it==payments.end())
        {
            return QVariant::fromValue(false);
        }
        QJsonObject payment = *it; //ToDo: use ref
        return exportStealthKey(payment["stealth"].toString(), path);
    }
    return QVariant::fromValue(true);
}


QVariant ExportKeyCommand::exportStealthKey(const QString &address, const QString &path)
{
    ExportStealthKeyCommand command(_database);
    return QVariant::fromValue(command.execute(address, path));
}


ExportStealthKeyCommand::ExportStealthKeyCommand(const DataBase &database ) :
    GenericExportKeyCommand<StealthKeyStore>(database.getStealthKeys())
{}

ExportEthereumKeyCommand::ExportEthereumKeyCommand(const DataBase &database ) :
    GenericExportKeyCommand<EthereumKeyStore>(database.getEthereumKeys())
{}


}
