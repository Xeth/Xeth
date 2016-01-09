#include "BlockChainSimulator.hpp"



BlockChainSimulator::BlockChainSimulator()
{}



void BlockChainSimulator::push(const char *json)
{
    Json::Value value;
    Json::Reader reader;

    if(!reader.parse(json, json+strlen(json), value))
    {
        throw std::runtime_error("invalid json");
    }

    push(Ethereum::Connector::Block(value));
}



void BlockChainSimulator::push(const Ethereum::Connector::Block &block)
{
    _blocks.push_back(block);
}



size_t BlockChainSimulator::getHeight()
{
    return _blocks.size();
}



Ethereum::Connector::Block BlockChainSimulator::getBlock(size_t number)
{
    if(number > _blocks.size())
    {
        throw std::runtime_error("invalid block offset");
    }

    return _blocks[number];
}