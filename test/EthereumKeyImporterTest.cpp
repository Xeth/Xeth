
#include "EthereumKeyImporterTest.hpp"

EthereumKeyImporterTest::EthereumKeyImporterTest() :
    _directory(true),
    _store(_directory.getPath()+"keys")
{}




void EthereumKeyImporterTest::checkKey(const std::string &address, const std::string &filename)
{
    Xeth::EthereumKeyStore::Iterator it = _store.find(address.c_str());
    Xeth::ObjectReader<Xeth::EthereumKey, Xeth::EthereumKeySerializer> reader;
    QVERIFY(it!=_store.end());
    Xeth::EthereumKey key = *it;
    Xeth::EthereumKey check = reader.read(filename);
    QVERIFY(key==check);
}


void EthereumKeyImporterTest::testImport()
{
    Xeth::EthereumKeyImporter importer(_store);
    QVERIFY(importer.import("key/UTC--2016-02-09T04:33:27.433427--8a3015660bca082f81e53b2036bea9d41a8f79a8"));
    checkKey("8a3015660bca082f81e53b2036bea9d41a8f79a8", "key/UTC--2016-02-09T04:33:27.433427--8a3015660bca082f81e53b2036bea9d41a8f79a8");
}

void EthereumKeyImporterTest::testNonExistentFile()
{
    Xeth::EthereumKeyImporter importer(_store);
    QVERIFY(!importer.import("key/somenonexistentkey.skey"));
}

void EthereumKeyImporterTest::testMalformedFile()
{
    Xeth::EthereumKeyImporter importer(_store);
    QVERIFY(!importer.import("3oTYZ99VRU4oAqBarSjVAGZpQ1XfyftWkQYJQZKSRAzWAzCizPFS4sqrfZFXhgpQ473jVUJ5mZ5EYviUp9dfPsnD2kQgLWzFtshbCRf.skey"));
}

void EthereumKeyImporterTest::testIncorrectName()
{
    Xeth::EthereumKeyImporter importer(_store);
    QVERIFY(importer.import("key/ethbackup"));
    checkKey("d4e7fd527d69f33ad9f88e16dcb218598dc3a3ee", "key/ethbackup");
}
