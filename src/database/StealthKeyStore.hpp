#pragma once 

#include "types/StealthKey.hpp"
#include "FileStore.hpp"


namespace Xeth{



class StealthKeyStore : protected FileStore<StealthKey, StealthKeySerializer>
{
    public:
        typedef FileStore<StealthKey, StealthKeySerializer> Base;
        typedef Base::Iterator Iterator;

    public:
        StealthKeyStore(const std::string &path);

        bool insert(const StealthKey &);

        Iterator find(const char *address) const;
        Iterator find(const StealthAddress &) const;

        using Base::begin;
        using Base::end;
        using Base::importFile;

    private:
        std::string makeAddress(const StealthKey &) const;

};



}
