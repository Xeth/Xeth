#include "ScanWorker.hpp"

namespace Xeth{


ScanWorker::ScanWorker(QThread *parent, BlockChain &chain, ScanCriteria &criteria, ScanResult &result, ScanProgress &progress):
    _parent(parent),
    _interrupted(false),
    _chain(chain),
    _criteria(criteria),
    _result(result),
    _progress(progress)
{}


void ScanWorker::run()
{
    _criteria.parse(_chain, _result, _progress);
    _criteria.moveToThread(_parent);
}


bool ScanWorker::isInterrupted() const
{
    return _interrupted;
}


void ScanWorker::stop()
{
    _interrupted = true;
}


}
