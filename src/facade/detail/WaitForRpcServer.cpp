#include "WaitForRpcServer.hpp"
#include <QDebug>


namespace Xeth{


WaitForRpcServer::WaitForRpcServer(Ethereum::Connector::Provider &provider,  Ethereum::Connector::NetworkParams net) : 
    _provider(provider),
    _net(net)
{}


void WaitForRpcServer::operator()()
{
    size_t cnt = 0;
    while(!_provider.connect(_net)&&cnt<30)
    {
        qDebug()<<"failed to connect, retrying in 1 sec";
        cnt++;
        boost::this_thread::sleep(boost::posix_time::milliseconds(1000));
    }

}


}
