#include "ScanAction.hpp"

namespace Xeth{

ScanAction::ScanAction()
{}

void ScanAction::start(BlockChain &chain, ScanCriteria &criteria, ScanProgress &progress)
{
    _result = ScanResult();
    _worker.reset(new ScanWorker(QThread::currentThread(), chain, criteria, _result, progress));
    QObject::connect(_worker.get(), &ScanWorker::finished, this, &ScanAction::emitDone);
    criteria.moveToThread(_worker.get());
    _worker->start();
}


void ScanAction::stop()
{
    if(isActive())
    {
        _worker->stop();
        _worker->wait();
    }
}

void ScanAction::waitToComplete()
{
    if(isActive())
    {
        _worker->wait();
    }
}

bool ScanAction::isActive() const
{
    if(!_worker)
    {
        return false;
    }
    return !_worker->isFinished();
}



const ScanResult & ScanAction::getResult() const
{
    return _result;
}


void ScanAction::emitDone()
{
    emit Done();
}


}
