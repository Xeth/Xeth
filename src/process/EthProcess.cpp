#include "EthProcess.hpp"

#include <QDebug>

namespace Xeth{

EthProcess::EthProcess(const Settings &settings) :
    _command(settings.get("eth-command", "geth"))
{
    if(settings.get<bool>("testnet", false))
    {
        _args.push_back("--testnet");
    }
}

EthProcess::EthProcess() :
    _command("geth")
{}


EthProcess::~EthProcess()
{
    qDebug()<<"terminating eth process";
    terminate();
    waitForFinished();
}

void EthProcess::exec()
{
    qDebug()<<"Process:exec : "<<_command<<" args:"<<_args;
    start(_command, _args);
}


void EthProcess::exec(const QStringList &args)
{
    QStringList ethArgs = _args;
    ethArgs += args;
    qDebug()<<"Process:exec : "<<_command<<" args:"<<ethArgs;
    start(_command, _args);
}



}

