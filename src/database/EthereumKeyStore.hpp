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
        bool insert(const char *id, const EthereumKey &);
        bool insert(const std::string &, const EthereumKey &);

        Iterator find(const char *address) const;
        Iterator find(const Ethereum::Address &) const;

        using Base::begin;
        using Base::end;

    private:
        std::string makeFileName(const EthereumKey &, const boost::posix_time::ptime &time) const;
        bool validateId(const std::string &id, const EthereumKey &);
};


typedef FileImporter<EthereumKeyStore> EthereumKeyImporter;


}
