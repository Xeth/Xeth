#pragma once

#include <QObject>

#include "DataBase.hpp"

#include "addressbook/AddContactCommand.hpp"
#include "addressbook/EditContactCommand.hpp"
#include "addressbook/ListContactsCommand.hpp"
#include "addressbook/RemoveContactCommand.hpp"
#include "addressbook/RenameConactCommand.hpp"

#include "Invoker.hpp"


namespace Xeth{

class AddressBookFacade : public QObject
{
    Q_OBJECT

    public:
        AddressBookFacade(DataBase &, Notifier &);


    public slots:
        QVariant addContact(const QVariantMap &);
        QVariant editContact(const QVariantMap &);
        QVariant renameContact(const QVariantMap &);
        QVariant listContacts();
        QVariant removeContact(const QString &);


    private:
        DataBase &_database;
        Invoker _invoker;

};


}
