#pragma once

#include <vector>
#include <string>

#include "ethrpc/Block.hpp"

#include <json/reader.h>


class BlockChainSimulator
{
    public:
        typedef Ethereum::Connector::Block Block;

    public:
        BlockChainSimulator();

        void retrieveBlockDetails(bool);

        void push(const std::string &);
        void push(const char *);

        Ethereum::Connector::Block getBlock(size_t);
        const char * getBlockData(size_t);
        size_t getHeight();

    private:
        std::vector<Ethereum::Connector::Block> _blocks;
        std::vector<std::string> _data;

};
