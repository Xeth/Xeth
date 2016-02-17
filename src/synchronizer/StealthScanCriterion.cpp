#include "StealthScanCriterion.hpp"


namespace Xeth{

using Ethereum::PublicKeySerializer;
using Ethereum::Data;
using Ethereum::Literal;
using Ethereum::HexEncoder;

StealthScanCriterion::StealthScanCriterion(const StealthKey &key) :
    ScanCriterion(Literal(Ethereum::Stealth::Address(key))),
    _key(key)
{}

StealthScanCriterion::StealthScanCriterion(const StealthKey &key, const Ethereum::Stealth::Address &address) :
    ScanCriterion(Literal(address)),
    _key(key)
{}



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
    if(data.size() == 66 || data.size() == 130)
    {
        PublicKeySerializer serializer;
        try
        {
            Ethereum::PublicKey ephem = serializer.unserialize(data);
            StealthResolver resolver(_key);
            Ethereum::Stealth::SharedSecret secret;
            if(resolver.uncover(Ethereum::Address(to), ephem, secret))
            {
                QJsonObject tx;
                tx.insert("category", TransactionCategory::ToString(TransactionCategory::Stealth));
                tx.insert("hash", hash.c_str());
                tx.insert("from",  from.c_str());
                tx.insert("to", to.c_str());
                tx.insert("amount", boost::lexical_cast<std::string>(amount).c_str());
                tx.insert("timestamp", (int)timestamp);
                tx.insert("stealth", getAddress());
                result.transactions.push_back(tx);

                HexEncoder encoder;
                QJsonObject sp;
                sp.insert("address", to.c_str());
                sp.insert("secret", encoder.encode(secret.begin(), secret.end()).c_str());
                sp.insert("txid", hash.c_str());
                sp.insert("stealth", getAddress());
                result.stealthPayments.push_back(sp);
            }
        }
        catch(...)
        {}
    }
}


}
