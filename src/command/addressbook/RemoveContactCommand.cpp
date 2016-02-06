#include "RemoveContactCommand.hpp"


namespace Xeth{


RemoveContactCommand::RemoveContactCommand(DataBase &database) :
    _database(database)
{}



QVariant RemoveContactCommand::operator ()(const QString &alias)
{
    return QVariant::fromValue(_database.getAddressBook().remove(alias.toStdString().c_str()));
}


}
