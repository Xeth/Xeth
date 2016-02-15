#pragma once

#include <QTimer>
#include <QObject>
#include <QVariantMap>
#include <QVariantList>
#include <QJsonDocument>

#include "ethrpc/Provider.hpp"
#include "ethrpc/BlockChain.hpp"

#include "database/DataBase.hpp"

#include "ScanProgress.hpp"
#include "ScanCriteria.hpp"
#include "ScanAction.hpp"
#include "AccountScanCriterion.hpp"
#include "StealthScanCriterion.hpp"
#include "ScanCriteriaLoader.hpp"


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

        void addAddress(const std::string &);
        void addAddress(const std::string &, time_t);

        void addAddress(const Ethereum::Address &);
        void addStealthAddress(const StealthKey &);

        void addAddress(const Ethereum::Address &, time_t);
        void addStealthAddress(const StealthKey &, time_t);

        void stop();
        
        const ScanCriteria & getScanCriteria() const;

        void syncScan();

    public slots:
        void scan();
        void scheduleScan();

    public slots:
        bool processData(const PartialScanResult &);
        bool processTest();

    private:
        ChainScanner(const ChainScanner &);
        size_t estimateHeight(time_t);
        size_t getChainHeight();

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
