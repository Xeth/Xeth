#pragma once

#include <QTest>



#include "simulator/DataBaseDirectory.hpp"
#include "database/AddressBookStore.hpp"


class AddressBookStoreTest : public QObject
{
    Q_OBJECT


    private slots:
        void initTestCase();
        void testOpen();
        void testInsert();
        void testInsertDuplicate();
        void testGet();
        void testGetEmpty();
        void testIteration();
        void testReverseIteration();
        void testFind();
        void testFindEmpty();
        void testMove();
        void testMoveEmpty();
        void testReplace();
        void testRemove();
        void cleanupTestCase();

    private:
        DataBaseDirectory _directory;
        Xeth::AddressBookStore _store;
};

