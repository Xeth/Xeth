
#include "StealthKeyStoreTest.hpp"

StealthKeyStoreTest::StealthKeyStoreTest() :
    _directory(true),
    _store(_directory.getPath()+"keys")
{}




void StealthKeyStoreTest::testInsert()
{
    Xeth::StealthKeySerializer serializer;

    QVERIFY(_store.insert(serializer.unserialize(std::string("{\"address\":\"3oTYbZG4ZUsJatou8gmtJatRU19Sn5HXDWnhjRStbMpRsyT4UD4hApbnjuvZThmj1TtTgbbLbUiZ9hrKkjRwcTpV7uxBnEoA1ZsiZCw\",\"scan\":\"2966bfcaa0e736689eb14ff543f5c396ee41e086651a06bb57d0c3b52c8585c4\",\"spend\":[{\"pub\":\"0281b607128c8211ca903b65aae6e7cb051f66553c8a1ffeee7092aac463c17a05\",\"secret\":{\"cipher\":\"aes-128-ctr\",\"cipherparams\":{\"iv\":\"eabb8507072ecaba6964d145dfc6d609\"},\"ciphertext\":\"757e113c66132b33acec2e287d630d4fafda72b31300c53bc9f6ca64991cc64a\",\"kdf\":\"scrypt\",\"kdfparams\":{\"dklen\":32,\"n\":262144,\"p\":1,\"r\":8,\"salt\":\"cabc1fce88dc16f4b968905e057591150fb830b6a87cc19eb62c7ac02cdeffb7\"},\"mac\":\"55d17be909b1589c9db4d7e1d1e017c5ba7892b121df8c6ad6facc152f69eac5\"}}],\"time\":1454983283,\"version\":1}"))));

    QVERIFY(_store.insert(serializer.unserialize(std::string("{\"address\":\"3oTYcWA1XeEvkx4JB3MKq8FuSVgESQZG53L8DhMRWY7rnh8tb15cdDLVfGDZKZ5K3XYmwXg3mNSqiZvcWAtXFym4QMR9owhBGTFcgjZ\",\"scan\":\"b017fb3574239ee68c63aeb9c16c76d8e07e360511df53932feedbd3be453a03\",\"spend\":[{\"pub\":\"030f09073665b53483b2eff73df7c6424352578e037732241ca08512536b36d4dc\",\"secret\":{\"cipher\":\"aes-128-ctr\",\"cipherparams\":{\"iv\":\"3d6889095b6b65c7e1ac4b6cd0b9440a\"},\"ciphertext\":\"3618c27251da03981d0910d45253f99f40e8a2fb56960f2a2347084d865a61ad\",\"kdf\":\"scrypt\",\"kdfparams\":{\"dklen\":32,\"n\":262144,\"p\":1,\"r\":8,\"salt\":\"2a8a8e6a603fc3e0e6ebf4d129385e94b5d5e28e9014e2531b403a70a0b661d4\"},\"mac\":\"fd18e450984e73dcfbf9872e0587c48fa6560287bc3a51ff0a2c1eacef73b406\"}}],\"time\":1454983284,\"version\":1}"))));

    QVERIFY(_store.insert(serializer.unserialize(std::string("{\"address\":\"3oTYZ99VRU4oAqBarSjVAGZpQ1XfyftWkQYJQZKSRAzWAzCizPFS4sqrfZFXhgpQ473jVUJ5mZ5EYviUp9dfPsnD2kQgLWzFtshbCRf\",\"scan\":\"89614f860433338a2405daf22f81fbca9eafc4ed68fda64ff560a62cacc8461d\",\"spend\":[{\"pub\":\"02f3a813feef1f06710f7e56f57564c3051d4b006f989d0306415ea9be587c2de1\",\"secret\":{\"cipher\":\"aes-128-ctr\",\"cipherparams\":{\"iv\":\"a53332587289624e0b59c7b32aa50e19\"},\"ciphertext\":\"cbea010dfc9ba2dcf3ad783f6d85d2e740410347b78428fa6d7947c95ed4170c\",\"kdf\":\"scrypt\",\"kdfparams\":{\"dklen\":32,\"n\":262144,\"p\":1,\"r\":8,\"salt\":\"4fbefebf9ba412b11ca4d63c697c1c4528af2c32c39c6c45da61198b20d02606\"},\"mac\":\"fa2fdd3114c5402826d561b5f3bbef51e056b062cc93d03ac28b0591aa64a047\"}}],\"time\":1454983284,\"version\":1}"))));


}

void StealthKeyStoreTest::checkKey(const std::string &address, const std::string checkStr, bool equal)
{
    Xeth::StealthKeyStore::Iterator it = _store.find(address.c_str());

    if(equal)
    {
        QVERIFY(it!=_store.end());
        Xeth::StealthKey key = *it;
        Xeth::StealthKeySerializer serializer;
        Xeth::StealthKey check = serializer.unserialize(checkStr);
        QVERIFY(key==check);
    }
    else
    {
        QVERIFY(it==_store.end());
    }
}

void StealthKeyStoreTest::testRandomAccessIteration()
{
     checkKey("3oTYbZG4ZUsJatou8gmtJatRU19Sn5HXDWnhjRStbMpRsyT4UD4hApbnjuvZThmj1TtTgbbLbUiZ9hrKkjRwcTpV7uxBnEoA1ZsiZCw", "{\"address\":\"3oTYbZG4ZUsJatou8gmtJatRU19Sn5HXDWnhjRStbMpRsyT4UD4hApbnjuvZThmj1TtTgbbLbUiZ9hrKkjRwcTpV7uxBnEoA1ZsiZCw\",\"scan\":\"2966bfcaa0e736689eb14ff543f5c396ee41e086651a06bb57d0c3b52c8585c4\",\"spend\":[{\"pub\":\"0281b607128c8211ca903b65aae6e7cb051f66553c8a1ffeee7092aac463c17a05\",\"secret\":{\"cipher\":\"aes-128-ctr\",\"cipherparams\":{\"iv\":\"eabb8507072ecaba6964d145dfc6d609\"},\"ciphertext\":\"757e113c66132b33acec2e287d630d4fafda72b31300c53bc9f6ca64991cc64a\",\"kdf\":\"scrypt\",\"kdfparams\":{\"dklen\":32,\"n\":262144,\"p\":1,\"r\":8,\"salt\":\"cabc1fce88dc16f4b968905e057591150fb830b6a87cc19eb62c7ac02cdeffb7\"},\"mac\":\"55d17be909b1589c9db4d7e1d1e017c5ba7892b121df8c6ad6facc152f69eac5\"}}],\"time\":1454983283,\"version\":1}", true);
     checkKey("3oTYcWA1XeEvkx4JB3MKq8FuSVgESQZG53L8DhMRWY7rnh8tb15cdDLVfGDZKZ5K3XYmwXg3mNSqiZvcWAtXFym4QMR9owhBGTFcgjZ","{\"address\":\"3oTYcWA1XeEvkx4JB3MKq8FuSVgESQZG53L8DhMRWY7rnh8tb15cdDLVfGDZKZ5K3XYmwXg3mNSqiZvcWAtXFym4QMR9owhBGTFcgjZ\",\"scan\":\"b017fb3574239ee68c63aeb9c16c76d8e07e360511df53932feedbd3be453a03\",\"spend\":[{\"pub\":\"030f09073665b53483b2eff73df7c6424352578e037732241ca08512536b36d4dc\",\"secret\":{\"cipher\":\"aes-128-ctr\",\"cipherparams\":{\"iv\":\"3d6889095b6b65c7e1ac4b6cd0b9440a\"},\"ciphertext\":\"3618c27251da03981d0910d45253f99f40e8a2fb56960f2a2347084d865a61ad\",\"kdf\":\"scrypt\",\"kdfparams\":{\"dklen\":32,\"n\":262144,\"p\":1,\"r\":8,\"salt\":\"2a8a8e6a603fc3e0e6ebf4d129385e94b5d5e28e9014e2531b403a70a0b661d4\"},\"mac\":\"fd18e450984e73dcfbf9872e0587c48fa6560287bc3a51ff0a2c1eacef73b406\"}}],\"time\":1454983284,\"version\":1}", true);
     checkKey("3oTYZ99VRU4oAqBarSjVAGZpQ1XfyftWkQYJQZKSRAzWAzCizPFS4sqrfZFXhgpQ473jVUJ5mZ5EYviUp9dfPsnD2kQgLWzFtshbCRf","{\"address\":\"3oTYZ99VRU4oAqBarSjVAGZpQ1XfyftWkQYJQZKSRAzWAzCizPFS4sqrfZFXhgpQ473jVUJ5mZ5EYviUp9dfPsnD2kQgLWzFtshbCRf\",\"scan\":\"89614f860433338a2405daf22f81fbca9eafc4ed68fda64ff560a62cacc8461d\",\"spend\":[{\"pub\":\"02f3a813feef1f06710f7e56f57564c3051d4b006f989d0306415ea9be587c2de1\",\"secret\":{\"cipher\":\"aes-128-ctr\",\"cipherparams\":{\"iv\":\"a53332587289624e0b59c7b32aa50e19\"},\"ciphertext\":\"cbea010dfc9ba2dcf3ad783f6d85d2e740410347b78428fa6d7947c95ed4170c\",\"kdf\":\"scrypt\",\"kdfparams\":{\"dklen\":32,\"n\":262144,\"p\":1,\"r\":8,\"salt\":\"4fbefebf9ba412b11ca4d63c697c1c4528af2c32c39c6c45da61198b20d02606\"},\"mac\":\"fa2fdd3114c5402826d561b5f3bbef51e056b062cc93d03ac28b0591aa64a047\"}}],\"time\":1454983284,\"version\":1}", true);
}


void StealthKeyStoreTest::testGetEmpty()
{
    checkKey("3oTYdxNtjoTqHdZFTD63VFwwHyywfbo5F7HxgiT4YQH3g7BEM48k23SMqowDBCxC5rLr2KNTvwpXQyBzDQLtouk3LkRKdVVbUNgNfio", "", false);
}


void StealthKeyStoreTest::testIteration()
{
    int iterations = 0;
    for(Xeth::StealthKeyStore::Iterator it = _store.begin(), end = _store.end(); it!=end; ++it)
    {
        iterations++;
    }

    QCOMPARE(iterations, 3);
}




void StealthKeyStoreTest::cleanupTestCase()
{
    QVERIFY(_directory.remove());
}
