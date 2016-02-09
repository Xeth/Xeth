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

    private:
        EthereumKey create(const std::string &paymentTxid, const std::string &sharedSecret, const std::string &password);

    private:
        DataBase &_database;

};


}
