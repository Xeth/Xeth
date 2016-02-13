#include "ImportStealthKeyTest.hpp"


ImportStealthKeyTest::ImportStealthKeyTest()
{}


void ImportStealthKeyTest::testImport()
{
    Xeth::DataBase & database = _context.getDataBase();
    Xeth::Synchronizer & synchronizer = _context.getSynchronizer();
    Xeth::ImportStealthKeyCommand command(database, synchronizer);
    QVariantMap request;
    request.insert("file", "data/key/3oTYbZG4ZUsJatou8gmtJatRU19Sn5HXDWnhjRStbMpRsyT4UD4hApbnjuvZThmj1TtTgbbLbUiZ9hrKkjRwcTpV7uxBnEoA1ZsiZCw.skey");
    QVariant result = command(request);
    QVERIFY(result.toBool());

    const Xeth::ScanCriteria & criteria = synchronizer.getScanCriteria();
    Xeth::StealthKeyStore & keys = database.getStealthKeys();
    QVERIFY(getSize(criteria.begin(), criteria.end())==1);
    QVERIFY(getSize(keys.begin(), keys.end())==1);
}

void ImportStealthKeyTest::testInvalidRequest()
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


void ImportStealthKeyTest::testRenamedFile()
{
    Xeth::DataBase & database = _context.getDataBase();
    Xeth::Synchronizer & synchronizer = _context.getSynchronizer();
    Xeth::ImportStealthKeyCommand command(database, synchronizer);
    QVariantMap request;
    request.insert("file", "data/key/stealthbackup.skey");
    QVariant result = command(request);
    QVERIFY(result.toBool());

    const Xeth::ScanCriteria & criteria = synchronizer.getScanCriteria();
    Xeth::StealthKeyStore & keys = database.getStealthKeys();
    QVERIFY(getSize(criteria.begin(), criteria.end())==2);
    QVERIFY(getSize(keys.begin(), keys.end())==2);
}

void ImportStealthKeyTest::testMalformedFile()
{
    Xeth::DataBase & database = _context.getDataBase();
    Xeth::Synchronizer & synchronizer = _context.getSynchronizer();
    Xeth::ImportStealthKeyCommand command(database, synchronizer);
    QVariantMap request;
    request.insert("file", "data/key/3oTYZ99VRU4oAqBarSjVAGZpQ1XfyftWkQYJQZKSRAzWAzCizPFS4sqrfZFXhgpQ473jVUJ5mZ5EYviUp9dfPsnD2kQgLWzFtshbCRf.skey");
    QVariant result = command(request);
    QVERIFY(!result.toBool());

    const Xeth::ScanCriteria & criteria = synchronizer.getScanCriteria();
    Xeth::StealthKeyStore & keys = database.getStealthKeys();
    QVERIFY(getSize(criteria.begin(), criteria.end())==1);
    QVERIFY(getSize(keys.begin(), keys.end())==1);
}


void ImportStealthKeyTest::testImportNonExistendFile()
{
    Xeth::DataBase & database = _context.getDataBase();
    Xeth::Synchronizer & synchronizer = _context.getSynchronizer();
    Xeth::ImportStealthKeyCommand command(database, synchronizer);
    QVariantMap request;
    request.insert("file", "data/key/nonexistentkey");
    QVariant result = command(request);
    QVERIFY(!result.toBool());

    const Xeth::ScanCriteria & criteria = synchronizer.getScanCriteria();
    Xeth::StealthKeyStore & keys = database.getStealthKeys();
    QVERIFY(getSize(criteria.begin(), criteria.end())==2);
    QVERIFY(getSize(keys.begin(), keys.end())==2);
}

void ImportStealthKeyTest::cleanupTestCase()
{
    _context.getGeth().stop();
}

template<class Iterator>
size_t ImportStealthKeyTest::getSize(Iterator begin, Iterator end)
{
    size_t size = 0;
    for(;begin!=end; ++begin)
    {
        size++;
    }
    return size;
}


