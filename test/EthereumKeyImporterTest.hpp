#pragma once

#include <QObject>
#include <QJsonObject>
#include <QTest>

#include "database/EthereumKeyStore.hpp"
#include "DataBaseDirectory.hpp"




class EthereumKeyImporterTest : public QObject
{
    Q_OBJECT
    public:
        EthereumKeyImporterTest();

    private:
        void checkKey(const std::string &address, const std::string &path);

    private slots:
        void testImport();
        void testNonExistentFile();
        void testMalformedFile();
        void testIncorrectName();

    private:
        DataBaseDirectory _directory;
        Xeth::EthereumKeyStore _store;
};

