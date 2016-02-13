
template<class KeyStore, class BlockChain>
ApplicationContext<KeyStore, BlockChain>::ApplicationContext() :
    _dir(true),
    _database(_dir, Xeth::EthereumKeyStorePath(_dir.getPath())),
    _keys(_database), 
    _gethPath(_dir.getPath() + "geth.ipc"),
    _geth(_keys, _chain, _gethPath),
    _synchronizer(_provider, _database)
{
    sleep(1);
    if(!_provider.connect(std::string("ipc:" + _gethPath).c_str()))
    {
        throw std::runtime_error("provider failed to connect");
    }
}


template<class KeyStore, class BlockChain>
Xeth::DataBase & ApplicationContext<KeyStore, BlockChain>::getDataBase()
{
    return _database;
}


template<class KeyStore, class BlockChain>
Xeth::Synchronizer & ApplicationContext<KeyStore, BlockChain>::getSynchronizer()
{
    return _synchronizer;
}


template<class KeyStore, class BlockChain>
GethSimulator<KeyStore, BlockChain> & ApplicationContext<KeyStore, BlockChain>::getGeth()
{
    return _geth;
}


template<class KeyStore, class BlockChain>
Ethereum::Connector::Provider & ApplicationContext<KeyStore, BlockChain>::getProvider()
{
    return _provider;
}


template<class KeyStore, class BlockChain>
KeyStore & ApplicationContext<KeyStore, BlockChain>::getKeyStore()
{
    return _keys;
}


template<class KeyStore, class BlockChain>
BlockChain & ApplicationContext<KeyStore, BlockChain>::getBlockChain()
{
    return _chain;
}
