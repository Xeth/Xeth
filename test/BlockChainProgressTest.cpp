#include "BlockChainProgressTest.hpp"

#include <iostream>

std::string BlockChainProgressTest::makeBlock(time_t time)
{
    std::stringstream stream;
    stream<<"0x"<<std::hex<<time;
    std::string timeStr = stream.str();
    std::string block = "{\"number\":\"";
    block += timeStr;
    block += "\", \"hash\":\"blockhash_";
    block += timeStr;
    block += "\", \"miner\":\"testaddress\", \"timestamp\":\"";
    block += timeStr;
    block += "\",\"transactions\":[]}";
    return block;
}

void BlockChainProgressTest::testZeroProgress()
{
    BlockChainSimulator chain;
    Xeth::ChainProgress<BlockChainSimulator> progress(chain);
    chain.push(makeBlock(time(NULL)-108));
    progress.update();
    QCOMPARE(progress.getValue(),0.0);
}

void BlockChainProgressTest::testPartialProgress()
{
    BlockChainSimulator chain;
    Xeth::ChainProgress<BlockChainSimulator> progress(chain);
    chain.push(makeBlock(time(NULL)-48));
    chain.push(makeBlock(time(NULL)-36));
    progress.update();
    QCOMPARE(progress.getValue(), 25.0);
}

void BlockChainProgressTest::testProgressComplete()
{
    BlockChainSimulator chain;
    Xeth::ChainProgress<BlockChainSimulator> progress(chain);

    chain.push(makeBlock(time(NULL)-48));
    chain.push(makeBlock(time(NULL)-36));
    chain.push(makeBlock(time(NULL)-11));
    progress.update();
    QCOMPARE(progress.getValue(), 100.0);
    chain.push(makeBlock(time(NULL)-1));
    progress.update();
    QCOMPARE(progress.getValue(), 100.0);
    chain.push(makeBlock(time(NULL)+20));
    progress.update();
    QCOMPARE(progress.getValue(), 100.0);
}

void BlockChainProgressTest::testProgressUpdate()
{
    BlockChainSimulator chain;
    Xeth::ChainProgress<BlockChainSimulator> progress(chain);
    chain.push(makeBlock(time(NULL)-48));
    chain.push(makeBlock(time(NULL)-36));
    progress.update();
    QCOMPARE(progress.getValue(), 25.0);
    chain.push(makeBlock(time(NULL)-24));
    progress.update();
    QCOMPARE(progress.getValue(), 50.0);
    chain.push(makeBlock(time(NULL)-12));
    progress.update();
    QCOMPARE(progress.getValue(), 75.0);
    chain.push(makeBlock(time(NULL)+5));
    progress.update();
    QCOMPARE(progress.getValue(), 100.0);
}
