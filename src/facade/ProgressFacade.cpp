#include "ProgressFacade.hpp"


namespace Xeth{


ProgressFacade::ProgressFacade(Synchronizer &synchronizer, Notifier &notifier) :
    _synchronizer(synchronizer)
{}


QVariant ProgressFacade::getScanProgress() const
{
    return QVariant::fromValue(_synchronizer.getScanProgress());
}


QVariant ProgressFacade::getSyncProgress() const
{
    return QVariant::fromValue(_synchronizer.getChainProgress());
}



}
