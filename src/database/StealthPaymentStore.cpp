#include "StealthPaymentStore.hpp"


namespace Xeth{


StealthPaymentStore::StealthPaymentStore()
{}


StealthPaymentStore::StealthPaymentStore(const std::string &path) : 
    Base(path)
{}


bool StealthPaymentStore::insert(const char *address, const char *sharedSecret, const char *txid)
{
    QJsonObject object;
    object.insert("address", address);
    object.insert("secret", sharedSecret);
    object.insert("txid", txid);

    return Base::insert(address, object);
}


bool StealthPaymentStore::insert(const QJsonObject &obj)
{
    return Base::insert(obj["address"].toString().toStdString().c_str(), obj); //ToDo: optimize it !!!
}


}
