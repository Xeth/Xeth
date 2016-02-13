#pragma once

#include <string>
#include <sstream>


#include <json/reader.h>

#include "ethrpc/Block.hpp"
#include "ethrpc/Transaction.hpp"
#include "ethrpc/Collection.hpp"

#include "types/BigInt.hpp"

#include "RandomString.hpp"
#include "Hex.hpp"

using Xeth::BigInt;

class RandomBlockChain
{
    public:
        typedef Ethereum::Connector::Block Block;
        typedef Ethereum::Connector::Transaction Transaction;
        typedef Ethereum::Connector::Collection<Transaction> TransactionCollection;

    public:
        RandomBlockChain();
        RandomBlockChain(size_t maxHeight);

        void retrieveBlockDetails(bool);

        Ethereum::Connector::Block getBlock(size_t);
        Json::Value getBlockData(size_t);

        size_t getHeight();
        size_t getTotalFetched();
        void resetCounter();

        void setHeight(size_t);

        void pushMemPool(const char *from, const char *to, const BigInt &amount, const char *data = NULL);
        void pushMemPool(const char *txid, const char *from, const char *to, const BigInt &amount, const char *data = NULL);

        size_t getMemPoolSize() const;

        TransactionCollection getMemPool() const;

    private:
        size_t _height;
        size_t _fetched;
        Json::Value _mempool;
};
