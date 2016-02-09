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
    Json::Value value;
    Json::Reader reader;

    if(!reader.parse(json, json+strlen(json), value))
    {
        throw std::runtime_error("invalid json");
    }

    _blocks.push_back(Ethereum::Connector::Block(value));
    
    _data.push_back(json);
}




size_t BlockChainSimulator::getHeight()
{
    size_t size = _blocks.size();
    return size? size -1: 0;
}

const char * BlockChainSimulator::getBlockData(size_t number)
{
    if(number > _data.size())
    {
        throw std::runtime_error("invalid block offset");
    }

    return _data[number].c_str();
}


Ethereum::Connector::Block BlockChainSimulator::getBlock(size_t number)
{
    if(number > _blocks.size())
    {
        throw std::runtime_error("invalid block offset");
    }

    return _blocks[number];
}
