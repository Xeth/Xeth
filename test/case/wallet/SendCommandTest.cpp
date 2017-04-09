#include "SendCommandTest.hpp"

#if __GETH_SIMULATOR_ENABLED__
SendCommandTest::SendCommandTest() :
    _context(true),
    _command(_context.getProvider(), _context.getDataBase())
{}


void SendCommandTest::initTestCase()
{
    Xeth::EthereumKeySerializer serializer;
    QVERIFY(_context.getDataBase().getEthereumKeys().insert(serializer.unserialize(std::string("{\"Crypto\":{\"cipher\":\"aes-128-ctr\",\"cipherparams\":{\"iv\":\"f4e7137194e364a20236cfa6e325d00d\"},\"ciphertext\":\"3a053096af2f1dacdc83e669ea64e6d28d52a3a8a9f2d08db589fbbeac4ea1ac\",\"kdf\":\"scrypt\",\"kdfparams\":{\"dklen\":32,\"n\":262144,\"p\":1,\"r\":8,\"salt\":\"39bec0376261a900be31feaa373b7e7f69287a1e6e503bee425645aba84d968a\"},\"mac\":\"5580eab36b5aa97079bb4cb123212639c54c596f9b6dd74f92c43d9fca442409\"},\"address\":\"8a3015660bca082f81e53b2036bea9d41a8f79a8\",\"id\":\"be8adfb5-fd55-4754-a741-42dc7c2408ba\",\"version\":3}"))));
}

void SendCommandTest::testSend()
{
    GethSimulator & geth = _context.getGeth();
    _context.getKeyStore().registerAccount("0x8a3015660bca082f81e53b2036bea9d41a8f79a8", "asdasd123");
    geth.setBalance("0x8a3015660bca082f81e53b2036bea9d41a8f79a8", BigInt("1000000000000000000"));

    QString from = "0x8a3015660bca082f81e53b2036bea9d41a8f79a8";
    QString to = "0x0000000000000000000000000000000000000001";
    QVariantMap request;
    request.insert("from", from);
    request.insert("address", to);
    request.insert("amount", "100000000000000000");
    request.insert("password", "asdasd123");

    QVariant result = _command(request);
    QString txid = result.toString();

    QVERIFY(geth.getBalance("0x0000000000000000000000000000000000000001") == BigInt("100000000000000000"));
    QVERIFY(geth.getBalance("0x8a3015660bca082f81e53b2036bea9d41a8f79a8") == BigInt("900000000000000000"));

}

void SendCommandTest::testSendStealth()
{
    GethSimulator & geth = _context.getGeth();
    geth.setBalance("0x8a3015660bca082f81e53b2036bea9d41a8f79a8", BigInt("1000000000000000000"));

    QString from = "0x8a3015660bca082f81e53b2036bea9d41a8f79a8";
    QString to = "3oTYbZG4ZUsJatou8gmtJatRU19Sn5HXDWnhjRStbMpRsyT4UD4hApbnjuvZThmj1TtTgbbLbUiZ9hrKkjRwcTpV7uxBnEoA1ZsiZCw";
    QVariantMap request;
    request.insert("from", from);
    request.insert("address", to);
    request.insert("amount", "100000000000000000");
    request.insert("password", "asdasd123");

    QVariant result = _command(request);
    QString txid = result.toString();

    QVERIFY(geth.getBalance("0x8a3015660bca082f81e53b2036bea9d41a8f79a8") == BigInt("900000000000000000"));

}

void SendCommandTest::testInvalidRequest()
{
    QVariantMap request;
    QVariant result = _command(request);
    QVERIFY(!result.toBool());

    request.insert("from", "0x8a3015660bca082f81e53b2036bea9d41a8f79a8");
    result =_command(request);
    QVERIFY(!result.toBool());

    request.insert("address", "0x0000000000000000000000000000000000000001");

    result = _command(request);
    QVERIFY(!result.toBool());

    request.insert("amount", "100000000000000000");
    result = _command(request);
    QVERIFY(!result.toBool());
}

void SendCommandTest::testInvalidDestiantion()
{
    QVariantMap request;
    request.insert("from", "0x8a3015660bca082f81e53b2036bea9d41a8f79a8");
    request.insert("address", "0x01");
    request.insert("amount", "100000000000000000");
    request.insert("password", "asdasd123");

    QVariant result = _command(request);
    QVERIFY(!result.toBool());
}


void SendCommandTest::testInvalidSource()
{
    QVariantMap request;
    request.insert("from", "0x0000000000000000000000000000000000000005");
    request.insert("address", "0x0000000000000000000000000000000000000001");
    request.insert("amount", "100000000000000000");
    request.insert("password", "asdasd123");

    QVERIFY_EXCEPTION_THROWN(_command(request), std::runtime_error);
}

void SendCommandTest::testInvalidPassword()
{
    QString from = "0x8a3015660bca082f81e53b2036bea9d41a8f79a8";
    QString to = "0x0000000000000000000000000000000000000001";
    QVariantMap request;
    request.insert("from", from);
    request.insert("address", to);
    request.insert("amount", "100000000000000000");
    request.insert("password", "asdasd");

    QVERIFY_EXCEPTION_THROWN(_command(request), std::runtime_error);
}

void SendCommandTest::testNotEnoughFunds()
{
    QString from = "0x8a3015660bca082f81e53b2036bea9d41a8f79a8";
    QString to = "0x0000000000000000000000000000000000000001";
    QVariantMap request;
    request.insert("from", from);
    request.insert("address", to);
    request.insert("amount", "10000000000000000000000000000");
    request.insert("password", "asdasd123");

    QVERIFY_EXCEPTION_THROWN(_command(request), std::runtime_error);
}

void SendCommandTest::cleanupTestCase()
{}

#endif
