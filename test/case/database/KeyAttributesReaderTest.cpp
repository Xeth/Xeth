#include "KeyAttributesReaderTest.hpp"

void KeyAttributesReaderTest::checkStealthKeyCreationTime()
{
    Xeth::KeyAttributesReader<Xeth::StealthKeyStore> reader("data/key/3oTYcWA1XeEvkx4JB3MKq8FuSVgESQZG53L8DhMRWY7rnh8tb15cdDLVfGDZKZ5K3XYmwXg3mNSqiZvcWAtXFym4QMR9owhBGTFcgjZ.skey");
    QVERIFY(reader.getCreationTime() == 1454983284);
}

void KeyAttributesReaderTest::checkStealthKeyAddress()
{
    Xeth::KeyAttributesReader<Xeth::StealthKeyStore> reader("data/key/3oTYcWA1XeEvkx4JB3MKq8FuSVgESQZG53L8DhMRWY7rnh8tb15cdDLVfGDZKZ5K3XYmwXg3mNSqiZvcWAtXFym4QMR9owhBGTFcgjZ.skey");
    QVERIFY(reader.getAddress()=="3oTYcWA1XeEvkx4JB3MKq8FuSVgESQZG53L8DhMRWY7rnh8tb15cdDLVfGDZKZ5K3XYmwXg3mNSqiZvcWAtXFym4QMR9owhBGTFcgjZ");
}

void KeyAttributesReaderTest::checkNonExistentStealthKey()
{
    bool thrown = false;
    try
    {
        Xeth::KeyAttributesReader<Xeth::StealthKeyStore> reader("data/key/3oTYcKA1XeEvkx4JB3MKq8FuSVgESQZG53L8DhMRWY7rnh8tb15cdDLVfGDZKZ5K3XYmwXg3mNSqiZvcWAtXFym4QMR9owhBGTFcgjZ.skey");
    }
    catch(...)
    {
        thrown = true;
    }
    QVERIFY(thrown);
}

void KeyAttributesReaderTest::checkEthereumKeyCreationTime()
{
    Xeth::KeyAttributesReader<Xeth::EthereumKeyStore> reader("data/key/UTC--2016-02-09T04:33:27.434985--d4e7fd527d69f33ad9f88e16dcb218598dc3a3ee");
    QVERIFY(reader.getCreationTime()==1454992407);
}

void KeyAttributesReaderTest::checkEthereumKeyAddress()
{
    Xeth::KeyAttributesReader<Xeth::EthereumKeyStore> reader("data/key/UTC--2016-02-09T04:33:27.434985--d4e7fd527d69f33ad9f88e16dcb218598dc3a3ee");
    QVERIFY(reader.getAddress()=="d4e7fd527d69f33ad9f88e16dcb218598dc3a3ee");
}

void KeyAttributesReaderTest::checkNonExistentEthereumKey()
{
    bool thrown = false;
    try
    {
        Xeth::KeyAttributesReader<Xeth::EthereumKeyStore> reader("data/key/UTC--2016-02-09T04:33:27.434985--r4e7fd527d69f33ad9f88e16dcb218598dc3a3ee");
    }
    catch(...)
    {
        thrown = true;
    }
    QVERIFY(thrown);
}
