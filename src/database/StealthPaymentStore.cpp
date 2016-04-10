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


bool StealthPaymentStore::insert(const char *address, const char *stealth, const char *secret, const char *txid)
{
    QJsonObject object;

    object.insert("address", QString(address));
    object.insert("stealth", QString(stealth));
    object.insert("secret", QString(secret));
    object.insert("txid", QString(txid));

    if(Base::insert(address, object))
    {
        emit NewItem(object);
        return true;
    }
    return false;
}


bool StealthPaymentStore::insert(const QJsonObject &obj)
{
    if(Base::insert(obj["address"].toString().toStdString().c_str(), obj)) //ToDo: optimize it !!!
    {
        emit NewItem(obj);
        return true;
    }
    return false;
}


}
