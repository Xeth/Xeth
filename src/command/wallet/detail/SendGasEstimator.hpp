#pragma once

#include <string>
#include <QString>

#include "ethrpc/Provider.hpp"
#include "ethrpc/GasEstimator.hpp"
#include "types/BigInt.hpp"


namespace Xeth{


class SendGasEstimator
{
    public:
        SendGasEstimator(Ethereum::Connector::Provider &);

        BigInt estimate(const QString &from, const QString &to, const BigInt &amount);
        BigInt estimate(const std::string &from, const std::string &to, const BigInt &amount);

        BigInt getGasPrice();

        BigInt estimateHex(const QString &from, const QString &to, const BigInt &amount);
        BigInt estimateHex(const std::string &from, const std::string &to, const BigInt &amount);

        BigInt estimateStealth(const QString &from, const QString &to, const BigInt &amount);
        BigInt estimateStealth(const std::string &from, const std::string &to, const BigInt &amount);

        BigInt estimateStealth(const std::string &from, const BigInt &);

    private:
        Ethereum::Connector::GasEstimator _estimator;

};


class StealthSendGasEstimator
{
    public:
        StealthSendGasEstimator(Ethereum::Connector::Provider &);
        BigInt estimate(const QString &from, const QString &to, const BigInt &amount);
        BigInt estimate(const std::string &from, const std::string &to, const BigInt &amount);

        BigInt getGasPrice();

    private:
        SendGasEstimator _estimator;
};


class HexSendGasEstimator
{
    public:
        HexSendGasEstimator(Ethereum::Connector::Provider &);

        BigInt estimate(const QString &from, const QString &to, const BigInt &amount);
        BigInt estimate(const std::string &from, const std::string &to, const BigInt &amount);

        BigInt getGasPrice();

    private:
        SendGasEstimator _estimator;
};


}
