#pragma once

#include <QTimer>
#include <QObject>
#include <QVariantMap>
#include <QVariantList>
#include <QJsonDocument>

#include "ethrpc/Provider.hpp"
#include "ethrpc/BlockChain.hpp"
#include "ethrpc/Wallet.hpp"

#include "DataBase.hpp"
#include "ScanProgress.hpp"
#include "ScanCriteria.hpp"
#include "ScanAction.hpp"
#include "AccountScanCriterion.hpp"


namespace Xeth{

class ChainScanner : public QObject
{
    Q_OBJECT

    public:
        ChainScanner(Ethereum::Connector::Provider &, DataBase &);

        void autoScan(size_t interval);

        const ScanProgress & getProgress() const;

        bool isActive() const;

        void loadAddresses();
        void addAddress(const char *);

        void stop();

    public slots:
        void scan();
        void scheduleScan();

    signals:
        void Data(QJsonArray::const_iterator, QJsonArray::const_iterator );

    private slots:
        void processData(size_t , QJsonArray::const_iterator, QJsonArray::const_iterator);

    private:

        template<class Criterion>
        void addCriterion(const char *);

    private:
        Ethereum::Connector::Provider &_provider;
        Ethereum::Connector::BlockChain _blockchain;
        DataBase &_database;
        ScanProgress _scanProgress;
        ScanCriteria _scanCriteria;
        ScanAction _scanAction;
        QTimer _scanTimer;
        size_t _scanInterval;

};


class ScopedScanPause
{
    public:
        ScopedScanPause(ChainScanner *);
        ~ScopedScanPause();

    private:
        ChainScanner *_scanner;
        bool _active;
};

}
