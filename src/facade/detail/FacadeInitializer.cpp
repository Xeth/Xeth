#include "FacadeInitializer.hpp"

namespace Xeth{


FacadeInitializer::FacadeInitializer(QThread *parent,Ethereum::Connector::Provider &provider, EthProcessSupervisor &process) : 
    _parent(parent),
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
            boost::this_thread::sleep(boost::posix_time::milliseconds(1000));
        }


        if(!_provider.isConnected())
        {
            qDebug()<<"failed to initialize";
            _process.moveToThread(_parent);
            emit Error("RPC failed to connect");
            return ;

        }
    }
    qDebug()<<"initialization complete";
    _process.moveToThread(_parent);
    emit Done();
}


}
