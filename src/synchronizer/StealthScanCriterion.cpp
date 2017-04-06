#include "StealthScanCriterion.hpp"

namespace Xeth{

using Ethereum::PublicKeySerializer;
using Ethereum::Data;
using Ethereum::Literal;
using Ethereum::HexEncoder;

StealthScanCriterion::StealthScanCriterion(const StealthKey &key) :
    ScanCriterion(makeAddress(key)),
    _key(key)
{}

StealthScanCriterion::StealthScanCriterion(const StealthKey &key, const Ethereum::Stealth::Address &address) :
    ScanCriterion(address.toString()),
    _key(key)
{}


std::string StealthScanCriterion::makeAddress(const StealthKey &key) const
{
    Ethereum::Stealth::Address address(key);
    std::string str =  address.toString();
    return str;
}


void StealthScanCriterion::uncoverStealthPayment
(
    const std::string &hash,
    const std::string &from,
    const std::string &to,
    const BigInt &amount,
    const char *data,
    size_t dataSize,
    time_t timestamp,
    ScanResult &result
)
{
    PublicKeySerializer serializer;
    try
    {
        Ethereum::PublicKey ephem = serializer.unserialize(data, dataSize);
        StealthResolver resolver(_key);
        Ethereum::Stealth::SharedSecret secret;
        if(resolver.uncover(Ethereum::Address(to), ephem, secret))
        {
            QJsonObject tx;
            QString stealthStr = getAddress();
            QString hashStr = hash.c_str();
            QString toStr = to.c_str();
            QString fromStr = from.c_str();

            tx.insert("category", QString(TransactionCategory::ToString(TransactionCategory::Received)));
            tx.insert("hash", hashStr);
            tx.insert("from", fromStr);
            tx.insert("to", toStr);
            tx.insert("amount", QString(boost::lexical_cast<std::string>(amount).c_str()));
            tx.insert("timestamp", (int)timestamp);
            tx.insert("stealth", stealthStr);
            result.transactions.push_back(tx);

            HexEncoder encoder;
            QJsonObject sp;
            sp.insert("address", toStr);
            sp.insert("secret", QString(encoder.encode(secret.begin(), secret.end()).c_str()));
            sp.insert("txid", hashStr);
            sp.insert("stealth", stealthStr);
            tx.insert("timestamp", (int)timestamp);
            result.stealthPayments.push_back(sp);
        }
    }
    catch(...)
    {}
}

void StealthScanCriterion::processTransaction
(
    const std::string &hash,
    const std::string &from,
    const std::string &to,
    const BigInt &amount,
    const std::string &data,
    time_t timestamp,
    ScanResult &result
)
{
    size_t dataSize = data.size();

    if(dataSize == 66 || dataSize == 130 || ((dataSize == 68 || dataSize == 132)&&data[0]=='0'&&(data[1]=='x'||data[1]=='X')))
    {
        uncoverStealthPayment(hash, from, to, amount, data.data(), dataSize, timestamp, result);
    }
}


}
