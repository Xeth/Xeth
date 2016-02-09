#pragma once

#include <QObject>
#include <QTimer>

#include "ethrpc/Provider.hpp"
#include "ethrpc/BlockChain.hpp"

#include "ChainProgress.hpp"


namespace Xeth{


class ChainProgressFetcher : public QObject
{
    Q_OBJECT

    public:
        ChainProgressFetcher(Ethereum::Connector::Provider &);
        double getValue() const;

        void autoUpdate(size_t interval = 120000);
        void stop();

        bool isActive() const;

    public slots:
        void update();

    signals:
        void Progress(double) const;

    private:
        Ethereum::Connector::BlockChain _chain;
        ChainProgress<Ethereum::Connector::BlockChain> _progress;
        QTimer _timer;
};


}

