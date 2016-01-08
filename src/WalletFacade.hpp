#pragma once

#include <QObject>
#include <QVariantList>
#include <QObjectList>

#include <boost/shared_ptr.hpp>
#include <boost/thread.hpp>

#include "Settings.hpp"
#include "DataBase.hpp"


#include "wallet/GetAccountsCommand.hpp"
#include "wallet/GetBalanceCommand.hpp"
#include "wallet/GetTransactionCommand.hpp"
#include "wallet/ListTransactionsCommand.hpp"
#include "wallet/SendToAddressCommand.hpp"
#include "wallet/ImportKeyCommand.hpp"
#include "wallet/ExportKeyCommand.hpp"

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
        Q_INVOKABLE QVariant importKey(const QVariantMap &);


    private:
        const Settings &_settings;
        Invoker _invoker;
        Ethereum::Connector::Provider &_provider;
        DataBase &_database;

};


}
