#include "AddContactCommand.hpp"

namespace Xeth{


AddContactCommand::AddContactCommand(DataBase &database) :
    _database(database)
{}



QVariant AddContactCommand::operator ()(const QVariantMap &request)
{
    if(!request.contains("alias"))
    {
        return QVariant::fromValue(false);
    }
    QString alias = request["alias"].toString();

    if(alias.length() == 0)
    {
        return QVariant::fromValue(false);
    }

    AddressBookStore & addressbook = _database.getAddressBook();

    return QVariant::fromValue(addressbook.replace(alias.toStdString().c_str(), QJsonObject::fromVariantMap(request)));
}



}
