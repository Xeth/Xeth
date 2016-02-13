#pragma once 

#include <boost/asio.hpp>

//#if defined(BOOST_ASIO_HAS_LOCAL_SOCKETS)

#include <sstream>

#include <boost/array.hpp>
#include <boost/bind.hpp>
#include <boost/enable_shared_from_this.hpp>
#include <boost/shared_ptr.hpp>

#include <json/value.h>
#include <json/reader.h>
#include <json/writer.h>

#include "ethrpc/transport/JsonMatcher.hpp"
#include "ethrpc/hex.hpp"

#include "types/BigInt.hpp"


using boost::asio::local::stream_protocol;
using Xeth::BigInt;
using Ethereum::Connector::JsonMatcher;
using Ethereum::Connector::unhex;


template<class GethSimulator>
class GethSession : public boost::enable_shared_from_this<GethSession<GethSimulator> >
{
    public:
        GethSession(boost::asio::io_service &, GethSimulator *);

        stream_protocol::socket & getSocket();
        void start();

    private:
        void read();
        void handleRead(const boost::system::error_code& error, size_t bytes_transferred);
        void handleWrite(const boost::system::error_code& error);

    private:
        boost::asio::streambuf _readBuffer;
        boost::asio::streambuf _writeBuffer;
        GethSimulator *_simulator;
        boost::asio::local::stream_protocol::socket _socket;
};



#include "GethSession.ipp"
