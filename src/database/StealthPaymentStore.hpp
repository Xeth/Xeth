#pragma once 

#include <QJsonObject>
#include <QObject>

#include "detail/LevelDbStore.hpp"
#include "detail/HexAddressNormalizer.hpp"

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
        bool replace(const QJsonObject &);

    private:
        std::string normalizedAddress(const std::string &) const;
        using Base::find;
        using Base::get;
        using Base::replace;

    signals:
        void NewItem(const QJsonObject &) const;

};



}
