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
#include "command/Invoker.hpp"

#include "Notifier.hpp"

namespace Xeth{


class WalletFacade :public QObject
{
    Q_OBJECT
    public:
        WalletFacade(const Settings &, Ethereum::Connector::Provider &, DataBase &, Notifier &, Synchronizer &, Invoker<Notifier> &);

    public:

        Q_INVOKABLE QVariant getAccounts() ;
        Q_INVOKABLE QVariant getBalance(const QString &);
        Q_INVOKABLE QVariant getPendingBalance(const QString &);
        Q_INVOKABLE QVariant send(const QVariantMap &);

        Q_INVOKABLE QVariant listTransactions(const QVariantMap &);
        Q_INVOKABLE QVariant exportKey(const QVariantMap &);
        Q_INVOKABLE QVariant importKey(const QVariantMap &);
        Q_INVOKABLE QVariant generateKey(const QVariantMap &);
        Q_INVOKABLE QVariant validateAddress(const QString &);
        Q_INVOKABLE QVariant validateAddress(const QVariantMap &);
        Q_INVOKABLE QVariant changePassword(const QVariantMap &);
        Q_INVOKABLE QVariant estimateFee(const QVariantMap &);


        Q_INVOKABLE QObject * getBalanceAsync(const QString &);
        Q_INVOKABLE QObject * getPendingBalanceAsync(const QString &);
        Q_INVOKABLE QObject * sendAsync(const QVariantMap &);
        Q_INVOKABLE QObject * importKeyAsync(const QVariantMap &);
        Q_INVOKABLE QObject * generateKeyAsync(const QVariantMap &);
        Q_INVOKABLE QObject * changePasswordAsync(const QVariantMap &);

    signals:
        void Balance(const QString &, const QString &, const QString &) const;
        void Account(const QVariantMap &) const;
        void Transaction(const QVariantMap &) const;

    private slots:
        void emitBalance(const QString &, const BigInt &, const BigInt &);
        void emitStealthPayment(const QJsonObject &);
        void emitStealthKey(const QString &);
        void emitTransaction(const QJsonObject &);
        void emitEthereumKey(const QString &);

    private:
        const Settings &_settings;
        Invoker<Notifier> &_invoker;
        Ethereum::Connector::Provider &_provider;
        DataBase &_database;
        Notifier &_notifier;
        Synchronizer &_synchronizer;

};


}
