#include "Synchronizer.hpp"

#include <QDebug>

namespace Xeth{

Synchronizer::Synchronizer(Ethereum::Connector::Provider &provider, DataBase &database):
    _loader(provider, database),
    _syncProgress(provider),
    _scanner(provider, database),
    _balanceObserver(provider)
{}

Synchronizer::Synchronizer(Ethereum::Connector::Provider &provider, DataBase &database, const Settings &settings):
    _loader(provider, database),
    _syncProgress(provider),
    _scanner(provider, database, settings.get("scan_chunk", 500), settings.get("scan_interval", 10000)),
    _balanceObserver(provider)
{}

void Synchronizer::watchAddress(const std::string &address)
{
    _scanner.addAddress(address);
    _balanceObserver.watch(address);
}

void Synchronizer::watchAddress(const std::string &address, time_t scanStart)
{
    _scanner.addAddress(address, scanStart);
    _balanceObserver.watch(address);
}

void Synchronizer::watch(const EthereumKey &key)
{
    watchAddress(key.getAddress());
}

void Synchronizer::watch(const Ethereum::Address &address)
{
    watchAddress(address.toString());
}

void Synchronizer::watch(const StealthKey &key)
{
    _scanner.addStealthAddress(key);
}


void Synchronizer::watch(const EthereumKey &key, time_t startTime)
{
    watchAddress(key.getAddress(), startTime);
}

void Synchronizer::watch(const Ethereum::Address &address, time_t startTime)
{
    watchAddress(address, startTime);
}

void Synchronizer::watch(const StealthKey &key, time_t startTime)
{
    _scanner.addStealthAddress(key, startTime);
}

void Synchronizer::loadAddresses()
{
    _loader.load(_scanner, _balanceObserver);
}


void Synchronizer::scan()
{
    _scanner.syncScan();
}


const ScanCriteria & Synchronizer::getScanCriteria() const
{
    return _scanner.getScanCriteria();
}


const BalanceObserver & Synchronizer::getBalanceObserver() const
{
    return _balanceObserver;
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
    size_t scanInterval = 24000, syncInterval = 12000;
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
