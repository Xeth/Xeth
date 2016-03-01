#include "StealthPaymentTest.hpp"

#if __GETH_SIMULATOR_ENABLED__

StealthPaymentTest::StealthPaymentTest() :
    _context(true),
    _command(_context.getProvider(), _context.getDataBase())
{}


void StealthPaymentTest::initTestCase()
{
    generateStealthKey();
    generateEthereumKey();
}

void StealthPaymentTest::generateStealthKey()
{
    generateKey<Ethereum::Stealth::KeyGenerator>(_context.getDataBase().getStealthKeys());
}

void StealthPaymentTest::generateEthereumKey()
{
    generateKey<Ethereum::KeyGenerator>(_context.getDataBase().getEthereumKeys());
}


template<class Generator, class Store>
void StealthPaymentTest::generateKey(Store &store)
{
    Generator generator;
    Xeth::CipherFactory cipherFactory;
    registerKey(generator.generate(cipherFactory.create(), "asdasd123"), store);
}

template<class Key, class Store>
void StealthPaymentTest::registerKey(const Key &key, Store &store)
{
    store.insert(key);
    _context.getSynchronizer().watch(key, 0);
}

void StealthPaymentTest::testSend()
{
    GethSimulator & geth = _context.getGeth();
    Xeth::EthereumKey ethKey = *_context.getDataBase().getEthereumKeys().begin();
    Xeth::StealthKey stealthKey = *_context.getDataBase().getStealthKeys().begin();

    std::string from = ethKey.getAddress().toString();
    std::string to = Ethereum::Stealth::Address(stealthKey).toString();
    BigInt amount = BigInt("10000000000000");
    geth.setBalance(from.c_str(), BigInt("10000000000000000"));

    QVariantMap request;
    request.insert("from", from.c_str());
    request.insert("to", to.c_str());
    request.insert("amount", amount.str().c_str());
    request.insert("password", "asdasd123");

    QVariant result = _command(request);

    std::string txid = result.toString().toStdString();

    TransactionCollection transactions = _context.getBlockChain().getMemPool();

    QVERIFY(transactions.size()==1);
    Transaction tx = *transactions.begin();
    QCOMPARE(tx.getSender(), from);
    QCOMPARE(tx.getAmount(), amount);
    QVERIFY(tx.getInput().size());
    QVERIFY(tx.getHash() == txid.c_str());
}


void StealthPaymentTest::testSpend()
{
    Transaction tx = *_context.getBlockChain().getMemPool().begin();
    _context.getBlockChain().mineBlock(); //to confirm previous stealth transaction
    _context.getSynchronizer().scan();
    GethSimulator & geth = _context.getGeth();
    Xeth::SendToAddressCommand command(_context.getProvider(), _context.getDataBase());

    QString from = tx.getReceiver().c_str();
    QString to = "0x0000000000000000000000000000000000000000";
    BigInt amount = BigInt("100000000000");

    QVariantMap request;
    request["from"] = from;
    request["to"] = to;
    request["amount"] = amount.str().c_str();
    request["password"] = "asdasd123";

    QVariant result = command(request);

    QString txid = result.toString();

    QVERIFY(geth.getBalance("0x0000000000000000000000000000000000000000") == BigInt("100000000000"));

    QJsonObject transaction = _context.getDataBase().getTransactions().get(txid.toStdString().c_str());
    QCOMPARE(transaction["hash"].toString(), txid);
    QCOMPARE(transaction["from"].toString(), from);
    QCOMPARE(transaction["to"].toString(), to);
    QCOMPARE(transaction["amount"].toString(), QString(amount.str().c_str()));

}


void StealthPaymentTest::testInvalidRequest()
{
    QVariantMap request;
    QVariant result = _command(request);
    QVERIFY(!result.toBool());
}


void StealthPaymentTest::testInvalidDestiantion()
{
    GethSimulator & geth = _context.getGeth();
    Xeth::EthereumKey ethKey = *_context.getDataBase().getEthereumKeys().begin();
    std::string from = ethKey.getAddress().toString();
    std::string to = "123123123123123123123123123123123123123123123123123123";
    BigInt amount = BigInt("10000000000000");
    geth.setBalance(from.c_str(), BigInt("10000000000000000"));

    QVariantMap request;
    request.insert("from", from.c_str());
    request.insert("to", to.c_str());
    request.insert("amount", amount.str().c_str());
    request.insert("password", "asdasd123");

    QVariant result = _command(request);
    QVERIFY(!result.toBool());
}


void StealthPaymentTest::testInvalidSource()
{
    Xeth::StealthKey stealthKey = *_context.getDataBase().getStealthKeys().begin();

    std::string from = "0x0000000";
    std::string to = Ethereum::Stealth::Address(stealthKey).toString();
    BigInt amount = BigInt("10000000000000");

    QVariantMap request;
    request.insert("from", from.c_str());
    request.insert("to", to.c_str());
    request.insert("amount", amount.str().c_str());
    request.insert("password", "asdasd123");

    QVariant result = _command(request);
    QVERIFY(!result.toBool());
}


void StealthPaymentTest::testNotEnoughFunds()
{
    Xeth::EthereumKey ethKey = *_context.getDataBase().getEthereumKeys().begin();
    Xeth::StealthKey stealthKey = *_context.getDataBase().getStealthKeys().begin();

    std::string from = ethKey.getAddress().toString();
    std::string to = Ethereum::Stealth::Address(stealthKey).toString();
    BigInt amount = BigInt("100000000000000000000000000000000");

    QVariantMap request;
    request.insert("from", from.c_str());
    request.insert("to", to.c_str());
    request.insert("amount", amount.str().c_str());
    request.insert("password", "asdasd123");

    QVariant result = _command(request);

}


void StealthPaymentTest::testInvalidPassword()
{
    GethSimulator & geth = _context.getGeth();
    Xeth::EthereumKey ethKey = *_context.getDataBase().getEthereumKeys().begin();
    Xeth::StealthKey stealthKey = *_context.getDataBase().getStealthKeys().begin();

    std::string from = ethKey.getAddress().toString();
    std::string to = Ethereum::Stealth::Address(stealthKey).toString();
    BigInt amount = BigInt("10000000000000");
    geth.setBalance(from.c_str(), BigInt("10000000000000000"));

    QVariantMap request;
    request.insert("from", from.c_str());
    request.insert("to", to.c_str());
    request.insert("amount", amount.str().c_str());
    request.insert("password", "asd");

    QVariant result = _command(request);
    QVERIFY(!result.toBool());
}


void StealthPaymentTest::cleanupTestCase()
{
    _context.getGeth().stop();
}

#endif
