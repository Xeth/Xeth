#pragma once

#include "database/DataBase.hpp"

#include "types/EthereumKey.hpp"
#include "types/StealthKey.hpp"


namespace Xeth{


class StealthRedeemKeyFactory
{
    public:
        StealthRedeemKeyFactory(DataBase &);

        EthereumKey create(const QJsonObject &, const std::string &password);
        EthereumKey create(const QJsonObject &, const std::string &masterPassword, const std::string &keyPassword);

        EthereumKey create(const std::string &stealth, const std::string &secret, const std::string &password);
        EthereumKey create(const std::string &stealth, const std::string &secret, const std::string &masterPassword, const std::string &keyPassword);

    private:
        DataBase &_database;

};


}
