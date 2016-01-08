
#include "TransactionStoreTest.hpp"

#include <QDebug>

void TransactionStoreTest::initTestCase()
{
    QVERIFY(_directory.createIfNotExistsNoThrow());
}


void TransactionStoreTest::testOpen()
{
    QVERIFY(_store.openNoThrow(_directory.getPath()+"transactions"));
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


void TransactionStoreTest::testGet()
{
    QJsonObject transaction = _store.get("somehash1");
    qDebug()<<"got : "<<transaction;
    QVERIFY(transaction["hash"].toString() == "somehash1");
    QVERIFY(transaction["index"].toInt() == 0);

    transaction = _store.get("somehash2");
    qDebug()<<"got : "<<transaction;
    QVERIFY(transaction["hash"].toString() == "somehash2");
    QVERIFY(transaction["index"].toInt() == 1);

    transaction = _store.get("somehash3");
    qDebug()<<"got : "<<transaction;
    QVERIFY(transaction["hash"].toString() == "somehash3");
    QVERIFY(transaction["index"].toInt() == 2);
}


void TransactionStoreTest::testGetEmpty()
{
    QJsonObject transaction = _store.get("somehash4");
    QVERIFY(transaction.empty());
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
    qDebug()<<"here";
    QVERIFY(it != end);
    qDebug()<<"here2";
    qDebug()<<*it;
    QVERIFY((*it)["index"].toInt() == 1);
    QVERIFY((*it)["hash"].toString() == "somehash2");

    qDebug()<<"here3";
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
