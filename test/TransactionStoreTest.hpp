#pragma once

#include <QObject>
#include <QJsonObject>
#include <QTest>

#include "database/TransactionStore.hpp"
#include "DataBaseDirectory.hpp"




class TransactionStoreTest : public QObject
{
    Q_OBJECT

    private slots:
        void initTestCase();
        void testOpen();
        void testInsert();
        void testGet();
        void testGetEmpty();
        void testIteration();
        void testReverseIteration();
        void testRandomAccessIteration();
        void cleanupTestCase();

    private:
        DataBaseDirectory _directory;
        Xeth::TransactionStore _store;
};

