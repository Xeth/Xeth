#pragma once

#include <QObject>
#include <QVariantList>
#include <QObjectList>

#include <boost/shared_ptr.hpp>
#include <boost/thread.hpp>

#include "Settings.hpp"
#include "database/DataBase.hpp"


#include "command/wallet/GetAccountsCommand.hpp"
#include "command/wallet/GetBalanceCommand.hpp"
#include "command/wallet/GetTransactionCommand.hpp"
#include "command/wallet/ListTransactionsCommand.hpp"
#include "command/wallet/SendToAddressCommand.hpp"
#include "command/wallet/ImportPresaleKeyCommand.hpp"
#include "command/wallet/ExportKeyCommand.hpp"

#include "Invoker.hpp"
#include "Notifier.hpp"

namespace Xeth{


class WalletFacade :public QObject
{
    Q_OBJECT
    public:
        WalletFacade(const Settings &, Ethereum::Connector::Provider &, DataBase &, Notifier &);

    public:

        Q_INVOKABLE QVariant getAccounts() ;
        Q_INVOKABLE QVariant getBalance(const QString &);
        Q_INVOKABLE QVariant sendToAddress(const QVariantMap &);
        Q_INVOKABLE QVariant listTransactions(const QVariantMap &);
        Q_INVOKABLE QVariant getTransaction(const QString &hash);
        Q_INVOKABLE QVariant exportKey(const QVariantMap &);
        Q_INVOKABLE QVariant importPresaleKey(const QVariantMap &);


    private:
        const Settings &_settings;
        Invoker _invoker;
        Ethereum::Connector::Provider &_provider;
        DataBase &_database;

};


}
