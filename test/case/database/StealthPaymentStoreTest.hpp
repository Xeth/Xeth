#pragma once

#include <QObject>
#include <QJsonObject>
#include <QTest>

#include "database/StealthPaymentStore.hpp"

#include "simulator/DataBaseDirectory.hpp"




class StealthPaymentStoreTest : public QObject
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
        void cleanupTestCase();

    private:
        DataBaseDirectory _directory;
        Xeth::StealthPaymentStore _store;
};

