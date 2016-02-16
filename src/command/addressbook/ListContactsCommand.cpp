#include "ListContactsCommand.hpp"


namespace Xeth{

ListContactsCommand::ListContactsCommand(DataBase &database) :
    _database(database)
{}



QVariant ListContactsCommand::operator ()()
{
    QVariantList result;
    AddressBookStore & store = _database.getAddressBook();

    for(AddressBookStore::Iterator it=store.begin(), end=store.end(); it!=end; ++it)
    {
        result.push_back(it->toVariantMap());
    }

    return QVariant::fromValue(result);
}



}
