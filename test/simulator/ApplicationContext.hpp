#pragma once 

#include "ethrpc/Provider.hpp"

#include "database/DataBase.hpp"
#include "synchronizer/Synchronizer.hpp"

#include "GethSimulator.hpp"
#include "DataBaseDirectory.hpp"



template<class KeyStore, class BlockChain>
class ApplicationContext
{
    public:
        typedef ::GethSimulator<KeyStore, BlockChain> GethSimulator;
        typedef Ethereum::Connector::Provider Provider;

    public:
        ApplicationContext(bool connect);

        bool connectProvider();

        Xeth::DataBase & getDataBase();
        KeyStore & getKeyStore();
        BlockChain & getBlockChain();
        GethSimulator & getGeth();
        Ethereum::Connector::Provider & getProvider();
        Xeth::Synchronizer & getSynchronizer();

    private:
        DataBaseDirectory _dir;
        Xeth::DataBase _database;
        BlockChain _chain;
        KeyStore _keys;
        std::string _gethPath;
        GethSimulator _geth;
        Ethereum::Connector::Provider _provider;
        Xeth::Synchronizer _synchronizer;
};


#include "ApplicationContext.ipp"
