#include "GenerateStealthKeyTest.hpp"

#if __GETH_SIMULATOR_ENABLED__

GenerateStealthKeyTest::GenerateStealthKeyTest() :
    _context(true)
{}


void GenerateStealthKeyTest::testGenerate()
{
    Xeth::DataBase & database = _context.getDataBase();
    Xeth::Synchronizer & synchronizer = _context.getSynchronizer();
    Xeth::GenerateStealthKeyCommand command(database, synchronizer);
    QVariantMap request;
    request.insert("password","asdasd123");
    QVariant result = command(request);
    QVERIFY(result.toBool());

    const Xeth::ScanCriteria & criteria = synchronizer.getScanCriteria();
    Xeth::StealthKeyStore & keys = database.getStealthKeys();
    QVERIFY(getSize(criteria.begin(), criteria.end())==1);
    QVERIFY(getSize(keys.begin(), keys.end())==1);
}


void GenerateStealthKeyTest::testGenerateFromEntropy()
{
    Xeth::DataBase & database = _context.getDataBase();
    Xeth::Synchronizer & synchronizer = _context.getSynchronizer();
    Xeth::GenerateStealthKeyCommand command(database, synchronizer);
    QVariantMap request;
    request.insert("password", "asdasd123");
    request.insert("entropy", "asdasdasdasdasdasdasdasdasdasdasdasdasdasdasdasdasdasdasdasdasdasdasdasdasdasdasdasdasdasdasdasdasdasdasdasdasdasdasdasdasdasdasdasd");
    QVariant result = command(request);
    QVERIFY(result.toBool());
    Xeth::StealthKeyStore & keys = database.getStealthKeys();
    const Xeth::ScanCriteria & criteria = synchronizer.getScanCriteria();
    QVERIFY(getSize(criteria.begin(), criteria.end())==2);
    QVERIFY(getSize(keys.begin(), keys.end())==2);
}
#include "GenerateStealthKeyTest.hpp"

void GenerateStealthKeyTest::testInvalidEntropy()
{
    Xeth::DataBase & database = _context.getDataBase();
    Xeth::Synchronizer & synchronizer = _context.getSynchronizer();
    Xeth::GenerateStealthKeyCommand command(database, synchronizer);
    QVariantMap request;
    request.insert("password", "adsasd123");
    request.insert("entropy", "asdas");
    QVariant result = command(request);
    QVERIFY(!result.toBool());
    Xeth::StealthKeyStore & keys = database.getStealthKeys();
    const Xeth::ScanCriteria & criteria = synchronizer.getScanCriteria();
    QVERIFY(getSize(criteria.begin(), criteria.end())==2);
    QVERIFY(getSize(keys.begin(), keys.end())==2);
}


void GenerateStealthKeyTest::testInvalidPassword()
{
    Xeth::DataBase & database = _context.getDataBase();
    Xeth::Synchronizer & synchronizer = _context.getSynchronizer();
    Xeth::GenerateStealthKeyCommand command(database, synchronizer);
    QVariantMap request;
    request.insert("entropy", "asdas");
    QVariant result = command(request);
    QVERIFY(!result.toBool());
    Xeth::StealthKeyStore & keys = database.getStealthKeys();
    const Xeth::ScanCriteria & criteria = synchronizer.getScanCriteria();
    QVERIFY(getSize(criteria.begin(), criteria.end())==2);
    QVERIFY(getSize(keys.begin(), keys.end())==2);
}

void GenerateStealthKeyTest::cleanupTestCase()
{
    _context.getGeth().stop();
}

template<class Iterator>
size_t GenerateStealthKeyTest::getSize(Iterator begin, Iterator end)
{
    size_t size = 0;
    for(;begin!=end; ++begin)
    {
        size++;
    }
    return size;
}

#endif
