#include "StealthPaymentStore.hpp"


namespace Xeth{


StealthPaymentStore::StealthPaymentStore()
{}


StealthPaymentStore::StealthPaymentStore(const std::string &path) : 
    Base(path)
{}


bool StealthPaymentStore::insert(const char *stealthAddress, const char *paymentAddress, const char *ephemPubKey, const char *txid)
{
    QJsonObject object;
    object.insert("address", paymentAddress);
    object.insert("ephem", ephemPubKey);
    object.insert("txid", txid);
    object.insert("stealth", stealthAddress);

    return Base::insert(stealthAddress, object);
}


}
