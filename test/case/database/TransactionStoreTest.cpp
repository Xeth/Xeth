
#include "TransactionStoreTest.hpp"


void TransactionStoreTest::initTestCase()
{
    QVERIFY(_directory.createIfNotExistsNoThrow());
}


void TransactionStoreTest::testOpen()
{
    QVERIFY(_store.openNoThrow(_directory.getPath() / "transactions"));
}

void TransactionStoreTest::testInsert()
{
    QJsonObject transaction;

    transaction.insert("hash", "somehash1");
    QVERIFY(_store.insert(transaction));

    transaction.insert("hash", "somehash2");
    QVERIFY(_store.insert(transaction));

    transaction.insert("hash", "somehash3");
    QVERIFY(_store.insert(transaction));
}



void TransactionStoreTest::testIteration()
{
    size_t count = 0;

    for(Xeth::TransactionStore::Iterator it = _store.begin(), end = _store.end(); it != end; ++it)
    {
        count++;
    }

    QVERIFY(count==3);
}


void TransactionStoreTest::testReverseIteration()
{
    size_t count = 0;

    for(Xeth::TransactionStore::ReverseIterator it = _store.rbegin(), end = _store.rend(); it != end; ++it)
    {
        count++;
    }

    QVERIFY(count==3);
}

void TransactionStoreTest::testRandomAccessIteration()
{
    Xeth::TransactionStore::Iterator it = _store.at(1), end = _store.end();
    QVERIFY(it != end);

    QVERIFY((*it)["hash"].toString() == "somehash2");

    size_t count = 0;

    for(;it!=end; ++it)
    {
        count++;
    }

    QVERIFY(count==2);

}

void TransactionStoreTest::cleanupTestCase()
{
    QVERIFY(_directory.remove());
}
