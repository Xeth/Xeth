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
#include "command/wallet/SendToStealthCommand.hpp"
#include "command/wallet/ImportPresaleKeyCommand.hpp"
#include "command/wallet/ImportKeyCommand.hpp"
#include "command/wallet/ExportKeyCommand.hpp"
#include "command/wallet/ImportStealthKeyCommand.hpp"
#include "command/wallet/ExportStealthKeyCommand.hpp"
#include "command/wallet/GenerateEthereumKeyCommand.hpp"
#include "command/wallet/GenerateStealthKeyCommand.hpp"
#include "command/wallet/ValidateAddressCommand.hpp"
#include "command/wallet/ValidateStealthAddressCommand.hpp"
#include "command/wallet/SendCommand.hpp"

#include "Invoker.hpp"
#include "Notifier.hpp"

namespace Xeth{


class WalletFacade :public QObject
{
    Q_OBJECT
    public:
        WalletFacade(const Settings &, Ethereum::Connector::Provider &, DataBase &, Notifier &, Synchronizer &);

    public:

        Q_INVOKABLE QVariant getAccounts() ;
        Q_INVOKABLE QVariant getBalance(const QString &);
        Q_INVOKABLE QVariant send(const QVariantMap &);
        Q_INVOKABLE QVariant sendToAddress(const QVariantMap &);
        Q_INVOKABLE QVariant sendToStealth(const QVariantMap &);
        Q_INVOKABLE QVariant listTransactions(const QVariantMap &);
        Q_INVOKABLE QVariant getTransaction(const QString &hash);
        Q_INVOKABLE QVariant exportKey(const QVariantMap &);
        Q_INVOKABLE QVariant importPresaleKey(const QVariantMap &);
        Q_INVOKABLE QVariant importKey(const QVariantMap &);
        Q_INVOKABLE QVariant importStealthKey(const QVariantMap &);
        Q_INVOKABLE QVariant exportStealthKey(const QVariantMap &);
        Q_INVOKABLE QVariant generateEthereumKey(const QVariantMap &);
        Q_INVOKABLE QVariant generateStealthKey(const QVariantMap &);
        Q_INVOKABLE QVariant validateAddress(const QVariantMap &);
        Q_INVOKABLE QVariant validateStealthAddress(const QVariantMap &);

    private:
        const Settings &_settings;
        Invoker _invoker;
        Ethereum::Connector::Provider &_provider;
        DataBase &_database;
        Synchronizer &_synchronizer;

};


}
