#include "EthProcessSupervisor.hpp"

namespace Xeth{

EthProcessSupervisor::EthProcessSupervisor() :
    _respawnLimit(10),
    _respawnCnt(0),
    _respawnInterval(1000)
{
    initSignals();
}

EthProcessSupervisor::EthProcessSupervisor(const Settings &settings) :
    _respawnLimit(settings.get<size_t>("respawn_limit", 10)),
    _respawnCnt(0),
    _respawnInterval(settings.get<size_t>("respawn_interval", 1000)),
    _process(settings)
{
    initSignals();
}

EthProcessSupervisor::~EthProcessSupervisor()
{
    QObject::disconnect(&_process, SIGNAL(error(QProcess::ProcessError)));
    QObject::disconnect(&_process, SIGNAL(started()));
    QObject::disconnect(&_timer, SIGNAL(timeout()));
}

void EthProcessSupervisor::initSignals()
{
    QObject::connect(&_process, SIGNAL(error(QProcess::ProcessError)), this, SLOT(handleError(QProcess::ProcessError)));
    QObject::connect(&_timer, SIGNAL(timeout()), this, SLOT(fork()));
    QObject::connect(&_process, SIGNAL(started()), this, SLOT(handleReady()));
}

bool EthProcessSupervisor::isActive() const
{
    return _process.atEnd() ||_timer.isActive();
}

void EthProcessSupervisor::handleReady()
{
    emit Ready();
}

void EthProcessSupervisor::handleError(QProcess::ProcessError)
{
    if(++_respawnCnt > _respawnLimit)
    {
        emit Error(_process.errorString());
    }
    else
    {
        scheduleFork();
    }
}


void EthProcessSupervisor::start()
{
//    if(!isActive())
//    {
        fork();
//    }
}

void EthProcessSupervisor::moveToThread(QThread *thread)
{
    QObject::moveToThread(thread);
    _process.moveToThread(thread);
    _timer.moveToThread(thread);
}


void EthProcessSupervisor::stop()
{
    _timer.stop();
    _process.kill();
}


void EthProcessSupervisor::scheduleFork()
{
    _timer.start(_respawnInterval);
}

void EthProcessSupervisor::fork()
{
    _timer.stop();
    _process.exec();
}






}
