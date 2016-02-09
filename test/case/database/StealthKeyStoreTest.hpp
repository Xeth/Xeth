#pragma once

#include <QObject>
#include <QJsonObject>
#include <QTest>

#include "types/StealthKey.hpp"
#include "types/Cipher.hpp"
#include "database/StealthKeyStore.hpp"

#include "simulator/DataBaseDirectory.hpp"




class StealthKeyStoreTest : public QObject
{
    Q_OBJECT
    public:
        StealthKeyStoreTest();

    private:
        void checkKey(const std::string &address, const std::string checkStr, bool equal);

    private slots:
        void testInsert();
        void testGetEmpty();
        void testIteration();
        void testRandomAccessIteration();
        void cleanupTestCase();

    private:
        DataBaseDirectory _directory;
        Xeth::StealthKeyStore _store;
};

