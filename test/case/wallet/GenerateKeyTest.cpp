#include "GenerateKeyTest.hpp"


GenerateKeyTest::GenerateKeyTest()
{}


void GenerateKeyTest::testGenerate()
{
    Xeth::DataBase & database = _context.getDataBase();
    Xeth::Synchronizer & synchronizer = _context.getSynchronizer();
    Xeth::GenerateKeyCommand command(database, synchronizer);
    QVariantMap request;
    request.insert("password","asdasd123");
    QVariant result = command(request);
    QVERIFY(result.toBool());

    const Xeth::ScanCriteria & criteria = synchronizer.getScanCriteria();
    Xeth::EthereumKeyStore & keys = database.getEthereumKeys();
    QVERIFY(getSize(criteria.begin(), criteria.end())==1);
    QVERIFY(getSize(keys.begin(), keys.end())==1);
}


void GenerateKeyTest::testGenerateFromEntropy()
{
    Xeth::DataBase & database = _context.getDataBase();
    Xeth::Synchronizer & synchronizer = _context.getSynchronizer();
    Xeth::GenerateKeyCommand command(database, synchronizer);
    QVariantMap request;
    request.insert("password", "asdasd123");
    request.insert("entropy", "asdasdasdasdasdasdasdasdasdasdasdasdasdasdasdasdasdasd");
    QVariant result = command(request);
    QVERIFY(result.toBool());
    Xeth::EthereumKeyStore & keys = database.getEthereumKeys();
    const Xeth::ScanCriteria & criteria = synchronizer.getScanCriteria();
    QVERIFY(getSize(criteria.begin(), criteria.end())==2);
    QVERIFY(getSize(keys.begin(), keys.end())==2);
}
#include "GenerateKeyTest.hpp"

void GenerateKeyTest::testInvalidEntropy()
{
    Xeth::DataBase & database = _context.getDataBase();
    Xeth::Synchronizer & synchronizer = _context.getSynchronizer();
    Xeth::GenerateKeyCommand command(database, synchronizer);
    QVariantMap request;
    request.insert("password", "adsasd123");
    request.insert("entropy", "asdas");
    QVariant result = command(request);
    QVERIFY(!result.toBool());
    Xeth::EthereumKeyStore & keys = database.getEthereumKeys();
    const Xeth::ScanCriteria & criteria = synchronizer.getScanCriteria();
    QVERIFY(getSize(criteria.begin(), criteria.end())==2);
    QVERIFY(getSize(keys.begin(), keys.end())==2);
}


void GenerateKeyTest::testInvalidPassword()
{
    Xeth::DataBase & database = _context.getDataBase();
    Xeth::Synchronizer & synchronizer = _context.getSynchronizer();
    Xeth::GenerateKeyCommand command(database, synchronizer);
    QVariantMap request;
    request.insert("entropy", "asdas");
    QVariant result = command(request);
    QVERIFY(!result.toBool());
    Xeth::EthereumKeyStore & keys = database.getEthereumKeys();
    const Xeth::ScanCriteria & criteria = synchronizer.getScanCriteria();
    QVERIFY(getSize(criteria.begin(), criteria.end())==2);
    QVERIFY(getSize(keys.begin(), keys.end())==2);
}

void GenerateKeyTest::cleanupTestCase()
{
    _context.getGeth().stop();
}

template<class Iterator>
size_t GenerateKeyTest::getSize(Iterator begin, Iterator end)
{
    size_t size = 0;
    for(;begin!=end; ++begin)
    {
        size++;
    }
    return size;
}


