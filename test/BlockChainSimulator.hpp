#pragma once

#include <vector>

#include "ethrpc/Block.hpp"

#include <json/reader.h>


class BlockChainSimulator
{

    public:
        BlockChainSimulator();

        void retrieveBlockDetails(bool);

        void push(const char *);
        void push(const Ethereum::Connector::Block &);

        Ethereum::Connector::Block getBlock(size_t);
        size_t getHeight();

    private:
        std::vector<Ethereum::Connector::Block> _blocks;

};
