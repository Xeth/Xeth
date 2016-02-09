#include "ScanIndexStoreTest.hpp"

void ScanIndexStoreTest::initTestCase()
{
    _directory.createIfNotExists();
}

void ScanIndexStoreTest::testOpen()
{
    QVERIFY(_store.openNoThrow(_directory.getPath() + "scanindex"));
}

void ScanIndexStoreTest::testInsert()
{
    QVERIFY(_store.insert("address1", 1));
    QVERIFY(_store.insert("address2", 2));
    QVERIFY(_store.insert("address3", 3));
}

void ScanIndexStoreTest::testUpdate()
{
    QVERIFY(_store.insert("address3", 4));
}

void ScanIndexStoreTest::testGet()
{
    QVERIFY(_store.get("address1") == 1);
    QVERIFY(_store.get("address2") == 2);
    QVERIFY(_store.get("address3") == 4);
}

void ScanIndexStoreTest::testGetEmpty()
{
    QVERIFY(_store.get("address4") == 0);
}

void ScanIndexStoreTest::cleanupTestCase()
{
    _directory.remove();
}
