#include "RandomBlockChain.hpp"



RandomBlockChain::RandomBlockChain(size_t size) :
    _height(size),
    _fetched(0),
    _alphabet("0123456789abcdef"),
    _dist(0, _alphabet.size() - 1)
{}


void RandomBlockChain::retrieveBlockDetails(bool)
{}


size_t RandomBlockChain::getHeight()
{
    return _height;
}


std::string RandomBlockChain::randomString(size_t size) const
{
    boost::random::random_device rng;
    std::string result;
    result.resize(size);

    for(int i = 0; i < size; ++i)
    {
        result[i] = _alphabet[_dist(rng)];
    }

    return result;
}

std::string RandomBlockChain::getHex(size_t number) const
{
    std::stringstream stream;
    stream<<"0x"<<std::hex<<number;
    return stream.str();
}

size_t RandomBlockChain::getTotalFetched()
{
    return _fetched;
}

Ethereum::Connector::Block RandomBlockChain::getBlock(size_t number)
{
    if(number > _height)
    {
        throw std::runtime_error("invalid block offset");
    }

    _fetched ++;

    std::string data = "{\"number\":\"";
    data += getHex(number);
    data += "\", \"hash\":\"0x";
    data += randomString(65);
    data += "\", \"miner\":\"";
    data += randomString(65);
    data += "\", \"timestamp\":\"";
    data += getHex(time(NULL) - (_height - number)*12);
    data += "\",\"transactions\":[]}";

    Json::Value json;
    Json::Reader reader;
    reader.parse(data, json);

    return Ethereum::Connector::Block(json);
}
