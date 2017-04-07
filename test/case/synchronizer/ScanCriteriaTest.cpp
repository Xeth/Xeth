#include "ScanCriteriaTest.hpp"
#include <QSignalSpy>

void ScanCriteriaTest::testScan()
{

    BlockChainSimulator blockchain;

    blockchain.push("{"
        "\"number\":\"1\", "
        "\"hash\":\"blockhash\", "
        "\"miner\":\"0xffff\", "
        "\"timestamp\":\"123\","
         "\"transactions\":[]"
        "}");

    blockchain.push("{"
        "\"number\":\"2\", "
        "\"hash\":\"blockhash2\", "
        "\"miner\":\"someaddress\", "
        "\"timestamp\":\"124\","
         "\"transactions\":[]"
        "}");

    blockchain.push("{"
        "\"number\":\"3\", "
        "\"hash\":\"blockhash3\", "
        "\"miner\":\"someaddress2\", "
        "\"timestamp\":\"125\","
         "\"transactions\":["
                "{"
                    "\"hash\":\"txhash1\","
                    "\"from\":\"0xffff\","
                    "\"to\":\"somereceiver1\","
                    "\"value\":\"1000000\","
                    "\"input\":\"\""
                 "},"
                "{"
                    "\"hash\":\"txhash2\","
                    "\"from\":\"somesender2\","
                    "\"to\":\"somereceiver\","
                    "\"value\":\"1000000\","
                    "\"input\":\"\""
                 "},"
                "{"
                    "\"hash\":\"txhash3\","
                    "\"from\":\"somesender3\","
                    "\"to\":\"0xffff2\","
                    "\"value\":\"1000000\","
                    "\"input\":\"\""
                 "}"
          "]"
        "}");


    blockchain.push("{"
        "\"number\":\"4\", "
        "\"hash\":\"blockhash4\", "
        "\"miner\":\"someaddress\", "
        "\"timestamp\":\"124\","
         "\"transactions\":[]"
        "}");

    blockchain.push("{"
        "\"number\":\"5\", "
        "\"hash\":\"blockhash\", "
        "\"miner\":\"someaddress2\", "
        "\"timestamp\":\"125\","
         "\"transactions\":["
                "{"
                    "\"hash\":\"txhash4\","
                    "\"from\":\"somesender\","
                    "\"to\":\"somereceiver\","
                    "\"value\":\"1000000\","
                    "\"input\":\"\""
                 "},"
                "{"
                    "\"hash\":\"txhash5\","
                    "\"from\":\"somesender\","
                    "\"to\":\"0xffff\","
                    "\"value\":\"1000000\","
                    "\"input\":\"\""
                 "}"
          "]"
        "}");
    Xeth::ScanCriteria criteria;
    QSignalSpy spy(&criteria, SIGNAL(Data(const Xeth::PartialScanResult &)));
    criteria.addCriterion<Xeth::AccountScanCriterion>(0, "0xffff");
    criteria.addCriterion<Xeth::AccountScanCriterion>(0, "0xffff2");
    criteria.setLimit(100);

    Xeth::ScanResult result;
    Xeth::DummyScanProgress progress;

    criteria.parse(blockchain, result, progress);

    QVERIFY(result.transactions.size()==4);
    QVERIFY(spy.size() == 3);
}

void ScanCriteriaTest::testEmptyResultScan()
{
    BlockChainSimulator blockchain;

    blockchain.push("{"
        "\"number\":\"1\", "
        "\"hash\":\"blockhash\", "
        "\"miner\":\"0xffff3\", "
        "\"timestamp\":\"123\","
         "\"transactions\":[]"
        "}");

    blockchain.push("{"
        "\"number\":\"2\", "
        "\"hash\":\"blockhash2\", "
        "\"miner\":\"someaddress\", "
        "\"timestamp\":\"124\","
         "\"transactions\":[]"
        "}");

    Xeth::ScanCriteria criteria;
    QSignalSpy spy(&criteria, SIGNAL(Data(const Xeth::PartialScanResult &)));
    criteria.addCriterion<Xeth::AccountScanCriterion>(0, "0xffff");
    criteria.addCriterion<Xeth::AccountScanCriterion>(0, "0xffff2");
    criteria.setLimit(100);

    Xeth::ScanResult result;
    Xeth::DummyScanProgress progress;

    criteria.parse(blockchain, result, progress);

    QVERIFY(result.transactions.size()==0);
    QVERIFY(spy.size()==0);
}

void ScanCriteriaTest::testEmptyChainScan()
{
    BlockChainSimulator blockchain;
    blockchain.push("{"
        "\"number\":\"1\", "
        "\"hash\":\"blockhash\", "
        "\"miner\":\"nominer\", "
        "\"timestamp\":\"123\","
         "\"transactions\":[]"
    "}"); //genesis only
    Xeth::ScanCriteria criteria;
    QSignalSpy spy(&criteria, SIGNAL(Data(const Xeth::PartialScanResult &)));
    criteria.addCriterion<Xeth::AccountScanCriterion>(0, "0xffff");
    criteria.addCriterion<Xeth::AccountScanCriterion>(0, "0xffff2");
    criteria.setLimit(100);

    Xeth::ScanResult result;
    Xeth::DummyScanProgress progress;

    criteria.parse(blockchain, result, progress);

    QVERIFY(result.transactions.size()==0);
    QVERIFY(spy.size()==0);
}

void ScanCriteriaTest::testRandomOffsetScan()
{
    BlockChainSimulator blockchain;

    blockchain.push("{"
        "\"number\":\"1\", "
        "\"hash\":\"blockhash\", "
        "\"miner\":\"0xffff\", "
        "\"timestamp\":\"123\","
         "\"transactions\":[]"
        "}");

    blockchain.push("{"
        "\"number\":\"2\", "
        "\"hash\":\"blockhash2\", "
        "\"miner\":\"someaddress\", "
        "\"timestamp\":\"124\","
         "\"transactions\":[]"
        "}");

    blockchain.push("{"
        "\"number\":\"3\", "
        "\"hash\":\"blockhash3\", "
        "\"miner\":\"someaddress2\", "
        "\"timestamp\":\"125\","
         "\"transactions\":["
                "{"
                    "\"hash\":\"txhash1\","
                    "\"from\":\"0xffff\","
                    "\"to\":\"somereceiver1\","
                    "\"value\":\"1000000\","
                    "\"input\":\"\""
                 "},"
                "{"
                    "\"hash\":\"txhash2\","
                    "\"from\":\"somesender2\","
                    "\"to\":\"somereceiver\","
                    "\"value\":\"1000000\","
                    "\"input\":\"\""
                 "},"
                "{"
                    "\"hash\":\"txhash3\","
                    "\"from\":\"somesender3\","
                    "\"to\":\"0xffff2\","
                    "\"value\":\"1000000\","
                    "\"input\":\"\""
                 "}"
          "]"
        "}");


    blockchain.push("{"
        "\"number\":\"4\", "
        "\"hash\":\"blockhash4\", "
        "\"miner\":\"someaddress\", "
        "\"timestamp\":\"124\","
         "\"transactions\":[]"
        "}");

    blockchain.push("{"
        "\"number\":\"5\", "
        "\"hash\":\"blockhash\", "
        "\"miner\":\"someaddress2\", "
        "\"timestamp\":\"125\","
         "\"transactions\":["
                "{"
                    "\"hash\":\"txhash4\","
                    "\"from\":\"somesender\","
                    "\"to\":\"somereceiver\","
                    "\"value\":\"1000000\","
                    "\"input\":\"\""
                 "},"
                "{"
                    "\"hash\":\"txhash5\","
                    "\"from\":\"somesender\","
                    "\"to\":\"0xffff\","
                    "\"value\":\"1000000\","
                    "\"input\":\"\""
                 "}"
          "]"
        "}");
    Xeth::ScanCriteria criteria;
    QSignalSpy spy(&criteria, &Xeth::ScanCriteria::Data);
    criteria.addCriterion<Xeth::AccountScanCriterion>(1, "0xffff");
    criteria.addCriterion<Xeth::AccountScanCriterion>(0, "0xffff2");
    criteria.setLimit(100);

    Xeth::ScanResult result;
    Xeth::DummyScanProgress progress;

    criteria.parse(blockchain, result, progress);

    QVERIFY(result.transactions.size()==3);
    QVERIFY(spy.size() == 2);
}

void ScanCriteriaTest::testConsecutiveScan()
{
    BlockChainSimulator blockchain;

    blockchain.push("{"
        "\"number\":\"1\", "
        "\"hash\":\"blockhash\", "
        "\"miner\":\"0xffff\", "
        "\"timestamp\":\"123\","
         "\"transactions\":[]"
        "}");

    blockchain.push("{"
        "\"number\":\"2\", "
        "\"hash\":\"blockhash2\", "
        "\"miner\":\"someaddress\", "
        "\"timestamp\":\"124\","
         "\"transactions\":[]"
        "}");

    blockchain.push("{"
        "\"number\":\"3\", "
        "\"hash\":\"blockhash3\", "
        "\"miner\":\"someaddress2\", "
        "\"timestamp\":\"125\","
         "\"transactions\":["
                "{"
                    "\"hash\":\"txhash1\","
                    "\"from\":\"0xffff\","
                    "\"to\":\"somereceiver1\","
                    "\"value\":\"1000000\","
                    "\"input\":\"\""
                 "},"
                "{"
                    "\"hash\":\"txhash2\","
                    "\"from\":\"somesender2\","
                    "\"to\":\"somereceiver\","
                    "\"value\":\"1000000\","
                    "\"input\":\"\""
                 "},"
                "{"
                    "\"hash\":\"txhash3\","
                    "\"from\":\"somesender3\","
                    "\"to\":\"0xffff2\","
                    "\"value\":\"1000000\","
                    "\"input\":\"\""
                 "}"
          "]"
        "}");


    blockchain.push("{"
        "\"number\":\"4\", "
        "\"hash\":\"blockhash4\", "
        "\"miner\":\"someaddress\", "
        "\"timestamp\":\"124\","
         "\"transactions\":[]"
        "}");

    blockchain.push("{"
        "\"number\":\"5\", "
        "\"hash\":\"blockhash\", "
        "\"miner\":\"someaddress2\", "
        "\"timestamp\":\"125\","
         "\"transactions\":["
                "{"
                    "\"hash\":\"txhash4\","
                    "\"from\":\"somesender\","
                    "\"to\":\"somereceiver\","
                    "\"value\":\"1000000\","
                    "\"input\":\"\""
                 "},"
                "{"
                    "\"hash\":\"txhash5\","
                    "\"from\":\"somesender\","
                    "\"to\":\"0xffff\","
                    "\"value\":\"1000000\","
                    "\"input\":\"\""
                 "}"
          "]"
        "}");
    Xeth::ScanCriteria criteria;
    QSignalSpy spy(&criteria, &Xeth::ScanCriteria::Data);
    criteria.addCriterion<Xeth::AccountScanCriterion>(1, "0xffff");
    criteria.addCriterion<Xeth::AccountScanCriterion>(0, "0xffff2");
    criteria.setLimit(100);

    Xeth::ScanResult result;
    Xeth::DummyScanProgress progress;

    criteria.parse(blockchain, result, progress);

    QVERIFY(result.transactions.size()==3);

    blockchain.push("{"
        "\"number\":\"6\", "
        "\"hash\":\"blockhash\", "
        "\"miner\":\"someaddress2\", "
        "\"timestamp\":\"125\","
         "\"transactions\":["
                "{"
                    "\"hash\":\"txhash4\","
                    "\"from\":\"somesender\","
                    "\"to\":\"somereceiver\","
                    "\"value\":\"1000000\","
                    "\"input\":\"\""
                 "},"
                "{"
                    "\"hash\":\"txhash5\","
                    "\"from\":\"somesender\","
                    "\"to\":\"0xffff2\","
                    "\"value\":\"1000000\","
                    "\"input\":\"\""
                 "}"
          "]"
        "}");
    blockchain.push("{"
        "\"number\":\"7\", "
        "\"hash\":\"blockhash4\", "
        "\"miner\":\"someaddress\", "
        "\"timestamp\":\"124\","
         "\"transactions\":[]"
        "}");
    blockchain.push("{"
        "\"number\":\"8\", "
        "\"hash\":\"blockhash\", "
        "\"miner\":\"someaddress2\", "
        "\"timestamp\":\"125\","
         "\"transactions\":["
                "{"
                    "\"hash\":\"txhash4\","
                    "\"from\":\"somesender\","
                    "\"to\":\"somereceiver\","
                    "\"value\":\"1000000\","
                    "\"input\":\"\""
                 "},"
                "{"
                    "\"hash\":\"txhash5\","
                    "\"from\":\"somesender\","
                    "\"to\":\"0xffff\","
                    "\"value\":\"1000000\","
                    "\"input\":\"\""
                 "}"
          "]"
        "}");
    blockchain.push("{"
        "\"number\":\"9\", "
        "\"hash\":\"blockhash4\", "
        "\"miner\":\"someaddress321\", "
        "\"timestamp\":\"124\","
         "\"transactions\":[]"
        "}");

    criteria.parse(blockchain, result, progress);
    QVERIFY(result.transactions.size()==5);
    QVERIFY(spy.size() == 4);
}
