#include "ScanAction.hpp"

namespace Xeth{

ScanAction::ScanAction() :
    _scanHeight(0)
{}

void ScanAction::start(BlockChain &blockchain, ScanCriteria &criteria)
{
    _thread.reset(new boost::thread(boost::bind(&ScanAction::execute, this, boost::ref(blockchain), boost::ref(criteria))));
}

void ScanAction::start(BlockChain &blockchain, ScanCriteria &criteria, ScanProgress &progress)
{
    _thread.reset(new boost::thread(boost::bind(&ScanAction::execute, this, boost::ref(blockchain), boost::ref(criteria), boost::ref(progress))));
}


void ScanAction::stop()
{
    if(_thread)
    {
        _thread->interrupt();
        _thread->join();
    }
}

void ScanAction::waitToComplete()
{
    if(_thread)
    {
        _thread->join();
    }
}

bool ScanAction::isActive() const
{
    if(!_thread)
    {
        return false;
    }
    return !_thread->timed_join(boost::posix_time::seconds(0));
}


void ScanAction::execute(BlockChain &blockchain, ScanCriteria &criteria)
{
    _result = QJsonArray();
    _scanHeight = criteria.process(blockchain, _result);
    emit Done();
}

void ScanAction::execute(BlockChain &blockchain, ScanCriteria &criteria, ScanProgress &progress)
{
    _result = QJsonArray();
    _scanHeight = criteria.process(blockchain, _result, progress);
    emit Done();
}

const QJsonArray & ScanAction::getResult() const
{
    return _result;
}

size_t ScanAction::getScanHeight() const
{
    return _scanHeight;
}

}
