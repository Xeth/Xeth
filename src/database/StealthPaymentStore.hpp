#pragma once 

#include <QJsonObject>

#include "Store.hpp"


namespace Xeth{


class StealthPaymentStore : public Store<QJsonObject>
{
    public:
        typedef Store<QJsonObject> Base;
        typedef Base::Iterator Iterator;
        typedef Base::ReverseIterator ReverseIterator;
        typedef Base::DataType DataType;

    public:
        StealthPaymentStore();
        StealthPaymentStore(const std::string &);

        bool insert(const char *stealthAddress, const char *paymentAddress, const char *ephemPubKey, const char *txid);

        using Base::insert;

};



}
