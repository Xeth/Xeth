#include "ChangeKeyPasswordCommand.hpp"


namespace Xeth{


ChangeKeyPasswordCommand::ChangeKeyPasswordCommand(DataBase &database) :
    _database(database)
{}


QVariant ChangeKeyPasswordCommand::operator()(const QVariantMap &request)
{
    if(!request.contains("address")||!request.contains("password")||!request.contains("newPassword"))
    {
        return QVariant::fromValue(false);
    }

    QString address = request["address"].toString();
    QString password = request["password"].toString();
    QString newPassword = request["newPassword"].toString();

    size_t addrSize = address.length();

    if(addrSize==40||addrSize==42)
    {
        return QVariant::fromValue(changeEthereumKeyPassword(address, password, newPassword));
    }
    return QVariant::fromValue(changeStealthKeyPassword(address, password, newPassword));
}


bool ChangeKeyPasswordCommand::changeEthereumKeyPassword(const QString &address, const QString &password, const QString &newPassword)
{
    ChangeEthereumKeyPasswordCommand command(_database);
    return command.execute(address, password, newPassword);
}


bool ChangeKeyPasswordCommand::changeStealthKeyPassword(const QString &address, const QString &password, const QString &newPassword)
{
    ChangeStealthKeyPasswordCommand command(_database);
    return command.execute(address, password, newPassword);
}



ChangeEthereumKeyPasswordCommand::ChangeEthereumKeyPasswordCommand(DataBase &database) :
    Base(database.getEthereumKeys())
{}



ChangeStealthKeyPasswordCommand::ChangeStealthKeyPasswordCommand(DataBase &database) :
    Base(database.getStealthKeys())
{}

}
