#pragma once 

#include "ethrpc/Provider.hpp"
#include "conf/Settings.hpp"

namespace Xeth{


class WaitForRpcServer
{
    public:
        WaitForRpcServer(Ethereum::Connector::Provider &, Ethereum::Connector::NetworkParams );
        void operator()();

    private:
        Ethereum::Connector::Provider &_provider;
        Ethereum::Connector::NetworkParams _net;
};


}
