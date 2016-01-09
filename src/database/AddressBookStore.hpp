#pragma once

#include <QJsonObject>

#include "Store.hpp"

namespace Xeth{


class AddressBookDataDecoder
{
    public:
        QJsonObject operator()(const char *, const char *) const;
        bool operator()(const char *, const char *, QJsonObject &) const;
        std::string operator()(const QJsonObject &) const;
};



class AddressBookStore : public Store<AddressBookDataDecoder, QJsonObject>
{
    public:
        typedef Store<AddressBookDataDecoder, QJsonObject> Base;
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
