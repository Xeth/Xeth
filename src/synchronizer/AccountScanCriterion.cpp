#include "AccountScanCriterion.hpp"

namespace Xeth{

AccountScanCriterion::AccountScanCriterion(const char *address) :
    ScanCriterion(address)
{}

void AccountScanCriterion::processHeader
(
    size_t,
    const std::string &hash,
    const std::string &miner,
    const BigInt &amount,
    time_t timestamp,
    QJsonArray &result
)
{
    if(miner == _address)
    {
        saveTransaction(TransactionCategory::Mined, hash, "", miner, amount, timestamp, result);
    }
}

void AccountScanCriterion::processTransaction
(
    const std::string &hash,
    const std::string &from,
    const std::string &to,
    const BigInt &amount,
    const std::string &,
    time_t timestamp,
    QJsonArray &result
)
{
    if(from == _address)
    {
        saveTransaction(TransactionCategory::Sent, hash, from, to, amount, timestamp, result);
    }
    else if(to == _address)
    {
        saveTransaction(TransactionCategory::Received, hash, from, to, amount, timestamp, result);
    }
}


void AccountScanCriterion::saveTransaction
(
    const TransactionCategory &category,
    const std::string &hash,
    const std::string &from,
    const std::string &to,
    const BigInt &amount,
    time_t timestamp,
    QJsonArray &result
)
{
    QJsonObject obj;
    obj.insert("category", category.toString());
    obj.insert("hash", hash.c_str());
    obj.insert("from",  from.c_str());
    obj.insert("to", to.c_str());
    obj.insert("amount", amount.str().c_str());
    obj.insert("timestamp", boost::lexical_cast<std::string>(timestamp).c_str());
    result.push_back(obj);
}


}
