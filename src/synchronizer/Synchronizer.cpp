#include "Synchronizer.hpp"

#include <QDebug>

namespace Xeth{

Synchronizer::Synchronizer(Ethereum::Connector::Provider &provider, DataBase &database):
    _syncProgress(provider),
    _scanner(provider, database)
{
    QObject::connect(&_scanner.getProgress(), SIGNAL(Progress(double)), this, SLOT(emitScanProgress(double)));
    QObject::connect(&_syncProgress, SIGNAL(Progress(double)), this, SLOT(emitChainProgress(double)));
}

void Synchronizer::addAddress(const EthereumAddress &address)
{
    _scanner.addAddress(address);
}

void Synchronizer::addStealthAddress(const StealthKey &key)
{
    _scanner.addStealthAddress(key);
}

void Synchronizer::loadAddresses()
{
    _scanner.loadAddresses();
}

void Synchronizer::synchronize(size_t scanInterval, size_t syncInterval)
{
    _syncProgress.autoUpdate(syncInterval);
    _scanner.autoScan(scanInterval);
}

void Synchronizer::stop()
{
    _syncProgress.stop();
    _scanner.stop();
}

bool Synchronizer::isActive() const
{
    return _syncProgress.isActive() && _scanner.isActive();
}

double Synchronizer::getChainProgress() const
{
    return _syncProgress.getValue();
}

double Synchronizer::getScanProgress() const
{
    return _scanner.getProgress().getValue();
}

void Synchronizer::emitScanProgress(double progress)
{
    emit ScanProgress(progress);
}

void Synchronizer::emitChainProgress(double progress)
{
    emit ChainProgress(progress);
}


}
