#include "ImportEthereumKeyTest.hpp"

#if __GETH_SIMULATOR_ENABLED__


ImportEthereumKeyTest::ImportEthereumKeyTest() :
    _context(true)
{}


void ImportEthereumKeyTest::testImport()
{
    Xeth::DataBase & database = _context.getDataBase();
    Xeth::Synchronizer & synchronizer = _context.getSynchronizer();
    Xeth::ImportEthereumKeyCommand command(database, synchronizer);
    QVariantMap request;
    request.insert("file", "data/key/UTC--2016-02-09T04:33:27.433427--8a3015660bca082f81e53b2036bea9d41a8f79a8");
    QVariant result = command(request);
    QVERIFY(result.toBool());

    const Xeth::ScanCriteria & criteria = synchronizer.getScanCriteria();
    Xeth::EthereumKeyStore & keys = database.getEthereumKeys();
    QVERIFY(getSize(criteria.begin(), criteria.end())==1);
    QVERIFY(getSize(keys.begin(), keys.end())==1);
}

void ImportEthereumKeyTest::testInvalidRequest()
{
    Xeth::DataBase & database = _context.getDataBase();
    Xeth::Synchronizer & synchronizer = _context.getSynchronizer();
    Xeth::ImportEthereumKeyCommand command(database, synchronizer);
    QVariantMap request;
    QVariant result = command(request);
    QVERIFY(!result.toBool());

    const Xeth::ScanCriteria & criteria = synchronizer.getScanCriteria();
    Xeth::EthereumKeyStore & keys = database.getEthereumKeys();
    QVERIFY(getSize(criteria.begin(), criteria.end())==1);
    QVERIFY(getSize(keys.begin(), keys.end())==1);
}


void ImportEthereumKeyTest::testRenamedFile()
{
    Xeth::DataBase & database = _context.getDataBase();
    Xeth::Synchronizer & synchronizer = _context.getSynchronizer();
    Xeth::ImportEthereumKeyCommand command(database, synchronizer);
    QVariantMap request;
    request.insert("file", "data/key/ethbackup");
    QVariant result = command(request);
    QVERIFY(result.toBool());

    const Xeth::ScanCriteria & criteria = synchronizer.getScanCriteria();
    Xeth::EthereumKeyStore & keys = database.getEthereumKeys();
    QVERIFY(getSize(criteria.begin(), criteria.end())==2);
    QVERIFY(getSize(keys.begin(), keys.end())==2);
}

void ImportEthereumKeyTest::testMalformedFile()
{
    Xeth::DataBase & database = _context.getDataBase();
    Xeth::Synchronizer & synchronizer = _context.getSynchronizer();
    Xeth::ImportEthereumKeyCommand command(database, synchronizer);
    QVariantMap request;
    request.insert("file", "data/key/UTC--2016-02-09T04:33:27.436497--7420f23ff3e5c9d713f87d9db5a0a18bb9bfb6d0");
    QVariant result = command(request);
    QVERIFY(!result.toBool());

    const Xeth::ScanCriteria & criteria = synchronizer.getScanCriteria();
    Xeth::EthereumKeyStore & keys = database.getEthereumKeys();
    QVERIFY(getSize(criteria.begin(), criteria.end())==1);
    QVERIFY(getSize(keys.begin(), keys.end())==1);
}


void ImportEthereumKeyTest::testImportNonExistendFile()
{
    Xeth::DataBase & database = _context.getDataBase();
    Xeth::Synchronizer & synchronizer = _context.getSynchronizer();
    Xeth::ImportEthereumKeyCommand command(database, synchronizer);
    QVariantMap request;
    request.insert("file", "data/key/nonexistentkey");
    QVariant result = command(request);
    QVERIFY(!result.toBool());

    const Xeth::ScanCriteria & criteria = synchronizer.getScanCriteria();
    Xeth::EthereumKeyStore & keys = database.getEthereumKeys();
    QVERIFY(getSize(criteria.begin(), criteria.end())==2);
    QVERIFY(getSize(keys.begin(), keys.end())==2);
}

void ImportEthereumKeyTest::cleanupTestCase()
{
    _context.getGeth().stop();
}

template<class Iterator>
size_t ImportEthereumKeyTest::getSize(Iterator begin, Iterator end)
{
    size_t size = 0;
    for(;begin!=end; ++begin)
    {
        size++;
    }
    return size;
}

#endif
