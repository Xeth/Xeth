#include "StealthPaymentStore.hpp"


namespace Xeth{


StealthPaymentStore::StealthPaymentStore()
{}


StealthPaymentStore::StealthPaymentStore(const std::string &path) : 
    Base(path)
{}


StealthPaymentStore::StealthPaymentStore(const boost::filesystem::path &path) : 
    Base(path)
{}


std::string StealthPaymentStore::normalizedAddress(const std::string &address) const
{
    std::string result = address;
    if(result[1]=='x'||result[1]=='X')
    {
        result.erase(0, 2);
    }

    std::transform(result.begin(), result.end(), result.begin(), ::tolower);
    return result;
}


StealthPaymentStore::Iterator StealthPaymentStore::find(const std::string &address) const
{
    return Base::find(normalizedAddress(address).c_str());
}

QJsonObject StealthPaymentStore::get(const std::string &address) const
{
    return Base::get(normalizedAddress(address).c_str());
}


bool StealthPaymentStore::insert(const char *address, const char *stealth, const char *secret, const char *txid)
{
    QJsonObject object;

    object.insert("address", QString(address));
    object.insert("stealth", QString(stealth));
    object.insert("secret", QString(secret));
    object.insert("txid", QString(txid));

    if(Base::insert(normalizedAddress(address).c_str(), object))
    {
        emit NewItem(object);
        return true;
    }
    return false;
}


bool StealthPaymentStore::insert(const QJsonObject &obj)
{
    if(Base::insert(normalizedAddress(obj["address"].toString().toStdString()).c_str(), obj)) //ToDo: optimize it !!!
    {
        emit NewItem(obj);
        return true;
    }
    return false;
}


}
