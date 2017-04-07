#pragma once

#include <QObject>
#include <QJsonObject>
#include <QTest>

#include "database/TransactionStore.hpp"

#include "simulator/DataBaseDirectory.hpp"




class TransactionStoreTest : public QObject
{
    Q_OBJECT

    private slots:
        void initTestCase();
        void testOpen();
        void testInsert();
        void testIteration();
        void testReverseIteration();
        void testRandomAccessIteration();
        void cleanupTestCase();

    private:
        DataBaseDirectory _directory;
        Xeth::TransactionStore _store;
};

