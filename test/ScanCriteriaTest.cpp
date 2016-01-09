#include "ScanCriteriaTest.hpp"

void ScanCriteriaTest::testScan()
{
    BlockChainSimulator blockchain;

    blockchain.push("{"
        "\"number\":\"1\", "
        "\"hash\":\"blockhash\", "
        "\"miner\":\"testaddress\", "
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
                    "\"from\":\"testaddress\","
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
                    "\"to\":\"testaddress2\","
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
                    "\"to\":\"testaddress\","
                    "\"value\":\"1000000\","
                    "\"input\":\"\""
                 "}"
          "]"
        "}");
    Xeth::ScanCriteria criteria;
    criteria.addCriterion<Xeth::AccountScanCriterion>(0, "testaddress");
    criteria.addCriterion<Xeth::AccountScanCriterion>(0, "testaddress2");

    QJsonArray result;
    Xeth::DummyScanProgress progress;

    criteria.process(blockchain, result, progress);

    QVERIFY(result.size()==4);
}

void ScanCriteriaTest::testEmptyResultScan()
{
    BlockChainSimulator blockchain;

    blockchain.push("{"
        "\"number\":\"1\", "
        "\"hash\":\"blockhash\", "
        "\"miner\":\"testaddress3\", "
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
    criteria.addCriterion<Xeth::AccountScanCriterion>(0, "testaddress");
    criteria.addCriterion<Xeth::AccountScanCriterion>(0, "testaddress2");

    QJsonArray result;
    Xeth::DummyScanProgress progress;

    criteria.process(blockchain, result, progress);

    QVERIFY(result.size()==0);
}

void ScanCriteriaTest::testEmptyChainScan()
{
    BlockChainSimulator blockchain;

    Xeth::ScanCriteria criteria;
    criteria.addCriterion<Xeth::AccountScanCriterion>(0, "testaddress");
    criteria.addCriterion<Xeth::AccountScanCriterion>(0, "testaddress2");

    QJsonArray result;
    Xeth::DummyScanProgress progress;

    criteria.process(blockchain, result, progress);

    QVERIFY(result.size()==0);
}

void ScanCriteriaTest::testRandomOffsetScan()
{
    BlockChainSimulator blockchain;

    blockchain.push("{"
        "\"number\":\"1\", "
        "\"hash\":\"blockhash\", "
        "\"miner\":\"testaddress\", "
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
                    "\"from\":\"testaddress\","
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
                    "\"to\":\"testaddress2\","
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
                    "\"to\":\"testaddress\","
                    "\"value\":\"1000000\","
                    "\"input\":\"\""
                 "}"
          "]"
        "}");
    Xeth::ScanCriteria criteria;
    criteria.addCriterion<Xeth::AccountScanCriterion>(1, "testaddress");
    criteria.addCriterion<Xeth::AccountScanCriterion>(0, "testaddress2");

    QJsonArray result;
    Xeth::DummyScanProgress progress;

    criteria.process(blockchain, result, progress);

    QVERIFY(result.size()==3);
}

void ScanCriteriaTest::testConsecutiveScan()
{
    BlockChainSimulator blockchain;

    blockchain.push("{"
        "\"number\":\"1\", "
        "\"hash\":\"blockhash\", "
        "\"miner\":\"testaddress\", "
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
                    "\"from\":\"testaddress\","
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
                    "\"to\":\"testaddress2\","
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
                    "\"to\":\"testaddress\","
                    "\"value\":\"1000000\","
                    "\"input\":\"\""
                 "}"
          "]"
        "}");
    Xeth::ScanCriteria criteria;
    criteria.addCriterion<Xeth::AccountScanCriterion>(1, "testaddress");
    criteria.addCriterion<Xeth::AccountScanCriterion>(0, "testaddress2");

    QJsonArray result;
    Xeth::DummyScanProgress progress;

    criteria.process(blockchain, result, progress);

    QVERIFY(result.size()==3);

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
                    "\"to\":\"testaddress2\","
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
                    "\"to\":\"testaddress\","
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

    criteria.process(blockchain, result, progress);
    QVERIFY(result.size()==5);
}
