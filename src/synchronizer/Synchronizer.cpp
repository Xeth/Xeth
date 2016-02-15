#include "Synchronizer.hpp"

#include <QDebug>

namespace Xeth{

Synchronizer::Synchronizer(Ethereum::Connector::Provider &provider, DataBase &database):
    _syncProgress(provider),
    _scanner(provider, database)
{}

void Synchronizer::watchAddress(const std::string &address)
{
    _scanner.addAddress(address);
}

void Synchronizer::watchAddress(const std::string &address, time_t scanStart)
{
    _scanner.addAddress(address, scanStart);
}

void Synchronizer::watch(const EthereumKey &key)
{
    _scanner.addAddress(key.getAddress());
}

void Synchronizer::watch(const Ethereum::Address &address)
{
    _scanner.addAddress(address);
}

void Synchronizer::watch(const StealthKey &key)
{
    _scanner.addStealthAddress(key);
}


void Synchronizer::watch(const EthereumKey &key, time_t startTime)
{
    _scanner.addAddress(key.getAddress(), startTime);
}

void Synchronizer::watch(const Ethereum::Address &address, time_t startTime)
{
    _scanner.addAddress(address, startTime);
}

void Synchronizer::watch(const StealthKey &key, time_t startTime)
{
    _scanner.addStealthAddress(key, startTime);
}

void Synchronizer::loadAddresses()
{
    _scanner.loadAddresses();
}

void Synchronizer::scan()
{
    _scanner.syncScan();
}


const ScanCriteria & Synchronizer::getScanCriteria() const
{
    return _scanner.getScanCriteria();
}


const Synchronizer::SyncProgress & Synchronizer::getSyncProgressFetcher() const
{
    return _syncProgress;
}

const ChainScanner & Synchronizer::getScanner() const
{
    return _scanner;
}

void Synchronizer::synchronize()
{
    qDebug()<<"synchronizing...";
    size_t scanInterval = 12000, syncInterval = 12000;
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



}
