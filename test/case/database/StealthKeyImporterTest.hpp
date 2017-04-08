#pragma once

#include <QObject>
#include <QJsonObject>
#include <QTest>

#include "types/StealthKey.hpp"
#include "types/Cipher.hpp"
#include "database/StealthKeyStore.hpp"
#include "database/KeyImporter.hpp"

#include "simulator/DataBaseDirectory.hpp"




class StealthKeyImporterTest : public QObject
{
    Q_OBJECT
    public:
        StealthKeyImporterTest();

    private:
        void checkKey(const std::string &address, const std::string &path);

    private slots:
        void testImport();
        void testNonExistentFile();
        void testMalformedFile();
        void testIncorrectName();

    private:
        DataBaseDirectory _directory;
        Xeth::StealthKeyStore _store;
};

