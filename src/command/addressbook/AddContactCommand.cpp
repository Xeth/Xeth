#include "AddContactCommand.hpp"


namespace Xeth{


AddContactCommand::AddContactCommand(DataBase &database) :
    _database(database)
{}



QVariant AddContactCommand::operator ()(const QVariantMap &request)
{
    if(!request.contains("alias") || !request.contains("address"))
    {
        return QVariant::fromValue(false);
    }

    AddressBookStore & addressbook = _database.getAddressBook();

    return QVariant::fromValue(addressbook.insert(request["alias"].toString().toStdString().c_str(), QJsonObject::fromVariantMap(request)));
}



}
