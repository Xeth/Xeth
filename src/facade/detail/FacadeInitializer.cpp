#include "FacadeInitializer.hpp"

namespace Xeth{


FacadeInitializer::FacadeInitializer(Ethereum::Connector::Provider &provider, EthProcessSupervisor &process) : 
    _provider(provider),
    _process(process)
{}


void FacadeInitializer::initialize()
{
    if(!_provider.connect())
    {
        qDebug()<<"failed to connect, forking new process";

        _process.start();
        size_t cnt = 0;
        while(!_provider.connect()||cnt>5)
        {
            qDebug()<<"failed to connect, retrying in 1 sec";
            cnt++;
            sleep(1);
        }


        if(!_provider.isConnected())
        {
            emit Error("RPC failed to connect");
            return ;

        }
    }
    emit Done();
}


}
