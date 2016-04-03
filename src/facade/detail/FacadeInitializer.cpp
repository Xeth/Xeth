#include "FacadeInitializer.hpp"
#include <QDebug>

namespace Xeth{


FacadeInitializer::FacadeInitializer(QThread *parent,Ethereum::Connector::Provider &provider, ProcessSupervisor &eth, ProcessSupervisor &ipfs, Ethereum::Connector::Network net, const Settings &settings) : 
    _parent(parent),
    _provider(provider),
    _eth(eth),
    _ipfs(ipfs),
    _net(net),
    _settings(settings)
{}


void FacadeInitializer::initialize()
{

    bool success = initializeIpfs()&&initializeEth();
    _eth.moveToThread(_parent);
    _ipfs.moveToThread(_parent);

    if(success)
    {
        emit Done();
    }
    else
    {
        emit Error("RPC failed to connect");
    }

}

bool FacadeInitializer::initializeIpfs()
{
    QProcess client;
    client.setProcessChannelMode(QProcess::MergedChannels);
    IpfsProcessInitializer::Initialize(client, _settings, QStringList()<<"swarm"<<"peers");
    qDebug()<<"testing ipfs: "<<client.program()<<" args="<<client.arguments();
    client.start();
    client.waitForFinished();
    qDebug()<<client.readAllStandardOutput();
    if(client.exitCode() != 0)
    {
        qDebug()<<"initializing ipfs ...";
        //lets try to initialize
        IpfsProcessInitializer::Initialize(client, _settings, QStringList()<<"init");
        client.start();
        client.waitForFinished();
        qDebug()<<"starting daemon...";
        _ipfs.start();
    }
    return true;
}


bool FacadeInitializer::initializeEth()
{
    if(!_provider.connect(_net))
    {
        qDebug()<<"failed to connect, forking new process";

        _eth.start();
        size_t cnt = 0;
        while(!_provider.connect(_net)&&cnt<10)
        {
            qDebug()<<"failed to connect, retrying in 1 sec";
            cnt++;
            boost::this_thread::sleep(boost::posix_time::milliseconds(1000));
        }


        if(!_provider.isConnected())
        {
            qDebug()<<"failed to initialize";
            return false;

        }
    }
    return true;
}


}
