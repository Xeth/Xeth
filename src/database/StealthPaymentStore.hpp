#pragma once 

#include <QJsonObject>
#include <QObject>
#include <algorithm>

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

        Iterator find(const std::string &) const;
        QJsonObject get(const std::string &) const;

        bool insert(const char *address, const char *stealth, const char *secret, const char *txid);
        bool insert(const QJsonObject &);

    private:
        std::string normalizedAddress(const std::string &) const;
        using Base::find;
        using Base::get;

    signals:
        void NewItem(const QJsonObject &) const;

};



}
