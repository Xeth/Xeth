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

    public:
        ApplicationContext();

        Xeth::DataBase & getDataBase();
        KeyStore & getKeyStore();
        BlockChain & getBlockChain();
        GethSimulator & getGeth();
        Ethereum::Connector::Provider & getProvider();
        Xeth::Synchronizer & getSynchronizer();

    private:
        DataBaseDirectory _dir;
        Xeth::DataBase _database;
        KeyStore _keys;
        BlockChain _chain;
        std::string _gethPath;
        GethSimulator _geth;
        Ethereum::Connector::Provider _provider;
        Xeth::Synchronizer _synchronizer;
};


#include "ApplicationContext.ipp"
