#pragma once

#include <boost/lexical_cast.hpp>
#include <string>

#include "detail/LevelDbStore.hpp"


namespace Xeth{


class ScanIndexStore : private LevelDbStore<size_t>
{
    public:
        typedef LevelDbStore<size_t> Base;
        typedef Base::Iterator Iterator;

    public:
        ScanIndexStore();
        ScanIndexStore(const char *);
        ScanIndexStore(const std::string &);
        ScanIndexStore(const boost::filesystem::path &);

        using Base::open;
        using Base::openNoThrow;
        using Base::remove;
        using Base::getPath;
        using Base::begin;
        using Base::end;

        bool insert(const char *key, size_t index);
        size_t get(const char *key) const;

};


}
