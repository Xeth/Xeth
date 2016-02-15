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
    if(!QObject::connect(&_scanTimer, SIGNAL(timeout()), this, SLOT(scan())))
    {
        throw std::runtime_error("failed to connect timeout signal");
    }

    if(!QObject::connect(&_scanCriteria, &ScanCriteria::Data, this, &ChainScanner::processData))
    {
        throw std::runtime_error("failed to connect Data signal");
    }

}


ChainScanner::ChainScanner(const ChainScanner &copy) : /*is private, copy is not allowed */
    _provider(copy._provider),
    _blockchain(copy._blockchain),
    _database(copy._database)
{}

void ChainScanner::addAddress(const Ethereum::Address &address)
{
    ScopedScanPause pause(this);
    _scanCriteria.addCriterion<AccountScanCriterion>(getChainHeight(), address.toString().c_str());
}


void ChainScanner::addAddress(const std::string &address)
{
    ScopedScanPause pause(this);
    _scanCriteria.addCriterion<AccountScanCriterion>(getChainHeight(), address.c_str());
}


void ChainScanner::addAddress(const std::string &address, time_t time)
{
    ScopedScanPause pause(this);
    _scanCriteria.addCriterion<AccountScanCriterion>(estimateHeight(time), address.c_str());
}

void ChainScanner::addStealthAddress(const StealthKey &key)
{
    ScopedScanPause pause(this);
    _scanCriteria.addCriterion<StealthScanCriterion>(getChainHeight(), key);
}

void ChainScanner::addAddress(const Ethereum::Address &address, time_t time)
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
    if(!_scanAction.isActive())
    {
        _scanTimer.stop();
        _scanAction.start(_blockchain, _scanCriteria, _scanProgress);
    }
}

void ChainScanner::syncScan()
{
    if(_scanAction.isActive())
    {
        _scanAction.waitToComplete();
    }
    else
    {
        ScanResult result;
        _scanCriteria.parse(_blockchain, result, _scanProgress);
    }
}

bool ChainScanner::processTest()
{
    return true;
}

bool ChainScanner::processData(const PartialScanResult &result)
{
    ScanIndexStore & indexStore = _database.getScanIndex();
    TransactionStore & transactionStore = _database.getTransactions();
    StealthPaymentStore & stealthPaymentStore = _database.getStealthPayments();

    for(QJsonArray::const_iterator it = result.transactions.first; it!=result.transactions.second; ++it)
    {
        QJsonObject object = it->toObject(); //ToDo : use const reference isntead
        transactionStore.insert(object); //ignore duplicates
    }

    for(QJsonArray::const_iterator it = result.stealthPayments.first; it!=result.stealthPayments.second; ++it)
    {
        if(!stealthPaymentStore.insert(it->toObject()))
        {
            return true;
        }
    }

    for(ScanCriteria::Iterator sIt=_scanCriteria.begin(), sEnd=_scanCriteria.end(); sIt!=sEnd; ++sIt)
    {
        indexStore.insert(sIt->getAddress(), result.lastBlock);
    }


    return true;
}

const ScanCriteria & ChainScanner::getScanCriteria() const
{
    return _scanCriteria;
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
    if(_scanTimer.isActive())
    {
        _scanTimer.stop();
    }
    else
    {
        QObject::connect(&_scanAction, SIGNAL(Done()), this, SLOT(scheduleScan()));
    }
    scan();
}





}
