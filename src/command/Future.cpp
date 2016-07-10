#include "Future.hpp"


namespace Xeth{


Future::Future()
{}


Future::Future(const QFuture<QVariant> &future) :
    _watcher(new QFutureWatcher<QVariant>)
{
    QObject::connect(_watcher.get(), &QFutureWatcher<QVariant>::finished, this, &Future::emitDone);
    _watcher->setFuture(future);
}


Future::Future(const Future &copy) :
    _watcher(copy._watcher)
{}


Future::~Future()
{}


Future & Future::operator = (const Future &copy)
{
    _watcher = copy._watcher;
    return *this;
}


bool Future::isEmpty()
{
    return !_watcher;
}


bool Future::isFinished()
{
    return _watcher ? _watcher->isFinished() : false;
}


bool Future::isRunning()
{
    return _watcher ? _watcher->isRunning() : false;
}


QVariant Future::getResult()
{
    return _watcher ? _watcher->result() : QVariant();
}

void Future::dispose()
{
    deleteLater();
}

void Future::wait()
{
    if(_watcher)
    {
        _watcher->waitForFinished();
    }
}


void Future::emitDone()
{
    emit Finished(_watcher->result());
}


}
