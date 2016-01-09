#pragma once

#include <vector>

#include <eth-connector/Block.hpp>

#include <json/reader.h>


class BlockChainSimulator
{

    public:
        BlockChainSimulator();


        void push(const char *);
        void push(const Ethereum::Connector::Block &);

        Ethereum::Connector::Block getBlock(size_t);
        size_t getHeight();

    private:
        std::vector<Ethereum::Connector::Block> _blocks;

};
