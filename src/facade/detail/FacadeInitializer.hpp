#pragma once 

#include <QObject>
#include <QDebug>

#include <boost/date_time/posix_time/posix_time.hpp>
#include <boost/thread/thread.hpp> 

#include "ethrpc/Provider.hpp"

#include "process/ProcessSupervisor.hpp"
#include "process/IpfsProcessInitializer.hpp"


namespace Xeth{



class FacadeInitializer : public QObject
{
    Q_OBJECT
    public:
        FacadeInitializer(QThread *parent, Ethereum::Connector::Provider &provider, ProcessSupervisor &eth, ProcessSupervisor &ipfs, Ethereum::Connector::Network net, const Settings &);
        void initialize();

    private:
        bool initializeIpfs();
        bool initializeEth();

    signals:
        void Done();
        void Error(const QString &);

    private:
        QThread *_parent;
        Ethereum::Connector::Provider &_provider;
        ProcessSupervisor &_eth;
        ProcessSupervisor &_ipfs;
        Ethereum::Connector::Network _net;
        const Settings &_settings;
};


}
