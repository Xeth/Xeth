#include "AddressBookFacade.hpp"


namespace Xeth{



AddressBookFacade::AddressBookFacade(DataBase &database, Notifier &notifier) :
    _database(database),
    _invoker(notifier)
{}


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


}
