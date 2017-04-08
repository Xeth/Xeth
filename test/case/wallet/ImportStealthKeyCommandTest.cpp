#include "ImportStealthKeyCommandTest.hpp"

#if __GETH_SIMULATOR_ENABLED__

ImportStealthKeyCommandTest::ImportStealthKeyCommandTest() :
    _context(true)
{}


void ImportStealthKeyCommandTest::testImport()
{
    Xeth::DataBase & database = _context.getDataBase();
    Xeth::Synchronizer & synchronizer = _context.getSynchronizer();
    Xeth::ImportStealthKeyCommand command(database, synchronizer);
    QVariantMap request;
    request.insert("file", "data/key/3oTYbZG4ZUsJatou8gmtJatRU19Sn5HXDWnhjRStbMpRsyT4UD4hApbnjuvZThmj1TtTgbbLbUiZ9hrKkjRwcTpV7uxBnEoA1ZsiZCw.skey");
    request.insert("password", "asdasd123");
    QVariant result = command(request);
    QVERIFY(result.toBool());

    const Xeth::ScanCriteria & criteria = synchronizer.getScanCriteria();
    Xeth::StealthKeyStore & keys = database.getStealthKeys();
    QVERIFY(getSize(criteria.begin(), criteria.end())==1);
    QVERIFY(getSize(keys.begin(), keys.end())==1);
}

void ImportStealthKeyCommandTest::testInvalidRequest()
{
    Xeth::DataBase & database = _context.getDataBase();
    Xeth::Synchronizer & synchronizer = _context.getSynchronizer();
    Xeth::ImportStealthKeyCommand command(database, synchronizer);
    QVariantMap request;
    QVariant result = command(request);
    QVERIFY(!result.toBool());

    const Xeth::ScanCriteria & criteria = synchronizer.getScanCriteria();
    Xeth::StealthKeyStore & keys = database.getStealthKeys();
    QVERIFY(getSize(criteria.begin(), criteria.end())==1);
    QVERIFY(getSize(keys.begin(), keys.end())==1);
}


void ImportStealthKeyCommandTest::testRenamedFile()
{
    Xeth::DataBase & database = _context.getDataBase();
    Xeth::Synchronizer & synchronizer = _context.getSynchronizer();
    Xeth::ImportStealthKeyCommand command(database, synchronizer);
    QVariantMap request;
    request.insert("file", "data/key/stealthbackup.skey");
    request.insert("password", "asdasd123");
    QVariant result = command(request);
    QVERIFY(result.toBool());

    const Xeth::ScanCriteria & criteria = synchronizer.getScanCriteria();
    Xeth::StealthKeyStore & keys = database.getStealthKeys();
    QVERIFY(getSize(criteria.begin(), criteria.end())==2);
    QVERIFY(getSize(keys.begin(), keys.end())==2);
}

void ImportStealthKeyCommandTest::testMalformedFile()
{
    Xeth::DataBase & database = _context.getDataBase();
    Xeth::Synchronizer & synchronizer = _context.getSynchronizer();
    Xeth::ImportStealthKeyCommand command(database, synchronizer);
    QVariantMap request;
    request.insert("file", "data/key/3oTYZ99VRU4oAqBarSjVAGZpQ1XfyftWkQYJQZKSRAzWAzCizPFS4sqrfZFXhgpQ473jVUJ5mZ5EYviUp9dfPsnD2kQgLWzFtshbCRf.skey");
    request.insert("password", "asdasd123");
    QVariant result = command(request);
    QVERIFY(!result.toBool());

    const Xeth::ScanCriteria & criteria = synchronizer.getScanCriteria();
    Xeth::StealthKeyStore & keys = database.getStealthKeys();
    QVERIFY(getSize(criteria.begin(), criteria.end())==1);
    QVERIFY(getSize(keys.begin(), keys.end())==1);
}


void ImportStealthKeyCommandTest::testImportNonExistendFile()
{
    Xeth::DataBase & database = _context.getDataBase();
    Xeth::Synchronizer & synchronizer = _context.getSynchronizer();
    Xeth::ImportStealthKeyCommand command(database, synchronizer);
    QVariantMap request;
    request.insert("file", "data/key/nonexistentkey");
    request.insert("password", "asdasd123");
    QVariant result = command(request);
    QVERIFY(!result.toBool());

    const Xeth::ScanCriteria & criteria = synchronizer.getScanCriteria();
    Xeth::StealthKeyStore & keys = database.getStealthKeys();
    QVERIFY(getSize(criteria.begin(), criteria.end())==2);
    QVERIFY(getSize(keys.begin(), keys.end())==2);
}

void ImportStealthKeyCommandTest::cleanupTestCase()
{}

template<class Iterator>
size_t ImportStealthKeyCommandTest::getSize(Iterator begin, Iterator end)
{
    size_t size = 0;
    for(;begin!=end; ++begin)
    {
        size++;
    }
    return size;
}

#endif
