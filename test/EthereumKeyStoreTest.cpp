
#include "EthereumKeyStoreTest.hpp"

EthereumKeyStoreTest::EthereumKeyStoreTest() :
    _directory(true),
    _store(_directory.getPath()+"keys")
{}




void EthereumKeyStoreTest::testInsert()
{
    Xeth::EthereumKeySerializer serializer;

    QVERIFY(_store.insert(serializer.unserialize(std::string("{\"Crypto\":{\"cipher\":\"aes-128-ctr\",\"cipherparams\":{\"iv\":\"f4e7137194e364a20236cfa6e325d00d\"},\"ciphertext\":\"3a053096af2f1dacdc83e669ea64e6d28d52a3a8a9f2d08db589fbbeac4ea1ac\",\"kdf\":\"scrypt\",\"kdfparams\":{\"dklen\":32,\"n\":262144,\"p\":1,\"r\":8,\"salt\":\"39bec0376261a900be31feaa373b7e7f69287a1e6e503bee425645aba84d968a\"},\"mac\":\"5580eab36b5aa97079bb4cb123212639c54c596f9b6dd74f92c43d9fca442409\"},\"address\":\"8a3015660bca082f81e53b2036bea9d41a8f79a8\",\"id\":\"be8adfb5-fd55-4754-a741-42dc7c2408ba\",\"version\":3}"))));

    QVERIFY(_store.insert(serializer.unserialize(std::string("{\"Crypto\":{\"cipher\":\"aes-128-ctr\",\"cipherparams\":{\"iv\":\"15b24b8b907b6cd2826675c9a3fd8b54\"},\"ciphertext\":\"d19c1be5cea933ef44a72d6ced70524405b2f460f5389de0ff7bdd57486b80a3\",\"kdf\":\"scrypt\",\"kdfparams\":{\"dklen\":32,\"n\":262144,\"p\":1,\"r\":8,\"salt\":\"6c4a41633a1c22629d065e646fdd61fa535bae034ae8945a49f6d3244091fa8d\"},\"mac\":\"a4d0c97a970ca9a25a9dfe1480d18a5bb29a00983f72548e66cf71bd7a69022f\"},\"address\":\"d4e7fd527d69f33ad9f88e16dcb218598dc3a3ee\",\"id\":\"e1b28449-1a4e-4a83-8d41-3db38675686d\",\"version\":3}"))));

    QVERIFY(_store.insert(serializer.unserialize(std::string("{\"Crypto\":{\"cipher\":\"aes-128-ctr\",\"cipherparams\":{\"iv\":\"d18cba2c2b3ffb8c2c3bf06549771974\"},\"ciphertext\":\"fd986f9b3e052018938d3c3cb9909bcceaf584c50900e3715fece5e3252c2054\",\"kdf\":\"scrypt\",\"kdfparams\":{\"dklen\":32,\"n\":262144,\"p\":1,\"r\":8,\"salt\":\"bd838424e0216c4cfcae552171cae4636c7557fbcdb746e5e2186d1469450439\"},\"mac\":\"e54796485803be1f9242fb0ea6163e3f63011f7a63ba9a3ff1cd35f893d43c1f\"},\"address\":\"7420f23ff3e5c9d713f87d9db5a0a18bb9bfb6d0\",\"id\":\"4e97f00a-0f10-45f3-9731-aa7f005c95f6\",\"version\":3}"))));


}

void EthereumKeyStoreTest::checkKey(const std::string &address, const std::string checkStr, bool equal)
{
    Xeth::EthereumKeyStore::Iterator it = _store.find(address.c_str());

    if(equal)
    {
        QVERIFY(it!=_store.end());
        Xeth::EthereumKey key = *it;
        Xeth::EthereumKeySerializer serializer;
        Xeth::EthereumKey check = serializer.unserialize(checkStr);
        QVERIFY(key==check);
    }
    else
    {
        QVERIFY(it==_store.end());
    }
}

void EthereumKeyStoreTest::testRandomAccessIteration()
{
    checkKey("7420f23ff3e5c9d713f87d9db5a0a18bb9bfb6d0", "{\"Crypto\":{\"cipher\":\"aes-128-ctr\",\"cipherparams\":{\"iv\":\"d18cba2c2b3ffb8c2c3bf06549771974\"},\"ciphertext\":\"fd986f9b3e052018938d3c3cb9909bcceaf584c50900e3715fece5e3252c2054\",\"kdf\":\"scrypt\",\"kdfparams\":{\"dklen\":32,\"n\":262144,\"p\":1,\"r\":8,\"salt\":\"bd838424e0216c4cfcae552171cae4636c7557fbcdb746e5e2186d1469450439\"},\"mac\":\"e54796485803be1f9242fb0ea6163e3f63011f7a63ba9a3ff1cd35f893d43c1f\"},\"address\":\"7420f23ff3e5c9d713f87d9db5a0a18bb9bfb6d0\",\"id\":\"4e97f00a-0f10-45f3-9731-aa7f005c95f6\",\"version\":3}", true);

    checkKey("d4e7fd527d69f33ad9f88e16dcb218598dc3a3ee","{\"Crypto\":{\"cipher\":\"aes-128-ctr\",\"cipherparams\":{\"iv\":\"15b24b8b907b6cd2826675c9a3fd8b54\"},\"ciphertext\":\"d19c1be5cea933ef44a72d6ced70524405b2f460f5389de0ff7bdd57486b80a3\",\"kdf\":\"scrypt\",\"kdfparams\":{\"dklen\":32,\"n\":262144,\"p\":1,\"r\":8,\"salt\":\"6c4a41633a1c22629d065e646fdd61fa535bae034ae8945a49f6d3244091fa8d\"},\"mac\":\"a4d0c97a970ca9a25a9dfe1480d18a5bb29a00983f72548e66cf71bd7a69022f\"},\"address\":\"d4e7fd527d69f33ad9f88e16dcb218598dc3a3ee\",\"id\":\"e1b28449-1a4e-4a83-8d41-3db38675686d\",\"version\":3}", true);

    checkKey("8a3015660bca082f81e53b2036bea9d41a8f79a8", "{\"Crypto\":{\"cipher\":\"aes-128-ctr\",\"cipherparams\":{\"iv\":\"f4e7137194e364a20236cfa6e325d00d\"},\"ciphertext\":\"3a053096af2f1dacdc83e669ea64e6d28d52a3a8a9f2d08db589fbbeac4ea1ac\",\"kdf\":\"scrypt\",\"kdfparams\":{\"dklen\":32,\"n\":262144,\"p\":1,\"r\":8,\"salt\":\"39bec0376261a900be31feaa373b7e7f69287a1e6e503bee425645aba84d968a\"},\"mac\":\"5580eab36b5aa97079bb4cb123212639c54c596f9b6dd74f92c43d9fca442409\"},\"address\":\"8a3015660bca082f81e53b2036bea9d41a8f79a8\",\"id\":\"be8adfb5-fd55-4754-a741-42dc7c2408ba\",\"version\":3}", true);
}


void EthereumKeyStoreTest::testGetEmpty()
{
    checkKey("9a3015660bca082f81e53b2036bea9d41a8f79a8","{\"Crypto\":{\"cipher\":\"aes-128-ctr\",\"cipherparams\":{\"iv\":\"f4e7137194e364a20236cfa6e325d00d\"},\"ciphertext\":\"3a053096af2f1dacdc83e669ea64e6d28d52a3a8a9f2d08db589fbbeac4ea1ac\",\"kdf\":\"scrypt\",\"kdfparams\":{\"dklen\":32,\"n\":262144,\"p\":1,\"r\":8,\"salt\":\"39bec0376261a900be31feaa373b7e7f69287a1e6e503bee425645aba84d968a\"},\"mac\":\"5580eab36b5aa97079bb4cb123212639c54c596f9b6dd74f92c43d9fca442409\"},\"address\":\"8a3015660bca082f81e53b2036bea9d41a8f79a8\",\"id\":\"be8adfb5-fd55-4754-a741-42dc7c2408ba\",\"version\":3}", false);
}


void EthereumKeyStoreTest::testIteration()
{
    int iterations = 0;
    for(Xeth::EthereumKeyStore::Iterator it = _store.begin(), end = _store.end(); it!=end; ++it)
    {
        iterations++;
    }

    QCOMPARE(iterations, 3);
}




void EthereumKeyStoreTest::cleanupTestCase()
{
    QVERIFY(_directory.remove());
}
