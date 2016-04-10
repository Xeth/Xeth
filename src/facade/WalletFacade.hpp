#pragma once

#include <QObject>
#include <QVariantList>
#include <QObjectList>

#include <boost/shared_ptr.hpp>
#include <boost/thread.hpp>

#include "conf/Settings.hpp"
#include "database/DataBase.hpp"


#include "command/wallet/GetAccountsCommand.hpp"
#include "command/wallet/GetBalanceCommand.hpp"
#include "command/wallet/ListTransactionsCommand.hpp"
#include "command/wallet/ImportKeyCommand.hpp"
#include "command/wallet/GenerateKeyCommand.hpp"
#include "command/wallet/ValidateAddressCommand.hpp"
#include "command/wallet/SendCommand.hpp"
#include "command/wallet/ExportKeyCommand.hpp"
#include "command/wallet/ChangeKeyPasswordCommand.hpp"
#include "command/wallet/EstimateFeeCommand.hpp"

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
        Q_INVOKABLE QVariant getPendingBalance(const QString &);
        Q_INVOKABLE QVariant send(const QVariantMap &);
        Q_INVOKABLE QVariant listTransactions(const QVariantMap &);
        Q_INVOKABLE QVariant exportKey(const QVariantMap &);
        Q_INVOKABLE QVariant exportEthereumKey(const QVariantMap &);
        Q_INVOKABLE QVariant importKey(const QVariantMap &);
        Q_INVOKABLE QVariant importPresaleKey(const QVariantMap &);
        Q_INVOKABLE QVariant importEthereumKey(const QVariantMap &);
        Q_INVOKABLE QVariant importStealthKey(const QVariantMap &);
        Q_INVOKABLE QVariant exportStealthKey(const QVariantMap &);
        Q_INVOKABLE QVariant generateKey(const QVariantMap &);
        Q_INVOKABLE QVariant generateEthereumKey(const QVariantMap &);
        Q_INVOKABLE QVariant generateStealthKey(const QVariantMap &);
        Q_INVOKABLE QVariant validateAddress(const QString &);
        Q_INVOKABLE QVariant validateAddress(const QVariantMap &);
        Q_INVOKABLE QVariant changeEthereumKeyPassword(const QVariantMap &);
        Q_INVOKABLE QVariant changeStealthKeyPassword(const QVariantMap &);
        Q_INVOKABLE QVariant changePassword(const QVariantMap &);
        Q_INVOKABLE QVariant estimateFee(const QVariantMap &);

    private:
        const Settings &_settings;
        Invoker _invoker;
        Ethereum::Connector::Provider &_provider;
        DataBase &_database;
        Synchronizer &_synchronizer;

};


}
