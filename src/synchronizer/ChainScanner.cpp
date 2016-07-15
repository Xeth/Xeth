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
        _scanner->scheduleScan(100);
    }
}


ChainScanner::ChainScanner(Ethereum::Connector::Provider &provider, DataBase &database, size_t scanChunk, size_t scanInterval):
    _provider(provider),
    _blockchain(_provider),
    _database(database),
    _scanCriteria(scanChunk),
    _scanInterval(scanInterval)
{
    qRegisterMetaType<std::string>("std::string");
    qRegisterMetaType<Xeth::StealthKey>("Xeth::StealthKey");
    qRegisterMetaType<size_t>("size_t");

    if(!QObject::connect(&_scanTimer, SIGNAL(timeout()), this, SLOT(scan())))
    {
        throw std::runtime_error("failed to connect timeout signal");
    }

    if(!QObject::connect(&_scanCriteria, &ScanCriteria::Data, this, &ChainScanner::processPartialData))
    {
        throw std::runtime_error("failed to connect Data signal");
    }

    if(!QObject::connect(&_scanCriteria, &ScanCriteria::Done, this, &ChainScanner::processData))
    {
        throw std::runtime_error("failed to connect Data signal");
    }

    if(!QObject::connect(this, SIGNAL(NewAddressCriterion(const std::string &, size_t)), this, SLOT(addAddressCriterion(const std::string &, size_t))))
    {
        throw std::runtime_error("failed to connect AddressCriterion signal");
    }
    if(!QObject::connect(this, SIGNAL(NewStealthCriterion(const Xeth::StealthKey &, size_t)), this, SLOT(addStealthCriterion(const Xeth::StealthKey &, size_t))))
    {
        throw std::runtime_error("failed to connect StealtCriterion signal");
    }

}


ChainScanner::ChainScanner(const ChainScanner &copy) : /*is private, copy is not allowed */
    _provider(copy._provider),
    _blockchain(copy._blockchain),
    _database(copy._database)
{}


ChainScanner::~ChainScanner()
{
    stop();
    updateScanCursor();
}


void ChainScanner::setScanChunkSize(size_t limit)
{
    _scanCriteria.setLimit(limit);
}


void ChainScanner::loadAddress(const std::string &address)
{
    emit NewAddressCriterion(address, getScanIndex(address));
}

void ChainScanner::loadStealthAddress(const Xeth::StealthKey &key)
{
    Ethereum::Stealth::Address address(key);
    emit NewStealthCriterion(key, getScanIndex(address.toString()));
}

size_t ChainScanner::getScanIndex(const std::string &address)
{
    return _database.getScanIndex().get(address.c_str());
}

void ChainScanner::addAddress(const Ethereum::Address &address)
{
    emit NewAddressCriterion(address.toString(), getChainHeight());
}

void ChainScanner::addAddress(const std::string &address)
{
    emit NewAddressCriterion(address, getChainHeight());
}


void ChainScanner::addAddress(const std::string &address, time_t time)
{
    emit NewAddressCriterion(address, estimateHeight(time));
}

void ChainScanner::addStealthAddress(const StealthKey &key)
{
    emit NewStealthCriterion(key, getChainHeight());
}

void ChainScanner::addStealthAddress(const StealthKey &key, time_t time)
{
    emit NewStealthCriterion(key, estimateHeight(time));
}

void ChainScanner::addAddress(const Ethereum::Address &address, time_t time)
{
    emit NewAddressCriterion(address.toString(), estimateHeight(time));
}

void ChainScanner::addStealthCriterion(const Xeth::StealthKey &key, size_t cursor)
{
    ScopedScanPause pause(this);
    _scanCriteria.addCriterion<StealthScanCriterion>(cursor, key);
}

void ChainScanner::addAddressCriterion(const std::string &address, size_t cursor)
{
    ScopedScanPause pause(this);
    _scanCriteria.addCriterion<AccountScanCriterion>(cursor, address.c_str());
}


size_t ChainScanner::estimateHeight(time_t time)
{
    return (time > 1438266388) ? (time - 1438266388)/20 : 0;
}

size_t ChainScanner::getChainHeight()
{
    Ethereum::Connector::BlockChain chain(_provider);
    return chain.getHeight();
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


void ChainScanner::processData(const ScanResult &result)
{
    updateScanCursor();
}


void ChainScanner::updateScanCursor()
{
    ScanIndexStore & indexStore = _database.getScanIndex();
    for(ScanCriteria::Iterator sIt=_scanCriteria.begin(), sEnd=_scanCriteria.end(); sIt!=sEnd; ++sIt)
    {
        indexStore.insert(sIt->getAddress(), sIt.getBlockIndex());
    }
}

void ChainScanner::processPartialData(const PartialScanResult &result)
{
    TransactionStore & transactionStore = _database.getTransactions();
    StealthPaymentStore & stealthPaymentStore = _database.getStealthPayments();

    for(QJsonArray::const_iterator it = result.transactions.first; it!=result.transactions.second; ++it)
    {
        const QJsonValue & value = *it;
        QJsonObject object = value.toObject(); //ToDo : use const reference isntead
        transactionStore.insert(object); //ignore duplicates
    }

    for(QJsonArray::const_iterator it = result.stealthPayments.first; it!=result.stealthPayments.second; ++it)
    {
        QJsonObject obj = it->toObject();
        if(!stealthPaymentStore.replace(obj))
        {
            return;
        }
        addAddress(obj["address"].toString().toStdString());
    }
}

const ScanCriteria & ChainScanner::getScanCriteria() const
{
    return _scanCriteria;
}



void ChainScanner::scheduleScan(size_t interval)
{
    _scanTimer.start(interval);
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
        QObject::connect(&_scanAction, SIGNAL(Done()), this, SLOT(handleScanComplete()));
    }
    scan();
}


void ChainScanner::handleScanComplete()
{
    scheduleScan((_scanProgress.getValue() >= 100) ? _scanInterval : 500);
}





}
