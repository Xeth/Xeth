#pragma once 

#include <QObject>
#include <QDebug>

#include <boost/date_time/posix_time/posix_time.hpp>
#include <boost/thread/thread.hpp> 

#include "ethrpc/Provider.hpp"

#include "process/ProcessSupervisor.hpp"


namespace Xeth{



class FacadeInitializer : public QObject
{
    Q_OBJECT
    public:
        FacadeInitializer(QThread *parent, Ethereum::Connector::Provider &provider, ProcessSupervisor &process, Ethereum::Connector::Network net);
        void initialize();

    signals:
        void Done();
        void Error(const QString &);

    private:
        QThread *_parent;
        Ethereum::Connector::Provider &_provider;
        ProcessSupervisor &_process;
        Ethereum::Connector::Network _net;
};


}
