#include "EthProcess.hpp"

#include <QDebug>


namespace Xeth{


EthProcess::EthProcess(const Settings &settings) :
#ifdef __WINDOWS_OS__
    _command(settings.get("eth-command", "geth.exe"))
#else
    _command(settings.get("eth-command", "geth"))
#endif
{
    if(settings.get<bool>("testnet", false))
    {
        _args.push_back("--testnet");
    }
}

EthProcess::EthProcess() :
#ifdef __WINDOWS_OS__
    _command("geth.exe")
#else
    _command("geth")
#endif
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

