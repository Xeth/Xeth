#include "SendToAddressTest.hpp"


SendToAddressTest::SendToAddressTest() :
    _command(_context.getProvider(), _context.getDataBase())
{}


void SendToAddressTest::testSend()
{
    GethSimulator & geth = _context.getGeth();
    _context.getKeyStore().registerAccount("0x0000000000000000000000000000000000000000", "asdasd123");
    geth.setBalance("0x0000000000000000000000000000000000000000", BigInt("1000000000000000000"));

    QString from = "0x0000000000000000000000000000000000000000";
    QString to = "0x0000000000000000000000000000000000000001";
    QVariantMap request;
    request.insert("from", from);
    request.insert("to", to);
    request.insert("amount", "100000000000000000");
    request.insert("password", "asdasd123");

    QVariant result = _command(request);
    QString txid = result.toString();

    QVERIFY(geth.getBalance("0x0000000000000000000000000000000000000001") == BigInt("100000000000000000"));
    QVERIFY(geth.getBalance("0x0000000000000000000000000000000000000000") == BigInt("900000000000000000"));

    QJsonObject transaction = _context.getDataBase().getTransactions().get(txid.toStdString().c_str());
    QCOMPARE(transaction["hash"].toString(), txid);
    QCOMPARE(transaction["from"].toString(), from);
    QCOMPARE(transaction["to"].toString(), to);
    QCOMPARE(transaction["amount"].toString(), QString("100000000000000000"));
}


void SendToAddressTest::testInvalidRequest()
{
    QVariantMap request;
    QVariant result = _command(request);
    QVERIFY(!result.toBool());
    request.insert("from", "0x0000000000000000000000000000000000000000");
    result = _command(request);
    QVERIFY(!result.toBool());
    request.insert("to", "0x0000000000000000000000000000000000000001");
    result = _command(request);
    QVERIFY(!result.toBool());
    request.insert("amount", "100000000000000000");
    result = _command(request);
    QVERIFY(!result.toBool());
}

void SendToAddressTest::testInvalidDestiantion()
{
    QVariantMap request;
    request.insert("from", "0x0000000000000000000000000000000000000000");
    request.insert("to", "0x01");
    request.insert("amount", "100000000000000000");
    request.insert("password", "asdasd123");

    QVariant result = _command(request);
    QVERIFY(!result.toBool());
}


void SendToAddressTest::testInvalidSource()
{
    QVariantMap request;
    request.insert("from", "0x0000000000000000000000000000000000000005");
    request.insert("to", "0x0000000000000000000000000000000000000001");
    request.insert("amount", "100000000000000000");
    request.insert("password", "asdasd123");

    QVariant result = _command(request);
    QVERIFY(!result.toBool());
}

void SendToAddressTest::testInvalidPassword()
{
    QString from = "0x0000000000000000000000000000000000000000";
    QString to = "0x0000000000000000000000000000000000000001";
    QVariantMap request;
    request.insert("from", from);
    request.insert("to", to);
    request.insert("amount", "100000000000000000");
    request.insert("password", "asdasd");

    QVariant result = _command(request);
    QVERIFY(!result.toBool());
}

void SendToAddressTest::testNotEnoughFunds()
{
    QString from = "0x0000000000000000000000000000000000000000";
    QString to = "0x0000000000000000000000000000000000000001";
    QVariantMap request;
    request.insert("from", from);
    request.insert("to", to);
    request.insert("amount", "10000000000000000000000000000");
    request.insert("password", "asdasd123");

    QVariant result = _command(request);
    QVERIFY(!result.toBool());
}

void SendToAddressTest::cleanupTestCase()
{
    _context.getGeth().stop();
}
