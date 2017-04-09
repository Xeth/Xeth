
template<class GethSimulator>
GethSession<GethSimulator>::GethSession(boost::asio::io_service &service, GethSimulator *simulator) :
    _simulator(simulator),
    _socket(service)
{}


template<class GethSimulator>
stream_protocol::socket & GethSession<GethSimulator>::getSocket()
{
    return _socket;
}


template<class GethSimulator>
void GethSession<GethSimulator>::start()
{
    read();
}


template<class GethSimulator>
void GethSession<GethSimulator>::read()
{
    boost::asio::async_read_until
    (
        _socket,
        _readBuffer,
        JsonMatcher(),
        boost::bind
        (
            &GethSession<GethSimulator>::handleRead,
            this->shared_from_this(),
            boost::asio::placeholders::error,
            boost::asio::placeholders::bytes_transferred
        )
    );
}

template<class GethSimulator>
void GethSession<GethSimulator>::handleRead(const boost::system::error_code& error, size_t bytes)
{
    if (error)
    {
        std::cout<<"read failed : "<<error.message()<<"\n"<<std::flush;
    }
    else
    {
        if(!bytes)
        {
            std::cout<<"empty message\n"<<std::flush;
            _readBuffer.consume(1);
            read();
        }
        else
        {
            Json::Value response;
            Json::Value request;
            Json::Reader reader;
            try
            {
                const char *data = boost::asio::buffer_cast<const char*>(_readBuffer.data());
                if(reader.parse(data, data + bytes + 1, request, false))
                {
                    std::string method = request["method"].asString();
                    Json::Value params = request["params"];

                    response["id"] = request["id"];

                    if(method=="eth_getBalance")
                    {
                        std::stringstream stream;
                        BigInt balance = _simulator->getBalance(params[0].asCString());
                        stream<<"0x"<<std::hex<<balance;
                        response["result"] = Json::Value(stream.str());
                    }
                    else
                    if(method=="eth_sendTransaction")
                    {
                        Json::Value tx = params[0];
                        const char *data = tx.isMember("data") ? tx["data"].asCString() : NULL;
                        const char *from = tx["from"].asCString();
                        const char *to = tx["to"].asCString();
                        const char *value = tx["value"].asCString();
                        std::string txid = _simulator->sendTransaction(from, to, BigInt(value), data);
                        if(txid.size())
                        {
                            response["result"] = txid;
                        }
                        else
                        {
                            
                            response["error"] = "transaction failed";
                        }
                    }
                    else
                    if(method == "personal_signAndSendTransaction")
                    {
                        Json::Value tx = params[0];
                        const char *data = tx.isMember("data") ? tx["data"].asCString() : NULL;
                        const char *from = tx["from"].asCString();
                        const char *to = tx["to"].asCString();
                        const char *value = tx["value"].asCString();
                        const char * password = params[1].asCString();

                        std::string txid = _simulator->sendTransaction(from, to, BigInt(value), data, password);
                        if(txid.size())
                        {
                            response["result"] = txid;
                        }
                        else
                        {
                            response["error"] = "transaction failed";
                        }
                    }
                    else
                    if(method=="personal_unlockAccount")
                    {
                        response["result"] = (bool)_simulator->unlockAccount(params[0].asCString(), params[1].asCString(), params[2].asInt());
                    }
                    else
                    if(method=="eth_accounts")
                    {
                        Json::Value accounts;
                        std::vector<std::string> accountsData = _simulator->getAccounts();
                        for(std::vector<std::string>::iterator it=accountsData.begin(); it!=accountsData.end(); ++it)
                        {
                            accounts.append(*it);
                        }
                        response["result"] = accounts;
                    }
                    else
                    if(method=="eth_blockNumber")
                    {
                        size_t heigh = _simulator->getChainHeight();
                        std::stringstream stream;
                        stream<<"0x"<<std::hex<<heigh;
                        response["result"] = stream.str();
                    }
                    else
                    if(method=="eth_getBlockByNumber")
                    {
                        response["result"] = _simulator->getBlockData(unhex<size_t>(params[0].asCString()));
                    }
                    else
                    {
                        response["error"] = "invalid method";
                    }


                }
                else
                {
                    std::cout<<"Bad request: invalid json\n"<<std::flush;
                }

            }
            catch(const std::exception &e)
            {
                std::cout<<"Error : "<<e.what()<<"\n"<<std::flush;
                response["error"] = e.what();
            }
            _readBuffer.consume(bytes+2);
            read();
            Json::FastWriter writer;
            std::ostream stream(&_writeBuffer);
            stream<<writer.write(response);
            boost::asio::async_write
            (
                _socket, 
                _writeBuffer,
                boost::bind
                (
                    &GethSession<GethSimulator>::handleWrite,
                    this->shared_from_this(),
                    boost::asio::placeholders::error
                )
            );

        }
    }
}

template<class GethSimulator>
void GethSession<GethSimulator>::handleWrite(const boost::system::error_code& error)
{
    if (error)
    {
        std::cout<<"write failed : "<<error.message()<<"\n";
    }
}
