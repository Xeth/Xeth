
#include "StealthKeyImporterTest.hpp"

StealthKeyImporterTest::StealthKeyImporterTest() :
    _directory(true),
    _store(_directory.getPath()+"keys")
{}




void StealthKeyImporterTest::checkKey(const std::string &address, const std::string &filename)
{
    Xeth::StealthKeyStore::Iterator it = _store.find(address.c_str());
    Xeth::ObjectReader<Xeth::StealthKey, Xeth::StealthKeySerializer> reader;
    QVERIFY(it!=_store.end());
    Xeth::StealthKey key = *it;
    Xeth::StealthKey check = reader.read(filename);
    QVERIFY(key==check);
}


void StealthKeyImporterTest::testImport()
{
    Xeth::StealthKeyImporter importer(_store);
    QVERIFY(importer.import("data/key/3oTYbZG4ZUsJatou8gmtJatRU19Sn5HXDWnhjRStbMpRsyT4UD4hApbnjuvZThmj1TtTgbbLbUiZ9hrKkjRwcTpV7uxBnEoA1ZsiZCw.skey"));
    checkKey("3oTYbZG4ZUsJatou8gmtJatRU19Sn5HXDWnhjRStbMpRsyT4UD4hApbnjuvZThmj1TtTgbbLbUiZ9hrKkjRwcTpV7uxBnEoA1ZsiZCw", "data/key/3oTYbZG4ZUsJatou8gmtJatRU19Sn5HXDWnhjRStbMpRsyT4UD4hApbnjuvZThmj1TtTgbbLbUiZ9hrKkjRwcTpV7uxBnEoA1ZsiZCw.skey");
}

void StealthKeyImporterTest::testNonExistentFile()
{
    Xeth::StealthKeyImporter importer(_store);
    QVERIFY(!importer.import("data/key/somenonexistentkey.skey"));
}

void StealthKeyImporterTest::testMalformedFile()
{
    Xeth::StealthKeyImporter importer(_store);
    QVERIFY(!importer.import("data/key/3oTYZ99VRU4oAqBarSjVAGZpQ1XfyftWkQYJQZKSRAzWAzCizPFS4sqrfZFXhgpQ473jVUJ5mZ5EYviUp9dfPsnD2kQgLWzFtshbCRf.skey"));
}

void StealthKeyImporterTest::testIncorrectName()
{
    Xeth::StealthKeyImporter importer(_store);
    QVERIFY(importer.import("data/key/stealthbackup.skey"));
    checkKey("3oTYcWA1XeEvkx4JB3MKq8FuSVgESQZG53L8DhMRWY7rnh8tb15cdDLVfGDZKZ5K3XYmwXg3mNSqiZvcWAtXFym4QMR9owhBGTFcgjZ", "data/key/stealthbackup.skey");
}
