#include "AddressBookFacade.hpp"


namespace Xeth{



AddressBookFacade::AddressBookFacade(DataBase &database, Invoker<Notifier> &invoker) :
    _database(database),
    _invoker(invoker)
{
    QObject::connect(&database.getAddressBook(), &AddressBookStore::NewItem, this, &AddressBookFacade::emitContact);
}


QVariant AddressBookFacade::addContact(const QVariantMap &request)
{
    AddContactCommand command(_database);
    return _invoker.invoke(command, request);
}


QVariant AddressBookFacade::editContact(const QVariantMap &request)
{
    EditContactCommand command(_database);
    return _invoker.invoke(command, request);
}


QVariant AddressBookFacade::renameContact(const QVariantMap &request)
{
    RenameConactCommand command(_database);
    return _invoker.invoke(command, request);
}


QVariant AddressBookFacade::removeContact(const QString &alias)
{
    RemoveContactCommand command(_database);
    return _invoker.invoke(command, alias);
}


QVariant AddressBookFacade::listContacts()
{
    ListContactsCommand command(_database);
    return _invoker.invoke(command, NullCommandArguments());
}


void AddressBookFacade::emitContact(const QJsonObject &item)
{
    emit Contact(item.toVariantMap());
}


}
