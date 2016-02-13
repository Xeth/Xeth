#include "ScanWorker.hpp"

namespace Xeth{


ScanWorker::ScanWorker(BlockChain &chain, ScanCriteria &criteria, ScanResult &result, ScanProgress &progress):
    _interrupted(false),
    _chain(chain),
    _criteria(criteria),
    _result(result),
    _progress(progress)
{}


void ScanWorker::run()
{
    _criteria.parse(_chain, _result, _progress);
    quit();
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
