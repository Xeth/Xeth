#include "TransactionObjectBuilder.hpp"


namespace Xeth{


void TransactionObjectBuilder::setDetails(const std::string &hash, const TransactionCategory &, const std::string &from, const std::string &to, const BigInt &amount, time_t timestamp)
{
    _data.insert("category", TransactionCategory::ToString(TransactionCategory::Received));
    _data.insert("hash", hash.c_str());
    _data.insert("from",  from.c_str());
    _data.insert("to", to.c_str());
    _data.insert("amount", boost::lexical_cast<std::string>(amount).c_str());
    _data.insert("timestamp", (int)timestamp);
}


void TransactionObjectBuilder::setStealth(const Ethereum::Stealth::Address &address)
{
    _data.insert("stealth", address.toString().c_str());
}


void TransactionObjectBuilder::setExtraData(const QVariantMap &data)
{
    for(QVariantMap::const_iterator it = data.begin(), end = data.end(); it!=end; ++it)
    {
        _data.insert(it.key(), QJsonValue::fromVariant(it.value()));
    }
}


const QJsonObject & TransactionObjectBuilder::build()
{
    return _data;
}


}
