#include "ProcessSupervisor.hpp"
#include <QDebug>
#include <QThread>

namespace Xeth{

ProcessSupervisor::ProcessSupervisor() :
    _respawnLimit(10),
    _respawnCnt(0),
    _respawnInterval(1000),
    _process(NULL),
    _lastStart(0)
{
    initSignals();
}

ProcessSupervisor::ProcessSupervisor(const Settings &settings) :
    _respawnLimit(settings.get<size_t>("respawn_limit", 10)),
    _respawnCnt(0),
    _respawnInterval(settings.get<size_t>("respawn_interval", 1000)),
    _process(NULL),
    _lastStart(0)
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
//    QObject::connect(this, &ProcessSupervisor::Restart, this, &ProcessSupervisor::restartProcess);
//    QObject::connect(this, &ProcessSupervisor::Stop, this, &ProcessSupervisor::stopProcess);
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


void ProcessSupervisor::stop()
{
    invokeMethod("stopProcess");
    emit Stop();
}

void ProcessSupervisor::restart()
{
    invokeMethod("restartProcess");
    emit Restart();
}


void ProcessSupervisor::invokeMethod(const char *method)
{
    try
    {
        QMetaObject::invokeMethod(this, method, QThread::currentThread() == thread() ? Qt::DirectConnection : Qt::BlockingQueuedConnection);
    }
    catch(const std::exception &e)
    {
        qDebug()<<"got exception : "<<e.what();
    }
    catch(...)
    {
        qDebug()<<"got unknown exception";
    }
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
    QMutexLocker lock(&_mutex);
    forkAndInitialize();
}


void ProcessSupervisor::restartProcess()
{
    try
    {
        QMutexLocker lock(&_mutex);
        if((time(NULL) - _lastStart) > 1)
        {
            stopProcess();
            forkAndInitialize();
        }
    }
    catch(const std::exception &e)
    {
        qDebug()<<"restart exception : "<<e.what();
    }
}


void ProcessSupervisor::forkAndInitialize()
{
    fork();
    _loaders();
}


void ProcessSupervisor::stopProcess()
{
    try
    {
        _timer.stop();
        if(_process)
        {
            _process->terminate();
            _process->waitForFinished();
            if(_process->state() != QProcess::NotRunning)
            {
                _process->kill();
                _process->waitForFinished();
            }
        }
    }
    catch(const std::exception &e)
    {
        qDebug()<<"stop exception : "<<e.what();
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
    _lastStart = time(NULL);
}



}
