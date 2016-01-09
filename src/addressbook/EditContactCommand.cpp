#include "EditContactCommand.hpp"


namespace  Xeth {


EditContactCommand::EditContactCommand(DataBase &database) :
    _database(database)
{}


QVariant EditContactCommand::operator ()(const QVariantMap &request)
{
    if(!request.contains("alias") || !request.contains("address"))
    {
        return QVariant::fromValue(false);
    }

    AddressBookStore & addressbook = _database.getAddressBook();

    return QVariant::fromValue(addressbook.replace(request["alias"].toString().toStdString().c_str(), QJsonObject::fromVariantMap(request)));
}


}
