#pragma once

#include <QObject>
#include <QJsonObject>
#include <QTest>

#include "types/EthereumKey.hpp"
#include "types/Cipher.hpp"
#include "database/EthereumKeyStore.hpp"

#include "simulator/DataBaseDirectory.hpp"




class EthereumKeyStoreTest : public QObject
{
    Q_OBJECT
    public:
        EthereumKeyStoreTest();

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
        Xeth::EthereumKeyStore _store;
};

