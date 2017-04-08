#include "GenerateKeyCommandTest.hpp"

#if __GETH_SIMULATOR_ENABLED__
GenerateKeyCommandTest::GenerateKeyCommandTest() :
    _context(true)
{}


void GenerateKeyCommandTest::testGenerateEthereumKey()
{
    Xeth::DataBase & database = _context.getDataBase();
    Xeth::Synchronizer & synchronizer = _context.getSynchronizer();
    Xeth::GenerateEthereumKeyCommand command(database, synchronizer);
    QVariantMap request;
    request.insert("password","asdasd123");
    QVariant result = command(request);
    QVERIFY(result.toBool());

    const Xeth::ScanCriteria & criteria = synchronizer.getScanCriteria();
    Xeth::EthereumKeyStore & keys = database.getEthereumKeys();
    QVERIFY(getSize(criteria.begin(), criteria.end())==1);
    QVERIFY(getSize(keys.begin(), keys.end())==1);
}


void GenerateKeyCommandTest::testGenerateStealthKey()
{
    Xeth::DataBase & database = _context.getDataBase();
    Xeth::Synchronizer & synchronizer = _context.getSynchronizer();
    Xeth::GenerateEthereumKeyCommand command(database, synchronizer);
    QVariantMap request;
    request["password"] = "asdasd123";
    request["type"] = "stealth";
    QVariant result = command(request);
    QVERIFY(result.toBool());

    const Xeth::ScanCriteria & criteria = synchronizer.getScanCriteria();
    Xeth::EthereumKeyStore & keys = database.getEthereumKeys();
    QVERIFY(getSize(criteria.begin(), criteria.end())==2);
    QVERIFY(getSize(keys.begin(), keys.end())== 2);
}


void GenerateKeyCommandTest::testGenerateFromEntropy()
{
    Xeth::DataBase & database = _context.getDataBase();
    Xeth::Synchronizer & synchronizer = _context.getSynchronizer();
    Xeth::GenerateEthereumKeyCommand command(database, synchronizer);
    QVariantMap request;
    request["password"] = "asdasd123";
    request["entropy"] = "asdasdasdasdasdasdasdasdasdasdasdasdasdasdasdasdasdasd";
    QVariant result = command(request);
    QVERIFY(result.toBool());
    Xeth::EthereumKeyStore & keys = database.getEthereumKeys();
    const Xeth::ScanCriteria & criteria = synchronizer.getScanCriteria();
    QVERIFY(getSize(criteria.begin(), criteria.end())==3);
    QVERIFY(getSize(keys.begin(), keys.end())==3);
}

void GenerateKeyCommandTest::testInvalidEntropy()
{
    Xeth::DataBase & database = _context.getDataBase();
    Xeth::Synchronizer & synchronizer = _context.getSynchronizer();
    Xeth::GenerateEthereumKeyCommand command(database, synchronizer);
    QVariantMap request;
    request["password"] = "adsasd123";
    request["entropy"] = "asdas";
    QVariant result = command(request);
    QVERIFY(!result.toBool());
    Xeth::EthereumKeyStore & keys = database.getEthereumKeys();
    const Xeth::ScanCriteria & criteria = synchronizer.getScanCriteria();
    QVERIFY(getSize(criteria.begin(), criteria.end())==3);
    QVERIFY(getSize(keys.begin(), keys.end())==3);
}


void GenerateKeyCommandTest::testInvalidPassword()
{
    Xeth::DataBase & database = _context.getDataBase();
    Xeth::Synchronizer & synchronizer = _context.getSynchronizer();
    Xeth::GenerateEthereumKeyCommand command(database, synchronizer);
    QVariantMap request;
    request["entropy"] = "asdas";
    QVariant result = command(request);
    QVERIFY(!result.toBool());
    Xeth::EthereumKeyStore & keys = database.getEthereumKeys();
    const Xeth::ScanCriteria & criteria = synchronizer.getScanCriteria();
    QVERIFY(getSize(criteria.begin(), criteria.end())==3);
    QVERIFY(getSize(keys.begin(), keys.end())==3);
}

void GenerateKeyCommandTest::cleanupTestCase()
{}

template<class Iterator>
size_t GenerateKeyCommandTest::getSize(Iterator begin, Iterator end)
{
    size_t size = 0;
    for(;begin!=end; ++begin)
    {
        size++;
    }
    return size;
}
#endif

