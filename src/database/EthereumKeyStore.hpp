#pragma once 

#include <boost/date_time/posix_time/posix_time.hpp>
#include <boost/regex.hpp> 
#include <boost/filesystem.hpp>

#include <QObject>

#include "types/EthereumKey.hpp"

#include "detail/FileStore.hpp"
#include "detail/FileImporter.hpp"


namespace Xeth{



class EthereumKeyStore : 
    public QObject,
    protected FileStore<EthereumKey, EthereumKeySerializer>
{

    Q_OBJECT
    public:
        typedef FileStore<EthereumKey, EthereumKeySerializer> Base;
        typedef Base::Iterator Iterator;
        typedef Base::Data Data;
        typedef Base::DataSerializer DataSerializer;

    public:
        EthereumKeyStore(const std::string &path);
        EthereumKeyStore(const boost::filesystem::path &path);

        bool replace(const EthereumKey &);
        bool insert(const EthereumKey &);
        bool insert(const char *id, const EthereumKey &);
        bool insert(const std::string &, const EthereumKey &);

        Iterator find(const char *address) const;
        Iterator find(const Ethereum::Address &) const;
        EthereumKey get(const char *address) const;

        using Base::begin;
        using Base::end;

    signals:
        void NewItem(const QString &) const;

    private:
        std::string makeFileName(const EthereumKey &) const;
        std::string makeFileName(const EthereumKey &, const boost::posix_time::ptime &time) const;
        bool validateId(const std::string &id, const EthereumKey &);
};


typedef FileImporter<EthereumKeyStore> EthereumKeyImporter;


}
