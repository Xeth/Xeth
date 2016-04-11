#pragma once 

#include <boost/date_time/posix_time/posix_time.hpp>
#include <boost/date_time/gregorian/conversion.hpp>
#include <boost/regex.hpp> 
#include <boost/filesystem.hpp>

#include <QObject>

#include "types/EthereumKey.hpp"

#include "detail/FileStore.hpp"


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
        bool replace(const EthereumKey &, time_t);

        bool insert(const EthereumKey &);
        bool insert(const EthereumKey &, time_t);

        Iterator find(const char *address) const;
        Iterator find(const Ethereum::Address &) const;
        EthereumKey get(const char *address) const;

        using Base::begin;
        using Base::end;

    signals:
        void NewItem(const QString &) const;

    private:
        bool insertNoCheck(const char *, const EthereumKey &);
        bool replaceNoCheck(const char *, const EthereumKey &);
        std::string makeFileName(const EthereumKey &) const;
        std::string makeFileName(const EthereumKey &, time_t time) const;
        std::string makeFileName(const EthereumKey &, const boost::posix_time::ptime &time) const;
        bool validateId(const std::string &id, const EthereumKey &);
};





}
