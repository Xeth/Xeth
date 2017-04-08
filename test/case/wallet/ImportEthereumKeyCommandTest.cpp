#include "ImportEthereumKeyCommandTest.hpp"

#if __GETH_SIMULATOR_ENABLED__


ImportEthereumKeyCommandTest::ImportEthereumKeyCommandTest() :
    _context(true)
{}


void ImportEthereumKeyCommandTest::testImport()
{
    Xeth::DataBase & database = _context.getDataBase();
    Xeth::Synchronizer & synchronizer = _context.getSynchronizer();

    Xeth::ImportEthereumKeyCommand command(database, synchronizer);
    QVariantMap request;
    request.insert("file", "data/key/UTC--2017-04-08T12-36-57.044869688Z--3fb02dc2e19ca28326342042f85a2578a41a27fb");
    request.insert("password", "asdasd123");

    QVariant result = command(request);
    QVERIFY(result.toBool());

    const Xeth::ScanCriteria & criteria = synchronizer.getScanCriteria();
    Xeth::EthereumKeyStore & keys = database.getEthereumKeys();
    QVERIFY(getSize(criteria.begin(), criteria.end())==1);
    QVERIFY(getSize(keys.begin(), keys.end())==1);
}

void ImportEthereumKeyCommandTest::testInvalidRequest()
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


void ImportEthereumKeyCommandTest::testRenamedFile()
{
    Xeth::DataBase & database = _context.getDataBase();
    Xeth::Synchronizer & synchronizer = _context.getSynchronizer();

    Xeth::ImportEthereumKeyCommand command(database, synchronizer);
    QVariantMap request;
    request.insert("file", "data/key/ethbackup");
    request.insert("password", "asdasd123");
    QVariant result = command(request);
    QVERIFY(result.toBool());

    const Xeth::ScanCriteria & criteria = synchronizer.getScanCriteria();
    Xeth::EthereumKeyStore & keys = database.getEthereumKeys();
    QVERIFY(getSize(criteria.begin(), criteria.end())==2);
    QVERIFY(getSize(keys.begin(), keys.end())==2);
}

void ImportEthereumKeyCommandTest::testMalformedFile()
{
    Xeth::DataBase & database = _context.getDataBase();
    Xeth::Synchronizer & synchronizer = _context.getSynchronizer();

    Xeth::ImportEthereumKeyCommand command(database, synchronizer);
    QVariantMap request;
    request.insert("file", "data/key/UTC--2016-02-09T04-33-27.436497--7420f23ff3e5c9d713f87d9db5a0a18bb9bfb6d0");
    request.insert("password", "asdasd123");

    QVariant result = command(request);
    QVERIFY(!result.toBool());

    const Xeth::ScanCriteria & criteria = synchronizer.getScanCriteria();
    Xeth::EthereumKeyStore & keys = database.getEthereumKeys();
    QVERIFY(getSize(criteria.begin(), criteria.end())==1);
    QVERIFY(getSize(keys.begin(), keys.end())==1);
}


void ImportEthereumKeyCommandTest::testImportNonExistendFile()
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

void ImportEthereumKeyCommandTest::cleanupTestCase()
{}

template<class Iterator>
size_t ImportEthereumKeyCommandTest::getSize(Iterator begin, Iterator end)
{
    size_t size = 0;
    for(;begin!=end; ++begin)
    {
        size++;
    }
    return size;
}

#endif
