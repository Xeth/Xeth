#pragma once 

#include <QObject>
#include <QDebug>

#include <boost/date_time/posix_time/posix_time.hpp>
#include <boost/thread/thread.hpp> 

#include "ethrpc/Provider.hpp"

#include "process/EthProcessSupervisor.hpp"


namespace Xeth{



class FacadeInitializer : public QObject
{
    Q_OBJECT
    public:
        FacadeInitializer(QThread *parent, Ethereum::Connector::Provider &provider, EthProcessSupervisor &process);
        void initialize();

    signals:
        void Done();
        void Error(const QString &);

    private:
        QThread *_parent;
        Ethereum::Connector::Provider &_provider;
        EthProcessSupervisor &_process;
};


}
