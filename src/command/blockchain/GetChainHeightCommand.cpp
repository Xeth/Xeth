#include "GetChainHeightCommand.hpp"


namespace Xeth{


GetChainHeightCommand::GetChainHeightCommand(Ethereum::Connector::Provider &provider) : 
    _provider(provider)
{}


QVariant GetChainHeightCommand::operator()()
{
    Ethereum::Connector::BlockChain chain(_provider);
    return QVariant::fromValue(chain.getHeight());
}



}
