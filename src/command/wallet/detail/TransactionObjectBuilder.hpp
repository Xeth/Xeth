#pragma once

#include <QJsonObject>
#include <QJsonValue>
#include <QString>
#include <QVariantMap>
#include <string>
#include <ctime>


#include "types/BigInt.hpp"
#include "types/StealthKey.hpp"
#include "types/TransactionCategory.hpp"


namespace Xeth{


class TransactionObjectBuilder
{
    public:

        void setDetails(const std::string &txid, const TransactionCategory &, const std::string &from, const std::string &to, const BigInt &amount, time_t timestamp = time(NULL));
        void setExtraData(const QVariantMap &);
        void setStealth(const Ethereum::Stealth::Address &);

        const QJsonObject & build();

    private:
        QJsonObject _data;
};


}
