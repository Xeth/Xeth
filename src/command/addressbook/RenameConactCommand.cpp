#include "RenameConactCommand.hpp"


namespace Xeth{


RenameConactCommand::RenameConactCommand(DataBase &database):
    _database(database)
{}



QVariant RenameConactCommand::operator ()(const QVariantMap &request)
{
    if(!request.contains("previous")||!request.contains("alias"))
    {
        return QVariant::fromValue(false);
    }

    QString alias = request["alias"].toString();
    if(!alias.length())
    {
        return QVariant::fromValue(false);
    }

    return QVariant::fromValue(_database.getAddressBook().move(request["previous"].toString().toStdString().c_str(), alias.toStdString().c_str()));

}


}
