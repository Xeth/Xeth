#pragma once

#include <QObject>
#include <QTest>

#include "database/ScanIndexStore.hpp"
#include "simulator/DataBaseDirectory.hpp"



class ScanIndexStoreTest : public QObject
{
    Q_OBJECT

    private slots:
        void initTestCase();
        void testOpen();
        void testInsert();
        void testUpdate();
        void testGet();
        void testGetEmpty();
        void cleanupTestCase();

    private:
        DataBaseDirectory _directory;
        Xeth::ScanIndexStore _store;
};
