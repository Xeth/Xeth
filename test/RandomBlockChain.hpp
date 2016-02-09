#pragma once

#include <string>
#include <sstream>

#include <boost/random/random_device.hpp>
#include <boost/random/uniform_int_distribution.hpp>

#include <json/reader.h>

#include "ethrpc/Block.hpp"




class RandomBlockChain
{
    public:
        typedef Ethereum::Connector::Block Block;

    public:
        RandomBlockChain(size_t maxHeight);

        void retrieveBlockDetails(bool);

        Ethereum::Connector::Block getBlock(size_t);
        size_t getHeight();
        size_t getTotalFetched();

    private:
        std::string randomString(size_t) const;
        std::string getHex(size_t) const;

    private:
        size_t _height;
        size_t _fetched;
        std::string _alphabet;
        boost::random::uniform_int_distribution<> _dist;

};
