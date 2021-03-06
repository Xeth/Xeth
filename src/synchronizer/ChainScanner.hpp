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


namespace Xeth{

class ChainScanner : public QObject
{
    Q_OBJECT

    public:
        ChainScanner(Ethereum::Connector::Provider &, DataBase &, size_t scanChunk=100, size_t scanInterval=10000);
        ~ChainScanner();

        void setScanChunkSize(size_t limit);
        void autoScan(size_t interval);

        const ScanProgress & getProgress() const;

        bool isActive() const;

        void loadAddress(const std::string &);
        void loadStealthAddress(const StealthKey &);

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

    signals:
        void NewAddressCriterion(const std::string &, size_t);
        void NewStealthCriterion(const Xeth::StealthKey &, size_t);

    private slots:
        void addAddressCriterion(const std::string &, size_t);
        void addStealthCriterion(const Xeth::StealthKey &, size_t);

        void processPartialData(const PartialScanResult &);
        void processData(const ScanResult &);
        void updateScanCursor();
        void handleScanComplete();

    private:
        ChainScanner(const ChainScanner &);
        size_t estimateHeight(time_t);
        size_t getChainHeight();
        void scheduleScan(size_t );
        size_t getScanIndex(const std::string &);

    private:
        Ethereum::Connector::Provider &_provider;
        Ethereum::Connector::BlockChain _blockchain;
        DataBase &_database;
        ScanProgress _scanProgress;
        ScanCriteria _scanCriteria;
        ScanAction _scanAction;
        QTimer _scanTimer;
        size_t _scanInterval;

    friend class ScopedScanPause;
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
