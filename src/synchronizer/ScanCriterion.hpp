#pragma once

#include <eth-connector/Block.hpp>

#include <string>
#include <QVariantList>

#include "BigInt.hpp"

namespace Xeth{


class ScanCriterion
{
    public:
        ScanCriterion(const char *);

        virtual ~ScanCriterion();

        virtual void processHeader
        (
            size_t index,
            const std::string &hash,
            const std::string &miner,
            const BigInt &amount,
            time_t timestamp,
            QJsonArray &result
        );

        virtual void processTransaction
        (
            const std::string &hash,
            const std::string &from,
            const std::string &to,
            const BigInt &amount,
            const std::string &data,
            time_t timestamp,
            QJsonArray &result
        );

        const char * getAddress() const;

    protected:
        std::string _address;

};



}
