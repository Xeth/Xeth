#pragma once 

#include "types/StealthKey.hpp"

#include "detail/FileStore.hpp"
#include "detail/FileImporter.hpp"


namespace Xeth{


class StealthKeyStore : protected FileStore<StealthKey, StealthKeySerializer>
{
    public:
        typedef FileStore<StealthKey, StealthKeySerializer> Base;
        typedef Base::Iterator Iterator;
        typedef Base::Data Data;
        typedef Base::DataSerializer DataSerializer;

    public:
        StealthKeyStore(const std::string &path);

        bool insert(const StealthKey &);
        bool insert(const std::string &, const StealthKey &);
        bool insert(const char *, const StealthKey &);

        Iterator find(const char *address) const;
        Iterator find(const Ethereum::Stealth::Address &) const;

        using Base::begin;
        using Base::end;

    private:
        std::string makeAddress(const StealthKey &) const;

};


typedef FileImporter<StealthKeyStore> StealthKeyImporter;


}
