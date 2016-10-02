#include "ChildrenInitializer.hpp"
#include <QDebug>

namespace Xeth{


ChildrenInitializer::ChildrenInitializer(QThread *parent,Ethereum::Connector::Provider &provider, ProcessSupervisor &eth, ProcessSupervisor &ipfs, Ethereum::Connector::NetworkParams net, const Settings &settings) : 
    _parent(parent),
    _provider(provider),
    _eth(eth),
    _ipfs(ipfs),
    _net(net),
    _settings(settings)
{}


void ChildrenInitializer::initialize()
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

bool ChildrenInitializer::initializeIpfs()
{
    qDebug()<<"checking ipfs...";
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


bool ChildrenInitializer::initializeEth()
{
    qDebug()<<"checking "<<_eth.getProgram()<<"...";
    if(!_provider.connect(_net))
    {
        qDebug()<<"failed to connect, forking new process";
        _eth.start();
        if(!_provider.isConnected())
        {
            if(!_provider.connect(_net))
            {
                qDebug()<<"failed to initialize";
                return false;
            }
        }
    }
    return true;
}


}
