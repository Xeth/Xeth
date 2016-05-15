#include "ProgressFacade.hpp"

namespace Xeth{


ProgressFacade::ProgressFacade(Synchronizer &synchronizer, Invoker<Notifier> &) :
    _synchronizer(synchronizer)
{
    QObject::connect(&synchronizer.getScanner().getProgress(), &Synchronizer::ScanProgress::Progress, this, &ProgressFacade::emitScanProgress);
    QObject::connect(&synchronizer.getSyncProgressFetcher(), &Synchronizer::SyncProgress::Progress, this, &ProgressFacade::emitSyncProgress);
}


QVariant ProgressFacade::getScan() const
{
    return QVariant::fromValue(_synchronizer.getScanProgress());
}


QVariant ProgressFacade::getSync() const
{
    return QVariant::fromValue(_synchronizer.getChainProgress());
}


void ProgressFacade::emitScanProgress(double progress)
{
    emit Scan(QVariant::fromValue(progress));
}


void ProgressFacade::emitSyncProgress(double progress)
{
    emit Sync(QVariant::fromValue(progress));
}


}
