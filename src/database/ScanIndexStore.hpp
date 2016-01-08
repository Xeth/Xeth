#pragma once

#include <boost/lexical_cast.hpp>
#include <string>

#include "Store.hpp"


namespace Xeth{



class ScanIndexDataDecoder
{
    public:
        size_t operator()(const char *key, const char *value) const;
        bool operator()(const char *key, const char *value, size_t &result) const;
        std::string operator()(size_t ) const;
};


class ScanIndexStore : private Store<ScanIndexDataDecoder, size_t>
{
    public:
        typedef Store<ScanIndexDataDecoder, size_t> Base;

    public:
        ScanIndexStore();
        ScanIndexStore(const char *);
        ScanIndexStore(const std::string &);

        using Base::open;
        using Base::openNoThrow;
        using Base::remove;
        using Base::getPath;

        bool insert(const char *key, size_t index);
        size_t get(const char *key);

};


}
