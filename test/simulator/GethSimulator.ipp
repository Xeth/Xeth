
template<class KeyStore, class BlockChain>
GethSimulator<KeyStore, BlockChain>::GethSimulator(KeyStore &keys, BlockChain &chain) : 
    _keys(keys),
    _chain(chain),
    _work(_service),
    _acceptor(_service),
    _thread(boost::bind(&GethSimulator<KeyStore, BlockChain>::run, this))
{}

template<class KeyStore, class BlockChain>
GethSimulator<KeyStore, BlockChain>::GethSimulator(KeyStore &keys, BlockChain &chain, const std::string &path) : 
    _keys(keys),
    _chain(chain),
    _work(_service),
    _acceptor(_service, stream_protocol::endpoint(path)),
    _thread(boost::bind(&GethSimulator<KeyStore, BlockChain>::run, this))
{
    acceptNew();
}


template<class KeyStore, class BlockChain>
void GethSimulator<KeyStore, BlockChain>::run()
{
    _service.run();
}

template<class KeyStore, class BlockChain>
std::vector<std::string> GethSimulator<KeyStore, BlockChain>::getAccounts()
{
    boost::mutex::scoped_lock lock(_mutex);
    return _keys.getAccounts();
}

template<class KeyStore, class BlockChain>
void GethSimulator<KeyStore, BlockChain>::setBalance(const char *address, const BigInt &amount)
{
    boost::mutex::scoped_lock lock(_mutex);
    _balances[address] = amount;
}

template<class KeyStore, class BlockChain>
void GethSimulator<KeyStore, BlockChain>::addBalance(const char *address, const BigInt &amount)
{
    boost::mutex::scoped_lock lock(_mutex);
    _balances[address] += amount;
}

template<class KeyStore, class BlockChain>
BigInt GethSimulator<KeyStore, BlockChain>::getBalance(const char *address)
{
    boost::mutex::scoped_lock lock(_mutex);
    return _balances[address];
}


template<class KeyStore, class BlockChain>
bool GethSimulator<KeyStore, BlockChain>::unlockAccount(const char *address, const char *password, size_t duration)
{
    boost::mutex::scoped_lock lock(_mutex);
    return _keys.unlockAccount(address, password, duration);
}


template<class KeyStore, class BlockChain>
bool GethSimulator<KeyStore, BlockChain>::sendTransaction(const char *from, const char *to, const BigInt &amount)
{
    {
        boost::mutex::scoped_lock lock(_mutex);
        if(!_keys.isUnlocked(from))
        {
            return false;
        }

        if(_balances[from] < amount)
        {
            return false;
        }
    }
    addBalance(from, -amount);
    addBalance(to, amount);

    return true;
}


template<class KeyStore, class BlockChain>
Ethereum::Connector::Block GethSimulator<KeyStore, BlockChain>::getBlock(size_t number)
{
    boost::mutex::scoped_lock lock(_mutex);
    return _chain.getBlock(number);
}

template<class KeyStore, class BlockChain>
const char * GethSimulator<KeyStore, BlockChain>::getBlockData(size_t number)
{
    boost::mutex::scoped_lock lock(_mutex);
    return _chain.getBlockData(number);
}

template<class KeyStore, class BlockChain>
size_t GethSimulator<KeyStore, BlockChain>::getChainHeight()
{
    boost::mutex::scoped_lock lock(_mutex);
    return _chain.getHeight();
}

template<class KeyStore, class BlockChain>
bool GethSimulator<KeyStore, BlockChain>::listen(const char *path)
{
    boost::system::error_code error;
    stream_protocol::endpoint endpoint(path);
    _acceptor.bind(path, error);
    acceptNew();
    if(error)
    {
        return false;
    }
    return true;
}

template<class KeyStore, class BlockChain>
void GethSimulator<KeyStore, BlockChain>::stop()
{
    _service.stop();
    _thread.join();
}

template<class KeyStore, class BlockChain>
void GethSimulator<KeyStore, BlockChain>::handleAccept(boost::shared_ptr<Session> session, const boost::system::error_code& error)
{
    if (!error)
    {
        session->start();
    }
    else
    {
        std::cout<<"failed to accept : "<<error.message()<<std::endl<<std::flush;
    }
    acceptNew();
}

template<class KeyStore, class BlockChain>
void GethSimulator<KeyStore, BlockChain>::acceptNew()
{
    boost::shared_ptr<Session> session(new Session(_service, this));
    _acceptor.async_accept
    (
        session->getSocket(), 
        boost::bind
        (
            &GethSimulator<KeyStore, BlockChain>::handleAccept, 
            this, 
            session, 
            boost::asio::placeholders::error
        )
    );
}





