#pragma once 

#include <QObject>

#include "types/StealthKey.hpp"

#include "detail/FileStore.hpp"
#include "detail/FileImporter.hpp"


namespace Xeth{


class StealthKeyStore : 
    public QObject,
    protected FileStore<StealthKey, StealthKeySerializer>
{

    Q_OBJECT
    public:
        typedef FileStore<StealthKey, StealthKeySerializer> Base;
        typedef Base::Iterator Iterator;
        typedef Base::Data Data;
        typedef Base::DataSerializer DataSerializer;

    public:
        StealthKeyStore(const std::string &path);
        StealthKeyStore(const boost::filesystem::path &path);

        bool replace(const StealthKey &);

        bool insert(const StealthKey &);
        bool insert(const std::string &, const StealthKey &);
        bool insert(const char *, const StealthKey &);

        Iterator find(const char *address) const;
        Iterator find(const Ethereum::Stealth::Address &) const;

        StealthKey get(const char *address) const;

        using Base::begin;
        using Base::end;

    signals:
        void NewItem(const QString &) const;

    private:
        std::string makeAddress(const StealthKey &) const;

};


typedef FileImporter<StealthKeyStore> StealthKeyImporter;


}
