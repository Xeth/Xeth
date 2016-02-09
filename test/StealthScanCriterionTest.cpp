#include "StealthScanCriterionTest.hpp"

Xeth::StealthKey StealthScanCriterionTest::makeKey()
{
    Xeth::CipherFactory cipherFactory;
    Ethereum::Stealth::KeyGenerator generator;
    return generator.generate(cipherFactory.create(), "asdasd123");
}

void StealthScanCriterionTest::testReceivedTransaction()
{

    Xeth::ScanResult result;
    Ethereum::PublicKeySerializer pubSerializer;

    Xeth::StealthKey key = makeKey();

    Ethereum::Stealth::Address address(key);
    Ethereum::Stealth::PaymentAddressBuilder builder(address);
    Ethereum::Stealth::PaymentAddress paymentAddr = builder.build();


    Xeth::StealthScanCriterion criterion(key);
    criterion.processTransaction(
        "somehash",
        "senderaddress",
        paymentAddr.getAddresses()[0].toString(),
        Xeth::BigInt(10001),
        pubSerializer.serialize(paymentAddr.getEphemPublicKey()),
        1001,
        result
    );

    QVERIFY(result.transactions.size()==1);

    QJsonObject transaction = result.transactions.begin()->toObject();
    QVERIFY(transaction["to"].toString() == paymentAddr.getAddresses()[0].toString().c_str());
    QVERIFY(transaction["from"].toString() == "senderaddress");
    QVERIFY(transaction["amount"].toString() == boost::lexical_cast<std::string>(Xeth::BigInt(10001)).c_str());
    QVERIFY(transaction["category"].toString() == Xeth::TransactionCategory::ToString(Xeth::TransactionCategory::Stealth));
    QVERIFY(transaction["timestamp"].toInt() == 1001);
}



void StealthScanCriterionTest::testUnknownTransaction()
{
    Xeth::ScanResult result;
    Xeth::StealthKey key = makeKey();
    Xeth::StealthScanCriterion criterion(key);
    criterion.processTransaction("somehash", "senderaddress", "receiveraddress", Xeth::BigInt(10003), "", 1003, result);
    QVERIFY(result.transactions.size()==0);
}
