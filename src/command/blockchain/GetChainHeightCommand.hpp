#pragma once 

#include <QVariant>
#include "ethrpc/Provider.hpp"
#include "ethrpc/BlockChain.hpp"


namespace Xeth{


class GetChainHeightCommand 
{
    public :
        GetChainHeightCommand(Ethereum::Connector::Provider &provider);
        QVariant operator ()();

    private:
        Ethereum::Connector::Provider &_provider;
};



}
