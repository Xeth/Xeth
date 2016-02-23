#pragma once 

#include <QJsonObject>
#include <QObject>

#include "detail/LevelDbStore.hpp"


namespace Xeth{


class StealthPaymentStore : 
    public QObject,
    public LevelDbStore<QJsonObject>
{
    Q_OBJECT
    public:
        typedef LevelDbStore<QJsonObject> Base;
        typedef Base::Iterator Iterator;
        typedef Base::ReverseIterator ReverseIterator;
        typedef Base::DataType DataType;

    public:
        StealthPaymentStore();
        StealthPaymentStore(const std::string &);
        StealthPaymentStore(const boost::filesystem::path &);

        bool insert(const char *address, const char *stealth, const char *secret, const char *txid);
        bool insert(const QJsonObject &);

    signals:
        void NewItem(const QJsonObject &) const;

};



}
