
#include "StealthPaymentStoreTest.hpp"


void StealthPaymentStoreTest::initTestCase()
{
    QVERIFY(_directory.createIfNotExistsNoThrow());
}


void StealthPaymentStoreTest::testOpen()
{
    QVERIFY(_store.openNoThrow(_directory.getPath() / "payments"));
}

void StealthPaymentStoreTest::testInsert()
{
    QVERIFY(_store.insert("someaddress1", "somestealthaddress123", "sharedsecret1", "txid1"));
    QVERIFY(_store.insert("someaddress2", "somestealthaddress123", "sharedsecret2", "txid2"));
    QVERIFY(_store.insert("someaddress3", "somestealthaddress123", "sharedsecret3", "txid3"));
}


void StealthPaymentStoreTest::testGet()
{
    QJsonObject payment = _store.get("someaddress1");
    QVERIFY(payment["address"].toString() == "someaddress1");
    QVERIFY(payment["secret"].toString() == "sharedsecret1");
    QVERIFY(payment["txid"].toString() == "txid1");

    payment = _store.get("someaddress2");
    QVERIFY(payment["address"].toString() == "someaddress2");
    QVERIFY(payment["secret"].toString() == "sharedsecret2");
    QVERIFY(payment["txid"].toString() == "txid2");

    payment = _store.get("someaddress3");
    QVERIFY(payment["address"].toString() == "someaddress3");
    QVERIFY(payment["secret"].toString() == "sharedsecret3");
    QVERIFY(payment["txid"].toString() == "txid3");


}


void StealthPaymentStoreTest::testGetEmpty()
{
    QJsonObject payment = _store.get("someaddress4");
    QVERIFY(payment.empty());
}


void StealthPaymentStoreTest::testIteration()
{
    size_t count = 0;

    for(Xeth::StealthPaymentStore::Iterator it = _store.begin(), end = _store.end(); it != end; ++it)
    {
        count++;
    }

    QVERIFY(count==3);
}


void StealthPaymentStoreTest::testReverseIteration()
{
    size_t count = 0;

    for(Xeth::StealthPaymentStore::ReverseIterator it = _store.rbegin(), end = _store.rend(); it != end; ++it)
    {
        count++;
    }

    QVERIFY(count==3);
}



void StealthPaymentStoreTest::cleanupTestCase()
{
    QVERIFY(_directory.remove());
}
