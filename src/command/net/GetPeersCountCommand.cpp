#include "GetPeersCountCommand.hpp"


namespace Xeth{


GetPeersCountCommand::GetPeersCountCommand(Ethereum::Connector::Provider &provider) : 
    _provider(provider)
{}


QVariant GetPeersCountCommand::operator()()
{
    Ethereum::Connector::Network net(_provider);
    return QVariant::fromValue(net.getPeersCount());
}


}
