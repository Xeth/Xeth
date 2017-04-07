#pragma once

#include <vector>
#include <string>
#include <json/reader.h>
#include <json/writer.h>

#include "ethrpc/Block.hpp"

#include "types/BigInt.hpp"
#include "RandomString.hpp"
#include "Hex.hpp"


using Xeth::BigInt;


class BlockChainSimulator
{
    public:
        typedef Ethereum::Connector::Block Block;
        typedef Ethereum::Connector::Transaction Transaction;
        typedef Ethereum::Connector::Collection<Transaction> TransactionCollection;

    public:
        BlockChainSimulator();

        void retrieveBlockDetails(bool);

        void push(const std::string &);
        void push(const char *);

        Ethereum::Connector::Block getBlock(size_t) const;
        Json::Value getBlockData(size_t) const;
        size_t getHeight() const;

        void pushMemPool(const char *from, const char *to, const BigInt &amount, const char *data = NULL);
        void pushMemPool(const char *txid, const char *from, const char *to, const BigInt &amount, const char *data = NULL);

        size_t getMemPoolSize() const;

        TransactionCollection getMemPool() const;
        Transaction getTransaction(const char *txid) const;


        void mineBlock(const char *miner);
        void mineBlock();

    private:
        std::vector<Ethereum::Connector::Block> _blocks;
        std::vector<Json::Value> _blocksData;
        Json::Value _mempool;
        mutable std::map<std::string, Json::Value> _transactionsMap;
};
