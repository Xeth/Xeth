#pragma once

#include <eth-connector/Provider.hpp>
#include <eth-connector/BlockChain.hpp>

#include <QObject>
#include <QTimer>



namespace Xeth{


class ChainProgress : public QObject
{
    Q_OBJECT

    public:
        ChainProgress(Ethereum::Connector::Provider &);
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
        time_t _firstBlockTime;
        double _progress;
        QTimer _timer;
};


}
