#include "BlockChainFacade.hpp"


namespace Xeth{


BlockChainFacade::BlockChainFacade(Ethereum::Connector::Provider &provider, Notifier &notifier, Synchronizer &synchronizer, Invoker<Notifier> &invoker) :
    _provider(provider),
    _notifier(notifier),
    _synchronizer(synchronizer),
    _invoker(invoker)
{
    QObject::connect(&synchronizer.getSyncProgressFetcher(), &ChainProgressFetcher::Progress, this, &BlockChainFacade::emitSyncProgress);
    QObject::connect(&synchronizer.getScanner().getProgress(), &ScanProgress::Progress, this, &BlockChainFacade::emitScanProgress);
}


QVariant BlockChainFacade::getChainHeight()
{
    GetChainHeightCommand command(_provider);
    return _invoker.invoke(command, NullCommandArguments());
}


QVariant BlockChainFacade::getSyncProgress()
{
    GetSyncProgressCommand command(_synchronizer);
    return _invoker.invoke(command, NullCommandArguments());
}


QVariant BlockChainFacade::getScanProgress()
{
    GetScanProgressCommand command(_synchronizer);
    return _invoker.invoke(command, NullCommandArguments());
}


QObject * BlockChainFacade::getChainHeightAsync()
{
    GetChainHeightCommand command(_provider);
    return _invoker.invokeAsync(command, NullCommandArguments());
}


QObject * BlockChainFacade::getSyncProgressAsync()
{
    GetSyncProgressCommand command(_synchronizer);
    return _invoker.invokeAsync(command, NullCommandArguments());
}


QObject * BlockChainFacade::getScanProgressAsync()
{
    GetScanProgressCommand command(_synchronizer);
    return _invoker.invokeAsync(command, NullCommandArguments());
}


void BlockChainFacade::emitScanProgress(double progress)
{
    emit ScanProgress(progress);
}


void BlockChainFacade::emitSyncProgress(double progress)
{
    emit SyncProgress(progress);
}


}
