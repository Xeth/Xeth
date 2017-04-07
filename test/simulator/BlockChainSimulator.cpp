#include "BlockChainSimulator.hpp"


BlockChainSimulator::BlockChainSimulator()
{}


void BlockChainSimulator::retrieveBlockDetails(bool)
{}

void BlockChainSimulator::push(const std::string &block)
{
    push(block.c_str());
}

void BlockChainSimulator::push(const char *json)
{
    Json::Value block;
    Json::Reader reader;

    if(!reader.parse(json, json+strlen(json), block))
    {
        throw std::runtime_error("invalid json");
    }

    Json::Value transactions = block["transactions"];
    Json::Value hashes = Json::arrayValue;
    for(Json::ValueIterator it = transactions.begin(), end = transactions.end(); it!=end; ++it)
    {
        Json::Value tx = *it;
        std::string hash = tx["hash"].asString();
        hashes.append(hash);
        _transactionsMap[hash] = tx;
    }

    block["transactions"] = hashes;

    _blocks.push_back(Ethereum::Connector::Block(block));
    _blocksData.push_back(block);

}

BlockChainSimulator::Transaction BlockChainSimulator::getTransaction(const char *txid) const
{
    return Transaction(_transactionsMap[txid]);
}


void BlockChainSimulator::pushMemPool(const char *from, const char *to, const BigInt &amount, const char *data)
{
    pushMemPool(RandomHexString().c_str(), from, to, amount, data);
}

void BlockChainSimulator::pushMemPool(const char *txid, const char *from, const char *to, const BigInt &amount, const char *data)
{
    Json::Value tx;
    tx["hash"] = txid;
    tx["from"] = from;
    tx["to"] = to;
    tx["value"] = Hex(amount);
    tx["input"] = data ? data : "";
    tx["time"] = Hex(time(NULL));
    _mempool.append(tx);
    _transactionsMap[txid] = tx;
}


void BlockChainSimulator::mineBlock(const char *miner)
{
    Json::FastWriter writer;
    Json::Value block;
    block["number"] = Hex(_blocks.size());
    block["hash"] = RandomHexString(65);
    block["miner"] = miner;
    block["timestamp"] = Hex(time(NULL));
    block["transactions"] = _mempool;
    _blocks.push_back(Block(block));
    _blocksData.push_back(block);
    _mempool.clear();
}


BlockChainSimulator::TransactionCollection BlockChainSimulator::getMemPool() const
{
    return TransactionCollection(_mempool);
}


void BlockChainSimulator::mineBlock()
{
    mineBlock(RandomHexString().c_str());
}


size_t BlockChainSimulator::getHeight() const
{
    size_t size = _blocks.size();
    return size? size -1: 0;
}

Json::Value BlockChainSimulator::getBlockData(size_t number) const
{
    if(number > _blocksData.size())
    {
        throw std::runtime_error("invalid block offset");
    }

    return _blocksData[number];
}


Ethereum::Connector::Block BlockChainSimulator::getBlock(size_t number) const
{
    if(number > _blocks.size())
    {
        throw std::runtime_error("invalid block offset");
    }

    return _blocks[number];
}
