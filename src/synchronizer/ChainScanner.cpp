#include "ChainScanner.hpp"

namespace Xeth{

ScopedScanPause::ScopedScanPause(ChainScanner *scanner) :
    _scanner(scanner),
    _active(scanner->isActive())
{
    if(_active)
    {
        _scanner->stop();
    }
}

ScopedScanPause::~ScopedScanPause()
{
    if(_active)
    {
        _scanner->scheduleScan();
    }
}


ChainScanner::ChainScanner(Ethereum::Connector::Provider &provider, DataBase &database):
    _provider(provider),
    _blockchain(_provider),
    _database(database),
    _scanInterval(10000)
{
    QObject::connect(&_scanTimer, SIGNAL(timeout()), this, SLOT(scan()));
    QObject::connect(&_scanCriteria, SIGNAL(Data(const PartialScanResult &)),
                     this, SLOT(processData(const PartialScanResult &)));
    QObject::connect(&_scanAction, SIGNAL(Done()), this, SLOT(scheduleScan()));
}

void ChainScanner::addAddress(const EthereumAddress &address)
{
    ScopedScanPause pause(this);
    _scanCriteria.addCriterion<AccountScanCriterion>(getChainHeight(), address.toString().c_str());
}


void ChainScanner::addStealthAddress(const StealthKey &key)
{
    ScopedScanPause pause(this);
    _scanCriteria.addCriterion<StealthScanCriterion>(getChainHeight(), key);
}

void ChainScanner::addAddress(const EthereumAddress &address, time_t time)
{
    ScopedScanPause pause(this);
    _scanCriteria.addCriterion<AccountScanCriterion>(estimateHeight(time), address.toString().c_str());
}

size_t ChainScanner::estimateHeight(time_t time)
{
    return time/12;
}

size_t ChainScanner::getChainHeight()
{
    Ethereum::Connector::BlockChain chain(_provider);
    return chain.getHeight();
}


void ChainScanner::addStealthAddress(const StealthKey &key, time_t time)
{
    ScopedScanPause pause(this);
    _scanCriteria.addCriterion<StealthScanCriterion>(estimateHeight(time), key);
}

void ChainScanner::loadAddresses()
{
    ScopedScanPause pause(this);
    _scanCriteria.clear();
    ScanCriteriaLoader loader(_provider, _database);
    loader.load(_scanCriteria);
}


const ScanProgress & ChainScanner::getProgress() const
{
    return _scanProgress;
}

bool ChainScanner::isActive() const
{
    return _scanAction.isActive() || _scanTimer.isActive();
}

void ChainScanner::stop()
{
    _scanAction.stop();
    _scanTimer.stop();
}

void ChainScanner::scan()
{
    _scanTimer.stop();
    _scanAction.start(_blockchain, _scanCriteria, _scanProgress);
}

void ChainScanner::processData(const PartialScanResult &result)
{
    ScanIndexStore & indexStore = _database.getScanIndex();
    TransactionStore & transactionStore = _database.getTransactions();
    StealthPaymentStore & stealthPaymentStore = _database.getStealthPayments();

    for(QJsonArray::const_iterator it = result.transactions.first; it!=result.transactions.second; ++it)
    {
        if(!transactionStore.insert(it->toObject()))
        {
            return;
        }
    }

    for(QJsonArray::const_iterator it = result.stealthPayments.first; it!=result.stealthPayments.second; ++it)
    {
        if(!stealthPaymentStore.insert(it->toObject()))
        {
            return;
        }
    }

    for(ScanCriteria::Iterator sIt=_scanCriteria.begin(), sEnd=_scanCriteria.end(); sIt!=sEnd; ++sIt)
    {
        indexStore.insert(sIt->getAddress(), result.lastBlock);
    }


    emit Data(result);

}

void ChainScanner::scheduleScan()
{
    if(_scanInterval)
    {
        _scanTimer.start(_scanInterval);
    }
}

void ChainScanner::autoScan(size_t scanInterval)
{
    _scanInterval = scanInterval;

    if(!isActive())
    {
        scan();
    }
}





}
