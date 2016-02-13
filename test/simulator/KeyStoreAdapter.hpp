#pragma once 

#include <string>
#include <map>
#include <vector>

#include "database/DataBase.hpp"
#include "types/EthereumKey.hpp"

class KeyStoreAdapter
{

    public:
        KeyStoreAdapter(Xeth::DataBase &);

        std::string registerAccount(const std::string &password);

        bool unlockAccount(const char *address, const char *password, size_t duration);
        std::vector<std::string> getAccounts();
        bool isUnlocked(const char *address);

    private:
        Xeth::EthereumKeyStore &_store;
        std::map<std::string, time_t> _locks;
};
