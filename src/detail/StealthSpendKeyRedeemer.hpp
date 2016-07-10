#pragma once

#include "database/DataBase.hpp"

#include "types/EthereumKey.hpp"
#include "types/StealthKey.hpp"


namespace Xeth{


class StealthSpendKeyRedeemer
{
    public:
        StealthSpendKeyRedeemer(DataBase &);

        bool redeem(const std::string &address, const std::string &password);
        bool redeem(const std::string &address, const std::string &masterPassword, const std::string &newPassword);


    private:

        EthereumKey createFromPaymentData(const QJsonObject &, const std::string &password);
        EthereumKey createFromPaymentData(const QJsonObject &, const std::string &masterPassword, const std::string &keyPassword);

        EthereumKey createFromPaymentData(const std::string &stealth, const std::string &secret, const std::string &password);
        EthereumKey createFromPaymentData(const std::string &stealth, const std::string &secret, const std::string &masterPassword, const std::string &keyPassword);

    private:
        DataBase &_database;

};


}
