#pragma once

#include <boost/lexical_cast.hpp>
#include <string>

#include "LevelDbStore.hpp"


namespace Xeth{


class ScanIndexStore : private LevelDbStore<size_t>
{
    public:
        typedef LevelDbStore<size_t> Base;

    public:
        ScanIndexStore();
        ScanIndexStore(const char *);
        ScanIndexStore(const std::string &);

        using Base::open;
        using Base::openNoThrow;
        using Base::remove;
        using Base::getPath;

        bool insert(const char *key, size_t index);
        size_t get(const char *key) const;

};


}
