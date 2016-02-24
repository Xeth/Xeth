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

    return QVariant::fromValue(_database.getAddressBook().move(request["previous"].toString().toStdString().c_str(), request["alias"].toString().toStdString().c_str()));

}


}
