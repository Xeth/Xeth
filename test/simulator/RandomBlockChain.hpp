#pragma once

#include <string>
#include <sstream>


#include <json/reader.h>

#include "ethrpc/Block.hpp"

#include "RandomString.hpp"
#include "Hex.hpp"


class RandomBlockChain
{
    public:
        typedef Ethereum::Connector::Block Block;

    public:
        RandomBlockChain();
        RandomBlockChain(size_t maxHeight);

        void retrieveBlockDetails(bool);

        Ethereum::Connector::Block getBlock(size_t);
        Json::Value getBlockData(size_t);

        size_t getHeight();
        size_t getTotalFetched();

        void setHeight(size_t);

    private:
        size_t _height;
        size_t _fetched;
};
