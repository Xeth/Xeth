#include "ScanAction.hpp"

namespace Xeth{

ScanAction::ScanAction()
{}



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



const ScanResult & ScanAction::getResult() const
{
    return _result;
}


}
