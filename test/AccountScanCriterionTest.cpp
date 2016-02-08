#include "AccountScanCriterionTest.hpp"


AccountScanCriterionTest::AccountScanCriterionTest() :
    _criterion("testaddress")
{}

void AccountScanCriterionTest::testMinedTransaction()
{
    Xeth::ScanResult result;

    _criterion.processHeader(1, "blockhash", "testaddress", Xeth::BigInt("10000"), 1000, result);

    QVERIFY(result.transactions.size()==1);

    QJsonObject transaction = result.transactions.begin()->toObject();


    QVERIFY(transaction["to"].toString() == "testaddress");
    QVERIFY(transaction["from"].isNull());
    QVERIFY(transaction["amount"].toString() == boost::lexical_cast<std::string>(Xeth::BigInt("10000")).c_str());
    QVERIFY(transaction["category"].toString() == Xeth::TransactionCategory::ToString(Xeth::TransactionCategory::Mined));
    QVERIFY(transaction["timestamp"].toInt() == 1000);
}

void AccountScanCriterionTest::testReceivedTransaction()
{
    Xeth::ScanResult result;

    _criterion.processTransaction("somehash", "senderaddress", "testaddress", Xeth::BigInt(10001), "", 1001, result);

    QVERIFY(result.transactions.size()==1);

    QJsonObject transaction = result.transactions.begin()->toObject();


    QVERIFY(transaction["to"].toString() == "testaddress");
    QVERIFY(transaction["from"].toString() == "senderaddress");
    QVERIFY(transaction["amount"].toString() == boost::lexical_cast<std::string>(Xeth::BigInt(10001)).c_str());
    QVERIFY(transaction["category"].toString() == Xeth::TransactionCategory::ToString(Xeth::TransactionCategory::Received));
    QVERIFY(transaction["timestamp"].toInt() == 1001);
}

void AccountScanCriterionTest::testSentTransaction()
{
    Xeth::ScanResult result;

    _criterion.processTransaction("somehash", "testaddress", "receiveraddress", Xeth::BigInt(10002), "", 1002, result);

    QVERIFY(result.transactions.size()==1);

    QJsonObject transaction = result.transactions.begin()->toObject();


    QVERIFY(transaction["to"].toString() == "receiveraddress");
    QVERIFY(transaction["from"].toString() == "testaddress");
    QVERIFY(transaction["amount"].toString() == boost::lexical_cast<std::string>(Xeth::BigInt(10002)).c_str());
    QVERIFY(transaction["category"].toString() == Xeth::TransactionCategory::ToString(Xeth::TransactionCategory::Sent));
    QVERIFY(transaction["timestamp"].toInt() == 1002);
}

void AccountScanCriterionTest::testUnknownTransaction()
{
    Xeth::ScanResult result;

    _criterion.processTransaction("somehash", "senderaddress", "receiveraddress", Xeth::BigInt(10003), "", 1003, result);

    QVERIFY(result.transactions.size()==0);
}
