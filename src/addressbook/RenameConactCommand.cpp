#include "RenameConactCommand.hpp"


namespace Xeth{


RenameConactCommand::RenameConactCommand(DataBase &database):
    _database(database)
{}



QVariant RenameConactCommand::operator ()(const QVariantMap &request)
{
    if(!request.contains("oldAlias")||!request.contains("newAlias"))
    {
        return QVariant::fromValue(false);
    }

    return QVariant::fromValue(_database.getAddressBook().move(request["oldAlias"].toString().toStdString().c_str(), request["newAlias"].toString().toStdString().c_str()));

}


}
