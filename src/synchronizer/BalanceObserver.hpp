#pragma once

#include <string>
#include <QMutex>
#include <QObject>
#include <QMutexLocker>
#include <QList>
#include <QTimer>
#include <QtConcurrent>

#include "ethrpc/Provider.hpp"
#include "ethrpc/Wallet.hpp"

#include "types/BigInt.hpp"
#include "types/EthereumKey.hpp"


namespace Xeth{


class BalanceObserver : public QObject
{
    Q_OBJECT
    public:
        BalanceObserver(Ethereum::Connector::Provider &, time_t interval=5000);

        void watch();
        void watch(const std::string &);
        void start();

        time_t getUpdateInterval() const;

    signals:
        void Update(const QString &, const BigInt &, const BigInt &) const;
        void processed();


    private slots:
        void checkBalanceAsync();
        void checkBalanceLater();

    private:
        struct AccountInfo
        {
            std::string address;
            BigInt confirmed;
            BigInt unconfirmed;
        };

        void checkBalance();
        void checkBalance(AccountInfo &);

        time_t _interval;
        Ethereum::Connector::Wallet _wallet;
        QList<AccountInfo> _accounts;
        QTimer _timer;
};



}
