#pragma once

#include <string>

#include "ethrpc/Block.hpp"

#include "TransactionCategory.hpp"
#include "BigInt.hpp"
#include "ScanResult.hpp"

namespace Xeth{


class ScanCriterion
{
    public:

        ScanCriterion(const char *);
        ScanCriterion(const std::string &);

        virtual ~ScanCriterion();

        virtual void processHeader
        (
            size_t index,
            const std::string &hash,
            const std::string &miner,
            const BigInt &amount,
            time_t timestamp,
            ScanResult &result
        );

        virtual void processTransaction
        (
            const std::string &hash,
            const std::string &from,
            const std::string &to,
            const BigInt &amount,
            const std::string &data,
            time_t timestamp,
            ScanResult &result
        );

        const char * getAddress() const;

    protected:
        std::string _address;

};



}
