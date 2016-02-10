#pragma once 

#include <boost/asio.hpp>

//#if defined(BOOST_ASIO_HAS_LOCAL_SOCKETS)

#include <map>
#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <sstream>

#include <boost/thread.hpp>
#include <boost/bind.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/noncopyable.hpp>

#include "types/BigInt.hpp"

#include "GethSession.hpp"


using boost::asio::local::stream_protocol;
using Ethereum::Connector::Block;
using Xeth::BigInt;



template<class KeyStore, class BlockChain>
class GethSimulator : public boost::noncopyable
{
    public:
        typedef GethSession<GethSimulator> Session;

    public:
        GethSimulator(KeyStore &, BlockChain &);
        GethSimulator(KeyStore &, BlockChain &, const std::string &path);

        void setBalance(const char *address, const BigInt &);
        void addBalance(const char *address, const BigInt &);
        BigInt getBalance(const char *address);

        bool sendTransaction(const char *from, const char *to, const BigInt &amount);

        bool unlockAccount(const char *address, const char *password, size_t duration);
        std::vector<std::string> getAccounts();

        Block getBlock(size_t );
        const char * getBlockData(size_t );
        size_t getChainHeight();

        bool listen(const char *path);
        void stop();

    private:
        void run();
        void acceptNew();
        void handleAccept(boost::shared_ptr<Session> session, const boost::system::error_code& error);

    private:
        boost::mutex _mutex;
        std::map<std::string, BigInt> _balances;
        KeyStore &_keys;
        BlockChain &_chain;

        boost::asio::io_service _service;
        boost::asio::io_service::work _work;
        boost::asio::local::stream_protocol::acceptor _acceptor;
        boost::thread _thread;
};


#include "GethSimulator.ipp"

//#endif
