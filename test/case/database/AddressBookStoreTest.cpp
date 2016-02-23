#include "AddressBookStoreTest.hpp"

void AddressBookStoreTest::initTestCase()
{
    _directory.createIfNotExists();
}

void AddressBookStoreTest::cleanupTestCase()
{
    _directory.remove();
}

void AddressBookStoreTest::testOpen()
{
    QVERIFY(_store.openNoThrow(_directory.getPath() / "addressbook"));
}

void AddressBookStoreTest::testInsert()
{
    QJsonObject obj;
    obj.insert("address", "someaddress1");
    QVERIFY(_store.insert("foo", obj));
    obj.insert("address", "someaddress2");
    QVERIFY(_store.insert("bar", obj));
    obj.insert("address", "someaddress3");
    QVERIFY(_store.insert("foobar", obj));
}

void AddressBookStoreTest::testInsertDuplicate()
{
    QJsonObject obj;
    obj.insert("address", "someaddress4");
    QVERIFY(_store.insert("foo", obj) == false);
}

void AddressBookStoreTest::testGet()
{
    QJsonObject result = _store.get("foo");
    QVERIFY(result["address"] == "someaddress1");
    result = _store.get("bar");
    QVERIFY(result["address"] == "someaddress2");
    result = _store.get("foobar");
    QVERIFY(result["address"] == "someaddress3");
}

void AddressBookStoreTest::testGetEmpty()
{
    QJsonObject result = _store.get("unknown");
    QVERIFY(result["address"].isNull());
}

void AddressBookStoreTest::testFind()
{
    Xeth::AddressBookStore::Iterator it = _store.find("foo");
    QVERIFY(it != _store.end());
    QVERIFY((*it)["address"] == "someaddress1");

    it = _store.find("bar");
    QVERIFY(it != _store.end());
    QVERIFY((*it)["address"] == "someaddress2");

    it = _store.find("foobar");
    QVERIFY(it != _store.end());
    QVERIFY((*it)["address"] == "someaddress3");
}

void AddressBookStoreTest::testFindEmpty()
{
    Xeth::AddressBookStore::Iterator it = _store.find("unknown");
    QVERIFY(it == _store.end());
}


void AddressBookStoreTest::testIteration()
{
    size_t num = 0;
    for(Xeth::AddressBookStore::Iterator it = _store.begin(), end=_store.end(); it!= end; ++it)
    {
        num++;
    }

    QVERIFY(num == 3);
}

void AddressBookStoreTest::testReverseIteration()
{
    size_t num = 0;
    for(Xeth::AddressBookStore::ReverseIterator it = _store.rbegin(), end=_store.rend(); it!= end; ++it)
    {
        num++;
    }

    QVERIFY(num == 3);
}

void AddressBookStoreTest::testMove()
{
    QVERIFY(_store.move("foobar", "foobar2"));
    QVERIFY(_store.get("foobar").isEmpty());
    QVERIFY(_store.get("foobar2")["address"] == "someaddress3");
}

void AddressBookStoreTest::testMoveEmpty()
{
    QVERIFY(_store.move("foobar", "foobar3") == false);
}


void AddressBookStoreTest::testReplace()
{
    QJsonObject obj;
    obj["address"] = "someaddress4";
    QVERIFY(_store.replace("foo", obj));

    QVERIFY(_store.get("foo")["address"] == "someaddress4");
}



void AddressBookStoreTest::testRemove()
{
    QVERIFY(_store.remove("foo"));
    QVERIFY(_store.get("foo").isEmpty());
}


