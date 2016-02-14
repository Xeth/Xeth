#include "ProgressFacade.hpp"


namespace Xeth{


ProgressFacade::ProgressFacade(Synchronizer &synchronizer, Notifier &notifier) :
    _synchronizer(synchronizer)
{
    QObject::connect(&_synchronizer, &Synchronizer::ScanProgress, &notifier, &Notifier::emitScanProgress);
    QObject::connect(&_synchronizer, &Synchronizer::ChainProgress, &notifier, &Notifier::emitSyncProgress);
}


QVariant ProgressFacade::getScanProgress() const
{
    return QVariant::fromValue(_synchronizer.getScanProgress());
}


QVariant ProgressFacade::getSyncProgress() const
{
    return QVariant::fromValue(_synchronizer.getChainProgress());
}



}
