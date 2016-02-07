#pragma once 

#include <boost/date_time/posix_time/posix_time.hpp>
#include <boost/regex.hpp> 

#include "types/EthereumKey.hpp"

#include "FileStore.hpp"
#include "FileImporter.hpp"


namespace Xeth{


class EthereumKeyStore : protected FileStore<EthereumKey, EthereumKeySerializer>
{
    public:
        typedef FileStore<EthereumKey, EthereumKeySerializer> Base;
        typedef Base::Iterator Iterator;
        typedef Base::Data Data;
        typedef Base::DataSerializer DataSerializer;

    public:
        EthereumKeyStore(const std::string &path);

        bool insert(const EthereumKey &);

        Iterator find(const char *address) const;
        Iterator find(const EthereumAddress &) const;

        using Base::begin;
        using Base::end;
        using Base::insert;

    private:
        std::string makeFileName(const std::string &) const;
};


typedef FileImporter<EthereumKeyStore> EthereumKeyImporter;


}
