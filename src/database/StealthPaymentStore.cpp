#include "StealthPaymentStore.hpp"


namespace Xeth{


StealthPaymentStore::StealthPaymentStore()
{}


StealthPaymentStore::StealthPaymentStore(const std::string &path) : 
    Base(path)
{}


bool StealthPaymentStore::insert(const char *address, const char *stealth, const char *secret, const char *txid)
{
    QJsonObject object;

    object.insert("address", address);
    object.insert("stealth", stealth);
    object.insert("secret", secret);
    object.insert("txid", txid);

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
