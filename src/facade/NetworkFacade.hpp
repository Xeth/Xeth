#pragma once 

#include <QObject>

#include "ethrpc/Provider.hpp"

#include "command/net/GetPeersCountCommand.hpp"
#include "command/Invoker.hpp"

#include "Notifier.hpp"


namespace Xeth{


class NetworkFacade : public QObject
{
    Q_OBJECT
    public:
        NetworkFacade( Ethereum::Connector::Provider &,  Invoker<Notifier> &);

    public:

        Q_INVOKABLE QVariant getPeersCount() ;
        Q_INVOKABLE QObject * getPeersCountAsync();

    private:
        Ethereum::Connector::Provider &_provider;
        Invoker<Notifier> &_invoker;

};


}
