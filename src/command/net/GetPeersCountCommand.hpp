#pragma once

#include "ethrpc/Provider.hpp"
#include "ethrpc/Network.hpp"
#include <QVariant>



namespace Xeth{


class GetPeersCountCommand
{
    public:
        GetPeersCountCommand(Ethereum::Connector::Provider &);
        QVariant operator()();


    private:
        Ethereum::Connector::Provider &_provider;
};


}



