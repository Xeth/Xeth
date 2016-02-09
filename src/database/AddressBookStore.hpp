#pragma once

#include <QJsonObject>

#include "detail/LevelDbStore.hpp"

namespace Xeth{


class AddressBookDataSerializer
{
    public:
        QJsonObject operator()(const char *, const char *) const;
        bool operator()(const char *, const char *, QJsonObject &) const;
        std::string operator()(const QJsonObject &) const;
};



class AddressBookStore : public LevelDbStore<QJsonObject, AddressBookDataSerializer>
{
    public:
        typedef LevelDbStore<QJsonObject, AddressBookDataSerializer> Base;
        typedef Base::Iterator Iterator;
        typedef Base::ReverseIterator ReverseIterator;
        typedef Base::DataType DataType;

    public:
        AddressBookStore();
        AddressBookStore(const std::string &);

        bool insert(const char *, const char *);

        using Base::insert;

};





}
