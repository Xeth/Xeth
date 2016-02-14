#pragma once 

#include <QObject>
#include <QDebug>

#include "ethrpc/Provider.hpp"

#include "process/EthProcessSupervisor.hpp"


namespace Xeth{



class FacadeInitializer : public QObject
{
    Q_OBJECT
    public:
        FacadeInitializer(Ethereum::Connector::Provider &provider, EthProcessSupervisor &process);
        void initialize();

    signals:
        void Done();
        void Error(const QString &);

    private:
        Ethereum::Connector::Provider &_provider;
        EthProcessSupervisor &_process;
};


}
