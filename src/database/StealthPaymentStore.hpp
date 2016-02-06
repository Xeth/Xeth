#pragma once 

#include <QJsonObject>

#include "LevelDbStore.hpp"


namespace Xeth{


class StealthPaymentStore : public LevelDbStore<QJsonObject>
{
    public:
        typedef LevelDbStore<QJsonObject> Base;
        typedef Base::Iterator Iterator;
        typedef Base::ReverseIterator ReverseIterator;
        typedef Base::DataType DataType;

    public:
        StealthPaymentStore();
        StealthPaymentStore(const std::string &);

        bool insert(const char *address, const char *sharedSecret, const char *txid);
        bool insert(const QJsonObject &);

};



}
