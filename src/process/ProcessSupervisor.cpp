#include "ProcessSupervisor.hpp"
#include <QDebug>

namespace Xeth{

ProcessSupervisor::ProcessSupervisor() :
    _respawnLimit(10),
    _respawnCnt(0),
    _respawnInterval(1000),
    _process(NULL)
{
    initSignals();
}

ProcessSupervisor::ProcessSupervisor(const Settings &settings) :
    _respawnLimit(settings.get<size_t>("respawn_limit", 10)),
    _respawnCnt(0),
    _respawnInterval(settings.get<size_t>("respawn_interval", 1000)),
    _process(NULL)
{
    initSignals();
}

ProcessSupervisor::~ProcessSupervisor()
{
    stopListening();
    QObject::disconnect(&_timer, SIGNAL(timeout()));
}


void ProcessSupervisor::initSignals()
{
    QObject::connect(&_timer, &QTimer::timeout, this, &ProcessSupervisor::fork);
}


void ProcessSupervisor::attach(QProcess *process)
{
    stopListening();
    _process = process;
    _process->setParent(this);
    QObject::connect(_process, SIGNAL(error(QProcess::ProcessError)), this, SLOT(handleError(QProcess::ProcessError)));
}


void ProcessSupervisor::stopListening()
{
    if(_process)
    {
        QObject::disconnect(_process, SIGNAL(error(QProcess::ProcessError)));
    }
    _timer.stop();
}


QString ProcessSupervisor::getProgram() const
{
    return _process ? _process->program() : "";
}

bool ProcessSupervisor::isActive() const
{
    return _process!=NULL && (_process->atEnd() ||_timer.isActive());
}



void ProcessSupervisor::handleError(QProcess::ProcessError error)
{
    qDebug()<<"process error : "<<error;
    if(++_respawnCnt > _respawnLimit)
    {
        emit Error(_process->errorString());
    }
    else
    {
        scheduleFork();
    }
}


void ProcessSupervisor::moveToThread(QThread *thread)
{
    QObject::moveToThread(thread);
    if(_process) _process->moveToThread(thread);
    _timer.moveToThread(thread);
}


void ProcessSupervisor::start()
{
    fork();
}


void ProcessSupervisor::restart()
{
    stop();
    start();
}

void ProcessSupervisor::stop()
{
    _timer.stop();
    if(_process)
    {
        _process->kill();
        _process->waitForFinished();
    }
}


void ProcessSupervisor::scheduleFork()
{
    _timer.start(_respawnInterval);
}


void ProcessSupervisor::fork()
{
    _timer.stop();
    _process->setProcessChannelMode(QProcess::MergedChannels);
    _process->start();
}








}
