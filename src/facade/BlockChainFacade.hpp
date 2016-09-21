#pragma once

#include <QObject>


#include "synchronizer/Synchronizer.hpp"


#include "command/blockchain/GetScanProgressCommand.hpp"
#include "command/blockchain/GetSyncProgressCommand.hpp"
#include "command/blockchain/GetChainHeightCommand.hpp"
#include "command/Invoker.hpp"

#include "Notifier.hpp"


namespace Xeth{


class BlockChainFacade :public QObject
{
    Q_OBJECT
    public:
        BlockChainFacade(Ethereum::Connector::Provider &, Notifier &, Synchronizer &, Invoker<Notifier> &);

    public:

        Q_INVOKABLE QVariant getChainHeight();
        Q_INVOKABLE QVariant getSyncProgress();
        Q_INVOKABLE QVariant getScanProgress();

        Q_INVOKABLE QObject * getChainHeightAsync();
        Q_INVOKABLE QObject * getSyncProgressAsync();
        Q_INVOKABLE QObject * getScanProgressAsync();

    signals:
        void SyncProgress(double) const;
        void ScanProgress(double) const;

    private slots:
        void emitScanProgress(double);
        void emitSyncProgress(double);

    private:
        Invoker<Notifier> &_invoker;
        Ethereum::Connector::Provider &_provider;
        Notifier &_notifier;
        Synchronizer &_synchronizer;
};


}
