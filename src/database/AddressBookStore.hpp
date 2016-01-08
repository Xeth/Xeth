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

typedef Store<AddressBookDataDecoder, QJsonObject> AddressBookStore;




}
