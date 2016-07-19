#pragma once

#include <QObject>

#include "database/DataBase.hpp"

#include "command/addressbook/AddContactCommand.hpp"
#include "command/addressbook/EditContactCommand.hpp"
#include "command/addressbook/ListContactsCommand.hpp"
#include "command/addressbook/RemoveContactCommand.hpp"
#include "command/addressbook/RenameConactCommand.hpp"
#include "command/Invoker.hpp"

#include "Notifier.hpp"

namespace Xeth{

class AddressBookFacade : public QObject
{
    Q_OBJECT

    public:
        AddressBookFacade(DataBase &, Invoker<Notifier> &);

    public slots:
        QVariant addContact(const QVariantMap &);
        QVariant editContact(const QVariantMap &);
        QVariant renameContact(const QVariantMap &);
        QVariant listContacts();
        QVariant removeContact(const QString &);


    signals:
        void Contact(const QVariantMap &) const;

    private slots:
        void emitContact(const QJsonObject &);

    private:
        DataBase &_database;
        Invoker<Notifier> &_invoker;

};


}
